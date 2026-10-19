static int resume_header_is_valid(void)
{
    unsigned char header[0x80];
    FILE *file = fopen("C:\\Program Files\\Tone\\resume.gam", "rb");
    size_t count;
    uint32_t marker;
    if (file == NULL) return 0;
    count = fread(header, 1, sizeof(header), file);
    (void)fclose(file);
    if (count != sizeof(header)) return 0;
    marker = (uint32_t)header[0x7c] | ((uint32_t)header[0x7d] << 8) |
             ((uint32_t)header[0x7e] << 16) | ((uint32_t)header[0x7f] << 24);
    return marker == 0x000378b8u;
}

/* FUN_00458371 scans slots 00.sav through 07.sav. It accepts a slot only
   when the 0x80-byte header has the game's marker and 1.16 version prefix. */
static int save_header_is_valid(const char *path)
{
    unsigned char header[0x80];
    FILE *file = fopen(path, "rb");
    size_t count;
    uint32_t marker;
    if (file == NULL) return 0;
    count = fread(header, 1, sizeof(header), file);
    (void)fclose(file);
    if (count != sizeof(header) || memcmp(header, "1.16", 4) != 0) return 0;
    marker = (uint32_t)header[0x7c] | ((uint32_t)header[0x7d] << 8) |
             ((uint32_t)header[0x7e] << 16) | ((uint32_t)header[0x7f] << 24);
    return marker == 0x000378b8u;
}

static void scan_load_slots(void)
{
    int slot;
    for (slot = 0; slot < 8; ++slot) {
        char path[MAX_PATH];
        (void)snprintf(path, sizeof(path), "C:\\Program Files\\Tone\\%02d.SAV", slot);
        g_load_slot_valid[slot] = (unsigned char)save_header_is_valid(path);
    }
}

static int create_help_sheet(SpriteSheet *sheet, char *error, size_t error_capacity)
{
    int entry;
    sheet->frames = (SpriteFrame *)calloc(HELP_ENTRY_COUNT, sizeof(*sheet->frames));
    if (sheet->frames == NULL) {
        (void)snprintf(error, error_capacity, "could not allocate contextual help frames");
        return 0;
    }
    sheet->frame_count = HELP_ENTRY_COUNT;
    for (entry = 0; entry < HELP_ENTRY_COUNT; ++entry) {
        char lines[16][256];
        const char *text = g_help_text[entry];
        size_t text_length = strlen(text);
        size_t cursor = 0;
        int line_count = 0;
        int height;
        BITMAPINFO info;
        void *bitmap_bits = NULL;
        HBITMAP bitmap;
        int line;
        while (cursor < text_length && line_count < 16) {
            size_t start;
            size_t last_space = SIZE_MAX;
            size_t i;
            int width = 0;
            while (cursor < text_length && text[cursor] == ' ') ++cursor;
            start = cursor;
            for (i = start; i < text_length; ++i) {
                uint32_t glyph_width;
                const uint8_t *glyph_pixels;
                uint32_t code = (unsigned char)text[i];
                if (!bitmap_font_get_glyph(&g_bitmap_font, code, &glyph_width,
                                           &glyph_pixels)) {
                    code = '?';
                    (void)bitmap_font_get_glyph(&g_bitmap_font, code, &glyph_width,
                                                &glyph_pixels);
                }
                if (width + (int)glyph_width > 304 && i > start) break;
                width += (int)glyph_width;
                if (text[i] == ' ') last_space = i;
            }
            if (i < text_length && last_space != SIZE_MAX && last_space >= start) i = last_space;
            if (i == start && i < text_length) ++i;
            {
                size_t count = i - start;
                if (count >= sizeof(lines[line_count])) count = sizeof(lines[line_count]) - 1;
                memcpy(lines[line_count], text + start, count);
                lines[line_count][count] = '\0';
                ++line_count;
            }
            cursor = i;
            while (cursor < text_length && text[cursor] == ' ') ++cursor;
        }
        if (line_count == 0) continue;
        height = 12 + line_count * ((int)g_bitmap_font.height + 2);
        ZeroMemory(&info, sizeof(info));
        info.bmiHeader.biSize = sizeof(info.bmiHeader);
        info.bmiHeader.biWidth = 320;
        info.bmiHeader.biHeight = -height;
        info.bmiHeader.biPlanes = 1;
        info.bmiHeader.biBitCount = 32;
        info.bmiHeader.biCompression = BI_RGB;
        bitmap = CreateDIBSection(NULL, &info, DIB_RGB_COLORS, &bitmap_bits, NULL, 0);
        if (bitmap == NULL || bitmap_bits == NULL) {
            if (bitmap != NULL) DeleteObject(bitmap);
            (void)snprintf(error, error_capacity, "could not create contextual help bitmap");
            return 0;
        }
        memset(bitmap_bits, 0, (size_t)320 * (size_t)height * 4);
        {
            DWORD *surface = (DWORD *)bitmap_bits;
            int x;
            int y;
            const DWORD background = 0xe80b1320u;
            const DWORD border = 0xffe8d79au;
            for (y = 0; y < height; ++y) {
                for (x = 0; x < 320; ++x) {
                    if (x < 2 || x >= 318 || y < 2 || y >= height - 2)
                        surface[(size_t)y * 320 + x] = border;
                    else
                        surface[(size_t)y * 320 + x] = background;
                }
            }
            for (line = 0; line < line_count; ++line) {
                draw_bitmap_text_at(surface, 320, height, lines[line], 8,
                                    6 + line * ((int)g_bitmap_font.height + 2),
                                    0xffe5e7eau);
            }
        }
        sheet->frames[entry].bitmap = bitmap;
        sheet->frames[entry].width = 320;
        sheet->frames[entry].height = height;
    }
    return 1;
}

/* FUN_00474b90 is the game's 15-bit MSVC-style LCG. The original seeds it
   from QueryPerformanceCounter before entering the message loop. */
