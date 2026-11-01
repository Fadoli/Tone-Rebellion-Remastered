#ifndef TONE_REBELLION_PE_CURSOR_H
#define TONE_REBELLION_PE_CURSOR_H

#include <stddef.h>
#include <stdint.h>

/* Read-only reader for the cursor resources of a PE image (FLOAT.EXE), read
   as plain bytes: nothing is loaded or executed. A cursor group
   (RT_GROUP_CURSOR, the id LoadImage(IMAGE_CURSOR) takes) names RT_CURSOR
   images: a hotspot followed by a DIB whose doubled height holds the colour
   (XOR) rows and then the 1-bit AND mask. */

typedef struct PeCursor {
    int width;
    int height;
    int hotspot_x;
    int hotspot_y;
    /* width * height pixels 0xAARRGGBB (straight alpha), top-down. */
    uint32_t *pixels;
} PeCursor;

/* Loads the file into memory for pe_cursor_decode; free with pe_image_free. */
int pe_image_load(const char *path, uint8_t **data, size_t *size);
void pe_image_free(uint8_t *data);

/* Decodes the first image of cursor group `group_id`. Pixels where the AND
   mask is set are transparent (an inverting pixel becomes opaque black).
   Returns 1 on success; free with pe_cursor_free. */
int pe_cursor_decode(const uint8_t *image, size_t size, uint16_t group_id,
                     PeCursor *out);
void pe_cursor_free(PeCursor *cursor);

#endif
