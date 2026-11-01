/* Original game data location. The game files are read-only and need no
   installation: the directory may be the install folder, THING1 of an
   extracted or mounted ISO, or any folder holding TONE00/TONE01.COB.
   Search order: --game-dir <path>, TONE_REBELLION_GAME_DIR, next to the
   executable (and its THING1), C:\Program Files\Tone, THING1 on every drive
   (mounted ISO), C:\toneIso\THING1. */

static char g_game_directory[MAX_PATH];

static int game_directory_is_valid(const char *directory)
{
    char path[MAX_PATH];
    if (directory == NULL || directory[0] == '\0' ||
        strlen(directory) + sizeof("/TONE01.COB") >= sizeof(path)) return 0;
    (void)snprintf(path, sizeof(path), "%s/TONE01.COB", directory);
    return platform_path_kind(path) != PLATFORM_PATH_MISSING;
}

static int game_directory_accept(const char *directory)
{
    size_t length;
    if (!game_directory_is_valid(directory)) return 0;
    (void)snprintf(g_game_directory, sizeof(g_game_directory), "%s", directory);
    length = strlen(g_game_directory);
    while (length > 0 && (g_game_directory[length - 1] == '\\' ||
                          g_game_directory[length - 1] == '/')) {
        g_game_directory[--length] = '\0';
    }
    return 1;
}

/* A disc image (.iso) can be used directly: the files the game needs are
   copied once into a cache folder (the image itself is never modified) and
   that folder becomes the game directory. Tunes are copied on first use. */
static Iso9660 g_iso;
static int g_iso_open;
static char g_iso_cache[MAX_PATH];

static int iso_prepare_cache(void)
{
    char base[MAX_PATH];
    if (platform_environment("LOCALAPPDATA", base, sizeof(base) - 40U)) {
        (void)strcat(base, "/ToneRebellion_Remake");
        platform_create_directory(base);
    } else if (!platform_executable_directory(base, sizeof(base) - 40U)) {
        return 0;
    }
    (void)snprintf(g_iso_cache, sizeof(g_iso_cache), "%s/iso_cache", base);
    platform_create_directory(g_iso_cache);
    (void)snprintf(base, sizeof(base), "%s/THING1", g_iso_cache);
    platform_create_directory(base);
    (void)snprintf(base, sizeof(base), "%s/THING2", g_iso_cache);
    platform_create_directory(base);
    return 1;
}

static int iso_extract_to_cache(const char *iso_path, const char *name)
{
    IsoFile file;
    char destination[MAX_PATH];
    char error[128];
    if (!iso9660_find(&g_iso, iso_path, &file)) return 0;
    (void)snprintf(destination, sizeof(destination), "%s/%s", g_iso_cache, name);
    return iso9660_extract(&g_iso, &file, destination, error, sizeof(error));
}

static int game_directory_from_iso(const char *iso_path)
{
    static const char *const files[] = {
        "TONE00.COB", "TONE01.COB", "FLOAT.EXE", "FLOAT.CFG", "COB.CFG", "MULTI.CFG"
    };
    char error[128];
    char path[64];
    char cache_thing1[MAX_PATH];
    size_t index;

    if (iso_path == NULL || iso_path[0] == '\0') return 0;
    if (!iso9660_open(iso_path, &g_iso, error, sizeof(error))) return 0;
    g_iso_open = 1;
    if (!iso_prepare_cache()) goto fail;
    for (index = 0; index < sizeof(files) / sizeof(files[0]); ++index) {
        (void)snprintf(path, sizeof(path), "THING1/%s", files[index]);
        if (!iso_extract_to_cache(path, path) && index < 2) goto fail;
    }
    (void)snprintf(cache_thing1, sizeof(cache_thing1), "%s/THING1", g_iso_cache);
    if (game_directory_accept(cache_thing1)) return 1;
fail:
    iso9660_close(&g_iso);
    g_iso_open = 0;
    return 0;
}

/* Copies THING2\<file_name> out of the image on first use; fills `path`. */
static int iso_extract_music(const char *file_name, char *path, size_t path_capacity)
{
    char relative[64];
    if (!g_iso_open || strlen(file_name) + sizeof("THING2/") >= sizeof(relative)) return 0;
    (void)snprintf(relative, sizeof(relative), "THING2/%s", file_name);
    if (!iso_extract_to_cache(relative, relative)) return 0;
    return snprintf(path, path_capacity, "%s/%s", g_iso_cache, relative) < (int)path_capacity;
}

/* Value of `--name <v>`, `--name=<v>` or `--name "<v>"`; 0 when absent. */
static int command_line_value(const char *command_line, const char *name,
                              char *out, size_t capacity)
{
    const char *option = command_line != NULL ? strstr(command_line, name) : NULL;
    const char *cursor;
    size_t count = 0;
    if (option == NULL) return 0;
    cursor = option + strlen(name);
    while (*cursor == ' ' || *cursor == '=') ++cursor;
    if (*cursor == '"') {
        ++cursor;
        while (cursor[count] != '\0' && cursor[count] != '"') ++count;
    } else {
        while (cursor[count] != '\0' && cursor[count] != ' ') ++count;
    }
    if (count == 0 || count >= capacity) return 0;
    (void)memcpy(out, cursor, count);
    out[count] = '\0';
    return 1;
}

typedef struct IsoSearch {
    char *out;
    size_t capacity;
} IsoSearch;

static int visit_game_iso(const char *path, void *context)
{
    IsoSearch *search = (IsoSearch *)context;
    Iso9660 probe;
    IsoFile file;
    int ok;
    if (strlen(path) >= search->capacity || !iso9660_open(path, &probe, NULL, 0))
        return 0;
    ok = iso9660_find(&probe, "THING1\\TONE01.COB", &file);
    iso9660_close(&probe);
    if (ok) (void)strcpy(search->out, path);
    return ok;
}

/* First *.iso next to the executable that holds the game. */
static int find_adjacent_iso(const char *directory, char *out, size_t capacity)
{
    IsoSearch search;
    search.out = out;
    search.capacity = capacity;
    return platform_each_file(directory, ".iso", visit_game_iso, &search);
}

static void game_directory_resolve(const char *command_line)
{
    char candidate[MAX_PATH];
    char executable_directory[MAX_PATH];
    char drive;

    g_game_directory[0] = '\0';
    executable_directory[0] = '\0';
    if (command_line_value(command_line, "--game-dir", candidate, sizeof(candidate)) &&
        game_directory_accept(candidate)) return;
    if (command_line_value(command_line, "--iso", candidate, sizeof(candidate)) &&
        game_directory_from_iso(candidate)) return;
    /* Dropping an .iso (or a game folder) on the executable passes it as the
       sole argument. */
    if (command_line != NULL) {
        const char *cursor = command_line;
        size_t count = 0;
        while (*cursor == ' ') ++cursor;
        if (*cursor != '-' && *cursor != '\0') {
            if (*cursor == '"') {
                ++cursor;
                while (cursor[count] != '\0' && cursor[count] != '"') ++count;
            } else {
                while (cursor[count] != '\0') ++count;
                while (count > 0 && cursor[count - 1] == ' ') --count;
            }
            if (count > 0 && count < sizeof(candidate)) {
                int kind;
                (void)memcpy(candidate, cursor, count);
                candidate[count] = '\0';
                kind = platform_path_kind(candidate);
                if (kind != PLATFORM_PATH_MISSING) {
                    if (kind == PLATFORM_PATH_DIRECTORY) {
                        char thing1[MAX_PATH];
                        if (game_directory_accept(candidate)) return;
                        (void)snprintf(thing1, sizeof(thing1), "%s/THING1", candidate);
                        if (game_directory_accept(thing1)) return;
                    } else if (game_directory_from_iso(candidate)) {
                        return;
                    }
                }
            }
        }
    }
    if (platform_environment("TONE_REBELLION_GAME_DIR", candidate, sizeof(candidate)) &&
        game_directory_accept(candidate)) return;
    if (platform_environment("TONE_REBELLION_ISO", candidate, sizeof(candidate)) &&
        game_directory_from_iso(candidate)) return;
    if (platform_executable_directory(executable_directory, sizeof(executable_directory))) {
        char sibling[MAX_PATH];
        if (game_directory_accept(executable_directory)) return;
        if (strlen(executable_directory) + sizeof("/THING1") < sizeof(sibling)) {
            (void)snprintf(sibling, sizeof(sibling), "%s/THING1", executable_directory);
            if (game_directory_accept(sibling)) return;
        }
    } else {
        executable_directory[0] = '\0';
    }
    if (game_directory_accept("C:\\Program Files\\Tone")) return;
    for (drive = 'A'; drive <= 'Z'; ++drive) {
        (void)snprintf(candidate, sizeof(candidate), "%c:\\THING1", drive);
        if (game_directory_accept(candidate)) return;
    }
    if (game_directory_accept("C:\\toneIso\\THING1")) return;
    if (executable_directory[0] != '\0' &&
        find_adjacent_iso(executable_directory, candidate, sizeof(candidate)) &&
        game_directory_from_iso(candidate)) return;
    if (game_directory_from_iso("C:\\TONE116F.ISO")) return;
    /* Keep the historical default so load errors name a concrete path. */
    (void)snprintf(g_game_directory, sizeof(g_game_directory), "C:\\Program Files\\Tone");
}

/* Full path of `name` inside the game directory; rotating buffers let several
   calls appear in one expression. */
static const char *game_file_path(const char *name)
{
    static char buffers[4][MAX_PATH];
    static unsigned next;
    char *buffer = buffers[next++ & 3U];
    (void)snprintf(buffer, MAX_PATH, "%s/%s", g_game_directory, name);
    return buffer;
}
