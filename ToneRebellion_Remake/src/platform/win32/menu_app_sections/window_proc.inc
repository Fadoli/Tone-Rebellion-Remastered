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
                (void)game_session_dispatch_glyph_actions(&g_game_session);
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
