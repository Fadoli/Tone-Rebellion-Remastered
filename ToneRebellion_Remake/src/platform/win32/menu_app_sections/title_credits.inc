/* Title screen animation, drawn by the SceneWindow paint FUN_0042af35 for the
   window BACKGRND outside state 8 (REA haiku 2026-11-04, ev_de222a9d,
   ev_550c7247, ev_ad3a187c, ev_8b656df8):
   - twinkling stars (FUN_0042a6c9) inside the window rect inset by 20;
   - credits.txt (FUN_0042ac69, TONE00.COB) scrolling up 1 px per paint once
     the counter DAT_0049d64c, set to -600 on window entry, turns positive;
     the title (TITSCRN frame 1) scrolls away first and comes back at the end.
   No input resets the counter: the text simply starts after 600 paints. */

enum {
    TITLE_CREDITS_MAX_LINES = 25,
    TITLE_CREDITS_DRAWN_LINES = 24,
    TITLE_CREDITS_LINE_CAPACITY = 0x50,
    TITLE_CREDITS_START = -600,
    TITLE_CREDITS_END = 2230,
    TITLE_CREDITS_LEFT = 100,
    TITLE_CREDITS_TOP = 20,
    TITLE_CREDITS_RIGHT = 540,
    TITLE_CREDITS_BOTTOM = 270,
    TITLE_STAR_SLOTS = 50,
    TITLE_STAR_LEFT = 20,
    TITLE_STAR_TOP = 20,
    TITLE_STAR_RIGHT = 619,
    TITLE_STAR_BOTTOM = 459
};

static COLORREF g_title_palette[256];
static char g_title_credit_lines[TITLE_CREDITS_MAX_LINES][TITLE_CREDITS_LINE_CAPACITY];
static unsigned g_title_credit_count;
static int g_title_credits_loaded;
static int g_title_credits_tick = TITLE_CREDITS_START;
static int16_t g_title_star_age[TITLE_STAR_SLOTS];
static int16_t g_title_star_x[TITLE_STAR_SLOTS];
static int16_t g_title_star_y[TITLE_STAR_SLOTS];
static int g_title_stars_ready;
static uint32_t g_title_star_seed = 1U;

/* Line offsets at 0x49d6a0 + i * 0x54 (read_bytes), summed once by the
   loader: 450 px below the rect top for the first line. */
static const int g_title_credit_pitch[TITLE_CREDITS_DRAWN_LINES] = {
    450, 40, 30, 30, 120, 40, 30, 120, 40, 30, 30, 120,
    40, 230, 50, 50, 80, 50, 50, 80, 50, 50, 50, 120};

/* FUN_0040f5b3 accepts a line unless it starts with ' ', '\t', '\n', ';' or
   "//", then trims trailing bytes below '!'. "\r" is accepted, so the blank
   line between the credits and the story takes an entry and the last story
   line ("Ou du moins le croyait-on...") is entry 24, never drawn by the
   24-line loop. Parsing stops at ENDCREDITS. */
static void parse_title_credits(const unsigned char *bytes, size_t length)
{
    size_t position = 0;
    g_title_credit_count = 0;
    while (position < length && g_title_credit_count < TITLE_CREDITS_MAX_LINES) {
        size_t start = position;
        size_t end;
        size_t out = 0;
        char *line = g_title_credit_lines[g_title_credit_count];
        while (position < length && bytes[position] != '\n') ++position;
        end = position;
        if (position < length) ++position;
        if (start == end || bytes[start] == ' ' || bytes[start] == '\t' ||
            bytes[start] == ';' ||
            (end - start >= 2 && bytes[start] == '/' && bytes[start + 1] == '/'))
            continue;
        while (end > start && bytes[end - 1] < '!') --end;
        if (end - start == 10 && memcmp(bytes + start, "ENDCREDITS", 10) == 0) break;
        while (start < end && out < TITLE_CREDITS_LINE_CAPACITY - 1)
            line[out++] = (char)bytes[start++];
        line[out] = '\0';
        ++g_title_credit_count;
    }
}

static void load_title_credits(void)
{
    CobArchive archive = {0};
    const CobMember *member;
    unsigned char *bytes;
    char error[128];
    if (g_title_credits_loaded) return;
    g_title_credits_loaded = 1;
    if (!cob_archive_open(game_file_path("TONE00.COB"), &archive,
                          error, sizeof(error))) return;
    member = cob_archive_find(&archive, "credits.txt");
    bytes = member == NULL ? NULL : (unsigned char *)malloc(member->length + 1);
    if (bytes != NULL &&
        cob_archive_read_member(&archive, member, bytes, member->length,
                                error, sizeof(error)))
        parse_title_credits(bytes, member->length);
    free(bytes);
    cob_archive_close(&archive);
}

/* FUN_00474b90: the CRT rand LCG. The native seed is shared with the rest of
   the game; the title keeps its own. */
static unsigned title_star_rand(void)
{
    g_title_star_seed = g_title_star_seed * 0x343fdU + 0x269ec3U;
    return (g_title_star_seed >> 16) & 0x7fffU;
}

/* Called once per 20 Hz frame (one native paint). */
static void title_credits_tick(void)
{
    int width = TITLE_STAR_RIGHT - TITLE_STAR_LEFT;
    int height = TITLE_STAR_BOTTOM - TITLE_STAR_TOP;
    int count = width * height / 6000;
    int spawned = 0;
    int k;
    if (g_menu.screen != SCREEN_MAIN_MENU) {
        /* Window message 1 (FUN_0042ad76) resets the counter on entry. */
        g_title_credits_tick = TITLE_CREDITS_START;
        return;
    }
    if (++g_title_credits_tick > TITLE_CREDITS_END)
        g_title_credits_tick = TITLE_CREDITS_START;
    if (!g_title_stars_ready) {
        for (k = 0; k < TITLE_STAR_SLOTS; ++k) g_title_star_age[k] = -1;
        g_title_stars_ready = 1;
    }
    if (count > TITLE_STAR_SLOTS) count = TITLE_STAR_SLOTS;
    /* FUN_0042a6c9: one spawn per paint into the first free slot, at a
       random rect-relative point; a star lives 32 paints. The obstacle
       rects (DAT_005970c0) are set only in state 1. */
    for (k = 0; k < count; ++k) {
        if (g_title_star_age[k] == -1) {
            if (spawned) continue;
            spawned = 1;
            g_title_star_age[k] = 0;
            g_title_star_x[k] = (int16_t)((float)title_star_rand() * (float)(width + 1) / 32768.0f);
            g_title_star_y[k] = (int16_t)((float)title_star_rand() * (float)(height + 1) / 32768.0f);
            continue;
        }
        if (++g_title_star_age[k] == 0x20) g_title_star_age[k] = -1;
    }
}

/* FUN_0041081b: palette index nearest (6-bit RGB, indices 0..254) to the
   ramp step (7k, 7k, 20 + 6k), k = 0..7: dark blue up to pale blue. */
static COLORREF title_star_color(int step)
{
    int i;
    int best = 0;
    int best_distance = -1;
    for (i = 0; i < 255; ++i) {
        int r = (int)(GetRValue(g_title_palette[i]) * 63u / 255u) - 7 * step;
        int g = (int)(GetGValue(g_title_palette[i]) * 63u / 255u) - 7 * step;
        int b = (int)(GetBValue(g_title_palette[i]) * 63u / 255u) - (20 + 6 * step);
        int distance = r * r + g * g + b * b;
        if (best_distance < 0 || distance < best_distance) {
            best = i;
            best_distance = distance;
            if (distance == 0) break;
        }
    }
    return g_title_palette[best];
}

static void render_title_credits(RenderSurface *surface, const SpriteSheet *sheet,
                                 uint32_t logo_frame)
{
    int tick = g_title_credits_tick;
    int saved;
    int logo_y = 0;
    int draw_logo = 1;
    int k;
    load_title_credits();
    /* Stars: brightness step min(7, (age > 16 ? 32 - age : age) / 2); at age
       31 the native redraws the saved backdrop pixel, i.e. nothing here. */
    if (g_title_stars_ready) {
        for (k = 0; k < TITLE_STAR_SLOTS; ++k) {
            int age = g_title_star_age[k];
            int step;
            int x;
            int y;
            if (age < 0 || age == 0x1f) continue;
            step = (age > 16 ? 0x20 - age : age) / 2;
            if (step > 7) step = 7;
            x = TITLE_STAR_LEFT + g_title_star_x[k];
            y = TITLE_STAR_TOP + g_title_star_y[k];
            if (x > TITLE_STAR_RIGHT || y > TITLE_STAR_BOTTOM) continue;
            fill_rect(surface, x, y, x + 1, y + 1, title_star_color(step));
        }
    }
    saved = render_surface_save(surface);
    render_surface_intersect_clip(surface, TITLE_CREDITS_LEFT, TITLE_CREDITS_TOP,
                                  TITLE_CREDITS_RIGHT + 1, TITLE_CREDITS_BOTTOM + 1);
    /* FUN_0042b239: the title at rect-relative (-100, y), y = -60 before the
       scroll, -60 - P while it leaves, (T - P) - 60 when it comes back. */
    if (tick <= 0) logo_y = -60;
    else if (tick < 300) logo_y = -60 - tick;
    else if (tick > TITLE_CREDITS_END - 280) logo_y = (TITLE_CREDITS_END - tick) - 60;
    else draw_logo = 0;
    if (draw_logo && logo_frame < sheet->frame_count)
        draw_sprite(surface, sheet, logo_frame, 0, TITLE_CREDITS_TOP + logo_y);
    /* Line i at rect-relative y = sum(pitch[0..i]) - P, drawn while
       -10 < y < 300, centred in the 440 px rect. The text object 0x4c2f30
       keeps font handle 0 (default font, SMFONT here) and pen 6. */
    if (tick > 0 && g_small_font.bytes != NULL) {
        int y = 0;
        COLORREF color = native_text_color(g_title_palette, 6);
        for (k = 0; k < TITLE_CREDITS_DRAWN_LINES; ++k) {
            const char *line;
            int line_y;
            y += g_title_credit_pitch[k];
            if ((unsigned)k >= g_title_credit_count) break;
            line = g_title_credit_lines[k];
            line_y = y - tick;
            if (line[0] == '\0' || line_y <= -10 || line_y >= 300) continue;
            /* Text ignores the surface clip: draw into the clip rectangle
               itself, as the native glyph blit clips to the rect. */
            if (surface->width > TITLE_CREDITS_RIGHT &&
                surface->height > TITLE_CREDITS_BOTTOM)
                (void)bitmap_font_render_pixels(&g_small_font, line,
                    surface->pixels + (size_t)TITLE_CREDITS_TOP * (size_t)surface->stride +
                        TITLE_CREDITS_LEFT,
                    TITLE_CREDITS_RIGHT - TITLE_CREDITS_LEFT + 1,
                    TITLE_CREDITS_BOTTOM - TITLE_CREDITS_TOP + 1,
                    (size_t)surface->stride,
                    (TITLE_CREDITS_RIGHT - TITLE_CREDITS_LEFT -
                     (int)measure_small_text(line, strlen(line))) / 2,
                    line_y, colorref_pixel(color));
        }
    }
    (void)render_surface_restore(surface, saved);
}
