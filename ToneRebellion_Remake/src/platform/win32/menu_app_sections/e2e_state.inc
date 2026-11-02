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
   (subtypes 12 and 9). Returns 1 when built. */
static int e2e_build_fixture(HWND window)
{
    char name[32];
    char error[256];
    const GamePlayerEconomy *economy;
    const GameRuntimeLocation *hall;
    const FloaterStats *warrior;
    uint8_t island;
    uint16_t x;
    uint16_t y;
    if (!e2e_enabled() ||
        !platform_environment("TONE_REBELLION_E2E_FIXTURE", name, sizeof(name)) ||
        strcmp(name, "badges") != 0) return 0;
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
    (void)native_save_add_fixture_floater(&g_game_session, &g_floater_catalog,
        1, 1, island, (uint16_t)(x + 130), (uint16_t)(y - 30), 0, 0);
    (void)native_save_add_fixture_floater(&g_game_session, &g_floater_catalog,
        GAME_START_PLAYER_COUNT, 12, island, (uint16_t)(x + 520),
        (uint16_t)(y - 60), 1, 0);
    (void)native_save_add_fixture_floater(&g_game_session, &g_floater_catalog,
        GAME_START_PLAYER_COUNT, 9, island, (uint16_t)(x + 580),
        (uint16_t)(y - 10), 0, 0);
    if (!open_island_view(window, island)) return 0;
    g_island_scroll_x = island_clamp_scroll((int)x - 0x140);
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
    fprintf(file, "selection_island %d\n", selection_island());
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
                    "flags=%u link=%d\n", i, (int)f->x, (int)f->y,
                    (int)f->owner_slot, (int)f->type_index,
                    (int)f->source_subtype, (unsigned)f->source_runtime_flags,
                    (int)f->source_link_0c);
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

