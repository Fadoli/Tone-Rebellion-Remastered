/* IWLilMap palette slots DAT_0049e140[1..6] are the 6-bit RGB triples at
   0x49e148 matched to the island palette by FUN_0041081b (assumed nearest
   colour); slot 0 is palette entry 0. */
static COLORREF lilmap_slot_color(int slot)
{
    static const unsigned char rgb6[7][3] = {
        {0, 0, 0}, {63, 63, 63}, {63, 0, 0}, {0, 63, 0},
        {0, 0, 63}, {63, 63, 0}, {50, 50, 50}
    };
    int best = 0;
    int best_distance = 0x7fffffff;
    int index;
    if (slot <= 0 || slot > 6) return g_island_palette[0];
    for (index = 0; index < 256; ++index) {
        int dr = (int)GetRValue(g_island_palette[index]) - rgb6[slot][0] * 255 / 63;
        int dg = (int)GetGValue(g_island_palette[index]) - rgb6[slot][1] * 255 / 63;
        int db = (int)GetBValue(g_island_palette[index]) - rgb6[slot][2] * 255 / 63;
        int distance = dr * dr + dg * dg + db * db;
        if (distance < best_distance) {
            best_distance = distance;
            best = index;
        }
    }
    return g_island_palette[best];
}

static void rebuild_island_palette_lookup(void)
{
    uint32_t palette_rgb24[256];
    unsigned int index;
    for (index = 0; index < 256U; ++index) {
        palette_rgb24[index] = (uint32_t)g_island_palette[index] &
                               UINT32_C(0x00ffffff);
    }
    /* Task row highlights use entries 0..254 in the original scan. */
    island_palette_lookup_build(&g_island_palette_lookup, palette_rgb24, 255U);
    /* The selected row uses this fixed haze transform for every pixel. Cache
       the final opaque color by palette index instead of repeating haze and
       COLORREF conversion work in the per-pixel loop. */
    for (index = 0; index < 256U; ++index) {
        uint8_t remapped_index = island_haze_remap(&g_island_haze, 1, 1,
                                                   (uint8_t)index);
        COLORREF color = g_island_palette[remapped_index];
        g_task_highlight_pixels[index] = 0xff000000U |
            ((DWORD)GetRValue(color) << 16) |
            ((DWORD)GetGValue(color) << 8) | (DWORD)GetBValue(color);
    }
    /* A 256-entry search per slot: once per palette, not per dot. */
    for (index = 0; index < 7U; ++index)
        g_lilmap_slot_colors[index] = lilmap_slot_color((int)index);
}

static int g_mouse_x;
static int g_mouse_y;
static int island_location_at(int x, int y);

/* FUN_00435581 hit test under the mouse: 2 = floater, 1 = island site,
   0 = nothing (playfield only). */
static int island_cursor_hit_kind(void)
{
    if (!g_game_session_valid || g_mouse_x < 0 || g_mouse_x >= LOGICAL_WIDTH ||
        g_mouse_y < 0 || g_mouse_y >= 320) return 0;
    if (game_session_floater_at(&g_game_session,
            (uint8_t)g_menu.selected_map_island,
            (uint16_t)(g_mouse_x + g_island_scroll_x),
            (uint16_t)g_mouse_y) >= 0) return 2;
    return island_location_at(g_mouse_x, g_mouse_y) >= 0 ? 1 : 0;
}

static void update_interaction_cursor(void)
{
    int slot = 0;
    if (g_menu.screen == SCREEN_ISLAND) {
        /* FUN_0043530b mode -> slot (+0x17e) and hit kind (+0x178): grab
           (mode 1) 9/kind 1; armed item/glyph (mode 0x11) 11/kind 1; order
           genres 6..9 -> modes 0x10..0x13: 3/kind 2, 13/kind 1, 5/kind 2,
           15/kind 4; spells 0xb/kind 1 for a site pick, 7/kind 2 for a
           floater pick (ev_614c66b1). FUN_004337d9 case 10 (ev_bf1a97d8)
           shows slot + 1 while the hovered hit matches the kind; with no
           mode any floater or site hit shows cursor 1 (resource 0x75). */
        static const int k_order_slots[4] = {3, 13, 5, 15};
        static const int k_order_kinds[4] = {2, 1, 2, 4};
        int kind = 0;
        int hit = island_cursor_hit_kind();
        if (game_glyph_inventory_cursor_slot(g_selected_glyph,
                                             g_selected_inventory_item) == 0x0b) {
            slot = 0x0b;
            kind = 1;
        } else if (g_defend_area_armed >= 6 && g_defend_area_armed <= 9) {
            slot = k_order_slots[g_defend_area_armed - 6];
            kind = k_order_kinds[g_defend_area_armed - 6];
        } else if (g_armed_spell_action != 0) {
            slot = g_armed_spell_pick == 2 ? 7 : 0x0b;
            kind = g_armed_spell_pick == 2 ? 2 : 1;
        } else if (g_game_session_valid &&
                   g_game_session.location_move_active) {
            slot = 9;
            kind = 1;
        }
        if (kind == 0) {
            if (hit != 0) slot = 1;
        } else if (kind == hit) {
            ++slot;
        }
    }
    if (g_interaction_cursors[slot] != NULL) {
        SetCursor(g_interaction_cursors[slot]);
        return;
    }
    SetCursor(LoadCursorA(NULL, IDC_ARROW));
}


static void update_window_title(HWND window);
static void set_background_tune(const char *tune_id);
static void set_background_tune_once(const char *tune_id);
static void stop_background_tune(void);
static void draw_location_action_panel(RenderSurface *surface);
static void draw_clipboard_strip(RenderSurface *surface);
static int load_game_session_for_selected_world(char *error, size_t error_capacity);
static int draw_building_preview(RenderSurface *surface, uint16_t item_id, uint8_t player_slot,
                                 int x, int y, uint32_t scale_16_16);
static int draw_runtime_item_scaled(RenderSurface *surface,
                                    const GameRuntimeLocation *runtime_location,
                                    int x, int y, uint32_t scale_16_16);

static int begin_new_game(HWND window)
{
    char error[256];
    g_sim_speed = 1U;   /* FUN_004121b7 case 9 resets DAT_004bf110 */
    if (!load_game_session_for_selected_world(error, sizeof(error))) {
        platform_message_box(window, error, "Tone Rebellion remake - game setup error",
                             1);
        return 0;
    }
    g_menu.setup_accepted = 1;
    g_menu.selected_map_island = -1;
    g_hovered_island = -1;
    g_menu.screen = SCREEN_WORLD_MAP;
    update_window_title(window);
    InvalidateRect(window, NULL, FALSE);
    return 1;
}

static const int g_difficulty_count = 5;
static void update_window_title(HWND window)
{
    const char *title = "Tone Rebellion - Title";
    if (g_menu.screen == SCREEN_NEW_GAME) title = "Tone Rebellion - New Game";
    else if (g_menu.screen == SCREEN_NET_SETUP) title = "Tone Rebellion - Multiplayer";
    else if (g_menu.screen == SCREEN_WORLD_MAP) title = "Tone Rebellion - World Map";
    else if (g_menu.screen == SCREEN_ISLAND)
        title = "Tone Rebellion - Island (arrows: scroll, Esc: map)";
    else if (g_menu.screen == SCREEN_LOAD_GAME) title = g_load_save_mode ? "Tone Rebellion - Save Game (Esc: back)" : "Tone Rebellion - Load Game (Esc: back)";
    platform_set_title(window, title);
    if (g_menu.screen != SCREEN_ISLAND) {
        /* FUN_004489c0 requests ambi1 for the title. The remake keeps this
           menu bed through setup/map screens. Island-entry music is selected
           once per realm using FUN_00470fe7's transition table. */
        set_background_tune("ambi1");
    }
}

typedef struct MusicTune {
    const char *id;
    const char *file_name;
} MusicTune;

static const MusicTune g_music_tunes[] = {
    {"tribe0", "PROTECT.WAV"}, {"tribe1", "SEEKERS.WAV"},
    {"tribe2", "MYSTICS.WAV"}, {"tribe3", "LIFEGIVE.WAV"},
    /* sound.txt deliberately maps act indices in reverse file order. */
    {"act1", "ACT4.WAV"}, {"act2", "ACT3.WAV"},
    {"act3", "ACT2.WAV"}, {"act4", "ACT1.WAV"},
    {"start", "START.WAV"}, {"ambi1", "AMBIENT1.WAV"},
    {"ambi2", "AMBIENT2.WAV"}, {"ambi3", "AMBIENT3.WAV"},
    {"ambi4", "AMBIENT4.WAV"}, {"levi", "LEVIATAN.WAV"},
    {"winend", "WINNER.WAV"}, {"loosend", "LOSEND.WAV"}
};

static int music_file_exists_in(const char *directory, const char *file_name,
                                char *path, size_t path_capacity)
{
    DWORD attributes;
    int written = snprintf(path, path_capacity, "%s\\%s", directory, file_name);
    if (written < 0 || (size_t)written >= path_capacity) return 0;
    attributes = GetFileAttributesA(path);
    return attributes != INVALID_FILE_ATTRIBUTES &&
           (attributes & FILE_ATTRIBUTE_DIRECTORY) == 0;
}

static int resolve_music_directory(const char *file_name,
                                   char *path, size_t path_capacity)
{
    char candidate[MAX_PATH];
    DWORD environment_length;
    DWORD executable_length;
    char *separator;

    if (g_iso_open && iso_extract_music(file_name, path, path_capacity)) return 1;
    if (g_music_directory[0] != '\0' &&
        music_file_exists_in(g_music_directory, file_name, path, path_capacity)) {
        return 1;
    }
    environment_length = GetEnvironmentVariableA(
        "TONE_REBELLION_THING2", candidate, (DWORD)sizeof(candidate));
    if (environment_length > 0 && environment_length < sizeof(candidate) &&
        music_file_exists_in(candidate, file_name, path, path_capacity)) {
        (void)strncpy(g_music_directory, candidate, sizeof(g_music_directory) - 1);
        g_music_directory[sizeof(g_music_directory) - 1] = '\0';
        return 1;
    }
    executable_length = GetModuleFileNameA(NULL, candidate, (DWORD)sizeof(candidate));
    if (executable_length > 0 && executable_length < sizeof(candidate)) {
        separator = strrchr(candidate, '\\');
        if (separator != NULL) {
            *separator = '\0';
            if (strlen(candidate) + sizeof("\\THING2") < sizeof(g_music_directory)) {
                (void)strcpy(g_music_directory, candidate);
                (void)strcat(g_music_directory, "\\THING2");
                if (music_file_exists_in(g_music_directory, file_name,
                                         path, path_capacity)) return 1;
            }
        }
    }
    /* Disc layout: game files in THING1, music in the sibling THING2. */
    if (strlen(g_game_directory) + sizeof("\\..\\THING2") < sizeof(candidate)) {
        (void)snprintf(candidate, sizeof(candidate), "%s\\..\\THING2", g_game_directory);
        if (music_file_exists_in(candidate, file_name, path, path_capacity)) {
            (void)strncpy(g_music_directory, candidate, sizeof(g_music_directory) - 1);
            g_music_directory[sizeof(g_music_directory) - 1] = '\0';
            return 1;
        }
    }
    if (music_file_exists_in("C:\\toneIso\\THING2", file_name,
                             path, path_capacity)) {
        (void)strcpy(g_music_directory, "C:\\toneIso\\THING2");
        return 1;
    }
    return 0;
}

static void stop_background_tune(void)
{
    if (g_music_device_open) {
#ifdef TONE_PLATFORM_SDL
        sdl_music_close();
#else
        (void)mciSendStringA("stop tone_music", NULL, 0, NULL);
        (void)mciSendStringA("close tone_music", NULL, 0, NULL);
#endif
        g_music_device_open = 0;
    }
    g_current_tune[0] = '\0';
    g_music_loops = 0;
}

static void keep_background_tune_playing(void)
{
    if (!g_music_device_open || g_current_tune[0] == '\0') return;
#ifdef TONE_PLATFORM_SDL
    /* The stream callback rewinds a looping tune itself. */
    if (sdl_music_stopped()) {
        if (g_music_loops) {
            char tune[sizeof(g_current_tune)];
            (void)strcpy(tune, g_current_tune);
            stop_background_tune();
            set_background_tune(tune);
        } else {
#else
    char mode[32];
    MCIERROR result;

    result = mciSendStringA("status tone_music mode", mode, sizeof(mode), NULL);
    if (result == 0 && strcmp(mode, "stopped") == 0) {
        if (g_music_loops) {
            (void)mciSendStringA("play tone_music from 0", NULL, 0, NULL);
        } else {
#endif
            /* FUN_0041c46f requests the `start` tune once; the title handler
               then requests the looping `ambi1` menu bed. */
            stop_background_tune();
            set_background_tune("ambi1");
        }
    }
}

static void set_background_tune_mode(const char *tune_id, int loop)
{
    char path[MAX_PATH];
    char command[MAX_PATH + 64];
    size_t i;
    const char *file_name = NULL;
    MCIERROR result;

    if (tune_id == NULL || strcmp(g_current_tune, tune_id) == 0) return;
    if (!g_music_enabled) {
        /* Music is switched off in the SlideWindow: remember the request. */
        (void)strncpy(g_music_resume_tune, tune_id, sizeof(g_music_resume_tune) - 1);
        g_music_resume_tune[sizeof(g_music_resume_tune) - 1] = '\0';
        g_music_resume_loop = loop;
        return;
    }
    for (i = 0; i < sizeof(g_music_tunes) / sizeof(g_music_tunes[0]); ++i) {
        if (strcmp(g_music_tunes[i].id, tune_id) == 0) {
            file_name = g_music_tunes[i].file_name;
            break;
        }
    }
    if (file_name == NULL ||
        !resolve_music_directory(file_name, path, sizeof(path))) return;

    stop_background_tune();
#ifdef TONE_PLATFORM_SDL
    /* Silent until apply_music_volume below sets the slider gain. */
    (void)command;
    (void)result;
    if (!sdl_music_open(path, loop, 0.0)) return;
    g_music_device_open = 1;
#else
    {
        int command_length = snprintf(
            command, sizeof(command),
            "open \"%s\" type mpegvideo alias tone_music", path);
        if (command_length < 0 || (size_t)command_length >= sizeof(command)) return;
    }
    result = mciSendStringA(command, NULL, 0, NULL);
    if (result != 0) return;
    g_music_device_open = 1;
    result = mciSendStringA("play tone_music", NULL, 0, NULL);
    if (result != 0) {
        stop_background_tune();
        return;
    }
#endif
    (void)strncpy(g_current_tune, tune_id, sizeof(g_current_tune) - 1);
    g_current_tune[sizeof(g_current_tune) - 1] = '\0';
    g_music_loops = loop;
    (void)strncpy(g_music_resume_tune, tune_id, sizeof(g_music_resume_tune) - 1);
    g_music_resume_tune[sizeof(g_music_resume_tune) - 1] = '\0';
    g_music_resume_loop = loop;
    apply_music_volume();
}

static void set_background_tune(const char *tune_id)
{
    set_background_tune_mode(tune_id, 1);
}

static void set_background_tune_once(const char *tune_id)
{
    set_background_tune_mode(tune_id, 0);
}

static int load_palette(CobArchive *archive, const char *member_name,
                        COLORREF palette[256], uint8_t palette_rgb6[768],
                        char *error, size_t error_capacity)
{
    const CobMember *member = cob_archive_find(archive, member_name);
    unsigned char bytes[768];
    size_t i;
    if (member == NULL || member->length != sizeof(bytes) ||
        !cob_archive_read_member(archive, member, bytes, sizeof(bytes), error, error_capacity)) {
        if (member == NULL) {
            (void)snprintf(error, error_capacity, "%s was not found in TONE01.COB", member_name);
        } else if (member->length != sizeof(bytes)) {
            (void)snprintf(error, error_capacity, "%s has an unexpected palette size", member_name);
        }
        return 0;
    }
    for (i = 0; i < 256; ++i) {
        unsigned r = bytes[i * 3] > 63 ? 255u : (unsigned)bytes[i * 3] * 255u / 63u;
        unsigned g = bytes[i * 3 + 1] > 63 ? 255u : (unsigned)bytes[i * 3 + 1] * 255u / 63u;
        unsigned b = bytes[i * 3 + 2] > 63 ? 255u : (unsigned)bytes[i * 3 + 2] * 255u / 63u;
        palette[i] = RGB(r, g, b);
    }
    if (palette_rgb6 != NULL) memcpy(palette_rgb6, bytes, sizeof(bytes));
    return 1;
}

/* Native text pen slots 1..6 (DAT_0049e140, FUN_0042bfa9): after every palette
   change the slot holds the palette index nearest (squared RGB distance over
   6-bit values, indices 0..254, first minimum wins; FUN_0041081b) to the fixed
   targets at 0x49e148: white, red, green, blue, yellow, grey (50,50,50). */
static COLORREF native_text_color(const COLORREF palette[256], int slot)
{
    static const unsigned char target[7][3] = {
        {0, 0, 0}, {63, 63, 63}, {63, 0, 0}, {0, 63, 0},
        {0, 0, 63}, {63, 63, 0}, {50, 50, 50}};
    int i;
    int best = 0;
    int best_distance = 0;
    if (slot < 1 || slot > 6) return palette[slot & 0xff];
    for (i = 0; i < 255; ++i) {
        int r = (int)(GetRValue(palette[i]) * 63u / 255u) - target[slot][0];
        int g = (int)(GetGValue(palette[i]) * 63u / 255u) - target[slot][1];
        int b = (int)(GetBValue(palette[i]) * 63u / 255u) - target[slot][2];
        int distance = r * r + g * g + b * b;
        if (i == 0 || distance < best_distance) {
            best = i;
            best_distance = distance;
        }
        if (distance == 0) break;
    }
    return palette[best];
}

/* Port choice: island palettes differ only in entries 224..254, so a sheet
   whose opaque pixels avoid them converts to the same bitmaps on every
   island. Loaded sheets are shared by COB member and the colors their pixels
   use, which lets an island switch reuse them instead of decoding again. */
struct SpriteSheetShare {
    SpriteSheetShare *next;
    SpriteSheetShare *mirror;    /* shared horizontal mirror of this sheet */
    SpriteSheetShare *mirror_of; /* source sheet of a mirror */
    char name[COB_ARCHIVE_NAME_CAPACITY]; /* empty for mirrors */
    uint32_t offset;
    uint32_t length;
    uint32_t used[8];
    COLORREF palette[256];
    unsigned int references;
    SpriteFrame *frames;
    uint32_t frame_count;
};

static SpriteSheetShare *g_sprite_sheet_shares;

/* A cleared (transparent) width x height frame, or NULL. */
static uint32_t *sprite_pixels_alloc(int width, int height)
{
    if (width <= 0 || height <= 0) return (uint32_t *)calloc(1, sizeof(uint32_t));
    return (uint32_t *)calloc((size_t)width * (size_t)height, sizeof(uint32_t));
}

static SpriteSheetShare *sprite_share_find(const CobMember *member,
                                           const COLORREF palette[256])
{
    SpriteSheetShare *share;
    for (share = g_sprite_sheet_shares; share != NULL; share = share->next) {
        unsigned int i;
        if (share->name[0] == '\0' || share->offset != member->offset ||
            share->length != member->length ||
            strcmp(share->name, member->name) != 0) continue;
        for (i = 0; i < 256U; ++i) {
            if (((share->used[i >> 5] >> (i & 31U)) & 1U) != 0U &&
                share->palette[i] != palette[i]) break;
        }
        if (i == 256U) return share;
    }
    return NULL;
}

static void sprite_share_attach(SpriteSheetShare *share, SpriteSheet *sheet)
{
    ++share->references;
    sheet->frames = share->frames;
    sheet->frame_count = share->frame_count;
    sheet->share = share;
}

/* Hands a freshly built sheet's frames to a new share; on allocation failure
   the sheet simply stays private. */
static SpriteSheetShare *sprite_share_adopt(SpriteSheet *sheet)
{
    SpriteSheetShare *share = (SpriteSheetShare *)calloc(1, sizeof(*share));
    if (share == NULL) return NULL;
    share->frames = sheet->frames;
    share->frame_count = sheet->frame_count;
    share->references = 1;
    share->next = g_sprite_sheet_shares;
    g_sprite_sheet_shares = share;
    sheet->share = share;
    return share;
}

static void sprite_share_release(SpriteSheetShare *share)
{
    SpriteSheetShare **link;
    uint32_t i;
    if (--share->references != 0) return;
    for (link = &g_sprite_sheet_shares; *link != NULL; link = &(*link)->next) {
        if (*link == share) {
            *link = share->next;
            break;
        }
    }
    if (share->mirror != NULL) share->mirror->mirror_of = NULL;
    if (share->mirror_of != NULL) share->mirror_of->mirror = NULL;
    for (i = 0; i < share->frame_count; ++i) free(share->frames[i].pixels);
    free(share->frames);
    free(share);
}

static int load_sprite_sheet(CobArchive *archive, const char *member_name,
                             const COLORREF palette[256], SpriteSheet *sheet,
                             char *error, size_t error_capacity)
{
    const CobMember *member = cob_archive_find(archive, member_name);
    unsigned char *bytes;
    ShpFile source;
    uint32_t frame_index;
    uint32_t used[8] = {0};
    SpriteSheetShare *share;
    sheet->share = NULL;
    if (member == NULL) {
        (void)snprintf(error, error_capacity, "%s was not found in TONE01.COB", member_name);
        return 0;
    }
    share = sprite_share_find(member, palette);
    if (share != NULL) {
        sprite_share_attach(share, sheet);
        return 1;
    }
    bytes = (unsigned char *)malloc(member->length == 0 ? 1 : member->length);
    if (bytes == NULL || !cob_archive_read_member(archive, member, bytes, member->length,
                                                   error, error_capacity)) {
        free(bytes);
        return 0;
    }
    if (!shp_file_init(&source, bytes, member->length, error, error_capacity)) {
        free(bytes);
        return 0;
    }
    sheet->frames = (SpriteFrame *)calloc(source.frame_count, sizeof(*sheet->frames));
    if (sheet->frames == NULL) {
        free(bytes);
        (void)snprintf(error, error_capacity, "could not allocate sprite frame table");
        return 0;
    }
    sheet->frame_count = source.frame_count;
    for (frame_index = 0; frame_index < source.frame_count; ++frame_index) {
        ShpFrame decoded;
        uint32_t *pixels;
        size_t p;
        int hit_left;
        int hit_top;
        int hit_right = -1;
        int hit_bottom = -1;
        if (!shp_decode_frame(&source, frame_index, &decoded, error, error_capacity)) {
            free(bytes);
            return 0;
        }
        hit_left = (int)decoded.width;
        hit_top = (int)decoded.height;
        pixels = sprite_pixels_alloc((int)decoded.width, (int)decoded.height);
        if (pixels == NULL) {
            shp_frame_free(&decoded);
            free(bytes);
            (void)snprintf(error, error_capacity, "could not allocate sprite pixels");
            return 0;
        }
        for (p = 0; p < (size_t)decoded.width * decoded.height; ++p) {
            uint32_t *pixel = pixels + p;
            COLORREF color = palette[decoded.pixels[p]];
            if (decoded.opaque[p]) {
                int pixel_x = (int)(p % decoded.width);
                int pixel_y = (int)(p / decoded.width);
                used[decoded.pixels[p] >> 5] |= 1U << (decoded.pixels[p] & 31U);
                *pixel = 0xff000000u | colorref_pixel(color);
                if (pixel_x < hit_left) hit_left = pixel_x;
                if (pixel_y < hit_top) hit_top = pixel_y;
                if (pixel_x + 1 > hit_right) hit_right = pixel_x + 1;
                if (pixel_y + 1 > hit_bottom) hit_bottom = pixel_y + 1;
            } else {
                *pixel = 0;
            }
        }
        sheet->frames[frame_index].pixels = pixels;
        sheet->frames[frame_index].width = (int)decoded.width;
        sheet->frames[frame_index].height = (int)decoded.height;
        sheet->frames[frame_index].x_offset = decoded.x_offset;
        sheet->frames[frame_index].y_offset = decoded.y_offset;
        sheet->frames[frame_index].hit_left = hit_left;
        sheet->frames[frame_index].hit_top = hit_top;
        sheet->frames[frame_index].hit_right = hit_right;
        sheet->frames[frame_index].hit_bottom = hit_bottom;
        shp_frame_free(&decoded);
    }
    free(bytes);
    share = sprite_share_adopt(sheet);
    if (share != NULL) {
        (void)snprintf(share->name, sizeof(share->name), "%s", member->name);
        share->offset = member->offset;
        share->length = member->length;
        memcpy(share->used, used, sizeof(share->used));
        memcpy(share->palette, palette, sizeof(share->palette));
    }
    return 1;
}

static void free_sprite_sheet(SpriteSheet *sheet)
{
    uint32_t i;
    if (sheet->share != NULL) {
        sprite_share_release(sheet->share);
    } else if (sheet->frames != NULL) {
        for (i = 0; i < sheet->frame_count; ++i) free(sheet->frames[i].pixels);
        free(sheet->frames);
    }
    memset(sheet, 0, sizeof(*sheet));
}

/* FUN_00423068 stores facing-left in object flag 0x002, and FUN_0042704b
   passes a negative horizontal scale for that state. Cache equivalent flipped
   frames so the blitter only ever copies left to right. */
static int mirror_sprite_sheet_horizontally(const SpriteSheet *source,
                                            SpriteSheet *out,
                                            char *error, size_t error_capacity)
{
    uint32_t frame_index;
    if (source == NULL || out == NULL || source->frames == NULL ||
        source->frame_count == 0) return 0;
    memset(out, 0, sizeof(*out));
    if (source->share != NULL && source->share->mirror != NULL) {
        sprite_share_attach(source->share->mirror, out);
        return 1;
    }
    out->frames = (SpriteFrame *)calloc(source->frame_count, sizeof(*out->frames));
    if (out->frames == NULL) {
        (void)snprintf(error, error_capacity, "could not allocate mirrored floater frames");
        return 0;
    }
    out->frame_count = source->frame_count;
    for (frame_index = 0; frame_index < source->frame_count; ++frame_index) {
        const SpriteFrame *input = &source->frames[frame_index];
        SpriteFrame *output = &out->frames[frame_index];
        uint32_t *pixels;
        int y;

        if (input->pixels == NULL || input->width <= 0 || input->height <= 0) {
            (void)snprintf(error, error_capacity,
                           "floater sprite has an invalid frame for horizontal mirroring");
            free_sprite_sheet(out);
            return 0;
        }
        pixels = sprite_pixels_alloc(input->width, input->height);
        if (pixels == NULL) {
            (void)snprintf(error, error_capacity,
                           "could not create horizontally mirrored floater frame");
            free_sprite_sheet(out);
            return 0;
        }
        for (y = 0; y < input->height; ++y) {
            const uint32_t *source_row = input->pixels +
                                         (size_t)y * (size_t)input->width;
            uint32_t *destination_row = pixels +
                                        (size_t)y * (size_t)input->width;
            int x;
            for (x = 0; x < input->width; ++x) {
                destination_row[x] = source_row[input->width - 1 - x];
            }
        }
        *output = *input;
        output->pixels = pixels;
        /* Reflect the frame bounds around the floater origin as well as its
           pixels. Keeping the source offset unchanged makes left-facing
           animation frames slide relative to the worker as their widths and
           offsets change. */
        output->x_offset = -input->x_offset - input->width;
        output->hit_left = input->width - input->hit_right;
        output->hit_right = input->width - input->hit_left;
    }
    if (source->share != NULL) {
        SpriteSheetShare *mirror = sprite_share_adopt(out);
        if (mirror != NULL) {
            mirror->mirror_of = source->share;
            source->share->mirror = mirror;
        }
    }
    return 1;
}

/* FUN_00432940 is the original location comparator: ascending Y coordinate. */
static void build_island_draw_order(void)
{
    uint16_t i;
    for (i = 0; i < g_island_surface_data.location_count; ++i) {
        uint16_t index = i;
        uint16_t j = i;
        while (j > 0 &&
               g_island_surface_data.locations[g_island_draw_order[j - 1]].y >
                   g_island_surface_data.locations[index].y) {
            g_island_draw_order[j] = g_island_draw_order[j - 1];
            --j;
        }
        g_island_draw_order[j] = index;
    }
}

static uint32_t hazed_island_pixel(uint32_t pixel, int selector, int level);

/* FUN_0040bf98 copies a FUN_004106dd haze table into DAT_0049a610 for the
   flag-0x10 placement ramp and blits the following layers through it
   (FUN_00404c5a). A negative level draws sprites unchanged. */
static int g_sprite_haze_selector;
static int g_sprite_haze_level = -1;

typedef struct SpriteHaze {
    int selector;
    int level;
} SpriteHaze;

static uint32_t sprite_haze_pixel(uint32_t pixel, void *context)
{
    const SpriteHaze *haze = (const SpriteHaze *)context;
    return hazed_island_pixel(pixel, haze->selector, haze->level);
}

/* Source-over blit of a whole frame at the frame's offset. */
static void draw_sprite(RenderSurface *surface, const SpriteSheet *sheet,
                        uint32_t frame_index, int x, int y)
{
    const SpriteFrame *frame;
    if (sheet == NULL || frame_index >= sheet->frame_count) return;
    frame = &sheet->frames[frame_index];
    if (frame->pixels == NULL) return;
    render_surface_blit(surface, frame->pixels, frame->width, frame->height,
                        frame->width, 0, 0, frame->width, frame->height,
                        x + frame->x_offset, y + frame->y_offset, 0x10000U,
                        NULL, NULL);
}

/* FUN_00405265 scales by sampling the source pixel under each destination
   pixel (16.16 step), so a reduced sprite stays opaque and sharp (a
   filtering stretch blended transparent pixels in, which made half-size
   building previews look ghostly, like unfinished buildings). */
static void draw_frame_scaled(RenderSurface *surface, const SpriteFrame *frame,
                              int x, int y, uint32_t scale_16_16,
                              const SpriteHaze *haze)
{
    int width;
    int height;
    if (frame->pixels == NULL || scale_16_16 == 0U) return;
    width = (int)(((uint64_t)(unsigned)frame->width * scale_16_16) >> 16);
    height = (int)(((uint64_t)(unsigned)frame->height * scale_16_16) >> 16);
    if (width <= 0 || height <= 0) return;
    render_surface_blit(surface, frame->pixels, frame->width, frame->height,
        frame->width, 0, 0, width, height,
        x + (int)(((int64_t)frame->x_offset * scale_16_16) >> 16),
        y + (int)(((int64_t)frame->y_offset * scale_16_16) >> 16),
        scale_16_16, haze != NULL ? sprite_haze_pixel : NULL, (void *)haze);
}

static void draw_sprite_scaled_plain(RenderSurface *surface,
                                     const SpriteSheet *sheet,
                                     uint32_t frame_index, int x, int y,
                                     uint32_t scale_16_16)
{
    if (sheet == NULL || frame_index >= sheet->frame_count) return;
    draw_frame_scaled(surface, &sheet->frames[frame_index], x, y, scale_16_16,
                      NULL);
}

static uint32_t hazed_island_pixel(uint32_t pixel, int selector, int level)
{
    uint8_t index;
    COLORREF color;
    if (!island_palette_lookup_nearest(&g_island_palette_lookup,
            (uint32_t)RGB((pixel >> 16) & 0xffU, (pixel >> 8) & 0xffU,
                          pixel & 0xffU) & UINT32_C(0x00ffffff), &index))
        return pixel;
    color = g_island_palette[island_haze_remap(&g_island_haze, selector,
                                               level, index)];
    return 0xff000000U | colorref_pixel(color);
}

/* Scaled blit through the current sprite haze (g_sprite_haze_level). */
static void draw_sprite_scaled(RenderSurface *surface, const SpriteSheet *sheet,
                               uint32_t frame_index, int x, int y,
                               uint32_t scale_16_16)
{
    SpriteHaze haze;
    if (sheet == NULL || frame_index >= sheet->frame_count) return;
    haze.selector = g_sprite_haze_selector;
    haze.level = g_sprite_haze_level;
    draw_frame_scaled(surface, &sheet->frames[frame_index], x, y, scale_16_16,
                      haze.level >= 0 ? &haze : NULL);
}

/* FUN_004109a6: every destination pixel under the frame's opaque RLE spans is
   replaced by table[destination]; the sprite's own colors are ignored. The
   surface clip does not apply, only `clip` (inclusive bounds) when given. */
static void recolor_under_sprite_clipped(RenderSurface *surface,
                                         const SpriteSheet *sheet,
                                         uint32_t frame_index, int x, int y,
                                         int selector, int level,
                                         const RECT *clip)
{
    const SpriteFrame *frame;
    int row;
    if (sheet == NULL || frame_index >= sheet->frame_count ||
        surface->pixels == NULL) return;
    frame = &sheet->frames[frame_index];
    if (frame->pixels == NULL) return;
    for (row = 0; row < frame->height; ++row) {
        const uint32_t *mask = frame->pixels + (size_t)row * (size_t)frame->width;
        int destination_y = y + frame->y_offset + row;
        int column;
        if (destination_y < 0 || destination_y >= surface->height) continue;
        for (column = 0; column < frame->width; ++column) {
            int destination_x = x + frame->x_offset + column;
            uint32_t *pixel;
            if ((mask[column] >> 24) == 0U || destination_x < 0 ||
                destination_x >= surface->width) continue;
            if (clip != NULL &&
                (destination_x < clip->left || destination_x > clip->right ||
                 destination_y < clip->top || destination_y > clip->bottom))
                continue;
            pixel = &surface->pixels[(ptrdiff_t)destination_y * surface->stride +
                                     destination_x];
            *pixel = hazed_island_pixel(*pixel, selector, level);
        }
    }
}

static void recolor_under_sprite(RenderSurface *surface, const SpriteSheet *sheet,
                                 uint32_t frame_index, int x, int y,
                                 int selector, int level)
{
    recolor_under_sprite_clipped(surface, sheet, frame_index, x, y, selector,
                                 level, NULL);
}

static void draw_sprite_region(RenderSurface *surface, const SpriteSheet *sheet,
                               uint32_t frame_index,
                               int source_x, int source_y, int width, int height,
                               int destination_x, int destination_y)
{
    const SpriteFrame *frame;
    if (sheet == NULL || frame_index >= sheet->frame_count || width <= 0 || height <= 0) return;
    frame = &sheet->frames[frame_index];
    if (frame->pixels == NULL || source_x < 0 || source_y < 0 ||
        source_x + width > frame->width || source_y + height > frame->height) return;
    render_surface_blit(surface, frame->pixels, frame->width, frame->height,
                        frame->width, source_x, source_y, width, height,
                        destination_x, destination_y, 0x10000U, NULL, NULL);
}
