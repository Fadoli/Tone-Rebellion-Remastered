static HDC get_sprite_source_dc(HDC reference_dc)
{
    if (g_sprite_source_dc == NULL && reference_dc != NULL)
        g_sprite_source_dc = CreateCompatibleDC(reference_dc);
    return g_sprite_source_dc;
}

static void destroy_sprite_source_dc(void)
{
    if (g_sprite_source_dc != NULL) DeleteDC(g_sprite_source_dc);
    g_sprite_source_dc = NULL;
}

static int ensure_paint_buffer(HDC reference_dc)
{
    BITMAPINFO info;
    void *bits = NULL;
    HDC dc;
    HBITMAP bitmap;
    HGDIOBJ original_bitmap;
    if (g_paint_buffer_dc != NULL && g_paint_buffer_bitmap != NULL &&
        g_paint_buffer_pixels != NULL) return 1;

    ZeroMemory(&info, sizeof(info));
    info.bmiHeader.biSize = sizeof(info.bmiHeader);
    info.bmiHeader.biWidth = LOGICAL_WIDTH;
    info.bmiHeader.biHeight = -LOGICAL_HEIGHT;
    info.bmiHeader.biPlanes = 1;
    info.bmiHeader.biBitCount = 32;
    info.bmiHeader.biCompression = BI_RGB;
    dc = CreateCompatibleDC(reference_dc);
    if (dc == NULL) return 0;
    bitmap = CreateDIBSection(reference_dc, &info, DIB_RGB_COLORS,
                              &bits, NULL, 0);
    if (bitmap == NULL || bits == NULL) {
        if (bitmap != NULL) DeleteObject(bitmap);
        DeleteDC(dc);
        return 0;
    }
    original_bitmap = SelectObject(dc, bitmap);
    if (original_bitmap == NULL || original_bitmap == HGDI_ERROR) {
        DeleteObject(bitmap);
        DeleteDC(dc);
        return 0;
    }
    g_paint_buffer_dc = dc;
    g_paint_buffer_bitmap = bitmap;
    g_paint_buffer_original_bitmap = original_bitmap;
    g_paint_buffer_pixels = (DWORD *)bits;
    return 1;
}

static void destroy_paint_buffer(void)
{
    if (g_paint_buffer_dc != NULL && g_paint_buffer_original_bitmap != NULL)
        (void)SelectObject(g_paint_buffer_dc, g_paint_buffer_original_bitmap);
    if (g_paint_buffer_bitmap != NULL) DeleteObject(g_paint_buffer_bitmap);
    if (g_paint_buffer_dc != NULL) DeleteDC(g_paint_buffer_dc);
    g_paint_buffer_pixels = NULL;
    g_paint_buffer_original_bitmap = NULL;
    g_paint_buffer_bitmap = NULL;
    g_paint_buffer_dc = NULL;
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
}

static void update_interaction_cursor(void)
{
    int slot = 0;
    if (g_menu.screen == SCREEN_ISLAND &&
        game_glyph_inventory_cursor_slot(g_selected_glyph,
                                         g_selected_inventory_item) == 0x0b) {
        slot = 0x0b;
    }
    if (g_interaction_cursors[slot] != NULL) {
        SetCursor(g_interaction_cursors[slot]);
        return;
    }
    SetCursor(LoadCursorA(NULL, IDC_ARROW));
}
static int g_mouse_x;
static int g_mouse_y;

static void update_window_title(HWND window);
static void set_background_tune(const char *tune_id);
static void set_background_tune_once(const char *tune_id);
static void stop_background_tune(void);
static void draw_location_action_panel(HDC dc);
static int load_game_session_for_selected_world(char *error, size_t error_capacity);
static int draw_building_preview(HDC dc, uint16_t item_id, uint8_t player_slot,
                                 int x, int y, uint32_t scale_16_16);
static int draw_runtime_item_scaled(HDC dc,
                                    const GameRuntimeLocation *runtime_location,
                                    int x, int y, uint32_t scale_16_16);

static int begin_new_game(HWND window)
{
    char error[256];
    g_sim_speed = 1U;   /* FUN_004121b7 case 9 resets DAT_004bf110 */
    if (!load_game_session_for_selected_world(error, sizeof(error))) {
        MessageBoxA(window, error, "Tone Rebellion remake - game setup error",
                    MB_OK | MB_ICONERROR);
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
    else if (g_menu.screen == SCREEN_WORLD_MAP) title = "Tone Rebellion - World Map (Esc: setup, Left/Right: size)";
    else if (g_menu.screen == SCREEN_ISLAND)
        title = "Tone Rebellion - Island (arrows: scroll, Esc: map)";
    else if (g_menu.screen == SCREEN_LOAD_GAME) title = g_load_save_mode ? "Tone Rebellion - Save Game (Esc: back)" : "Tone Rebellion - Load Game (Esc: back)";
    SetWindowTextA(window, title);
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
        (void)mciSendStringA("stop tone_music", NULL, 0, NULL);
        (void)mciSendStringA("close tone_music", NULL, 0, NULL);
        g_music_device_open = 0;
    }
    g_current_tune[0] = '\0';
    g_music_loops = 0;
}

static void keep_background_tune_playing(void)
{
    char mode[32];
    MCIERROR result;

    if (!g_music_device_open || g_current_tune[0] == '\0') return;
    result = mciSendStringA("status tone_music mode", mode, sizeof(mode), NULL);
    if (result == 0 && strcmp(mode, "stopped") == 0) {
        if (g_music_loops) {
            (void)mciSendStringA("play tone_music from 0", NULL, 0, NULL);
        } else {
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

static int load_sprite_sheet(CobArchive *archive, const char *member_name,
                             const COLORREF palette[256], SpriteSheet *sheet,
                             char *error, size_t error_capacity)
{
    const CobMember *member = cob_archive_find(archive, member_name);
    unsigned char *bytes;
    ShpFile source;
    uint32_t frame_index;
    if (member == NULL) {
        (void)snprintf(error, error_capacity, "%s was not found in TONE01.COB", member_name);
        return 0;
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
        BITMAPINFO info;
        void *bitmap_bits = NULL;
        HBITMAP bitmap;
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
        ZeroMemory(&info, sizeof(info));
        info.bmiHeader.biSize = sizeof(info.bmiHeader);
        info.bmiHeader.biWidth = (LONG)decoded.width;
        info.bmiHeader.biHeight = -(LONG)decoded.height;
        info.bmiHeader.biPlanes = 1;
        info.bmiHeader.biBitCount = 32;
        info.bmiHeader.biCompression = BI_RGB;
        bitmap = CreateDIBSection(NULL, &info, DIB_RGB_COLORS, &bitmap_bits, NULL, 0);
        if (bitmap == NULL || bitmap_bits == NULL) {
            if (bitmap != NULL) DeleteObject(bitmap);
            shp_frame_free(&decoded);
            free(bytes);
            (void)snprintf(error, error_capacity, "could not create a GDI sprite bitmap");
            return 0;
        }
        for (p = 0; p < (size_t)decoded.width * decoded.height; ++p) {
            DWORD *pixel = (DWORD *)bitmap_bits + p;
            COLORREF color = palette[decoded.pixels[p]];
            if (decoded.opaque[p]) {
                int pixel_x = (int)(p % decoded.width);
                int pixel_y = (int)(p / decoded.width);
                *pixel = 0xff000000u | ((DWORD)GetRValue(color) << 16) |
                         ((DWORD)GetGValue(color) << 8) | (DWORD)GetBValue(color);
                if (pixel_x < hit_left) hit_left = pixel_x;
                if (pixel_y < hit_top) hit_top = pixel_y;
                if (pixel_x + 1 > hit_right) hit_right = pixel_x + 1;
                if (pixel_y + 1 > hit_bottom) hit_bottom = pixel_y + 1;
            } else {
                *pixel = 0;
            }
        }
        sheet->frames[frame_index].bitmap = bitmap;
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
    return 1;
}

static void free_sprite_sheet(SpriteSheet *sheet)
{
    uint32_t i;
    if (sheet->frames != NULL) {
        for (i = 0; i < sheet->frame_count; ++i) {
            if (sheet->frames[i].bitmap != NULL) DeleteObject(sheet->frames[i].bitmap);
        }
        free(sheet->frames);
    }
    memset(sheet, 0, sizeof(*sheet));
}

/* FUN_00423068 stores facing-left in object flag 0x002, and FUN_0042704b
   passes a negative horizontal scale for that state. Cache equivalent flipped
   bitmaps so the Win32 renderer can preserve AlphaBlend transparency. */
static int mirror_sprite_sheet_horizontally(const SpriteSheet *source,
                                            SpriteSheet *out,
                                            char *error, size_t error_capacity)
{
    uint32_t frame_index;
    if (source == NULL || out == NULL || source->frames == NULL ||
        source->frame_count == 0) return 0;
    memset(out, 0, sizeof(*out));
    out->frames = (SpriteFrame *)calloc(source->frame_count, sizeof(*out->frames));
    if (out->frames == NULL) {
        (void)snprintf(error, error_capacity, "could not allocate mirrored floater frames");
        return 0;
    }
    out->frame_count = source->frame_count;
    for (frame_index = 0; frame_index < source->frame_count; ++frame_index) {
        const SpriteFrame *input = &source->frames[frame_index];
        SpriteFrame *output = &out->frames[frame_index];
        DIBSECTION dib;
        BITMAPINFO info;
        void *bitmap_bits = NULL;
        HBITMAP bitmap;
        int got;
        int y;

        if (input->bitmap == NULL || input->width <= 0 || input->height <= 0) {
            (void)snprintf(error, error_capacity,
                           "floater sprite has an invalid frame for horizontal mirroring");
            free_sprite_sheet(out);
            return 0;
        }
        ZeroMemory(&dib, sizeof(dib));
        got = GetObjectA(input->bitmap, sizeof(dib), &dib);
        if (got < (int)sizeof(BITMAP) || dib.dsBm.bmBits == NULL ||
            dib.dsBm.bmBitsPixel != 32 || dib.dsBm.bmWidthBytes < input->width * 4) {
            (void)snprintf(error, error_capacity,
                           "floater sprite frame is not a readable 32-bit DIB section");
            free_sprite_sheet(out);
            return 0;
        }
        ZeroMemory(&info, sizeof(info));
        info.bmiHeader.biSize = sizeof(info.bmiHeader);
        info.bmiHeader.biWidth = input->width;
        info.bmiHeader.biHeight = -input->height;
        info.bmiHeader.biPlanes = 1;
        info.bmiHeader.biBitCount = 32;
        info.bmiHeader.biCompression = BI_RGB;
        bitmap = CreateDIBSection(NULL, &info, DIB_RGB_COLORS,
                                  &bitmap_bits, NULL, 0);
        if (bitmap == NULL || bitmap_bits == NULL) {
            if (bitmap != NULL) DeleteObject(bitmap);
            (void)snprintf(error, error_capacity,
                           "could not create horizontally mirrored floater frame");
            free_sprite_sheet(out);
            return 0;
        }
        for (y = 0; y < input->height; ++y) {
            const DWORD *source_row = (const DWORD *)
                ((const unsigned char *)dib.dsBm.bmBits +
                 (size_t)y * (size_t)dib.dsBm.bmWidthBytes);
            DWORD *destination_row = (DWORD *)bitmap_bits +
                                     (size_t)y * (size_t)input->width;
            int x;
            for (x = 0; x < input->width; ++x) {
                destination_row[x] = source_row[input->width - 1 - x];
            }
        }
        *output = *input;
        output->bitmap = bitmap;
        /* Reflect the frame bounds around the floater origin as well as its
           pixels. Keeping the source offset unchanged makes left-facing
           animation frames slide relative to the worker as their widths and
           offsets change. */
        output->x_offset = -input->x_offset - input->width;
        output->hit_left = input->width - input->hit_right;
        output->hit_right = input->width - input->hit_left;
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

static void draw_sprite(HDC target, const SpriteSheet *sheet, uint32_t frame_index,
                        int x, int y)
{
    HDC source;
    HGDIOBJ previous;
    BLENDFUNCTION blend = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
    const SpriteFrame *frame;
    if (sheet == NULL || frame_index >= sheet->frame_count) return;
    frame = &sheet->frames[frame_index];
    if (frame->bitmap == NULL) return;
    source = get_sprite_source_dc(target);
    if (source == NULL) return;
    previous = SelectObject(source, frame->bitmap);
    (void)AlphaBlend(target, x + frame->x_offset, y + frame->y_offset,
                     frame->width, frame->height, source, 0, 0,
                     frame->width, frame->height, blend);
    SelectObject(source, previous);
}

static void draw_sprite_scaled_plain(HDC target, const SpriteSheet *sheet,
                                     uint32_t frame_index, int x, int y,
                                     uint32_t scale_16_16)
{
    HDC source;
    HGDIOBJ previous;
    BLENDFUNCTION blend = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
    const SpriteFrame *frame;
    int width;
    int height;
    int offset_x;
    int offset_y;
    if (sheet == NULL || frame_index >= sheet->frame_count) return;
    frame = &sheet->frames[frame_index];
    if (frame->bitmap == NULL) return;
    width = (int)(((uint64_t)(unsigned)frame->width * scale_16_16) >> 16);
    height = (int)(((uint64_t)(unsigned)frame->height * scale_16_16) >> 16);
    if (width <= 0 || height <= 0) return;
    offset_x = (int)(((int64_t)frame->x_offset * scale_16_16) >> 16);
    offset_y = (int)(((int64_t)frame->y_offset * scale_16_16) >> 16);
    source = get_sprite_source_dc(target);
    if (source == NULL) return;
    previous = SelectObject(source, frame->bitmap);
    (void)AlphaBlend(target, x + offset_x, y + offset_y, width, height,
                     source, 0, 0, frame->width, frame->height, blend);
    SelectObject(source, previous);
}

/* FUN_0040bf98 copies a FUN_004106dd haze table into DAT_0049a610 for the
   flag-0x10 placement ramp and blits the following layers through it
   (FUN_00404c5a). A negative level draws sprites unchanged. */
static int g_sprite_haze_selector;
static int g_sprite_haze_level = -1;

static int read_sprite_frame_pixels(const SpriteFrame *frame, DIBSECTION *dib)
{
    ZeroMemory(dib, sizeof(*dib));
    return frame->bitmap != NULL &&
           GetObjectA(frame->bitmap, sizeof(*dib), dib) >= (int)sizeof(*dib) &&
           dib->dsBm.bmBits != NULL && dib->dsBm.bmBitsPixel == 32 &&
           dib->dsBm.bmWidthBytes >= frame->width * 4;
}

static DWORD hazed_island_pixel(DWORD pixel, int selector, int level)
{
    uint8_t index;
    COLORREF color;
    if (!island_palette_lookup_nearest(&g_island_palette_lookup,
            (uint32_t)RGB((pixel >> 16) & 0xffU, (pixel >> 8) & 0xffU,
                          pixel & 0xffU) & UINT32_C(0x00ffffff), &index))
        return pixel;
    color = g_island_palette[island_haze_remap(&g_island_haze, selector,
                                               level, index)];
    return 0xff000000U | ((DWORD)GetRValue(color) << 16) |
           ((DWORD)GetGValue(color) << 8) | (DWORD)GetBValue(color);
}

static void draw_sprite_scaled(HDC target, const SpriteSheet *sheet, uint32_t frame_index,
                               int x, int y, uint32_t scale_16_16)
{
    const SpriteFrame *frame;
    DIBSECTION dib;
    BITMAPINFO info;
    void *bits = NULL;
    HBITMAP bitmap;
    SpriteFrame hazed;
    SpriteSheet single;
    int level = g_sprite_haze_level;
    int row;
    if (level < 0 || sheet == NULL || frame_index >= sheet->frame_count) {
        draw_sprite_scaled_plain(target, sheet, frame_index, x, y, scale_16_16);
        return;
    }
    frame = &sheet->frames[frame_index];
    if (!read_sprite_frame_pixels(frame, &dib)) return;
    ZeroMemory(&info, sizeof(info));
    info.bmiHeader.biSize = sizeof(info.bmiHeader);
    info.bmiHeader.biWidth = frame->width;
    info.bmiHeader.biHeight = -frame->height;
    info.bmiHeader.biPlanes = 1;
    info.bmiHeader.biBitCount = 32;
    info.bmiHeader.biCompression = BI_RGB;
    bitmap = CreateDIBSection(NULL, &info, DIB_RGB_COLORS, &bits, NULL, 0);
    if (bitmap == NULL || bits == NULL) {
        if (bitmap != NULL) DeleteObject(bitmap);
        return;
    }
    for (row = 0; row < frame->height; ++row) {
        const DWORD *in = (const DWORD *)((const unsigned char *)dib.dsBm.bmBits +
                                          (size_t)row * (size_t)dib.dsBm.bmWidthBytes);
        DWORD *out = (DWORD *)bits + (size_t)row * (size_t)frame->width;
        int column;
        for (column = 0; column < frame->width; ++column)
            out[column] = (in[column] >> 24) == 0U ? 0U :
                hazed_island_pixel(in[column], g_sprite_haze_selector, level);
    }
    hazed = *frame;
    hazed.bitmap = bitmap;
    single.frames = &hazed;
    single.frame_count = 1;
    draw_sprite_scaled_plain(target, &single, 0, x, y, scale_16_16);
    DeleteObject(bitmap);
}

/* FUN_004109a6: every destination pixel under the frame's opaque RLE spans is
   replaced by table[destination]; the sprite's own colors are ignored. */
static void recolor_under_sprite(HDC target, const SpriteSheet *sheet,
                                 uint32_t frame_index, int x, int y,
                                 int selector, int level)
{
    const SpriteFrame *frame;
    DIBSECTION dib;
    int row;
    if (sheet == NULL || frame_index >= sheet->frame_count ||
        target != g_paint_buffer_dc || g_paint_buffer_pixels == NULL) return;
    frame = &sheet->frames[frame_index];
    if (!read_sprite_frame_pixels(frame, &dib)) return;
    (void)GdiFlush();
    for (row = 0; row < frame->height; ++row) {
        const DWORD *mask = (const DWORD *)((const unsigned char *)dib.dsBm.bmBits +
                                            (size_t)row * (size_t)dib.dsBm.bmWidthBytes);
        int destination_y = y + frame->y_offset + row;
        int column;
        if (destination_y < 0 || destination_y >= LOGICAL_HEIGHT) continue;
        for (column = 0; column < frame->width; ++column) {
            int destination_x = x + frame->x_offset + column;
            DWORD *pixel;
            if ((mask[column] >> 24) == 0U || destination_x < 0 ||
                destination_x >= LOGICAL_WIDTH) continue;
            pixel = &g_paint_buffer_pixels[(size_t)destination_y * LOGICAL_WIDTH +
                                           (size_t)destination_x];
            *pixel = hazed_island_pixel(*pixel, selector, level);
        }
    }
}

static void draw_sprite_region(HDC target, const SpriteSheet *sheet, uint32_t frame_index,
                               int source_x, int source_y, int width, int height,
                               int destination_x, int destination_y)
{
    HDC source;
    HGDIOBJ previous;
    BLENDFUNCTION blend = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
    const SpriteFrame *frame;
    if (sheet == NULL || frame_index >= sheet->frame_count || width <= 0 || height <= 0) return;
    frame = &sheet->frames[frame_index];
    if (frame->bitmap == NULL || source_x < 0 || source_y < 0 ||
        source_x + width > frame->width || source_y + height > frame->height) return;
    source = get_sprite_source_dc(target);
    if (source == NULL) return;
    previous = SelectObject(source, frame->bitmap);
    (void)AlphaBlend(target, destination_x, destination_y, width, height,
                     source, source_x, source_y, width, height, blend);
    SelectObject(source, previous);
}
