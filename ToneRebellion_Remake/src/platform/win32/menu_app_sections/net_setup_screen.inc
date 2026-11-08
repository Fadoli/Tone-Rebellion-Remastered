/* Multiplayer setup screens (remake only). The original opens a DirectPlay
   property sheet (FUN_0044c2b9) outside windows.txt states 0..8, so there is
   no native screen to port. Three pages:
   - choose: the player name, then Create or Join;
   - host: the port to listen on;
   - join: the server list (hosts joined before, most recent first; public
     lobbies will be added there by a future lobby server, see
     net_server_list.h), the address and the port.
   Then the New Game lobby. Values are kept in saves\network.cfg and the
   server list in saves\servers.cfg; --name/--port/--join still override. */

enum { NET_PAGE_CHOOSE, NET_PAGE_HOST, NET_PAGE_JOIN };
enum { NET_FIELD_NONE = -1, NET_FIELD_NAME, NET_FIELD_HOST_PORT, NET_FIELD_ADDRESS,
       NET_FIELD_JOIN_PORT, NET_FIELD_COUNT };
enum { NET_BUTTON_NONE = -1, NET_BUTTON_HOST, NET_BUTTON_JOIN, NET_BUTTON_QUIT,
       NET_BUTTON_CREATE, NET_BUTTON_CONNECT, NET_BUTTON_BACK, NET_BUTTON_COUNT };
enum { NET_SETUP_PORT_CAPACITY = 6, NET_SERVER_ROWS = 6, NET_SERVER_ROW_HEIGHT = 18 };

typedef struct NetSetupField {
    int page;
    RECT box;
    RemakeTextId label;
} NetSetupField;

typedef struct NetSetupButton {
    int page;
    RECT box;
    RemakeTextId first;  /* caption lines (remake_buttons.inc) */
    RemakeTextId second; /* "" in a language: a one-line button */
} NetSetupButton;

/* Logical 640x480 coordinates; the panel is {120, 90, 520, 410}. */
static const NetSetupField g_net_setup_fields[NET_FIELD_COUNT] = {
    {NET_PAGE_CHOOSE, {290, 170, 496, 198}, T_SETUP_NAME},
    {NET_PAGE_HOST, {290, 170, 380, 198}, T_SETUP_PORT},
    {NET_PAGE_JOIN, {290, 262, 496, 288}, T_SETUP_ADDRESS},
    {NET_PAGE_JOIN, {290, 294, 380, 320}, T_SETUP_PORT}};
/* TITSCRN-style buttons, 102x49. Host = CREER PARTIE, join = ENTRER
   PARTIE (no B, J, M or S among the original letters). */
static const NetSetupButton g_net_setup_buttons[NET_BUTTON_COUNT] = {
    {NET_PAGE_CHOOSE, {174, 300, 276, 349}, T_BTN_CREATE1, T_BTN_CREATE2},
    {NET_PAGE_CHOOSE, {364, 300, 466, 349}, T_BTN_JOIN1, T_BTN_JOIN2},
    {NET_PAGE_CHOOSE, {269, 352, 371, 401}, T_BTN_BACK, REMAKE_TEXT_COUNT},
    {NET_PAGE_HOST, {174, 352, 276, 401}, T_BTN_CREATE1, T_BTN_CREATE2},
    {NET_PAGE_JOIN, {174, 352, 276, 401}, T_BTN_JOIN1, T_BTN_JOIN2},
    {-1, {364, 352, 466, 401}, T_BTN_BACK, REMAKE_TEXT_COUNT}}; /* host and join pages */
static const RECT g_net_setup_panel = {120, 90, 520, 410};
static const RECT g_net_server_box = {140, 132, 500, 254};
/* Title-screen entry where LOADGAME's button stands one row up (LOADGAME
   draws frame 6 at 402 + 18), level with EXITAPP (407 + 9). */
static const RECT g_net_setup_title_button = {420, 416, 522, 465};

static int g_net_page = NET_PAGE_CHOOSE;
static int g_net_setup_field = NET_FIELD_NAME;
static int g_net_setup_hover = NET_BUTTON_NONE;
static int g_net_server_hover = -1;
static int g_net_setup_title_hover;
/* The title-screen M key also yields WM_CHAR 'm' (repeats included) until
   its WM_KEYUP. */
static int g_net_setup_swallow_char;
/* platform_ticks_ms() before which a trailing 'm' is still dropped. */
static uint32_t g_net_setup_swallow_until;
static char g_net_host_port_text[NET_SETUP_PORT_CAPACITY];
static char g_net_join_port_text[NET_SETUP_PORT_CAPACITY];
/* Port the host listens on; 0 = g_net_port (--port or network.cfg port=). */
static unsigned short g_net_host_port;
static NetServerList g_net_servers;
static int g_net_server_selected = -1;
static int g_net_server_scroll;

static int net_setup_point_in(const RECT *rect, int x, int y)
{
    return x >= rect->left && x < rect->right && y >= rect->top && y < rect->bottom;
}

static int net_button_on_page(int button)
{
    const int page = g_net_setup_buttons[button].page;
    return page == g_net_page || (page == -1 && g_net_page != NET_PAGE_CHOOSE);
}

static char *net_setup_field_text(int field, size_t *capacity)
{
    switch (field) {
    case NET_FIELD_NAME:
        *capacity = sizeof(g_net_name);
        return g_net_name;
    case NET_FIELD_ADDRESS:
        *capacity = sizeof(g_net_join_address);
        return g_net_join_address;
    case NET_FIELD_HOST_PORT:
        *capacity = sizeof(g_net_host_port_text);
        return g_net_host_port_text;
    default:
        *capacity = sizeof(g_net_join_port_text);
        return g_net_join_port_text;
    }
}

static int net_setup_save_path(const char *name, char *path, size_t capacity)
{
    char directory[MAX_PATH];
    if (!save_directory(directory, sizeof(directory))) return 0;
    (void)snprintf(path, capacity, "%s/%s", directory, name);
    return 1;
}

/* Reads name=, address=, port= and hostport= lines; unknown or malformed
   lines are ignored so a hand-edited file cannot block the title screen. */
static void net_setup_load_config(void)
{
    char path[MAX_PATH];
    char line[160];
    FILE *file;
    if (!net_setup_save_path("network.cfg", path, sizeof(path))) return;
    file = fopen(path, "r");
    if (file == NULL) return;
    while (fgets(line, sizeof(line), file) != NULL) {
        char *value = strchr(line, '=');
        size_t length;
        int number;
        if (value == NULL) continue;
        *value++ = '\0';
        length = strcspn(value, "\r\n");
        value[length] = '\0';
        number = atoi(value);
        if (strcmp(line, "name") == 0 && value[0] != '\0')
            (void)snprintf(g_net_name, sizeof(g_net_name), "%s", value);
        else if (strcmp(line, "address") == 0 && net_server_address_valid(value))
            (void)snprintf(g_net_join_address, sizeof(g_net_join_address), "%s", value);
        else if (strcmp(line, "port") == 0 && number > 0 && number < 65536)
            g_net_port = (unsigned short)number;
        else if (strcmp(line, "hostport") == 0 && number > 0 && number < 65536)
            g_net_host_port = (unsigned short)number;
    }
    (void)fclose(file);
}

static void net_setup_save_config(void)
{
    char path[MAX_PATH];
    FILE *file;
    if (!net_setup_save_path("network.cfg", path, sizeof(path))) return;
    file = fopen(path, "w");
    if (file == NULL) return;
    (void)fprintf(file, "name=%s\naddress=%s\nport=%u\nhostport=%u\n", g_net_name,
                  g_net_join_address, (unsigned)g_net_port,
                  (unsigned)(g_net_host_port != 0 ? g_net_host_port : g_net_port));
    (void)fclose(file);
    platform_storage_changed();
}

static void net_servers_load(void)
{
    char path[MAX_PATH];
    char text[8192];
    size_t length = 0;
    FILE *file;
    net_server_list_clear(&g_net_servers);
    if (!net_setup_save_path("servers.cfg", path, sizeof(path))) return;
    file = fopen(path, "rb");
    if (file == NULL) return;
    length = fread(text, 1, sizeof(text), file);
    (void)fclose(file);
    (void)net_server_list_parse(&g_net_servers, text, length);
}

static void net_servers_save(void)
{
    char path[MAX_PATH];
    char text[NET_SERVER_LIST_MAX * 200];
    size_t length = net_server_list_format(&g_net_servers, text, sizeof(text));
    FILE *file;
    if (!net_setup_save_path("servers.cfg", path, sizeof(path))) return;
    file = fopen(path, "wb");
    if (file == NULL) return;
    if (length != 0U) (void)fwrite(text, 1, length, file);
    (void)fclose(file);
    platform_storage_changed();
}

static void net_setup_set_page(int page)
{
    static const int first_field[3] = {NET_FIELD_NAME, NET_FIELD_HOST_PORT, NET_FIELD_ADDRESS};
    g_net_page = page;
    g_net_setup_field = first_field[page];
    g_net_setup_hover = NET_BUTTON_NONE;
    g_net_server_hover = -1;
    if (page == NET_PAGE_JOIN) {
        net_servers_load();
        g_net_server_selected = net_server_list_find(&g_net_servers, g_net_join_address,
                                                     g_net_port);
        g_net_server_scroll = 0;
        if (g_net_server_selected >= NET_SERVER_ROWS)
            g_net_server_scroll = g_net_server_selected - NET_SERVER_ROWS + 1;
    }
}

/* Shows the setup screen on the page in use (back from a lobby or after a
   failed join). */
static void enter_net_setup_screen(void)
{
    net_default_name();
    (void)snprintf(g_net_host_port_text, sizeof(g_net_host_port_text), "%u",
                   (unsigned)(g_net_host_port != 0 ? g_net_host_port : g_net_port));
    (void)snprintf(g_net_join_port_text, sizeof(g_net_join_port_text), "%u",
                   (unsigned)g_net_port);
    net_setup_set_page(g_net_page);
    g_menu.screen = SCREEN_NET_SETUP;
}

/* From the title: the first page. */
static void net_setup_open(void)
{
    g_net_page = NET_PAGE_CHOOSE;
    enter_net_setup_screen();
}

static int net_setup_port_value(const char *text)
{
    const int port = atoi(text);
    return port > 0 && port < 65536 ? port : 0;
}

/* Fills the address and port from a list entry. */
static void net_server_select(int index)
{
    const NetServerEntry *entry;
    if (index < 0 || (unsigned)index >= g_net_servers.count) return;
    entry = &g_net_servers.entries[index];
    g_net_server_selected = index;
    (void)snprintf(g_net_join_address, sizeof(g_net_join_address), "%s", entry->address);
    (void)snprintf(g_net_join_port_text, sizeof(g_net_join_port_text), "%u",
                   (unsigned)entry->port);
    if (index < g_net_server_scroll) g_net_server_scroll = index;
    if (index >= g_net_server_scroll + NET_SERVER_ROWS)
        g_net_server_scroll = index - NET_SERVER_ROWS + 1;
}

/* Client lobby update (net_session.inc): the host's name labels its entry.
   Also records hosts joined without this screen (--join, the title J key). */
static void net_setup_note_host_name(const char *host_name)
{
    int index;
    if (host_name == NULL || host_name[0] == '\0') return;
    net_servers_load();
    index = net_server_list_find(&g_net_servers, g_net_join_address, g_net_port);
    if (index >= 0 && strcmp(g_net_servers.entries[index].label, host_name) == 0) return;
    if (net_server_list_remember(&g_net_servers, g_net_join_address, g_net_port, host_name,
                                 (uint64_t)time(NULL)) == 0)
        net_servers_save();
}

static void net_setup_lobby_entered(void)
{
    g_menu.screen = SCREEN_NEW_GAME;
    g_menu.setup_accepted = 0;
}

static void net_setup_create(void)
{
    const int port = net_setup_port_value(g_net_host_port_text);
    if (port == 0) {
        g_net_setup_field = NET_FIELD_HOST_PORT;
        net_set_status(TR(T_SETUP_BAD_PORT));
        return;
    }
    g_net_host_port = (unsigned short)port;
    g_net_port = (unsigned short)port;
    net_setup_save_config();
    if (net_start_host()) net_setup_lobby_entered();
}

static void net_setup_connect(void)
{
    const int port = net_setup_port_value(g_net_join_port_text);
    if (!net_server_address_valid(g_net_join_address)) {
        g_net_setup_field = NET_FIELD_ADDRESS;
        net_set_status(TR(T_SETUP_NEED_ADDRESS));
        return;
    }
    if (port == 0) {
        g_net_setup_field = NET_FIELD_JOIN_PORT;
        net_set_status(TR(T_SETUP_BAD_PORT));
        return;
    }
    g_net_port = (unsigned short)port;
    net_setup_save_config();
    /* Every address tried is remembered, reachable or not. */
    if (net_server_list_remember(&g_net_servers, g_net_join_address, g_net_port, NULL,
                                 (uint64_t)time(NULL)) == 0) {
        g_net_server_selected = 0;
        g_net_server_scroll = 0;
        net_servers_save();
    }
    if (net_start_join()) net_setup_lobby_entered();
}

static void net_setup_activate(int button)
{
    switch (button) {
    case NET_BUTTON_HOST:
    case NET_BUTTON_JOIN:
        if (g_net_name[0] == '\0') {
            g_net_setup_field = NET_FIELD_NAME;
            net_set_status(TR(T_SETUP_NEED_NAME));
            return;
        }
        net_set_status("");
        net_setup_save_config();
        net_setup_set_page(button == NET_BUTTON_HOST ? NET_PAGE_HOST : NET_PAGE_JOIN);
        break;
    case NET_BUTTON_QUIT:
        net_leave_lobby();
        g_menu.screen = SCREEN_MAIN_MENU;
        break;
    case NET_BUTTON_BACK:
        net_set_status("");
        net_setup_set_page(NET_PAGE_CHOOSE);
        break;
    case NET_BUTTON_CREATE:
        net_setup_create();
        break;
    case NET_BUTTON_CONNECT:
        net_setup_connect();
        break;
    default:
        break;
    }
}

/* New Game exit (Esc or the native exit control): a lobby goes back to the
   page it was entered from, a solo setup to the title. */
static void leave_new_game_screen(void)
{
    if (g_net_mode != NET_MODE_NONE) {
        /* net_leave_lobby drops a loaded game with the lobby. */
        net_leave_lobby();
        g_menu.setup_accepted = 0;
        enter_net_setup_screen();
        return;
    }
    if (g_tribe_choice_mask != 0) {
        /* Leaving the tribe choice drops the loaded game. */
        g_tribe_choice_mask = 0;
        g_game_session_valid = 0;
        g_menu.screen = SCREEN_MAIN_MENU;
        return;
    }
    net_leave_lobby();
    g_menu.setup_accepted = 0;
    g_menu.screen = SCREEN_MAIN_MENU;
}

static int net_setup_button_at(int x, int y)
{
    int button;
    for (button = 0; button < NET_BUTTON_COUNT; ++button)
        if (net_button_on_page(button) &&
            net_setup_point_in(&g_net_setup_buttons[button].box, x, y)) return button;
    return NET_BUTTON_NONE;
}

static RECT net_server_row_rect(int row)
{
    RECT rect;
    rect.left = g_net_server_box.left + 4;
    rect.right = g_net_server_box.right - 4;
    rect.top = g_net_server_box.top + 6 + row * NET_SERVER_ROW_HEIGHT;
    rect.bottom = rect.top + NET_SERVER_ROW_HEIGHT;
    return rect;
}

/* List index under (x, y) on the join page, or -1. */
static int net_server_at(int x, int y)
{
    int row;
    if (g_net_page != NET_PAGE_JOIN) return -1;
    for (row = 0; row < NET_SERVER_ROWS; ++row) {
        const RECT rect = net_server_row_rect(row);
        const int index = g_net_server_scroll + row;
        if ((unsigned)index >= g_net_servers.count) break;
        if (net_setup_point_in(&rect, x, y)) return index;
    }
    return -1;
}

/* Returns 1 when a hover changed and the screen must repaint. */
static int update_net_setup_hover(int x, int y)
{
    const int on_setup = g_menu.screen == SCREEN_NET_SETUP;
    const int hover = on_setup ? net_setup_button_at(x, y) : NET_BUTTON_NONE;
    const int server = on_setup ? net_server_at(x, y) : -1;
    const int title_hover = g_menu.screen == SCREEN_MAIN_MENU &&
                            net_setup_point_in(&g_net_setup_title_button, x, y);
    const int changed = hover != g_net_setup_hover || server != g_net_server_hover ||
                        title_hover != g_net_setup_title_hover;
    g_net_setup_hover = hover;
    g_net_server_hover = server;
    g_net_setup_title_hover = title_hover;
    return changed;
}

/* Title screen: returns 1 if the click opened the setup screen. */
static int net_setup_title_click(int x, int y)
{
    if (!net_setup_point_in(&g_net_setup_title_button, x, y)) return 0;
    net_setup_open();
    return 1;
}

static void net_setup_click(HWND window, int x, int y)
{
    int field;
    const int server = net_server_at(x, y);
    (void)window;
    if (server >= 0) {
        /* A second click on the selected host joins it. */
        if (server == g_net_server_selected) {
            net_server_select(server);
            net_setup_connect();
        } else {
            net_server_select(server);
        }
        return;
    }
    for (field = 0; field < NET_FIELD_COUNT; ++field)
        if (g_net_setup_fields[field].page == g_net_page &&
            net_setup_point_in(&g_net_setup_fields[field].box, x, y)) {
            g_net_setup_field = field;
            return;
        }
    net_setup_activate(net_setup_button_at(x, y));
}

/* Next field of the page in `direction` (+1 / -1), wrapping. */
static void net_setup_cycle_field(int direction)
{
    int field = g_net_setup_field;
    int step;
    for (step = 0; step < NET_FIELD_COUNT; ++step) {
        field = (field + direction + NET_FIELD_COUNT) % NET_FIELD_COUNT;
        if (g_net_setup_fields[field].page == g_net_page) break;
    }
    g_net_setup_field = field;
}

static void net_setup_key(HWND window, WPARAM key)
{
    (void)window;
    if (key == VK_ESCAPE) {
        net_setup_activate(g_net_page == NET_PAGE_CHOOSE ? NET_BUTTON_QUIT : NET_BUTTON_BACK);
    } else if (key == VK_RETURN) {
        net_setup_activate(g_net_page == NET_PAGE_HOST ? NET_BUTTON_CREATE
                           : g_net_page == NET_PAGE_JOIN ? NET_BUTTON_CONNECT
                           : NET_BUTTON_JOIN);
    } else if (key == VK_TAB) {
        net_setup_cycle_field(platform_shift_down() ? -1 : 1);
    } else if (g_net_page == NET_PAGE_JOIN && (key == VK_UP || key == VK_DOWN) &&
               g_net_servers.count > 0) {
        int index = g_net_server_selected < 0 ? 0
                  : g_net_server_selected + (key == VK_DOWN ? 1 : -1);
        if (index < 0) index = 0;
        if ((unsigned)index >= g_net_servers.count) index = (int)g_net_servers.count - 1;
        net_server_select(index);
    } else if (key == VK_UP || key == VK_DOWN) {
        net_setup_cycle_field(key == VK_DOWN ? 1 : -1);
    } else if (key == VK_DELETE && g_net_page == NET_PAGE_JOIN &&
               g_net_server_selected >= 0 &&
               (unsigned)g_net_server_selected < g_net_servers.count) {
        /* Forget the selected host. */
        net_server_list_remove(&g_net_servers, (unsigned)g_net_server_selected);
        net_servers_save();
        if ((unsigned)g_net_server_selected >= g_net_servers.count)
            g_net_server_selected = (int)g_net_servers.count - 1;
        if (g_net_server_scroll > 0 &&
            (unsigned)(g_net_server_scroll + NET_SERVER_ROWS) > g_net_servers.count)
            --g_net_server_scroll;
        if (g_net_server_selected >= 0) net_server_select(g_net_server_selected);
    }
}

/* WM_CHAR: printable ASCII the fonts can draw; Backspace erases. */
static int net_setup_char(WPARAM code)
{
    size_t capacity;
    char *text;
    size_t length;
    if (g_net_setup_field == NET_FIELD_NONE) return 0;
    text = net_setup_field_text(g_net_setup_field, &capacity);
    length = strlen(text);
    if ((code == 'm' || code == 'M') &&
        (g_net_setup_swallow_char ||
         (int32_t)(g_net_setup_swallow_until - platform_ticks_ms()) > 0)) return 0;
    g_net_setup_swallow_until = platform_ticks_ms();
    if (code == '\b') {
        if (length == 0U) return 0;
        text[length - 1U] = '\0';
        if (g_net_setup_field == NET_FIELD_ADDRESS || g_net_setup_field == NET_FIELD_JOIN_PORT)
            g_net_server_selected = -1;
        return 1;
    }
    if (code < 32U || code > 126U || length + 1U >= capacity) return 0;
    if ((g_net_setup_field == NET_FIELD_HOST_PORT || g_net_setup_field == NET_FIELD_JOIN_PORT) &&
        (code < '0' || code > '9')) return 0;
    if (g_net_setup_field == NET_FIELD_ADDRESS && code == ' ') return 0;
    text[length] = (char)code;
    text[length + 1U] = '\0';
    if (g_net_setup_field == NET_FIELD_ADDRESS || g_net_setup_field == NET_FIELD_JOIN_PORT)
        g_net_server_selected = -1;
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

/* A TITSCRN-style button; without usable TITSCRN frames, a plain box. */
static void net_setup_draw_button(RenderSurface *surface, const RECT *rect,
                                  RemakeTextId first_id, RemakeTextId second_id, int hovered)
{
    char label[64];
    const char *first = TR(first_id);
    const char *second = second_id < REMAKE_TEXT_COUNT && TR(second_id)[0] != '\0'
        ? TR(second_id) : NULL;
    if (draw_remake_button(surface, rect->left, rect->top, first, second, hovered)) return;
    (void)snprintf(label, sizeof(label), "%s%s%s", first, second != NULL ? " " : "",
                   second != NULL ? second : "");
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
    net_setup_draw_button(surface, &g_net_setup_title_button, T_BTN_ONLINE1, T_BTN_ONLINE2,
                          g_net_setup_title_hover);
}

/* `text` cut with "..." to fit `width` pixels of BGOUTFNT. */
static void net_setup_fit_text(char *text, size_t capacity, int width)
{
    size_t length = strlen(text);
    if ((int)measure_plain_bitmap_text(text, length) <= width) return;
    while (length > 0U) {
        --length;
        if (length + 4U > capacity) continue;
        (void)memcpy(text + length, "...", 4U);
        if ((int)measure_plain_bitmap_text(text, length + 3U) <= width) return;
    }
}

static void render_net_server_list(RenderSurface *surface)
{
    const COLORREF ink = RGB(222, 238, 255);
    int row;
    net_setup_draw_box(surface, &g_net_server_box, 1, RGB(70, 110, 170), RGB(4, 6, 24),
                       RGB(4, 6, 24), 240);
    if (g_net_servers.count == 0U) {
        draw_small_label(surface, TR(T_SETUP_NO_RECENT),
                         g_net_server_box.left + 10, g_net_server_box.top + 12,
                         RGB(110, 140, 190));
        return;
    }
    for (row = 0; row < NET_SERVER_ROWS; ++row) {
        const int index = g_net_server_scroll + row;
        const NetServerEntry *entry;
        RECT rect;
        char text[NET_SERVER_ADDRESS_CAPACITY + NET_SERVER_LABEL_CAPACITY + 16];
        const char *tag;
        if ((unsigned)index >= g_net_servers.count) break;
        entry = &g_net_servers.entries[index];
        rect = net_server_row_rect(row);
        if (index == g_net_server_selected || index == g_net_server_hover)
            net_setup_draw_box(surface, &rect, 0, RGB(0, 0, 0),
                               index == g_net_server_selected ? RGB(52, 84, 170) : RGB(30, 44, 100),
                               index == g_net_server_selected ? RGB(30, 44, 120) : RGB(16, 24, 70),
                               200);
        if (entry->label[0] != '\0')
            (void)snprintf(text, sizeof(text), "%s - %s:%u", entry->label, entry->address,
                           (unsigned)entry->port);
        else
            (void)snprintf(text, sizeof(text), "%s:%u", entry->address, (unsigned)entry->port);
        net_setup_fit_text(text, sizeof(text), rect.right - rect.left - 70);
        draw_bitmap_label(surface, text, rect.left + 6,
                          (rect.top + rect.bottom - (int)g_bitmap_font.height) / 2, ink);
        tag = entry->source == NET_SERVER_SOURCE_PUBLIC ? TR(T_SETUP_TAG_PUBLIC) : TR(T_SETUP_TAG_RECENT);
        draw_small_label(surface, tag, rect.right - 56, rect.top + 5, RGB(110, 140, 190));
    }
    if (g_net_servers.count > NET_SERVER_ROWS) {
        char more[32];
        (void)snprintf(more, sizeof(more), "%d-%d / %u", g_net_server_scroll + 1,
                       g_net_server_scroll + NET_SERVER_ROWS, g_net_servers.count);
        draw_small_label(surface, more, g_net_server_box.right - 60,
                         g_net_server_box.bottom - 10, RGB(110, 140, 190));
    }
}

static void render_net_setup(RenderSurface *surface)
{
    static const RemakeTextId titles[3] = {
        T_SETUP_TITLE_CHOOSE, T_SETUP_TITLE_HOST, T_SETUP_TITLE_JOIN};
    static const RECT title_band = {120, 96, 520, 126};
    const COLORREF label_ink = RGB(150, 196, 236);
    const COLORREF hint_ink = RGB(110, 140, 190);
    int field;
    int button;
    fill_rect(surface, 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT, RGB(0, 0, 0));
    draw_sprite(surface, &g_title_art, 0, 0, 0);
    net_setup_draw_box(surface, &g_net_setup_panel, 2, RGB(118, 178, 222), RGB(20, 26, 70),
                       RGB(6, 6, 26), 216);
    net_setup_draw_centred_text(surface, &title_band, TR(titles[g_net_page]), RGB(222, 238, 255),
                                RGB(30, 60, 150));
    if (g_net_page == NET_PAGE_JOIN) render_net_server_list(surface);
    for (field = 0; field < NET_FIELD_COUNT; ++field) {
        const RECT *box = &g_net_setup_fields[field].box;
        const int focused = field == g_net_setup_field;
        const int text_y = (box->top + box->bottom - (int)g_bitmap_font.height) / 2;
        size_t capacity;
        const char *value;
        if (g_net_setup_fields[field].page != g_net_page) continue;
        value = net_setup_field_text(field, &capacity);
        draw_bitmap_label(surface, TR(g_net_setup_fields[field].label), 146, text_y, label_ink);
        net_setup_draw_box(surface, box, 1, focused ? RGB(160, 220, 255) : RGB(70, 110, 170),
                           RGB(4, 6, 24), RGB(4, 6, 24), 240);
        draw_bitmap_label(surface, value, box->left + 7, text_y, RGB(240, 246, 255));
        if (focused && (platform_ticks_ms() / 500U) % 2U == 0U) {
            int caret_x = box->left + 8 + (int)measure_plain_bitmap_text(value, strlen(value));
            fill_rect(surface, caret_x, box->top + 6, caret_x + 2, box->bottom - 6,
                      RGB(205, 238, 255));
        }
    }
    if (g_net_page == NET_PAGE_CHOOSE) {
        draw_small_label(surface, TR(T_SETUP_HINT_CHOOSE),
                         146, 214, hint_ink);
        draw_small_label(surface, TR(T_SETUP_KEYS_CHOOSE), 146, 268, hint_ink);
        draw_small_label(surface, g_net_status, 146, 284, RGB(255, 220, 120));
    } else if (g_net_page == NET_PAGE_HOST) {
        draw_small_label(surface, TR(T_SETUP_HINT_HOST1),
                         146, 214, hint_ink);
        draw_small_label(surface, TR(T_SETUP_HINT_HOST2),
                         146, 226, hint_ink);
        draw_small_label(surface, TR(T_SETUP_KEYS_HOST), 146, 318, hint_ink);
        draw_small_label(surface, g_net_status, 146, 334, RGB(255, 220, 120));
    } else {
        draw_small_label(surface, TR(T_SETUP_KEYS_JOIN),
                         146, 326, hint_ink);
        draw_small_label(surface, g_net_status, 146, 338, RGB(255, 220, 120));
    }
    for (button = 0; button < NET_BUTTON_COUNT; ++button) {
        const NetSetupButton *spec = &g_net_setup_buttons[button];
        if (!net_button_on_page(button)) continue;
        net_setup_draw_button(surface, &spec->box, spec->first, spec->second,
                              button == g_net_setup_hover);
    }
}
