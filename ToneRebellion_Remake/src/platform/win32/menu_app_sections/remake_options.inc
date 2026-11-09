/* Remake options (remake extension, no native counterpart): a panel over
   the island and the world map for the port's own settings. F2 opens or
   closes it, and so does the left claw of the SlideWindow options panel.
   The rows sit in collapsible sections (a click, Enter or Left/Right on a
   header folds or opens it; saved as video.cfg `optfolds`) inside a list
   that scrolls with the wheel or the scrollbar. Up/Down pick a row,
   Left/Right or a click change its value, Escape, F2 or Enter close it. The game keeps running behind it. Choices persist in
   saves\video.cfg and saves\audio.cfg. F2 also opens it on the title
   screen (language and display settings before playing). */

/* In section order (g_option_sections). */
enum {
    OPTION_LANGUAGE,
    OPTION_PAINT_RATE,
    OPTION_SCALE,
    OPTION_WIDESCREEN,
    OPTION_FILTER,
    OPTION_VSYNC,
    OPTION_MUSIC,
    OPTION_SOUND,
    OPTION_SFX_OVERLAP,
    OPTION_GAME_SPEED,
    OPTION_ALERTS,
    OPTION_CRYPTIC,
    OPTION_LOAD_PAUSED,
    OPTION_CLIPBOARD,
    OPTION_SMOOTH_SCROLL,
    OPTION_EDGE_SCROLL,
    OPTION_SHORTCUTS,
    OPTION_SHORTCUT_KEYS,
    OPTION_QUICKSAVE,
    OPTION_AUTOSAVE,
    OPTION_COUNT
};

typedef struct OptionSection {
    RemakeTextId label;
    int first, end; /* options [first, end) */
} OptionSection;

static const OptionSection g_option_sections[] = {
    {T_OPT_SEC_DISPLAY, OPTION_LANGUAGE, OPTION_MUSIC},
    {T_OPT_SEC_AUDIO, OPTION_MUSIC, OPTION_GAME_SPEED},
    {T_OPT_SEC_GAME, OPTION_GAME_SPEED, OPTION_SMOOTH_SCROLL},
    {T_OPT_SEC_CONTROLS, OPTION_SMOOTH_SCROLL, OPTION_QUICKSAVE},
    {T_OPT_SEC_SAVES, OPTION_QUICKSAVE, OPTION_COUNT}
};
enum {
    OPTION_SECTION_COUNT = sizeof(g_option_sections) / sizeof(g_option_sections[0]),
    OPTION_LINE_MAX = OPTION_COUNT + OPTION_SECTION_COUNT
};

enum {
    OPTIONS_LEFT = 90, OPTIONS_TOP = 56, OPTIONS_WIDTH = 460,
    OPTIONS_ROW_TOP = 92, OPTIONS_ROW_HEIGHT = 19, OPTIONS_PAGE_ROWS = 16,
    OPTIONS_VALUE_LEFT = 340, OPTIONS_VALUE_RIGHT = 525,
    /* Rows end left of the scrollbar. */
    OPTIONS_ROW_LEFT = OPTIONS_LEFT + 10, OPTIONS_ROW_RIGHT = OPTIONS_LEFT + 438,
    OPTIONS_BAR_LEFT = OPTIONS_LEFT + 441, OPTIONS_BAR_RIGHT = OPTIONS_LEFT + 449,
    OPTIONS_BAR_TOP = OPTIONS_ROW_TOP - 2,
    OPTIONS_BAR_BOTTOM = OPTIONS_ROW_TOP + OPTIONS_PAGE_ROWS * OPTIONS_ROW_HEIGHT - 4,
    /* SlideWindow left claw (no native control there). */
    OPTIONS_CLAW_LEFT = 6, OPTIONS_CLAW_TOP = 6,
    OPTIONS_CLAW_RIGHT = 88, OPTIONS_CLAW_BOTTOM = 92
};

static int g_options_open;
/* Cursor: an option, or -(section + 1) for a section header. */
static int g_options_row;
/* First visible line of the settings list. */
static int g_options_first;
/* Scrollbar thumb held, and the grab point inside the thumb. */
static int g_options_drag;
static int g_options_drag_offset;
static int g_shortcut_first;
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
static int shortcut_page_total(void);

static const RemakeTextId g_option_labels[OPTION_COUNT] = {
    [OPTION_LANGUAGE] = T_OPT_LANGUAGE, [OPTION_PAINT_RATE] = T_OPT_PAINT_RATE,
    [OPTION_SCALE] = T_OPT_SCALE, [OPTION_WIDESCREEN] = T_OPT_WIDESCREEN,
    [OPTION_FILTER] = T_OPT_FILTER,
    [OPTION_VSYNC] = T_OPT_VSYNC, [OPTION_MUSIC] = T_OPT_MUSIC,
    [OPTION_SOUND] = T_OPT_SOUND, [OPTION_SFX_OVERLAP] = T_OPT_SFX_OVERLAP,
    [OPTION_GAME_SPEED] = T_OPT_GAME_SPEED, [OPTION_ALERTS] = T_OPT_ALERTS,
    [OPTION_CRYPTIC] = T_OPT_CRYPTIC, [OPTION_LOAD_PAUSED] = T_OPT_LOAD_PAUSED,
    [OPTION_CLIPBOARD] = T_OPT_CLIPBOARD, [OPTION_SMOOTH_SCROLL] = T_OPT_SMOOTH_SCROLL,
    [OPTION_EDGE_SCROLL] = T_OPT_EDGE_SCROLL, [OPTION_SHORTCUTS] = T_OPT_SHORTCUTS,
    [OPTION_SHORTCUT_KEYS] = T_OPT_SHORTCUT_KEYS, [OPTION_QUICKSAVE] = T_OPT_QUICKSAVE,
    [OPTION_AUTOSAVE] = T_OPT_AUTOSAVE
};

/* The visible lines: each section header, then its options unless folded. */
static int options_lines(int *items)
{
    int count = 0, section, option;
    for (section = 0; section < OPTION_SECTION_COUNT; ++section) {
        items[count++] = -(section + 1);
        if ((g_options_folds >> section) & 1) continue;
        for (option = g_option_sections[section].first;
             option < g_option_sections[section].end; ++option)
            items[count++] = option;
    }
    return count;
}

static int options_item_section(int item)
{
    int section;
    if (item < 0) return -item - 1;
    for (section = 0; section < OPTION_SECTION_COUNT; ++section)
        if (item < g_option_sections[section].end) return section;
    return 0;
}

static int options_folded(int section)
{
    return (g_options_folds >> section) & 1;
}

/* Line of the cursor; a cursor hidden in a folded section moves to its
   header. */
static int options_cursor_line(const int *items, int count)
{
    int line;
    for (line = 0; line < count; ++line)
        if (items[line] == g_options_row) return line;
    g_options_row = -(options_item_section(g_options_row) + 1);
    for (line = 0; line < count; ++line)
        if (items[line] == g_options_row) return line;
    return 0;
}

/* First visible line of the open page, and its line count. */
static int *options_page_first(void)
{
    return g_options_page == 1 ? &g_shortcut_first : &g_options_first;
}

static int options_page_total(void)
{
    int items[OPTION_LINE_MAX];
    return g_options_page == 1 ? shortcut_page_total() : options_lines(items);
}

static void options_scroll_clamp(void)
{
    int *first = options_page_first();
    int last = options_page_total() - OPTIONS_PAGE_ROWS;
    if (*first > last) *first = last;
    if (*first < 0) *first = 0;
}

/* Scrolls the open page by `lines` (mouse wheel, scrollbar track). */
static void options_scroll(int lines)
{
    *options_page_first() += lines;
    options_scroll_clamp();
}

/* Scrolls the settings list so the cursor shows. */
static void options_follow(void)
{
    int items[OPTION_LINE_MAX];
    int count = options_lines(items);
    int line = options_cursor_line(items, count);
    if (line < g_options_first) g_options_first = line;
    if (line >= g_options_first + OPTIONS_PAGE_ROWS)
        g_options_first = line - OPTIONS_PAGE_ROWS + 1;
    options_scroll_clamp();
}

static void options_fold(int section, int folded)
{
    if (folded) g_options_folds |= 1 << section;
    else g_options_folds &= ~(1 << section);
    g_options_row = -(section + 1);
    save_video_settings();
    options_follow();
}

/* Scrollbar thumb for `total` lines shown from `first`. */
static void options_thumb(int total, int first, int *top, int *bottom)
{
    int track = OPTIONS_BAR_BOTTOM - OPTIONS_BAR_TOP;
    int range = total - OPTIONS_PAGE_ROWS;
    int length = total > OPTIONS_PAGE_ROWS ? track * OPTIONS_PAGE_ROWS / total : track;
    if (length < 12) length = 12;
    *top = OPTIONS_BAR_TOP + (range > 0 ? (track - length) * first / range : 0);
    *bottom = *top + length;
}

/* Moves the held thumb to logical y. */
static void options_bar_drag(int y)
{
    int total = options_page_total();
    int range = total - OPTIONS_PAGE_ROWS;
    int top, bottom, track;
    if (range <= 0) return;
    options_thumb(total, 0, &top, &bottom);
    track = OPTIONS_BAR_BOTTOM - OPTIONS_BAR_TOP - (bottom - top);
    if (track <= 0) return;
    *options_page_first() = ((y - g_options_drag_offset - OPTIONS_BAR_TOP) * range +
                             track / 2) / track;
    options_scroll_clamp();
}

static void options_bar_release(void)
{
    if (!g_options_drag) return;
    g_options_drag = 0;
    platform_capture_mouse(NULL, 0);
}

/* A press on the scrollbar: the thumb is grabbed, the track pages. Returns 1
   when the press was on the bar. */
static int options_bar_press(HWND window, int x, int y)
{
    int total = options_page_total();
    int top, bottom;
    if (total <= OPTIONS_PAGE_ROWS || x < OPTIONS_BAR_LEFT - 2 ||
        x >= OPTIONS_BAR_RIGHT + 2 || y < OPTIONS_BAR_TOP || y >= OPTIONS_BAR_BOTTOM)
        return 0;
    options_thumb(total, *options_page_first(), &top, &bottom);
    if (y < top) {
        options_scroll(-OPTIONS_PAGE_ROWS);
    } else if (y >= bottom) {
        options_scroll(OPTIONS_PAGE_ROWS);
    } else {
        g_options_drag = 1;
        g_options_drag_offset = y - top;
        platform_capture_mouse(window, 1);
    }
    return 1;
}

static void render_options_scrollbar(RenderSurface *surface)
{
    int total = options_page_total();
    int top, bottom;
    int hovered;
    if (total <= OPTIONS_PAGE_ROWS) return;
    options_scroll_clamp();
    options_thumb(total, *options_page_first(), &top, &bottom);
    hovered = g_options_drag || (g_mouse_inside &&
        g_mouse_x >= OPTIONS_BAR_LEFT - 2 && g_mouse_x < OPTIONS_BAR_RIGHT + 2 &&
        g_mouse_y >= top && g_mouse_y < bottom);
    fill_rect(surface, OPTIONS_BAR_LEFT, OPTIONS_BAR_TOP, OPTIONS_BAR_RIGHT,
              OPTIONS_BAR_BOTTOM, RGB(38, 24, 32));
    fill_rect(surface, OPTIONS_BAR_LEFT + 1, top + 1, OPTIONS_BAR_RIGHT - 1, bottom - 1,
              hovered ? RGB(255, 210, 120) : RGB(64, 200, 210));
}

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
    case OPTION_WIDESCREEN:
        if (g_widescreen == WIDESCREEN_UNLIMITED)
            (void)snprintf(text, capacity, "%s", TR(T_ASPECT_UNLIMITED));
        else
            (void)snprintf(text, capacity, "%s%s",
                           g_widescreen == WIDESCREEN_16_9 ? "16:9"
                           : g_widescreen == WIDESCREEN_16_10 ? "16:10"
                           : g_widescreen == WIDESCREEN_21_9 ? "21:9" : "4:3",
                           g_widescreen == WIDESCREEN_4_3 ? TR(T_ORIGINAL_SUFFIX) : "");
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
    case OPTION_SFX_OVERLAP:
        (void)snprintf(text, capacity, "%s", options_yes_no(g_sfx_overlap));
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
    if (row < 0) { /* section header: Left folds, Right opens */
        options_fold(-row - 1, step < 0);
        return;
    }
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
    case OPTION_WIDESCREEN: {
        int at = 0;
        while (at < WIDESCREEN_COUNT - 1 && g_widescreen_order[at] != g_widescreen) ++at;
        g_widescreen = g_widescreen_order[(at + step + WIDESCREEN_COUNT) % WIDESCREEN_COUNT];
        save_video_settings();
        /* The frame changes shape: repaint the whole client. */
        platform_invalidate(window);
        break;
    }
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
    case OPTION_SFX_OVERLAP: options_flip(&g_sfx_overlap); break;
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
    options_bar_release();
    if (g_options_open) options_follow();
    if (g_options_open && options_screen()) slide_panel_close_now();
}

static int options_panel_bottom(void)
{
    return OPTIONS_ROW_TOP + OPTIONS_PAGE_ROWS * OPTIONS_ROW_HEIGHT + 34;
}

/* Shown line under a logical point (0 = top of the list), or -1. */
static int options_line_at(int x, int y)
{
    int line;
    if (x < OPTIONS_ROW_LEFT || x >= OPTIONS_ROW_RIGHT || y < OPTIONS_ROW_TOP) return -1;
    line = (y - OPTIONS_ROW_TOP) / OPTIONS_ROW_HEIGHT;
    return line < OPTIONS_PAGE_ROWS ? line : -1;
}

/* Item (option, or -(section + 1)) under a logical point, or OPTION_COUNT. */
static int options_row_at(int x, int y)
{
    int items[OPTION_LINE_MAX];
    int count = options_lines(items);
    int line = options_line_at(x, y);
    if (line < 0 || g_options_first + line >= count) return OPTION_COUNT;
    return items[g_options_first + line];
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
    if (options_bar_press(window, x, y)) return 1;
    if (g_options_page == 1) return shortcut_page_press(window, x, y);
    row = options_row_at(x, y);
    if (row < 0) {
        options_fold(-row - 1, !options_folded(-row - 1));
    } else if (row < OPTION_COUNT) {
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
    } else if (key == VK_RETURN && g_options_row < 0) {
        options_fold(-g_options_row - 1, !options_folded(-g_options_row - 1));
    } else if (key == VK_ESCAPE || key == VK_F2 || key == VK_RETURN) {
        g_options_open = 0;
        options_bar_release();
    } else if (key == VK_UP || key == VK_DOWN) {
        int items[OPTION_LINE_MAX];
        int count = options_lines(items);
        int line = options_cursor_line(items, count);
        line = (line + (key == VK_UP ? count - 1 : 1)) % count;
        g_options_row = items[line];
        options_follow();
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
    int hover = g_mouse_inside ? options_row_at(g_mouse_x, g_mouse_y) : OPTION_COUNT;
    int items[OPTION_LINE_MAX];
    int count = options_lines(items);
    int line;
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
    render_options_scrollbar(surface);
    if (g_options_page == 1) {
        render_shortcut_page(surface);
        return;
    }
    (void)options_cursor_line(items, count);
    for (line = 0; line < OPTIONS_PAGE_ROWS && g_options_first + line < count; ++line) {
        char value[64];
        int row = items[g_options_first + line];
        int y = OPTIONS_ROW_TOP + line * OPTIONS_ROW_HEIGHT;
        int selected = row == g_options_row;
        if (row < 0) { /* section header */
            int section = -row - 1;
            char caption[64];
            fill_rect(surface, OPTIONS_ROW_LEFT, y - 2, OPTIONS_ROW_RIGHT,
                      y + OPTIONS_ROW_HEIGHT - 4,
                      selected ? RGB(60, 34, 44)
                               : row == hover ? RGB(38, 34, 52) : RGB(26, 26, 42));
            (void)snprintf(caption, sizeof(caption), "%s %s",
                           options_folded(section) ? "+" : "-",
                           TR(g_option_sections[section].label));
            options_label(surface, caption, OPTIONS_ROW_LEFT + 4, y + 3,
                          selected ? accent : frame);
            continue;
        }
        if (selected || row == hover)
            fill_rect(surface, OPTIONS_ROW_LEFT, y - 2,
                      OPTIONS_ROW_RIGHT, y + OPTIONS_ROW_HEIGHT - 4,
                      selected ? RGB(60, 34, 44) : RGB(38, 24, 32));
        options_label(surface, TR(g_option_labels[row]), OPTIONS_ROW_LEFT + 14, y + 3,
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
