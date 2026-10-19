static int update_hover_help(int x, int y)
{
    int help = -1;
    if (g_menu.screen == SCREEN_MAIN_MENU) {
        const WindowTemplate *control = window_catalog_hit_test(&g_window_catalog, 0, x, y);
        if (control != NULL && strcmp(control->name, "NEWGAME") == 0) help = HELP_MAIN_NEWGAME;
        else if (control != NULL && strcmp(control->name, "RESUME") == 0 && g_resume_available)
            help = HELP_MAIN_RESUME;
        else if (control != NULL && strcmp(control->name, "LOADGAME") == 0) help = HELP_MAIN_LOAD;
        else if (control != NULL && strcmp(control->name, "EXITAPP") == 0) help = HELP_MAIN_EXIT;
    }
    if (help == g_hovered_help) return 0;
    g_hovered_help = help;
    return 1;
}

static int tribe_icon_at(int x, int y)
{
    static const POINT centers[4] = {{170, 240}, {320, 90}, {470, 240}, {320, 390}};
    int tribe;
    for (tribe = 0; tribe < 4; ++tribe) {
        int dx = x - centers[tribe].x;
        int dy = y - centers[tribe].y;
        if (dx * dx + dy * dy < 2500) return tribe;
    }
    return -1;
}

static int newgame_text_index_at(int x, int y)
{
    int tribe = tribe_icon_at(x, y);
    const WindowTemplate *control;
    if (tribe >= 0) return tribe;
    {
        int dx = x - 320;
        int dy = y - 240;
        int distance_squared = dx * dx + dy * dy;
        if (distance_squared < 100) return 4;
        if (distance_squared < 200) return 5;
    }
    control = window_catalog_hit_test(&g_window_catalog, 1, x, y);
    if (control == NULL) return -1;
    if (strcmp(control->message_destination, "WINMGR") == 0 &&
        control->send_message[0] == 1 && control->send_message[1] == 0) return 6;
    if (strcmp(control->message_destination, "MASTER") != 0) return -1;
    if (control->send_message[0] == 52) return 7;
    if (control->send_message[0] == 53) return 5;
    if (control->send_message[0] == 55) return 4;
    if (control->send_message[0] >= 60 && control->send_message[0] <= 63)
        return control->send_message[0] - 60;
    return -1;
}

static int update_newgame_text(int x, int y)
{
    int text_index = g_menu.screen == SCREEN_NEW_GAME ? newgame_text_index_at(x, y) : -1;
    if (text_index == g_hovered_newgame_text) return 0;
    g_hovered_newgame_text = text_index;
    return 1;
}

static void draw_hover_help(HDC dc)
{
    if (g_menu.screen != SCREEN_MAIN_MENU || !g_mouse_inside || g_hovered_help < 0 ||
        (uint32_t)g_hovered_help >= g_menu_help.frame_count) return;
    /* Keep contextual help away from the title buttons and their baked-in
       captions. Anchoring it to the pointer covered the active control. */
    draw_sprite(dc, &g_menu_help, (uint32_t)g_hovered_help,
                12, 12);
}

static void draw_newgame_text(HDC dc)
{
    if (g_menu.screen != SCREEN_NEW_GAME || !g_mouse_inside ||
        g_hovered_newgame_text < 0 || g_hovered_newgame_text >= 8) return;
    draw_sprite(dc, &g_newgame_captions, (uint32_t)g_hovered_newgame_text, 160, 430);
}

static void draw_tribe_descriptions(HDC dc)
{
    int left_index;
    int right_index;
    if (g_menu.screen != SCREEN_NEW_GAME || g_menu.selected_tribe < 0 ||
        g_menu.selected_tribe >= 4) return;
    left_index = g_menu.selected_tribe * 2;
    right_index = left_index + 1;
    if ((uint32_t)right_index >= g_tribe_descriptions.frame_count) return;
    draw_sprite(dc, &g_tribe_descriptions, (uint32_t)left_index, 0, 0);
    draw_sprite(dc, &g_tribe_descriptions, (uint32_t)right_index, 0, 0);
}

static void fill_rect(HDC dc, int left, int top, int right, int bottom, COLORREF color)
{
    RECT rect = {left, top, right, bottom};
    HBRUSH brush = CreateSolidBrush(color);
    FillRect(dc, &rect, brush);
    DeleteObject(brush);
}

static void draw_bitmap_text_at(DWORD *pixels, int surface_width, int surface_height,
                                const char *text, int x, int y, DWORD ink)
{
    const unsigned char *cursor = (const unsigned char *)text;
    while (*cursor != 0) {
        uint32_t glyph_width;
        const uint8_t *glyph_pixels;
        uint32_t code = *cursor < g_bitmap_font.glyph_count ? *cursor : (uint32_t)'?';
        uint32_t row;
        if (bitmap_font_get_glyph(&g_bitmap_font, code, &glyph_width, &glyph_pixels)) {
            uint32_t col;
            for (row = 0; row < g_bitmap_font.height; ++row) {
                for (col = 0; col < glyph_width; ++col) {
                    /* BGOUTFNT masks distinguish ink (1), background (0),
                       and transparent padding (0xff). Treating zero as ink
                       filled each glyph's entire bounding box. */
                    if (glyph_pixels[(size_t)row * glyph_width + col] == 1u) {
                        int px = x + (int)col;
                        int py = y + (int)row;
                        if (px >= 0 && px < surface_width && py >= 0 && py < surface_height) {
                            pixels[(size_t)py * (size_t)surface_width + (size_t)px] = ink;
                        }
                    }
                }
            }
            x += (int)glyph_width;
        }
        ++cursor;
    }
}

static int32_t measure_bitmap_text(void *context, const char *text, size_t length)
{
    size_t i;
    int32_t width = 0;
    (void)context;
    for (i = 0; i < length; ++i) {
        uint32_t glyph_width;
        const uint8_t *glyph_pixels;
        uint32_t code = (unsigned char)text[i];
        if (code >= g_bitmap_font.glyph_count) code = (uint32_t)'?';
        if (bitmap_font_get_glyph(&g_bitmap_font, code, &glyph_width, &glyph_pixels))
            width += (int32_t)((glyph_width * CURVED_TEXT_NEWGAME_WIDTH_NUMERATOR +
                                CURVED_TEXT_NEWGAME_WIDTH_DENOMINATOR / 2u) /
                               CURVED_TEXT_NEWGAME_WIDTH_DENOMINATOR);
    }
    return width;
}

static int32_t measure_curved_bitmap_text(void *context, const char *text,
                                          size_t length)
{
    size_t i;
    int32_t width = 0;
    (void)context;
    for (i = 0; i < length; ++i) {
        uint32_t glyph_width;
        const uint8_t *glyph_pixels;
        uint32_t code = (unsigned char)text[i];
        if (code >= g_bitmap_font.glyph_count) code = (uint32_t)'?';
        if (bitmap_font_get_glyph(&g_bitmap_font, code, &glyph_width, &glyph_pixels))
            width += (int32_t)glyph_width;
    }
    return width;
}

static void draw_curved_bitmap_text_at(DWORD *pixels, int surface_width,
                                       int surface_height, const char *text,
                                       int x, int y, DWORD ink)
{
    const unsigned char *cursor = (const unsigned char *)text;
    while (*cursor != 0) {
        uint32_t source_width;
        const uint8_t *glyph_pixels;
        uint32_t code = *cursor < g_bitmap_font.glyph_count
            ? *cursor : (uint32_t)'?';
        if (bitmap_font_get_glyph(&g_bitmap_font, code, &source_width,
                                  &glyph_pixels)) {
            uint32_t width = (source_width * CURVED_TEXT_NEWGAME_WIDTH_NUMERATOR +
                              CURVED_TEXT_NEWGAME_WIDTH_DENOMINATOR / 2u) /
                             CURVED_TEXT_NEWGAME_WIDTH_DENOMINATOR;
            if (width == 0) width = 1;
            uint32_t row;
            for (row = 0; row < CURVED_TEXT_NEWGAME_RENDER_HEIGHT; ++row) {
                uint32_t col;
                for (col = 0; col < width; ++col) {
                    uint32_t source_col = col * source_width / width;
                    int px = x + (int)col;
                    int py = y + (int)row;
                    if (glyph_pixels[(size_t)row * source_width + source_col] == 1u &&
                        px >= 0 && px < surface_width &&
                        py >= 0 && py < surface_height) {
                        pixels[(size_t)py * (size_t)surface_width + (size_t)px] = ink;
                    }
                }
            }
            x += (int)width;
        }
        ++cursor;
    }
}

static void draw_justified_bitmap_line(DWORD *pixels, int surface_width,
                                       int surface_height, const char *text,
                                       const CurvedTextLine *line, DWORD ink)
{
    char word[1024];
    size_t cursor = line->offset;
    size_t end = line->offset + line->length;
    size_t space_count = 0;
    size_t i;
    size_t remainder;
    int32_t text_width;
    int32_t extra;
    int32_t per_space;
    int32_t single_space_width = measure_curved_bitmap_text(NULL, " ", 1);
    int x = line->x;
    for (i = cursor; i < end; ++i) if (text[i] == ' ') ++space_count;
    text_width = measure_curved_bitmap_text(NULL, text + cursor, end - cursor);
    extra = line->width - text_width;
    if (extra < 0) extra = 0;
    if (space_count == 0) {
        size_t length = end - cursor;
        if (length >= sizeof(word)) length = sizeof(word) - 1;
        memcpy(word, text + cursor, length);
        word[length] = '\0';
        draw_curved_bitmap_text_at(pixels, surface_width, surface_height,
                                   word, x, line->y, ink);
        return;
    }
    per_space = extra / (int32_t)space_count;
    remainder = (size_t)(extra - per_space * (int32_t)space_count);
    while (cursor < end) {
        size_t word_end = cursor;
        size_t word_length;
        int32_t word_width;
        while (word_end < end && text[word_end] != ' ') ++word_end;
        word_length = word_end - cursor;
        if (word_length >= sizeof(word)) word_length = sizeof(word) - 1;
        memcpy(word, text + cursor, word_length);
        word[word_length] = '\0';
        draw_curved_bitmap_text_at(pixels, surface_width, surface_height,
                                   word, x, line->y, ink);
        word_width = measure_curved_bitmap_text(NULL, word, word_length);
        x += word_width;
        if (word_end < end) {
            x += single_space_width + per_space;
            if (remainder != 0) {
                ++x;
                --remainder;
            }
        }
        cursor = word_end + 1;
    }
}

static int extract_help_entry(const unsigned char *bytes, size_t length,
                              const char *key, char *output, size_t output_capacity)
{
    return island_panel_info_extract_entry(bytes, length, key,
                                           output, output_capacity);
}

static int load_island_panel_info_text(char *error, size_t error_capacity)
{
    CobArchive archive = {0};
    const CobMember *member;
    unsigned char *bytes = NULL;
    char inventory_text[sizeof(g_inventory_info_text)];
    char glyph_text[sizeof(g_glyph_info_text)];
    char diplomacy_policy_text[sizeof(g_diplomacy_policy_text)];
    char diplomacy_recipient_text[sizeof(g_diplomacy_recipient_text)];
    char item_text[sizeof(g_inventory_item_info_text[0])];
    char item_key[16];
    unsigned int item_id;
    unsigned int glyph_index;
    int success = 0;

    if (!cob_archive_open("C:\\Program Files\\Tone\\TONE00.COB", &archive,
                          error, error_capacity)) return 0;
    member = cob_archive_find(&archive, "newtext.txt");
    if (member == NULL) {
        (void)snprintf(error, error_capacity,
                       "newtext.txt was not found in TONE00.COB");
        goto done;
    }
    memset(inventory_text, 0, sizeof(inventory_text));
    memset(glyph_text, 0, sizeof(glyph_text));
    memset(diplomacy_policy_text, 0, sizeof(diplomacy_policy_text));
    memset(diplomacy_recipient_text, 0, sizeof(diplomacy_recipient_text));
    bytes = (unsigned char *)malloc(member->length == 0 ? 1 : member->length);
    if (bytes == NULL ||
        !cob_archive_read_member(&archive, member, bytes, member->length,
                                 error, error_capacity)) goto done;
    if (!extract_help_entry(bytes, member->length, "COLLART",
                            inventory_text, sizeof(inventory_text)) ||
        !extract_help_entry(bytes, member->length, "GLYSTONE",
                            glyph_text, sizeof(glyph_text)) ||
        !extract_help_entry(bytes, member->length, "TRDIPHI",
                            diplomacy_policy_text,
                            sizeof(diplomacy_policy_text)) ||
        !extract_help_entry(bytes, member->length, "TRCOMHI",
                            diplomacy_recipient_text,
                            sizeof(diplomacy_recipient_text))) {
        (void)snprintf(error, error_capacity,
                       "newtext.txt is missing a Hall panel caption");
        goto done;
    }
    memcpy(g_inventory_info_text, inventory_text, strlen(inventory_text) + 1);
    memcpy(g_glyph_info_text, glyph_text, strlen(glyph_text) + 1);
    memcpy(g_diplomacy_policy_text, diplomacy_policy_text,
           strlen(diplomacy_policy_text) + 1);
    memcpy(g_diplomacy_recipient_text, diplomacy_recipient_text,
           strlen(diplomacy_recipient_text) + 1);
    free(bytes);
    bytes = NULL;

    member = cob_archive_find(&archive, "plotobj.txt");
    if (member == NULL) {
        (void)snprintf(error, error_capacity,
                       "plotobj.txt was not found in TONE00.COB");
        goto done;
    }
    bytes = (unsigned char *)malloc(member->length == 0 ? 1 : member->length);
    if (bytes == NULL ||
        !cob_archive_read_member(&archive, member, bytes, member->length,
                                 error, error_capacity)) goto done;
    for (item_id = 5; item_id <= 33; ++item_id) {
        if (!island_panel_info_inventory_key(item_id, item_key,
                                             sizeof(item_key)) ||
            !extract_help_entry(bytes, member->length, item_key,
                               item_text, sizeof(item_text))) {
            (void)snprintf(error, error_capacity,
                           "plotobj.txt is missing inventory entry %s", item_key);
            goto done;
        }
        memcpy(g_inventory_item_info_text[item_id - 5], item_text,
               strlen(item_text) + 1);
    }
    for (glyph_index = 0; glyph_index < GAME_GLYPH_COUNT; ++glyph_index) {
        if (!game_glyph_inventory_key(glyph_index, item_key, sizeof(item_key)) ||
            !extract_help_entry(bytes, member->length, item_key,
                                item_text, sizeof(item_text))) {
            (void)snprintf(error, error_capacity,
                           "plotobj.txt is missing glyph entry %s", item_key);
            goto done;
        }
        memcpy(g_glyph_item_info_text[glyph_index], item_text,
               strlen(item_text) + 1);
    }
    success = 1;
done:
    free(bytes);
    cob_archive_close(&archive);
    return success;
}

static size_t extract_repeated_help_entries(const unsigned char *bytes, size_t length,
                                           const char *key,
                                           char (*outputs)[BUILDING_NAME_CAPACITY],
                                           size_t output_count)
{
    size_t cursor = 0;
    size_t key_length = strlen(key);
    size_t found = 0;

    while (cursor < length && found < output_count) {
        size_t line_start = cursor;
        size_t line_end;
        while (cursor < length && bytes[cursor] != '\n') ++cursor;
        line_end = cursor;
        if (line_end > line_start && bytes[line_end - 1] == '\r') --line_end;
        if (line_end - line_start == key_length &&
            memcmp(bytes + line_start, key, key_length) == 0) {
            size_t used = 0;
            if (cursor < length) ++cursor;
            while (cursor < length) {
                size_t text_start = cursor;
                size_t text_end;
                size_t count;
                while (cursor < length && bytes[cursor] != '\n') ++cursor;
                text_end = cursor;
                if (text_end > text_start && bytes[text_end - 1] == '\r') --text_end;
                if (text_end - text_start >= 3 &&
                    memcmp(bytes + text_start, "END", 3) == 0) {
                    outputs[found][used] = '\0';
                    ++found;
                    if (cursor < length) ++cursor;
                    break;
                }
                count = text_end - text_start;
                while (count > 0 && (bytes[text_start] == ' ' ||
                                     bytes[text_start] == '\t')) {
                    ++text_start;
                    --count;
                }
                while (count > 0 && (bytes[text_start + count - 1] == ' ' ||
                                     bytes[text_start + count - 1] == '\t')) --count;
                if (count != 0) {
                    if (used != 0 && used + 1 < BUILDING_NAME_CAPACITY) {
                        outputs[found][used++] = ' ';
                    }
                    if (count >= BUILDING_NAME_CAPACITY - used) {
                        count = BUILDING_NAME_CAPACITY - used - 1;
                    }
                    memcpy(outputs[found] + used, bytes + text_start, count);
                    used += count;
                }
                if (cursor < length) ++cursor;
            }
            continue;
        }
        if (cursor < length) ++cursor;
    }
    return found;
}

static int load_menu_help(char *error, size_t error_capacity)
{
    static const char *keys[HELP_ENTRY_COUNT] = {
        "NEWGAME", "RESUME", "LOADGAME", "EXITAPP",
        "EXITNEWGAME", "WORLDSIZE", "TRIBE0", "TRIBE1", "TRIBE2",
        "TRIBE3", "DIFFICULTY", "BEGINGAME"
    };
    CobArchive archive = {0};
    const CobMember *member;
    unsigned char *bytes;
    int i;
    int success = 0;
    if (!cob_archive_open("C:\\Program Files\\Tone\\TONE00.COB", &archive,
                          error, error_capacity)) return 0;
    member = cob_archive_find(&archive, "tonehelp.txt");
    if (member == NULL) {
        (void)snprintf(error, error_capacity, "tonehelp.txt was not found in TONE00.COB");
        goto done;
    }
    bytes = (unsigned char *)malloc(member->length);
    if (bytes == NULL || !cob_archive_read_member(&archive, member, bytes,
                                                  member->length, error,
                                                  error_capacity)) {
        free(bytes);
        goto done;
    }
    for (i = 0; i < HELP_ENTRY_COUNT; ++i) {
        if (!extract_help_entry(bytes, member->length, keys[i], g_help_text[i],
                                sizeof(g_help_text[i]))) {
            (void)snprintf(error, error_capacity, "help text key %s is missing or empty", keys[i]);
            free(bytes);
            goto done;
        }
    }
    free(bytes);
    success = 1;
done:
    cob_archive_close(&archive);
    return success;
}

static int load_newgame_captions(char *error, size_t error_capacity)
{
    CobArchive archive = {0};
    const CobMember *member;
    unsigned char *bytes = NULL;
    int success = 0;
    int i;
    if (!cob_archive_open("C:\\Program Files\\Tone\\TONE00.COB", &archive,
                          error, error_capacity)) return 0;
    member = cob_archive_find(&archive, "gamey.txt");
    if (member == NULL) {
        (void)snprintf(error, error_capacity, "gamey.txt was not found in TONE00.COB");
        goto done;
    }
    bytes = (unsigned char *)malloc(member->length == 0 ? 1 : member->length);
    if (bytes == NULL || !cob_archive_read_member(&archive, member, bytes, member->length,
                                                   error, error_capacity)) goto done;
    for (i = 0; i < 8; ++i) {
        char key[16];
        (void)snprintf(key, sizeof(key), "NEWGAME%d", i);
        if (!extract_help_entry(bytes, member->length, key, g_newgame_text[i],
                                sizeof(g_newgame_text[i]))) {
            (void)snprintf(error, error_capacity, "gamey.txt key %s is missing or empty", key);
            goto done;
        }
    }
    if (!extract_help_entry(bytes, member->length, "NOKNOW",
                            g_empty_glyph_text, sizeof(g_empty_glyph_text))) {
        (void)snprintf(error, error_capacity,
                       "gamey.txt key NOKNOW is missing or empty");
        goto done;
    }
    if (!extract_help_entry(bytes, member->length, "NOART",
                            g_empty_inventory_text,
                            sizeof(g_empty_inventory_text))) {
        (void)snprintf(error, error_capacity,
                       "gamey.txt key NOART is missing or empty");
        goto done;
    }
    if (!extract_help_entry(bytes, member->length, "NOTASKS",
                            g_empty_task_text, sizeof(g_empty_task_text))) {
        (void)snprintf(error, error_capacity,
                       "gamey.txt key NOTASKS is missing or empty");
        goto done;
    }
    {
        static const char *const task_keys[4] = {
            "CONSTR", "REPAIR", "DARTIFACT", "OARTIFACT"
        };
        for (i = 0; i < 4; ++i) {
            if (!extract_help_entry(bytes, member->length, task_keys[i],
                                    g_task_label_text[i],
                                    sizeof(g_task_label_text[i]))) {
                (void)snprintf(error, error_capacity,
                               "gamey.txt key %s is missing or empty", task_keys[i]);
                goto done;
            }
        }
    }
    if (!extract_help_entry(bytes, member->length, "STOCK",
                            g_task_stock_text, sizeof(g_task_stock_text))) {
        (void)snprintf(error, error_capacity,
                       "gamey.txt key STOCK is missing or empty");
        goto done;
    }
    if (!extract_help_entry(bytes, member->length, "BLDCONST",
                            g_task_building_const_text,
                            sizeof(g_task_building_const_text))) {
        (void)snprintf(error, error_capacity,
                       "gamey.txt key BLDCONST is missing or empty");
        goto done;
    }
    {
        static const char *const priority_keys[3] = {
            "TNORM", "THIGH", "TEXCL"
        };
        static const char *const transfer_keys[2] = {
            "DELIVER", "RETRIEVE"
        };
        static const char *const category_keys[4] = {
            "STONE", "CTONE", "MTONE", "ARTIFACT"
        };
        for (i = 0; i < 3; ++i) {
            if (!extract_help_entry(bytes, member->length, priority_keys[i],
                                    g_task_priority_text[i],
                                    sizeof(g_task_priority_text[i]))) {
                (void)snprintf(error, error_capacity,
                               "gamey.txt key %s is missing or empty",
                               priority_keys[i]);
                goto done;
            }
        }
        for (i = 0; i < 2; ++i) {
            if (!extract_help_entry(bytes, member->length, transfer_keys[i],
                                    g_task_transfer_text[i],
                                    sizeof(g_task_transfer_text[i]))) {
                (void)snprintf(error, error_capacity,
                               "gamey.txt key %s is missing or empty",
                               transfer_keys[i]);
                goto done;
            }
        }
        for (i = 0; i < 4; ++i) {
            if (!extract_help_entry(bytes, member->length, category_keys[i],
                                    g_task_category_text[i],
                                    sizeof(g_task_category_text[i]))) {
                (void)snprintf(error, error_capacity,
                               "gamey.txt key %s is missing or empty",
                               category_keys[i]);
                goto done;
            }
        }
    }
    if (!extract_help_entry(bytes, member->length, "POPSTR",
                            g_hall_population_label,
                            sizeof(g_hall_population_label))) {
        (void)snprintf(error, error_capacity,
                       "gamey.txt key POPSTR is missing or empty");
        goto done;
    }
    if (!extract_help_entry(bytes, member->length, "WORKSTR",
                            g_hall_work_label,
                            sizeof(g_hall_work_label))) {
        (void)snprintf(error, error_capacity,
                       "gamey.txt key WORKSTR is missing or empty");
        goto done;
    }
    for (i = 0; i < ISLAND_PANEL_INFO_CRYPTIC_COUNT; ++i) {
        char key[16] = {0};
        if (!island_panel_info_cryptic_key((unsigned int)i, key, sizeof(key)) ||
            !extract_help_entry(bytes, member->length, key, g_cryptic_text[i],
                                sizeof(g_cryptic_text[i]))) {
            (void)snprintf(error, error_capacity,
                           "gamey.txt key %s is missing or empty", key);
            goto done;
        }
    }
    success = 1;
done:
    free(bytes);
    cob_archive_close(&archive);
    return success;
}

static int load_tribe_descriptions(char *error, size_t error_capacity)
{
    static const char *keys[4][2] = {
        {"PROTECT0", "PROTECT1"}, {"SEEKER0", "SEEKER1"},
        {"MYSTIC0", "MYSTIC1"}, {"LIFE0", "LIFE1"}
    };
    CobArchive archive = {0};
    const CobMember *member;
    unsigned char *bytes = NULL;
    int tribe;
    int part;
    int success = 0;
    if (!cob_archive_open("C:\\Program Files\\Tone\\TONE00.COB", &archive,
                          error, error_capacity)) return 0;
    member = cob_archive_find(&archive, "newgame.txt");
    if (member == NULL) {
        (void)snprintf(error, error_capacity, "newgame.txt was not found in TONE00.COB");
        goto done;
    }
    bytes = (unsigned char *)malloc(member->length == 0 ? 1 : member->length);
    if (bytes == NULL || !cob_archive_read_member(&archive, member, bytes,
                                                  member->length, error,
                                                  error_capacity)) goto done;
    for (tribe = 0; tribe < 4; ++tribe) {
        for (part = 0; part < 2; ++part) {
            if (!extract_help_entry(bytes, member->length, keys[tribe][part],
                                    g_tribe_text[tribe][part],
                                    sizeof(g_tribe_text[tribe][part]))) {
                (void)snprintf(error, error_capacity,
                               "newgame.txt key %s is missing or empty",
                               keys[tribe][part]);
                goto done;
            }
        }
    }
    success = 1;
done:
    free(bytes);
    cob_archive_close(&archive);
    return success;
}

static int parse_island_names(const unsigned char *bytes, size_t length)
{
    size_t cursor = 0;
    int in_island_section = 0;
    int name_count = 0;
    while (cursor < length) {
        size_t line_start = cursor;
        size_t line_end;
        size_t first;
        size_t last;
        while (cursor < length && bytes[cursor] != '\n') ++cursor;
        line_end = cursor;
        if (cursor < length) ++cursor;
        if (line_end > line_start && bytes[line_end - 1] == '\r') --line_end;
        first = line_start;
        last = line_end;
        while (first < last && (bytes[first] == ' ' || bytes[first] == '\t')) ++first;
        while (last > first && (bytes[last - 1] == ' ' || bytes[last - 1] == '\t')) --last;
        if (!in_island_section) {
            static const char section[] = "// Island Names";
            if (last - first >= sizeof(section) - 1 &&
                memcmp(bytes + first, section, sizeof(section) - 1) == 0) {
                in_island_section = 1;
            }
            continue;
        }
        if (first == last || bytes[first] == ';' ||
            (last - first >= 2 && bytes[first] == '/' && bytes[first + 1] == '/')) {
            continue;
        }
        if (name_count >= ISLAND_NAME_COUNT || last - first >= sizeof(g_island_names[0])) {
            return 0;
        }
        memcpy(g_island_names[name_count], bytes + first, last - first);
        g_island_names[name_count][last - first] = '\0';
        ++name_count;
        if (name_count == ISLAND_NAME_COUNT) return 1;
    }
    return 0;
}

static int load_island_names(char *error, size_t error_capacity)
{
    CobArchive archive = {0};
    const CobMember *member;
    unsigned char *bytes = NULL;
    int success = 0;
    if (!cob_archive_open("C:\\Program Files\\Tone\\TONE00.COB", &archive,
                          error, error_capacity)) return 0;
    member = cob_archive_find(&archive, "names.txt");
    if (member == NULL) {
        (void)snprintf(error, error_capacity, "names.txt was not found in TONE00.COB");
        goto done;
    }
    bytes = (unsigned char *)malloc(member->length == 0 ? 1 : member->length);
    if (bytes == NULL || !cob_archive_read_member(&archive, member, bytes, member->length,
                                                  error, error_capacity)) goto done;
    if (!parse_island_names(bytes, member->length)) {
        (void)snprintf(error, error_capacity,
                       "names.txt does not contain the expected 15 island names");
        goto done;
    }
    success = 1;
done:
    free(bytes);
    cob_archive_close(&archive);
    return success;
}

static int create_tribe_description_sheet(SpriteSheet *sheet,
                                          char *error, size_t error_capacity)
{
    enum { TEXT_WIDTH = 640, TEXT_HEIGHT = 480, MAX_LINES = CURVED_TEXT_MAX_LINES };
    COLORREF description_color = g_newgame_palette[0xbf];
    DWORD ink = 0xff000000u | ((DWORD)GetRValue(description_color) << 16) |
                ((DWORD)GetGValue(description_color) << 8) |
                (DWORD)GetBValue(description_color);
    int entry;
    sheet->frames = (SpriteFrame *)calloc(8, sizeof(*sheet->frames));
    if (sheet->frames == NULL) {
        (void)snprintf(error, error_capacity, "could not allocate tribe descriptions");
        return 0;
    }
    sheet->frame_count = 8;
    for (entry = 0; entry < 8; ++entry) {
        const char *text = g_tribe_text[entry / 2][entry % 2];
        CurvedTextLine lines[MAX_LINES];
        size_t line_count = 0;
        BITMAPINFO info;
        void *bitmap_bits = NULL;
        HBITMAP bitmap;
        size_t line;
        if (!curved_text_layout(text,
                                entry % 2 == 0 ? CURVED_TEXT_LEFT : CURVED_TEXT_RIGHT,
                                CURVED_TEXT_NEWGAME_LAST_LINE_Y,
                                CURVED_TEXT_NEWGAME_RENDER_HEIGHT,
                                measure_curved_bitmap_text, NULL, lines, MAX_LINES,
                                &line_count)) {
            (void)snprintf(error, error_capacity,
                           "could not lay out curved tribe description %d", entry);
            return 0;
        }
        ZeroMemory(&info, sizeof(info));
        info.bmiHeader.biSize = sizeof(info.bmiHeader);
        info.bmiHeader.biWidth = TEXT_WIDTH;
        info.bmiHeader.biHeight = -TEXT_HEIGHT;
        info.bmiHeader.biPlanes = 1;
        info.bmiHeader.biBitCount = 32;
        info.bmiHeader.biCompression = BI_RGB;
        bitmap = CreateDIBSection(NULL, &info, DIB_RGB_COLORS, &bitmap_bits, NULL, 0);
        if (bitmap == NULL || bitmap_bits == NULL) {
            if (bitmap != NULL) DeleteObject(bitmap);
            (void)snprintf(error, error_capacity, "could not create tribe description bitmap");
            return 0;
        }
        memset(bitmap_bits, 0, (size_t)TEXT_WIDTH * TEXT_HEIGHT * sizeof(DWORD));
        for (line = 0; line < line_count; ++line)
            draw_justified_bitmap_line((DWORD *)bitmap_bits, TEXT_WIDTH,
                                       TEXT_HEIGHT, text, &lines[line], ink);
        sheet->frames[entry].bitmap = bitmap;
        sheet->frames[entry].width = TEXT_WIDTH;
        sheet->frames[entry].height = TEXT_HEIGHT;
    }
    return 1;
}

static int create_newgame_caption_sheet(SpriteSheet *sheet,
                                        char *error, size_t error_capacity)
{
    int entry;
    sheet->frames = (SpriteFrame *)calloc(8, sizeof(*sheet->frames));
    if (sheet->frames == NULL) {
        (void)snprintf(error, error_capacity, "could not allocate New Game captions");
        return 0;
    }
    sheet->frame_count = 8;
    for (entry = 0; entry < 8; ++entry) {
        BITMAPINFO info;
        void *bitmap_bits = NULL;
        HBITMAP bitmap;
        int text_width = 0;
        int x = 0;
        const unsigned char *cursor = (const unsigned char *)g_newgame_text[entry];
        while (*cursor != 0) {
            uint32_t glyph_width;
            const uint8_t *glyph_pixels;
            uint32_t code = *cursor < g_bitmap_font.glyph_count ? *cursor : (uint32_t)'?';
            if (bitmap_font_get_glyph(&g_bitmap_font, code, &glyph_width, &glyph_pixels)) {
                text_width += (int)glyph_width;
            }
            ++cursor;
        }
        ZeroMemory(&info, sizeof(info));
        info.bmiHeader.biSize = sizeof(info.bmiHeader);
        info.bmiHeader.biWidth = 320;
        info.bmiHeader.biHeight = -(LONG)g_bitmap_font.height;
        info.bmiHeader.biPlanes = 1;
        info.bmiHeader.biBitCount = 32;
        info.bmiHeader.biCompression = BI_RGB;
        bitmap = CreateDIBSection(NULL, &info, DIB_RGB_COLORS, &bitmap_bits, NULL, 0);
        if (bitmap == NULL || bitmap_bits == NULL) {
            if (bitmap != NULL) DeleteObject(bitmap);
            (void)snprintf(error, error_capacity, "could not create New Game caption bitmap");
            return 0;
        }
        memset(bitmap_bits, 0, (size_t)320 * g_bitmap_font.height * sizeof(DWORD));
        x = (320 - text_width) / 2;
        if (x < 0) x = 0;
        draw_bitmap_text_at((DWORD *)bitmap_bits, 320, (int)g_bitmap_font.height,
                            g_newgame_text[entry], x, 0, 0xffffe88au);
        sheet->frames[entry].bitmap = bitmap;
        sheet->frames[entry].width = 320;
        sheet->frames[entry].height = (int)g_bitmap_font.height;
    }
    return 1;
}

static int create_island_name_sheet(SpriteSheet *sheet,
                                    char *error, size_t error_capacity)
{
    enum { TEXT_WIDTH = 640 };
    int entry;
    sheet->frames = (SpriteFrame *)calloc(ISLAND_NAME_COUNT, sizeof(*sheet->frames));
    if (sheet->frames == NULL) {
        (void)snprintf(error, error_capacity, "could not allocate island-name frames");
        return 0;
    }
    sheet->frame_count = ISLAND_NAME_COUNT;
    for (entry = 0; entry < ISLAND_NAME_COUNT; ++entry) {
        BITMAPINFO info;
        void *bitmap_bits = NULL;
        HBITMAP bitmap;
        int text_width = 0;
        int x;
        const unsigned char *cursor = (const unsigned char *)g_island_names[entry];
        while (*cursor != 0) {
            uint32_t glyph_width;
            const uint8_t *glyph_pixels;
            uint32_t code = *cursor < g_bitmap_font.glyph_count ? *cursor : (uint32_t)'?';
            if (bitmap_font_get_glyph(&g_bitmap_font, code, &glyph_width, &glyph_pixels)) {
                text_width += (int)glyph_width;
            }
            ++cursor;
        }
        ZeroMemory(&info, sizeof(info));
        info.bmiHeader.biSize = sizeof(info.bmiHeader);
        info.bmiHeader.biWidth = TEXT_WIDTH;
        info.bmiHeader.biHeight = -(LONG)g_bitmap_font.height;
        info.bmiHeader.biPlanes = 1;
        info.bmiHeader.biBitCount = 32;
        info.bmiHeader.biCompression = BI_RGB;
        bitmap = CreateDIBSection(NULL, &info, DIB_RGB_COLORS, &bitmap_bits, NULL, 0);
        if (bitmap == NULL || bitmap_bits == NULL) {
            if (bitmap != NULL) DeleteObject(bitmap);
            (void)snprintf(error, error_capacity, "could not create island-name bitmap");
            return 0;
        }
        memset(bitmap_bits, 0, (size_t)TEXT_WIDTH * g_bitmap_font.height * sizeof(DWORD));
        x = (TEXT_WIDTH - text_width) / 2;
        if (x < 0) x = 0;
        draw_bitmap_text_at((DWORD *)bitmap_bits, TEXT_WIDTH, (int)g_bitmap_font.height,
                            g_island_names[entry], x, 0, 0xffe8e8d8u);
        sheet->frames[entry].bitmap = bitmap;
        sheet->frames[entry].width = TEXT_WIDTH;
        sheet->frames[entry].height = (int)g_bitmap_font.height;
    }
    return 1;
}

/* FUN_004489c0 reads a 0x80-byte resume header and enables RESUME only when
   its final dword matches FUN_00457490's 0x378b8 value. */
