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

