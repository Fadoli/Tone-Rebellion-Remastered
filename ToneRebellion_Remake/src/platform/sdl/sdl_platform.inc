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

enum { PLATFORM_PATH_MISSING, PLATFORM_PATH_FILE, PLATFORM_PATH_DIRECTORY };

static int platform_path_kind(const char *path)
{
    SDL_PathInfo info;
    if (!SDL_GetPathInfo(path, &info)) return PLATFORM_PATH_MISSING;
    return info.type == SDL_PATHTYPE_DIRECTORY ? PLATFORM_PATH_DIRECTORY
                                               : PLATFORM_PATH_FILE;
}

static void platform_create_directory(const char *path)
{
    (void)SDL_CreateDirectory(path);
}

static int platform_rename_replace(const char *from, const char *to)
{
    return SDL_RenamePath(from, to);
}

/* SDL_GetBasePath ends with a separator; the callers add their own. */
static int platform_executable_directory(char *out, size_t capacity)
{
    const char *base = SDL_GetBasePath();
    size_t length;
    if (base == NULL) return 0;
    length = strlen(base);
    while (length > 0 && (base[length - 1] == '\\' || base[length - 1] == '/'))
        --length;
    if (length == 0 || length >= capacity) return 0;
    (void)memcpy(out, base, length);
    out[length] = '\0';
    return 1;
}

static int platform_environment(const char *name, char *out, size_t capacity)
{
    const char *value = SDL_getenv(name);
    size_t length = value != NULL ? strlen(value) : 0;
    if (length == 0 || length >= capacity) return 0;
    (void)memcpy(out, value, length + 1);
    return 1;
}

typedef struct PlatformDateTime {
    int year, month, day;  /* month 1..12 */
    int hour, minute, second;
    int day_of_week;       /* 0 = Sunday */
} PlatformDateTime;

static int platform_file_time(const char *path, PlatformDateTime *out)
{
    SDL_PathInfo info;
    SDL_DateTime time;
    if (!SDL_GetPathInfo(path, &info) ||
        !SDL_TimeToDateTime(info.modify_time, &time, true)) return 0;
    out->year = time.year;
    out->month = time.month;
    out->day = time.day;
    out->hour = time.hour;
    out->minute = time.minute;
    out->second = time.second;
    out->day_of_week = time.day_of_week;
    return 1;
}

static int platform_each_file(const char *directory, const char *suffix,
                              int (*visit)(const char *path, void *context),
                              void *context)
{
    char pattern[64];
    char path[MAX_PATH];
    char **names;
    int count = 0;
    int index;
    int result = 0;
    if (snprintf(pattern, sizeof(pattern), "*%s", suffix) >= (int)sizeof(pattern))
        return 0;
    names = SDL_GlobDirectory(directory, pattern, SDL_GLOB_CASEINSENSITIVE, &count);
    if (names == NULL) return 0;
    for (index = 0; index < count && result == 0; ++index) {
        if (snprintf(path, sizeof(path), "%s\\%s", directory, names[index]) <
                (int)sizeof(path) &&
            platform_path_kind(path) == PLATFORM_PATH_FILE)
            result = visit(path, context);
    }
    SDL_free(names);
    return result;
}
