/* Remake options (remake extension, no native counterpart): a panel over
   the island and the world map for the port's own settings. F2 opens or
   closes it, and so does the left claw of the SlideWindow options panel.
   Up/Down pick a row, Left/Right or a click change its value, Escape, F2 or
   Enter close it. The game keeps running behind it. Choices persist in
   saves\video.cfg and saves\audio.cfg. F2 also opens it on the title
   screen (language and display settings before playing). */

enum {
    OPTION_LANGUAGE,
    OPTION_PAINT_RATE,
    OPTION_SCALE,
    OPTION_FILTER,
    OPTION_VSYNC,
    OPTION_GAME_SPEED,
    OPTION_MUSIC,
    OPTION_SOUND,
    OPTION_SMOOTH_SCROLL,
    OPTION_EDGE_SCROLL,
    OPTION_ALERTS,
    OPTION_CRYPTIC,
    OPTION_SHORTCUTS,
    OPTION_SHORTCUT_KEYS,
    OPTION_QUICKSAVE,
    OPTION_AUTOSAVE,
    OPTION_LOAD_PAUSED,
    OPTION_CLIPBOARD,
    OPTION_COUNT
};

enum {
    OPTIONS_LEFT = 100, OPTIONS_TOP = 56, OPTIONS_WIDTH = 440,
    OPTIONS_ROW_TOP = 92, OPTIONS_ROW_HEIGHT = 19,
    OPTIONS_VALUE_LEFT = 340, OPTIONS_VALUE_RIGHT = 525,
    /* SlideWindow left claw (no native control there). */
    OPTIONS_CLAW_LEFT = 6, OPTIONS_CLAW_TOP = 6,
    OPTIONS_CLAW_RIGHT = 88, OPTIONS_CLAW_BOTTOM = 92
};

static int g_options_open;
static int g_options_row;
/* 0: settings, 1: shortcut keys (remake_qol.inc draws and drives it). */
static int g_options_page;

static void set_scale_mode(HWND window, int mode);
static void set_paint_rate(HWND window, int index);
static void set_upscale_filter(HWND window, int filter);
static void slide_toggle_music(void);
static void slide_toggle_sound(void);
static void render_shortcut_page(RenderSurface *surface);
static int shortcut_page_key(HWND window, WPARAM key);
static int shortcut_page_press(HWND window, int x, int y);

static const RemakeTextId g_option_labels[OPTION_COUNT] = {
    T_OPT_LANGUAGE, T_OPT_PAINT_RATE, T_OPT_SCALE, T_OPT_FILTER, T_OPT_VSYNC,
    T_OPT_GAME_SPEED, T_OPT_MUSIC, T_OPT_SOUND, T_OPT_SMOOTH_SCROLL,
    T_OPT_EDGE_SCROLL, T_OPT_ALERTS, T_OPT_CRYPTIC, T_OPT_SHORTCUTS,
    T_OPT_SHORTCUT_KEYS, T_OPT_QUICKSAVE, T_OPT_AUTOSAVE, T_OPT_LOAD_PAUSED,
    T_OPT_CLIPBOARD
};

static const int g_autosave_choices[] = {0, 2, 5, 10, 15, 30};
enum { AUTOSAVE_CHOICE_COUNT = 6 };

static int options_screen(void)
{
    return g_menu.screen == SCREEN_ISLAND || g_menu.screen == SCREEN_WORLD_MAP;
}

/* Screens where F2 opens the panel: in game and on the title. */
static int options_panel_screen(void)
{
    return options_screen() || g_menu.screen == SCREEN_MAIN_MENU;
}

/* Title screen corner: how to reach the options there. */
static void render_title_options_hint(RenderSurface *surface)
{
    const char *hint = TR(T_TITLE_F2_HINT);
    if (g_options_open) return;
    draw_small_label(surface, hint, LOGICAL_WIDTH - 14 -
                     (int)measure_small_text(hint, strlen(hint)), 8, RGB(110, 140, 190));
}

static int options_game_speed(void)
{
    if (g_net_in_game)
        return g_game_session.network_speed >= 1U &&
               g_game_session.network_speed <= 3U
                   ? (int)g_game_session.network_speed : 1;
    return (int)g_sim_speed;
}

static const char *options_yes_no(int value)
{
    return TR(value ? T_YES : T_NO_ORIGINAL);
}

static void options_value_text(int row, char *text, size_t capacity)
{
    static const RemakeTextId scales[SCALE_MODE_COUNT] = {T_SCALE_INTEGER, T_SCALE_FIT};
    switch (row) {
    case OPTION_LANGUAGE:
        if (g_language_setting < 0)
            (void)snprintf(text, capacity, TR(T_LANG_AUTO),
                           remake_lang_name(detected_language()));
        else
            (void)snprintf(text, capacity, "%s", remake_lang_name(g_language_setting));
        break;
    case OPTION_PAINT_RATE:
        (void)snprintf(text, capacity, "%u Hz%s", g_paint_rates[g_paint_rate_index],
                       g_paint_rate_index == 0 ? TR(T_ORIGINAL_SUFFIX) : "");
        break;
    case OPTION_SCALE:
        (void)snprintf(text, capacity, "%s", TR(scales[g_scale_mode]));
        break;
    case OPTION_FILTER:
        (void)snprintf(text, capacity, "%s", upscale_filter_label(g_upscale_filter));
        break;
    case OPTION_VSYNC:
        (void)snprintf(text, capacity, "%s", !gl_is_ready() ? TR(T_NO_OPENGL)
                       : TR(g_vsync ? T_YES : T_NO));
        break;
    case OPTION_GAME_SPEED:
        (void)snprintf(text, capacity, "%d", options_game_speed());
        break;
    case OPTION_MUSIC:
        (void)snprintf(text, capacity, "%s", TR(g_music_enabled ? T_YES : T_NO));
        break;
    case OPTION_SOUND:
        (void)snprintf(text, capacity, "%s", TR(g_sound_enabled ? T_YES : T_NO));
        break;
    case OPTION_SMOOTH_SCROLL:
        (void)snprintf(text, capacity, "%s", options_yes_no(g_smooth_scroll));
        break;
    case OPTION_EDGE_SCROLL:
        (void)snprintf(text, capacity, "%s", options_yes_no(g_edge_scroll));
        break;
    case OPTION_ALERTS:
        (void)snprintf(text, capacity, "%s", options_yes_no(g_event_alerts));
        break;
    case OPTION_CRYPTIC:
        (void)snprintf(text, capacity, "%s", TR(g_cryptic_messages ? T_YES_ORIGINAL : T_NO));
        break;
    case OPTION_SHORTCUTS:
        (void)snprintf(text, capacity, "%s", options_yes_no(g_shortcuts_enabled));
        break;
    case OPTION_SHORTCUT_KEYS:
        (void)snprintf(text, capacity, "%s", TR(T_KEY_ENTER));
        break;
    case OPTION_QUICKSAVE:
        (void)snprintf(text, capacity, "%s",
                       TR(g_quicksave_enabled ? T_QUICKSAVE_ON : T_QUICKSAVE_OFF));
        break;
    case OPTION_AUTOSAVE:
        if (g_autosave_minutes <= 0) (void)snprintf(text, capacity, "%s", TR(T_NO));
        else (void)snprintf(text, capacity, TR(T_AUTOSAVE_EVERY), g_autosave_minutes);
        break;
    case OPTION_LOAD_PAUSED:
        (void)snprintf(text, capacity, "%s", options_yes_no(g_load_starts_paused));
        break;
    default:
        (void)snprintf(text, capacity, "%s",
                       TR(g_clip_all_training ? T_CLIP_ALL : T_CLIP_SELECTION));
        break;
    }
}

static void options_flip(int *flag)
{
    *flag = !*flag;
    save_video_settings();
}

/* Steps the row's value by `step` (+1 / -1), wrapping. */
static void options_change(HWND window, int row, int step)
{
    switch (row) {
    case OPTION_LANGUAGE:
        /* -1 (auto: the system language) then each language. */
        g_language_setting = (g_language_setting + 1 + step + REMAKE_LANG_COUNT + 1) %
                             (REMAKE_LANG_COUNT + 1) - 1;
        apply_language();
        save_video_settings();
        update_window_title(window);
        break;
    case OPTION_PAINT_RATE:
        set_paint_rate(window, (g_paint_rate_index + step + PAINT_RATE_COUNT) %
                                   PAINT_RATE_COUNT);
        break;
    case OPTION_SCALE:
        set_scale_mode(window, (g_scale_mode + step + SCALE_MODE_COUNT) %
                                   SCALE_MODE_COUNT);
        break;
    case OPTION_FILTER:
    {
        /* Only the filters this machine can run. */
        int filter = g_upscale_filter, n;
        for (n = 0; n < FILTER_COUNT; ++n) {
            filter = (filter + step + FILTER_COUNT) % FILTER_COUNT;
            if (filter_available(filter)) break;
        }
        set_upscale_filter(window, filter);
    }
        break;
    case OPTION_VSYNC:
        if (gl_is_ready()) {
            options_flip(&g_vsync);
            (void)SDL_GL_SetSwapInterval(g_vsync ? 1 : 0);
        }
        break;
    case OPTION_GAME_SPEED: {
        int32_t speed = (options_game_speed() - 1 + step + 3) % 3 + 1;
        /* A network game changes it on every machine at the same turn. */
        if (g_net_in_game)
            (void)issue_command(GAME_COMMAND_SET_NETWORK_SPEED, 1, &speed);
        else
            g_sim_speed = (unsigned)speed;
        break;
    }
    case OPTION_MUSIC:
        slide_toggle_music();
        break;
    case OPTION_SOUND:
        slide_toggle_sound();
        break;
    case OPTION_SMOOTH_SCROLL: options_flip(&g_smooth_scroll); break;
    case OPTION_EDGE_SCROLL: options_flip(&g_edge_scroll); break;
    case OPTION_ALERTS: options_flip(&g_event_alerts); break;
    case OPTION_CRYPTIC: options_flip(&g_cryptic_messages); break;
    case OPTION_SHORTCUTS: options_flip(&g_shortcuts_enabled); break;
    case OPTION_SHORTCUT_KEYS:
        g_options_page = 1;
        break;
    case OPTION_QUICKSAVE: options_flip(&g_quicksave_enabled); break;
    case OPTION_AUTOSAVE: {
        int index = 0, i;
        for (i = 0; i < AUTOSAVE_CHOICE_COUNT; ++i)
            if (g_autosave_choices[i] == g_autosave_minutes) index = i;
        index = (index + step + AUTOSAVE_CHOICE_COUNT) % AUTOSAVE_CHOICE_COUNT;
        g_autosave_minutes = g_autosave_choices[index];
        save_video_settings();
        break;
    }
    case OPTION_LOAD_PAUSED: options_flip(&g_load_starts_paused); break;
    default: options_flip(&g_clip_all_training); break;
    }
}

static void options_toggle(void)
{
    if (!g_options_open && !options_panel_screen()) return;
    g_options_open = !g_options_open;
    g_options_page = 0;
    if (g_options_open && options_screen()) slide_panel_close_now();
}

static int options_panel_bottom(void)
{
    return OPTIONS_ROW_TOP + OPTION_COUNT * OPTIONS_ROW_HEIGHT + 34;
}

/* Row under a logical point, or -1. */
static int options_row_at(int x, int y)
{
    int row;
    if (x < OPTIONS_LEFT + 10 || x >= OPTIONS_LEFT + OPTIONS_WIDTH - 10 ||
        y < OPTIONS_ROW_TOP) return -1;
    row = (y - OPTIONS_ROW_TOP) / OPTIONS_ROW_HEIGHT;
    return row < OPTION_COUNT ? row : -1;
}

/* A press while the panel is open: a row changes (left arrow: back), outside
   the panel closes it. Always consumed. */
static int options_press(HWND window, int x, int y)
{
    int row;
    if (!g_options_open) return 0;
    if (x < OPTIONS_LEFT || x >= OPTIONS_LEFT + OPTIONS_WIDTH ||
        y < OPTIONS_TOP || y >= options_panel_bottom()) {
        g_options_open = 0;
        return 1;
    }
    if (g_options_page == 1) return shortcut_page_press(window, x, y);
    row = options_row_at(x, y);
    if (row >= 0) {
        g_options_row = row;
        options_change(window, row,
                       x >= OPTIONS_VALUE_LEFT - 4 && x < OPTIONS_VALUE_LEFT + 14 ? -1 : 1);
    }
    return 1;
}

/* Keys while the panel is open; returns 1 when consumed. */
static int options_key(HWND window, WPARAM key)
{
    if (!g_options_open) return 0;
    if (g_options_page == 1) return shortcut_page_key(window, key);
    if (key == VK_RETURN && g_options_row == OPTION_SHORTCUT_KEYS) {
        g_options_page = 1;
    } else if (key == VK_ESCAPE || key == VK_F2 || key == VK_RETURN) {
        g_options_open = 0;
    } else if (key == VK_UP) {
        g_options_row = (g_options_row + OPTION_COUNT - 1) % OPTION_COUNT;
    } else if (key == VK_DOWN) {
        g_options_row = (g_options_row + 1) % OPTION_COUNT;
    } else if (key == VK_LEFT || key == VK_RIGHT) {
        options_change(window, g_options_row, key == VK_RIGHT ? 1 : -1);
    }
    return 1;
}

static void options_frame_rect(RenderSurface *surface, int left, int top,
                               int right, int bottom, COLORREF color)
{
    fill_rect(surface, left, top, right, top + 1, color);
    fill_rect(surface, left, bottom - 1, right, bottom, color);
    fill_rect(surface, left, top, left + 1, bottom, color);
    fill_rect(surface, right - 1, top, right, bottom, color);
}

static void options_label(RenderSurface *surface, const char *text, int x, int y,
                          COLORREF color)
{
    if (g_big_font.bytes != NULL) draw_big_label(surface, text, x, y, color);
    else draw_bitmap_label(surface, text, x, y, color);
}

static int options_text_width(const char *text)
{
    return g_big_font.bytes != NULL
        ? (int)measure_big_text(text, strlen(text))
        : (int)measure_bitmap_text(NULL, text, strlen(text));
}

static void render_options_panel(RenderSurface *surface)
{
    const COLORREF frame = RGB(64, 200, 210);
    const COLORREF text = RGB(230, 238, 255);
    const COLORREF dim = RGB(150, 160, 180);
    const COLORREF accent = RGB(255, 210, 120);
    int bottom = options_panel_bottom();
    int hover = g_mouse_inside ? options_row_at(g_mouse_x, g_mouse_y) : -1;
    int row;
    const char *title = TR(T_OPT_TITLE);
    if (!g_options_open) return;
    fill_rect(surface, OPTIONS_LEFT, OPTIONS_TOP, OPTIONS_LEFT + OPTIONS_WIDTH,
              bottom, RGB(16, 10, 18));
    options_frame_rect(surface, OPTIONS_LEFT, OPTIONS_TOP,
                       OPTIONS_LEFT + OPTIONS_WIDTH, bottom, frame);
    options_frame_rect(surface, OPTIONS_LEFT + 3, OPTIONS_TOP + 3,
                       OPTIONS_LEFT + OPTIONS_WIDTH - 3, bottom - 3, frame);
    options_label(surface, title,
                  OPTIONS_LEFT + (OPTIONS_WIDTH - options_text_width(title)) / 2,
                  OPTIONS_TOP + 10, accent);
    if (g_options_page == 1) {
        render_shortcut_page(surface);
        return;
    }
    for (row = 0; row < OPTION_COUNT; ++row) {
        char value[64];
        int y = OPTIONS_ROW_TOP + row * OPTIONS_ROW_HEIGHT;
        int selected = row == g_options_row;
        if (selected || row == hover)
            fill_rect(surface, OPTIONS_LEFT + 10, y - 2,
                      OPTIONS_LEFT + OPTIONS_WIDTH - 10, y + OPTIONS_ROW_HEIGHT - 4,
                      selected ? RGB(60, 34, 44) : RGB(38, 24, 32));
        options_label(surface, TR(g_option_labels[row]), OPTIONS_LEFT + 20, y + 3,
                      selected ? accent : text);
        options_value_text(row, value, sizeof(value));
        options_label(surface, "<", OPTIONS_VALUE_LEFT, y + 3, dim);
        options_label(surface, ">", OPTIONS_VALUE_RIGHT - options_text_width(">"),
                      y + 3, dim);
        options_label(surface, value,
                      (OPTIONS_VALUE_LEFT + OPTIONS_VALUE_RIGHT -
                       options_text_width(value)) / 2, y + 3, text);
    }
    {
        const char *help = TR(T_OPT_HELP);
        options_label(surface, help,
                      OPTIONS_LEFT + (OPTIONS_WIDTH - options_text_width(help)) / 2,
                      bottom - 22, dim);
    }
}

/* The claw's caption on the SlideWindow panel (offset d while it slides). */
static void render_options_claw_caption(RenderSurface *surface, int d)
{
    const char *caption = TR(T_OPT_CLAW);
    int hovered = g_slide_phase == 2 && g_mouse_inside &&
        g_mouse_x >= OPTIONS_CLAW_LEFT && g_mouse_x <= OPTIONS_CLAW_RIGHT &&
        g_mouse_y >= OPTIONS_CLAW_TOP && g_mouse_y <= OPTIONS_CLAW_BOTTOM;
    draw_bitmap_label(surface, caption,
                      (OPTIONS_CLAW_LEFT + OPTIONS_CLAW_RIGHT -
                       (int)measure_bitmap_text(NULL, caption, strlen(caption))) / 2,
                      d + 42, hovered ? RGB(255, 210, 120) : RGB(230, 238, 255));
}
