static void dispatch_newgame_master_message(HWND window, int message)
{
    if (message == 52) {
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
    if (g_menu.screen == SCREEN_MAIN_MENU) {
        control = window_catalog_hit_test(&g_window_catalog, 0, x, y);
        if (control != NULL && strcmp(control->message_destination, "WINMGR") == 0) {
            if (control->send_message[0] == 5) {
                g_menu.screen = SCREEN_NEW_GAME;
                g_menu.setup_accepted = 0;
            } else if (control->send_message[0] == 1 &&
                       control->send_message[1] == 4) {
                g_menu.screen = SCREEN_LOAD_GAME;
            } else if (control->send_message[0] == 2) {
                PostMessageA(window, WM_CLOSE, 0, 0);
            }
        } else if (control != NULL && strcmp(control->name, "RESUME") == 0 &&
                   g_resume_available) {
            MessageBoxA(window, "La reprise d'une sauvegarde n'est pas encore prise en charge.",
                        "Tone Rebellion remake", MB_OK | MB_ICONINFORMATION);
        }
    } else if (g_menu.screen == SCREEN_NEW_GAME && clicked_tribe >= 0) {
        /* NewGameWin's custom mouse handler resolves the animated tribe glyphs. */
        g_menu.selected_tribe = clicked_tribe;
        g_menu.setup_accepted = 0;
    } else if (g_menu.screen == SCREEN_NEW_GAME &&
               (x - 320) * (x - 320) + (y - 240) * (y - 240) < 100) {
        /* The NewGameWin handler assigns this inner hit region to difficulty. */
        g_menu.difficulty = (g_menu.difficulty + 1) % g_difficulty_count;
        g_menu.setup_accepted = 0;
    } else if (g_menu.screen == SCREEN_NEW_GAME &&
               (x - 320) * (x - 320) + (y - 240) * (y - 240) < 200) {
        /* The surrounding NewGameWin hit region changes world size. */
        g_menu.world_index = (g_menu.world_index + 1) % g_menu.world_map.world_count;
        g_menu.setup_accepted = 0;
    } else if (g_menu.screen == SCREEN_NEW_GAME) {
        control = window_catalog_hit_test(&g_window_catalog, 1, x, y);
        if (control != NULL && strcmp(control->message_destination, "WINMGR") == 0 &&
            control->send_message[0] == 1 && control->send_message[1] == 0) {
            g_menu.screen = SCREEN_MAIN_MENU;
            g_menu.setup_accepted = 0;
        } else if (control != NULL && strcmp(control->message_destination, "MASTER") == 0) {
            dispatch_newgame_master_message(window, control->send_message[0]);
        }
    } else if (g_menu.screen == SCREEN_WORLD_MAP) {
        int clicked_island = world_island_at(x, y);
        if (clicked_island >= 0) {
            if (clicked_island == g_menu.selected_map_island) {
                (void)open_island_view(window, clicked_island);
            } else {
                g_menu.selected_map_island = clicked_island;
            }
        }
    } else if (g_menu.screen == SCREEN_ISLAND) {
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
                InvalidateRect(window, NULL, FALSE);
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
                    if (game_session_dispatch_task_command(&g_game_session,
                            slot, subtype, &expected)) {
                        if (subtype == 12) g_selected_task_slot = -1;
                        InvalidateRect(window, NULL, FALSE);
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
                InvalidateRect(window, NULL, FALSE);
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
                    InvalidateRect(window, NULL, FALSE);
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
                InvalidateRect(window, NULL, FALSE);
                return;
            }
        }
        if (g_island_panel_mode == WINDOW_ISLAND_PANEL_GENERAL &&
            g_game_session_valid && g_menu.selected_map_island >= 0 &&
            g_menu.selected_map_island < g_game_session.island_count &&
            g_selected_location >= 0 &&
            g_selected_location < g_game_session.islands[
                g_menu.selected_map_island].location_count) {
            static const char *const onoff_names[] = {"BC_OnOff"};
            const WindowTemplate *onoff_control =
                selected_onoff_button_visible()
                    ? window_catalog_hit_test_names(&g_window_catalog, 3, x, y,
                        onoff_names, sizeof(onoff_names) / sizeof(onoff_names[0]))
                    : NULL;
            if (onoff_control != NULL) {
                /* Message 101/index 0 reaches type-1/subtype-0. Preserve the
                   request, but leave its unknown flow guard/effect untouched. */
                (void)game_session_queue_onoff_action(&g_game_session,
                    (uint8_t)g_menu.selected_tribe,
                    (uint8_t)g_menu.selected_map_island,
                    (uint16_t)g_selected_location);
                InvalidateRect(window, NULL, FALSE);
                return;
            }
            static const char *const repair_names[] = {"BC_Repair"};
            const WindowTemplate *repair_control = selected_repair_button_visible()
                ? window_catalog_hit_test_names(&g_window_catalog, 3, x, y,
                    repair_names,
                    sizeof(repair_names) / sizeof(repair_names[0])) : NULL;
            if (repair_control != NULL) {
                /* BC_Repair sends message 101 to MASTER, but its downstream
                   repair effect is unresolved. Consume the button hit. */
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
                    /* The source action handler is not resolved. Consume this
                       control hit so it cannot fall through to location deselect. */
                    return;
                }
            }
        }
        if (adjust_trade_cell(x, y, 1)) {
            InvalidateRect(window, NULL, FALSE);
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
                InvalidateRect(window, NULL, FALSE);
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
            const WindowTemplate *hall_control = hall_player >= 0
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
            int stock_control = hall_player >= 0 ? hall_stock_control_at(x, y) : -1;
            int clicked_roster_floater = hall_player >= 0
                ? selected_hall_roster_hit_test(x, y) : -1;
            int hall_panel_mode = hall_control != NULL
                ? window_catalog_hall_panel_mode(hall_control->name)
                : WINDOW_ISLAND_PANEL_NONE;
            if (click_diplomacy_action(x, y, hall_player)) {
                /* FUN_0043e296 sends subtype 10 from the active local Hall. */
            } else if (trade_control != NULL) {
                if (strcmp(trade_control->name, "TradeZERO") == 0) {
                    (void)game_session_clear_trade_offers(
                        &g_game_session, (uint8_t)hall_player);
                } else {
                    /* FUN_0042fa0f(4011) queues type-0xb messages for each
                       recipient with a nonzero row, then clears the table.
                       The local tick applies those transfers through the
                       observed FUN_00465793 receiver path. */
                    (void)game_session_commit_trade_offers(
                        &g_game_session, (uint8_t)hall_player);
                }
            } else if (button_index >= 0) {
                if (button_index == WINDOW_ISLAND_BUTTON_MAP) {
                    g_menu.screen = SCREEN_WORLD_MAP;
                    g_selected_floater = -1;
                    g_selected_location = -1;
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
                        (void)game_session_queue_island_event3_subtype0(
                            &g_game_session, g_menu.selected_tribe,
                            (uint8_t)g_menu.selected_map_island);
                    }
                }
            } else if (hall_panel_mode != WINDOW_ISLAND_PANEL_NONE) {
                g_iw_construct_open = 0;
                g_island_panel_mode = hall_panel_mode;
                g_hovered_hall_command = hall_panel_mode;
                g_diplomacy_hover_valid = 0;
                g_hovered_glyph = -1;
                g_glyph_info_default =
                    hall_panel_mode == WINDOW_ISLAND_PANEL_GLYPHS;
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
                (void)game_session_cycle_resource_stock_mode(
                    &g_game_session, (uint8_t)hall_player,
                    (GameResourceType)stock_control);
            } else if (clicked_roster_floater >= 0) {
                IslandPanelSelection selection = {
                    g_selected_location, g_selected_floater
                };
                /* FUN_0042fa0f's 0x3f branch changes the floater selection
                   while retaining the selected IWLocInfo location context. */
                island_panel_select_floater(&selection,
                                             clicked_roster_floater);
                g_selected_location = selection.location_index;
                g_selected_floater = clicked_roster_floater;
                g_hovered_location = -1;
            } else {
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
                    g_selected_location = selection.location_index;
                    g_selected_floater = clicked_floater;
                    g_hovered_location = -1;
                    InvalidateRect(window, NULL, FALSE);
                } else {
                    int clicked_location = island_location_at(x, y);
                    g_selected_floater = -1;
                    if (clicked_location >= 0) {
                        if (g_selected_glyph >= 0 &&
                            g_selected_glyph < GAME_GLYPH_COUNT &&
                            g_game_session_valid &&
                            g_menu.selected_tribe < GAME_START_PLAYER_COUNT) {
                            /* FUN_0042fa0f(0x40) emits category-3/type-3
                               with the clicked island/location and selected
                               glyph. The receiver's raw record filter (+0
                               player, +4 == 8) and runtime order are not modelled. */
                            (void)game_session_queue_glyph_action(
                                &g_game_session, g_menu.selected_tribe,
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
                            (void)game_session_queue_inventory_action(
                                &g_game_session, g_menu.selected_tribe,
                                (uint8_t)g_menu.selected_map_island,
                                (uint16_t)clicked_location,
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
                        } else {
                            g_selected_location = clicked_location;
                            (void)open_iw_construct(clicked_location);
                        }
                        InvalidateRect(window, NULL, FALSE);
                    } else {
                        g_selected_location = -1;
                        InvalidateRect(window, NULL, FALSE);
                    }
                }
            }
        }
    } else if (g_menu.screen == SCREEN_LOAD_GAME) {
        /* FUN_00458162 maps the two columns and four rows to slots 00..07.
           An empty slot closes the load/save screen; a valid slot is kept
           here with an explicit notice until savegame restoration is ported. */
        if (y >= 35) {
            int slot = (y - 28) / 112 + (x / 320) * 4;
            if (slot >= 0 && slot < 8 && g_load_slot_valid[slot]) {
                MessageBoxA(window,
                            "Cette sauvegarde est valide, mais son chargement n'est pas encore pris en charge.",
                            "Tone Rebellion remake", MB_OK | MB_ICONINFORMATION);
            } else {
                g_menu.screen = SCREEN_MAIN_MENU;
            }
        } else {
            g_menu.screen = SCREEN_MAIN_MENU;
        }
    }
    (void)update_hover_help(x, y);
    (void)update_newgame_text(x, y);
    (void)update_hall_stock_hover(x, y);
    (void)update_island_button_hover(x, y);
    (void)update_hall_command_hover(x, y);
    update_window_title(window);
    InvalidateRect(window, NULL, FALSE);
}

static LRESULT CALLBACK menu_window_proc(HWND window, UINT message,
                                          WPARAM wparam, LPARAM lparam)
{
    switch (message) {
    case WM_SETCURSOR:
        if (LOWORD(lparam) == HTCLIENT) {
            update_interaction_cursor();
            return TRUE;
        }
        break;
    case WM_PAINT:
        paint_window(window);
        return 0;
    case WM_ERASEBKGND:
        return 1;
    case WM_TIMER:
        if (wparam == 2) {
            keep_background_tune_playing();
            return 0;
        }
        if (wparam == 1 && (g_menu.screen == SCREEN_NEW_GAME ||
                            g_menu.screen == SCREEN_WORLD_MAP ||
                            g_menu.screen == SCREEN_ISLAND)) {
            ++g_menu.animation_ticks;
            if (g_menu.screen == SCREEN_WORLD_MAP && g_mouse_inside) {
                /* Islands orbit under a stationary pointer. Re-hit-test each
                   animation tick so the hover frame follows the moving art. */
                (void)update_world_map_hover(g_mouse_x, g_mouse_y);
            }
            if (g_menu.screen == SCREEN_ISLAND && g_game_session_valid) {
                game_session_dispatch_island_events(&g_game_session);
                (void)game_session_dispatch_trade_requests(&g_game_session);
                (void)game_session_dispatch_build_selections(&g_game_session);
                (void)game_session_dispatch_onoff_actions(&g_game_session,
                                                          &g_pad_catalog);
                game_session_tick_item_animations(&g_game_session,
                                                  &g_building_render_catalog);
                game_session_tick_floater_moves(&g_game_session,
                                                g_menu.animation_ticks);
                (void)game_session_update_resource_requests(&g_game_session);
            }
            /* Redraw the full animated screen at every 30 Hz simulation tick,
               including while the Tasks panel is open. */
            InvalidateRect(window, NULL, FALSE);
        }
        return 0;
    case WM_MOUSEMOVE: {
        RECT client;
        RECT viewport;
        TRACKMOUSEEVENT track;
        int width;
        int height;
        int x;
        int y;
        GetClientRect(window, &client);
        width = client.right - client.left;
        height = client.bottom - client.top;
        if (!logical_viewport(width, height, &viewport)) return 0;
        x = GET_X_LPARAM(lparam);
        y = GET_Y_LPARAM(lparam);
        if (x < viewport.left || x >= viewport.right || y < viewport.top || y >= viewport.bottom) {
            int construct_hover_changed = update_iw_construct_hover(-1, -1);
            int inventory_hover_changed = update_inventory_hover(-1, -1);
            int diplomacy_hover_changed = update_diplomacy_hover(-1, -1);
            int action_hover_changed = update_location_action_hover(-1, -1);
            if (g_mouse_inside || g_hovered_help != -1 || g_hovered_newgame_text != -1 ||
                g_hovered_island != -1 || g_hovered_location != -1 ||
                g_hovered_hall_stock != -1 || g_hovered_island_button != -1 ||
                g_hovered_hall_command != WINDOW_ISLAND_PANEL_NONE ||
                action_hover_changed ||
                inventory_hover_changed || diplomacy_hover_changed) {
                g_mouse_inside = 0;
                if (g_hovered_help != -1 || g_hovered_newgame_text != -1 ||
                    g_hovered_island != -1 || g_hovered_location != -1 ||
                    g_hovered_hall_stock != -1 || g_hovered_island_button != -1 ||
                    g_hovered_hall_command != WINDOW_ISLAND_PANEL_NONE ||
                    action_hover_changed ||
                    inventory_hover_changed || diplomacy_hover_changed) {
                    g_hovered_help = -1;
                    g_hovered_newgame_text = -1;
                    g_hovered_island = -1;
                    g_hovered_location = -1;
                    g_hovered_hall_stock = -1;
                    g_hovered_island_button = -1;
                    g_hovered_hall_command = WINDOW_ISLAND_PANEL_NONE;
                    g_hovered_location_action = ISLAND_LOCATION_ACTION_NONE;
                    InvalidateRect(window, NULL, FALSE);
                }
            }
            if (construct_hover_changed) InvalidateRect(window, NULL, FALSE);
            return 0;
        }
        g_mouse_x = (x - viewport.left) * LOGICAL_WIDTH / (viewport.right - viewport.left);
        g_mouse_y = (y - viewport.top) * LOGICAL_HEIGHT / (viewport.bottom - viewport.top);
        g_mouse_inside = 1;
        ZeroMemory(&track, sizeof(track));
        track.cbSize = sizeof(track);
        track.dwFlags = TME_LEAVE;
        track.hwndTrack = window;
        (void)TrackMouseEvent(&track);
        if (update_hover_help(g_mouse_x, g_mouse_y) |
            update_newgame_text(g_mouse_x, g_mouse_y) |
            update_world_map_hover(g_mouse_x, g_mouse_y) |
            update_island_location_hover(g_mouse_x, g_mouse_y) |
            update_hall_stock_hover(g_mouse_x, g_mouse_y) |
            update_location_action_hover(g_mouse_x, g_mouse_y) |
            update_island_button_hover(g_mouse_x, g_mouse_y) |
            update_hall_command_hover(g_mouse_x, g_mouse_y) |
            update_inventory_hover(g_mouse_x, g_mouse_y) |
            update_glyph_hover(g_mouse_x, g_mouse_y) |
            update_diplomacy_hover(g_mouse_x, g_mouse_y) |
            update_iw_construct_hover(g_mouse_x, g_mouse_y)) {
            InvalidateRect(window, NULL, FALSE);
        }
        return 0;
    }
    case WM_MOUSELEAVE: {
        int glyph_hover_changed;
        g_mouse_inside = 0;
        (void)update_iw_construct_hover(-1, -1);
        (void)update_diplomacy_hover(-1, -1);
        glyph_hover_changed = g_island_panel_mode == WINDOW_ISLAND_PANEL_GLYPHS
            ? game_glyph_inventory_mouse_leave(&g_hovered_glyph,
                                               &g_glyph_info_default) : 0;
        if (g_hovered_help != -1 || g_hovered_newgame_text != -1 ||
            g_hovered_island != -1 || g_hovered_location != -1 ||
            g_hovered_hall_stock != -1 || g_hovered_island_button != -1 ||
            g_hovered_hall_command != WINDOW_ISLAND_PANEL_NONE ||
            g_hovered_location_action != ISLAND_LOCATION_ACTION_NONE ||
            g_hovered_inventory_item != -1 || g_diplomacy_hover_valid ||
            glyph_hover_changed) {
            if (g_hovered_inventory_item != -1 &&
                g_island_panel_mode == WINDOW_ISLAND_PANEL_INVENTORY) {
                g_inventory_info_mode = ISLAND_PANEL_INFO_INVENTORY_DETAIL;
            }
            g_hovered_help = -1;
            g_hovered_newgame_text = -1;
            g_hovered_island = -1;
            g_hovered_location = -1;
            g_hovered_hall_stock = -1;
            g_hovered_island_button = -1;
            g_hovered_hall_command = WINDOW_ISLAND_PANEL_NONE;
            g_hovered_location_action = ISLAND_LOCATION_ACTION_NONE;
            g_hovered_inventory_item = -1;
            g_diplomacy_hover_valid = 0;
            InvalidateRect(window, NULL, FALSE);
        }
        return 0;
    }
    case WM_LBUTTONUP: {
        RECT client;
        RECT viewport;
        int width;
        int height;
        int x;
        int y;
        GetClientRect(window, &client);
        width = client.right - client.left;
        height = client.bottom - client.top;
        if (!logical_viewport(width, height, &viewport)) return 0;
        if (GET_X_LPARAM(lparam) < viewport.left || GET_X_LPARAM(lparam) >= viewport.right ||
            GET_Y_LPARAM(lparam) < viewport.top || GET_Y_LPARAM(lparam) >= viewport.bottom) {
            return 0;
        }
        x = ((GET_X_LPARAM(lparam) - viewport.left) * LOGICAL_WIDTH) /
            (viewport.right - viewport.left);
        y = ((GET_Y_LPARAM(lparam) - viewport.top) * LOGICAL_HEIGHT) /
            (viewport.bottom - viewport.top);
        handle_click(window, x, y);
        update_interaction_cursor();
        return 0;
    }
    case WM_RBUTTONDOWN:
        return 0;
    case WM_RBUTTONUP: {
        RECT client;
        RECT viewport;
        int width;
        int height;
        int x;
        int y;
        GetClientRect(window, &client);
        width = client.right - client.left;
        height = client.bottom - client.top;
        if (!logical_viewport(width, height, &viewport) ||
            GET_X_LPARAM(lparam) < viewport.left ||
            GET_X_LPARAM(lparam) >= viewport.right ||
            GET_Y_LPARAM(lparam) < viewport.top ||
            GET_Y_LPARAM(lparam) >= viewport.bottom) return 0;
        x = ((GET_X_LPARAM(lparam) - viewport.left) * LOGICAL_WIDTH) /
            (viewport.right - viewport.left);
        y = ((GET_Y_LPARAM(lparam) - viewport.top) * LOGICAL_HEIGHT) /
            (viewport.bottom - viewport.top);
        if (adjust_trade_cell(x, y, -1) ||
            click_diplomacy_action(x, y, selected_hall_player())) {
            InvalidateRect(window, NULL, FALSE);
        } else if (g_menu.screen == SCREEN_ISLAND && g_game_session_valid &&
            x >= 0 && x < LOGICAL_WIDTH && y >= 0 && y < 320 &&
            g_selected_floater >= 0 &&
            g_selected_floater < g_game_session.floater_count &&
            g_menu.selected_map_island >= 0 &&
            g_menu.selected_map_island < g_game_session.island_count &&
            g_menu.selected_tribe < GAME_START_PLAYER_COUNT &&
            g_game_session.floaters[g_selected_floater].source_subtype != 0) {
            (void)game_session_order_floater_to_coordinate(
                &g_game_session, g_menu.selected_tribe,
                (uint8_t)g_menu.selected_map_island,
                (unsigned int)g_selected_floater,
                (uint16_t)(x + g_island_scroll_x), (uint16_t)y);
            InvalidateRect(window, NULL, FALSE);
        }
        return 0;
    }
    case WM_MOUSEWHEEL:
        if (g_menu.screen == SCREEN_ISLAND) {
            int direction = GET_WHEEL_DELTA_WPARAM(wparam) > 0 ? -1 : 1;
            g_island_scroll_x += direction * 128;
            if (g_island_scroll_x < 0) g_island_scroll_x = 0;
            if (g_island_scroll_x > 1920) g_island_scroll_x = 1920;
            g_hovered_location = -1;
            InvalidateRect(window, NULL, FALSE);
        }
        return 0;
    case WM_KEYDOWN:
        if (wparam == VK_ESCAPE) {
            if (g_menu.screen == SCREEN_LOAD_GAME) {
                g_menu.screen = SCREEN_MAIN_MENU;
                InvalidateRect(window, NULL, FALSE);
            } else if (g_menu.screen == SCREEN_ISLAND) {
                g_menu.screen = SCREEN_WORLD_MAP;
                g_hovered_location = -1;
                InvalidateRect(window, NULL, FALSE);
            } else if (g_menu.screen == SCREEN_WORLD_MAP) {
                g_hovered_island = -1;
                g_menu.screen = SCREEN_NEW_GAME;
                g_menu.setup_accepted = 0;
                InvalidateRect(window, NULL, FALSE);
            } else if (g_menu.screen == SCREEN_NEW_GAME) {
                g_menu.screen = SCREEN_MAIN_MENU;
                g_menu.setup_accepted = 0;
                InvalidateRect(window, NULL, FALSE);
            } else {
                PostMessageA(window, WM_CLOSE, 0, 0);
            }
        } else if (wparam == VK_RETURN) {
            if (g_menu.screen == SCREEN_MAIN_MENU) {
                g_menu.screen = SCREEN_NEW_GAME;
            } else if (g_menu.screen == SCREEN_NEW_GAME) {
                (void)begin_new_game(window);
            } else if (g_menu.screen == SCREEN_LOAD_GAME) {
                g_menu.screen = SCREEN_MAIN_MENU;
            } else if (g_menu.screen == SCREEN_WORLD_MAP) {
                int selected = g_menu.selected_map_island;
                if (selected < 0) selected = g_menu.selected_tribe;
                (void)open_island_view(window, selected);
            } else if (g_menu.screen == SCREEN_ISLAND) {
                if (g_selected_location >= 0) g_hovered_location = g_selected_location;
            } else {
                g_menu.screen = SCREEN_NEW_GAME;
            }
            InvalidateRect(window, NULL, FALSE);
        } else if (g_menu.screen == SCREEN_MAIN_MENU && wparam == 'N') {
            g_menu.screen = SCREEN_NEW_GAME;
            InvalidateRect(window, NULL, FALSE);
        } else if (g_menu.screen == SCREEN_MAIN_MENU && wparam == 'L') {
            g_menu.screen = SCREEN_LOAD_GAME;
            InvalidateRect(window, NULL, FALSE);
        } else if (g_menu.screen == SCREEN_WORLD_MAP &&
                   (wparam == VK_LEFT || wparam == VK_RIGHT)) {
            const int count = g_menu.world_map.world_count;
            g_menu.world_index = (g_menu.world_index + count +
                (wparam == VK_RIGHT ? 1 : -1)) % count;
            g_menu.selected_map_island = -1;
            g_hovered_island = -1;
            InvalidateRect(window, NULL, FALSE);
        } else if (g_menu.screen == SCREEN_ISLAND &&
                   (wparam == VK_LEFT || wparam == VK_RIGHT)) {
            g_island_scroll_x += wparam == VK_RIGHT ? 160 : -160;
            if (g_island_scroll_x < 0) g_island_scroll_x = 0;
            if (g_island_scroll_x > 1920) g_island_scroll_x = 1920;
            g_hovered_location = -1;
            InvalidateRect(window, NULL, FALSE);
        } else if (g_menu.screen == SCREEN_NEW_GAME &&
                   (wparam == VK_LEFT || wparam == VK_RIGHT)) {
            const int count = g_menu.world_map.world_count;
            g_menu.world_index = (g_menu.world_index + count +
                (wparam == VK_RIGHT ? 1 : -1)) % count;
            g_menu.setup_accepted = 0;
            InvalidateRect(window, NULL, FALSE);
        } else if (g_menu.screen == SCREEN_NEW_GAME && wparam == 'D') {
            dispatch_newgame_master_message(window, 55);
            InvalidateRect(window, NULL, FALSE);
        } else if (g_menu.screen == SCREEN_NEW_GAME && wparam >= '1' && wparam <= '4') {
            dispatch_newgame_master_message(window, 60 + (int)(wparam - '1'));
            InvalidateRect(window, NULL, FALSE);
        }
        if (g_mouse_inside && (update_hover_help(g_mouse_x, g_mouse_y) |
                               update_newgame_text(g_mouse_x, g_mouse_y) |
                               update_world_map_hover(g_mouse_x, g_mouse_y) |
                               update_island_location_hover(g_mouse_x, g_mouse_y))) {
            InvalidateRect(window, NULL, FALSE);
        }
        update_window_title(window);
        update_interaction_cursor();
        return 0;
    case WM_DESTROY:
        destroy_sprite_source_dc();
        destroy_paint_buffer();
        stop_background_tune();
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProcA(window, message, wparam, lparam);
    }
}
