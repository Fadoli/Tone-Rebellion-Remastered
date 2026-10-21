/* Start-up logo: FUN_0041c46f shows data\logo.gif with data\logo.pal when
   float.cfg contains the keyword `logo` (DAT_004c2b98), fading the palette in
   (65 steps of 4) and out before the title; no delay, no input poll. */

enum {
    LOGO_WIDTH = 640,
    LOGO_HEIGHT = 480,
    /* Port pacing (the original has no delay): ticks are 50 ms timer ticks. */
    LOGO_FADE_IN_TICKS = 16,
    LOGO_HOLD_TICKS = 20,
    LOGO_FADE_OUT_TICKS = 16
};

static unsigned char *g_logo_pixels;
static unsigned char g_logo_palette[768];
static unsigned g_logo_tick;

/* True when the first token of a float.cfg line equals `keyword`. */
static int float_cfg_has_keyword(const char *keyword)
{
    FILE *file = fopen("C:\\Program Files\\Tone\\FLOAT.CFG", "rb");
    char line[256];
    int found = 0;
    size_t keyword_length = strlen(keyword);
    if (file == NULL) return 0;
    while (!found && fgets(line, sizeof(line), file) != NULL) {
        const char *cursor = line;
        while (*cursor == ' ' || *cursor == '\t') ++cursor;
        if (_strnicmp(cursor, keyword, keyword_length) == 0 &&
            (cursor[keyword_length] == '\0' || cursor[keyword_length] == ' ' ||
             cursor[keyword_length] == '\t' || cursor[keyword_length] == '\r' ||
             cursor[keyword_length] == '\n')) found = 1;
    }
    fclose(file);
    return found;
}

/* float.cfg `easyunlock` (DAT_004c2ba0), read once. */
static int float_cfg_easyunlock(void)
{
    static int cached = -1;
    if (cached < 0) cached = float_cfg_has_keyword("easyunlock") ? 1 : 0;
    return cached;
}

/* Minimal GIF87a/89a decoder for one non-animated 8-bit image of exactly
   640 x 480; writes the palette indices to `out`. */
static int decode_logo_gif(const unsigned char *data, size_t length,
                           unsigned char *out)
{
    size_t position = 13;
    unsigned flags;
    unsigned image_width;
    unsigned image_height;
    unsigned min_code_size;
    unsigned clear_code;
    unsigned end_code;
    unsigned next_code;
    unsigned code_size;
    unsigned prefix[4096];
    unsigned char suffix[4096];
    unsigned char stack[4096];
    unsigned previous = 0xffffU;
    unsigned bit_buffer = 0;
    unsigned bit_count = 0;
    size_t block_remaining = 0;
    size_t written = 0;
    size_t total = (size_t)LOGO_WIDTH * LOGO_HEIGHT;
    unsigned char first = 0;

    if (length < 14 || memcmp(data, "GIF8", 4) != 0) return 0;
    flags = data[10];
    if ((flags & 0x80U) != 0) position += (size_t)3U << ((flags & 7U) + 1U);
    while (position < length && data[position] != 0x2c) {
        if (data[position] != 0x21 || position + 2 >= length) return 0;
        position += 2;
        while (position < length && data[position] != 0) {
            position += (size_t)data[position] + 1;
        }
        ++position;
    }
    if (position + 11 > length) return 0;
    image_width = (unsigned)data[position + 5] | ((unsigned)data[position + 6] << 8);
    image_height = (unsigned)data[position + 7] | ((unsigned)data[position + 8] << 8);
    flags = data[position + 9];
    if (image_width != LOGO_WIDTH || image_height != LOGO_HEIGHT ||
        (flags & 0x40U) != 0) return 0;
    position += 10;
    if ((flags & 0x80U) != 0) position += (size_t)3U << ((flags & 7U) + 1U);
    if (position >= length) return 0;
    min_code_size = data[position++];
    if (min_code_size < 2 || min_code_size > 8) return 0;
    clear_code = 1U << min_code_size;
    end_code = clear_code + 1U;
    next_code = end_code + 1U;
    code_size = min_code_size + 1U;
    {
        unsigned index;
        for (index = 0; index < clear_code; ++index) {
            prefix[index] = 0xffffU;
            suffix[index] = (unsigned char)index;
        }
    }
    while (written < total) {
        unsigned code;
        while (bit_count < code_size) {
            if (block_remaining == 0) {
                if (position >= length) return written == total;
                block_remaining = data[position++];
                if (block_remaining == 0) return written == total;
            }
            if (position >= length) return written == total;
            bit_buffer |= (unsigned)data[position++] << bit_count;
            bit_count += 8;
            --block_remaining;
        }
        code = bit_buffer & ((1U << code_size) - 1U);
        bit_buffer >>= code_size;
        bit_count -= code_size;
        if (code == clear_code) {
            next_code = end_code + 1U;
            code_size = min_code_size + 1U;
            previous = 0xffffU;
            continue;
        }
        if (code == end_code) break;
        {
            unsigned current = code;
            size_t depth = 0;
            if (previous != 0xffffU && code == next_code) {
                /* KwKwK case: the string is previous + its own first byte. */
                stack[depth++] = first;
                current = previous;
            } else if (code >= next_code) {
                return 0;
            }
            while (current >= clear_code && depth < sizeof(stack)) {
                stack[depth++] = suffix[current];
                current = prefix[current];
            }
            if (depth >= sizeof(stack)) return 0;
            first = (unsigned char)current;
            stack[depth++] = first;
            while (depth != 0 && written < total) out[written++] = stack[--depth];
            if (previous != 0xffffU && next_code < 4096U) {
                prefix[next_code] = previous;
                suffix[next_code] = first;
                ++next_code;
                if (next_code == (1U << code_size) && code_size < 12U) ++code_size;
            }
            previous = code;
        }
    }
    return written == total;
}

/* Loads logo.gif and logo.pal from TONE01.COB when float.cfg asks for the
   logo; failure just skips the splash. */
static int load_logo_splash(CobArchive *archive)
{
    const CobMember *gif;
    const CobMember *palette;
    unsigned char *gif_bytes;
    char error[128];
    if (!float_cfg_has_keyword("logo")) return 0;
    gif = cob_archive_find(archive, "data\\logo.gif");
    palette = cob_archive_find(archive, "data\\logo.pal");
    if (gif == NULL || palette == NULL || palette->length < 768) return 0;
    gif_bytes = (unsigned char *)malloc(gif->length);
    g_logo_pixels = (unsigned char *)malloc((size_t)LOGO_WIDTH * LOGO_HEIGHT);
    if (gif_bytes == NULL || g_logo_pixels == NULL ||
        !cob_archive_read_member(archive, gif, gif_bytes, gif->length,
                                 error, sizeof(error)) ||
        !cob_archive_read_member(archive, palette, g_logo_palette, 768,
                                 error, sizeof(error)) ||
        !decode_logo_gif(gif_bytes, gif->length, g_logo_pixels)) {
        free(gif_bytes);
        free(g_logo_pixels);
        g_logo_pixels = NULL;
        return 0;
    }
    free(gif_bytes);
    g_logo_tick = 0;
    return 1;
}

static int logo_splash_finished(void)
{
    return g_logo_tick >= LOGO_FADE_IN_TICKS + LOGO_HOLD_TICKS +
                          LOGO_FADE_OUT_TICKS;
}

/* FUN_00410765: out = palette * scale >> 8 on the 6-bit values, with scale
   rising 0..256 for the fade-in and falling for the fade-out. */
static void render_logo(HDC dc)
{
    unsigned scale;
    DWORD lut[256];
    unsigned index;
    size_t pixel;
    fill_rect(dc, 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT, RGB(0, 0, 0));
    if (g_logo_pixels == NULL || g_paint_buffer_pixels == NULL) return;
    if (g_logo_tick < LOGO_FADE_IN_TICKS)
        scale = g_logo_tick * 256U / LOGO_FADE_IN_TICKS;
    else if (g_logo_tick < LOGO_FADE_IN_TICKS + LOGO_HOLD_TICKS)
        scale = 256U;
    else {
        unsigned out_tick = g_logo_tick - LOGO_FADE_IN_TICKS - LOGO_HOLD_TICKS;
        scale = out_tick >= LOGO_FADE_OUT_TICKS
            ? 0U : 256U - out_tick * 256U / LOGO_FADE_OUT_TICKS;
    }
    for (index = 0; index < 256U; ++index) {
        unsigned red = (g_logo_palette[index * 3U] * scale >> 8) * 255U / 63U;
        unsigned green = (g_logo_palette[index * 3U + 1U] * scale >> 8) * 255U / 63U;
        unsigned blue = (g_logo_palette[index * 3U + 2U] * scale >> 8) * 255U / 63U;
        lut[index] = (DWORD)(red << 16 | green << 8 | blue);
    }
    (void)GdiFlush();
    for (pixel = 0; pixel < (size_t)LOGO_WIDTH * LOGO_HEIGHT; ++pixel)
        ((DWORD *)g_paint_buffer_pixels)[pixel] = lut[g_logo_pixels[pixel]];
}
