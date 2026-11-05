/* Test support: when TONE_REBELLION_E2E_STATE names a file, the UI tick writes
   a line-oriented snapshot of the interaction state there so the end-to-end
   script (tests/e2e) can aim clicks and assert on selection instead of
   guessing from pixels. Read-only; no effect when the variable is unset. */
static int e2e_enabled(void)
{
    const char *path = getenv("TONE_REBELLION_E2E_STATE");
    return path != NULL && path[0] != '\0';
}

/* Test support: with the state file set, TONE_REBELLION_E2E_LOAD names a
   static original save (.SAV) to start from, loaded with a fixed seed, and
   TONE_REBELLION_E2E_ISLAND the island to open. Returns 1 when loaded. */
static int e2e_build_fixture(HWND window);

static int e2e_start_fixture(HWND window)
{
    char path[MAX_PATH];
    char value[16];
    char error[160];
    if (e2e_build_fixture(window)) return 1;
    if (!e2e_enabled() ||
        !platform_environment("TONE_REBELLION_E2E_LOAD", path, sizeof(path)))
        return 0;
    g_random_state = 0x13572468U;
    if (!read_native_save_file(window, path, error, sizeof(error))) {
        platform_message_box(window, error, "Tone Rebellion remake - e2e fixture", 0);
        return 0;
    }
    if (platform_environment("TONE_REBELLION_E2E_ISLAND", value, sizeof(value)))
        (void)open_island_view(window, atoi(value));
    return 1;
}

/* Test support: TONE_REBELLION_E2E_FIXTURE=badges builds a static game
   instead (the bench's fixed world 0, tribe 0, difficulty 0 and seed), opens
   the Hall island and adds known units beside the Hall: an own warrior
   (subtype 4, full charge), an enemy subtype-1 unit and two Leviathans
   (subtypes 12 and 9). TONE_REBELLION_E2E_FIXTURE=enemy_hall builds the
   same game and opens tribe 1's Hall island instead; "spell" adds a stocked
   spell building with a linked caster and selects it; "repair" a damaged
   0x25 producer (1 hit point), selected. Returns 1 when built. */
static int e2e_build_fixture(HWND window)
{
    char name[32];
    char error[256];
    const GamePlayerEconomy *economy;
    const GameRuntimeLocation *hall;
    const FloaterStats *warrior;
    int enemy;
    uint8_t island;
    uint16_t x;
    uint16_t y;
    if (!e2e_enabled() ||
        !platform_environment("TONE_REBELLION_E2E_FIXTURE", name, sizeof(name)) ||
        (strcmp(name, "badges") != 0 && strcmp(name, "enemy_hall") != 0 &&
         strcmp(name, "spell") != 0 && strcmp(name, "dying") != 0 &&
         strcmp(name, "obtain") != 0 && strcmp(name, "victory") != 0 &&
         strcmp(name, "messages") != 0 && strcmp(name, "return") != 0 &&
         strcmp(name, "repair") != 0))
        return 0;
    g_menu.world_index = 0;
    g_menu.selected_tribe = 0;
    g_menu.difficulty = 0;
    g_random_state = 0x13572468U;
    g_sim_speed = 1U;
    if (!load_game_session_for_selected_world(error, sizeof(error))) {
        platform_message_box(window, error, "Tone Rebellion remake - e2e fixture", 0);
        return 0;
    }
    g_menu.setup_accepted = 1;
    economy = &g_game_session.economy[0];
    if (economy->hall_island_index >= g_game_session.island_count) return 0;
    island = (uint8_t)economy->hall_island_index;
    hall = &g_game_session.islands[island].locations[economy->hall_location_index];
    x = hall->x;
    y = hall->y;
    warrior = floater_catalog_find(&g_floater_catalog,
        g_game_session.player_starts.players[0].floater_type_index, 4);
    (void)native_save_add_fixture_floater(&g_game_session, &g_floater_catalog,
        0, 4, island, (uint16_t)(x + 70), (uint16_t)(y - 20), 0,
        warrior != NULL ? warrior->max_attack_points : 0);
    enemy = native_save_add_fixture_floater(&g_game_session, &g_floater_catalog,
        1, 1, island, (uint16_t)(x + 130), (uint16_t)(y - 30), 0, 0);
    /* "dying": the enemy unit dies at once (FUN_004204bc), so its death
       ticks (DIE cells) can be watched. */
    if (strcmp(name, "dying") == 0 && enemy >= 0) {
        GameFloaterStart *victim = &g_game_session.floaters[enemy];
        victim->current_hit_points = 0;
        victim->source_runtime_flags |= 0x008U;
        victim->source_death_timer = 0;
    }
    if (strcmp(name, "badges") == 0) {
        /* The Leviathans keep to the island's floater range (the Hall
           island of this world does not scroll). Only this fixture: on
           the others they fight on the island the bridge test reaches. */
        int far_x = (int)x + 240;
        int max_x = g_game_session.islands[island].floater_max_x[0];
        if (max_x > (int)x && far_x > max_x - 20) far_x = max_x - 20;
        (void)native_save_add_fixture_floater(&g_game_session,
            &g_floater_catalog, GAME_START_PLAYER_COUNT, 12, island,
            (uint16_t)far_x, (uint16_t)(y - 60), 0x31, 0); /* rank 3, level 1 */
        (void)native_save_add_fixture_floater(&g_game_session,
            &g_floater_catalog, GAME_START_PLAYER_COUNT, 9, island,
            (uint16_t)(far_x - 40), (uint16_t)(y - 10), 0, 0);
    }
    if (strcmp(name, "enemy_hall") == 0) {
        /* A built bridge out of tribe 0's and tribe 1's Hall islands, each
           partner island reachable by tribe 0. */
        uint8_t halls[2];
        unsigned int h;
        halls[0] = island;
        halls[1] = (uint8_t)g_game_session.economy[1].hall_island_index;
        for (h = 0; h < 2U; ++h) {
            GameRuntimeIsland *bridge_island;
            uint16_t location;
            if (halls[h] >= g_game_session.island_count) continue;
            bridge_island = &g_game_session.islands[halls[h]];
            for (location = 0; location < bridge_island->location_count;
                 ++location) {
                const GameRuntimeLocation *marker =
                    &bridge_island->locations[location];
                if (marker->renderer_class != 2 ||
                    marker->bridge_neighbor_island < 0 ||
                    marker->bridge_neighbor_island >= g_game_session.island_count)
                    continue;
                if (game_session_mark_bridge_constructed_at(&g_game_session,
                        halls[h], location)) {
                    g_game_session.islands[marker->bridge_neighbor_island]
                        .access_mask |= 1U;
                    break;
                }
            }
        }
        economy = &g_game_session.economy[1];
        if (economy->hall_island_index >= g_game_session.island_count) return 0;
        island = (uint8_t)economy->hall_island_index;
        x = g_game_session.islands[island]
                .locations[economy->hall_location_index].x;
        /* The fixture's tribe 0 has reached that island. A Leviathan placed
           here made the Hall's workers react and broke the click checks. */
        g_game_session.islands[island].access_mask |= 1U;
    }
    if (strcmp(name, "messages") == 0)
        /* World event 6 (FUN_00416a9a, a trained floater advanced) for the
           local tribe: FUN_004334ce shows FLTADV. */
        (void)game_session_queue_world_event(&g_game_session,
            GAME_SESSION_WORLD_EVENT_FLOATER_ADVANCED, island, 0);
    if (strcmp(name, "victory") == 0 && g_game_session.island_count > 0) {
        /* Every PIT_LeviShield seal (0x17..0x24) of the last island gone:
           FUN_00460460 starts sequence state 2 on its next pass. Speed 3. */
        GameRuntimeIsland *last =
            &g_game_session.islands[g_game_session.island_count - 1U];
        uint16_t location;
        for (location = 0; location < last->location_count; ++location)
            if (last->locations[location].record_value_10 >= 0x17 &&
                last->locations[location].record_value_10 <= 0x24)
                last->locations[location].record_value_10 = 0;
        g_sim_speed = 3U;
    }
    if (strcmp(name, "obtain") == 0) {
        /* A PIT_Object (+0x10 == 1, artifact id 6 at +0x24, no owner) on the
           nearest empty class-0 pad to the Hall, selected so BC_Obtain shows
           (FUN_0045302a command 4). */
        GameRuntimeIsland *home = &g_game_session.islands[island];
        uint16_t location;
        int best = -1;
        int best_distance = 0;
        for (location = 0; location < home->location_count; ++location) {
            const GameRuntimeLocation *site = &home->locations[location];
            int distance = (int)site->x - (int)x;
            if (distance < 0) distance = -distance;
            if (site->renderer_class != 0 || site->record_value_10 != 0 ||
                site->owner_id != -1 || distance < 40) continue;
            if (best < 0 || distance < best_distance) {
                best = (int)location;
                best_distance = distance;
            }
        }
        if (best >= 0) {
            home->locations[best].record_value_10 = 1;
            home->locations[best].record_value_24 = 6;
            if (!open_island_view(window, island)) return 0;
            g_island_scroll_x = island_clamp_scroll((int)x - 0x140);
            select_location_on_view(best);
            return 1;
        }
    }
    if (strcmp(name, "repair") == 0) {
        uint16_t location;
        for (location = 0;
             location < g_game_session.islands[island].location_count;
             ++location) {
            IslandLocation site = {0};
            site.kind = ISLAND_LOCATION_PAD;
            site.renderer_subtype =
                g_game_session.islands[island].locations[location]
                    .construction_site_size;
            if (!game_session_place_building(&g_game_session, &g_pad_catalog,
                    0, island, location, &site, 0x25, NULL, 0)) continue;
            g_game_session.islands[island].locations[location].source_value_34 = 1;
            x = g_game_session.islands[island].locations[location].x;
            if (!open_island_view(window, island)) return 0;
            g_island_scroll_x = island_clamp_scroll((int)x - 0x140);
            select_location_on_view((int)location);
            return 1;
        }
    }
    if (strcmp(name, "spell") == 0 || strcmp(name, "return") == 0) {
        /* A finished 0x2f spell building near the Hall, stocked, with one
           linked level-1 caster: tribe 0's BC_Spell7 is kind 14
           (Enchantement de tribu), cast at once without a target pick. */
        uint16_t location;
        int placed = -1;
        for (location = 0; placed < 0 &&
             location < g_game_session.islands[island].location_count;
             ++location) {
            IslandLocation site = {0};
            site.kind = ISLAND_LOCATION_PAD;
            site.renderer_subtype =
                g_game_session.islands[island].locations[location]
                    .construction_site_size;
            if (game_session_place_building(&g_game_session, &g_pad_catalog, 0,
                    island, location, &site, 0x2f, NULL, 0))
                placed = (int)location;
        }
        if (placed >= 0) {
            GameRuntimeLocation *tower =
                &g_game_session.islands[island].locations[placed];
            int caster;
            tower->resource_stock[GAME_RESOURCE_MAGIC_TONE] = 200;
            tower->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] = 200;
            caster = native_save_add_fixture_floater(&g_game_session,
                &g_floater_catalog, 0, 4, island, tower->x,
                (uint16_t)(tower->y - 10), 1, 0);
            if (caster >= 0)
                (void)game_session_link_floater_charge(&g_game_session,
                    (unsigned int)caster, (uint16_t)placed);
            if (caster >= 0 && strcmp(name, "return") == 0) {
                /* "return": the linked caster stands 150 px away and has
                   just finished a state, so the 0x41f9ba block sends it
                   back to its building (action 9). */
                GameFloaterStart *f = &g_game_session.floaters[caster];
                f->x = (uint16_t)(tower->x + 150);
                f->destination_x = f->x;
                f->previous_movement_state = 1;
                f->movement_state = 0;
            }
            x = tower->x;
            if (!open_island_view(window, island)) return 0;
            g_island_scroll_x = island_clamp_scroll((int)x - 0x140);
            select_location_on_view(placed);
            return 1;
        }
    }
    if (!open_island_view(window, island)) return 0;
    g_island_scroll_x = island_clamp_scroll((int)x - 0x140);
    /* TONE_REBELLION_E2E_SELECT: a site of the opened island to select, for
       checks of what the panels draw rather than of click hit-testing. */
    if (platform_environment("TONE_REBELLION_E2E_SELECT", name, sizeof(name)) &&
        atoi(name) >= 0 &&
        atoi(name) < (int)g_game_session.islands[island].location_count)
        select_location_on_view(atoi(name));
    return 1;
}

static void e2e_write_state(void)
{
    static const char *path;
    static int resolved;
    char tmp_path[MAX_PATH];
    FILE *file;
    unsigned int i;
    if (!resolved) {
        path = getenv("TONE_REBELLION_E2E_STATE");
        resolved = 1;
    }
    if (path == NULL || path[0] == '\0') return;
    (void)snprintf(tmp_path, sizeof(tmp_path), "%s.tmp", path);
    file = fopen(tmp_path, "wb");
    if (file == NULL) return;
    fprintf(file, "screen %d\nisland %d\nscroll %d\nselected_floater %d\n"
            "selected_location %d\npanel_mode %d\ntribe %d\n",
            (int)g_menu.screen, g_menu.selected_map_island, g_island_scroll_x,
            g_selected_floater, g_selected_location, g_island_panel_mode,
            g_menu.selected_tribe);
    fprintf(file, "hall_player %d\n", selected_hall_player());
    fprintf(file, "sequence %d\nsequence_tick %d\n",
            g_game_session_valid ? (int)g_game_session.world_sequence_state : -1,
            g_game_session_valid ? (int)g_game_session.world_sequence_tick : -1);
    fprintf(file, "construct_open %d\nconstruct_column %d\nconstruct_item %d\n",
            g_iw_construct_open, (int)g_iw_construct.hovered_column,
            (int)g_iw_construct_info.item_id);
    fprintf(file, "net_status %s\nisland_message_count %u\n",
            g_net_status[0] != '\0' ? g_net_status : "-",
            (unsigned)g_island_message_count);
    fprintf(file, "island_message %s\n",
            g_island_message_count > 0 ? g_island_messages[0].text : "-");
    fprintf(file, "paused %d\nslide_phase %d\n", g_paused, g_slide_phase);
    fprintf(file, "sim_speed %u\nnet_speed %u\nsim_tick %lu\n", g_sim_speed,
            (unsigned)g_game_session.network_speed,
            (unsigned long)g_game_session.simulation_tick);
    fprintf(file, "cast_effects %u\n",
            (unsigned int)g_game_session.active_cast_effect_count);
    fprintf(file, "text_info %s\n",
            g_e2e_text_info[0] != '\0' ? g_e2e_text_info : "-");
    fprintf(file, "anim_ticks %u\nclock_ms %lu\n", g_menu.animation_ticks,
            (unsigned long)platform_ticks_ms());
    fprintf(file, "net_mode %d\nnet_slot %d\nnet_players %u\nnet_world %d\n",
            g_net_mode, g_net_mode != NET_MODE_NONE ? (int)g_net_lobby.local_slot : -1,
            g_net_mode != NET_MODE_NONE ? net_lobby_player_count(&g_net_lobby) : 0U,
            g_menu.world_index);
    if (g_net_in_game && g_game_session_valid)
        fprintf(file, "net_delay %u\nnet_rtt %lu\nnet_issue %lu %lu\nnet_apply %lu %lu\n",
                (unsigned)g_net_lockstep.delay, (unsigned long)g_net_round_trip[1],
                (unsigned long)g_net_issue_tick, (unsigned long)g_net_issue_ms,
                (unsigned long)g_net_apply_tick, (unsigned long)g_net_apply_ms);
    if (g_net_in_game && g_game_session_valid)
        fprintf(file, "net_tick %lu\nnet_desync %d\nnet_stock_mode %d\nsync_hash %08lx\n",
                (unsigned long)g_net_lockstep.tick, (int)g_net_lockstep.desync,
                g_menu.selected_tribe >= 0 && g_menu.selected_tribe < GAME_START_PLAYER_COUNT
                    ? (int)g_game_session.economy[g_menu.selected_tribe]
                          .stock_mode[GAME_RESOURCE_BUILD_TONE] : -1,
                (unsigned long)game_session_sync_hash(&g_game_session));
    fprintf(file, "move_active %d\ncan_grab %d\nhovered_location %d\nmouse %d %d\n",
            g_game_session_valid ? (int)g_game_session.location_move_active : 0,
            selected_location_can_be_grabbed(), g_hovered_location,
            g_mouse_x, g_mouse_y);
    fprintf(file, "active_mask %u\nchoice_mask %u\n",
            g_game_session_valid
                ? (unsigned)game_session_active_player_mask(&g_game_session) : 0U,
            (unsigned)g_tribe_choice_mask);
    fprintf(file, "repair_button %d\nrepair_hovered %d\n",
            selected_repair_button_visible(), g_hovered_repair_control);
    fprintf(file, "selection_island %d\n", selection_island());
    {
        int16_t hp = -1, hp_max = -1;
        if (g_game_session_valid && g_selected_location >= 0 &&
            selection_island() >= 0)
            (void)game_session_repair_location_values(
                &g_game_session, &g_pad_catalog, (uint8_t)selection_island(),
                (uint16_t)g_selected_location, &hp, &hp_max);
        fprintf(file, "selected_hp %d\nselected_hp_max %d\n", (int)hp,
                (int)hp_max);
    }
    {
        int fading = 0;
        uint16_t fi, fl;
        if (g_game_session_valid)
            for (fi = 0; fi < g_game_session.island_count; ++fi)
                for (fl = 0; fl < g_game_session.islands[fi].location_count; ++fl)
                    if (g_game_session.islands[fi].locations[fl]
                            .move_fade_item_10 != 0) ++fading;
        fprintf(file, "fade_sites %d\nscroll_x %d\n", fading, g_island_scroll_x);
        fprintf(file, "panic_shown %d\npanic_frame %d\n",
                island_panic_flag_shown(), g_panic_pulse_frame);
    }
    if (g_game_session_valid && g_menu.selected_tribe >= 0 &&
        g_menu.selected_tribe < GAME_START_PLAYER_COUNT) {
        for (i = 0; i < 3U; ++i) {
            fprintf(file, "clip_dots %u %u\n", i,
                    game_session_clip_slot(&g_game_session,
                        (uint8_t)g_menu.selected_tribe, i, NULL, NULL));
        }
        fprintf(file, "bildicon_frames %u clip_group %d\n",
                (unsigned)g_bildicon_art.frame_count,
                (int)g_game_session.clip_group);
    }
    if (g_game_session_valid) {
        for (i = 0; i < 9U; ++i) {
            if (g_game_session.clip_slot_used[i])
                fprintf(file, "clip_slot %u %d %d\n", i,
                        (int)g_game_session.clip_slot_island[i],
                        (int)g_game_session.clip_slot_location[i]);
        }
    }
    if (g_game_session_valid && g_menu.selected_tribe >= 0 &&
        g_menu.selected_tribe < GAME_START_PLAYER_COUNT) {
        fprintf(file, "hall_island %d\nhall_location %d\n",
                (int)g_game_session.economy[g_menu.selected_tribe].hall_island_index,
                (int)g_game_session.economy[g_menu.selected_tribe].hall_location_index);
    }
    if (g_game_session_valid && g_menu.screen == SCREEN_ISLAND &&
        g_menu.selected_map_island >= 0 &&
        g_menu.selected_map_island < g_game_session.island_count) {
        const GameRuntimeIsland *island =
            &g_game_session.islands[g_menu.selected_map_island];
        for (i = 0; i < g_game_session.floater_count; ++i) {
            const GameFloaterStart *f = &g_game_session.floaters[i];
            if (!game_session_floater_is_active(f) ||
                f->island_index != g_menu.selected_map_island) continue;
            fprintf(file, "floater %u %d %d owner=%d type=%d subtype=%d "
                    "flags=%u link=%d cargo=%d\n", i, (int)f->x, (int)f->y,
                    (int)f->owner_slot, (int)f->type_index,
                    (int)f->source_subtype, (unsigned)f->source_runtime_flags,
                    (int)f->source_link_0c, (int)f->carried_resource_code);
        }
        for (i = 0; i < island->location_count; ++i) {
            const GameRuntimeLocation *l = &island->locations[i];
            fprintf(file, "location %u %d %d class=%d item=%d owner=%d "
                    "bridge=%d neighbor=%d\n", i, (int)l->x, (int)l->y,
                    (int)l->renderer_class, (int)l->record_value_10,
                    (int)l->owner_id, (int)l->bridge_constructed,
                    (int)l->bridge_neighbor_island);
        }
    }
    fclose(file);
    (void)platform_rename_replace(tmp_path, path);
}

