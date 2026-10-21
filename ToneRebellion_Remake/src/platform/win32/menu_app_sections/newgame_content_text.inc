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
        static const char *const task_keys[5] = {
            "CONSTR", "REPAIR", "DARTIFACT", "OARTIFACT", "UPGRADE"
        };
        for (i = 0; i < 5; ++i) {
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
    if (!extract_help_entry(bytes, member->length, "SURPFLOW",
                            g_hall_surplus_label,
                            sizeof(g_hall_surplus_label))) {
        (void)snprintf(error, error_capacity,
                       "gamey.txt key SURPFLOW is missing or empty");
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
    {
        static const char *const trade_keys[2] = {"TRZERO", "TRDOIT"};
        for (i = 0; i < 2; ++i) {
            if (!extract_help_entry(bytes, member->length, trade_keys[i],
                                    g_trade_caption_text[i],
                                    sizeof(g_trade_caption_text[i]))) {
                (void)snprintf(error, error_capacity,
                               "gamey.txt key %s is missing or empty",
                               trade_keys[i]);
                goto done;
            }
        }
    }
    {
        static const char *const unit_keys[6] = {
            "WORKER", "AWAKE", "LEVEL", "HITS", "STRENGTH", "CHARGE"
        };
        for (i = 0; i < 6; ++i) {
            if (!extract_help_entry(bytes, member->length, unit_keys[i],
                                    g_unit_label_text[i],
                                    sizeof(g_unit_label_text[i]))) {
                (void)snprintf(error, error_capacity,
                               "gamey.txt key %s is missing or empty",
                               unit_keys[i]);
                goto done;
            }
        }
    }
    /* FUN_0041d70d reads names.txt, skipping blank and comment lines, into
       5 tribe slots (11 chars), 5 plural, 15 island and 18 beast slots. */
    {
        const CobMember *names = cob_archive_find(&archive, "names.txt");
        unsigned char *text;
        size_t pos = 0;
        unsigned int slot = 0;
        if (names == NULL) {
            (void)snprintf(error, error_capacity,
                           "names.txt was not found in TONE00.COB");
            goto done;
        }
        text = (unsigned char *)malloc(names->length == 0 ? 1 : names->length);
        if (text == NULL ||
            !cob_archive_read_member(&archive, names, text, names->length,
                                     error, error_capacity)) {
            free(text);
            goto done;
        }
        while (pos < names->length && slot < 43U) {
            size_t start = pos;
            size_t end;
            while (pos < names->length && text[pos] != '\n') ++pos;
            end = pos;
            if (pos < names->length) ++pos;
            while (end > start && (text[end - 1] == '\r' ||
                                   text[end - 1] == ' ')) --end;
            if (end == start || text[start] == ';' ||
                (end - start >= 2 && text[start] == '/' &&
                 text[start + 1] == '/')) continue;
            if (slot < 5U) {
                size_t n = end - start > 11U ? 11U : end - start;
                memcpy(g_tribe_names[slot], text + start, n);
                g_tribe_names[slot][n] = '\0';
            } else if (slot >= 25U) {
                size_t n = end - start > 15U ? 15U : end - start;
                memcpy(g_beast_names[slot - 25U], text + start, n);
                g_beast_names[slot - 25U][n] = '\0';
            }
            ++slot;
        }
        free(text);
        if (slot < 43U) {
            (void)snprintf(error, error_capacity,
                           "names.txt has %u names, expected 43", slot);
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
