/* Test support: when TONE_REBELLION_E2E_STATE names a file, the UI tick writes
   a line-oriented snapshot of the interaction state there so the end-to-end
   script (tests/e2e) can aim clicks and assert on selection instead of
   guessing from pixels. Read-only; no effect when the variable is unset. */
static int e2e_enabled(void)
{
    const char *path = getenv("TONE_REBELLION_E2E_STATE");
    return path != NULL && path[0] != '\0';
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
    (void)MoveFileExA(tmp_path, path, MOVEFILE_REPLACE_EXISTING);
}

