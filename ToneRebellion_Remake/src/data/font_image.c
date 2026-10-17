#include "font_image.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static uint32_t read_u32_le(const uint8_t *p)
{
    return (uint32_t)p[0] | ((uint32_t)p[1] << 8) |
           ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24);
}

static int fail(char *error, size_t capacity, const char *message)
{
    if (capacity != 0) (void)snprintf(error, capacity, "%s", message);
    return 0;
}

int bitmap_font_init(BitmapFont *font, const void *source, size_t length,
                     char *error, size_t error_capacity)
{
    const uint8_t *bytes = (const uint8_t *)source;
    uint32_t glyph_count;
    uint32_t height;
    uint32_t max_width;
    size_t table_end;
    uint32_t glyph;
    uint8_t *copy;

    if (font == NULL || bytes == NULL || length < 16 ||
        bytes[0] != '1' || bytes[1] != '.') {
        return fail(error, error_capacity, "font header is missing or unsupported");
    }
    glyph_count = read_u32_le(bytes + 4);
    height = read_u32_le(bytes + 8);
    max_width = read_u32_le(bytes + 12);
    if (glyph_count == 0 || glyph_count > 256 || height == 0 || height > 256 ||
        max_width == 0 || max_width > 8192 ||
        (size_t)glyph_count > (SIZE_MAX - 16) / 4) {
        return fail(error, error_capacity, "font header values are outside supported limits");
    }
    table_end = 16 + (size_t)glyph_count * 4;
    if (table_end > length) {
        return fail(error, error_capacity, "font glyph table exceeds the data length");
    }
    for (glyph = 0; glyph < glyph_count; ++glyph) {
        uint32_t offset = read_u32_le(bytes + 16 + (size_t)glyph * 4);
        uint32_t width;
        size_t pixel_bytes;
        if ((size_t)offset < table_end || (size_t)offset > length || length - offset < 4) {
            return fail(error, error_capacity, "font glyph offset is outside its data");
        }
        width = read_u32_le(bytes + offset);
        if (width > max_width || (size_t)width > SIZE_MAX / height) {
            return fail(error, error_capacity, "font glyph width is invalid");
        }
        pixel_bytes = (size_t)width * height;
        if (pixel_bytes > length - offset - 4) {
            return fail(error, error_capacity, "font glyph bitmap exceeds its data");
        }
    }

    copy = (uint8_t *)malloc(length);
    if (copy == NULL) return fail(error, error_capacity, "font data allocation failed");
    memcpy(copy, bytes, length);
    memset(font, 0, sizeof(*font));
    font->bytes = copy;
    font->length = length;
    font->glyph_count = glyph_count;
    font->height = height;
    font->max_glyph_width = max_width;
    return 1;
}

void bitmap_font_free(BitmapFont *font)
{
    if (font == NULL) return;
    free(font->bytes);
    memset(font, 0, sizeof(*font));
}

int bitmap_font_get_glyph(const BitmapFont *font, uint32_t code,
                          uint32_t *width, const uint8_t **pixels)
{
    uint32_t offset;
    uint32_t glyph_width;
    if (font == NULL || font->bytes == NULL || code >= font->glyph_count ||
        width == NULL || pixels == NULL) return 0;
    offset = read_u32_le(font->bytes + 16 + (size_t)code * 4);
    glyph_width = read_u32_le(font->bytes + offset);
    *width = glyph_width;
    *pixels = font->bytes + offset + 4;
    return 1;
}
