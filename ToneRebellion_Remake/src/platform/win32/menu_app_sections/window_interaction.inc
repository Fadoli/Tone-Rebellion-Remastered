static void dispatch_newgame_master_message(HWND window, int message)
{
    if (g_tribe_choice_mask != 0 && g_net_mode != NET_MODE_NONE) {
        /* Network lobby of a loaded game: the lobby rules apply (played
           tribes only, world size and difficulty locked). */
        (void)net_newgame_message(window, message);
        return;
    }
    if (g_tribe_choice_mask != 0) {
        /* Loaded game: the world size and difficulty are the save's; only a
           played tribe can be picked, and NEWGAME continues the game. */
        if (message == 52) {
            finish_tribe_choice(window);
        } else if (message >= 60 && message <= 63 &&
                   (g_tribe_choice_mask & (1U << (message - 60))) != 0) {
            g_menu.selected_tribe = message - 60;
        }
        return;
    }
    if (net_newgame_message(window, message)) return;
    if (message == 52) {
        /* A new game never inherits a loaded game's pause. */
        g_paused = 0;
        slide_panel_close_now();
        (void)begin_new_game(window);
    } else if (message == 53) {
        g_menu.world_index = (g_menu.world_index + 1) % g_menu.world_map.world_count;
        g_menu.setup_accepted = 0;
    } else if (message == 55) {
        g_menu.difficulty = (g_menu.difficulty + 1) % g_difficulty_count;
        g_menu.setup_accepted = 0;
    } else if (message >= 60 && message <= 63) {
        g_menu.selected_tribe = message - 60;
        g_menu.setup_accepted = 0;
    }
}

static void handle_click(HWND window, int x, int y)
{
    int clicked_tribe = g_menu.screen == SCREEN_NEW_GAME ? tribe_icon_at(x, y) : -1;
    const WindowTemplate *control = NULL;
    g_mouse_inside = 1;
    g_mouse_x = x;
    g_mouse_y = y;
    (void)update_hover_help(x, y);
    (void)update_newgame_text(x, y);
    if (g_button_sound != NULL) {
        (void)PlaySoundA((LPCSTR)g_button_sound, NULL,
                        SND_MEMORY | SND_ASYNC | SND_NODEFAULT);
    }
    if (g_menu.screen == SCREEN_NET_SETUP) {
        net_setup_click(window, x, y);
    } else if (g_menu.screen == SCREEN_MAIN_MENU && net_setup_title_click(x, y)) {
        /* Remake-only multiplayer button over the title art. */
    } else if (g_menu.screen == SCREEN_MAIN_MENU && intro_title_click(x, y)) {
        /* Remake-only Intro button. */
    } else if (g_menu.screen == SCREEN_MAIN_MENU) {
        control = window_catalog_hit_test(&g_window_catalog, 0, x, y);
        if (control != NULL && strcmp(control->message_destination, "WINMGR") == 0) {
            if (control->send_message[0] == 5) {
                g_menu.screen = SCREEN_NEW_GAME;
                g_menu.setup_accepted = 0;
            } else if (control->send_message[0] == 1 &&
                       control->send_message[1] == 4) {
                g_menu.screen = SCREEN_LOAD_GAME;
            } else if (control->send_message[0] == 2) {
                platform_request_close(window);
            }
        } else if (control != NULL && strcmp(control->name, "RESUME") == 0 &&
                   g_resume_available) {
            char path[MAX_PATH];
            if (!resume_path(path, sizeof(path)) || !read_save_file(window, path))
                platform_message_box(window, TRU(T_DLG_RESUME_FAILED),
                                     "Tone Rebellion remake", 1);
            else
                slide_panel_open_paused();
        }
    } else if (g_menu.screen == SCREEN_NEW_GAME && clicked_tribe >= 0) {
        /* NewGameWin's custom mouse handler resolves the animated tribe glyphs
           (messages 60..63). */
        dispatch_newgame_master_message(window, 60 + clicked_tribe);
    } else if (g_menu.screen == SCREEN_NEW_GAME &&
               (x - 320) * (x - 320) + (y - 240) * (y - 240) < 100) {
        /* The NewGameWin handler assigns this inner hit region to difficulty. */
        dispatch_newgame_master_message(window, 55);
    } else if (g_menu.screen == SCREEN_NEW_GAME &&
               (x - 320) * (x - 320) + (y - 240) * (y - 240) < 200) {
        /* The surrounding NewGameWin hit region changes world size. */
        dispatch_newgame_master_message(window, 53);
    } else if (g_menu.screen == SCREEN_NEW_GAME) {
        control = window_catalog_hit_test(&g_window_catalog, 1, x, y);
        if (control != NULL && strcmp(control->message_destination, "WINMGR") == 0 &&
            control->send_message[0] == 1 && control->send_message[1] == 0) {
            leave_new_game_screen();
        } else if (control != NULL && strcmp(control->message_destination, "MASTER") == 0) {
            dispatch_newgame_master_message(window, control->send_message[0]);
        }
    } else if (g_menu.screen == SCREEN_WORLD_MAP) {
        int clicked_island = world_island_at(x, y);
        /* FUN_00470fe7 (msg 6) enters the hovered island (+0x76, set only by
           the mouse-move hit test FUN_00470f67) when FUN_0047117d says it is
           accessible: one click, no select-then-open step. open_island_view
           applies the access check. */
        if (clicked_island >= 0) {
            g_menu.selected_map_island = clicked_island;
            (void)open_island_view(window, clicked_island);
        }
    } else if (g_menu.screen == SCREEN_ISLAND) {
        if (obtain_button_at(x, y)) {
            /* msg 0x65 case 4: FUN_0042fa0f(0x39) posts the task, then
               FUN_0042f303(0) returns to the Hall default (ev_02b58ae7). */
            (void)ISSUE_COMMAND(GAME_COMMAND_QUEUE_OBTAIN_TASK, (uint8_t)g_menu.selected_tribe,
                (uint8_t)g_menu.selected_map_island,
                (uint16_t)view_selected_location());
            select_location_on_view(-1);
            g_selected_floater = -1;
            g_island_panel_mode = WINDOW_ISLAND_PANEL_GENERAL;
            platform_invalidate(window);
            return;
        }
        if (upgspread_button_at(x, y)) {
            (void)ISSUE_COMMAND(GAME_COMMAND_TOGGLE_UPGSPREAD, (uint8_t)g_menu.selected_tribe,
                (uint8_t)selection_island(),
                (uint16_t)g_selected_location);
            platform_invalidate(window);
            return;
        }
        {
            int clip_control = clipboard_control_at(x, y);
            if (clip_control >= 1 && clip_control <= 3) {
                /* CLIPSEL msg 7001..7003: active group, repaint. */
                game_session_clip_set_group(&g_game_session,
                                            (unsigned int)clip_control - 1U);
                platform_invalidate(window);
                return;
            }
            if (clip_control >= 11 && clip_control <= 13 &&
                g_menu.selected_tribe >= 0 &&
                g_menu.selected_tribe < GAME_START_PLAYER_COUNT) {
                uint8_t clip_island = 0;
                uint16_t clip_location = 0;
                /* FUN_0042fa0f msgs 3001..3003 (0x431758..0x4317f6): an
                   empty slot does nothing; otherwise FUN_0042f303(0), then
                   +0x16c = the remembered building (any island) and
                   FUN_0042f755(building, 1) = building panel mode 3. The
                   viewed island never changes (ev_427f8632). */
                if (game_session_clip_slot(&g_game_session,
                        (uint8_t)g_menu.selected_tribe,
                        (unsigned int)clip_control - 11U, &clip_island,
                        &clip_location) != 0) {
                    select_location_anywhere((int)clip_island,
                                             (int)clip_location);
                    select_building_warrior();
                    g_island_panel_mode = WINDOW_ISLAND_PANEL_LOCATION;
                }
                platform_invalidate(window);
                return;
            }
        }
        if (g_menu.screen == SCREEN_ISLAND && g_game_session_valid &&
            island_panel_location_info_visible(g_island_panel_mode) &&
            selection_island() >= 0 &&
            selection_island() < g_game_session.island_count) {
            /* IWLocInfo slot floaters (FUN_0044003d case 6 ->
               FUN_00440451), then message 0x3f selects the floater while the
               location context is kept. */
            const GameRuntimeIsland *slot_island =
                &g_game_session.islands[selection_island()];
            const WindowTemplate *slot_info = window_catalog_find(
                &g_window_catalog, "IWLocInfo", 3);
            if (slot_info != NULL && g_selected_location >= 0 &&
                g_selected_location < slot_island->location_count &&
                x >= slot_info->pane.left && x <= slot_info->pane.right &&
                y >= slot_info->pane.top && y <= slot_info->pane.bottom) {
                int slot_floater = building_slot_floater_at(slot_info,
                    &slot_island->locations[g_selected_location], x, y);
                if (slot_floater >= 0) {
                    IslandPanelSelection selection = {
                        g_selected_location, g_selected_floater
                    };
                    island_panel_select_floater(&selection, slot_floater);
                    select_location_anywhere(selection_island(), selection.location_index);
                    g_selected_floater = slot_floater;
                    ++g_floater_select_serial;
                    g_hovered_location = -1;
                    platform_invalidate(window);
                    return;
                }
            }
        }
        {
            int training_control = training_stock_control_at(x, y);
            if (training_control != 0) {
                (void)ISSUE_COMMAND(GAME_COMMAND_TOGGLE_TRAINING_STOCK, (uint8_t)g_menu.selected_tribe,
                    (uint8_t)selection_island(),
                    (uint16_t)g_selected_location, training_control - 1);
                platform_invalidate(window);
                return;
            }
        }
        {
            int cast_action = selected_cast_action_at(x, y);
            if (cast_action >= 0) {
                press_cast_action(cast_action);
                platform_invalidate(window);
                return;
            }
        }
        {
            int order_genre = building_order_button_at(x, y);
            if (order_genre == 10) {
                /* FUN_0045dcf4: genre 9 at the building's own packed tile. */
                const GameRuntimeLocation *own = &g_game_session.islands[
                    selection_island()].locations[g_selected_location];
                (void)ISSUE_COMMAND(GAME_COMMAND_SET_BUILDING_ORDER, (uint8_t)g_menu.selected_tribe,
                    (uint8_t)selection_island(),
                    (uint16_t)g_selected_location, 9,
                    (uint8_t)selection_island(), own->x, own->y);
                g_defend_area_armed = 0;
                update_interaction_cursor();
                platform_invalidate(window);
                return;
            }
            if (order_genre != 0) {
                g_defend_area_armed =
                    g_defend_area_armed == order_genre ? 0 : order_genre;
                g_armed_spell_action = 0;
                update_interaction_cursor();
                platform_invalidate(window);
                return;
            }
        }
        if (g_armed_spell_action != 0 && x >= 0 && x < LOGICAL_WIDTH &&
            y >= 0 && y < 320) {
            int clicked_floater = game_session_floater_at(&g_game_session,
                (uint8_t)g_menu.selected_map_island,
                (uint16_t)(x + g_island_scroll_x), (uint16_t)y);
            if (island_spell_target_click(clicked_floater, x, y)) {
                platform_invalidate(window);
                return;
            }
        }
        if (g_defend_area_armed != 0 && x >= 0 && x < LOGICAL_WIDTH &&
            y >= 0 && y < 320) {
            /* FUN_0042fa0f msg 0x40 in modes 16..19: cat 1 sub 0x10..0x13
               writes the building's order record (FUN_0045d867/FUN_0045d8b2). */
            int target = -1;
            unsigned int target_y = 0;
            if (g_defend_area_armed == 9) {
                target = x + g_island_scroll_x;
                target_y = (unsigned int)y;
            } else if (g_defend_area_armed == 7) {
                target = island_location_at(x, y);
            } else {
                target = game_session_floater_at(&g_game_session,
                    (uint8_t)g_menu.selected_map_island,
                    (uint16_t)(x + g_island_scroll_x), (uint16_t)y);
            }
            if (target >= 0 && ISSUE_COMMAND(GAME_COMMAND_SET_BUILDING_ORDER, (uint8_t)g_menu.selected_tribe,
                    (uint8_t)selection_island(),
                    (uint16_t)g_selected_location,
                    (unsigned int)g_defend_area_armed,
                    (uint8_t)g_menu.selected_map_island,
                    (unsigned int)target, target_y)) {
                g_defend_area_armed = 0;
                update_interaction_cursor();
            }
            platform_invalidate(window);
            return;
        }
        if (g_game_session.location_move_active && x >= 0 &&
            x < LOGICAL_WIDTH && y >= 0 && y < 320) {
            int target_location = island_location_at(x, y);
            if (target_location >= 0 && ISSUE_COMMAND(GAME_COMMAND_FINISH_LOCATION_MOVE, (uint8_t)g_menu.selected_tribe,
                    (uint8_t)g_menu.selected_map_island,
                    (uint16_t)target_location)) {
                select_location_on_view(target_location);
                g_selected_floater = -1;
                g_hovered_location = target_location;
            }
            platform_invalidate(window);
            return;
        }
        if (g_island_panel_mode == WINDOW_ISLAND_PANEL_INVENTORY) {
            const WindowTemplate *inventory_panel = window_catalog_find(
                &g_window_catalog, "IWInventory", 3);
            if (inventory_panel != NULL &&
                x >= inventory_panel->pane.left &&
                x <= inventory_panel->pane.right &&
                y >= inventory_panel->pane.top + 24 &&
                y <= inventory_panel->pane.bottom) {
                int clicked_item = inventory_item_at(x, y);
                g_selected_inventory_item = game_inventory_click_selection(
                    g_selected_inventory_item, clicked_item);
                update_interaction_cursor();
                platform_invalidate(window);
                return;
            }
        }
        if (g_island_panel_mode == WINDOW_ISLAND_PANEL_TASKS) {
            static const char *const task_option_names[] = {
                "TaskNorm", "TaskHigh", "TaskExcl", "TaskKill"
            };
            static const char *const task_scroll_names[] = {
                "scrollup", "scrolldn"
            };
            const WindowTemplate *task_option =
                g_selected_task_slot >= 0
                ? window_catalog_hit_test_names(&g_window_catalog, 3, x, y,
                    task_option_names,
                    sizeof(task_option_names) / sizeof(task_option_names[0]))
                : NULL;
            if (task_option != NULL) {
                if (g_game_session_valid &&
                    g_selected_task_slot < GAME_SESSION_MAX_PENDING_EVENTS) {
                    const uint8_t slot = (uint8_t)g_selected_task_slot;
                    const GamePendingEvent expected =
                        g_game_session.pending_events[slot];
                    const uint8_t subtype = task_option->send_message[0] == 4003
                        ? 12 : (uint8_t)(12 + task_option->send_message[1]);
                    if (ISSUE_COMMAND(GAME_COMMAND_DISPATCH_TASK_COMMAND,
                            slot, subtype, (int32_t)expected.active,
                            expected.assigned_floater_count, expected.priority,
                            expected.player_id, expected.payload_0a,
                            expected.payload_0c, expected.payload_0e,
                            expected.action_type, expected.payload_12)) {
                        if (subtype == 12) g_selected_task_slot = -1;
                        platform_invalidate(window);
                    }
                }
                /* Keep configured task controls modal even if the selected
                   record became stale before dispatch. */
                return;
            }
            const WindowTemplate *scroll_control = window_catalog_hit_test_names(
                &g_window_catalog, 3, x, y, task_scroll_names,
                sizeof(task_scroll_names) / sizeof(task_scroll_names[0]));
            if (scroll_control != NULL) {
                const WindowTemplate *task_panel = window_catalog_find(
                    &g_window_catalog, "IWTasks", 3);
                uint8_t task_slots[GAME_SESSION_MAX_TASKS];
                int hall_player = island_panel_player_for_mode(
                    WINDOW_ISLAND_PANEL_TASKS,
                    g_game_session_valid
                        ? (int)g_game_session.config.selected_tribe : -1,
                    selected_hall_player());
                size_t task_count = g_game_session_valid && hall_player >= 0
                    ? game_session_collect_task_slots(&g_game_session,
                        (int16_t)hall_player, task_slots,
                        sizeof(task_slots) / sizeof(task_slots[0])) : 0;
                int visible_rows = task_panel != NULL
                    ? (task_panel->pane.bottom - task_panel->pane.top) / 13 : 0;
                int direction = window_catalog_scroll_direction(
                    scroll_control->name, WINDOW_ISLAND_PANEL_TASKS);
                /* The source consumes 6000/6001 even at either bound. */
                g_task_scroll_offset = window_catalog_scroll_step(
                    g_task_scroll_offset, (int)task_count, visible_rows,
                    direction);
                platform_invalidate(window);
                return;
            }
            {
                const WindowTemplate *task_panel = window_catalog_find(
                    &g_window_catalog, "IWTasks", 3);
                if (task_panel != NULL &&
                    x > task_panel->pane.left &&
                    x < task_panel->pane.right - 13 &&
                    y > task_panel->pane.top &&
                    y < task_panel->pane.bottom) {
                    uint8_t task_slots[GAME_SESSION_MAX_TASKS];
                    int hall_player = island_panel_player_for_mode(
                        WINDOW_ISLAND_PANEL_TASKS,
                        g_game_session_valid
                            ? (int)g_game_session.config.selected_tribe : -1,
                        selected_hall_player());
                    size_t task_count = g_game_session_valid && hall_player >= 0
                        ? game_session_collect_task_slots(&g_game_session,
                            (int16_t)hall_player, task_slots,
                            sizeof(task_slots) / sizeof(task_slots[0])) : 0;
                    int visible_rows =
                        (task_panel->pane.bottom - task_panel->pane.top) / 13;
                    int task_index = island_panel_info_task_index_at_y(
                        task_panel, y, (unsigned int)visible_rows,
                        g_task_scroll_offset, task_count);
                    if (task_index >= 0) {
                        g_selected_task_slot = task_slots[task_index];
                    }
                    platform_invalidate(window);
                    return;
                }
            }
        }
        if (g_island_panel_mode == WINDOW_ISLAND_PANEL_GLYPHS) {
            const WindowTemplate *glyph_panel = window_catalog_find(
                &g_window_catalog, "IWGlyphs", 3);
            if (glyph_panel != NULL && x >= glyph_panel->pane.left &&
                x <= glyph_panel->pane.right && y >= glyph_panel->pane.top &&
                y <= glyph_panel->pane.bottom) {
                (void)update_glyph_hover(x, y);
                (void)game_glyph_inventory_click_selection(&g_selected_glyph,
                    g_hovered_glyph, 1);
                /* IWGlyphs sends message 0x43 with its owned, hovered ID.
                   The source then arms interaction mode 0x11. The later
                   map-command guards/effect are not modelled here. */
                update_interaction_cursor();
                /* FUN_0043dcae consumes an in-pane click even when
                   FUN_0043dd9d has no hovered ID to send. */
                platform_invalidate(window);
                return;
            }
        }
        if (g_island_panel_mode == WINDOW_ISLAND_PANEL_GENERAL &&
            g_game_session_valid && selection_island() >= 0 &&
            selection_island() < g_game_session.island_count &&
            g_selected_location >= 0 &&
            g_selected_location < g_game_session.islands[
                selection_island()].location_count) {
            static const char *const onoff_names[] = {"BC_OnOff"};
            const WindowTemplate *onoff_control =
                selected_onoff_button_visible()
                    ? window_catalog_hit_test_names(&g_window_catalog, 3, x, y,
                        onoff_names, sizeof(onoff_names) / sizeof(onoff_names[0]))
                    : NULL;
            if (onoff_control != NULL) {
                /* Message 101/index 0 reaches type-1/subtype-0; the island
                   tick applies the observed bit-0x400 toggle and budget gate. */
                (void)ISSUE_COMMAND(GAME_COMMAND_QUEUE_ONOFF_ACTION, (uint8_t)g_menu.selected_tribe,
                    (uint8_t)selection_island(),
                    (uint16_t)g_selected_location);
                platform_invalidate(window);
                return;
            }
            static const char *const upgrade_names[] = {"BC_Upgrade"};
            const WindowTemplate *upgrade_control = selected_upgrade_button_visible()
                ? window_catalog_hit_test_names(&g_window_catalog, 3, x, y,
                    upgrade_names,
                    sizeof(upgrade_names) / sizeof(upgrade_names[0])) : NULL;
            if (upgrade_control != NULL) {
                /* The button only shows on a site FUN_0045c89b accepts
                   (staff kinds 0x2c..0x2f), so a click toggles the +0x4e
                   request (FUN_0045c9b5 / FUN_0045ca1e). */
                (void)ISSUE_COMMAND(GAME_COMMAND_TOGGLE_STAFF_UPGRADE, (uint8_t)g_menu.selected_tribe,
                    (uint8_t)selection_island(),
                    (uint16_t)g_selected_location);
                platform_invalidate(window);
                return;
            }
            static const char *const repair_names[] = {"BC_Repair"};
            const WindowTemplate *repair_control = selected_repair_button_visible()
                ? window_catalog_hit_test_names(&g_window_catalog, 3, x, y,
                    repair_names,
                    sizeof(repair_names) / sizeof(repair_names[0])) : NULL;
            if (repair_control != NULL) {
                /* BC_Repair sends cat 1 code 3 (FUN_0042fa0f 0x65 with
                   table index 3): FUN_00465793 toggles the repair entry. */
                (void)ISSUE_COMMAND(GAME_COMMAND_TOGGLE_REPAIR,
                    (int16_t)g_menu.selected_tribe,
                    (int16_t)selection_island(), (int16_t)g_selected_location);
                return;
            }
        }
        {
            IslandLocationActionControl action = selected_location_action();
            const char *action_name = action == ISLAND_LOCATION_ACTION_HALL_MOVE
                ? "IWHallMove" : action == ISLAND_LOCATION_ACTION_MOVE
                ? "IWMove" : NULL;
            if (action_name != NULL) {
                static const char *const action_names[] = {"IWMove", "IWHallMove"};
                const WindowTemplate *action_control =
                    window_catalog_hit_test_names(&g_window_catalog, 3, x, y,
                                                   action_names, 2);
                if (action_control != NULL &&
                    strcmp(action_control->name, action_name) == 0) {
                    /* The native IWMove / IWHallMove control starts (or, while a
                       building is held, cancels) the grab/place flow; the
                       packet behind it is not resolved, so the port uses its
                       own move model. The hit never falls through to the
                       location deselect. */
                    if (g_game_session.location_move_active) {
                        (void)issue_command(GAME_COMMAND_CANCEL_LOCATION_MOVE, 0, NULL);
                    } else if (selected_location_can_be_grabbed()) {
                        (void)ISSUE_COMMAND(GAME_COMMAND_BEGIN_LOCATION_MOVE, (uint8_t)g_menu.selected_tribe,
                            (uint8_t)selection_island(),
                            (uint16_t)g_selected_location);
                    }
                    platform_invalidate(window);
                    return;
                }
            }
        }
        if (adjust_trade_cell(x, y, 1)) {
            platform_invalidate(window);
            return;
        }
        const WindowTemplate *construct = window_catalog_find(
            &g_window_catalog, "IWConstruct", 3);
        const WindowTemplate *cycle = window_catalog_find(&g_window_catalog,
                                                           "BuildCycle", 3);
        IwConstructClickTarget click_target = iw_construct_click_target(
            g_iw_construct_open,
            construct != NULL ? &construct->pane : NULL,
            cycle != NULL && g_iw_construct.cycle_button_visible
                ? &cycle->pane : NULL,
            x, y);
        if (click_target == IW_CONSTRUCT_CLICK_CYCLE) {
            IwConstructTransition transition;
            iw_construct_build_cycle(&g_iw_construct, g_iw_construct_item_count,
                                     &transition);
            (void)apply_iw_construct_messages(&transition);
            (void)update_iw_construct_hover(x, y);
        } else if (click_target == IW_CONSTRUCT_CLICK_GRID) {
            (void)update_iw_construct_hover(x, y);
            if (select_iw_construct_item()) {
                platform_invalidate(window);
            }
        } else {
            /* IWConstruct overlaps the Hall's stock buttons in ISLETMP. Keep
               clicks modal only inside its panes; an outside click dismisses
               it and continues through the normal island/Hall hit routing.
               Without this, clicking the Hall location is swallowed and the
               Hall panel can never become selected after opening the grid. */
            if (g_iw_construct_open) {
                g_iw_construct_open = 0;
                g_iw_construct.hovered_column = -1;
                (void)iw_construct_info_handle_message(
                    &g_iw_construct_info, 1, 0);
            }
            static const char *const island_button_names[] = {
                "GOTOMAP", "PANIC", "TOGREALM", "TASKLIST"
            };
            static const char *const hall_command_names[] = {
                "BC_GenInfo", "BC_Storage", "BC_Knowledge", "BC_Trade", "BC_Diplomacy"
            };
            const WindowTemplate *island_control = window_catalog_hit_test_names(
                &g_window_catalog, 3, x, y, island_button_names,
                sizeof(island_button_names) / sizeof(island_button_names[0]));
            int hall_player = selected_hall_player();
            const WindowTemplate *hall_control = hall_player >= 0 &&
                island_panel_location_control_visible(g_island_panel_mode)
                ? window_catalog_hit_test_names(&g_window_catalog, 3, x, y,
                    hall_command_names,
                    sizeof(hall_command_names) / sizeof(hall_command_names[0]))
                : NULL;
            static const char *const inventory_controls[] = {"InvCycle"};
            static const char *const trade_controls[] = {"TradeZERO", "TradeDOIT"};
            const WindowTemplate *inventory_cycle =
                hall_player >= 0 &&
                g_island_panel_mode == WINDOW_ISLAND_PANEL_INVENTORY
                ? window_catalog_hit_test_names(&g_window_catalog, 3, x, y,
                    inventory_controls, 1) : NULL;
            const WindowTemplate *trade_control =
                hall_player >= 0 &&
                g_island_panel_mode == WINDOW_ISLAND_PANEL_TRADE
                ? window_catalog_hit_test_names(&g_window_catalog, 3, x, y,
                    trade_controls, 2) : NULL;
            int button_index = island_control != NULL
                ? island_button_index(island_control->name) : -1;
            int stock_control = hall_player >= 0 &&
                island_panel_location_control_visible(g_island_panel_mode)
                ? hall_stock_control_at(x, y) : -1;
            int hall_panel_mode = hall_control != NULL
                ? window_catalog_hall_panel_mode(hall_control->name)
                : WINDOW_ISLAND_PANEL_NONE;
            if (click_diplomacy_action(x, y, hall_player)) {
                /* FUN_0043e296 sends subtype 10 from the active local Hall. */
            } else if (trade_control != NULL) {
                if (strcmp(trade_control->name, "TradeZERO") == 0) {
                    (void)ISSUE_COMMAND(GAME_COMMAND_CLEAR_TRADE_OFFERS, (uint8_t)hall_player);
                } else {
                    /* FUN_0042fa0f(4011) queues type-0xb messages for each
                       recipient with a nonzero row, then clears the table.
                       The local tick applies those transfers through the
                       observed FUN_00465793 receiver path. */
                    (void)ISSUE_COMMAND(GAME_COMMAND_COMMIT_TRADE_OFFERS, (uint8_t)hall_player);
                }
            } else if (button_index >= 0) {
                if (button_index == WINDOW_ISLAND_BUTTON_MAP) {
                    if (g_game_session.location_move_active) {
                        (void)issue_command(GAME_COMMAND_CANCEL_LOCATION_MOVE, 0, NULL);
                    }
                    g_menu.screen = SCREEN_WORLD_MAP;
                    g_selected_floater = -1;
                    select_location_on_view(-1);
                    g_hovered_location = -1;
                    g_hovered_island_button = -1;
                    g_hovered_hall_command = -1;
                    g_hovered_inventory_item = -1;
                    g_selected_inventory_item = -1;
                    update_window_title(window);
                } else if (button_index == WINDOW_ISLAND_BUTTON_TASKS) {
                    g_island_panel_mode =
                        g_island_panel_mode == WINDOW_ISLAND_PANEL_TASKS
                        ? WINDOW_ISLAND_PANEL_GENERAL : WINDOW_ISLAND_PANEL_TASKS;
                    g_task_scroll_offset = 0;
                } else if (button_index == WINDOW_ISLAND_BUTTON_REALM) {
                    /* FUN_0042fa0f assigns each source global (flag == 0),
                       independently normalizing and flipping all three. */
                    g_floater_overlay_flags =
                        island_toggle_realm_overlay_flags(g_floater_overlay_flags);
                } else if (button_index == WINDOW_ISLAND_BUTTON_PANIC) {
                    /* 2002 -> FUN_0042fa0f(0x3b) -> type 3/subtype 0.
                       FUN_00465793 toggles bit 0 in this player's raw island
                       word; what consumes or displays that bit is unknown. */
                    if (g_game_session_valid &&
                        g_menu.selected_tribe < GAME_START_PLAYER_COUNT &&
                        g_menu.selected_map_island >= 0 &&
                        g_menu.selected_map_island < g_game_session.island_count) {
                        (void)ISSUE_COMMAND(GAME_COMMAND_QUEUE_ISLAND_EVENT3, g_menu.selected_tribe,
                            (uint8_t)g_menu.selected_map_island);
                    }
                }
            } else if (g_island_panel_mode == WINDOW_ISLAND_PANEL_TASKS ||
                       g_island_panel_mode == WINDOW_ISLAND_PANEL_EFFECT_DEBUG) {
                /* FUN_0042f303 hides IWLocInfo/IWLocControl in these states;
                   consume clicks outside the visible task/effect panels. The
                   island view itself (y < 320) keeps receiving clicks: a
                   constructed bridge still switches island, then
                   re-selects the kept location in the building panel (mode
                   3, FUN_0042f755(rec, 1)); any other pick returns
                   to mode 0 (FUN_0042f8f7 / FUN_0042f303(0)) and is handled
                   as a normal click. */
                if (y < 320 && x >= 0 && x < LOGICAL_WIDTH) {
                    int over_floater = game_session_floater_at(&g_game_session,
                        (uint8_t)g_menu.selected_map_island,
                        (uint16_t)(x + g_island_scroll_x), (uint16_t)y);
                    int over_location = island_location_at(x, y);
                    if (over_floater < 0 && over_location >= 0 &&
                        enter_bridge_destination(window, over_location)) {
                        platform_invalidate(window);
                        return;
                    }
                    g_island_panel_mode = WINDOW_ISLAND_PANEL_GENERAL;
                    handle_click(window, x, y);
                    return;
                }
                platform_invalidate(window);
                return;
            } else if (hall_panel_mode != WINDOW_ISLAND_PANEL_NONE) {
                g_iw_construct_open = 0;
                g_island_panel_mode = hall_panel_mode;
                g_hovered_hall_command = hall_panel_mode;
                g_diplomacy_hover_valid = 0;
                g_hovered_glyph = -1;
                g_glyph_info_default =
                    hall_panel_mode == WINDOW_ISLAND_PANEL_GLYPHS;
                if (hall_panel_mode == WINDOW_ISLAND_PANEL_TRADE &&
                    selected_hall_player() >= 0) {
                    /* FUN_0043eab5 message 1 zeroes the nine offers on open. */
                    (void)ISSUE_COMMAND(GAME_COMMAND_CLEAR_TRADE_OFFERS, (uint8_t)selected_hall_player());
                }
                if (hall_panel_mode == WINDOW_ISLAND_PANEL_INVENTORY) {
                    g_inventory_page = 0;
                    g_hovered_inventory_item = -1;
                    g_selected_inventory_item = -1;
                    g_inventory_info_mode = ISLAND_PANEL_INFO_INVENTORY_DEFAULT;
                } else {
                    g_selected_inventory_item = -1;
                }
            } else if (inventory_cycle != NULL &&
                game_inventory_collect(
                    g_game_session.economy[(unsigned int)hall_player].inventory_count,
                    NULL, 0) > GAME_INVENTORY_PAGE_SIZE) {
                g_inventory_page = game_inventory_next_page(g_inventory_page,
                    game_inventory_collect(
                        g_game_session.economy[(unsigned int)hall_player].inventory_count,
                        NULL, 0));
                g_hovered_inventory_item = -1;
            } else if (stock_control >= 0) {
                (void)ISSUE_COMMAND(GAME_COMMAND_CYCLE_RESOURCE_STOCK, (uint8_t)hall_player,
                    (GameResourceType)stock_control);
            } else {
                /* FUN_00435581 has no explored-cell gate on the floater pass. */
                int clicked_floater = g_game_session_valid
                    ? game_session_floater_at(&g_game_session,
                        (uint8_t)g_menu.selected_map_island,
                        (uint16_t)(x + g_island_scroll_x), (uint16_t)y)
                    : -1;
                if (clicked_floater >= 0) {
                    IslandPanelSelection selection = {
                        g_selected_location, g_selected_floater
                    };
                    island_panel_select_floater(&selection, clicked_floater);
                    select_location_anywhere(selection_island(), selection.location_index);
                    g_selected_floater = clicked_floater;
                    ++g_floater_select_serial;
                    select_floater_source_building(clicked_floater);
                    g_hovered_location = -1;
                    platform_invalidate(window);
                } else {
                    int clicked_location = island_location_at(x, y);
                    int clicked_ground_item = 0;
                    if (clicked_location >= 0 && g_selected_glyph < 0 &&
                        g_selected_inventory_item < GAME_INVENTORY_ITEM_FIRST_ID) {
                        const GameRuntimeLocation *location =
                            &g_game_session.islands[g_menu.selected_map_island]
                                .locations[clicked_location];
                        int32_t item_id = location->record_value_10 == 1
                            ? location->record_value_24 : 0;
                        clicked_ground_item = location->renderer_class == 0 &&
                            location->owner_id == -1 &&
                            item_id >= GAME_INVENTORY_ITEM_FIRST_ID &&
                            item_id < GAME_INVENTORY_ITEM_FIRST_ID +
                                GAME_INVENTORY_ITEM_COUNT;
                    }
                    if (clicked_ground_item) {
                        /* Keep the map target selected and the worker active;
                           the Obtain button posts the type-0xd task. */
                        select_location_on_view(clicked_location);
                        g_hovered_location = -1;
                    } else {
                        g_selected_floater = -1;
                    }
                    if (clicked_location >= 0 && !clicked_ground_item) {
                        if (g_selected_glyph >= 0 &&
                            g_selected_glyph < GAME_GLYPH_COUNT &&
                            g_game_session_valid &&
                            g_menu.selected_tribe < GAME_START_PLAYER_COUNT) {
                            /* FUN_0042fa0f(0x40) emits category-3/type-3
                               with the clicked island/location and selected
                               glyph. The receiver's raw record filter (+0
                               player, +4 == 8) and runtime order are not modelled. */
                            (void)ISSUE_COMMAND(GAME_COMMAND_QUEUE_GLYPH_ACTION, g_menu.selected_tribe,
                                (uint8_t)g_menu.selected_map_island,
                                (uint16_t)clicked_location,
                                (uint8_t)g_selected_glyph);
                            g_selected_glyph = -1;
                            g_glyph_info_default = 1;
                            update_interaction_cursor();
                        } else if (g_selected_inventory_item >=
                                GAME_INVENTORY_ITEM_FIRST_ID &&
                            g_selected_inventory_item <
                                GAME_INVENTORY_ITEM_FIRST_ID +
                                GAME_INVENTORY_ITEM_COUNT &&
                            g_menu.selected_tribe < GAME_START_PLAYER_COUNT) {
                            int target_location = clicked_location;
                            /* easyunlock (FUN_0042fa0f at 0x430dc1): a pair
                               item 6 + 2 * island id + side placed on its own
                               island is redirected next to the clicked site:
                               the island's centre feature site (kind 4) goes
                               to site + 1, a pair site (class 3) holding the
                               other side goes to site - 1 (side 0) or
                               site + 1 (side 1). */
                            if (float_cfg_easyunlock()) {
                                const GameRuntimeIsland *unlock_island =
                                    &g_game_session.islands[
                                        g_menu.selected_map_island];
                                int pair_code = g_selected_inventory_item - 6;
                                int pair_side = pair_code & 1;
                                const GameRuntimeLocation *clicked_site =
                                    &unlock_island->locations[clicked_location];
                                if ((pair_code >> 1) ==
                                        unlock_island->leviathan_marker_shape_id) {
                                    /* FUN_0042fa0f case 0x40: the second test runs
                                       on the site after the +1 shift, so both
                                       rules can apply (net +2 or 0). */
                                    const GameRuntimeLocation *test_site =
                                        clicked_site;
                                    if (clicked_site->record_value_10 == 4) {
                                        target_location = clicked_location + 1;
                                        test_site = target_location <
                                                (int)unlock_island->location_count
                                            ? &unlock_island->locations[
                                                  target_location]
                                            : NULL;
                                    }
                                    if (test_site != NULL &&
                                        test_site->renderer_class == 3 &&
                                        test_site->source_capacity_4a !=
                                            pair_side) {
                                        target_location += pair_side == 0 ? -1 : 1;
                                    }
                                    if (target_location < 0 ||
                                        target_location >=
                                            (int)unlock_island->location_count)
                                        target_location = clicked_location;
                                }
                            }
                            (void)ISSUE_COMMAND(GAME_COMMAND_QUEUE_INVENTORY_ACTION, g_menu.selected_tribe,
                                (uint8_t)g_menu.selected_map_island,
                                (uint16_t)target_location,
                                (uint8_t)g_selected_inventory_item);
                            /* FUN_0042fa0f clears the selection and returns
                               to general mode even if the location guard
                               prevented the request from being queued. */
                            island_panel_finish_inventory_target(
                                &g_island_panel_mode,
                                &g_selected_inventory_item,
                                &g_hovered_inventory_item,
                                &g_hovered_hall_command);
                            update_interaction_cursor();
                        } else if (enter_bridge_destination(window,
                                                            clicked_location)) {
                            /* island changed; selection kept (mode 3) */
                        } else if (open_construction_task(clicked_location)) {
                            /* Remake addition: pending build site opens its
                               task in the Tasks view. */
                        } else {
                            select_location_on_view(clicked_location);
                            select_building_warrior();
                            (void)open_iw_construct(clicked_location);
                        }
                        platform_invalidate(window);
                    } else if (clicked_location < 0) {
                        /* FUN_00435826 empty ground: msg 0x33 clears +0x16c and
                           +0x170, then FUN_0042f303(0) shows the player's Hall
                           (on any island) in mode 0 (ev_52232fe9, ev_379f1f88);
                           hall_default_selected() is that default. */
                        select_location_on_view(-1);
                        if (g_selected_glyph < 0 &&
                            g_selected_inventory_item <
                                GAME_INVENTORY_ITEM_FIRST_ID) {
                            g_island_panel_mode = WINDOW_ISLAND_PANEL_GENERAL;
                            g_hovered_hall_command = -1;
                        }
                        platform_invalidate(window);
                    }
                }
            }
        }
    } else if (g_menu.screen == SCREEN_LOAD_GAME) {
        /* FUN_00458162 (msg 6): y < 35 goes back; otherwise slot =
           (y - 28) / 112 + 4 * (x / 320). Save mode (DAT_0062d172 != 4)
           writes the slot, Load mode restores a valid one, then the screen
           closes. */
        if (y >= 35) {
            int slot = (y - 28) / 112 + (x / 320) * 4;
            char path[MAX_PATH];
            if (slot >= 0 && slot < 8 && g_load_save_mode) {
                if (save_slot_path(slot, path, sizeof(path)) &&
                    write_save_file(path)) {
                    scan_load_slots();
                    leave_load_screen();
                } else {
                    platform_message_box(window, TRU(T_DLG_SAVE_FAILED),
                                         "Tone Rebellion remake", 1);
                }
            } else if (slot >= 0 && slot < 8 && g_load_slot_valid[slot] &&
                       g_net_load_pick) {
                /* Network lobby: the host's pick goes to every guest. */
                if (g_load_slot_native[slot])
                    (void)net_host_pick_save(g_load_slot_native_path[slot], 1);
                else if (save_slot_path(slot, path, sizeof(path)))
                    (void)net_host_pick_save(path, 0);
                leave_load_screen();
            } else if (slot >= 0 && slot < 8 && g_load_slot_valid[slot] &&
                       g_load_slot_native[slot]) {
                char error[160];
                /* The scan's path: a manifested or 64-bit process is not
                   redirected to the VirtualStore copy. */
                if (read_native_save_file(window, g_load_slot_native_path[slot],
                                          error, sizeof(error))) {
                    g_load_save_mode = 0;
                    g_load_from_game = 0;
                    slide_panel_open_paused();
                } else {
                    char message[256];
                    (void)snprintf(message, sizeof(message),
                                   TRU(T_DLG_ORIGINAL_SAVE_FAILED),
                                   error);
                    platform_message_box(window, message, "Tone Rebellion remake",
                                         1);
                }
            } else if (slot >= 0 && slot < 8 && g_load_slot_valid[slot]) {
                if (save_slot_path(slot, path, sizeof(path)) &&
                    read_save_file(window, path)) {
                    g_load_save_mode = 0;
                    g_load_from_game = 0;
                    slide_panel_open_paused();
                } else {
                    platform_message_box(window, TRU(T_DLG_LOAD_FAILED),
                                         "Tone Rebellion remake", 1);
                }
            } else {
                leave_load_screen();
            }
        } else {
            leave_load_screen();
        }
    }
    (void)update_hover_help(x, y);
    (void)update_newgame_text(x, y);
    (void)update_hall_stock_hover(x, y);
    (void)update_island_button_hover(x, y);
    (void)update_hall_command_hover(x, y);
    update_window_title(window);
    platform_invalidate(window);
}

