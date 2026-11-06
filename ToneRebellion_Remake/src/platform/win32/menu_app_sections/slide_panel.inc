/* SlideWindow (WINTYPE 13, windows.txt SHADE, states 2 and 3; FUN_004578df
   message handler, paint 0x457f15): the options panel that slides down from
   the top edge of the world map and island view. Phases: 0 closed, 1 opening,
   2 open, 3 closing; the pane is 99 px high (OPENPANE 0 0 639 99). A press on
   the top row opens it; while open a press on y == 0 or y > 97 closes it. */

enum { SLIDE_OPEN_HEIGHT = 99, SLIDE_STEP = 15 };

static int g_slide_phase;
static int g_slide_pos;
static int g_paused;
static int g_music_volume = 100;
/* Set while dragging: the MCI volume command blocks, so slide_panel_tick
   sends it at most once per frame instead of once per mouse move. */
static int g_music_volume_pending;
static SpriteSheet g_slide_art;
static void apply_music_volume(void);
/* remake_options.inc */
static void options_toggle(void);
static void render_options_claw_caption(RenderSurface *surface, int d);

/* Table DAT_004a33f0 (xmin, ymin, xmax, ymax): 0 Save, 1 Load, 2 pause,
   3 quit to the title (writes resume.gam), 4 music, 5 sound. The first
   matching rectangle wins. */
static const RECT k_slide_rects[6] = {
    {102, 40, 197, 91}, {93, 8, 200, 50}, {285, 1, 359, 56},
    {271, 45, 339, 100}, {394, 3, 452, 51}, {401, 47, 447, 96}
};

/* FUN_0044964f formats slidwin%d.shp, loadsav%d.shp, isletmp%d.shp ... with
   the active player (DAT_0049f538): each tribe has its own colouring of the
   SlideWindow and Load/Save sheets. */
static int ui_art_tribe(void)
{
    return g_menu.selected_tribe >= 0 && g_menu.selected_tribe < 4
        ? g_menu.selected_tribe : 0;
}

static int g_slide_art_tribe = -1;
static int g_load_save_art_tribe = -1;

static int ensure_slide_art(void)
{
    CobArchive archive = {0};
    char error[128];
    char name[32];
    int tribe = ui_art_tribe();
    if (g_slide_art.frame_count != 0 && g_slide_art_tribe == tribe) return 1;
    free_sprite_sheet(&g_slide_art);
    memset(&g_slide_art, 0, sizeof(g_slide_art));
    g_slide_art_tribe = -1;
    if (!cob_archive_open(game_file_path("TONE01.COB"), &archive,
                          error, sizeof(error))) return 0;
    (void)snprintf(name, sizeof(name), "data\\slidwin%d.shp", tribe);
    (void)load_sprite_sheet(&archive, name, g_load_save_palette,
                            &g_slide_art, error, sizeof(error));
    cob_archive_close(&archive);
    if (g_slide_art.frame_count > 10U) g_slide_art_tribe = tribe;
    return g_slide_art.frame_count > 10U;
}

/* The Load/Save template of the active tribe (loadsav%d.shp). */
static void ensure_load_save_art(void)
{
    CobArchive archive = {0};
    char error[128];
    char name[32];
    SpriteSheet candidate = {0};
    int tribe = ui_art_tribe();
    if (g_load_save_art_tribe == tribe) return;
    if (!cob_archive_open(game_file_path("TONE01.COB"), &archive,
                          error, sizeof(error))) return;
    (void)snprintf(name, sizeof(name), "data\\loadsav%d.shp", tribe);
    if (load_sprite_sheet(&archive, name, g_load_save_palette, &candidate,
                          error, sizeof(error)) && candidate.frame_count >= 9U) {
        free_sprite_sheet(&g_load_save_art);
        g_load_save_art = candidate;
        g_load_save_art_tribe = tribe;
    } else {
        free_sprite_sheet(&candidate);
    }
    cob_archive_close(&archive);
}

/* FUN_004578df message 0x32 (timer, 50 ms): the pane height eases out while
   opening (15 px steps, slower inside the last 50 px) and retracts 15 px per
   tick while closing. */
static void slide_panel_tick(void)
{
    if (g_music_volume_pending) {
        g_music_volume_pending = 0;
        apply_music_volume();
    }
    if (g_slide_phase == 1) {
        int remaining = SLIDE_OPEN_HEIGHT - g_slide_pos;
        int step = remaining < 50 ? remaining * 15 / 50 + 1 : SLIDE_STEP;
        if (step > SLIDE_STEP) step = SLIDE_STEP;
        g_slide_pos += step;
        if (g_slide_pos >= SLIDE_OPEN_HEIGHT) {
            g_slide_pos = SLIDE_OPEN_HEIGHT;
            g_slide_phase = 2;
        }
    } else if (g_slide_phase == 3) {
        g_slide_pos -= SLIDE_STEP;
        if (g_slide_pos <= 0) {
            g_slide_pos = 0;
            g_slide_phase = 0;
        }
    }
}

/* Remake: Escape opens the panel (phase 1) or retracts it (phase 3) from
   wherever it is. */
static void slide_panel_toggle(void)
{
    g_slide_phase = g_slide_phase == 1 || g_slide_phase == 2 ? 3 : 1;
}

static void slide_panel_close_now(void)
{
    g_slide_phase = 0;
    g_slide_pos = 0;
}

/* Remake behaviour (requested; FUN_004576c7 neither pauses nor opens the
   SlideWindow): a loaded game starts paused with the panel open, so the
   player resumes it from the pause zone. */
static void slide_panel_open_paused(void)
{
    /* The remake options can turn it off (original behaviour). */
    if (!g_load_starts_paused) {
        slide_panel_close_now();
        g_paused = 0;
        return;
    }
    g_slide_phase = 2;
    g_slide_pos = SLIDE_OPEN_HEIGHT;
    g_paused = 1;
}

static int slide_panel_hit(int x, int y)
{
    int index;
    for (index = 0; index < 6; ++index) {
        if (x >= k_slide_rects[index].left && x <= k_slide_rects[index].right &&
            y >= k_slide_rects[index].top && y <= k_slide_rects[index].bottom)
            return index;
    }
    return -1;
}

/* Same attenuation curve as the effects (FUN_004595cc). MCI `waveaudio` has no
   `setaudio volume` (error 261), so the music is opened as `mpegvideo`
   (DirectShow), which takes a linear 0..1000 level: apply the amplitude gain. */
static void apply_music_volume(void)
{
    if (g_music_device_open) {
#ifdef TONE_PLATFORM_SDL
        sdl_music_set_gain(volume_gain(g_music_volume));
#else
        char command[64];
        (void)snprintf(command, sizeof(command),
                       "setaudio tone_music volume to %d",
                       (int)(1000.0 * volume_gain(g_music_volume) + 0.5));
        (void)mciSendStringA(command, NULL, 0, NULL);
#endif
    }
}

/* Port choice: the toggles and volumes persist in saves\audio.cfg. */
static int audio_settings_path(char *path, size_t capacity)
{
    char directory[MAX_PATH];
    if (!save_directory(directory, sizeof(directory))) return 0;
    (void)snprintf(path, capacity, "%s/audio.cfg", directory);
    return 1;
}

static void save_audio_settings(void)
{
    char path[MAX_PATH];
    FILE *file;
    if (!audio_settings_path(path, sizeof(path))) return;
    file = fopen(path, "w");
    if (file == NULL) return;
    (void)fprintf(file, "%d %d %d %d\n", g_music_enabled, g_music_volume,
                  g_sound_enabled, g_sound_volume);
    (void)fclose(file);
    platform_storage_changed();
}

static void load_audio_settings(void)
{
    char path[MAX_PATH];
    FILE *file;
    int music_on, music_volume, sound_on, sound_volume;
    if (!audio_settings_path(path, sizeof(path))) return;
    file = fopen(path, "r");
    if (file == NULL) return;
    if (fscanf(file, "%d %d %d %d", &music_on, &music_volume, &sound_on,
               &sound_volume) == 4 && music_volume >= 0 && music_volume <= 100 &&
        sound_volume >= 0 && sound_volume <= 100) {
        g_music_enabled = music_on != 0;
        g_music_volume = music_volume;
        g_sound_enabled = sound_on != 0;
        g_sound_volume = sound_volume;
    }
    (void)fclose(file);
}

/* Slider thumb under the held button: value = x - 456 clamped to 0..100.
   audio.cfg is written once on release (slide_panel_end_drag), not on
   every mouse move. */
static void slide_panel_drag(int x)
{
    int value = x - 456;
    if (value < 0) value = 0;
    if (value > 100) value = 100;
    if (g_slide_drag == 1 && g_music_volume != value) {
        g_music_volume = value;
        g_music_volume_pending = 1;
    } else if (g_slide_drag == 2) {
        g_sound_volume = value;
    }
}

static void slide_panel_end_drag(void)
{
    if (g_slide_drag == 0) return;
    g_slide_drag = 0;
    platform_capture_mouse(NULL, 0);
    if (g_music_volume_pending) {
        g_music_volume_pending = 0;
        apply_music_volume();
    }
    save_audio_settings();
}

/* Left press at logical (x, y); returns nonzero when the panel took it. */
static void slide_toggle_music(void)
{
    g_music_enabled = !g_music_enabled;
    save_audio_settings();
    if (!g_music_enabled) {
        stop_background_tune();
    } else {
        apply_music_volume();
        if (g_music_resume_tune[0] != '\0') {
            set_background_tune_mode(g_music_resume_tune, g_music_resume_loop);
            apply_music_volume();
        }
    }
}

static void slide_toggle_sound(void)
{
    g_sound_enabled = !g_sound_enabled;
    save_audio_settings();
}

static int slide_panel_press(HWND window, int x, int y)
{
    int hit;
    if (g_menu.screen != SCREEN_WORLD_MAP && g_menu.screen != SCREEN_ISLAND)
        return 0;
    if (g_slide_phase == 0) {
        if (y > 1) return 0;
        g_slide_phase = 1;
        g_slide_pos = 0;
        return 1;
    }
    if (g_slide_phase != 2) return 1;
    if (y == 0 || y > 97) {
        g_slide_phase = 3;
        return 1;
    }
    /* Volume sliders: thumb value = x - 456 clamped to 0..100. */
    if (x >= 450 && x <= 580) {
        int value = x - 456;
        if (value < 0) value = 0;
        if (value > 100) value = 100;
        if (y >= 11 && y <= 31) {
            g_slide_drag = 1;
            if (g_music_volume != value) {
                g_music_volume = value;
                g_music_volume_pending = 1;
            }
        } else if (y >= 57 && y <= 77) {
            g_slide_drag = 2;
            g_sound_volume = value;
        }
        if (g_slide_drag != 0) platform_capture_mouse(window, 1);
    }
    hit = slide_panel_hit(x, y);
    /* FUN_004578df only sends Save/Load (SetState 5/4) and pauses when
       DAT_004befe0 == 0. Remake: a network game keeps Save (a local copy of
       the shared session) and pauses every machine through a lockstep
       command; only the host can Load, which takes every machine back to
       the lobby with the picked game (net_host_pick_save). */
    if (g_net_in_game && hit == 1 && g_net_mode != NET_MODE_HOST) hit = -1;
    if (g_net_in_game && hit == 1) {
        slide_panel_close_now();
        g_save_return_screen = g_menu.screen;
        g_net_load_pick = 1;
        g_load_save_mode = 0;
        g_load_from_game = 0;
        scan_load_slots();
        g_menu.screen = SCREEN_LOAD_GAME;
        hit = -1;
    }
    if (g_net_in_game && hit == 2) {
        int32_t paused = g_game_session.network_paused ? 0 : 1;
        (void)issue_command(GAME_COMMAND_SET_NETWORK_PAUSE, 1, &paused);
        hit = -1;
    }
    if (hit == 0) {
        slide_panel_close_now();
        enter_save_screen();
    } else if (hit == 1) {
        slide_panel_close_now();
        if (g_game_session_valid) {
            g_save_return_screen = g_menu.screen;
            g_load_from_game = 1;
        }
        g_load_save_mode = 0;
        scan_load_slots();
        g_menu.screen = SCREEN_LOAD_GAME;
    } else if (hit == 2) {
        g_paused = !g_paused;
    } else if (hit == 3) {
        /* idx 3: write resume.gam, then SetState(0). */
        write_resume_file();
        g_resume_available = resume_header_is_valid();
        slide_panel_close_now();
        g_paused = 0;
        g_game_session_valid = 0;
        g_menu.screen = SCREEN_MAIN_MENU;
    } else if (hit == 4) {
        slide_toggle_music();
    } else if (hit == 5) {
        slide_toggle_sound();
    } else if (x >= 6 && x <= 88 && y >= 6 && y <= 92) {
        /* Remake: the left claw opens the remake options. */
        options_toggle();
    }
    (void)window;
    return 1;
}

/* FUN_0046ae19 (0x46b5f7..0x46b707): while DAT_004bf124 is set, frame 0 of
   the PAUSE shape (data\pause.shp, the closed eye) is drawn on the island
   and world map views, centred on its opaque bounds (FUN_00405e11 at the
   origin): x = clamp((640 - width) / 2, 0, 639), y = 112. */
static SpriteSheet g_pause_art;

static void render_pause_eye(RenderSurface *surface)
{
    const SpriteFrame *frame;
    int width;
    int x;
    if (!g_paused) return;
    if (g_pause_art.frame_count == 0) {
        CobArchive archive = {0};
        char error[128];
        if (!cob_archive_open(game_file_path("TONE01.COB"), &archive,
                              error, sizeof(error))) return;
        (void)load_sprite_sheet(&archive, "data\\pause.shp",
                                g_load_save_palette, &g_pause_art, error,
                                sizeof(error));
        cob_archive_close(&archive);
        if (g_pause_art.frame_count == 0) return;
    }
    frame = &g_pause_art.frames[0];
    width = frame->hit_right - frame->hit_left;
    x = (640 - width) / 2;
    if (x < 0) x = 0;
    if (x > 0x27f) x = 0x27f;
    draw_sprite(surface, &g_pause_art, 0, x, 0x70);
}

/* Paint 0x457f15: y offset d = pos - 99; frame 0 background, frame 7 when
   paused, music/sound off icons (frames 8/9) or slider thumbs (frame 10 at
   x = 456 + volume), and the hovered rectangle's frame (index + 1). */
static void render_slide_panel(RenderSurface *surface)
{
    int d;
    int hover = -1;
    if (g_slide_phase == 0 || !ensure_slide_art()) return;
    d = g_slide_pos - SLIDE_OPEN_HEIGHT;
    draw_sprite(surface, &g_slide_art, 0, 0, d);
    if (g_paused) draw_sprite(surface, &g_slide_art, 7, 292, d + 6);
    if (!g_music_enabled)
        draw_sprite(surface, &g_slide_art, 8, 414, d + 7);
    else
        draw_sprite(surface, &g_slide_art, 10, 456 + g_music_volume, d + 13);
    if (!g_sound_enabled)
        draw_sprite(surface, &g_slide_art, 9, 415, d + 63);
    else
        draw_sprite(surface, &g_slide_art, 10, 456 + g_sound_volume, d + 59);
    if (g_slide_phase == 2 && g_mouse_inside)
        hover = slide_panel_hit(g_mouse_x, g_mouse_y);
    if (hover >= 0)
        draw_sprite(surface, &g_slide_art, (uint32_t)hover + 1U,
                    k_slide_rects[hover].left, k_slide_rects[hover].top + d);
    render_options_claw_caption(surface, d);
}
