/* Platform services, SDL3 shell (TODO_WEB.md step 2): the functions of
   ../win32/platform_win32.inc on SDL. The window parameter is ignored; the
   SDL window is the one sdl_app.inc creates. */

static SDL_Window *g_sdl_window;

static uint32_t platform_ticks_ms(void)
{
    return (uint32_t)SDL_GetTicks();
}

static uint64_t platform_counter(void)
{
    return SDL_GetPerformanceCounter();
}

static uint64_t platform_counter_frequency(void)
{
    return SDL_GetPerformanceFrequency();
}

/* Also works before SDL_Init and without a window (data errors). */
static void platform_message_box(HWND window, const char *text,
                                 const char *caption, int error)
{
    (void)window;
    (void)SDL_ShowSimpleMessageBox(error ? SDL_MESSAGEBOX_ERROR
                                         : SDL_MESSAGEBOX_INFORMATION,
                                   caption, text, g_sdl_window);
}

static void platform_set_title(HWND window, const char *title)
{
    (void)window;
    if (g_sdl_window != NULL) (void)SDL_SetWindowTitle(g_sdl_window, title);
}

static void platform_capture_mouse(HWND window, int capture)
{
    (void)window;
    (void)SDL_CaptureMouse(capture != 0);
}
