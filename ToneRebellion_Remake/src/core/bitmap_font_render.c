#include "bitmap_font_render.h"

size_t bitmap_font_render_pixels(const BitmapFont *font, const char *text,
                                 uint32_t *target, size_t target_width,
                                 size_t target_height, size_t target_stride,
                                 int x, int y, uint32_t pixel)
{
    const unsigned char *cursor = (const unsigned char *)text;
    size_t written = 0;

    if (font == NULL || text == NULL || target == NULL || font->bytes == NULL ||
        target_width == 0 || target_height == 0 || target_stride < target_width)
        return 0;

    while (*cursor != '\0') {
        uint32_t code = *cursor < font->glyph_count ? *cursor : (uint32_t)'?';
        uint32_t glyph_width;
        const uint8_t *glyph_pixels;
        if (bitmap_font_get_glyph(font, code, &glyph_width, &glyph_pixels)) {
            uint32_t row;
            uint32_t col;
            for (row = 0; row < font->height; ++row) {
                int64_t py = (int64_t)y + row;
                if (py < 0 || (uint64_t)py >= target_height) continue;
                for (col = 0; col < glyph_width; ++col) {
                    int64_t px = (int64_t)x + col;
                    /* Ink is any value other than background 0 and transparent 0xff:
                     BGOUTFNT uses 1, SMFONT and BIGFONT use 243. */
                    uint8_t glyph_pixel = glyph_pixels[(size_t)row * glyph_width + col];
                    if (glyph_pixel != 0u && glyph_pixel != 0xffu &&
                        px >= 0 && (uint64_t)px < target_width) {
                        target[(size_t)py * target_stride + (size_t)px] = pixel;
                        ++written;
                    }
                }
            }
            x += (int)glyph_width;
        }
        ++cursor;
    }
    return written;
}
