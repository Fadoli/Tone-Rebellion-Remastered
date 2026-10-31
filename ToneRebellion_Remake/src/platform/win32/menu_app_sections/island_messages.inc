/* Island view message line (islewin.cpp). FUN_00436e06 appends a string of
   fewer than 60 bytes, its haze selector and a duration of 2 * length + 60
   paints to a ten-entry queue; IsleWindow's paint (FUN_00435f4d) advances
   the head (FUN_00436ea8, shifting the queue once elapsed reaches the
   duration) and draws it (FUN_00436f3f, FUN_00411033) with BGOUTFNT at
   (15, 295): background pixels through haze table (0, level), ink through
   (selector, level), level = elapsed / 2 for the first 50 paints,
   (duration - elapsed) / 2 for the last 50, else 7. */
enum { ISLAND_MESSAGE_CAPACITY = 10, ISLAND_MESSAGE_TEXT = 60 };

typedef struct IslandMessage {
    char text[ISLAND_MESSAGE_TEXT];
    int16_t selector;
    int16_t elapsed;
    int16_t duration;
} IslandMessage;

static IslandMessage g_island_messages[ISLAND_MESSAGE_CAPACITY];
static int g_island_message_count;

/* newtext.txt keys of FUN_004334ce event 10: AWAKE<player> (argument -1),
   LEVIBRK and BOND0..7 ("%s%s."). */
static char g_island_notice_awake[GAME_START_PLAYER_COUNT][ISLAND_MESSAGE_TEXT];
static char g_island_notice_levibrk[ISLAND_MESSAGE_TEXT];
static char g_island_notice_bond[8][ISLAND_MESSAGE_TEXT];
static int g_island_notice_loaded;

static void queue_island_message(const char *text, int16_t selector)
{
    IslandMessage *message;
    size_t length;
    if (text == NULL || text[0] == '\0' ||
        g_island_message_count >= ISLAND_MESSAGE_CAPACITY) return;
    length = strlen(text);
    /* The native assert rejects 60 bytes or more; keep the queue usable. */
    if (length >= ISLAND_MESSAGE_TEXT) length = ISLAND_MESSAGE_TEXT - 1;
    message = &g_island_messages[g_island_message_count++];
    memcpy(message->text, text, length);
    message->text[length] = '\0';
    message->selector = selector;
    message->elapsed = 0;
    message->duration = (int16_t)(length * 2U + 0x3cU);
}

static void clear_island_messages(void)
{
    g_island_message_count = 0;
}

static void load_island_notice_text(void)
{
    CobArchive archive;
    const CobMember *member;
    unsigned char *bytes;
    char error[256];
    char key[16];
    unsigned int index;

    if (g_island_notice_loaded) return;
    g_island_notice_loaded = 1;
    if (!cob_archive_open(game_file_path("TONE00.COB"), &archive,
                          error, sizeof(error))) return;
    member = cob_archive_find(&archive, "newtext.txt");
    bytes = member == NULL ? NULL : (unsigned char *)malloc(member->length + 1);
    if (bytes != NULL &&
        cob_archive_read_member(&archive, member, bytes, member->length,
                                error, sizeof(error))) {
        for (index = 0; index < GAME_START_PLAYER_COUNT; ++index) {
            (void)snprintf(key, sizeof(key), "AWAKE%u", index);
            (void)extract_help_entry(bytes, member->length, key,
                                     g_island_notice_awake[index],
                                     sizeof(g_island_notice_awake[index]));
        }
        (void)extract_help_entry(bytes, member->length, "LEVIBRK",
                                 g_island_notice_levibrk,
                                 sizeof(g_island_notice_levibrk));
        for (index = 0; index < 8; ++index) {
            (void)snprintf(key, sizeof(key), "BOND%u", index);
            (void)extract_help_entry(bytes, member->length, key,
                                     g_island_notice_bond[index],
                                     sizeof(g_island_notice_bond[index]));
        }
    }
    free(bytes);
    cob_archive_close(&archive);
}

/* FUN_004334ce event 10: argument -1 names the local tribe (AWAKE + the
   DAT_0049f538 digit), 0..7 build "%s%s." from LEVIBRK and BOND<k>. */
static void queue_leviathan_bond_notice(int32_t bond)
{
    char text[ISLAND_MESSAGE_TEXT * 2 + 2];
    load_island_notice_text();
    if (bond == -1) {
        if (g_menu.selected_tribe >= 0 &&
            g_menu.selected_tribe < GAME_START_PLAYER_COUNT)
            queue_island_message(g_island_notice_awake[g_menu.selected_tribe], 1);
    } else if (bond >= 0 && bond < 8) {
        (void)snprintf(text, sizeof(text), "%s%s.", g_island_notice_levibrk,
                       g_island_notice_bond[bond]);
        queue_island_message(text, 1);
    }
}

static void draw_island_message(HDC dc)
{
    IslandMessage *head;
    const unsigned char *cursor;
    int level;
    int x = 0x0f;
    const int y = 0x127;

    /* FUN_00436ea8 runs before the head is read, on every paint. */
    if (g_island_message_count != 0 &&
        ++g_island_messages[0].elapsed >= g_island_messages[0].duration) {
        memmove(&g_island_messages[0], &g_island_messages[1],
                (size_t)(g_island_message_count - 1) * sizeof(g_island_messages[0]));
        --g_island_message_count;
    }
    if (g_island_message_count == 0) return;
    head = &g_island_messages[0];
    level = 7;
    if (head->elapsed < 0x32) level = head->elapsed / 2;
    else if (head->duration - 0x32 < head->elapsed)
        level = (head->duration - head->elapsed) / 2;
    if (level < 0) level = 0;
    if (level > 7) level = 7;
    if (dc != g_paint_buffer_dc || g_paint_buffer_pixels == NULL) {
        draw_bitmap_label(dc, head->text, x, y, RGB(255, 255, 255));
        return;
    }
    (void)GdiFlush();
    for (cursor = (const unsigned char *)head->text; *cursor != '\0'; ++cursor) {
        uint32_t code = *cursor < g_bitmap_font.glyph_count ? *cursor : (uint32_t)'?';
        uint32_t glyph_width;
        const uint8_t *glyph_pixels;
        uint32_t row;
        uint32_t col;
        if (!bitmap_font_get_glyph(&g_bitmap_font, code, &glyph_width,
                                   &glyph_pixels)) continue;
        for (row = 0; row < g_bitmap_font.height; ++row) {
            int py = y + (int)row;
            if (py < 0 || py >= LOGICAL_HEIGHT) continue;
            for (col = 0; col < glyph_width; ++col) {
                uint8_t value = glyph_pixels[(size_t)row * glyph_width + col];
                int px = x + (int)col;
                DWORD *pixel;
                if (value == 0xffu || px < 0 || px >= LOGICAL_WIDTH) continue;
                pixel = &g_paint_buffer_pixels[(size_t)py * LOGICAL_WIDTH + (size_t)px];
                *pixel = hazed_island_pixel(*pixel, value == 0u ? 0 : head->selector,
                                            level);
            }
        }
        x += (int)glyph_width;
    }
}
