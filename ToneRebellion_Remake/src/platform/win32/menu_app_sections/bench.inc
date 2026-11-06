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
   --bench-screen title|newgame|map|load, --bench-client WxH,
   --bench-panel N (island panel mode, WINDOW_ISLAND_PANEL_*),
   --bench-construct (IWConstruct open on the first buildable site, first
   column hovered): fixed UI states for --bench-dump comparisons;
   --bench-dump-set DIR (all parity frames from one hidden process). */

enum { BENCH_PHASE_IDLE, BENCH_PHASE_SIM, BENCH_PHASE_RENDER,
       BENCH_PHASE_PRESENT, BENCH_PHASE_COUNT };
enum { BENCH_STACK_DEPTH = 24, BENCH_MAX_SAMPLES = 400000 };

typedef struct BenchSample {
    uint8_t phase;
    uint8_t depth;
    uintptr_t frames[BENCH_STACK_DEPTH];
} BenchSample;

static volatile LONG g_bench_phase;
static volatile LONG g_bench_sampling;
static volatile LONG g_bench_stop;

static const char *const g_bench_phase_names[BENCH_PHASE_COUNT] = {
    "idle", "sim", "render", "present"
};


static double bench_seconds(int64_t ticks)
{
    return (double)ticks / (double)platform_counter_frequency();
}

static int64_t bench_now(void)
{
    return (int64_t)platform_counter();
}

/* No portable thread / process CPU time: the report shows 0. */
static int64_t bench_thread_cpu(void)
{
    return 0;
}

static int64_t bench_process_cpu(void)
{
    return 0;
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
    /* Window events are not input to replay. */
    SDL_PumpEvents();
    SDL_FlushEvents(SDL_EVENT_FIRST, SDL_EVENT_LAST);
}

/* Presentation through the shell in use: GDI StretchBlt or the SDL
   texture. */
static int bench_begin_present(HWND window, HDC *screen)
{
    (void)window;
    *screen = NULL;
    return sdl_ensure_back_buffer();
}

static void bench_end_present(HWND window, HDC screen)
{
    (void)window;
    (void)screen;
}

static void bench_present(HDC screen, const RECT *client)
{
    (void)screen;
    (void)client;
    sdl_present();
}

static void bench_set_client_size(HWND window, unsigned width, unsigned height)
{
    (void)window;
    (void)SDL_SetWindowSize(g_sdl_window, (int)width, (int)height);
    (void)SDL_SyncWindow(g_sdl_window);
    bench_pump_messages();
}

static void bench_put_u32(unsigned char *p, uint32_t value)
{
    p[0] = (unsigned char)value;
    p[1] = (unsigned char)(value >> 8);
    p[2] = (unsigned char)(value >> 16);
    p[3] = (unsigned char)(value >> 24);
}

/* Writes the 640x480 back buffer as a top-down 32-bit BMP: a 14-byte file
   header and a 40-byte BITMAPINFOHEADER, written byte by byte. */
static void bench_dump_back_buffer(const char *path)
{
    unsigned char header[54];
    uint32_t bytes = LOGICAL_WIDTH * LOGICAL_HEIGHT * 4U;
    FILE *file = fopen(path, "wb");
    if (file == NULL || g_back_surface.pixels == NULL) {
        if (file != NULL) fclose(file);
        return;
    }
    memset(header, 0, sizeof(header));
    header[0] = 'B';
    header[1] = 'M';
    bench_put_u32(header + 2, (uint32_t)sizeof(header) + bytes);
    bench_put_u32(header + 10, (uint32_t)sizeof(header));
    bench_put_u32(header + 14, 40U);
    bench_put_u32(header + 18, LOGICAL_WIDTH);
    bench_put_u32(header + 22, (uint32_t)-LOGICAL_HEIGHT);
    header[26] = 1;   /* planes */
    header[28] = 32;  /* bits per pixel, BI_RGB */
    fwrite(header, sizeof(header), 1, file);
    fwrite(g_back_surface.pixels, bytes, 1, file);
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

/* Session and screen setup shared by a timed run and the dump set: fixed
   world, tribe 0, easiest difficulty, constant seed. Returns 0 on error. */
static int bench_prepare(HWND window, const char *command_line,
                         char *scenario, size_t scenario_size,
                         int *bench_screen, unsigned *active)
{
    char error[256];
    unsigned warmup = bench_option(command_line, "--bench-warmup", 300U);
    unsigned frame;
    /* What a fresh process starts with, so every dump of a set sees the
       same state as its own process would. */
    g_menu.screen = SCREEN_MAIN_MENU;
    g_menu.animation_ticks = 0;
    g_menu.selected_map_island = -1;
    g_game_session_valid = 0;
    g_island_scroll_x = 0;
    g_island_panel_mode = WINDOW_ISLAND_PANEL_GENERAL;
    snprintf(scenario, scenario_size, "idle");
    (void)command_line_value(command_line, "--bench-scenario", scenario,
                             scenario_size);
    *active = 0;
    g_menu.world_index = (int)bench_option(command_line, "--bench-world", 0U);
    if (g_menu.world_index >= g_menu.world_map.world_count) g_menu.world_index = 0;
    g_menu.selected_tribe = 0;
    g_menu.difficulty = 0;
    g_random_state = 0x13572468U;
    g_sim_speed = 1U;
    if (!load_game_session_for_selected_world(error, sizeof(error))) {
        platform_message_box(window, error, "Tone Rebellion remake - bench", 0);
        return 0;
    }
    g_menu.setup_accepted = 1;
    if (!bench_open_home_island(window)) {
        platform_message_box(window, "No enterable island.", "Tone Rebellion remake - bench",
                             0);
        return 0;
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
            else if (strcmp(screen_name, "load") == 0)
                g_menu.screen = SCREEN_LOAD_GAME;
        }
        *bench_screen = g_menu.screen;
    }
    if (strstr(command_line, "--bench-panel") != NULL)
        g_island_panel_mode = (int)bench_option(command_line, "--bench-panel",
                                                WINDOW_ISLAND_PANEL_GENERAL);
    if (strstr(command_line, "--bench-construct") != NULL) {
        uint16_t location;
        for (location = 0; location < g_island_surface_data.location_count;
             ++location)
            if (open_iw_construct((int)location)) {
                g_iw_construct.hovered_column = 0;
                break;
            }
    }
    for (frame = 0; frame < g_game_session.floater_count; ++frame)
        if (game_session_floater_is_active(&g_game_session.floaters[frame]))
            ++*active;
    return 1;
}

/* --bench-dump-set DIR: the parity frames (idle, crowd and battle at three
   warmups, panels 1..7, IWConstruct, other screens, world 3) written as
   DIR/NAME.bmp from one hidden process instead of one run each. */
static const char *const g_bench_dump_set[][2] = {
    {"idle_40", "--bench-scenario idle --bench-warmup 40"},
    {"idle_300", "--bench-scenario idle --bench-warmup 300"},
    {"idle_1500", "--bench-scenario idle --bench-warmup 1500"},
    {"crowd_40", "--bench-scenario crowd --bench-warmup 40"},
    {"crowd_300", "--bench-scenario crowd --bench-warmup 300"},
    {"crowd_1500", "--bench-scenario crowd --bench-warmup 1500"},
    {"battle_40", "--bench-scenario battle --bench-warmup 40"},
    {"battle_300", "--bench-scenario battle --bench-warmup 300"},
    {"battle_1500", "--bench-scenario battle --bench-warmup 1500"},
    {"panel1_idle", "--bench-scenario idle --bench-warmup 300 --bench-panel 1"},
    {"panel1_battle", "--bench-scenario battle --bench-warmup 300 --bench-panel 1"},
    {"panel2_idle", "--bench-scenario idle --bench-warmup 300 --bench-panel 2"},
    {"panel2_battle", "--bench-scenario battle --bench-warmup 300 --bench-panel 2"},
    {"panel3_idle", "--bench-scenario idle --bench-warmup 300 --bench-panel 3"},
    {"panel3_battle", "--bench-scenario battle --bench-warmup 300 --bench-panel 3"},
    {"panel4_idle", "--bench-scenario idle --bench-warmup 300 --bench-panel 4"},
    {"panel4_battle", "--bench-scenario battle --bench-warmup 300 --bench-panel 4"},
    {"panel5_idle", "--bench-scenario idle --bench-warmup 300 --bench-panel 5"},
    {"panel5_battle", "--bench-scenario battle --bench-warmup 300 --bench-panel 5"},
    {"panel6_idle", "--bench-scenario idle --bench-warmup 300 --bench-panel 6"},
    {"panel6_battle", "--bench-scenario battle --bench-warmup 300 --bench-panel 6"},
    {"panel7_idle", "--bench-scenario idle --bench-warmup 300 --bench-panel 7"},
    {"panel7_battle", "--bench-scenario battle --bench-warmup 300 --bench-panel 7"},
    {"construct", "--bench-scenario idle --bench-warmup 300 --bench-construct"},
    {"screen_title_idle", "--bench-scenario idle --bench-warmup 40 --bench-screen title"},
    {"screen_title_battle", "--bench-scenario battle --bench-warmup 40 --bench-screen title"},
    {"screen_newgame_idle", "--bench-scenario idle --bench-warmup 40 --bench-screen newgame"},
    {"screen_newgame_battle", "--bench-scenario battle --bench-warmup 40 --bench-screen newgame"},
    {"screen_map_idle", "--bench-scenario idle --bench-warmup 40 --bench-screen map"},
    {"screen_map_battle", "--bench-scenario battle --bench-warmup 40 --bench-screen map"},
    {"screen_load_idle", "--bench-scenario idle --bench-warmup 40 --bench-screen load"},
    {"screen_load_battle", "--bench-scenario battle --bench-warmup 40 --bench-screen load"},
    {"x_crowd_40", "--bench-scenario crowd --bench-warmup 40 --bench-world 3"},
    {"x_crowd_300", "--bench-scenario crowd --bench-warmup 300 --bench-world 3"}
};

static int bench_dump_set(HWND window, const char *directory)
{
    unsigned i;
    for (i = 0; i < sizeof(g_bench_dump_set) / sizeof(g_bench_dump_set[0]); ++i) {
        char scenario[32];
        char path[MAX_PATH];
        int bench_screen;
        unsigned active;
        unsigned frame;
        if (!bench_prepare(window, g_bench_dump_set[i][1], scenario,
                           sizeof(scenario), &bench_screen, &active)) return 1;
        /* Two frames, as a --bench-frames 2 run. */
        for (frame = 0; frame < 2U; ++frame) {
            run_ui_frame(window, 1);
            render_back_buffer(&g_back_surface);
            if (g_menu.screen != bench_screen) break;
        }
        (void)snprintf(path, sizeof(path), "%s/%s.bmp", directory,
                       g_bench_dump_set[i][0]);
        bench_dump_back_buffer(path);
    }
    return 0;
}

/* Runs the benchmark and returns the process exit code. */
static int bench_run(HWND window, const char *command_line)
{
    char scenario[32] = "idle";
    char out_path[MAX_PATH];
    unsigned frames = bench_option(command_line, "--bench-frames", 600U);
    unsigned warmup = bench_option(command_line, "--bench-warmup", 300U);
    int paced = strstr(command_line, "--bench-paced") != NULL;
    int profile = strstr(command_line, "--bench-profile") != NULL;
    double *frame_ms;
    double phase_total[BENCH_PHASE_COUNT] = {0};
    double phase_max[BENCH_PHASE_COUNT] = {0};
    int64_t wall_start, wall_end, thread_cpu_start, thread_cpu_end;
    int64_t process_cpu_start, process_cpu_end;
    FILE *file;
    unsigned frame;
    unsigned active = 0;
    int bench_screen;
    RECT client;
    HDC screen;

    if (frames == 0U) frames = 1U;
    {
        char directory[MAX_PATH];
        if (command_line_value(command_line, "--bench-dump-set", directory,
                               sizeof(directory))) {
            int exit_code = 1;
            if (bench_begin_present(window, &screen))
                exit_code = bench_dump_set(window, directory);
            bench_end_present(window, screen);
            return exit_code;
        }
    }
    if (!command_line_value(command_line, "--bench-out", out_path,
                            sizeof(out_path))) {
        if (platform_executable_directory(out_path, sizeof(out_path) - 1U))
            (void)strcat(out_path, "/");
        else
            out_path[0] = '\0';
        strncat(out_path, "bench_report.txt",
                sizeof(out_path) - strlen(out_path) - 1U);
    }

    if (!bench_prepare(window, command_line, scenario, sizeof(scenario),
                       &bench_screen, &active)) return 1;

    {
        /* --bench-client WxH: the client size to present into. */
        char size[32];
        unsigned width;
        unsigned height;
        if (command_line_value(command_line, "--bench-client", size,
                               sizeof(size)) &&
            sscanf(size, "%ux%u", &width, &height) == 2 &&
            width > 0U && height > 0U) {
            bench_set_client_size(window, width, height);
        }
    }
    platform_client_rect(window, &client);
    if (!bench_begin_present(window, &screen)) {
        bench_end_present(window, screen);
        return 1;
    }
    frame_ms = (double *)calloc(frames, sizeof(double));
    if (frame_ms == NULL) {
        bench_end_present(window, screen);
        return 1;
    }

    (void)profile;

    wall_start = bench_now();
    thread_cpu_start = bench_thread_cpu();
    process_cpu_start = bench_process_cpu();
    for (frame = 0; frame < frames; ++frame) {
        int64_t t0, t1, t2, t3;
        double phase_ms[BENCH_PHASE_COUNT];
        int phase;
        if (paced) {
            while (frame_clock_due() == 0U) {
                g_bench_phase = BENCH_PHASE_IDLE;
                bench_pump_messages();
                platform_sleep_ms(1);
            }
        }
        bench_pump_messages();
        t0 = bench_now();
        g_bench_phase = BENCH_PHASE_SIM;
        run_ui_frame(window, 1);
        t1 = bench_now();
        g_bench_phase = BENCH_PHASE_RENDER;
        render_back_buffer(&g_back_surface);
        t2 = bench_now();
        g_bench_phase = BENCH_PHASE_PRESENT;
        bench_present(screen, &client);
        t3 = bench_now();
        g_bench_phase = BENCH_PHASE_IDLE;
        g_sdl_dirty = 0;
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
    bench_end_present(window, screen);
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
        fclose(file);
    }
    free(frame_ms);
    return file != NULL ? 0 : 1;
}
