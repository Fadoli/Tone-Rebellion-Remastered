/* One tick of the shared session: queued requests, animations, moves,
   AI, then the world/audio events it produced. Solo runs it on the island
   screen with the UI clock; a network game runs it on every screen with
   the session clock (net_run_frame) so every machine steps alike. */
static void simulate_session_tick(uint32_t source_tick)
{
    GameSessionAudioEvent audio_event;
    GameSessionWorldEvent world_event;
    game_session_dispatch_island_events(&g_game_session);
    (void)game_session_dispatch_trade_requests(&g_game_session);
    (void)game_session_dispatch_build_selections(&g_game_session);
    (void)game_session_dispatch_glyph_actions(&g_game_session);
    (void)game_session_dispatch_cast_actions(&g_game_session);
    (void)game_session_dispatch_onoff_actions(&g_game_session,
                                              &g_pad_catalog);
    game_session_tick_item_animations_with_floaters(
        &g_game_session, &g_building_render_catalog,
        &g_floater_catalog, &g_pad_catalog);
    game_session_update_construction_tasks(&g_game_session,
                                           &g_pad_catalog);
    game_session_tick_floater_moves(&g_game_session, source_tick,
                                    &g_pad_catalog);
    (void)game_session_update_resource_requests(&g_game_session);
    game_session_tick_leviathan_ai(&g_game_session);
    {
        int32_t bond;
        if (game_session_leviathan_bond_notice(&g_game_session, &bond)) {
            queue_leviathan_bond_notice(bond);
            alert_leviathan_wave();
        }
    }
    while (game_session_pop_world_event(&g_game_session,
                                        &world_event)) {
        if (world_event.kind ==
            GAME_SESSION_WORLD_EVENT_FLOATER_ADVANCED) {
            queue_floater_advance_notice(world_event.payload);
        } else if (world_event.kind ==
            GAME_SESSION_WORLD_EVENT_ISLAND_REACHED) {
            char tune_id[16];
            if (game_music_island_reached(&g_game_music, world_event.payload,
                    (uint8_t)g_game_session.config.selected_tribe,
                    g_net_in_game ? &g_net_local_rng
                                  : &g_game_session.random_state,
                    tune_id, sizeof(tune_id)))
                set_background_tune(tune_id);
        } else if (world_event.kind ==
            GAME_SESSION_WORLD_EVENT_BUILDING_DESTROYED) {
            /* FUN_0042fa0f message 5, event 8: only a selected destroyed
               site matters; FUN_0042f303(0) returns to the Hall default. */
            if (selection_island() == (int)world_event.island_index &&
                g_selected_location ==
                    (int)((uint32_t)world_event.payload & 0xffffU)) {
                g_selected_floater = -1;
                select_location_on_view(-1);
                g_island_panel_mode = WINDOW_ISLAND_PANEL_GENERAL;
            }
        }
    }
    /* Drain the whole queue each frame; every audible instance plays on
       its own mixer voice with FUN_0045b24d's distance volume and pan. */
    while (game_session_pop_audio_event(&g_game_session, &audio_event)) {
        const unsigned char *sound = NULL;
        int restart = 0;
        if (!game_session_audio_event_is_audible(&audio_event,
                g_menu.screen == SCREEN_ISLAND,
                g_menu.selected_map_island)) continue;
        if (audio_event.kind == GAME_SESSION_AUDIO_BUILD) {
            sound = audio_event.owner_id == 4
                ? g_levbuild_sound : g_fltbuild_sound;
        } else if (audio_event.kind == GAME_SESSION_AUDIO_FLOATER_DEATH) {
            sound = audio_event.owner_id == 4
                ? g_levdeath_sound : g_fltdeath_sound;
            restart = 1; /* FUN_0045afb9 restarts levdeath/fltdeath */
        } else if (audio_event.kind == GAME_SESSION_AUDIO_BRIDGE) {
            sound = g_bridge_sound;
        } else if (audio_event.kind == GAME_SESSION_AUDIO_FLOATER_BIRTH) {
            sound = audio_event.owner_id == 4
                ? g_levbirth_sound : g_fltbirth_sound;
        } else if (audio_event.kind == GAME_SESSION_AUDIO_CAST &&
                   audio_event.sound < 10U) {
            sound = g_cast_sounds[audio_event.sound];
        } else if (audio_event.kind == GAME_SESSION_AUDIO_EFFECT &&
                   audio_event.sound < FLOATER_EFFECT_MAX) {
            sound = g_effect_sounds[audio_event.sound];
        }
        if (sound != NULL) sfx_play_at(sound, audio_event.x, restart);
    }
    sfx_pump();
}

/* One 50 ms UI frame (frame_limit 20): timers, animations and the
   simulation steps of that frame. */
static void run_ui_frame(HWND window, WPARAM wparam)
{
    if (wparam == 1) {
        e2e_write_state();
        /* One SceneWindow paint per frame; resets off the title. */
        title_credits_tick();
        if (net_poll(window)) platform_invalidate(window);
    }
    if (wparam == 1 && g_menu.screen == SCREEN_MAIN_MENU) {
        platform_invalidate(window);
        return;
    }
    if (wparam == 1 && g_menu.screen == SCREEN_NET_SETUP) {
        /* Caret blink. */
        platform_invalidate(window);
        return;
    }
    if (wparam == 2) {
        keep_background_tune_playing();
        return;
    }
    if (wparam == 1 && g_menu.screen == SCREEN_END_GAME) {
        end_game_screen_tick();
        platform_invalidate(window);
        return;
    }
    if (wparam == 1 && g_menu.screen == SCREEN_LOGO) {
        /* FUN_0041c46f: logo fade-in, fade-out, then the title state and
           the `start` tune (requested after the logo). */
        ++g_logo_tick;
        if (logo_splash_finished()) {
            free(g_logo_pixels);
            g_logo_pixels = NULL;
            g_menu.screen = SCREEN_MAIN_MENU;
            set_background_tune_once("start");
        }
        platform_invalidate(window);
        return;
    }
    if (wparam == 1 && g_net_in_game && g_menu.screen == SCREEN_LOAD_GAME) {
        /* Saving during a network game: the turns go on meanwhile. */
        net_run_frame(window);
        platform_invalidate(window);
        return;
    }
    if (wparam == 1 && (g_menu.screen == SCREEN_NEW_GAME ||
                        g_menu.screen == SCREEN_WORLD_MAP ||
                        g_menu.screen == SCREEN_ISLAND)) {
        /* FUN_0041c46f runs the tick DAT_004bf110 times per frame; keys 8/9
           change it from 1 to 3 (FUN_0046a5b7). */
        unsigned sim_steps = g_menu.screen == SCREEN_NEW_GAME ? 1U : g_sim_speed;
        render_interp_begin_frame();
        slide_panel_tick();
        /* The SlideWindow pause flag (DAT_004bf124) stops the game loop on
           the island and on the world map alike (planet view frozen). */
        if (g_paused && (g_menu.screen == SCREEN_ISLAND ||
                         g_menu.screen == SCREEN_WORLD_MAP)) sim_steps = 0;
        /* A network game advances by turns on every screen; the loop
           below then only drives the UI animation clock. */
        if (g_net_in_game) {
            net_run_frame(window);
            sim_steps = g_paused ? 0U : 1U;
        }
        /* FUN_0045eaa7 sets the end-sequence flag when the solo tribe has
           no floaters left; FUN_00464e4d then queues SetState(2) 100 ticks
           into S3 and SetState(0) (title) about 1,560 ticks after the flag
           (S1 100, S3 1,300, S5 160). The flag is also set when the gross
           capacity P+0x3c (source_maintenance_capacity) is below 1. The
           L == 0 end-screen branch (all seals broken) runs below through
           game_session_tick_world_sequence; FUN_00466ce2 only starts the
           defeat while the sequence state is 0. */
        if (g_game_session_valid && g_menu.screen != SCREEN_NEW_GAME &&
            g_game_session.world_sequence_state == 0 &&
            g_menu.selected_tribe >= 0 &&
            g_menu.selected_tribe < GAME_START_PLAYER_COUNT) {
            /* The +0x90 latch never clears, so the defeat runs to the end
               even if a floater or capacity comes back meanwhile. */
            if (g_game_session.economy[g_menu.selected_tribe].defeat_latched ||
                game_session_count_player_floaters(&g_game_session,
                    (uint8_t)g_menu.selected_tribe) == 0U ||
                g_game_session.economy[g_menu.selected_tribe]
                    .source_maintenance_capacity < 1) {
                ++g_defeat_ticks;
                /* FUN_0045eaa7 queues world event 0xb (p << 16 | 3) with
                   the flag; FUN_004334ce plays `loosend` for the local
                   player through FUN_0045aafd(name, 0, 0, 0). */
                if (g_defeat_ticks == 1U) set_background_tune_once("loosend");
                if (g_defeat_ticks == 200U &&
                    g_menu.screen == SCREEN_ISLAND) {
                    g_menu.screen = SCREEN_WORLD_MAP;
                    g_hovered_location = -1;
                }
                if (g_defeat_ticks >= 1563U) {
                    g_defeat_ticks = 0;
                    g_game_session_valid = 0;
                    g_menu.screen = SCREEN_MAIN_MENU;
                }
            } else {
                g_defeat_ticks = 0;
            }
        }
        island_panic_pulse_step();
        while (sim_steps-- != 0U) {
        ++g_menu.animation_ticks;
        world_map_tick_orbit_ranges();
        /* No per-tick world-map hover re-test: FUN_004702d9 re-tests only on
           message 10, the mouse-move code FUN_0046be81 sends, so an island
           orbiting under a still pointer keeps its old hover state. */
        if (g_menu.screen == SCREEN_ISLAND && g_game_session_valid &&
            !g_net_in_game)
            simulate_session_tick(g_menu.animation_ticks);
        if (!g_net_in_game && run_world_sequence_step(window)) break;
        }
        render_interp_end_frame();
        alerts_observe();
        autosave_tick();
        /* Redraw the full animated screen at every 20 Hz frame,
           including while the Tasks panel is open. */
        platform_invalidate(window);
    }
}

/* FUN_00464e4d runs once per world tick on every game screen, on every
   machine of a network game alike (lockstep: net_run_frame calls this after
   each turn). The seal victory reaches SetState(2) 1,102 ticks after state 2
   and SetState(7) 2,054 ticks after it; DAT_004bf120 = 0 then stops the
   game, so the session ends with the end screen. Returns 1 when it did. */
static int run_world_sequence_step(HWND window)
{
    int request;
    if (!g_game_session_valid || g_game_session.world_sequence_state < 2)
        return 0;
    /* State 2 queues world event 0xb (0) at tick 0; FUN_004334ce answers
       with the `winend` tune. */
    if (g_game_session.world_sequence_state == 2 &&
        g_game_session.world_sequence_tick == 0)
        set_background_tune_once("winend");
    game_session_world_sequence_state2_events(&g_game_session,
                                              &g_floater_catalog);
    request = game_session_tick_world_sequence(&g_game_session);
    if (request == 2 && g_menu.screen == SCREEN_ISLAND) {
        g_menu.screen = SCREEN_WORLD_MAP;
        g_hovered_location = -1;
        update_window_title(window);
    } else if (request == 7) {
        if (!enter_end_game_screen())
            g_menu.screen = SCREEN_MAIN_MENU;
        g_game_session_valid = 0;
        /* The game is over on every machine: leave the network session. */
        if (g_net_in_game) net_shutdown();
        return 1;
    }
    return 0;
}

/* WM_TIMER fires on the system tick (15.6 ms by default), so a 50 ms
   SetTimer really ran every 62.5 ms (16 frames/s). A 10 ms timer with
   1 ms resolution now polls this high-resolution clock, which releases
   one frame per elapsed 50 ms; a late timer runs the missed frames (at
   most four, then the clock resynchronises). */
static unsigned frame_clock_due(void)
{
    static uint64_t next;
    uint64_t period = platform_counter_frequency() / 20U;
    uint64_t now = platform_counter();
    unsigned due = 0;
    if (next == 0) next = now;
    while (now >= next && due < 4U) {
        next += period;
        ++due;
    }
    if (now >= next) next = now + period;
    return due;
}

/* Window (system) menu entries for the scaling modes; system command IDs
   keep their low four bits clear and stay below 0xF000. */
enum { SYSCOMMAND_SCALE_FIRST = 0x0100, SYSCOMMAND_RATE_FIRST = 0x0200 };
static const char *const g_scale_mode_labels[SCALE_MODE_COUNT] = {
    "Scale: whole multiples (sharp, even pixels)",
    "Scale: fill window (sharp)",
    "Scale: fill window (smooth)",
    "Scale: fill window (sharp bilinear: whole multiple, then smooth)"
};

/* remake_sdl has no system menu: F12 cycles the modes. */
static void update_scale_menu(HWND window)
{
#ifdef TONE_PLATFORM_SDL
    (void)window;
#else
    HMENU menu = GetSystemMenu(window, FALSE);
    if (menu == NULL) return;
    (void)CheckMenuRadioItem(menu, SYSCOMMAND_SCALE_FIRST,
                             SYSCOMMAND_SCALE_FIRST + 0x10 * (SCALE_MODE_COUNT - 1),
                             SYSCOMMAND_SCALE_FIRST + 0x10 * (UINT)g_scale_mode,
                             MF_BYCOMMAND);
    (void)CheckMenuRadioItem(menu, SYSCOMMAND_RATE_FIRST,
                             SYSCOMMAND_RATE_FIRST + 0x10 * (PAINT_RATE_COUNT - 1),
                             SYSCOMMAND_RATE_FIRST + 0x10 * (UINT)g_paint_rate_index,
                             MF_BYCOMMAND);
#endif
}

static void add_scale_menu(HWND window)
{
#ifdef TONE_PLATFORM_SDL
    (void)window;
    (void)g_scale_mode_labels;
#else
    HMENU menu = GetSystemMenu(window, FALSE);
    int mode;
    if (menu == NULL) return;
    (void)AppendMenuA(menu, MF_SEPARATOR, 0, NULL);
    for (mode = 0; mode < SCALE_MODE_COUNT; ++mode)
        (void)AppendMenuA(menu, MF_STRING,
                          SYSCOMMAND_SCALE_FIRST + 0x10 * (UINT)mode,
                          g_scale_mode_labels[mode]);
    (void)AppendMenuA(menu, MF_SEPARATOR, 0, NULL);
    for (mode = 0; mode < PAINT_RATE_COUNT; ++mode) {
        char label[64];
        (void)snprintf(label, sizeof(label), "Display rate: %u Hz%s",
                       g_paint_rates[mode],
                       mode == 0 ? " (original, no blending)" : "");
        (void)AppendMenuA(menu, MF_STRING,
                          SYSCOMMAND_RATE_FIRST + 0x10 * (UINT)mode, label);
    }
    update_scale_menu(window);
#endif
}

static void set_scale_mode(HWND window, int mode)
{
    if (mode < 0 || mode >= SCALE_MODE_COUNT) return;
    g_scale_mode = mode;
    save_video_settings();
    update_scale_menu(window);
    /* The bars change size: repaint the whole client. */
    platform_invalidate(window);
}

/* The port's test aids (F6..F9) need Ctrl; e2e scripts, which post keys
   without modifiers, set TONE_REBELLION_E2E_TEST_AIDS instead. */
static int test_aid_keys(void)
{
    char value[8];
    return platform_ctrl_down() ||
        (e2e_enabled() &&
         platform_environment("TONE_REBELLION_E2E_TEST_AIDS", value, sizeof(value)));
}

/* Remake: paint rate of the island and world map (render_interp.inc). */
static void set_paint_rate(HWND window, int index)
{
    if (index < 0 || index >= PAINT_RATE_COUNT) return;
    g_paint_rate_index = index;
    save_video_settings();
    update_scale_menu(window);
}

static LRESULT CALLBACK menu_window_proc(HWND window, UINT message,
                                          WPARAM wparam, LPARAM lparam)
{
    switch (message) {
    case WM_SYSCOMMAND:
        if ((wparam & 0xFFF0U) >= SYSCOMMAND_SCALE_FIRST &&
            (wparam & 0xFFF0U) < SYSCOMMAND_SCALE_FIRST + 0x10 * SCALE_MODE_COUNT) {
            set_scale_mode(window,
                (int)(((wparam & 0xFFF0U) - SYSCOMMAND_SCALE_FIRST) / 0x10));
            return 0;
        }
        if ((wparam & 0xFFF0U) >= SYSCOMMAND_RATE_FIRST &&
            (wparam & 0xFFF0U) < SYSCOMMAND_RATE_FIRST + 0x10 * PAINT_RATE_COUNT) {
            set_paint_rate(window,
                (int)(((wparam & 0xFFF0U) - SYSCOMMAND_RATE_FIRST) / 0x10));
            return 0;
        }
        break;
    case WM_SETCURSOR:
        if (LOWORD(lparam) == HTCLIENT) {
            update_interaction_cursor();
            return TRUE;
        }
        break;
#ifndef TONE_PLATFORM_SDL
    case WM_PAINT:
        paint_window(window);
        return 0;
#endif
    case WM_ERASEBKGND:
        return 1;
    case WM_TIMER:
        if (wparam == 1) {
            unsigned due = frame_clock_due();
            while (due-- != 0U) run_ui_frame(window, wparam);
        } else {
            run_ui_frame(window, wparam);
        }
        return 0;
    case WM_MOUSEMOVE: {
        RECT client;
        RECT viewport;
#ifndef TONE_PLATFORM_SDL
        TRACKMOUSEEVENT track;
#endif
        int width;
        int height;
        int x;
        int y;
        platform_client_rect(window, &client);
        width = client.right - client.left;
        height = client.bottom - client.top;
        if (!logical_viewport(width, height, &viewport)) return 0;
        x = GET_X_LPARAM(lparam);
        y = GET_Y_LPARAM(lparam);
        if (g_slide_drag) {
            if ((wparam & MK_LBUTTON) == 0) {
                slide_panel_end_drag();
            } else {
                /* No repaint: the panel only exists on the world map and
                   island view, which redraw every 20 Hz frame (see the
                   IWLilMap drag below). */
                slide_panel_drag(((x - viewport.left) * LOGICAL_WIDTH) /
                                 (viewport.right - viewport.left));
                return 0;
            }
        }
        if (g_lilmap_drag) {
            if ((wparam & MK_LBUTTON) == 0) {
                g_lilmap_drag = 0;
                platform_capture_mouse(NULL, 0);
            } else {
                int logical_x = ((x - viewport.left) * LOGICAL_WIDTH) /
                    (viewport.right - viewport.left);
                int logical_y = ((y - viewport.top) * LOGICAL_HEIGHT) /
                    (viewport.bottom - viewport.top);
                /* No repaint here: the island screen redraws on every 20 Hz
                   frame, and a WM_PAINT per mouse move outranks WM_TIMER,
                   starving the frame clock into catch-up bursts. */
                (void)island_lilmap_scroll_to(logical_x, logical_y, 1);
                return 0;
            }
        }
        if (x < viewport.left || x >= viewport.right || y < viewport.top || y >= viewport.bottom) {
            int construct_hover_changed = update_iw_construct_hover(-1, -1);
            int inventory_hover_changed = update_inventory_hover(-1, -1);
            int diplomacy_hover_changed = update_diplomacy_hover(-1, -1);
            int action_hover_changed = update_location_action_hover(-1, -1);
            if (g_mouse_inside || g_hovered_help != -1 || g_hovered_newgame_text != -1 ||
                g_hovered_island != -1 || g_hovered_location != -1 ||
                g_hovered_hall_stock != -1 || g_hovered_island_button != -1 ||
                g_hovered_hall_command != WINDOW_ISLAND_PANEL_NONE ||
                g_hovered_location_grab ||
                action_hover_changed ||
                inventory_hover_changed || diplomacy_hover_changed) {
                g_mouse_inside = 0;
                if (g_hovered_help != -1 || g_hovered_newgame_text != -1 ||
                    g_hovered_island != -1 || g_hovered_location != -1 ||
                    g_hovered_hall_stock != -1 || g_hovered_island_button != -1 ||
                    g_hovered_hall_command != WINDOW_ISLAND_PANEL_NONE ||
                    g_hovered_location_grab ||
                    action_hover_changed ||
                    inventory_hover_changed || diplomacy_hover_changed) {
                    g_hovered_help = -1;
                    g_hovered_newgame_text = -1;
                    g_hovered_island = -1;
                    g_hovered_location = -1;
                    g_hovered_hall_stock = -1;
                    g_hovered_island_button = -1;
                    g_hovered_hall_command = WINDOW_ISLAND_PANEL_NONE;
                    g_hovered_location_grab = 0; g_hovered_defend_area = 0; g_hovered_upgspread = 0; g_hovered_training_stock = 0;
                    g_hovered_location_action = ISLAND_LOCATION_ACTION_NONE;
                    platform_invalidate(window);
                }
            }
            if (construct_hover_changed) platform_invalidate(window);
            return 0;
        }
        g_mouse_x = (x - viewport.left) * LOGICAL_WIDTH / (viewport.right - viewport.left);
        g_mouse_y = (y - viewport.top) * LOGICAL_HEIGHT / (viewport.bottom - viewport.top);
        g_mouse_inside = 1;
#ifndef TONE_PLATFORM_SDL
        /* WM_MOUSELEAVE (SDL sends SDL_EVENT_WINDOW_MOUSE_LEAVE itself). */
        ZeroMemory(&track, sizeof(track));
        track.cbSize = sizeof(track);
        track.dwFlags = TME_LEAVE;
        track.hwndTrack = window;
        (void)TrackMouseEvent(&track);
#endif
        if (update_hover_help(g_mouse_x, g_mouse_y) |
            update_newgame_text(g_mouse_x, g_mouse_y) |
            update_world_map_hover(g_mouse_x, g_mouse_y) |
            update_island_location_hover(g_mouse_x, g_mouse_y) |
            update_hall_stock_hover(g_mouse_x, g_mouse_y) |
            update_location_action_hover(g_mouse_x, g_mouse_y) |
            update_location_grab_hover(g_mouse_x, g_mouse_y) |
            update_island_button_hover(g_mouse_x, g_mouse_y) |
            update_hall_command_hover(g_mouse_x, g_mouse_y) |
            update_inventory_hover(g_mouse_x, g_mouse_y) |
            update_glyph_hover(g_mouse_x, g_mouse_y) |
            update_diplomacy_hover(g_mouse_x, g_mouse_y) |
            update_iw_construct_hover(g_mouse_x, g_mouse_y) |
            update_net_setup_hover(g_mouse_x, g_mouse_y)) {
            platform_invalidate(window);
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
            g_hovered_location_grab ||
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
            g_hovered_location_grab = 0; g_hovered_defend_area = 0; g_hovered_upgspread = 0; g_hovered_training_stock = 0;
            g_hovered_location_action = ISLAND_LOCATION_ACTION_NONE;
            g_hovered_inventory_item = -1;
            g_diplomacy_hover_valid = 0;
            platform_invalidate(window);
        }
        return 0;
    }
    case WM_LBUTTONDOWN: {
        /* A release lost outside the window must not swallow a later click. */
        g_swallow_left_button_up = 0;
        if (g_menu.screen == SCREEN_END_GAME) {
            /* Message 6 (left press) on ENDGPLAYER, ENDGTEXT or an ENDGNONP
               card: FUN_0041a7d6 / FUN_0041b575 / FUN_0041afbb queue
               SetState(0), the title. Remake choice: the click skips the
               text scroll and the card reveal instead; Escape leaves. */
            RECT end_client;
            RECT end_viewport;
            platform_client_rect(window, &end_client);
            if (logical_viewport(end_client.right - end_client.left,
                                 end_client.bottom - end_client.top,
                                 &end_viewport) &&
                end_viewport.right > end_viewport.left &&
                end_viewport.bottom > end_viewport.top &&
                end_game_screen_hit(
                    ((GET_X_LPARAM(lparam) - end_viewport.left) * LOGICAL_WIDTH) /
                        (end_viewport.right - end_viewport.left),
                    ((GET_Y_LPARAM(lparam) - end_viewport.top) * LOGICAL_HEIGHT) /
                        (end_viewport.bottom - end_viewport.top))) {
                end_game_screen_skip();
                platform_invalidate(window);
            }
            return 0;
        }
        if (g_menu.screen == SCREEN_LOGO) return 0;
        {
            RECT panel_client;
            RECT panel_viewport;
            platform_client_rect(window, &panel_client);
            if (g_options_open && !options_screen()) g_options_open = 0;
            if (g_options_open) {
                int px = -1, py = -1;
                if (logical_viewport(panel_client.right - panel_client.left,
                                     panel_client.bottom - panel_client.top,
                                     &panel_viewport) &&
                    panel_viewport.right > panel_viewport.left &&
                    panel_viewport.bottom > panel_viewport.top) {
                    px = ((GET_X_LPARAM(lparam) - panel_viewport.left) *
                          LOGICAL_WIDTH) / (panel_viewport.right - panel_viewport.left);
                    py = ((GET_Y_LPARAM(lparam) - panel_viewport.top) *
                          LOGICAL_HEIGHT) / (panel_viewport.bottom - panel_viewport.top);
                }
                (void)options_press(window, px, py);
                g_swallow_left_button_up = 1;
                platform_invalidate(window);
                return 0;
            }
            if ((g_menu.screen == SCREEN_WORLD_MAP || g_menu.screen == SCREEN_ISLAND) &&
                logical_viewport(panel_client.right - panel_client.left,
                                 panel_client.bottom - panel_client.top,
                                 &panel_viewport) &&
                GET_X_LPARAM(lparam) >= panel_viewport.left &&
                GET_X_LPARAM(lparam) < panel_viewport.right &&
                GET_Y_LPARAM(lparam) >= panel_viewport.top &&
                GET_Y_LPARAM(lparam) < panel_viewport.bottom) {
                int panel_x = ((GET_X_LPARAM(lparam) - panel_viewport.left) *
                               LOGICAL_WIDTH) /
                              (panel_viewport.right - panel_viewport.left);
                int panel_y = ((GET_Y_LPARAM(lparam) - panel_viewport.top) *
                               LOGICAL_HEIGHT) /
                              (panel_viewport.bottom - panel_viewport.top);
                if (slide_panel_press(window, panel_x, panel_y)) {
                    g_swallow_left_button_up = 1;
                    platform_invalidate(window);
                    return 0;
                }
            }
        }
        /* FUN_00469f56 delivers the left button press as window message 6
           and drops the release; FUN_00470fe7 enters the hovered island on
           that press. Other screens keep their release-based clicks. */
        RECT client;
        RECT viewport;
        int x;
        int y;
        platform_client_rect(window, &client);
        if (g_menu.screen == SCREEN_ISLAND &&
            logical_viewport(client.right - client.left,
                             client.bottom - client.top, &viewport) &&
            GET_X_LPARAM(lparam) >= viewport.left &&
            GET_X_LPARAM(lparam) < viewport.right &&
            GET_Y_LPARAM(lparam) >= viewport.top &&
            GET_Y_LPARAM(lparam) < viewport.bottom) {
            x = ((GET_X_LPARAM(lparam) - viewport.left) * LOGICAL_WIDTH) /
                (viewport.right - viewport.left);
            y = ((GET_Y_LPARAM(lparam) - viewport.top) * LOGICAL_HEIGHT) /
                (viewport.bottom - viewport.top);
            if (island_lilmap_scroll_to(x, y, 0)) {
                g_lilmap_drag = 1;
                g_swallow_left_button_up = 1;
                platform_capture_mouse(window, 1);
                platform_invalidate(window);
                return 0;
            }
        }
        if (g_menu.screen != SCREEN_WORLD_MAP ||
            !logical_viewport(client.right - client.left,
                              client.bottom - client.top, &viewport)) return 0;
        if (GET_X_LPARAM(lparam) < viewport.left || GET_X_LPARAM(lparam) >= viewport.right ||
            GET_Y_LPARAM(lparam) < viewport.top || GET_Y_LPARAM(lparam) >= viewport.bottom) {
            return 0;
        }
        x = ((GET_X_LPARAM(lparam) - viewport.left) * LOGICAL_WIDTH) /
            (viewport.right - viewport.left);
        y = ((GET_Y_LPARAM(lparam) - viewport.top) * LOGICAL_HEIGHT) /
            (viewport.bottom - viewport.top);
        if (world_island_at(x, y) >= 0) {
            g_swallow_left_button_up = 1;
            handle_click(window, x, y);
            update_interaction_cursor();
            platform_invalidate(window);
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
        if (g_menu.screen == SCREEN_LOGO || g_menu.screen == SCREEN_END_GAME) return 0;
        slide_panel_end_drag();
        if (g_lilmap_drag) {
            g_lilmap_drag = 0;
            platform_capture_mouse(NULL, 0);
        }
        if (g_swallow_left_button_up) {
            g_swallow_left_button_up = 0;
            return 0;
        }
        platform_client_rect(window, &client);
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
        if (g_options_open) return 0;
        RECT client;
        RECT viewport;
        int width;
        int height;
        int x;
        int y;
        platform_client_rect(window, &client);
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
            platform_invalidate(window);
        } else if (g_menu.screen == SCREEN_ISLAND && g_game_session_valid &&
                   clipboard_control_at(x, y) >= 11 &&
                   clipboard_control_at(x, y) <= 13) {
            /* FUN_0043913c message 7 -> FUN_0043822b: a right click on
               CLIPBD<n> empties that cell of the active group, filled or
               not (ev_19419676, ev_9d39a1dd). */
            game_session_clip_clear_cell(&g_game_session,
                (unsigned int)clipboard_control_at(x, y) - 11U);
            platform_invalidate(window);
        } else if (g_menu.screen == SCREEN_ISLAND && g_game_session_valid &&
            x >= 0 && x < LOGICAL_WIDTH && y >= 0 && y < 320 &&
            g_menu.selected_map_island >= 0 &&
            g_menu.selected_map_island < g_game_session.island_count &&
            g_menu.selected_tribe < GAME_START_PLAYER_COUNT) {
            int clicked_floater = game_session_floater_at(&g_game_session,
                (uint8_t)g_menu.selected_map_island,
                (uint16_t)(x + g_island_scroll_x), (uint16_t)y);
            if (platform_shift_down() &&
                g_selected_floater >= 0 &&
                g_selected_floater < g_game_session.floater_count &&
                clicked_floater >= 0 && clicked_floater != g_selected_floater &&
                g_game_session.floaters[clicked_floater].owner_slot ==
                    g_menu.selected_tribe) {
                /* Remake shortcut kept from the earlier port (FA_MergeWith);
                   FUN_00435826 has no modifier branch. */
                (void)ISSUE_COMMAND(GAME_COMMAND_ORDER_FLOATER_TO_MERGE, g_menu.selected_tribe, (uint8_t)g_menu.selected_map_island,
                    (unsigned int)g_selected_floater,
                    (unsigned int)clicked_floater);
            } else {
                island_right_click(clicked_floater, x, y);
            }
            platform_invalidate(window);
        }
        return 0;
    }
    case WM_MOUSEWHEEL:
        if (g_options_open) return 0;
        if (g_menu.screen == SCREEN_ISLAND) {
            int direction = GET_WHEEL_DELTA_WPARAM(wparam) > 0 ? -1 : 1;
            island_scroll_by(direction * 128);
            platform_invalidate(window);
        }
        return 0;
    case WM_KEYDOWN:
        /* Port-only: Shift+F12 cycles the display rate, F12 the scaling
           mode, on every screen. */
        if (wparam == VK_F12 && platform_shift_down()) {
            set_paint_rate(window, (g_paint_rate_index + 1) % PAINT_RATE_COUNT);
            return 0;
        }
        if (wparam == VK_F12) {
            set_scale_mode(window, (g_scale_mode + 1) % SCALE_MODE_COUNT);
            return 0;
        }
        /* The original logo loop polls no input. */
        if (g_menu.screen == SCREEN_LOGO) return 0;
        /* Remake options: F2 opens or closes them; while open they take
           every key. */
        if (wparam == VK_F2 && !g_options_open && options_screen()) {
            options_toggle();
            platform_invalidate(window);
            return 0;
        }
        if (options_key(window, wparam)) {
            platform_invalidate(window);
            return 0;
        }
        /* Remake shortcuts for the island controls (remake_qol.inc). */
        if (shortcut_key(window, (int)wparam)) {
            platform_invalidate(window);
            return 0;
        }
        if (wparam == VK_SPACE && options_screen() && alert_jump(window)) {
            platform_invalidate(window);
            return 0;
        }
        if (g_menu.screen == SCREEN_NET_SETUP) {
            /* Typed text arrives as WM_CHAR; keys here only navigate. */
            net_setup_key(window, wparam);
            update_window_title(window);
            platform_invalidate(window);
            return 0;
        }
        if ((g_menu.screen == SCREEN_ISLAND || g_menu.screen == SCREEN_WORLD_MAP) &&
            (wparam == '8' || wparam == VK_SUBTRACT || wparam == '9' || wparam == VK_ADD)) {
            /* FUN_0046a5b7: +-1 bounded 1..3. A network game sends the new
               value as a command so every machine changes at the same turn
               (native: session message 0xb, gated by multispeed). */
            int faster = wparam == '9' || wparam == VK_ADD;
            if (g_net_in_game) {
                int32_t speed = g_game_session.network_speed >= 1U &&
                                g_game_session.network_speed <= 3U
                                    ? (int32_t)g_game_session.network_speed : 1;
                speed += faster ? 1 : -1;
                if (speed >= 1 && speed <= 3)
                    (void)issue_command(GAME_COMMAND_SET_NETWORK_SPEED, 1, &speed);
            } else if (faster) {
                if (g_sim_speed < 3U) ++g_sim_speed;
            } else if (g_sim_speed > 1U) {
                --g_sim_speed;
            }
            return 0;
        }
        if (wparam == VK_F5 && (g_menu.screen == SCREEN_WORLD_MAP ||
                                g_menu.screen == SCREEN_ISLAND)) {
            /* Remake: F5 quicksaves; Shift+F5 (or F5 with quicksave off)
               opens the Save screen (state 5), whose native entry point is
               not established. */
            if (g_quicksave_enabled && !platform_shift_down()) quick_save();
            else enter_save_screen();
            platform_invalidate(window);
            return 0;
        }
        if (wparam == VK_F9 && g_quicksave_enabled && options_screen() &&
            !test_aid_keys()) {
            quick_load(window, platform_shift_down());
            update_window_title(window);
            platform_invalidate(window);
            return 0;
        }
        if (wparam == 'H' && g_menu.screen == SCREEN_WORLD_MAP &&
            e2e_enabled() && g_game_session_valid &&
            g_menu.selected_tribe >= 0 &&
            g_menu.selected_tribe < GAME_START_PLAYER_COUNT) {
            /* Test aid (only with TONE_REBELLION_E2E_STATE): open the island
               holding the player's Hall. */
            (void)open_island_view(window, g_game_session
                .economy[g_menu.selected_tribe].hall_island_index);
            platform_invalidate(window);
            return 0;
        }
        if (wparam == 'C' && e2e_enabled() && g_game_session_valid &&
            g_menu.selected_tribe >= 0 &&
            g_menu.selected_tribe < GAME_START_PLAYER_COUNT) {
            /* Test aid (only with TONE_REBELLION_E2E_STATE): the Hall
               build-tone stock button, sent as a command like a click. */
            (void)ISSUE_COMMAND(GAME_COMMAND_CYCLE_RESOURCE_STOCK,
                g_menu.selected_tribe, GAME_RESOURCE_BUILD_TONE);
            return 0;
        }
        if (wparam == 'R' && g_menu.screen == SCREEN_WORLD_MAP &&
            e2e_enabled() && g_menu.selected_map_island >= 0) {
            /* Test aid (only with TONE_REBELLION_E2E_STATE): reopen the last
               island without aiming at its orbiting map icon. */
            (void)open_island_view(window, g_menu.selected_map_island);
            platform_invalidate(window);
            return 0;
        }
        if (wparam == VK_F9 && test_aid_keys() &&
            g_menu.screen == SCREEN_ISLAND && !g_net_in_game &&
            g_game_session_valid && g_menu.selected_tribe >= 0 &&
            g_menu.selected_tribe < GAME_START_PLAYER_COUNT) {
            /* Port-only test aid: place the first training building
               (0x2c..0x2e) that fits on a free site of this island, so the
               BC_* order buttons and the clipboard can be checked in play. */
            unsigned int location_index;
            const GameRuntimeIsland *island =
                &g_game_session.islands[g_menu.selected_map_island];
            int placed = 0;
            for (location_index = 0;
                 !placed && location_index < island->location_count;
                 ++location_index) {
                unsigned int item;
                for (item = 0x2c; !placed && item <= 0x2e; ++item) {
                    IslandLocation site = {0};
                    site.kind = ISLAND_LOCATION_PAD;
                    site.renderer_subtype =
                        island->locations[location_index].construction_site_size;
                    placed = game_session_place_building(&g_game_session,
                        &g_pad_catalog, (uint8_t)g_menu.selected_tribe,
                        (uint8_t)g_menu.selected_map_island,
                        (uint16_t)location_index, &site, (uint16_t)item,
                        NULL, 0);
                    if (placed) {
                        unsigned int floater_index;
                        unsigned int linked = 0;
                        select_location_on_view((int)location_index);
                        /* Test aid: link two idle floaters of the tribe to the
                           new building so order adoption can be watched. */
                        for (floater_index = 0;
                             linked < 2U &&
                             floater_index < g_game_session.floater_count;
                             ++floater_index) {
                            GameFloaterStart *candidate =
                                &g_game_session.floaters[floater_index];
                            if (!game_session_floater_is_active(candidate) ||
                                candidate->owner_slot != g_menu.selected_tribe ||
                                candidate->island_index !=
                                    (uint8_t)g_menu.selected_map_island ||
                                candidate->source_subtype != 0 ||
                                candidate->source_link_0c != -1) continue;
                            candidate->source_link_0c = island->locations[
                                location_index].source_location_slot_18;
                            candidate->charge_source_island =
                                (uint8_t)g_menu.selected_map_island;
                            candidate->charge_source_location =
                                (uint16_t)location_index;
                            ++linked;
                        }
                    }
                }
            }
            platform_invalidate(window);
            return 0;
        }
        if (wparam == VK_F7 && test_aid_keys() &&
            g_menu.screen == SCREEN_ISLAND && !g_net_in_game &&
            g_game_session_valid && g_menu.selected_tribe >= 0 &&
            g_menu.selected_tribe < GAME_START_PLAYER_COUNT) {
            /* Port-only test aid: remove every floater of the tribe so the
               end sequence (no floaters left) can be watched. */
            unsigned int floater_index;
            for (floater_index = 0; floater_index < g_game_session.floater_count;
                 ++floater_index) {
                if (g_game_session.floaters[floater_index].owner_slot ==
                        g_menu.selected_tribe)
                    g_game_session.floaters[floater_index].is_active = 0;
            }
            return 0;
        }
        if (wparam == VK_F6 && test_aid_keys() &&
            g_menu.screen == SCREEN_ISLAND && !g_net_in_game &&
            g_game_session_valid && g_menu.selected_tribe >= 0 &&
            g_menu.selected_tribe < GAME_START_PLAYER_COUNT) {
            /* Port-only test aid: place a producer (0x25..0x27) on a free site
               so the native IWMove control can be tried on a cheap building. */
            unsigned int location_index;
            const GameRuntimeIsland *island =
                &g_game_session.islands[g_menu.selected_map_island];
            int placed = 0;
            {
                /* Test aid: top up the Hall so the move cost can be paid. */
                const GamePlayerEconomy *economy =
                    &g_game_session.economy[g_menu.selected_tribe];
                if (economy->hall_island_index < g_game_session.island_count &&
                    economy->hall_location_index <
                        g_game_session.islands[economy->hall_island_index]
                            .location_count) {
                    unsigned int resource;
                    GameRuntimeLocation *hall = &g_game_session.islands[
                        economy->hall_island_index].locations[
                            economy->hall_location_index];
                    for (resource = 0; resource < GAME_RESOURCE_TYPE_COUNT; ++resource)
                        hall->resource_stock[resource] = 100;
                }
            }
            for (location_index = 0;
                 !placed && location_index < island->location_count;
                 ++location_index) {
                unsigned int item;
                for (item = 0x25; !placed && item <= 0x27; ++item) {
                    IslandLocation site = {0};
                    site.kind = ISLAND_LOCATION_PAD;
                    site.renderer_subtype =
                        island->locations[location_index].construction_site_size;
                    placed = game_session_place_building(&g_game_session,
                        &g_pad_catalog, (uint8_t)g_menu.selected_tribe,
                        (uint8_t)g_menu.selected_map_island,
                        (uint16_t)location_index, &site, (uint16_t)item,
                        NULL, 0);
                    if (placed) select_location_on_view((int)location_index);
                }
            }
            platform_invalidate(window);
            return 0;
        }
        if (wparam == VK_F8 && test_aid_keys() &&
            g_menu.screen == SCREEN_ISLAND && !g_net_in_game &&
            g_game_session_valid && g_menu.selected_tribe >= 0 &&
            g_menu.selected_tribe < GAME_START_PLAYER_COUNT) {
            /* Port-only test aid: give the next tribe a base-0x28 block on a
               free site and make it visible to the viewer, so UpgSpread can
               be checked in play. */
            unsigned int location_index;
            unsigned int other = (g_menu.selected_tribe + 1U) % 4U;
            GameRuntimeIsland *island =
                &g_game_session.islands[g_menu.selected_map_island];
            int placed = 0;
            g_game_session.economy[other].source_maintenance_budget = 1000;
            for (location_index = 0;
                 !placed && location_index < island->location_count;
                 ++location_index) {
                IslandLocation site = {0}; char dbg_error[160];
                island->locations[location_index].source_value_22 |=
                    (uint16_t)(1U << other);
                site.kind = ISLAND_LOCATION_PAD;
                site.renderer_subtype =
                    island->locations[location_index].construction_site_size;
                placed = game_session_place_building(&g_game_session,
                    &g_pad_catalog, (uint8_t)other,
                    (uint8_t)g_menu.selected_map_island,
                    (uint16_t)location_index, &site, 0x28, dbg_error, sizeof(dbg_error));
                if (!placed) platform_set_title(window, dbg_error);
                if (placed) {
                    island->locations[location_index].source_value_22 |=
                        (uint16_t)(1U << g_menu.selected_tribe);
                    select_location_on_view((int)location_index);
                }
            }
            platform_invalidate(window);
            return 0;
        }
        if (wparam == VK_F11 && (g_menu.screen == SCREEN_WORLD_MAP ||
                                 g_menu.screen == SCREEN_ISLAND)) {
            /* Port-only aid. In a network game it sends world command 0x15
               like the native debug key 'W' (FUN_0046a5b7 0x46a92a, gated by
               DAT_004c2b74): every machine jumps to sequence state 3. Solo
               keeps the direct end-screen preview. */
            if (g_net_in_game) {
                if (g_game_session_valid &&
                    g_game_session.world_sequence_state < 2)
                    (void)issue_command(GAME_COMMAND_START_END_SEQUENCE, 0, NULL);
            } else if (enter_end_game_screen()) platform_invalidate(window);
            return 0;
        }
        if (wparam == VK_ESCAPE && (g_defend_area_armed || g_armed_spell_action)) {
            g_defend_area_armed = 0;
            g_armed_spell_action = 0;
            update_interaction_cursor();
            platform_invalidate(window);
            return 0;
        }
        if (wparam == VK_ESCAPE && g_menu.screen == SCREEN_END_GAME) {
            /* Remake exit (the native one is a click): SetState(0), the
               title, as the native exit; the F11 preview ends the game too. */
            g_game_session_valid = 0;
            g_menu.screen = SCREEN_MAIN_MENU;
            update_window_title(window);
            platform_invalidate(window);
            return 0;
        }
        if (wparam == VK_ESCAPE) {
            if (g_menu.screen == SCREEN_LOAD_GAME) {
                leave_load_screen();
                platform_invalidate(window);
            } else if (g_menu.screen == SCREEN_ISLAND &&
                       g_game_session.location_move_active) {
                /* A held building is put back first. */
                (void)issue_command(GAME_COMMAND_CANCEL_LOCATION_MOVE, 0, NULL);
                platform_invalidate(window);
            } else if (g_menu.screen == SCREEN_ISLAND ||
                       g_menu.screen == SCREEN_WORLD_MAP) {
                /* Remake shortcut (no native Esc in game): open or close the
                   SlideWindow options panel (save, load, pause, quit, music,
                   sound), as a press on the top edge does. */
                slide_panel_toggle();
                platform_invalidate(window);
            } else if (g_menu.screen == SCREEN_NEW_GAME) {
                leave_new_game_screen();
                platform_invalidate(window);
            } else {
                platform_request_close(window);
            }
        } else if (wparam == VK_RETURN) {
            if (g_menu.screen == SCREEN_MAIN_MENU) {
                g_menu.screen = SCREEN_NEW_GAME;
            } else if (g_menu.screen == SCREEN_NEW_GAME) {
                dispatch_newgame_master_message(window, 52);
            } else if (g_menu.screen == SCREEN_LOAD_GAME) {
                leave_load_screen();
            } else if (g_menu.screen == SCREEN_ISLAND) {
                if (view_selected_location() >= 0) g_hovered_location = view_selected_location();
            }
            platform_invalidate(window);
        } else if (g_menu.screen == SCREEN_MAIN_MENU && wparam == 'N') {
            g_menu.screen = SCREEN_NEW_GAME;
            platform_invalidate(window);
        } else if (g_menu.screen == SCREEN_MAIN_MENU && (wparam == 'H' || wparam == 'J')) {
            /* Remake entry points: the native host/join property sheet
               (FUN_0044c2b9) has no screen in windows.txt. */
            if (wparam == 'H' ? net_start_host() : net_start_join()) {
                g_menu.screen = SCREEN_NEW_GAME;
                g_menu.setup_accepted = 0;
            }
            platform_invalidate(window);
        } else if (g_menu.screen == SCREEN_MAIN_MENU && wparam == 'M') {
            enter_net_setup_screen();
            g_net_setup_swallow_char = 1;
            platform_invalidate(window);
        } else if (g_menu.screen == SCREEN_MAIN_MENU && wparam == 'L') {
            g_menu.screen = SCREEN_LOAD_GAME;
            platform_invalidate(window);
        } else if (g_menu.screen == SCREEN_NEW_GAME && wparam == 'L' &&
                   g_net_mode == NET_MODE_HOST && !g_net_in_game) {
            /* Remake: the lobby host picks a saved game to continue in
               network; every guest receives it. */
            g_net_load_pick = 1;
            g_load_save_mode = 0;
            g_load_from_game = 0;
            scan_load_slots();
            g_menu.screen = SCREEN_LOAD_GAME;
            platform_invalidate(window);
        } else if (g_menu.screen == SCREEN_ISLAND &&
                   (wparam == VK_LEFT || wparam == VK_RIGHT)) {
            island_scroll_by(wparam == VK_RIGHT ? 160 : -160);
            platform_invalidate(window);
        } else if (g_menu.screen == SCREEN_NEW_GAME && g_net_mode != NET_MODE_NONE &&
                   (wparam == VK_LEFT || wparam == VK_RIGHT)) {
            dispatch_newgame_master_message(window, 53);
            platform_invalidate(window);
        } else if (g_menu.screen == SCREEN_NEW_GAME && g_tribe_choice_mask == 0 &&
                   (wparam == VK_LEFT || wparam == VK_RIGHT)) {
            const int count = g_menu.world_map.world_count;
            g_menu.world_index = (g_menu.world_index + count +
                (wparam == VK_RIGHT ? 1 : -1)) % count;
            g_menu.setup_accepted = 0;
            platform_invalidate(window);
        } else if (g_menu.screen == SCREEN_NEW_GAME && wparam == 'D') {
            dispatch_newgame_master_message(window, 55);
            platform_invalidate(window);
        } else if (g_menu.screen == SCREEN_NEW_GAME && wparam >= '1' && wparam <= '4') {
            dispatch_newgame_master_message(window, 60 + (int)(wparam - '1'));
            platform_invalidate(window);
        }
        if (g_mouse_inside && (update_hover_help(g_mouse_x, g_mouse_y) |
                               update_newgame_text(g_mouse_x, g_mouse_y) |
                               update_world_map_hover(g_mouse_x, g_mouse_y) |
                               update_island_location_hover(g_mouse_x, g_mouse_y))) {
            platform_invalidate(window);
        }
        update_window_title(window);
        update_interaction_cursor();
        return 0;
    case WM_CHAR:
        if (g_menu.screen == SCREEN_NET_SETUP && net_setup_char(wparam))
            platform_invalidate(window);
        return 0;
    case WM_KEYUP:
        if (wparam == 'M') g_net_setup_swallow_char = 0;
        return 0;
    case WM_NET_SOCKET:
        if (net_poll(window)) platform_invalidate(window);
        return 0;
    case WM_DESTROY:
        net_shutdown();
        write_resume_file();
#ifndef TONE_PLATFORM_SDL
        destroy_paint_buffer();
#endif
        stop_background_tune();
#ifndef TONE_PLATFORM_SDL
        PostQuitMessage(0);
#endif
        return 0;
    default:
        break;
    }
#ifdef TONE_PLATFORM_SDL
    /* SDL has handled the window itself. */
    return 0;
#else
    /* Cases that `break` (other system commands such as move, size and
       close; cursors outside the client area) get the default handling. */
    return DefWindowProcA(window, message, wparam, lparam);
#endif
}
