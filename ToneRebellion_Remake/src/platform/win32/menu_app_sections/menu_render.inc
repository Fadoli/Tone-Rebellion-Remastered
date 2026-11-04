static unsigned game_random(void)
{
    return tone_rng_next15(&g_random_state);
}

/* Port choice: how the 640x480 frame fills the window. INTEGER keeps every
   game pixel the same size (largest whole multiple, black bars); FIT_SHARP
   and FIT_SMOOTH fill the window keeping the aspect ratio, with nearest
   pixel (uneven pixel sizes) or HALFTONE filtering (blurred, about 5 ms of
   CPU per frame, bench/gameplay_hotspots.md). F12 and the window menu cycle
   it; saves\video.cfg keeps it. */
enum { SCALE_INTEGER, SCALE_FIT_SHARP, SCALE_FIT_SMOOTH, SCALE_MODE_COUNT };
static int g_scale_mode = SCALE_FIT_SHARP;

static int video_settings_path(char *path, size_t capacity)
{
    char directory[MAX_PATH];
    if (!save_directory(directory, sizeof(directory))) return 0;
    (void)snprintf(path, capacity, "%s/video.cfg", directory);
    return 1;
}

static void save_video_settings(void)
{
    char path[MAX_PATH];
    FILE *file;
    if (!video_settings_path(path, sizeof(path))) return;
    file = fopen(path, "w");
    if (file == NULL) return;
    (void)fprintf(file, "scale %d\n", g_scale_mode);
    (void)fclose(file);
    platform_storage_changed();
}

static void load_video_settings(void)
{
    char path[MAX_PATH];
    FILE *file;
    int mode;
    if (!video_settings_path(path, sizeof(path))) return;
    file = fopen(path, "r");
    if (file == NULL) return;
    if (fscanf(file, "scale %d", &mode) == 1 && mode >= 0 &&
        mode < SCALE_MODE_COUNT)
        g_scale_mode = mode;
    (void)fclose(file);
}

static int logical_viewport(int client_width, int client_height, RECT *viewport)
{
    if (client_width <= 0 || client_height <= 0 || viewport == NULL) return 0;
    if (g_scale_mode == SCALE_INTEGER) {
        int factor_x = client_width / LOGICAL_WIDTH;
        int factor_y = client_height / LOGICAL_HEIGHT;
        int factor = factor_x < factor_y ? factor_x : factor_y;
        /* Below 640x480 there is no whole multiple: fall back to fitting. */
        if (factor >= 1) {
            viewport->left = (client_width - factor * LOGICAL_WIDTH) / 2;
            viewport->top = (client_height - factor * LOGICAL_HEIGHT) / 2;
            viewport->right = viewport->left + factor * LOGICAL_WIDTH;
            viewport->bottom = viewport->top + factor * LOGICAL_HEIGHT;
            return 1;
        }
    }
    if ((int64_t)client_width * LOGICAL_HEIGHT <=
        (int64_t)client_height * LOGICAL_WIDTH) {
        viewport->left = 0;
        viewport->right = client_width;
        viewport->top = (client_height - client_width * LOGICAL_HEIGHT / LOGICAL_WIDTH) / 2;
        viewport->bottom = viewport->top + client_width * LOGICAL_HEIGHT / LOGICAL_WIDTH;
    } else {
        viewport->top = 0;
        viewport->bottom = client_height;
        viewport->left = (client_width - client_height * LOGICAL_WIDTH / LOGICAL_HEIGHT) / 2;
        viewport->right = viewport->left + client_height * LOGICAL_WIDTH / LOGICAL_HEIGHT;
    }
    return viewport->right > viewport->left && viewport->bottom > viewport->top;
}

static int template_is_in_state(const WindowTemplate *window, int state)
{
    size_t i;
    for (i = 0; i < window->state_count; ++i) {
        if (window->states[i] == state) return 1;
    }
    return 0;
}

static int template_help_index(const WindowTemplate *window)
{
    if (strcmp(window->name, "RESUME") == 0) return HELP_MAIN_RESUME;
    if (strcmp(window->name, "NEWGAME") == 0) return HELP_MAIN_NEWGAME;
    if (strcmp(window->name, "LOADGAME") == 0) return HELP_MAIN_LOAD;
    if (strcmp(window->name, "EXITAPP") == 0) return HELP_MAIN_EXIT;
    return -1;
}

static int template_caption_index(const WindowTemplate *window)
{
    if (strcmp(window->message_destination, "WINMGR") == 0 &&
        window->send_message[0] == 1 && window->send_message[1] == 0) return 6;
    if (strcmp(window->message_destination, "MASTER") != 0) return -1;
    if (window->send_message[0] == 52) return 7;
    if (window->send_message[0] == 53) return 5;
    if (window->send_message[0] == 55) return 4;
    if (window->send_message[0] >= 60 && window->send_message[0] <= 63)
        return window->send_message[0] - 60;
    return -1;
}

static void draw_configured_buttons(RenderSurface *surface, int state, const char *shape_id,
                                    SpriteSheet *sheet)
{
    size_t i;
    for (i = 0; i < g_window_catalog.count; ++i) {
        const WindowTemplate *window = &g_window_catalog.windows[i];
        int frame;
        if (!template_is_in_state(window, state) ||
            strcmp(window->shape_id, shape_id) != 0 || window->shape_frame < 0) continue;
        /* FUN_004489c0 (message 1) sends message 2 to RESUME when the resume
           file has no valid header; for the generic button class message 2
           clears +0x3c/+0x38 and FUN_0042a55d then skips the draw (hidden). */
        if (state == 0 && strcmp(window->name, "RESUME") == 0 &&
            !g_resume_available) continue;
        frame = window->shape_frame;
        if (state == 0) {
            int help_index = template_help_index(window);
            int hovered = window_catalog_hover_frame(
                window->shape_frame, help_index, g_hovered_help) !=
                window->shape_frame;
            frame = window_catalog_control_frame(window, hovered);
        } else if (state == 1) {
            int caption_index = template_caption_index(window);
            int hovered = window_catalog_hover_frame(
                window->shape_frame, caption_index,
                g_hovered_newgame_text) != window->shape_frame;
            frame = window_catalog_control_frame(window, hovered);
        }
        draw_sprite(surface, sheet, (uint32_t)frame, window->pane.left, window->pane.top);
        /* BACKGRND also shows SHAPEFRAME + 1, the game title (TITSCRN frame
           1, 331x145, offset 158,144), forty pixels higher: (158, 104).
           Outside state 8 the SceneWindow paint FUN_0042af35 draws it with
           the stars and the credits scroll (title_credits.inc); FUN_0042aafa
           draws it statically (REA haiku 2026-11-04, ev_ae3113dd). */
        if (strcmp(window->name, "BACKGRND") == 0) {
            if (state == 0)
                render_title_credits(surface, sheet, (uint32_t)window->shape_frame + 1U);
            else if ((uint32_t)window->shape_frame + 1U < sheet->frame_count)
                draw_sprite(surface, sheet, (uint32_t)window->shape_frame + 1U,
                            window->pane.left, window->pane.top - 0x28);
        }
    }
}

static void render_main_menu(RenderSurface *surface)
{
    fill_rect(surface, 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT, RGB(0, 0, 0));
    draw_configured_buttons(surface, 0, "TITSCRN", &g_title_art);
    draw_hover_help(surface);
}

static void render_new_game(RenderSurface *surface)
{
    static const POINT tribe_centers[4] = {{170, 240}, {320, 90}, {470, 240}, {320, 390}};
    static const int orbit_radii[3] = {150, 170, 130};
    int tribe;
    int ring;
    int angle_step;
    fill_rect(surface, 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT, RGB(0, 0, 0));
    draw_sprite(surface, &g_new_background, 0, 0, 0);
    for (ring = 0; ring < 3; ++ring) {
        const int radius = orbit_radii[ring];
        COLORREF color = g_newgame_palette[0];
        for (angle_step = 2; angle_step < 16; ++angle_step) {
            float angle = (float)(angle_step * 5) * 0.017453292f;
            int dx = (int)(sin((double)angle) * radius);
            int dy = (int)(cos((double)angle) * radius);
            const int xs[4] = {315 + dx, 315 - dx, 315 - dx, 315 + dx};
            const int ys[4] = {236 + dy, 236 + dy, 236 - dy, 236 - dy};
            int quadrant;
            for (quadrant = 0; quadrant < 4; ++quadrant)
                fill_rect(surface, xs[quadrant], ys[quadrant],
                          xs[quadrant] + 10, ys[quadrant] + 8, color);
            /* The original emits ten randomized pixels for each quadrant,
               using FUN_00474b90's LCG. Its palette byte is 0xb6..0xc6. */
            if (ring <= g_menu.world_index) {
                int speck;
                for (speck = 0; speck < 10; ++speck) {
                    int side;
                    for (side = 0; side < 4; ++side) {
                        int sx;
                        int sy;
                        unsigned color = game_random() % 17u + 0xb6u;
                        unsigned y_jitter = game_random() % 6u;
                        unsigned x_jitter = game_random() % 7u;
                        sx = (side == 0 || side == 3 ? 325 + dx : 325 - dx) - (int)x_jitter;
                        sy = (side < 2 ? 244 + dy : 244 - dy) - (int)y_jitter;
                        render_surface_set_pixel(surface, sx, sy,
                            colorref_pixel(g_newgame_palette[color]));
                    }
                }
            }
        }
    }
    /* NEWGAMWND contributes the 640x73 frame-0 footer at y=407; do not draw
       it twice or let its unmapped hover index select frame 1. */
    draw_configured_buttons(surface, 1, "NEWBUTT", &g_new_buttons);
    draw_sprite(surface, &g_realm_art, (uint32_t)g_menu.selected_tribe, 60, 40);
    draw_sprite(surface, &g_realm_art,
                (uint32_t)((g_menu.selected_tribe + 1) % 4), 140, 40);
    draw_sprite(surface, &g_difficulty_art, (uint32_t)g_menu.difficulty, 320, 240);
    {
        uint32_t tribe_frame = (uint32_t)(g_menu.selected_tribe * 17);
        uint32_t animation_frame = tribe_frame + ((g_menu.animation_ticks / 2u) % 16u) + 1u;
        unsigned game_tick = g_menu.animation_ticks / 2u;
        int floater_y = 38 + (int)(sin((double)(game_tick % 24u) *
                                       0.261799388) * 5.0) -
                        (g_menu.selected_tribe == 3 ? 5 : 0);
        /* FUN_0044ec5d draws the tribe's base frame and a cycling overlay
           frame at the same point; drawing only the overlay loses half of
           the original floater artwork. */
        draw_sprite(surface, &g_big_floaters, tribe_frame, 530, floater_y);
        draw_sprite(surface, &g_big_floaters, animation_frame, 530, floater_y);
    }
    for (tribe = 0; tribe < 4; ++tribe) {
        draw_sprite(surface, &g_glyphs,
                    (uint32_t)(tribe * 20 + (g_menu.animation_ticks / 3u) % 20u),
                    tribe_centers[tribe].x, tribe_centers[tribe].y);
    }
    draw_tribe_descriptions(surface);
    draw_hover_help(surface);
    draw_newgame_text(surface);
}

/* FUN_0046290d (per-island world tick) moves the orbit radius +0x29d8 during
   the end sequence: with DAT_006191b4 == 3 past tick 99 (t = tick - 100) or
   == 4 before tick 0x3c (t = tick + 200), a radius above 200 changes by
   -(t / 70) when the local player's +0x90 latch is clear (islands close on
   the centre) or by (t / 70) / 3 when it is set (they drift away), clamped
   to [-20, 20] per tick (REA haiku 2026-11-04, ev_d98059a7). WORLDPOS stays
   immutable; the shift is kept here per island and cleared outside the
   sequence. Display only, so it is not saved. */
static int32_t g_world_range_shift[WORLD_MAP_MAX_ISLANDS];

static int32_t world_island_range(const WorldIsland *island)
{
    const WorldDefinition *world;
    ptrdiff_t index;
    if (g_menu.world_index < 0 || g_menu.world_index >= g_menu.world_map.world_count)
        return island->range;
    world = &g_menu.world_map.worlds[g_menu.world_index];
    index = island - world->islands;
    if (index < 0 || (size_t)index >= world->island_count ||
        index >= WORLD_MAP_MAX_ISLANDS) return island->range;
    return island->range + g_world_range_shift[index];
}

static void world_map_tick_orbit_ranges(void)
{
    const WorldDefinition *world;
    int state;
    int tick;
    int t = -1;
    size_t index;
    if (!g_game_session_valid || g_menu.world_index < 0 ||
        g_menu.world_index >= g_menu.world_map.world_count) return;
    world = &g_menu.world_map.worlds[g_menu.world_index];
    state = g_game_session.world_sequence_state;
    tick = g_game_session.world_sequence_tick;
    if (state == 0) {
        memset(g_world_range_shift, 0, sizeof(g_world_range_shift));
        return;
    }
    if (state == 3 && tick > 99) t = tick - 100;
    else if (state == 4 && tick < 0x3c) t = tick + 200;
    if (t == -1) return;
    if (g_menu.selected_tribe >= 0 &&
        g_menu.selected_tribe < GAME_START_PLAYER_COUNT &&
        g_game_session.economy[g_menu.selected_tribe].defeat_latched)
        t = (t / 0x46) / 3;
    else
        t = -(t / 0x46);
    if (t < -0x14) t = -0x14;
    if (t > 0x14) t = 0x14;
    for (index = 0; index < world->island_count && index < WORLD_MAP_MAX_ISLANDS;
         ++index) {
        if (world->islands[index].range + g_world_range_shift[index] > 200)
            g_world_range_shift[index] += t;
    }
}

static float world_island_angle(const WorldIsland *island)
{
    /* FUN_00471536 uses angle - phase. Keep WORLDPOS immutable and advance
       the phase by 0.25 degree per 33 ms remake animation tick. */
    return ((float)island->angle_degrees -
            (float)(g_menu.animation_ticks % 1440u) * 0.25f) * 0.017453277f;
}

/* FUN_00471536 depth key (record +0x10, minus its 3000 bias):
   sin(angle) * range * 0.06. */
static float world_island_depth(const WorldIsland *island)
{
    return (float)(sin((double)world_island_angle(island)) *
                   world_island_range(island) * 0.06000000238418579);
}

/* FUN_00471b34 qsorts the display list with FUN_0046fee0 (0x46fee0): bridge
   records before islands, then a larger key first. A larger key is higher on
   screen (further back), so islands are drawn back to front and
   FUN_00472013, which scans the list from the end, hits the front-most one
   first. Ties keep record order here (qsort leaves them unspecified). */
static size_t world_island_draw_order(const WorldDefinition *world,
                                      size_t order[WORLD_MAP_MAX_ISLANDS])
{
    float keys[WORLD_MAP_MAX_ISLANDS];
    size_t count = world->island_count < WORLD_MAP_MAX_ISLANDS
        ? world->island_count : WORLD_MAP_MAX_ISLANDS;
    size_t i;
    for (i = 0; i < count; ++i) {
        size_t j = i;
        float key = world_island_depth(&world->islands[i]);
        while (j > 0 && keys[j - 1] < key) {
            keys[j] = keys[j - 1];
            order[j] = order[j - 1];
            --j;
        }
        keys[j] = key;
        order[j] = i;
    }
    return count;
}

static void world_island_position(const WorldIsland *island, int *x, int *y)
{
    const float scale_x = 0.12999999523162842f;
    const float scale_y = 0.06000000238418579f;
    float angle = world_island_angle(island);
    int32_t range = world_island_range(island);
    float x_delta = (float)(cos((double)angle) * range * scale_x);
    float y_delta = (float)(sin((double)angle) * range * scale_y);
    float z_delta = (float)island->z * scale_y;
    /* FUN_00470259 sets the centre to half the WORLDVIEW pane (0 0 639 479,
       inclusive coordinates as the other Iw* panes): cx = 639 / 2 and
       cy = 479 / 2 + 15 (this+0x784/0x786). */
    *x = 319 + (int)(x_delta + 0.5f);
    *y = 254 - (int)(y_delta + z_delta + 0.5f);
}

static uint8_t world_map_player_mask(void)
{
    if (g_game_session.config.selected_tribe >= GAME_START_PLAYER_COUNT) return 0;
    return (uint8_t)(1U << g_game_session.config.selected_tribe);
}

/* Stable within a rendered frame but advanced by the map's 33 ms timer.
   Drawing must not consume the gameplay RNG because WM_PAINT can run for
   reasons unrelated to simulation time. */
static uint32_t world_map_visual_sample(uint32_t tick, size_t bridge_index,
                                        int step, int spark)
{
    uint32_t value = tick * UINT32_C(0x9e3779b9) +
                     (uint32_t)bridge_index * UINT32_C(0x85ebca6b) +
                     (uint32_t)step * UINT32_C(0xc2b2ae35) +
                     (uint32_t)spark * UINT32_C(0x27d4eb2f);
    value ^= value >> 16;
    value *= UINT32_C(0x7feb352d);
    value ^= value >> 15;
    value *= UINT32_C(0x846ca68b);
    return value ^ (value >> 16);
}

static uint32_t world_island_frame_index(size_t island_index, int shape_id,
                                         int hovered)
{
    int offset;
    if (!g_game_session_valid || island_index >= UINT8_MAX || shape_id < 0) return UINT32_MAX;
    offset = game_session_world_map_frame_offset(
        &g_game_session, (uint8_t)island_index, world_map_player_mask(),
        hovered);
    return offset < 0 ? UINT32_MAX : (uint32_t)offset + (uint32_t)shape_id;
}

/* FUN_00472013 walks display items back-to-front and checks the opaque SHP
   bounds prepared by FUN_00405e11. The remake uses the same opaque bounds. */
