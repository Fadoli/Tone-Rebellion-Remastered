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
    END_GAME_TICK_RESTART = 0x1f5,
    END_GAME_MULTIPLAYER_SESSION = 0
};

static SpriteSheet g_end_game_template_art;
static SpriteSheet g_end_game_art;
static COLORREF g_end_game_palette[256];
static char g_end_game_lines[END_GAME_MAX_LINES][END_GAME_LINE_CAPACITY];
static unsigned g_end_game_line_count;
static unsigned g_end_game_tick;
/* newtext.txt keys read by FUN_00419a6b / FUN_0041a8df. */
enum { EGT_POINTS, EGT_IVISIT, EGT_GLYPHS, EGT_SHADSTR, EGT_FLOTTRIB,
       EGT_FLOTLOSS, EGT_TROFTHE, EGT_RANK0, EGT_LSTREN1 = EGT_RANK0 + 10,
       EGT_COUNT = EGT_LSTREN1 + 5 };
static char g_end_game_text[EGT_COUNT][48];
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
                                error, sizeof(error))) {
        static const char *const fixed_keys[EGT_RANK0] = {
            "POINTS", "IVISIT", "GLYPHS", "SHADSTR", "FLOTTRIB", "FLOTLOSS",
            "TROFTHE"
        };
        unsigned int key;
        char name[16];
        for (key = 0; key < EGT_COUNT; ++key) {
            if (key < EGT_RANK0) {
                (void)snprintf(name, sizeof(name), "%s", fixed_keys[key]);
            } else if (key < EGT_LSTREN1) {
                (void)snprintf(name, sizeof(name), "RANK%u", key - EGT_RANK0);
            } else {
                (void)snprintf(name, sizeof(name), "LSTREN%u",
                               key - EGT_LSTREN1 + 1U);
            }
            (void)extract_help_entry(bytes, member->length, name,
                                     g_end_game_text[key],
                                     sizeof(g_end_game_text[key]));
        }
    }
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

/* Literal palette indices written to the pen object by FUN_00419a6b before
   each line; the tribe colour map is 1 -> 0xda, 2 -> 100, 3 -> 0xa7, else 0xcf. */
static unsigned end_game_tribe_color(unsigned player)
{
    return player == 1U ? 0xdaU : player == 2U ? 100U : player == 3U ? 0xa7U : 0xcfU;
}

static void end_game_text(HDC dc, const char *text, int x, int y, unsigned color)
{
    if (g_small_font.bytes == NULL || text[0] == '\0') return;
    draw_small_label(dc, text, x, y, g_end_game_palette[color & 0xffU]);
}

static void end_game_text_centered(HDC dc, const char *text, int center,
                                   int y, unsigned color)
{
    if (g_small_font.bytes == NULL) return;
    end_game_text(dc, text, center - measure_small_text(text, strlen(text)) / 2,
                  y, color);
}

/* Tribe noun: FUN_00419a6b picks xTark / xTarks by count; the plural is the
   singular plus "s" in the string table at 0x49d008. */
static void end_game_tribe_noun(char *out, size_t capacity, unsigned player,
                                int plural)
{
    (void)snprintf(out, capacity, plural ? "%ss" : "%s", g_tribe_names[player]);
}

/* FUN_00419a6b (ENDGPLAYER): steps gated by strict `tick >` thresholds, pane
   at the screen origin. Level L (DAT_004bf11c) and DAT_004bf118 have no writer
   in the binary, so L = 0 and the first emblem frame is min(0 + 5, 7). Not
   ported: the 410x175 figure helper (FUN_00428191, asset unknown) and the
   player-name line (DAT_004beff0 table, writers unknown). */
static void render_end_game_player_card(HDC dc, int tick)
{
    unsigned player = g_menu.selected_tribe < 4U ? g_menu.selected_tribe : 3U;
    unsigned glyph;
    unsigned color = end_game_tribe_color(player);
    uint16_t mask = g_game_session_valid ? g_game_session.economy[player].glyph_mask : 0;
    GameEndGameScore score;
    char text[96];
    char noun[24];
    if (!g_game_session_valid ||
        !game_session_end_game_score(&g_game_session, (uint8_t)player, &score))
        return;
    if (tick > 250 && g_end_game_art.frame_count > 5U)
        draw_sprite(dc, &g_end_game_art, 5, 31, 20);
    if (tick > 300 && g_end_game_art.frame_count > 0U)
        draw_sprite(dc, &g_end_game_art, 0, 483, 19);
    if (tick > 350 && g_end_game_art.frame_count > 35U + player) {
        draw_sprite(dc, &g_end_game_art, 35U + player, 22, 187);
        for (glyph = 0; glyph < 14U; ++glyph) {
            if ((mask & (1U << glyph)) == 0) continue;
            if (g_end_game_art.frame_count > glyph + 19U)
                draw_sprite(dc, &g_end_game_art, glyph + 19U, 22, 187);
        }
    }
    if (tick > 400 && g_end_game_art.frame_count > 8U)
        draw_sprite(dc, &g_end_game_art, 8, 439, 188);
    if (tick > 500 && g_end_game_art.frame_count > 9U + score.grade)
        draw_sprite(dc, &g_end_game_art, 9U + score.grade, 239, 141);
    if (tick > 500 && g_initial_floater_bodies[player].frame_count > 0U) {
        /* FUN_00428191 -> FUN_0042704b draws the tribe's floater sprite at
           (410,175), scale 1.0; legs frame 0 and the body's first frame
           are an approximation (fltdraw shape table not established). */
        if (g_initial_floater_legs[player].frame_count > 0U)
            draw_sprite(dc, &g_initial_floater_legs[player], 0, 410, 175);
        draw_sprite(dc, &g_initial_floater_bodies[player], 0, 410, 175);
    }
    if (tick > 250) {
        (void)snprintf(text, sizeof(text), "%d %s:",
                       (int)score.visited_islands - 1,
                       g_end_game_text[EGT_IVISIT]);
        end_game_text_centered(dc, text, 102, 131, 0x9bU);
        (void)snprintf(text, sizeof(text), "%d %s", (int)score.points_visited,
                       g_end_game_text[EGT_POINTS]);
        end_game_text_centered(dc, text, 102, 141, 0xddU);
    }
    if (tick > 300) {
        (void)snprintf(text, sizeof(text), "%s:", g_end_game_text[EGT_LSTREN1]);
        end_game_text_centered(dc, text, 535, 131, 0xa0U);
        (void)snprintf(text, sizeof(text), "%d %s", (int)score.points_level,
                       g_end_game_text[EGT_POINTS]);
        end_game_text_centered(dc, text, 535, 141, 0xddU);
    }
    if (tick > 350) {
        (void)snprintf(text, sizeof(text), "%u %s:", (unsigned)score.glyphs,
                       g_end_game_text[EGT_GLYPHS]);
        end_game_text_centered(dc, text, 102, 266, 0x9cU);
        (void)snprintf(text, sizeof(text), "%d %s", (int)score.points_glyphs,
                       g_end_game_text[EGT_POINTS]);
        end_game_text_centered(dc, text, 102, 276, 0xddU);
    }
    if (tick > 400) {
        static const int kill_x[4] = {458, 506, 551, 593};
        unsigned pair;
        (void)snprintf(text, sizeof(text), "%u %s", (unsigned)score.shadow_total,
                       g_end_game_text[EGT_SHADSTR]);
        end_game_text(dc, text, 454, 167, 0xa0U);
        (void)snprintf(text, sizeof(text), "%s:", g_end_game_text[EGT_POINTS]);
        end_game_text(dc, text, 454, 177, 0xddU);
        for (pair = 0; pair < 4U; ++pair) {
            (void)snprintf(text, sizeof(text), "%d", (int)score.points_kills[pair]);
            end_game_text(dc, text, kill_x[pair], 236, 0xddU);
        }
    }
    if (tick > 425) {
        end_game_tribe_noun(noun, sizeof(noun), player, score.tribe_floaters != 1U);
        (void)snprintf(text, sizeof(text), score.tribe_floaters == 1U
                           ? "%u %s %s:" : "%u %s %s",
                       (unsigned)score.tribe_floaters, noun,
                       g_end_game_text[EGT_FLOTTRIB]);
        end_game_text(dc, text, 454, 258, color);
        (void)snprintf(text, sizeof(text), "%d %s:", (int)score.points_tribe,
                       g_end_game_text[EGT_POINTS]);
        end_game_text(dc, text, 458, 268, 0xddU);
    }
    if (tick > 450) {
        end_game_tribe_noun(noun, sizeof(noun), player, score.losses != 1U);
        (void)snprintf(text, sizeof(text), score.losses == 1U
                           ? "%u %s %s:" : "%u %s %s", (unsigned)score.losses,
                       noun, g_end_game_text[EGT_FLOTLOSS]);
        end_game_text(dc, text, 454, 283, color);
        (void)snprintf(text, sizeof(text), "%d %s", -(int)score.points_losses,
                       g_end_game_text[EGT_POINTS]);
        end_game_text(dc, text, 458, 293, 0xddU);
    }
    if (tick > 500) {
        end_game_tribe_noun(noun, sizeof(noun), player, 1);
        (void)snprintf(text, sizeof(text), "%s %s", g_end_game_text[EGT_TROFTHE], noun);
        end_game_text_centered(dc, text, 320, 172, color);
        (void)snprintf(text, sizeof(text), "%d %s: %s", (int)score.total,
                       g_end_game_text[EGT_POINTS],
                       g_end_game_text[EGT_RANK0 + score.grade]);
        end_game_text_centered(dc, text, 320, 288, 0xddU);
    }
}

/* FUN_0041a8df (ENDGNONP0..2): no tick gate; card k shows the k-th player other
   than the viewer. Not ported: the player-name line and the figure helper. */
static void render_end_game_other_cards(HDC dc)
{
    static const int card_x[3] = {15, 223, 432};
    unsigned viewer = g_menu.selected_tribe < 4U ? g_menu.selected_tribe : 3U;
    unsigned card;
    unsigned other = 0;
    if (!g_game_session_valid) return;
    for (card = 0; card < 3U; ++card, ++other) {
        GameEndGameScore score;
        unsigned player;
        unsigned color;
        char text[96];
        char noun[24];
        int saved;
        if (other == viewer) ++other;
        player = other;
        if (player >= 4U ||
            !game_session_end_game_score(&g_game_session, (uint8_t)player, &score))
            continue;
        color = end_game_tribe_color(player);
        saved = SaveDC(dc);
        (void)IntersectClipRect(dc, card_x[card], 326, card_x[card] + 190, 462);
        if (g_end_game_art.frame_count > 9U + score.grade)
            draw_sprite(dc, &g_end_game_art, 9U + score.grade, card_x[card] - 16, 326 - 19);
        (void)RestoreDC(dc, saved);
        end_game_tribe_noun(noun, sizeof(noun), player, 1);
        end_game_text(dc, noun, card_x[card] + 10, 326 + 2, color);
        (void)snprintf(text, sizeof(text), "%d %s: %s", (int)score.total,
                       g_end_game_text[EGT_POINTS],
                       g_end_game_text[EGT_RANK0 + score.grade]);
        end_game_text(dc, text, card_x[card] + 10, 326 + 12, 0xddU);
        (void)snprintf(text, sizeof(text), "%u %s", (unsigned)score.glyphs,
                       g_end_game_text[EGT_GLYPHS]);
        end_game_text(dc, text, card_x[card] + 10, 326 + 122, 0x9cU);
        (void)snprintf(text, sizeof(text), "%u %s", (unsigned)score.shadow_card_total,
                       g_end_game_text[EGT_SHADSTR]);
        end_game_text(dc, text, card_x[card] + 70, 326 + 122, 0xa0U);
        (void)snprintf(text, sizeof(text), "%u", (unsigned)score.tribe_floaters);
        end_game_text(dc, text, card_x[card] + 140, 326 + 52, color);
        end_game_tribe_noun(noun, sizeof(noun), player, score.tribe_floaters != 1U);
        end_game_text(dc, noun, card_x[card] + 140, 326 + 62, color);
        end_game_text(dc, g_end_game_text[EGT_FLOTTRIB], card_x[card] + 140, 326 + 72, color);
        (void)snprintf(text, sizeof(text), "%u", (unsigned)score.losses);
        end_game_text(dc, text, card_x[card] + 140, 326 + 85, color);
        end_game_tribe_noun(noun, sizeof(noun), player, score.losses != 1U);
        end_game_text(dc, noun, card_x[card] + 140, 326 + 95, color);
        end_game_text(dc, g_end_game_text[EGT_FLOTLOSS], card_x[card] + 140, 326 + 105, color);
    }
}

static void render_end_game(HDC dc)
{
    unsigned index;
    int tick = (int)g_end_game_tick;
    fill_rect(dc, 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT, RGB(0, 0, 0));
    draw_sprite(dc, &g_end_game_template_art, 0, 0, 0);
    render_end_game_player_card(dc, tick);
    /* FUN_0041a8df draws only when DAT_004befe0 (multiplayer session) is set;
       the port is solo-only, so the three ENDGNONP cards stay hidden. */
    if (END_GAME_MULTIPLAYER_SESSION) render_end_game_other_cards(dc);
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
