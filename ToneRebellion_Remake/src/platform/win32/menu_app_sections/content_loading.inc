static int load_world_map(char *error, size_t error_capacity)
{
    CobArchive archive = {0};
    const CobMember *member;
    unsigned char *data;
    const char *archive_path = "C:\\Program Files\\Tone\\TONE01.COB";
    int success;
    if (!cob_archive_open(archive_path, &archive, error, error_capacity)) {
        return 0;
    }
    member = cob_archive_find(&archive, "data\\worldpos.txt");
    if (member == NULL) {
        (void)snprintf(error, error_capacity, "data\\worldpos.txt was not found in TONE01.COB");
        cob_archive_close(&archive);
        return 0;
    }
    data = (unsigned char *)malloc(member->length == 0 ? 1 : member->length);
    if (data == NULL) {
        (void)snprintf(error, error_capacity, "could not allocate world table buffer");
        cob_archive_close(&archive);
        return 0;
    }
    success = cob_archive_read_member(&archive, member, data, member->length,
                                      error, error_capacity) &&
              world_map_load_data(data, member->length, &g_menu.world_map,
                                  error, error_capacity);
    free(data);
    cob_archive_close(&archive);
    return success;
}

static int load_game_session_for_selected_world(char *error, size_t error_capacity)
{
    CobArchive archive = {0};
    const WorldDefinition *world;
    IslandData island_records[WORLD_MAP_MAX_ISLANDS];
    GameSessionConfig config;
    GameSession session;
    unsigned int island_index;

    if (g_menu.world_index < 0 || g_menu.world_index >= g_menu.world_map.world_count) {
        (void)snprintf(error, error_capacity, "selected world is out of range");
        return 0;
    }
    world = &g_menu.world_map.worlds[g_menu.world_index];
    memset(island_records, 0, sizeof(island_records));
    if (!cob_archive_open("C:\\Program Files\\Tone\\TONE01.COB", &archive,
                          error, error_capacity)) return 0;

    for (island_index = 0; island_index < world->island_count; ++island_index) {
        char member_name[48];
        const CobMember *member;
        unsigned char *bytes;
        int shape_id = world->islands[island_index].shape_id;
        int parsed;

        if (shape_id < 0 || shape_id >= ISLAND_NAME_COUNT) {
            (void)snprintf(error, error_capacity,
                           "world island %u has unsupported shape ID %d",
                           island_index, shape_id);
            cob_archive_close(&archive);
            return 0;
        }
        (void)snprintf(member_name, sizeof(member_name), "data\\island%02d.txt", shape_id);
        member = cob_archive_find(&archive, member_name);
        if (member == NULL) {
            (void)snprintf(error, error_capacity, "%s was not found in TONE01.COB",
                           member_name);
            cob_archive_close(&archive);
            return 0;
        }
        bytes = (unsigned char *)malloc(member->length == 0 ? 1 : member->length);
        if (bytes == NULL) {
            (void)snprintf(error, error_capacity, "could not allocate %s buffer", member_name);
            cob_archive_close(&archive);
            return 0;
        }
        parsed = cob_archive_read_member(&archive, member, bytes, member->length,
                                         error, error_capacity) &&
                 island_data_load(bytes, member->length, &island_records[island_index],
                                  error, error_capacity);
        free(bytes);
        if (!parsed) {
            cob_archive_close(&archive);
            return 0;
        }
    }
    cob_archive_close(&archive);

    memset(&config, 0, sizeof(config));
    config.world_index = (uint8_t)g_menu.world_index;
    config.difficulty = (uint8_t)g_menu.difficulty;
    config.selected_tribe = (uint8_t)g_menu.selected_tribe;
    /* DAT_006136b0's runtime initializer remains unresolved in the source
       analysis. Keep the core's documented explicit default until that is
       resolved; do not infer it from the selected tribe. */
    config.home_island_index = 0;
    config.randomize_class0_assignment = 0;
    config.random_seed = g_random_state;
    if (!game_session_initialize(world, island_records, &g_pad_catalog,
                                 &g_floater_catalog, &config, &session,
                                 error, error_capacity)) return 0;

    g_game_session = session;
    game_music_state_init(&g_game_music);
    g_game_session_world_index = g_menu.world_index;
    g_game_session_valid = 1;
    return 1;
}

static int load_window_catalog(char *error, size_t error_capacity)
{
    CobArchive archive = {0};
    const CobMember *member;
    unsigned char *bytes = NULL;
    int success = 0;

    if (!cob_archive_open("C:\\Program Files\\Tone\\TONE00.COB", &archive,
                          error, error_capacity)) return 0;
    member = cob_archive_find(&archive, "windows.txt");
    if (member == NULL) {
        (void)snprintf(error, error_capacity, "windows.txt was not found in TONE00.COB");
        goto done;
    }
    bytes = (unsigned char *)malloc(member->length == 0 ? 1 : member->length);
    if (bytes == NULL || !cob_archive_read_member(&archive, member, bytes,
                                                   member->length, error,
                                                   error_capacity)) goto done;
    success = window_catalog_load(bytes, member->length, &g_window_catalog,
                                  error, error_capacity);
done:
    free(bytes);
    cob_archive_close(&archive);
    return success;
}

static int load_building_render_catalog(char *error, size_t error_capacity)
{
    CobArchive archive = {0};
    const CobMember *pad_member;
    const CobMember *floater_member;
    const CobMember *floater_animation_member;
    const CobMember *effects_member;
    const CobMember *animation_member;
    const CobMember *description_member;
    const CobMember *name_member;
    unsigned char *pad_bytes = NULL;
    unsigned char *floater_bytes = NULL;
    unsigned char *floater_animation_bytes = NULL;
    unsigned char *effects_bytes = NULL;
    unsigned char *animation_bytes = NULL;
    unsigned char *description_bytes = NULL;
    unsigned char *name_bytes = NULL;
    PadCatalog pads;
    FloaterCatalog floaters;
    BuildingRenderCatalog animations;
    int success = 0;

    if (!cob_archive_open("C:\\Program Files\\Tone\\TONE00.COB", &archive,
                          error, error_capacity)) return 0;
    pad_member = cob_archive_find(&archive, "pad.txt");
    floater_member = cob_archive_find(&archive, "floater.txt");
    floater_animation_member = cob_archive_find(&archive, "fltinf.txt");
    effects_member = cob_archive_find(&archive, "effects.txt");
    animation_member = cob_archive_find(&archive, "bldinf.txt");
    description_member = cob_archive_find(&archive, "bldtxt.txt");
    name_member = cob_archive_find(&archive, "bldname.txt");
    if (pad_member == NULL || floater_member == NULL || floater_animation_member == NULL ||
        effects_member == NULL ||
        animation_member == NULL || description_member == NULL ||
        name_member == NULL) {
        (void)snprintf(error, error_capacity,
                       "pad.txt, floater.txt, fltinf.txt, effects.txt, bldinf.txt, bldtxt.txt or bldname.txt was not found in TONE00.COB");
        goto done;
    }
    pad_bytes = (unsigned char *)malloc(pad_member->length == 0 ? 1 : pad_member->length);
    floater_bytes = (unsigned char *)malloc(floater_member->length == 0 ? 1 : floater_member->length);
    floater_animation_bytes = (unsigned char *)malloc(floater_animation_member->length == 0
                                                       ? 1 : floater_animation_member->length);
    effects_bytes = (unsigned char *)malloc(effects_member->length == 0
                                             ? 1 : effects_member->length);
    animation_bytes = (unsigned char *)malloc(animation_member->length == 0
                                               ? 1 : animation_member->length);
    description_bytes = (unsigned char *)malloc(description_member->length == 0
                                                  ? 1 : description_member->length);
    name_bytes = (unsigned char *)malloc(name_member->length == 0
                                           ? 1 : name_member->length);
    if (pad_bytes == NULL || floater_bytes == NULL || floater_animation_bytes == NULL ||
        effects_bytes == NULL ||
        animation_bytes == NULL || description_bytes == NULL ||
        name_bytes == NULL ||
        !cob_archive_read_member(&archive, pad_member, pad_bytes, pad_member->length,
                                 error, error_capacity) ||
        !cob_archive_read_member(&archive, floater_member, floater_bytes, floater_member->length,
                                 error, error_capacity) ||
        !cob_archive_read_member(&archive, floater_animation_member, floater_animation_bytes,
                                 floater_animation_member->length, error, error_capacity) ||
        !cob_archive_read_member(&archive, effects_member, effects_bytes,
                                 effects_member->length, error, error_capacity) ||
        !cob_archive_read_member(&archive, animation_member, animation_bytes,
                                 animation_member->length, error, error_capacity) ||
        !cob_archive_read_member(&archive, description_member, description_bytes,
                                 description_member->length, error, error_capacity) ||
        !cob_archive_read_member(&archive, name_member, name_bytes,
                                 name_member->length, error, error_capacity) ||
        !pad_catalog_load(pad_bytes, pad_member->length, &pads, error, error_capacity) ||
        !floater_catalog_load(floater_bytes, floater_member->length, &floaters,
                              error, error_capacity) ||
        !floater_catalog_load_animations(floater_animation_bytes,
                                         floater_animation_member->length,
                                         &floaters, error, error_capacity) ||
        !floater_catalog_load_impact_effects(effects_bytes, effects_member->length,
                                             &floaters, error, error_capacity) ||
        !building_render_catalog_load(animation_bytes, animation_member->length,
                                       &pads, &animations, error, error_capacity)) {
        goto done;
    }
    memset(g_building_names, 0, sizeof(g_building_names));
    if (extract_repeated_help_entries(name_bytes, name_member->length, "BLDNAME",
                                      g_building_names, BUILDING_NAME_COUNT) !=
        BUILDING_NAME_COUNT) {
        (void)snprintf(error, error_capacity,
                       "bldname.txt did not contain all 64 BLDNAME entries");
        goto done;
    }
    memset(g_building_descriptions, 0, sizeof(g_building_descriptions));
    {
        uint16_t item_index;
        for (item_index = 0; item_index < pads.item_count; ++item_index) {
            const PadCatalogItem *item = &pads.items[item_index];
            if (item->text_id[0] != '\0') {
                (void)extract_help_entry(description_bytes, description_member->length,
                    item->text_id, g_building_descriptions[item->item_id],
                    sizeof(g_building_descriptions[item->item_id]));
            }
        }
    }
    g_pad_catalog = pads;
    g_floater_catalog = floaters;
    g_building_render_catalog = animations;
    success = 1;
done:
    free(name_bytes);
    free(pad_bytes);
    free(floater_bytes);
    free(floater_animation_bytes);
    free(effects_bytes);
    free(animation_bytes);
    free(description_bytes);
    cob_archive_close(&archive);
    return success;
}

static int load_menu_art(char *error, size_t error_capacity)
{
    CobArchive archive = {0};
    COLORREF title_palette[256];
    COLORREF newgame_palette[256];
    COLORREF mainmap_palette[256];
    const char *path = "C:\\Program Files\\Tone\\TONE01.COB";
    int success = 0;
    if (!cob_archive_open(path, &archive, error, error_capacity)) return 0;
    if (!load_palette(&archive, "data\\titscrn.pal", title_palette, NULL,
                      error, error_capacity) ||
        !load_palette(&archive, "data\\newgame.pal", newgame_palette, NULL,
                      error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\titscrn.shp", title_palette,
                           &g_title_art, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\loadsav0.shp", title_palette,
                           &g_load_save_art, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\newback.shp", newgame_palette,
                           &g_new_background, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\ngmeintr.shp", newgame_palette,
                           &g_new_buttons, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\glyphs.shp", newgame_palette,
                           &g_glyphs, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\ngrealms.shp", newgame_palette,
                           &g_realm_art, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\bigfloat.shp", newgame_palette,
                           &g_big_floaters, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\levidif.shp", newgame_palette,
                           &g_difficulty_art, error, error_capacity) ||
        !load_palette(&archive, "data\\mainmap.pal", mainmap_palette, NULL,
                      error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\mapback.shp", mainmap_palette,
                           &g_map_background, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\smisle.shp", mainmap_palette,
                           &g_small_islands, error, error_capacity)) {
        goto done;
    }
    {
        const CobMember *button = cob_archive_find(&archive, "data\\button.wav");
        const CobMember *floater_build = cob_archive_find(&archive, "data\\fltbuild.wav");
        const CobMember *leviathan_build = cob_archive_find(&archive, "data\\levbuild.wav");
        const CobMember *floater_birth = cob_archive_find(&archive, "data\\fltbirth.wav");
        const CobMember *bridge = cob_archive_find(&archive, "data\\bridge.wav");
        if (button != NULL && button->length >= 44) {
            g_button_sound = (unsigned char *)malloc(button->length);
            if (g_button_sound == NULL ||
                !cob_archive_read_member(&archive, button, g_button_sound,
                                         button->length, error, error_capacity)) {
                free(g_button_sound);
                g_button_sound = NULL;
            }
        }
        if (floater_build != NULL && floater_build->length >= 44) {
            g_fltbuild_sound = (unsigned char *)malloc(floater_build->length);
            if (g_fltbuild_sound == NULL ||
                !cob_archive_read_member(&archive, floater_build, g_fltbuild_sound,
                                         floater_build->length, error, error_capacity)) {
                free(g_fltbuild_sound);
                g_fltbuild_sound = NULL;
            }
        }
        if (leviathan_build != NULL && leviathan_build->length >= 44) {
            g_levbuild_sound = (unsigned char *)malloc(leviathan_build->length);
            if (g_levbuild_sound == NULL ||
                !cob_archive_read_member(&archive, leviathan_build, g_levbuild_sound,
                                         leviathan_build->length, error, error_capacity)) {
                free(g_levbuild_sound);
                g_levbuild_sound = NULL;
            }
        }
        if (floater_birth != NULL && floater_birth->length >= 44) {
            g_fltbirth_sound = (unsigned char *)malloc(floater_birth->length);
            if (g_fltbirth_sound == NULL ||
                !cob_archive_read_member(&archive, floater_birth, g_fltbirth_sound,
                                         floater_birth->length, error, error_capacity)) {
                free(g_fltbirth_sound);
                g_fltbirth_sound = NULL;
            }
        }
        if (bridge != NULL && bridge->length >= 44) {
            g_bridge_sound = (unsigned char *)malloc(bridge->length);
            if (g_bridge_sound == NULL ||
                !cob_archive_read_member(&archive, bridge, g_bridge_sound,
                                         bridge->length, error, error_capacity)) {
                free(g_bridge_sound);
                g_bridge_sound = NULL;
            }
        }
    }
    {
        const CobMember *font = cob_archive_find(&archive, "data\\bgoutfnt.fnt");
        unsigned char *bytes = NULL;
        if (font == NULL) {
            (void)snprintf(error, error_capacity, "data\\bgoutfnt.fnt was not found in TONE01.COB");
            goto done;
        }
        bytes = (unsigned char *)malloc(font->length);
        if (bytes == NULL ||
            !cob_archive_read_member(&archive, font, bytes, font->length,
                                     error, error_capacity) ||
            !bitmap_font_init(&g_bitmap_font, bytes, font->length,
                              error, error_capacity)) {
            free(bytes);
            goto done;
        }
        free(bytes);
    }
    memcpy(g_newgame_palette, newgame_palette, sizeof(g_newgame_palette));
    memcpy(g_map_palette, mainmap_palette, sizeof(g_map_palette));
    success = 1;
done:
    cob_archive_close(&archive);
    if (!success) {
        free_sprite_sheet(&g_title_art);
        free_sprite_sheet(&g_new_background);
        free_sprite_sheet(&g_new_buttons);
        free_sprite_sheet(&g_glyphs);
        free_sprite_sheet(&g_realm_art);
        free_sprite_sheet(&g_big_floaters);
        free_sprite_sheet(&g_difficulty_art);
        free_sprite_sheet(&g_map_background);
        free_sprite_sheet(&g_small_islands);
        free_sprite_sheet(&g_load_save_art);
        bitmap_font_free(&g_bitmap_font);
        free(g_button_sound);
        g_button_sound = NULL;
        free(g_fltbuild_sound);
        g_fltbuild_sound = NULL;
        free(g_levbuild_sound);
        g_levbuild_sound = NULL;
        free(g_fltbirth_sound);
        g_fltbirth_sound = NULL;
        free(g_bridge_sound);
        g_bridge_sound = NULL;
    }
    return success;
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous_instance,
                   LPSTR command_line, int show_command)
{
    WNDCLASSA window_class;
    HWND window;
    MSG message;
    char error[256];
    unsigned int cursor_index;
    (void)previous_instance;
    (void)command_line;

    /* Read the original PE cursor resources without executing FLOAT.EXE.
       Resource IDs follow the 17-entry table at DAT_0049c950. */
    g_original_cursor_module = LoadLibraryExA(
        "C:\\Program Files\\Tone\\FLOAT.EXE", NULL,
        LOAD_LIBRARY_AS_DATAFILE);
    if (g_original_cursor_module != NULL) {
        for (cursor_index = 0; cursor_index < GAME_CURSOR_SLOT_COUNT;
             ++cursor_index) {
            g_interaction_cursors[cursor_index] = (HCURSOR)LoadImageA(
                g_original_cursor_module,
                MAKEINTRESOURCEA(g_cursor_resource_ids[cursor_index]),
                IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE);
        }
    }

    if (!load_world_map(error, sizeof(error)) ||
        !load_window_catalog(error, sizeof(error)) ||
        !load_building_render_catalog(error, sizeof(error)) ||
        !load_menu_art(error, sizeof(error)) ||
        !load_menu_help(error, sizeof(error)) ||
        !load_island_panel_info_text(error, sizeof(error)) ||
        !create_help_sheet(&g_menu_help, error, sizeof(error)) ||
        !load_newgame_captions(error, sizeof(error)) ||
        !create_newgame_caption_sheet(&g_newgame_captions, error, sizeof(error)) ||
        !load_island_names(error, sizeof(error)) ||
        !create_island_name_sheet(&g_island_names_art, error, sizeof(error)) ||
        !load_tribe_descriptions(error, sizeof(error)) ||
        !create_tribe_description_sheet(&g_tribe_descriptions,
                                        error, sizeof(error))) {
        MessageBoxA(NULL, error, "Tone Rebellion remake - data error", MB_OK | MB_ICONERROR);
        return 1;
    }
    g_resume_available = resume_header_is_valid();
    scan_load_slots();
    g_menu.world_index = 0;
    g_menu.difficulty = 0;
    g_menu.selected_tribe = 0;
    g_menu.selected_map_island = -1;
    {
        LARGE_INTEGER seed;
        QueryPerformanceCounter(&seed);
        g_random_state = (uint32_t)seed.LowPart;
    }

    memset(&window_class, 0, sizeof(window_class));
    window_class.lpfnWndProc = menu_window_proc;
    window_class.hInstance = instance;
    window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
    window_class.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    window_class.lpszClassName = "ToneRebellionRemakeMenu";
    if (!RegisterClassA(&window_class)) {
        MessageBoxA(NULL, "Could not register the menu window class.",
                    "Tone Rebellion remake", MB_OK | MB_ICONERROR);
        return 1;
    }
    window = CreateWindowExA(0, window_class.lpszClassName,
                             "Tone Rebellion - New Game",
                             WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                             1040, 820, NULL, NULL, instance, NULL);
    if (window == NULL) {
        MessageBoxA(NULL, "Could not create the menu window.",
                    "Tone Rebellion remake", MB_OK | MB_ICONERROR);
        return 1;
    }
    update_window_title(window);
    /* The original main loop requests `start` without a repeat flag before
       the title menu settles on `ambi1`. */
    set_background_tune_once("start");
    (void)SetTimer(window, 1, 33, NULL);
    (void)SetTimer(window, 2, 1000, NULL);
    ShowWindow(window, show_command);
    UpdateWindow(window);
    while (GetMessageA(&message, NULL, 0, 0) > 0) {
        TranslateMessage(&message);
        DispatchMessageA(&message);
    }
    if (g_original_cursor_module != NULL) {
        for (cursor_index = 0; cursor_index < GAME_CURSOR_SLOT_COUNT;
             ++cursor_index) {
            if (g_interaction_cursors[cursor_index] != NULL) {
                DestroyCursor(g_interaction_cursors[cursor_index]);
                g_interaction_cursors[cursor_index] = NULL;
            }
        }
        FreeLibrary(g_original_cursor_module);
        g_original_cursor_module = NULL;
    }
    free_sprite_sheet(&g_title_art);
    free_sprite_sheet(&g_new_background);
    free_sprite_sheet(&g_new_buttons);
    free_sprite_sheet(&g_glyphs);
    free_sprite_sheet(&g_realm_art);
    free_sprite_sheet(&g_big_floaters);
    free_sprite_sheet(&g_difficulty_art);
    free_sprite_sheet(&g_map_background);
    free_sprite_sheet(&g_small_islands);
    free_sprite_sheet(&g_island_surface_art);
    free_sprite_sheet(&g_island_template_art);
    free_sprite_sheet(&g_island_lilmap_art);
    free_sprite_sheet(&g_island_main_buttons);
    free_sprite_sheet(&g_island_realm_art);
    for (unsigned int effect_index = 0; effect_index < 4; ++effect_index) {
        free_sprite_sheet(&g_leviathan_projectile_art[effect_index]);
        free_sprite_sheet(&g_leviathan_impact_art[effect_index]);
    }
    free_sprite_sheet(&g_floater_info_art);
    free_sprite_sheet(&g_hall_command_art);
    free_sprite_sheet(&g_glyph_inventory_art);
    free_sprite_sheet(&g_trade_button_art);
    free_sprite_sheet(&g_tone_field_art);
    free_sprite_sheet(&g_pad_art);
    free_sprite_sheet(&g_bridge_trigger_art);
    free_sprite_sheet(&g_temp_hole_art);
    free_sprite_sheet(&g_build_cycle_art);
    free_sprite_sheet(&g_task_scroll_art);
    free_sprite_sheet(&g_task_icon_art);
    free_sprite_sheet(&g_task_priority_art);
    free_sprite_sheet(&g_bildtone_art);
    free_sprite_sheet(&g_tone_crys_art);
    free_sprite_sheet(&g_magctone_art);
    free_sprite_sheet(&g_crumble_art);
    free_sprite_sheet(&g_hall_stock_art);
    free_sprite_sheet(&g_repair_button_art);
    free_sprite_sheet(&g_upgrade_button_art);
    free_sprite_sheet(&g_building_command_art);
    free_sprite_sheet(&g_inventory_item_art);
    free_sprite_sheet(&g_diplomacy_art);
    {
        unsigned int hall_index;
        unsigned int item_index;
        for (hall_index = 0; hall_index < 4; ++hall_index) {
            free_sprite_sheet(&g_initial_floater_bodies[hall_index]);
            free_sprite_sheet(&g_initial_floater_legs[hall_index]);
            free_sprite_sheet(&g_initial_floater_bodies_flipped[hall_index]);
            free_sprite_sheet(&g_initial_floater_legs_flipped[hall_index]);
        }
        free_sprite_sheet(&g_leviathan_body_art);
        free_sprite_sheet(&g_leviathan_body_art_flipped);
        for (hall_index = 0; hall_index < 9; ++hall_index) {
            free_sprite_sheet(&g_leviathan_legs[hall_index]);
            free_sprite_sheet(&g_leviathan_legs_flipped[hall_index]);
        }
        for (item_index = 0; item_index < PAD_CATALOG_MAX_ITEMS; ++item_index) {
            free_sprite_sheet(&g_building_art[item_index]);
        }
    }
    free_sprite_sheet(&g_island_feature_art);
    free_sprite_sheet(&g_island_names_art);
    free_sprite_sheet(&g_load_save_art);
    free_sprite_sheet(&g_menu_help);
    free_sprite_sheet(&g_newgame_captions);
    free_sprite_sheet(&g_tribe_descriptions);
    bitmap_font_free(&g_bitmap_font);
    stop_background_tune();
    (void)PlaySoundA(NULL, NULL, 0);
    free(g_button_sound);
    free(g_fltbuild_sound);
    free(g_levbuild_sound);
    free(g_fltbirth_sound);
    free(g_bridge_sound);
    free(g_island_height_data);
    return (int)message.wParam;
}
