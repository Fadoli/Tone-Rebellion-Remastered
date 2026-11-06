/* Platform services, SDL3 shell (Web port step 2): the functions of
   ../win32/platform_win32.inc on SDL. The window parameter is ignored; the
   SDL window is the one sdl_app.inc creates. */

static SDL_Window *g_sdl_window;
/* Set when the frame must be composed and presented again. */
static int g_sdl_dirty = 1;
static int g_sdl_quit_requested;

static void platform_invalidate(HWND window)
{
    (void)window;
    g_sdl_dirty = 1;
}

static void platform_client_rect(HWND window, RECT *out)
{
    int width = 0;
    int height = 0;
    (void)window;
    if (g_sdl_window != NULL)
        (void)SDL_GetWindowSizeInPixels(g_sdl_window, &width, &height);
    out->left = 0;
    out->top = 0;
    out->right = width;
    out->bottom = height;
}

static int platform_window_focused(HWND window)
{
    (void)window;
    return g_sdl_window != NULL &&
        (SDL_GetWindowFlags(g_sdl_window) & SDL_WINDOW_INPUT_FOCUS) != 0;
}

/* Row-parallel helper for the presented-frame upscaler: splits [0, rows)
   over a few persistent worker threads plus the calling thread and returns
   when every slice is done. Falls back to one thread when none start. */
typedef void (*PlatformRowJob)(void *context, int y0, int y1);
enum { PLATFORM_MAX_WORKERS = 7 };
static SDL_Semaphore *g_pool_start[PLATFORM_MAX_WORKERS];
static SDL_Semaphore *g_pool_done;
static int g_pool_workers = -1;
static PlatformRowJob g_pool_job;
static void *g_pool_context;
static int g_pool_ranges[PLATFORM_MAX_WORKERS + 1][2];

static int SDLCALL platform_pool_worker(void *parameter)
{
    int index = (int)(intptr_t)parameter;
    for (;;) {
        SDL_WaitSemaphore(g_pool_start[index]);
        g_pool_job(g_pool_context, g_pool_ranges[index + 1][0], g_pool_ranges[index + 1][1]);
        SDL_SignalSemaphore(g_pool_done);
    }
    return 0;
}

static void platform_pool_init(void)
{
    int wanted, i;
    g_pool_workers = 0;
    wanted = SDL_GetNumLogicalCPUCores() - 1;
    if (wanted > PLATFORM_MAX_WORKERS) wanted = PLATFORM_MAX_WORKERS;
    if (wanted <= 0) return;
    g_pool_done = SDL_CreateSemaphore(0);
    if (g_pool_done == NULL) return;
    for (i = 0; i < wanted; ++i) {
        SDL_Thread *thread;
        g_pool_start[i] = SDL_CreateSemaphore(0);
        if (g_pool_start[i] == NULL) break;
        thread = SDL_CreateThread(platform_pool_worker, "upscale", (void *)(intptr_t)i);
        if (thread == NULL) break;
        SDL_DetachThread(thread);
        g_pool_workers = i + 1;
    }
}

static void platform_parallel_rows(PlatformRowJob job, void *context, int rows)
{
    int parts, i;
    if (rows <= 0) return;
    if (g_pool_workers < 0) platform_pool_init();
    parts = g_pool_workers + 1;
    if (parts > rows / 16) parts = rows / 16;
    if (parts <= 1) {
        job(context, 0, rows);
        return;
    }
    g_pool_job = job;
    g_pool_context = context;
    for (i = 0; i < parts; ++i) {
        g_pool_ranges[i][0] = rows * i / parts;
        g_pool_ranges[i][1] = rows * (i + 1) / parts;
    }
    for (i = 1; i < parts; ++i) SDL_SignalSemaphore(g_pool_start[i - 1]);
    job(context, g_pool_ranges[0][0], g_pool_ranges[0][1]);
    for (i = 1; i < parts; ++i) SDL_WaitSemaphore(g_pool_done);
}

static int platform_ctrl_down(void)
{
    return (SDL_GetModState() & SDL_KMOD_CTRL) != 0;
}

static int platform_shift_down(void)
{
    return (SDL_GetModState() & SDL_KMOD_SHIFT) != 0;
}

static void platform_request_close(HWND window)
{
    (void)window;
    g_sdl_quit_requested = 1;
}

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

static void platform_sleep_ms(uint32_t milliseconds)
{
    SDL_Delay(milliseconds);
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

/* OK/Cancel question; returns 1 for OK. */
static int platform_confirm(HWND window, const char *text, const char *caption)
{
    static const SDL_MessageBoxButtonData buttons[2] = {
        {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "OK"},
        {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "Cancel"}
    };
    SDL_MessageBoxData data;
    int choice = 0;
    (void)window;
    memset(&data, 0, sizeof(data));
    data.flags = SDL_MESSAGEBOX_WARNING;
    data.window = g_sdl_window;
    data.title = caption;
    data.message = text;
    data.numbuttons = 2;
    data.buttons = buttons;
    if (!SDL_ShowMessageBox(&data, &choice)) return 1;
    return choice == 1;
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

/* The original game's cursors, decoded from FLOAT.EXE's resources as bytes
   (pe_cursor.c); SDL needs the video subsystem, so they are created on
   first use. */
enum { PLATFORM_CURSOR_MAX = 32 };
static SDL_Cursor *g_platform_cursors[PLATFORM_CURSOR_MAX];
static PeCursor g_platform_cursor_images[PLATFORM_CURSOR_MAX];
static SDL_Cursor *g_platform_arrow;
static SDL_Cursor *g_platform_current_cursor;

static void platform_load_cursors(const char *exe_path, const WORD *ids,
                                  unsigned count)
{
    uint8_t *image;
    size_t size;
    unsigned slot;
    if (!pe_image_load(exe_path, &image, &size)) return;
    for (slot = 0; slot < count && slot < PLATFORM_CURSOR_MAX; ++slot)
        (void)pe_cursor_decode(image, size, ids[slot],
                               &g_platform_cursor_images[slot]);
    pe_image_free(image);
}

static void platform_set_cursor(int slot)
{
    SDL_Cursor *cursor = NULL;
    if (slot >= 0 && slot < PLATFORM_CURSOR_MAX) {
        PeCursor *image = &g_platform_cursor_images[slot];
        if (g_platform_cursors[slot] == NULL && image->pixels != NULL) {
            SDL_Surface *surface = SDL_CreateSurfaceFrom(
                image->width, image->height, SDL_PIXELFORMAT_ARGB8888,
                image->pixels, image->width * (int)sizeof(uint32_t));
            if (surface != NULL) {
                g_platform_cursors[slot] = SDL_CreateColorCursor(
                    surface, image->hotspot_x, image->hotspot_y);
                SDL_DestroySurface(surface);
            }
        }
        cursor = g_platform_cursors[slot];
    }
    if (cursor == NULL) {
        if (g_platform_arrow == NULL)
            g_platform_arrow = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
        cursor = g_platform_arrow;
    }
    if (cursor != NULL && cursor != g_platform_current_cursor) {
        (void)SDL_SetCursor(cursor);
        g_platform_current_cursor = cursor;
    }
}

/* Before SDL_Quit. */
static void platform_free_cursors(void)
{
    unsigned slot;
    for (slot = 0; slot < PLATFORM_CURSOR_MAX; ++slot) {
        if (g_platform_cursors[slot] != NULL) SDL_DestroyCursor(g_platform_cursors[slot]);
        g_platform_cursors[slot] = NULL;
        pe_cursor_free(&g_platform_cursor_images[slot]);
    }
    if (g_platform_arrow != NULL) SDL_DestroyCursor(g_platform_arrow);
    g_platform_arrow = NULL;
    g_platform_current_cursor = NULL;
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

/* A file under the save directory was written. In the browser /tone lives
   in memory until the page copies it to IndexedDB (web/shell.html,
   toneStorageChanged); elsewhere the write is already on disk. */
static void platform_storage_changed(void)
{
#ifdef __EMSCRIPTEN__
    EM_ASM({ if (Module.toneStorageChanged) Module.toneStorageChanged(); });
#endif
}

/* SDL_GetBasePath ends with a separator; the callers add their own. In the
   browser the page puts the player's game files in /tone (THING1, THING2)
   and keeps /tone/saves in IndexedDB: the usual search then finds them as
   if /tone held the executable. */
static int platform_executable_directory(char *out, size_t capacity)
{
#ifdef __EMSCRIPTEN__
    const char *base = "/tone";
#else
    const char *base = SDL_GetBasePath();
#endif
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
        if (snprintf(path, sizeof(path), "%s/%s", directory, names[index]) <
                (int)sizeof(path) &&
            platform_path_kind(path) == PLATFORM_PATH_FILE)
            result = visit(path, context);
    }
    SDL_free(names);
    return result;
}
