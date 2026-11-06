/* Platform services, Win32 shell (Web port step 2). remake_sdl defines
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

static void platform_sleep_ms(uint32_t milliseconds)
{
    Sleep(milliseconds);
}

static void platform_message_box(HWND window, const char *text,
                                 const char *caption, int error)
{
    (void)MessageBoxA(window, text, caption,
                      MB_OK | (error ? MB_ICONERROR : 0U));
}

/* OK/Cancel question; returns 1 for OK. */
static int platform_confirm(HWND window, const char *text, const char *caption)
{
    return MessageBoxA(window, text, caption, MB_OKCANCEL | MB_ICONWARNING) == IDOK;
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

/* Asks for the frame to be composed and presented again. */
static void platform_invalidate(HWND window)
{
    (void)InvalidateRect(window, NULL, FALSE);
}

/* The window's drawable area in pixels, as a RECT at (0, 0). */
static void platform_client_rect(HWND window, RECT *out)
{
    (void)GetClientRect(window, out);
}

static int platform_window_focused(HWND window)
{
    return GetForegroundWindow() == window;
}

/* Row-parallel helper for the presented-frame upscaler: splits [0, rows)
   over a few persistent worker threads plus the calling thread and returns
   when every slice is done. Falls back to one thread when none start. */
typedef void (*PlatformRowJob)(void *context, int y0, int y1);
enum { PLATFORM_MAX_WORKERS = 7 };
static HANDLE g_pool_start[PLATFORM_MAX_WORKERS];
static HANDLE g_pool_done;
static int g_pool_workers = -1;
static PlatformRowJob g_pool_job;
static void *g_pool_context;
static int g_pool_ranges[PLATFORM_MAX_WORKERS + 1][2];

static DWORD WINAPI platform_pool_worker(LPVOID parameter)
{
    int index = (int)(INT_PTR)parameter;
    for (;;) {
        (void)WaitForSingleObject(g_pool_start[index], INFINITE);
        g_pool_job(g_pool_context, g_pool_ranges[index + 1][0], g_pool_ranges[index + 1][1]);
        (void)ReleaseSemaphore(g_pool_done, 1, NULL);
    }
    return 0;
}

static void platform_pool_init(void)
{
    SYSTEM_INFO info;
    int wanted, i;
    g_pool_workers = 0;
    GetSystemInfo(&info);
    wanted = (int)info.dwNumberOfProcessors - 1;
    if (wanted > PLATFORM_MAX_WORKERS) wanted = PLATFORM_MAX_WORKERS;
    if (wanted <= 0) return;
    g_pool_done = CreateSemaphoreA(NULL, 0, PLATFORM_MAX_WORKERS, NULL);
    if (g_pool_done == NULL) return;
    for (i = 0; i < wanted; ++i) {
        HANDLE thread;
        g_pool_start[i] = CreateSemaphoreA(NULL, 0, 1, NULL);
        if (g_pool_start[i] == NULL) break;
        thread = CreateThread(NULL, 0, platform_pool_worker, (LPVOID)(INT_PTR)i, 0, NULL);
        if (thread == NULL) break;
        CloseHandle(thread);
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
    for (i = 1; i < parts; ++i) (void)ReleaseSemaphore(g_pool_start[i - 1], 1, NULL);
    job(context, g_pool_ranges[0][0], g_pool_ranges[0][1]);
    for (i = 1; i < parts; ++i) (void)WaitForSingleObject(g_pool_done, INFINITE);
}

static int platform_ctrl_down(void)
{
    return (GetKeyState(VK_CONTROL) & 0x8000) != 0;
}

static int platform_shift_down(void)
{
    return (GetKeyState(VK_SHIFT) & 0x8000) != 0;
}

/* Closes the window through the normal shutdown path (WM_DESTROY). */
static void platform_request_close(HWND window)
{
    (void)PostMessageA(window, WM_CLOSE, 0, 0);
}

/* The original game's cursors, read from FLOAT.EXE as a data file (never
   executed); slot n is cursor group ids[n]. */
enum { PLATFORM_CURSOR_MAX = 32 };
static HMODULE g_platform_cursor_module;
static HCURSOR g_platform_cursors[PLATFORM_CURSOR_MAX];

static void platform_load_cursors(const char *exe_path, const WORD *ids,
                                  unsigned count)
{
    unsigned slot;
    g_platform_cursor_module = LoadLibraryExA(exe_path, NULL,
                                              LOAD_LIBRARY_AS_DATAFILE);
    if (g_platform_cursor_module == NULL) return;
    for (slot = 0; slot < count && slot < PLATFORM_CURSOR_MAX; ++slot)
        g_platform_cursors[slot] = (HCURSOR)LoadImageA(
            g_platform_cursor_module, MAKEINTRESOURCEA(ids[slot]),
            IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE);
}

/* Slot of platform_load_cursors, or the system arrow when it has none. */
static void platform_set_cursor(int slot)
{
    if (slot >= 0 && slot < PLATFORM_CURSOR_MAX &&
        g_platform_cursors[slot] != NULL) {
        SetCursor(g_platform_cursors[slot]);
        return;
    }
    SetCursor(LoadCursorA(NULL, IDC_ARROW));
}

static void platform_free_cursors(void)
{
    unsigned slot;
    for (slot = 0; slot < PLATFORM_CURSOR_MAX; ++slot) {
        if (g_platform_cursors[slot] != NULL) DestroyCursor(g_platform_cursors[slot]);
        g_platform_cursors[slot] = NULL;
    }
    if (g_platform_cursor_module != NULL) FreeLibrary(g_platform_cursor_module);
    g_platform_cursor_module = NULL;
}

enum { PLATFORM_PATH_MISSING, PLATFORM_PATH_FILE, PLATFORM_PATH_DIRECTORY };

static int platform_path_kind(const char *path)
{
    DWORD attributes = GetFileAttributesA(path);
    if (attributes == INVALID_FILE_ATTRIBUTES) return PLATFORM_PATH_MISSING;
    return (attributes & FILE_ATTRIBUTE_DIRECTORY) != 0 ? PLATFORM_PATH_DIRECTORY
                                                        : PLATFORM_PATH_FILE;
}

/* Creates one directory level; an existing directory is not an error. */
static void platform_create_directory(const char *path)
{
    (void)CreateDirectoryA(path, NULL);
}

/* Replaces `to` with `from`. */
static int platform_rename_replace(const char *from, const char *to)
{
    return MoveFileExA(from, to, MOVEFILE_REPLACE_EXISTING) != 0;
}

/* A file under the save directory was written; nothing to flush here. */
static void platform_storage_changed(void)
{
}

/* The executable's directory, without a trailing separator. */
static int platform_executable_directory(char *out, size_t capacity)
{
    DWORD length = GetModuleFileNameA(NULL, out, (DWORD)capacity);
    char *slash;
    if (length == 0 || length >= capacity) return 0;
    slash = strrchr(out, '\\');
    if (slash == NULL) return 0;
    *slash = '\0';
    return 1;
}

/* Value of an environment variable; 0 when unset, empty or too long. */
static int platform_environment(const char *name, char *out, size_t capacity)
{
    DWORD length = GetEnvironmentVariableA(name, out, (DWORD)capacity);
    return length > 0 && length < capacity;
}

typedef struct PlatformDateTime {
    int year, month, day;  /* month 1..12 */
    int hour, minute, second;
    int day_of_week;       /* 0 = Sunday */
} PlatformDateTime;

/* Last write time of a file, in local time with the daylight-saving rule
   of that date (FileTimeToLocalFileTime would apply today's). */
static int platform_file_time(const char *path, PlatformDateTime *out)
{
    WIN32_FILE_ATTRIBUTE_DATA attributes;
    SYSTEMTIME utc;
    SYSTEMTIME time;
    if (!GetFileAttributesExA(path, GetFileExInfoStandard, &attributes) ||
        !FileTimeToSystemTime(&attributes.ftLastWriteTime, &utc) ||
        !SystemTimeToTzSpecificLocalTime(NULL, &utc, &time)) return 0;
    out->year = time.wYear;
    out->month = time.wMonth;
    out->day = time.wDay;
    out->hour = time.wHour;
    out->minute = time.wMinute;
    out->second = time.wSecond;
    out->day_of_week = time.wDayOfWeek;
    return 1;
}

/* Calls visit(full path) for each file of `directory` named *`suffix`
   (case-insensitive) until it returns non-zero; returns that value. */
static int platform_each_file(const char *directory, const char *suffix,
                              int (*visit)(const char *path, void *context),
                              void *context)
{
    WIN32_FIND_DATAA data;
    char pattern[MAX_PATH];
    char path[MAX_PATH];
    HANDLE handle;
    int result = 0;
    if (snprintf(pattern, sizeof(pattern), "%s\\*%s", directory, suffix) >=
        (int)sizeof(pattern)) return 0;
    handle = FindFirstFileA(pattern, &data);
    if (handle == INVALID_HANDLE_VALUE) return 0;
    do {
        if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0 &&
            snprintf(path, sizeof(path), "%s\\%s", directory, data.cFileName) <
                (int)sizeof(path))
            result = visit(path, context);
    } while (result == 0 && FindNextFileA(handle, &data));
    FindClose(handle);
    return result;
}
