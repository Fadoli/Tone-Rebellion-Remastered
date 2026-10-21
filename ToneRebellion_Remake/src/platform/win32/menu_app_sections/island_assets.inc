static int load_island_surface(int island_id, int map_island_index,
                               char *error, size_t error_capacity)
{
    static const uint8_t feature_frame_counts[ISLAND_NAME_COUNT] = {
        5, 3, 3, 2, 3, 3, 3, 3, 3, 3, 3, 4, 3, 3, 1
    };
    CobArchive archive = {0};
    SpriteSheet candidate = {0};
    SpriteSheet template_candidate = {0};
    SpriteSheet lilmap_candidate = {0};
    SpriteSheet main_buttons_candidate = {0};
    SpriteSheet realm_candidate = {0};
    SpriteSheet hall_command_candidate = {0};
    SpriteSheet glyph_inventory_candidate = {0};
    SpriteSheet trade_button_candidate = {0};
    SpriteSheet tone_candidate = {0};
    SpriteSheet pad_candidate = {0};
    SpriteSheet bridge_candidate = {0};
    SpriteSheet activation_icon_candidate = {0};
    SpriteSheet building_gauge_candidate = {0};
    SpriteSheet building_number_candidate = {0};
    SpriteSheet temp_hole_candidate = {0};
    SpriteSheet build_cycle_candidate = {0};
    SpriteSheet task_scroll_candidate = {0};
    SpriteSheet task_icon_candidate = {0};
    SpriteSheet task_priority_candidate = {0};
    SpriteSheet bildtone_candidate = {0};
    SpriteSheet tone_crys_candidate = {0};
    SpriteSheet magctone_candidate = {0};
    SpriteSheet crumble_candidate = {0};
    SpriteSheet solidpad_candidate = {0};
    SpriteSheet hall_stock_candidate = {0};
    SpriteSheet repair_button_candidate = {0};
    SpriteSheet upgrade_button_candidate = {0};
    SpriteSheet building_command_candidate = {0};
    SpriteSheet inventory_item_candidate = {0};
    SpriteSheet diplomacy_candidate = {0};
    SpriteSheet defense_projectile_candidates[4] = {{0}};
    SpriteSheet defense_impact_candidates[4] = {{0}};
    SpriteSheet floater_info_candidate = {0};
    SpriteSheet building_candidates[PAD_CATALOG_MAX_ITEMS] = {{0}};
    SpriteSheet floater_body_candidates[4] = {{0}};
    SpriteSheet floater_leg_candidates[4] = {{0}};
    SpriteSheet floater_body_flipped_candidates[4] = {{0}};
    SpriteSheet floater_leg_flipped_candidates[4] = {{0}};
    SpriteSheet leviathan_body_candidate = {0};
    SpriteSheet leviathan_body_flipped_candidate = {0};
    SpriteSheet leviathan_leg_candidates[9] = {{0}};
    SpriteSheet leviathan_leg_flipped_candidates[9] = {{0}};
    SpriteSheet feature_candidate = {0};
    SpriteSheet leviathan_reveal_candidate = {0};
    COLORREF palette[256];
    uint8_t palette_rgb6[ISLAND_HAZE_PALETTE_BYTES];
    IslandData parsed;
    IslandHaze haze_candidate;
    unsigned char *height_data = NULL;
    unsigned char *text_data = NULL;
    const CobMember *height_member;
    const CobMember *text_member;
    char shape_name[48];
    char palette_name[48];
    char template_shape_name[32];
    char height_name[48];
    char text_name[48];
    char feature_name[48];
    static const char *const floater_body_names[4] = {
        "data\\pbod.shp", "data\\sbod.shp", "data\\mbod.shp", "data\\lbod.shp"
    };
    static const char *const floater_leg_names[4] = {
        "data\\plegs.shp", "data\\slegs.shp", "data\\mlegs.shp", "data\\llegs.shp"
    };
    static const char *const leviathan_leg_names[9] = {
        "data\\v-spore.shp", "data\\vpclegs.shp", "data\\vprlegs.shp",
        "data\\vsclegs.shp", "data\\vsrlegs.shp", "data\\veclegs.shp",
        "data\\verlegs.shp", "data\\vnclegs.shp", "data\\vnrlegs.shp"
    };
    /* Require the frames used by the remake's movement animations. Some
       shapeinf.txt attack ranges extend past the frames in the shipped
       vsclegs.shp and verlegs.shp sheets; those attacks fall back to movement. */
    static const uint8_t leviathan_leg_frame_counts[9] = {
        10, 20, 37, 16, 16, 17, 11, 23, 25
    };
    static const char *const defense_impact_names[4] = {
        "data\\phy.shp", "data\\sup.shp", "data\\erealm.shp",
        "data\\nrealm.shp"
    };
    unsigned int hall_index;
    unsigned int item_id;
    int selected_player;
    const GameRuntimeIsland *runtime_island = NULL;
    const char *archive_path = "C:\\Program Files\\Tone\\TONE01.COB";
    int success = 0;

    if (island_id < 0 || island_id >= ISLAND_NAME_COUNT) {
        (void)snprintf(error, error_capacity, "island id is out of the supported range");
        return 0;
    }
    if (g_game_session_valid && g_game_session_world_index == g_menu.world_index &&
        map_island_index >= 0 && map_island_index < g_game_session.island_count) {
        runtime_island = &g_game_session.islands[map_island_index];
    }
    selected_player = g_game_session_valid
        ? (int)g_game_session.config.selected_tribe : g_menu.selected_tribe;
    if (selected_player < 0 || selected_player >= GAME_START_PLAYER_COUNT) {
        (void)snprintf(error, error_capacity, "selected tribe is out of range");
        return 0;
    }
    (void)snprintf(shape_name, sizeof(shape_name), "data\\island%02d.shp", island_id);
    (void)snprintf(palette_name, sizeof(palette_name), "data\\island%02d.pal", island_id);
    (void)snprintf(template_shape_name, sizeof(template_shape_name),
                   "data\\isletmp%d.shp", selected_player);
    (void)snprintf(height_name, sizeof(height_name), "data\\island%02d.hzt", island_id);
    (void)snprintf(text_name, sizeof(text_name), "data\\island%02d.txt", island_id);
    (void)snprintf(feature_name, sizeof(feature_name), "data\\i%02d-feat.shp", island_id);
    if (!cob_archive_open(archive_path, &archive, error, error_capacity)) return 0;
    if (!load_palette(&archive, palette_name, palette, palette_rgb6,
                      error, error_capacity) ||
        !load_sprite_sheet(&archive, shape_name, palette, &candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, template_shape_name, palette,
                           &template_candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\lilmap.shp", palette,
                           &lilmap_candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\mainbut0.shp", palette,
                           &main_buttons_candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\isrealm.shp", palette,
                           &realm_candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\fltinfo.shp", palette,
                           &floater_info_candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\thall0.shp", palette,
                           &hall_command_candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\glinv.shp", palette,
                           &glyph_inventory_candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\trade.shp", palette,
                           &trade_button_candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\tone.shp", palette, &tone_candidate,
                           error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\pad.shp", palette, &pad_candidate,
                           error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\br-trg01.shp", palette, &bridge_candidate,
                           error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\acticon.shp", palette,
                           &activation_icon_candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\bldgage.shp", palette,
                           &building_gauge_candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\bildicon.shp", palette,
                           &building_number_candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\temphol0.shp", palette, &temp_hole_candidate,
                           error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\scarrow0.shp", palette, &build_cycle_candidate,
                           error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\scroll.shp", palette, &task_scroll_candidate,
                           error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\taskicon.shp", palette,
                           &task_icon_candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\prior.shp", palette,
                           &task_priority_candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\bildtone.shp", palette, &bildtone_candidate,
                           error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\tonecrys.shp", palette,
                           &tone_crys_candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\magctone.shp", palette,
                           &magctone_candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\crumble.shp", palette,
                           &crumble_candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\solidpad.shp", palette,
                           &solidpad_candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\thbutt.shp", palette, &hall_stock_candidate,
                           error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\repair.shp", palette,
                           &repair_button_candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\upgrade.shp", palette,
                           &upgrade_button_candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\trainbut.shp", palette,
                           &building_command_candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\alltrigs.shp", palette,
                           &inventory_item_candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\diploma.shp", palette,
                           &diplomacy_candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\v-shot1b.shp", palette,
                           &defense_projectile_candidates[0], error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\v-sht2fx.shp", palette,
                           &defense_projectile_candidates[1], error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\v-mnrb.shp", palette,
                           &defense_projectile_candidates[2], error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\join4.shp", palette,
                           &defense_projectile_candidates[3], error, error_capacity) ||
        !load_sprite_sheet(&archive, defense_impact_names[0], palette,
                           &defense_impact_candidates[0], error, error_capacity) ||
        !load_sprite_sheet(&archive, defense_impact_names[1], palette,
                           &defense_impact_candidates[1], error, error_capacity) ||
        !load_sprite_sheet(&archive, defense_impact_names[2], palette,
                           &defense_impact_candidates[2], error, error_capacity) ||
        !load_sprite_sheet(&archive, defense_impact_names[3], palette,
                           &defense_impact_candidates[3], error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\v-nsupfx.shp", palette,
                           &leviathan_reveal_candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, feature_name, palette, &feature_candidate,
                           error, error_capacity)) {
        goto done;
    }
    if (leviathan_reveal_candidate.frame_count == 0) {
        (void)snprintf(error, error_capacity,
                       "data\\v-nsupfx.shp lacks the Leviathan reveal frame");
        goto done;
    }
    if (inventory_item_candidate.frame_count < GAME_INVENTORY_ITEM_COUNT) {
        (void)snprintf(error, error_capacity,
                       "data\\alltrigs.shp has fewer frames than inventory IDs 5..33");
        goto done;
    }
    if (diplomacy_candidate.frame_count < 24) {
        (void)snprintf(error, error_capacity,
                       "data\\diploma.shp lacks diplomacy frames 0..23");
        goto done;
    }
    if (bildtone_candidate.frame_count <= 4 || tone_crys_candidate.frame_count <= 4 ||
        magctone_candidate.frame_count <= 4) {
        (void)snprintf(error, error_capacity,
                       "Trade resource sheets must provide source frame 4");
        goto done;
    }
    if (crumble_candidate.frame_count < 36) {
        (void)snprintf(error, error_capacity,
                       "data\\crumble.shp must provide 36 destruction frames");
        goto done;
    }
    /* Load only item sheets referenced by this island's actual runtime records.
       bldinf.txt supplies their animation ranges; pad.txt supplies the SHP key. */
    if (runtime_island != NULL) {
        for (hall_index = 0; hall_index < runtime_island->location_count; ++hall_index) {
            int32_t raw_id = runtime_island->locations[hall_index].record_value_10;
            const BuildingRenderItem *definition;
            char item_shape[BUILDING_RENDER_SHAPE_CAPACITY];
            char item_member[48];
            char item_error[128];
            if (raw_id <= 0 || raw_id >= g_pad_catalog.item_count) continue;
            item_id = (unsigned int)raw_id;
            if (building_candidates[item_id].frames != NULL) continue;
            definition = building_render_find(&g_building_render_catalog,
                                               (uint16_t)item_id);
            if (definition == NULL || definition->shape_id[0] == '\0' ||
                strcmp(definition->shape_id, "noshape") == 0) continue;
            (void)snprintf(item_shape, sizeof(item_shape), "%s", definition->shape_id);
            {
                char *character;
                for (character = item_shape; *character != '\0'; ++character) {
                    if (*character >= 'A' && *character <= 'Z') {
                        *character = (char)(*character - 'A' + 'a');
                    }
                }
            }
            (void)snprintf(item_member, sizeof(item_member), "data\\%s.shp", item_shape);
            if (!load_sprite_sheet(&archive, item_member, palette,
                                   &building_candidates[item_id], item_error,
                                   sizeof(item_error))) {
                /* Some data entries are logical items without a drawable SHP. */
                free_sprite_sheet(&building_candidates[item_id]);
                continue;
            }
        }
    }

    /* IWConstruct's ordered candidates come from FUN_0045f121. Preload their
       selected player's actual item sheets so the grid can show source art. */
    if (g_game_session_valid) {
        static const uint8_t construction_candidates[IW_CONSTRUCT_BUILD_CANDIDATE_COUNT] = {
            40, 37, 39, 38, 44, 45, 46, 47
        };
        unsigned int candidate_index;
        for (candidate_index = 0;
             candidate_index < IW_CONSTRUCT_BUILD_CANDIDATE_COUNT; ++candidate_index) {
            const BuildingRenderItem *definition;
            char item_shape[BUILDING_RENDER_SHAPE_CAPACITY];
            char item_member[48];
            char item_error[128];
            item_id = construction_candidates[candidate_index] +
                      (unsigned int)g_game_session.config.selected_tribe * 16U;
            if (item_id >= PAD_CATALOG_MAX_ITEMS ||
                item_id >= g_pad_catalog.item_count ||
                building_candidates[item_id].frames != NULL) continue;
            definition = building_render_find(&g_building_render_catalog,
                                               (uint16_t)item_id);
            if (definition == NULL || definition->shape_id[0] == '\0' ||
                strcmp(definition->shape_id, "noshape") == 0) continue;
            (void)snprintf(item_shape, sizeof(item_shape), "%s", definition->shape_id);
            {
                char *character;
                for (character = item_shape; *character != '\0'; ++character) {
                    if (*character >= 'A' && *character <= 'Z') {
                        *character = (char)(*character - 'A' + 'a');
                    }
                }
            }
            (void)snprintf(item_member, sizeof(item_member), "data\\%s.shp", item_shape);
            if (!load_sprite_sheet(&archive, item_member, palette,
                                   &building_candidates[item_id], item_error,
                                   sizeof(item_error))) {
                free_sprite_sheet(&building_candidates[item_id]);
            }
        }
    }
    /* FUN_0042704b (fltdraw.cpp) draws tribe-specific body and legs sheets.
       shapeinf.txt specifies base-worker body frame 0 and hover frames 0..15. */
    for (hall_index = 0; hall_index < 4; ++hall_index) {
        if (!load_sprite_sheet(&archive, floater_body_names[hall_index], palette,
                               &floater_body_candidates[hall_index], error, error_capacity) ||
            !load_sprite_sheet(&archive, floater_leg_names[hall_index], palette,
                               &floater_leg_candidates[hall_index], error, error_capacity)) {
            goto done;
        }
        if (floater_body_candidates[hall_index].frame_count == 0 ||
            floater_leg_candidates[hall_index].frame_count < 16) {
            (void)snprintf(error, error_capacity,
                           "%s or %s lacks the base-worker or hover frames in shapeinf.txt",
                           floater_body_names[hall_index], floater_leg_names[hall_index]);
            goto done;
        }
        if (!mirror_sprite_sheet_horizontally(&floater_body_candidates[hall_index],
                                              &floater_body_flipped_candidates[hall_index],
                                              error, error_capacity) ||
            !mirror_sprite_sheet_horizontally(&floater_leg_candidates[hall_index],
                                              &floater_leg_flipped_candidates[hall_index],
                                              error, error_capacity)) {
            goto done;
        }
    }
    if (!load_sprite_sheet(&archive, "data\\vbod.shp", palette,
                           &leviathan_body_candidate, error, error_capacity))
        goto done;
    if (leviathan_body_candidate.frame_count < 16 ||
        !mirror_sprite_sheet_horizontally(&leviathan_body_candidate,
            &leviathan_body_flipped_candidate, error, error_capacity)) {
        (void)snprintf(error, error_capacity,
                       "data\\vbod.shp lacks the Leviathan body frames");
        goto done;
    }
    for (hall_index = 0; hall_index < 9; ++hall_index) {
        if (!load_sprite_sheet(&archive, leviathan_leg_names[hall_index], palette,
                               &leviathan_leg_candidates[hall_index],
                               error, error_capacity)) goto done;
        if (leviathan_leg_candidates[hall_index].frame_count <
            leviathan_leg_frame_counts[hall_index] ||
            !mirror_sprite_sheet_horizontally(
                &leviathan_leg_candidates[hall_index],
                &leviathan_leg_flipped_candidates[hall_index],
                error, error_capacity)) {
            (void)snprintf(error, error_capacity,
                           "%s lacks the movement frames used by the remake",
                           leviathan_leg_names[hall_index]);
            goto done;
        }
    }
    if (template_candidate.frame_count != 1 ||
        template_candidate.frames[0].width != LOGICAL_WIDTH ||
        template_candidate.frames[0].height != 160) {
        (void)snprintf(error, error_capacity,
                       "data\\isletmp0.shp does not match the 640x160 ISLETEMP pane");
        goto done;
    }
    if (lilmap_candidate.frame_count != 16 ||
        lilmap_candidate.frames[0].width != 256 ||
        lilmap_candidate.frames[0].height != 32) {
        (void)snprintf(error, error_capacity,
                       "data\\lilmap.shp does not match the 16 256x32 island-map frames");
        goto done;
    }
    if (pad_candidate.frame_count != 27) {
        (void)snprintf(error, error_capacity,
                       "data\\pad.shp does not contain the 27 frames used by the pad renderer");
        goto done;
    }
    if (tone_candidate.frame_count != 40) {
        (void)snprintf(error, error_capacity,
                       "data\\tone.shp does not contain the 40 POOL frames from bldinf.txt");
        goto done;
    }
    if (bridge_candidate.frame_count != 23) {
        (void)snprintf(error, error_capacity,
                       "data\\br-trg01.shp does not contain its 23 declared animation frames");
        goto done;
    }
    if (temp_hole_candidate.frame_count < 8 || build_cycle_candidate.frame_count < 2 ||
        task_scroll_candidate.frame_count < 4 ||
        task_icon_candidate.frame_count < 8 ||
        task_priority_candidate.frame_count < 8 ||
        hall_stock_candidate.frame_count < 6 || main_buttons_candidate.frame_count < 8 ||
        repair_button_candidate.frame_count <= 11 ||
        upgrade_button_candidate.frame_count <= 13 ||
        building_command_candidate.frame_count <= 21 ||
        hall_command_candidate.frame_count < 10 ||
        floater_info_candidate.frame_count < 26 ||
        glyph_inventory_candidate.frame_count < 1U + GAME_GLYPH_COUNT * 2U ||
        trade_button_candidate.frame_count < 4 ||
        realm_candidate.frame_count < 1) {
        (void)snprintf(error, error_capacity,
                       "island controls lack the frames declared in windows.txt or shapes.txt");
        goto done;
    }
    if (candidate.frame_count != 1 || candidate.frames[0].width != 2560 ||
        candidate.frames[0].height != 320) {
        (void)snprintf(error, error_capacity,
                       "%s does not contain the expected 2560x320 island panorama", shape_name);
        goto done;
    }
    if (feature_candidate.frame_count != feature_frame_counts[island_id]) {
        (void)snprintf(error, error_capacity,
                       "%s has an unexpected island feature frame count", feature_name);
        goto done;
    }
    height_member = cob_archive_find(&archive, height_name);
    text_member = cob_archive_find(&archive, text_name);
    if (height_member == NULL || text_member == NULL) {
        (void)snprintf(error, error_capacity, "island height or location member is missing");
        goto done;
    }
    if (height_member->length != ISLAND_HAZE_FILE_BYTES) {
        (void)snprintf(error, error_capacity, "%s has an unexpected HZT length", height_name);
        goto done;
    }
    height_data = (unsigned char *)malloc(height_member->length == 0 ? 1 : height_member->length);
    text_data = (unsigned char *)malloc(text_member->length == 0 ? 1 : text_member->length);
    if (height_data == NULL || text_data == NULL ||
        !cob_archive_read_member(&archive, height_member, height_data, height_member->length,
                                error, error_capacity) ||
        !cob_archive_read_member(&archive, text_member, text_data, text_member->length,
                                error, error_capacity) ||
        !island_haze_load(height_data, height_member->length, palette_rgb6,
                          &haze_candidate, error, error_capacity) ||
        !island_data_load(text_data, text_member->length, &parsed, error, error_capacity)) {
        goto done;
    }

    free_sprite_sheet(&g_island_surface_art);
    free_sprite_sheet(&g_island_template_art);
    free_sprite_sheet(&g_island_lilmap_art);
    free_sprite_sheet(&g_island_main_buttons);
    free_sprite_sheet(&g_island_realm_art);
    free_sprite_sheet(&g_floater_info_art);
    free_sprite_sheet(&g_hall_command_art);
    free_sprite_sheet(&g_glyph_inventory_art);
    free_sprite_sheet(&g_trade_button_art);
    free_sprite_sheet(&g_tone_field_art);
    free_sprite_sheet(&g_pad_art);
    free_sprite_sheet(&g_bridge_trigger_art);
    free_sprite_sheet(&g_activation_icon_art);
    free_sprite_sheet(&g_building_gauge_art);
    free_sprite_sheet(&g_building_number_art);
    free_sprite_sheet(&g_temp_hole_art);
    free_sprite_sheet(&g_build_cycle_art);
    free_sprite_sheet(&g_task_scroll_art);
    free_sprite_sheet(&g_task_icon_art);
    free_sprite_sheet(&g_task_priority_art);
    free_sprite_sheet(&g_bildtone_art);
    free_sprite_sheet(&g_tone_crys_art);
    free_sprite_sheet(&g_magctone_art);
    free_sprite_sheet(&g_crumble_art);
    free_sprite_sheet(&g_solidpad_art);
    free_sprite_sheet(&g_hall_stock_art);
    free_sprite_sheet(&g_repair_button_art);
    free_sprite_sheet(&g_upgrade_button_art);
    free_sprite_sheet(&g_building_command_art);
    free_sprite_sheet(&g_inventory_item_art);
    free_sprite_sheet(&g_diplomacy_art);
    for (hall_index = 0; hall_index < 4; ++hall_index) {
        free_sprite_sheet(&g_leviathan_projectile_art[hall_index]);
        g_leviathan_projectile_art[hall_index] =
            defense_projectile_candidates[hall_index];
        memset(&defense_projectile_candidates[hall_index], 0,
               sizeof(defense_projectile_candidates[hall_index]));
        free_sprite_sheet(&g_leviathan_impact_art[hall_index]);
        g_leviathan_impact_art[hall_index] =
            defense_impact_candidates[hall_index];
        memset(&defense_impact_candidates[hall_index], 0,
               sizeof(defense_impact_candidates[hall_index]));
    }
    for (hall_index = 0; hall_index < 4; ++hall_index) {
        free_sprite_sheet(&g_initial_floater_bodies[hall_index]);
        g_initial_floater_bodies[hall_index] = floater_body_candidates[hall_index];
        memset(&floater_body_candidates[hall_index], 0,
               sizeof(floater_body_candidates[hall_index]));
        free_sprite_sheet(&g_initial_floater_bodies_flipped[hall_index]);
        g_initial_floater_bodies_flipped[hall_index] =
            floater_body_flipped_candidates[hall_index];
        memset(&floater_body_flipped_candidates[hall_index], 0,
               sizeof(floater_body_flipped_candidates[hall_index]));
        free_sprite_sheet(&g_initial_floater_legs[hall_index]);
        g_initial_floater_legs[hall_index] = floater_leg_candidates[hall_index];
        memset(&floater_leg_candidates[hall_index], 0,
               sizeof(floater_leg_candidates[hall_index]));
        free_sprite_sheet(&g_initial_floater_legs_flipped[hall_index]);
        g_initial_floater_legs_flipped[hall_index] =
            floater_leg_flipped_candidates[hall_index];
        memset(&floater_leg_flipped_candidates[hall_index], 0,
               sizeof(floater_leg_flipped_candidates[hall_index]));
    }
    free_sprite_sheet(&g_leviathan_body_art);
    g_leviathan_body_art = leviathan_body_candidate;
    memset(&leviathan_body_candidate, 0, sizeof(leviathan_body_candidate));
    free_sprite_sheet(&g_leviathan_body_art_flipped);
    g_leviathan_body_art_flipped = leviathan_body_flipped_candidate;
    memset(&leviathan_body_flipped_candidate, 0,
           sizeof(leviathan_body_flipped_candidate));
    for (hall_index = 0; hall_index < 9; ++hall_index) {
        free_sprite_sheet(&g_leviathan_legs[hall_index]);
        g_leviathan_legs[hall_index] = leviathan_leg_candidates[hall_index];
        memset(&leviathan_leg_candidates[hall_index], 0,
               sizeof(leviathan_leg_candidates[hall_index]));
        free_sprite_sheet(&g_leviathan_legs_flipped[hall_index]);
        g_leviathan_legs_flipped[hall_index] =
            leviathan_leg_flipped_candidates[hall_index];
        memset(&leviathan_leg_flipped_candidates[hall_index], 0,
               sizeof(leviathan_leg_flipped_candidates[hall_index]));
    }
    for (item_id = 0; item_id < PAD_CATALOG_MAX_ITEMS; ++item_id) {
        free_sprite_sheet(&g_building_art[item_id]);
        g_building_art[item_id] = building_candidates[item_id];
        memset(&building_candidates[item_id], 0, sizeof(building_candidates[item_id]));
    }
    free_sprite_sheet(&g_island_feature_art);
    free_sprite_sheet(&g_leviathan_reveal_art);
    free(g_island_height_data);
    g_island_surface_art = candidate;
    memset(&candidate, 0, sizeof(candidate));
    g_island_template_art = template_candidate;
    memset(&template_candidate, 0, sizeof(template_candidate));
    g_island_lilmap_art = lilmap_candidate;
    memset(&lilmap_candidate, 0, sizeof(lilmap_candidate));
    g_island_main_buttons = main_buttons_candidate;
    memset(&main_buttons_candidate, 0, sizeof(main_buttons_candidate));
    g_island_realm_art = realm_candidate;
    memset(&realm_candidate, 0, sizeof(realm_candidate));
    g_floater_info_art = floater_info_candidate;
    memset(&floater_info_candidate, 0, sizeof(floater_info_candidate));
    g_hall_command_art = hall_command_candidate;
    memset(&hall_command_candidate, 0, sizeof(hall_command_candidate));
    g_glyph_inventory_art = glyph_inventory_candidate;
    memset(&glyph_inventory_candidate, 0, sizeof(glyph_inventory_candidate));
    g_trade_button_art = trade_button_candidate;
    memset(&trade_button_candidate, 0, sizeof(trade_button_candidate));
    g_tone_field_art = tone_candidate;
    memset(&tone_candidate, 0, sizeof(tone_candidate));
    g_pad_art = pad_candidate;
    memset(&pad_candidate, 0, sizeof(pad_candidate));
    g_bridge_trigger_art = bridge_candidate;
    memset(&bridge_candidate, 0, sizeof(bridge_candidate));
    g_activation_icon_art = activation_icon_candidate;
    memset(&activation_icon_candidate, 0, sizeof(activation_icon_candidate));
    g_building_gauge_art = building_gauge_candidate;
    memset(&building_gauge_candidate, 0, sizeof(building_gauge_candidate));
    g_building_number_art = building_number_candidate;
    memset(&building_number_candidate, 0, sizeof(building_number_candidate));
    g_temp_hole_art = temp_hole_candidate;
    memset(&temp_hole_candidate, 0, sizeof(temp_hole_candidate));
    g_build_cycle_art = build_cycle_candidate;
    memset(&build_cycle_candidate, 0, sizeof(build_cycle_candidate));
    g_task_scroll_art = task_scroll_candidate;
    memset(&task_scroll_candidate, 0, sizeof(task_scroll_candidate));
    g_task_icon_art = task_icon_candidate;
    memset(&task_icon_candidate, 0, sizeof(task_icon_candidate));
    g_task_priority_art = task_priority_candidate;
    memset(&task_priority_candidate, 0, sizeof(task_priority_candidate));
    g_bildtone_art = bildtone_candidate;
    memset(&bildtone_candidate, 0, sizeof(bildtone_candidate));
    g_tone_crys_art = tone_crys_candidate;
    memset(&tone_crys_candidate, 0, sizeof(tone_crys_candidate));
    g_magctone_art = magctone_candidate;
    memset(&magctone_candidate, 0, sizeof(magctone_candidate));
    g_crumble_art = crumble_candidate;
    memset(&crumble_candidate, 0, sizeof(crumble_candidate));
    g_solidpad_art = solidpad_candidate;
    memset(&solidpad_candidate, 0, sizeof(solidpad_candidate));
    g_hall_stock_art = hall_stock_candidate;
    memset(&hall_stock_candidate, 0, sizeof(hall_stock_candidate));
    g_repair_button_art = repair_button_candidate;
    memset(&repair_button_candidate, 0, sizeof(repair_button_candidate));
    g_upgrade_button_art = upgrade_button_candidate;
    memset(&upgrade_button_candidate, 0, sizeof(upgrade_button_candidate));
    g_building_command_art = building_command_candidate;
    memset(&building_command_candidate, 0, sizeof(building_command_candidate));
    g_inventory_item_art = inventory_item_candidate;
    memset(&inventory_item_candidate, 0, sizeof(inventory_item_candidate));
    g_diplomacy_art = diplomacy_candidate;
    memset(&diplomacy_candidate, 0, sizeof(diplomacy_candidate));
    g_island_feature_art = feature_candidate;
    memset(&feature_candidate, 0, sizeof(feature_candidate));
    g_leviathan_reveal_art = leviathan_reveal_candidate;
    memset(&leviathan_reveal_candidate, 0, sizeof(leviathan_reveal_candidate));
    g_island_height_data = height_data;
    g_island_height_length = height_member->length;
    height_data = NULL;
    g_island_surface_data = parsed;
    build_island_draw_order();
    g_island_haze = haze_candidate;
    memcpy(g_island_palette, palette, sizeof(g_island_palette));
    rebuild_island_palette_lookup();
    g_island_surface_id = island_id;
    g_island_scroll_x = 0;
    g_selected_location = -1;
    g_hovered_location = -1;
    g_island_panel_mode = WINDOW_ISLAND_PANEL_GENERAL;
    g_task_scroll_offset = 0;
    g_selected_task_slot = -1;
    g_hovered_inventory_item = -1;
    g_hovered_hall_command = -1;
    g_iw_construct_open = 0;
    g_iw_construct_item_count = 0;
    iw_construct_info_init(&g_iw_construct_info);
    success = 1;
done:
    free_sprite_sheet(&candidate);
    free_sprite_sheet(&template_candidate);
    free_sprite_sheet(&lilmap_candidate);
    free_sprite_sheet(&main_buttons_candidate);
    free_sprite_sheet(&realm_candidate);
    free_sprite_sheet(&floater_info_candidate);
    free_sprite_sheet(&hall_command_candidate);
    free_sprite_sheet(&glyph_inventory_candidate);
    free_sprite_sheet(&trade_button_candidate);
    free_sprite_sheet(&tone_candidate);
    free_sprite_sheet(&pad_candidate);
    free_sprite_sheet(&bridge_candidate);
    free_sprite_sheet(&activation_icon_candidate);
    free_sprite_sheet(&building_gauge_candidate);
    free_sprite_sheet(&building_number_candidate);
    free_sprite_sheet(&temp_hole_candidate);
    free_sprite_sheet(&build_cycle_candidate);
    free_sprite_sheet(&task_scroll_candidate);
    free_sprite_sheet(&task_icon_candidate);
    free_sprite_sheet(&task_priority_candidate);
    free_sprite_sheet(&bildtone_candidate);
    free_sprite_sheet(&tone_crys_candidate);
    free_sprite_sheet(&magctone_candidate);
    free_sprite_sheet(&crumble_candidate);
    free_sprite_sheet(&solidpad_candidate);
    free_sprite_sheet(&hall_stock_candidate);
    free_sprite_sheet(&repair_button_candidate);
    free_sprite_sheet(&upgrade_button_candidate);
    free_sprite_sheet(&building_command_candidate);
    free_sprite_sheet(&inventory_item_candidate);
    free_sprite_sheet(&diplomacy_candidate);
    for (hall_index = 0; hall_index < 4; ++hall_index)
        free_sprite_sheet(&defense_projectile_candidates[hall_index]);
    for (hall_index = 0; hall_index < 4; ++hall_index)
        free_sprite_sheet(&defense_impact_candidates[hall_index]);
    for (item_id = 0; item_id < PAD_CATALOG_MAX_ITEMS; ++item_id) {
        free_sprite_sheet(&building_candidates[item_id]);
    }
    for (hall_index = 0; hall_index < 4; ++hall_index) {
        free_sprite_sheet(&floater_body_candidates[hall_index]);
        free_sprite_sheet(&floater_leg_candidates[hall_index]);
        free_sprite_sheet(&floater_body_flipped_candidates[hall_index]);
        free_sprite_sheet(&floater_leg_flipped_candidates[hall_index]);
    }
    free_sprite_sheet(&leviathan_body_candidate);
    free_sprite_sheet(&leviathan_body_flipped_candidate);
    for (hall_index = 0; hall_index < 9; ++hall_index) {
        free_sprite_sheet(&leviathan_leg_candidates[hall_index]);
        free_sprite_sheet(&leviathan_leg_flipped_candidates[hall_index]);
    }
    free_sprite_sheet(&feature_candidate);
    free_sprite_sheet(&leviathan_reveal_candidate);
    free(height_data);
    free(text_data);
    cob_archive_close(&archive);
    return success;
}
