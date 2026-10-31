/* Benchmark mode (--bench): a scripted session on a fixed seed that runs
   the real UI frame, back-buffer composition and window present back to
   back, times each phase and, with --bench-profile, samples the main
   thread's call stack. Results go to a text report; bench/hotspots.js
   resolves the samples to function names. No effect without --bench.

   Options: --bench-frames N (default 600), --bench-warmup N ticks (300),
   --bench-scenario idle|crowd|battle, --bench-world N, --bench-paced
   (wait for the 50 ms frame clock like the game), --bench-out FILE
   (default bench_report.txt next to the executable), --bench-profile,
   --bench-dump FILE (the last composed frame as a 640x480 BMP),
   --bench-screen title|newgame|map. */

enum { BENCH_PHASE_IDLE, BENCH_PHASE_SIM, BENCH_PHASE_RENDER,
       BENCH_PHASE_PRESENT, BENCH_PHASE_COUNT };
enum { BENCH_STACK_DEPTH = 24, BENCH_MAX_SAMPLES = 400000 };

typedef struct BenchSample {
    uint8_t phase;
    uint8_t depth;
    DWORD frames[BENCH_STACK_DEPTH];
} BenchSample;

static volatile LONG g_bench_phase;
static volatile LONG g_bench_sampling;
static volatile LONG g_bench_stop;
static BenchSample *g_bench_samples;
static volatile LONG g_bench_sample_count;
static HANDLE g_bench_main_thread;
static DWORD g_bench_stack_low;
static DWORD g_bench_stack_high;

static const char *const g_bench_phase_names[BENCH_PHASE_COUNT] = {
    "idle", "sim", "render", "present"
};

/* Stack walk over the EBP chain of the suspended main thread. Frames must
   stay inside its stack and grow upwards; system DLLs keep frame pointers,
   the bench build adds -fno-omit-frame-pointer for ours. */
static DWORD WINAPI bench_sampler_thread(LPVOID parameter)
{
    (void)parameter;
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
    while (!g_bench_stop) {
        Sleep(1);
        if (!g_bench_sampling) continue;
        if (g_bench_sample_count >= BENCH_MAX_SAMPLES) continue;
        if (SuspendThread(g_bench_main_thread) == (DWORD)-1) continue;
        {
            CONTEXT context;
            BenchSample *sample = &g_bench_samples[g_bench_sample_count];
            ZeroMemory(&context, sizeof(context));
            context.ContextFlags = CONTEXT_CONTROL | CONTEXT_INTEGER;
            if (GetThreadContext(g_bench_main_thread, &context)) {
                DWORD frame = context.Ebp;
                unsigned depth = 0;
                sample->phase = (uint8_t)g_bench_phase;
                sample->frames[depth++] = context.Eip;
                while (depth < BENCH_STACK_DEPTH &&
                       frame >= g_bench_stack_low &&
                       frame + 8U <= g_bench_stack_high &&
                       (frame & 3U) == 0U) {
                    const DWORD *record = (const DWORD *)(uintptr_t)frame;
                    DWORD next = record[0];
                    sample->frames[depth++] = record[1];
                    if (next <= frame) break;
                    frame = next;
                }
                sample->depth = (uint8_t)depth;
                ++g_bench_sample_count;
            }
        }
        ResumeThread(g_bench_main_thread);
    }
    return 0;
}

/* Nearest export at or below address in a loaded system module, read from
   its in-memory export directory. */
static const char *bench_nearest_export(HMODULE module, DWORD address,
                                        DWORD *out_offset)
{
    const unsigned char *base = (const unsigned char *)module;
    const IMAGE_DOS_HEADER *dos = (const IMAGE_DOS_HEADER *)base;
    const IMAGE_NT_HEADERS *nt;
    const IMAGE_DATA_DIRECTORY *directory;
    const IMAGE_EXPORT_DIRECTORY *exports;
    const DWORD *functions;
    const DWORD *names;
    const WORD *ordinals;
    DWORD rva = address - (DWORD)(uintptr_t)module;
    DWORD best_rva = 0;
    const char *best = NULL;
    DWORD size;
    DWORD i;
    /* Stack garbage can point into any mapped image, including ones not
       laid out as loaded modules: bound every table by SizeOfImage. */
    if (dos->e_magic != IMAGE_DOS_SIGNATURE || dos->e_lfanew <= 0 ||
        dos->e_lfanew > 4096) return NULL;
    nt = (const IMAGE_NT_HEADERS *)(base + dos->e_lfanew);
    if (nt->Signature != IMAGE_NT_SIGNATURE) return NULL;
    size = nt->OptionalHeader.SizeOfImage;
    if (rva >= size) return NULL;
    directory = &nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
    if (directory->VirtualAddress == 0 ||
        directory->VirtualAddress > size - sizeof(*exports)) return NULL;
    exports = (const IMAGE_EXPORT_DIRECTORY *)(base + directory->VirtualAddress);
    if (exports->AddressOfFunctions >= size ||
        exports->NumberOfFunctions > (size - exports->AddressOfFunctions) / 4U ||
        exports->AddressOfNames >= size ||
        exports->NumberOfNames > (size - exports->AddressOfNames) / 4U ||
        exports->AddressOfNameOrdinals >= size ||
        exports->NumberOfNames >
            (size - exports->AddressOfNameOrdinals) / 2U) return NULL;
    functions = (const DWORD *)(base + exports->AddressOfFunctions);
    names = (const DWORD *)(base + exports->AddressOfNames);
    ordinals = (const WORD *)(base + exports->AddressOfNameOrdinals);
    for (i = 0; i < exports->NumberOfNames; ++i) {
        DWORD function_rva;
        if (ordinals[i] >= exports->NumberOfFunctions || names[i] >= size)
            continue;
        function_rva = functions[ordinals[i]];
        if (function_rva <= rva && function_rva >= best_rva) {
            best_rva = function_rva;
            best = (const char *)(base + names[i]);
        }
    }
    *out_offset = rva - best_rva;
    return best;
}

/* Our own frames are written as image offsets for bench/hotspots.js; the
   others as module!export+offset, memoised per address (export scans are
   slow and the same few system addresses repeat in every sample). */
enum { BENCH_FRAME_CACHE = 8192 };
typedef struct BenchFrameName {
    DWORD address;
    char text[96];
} BenchFrameName;
static BenchFrameName *g_bench_frame_names;

static void bench_write_frame(FILE *file, DWORD address)
{
    HMODULE module = NULL;
    HMODULE self = GetModuleHandleA(NULL);
    const IMAGE_NT_HEADERS *nt = (const IMAGE_NT_HEADERS *)
        ((const unsigned char *)self + ((const IMAGE_DOS_HEADER *)self)->e_lfanew);
    DWORD self_base = (DWORD)(uintptr_t)self;
    BenchFrameName *entry;
    char path[MAX_PATH];
    const char *name;
    const char *symbol;
    DWORD offset = 0;
    if (address >= self_base &&
        address - self_base < nt->OptionalHeader.SizeOfImage) {
        fprintf(file, " @%lx", (unsigned long)(address - self_base));
        return;
    }
    if (g_bench_frame_names == NULL)
        g_bench_frame_names = (BenchFrameName *)calloc(BENCH_FRAME_CACHE,
                                                       sizeof(BenchFrameName));
    if (g_bench_frame_names == NULL) return;
    entry = &g_bench_frame_names[(address * 2654435761U) >> 19];
    if (entry->address == address && entry->text[0] != '\0') {
        fprintf(file, " %s", entry->text);
        return;
    }
    /* A module's pages share its image base as allocation base. */
    {
        MEMORY_BASIC_INFORMATION memory;
        if (VirtualQuery((LPCVOID)(uintptr_t)address, &memory,
                         sizeof(memory)) == sizeof(memory) &&
            memory.Type == MEM_IMAGE)
            module = (HMODULE)memory.AllocationBase;
    }
    if (module == NULL) {
        (void)snprintf(entry->text, sizeof(entry->text), "?%08lx",
                       (unsigned long)address);
    } else {
        /* Only loaded modules: a data-file mapping (FLOAT.EXE's cursors)
           has no module name and is not laid out by RVA. */
        int loaded = GetModuleFileNameA(module, path, sizeof(path)) != 0;
        if (!loaded) path[0] = '\0';
        name = strrchr(path, '\\');
        name = name != NULL ? name + 1 : path;
        symbol = loaded ? bench_nearest_export(module, address, &offset) : NULL;
        if (symbol != NULL)
            (void)snprintf(entry->text, sizeof(entry->text), "%s!%s+%lx",
                           name, symbol, (unsigned long)offset);
        else
            (void)snprintf(entry->text, sizeof(entry->text), "%s!?", name);
    }
    entry->address = address;
    fprintf(file, " %s", entry->text);
}

static double bench_seconds(LONGLONG ticks)
{
    static LARGE_INTEGER frequency;
    if (frequency.QuadPart == 0) QueryPerformanceFrequency(&frequency);
    return (double)ticks / (double)frequency.QuadPart;
}

static LONGLONG bench_now(void)
{
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);
    return now.QuadPart;
}

static LONGLONG bench_filetime(const FILETIME *time)
{
    return ((LONGLONG)time->dwHighDateTime << 32) | time->dwLowDateTime;
}

/* User + kernel CPU of the main thread, in 100 ns units. */
static LONGLONG bench_thread_cpu(void)
{
    FILETIME created, exited, kernel, user;
    if (!GetThreadTimes(GetCurrentThread(), &created, &exited, &kernel, &user))
        return 0;
    return bench_filetime(&kernel) + bench_filetime(&user);
}

static LONGLONG bench_process_cpu(void)
{
    FILETIME created, exited, kernel, user;
    if (!GetProcessTimes(GetCurrentProcess(), &created, &exited, &kernel, &user))
        return 0;
    return bench_filetime(&kernel) + bench_filetime(&user);
}

static int bench_compare_double(const void *a, const void *b)
{
    double x = *(const double *)a;
    double y = *(const double *)b;
    return x < y ? -1 : x > y ? 1 : 0;
}

/* Copies a player's idle starting workers onto the viewed island, spread
   over its floater range, until the island holds `count` of them. They
   start unlinked and wandering, exactly like the originals. */
static void bench_clone_workers(uint8_t owner, uint8_t island, unsigned count)
{
    GameFloaterStart model;
    unsigned have = 0;
    unsigned n;
    int found = 0;
    /* The Hall-centred X window of the viewing player on that island. */
    int min_x = g_game_session.islands[island]
        .floater_min_x[g_menu.selected_tribe];
    int max_x = g_game_session.islands[island]
        .floater_max_x[g_menu.selected_tribe];
    for (n = 0; n < g_game_session.floater_count; ++n) {
        const GameFloaterStart *floater = &g_game_session.floaters[n];
        if (!game_session_floater_is_active(floater) ||
            floater->owner_slot != owner) continue;
        if (!found) {
            model = *floater;
            found = 1;
        }
        if (floater->island_index == island) ++have;
    }
    if (!found) return;
    if (max_x <= min_x) max_x = min_x + 1;
    model.island_index = island;
    model.order_target_island = island;
    model.order_source_island = island;
    while (have < count &&
           g_game_session.floater_count < GAME_SESSION_MAX_FLOATERS) {
        GameFloaterStart *clone =
            &g_game_session.floaters[g_game_session.floater_count];
        *clone = model;
        clone->x = (uint16_t)(min_x + (int)((have * 7919U) %
                                            (unsigned)(max_x - min_x)));
        clone->destination_x = clone->x;
        clone->animation_seed = (uint8_t)(have * 37U);
        ++g_game_session.floater_count;
        ++have;
    }
}

static int bench_open_home_island(HWND window)
{
    const WorldDefinition *world = &g_menu.world_map.worlds[g_menu.world_index];
    int island;
    unsigned n;
    /* The island holding the player's first floater is the start island. */
    for (n = 0; n < g_game_session.floater_count; ++n) {
        const GameFloaterStart *floater = &g_game_session.floaters[n];
        if (game_session_floater_is_active(floater) &&
            floater->owner_slot == (uint8_t)g_menu.selected_tribe &&
            open_island_view(window, floater->island_index)) return 1;
    }
    for (island = 0; island < world->island_count; ++island)
        if (open_island_view(window, island)) return 1;
    return 0;
}

static void bench_pump_messages(void)
{
    MSG message;
    while (PeekMessageA(&message, NULL, 0, 0, PM_REMOVE)) {
        if (message.message == WM_PAINT) {
            ValidateRect(message.hwnd, NULL);
            continue;
        }
        TranslateMessage(&message);
        DispatchMessageA(&message);
    }
}

/* Writes the 640x480 back buffer as a top-down 32-bit BMP. */
static void bench_dump_back_buffer(const char *path)
{
    BITMAPFILEHEADER file_header;
    BITMAPINFOHEADER info;
    DWORD bytes = LOGICAL_WIDTH * LOGICAL_HEIGHT * 4U;
    FILE *file = fopen(path, "wb");
    if (file == NULL || g_paint_buffer_pixels == NULL) {
        if (file != NULL) fclose(file);
        return;
    }
    (void)GdiFlush();
    ZeroMemory(&file_header, sizeof(file_header));
    ZeroMemory(&info, sizeof(info));
    file_header.bfType = 0x4d42;
    file_header.bfOffBits = sizeof(file_header) + sizeof(info);
    file_header.bfSize = file_header.bfOffBits + bytes;
    info.biSize = sizeof(info);
    info.biWidth = LOGICAL_WIDTH;
    info.biHeight = -LOGICAL_HEIGHT;
    info.biPlanes = 1;
    info.biBitCount = 32;
    info.biCompression = BI_RGB;
    fwrite(&file_header, sizeof(file_header), 1, file);
    fwrite(&info, sizeof(info), 1, file);
    fwrite(g_paint_buffer_pixels, bytes, 1, file);
    fclose(file);
}

static unsigned bench_option(const char *command_line, const char *name,
                             unsigned fallback)
{
    char value[32];
    if (!command_line_value(command_line, name, value, sizeof(value)))
        return fallback;
    return (unsigned)strtoul(value, NULL, 10);
}

/* Runs the benchmark and returns the process exit code. */
static int bench_run(HWND window, const char *command_line)
{
    char scenario[32] = "idle";
    char out_path[MAX_PATH];
    char error[256];
    unsigned frames = bench_option(command_line, "--bench-frames", 600U);
    unsigned warmup = bench_option(command_line, "--bench-warmup", 300U);
    int paced = strstr(command_line, "--bench-paced") != NULL;
    int profile = strstr(command_line, "--bench-profile") != NULL;
    double *frame_ms;
    double phase_total[BENCH_PHASE_COUNT] = {0};
    double phase_max[BENCH_PHASE_COUNT] = {0};
    LONGLONG wall_start, wall_end, thread_cpu_start, thread_cpu_end;
    LONGLONG process_cpu_start, process_cpu_end;
    HANDLE sampler = NULL;
    FILE *file;
    unsigned frame;
    unsigned active = 0;
    int bench_screen;
    RECT client;
    HDC screen;

    if (frames == 0U) frames = 1U;
    (void)command_line_value(command_line, "--bench-scenario", scenario,
                             sizeof(scenario));
    if (!command_line_value(command_line, "--bench-out", out_path,
                            sizeof(out_path))) {
        DWORD length = GetModuleFileNameA(NULL, out_path, sizeof(out_path));
        char *slash = length != 0 ? strrchr(out_path, '\\') : NULL;
        if (slash == NULL) out_path[0] = '\0';
        else slash[1] = '\0';
        strncat(out_path, "bench_report.txt",
                sizeof(out_path) - strlen(out_path) - 1U);
    }

    /* Fixed setup: world, tribe 0, easiest difficulty, constant seed. */
    g_menu.world_index = (int)bench_option(command_line, "--bench-world", 0U);
    if (g_menu.world_index >= g_menu.world_map.world_count) g_menu.world_index = 0;
    g_menu.selected_tribe = 0;
    g_menu.difficulty = 0;
    g_random_state = 0x13572468U;
    g_sim_speed = 1U;
    if (!load_game_session_for_selected_world(error, sizeof(error))) {
        MessageBoxA(window, error, "Tone Rebellion remake - bench", MB_OK);
        return 1;
    }
    g_menu.setup_accepted = 1;
    if (!bench_open_home_island(window)) {
        MessageBoxA(window, "No enterable island.", "Tone Rebellion remake - bench",
                    MB_OK);
        return 1;
    }
    if (strcmp(scenario, "crowd") == 0 || strcmp(scenario, "battle") == 0) {
        uint8_t island = (uint8_t)g_menu.selected_map_island;
        bench_clone_workers((uint8_t)g_menu.selected_tribe, island, 96U);
        if (strcmp(scenario, "battle") == 0) {
            uint8_t owner;
            for (owner = 0; owner < GAME_START_PLAYER_COUNT; ++owner)
                if (owner != (uint8_t)g_menu.selected_tribe)
                    bench_clone_workers(owner, island, 24U);
        }
    }
    /* Keep the music out of the measurement. */
    stop_background_tune();

    for (frame = 0; frame < warmup; ++frame) {
        ++g_menu.animation_ticks;
        simulate_session_tick(g_menu.animation_ticks);
    }
    /* --bench-screen title|newgame|map measures another screen over the
       same session (the island stays loaded). */
    {
        char screen_name[16];
        if (command_line_value(command_line, "--bench-screen", screen_name,
                               sizeof(screen_name))) {
            if (strcmp(screen_name, "title") == 0)
                g_menu.screen = SCREEN_MAIN_MENU;
            else if (strcmp(screen_name, "newgame") == 0)
                g_menu.screen = SCREEN_NEW_GAME;
            else if (strcmp(screen_name, "map") == 0)
                g_menu.screen = SCREEN_WORLD_MAP;
        }
        bench_screen = g_menu.screen;
    }
    for (frame = 0; frame < g_game_session.floater_count; ++frame)
        if (game_session_floater_is_active(&g_game_session.floaters[frame]))
            ++active;

    GetClientRect(window, &client);
    screen = GetDC(window);
    if (!ensure_paint_buffer(screen)) {
        ReleaseDC(window, screen);
        return 1;
    }
    frame_ms = (double *)calloc(frames, sizeof(double));
    if (frame_ms == NULL) {
        ReleaseDC(window, screen);
        return 1;
    }

    if (profile) {
        NT_TIB *tib = (NT_TIB *)NtCurrentTeb();
        g_bench_samples = (BenchSample *)calloc(BENCH_MAX_SAMPLES,
                                                sizeof(BenchSample));
        if (g_bench_samples != NULL &&
            DuplicateHandle(GetCurrentProcess(), GetCurrentThread(),
                            GetCurrentProcess(), &g_bench_main_thread,
                            THREAD_SUSPEND_RESUME | THREAD_GET_CONTEXT,
                            FALSE, 0)) {
            g_bench_stack_low = (DWORD)(uintptr_t)tib->StackLimit;
            g_bench_stack_high = (DWORD)(uintptr_t)tib->StackBase;
            sampler = CreateThread(NULL, 0, bench_sampler_thread, NULL, 0, NULL);
        }
        g_bench_sampling = sampler != NULL;
    }

    wall_start = bench_now();
    thread_cpu_start = bench_thread_cpu();
    process_cpu_start = bench_process_cpu();
    for (frame = 0; frame < frames; ++frame) {
        LONGLONG t0, t1, t2, t3;
        double phase_ms[BENCH_PHASE_COUNT];
        int phase;
        if (paced) {
            while (frame_clock_due() == 0U) {
                g_bench_phase = BENCH_PHASE_IDLE;
                bench_pump_messages();
                Sleep(1);
            }
        }
        bench_pump_messages();
        t0 = bench_now();
        g_bench_phase = BENCH_PHASE_SIM;
        run_ui_frame(window, 1);
        t1 = bench_now();
        g_bench_phase = BENCH_PHASE_RENDER;
        render_back_buffer(g_paint_buffer_dc);
        t2 = bench_now();
        g_bench_phase = BENCH_PHASE_PRESENT;
        present_back_buffer(screen, &client);
        (void)GdiFlush();
        t3 = bench_now();
        g_bench_phase = BENCH_PHASE_IDLE;
        ValidateRect(window, NULL);
        phase_ms[BENCH_PHASE_IDLE] = 0.0;
        phase_ms[BENCH_PHASE_SIM] = bench_seconds(t1 - t0) * 1000.0;
        phase_ms[BENCH_PHASE_RENDER] = bench_seconds(t2 - t1) * 1000.0;
        phase_ms[BENCH_PHASE_PRESENT] = bench_seconds(t3 - t2) * 1000.0;
        for (phase = 0; phase < BENCH_PHASE_COUNT; ++phase) {
            phase_total[phase] += phase_ms[phase];
            if (phase_ms[phase] > phase_max[phase]) phase_max[phase] = phase_ms[phase];
        }
        frame_ms[frame] = bench_seconds(t3 - t0) * 1000.0;
        if (g_menu.screen != bench_screen) break;
    }
    wall_end = bench_now();
    thread_cpu_end = bench_thread_cpu();
    process_cpu_end = bench_process_cpu();
    g_bench_sampling = 0;
    g_bench_stop = 1;
    if (sampler != NULL) {
        WaitForSingleObject(sampler, INFINITE);
        CloseHandle(sampler);
    }
    ReleaseDC(window, screen);
    if (frame < frames) frames = frame + 1U;
    {
        char dump_path[MAX_PATH];
        if (command_line_value(command_line, "--bench-dump", dump_path,
                               sizeof(dump_path)))
            bench_dump_back_buffer(dump_path);
    }

    file = fopen(out_path, "wb");
    if (file != NULL) {
        double wall = bench_seconds(wall_end - wall_start);
        double thread_cpu = (double)(thread_cpu_end - thread_cpu_start) / 1e7;
        double process_cpu = (double)(process_cpu_end - process_cpu_start) / 1e7;
        double sum = 0.0;
        unsigned i;
        int phase;
        for (i = 0; i < frames; ++i) sum += frame_ms[i];
        qsort(frame_ms, frames, sizeof(double), bench_compare_double);
        fprintf(file, "scenario %s\nworld %d\nisland %d\nfloaters %u\n"
                "warmup_ticks %u\nframes %u\npaced %d\nclient %ldx%ld\n",
                scenario, g_menu.world_index, g_menu.selected_map_island,
                active, warmup, frames, paced,
                (long)(client.right - client.left),
                (long)(client.bottom - client.top));
        fprintf(file, "wall_s %.3f\nthread_cpu_s %.3f\nprocess_cpu_s %.3f\n",
                wall, thread_cpu, process_cpu);
        fprintf(file, "frame_ms mean %.3f p50 %.3f p95 %.3f max %.3f\n",
                sum / frames, frame_ms[frames / 2],
                frame_ms[(frames * 95U) / 100U], frame_ms[frames - 1U]);
        /* Share of one core at the game's 20 frames per second, from the
           measured frame time: thread CPU times are sampled on the 15.6 ms
           scheduler tick and miss most short frames of a paced run. */
        fprintf(file, "core_at_20fps_pct %.2f\n",
                sum / frames * 20.0 / 1000.0 * 100.0);
        for (phase = BENCH_PHASE_SIM; phase < BENCH_PHASE_COUNT; ++phase)
            fprintf(file, "phase %s mean_ms %.3f max_ms %.3f\n",
                    g_bench_phase_names[phase], phase_total[phase] / frames,
                    phase_max[phase]);
        if (g_bench_samples != NULL) {
            LONG count = g_bench_sample_count;
            LONG s;
            fprintf(file, "image_base %lx\nsamples %ld\n",
                    (unsigned long)(uintptr_t)GetModuleHandleA(NULL), (long)count);
            for (s = 0; s < count; ++s) {
                const BenchSample *sample = &g_bench_samples[s];
                unsigned f;
                fprintf(file, "s %s", g_bench_phase_names[sample->phase]);
                for (f = 0; f < sample->depth; ++f)
                    bench_write_frame(file, sample->frames[f]);
                fputc('\n', file);
            }
        }
        fclose(file);
    }
    free(frame_ms);
    free(g_bench_samples);
    g_bench_samples = NULL;
    free(g_bench_frame_names);
    g_bench_frame_names = NULL;
    if (g_bench_main_thread != NULL) CloseHandle(g_bench_main_thread);
    return file != NULL ? 0 : 1;
}
