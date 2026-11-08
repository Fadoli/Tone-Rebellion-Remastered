/* Remake quality-of-life features (no native counterpart). Each one can be
   turned off in the remake options (remake_options.inc, video.cfg). */

/* ---- Island scrolling: smooth glide and edge scrolling ----------------
   The original jumps the island view (arrows 160 px, wheel 128 px). With
   smooth scrolling those jumps glide to their target; with edge scrolling
   the pointer at the left or right edge of the window scrolls the island.
   Both run on every poll (ui_motion_tick), so they follow the display rate
   rather than the 20 Hz game frame. */

enum { EDGE_SCROLL_MARGIN = 8, EDGE_SCROLL_SPEED = 900 /* logical px/s */ };

static int g_scroll_target;
static int g_scroll_animating;
static double g_scroll_position;
static uint64_t g_scroll_last_counter;

static int platform_window_focused(HWND window);

/* Arrow keys, wheel and remake shortcuts scroll through here. */
static void island_scroll_by(int delta)
{
    if (!g_smooth_scroll) {
        g_island_scroll_x = island_clamp_scroll(g_island_scroll_x + delta);
        g_hovered_location = -1;
        return;
    }
    if (!g_scroll_animating) {
        g_scroll_target = g_island_scroll_x;
        g_scroll_position = (double)g_island_scroll_x;
    }
    g_scroll_target = island_clamp_scroll(g_scroll_target + delta);
    g_scroll_animating = g_scroll_target != g_island_scroll_x;
}

static int edge_scroll_direction(HWND window)
{
    if (!g_edge_scroll || !g_mouse_inside || g_options_open || g_lilmap_drag ||
        g_slide_phase != 0 || !platform_window_focused(window)) return 0;
    if (g_mouse_x < EDGE_SCROLL_MARGIN) return -1;
    if (g_mouse_x >= LOGICAL_WIDTH - EDGE_SCROLL_MARGIN) return 1;
    return 0;
}

/* Returns 1 when the view moved and needs a paint. */
static int ui_motion_tick(HWND window)
{
    uint64_t now = platform_counter();
    double dt = g_scroll_last_counter == 0 ? 0.0
        : (double)(now - g_scroll_last_counter) / (double)platform_counter_frequency();
    int before = g_island_scroll_x;
    int direction;
    g_scroll_last_counter = now;
    if (dt > 0.1) dt = 0.1;
    if (g_menu.screen != SCREEN_ISLAND) {
        g_scroll_animating = 0;
        return 0;
    }
    if (!g_scroll_animating) g_scroll_position = (double)g_island_scroll_x;
    direction = edge_scroll_direction(window);
    if (direction != 0) {
        double moved = (double)direction * EDGE_SCROLL_SPEED * dt;
        g_scroll_position += moved;
        if (g_scroll_animating)
            g_scroll_target = island_clamp_scroll(g_scroll_target + (int)moved);
    }
    if (g_scroll_animating) {
        double remaining = (double)g_scroll_target - g_scroll_position;
        /* Exponential glide, about 90 % of the way in 160 ms. */
        g_scroll_position += remaining * (1.0 - exp(-dt * 14.0));
        if (fabs((double)g_scroll_target - g_scroll_position) < 0.75) {
            g_scroll_position = (double)g_scroll_target;
            g_scroll_animating = 0;
        }
    }
    g_island_scroll_x = island_clamp_scroll((int)floor(g_scroll_position + 0.5));
    if (g_island_scroll_x != (int)floor(g_scroll_position + 0.5))
        g_scroll_position = (double)g_island_scroll_x;
    if (g_island_scroll_x == before) return 0;
    g_hovered_location = -1;
    return 1;
}

/* Whether ui_motion_tick wants polls faster than the 10 ms timer. */
static int ui_motion_active(HWND window)
{
    return g_menu.screen == SCREEN_ISLAND &&
        (g_scroll_animating || edge_scroll_direction(window) != 0);
}

/* ---- Keyboard shortcuts for the island controls -------------------------
   The original has no keys for the island buttons, the Hall commands or
   the building controls. A shortcut replays a real click on its control:
   the pointer is moved over the control's centre (the hover state then
   says whether that control is shown there), the button is pressed and
   released, and the pointer goes back. So a shortcut does exactly what the
   click does, and nothing when the control is not offered. Bindings live in
   saves\keys.cfg ("NAME vk" lines); several actions may share a key (the
   first one shown wins, e.g. Upgrade and UpgSpread on one button). */

static LRESULT CALLBACK menu_window_proc(HWND window, UINT message,
                                          WPARAM wparam, LPARAM lparam);

typedef enum ShortcutCheck {
    SHORTCUT_ISLAND_BUTTON,  /* g_hovered_island_button == arg */
    SHORTCUT_HALL_COMMAND,   /* g_hovered_hall_command == arg */
    SHORTCUT_LOCATION_MOVE,  /* the IWMove / IWHallMove control */
    SHORTCUT_ONOFF,
    SHORTCUT_UPGRADE,
    SHORTCUT_REPAIR,
    SHORTCUT_UPGSPREAD,
    SHORTCUT_OBTAIN,
    SHORTCUT_ORDER,          /* building_order_button_at == 6 + arg */
    SHORTCUT_SPELL           /* selected_cast_action_at == 0x15 + arg */
} ShortcutCheck;

typedef struct ShortcutAction {
    const char *name;        /* windows.txt control, also the keys.cfg key */
    RemakeTextId label;      /* options panel (T_SC_SPELL: + spell number) */
    ShortcutCheck check;
    int arg;
    int default_key;
} ShortcutAction;

static const ShortcutAction g_shortcut_actions[] = {
    {"GOTOMAP", T_SC_MAP, SHORTCUT_ISLAND_BUTTON, WINDOW_ISLAND_BUTTON_MAP, 'M'},
    {"PANIC", T_SC_PANIC, SHORTCUT_ISLAND_BUTTON, WINDOW_ISLAND_BUTTON_PANIC, 'P'},
    {"TOGREALM", T_SC_REALMS, SHORTCUT_ISLAND_BUTTON, WINDOW_ISLAND_BUTTON_REALM, 'R'},
    {"TASKLIST", T_SC_TASKS, SHORTCUT_ISLAND_BUTTON, WINDOW_ISLAND_BUTTON_TASKS, 'T'},
    {"BC_GenInfo", T_SC_HALL_GENERAL, SHORTCUT_HALL_COMMAND, WINDOW_ISLAND_PANEL_GENERAL, 'G'},
    {"BC_Storage", T_SC_HALL_INVENTORY, SHORTCUT_HALL_COMMAND, WINDOW_ISLAND_PANEL_INVENTORY, 'I'},
    {"BC_Knowledge", T_SC_HALL_GLYPHS, SHORTCUT_HALL_COMMAND, WINDOW_ISLAND_PANEL_GLYPHS, 'K'},
    {"BC_Trade", T_SC_HALL_TRADE, SHORTCUT_HALL_COMMAND, WINDOW_ISLAND_PANEL_TRADE, 'B'},
    {"BC_Diplomacy", T_SC_HALL_DIPLOMACY, SHORTCUT_HALL_COMMAND, WINDOW_ISLAND_PANEL_DIPLOMACY, 'D'},
    {"IWMove", T_SC_MOVE, SHORTCUT_LOCATION_MOVE, 0, 'V'},
    {"IWHallMove", T_SC_MOVE_HALL, SHORTCUT_LOCATION_MOVE, 0, 'V'},
    {"BC_OnOff", T_SC_ONOFF, SHORTCUT_ONOFF, 0, 'O'},
    {"BC_Upgrade", T_SC_UPGRADE, SHORTCUT_UPGRADE, 0, 'U'},
    {"BC_UpgSpread", T_SC_UPGSPREAD, SHORTCUT_UPGSPREAD, 0, 'U'},
    {"BC_Repair", T_SC_REPAIR, SHORTCUT_REPAIR, 0, 'F'},
    {"BC_Obtain", T_SC_OBTAIN, SHORTCUT_OBTAIN, 0, 'L'},
    {"BC_AttackFlt", T_SC_ATTACK_UNIT, SHORTCUT_ORDER, 0, 'A'},
    {"BC_AttackLoc", T_SC_ATTACK_SITE, SHORTCUT_ORDER, 1, 'S'},
    {"BC_DefendFlt", T_SC_DEFEND_UNIT, SHORTCUT_ORDER, 2, 'Z'},
    {"BC_DefendArea", T_SC_DEFEND_AREA, SHORTCUT_ORDER, 3, 'X'},
    {"BC_Recall", T_SC_RECALL, SHORTCUT_ORDER, 4, 'Q'},
    {"BC_Spell1", T_SC_SPELL, SHORTCUT_SPELL, 0, '1'},
    {"BC_Spell2", T_SC_SPELL, SHORTCUT_SPELL, 1, '2'},
    {"BC_Spell3", T_SC_SPELL, SHORTCUT_SPELL, 2, '3'},
    {"BC_Spell4", T_SC_SPELL, SHORTCUT_SPELL, 3, '4'},
    {"BC_Spell5", T_SC_SPELL, SHORTCUT_SPELL, 4, '5'},
    {"BC_Spell6", T_SC_SPELL, SHORTCUT_SPELL, 5, '6'},
    {"BC_Spell7", T_SC_SPELL, SHORTCUT_SPELL, 6, '7'},
    {"BC_Spell8", T_SC_SPELL, SHORTCUT_SPELL, 7, 0}
};
enum { SHORTCUT_COUNT = sizeof(g_shortcut_actions) / sizeof(g_shortcut_actions[0]) };

static int g_shortcut_keys[SHORTCUT_COUNT];
static int g_shortcut_keys_loaded;

static void shortcut_defaults(void)
{
    unsigned i;
    for (i = 0; i < SHORTCUT_COUNT; ++i)
        g_shortcut_keys[i] = g_shortcut_actions[i].default_key;
}

static int keys_settings_path(char *path, size_t capacity)
{
    char directory[MAX_PATH];
    if (!save_directory(directory, sizeof(directory))) return 0;
    (void)snprintf(path, capacity, "%s/keys.cfg", directory);
    return 1;
}

static void save_shortcut_keys(void)
{
    char path[MAX_PATH];
    FILE *file;
    unsigned i;
    if (!keys_settings_path(path, sizeof(path))) return;
    file = fopen(path, "w");
    if (file == NULL) return;
    for (i = 0; i < SHORTCUT_COUNT; ++i)
        (void)fprintf(file, "%s %d\n", g_shortcut_actions[i].name, g_shortcut_keys[i]);
    (void)fclose(file);
    platform_storage_changed();
}

static void load_shortcut_keys(void)
{
    char path[MAX_PATH];
    char name[32];
    int key;
    FILE *file;
    g_shortcut_keys_loaded = 1;
    shortcut_defaults();
    if (!keys_settings_path(path, sizeof(path))) return;
    file = fopen(path, "r");
    if (file == NULL) return;
    while (fscanf(file, " %31s %d", name, &key) == 2) {
        unsigned i;
        for (i = 0; i < SHORTCUT_COUNT; ++i)
            if (strcmp(name, g_shortcut_actions[i].name) == 0 && key >= 0 && key < 256)
                g_shortcut_keys[i] = key;
    }
    (void)fclose(file);
}

/* Short text for a virtual key. */
static void shortcut_key_name(int key, char *text, size_t capacity)
{
    if (key == 0) (void)snprintf(text, capacity, "-");
    else if ((key >= 'A' && key <= 'Z') || (key >= '0' && key <= '9'))
        (void)snprintf(text, capacity, "%c", key);
    else if (key == VK_SPACE) (void)snprintf(text, capacity, "%s", TR(T_KEY_SPACE));
    else if (key == VK_TAB) (void)snprintf(text, capacity, "%s", TR(T_KEY_TAB));
    else (void)snprintf(text, capacity, "#%d", key);
}

/* Keys that stay reserved for the game and the remake (F-keys, arrows,
   Escape, Enter, the speed keys). */
static int shortcut_key_allowed(int key)
{
    return key > 0 && key < 256 && key != VK_ESCAPE && key != VK_RETURN &&
        key != VK_LEFT && key != VK_RIGHT && key != VK_UP && key != VK_DOWN &&
        key != '8' && key != '9' && key != VK_ADD && key != VK_SUBTRACT &&
        key != VK_SHIFT && key != VK_CONTROL && key != VK_BACK &&
        !(key >= VK_F1 && key <= VK_F1 + 11);
}

static LPARAM logical_to_client_lparam(HWND window, int x, int y)
{
    RECT client;
    RECT viewport;
    int width, height, cx, cy;
    platform_client_rect(window, &client);
    width = client.right - client.left;
    height = client.bottom - client.top;
    if (!logical_viewport(width, height, &viewport)) return (LPARAM)-1;
    cx = viewport.left + (int)(((long long)(2 * x + 1) * (viewport.right - viewport.left)) /
                               (2 * LOGICAL_WIDTH));
    cy = viewport.top + (int)(((long long)(2 * y + 1) * (viewport.bottom - viewport.top)) /
                              (2 * LOGICAL_HEIGHT));
    return (LPARAM)(((cy & 0xffff) << 16) | (cx & 0xffff));
}

static int shortcut_control_shown(const ShortcutAction *action, int x, int y)
{
    switch (action->check) {
    case SHORTCUT_ISLAND_BUTTON: return g_hovered_island_button == action->arg;
    case SHORTCUT_HALL_COMMAND: return g_hovered_hall_command == action->arg;
    case SHORTCUT_LOCATION_MOVE: {
        IslandLocationActionControl shown = selected_location_action();
        return shown != ISLAND_LOCATION_ACTION_NONE && g_hovered_location_action == shown;
    }
    case SHORTCUT_ONOFF: return g_hovered_onoff_control != 0;
    case SHORTCUT_UPGRADE: return g_hovered_upgrade_control != 0;
    case SHORTCUT_REPAIR: return g_hovered_repair_control != 0;
    case SHORTCUT_UPGSPREAD: return g_hovered_upgspread != 0;
    case SHORTCUT_OBTAIN: return g_hovered_location_grab != 0;
    case SHORTCUT_ORDER: return building_order_button_at(x, y) == 6 + action->arg;
    default: return selected_cast_action_at(x, y) == 0x15 + action->arg;
    }
}

/* Puts the pointer state back where the real pointer is. */
static void shortcut_restore_pointer(HWND window, LPARAM back)
{
    if (back != (LPARAM)-1) (void)menu_window_proc(window, WM_MOUSEMOVE, 0, back);
    else (void)menu_window_proc(window, WM_MOUSELEAVE, 0, 0);
}

/* Runs the first shown control bound to `key`; returns 1 when one ran. */
static int shortcut_key(HWND window, int key)
{
    LPARAM back;
    unsigned i;
    if (!g_shortcuts_enabled || g_menu.screen != SCREEN_ISLAND || !g_game_session_valid ||
        g_options_open || !shortcut_key_allowed(key)) return 0;
    if (!g_shortcut_keys_loaded) load_shortcut_keys();
    for (i = 0; i < SHORTCUT_COUNT && g_shortcut_keys[i] != key; ++i) {}
    if (i == SHORTCUT_COUNT) return 0;   /* unbound: no side effect */
    /* A click below the open SlideWindow only closes it: close it first. */
    if (g_slide_phase != 0) slide_panel_close_now();
    back = g_mouse_inside ? logical_to_client_lparam(window, g_mouse_x, g_mouse_y)
                          : (LPARAM)-1;
    for (i = 0; i < SHORTCUT_COUNT; ++i) {
        const WindowTemplate *control;
        LPARAM at;
        int x, y;
        if (g_shortcut_keys[i] != key) continue;
        control = window_catalog_find(&g_window_catalog, g_shortcut_actions[i].name, 3);
        if (control == NULL) continue;
        x = (control->pane.left + control->pane.right) / 2;
        y = (control->pane.top + control->pane.bottom) / 2;
        at = logical_to_client_lparam(window, x, y);
        if (at == (LPARAM)-1) break;
        (void)menu_window_proc(window, WM_MOUSEMOVE, 0, at);
        if (!shortcut_control_shown(&g_shortcut_actions[i], x, y)) continue;
        (void)menu_window_proc(window, WM_LBUTTONDOWN, MK_LBUTTON, at);
        (void)menu_window_proc(window, WM_LBUTTONUP, 0, at);
        shortcut_restore_pointer(window, back);
        return 1;
    }
    shortcut_restore_pointer(window, back);
    return 0;
}

/* Options page 1: the shortcut list. Up/Down pick, Enter (or a click) waits
   for the new key, Delete clears it, Escape goes back. The last row puts
   every default back. */
enum { SHORTCUT_PAGE_ROWS = 13 };
static int g_shortcut_row;
static int g_shortcut_first;
static int g_shortcut_waiting;

static void shortcut_page_follow(void)
{
    if (g_shortcut_row < g_shortcut_first) g_shortcut_first = g_shortcut_row;
    if (g_shortcut_row >= g_shortcut_first + SHORTCUT_PAGE_ROWS)
        g_shortcut_first = g_shortcut_row - SHORTCUT_PAGE_ROWS + 1;
}

static void shortcut_page_activate(void)
{
    if (g_shortcut_row == SHORTCUT_COUNT) {
        shortcut_defaults();
        save_shortcut_keys();
    } else {
        g_shortcut_waiting = 1;
    }
}

static int shortcut_page_key(HWND window, WPARAM key)
{
    (void)window;
    if (!g_shortcut_keys_loaded) load_shortcut_keys();
    if (g_shortcut_waiting) {
        g_shortcut_waiting = 0;
        if (key == VK_ESCAPE) return 1;
        if (key == VK_DELETE || key == VK_BACK) g_shortcut_keys[g_shortcut_row] = 0;
        else if (shortcut_key_allowed((int)key)) g_shortcut_keys[g_shortcut_row] = (int)key;
        else return 1;
        save_shortcut_keys();
        return 1;
    }
    if (key == VK_ESCAPE || key == VK_F2) {
        g_options_page = 0;
    } else if (key == VK_UP) {
        g_shortcut_row = (g_shortcut_row + SHORTCUT_COUNT) % (SHORTCUT_COUNT + 1);
    } else if (key == VK_DOWN) {
        g_shortcut_row = (g_shortcut_row + 1) % (SHORTCUT_COUNT + 1);
    } else if (key == VK_RETURN) {
        shortcut_page_activate();
    } else if ((key == VK_DELETE || key == VK_BACK) && g_shortcut_row < SHORTCUT_COUNT) {
        g_shortcut_keys[g_shortcut_row] = 0;
        save_shortcut_keys();
    }
    shortcut_page_follow();
    return 1;
}

static int shortcut_page_row_at(int x, int y)
{
    int row;
    if (x < OPTIONS_LEFT + 10 || x >= OPTIONS_LEFT + OPTIONS_WIDTH - 10 ||
        y < OPTIONS_ROW_TOP) return -1;
    row = (y - OPTIONS_ROW_TOP) / OPTIONS_ROW_HEIGHT;
    if (row >= SHORTCUT_PAGE_ROWS) return -1;
    row += g_shortcut_first;
    return row <= SHORTCUT_COUNT ? row : -1;
}

static int shortcut_page_press(HWND window, int x, int y)
{
    int row = shortcut_page_row_at(x, y);
    (void)window;
    if (!g_shortcut_keys_loaded) load_shortcut_keys();
    g_shortcut_waiting = 0;
    if (row >= 0) {
        g_shortcut_row = row;
        shortcut_page_activate();
    }
    return 1;
}

static void render_shortcut_page(RenderSurface *surface)
{
    const COLORREF text = RGB(230, 238, 255);
    const COLORREF dim = RGB(150, 160, 180);
    const COLORREF accent = RGB(255, 210, 120);
    int hover = g_mouse_inside ? shortcut_page_row_at(g_mouse_x, g_mouse_y) : -1;
    int line;
    const char *help = TR(g_shortcut_waiting ? T_SC_WAITING_HELP : T_SC_HELP);
    if (!g_shortcut_keys_loaded) load_shortcut_keys();
    for (line = 0; line < SHORTCUT_PAGE_ROWS; ++line) {
        int row = g_shortcut_first + line;
        int y = OPTIONS_ROW_TOP + line * OPTIONS_ROW_HEIGHT;
        char key[16];
        char label[64];
        if (row > SHORTCUT_COUNT) break;
        if (row == g_shortcut_row || row == hover)
            fill_rect(surface, OPTIONS_LEFT + 10, y - 2,
                      OPTIONS_LEFT + OPTIONS_WIDTH - 10, y + OPTIONS_ROW_HEIGHT - 4,
                      row == g_shortcut_row ? RGB(60, 34, 44) : RGB(38, 24, 32));
        if (row == SHORTCUT_COUNT) {
            options_label(surface, TR(T_SC_RESET), OPTIONS_LEFT + 20,
                          y + 3, row == g_shortcut_row ? accent : text);
            continue;
        }
        if (g_shortcut_actions[row].label == T_SC_SPELL)
            (void)snprintf(label, sizeof(label), TR(T_SC_SPELL), g_shortcut_actions[row].arg + 1);
        else
            (void)snprintf(label, sizeof(label), "%s", TR(g_shortcut_actions[row].label));
        options_label(surface, label, OPTIONS_LEFT + 20, y + 3,
                      row == g_shortcut_row ? accent : text);
        if (g_shortcut_waiting && row == g_shortcut_row)
            (void)snprintf(key, sizeof(key), "...");
        else
            shortcut_key_name(g_shortcut_keys[row], key, sizeof(key));
        options_label(surface, key, OPTIONS_VALUE_RIGHT - options_text_width(key), y + 3,
                      g_shortcut_keys[row] != 0 ? text : dim);
    }
    options_label(surface, help,
                  OPTIONS_LEFT + (OPTIONS_WIDTH - options_text_width(help)) / 2,
                  options_panel_bottom() - 22, dim);
}

/* ---- Event alerts ---------------------------------------------------------
   The original only shows island messages for the island in view. Alerts
   watch the session after each game frame (read only, so the simulation
   and the network hash are untouched) and list, at the top of the island
   view and the world map, what happens to the local tribe elsewhere: units
   or buildings losing health, a building lost, Leviathan units appearing
   where the tribe is present, and the Leviathan's periodic notice. Space
   jumps to the island (and the spot) of the newest alert. */

enum { ALERT_SLOTS = 4, ALERT_SHOW_MS = 7000, ALERT_COOLDOWN_MS = 15000 };

typedef struct RemakeAlert {
    char text[96];
    int island;      /* -1: no place to jump to */
    int x;
    uint32_t since_ms;
    int notice;      /* save notices: shown even with alerts off */
} RemakeAlert;

static RemakeAlert g_alerts[ALERT_SLOTS];
static unsigned g_alert_next;
static int g_alert_jump = -1;   /* slot of the newest alert with a place */
static int g_alert_primed;
static int16_t g_alert_floater_hp[GAME_SESSION_MAX_FLOATERS];
static uint8_t g_alert_floater_live[GAME_SESSION_MAX_FLOATERS];
static int16_t g_alert_site_hp[WORLD_MAP_MAX_ISLANDS][ISLAND_DATA_MAX_LOCATIONS];
static int8_t g_alert_site_owner[WORLD_MAP_MAX_ISLANDS][ISLAND_DATA_MAX_LOCATIONS];
static uint32_t g_alert_attack_ms[WORLD_MAP_MAX_ISLANDS];
static uint32_t g_alert_leviathan_ms[WORLD_MAP_MAX_ISLANDS];

static const char *alert_island_name(int island)
{
    const WorldDefinition *world;
    int shape;
    if (g_menu.world_index < 0 || g_menu.world_index >= g_menu.world_map.world_count)
        return "?";
    world = &g_menu.world_map.worlds[g_menu.world_index];
    if (island < 0 || island >= (int)world->island_count) return "?";
    shape = world->islands[island].shape_id;
    return shape >= 0 && shape < ISLAND_NAME_COUNT && g_island_names[shape][0] != '\0'
        ? g_island_names[shape] : "?";
}

static void alert_push(const char *text, int island, int x)
{
    RemakeAlert *alert = &g_alerts[g_alert_next];
    /* Nothing to report about the island in view. */
    if (island >= 0 && g_menu.screen == SCREEN_ISLAND &&
        g_menu.selected_map_island == island) return;
    (void)snprintf(alert->text, sizeof(alert->text), "%s", text);
    alert->island = island;
    alert->x = x;
    alert->notice = 0;
    alert->since_ms = platform_ticks_ms();
    if (island >= 0) g_alert_jump = (int)g_alert_next;
    g_alert_next = (g_alert_next + 1U) % ALERT_SLOTS;
}

/* Rate limit per island: one alert of a kind per ALERT_COOLDOWN_MS. */
static int alert_cooldown(uint32_t *last, uint32_t now)
{
    if (*last != 0 && now - *last < ALERT_COOLDOWN_MS) return 0;
    *last = now != 0 ? now : 1;
    return 1;
}

static void alerts_reset(void)
{
    memset(g_alerts, 0, sizeof(g_alerts));
    g_alert_jump = -1;
    g_alert_primed = 0;
    memset(g_alert_attack_ms, 0, sizeof(g_alert_attack_ms));
    memset(g_alert_leviathan_ms, 0, sizeof(g_alert_leviathan_ms));
}

/* After each game frame. */
static void alerts_observe(void)
{
    int tribe = g_menu.selected_tribe;
    uint32_t now = platform_ticks_ms();
    uint16_t present = 0;   /* islands where the tribe has units or buildings */
    unsigned i, island;
    char text[96];
    static uint32_t last_tick;
    if (!g_game_session_valid || tribe < 0 || tribe >= GAME_START_PLAYER_COUNT) {
        g_alert_primed = 0;
        return;
    }
    /* Another game (new, loaded, resynchronised): start over silently. */
    if (g_game_session.simulation_tick < last_tick ||
        g_game_session.simulation_tick > last_tick + 200U) g_alert_primed = 0;
    last_tick = g_game_session.simulation_tick;
    for (i = 0; i < g_game_session.floater_count && i < GAME_SESSION_MAX_FLOATERS; ++i) {
        const GameFloaterStart *f = &g_game_session.floaters[i];
        if (game_session_floater_is_active(f) && f->owner_slot == (uint8_t)tribe &&
            f->island_index < WORLD_MAP_MAX_ISLANDS)
            present |= (uint16_t)(1U << f->island_index);
    }
    for (island = 0; island < g_game_session.island_count && island < WORLD_MAP_MAX_ISLANDS;
         ++island) {
        const GameRuntimeIsland *runtime = &g_game_session.islands[island];
        uint16_t location;
        for (location = 0; location < runtime->location_count &&
                            location < ISLAND_DATA_MAX_LOCATIONS; ++location) {
            const GameRuntimeLocation *site = &runtime->locations[location];
            int mine = site->owner_id == tribe && site->record_value_10 > 1;
            if (mine) present |= (uint16_t)(1U << island);
            if (g_alert_primed && g_event_alerts) {
                if (g_alert_site_owner[island][location] == (int8_t)tribe && !mine &&
                    site->move_fade_item_10 == 0) {
                    (void)snprintf(text, sizeof(text), TR(T_ALERT_BUILDING_LOST),
                                   alert_island_name((int)island));
                    alert_push(text, (int)island, site->x);
                } else if (mine && site->source_value_34 >= 0 &&
                           site->source_value_34 < g_alert_site_hp[island][location] &&
                           alert_cooldown(&g_alert_attack_ms[island], now)) {
                    (void)snprintf(text, sizeof(text), TR(T_ALERT_ATTACK),
                                   alert_island_name((int)island));
                    alert_push(text, (int)island, site->x);
                }
            }
            g_alert_site_owner[island][location] = (int8_t)(mine ? tribe : -1);
            g_alert_site_hp[island][location] = site->source_value_34;
        }
    }
    for (i = 0; i < GAME_SESSION_MAX_FLOATERS; ++i) {
        const GameFloaterStart *f = &g_game_session.floaters[i];
        int live = i < g_game_session.floater_count && game_session_floater_is_active(f);
        if (g_alert_primed && g_event_alerts && live &&
            f->island_index < WORLD_MAP_MAX_ISLANDS) {
            if (f->owner_slot == (uint8_t)tribe && g_alert_floater_live[i] &&
                f->current_hit_points < g_alert_floater_hp[i] &&
                alert_cooldown(&g_alert_attack_ms[f->island_index], now)) {
                (void)snprintf(text, sizeof(text), TR(T_ALERT_ATTACK),
                               alert_island_name(f->island_index));
                alert_push(text, f->island_index, f->x);
            } else if (f->type_index == 4 && !g_alert_floater_live[i] &&
                       (present & (1U << f->island_index)) != 0 &&
                       alert_cooldown(&g_alert_leviathan_ms[f->island_index], now)) {
                (void)snprintf(text, sizeof(text), TR(T_ALERT_LEVIATHAN),
                               alert_island_name(f->island_index));
                alert_push(text, f->island_index, f->x);
            }
        }
        g_alert_floater_live[i] = (uint8_t)live;
        g_alert_floater_hp[i] = live ? f->current_hit_points : 0;
    }
    g_alert_primed = 1;
}

/* Space: to the newest alert's island and spot. */
static int alert_jump(HWND window)
{
    const RemakeAlert *alert;
    if (!g_event_alerts || g_alert_jump < 0) return 0;
    alert = &g_alerts[g_alert_jump];
    if (alert->island < 0 || alert->since_ms == 0) return 0;
    if (g_menu.screen != SCREEN_ISLAND || g_menu.selected_map_island != alert->island) {
        if (!open_island_view(window, alert->island)) return 0;
    }
    g_scroll_animating = 0;
    g_island_scroll_x = island_clamp_scroll(alert->x - LOGICAL_WIDTH / 2);
    g_hovered_location = -1;
    return 1;
}

static void render_alerts(RenderSurface *surface)
{
    uint32_t now = platform_ticks_ms();
    int y = 104;
    unsigned n;
    if (g_options_open) return;
    for (n = 0; n < ALERT_SLOTS; ++n) {
        /* Newest first. */
        const RemakeAlert *alert =
            &g_alerts[(g_alert_next + ALERT_SLOTS - 1U - n) % ALERT_SLOTS];
        char line[128];
        int width;
        if (alert->since_ms == 0 || now - alert->since_ms >= ALERT_SHOW_MS ||
            (!g_event_alerts && !alert->notice)) continue;
        (void)snprintf(line, sizeof(line), "%s%s", alert->text,
                       n == 0 && alert->island >= 0 ? TR(T_ALERT_GO_SUFFIX) : "");
        width = options_text_width(line);
        fill_rect(surface, LOGICAL_WIDTH - width - 16, y - 3, LOGICAL_WIDTH - 4, y + 16,
                  RGB(24, 12, 20));
        options_label(surface, line, LOGICAL_WIDTH - width - 10, y,
                      alert->island >= 0 ? RGB(255, 200, 120) : RGB(200, 210, 255));
        y += 21;
    }
}

/* ---- Quicksave, quickload and autosave ------------------------------------
   F5 writes saves/quick.sav, F9 loads it, Shift+F9 loads saves/auto.sav,
   which the autosave rewrites every g_autosave_minutes of play (game ticks,
   so a paused game does not autosave). Shift+F5 opens the Save screen. A
   network game can save (a local copy, as the Save screen) but not load. */

static void remake_notice(const char *text)
{
    RemakeAlert *alert = &g_alerts[g_alert_next];
    alert_push(text, -1, 0);
    alert->notice = 1;
}

static int remake_save_path(const char *name, char *path, size_t capacity)
{
    char directory[MAX_PATH];
    if (!save_directory(directory, sizeof(directory))) return 0;
    (void)snprintf(path, capacity, "%s/%s", directory, name);
    return 1;
}

static void quick_save(void)
{
    char path[MAX_PATH];
    if (!g_game_session_valid || !options_screen()) return;
    remake_notice(remake_save_path("quick.sav", path, sizeof(path)) &&
                  write_save_file(path)
                  ? TR(T_QUICKSAVE_DONE)
                  : TR(T_QUICKSAVE_FAILED));
}

static void quick_load(HWND window, int automatic)
{
    char path[MAX_PATH];
    FILE *file;
    if (g_net_in_game) {
        remake_notice(TR(T_QUICKLOAD_NETWORK));
        return;
    }
    if (!remake_save_path(automatic ? "auto.sav" : "quick.sav", path, sizeof(path)) ||
        (file = fopen(path, "rb")) == NULL) {
        remake_notice(automatic ? TR(T_NO_AUTOSAVE)
                                : TR(T_NO_QUICKSAVE));
        return;
    }
    (void)fclose(file);
    if (read_save_file(window, path)) {
        slide_panel_open_paused();
        alerts_reset();
        remake_notice(automatic ? TR(T_AUTOSAVE_LOADED)
                                : TR(T_QUICKSAVE_LOADED));
    } else {
        remake_notice(TR(T_LOAD_FAILED));
    }
}

/* After each game frame: counts play ticks and writes auto.sav. */
static void autosave_tick(void)
{
    static uint32_t last_tick;
    static uint32_t played;
    uint32_t tick;
    if (!g_game_session_valid || !options_screen()) return;
    tick = g_game_session.simulation_tick;
    if (tick > last_tick && tick - last_tick < 200U) played += tick - last_tick;
    last_tick = tick;
    if (g_autosave_minutes <= 0) {
        played = 0;
        return;
    }
    /* 20 game ticks per second at speed 1. */
    if (played >= (uint32_t)g_autosave_minutes * 60U * 20U) {
        char path[MAX_PATH];
        played = 0;
        if (remake_save_path("auto.sav", path, sizeof(path)) && write_save_file(path))
            remake_notice(TR(T_AUTOSAVE_DONE));
    }
}
