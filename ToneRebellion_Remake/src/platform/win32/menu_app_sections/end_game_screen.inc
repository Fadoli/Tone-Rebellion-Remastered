/* Menu state 7 (windows.txt "StatusScreen (winning)"): STATBKG paints ENDTEMP
   frame 0 under the endgame.pal palette; ENDGTEXT (type 38, FUN_0041b0d7)
   scrolls the endgame.txt lines inside pane 211,15..427,134. Native entry
   trigger, leave input and the ENDGPLAYER/ENDGNONP stat cards are not
   established (see behavior/end-game.md); the port enters the screen only
   through the F11 preview key. */

enum {
    END_GAME_PANE_LEFT = 211,
    END_GAME_PANE_TOP = 15,
    END_GAME_PANE_WIDTH = 216,
    END_GAME_PANE_HEIGHT = 119,
    END_GAME_LINE_PITCH = 16,
    END_GAME_MAX_LINES = 64,
    END_GAME_LINE_CAPACITY = 41,
    END_GAME_SCROLL_START = 5,
    END_GAME_SCROLL_END = 500,
    END_GAME_TICK_WRAP = 6000,
    END_GAME_TICK_RESTART = 0x1f5
};

static SpriteSheet g_end_game_template_art;
static SpriteSheet g_end_game_art;
static COLORREF g_end_game_palette[256];
static char g_end_game_lines[END_GAME_MAX_LINES][END_GAME_LINE_CAPACITY];
static unsigned g_end_game_line_count;
static unsigned g_end_game_tick;
static char g_end_game_glyph_label[32];
static int g_end_game_loaded;

/* FUN_0041b0d7: records of 40 characters, read until a line starting with
   ENDSTORY; lines starting with '*' become empty spacers. */
static void parse_end_game_text(const unsigned char *bytes, size_t length)
{
    size_t position = 0;
    g_end_game_line_count = 0;
    while (position < length && g_end_game_line_count < END_GAME_MAX_LINES) {
        char *line = g_end_game_lines[g_end_game_line_count];
        size_t out = 0;
        while (position < length && bytes[position] != '\n') {
            if (bytes[position] != '\r' && out < END_GAME_LINE_CAPACITY - 1)
                line[out++] = (char)bytes[position];
            ++position;
        }
        if (position < length) ++position;
        line[out] = '\0';
        if (strncmp(line, "ENDSTORY", 8) == 0) break;
        if (line[0] == '*') line[0] = '\0';
        ++g_end_game_line_count;
    }
}

static int load_end_game_screen(void)
{
    CobArchive archive = {0};
    const CobMember *member;
    unsigned char *bytes;
    char error[128];
    if (g_end_game_loaded) return 1;
    if (!cob_archive_open("C:\\Program Files\\Tone\\TONE01.COB", &archive,
                          error, sizeof(error))) return 0;
    if (!load_palette(&archive, "data\\endgame.pal", g_end_game_palette, NULL,
                      error, sizeof(error)) ||
        !load_sprite_sheet(&archive, "data\\endtemp.shp", g_end_game_palette,
                           &g_end_game_template_art, error, sizeof(error)) ||
        !load_sprite_sheet(&archive, "data\\endgame.shp", g_end_game_palette,
                           &g_end_game_art, error, sizeof(error))) {
        free_sprite_sheet(&g_end_game_template_art);
        free_sprite_sheet(&g_end_game_art);
        cob_archive_close(&archive);
        return 0;
    }
    cob_archive_close(&archive);
    if (!cob_archive_open("C:\\Program Files\\Tone\\TONE00.COB", &archive,
                          error, sizeof(error))) return 0;
    member = cob_archive_find(&archive, "endgame.txt");
    bytes = member == NULL ? NULL : (unsigned char *)malloc(member->length + 1);
    if (bytes != NULL &&
        cob_archive_read_member(&archive, member, bytes, member->length,
                                error, sizeof(error)))
        parse_end_game_text(bytes, member->length);
    free(bytes);
    member = cob_archive_find(&archive, "newtext.txt");
    bytes = member == NULL ? NULL : (unsigned char *)malloc(member->length + 1);
    if (bytes != NULL &&
        cob_archive_read_member(&archive, member, bytes, member->length,
                                error, sizeof(error)))
        (void)extract_help_entry(bytes, member->length, "GLYPHS",
                                 g_end_game_glyph_label,
                                 sizeof(g_end_game_glyph_label));
    free(bytes);
    cob_archive_close(&archive);
    g_end_game_loaded = 1;
    return 1;
}

static int enter_end_game_screen(void)
{
    if (!load_end_game_screen()) return 0;
    g_end_game_tick = 0;
    g_menu.screen = SCREEN_END_GAME;
    return 1;
}

/* DAT_004c2994: one step per paint; wraps to 0x1f5 once above 6000. */
static void end_game_screen_tick(void)
{
    if (++g_end_game_tick > END_GAME_TICK_WRAP)
        g_end_game_tick = END_GAME_TICK_RESTART;
}

/* FUN_00419a6b (ENDGPLAYER): steps gated by strict `tick >` thresholds.
   Ported: tribe emblem (frame 35 + player, 22,187, tick > 350), owned-glyph
   overlays (frame 19 + glyph, same spot), frame 8 at (439,188) (tick > 400)
   and the glyph count line. Not ported: the other blits and figure helper,
   score/rank lines (their inputs, ECX record and font/colour map are not
   established, see behavior/end-game.md). */
static void render_end_game_player_card(HDC dc, int tick)
{
    unsigned player = g_menu.selected_tribe < 4U ? g_menu.selected_tribe : 3U;
    unsigned glyph;
    unsigned owned = 0;
    uint16_t mask = g_game_session_valid ? g_game_session.economy[player].glyph_mask : 0;
    if (tick > 350 && g_end_game_art.frame_count > 35U + player) {
        draw_sprite(dc, &g_end_game_art, 35U + player, 22, 187);
        for (glyph = 0; glyph < 14U; ++glyph) {
            if ((mask & (1U << glyph)) == 0) continue;
            ++owned;
            if (g_end_game_art.frame_count > glyph + 19U)
                draw_sprite(dc, &g_end_game_art, glyph + 19U, 22, 187);
        }
    }
    if (tick > 400 && g_end_game_art.frame_count > 8U)
        draw_sprite(dc, &g_end_game_art, 8, 439, 188);
    if (tick > 350 && g_small_font.bytes != NULL &&
        g_end_game_glyph_label[0] != '\0') {
        char text[64];
        int width;
        (void)snprintf(text, sizeof(text), "%u %s:", owned, g_end_game_glyph_label);
        width = measure_small_text(text, strlen(text));
        draw_small_label(dc, text, (204 - width) / 2, 266, g_end_game_palette[6]);
    }
}

static void render_end_game(HDC dc)
{
    unsigned index;
    int tick = (int)g_end_game_tick;
    fill_rect(dc, 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT, RGB(0, 0, 0));
    draw_sprite(dc, &g_end_game_template_art, 0, 0, 0);
    render_end_game_player_card(dc, tick);
    if (tick <= END_GAME_SCROLL_START || tick >= END_GAME_SCROLL_END ||
        g_big_font.bytes == NULL) return;
    /* ENDGTEXT line i sits at local y = 150 - (tick - 5) + 16 i, centred in
       the 216 px pane. The font is not established; BIGFONT (h 11) is used and
       lines are drawn only when fully inside the pane (no partial clipping). */
    for (index = 0; index < g_end_game_line_count; ++index) {
        const char *line = g_end_game_lines[index];
        int y = 150 - (tick - END_GAME_SCROLL_START) +
                END_GAME_LINE_PITCH * (int)index;
        int width;
        if (line[0] == '\0' || y < 0 || y > END_GAME_PANE_HEIGHT - 11) continue;
        width = measure_big_text(line, strlen(line));
        draw_big_label(dc, line,
                       END_GAME_PANE_LEFT + (END_GAME_PANE_WIDTH - width) / 2,
                       END_GAME_PANE_TOP + y, g_end_game_palette[6]);
    }
}
