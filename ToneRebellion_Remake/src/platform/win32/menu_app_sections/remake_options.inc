/* Remake options (remake extension, no native counterpart): a panel over
   the island and the world map for the port's own settings. F2 opens or
   closes it, and so does the left claw of the SlideWindow options panel.
   Up/Down pick a row, Left/Right or a click change its value, Escape, F2 or
   Enter close it. The game keeps running behind it. Choices persist in
   saves\video.cfg and saves\audio.cfg. */

enum {
    OPTION_PAINT_RATE,
    OPTION_SCALE,
    OPTION_GAME_SPEED,
    OPTION_MUSIC,
    OPTION_SOUND,
    OPTION_LOAD_PAUSED,
    OPTION_CLIPBOARD,
    OPTION_COUNT
};

enum {
    OPTIONS_LEFT = 110, OPTIONS_TOP = 70, OPTIONS_WIDTH = 420,
    OPTIONS_ROW_TOP = 112, OPTIONS_ROW_HEIGHT = 24,
    OPTIONS_VALUE_LEFT = 330, OPTIONS_VALUE_RIGHT = 515,
    /* SlideWindow left claw (no native control there). */
    OPTIONS_CLAW_LEFT = 6, OPTIONS_CLAW_TOP = 6,
    OPTIONS_CLAW_RIGHT = 88, OPTIONS_CLAW_BOTTOM = 92
};

static int g_options_open;
static int g_options_row;
/* Remake choices kept in video.cfg. */
static int g_load_starts_paused = 1;
static int g_clip_all_training = 1;

static void set_scale_mode(HWND window, int mode);
static void set_paint_rate(HWND window, int index);
static void slide_toggle_music(void);
static void slide_toggle_sound(void);

static const char *const g_option_labels[OPTION_COUNT] = {
    "Frequence d'affichage",
    "Mise a l'echelle",
    "Vitesse du jeu",
    "Musique",
    "Effets sonores",
    "Partie chargee en pause",
    "Presse-papiers"
};

static int options_screen(void)
{
    return g_menu.screen == SCREEN_ISLAND || g_menu.screen == SCREEN_WORLD_MAP;
}

static int options_game_speed(void)
{
    if (g_net_in_game)
        return g_game_session.network_speed >= 1U &&
               g_game_session.network_speed <= 3U
                   ? (int)g_game_session.network_speed : 1;
    return (int)g_sim_speed;
}

static void options_value_text(int row, char *text, size_t capacity)
{
    static const char *const scales[SCALE_MODE_COUNT] = {
        "Multiples entiers", "Remplir (net)", "Remplir (lisse)"
    };
    switch (row) {
    case OPTION_PAINT_RATE:
        (void)snprintf(text, capacity, "%u Hz%s", g_paint_rates[g_paint_rate_index],
                       g_paint_rate_index == 0 ? " (original)" : "");
        break;
    case OPTION_SCALE:
        (void)snprintf(text, capacity, "%s", scales[g_scale_mode]);
        break;
    case OPTION_GAME_SPEED:
        (void)snprintf(text, capacity, "%d", options_game_speed());
        break;
    case OPTION_MUSIC:
        (void)snprintf(text, capacity, "%s", g_music_enabled ? "Oui" : "Non");
        break;
    case OPTION_SOUND:
        (void)snprintf(text, capacity, "%s", g_sound_enabled ? "Oui" : "Non");
        break;
    case OPTION_LOAD_PAUSED:
        (void)snprintf(text, capacity, "%s", g_load_starts_paused ? "Oui" : "Non (original)");
        break;
    default:
        (void)snprintf(text, capacity, "%s", g_clip_all_training
            ? "Tous les batiments" : "Selection (original)");
        break;
    }
}

/* Steps the row's value by `step` (+1 / -1), wrapping. */
static void options_change(HWND window, int row, int step)
{
    switch (row) {
    case OPTION_PAINT_RATE:
        set_paint_rate(window, (g_paint_rate_index + step + PAINT_RATE_COUNT) %
                                   PAINT_RATE_COUNT);
        break;
    case OPTION_SCALE:
        set_scale_mode(window, (g_scale_mode + step + SCALE_MODE_COUNT) %
                                   SCALE_MODE_COUNT);
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
    case OPTION_LOAD_PAUSED:
        g_load_starts_paused = !g_load_starts_paused;
        save_video_settings();
        break;
    default:
        g_clip_all_training = !g_clip_all_training;
        save_video_settings();
        break;
    }
}

static void options_toggle(void)
{
    if (!g_options_open && !options_screen()) return;
    g_options_open = !g_options_open;
    if (g_options_open) slide_panel_close_now();
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
    if (key == VK_ESCAPE || key == VK_F2 || key == VK_RETURN) {
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
    const char *title = "Options du remake";
    if (!g_options_open) return;
    fill_rect(surface, OPTIONS_LEFT, OPTIONS_TOP, OPTIONS_LEFT + OPTIONS_WIDTH,
              bottom, RGB(16, 10, 18));
    options_frame_rect(surface, OPTIONS_LEFT, OPTIONS_TOP,
                       OPTIONS_LEFT + OPTIONS_WIDTH, bottom, frame);
    options_frame_rect(surface, OPTIONS_LEFT + 3, OPTIONS_TOP + 3,
                       OPTIONS_LEFT + OPTIONS_WIDTH - 3, bottom - 3, frame);
    options_label(surface, title,
                  OPTIONS_LEFT + (OPTIONS_WIDTH - options_text_width(title)) / 2,
                  OPTIONS_TOP + 14, accent);
    for (row = 0; row < OPTION_COUNT; ++row) {
        char value[64];
        int y = OPTIONS_ROW_TOP + row * OPTIONS_ROW_HEIGHT;
        int selected = row == g_options_row;
        if (selected || row == hover)
            fill_rect(surface, OPTIONS_LEFT + 10, y - 2,
                      OPTIONS_LEFT + OPTIONS_WIDTH - 10, y + OPTIONS_ROW_HEIGHT - 4,
                      selected ? RGB(60, 34, 44) : RGB(38, 24, 32));
        options_label(surface, g_option_labels[row], OPTIONS_LEFT + 20, y + 3,
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
        const char *help = "Fleches: choisir   F2 ou Echap: fermer";
        options_label(surface, help,
                      OPTIONS_LEFT + (OPTIONS_WIDTH - options_text_width(help)) / 2,
                      bottom - 24, dim);
    }
}

/* The claw's caption on the SlideWindow panel (offset d while it slides). */
static void render_options_claw_caption(RenderSurface *surface, int d)
{
    const char *caption = "Options";
    int hovered = g_slide_phase == 2 && g_mouse_inside &&
        g_mouse_x >= OPTIONS_CLAW_LEFT && g_mouse_x <= OPTIONS_CLAW_RIGHT &&
        g_mouse_y >= OPTIONS_CLAW_TOP && g_mouse_y <= OPTIONS_CLAW_BOTTOM;
    draw_bitmap_label(surface, caption,
                      (OPTIONS_CLAW_LEFT + OPTIONS_CLAW_RIGHT -
                       (int)measure_bitmap_text(NULL, caption, strlen(caption))) / 2,
                      d + 42, hovered ? RGB(255, 210, 120) : RGB(230, 238, 255));
}
