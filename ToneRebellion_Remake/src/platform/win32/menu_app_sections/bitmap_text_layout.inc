static void fill_rect(HDC dc, int left, int top, int right, int bottom, COLORREF color)
{
    RECT rect = {left, top, right, bottom};
    HBRUSH brush = CreateSolidBrush(color);
    FillRect(dc, &rect, brush);
    DeleteObject(brush);
}

static void draw_bitmap_text_at(DWORD *pixels, int surface_width, int surface_height,
                                const char *text, int x, int y, DWORD ink)
{
    const unsigned char *cursor = (const unsigned char *)text;
    while (*cursor != 0) {
        uint32_t glyph_width;
        const uint8_t *glyph_pixels;
        uint32_t code = *cursor < g_bitmap_font.glyph_count ? *cursor : (uint32_t)'?';
        uint32_t row;
        if (bitmap_font_get_glyph(&g_bitmap_font, code, &glyph_width, &glyph_pixels)) {
            uint32_t col;
            for (row = 0; row < g_bitmap_font.height; ++row) {
                for (col = 0; col < glyph_width; ++col) {
                    /* BGOUTFNT masks distinguish ink (1), background (0),
                       and transparent padding (0xff). Treating zero as ink
                       filled each glyph's entire bounding box. */
                    if (glyph_pixels[(size_t)row * glyph_width + col] == 1u) {
                        int px = x + (int)col;
                        int py = y + (int)row;
                        if (px >= 0 && px < surface_width && py >= 0 && py < surface_height) {
                            pixels[(size_t)py * (size_t)surface_width + (size_t)px] = ink;
                        }
                    }
                }
            }
            x += (int)glyph_width;
        }
        ++cursor;
    }
}

static int32_t measure_bitmap_text(void *context, const char *text, size_t length)
{
    size_t i;
    int32_t width = 0;
    (void)context;
    for (i = 0; i < length; ++i) {
        uint32_t glyph_width;
        const uint8_t *glyph_pixels;
        uint32_t code = (unsigned char)text[i];
        if (code >= g_bitmap_font.glyph_count) code = (uint32_t)'?';
        if (bitmap_font_get_glyph(&g_bitmap_font, code, &glyph_width, &glyph_pixels))
            width += (int32_t)((glyph_width * CURVED_TEXT_NEWGAME_WIDTH_NUMERATOR +
                                CURVED_TEXT_NEWGAME_WIDTH_DENOMINATOR / 2u) /
                               CURVED_TEXT_NEWGAME_WIDTH_DENOMINATOR);
    }
    return width;
}

/* The New Game paragraphs are drawn with glyphs narrowed to 11/13 of their
   source width (draw_curved_bitmap_text_at). FUN_00428baa wraps and justifies
   with the same width function it draws with, so the wrap test, the line's
   natural width and each word's advance must use these narrowed widths too;
   mixing source widths here left words drawn narrow but spaced as if wide. */
static int32_t measure_curved_bitmap_text(void *context, const char *text,
                                          size_t length)
{
    size_t i;
    int32_t width = 0;
    (void)context;
    for (i = 0; i < length; ++i) {
        uint32_t glyph_width;
        const uint8_t *glyph_pixels;
        uint32_t code = (unsigned char)text[i];
        if (code >= g_bitmap_font.glyph_count) code = (uint32_t)'?';
        if (bitmap_font_get_glyph(&g_bitmap_font, code, &glyph_width, &glyph_pixels)) {
            uint32_t narrowed = (glyph_width * CURVED_TEXT_NEWGAME_WIDTH_NUMERATOR +
                                 CURVED_TEXT_NEWGAME_WIDTH_DENOMINATOR / 2u) /
                                CURVED_TEXT_NEWGAME_WIDTH_DENOMINATOR;
            width += (int32_t)(narrowed == 0u ? 1u : narrowed);
        }
    }
    return width;
}

static void draw_curved_bitmap_text_at(DWORD *pixels, int surface_width,
                                       int surface_height, const char *text,
                                       int x, int y, DWORD ink)
{
    const unsigned char *cursor = (const unsigned char *)text;
    while (*cursor != 0) {
        uint32_t source_width;
        const uint8_t *glyph_pixels;
        uint32_t code = *cursor < g_bitmap_font.glyph_count
            ? *cursor : (uint32_t)'?';
        if (bitmap_font_get_glyph(&g_bitmap_font, code, &source_width,
                                  &glyph_pixels)) {
            uint32_t width = (source_width * CURVED_TEXT_NEWGAME_WIDTH_NUMERATOR +
                              CURVED_TEXT_NEWGAME_WIDTH_DENOMINATOR / 2u) /
                             CURVED_TEXT_NEWGAME_WIDTH_DENOMINATOR;
            if (width == 0) width = 1;
            uint32_t row;
            for (row = 0; row < CURVED_TEXT_NEWGAME_RENDER_HEIGHT; ++row) {
                uint32_t col;
                for (col = 0; col < width; ++col) {
                    uint32_t source_col = col * source_width / width;
                    int px = x + (int)col;
                    int py = y + (int)row;
                    if (glyph_pixels[(size_t)row * source_width + source_col] == 1u &&
                        px >= 0 && px < surface_width &&
                        py >= 0 && py < surface_height) {
                        pixels[(size_t)py * (size_t)surface_width + (size_t)px] = ink;
                    }
                }
            }
            x += (int)width;
        }
        ++cursor;
    }
}

static void draw_justified_bitmap_line(DWORD *pixels, int surface_width,
                                       int surface_height, const char *text,
                                       const CurvedTextLine *line, DWORD ink)
{
    char word[1024];
    size_t cursor = line->offset;
    size_t end = line->offset + line->length;
    size_t space_count = 0;
    size_t i;
    size_t remainder;
    int32_t text_width;
    int32_t extra;
    int32_t per_space;
    int32_t single_space_width = measure_curved_bitmap_text(NULL, " ", 1);
    int x = line->x;
    for (i = cursor; i < end; ++i) if (text[i] == ' ') ++space_count;
    text_width = measure_curved_bitmap_text(NULL, text + cursor, end - cursor);
    extra = line->width - text_width;
    if (extra < 0) extra = 0;
    if (space_count == 0) {
        size_t length = end - cursor;
        if (length >= sizeof(word)) length = sizeof(word) - 1;
        memcpy(word, text + cursor, length);
        word[length] = '\0';
        draw_curved_bitmap_text_at(pixels, surface_width, surface_height,
                                   word, x, line->y, ink);
        return;
    }
    per_space = extra / (int32_t)space_count;
    remainder = (size_t)(extra - per_space * (int32_t)space_count);
    while (cursor < end) {
        size_t word_end = cursor;
        size_t word_length;
        int32_t word_width;
        while (word_end < end && text[word_end] != ' ') ++word_end;
        word_length = word_end - cursor;
        if (word_length >= sizeof(word)) word_length = sizeof(word) - 1;
        memcpy(word, text + cursor, word_length);
        word[word_length] = '\0';
        draw_curved_bitmap_text_at(pixels, surface_width, surface_height,
                                   word, x, line->y, ink);
        word_width = measure_curved_bitmap_text(NULL, word, word_length);
        x += word_width;
        if (word_end < end) {
            x += single_space_width + per_space;
            if (remainder != 0) {
                ++x;
                --remainder;
            }
        }
        cursor = word_end + 1;
    }
}

