/* Remake save files. The native format (FUN_0045749a / FUN_004576c7) is a
   0x80-byte header followed by four engine serialisations that the remake
   does not reproduce, so the remake writes its own files: the same 0x80-byte
   header layout (so the Load/Save screen lists them like the native slots)
   followed by a "TRRM" body with the menu state and the raw GameSession.
   They live in a `saves` directory next to the executable; the original game
   directory is never written. */

enum { REMAKE_SAVE_MAGIC = 0x4d525254 /* "TRRM" */, REMAKE_SAVE_VERSION = 1 };

typedef struct RemakeSaveBody {
    uint32_t magic;
    uint32_t version;
    uint32_t session_size;
    int32_t world_index;
    int32_t difficulty;
    int32_t selected_tribe;
    int32_t selected_map_island;
    int32_t on_island;
    uint32_t sim_speed;
    uint32_t animation_ticks;
} RemakeSaveBody;

static void put_le32(unsigned char *bytes, uint32_t value)
{
    bytes[0] = (unsigned char)value;
    bytes[1] = (unsigned char)(value >> 8);
    bytes[2] = (unsigned char)(value >> 16);
    bytes[3] = (unsigned char)(value >> 24);
}

/* Header fields read by FUN_0045858a: +0x1c tribe, +0x30/+0x32/+0x34 stock
   shorts, +0x68 surplus, +0x6c population, +0x70 workers, +0x7c key. */
static void fill_save_header(unsigned char header[0x80])
{
    unsigned int tribe = g_menu.selected_tribe >= 0 &&
        g_menu.selected_tribe < GAME_START_PLAYER_COUNT
        ? (unsigned int)g_menu.selected_tribe : 0U;
    const GamePlayerEconomy *economy = &g_game_session.economy[tribe];
    unsigned int count = 0;
    unsigned int total = 0;
    unsigned int percentage = 0;
    unsigned int resource;
    memset(header, 0, 0x80);
    memcpy(header, "1.16F", 6);
    put_le32(header + 0x1c, tribe);
    if (economy->hall_island_index < g_game_session.island_count &&
        economy->hall_location_index <
            g_game_session.islands[economy->hall_island_index].location_count) {
        const GameRuntimeLocation *hall = &g_game_session.islands[
            economy->hall_island_index].locations[economy->hall_location_index];
        /* Site record copy at header +0x08: +0x10 item id (header +0x18) and
           +0x14 owner (header +0x1c, already the tribe). */
        put_le32(header + 0x18, (uint32_t)hall->record_value_10);
        for (resource = 0; resource < GAME_RESOURCE_TYPE_COUNT; ++resource) {
            header[0x30 + resource * 2] = (unsigned char)hall->resource_stock[resource];
            header[0x31 + resource * 2] =
                (unsigned char)(hall->resource_stock[resource] >> 8);
        }
    }
    (void)game_session_workstr_summary(&g_game_session, (uint8_t)tribe, &count,
                                       &total, &percentage);
    put_le32(header + 0x68, (uint32_t)economy->source_maintenance_budget);
    put_le32(header + 0x6c, total);
    put_le32(header + 0x70, count);
    put_le32(header + 0x7c, 0x000378b8u);
}

static int write_save_file(const char *path)
{
    unsigned char header[0x80];
    RemakeSaveBody body;
    FILE *file;
    int ok;
    if (!g_game_session_valid) return 0;
    fill_save_header(header);
    memset(&body, 0, sizeof(body));
    body.magic = REMAKE_SAVE_MAGIC;
    body.version = REMAKE_SAVE_VERSION;
    body.session_size = (uint32_t)sizeof(GameSession);
    body.world_index = g_menu.world_index;
    body.difficulty = g_menu.difficulty;
    body.selected_tribe = g_menu.selected_tribe;
    body.selected_map_island = g_menu.selected_map_island;
    body.on_island = g_menu.screen == SCREEN_ISLAND ||
        (g_menu.screen == SCREEN_LOAD_GAME &&
         g_save_return_screen == SCREEN_ISLAND);
    body.sim_speed = g_sim_speed;
    body.animation_ticks = g_menu.animation_ticks;
    file = fopen(path, "wb");
    if (file == NULL) return 0;
    ok = fwrite(header, 1, sizeof(header), file) == sizeof(header) &&
         fwrite(&body, 1, sizeof(body), file) == sizeof(body) &&
         fwrite(&g_game_session, 1, sizeof(g_game_session), file) ==
             sizeof(g_game_session);
    ok = (fclose(file) == 0) && ok;
    return ok;
}

/* Restores a remake save; returns 0 (without touching the running game) when
   the file is not a valid remake save. */
static int read_save_file(HWND window, const char *path)
{
    unsigned char header[0x80];
    RemakeSaveBody body;
    GameSession *session;
    FILE *file = fopen(path, "rb");
    int on_island;
    char error[160];
    if (file == NULL) return 0;
    session = (GameSession *)malloc(sizeof(*session));
    if (session == NULL ||
        fread(header, 1, sizeof(header), file) != sizeof(header) ||
        memcmp(header, "1.16", 4) != 0 ||
        fread(&body, 1, sizeof(body), file) != sizeof(body) ||
        body.magic != REMAKE_SAVE_MAGIC || body.version != REMAKE_SAVE_VERSION ||
        body.session_size != sizeof(GameSession) ||
        body.world_index < 0 ||
        body.world_index >= g_menu.world_map.world_count ||
        body.selected_tribe < 0 || body.selected_tribe >= GAME_START_PLAYER_COUNT ||
        fread(session, 1, sizeof(*session), file) != sizeof(*session)) {
        (void)fclose(file);
        free(session);
        return 0;
    }
    (void)fclose(file);
    g_game_session = *session;
    free(session);
    game_music_state_init(&g_game_music);
    g_game_session_world_index = body.world_index;
    g_game_session_valid = 1;
    g_menu.world_index = body.world_index;
    g_menu.difficulty = body.difficulty;
    g_menu.selected_tribe = body.selected_tribe;
    g_menu.selected_map_island = -1;
    g_menu.setup_accepted = 1;
    g_menu.animation_ticks = body.animation_ticks;
    g_sim_speed = body.sim_speed >= 1U && body.sim_speed <= 3U ? body.sim_speed : 1U;
    g_selected_floater = -1;
    g_selected_location = -1;
    g_hovered_island = -1;
    g_defeat_ticks = 0;
    on_island = body.on_island && body.selected_map_island >= 0;
    g_menu.screen = SCREEN_WORLD_MAP;
    if (on_island && !open_island_view(window, body.selected_map_island)) {
        (void)snprintf(error, sizeof(error), "island view could not be restored");
        g_menu.screen = SCREEN_WORLD_MAP;
    }
    return 1;
}

static int save_slot_path(int slot, char *path, size_t capacity)
{
    char directory[MAX_PATH];
    if (slot < 0 || slot > 7 || !save_directory(directory, sizeof(directory)))
        return 0;
    (void)snprintf(path, capacity, "%s\\%02d.sav", directory, slot);
    return 1;
}

static int resume_path(char *path, size_t capacity)
{
    char directory[MAX_PATH];
    if (!save_directory(directory, sizeof(directory))) return 0;
    (void)snprintf(path, capacity, "%s\\resume.gam", directory);
    return 1;
}

/* Leaves the Load/Save screen: Save returns to the screen it was opened from,
   Load returns to the title. */
static void leave_load_screen(void)
{
    if (g_load_save_mode || g_load_from_game) {
        g_load_save_mode = 0;
        g_load_from_game = 0;
        g_menu.screen = g_save_return_screen == SCREEN_ISLAND ||
            g_save_return_screen == SCREEN_WORLD_MAP
            ? g_save_return_screen : SCREEN_WORLD_MAP;
    } else {
        g_menu.screen = SCREEN_MAIN_MENU;
    }
}

/* F5 from the world map or an island opens the Save screen (state 5). */
static void enter_save_screen(void)
{
    if (!g_game_session_valid || (g_menu.screen != SCREEN_WORLD_MAP &&
                                  g_menu.screen != SCREEN_ISLAND)) return;
    g_save_return_screen = g_menu.screen;
    g_load_save_mode = 1;
    scan_load_slots();
    g_menu.screen = SCREEN_LOAD_GAME;
}

/* Automatic resume point written when the window closes during a game. */
static void write_resume_file(void)
{
    char path[MAX_PATH];
    if (g_game_session_valid &&
        (g_menu.screen == SCREEN_WORLD_MAP || g_menu.screen == SCREEN_ISLAND) &&
        resume_path(path, sizeof(path)))
        (void)write_save_file(path);
}
