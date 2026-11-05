/* Render interpolation (remake extension). The game still runs on its
   20 frames/s clock, with 1..3 simulation ticks per frame (game speed), but
   the island view and the world map are painted at the chosen display rate
   (20, 40, 60 or 120 Hz; video.cfg "fps"; 20 = once per game frame, as the
   original). Each paint between frames blends the positions saved at the start of the last frame with the
   current ones, by the time elapsed since that frame. Motion is then smooth
   at any game speed, one frame (50 ms) behind the simulation.
   The blended values are written into the session only for the paint and
   put back right after it, so the simulation, the hit tests and the network
   hash never see them. Sprite frames stay discrete, as in the original. */

enum { RENDER_INTERP_FRAME_MS = 50, RENDER_INTERP_MAX_STEP = 64,
       PAINT_RATE_COUNT = 4 };
static const unsigned g_paint_rates[PAINT_RATE_COUNT] = {20, 40, 60, 120};
static int g_paint_rate_index = 2;

typedef struct RenderInterpPoint {
    uint16_t x, y;
    uint8_t island;
    uint8_t active;
} RenderInterpPoint;

static int g_interp_valid;
static int g_interp_screen;
static uint32_t g_interp_frame_ms;
static RenderInterpPoint g_interp_floaters[GAME_SESSION_MAX_FLOATERS];
static RenderInterpPoint g_interp_visuals[GAME_SESSION_MAX_CAST_EFFECTS];
static RenderInterpPoint g_interp_casts[GAME_SESSION_MAX_CAST_EFFECTS];
static RenderInterpPoint g_interp_bolts[32];
static uint32_t g_interp_ticks_start, g_interp_ticks_end;
/* World-map orbit phase offset (animation ticks) used by
   world_island_angle while a paint is blended; 0 otherwise. */
static float g_interp_orbit_ticks;

/* The current values swapped out during a paint. */
static RenderInterpPoint g_interp_saved_floaters[GAME_SESSION_MAX_FLOATERS];
static RenderInterpPoint g_interp_saved_visuals[GAME_SESSION_MAX_CAST_EFFECTS];
static RenderInterpPoint g_interp_saved_casts[GAME_SESSION_MAX_CAST_EFFECTS];
static RenderInterpPoint g_interp_saved_bolts[32];
static int g_interp_applied;
/* Counter time of the next paint between frames. */
static uint64_t g_interp_next_paint;
/* E2E aid: paints so far, and paints drawn blended. */
static unsigned long g_paint_count, g_paint_blended_count;

static int render_interp_screen(void)
{
    return g_game_session_valid &&
        (g_menu.screen == SCREEN_ISLAND || g_menu.screen == SCREEN_WORLD_MAP);
}

/* Start of a 20 Hz frame, before its ticks: the positions to blend from. */
static void render_interp_begin_frame(void)
{
    unsigned i;
    if (!render_interp_screen()) {
        g_interp_valid = 0;
        return;
    }
    for (i = 0; i < GAME_SESSION_MAX_FLOATERS; ++i) {
        const GameFloaterStart *f = &g_game_session.floaters[i];
        g_interp_floaters[i].x = f->x;
        g_interp_floaters[i].y = f->y;
        g_interp_floaters[i].island = f->island_index;
        g_interp_floaters[i].active = i < g_game_session.floater_count && f->is_active;
    }
    for (i = 0; i < GAME_SESSION_MAX_CAST_EFFECTS; ++i) {
        const struct GameAttackVisual *v = &g_game_session.attack_visuals[i];
        const struct GameCastEffectState *c = &g_game_session.cast_effects[i];
        g_interp_visuals[i].x = v->x;
        g_interp_visuals[i].y = v->y;
        g_interp_visuals[i].island = v->island_index;
        g_interp_visuals[i].active = v->active;
        g_interp_casts[i].x = c->effect_x;
        g_interp_casts[i].y = c->effect_y;
        g_interp_casts[i].island = 0;
        g_interp_casts[i].active = c->active;
    }
    for (i = 0; i < 32U; ++i) {
        const GameDefenseProjectile *p = &g_game_session.defense_projectiles[i];
        g_interp_bolts[i].x = p->x;
        g_interp_bolts[i].y = p->y;
        g_interp_bolts[i].island = p->island_index;
        g_interp_bolts[i].active = p->active;
    }
    g_interp_ticks_start = g_menu.animation_ticks;
    g_interp_screen = g_menu.screen;
    g_interp_frame_ms = platform_ticks_ms();
    g_interp_valid = 1;
    /* The frame's own paint is the first of the period. */
    g_interp_next_paint = platform_counter() +
        platform_counter_frequency() / g_paint_rates[g_paint_rate_index];
}

/* End of the frame: the orbit phase it reached; a screen change during the
   frame is shown at once. */
static void render_interp_end_frame(void)
{
    g_interp_ticks_end = g_menu.animation_ticks;
    if (g_menu.screen != g_interp_screen) g_interp_valid = 0;
}

/* Elapsed share of the current frame, 0..256; 256 = no blending. */
static int render_interp_alpha(void)
{
    uint32_t elapsed;
    if (g_paint_rates[g_paint_rate_index] <= 20U ||
        !g_interp_valid || !render_interp_screen() ||
        g_menu.screen != g_interp_screen) return 256;
    elapsed = platform_ticks_ms() - g_interp_frame_ms;
    if (elapsed >= RENDER_INTERP_FRAME_MS) return 256;
    return (int)(elapsed * 256U / RENDER_INTERP_FRAME_MS);
}

static uint16_t render_interp_mix(uint16_t from, uint16_t to, int alpha)
{
    int delta = (int)to - (int)from;
    return (uint16_t)((int)from + (delta * alpha) / 256);
}

static void render_interp_blend(const RenderInterpPoint *from, uint16_t *x,
                                uint16_t *y, uint8_t island, uint8_t active,
                                int alpha)
{
    int dx = (int)*x - (int)from->x;
    int dy = (int)*y - (int)from->y;
    if (!from->active || !active || from->island != island ||
        dx > RENDER_INTERP_MAX_STEP || dx < -RENDER_INTERP_MAX_STEP ||
        dy > RENDER_INTERP_MAX_STEP || dy < -RENDER_INTERP_MAX_STEP) return;
    *x = render_interp_mix(from->x, *x, alpha);
    *y = render_interp_mix(from->y, *y, alpha);
}

static void render_interp_apply(void)
{
    int alpha = render_interp_alpha();
    unsigned i;
    g_interp_applied = 0;
    g_interp_orbit_ticks = 0.0f;
    ++g_paint_count;
    if (alpha >= 256) return;
    ++g_paint_blended_count;
    for (i = 0; i < GAME_SESSION_MAX_FLOATERS; ++i) {
        GameFloaterStart *f = &g_game_session.floaters[i];
        g_interp_saved_floaters[i].x = f->x;
        g_interp_saved_floaters[i].y = f->y;
        if (i < g_game_session.floater_count)
            render_interp_blend(&g_interp_floaters[i], &f->x, &f->y,
                                f->island_index, f->is_active, alpha);
    }
    for (i = 0; i < GAME_SESSION_MAX_CAST_EFFECTS; ++i) {
        struct GameAttackVisual *v = &g_game_session.attack_visuals[i];
        struct GameCastEffectState *c = &g_game_session.cast_effects[i];
        g_interp_saved_visuals[i].x = v->x;
        g_interp_saved_visuals[i].y = v->y;
        render_interp_blend(&g_interp_visuals[i], &v->x, &v->y,
                            v->island_index, v->active, alpha);
        g_interp_saved_casts[i].x = c->effect_x;
        g_interp_saved_casts[i].y = c->effect_y;
        render_interp_blend(&g_interp_casts[i], &c->effect_x, &c->effect_y,
                            0, c->active, alpha);
    }
    for (i = 0; i < 32U; ++i) {
        GameDefenseProjectile *p = &g_game_session.defense_projectiles[i];
        g_interp_saved_bolts[i].x = p->x;
        g_interp_saved_bolts[i].y = p->y;
        render_interp_blend(&g_interp_bolts[i], &p->x, &p->y,
                            p->island_index, p->active, alpha);
    }
    if (g_menu.animation_ticks == g_interp_ticks_end)
        g_interp_orbit_ticks = -(float)(g_interp_ticks_end - g_interp_ticks_start) *
            (float)(256 - alpha) / 256.0f;
    g_interp_applied = 1;
}

static void render_interp_restore(void)
{
    unsigned i;
    g_interp_orbit_ticks = 0.0f;
    if (!g_interp_applied) return;
    g_interp_applied = 0;
    for (i = 0; i < GAME_SESSION_MAX_FLOATERS; ++i) {
        g_game_session.floaters[i].x = g_interp_saved_floaters[i].x;
        g_game_session.floaters[i].y = g_interp_saved_floaters[i].y;
    }
    for (i = 0; i < GAME_SESSION_MAX_CAST_EFFECTS; ++i) {
        g_game_session.attack_visuals[i].x = g_interp_saved_visuals[i].x;
        g_game_session.attack_visuals[i].y = g_interp_saved_visuals[i].y;
        g_game_session.cast_effects[i].effect_x = g_interp_saved_casts[i].x;
        g_game_session.cast_effects[i].effect_y = g_interp_saved_casts[i].y;
    }
    for (i = 0; i < 32U; ++i) {
        g_game_session.defense_projectiles[i].x = g_interp_saved_bolts[i].x;
        g_game_session.defense_projectiles[i].y = g_interp_saved_bolts[i].y;
    }
}

/* Paint clock: 1 when a paint between game frames is due at the chosen
   rate (only while blending can change the picture). */
static int render_interp_paint_due(void)
{
    uint64_t period = platform_counter_frequency() /
        g_paint_rates[g_paint_rate_index];
    uint64_t now = platform_counter();
    if (render_interp_alpha() >= 256) return 0;
    if (now < g_interp_next_paint) return 0;
    g_interp_next_paint = g_interp_next_paint + period > now
        ? g_interp_next_paint + period : now + period;
    return 1;
}

/* Milliseconds until the next paint, for a message loop wait. */
static uint32_t render_interp_wait_ms(void)
{
    uint32_t period = 1000U / g_paint_rates[g_paint_rate_index];
    return render_interp_alpha() >= 256 ? 10U : (period > 10U ? 10U : period / 2U + 1U);
}
