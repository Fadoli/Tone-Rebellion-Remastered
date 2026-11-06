/* remake_sdl entry: SDL's main callbacks (SDL_MAIN_USE_CALLBACKS). SDL
   calls SDL_AppIterate in its own loop on the desktop and from the
   browser's frame callback under Emscripten, so both use the same code. */

static HWND g_sdl_window_token;
static char g_sdl_command_line[4096];
static int g_sdl_started;
static Uint64 g_sdl_tune_check;

#ifdef _WIN32
/* e2e_input_win.c: test input straight to menu_window_proc. */
void e2e_install_input_hook(void);
void e2e_deliver_input(unsigned message, uintptr_t wparam, intptr_t lparam);
void e2e_deliver_input(unsigned message, uintptr_t wparam, intptr_t lparam)
{
    if (g_sdl_window_token != NULL)
        (void)menu_window_proc(g_sdl_window_token, (UINT)message, (WPARAM)wparam,
                               (LPARAM)lparam);
}
#endif

/* The arguments as the single command line the game code parses (WinMain's
   lpCmdLine): arguments with spaces are quoted. */
static void sdl_join_arguments(int argc, char *argv[])
{
    int index;
    size_t used = 0;
    g_sdl_command_line[0] = '\0';
    for (index = 1; index < argc; ++index) {
        const char *argument = argv[index];
        int quote = strchr(argument, ' ') != NULL;
        int written = snprintf(g_sdl_command_line + used,
                               sizeof(g_sdl_command_line) - used,
                               quote ? "%s\"%s\"" : "%s%s",
                               used > 0 ? " " : "", argument);
        if (written < 0 || (size_t)written >= sizeof(g_sdl_command_line) - used) break;
        used += (size_t)written;
    }
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    int exit_code;
    (void)appstate;
    sdl_join_arguments(argc, argv);
    if (!app_load_content(g_sdl_command_line)) return SDL_APP_FAILURE;
    g_sdl_window_token = sdl_create_window();
#ifdef _WIN32
    if (getenv("TONE_REBELLION_E2E_STATE") != NULL &&
        getenv("TONE_REBELLION_E2E_STATE")[0] != 0)
        e2e_install_input_hook();
#endif
    if (g_sdl_window_token == NULL) {
        platform_message_box(NULL, SDL_GetError(), "Tone Rebellion remake - SDL", 1);
        return SDL_APP_FAILURE;
    }
    app_start(g_sdl_window_token, g_sdl_command_line);
    /* The dump set only renders: its window stays hidden. */
    if (strstr(g_sdl_command_line, "--bench") != NULL &&
        strstr(g_sdl_command_line, "--bench-dump-set") == NULL)
        SDL_ShowWindow(g_sdl_window);
    if (app_run_bench(g_sdl_window_token, g_sdl_command_line, &exit_code))
        return exit_code == 0 ? SDL_APP_SUCCESS : SDL_APP_FAILURE;
    /* The frame and paint clocks release the work; SDL_AppIterate sleeps
       until their next deadline, so SDL only caps the loop at 1000/s. */
    (void)SDL_SetHint(SDL_HINT_MAIN_CALLBACK_RATE, "1000");
    SDL_ShowWindow(g_sdl_window);
    (void)SDL_StartTextInput(g_sdl_window);
    g_sdl_tune_check = SDL_GetTicks();
    g_sdl_started = 1;
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    (void)appstate;
    if (!sdl_dispatch_event(g_sdl_window_token, event)) return SDL_APP_SUCCESS;
    return SDL_APP_CONTINUE;
}

/* The network sockets (WM_NET_SOCKET under Win32), the 20 Hz frame clock
   of WM_TIMER 1, the one-second tune check of WM_TIMER 2, the pointer's
   cursor and a repaint when something changed. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    unsigned due;
    (void)appstate;
    /* The loop sleeps until the next deadline itself (2 ms at most). */
    ui_wait_for_next_deadline(g_sdl_window_token);
    due = frame_clock_due();
    if (net_poll(g_sdl_window_token)) platform_invalidate(g_sdl_window_token);
    while (due-- != 0U) run_ui_frame(g_sdl_window_token, 1);
    if (render_interp_paint_due()) g_sdl_dirty = 1;
    if (ui_motion_tick(g_sdl_window_token)) g_sdl_dirty = 1;
    if (SDL_GetTicks() - g_sdl_tune_check >= 1000U) {
        g_sdl_tune_check = SDL_GetTicks();
        run_ui_frame(g_sdl_window_token, 2);
    }
    if (g_mouse_inside) update_interaction_cursor();
    if (g_sdl_dirty) sdl_redraw();
    return g_sdl_quit_requested ? SDL_APP_SUCCESS : SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    (void)appstate;
    (void)result;
    if (g_sdl_started) {
        (void)SDL_StopTextInput(g_sdl_window);
        /* WM_DESTROY: network shutdown, resume save, music stop. */
        (void)menu_window_proc(g_sdl_window_token, WM_DESTROY, 0, 0);
    }
    app_release_content();
    sdl_destroy_window();
}
