#ifndef TONE_FONT_IMAGE_H
#define TONE_FONT_IMAGE_H

#include <stddef.h>
#include <stdint.h>

typedef struct BitmapFont {
    uint8_t *bytes;
    size_t length;
    uint32_t glyph_count;
    uint32_t height;
    uint32_t max_glyph_width;
} BitmapFont;

/* Parses the observed 1.x font container and keeps a private copy of its data. */
int bitmap_font_init(BitmapFont *font, const void *bytes, size_t length,
                     char *error, size_t error_capacity);
void bitmap_font_free(BitmapFont *font);
int bitmap_font_get_glyph(const BitmapFont *font, uint32_t code,
                          uint32_t *width, const uint8_t **pixels);

#endif
