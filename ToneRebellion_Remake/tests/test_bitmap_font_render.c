#include "bitmap_font_render.h"

#include <assert.h>
#include <stdint.h>
#include <string.h>

int main(void)
{
    /* 256-entry font table with a two-pixel glyph and an all-on '?' glyph. */
    static uint8_t font_bytes[16 + 256 * 4 + 16];
    BitmapFont font;
    uint32_t pixels[4 * 3];
    const uint32_t ink = UINT32_C(0x00123456);

    const uint32_t table_end = 16 + 256 * 4;
    for (size_t i = 0; i < sizeof(pixels) / sizeof(pixels[0]); ++i)
        pixels[i] = UINT32_C(0x00abcdef);

    font_bytes[0] = '1';
    font_bytes[1] = '.';
    font_bytes[4] = 0;
    font_bytes[5] = 1;
    font_bytes[8] = 2;
    font_bytes[12] = 2;
    for (unsigned int glyph = 0; glyph < 256; ++glyph) {
        uint32_t offset = table_end + 8;
        if (glyph == 1) offset = table_end;
        for (unsigned int byte = 0; byte < 4; ++byte)
            font_bytes[16 + glyph * 4 + byte] = (uint8_t)(offset >> (byte * 8));
    }
    font_bytes[table_end] = 2;
    font_bytes[table_end + 4] = 1;
    font_bytes[table_end + 7] = 1;
    font_bytes[table_end + 8] = 2;
    font_bytes[table_end + 12] = 1;
    font_bytes[table_end + 13] = 1;
    font_bytes[table_end + 14] = 1;
    font_bytes[table_end + 15] = 1;
    font.bytes = font_bytes;
    font.length = sizeof(font_bytes);
    font.glyph_count = 256;
    font.height = 2;
    font.max_glyph_width = 2;

    assert(bitmap_font_render_pixels(&font, "\x01", pixels, 4, 3, 4,
                                     1, 1, ink) == 2);
    assert(pixels[1 * 4 + 1] == ink);
    assert(pixels[1 * 4 + 2] == UINT32_C(0x00abcdef));
    assert(pixels[2 * 4 + 1] == UINT32_C(0x00abcdef));
    assert(pixels[2 * 4 + 2] == ink);

    /* A missing glyph uses '?' and clips the part beyond the right edge. */
    assert(bitmap_font_render_pixels(&font, "x", pixels, 4, 3, 4,
                                     3, 0, ink) == 2);
    assert(pixels[0 * 4 + 3] == ink && pixels[1 * 4 + 3] == ink);

    /* Negative positions clip cleanly and preserve mask-zero pixels. */
    assert(bitmap_font_render_pixels(&font, "\x01", pixels, 4, 3, 4,
                                     -1, 0, ink) == 1);
    assert(pixels[0] == UINT32_C(0x00abcdef));
    assert(pixels[4] == ink);

    assert(bitmap_font_render_pixels(&font, "x", pixels, 4, 3, 3,
                                     0, 0, ink) == 0);
    assert(bitmap_font_render_pixels(&font, "x", NULL, 4, 3, 4,
                                     0, 0, ink) == 0);
    return 0;
}
