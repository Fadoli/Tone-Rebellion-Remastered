/* Multiplayer setup screen (remake only). The original opens a DirectPlay
   property sheet (FUN_0044c2b9) outside windows.txt states 0..8, so there is
   no native screen to port: this one edits the player name, host address and
   port, then hosts or joins and leaves for the New Game lobby. Values are
   kept in saves\network.cfg; --name/--port/--join still override them. */

enum { NET_SETUP_FIELD_NAME, NET_SETUP_FIELD_ADDRESS, NET_SETUP_FIELD_PORT,
       NET_SETUP_FIELD_COUNT };
enum { NET_SETUP_BUTTON_NONE = -1, NET_SETUP_BUTTON_HOST, NET_SETUP_BUTTON_JOIN,
       NET_SETUP_BUTTON_BACK, NET_SETUP_BUTTON_COUNT };
enum { NET_SETUP_PORT_CAPACITY = 6 };

static int g_net_setup_field = NET_SETUP_FIELD_ADDRESS;
static int g_net_setup_hover = NET_SETUP_BUTTON_NONE;
static int g_net_setup_title_hover;
/* The title-screen M key also yields WM_CHAR 'm' (repeats included) until
   its WM_KEYUP. */
static int g_net_setup_swallow_char;
static char g_net_setup_port[NET_SETUP_PORT_CAPACITY];

/* Panel, field and button rectangles in logical 640x480 coordinates. */
static const RECT g_net_setup_panel = {120, 90, 520, 410};
static const RECT g_net_setup_fields[NET_SETUP_FIELD_COUNT] = {
    {290, 146, 496, 174}, {290, 184, 496, 212}, {290, 222, 380, 250}};
static const RECT g_net_setup_buttons[NET_SETUP_BUTTON_COUNT] = {
    {150, 310, 300, 352}, {340, 310, 490, 352}, {245, 360, 395, 398}};
static const char *const g_net_setup_field_labels[NET_SETUP_FIELD_COUNT] = {
    "Nom du joueur", "Adresse de l'hote", "Port"};
static const char *const g_net_setup_button_labels[NET_SETUP_BUTTON_COUNT] = {
    "HEBERGER", "REJOINDRE", "RETOUR"};
/* Title-screen entry, in the free band right of EXITAPP (255..375, 407..469),
   sized like the TITSCRN buttons. */
static const RECT g_net_setup_title_button = {448, 414, 598, 458};

static int net_setup_point_in(const RECT *rect, int x, int y)
{
    return x >= rect->left && x < rect->right && y >= rect->top && y < rect->bottom;
}

static char *net_setup_field_text(int field, size_t *capacity)
{
    if (field == NET_SETUP_FIELD_NAME) {
        *capacity = sizeof(g_net_name);
        return g_net_name;
    }
    if (field == NET_SETUP_FIELD_ADDRESS) {
        *capacity = sizeof(g_net_join_address);
        return g_net_join_address;
    }
    *capacity = sizeof(g_net_setup_port);
    return g_net_setup_port;
}

static int net_setup_config_path(char *path, size_t capacity)
{
    char directory[MAX_PATH];
    if (!save_directory(directory, sizeof(directory))) return 0;
    (void)snprintf(path, capacity, "%s\\network.cfg", directory);
    return 1;
}

/* Reads name=, address= and port= lines; unknown or malformed lines are
   ignored so a hand-edited file cannot block the title screen. */
static void net_setup_load_config(void)
{
    char path[MAX_PATH];
    char line[160];
    FILE *file;
    if (!net_setup_config_path(path, sizeof(path))) return;
    file = fopen(path, "r");
    if (file == NULL) return;
    while (fgets(line, sizeof(line), file) != NULL) {
        char *value = strchr(line, '=');
        size_t length;
        if (value == NULL) continue;
        *value++ = '\0';
        length = strcspn(value, "\r\n");
        value[length] = '\0';
        if (strcmp(line, "name") == 0 && value[0] != '\0')
            (void)snprintf(g_net_name, sizeof(g_net_name), "%s", value);
        else if (strcmp(line, "address") == 0 && value[0] != '\0')
            (void)snprintf(g_net_join_address, sizeof(g_net_join_address), "%s", value);
        else if (strcmp(line, "port") == 0 && atoi(value) > 0 && atoi(value) < 65536)
            g_net_port = (unsigned short)atoi(value);
    }
    (void)fclose(file);
}

static void net_setup_save_config(void)
{
    char path[MAX_PATH];
    FILE *file;
    if (!net_setup_config_path(path, sizeof(path))) return;
    file = fopen(path, "w");
    if (file == NULL) return;
    (void)fprintf(file, "name=%s\naddress=%s\nport=%u\n", g_net_name,
                  g_net_join_address, (unsigned)g_net_port);
    (void)fclose(file);
}

static void enter_net_setup_screen(void)
{
    net_default_name();
    (void)snprintf(g_net_setup_port, sizeof(g_net_setup_port), "%u", (unsigned)g_net_port);
    g_net_setup_hover = NET_SETUP_BUTTON_NONE;
    g_menu.screen = SCREEN_NET_SETUP;
}

/* Checks the edited fields and copies the port; returns 0 with a status. */
static int net_setup_validate(int joining)
{
    int port = atoi(g_net_setup_port);
    if (g_net_name[0] == '\0') {
        g_net_setup_field = NET_SETUP_FIELD_NAME;
        net_set_status("Indiquez un nom de joueur");
        return 0;
    }
    if (port <= 0 || port >= 65536) {
        g_net_setup_field = NET_SETUP_FIELD_PORT;
        net_set_status("Port invalide (1..65535)");
        return 0;
    }
    if (joining && g_net_join_address[0] == '\0') {
        g_net_setup_field = NET_SETUP_FIELD_ADDRESS;
        net_set_status("Indiquez l'adresse de l'hote");
        return 0;
    }
    g_net_port = (unsigned short)port;
    return 1;
}

static void net_setup_activate(HWND window, int button)
{
    (void)window;
    if (button == NET_SETUP_BUTTON_BACK) {
        net_leave_lobby();
        g_menu.screen = SCREEN_MAIN_MENU;
        return;
    }
    if (button != NET_SETUP_BUTTON_HOST && button != NET_SETUP_BUTTON_JOIN) return;
    if (!net_setup_validate(button == NET_SETUP_BUTTON_JOIN)) return;
    net_setup_save_config();
    if (button == NET_SETUP_BUTTON_HOST ? net_start_host() : net_start_join()) {
        g_menu.screen = SCREEN_NEW_GAME;
        g_menu.setup_accepted = 0;
    }
}

/* New Game exit (Esc or the native exit control): a lobby goes back to the
   multiplayer setup screen, a solo setup to the title. */
static void leave_new_game_screen(void)
{
    const int networked = g_net_mode != NET_MODE_NONE;
    net_leave_lobby();
    g_menu.setup_accepted = 0;
    if (networked) enter_net_setup_screen();
    else g_menu.screen = SCREEN_MAIN_MENU;
}

static int net_setup_button_at(int x, int y)
{
    int button;
    for (button = 0; button < NET_SETUP_BUTTON_COUNT; ++button)
        if (net_setup_point_in(&g_net_setup_buttons[button], x, y)) return button;
    return NET_SETUP_BUTTON_NONE;
}

/* Returns 1 when the hovered button changed and the screen must repaint. */
static int update_net_setup_hover(int x, int y)
{
    int hover = g_menu.screen == SCREEN_NET_SETUP ? net_setup_button_at(x, y)
                                                  : NET_SETUP_BUTTON_NONE;
    int title_hover = g_menu.screen == SCREEN_MAIN_MENU &&
                      net_setup_point_in(&g_net_setup_title_button, x, y);
    int changed = hover != g_net_setup_hover || title_hover != g_net_setup_title_hover;
    g_net_setup_hover = hover;
    g_net_setup_title_hover = title_hover;
    return changed;
}

/* Title screen: returns 1 if the click opened the setup screen. */
static int net_setup_title_click(int x, int y)
{
    if (!net_setup_point_in(&g_net_setup_title_button, x, y)) return 0;
    enter_net_setup_screen();
    return 1;
}

static void net_setup_click(HWND window, int x, int y)
{
    int field;
    for (field = 0; field < NET_SETUP_FIELD_COUNT; ++field)
        if (net_setup_point_in(&g_net_setup_fields[field], x, y)) {
            g_net_setup_field = field;
            return;
        }
    net_setup_activate(window, net_setup_button_at(x, y));
}

static void net_setup_key(HWND window, WPARAM key)
{
    if (key == VK_ESCAPE) {
        net_setup_activate(window, NET_SETUP_BUTTON_BACK);
    } else if (key == VK_RETURN) {
        /* Return joins; hosting is one click on its button. */
        net_setup_activate(window, NET_SETUP_BUTTON_JOIN);
    } else if (key == VK_TAB || key == VK_DOWN) {
        g_net_setup_field = (g_net_setup_field + (GetKeyState(VK_SHIFT) < 0 ? -1 : 1) +
                             NET_SETUP_FIELD_COUNT) % NET_SETUP_FIELD_COUNT;
    } else if (key == VK_UP) {
        g_net_setup_field = (g_net_setup_field + NET_SETUP_FIELD_COUNT - 1) %
                            NET_SETUP_FIELD_COUNT;
    }
}

/* WM_CHAR: printable ASCII the fonts can draw; Backspace erases. */
static int net_setup_char(WPARAM code)
{
    size_t capacity;
    char *text = net_setup_field_text(g_net_setup_field, &capacity);
    size_t length = strlen(text);
    if (g_net_setup_swallow_char && (code == 'm' || code == 'M')) return 0;
    if (code =='\b') {
        if (length == 0U) return 0;
        text[length - 1U] = '\0';
        return 1;
    }
    if (code < 32U || code > 126U || length + 1U >= capacity) return 0;
    if (g_net_setup_field == NET_SETUP_FIELD_PORT && (code < '0' || code > '9')) return 0;
    if (g_net_setup_field == NET_SETUP_FIELD_ADDRESS && code == ' ') return 0;
    text[length] = (char)code;
    text[length + 1U] = '\0';
    return 1;
}

/* Rounded box drawn in the back buffer, modelled on the TITSCRN buttons: a dark
   outline, a light blue rim of `rim` pixels and a fill fading from `centre`
   to `edge`, blended over the background with `alpha` (0..256). */
static void net_setup_draw_box(RenderSurface *surface, const RECT *rect,
                               int rim, COLORREF border,
                               COLORREF centre, COLORREF edge, int alpha)
{
    const float radius = 5.0f;
    const float half_width = (float)(rect->right - rect->left) * 0.5f;
    const float half_height = (float)(rect->bottom - rect->top) * 0.5f;
    int x;
    int y;
    if (surface->pixels == NULL) return;
    for (y = rect->top; y < rect->bottom; ++y) {
        if (y < 0 || y >= LOGICAL_HEIGHT) continue;
        for (x = rect->left; x < rect->right; ++x) {
            uint32_t *pixel;
            float dx = (float)(x < (rect->left + rect->right) / 2 ? x - rect->left
                                                                  : rect->right - 1 - x);
            float dy = (float)(y < (rect->top + rect->bottom) / 2 ? y - rect->top
                                                                  : rect->bottom - 1 - y);
            float inset = dx < dy ? dx : dy;
            COLORREF color;
            int keep = 256 - alpha;
            if (x < 0 || x >= LOGICAL_WIDTH) continue;
            if (dx < radius && dy < radius) {
                float cx = radius - dx;
                float cy = radius - dy;
                inset = radius - (float)sqrt((double)(cx * cx + cy * cy));
            }
            if (inset < 0.0f) continue;
            if (inset < 1.0f) {
                color = RGB(6, 8, 30);
                keep = 0;
            } else if (inset < 1.0f + (float)rim) {
                color = border;
                keep = 0;
            } else {
                /* Elliptic distance from the centre: 0 there, 1 at the corners. */
                float nx = ((float)x - (float)rect->left - half_width) / half_width;
                float ny = ((float)y - (float)rect->top - half_height) / half_height;
                float t = (float)sqrt((double)(nx * nx + ny * ny) * 0.5);
                if (t > 1.0f) t = 1.0f;
                color = RGB((int)(GetRValue(centre) + (GetRValue(edge) - GetRValue(centre)) * t),
                            (int)(GetGValue(centre) + (GetGValue(edge) - GetGValue(centre)) * t),
                            (int)(GetBValue(centre) + (GetBValue(edge) - GetBValue(centre)) * t));
            }
            pixel = &surface->pixels[(ptrdiff_t)y * surface->stride + x];
            *pixel = (((((*pixel >> 16) & 0xFFU) * (DWORD)keep >> 8) +
                       ((DWORD)GetRValue(color) * (DWORD)(256 - keep) >> 8)) << 16) |
                     (((((*pixel >> 8) & 0xFFU) * (DWORD)keep >> 8) +
                       ((DWORD)GetGValue(color) * (DWORD)(256 - keep) >> 8)) << 8) |
                     (((*pixel & 0xFFU) * (DWORD)keep >> 8) +
                      ((DWORD)GetBValue(color) * (DWORD)(256 - keep) >> 8));
        }
    }
}

/* Two-pixel-wide BGOUTFNT caption with a one-pixel halo, like the heavy,
   glowing captions baked into the title buttons. */
static void net_setup_draw_glow_text(RenderSurface *surface, const char *text, int x, int y,
                                     COLORREF ink, COLORREF glow)
{
    static const POINT offsets[6] = {{-1, 0}, {2, 0}, {0, -1}, {1, -1}, {0, 1}, {1, 1}};
    int i;
    for (i = 0; i < 6; ++i)
        draw_bitmap_label(surface, text, x + offsets[i].x, y + offsets[i].y, glow);
    draw_bitmap_label(surface, text, x, y, ink);
    draw_bitmap_label(surface, text, x + 1, y, ink);
}

static void net_setup_draw_centred_text(RenderSurface *surface, const RECT *rect, const char *text,
                                        COLORREF ink, COLORREF glow)
{
    int width = (int)measure_plain_bitmap_text(text, strlen(text));
    net_setup_draw_glow_text(surface, text, (rect->left + rect->right - width) / 2,
                             (rect->top + rect->bottom - (int)g_bitmap_font.height) / 2,
                             ink, glow);
}

static void net_setup_draw_button(RenderSurface *surface, const RECT *rect, const char *label, int hovered)
{
    net_setup_draw_box(surface, rect, 2, hovered ? RGB(205, 238, 255) : RGB(118, 178, 222),
                       hovered ? RGB(92, 128, 214) : RGB(66, 92, 176),
                       hovered ? RGB(36, 44, 120) : RGB(24, 30, 92), 256);
    net_setup_draw_centred_text(surface, rect, label,
                                hovered ? RGB(255, 255, 255) : RGB(222, 238, 255),
                                hovered ? RGB(70, 140, 230) : RGB(30, 60, 150));
}

/* Drawn over the title art by render_main_menu's caller. */
static void render_net_setup_title_button(RenderSurface *surface)
{
    net_setup_draw_button(surface, &g_net_setup_title_button, "MULTIJOUEUR",
                          g_net_setup_title_hover);
}

static void render_net_setup(RenderSurface *surface)
{
    static const char *const title = "PARTIE MULTIJOUEUR";
    static const RECT title_band = {120, 100, 520, 132};
    const COLORREF label_ink = RGB(150, 196, 236);
    int field;
    int button;
    fill_rect(surface, 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT, RGB(0, 0, 0));
    draw_sprite(surface, &g_title_art, 0, 0, 0);
    net_setup_draw_box(surface, &g_net_setup_panel, 2, RGB(118, 178, 222), RGB(20, 26, 70),
                       RGB(6, 6, 26), 216);
    net_setup_draw_centred_text(surface, &title_band, title, RGB(222, 238, 255),
                                RGB(30, 60, 150));
    for (field = 0; field < NET_SETUP_FIELD_COUNT; ++field) {
        const RECT *box = &g_net_setup_fields[field];
        const int focused = field == g_net_setup_field;
        const int text_y = (box->top + box->bottom - (int)g_bitmap_font.height) / 2;
        size_t capacity;
        const char *value = net_setup_field_text(field, &capacity);
        draw_bitmap_label(surface, g_net_setup_field_labels[field], 146, text_y, label_ink);
        net_setup_draw_box(surface, box, 1, focused ? RGB(160, 220, 255) : RGB(70, 110, 170),
                           RGB(4, 6, 24), RGB(4, 6, 24), 240);
        draw_bitmap_label(surface, value, box->left + 7, text_y, RGB(240, 246, 255));
        if (focused && (GetTickCount() / 500U) % 2U == 0U) {
            int caret_x = box->left + 8 + (int)measure_plain_bitmap_text(value, strlen(value));
            fill_rect(surface, caret_x, box->top + 6, caret_x + 2, box->bottom - 6,
                      RGB(205, 238, 255));
        }
    }
    draw_small_label(surface, "Tab: champ suivant   Entree: rejoindre   Echap: retour",
                     146, 268, RGB(110, 140, 190));
    draw_small_label(surface, g_net_status, 146, 284, RGB(255, 220, 120));
    for (button = 0; button < NET_SETUP_BUTTON_COUNT; ++button)
        net_setup_draw_button(surface, &g_net_setup_buttons[button],
                              g_net_setup_button_labels[button],
                              button == g_net_setup_hover);
}
