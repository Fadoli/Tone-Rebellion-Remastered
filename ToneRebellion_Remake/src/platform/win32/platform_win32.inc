/* Platform services, Win32 shell (TODO_WEB.md step 2). remake_sdl defines
   the same functions in ../sdl/sdl_platform.inc. The window parameter stays
   an HWND until the remaining Win32 uses (cursors, sockets) move too. */

/* Milliseconds since an arbitrary start; wraps like GetTickCount. */
static uint32_t platform_ticks_ms(void)
{
    return (uint32_t)GetTickCount();
}

/* High-resolution counter and its ticks per second. */
static uint64_t platform_counter(void)
{
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);
    return (uint64_t)now.QuadPart;
}

static uint64_t platform_counter_frequency(void)
{
    static LARGE_INTEGER frequency;
    if (frequency.QuadPart == 0) QueryPerformanceFrequency(&frequency);
    return (uint64_t)frequency.QuadPart;
}

static void platform_message_box(HWND window, const char *text,
                                 const char *caption, int error)
{
    (void)MessageBoxA(window, text, caption,
                      MB_OK | (error ? MB_ICONERROR : 0U));
}

static void platform_set_title(HWND window, const char *title)
{
    (void)SetWindowTextA(window, title);
}

/* Keeps mouse messages coming while a button is held outside the window. */
static void platform_capture_mouse(HWND window, int capture)
{
    if (capture) (void)SetCapture(window);
    else (void)ReleaseCapture();
}
