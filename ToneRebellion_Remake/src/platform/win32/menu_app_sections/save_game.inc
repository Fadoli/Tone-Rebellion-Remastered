/* Remake save files. The native format (FUN_0045749a / FUN_004576c7) is a
   0x80-byte header followed by four engine serialisations that the remake
   does not reproduce, so the remake writes its own files: the same 0x80-byte
   header layout (so the Load/Save screen lists them like the native slots)
   followed by a "TRRM" body with the menu state and the raw GameSession.
   Version 2 adds the GameSession field table (game_session_schema.h) before
   the session bytes, so a later build whose GameSession changed copies the
   fields by name over a fresh session of the same world. Version 1 files
   (no table) still load when their session size matches. They live in a
   `saves` directory next to the executable; the original game directory is
   never written. */

enum { REMAKE_SAVE_MAGIC = 0x4d525254 /* "TRRM" */, REMAKE_SAVE_VERSION = 2,
       REMAKE_SAVE_MAX_SCHEMA = 1u << 20 };

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

/* Version 2: the schema length follows the body, then the schema, then
   session_size bytes of session. */

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
    unsigned char *schema;
    size_t schema_length = game_session_schema_write(NULL, 0);
    unsigned char length_bytes[4];
    GameSession *stamped;
    int ok;
    if (!g_game_session_valid) return 0;
    schema = (unsigned char *)malloc(schema_length);
    /* The file carries this build's revision; the live session is left
       untouched (network games hash it). */
    stamped = (GameSession *)malloc(sizeof(GameSession));
    if (schema == NULL || stamped == NULL ||
        game_session_schema_write(schema, schema_length) != schema_length) {
        free(schema);
        free(stamped);
        return 0;
    }
    *stamped = g_game_session;
    stamped->save_revision = GAME_SESSION_SAVE_REVISION;
    put_le32(length_bytes, (uint32_t)schema_length);
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
    if (file == NULL) {
        free(schema);
        free(stamped);
        return 0;
    }
    ok = fwrite(header, 1, sizeof(header), file) == sizeof(header) &&
         fwrite(&body, 1, sizeof(body), file) == sizeof(body) &&
         fwrite(length_bytes, 1, 4, file) == 4 &&
         fwrite(schema, 1, schema_length, file) == schema_length &&
         fwrite(stamped, 1, sizeof(*stamped), file) == sizeof(*stamped);
    free(schema);
    free(stamped);
    ok = (fclose(file) == 0) && ok;
    platform_storage_changed();
    return ok;
}

/* Remake: a loaded game with two or more played tribes
   (game_session_active_player_mask, plus the saved tribe) opens the New Game
   screen as a tribe choice instead of the map. Returns 1 when it did. */
static int begin_tribe_choice(HWND window)
{
    uint8_t mask = game_session_active_player_mask(&g_game_session);
    unsigned int count = 0;
    unsigned int tribe;
    if (g_menu.selected_tribe >= 0 && g_menu.selected_tribe < GAME_START_PLAYER_COUNT)
        mask |= (uint8_t)(1U << g_menu.selected_tribe);
    for (tribe = 0; tribe < GAME_START_PLAYER_COUNT; ++tribe)
        if ((mask & (1U << tribe)) != 0) ++count;
    if (count < 2U) return 0;
    g_tribe_choice_mask = mask;
    g_menu.screen = SCREEN_NEW_GAME;
    update_window_title(window);
    return 1;
}

/* NEWGAME on the tribe choice: play the loaded game as the picked tribe. */
static void finish_tribe_choice(HWND window)
{
    g_tribe_choice_mask = 0;
    if (!g_game_session_valid || g_menu.selected_tribe < 0 ||
        g_menu.selected_tribe >= GAME_START_PLAYER_COUNT) {
        g_menu.screen = SCREEN_MAIN_MENU;
        return;
    }
    g_game_session.config.selected_tribe = (uint8_t)g_menu.selected_tribe;
    g_menu.selected_map_island = -1;
    g_menu.screen = SCREEN_WORLD_MAP;
    update_window_title(window);
}

/* The whole file in a malloc'ed buffer, or NULL. */
static unsigned char *read_whole_file(const char *path, size_t *length)
{
    FILE *file = fopen(path, "rb");
    unsigned char *bytes = NULL;
    long size;
    *length = 0;
    if (file == NULL) return NULL;
    if (fseek(file, 0, SEEK_END) == 0 && (size = ftell(file)) > 0 &&
        size <= 64L * 1024L * 1024L && fseek(file, 0, SEEK_SET) == 0 &&
        (bytes = (unsigned char *)malloc((size_t)size)) != NULL &&
        fread(bytes, 1, (size_t)size, file) == (size_t)size) {
        *length = (size_t)size;
    } else {
        free(bytes);
        bytes = NULL;
    }
    (void)fclose(file);
    return bytes;
}

static uint32_t get_le32(const unsigned char *bytes)
{
    return (uint32_t)bytes[0] | (uint32_t)bytes[1] << 8 |
        (uint32_t)bytes[2] << 16 | (uint32_t)bytes[3] << 24;
}

/* A remake save's bytes into g_game_session; g_menu takes the save's world,
   tribe and difficulty. Returns 0 and leaves the game and the menu as they
   were when the bytes are not a valid remake save. A network game loads the
   host's file through here on every machine. */
static int apply_remake_save_bytes(const unsigned char *bytes, size_t length,
                                   RemakeSaveBody *body)
{
    const unsigned char *schema = NULL;
    const unsigned char *data;
    uint32_t schema_length = 0;
    size_t at = 0x80 + sizeof(RemakeSaveBody);
    char error[160];
    int ok;
    if (bytes == NULL || length < at || memcmp(bytes, "1.16", 4) != 0) return 0;
    memcpy(body, bytes + 0x80, sizeof(*body));
    ok = body->magic == REMAKE_SAVE_MAGIC &&
        (body->version == REMAKE_SAVE_VERSION ||
         (body->version == 1 && body->session_size == sizeof(GameSession))) &&
        body->session_size > 0 && body->session_size <= 64u * 1024u * 1024u &&
        body->world_index >= 0 &&
        body->world_index < g_menu.world_map.world_count &&
        body->selected_tribe >= 0 && body->selected_tribe < GAME_START_PLAYER_COUNT;
    if (ok && body->version == REMAKE_SAVE_VERSION) {
        ok = length >= at + 4;
        if (ok) schema_length = get_le32(bytes + at);
        at += 4;
        ok = ok && schema_length > 0 && schema_length <= REMAKE_SAVE_MAX_SCHEMA &&
            length - at >= schema_length;
        if (ok) schema = bytes + at;
        at += schema_length;
    }
    ok = ok && length - at >= body->session_size;
    if (!ok) return 0;
    data = bytes + at;
    if (schema == NULL) {
        memcpy(&g_game_session, data, sizeof(GameSession));
    } else {
        /* Fields the save does not know keep the values of a fresh session
           of the same world and tribe. */
        int previous_world = g_menu.world_index;
        int previous_tribe = g_menu.selected_tribe;
        int previous_difficulty = g_menu.difficulty;
        GameSession *previous = (GameSession *)malloc(sizeof(GameSession));
        if (previous == NULL) return 0;
        *previous = g_game_session;
        g_menu.world_index = body->world_index;
        g_menu.selected_tribe = body->selected_tribe;
        g_menu.difficulty = body->difficulty;
        ok = load_game_session_for_selected_world(error, sizeof(error));
        /* A save older than the revision field reads as revision 0. */
        if (ok) g_game_session.save_revision = 0;
        ok = ok && game_session_schema_migrate(&g_game_session, schema,
                schema_length, data, body->session_size);
        if (ok) game_session_schema_upgrade(&g_game_session);
        if (!ok) {
            g_game_session = *previous;
            g_menu.world_index = previous_world;
            g_menu.selected_tribe = previous_tribe;
            g_menu.difficulty = previous_difficulty;
        }
        free(previous);
        if (!ok) return 0;
    }
    g_game_session_world_index = body->world_index;
    g_menu.world_index = body->world_index;
    g_menu.difficulty = body->difficulty;
    g_menu.selected_tribe = body->selected_tribe;
    return 1;
}

/* Menu and view state for a game that was just loaded. */
static void reset_view_after_load(void)
{
    game_music_state_init(&g_game_music);
    g_game_session_valid = 1;
    clear_island_messages();
    g_menu.selected_map_island = -1;
    g_menu.setup_accepted = 1;
    g_selected_floater = -1;
    select_location_on_view(-1);
    g_hovered_island = -1;
    g_defeat_ticks = 0;
}

/* Restores a remake save; returns 0 (without touching the running game) when
   the file is not a valid remake save. */
static int read_save_file(HWND window, const char *path)
{
    RemakeSaveBody body;
    size_t length;
    unsigned char *bytes = read_whole_file(path, &length);
    int on_island;
    int ok = apply_remake_save_bytes(bytes, length, &body);
    free(bytes);
    if (!ok) return 0;
    /* A save made during a network game continues as a solo game here. */
    g_game_session.config.multiplayer_session = 0;
    g_game_session.network_paused = 0;
    reset_view_after_load();
    g_menu.animation_ticks = body.animation_ticks;
    g_sim_speed = body.sim_speed >= 1U && body.sim_speed <= 3U ? body.sim_speed : 1U;
    if (begin_tribe_choice(window)) return 1;
    on_island = body.on_island && body.selected_map_island >= 0;
    g_menu.screen = SCREEN_WORLD_MAP;
    if (on_island && !open_island_view(window, body.selected_map_island))
        g_menu.screen = SCREEN_WORLD_MAP;
    return 1;
}

/* An original save's bytes: the world and tribe come from the file, a fresh
   session is built for them and the native records are applied on top
   (core/native_save.c). Returns 0 and leaves the game and the menu as they
   were when the bytes cannot be restored. */
static int apply_native_save_bytes(const unsigned char *bytes, size_t length,
                                   char *error, size_t error_capacity)
{
    NativeSave save;
    int world;
    int previous_world = g_menu.world_index;
    int previous_tribe = g_menu.selected_tribe;
    int previous_difficulty = g_menu.difficulty;
    if (bytes == NULL ||
        !native_save_parse(bytes, length, &save, error, error_capacity))
        return 0;
    world = native_save_find_world(&save, &g_menu.world_map);
    if (world < 0 || save.tribe >= GAME_START_PLAYER_COUNT) {
        (void)snprintf(error, error_capacity,
                       "save world or tribe is not supported");
        return 0;
    }
    g_menu.world_index = world;
    g_menu.selected_tribe = (int)save.tribe;
    if (!load_game_session_for_selected_world(error, error_capacity) ||
        !native_save_apply(&save, &g_floater_catalog, &g_game_session, error,
                           error_capacity)) {
        g_menu.world_index = previous_world;
        g_menu.selected_tribe = previous_tribe;
        g_menu.difficulty = previous_difficulty;
        return 0;
    }
    return 1;
}

/* Loads an original-game save (C:\Program Files\Tone\NN.SAV; the process sees
   the VirtualStore copy). Returns 0 and leaves the running game untouched when
   the file cannot be restored. */
static int read_native_save_file(HWND window, const char *path, char *error,
                                 size_t error_capacity)
{
    size_t length;
    unsigned char *bytes = read_whole_file(path, &length);
    int ok;
    if (bytes == NULL) {
        (void)snprintf(error, error_capacity, "save file could not be read");
        return 0;
    }
    ok = apply_native_save_bytes(bytes, length, error, error_capacity);
    free(bytes);
    if (!ok) return 0;
    reset_view_after_load();
    g_sim_speed = 1U;
    g_menu.screen = SCREEN_WORLD_MAP;
    (void)begin_tribe_choice(window);
    return 1;
}

/* The host's save, applied to g_game_session on every machine of the
   lobby: the tribe choice offers the tribes played in it. The lobby keeps
   its own tribe for this machine. */
static int net_load_apply(void)
{
    RemakeSaveBody body;
    char error[160];
    int lobby_tribe = g_menu.selected_tribe;
    int ok = g_net_save_native
        ? apply_native_save_bytes(g_net_save, g_net_save_length, error, sizeof(error))
        : apply_remake_save_bytes(g_net_save, g_net_save_length, &body);
    if (!ok) return 0;
    g_game_session_valid = 0;
    g_tribe_choice_mask = (uint8_t)(game_session_active_player_mask(&g_game_session) |
        (g_menu.selected_tribe >= 0 && g_menu.selected_tribe < GAME_START_PLAYER_COUNT
             ? 1U << g_menu.selected_tribe : 0U));
    if (lobby_tribe >= 0 && lobby_tribe < GAME_START_PLAYER_COUNT)
        g_menu.selected_tribe = lobby_tribe;
    return 1;
}

/* Game start of a loaded network game: every machine applies the same file
   again, then plays its lobby tribe. */
static int net_load_start(HWND window, uint8_t tribe)
{
    if (!net_load_apply()) return 0;
    g_game_session.config.multiplayer_session = 1;
    g_game_session.config.selected_tribe = tribe;
    g_game_session.network_paused = 0;
    g_menu.selected_tribe = tribe;
    reset_view_after_load();
    g_sim_speed = 1U;
    net_save_clear();
    g_menu.screen = SCREEN_WORLD_MAP;
    update_window_title(window);
    platform_invalidate(window);
    return 1;
}

/* Lobby host: a save picked on the Load screen becomes the game to continue.
   Returns 1 when it was read and applied. */
static int net_host_pick_save(const char *path, int native)
{
    size_t length;
    unsigned char *bytes = read_whole_file(path, &length);
    unsigned tribe;
    if (bytes == NULL) {
        net_set_status(TR(T_NET_SAVE_UNREADABLE));
        return 0;
    }
    if (g_net_in_game) {
        /* Loading during the game: every machine goes back to the lobby
           first, then receives the file there. */
        uint8_t frame[NET_FRAME_MAX_SIZE];
        size_t frame_length = net_frame_encode(frame, sizeof(frame),
            NET_RECORD_LOBBY_RETURN, 0, NULL, 0);
        if (frame_length != 0U) net_host_broadcast(frame, frame_length);
        net_back_to_lobby();
    }
    net_save_clear();
    g_net_save = bytes;
    g_net_save_length = length;
    g_net_save_native = native ? 1U : 0U;
    if (!net_load_apply()) {
        net_save_clear();
        net_set_status(TR(T_NET_SAVE_UNREADABLE));
        return 0;
    }
    g_net_save_ready = 1;
    net_lobby_set_world(&g_net_lobby, (uint8_t)g_menu.world_index,
                        (uint8_t)g_menu.difficulty);
    if (g_net_lobby.players[0].tribe >= GAME_START_PLAYER_COUNT ||
        (g_tribe_choice_mask & (1U << g_net_lobby.players[0].tribe)) == 0) {
        for (tribe = 0; tribe < GAME_START_PLAYER_COUNT; ++tribe)
            if ((g_tribe_choice_mask & (1U << tribe)) != 0) break;
        (void)net_lobby_set_tribe(&g_net_lobby, 0, (uint8_t)tribe);
    }
    net_host_broadcast_state();
    net_set_status(TR(T_NET_SAVE_SENDING));
    return 1;
}

static int save_slot_path(int slot, char *path, size_t capacity)
{
    char directory[MAX_PATH];
    if (slot < 0 || slot > 7 || !save_directory(directory, sizeof(directory)))
        return 0;
    (void)snprintf(path, capacity, "%s/%02d.sav", directory, slot);
    return 1;
}

static int resume_path(char *path, size_t capacity)
{
    char directory[MAX_PATH];
    if (!save_directory(directory, sizeof(directory))) return 0;
    (void)snprintf(path, capacity, "%s/resume.gam", directory);
    return 1;
}

/* Leaves the Load/Save screen: Save returns to the screen it was opened from,
   Load returns to the title. */
static void leave_load_screen(void)
{
    if (g_net_load_pick) {
        /* Picking a save for the network lobby, or from a running network
           game (back to it when nothing was picked). */
        g_net_load_pick = 0;
        g_menu.screen = g_net_in_game ? g_save_return_screen : SCREEN_NEW_GAME;
        return;
    }
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
