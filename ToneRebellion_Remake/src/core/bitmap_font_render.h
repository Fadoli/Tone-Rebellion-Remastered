#ifndef TONE_BITMAP_FONT_RENDER_H
#define TONE_BITMAP_FONT_RENDER_H

#include "font_image.h"

#include <stddef.h>
#include <stdint.h>

/* Draws the existing 1-bit glyph masks into a top-down 32-bit pixel buffer.
   Pixels outside the target are clipped. Returns the number of written pixels. */
size_t bitmap_font_render_pixels(const BitmapFont *font, const char *text,
                                 uint32_t *target, size_t target_width,
                                 size_t target_height, size_t target_stride,
                                 int x, int y, uint32_t pixel);

#endif
