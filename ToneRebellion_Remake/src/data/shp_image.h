#ifndef TONE_SHP_IMAGE_H
#define TONE_SHP_IMAGE_H

#include <stddef.h>
#include <stdint.h>

typedef struct ShpFile {
    const uint8_t *bytes;
    size_t length;
    uint32_t frame_count;
} ShpFile;

typedef struct ShpFrame {
    uint32_t width;
    uint32_t height;
    int32_t x_offset;
    int32_t y_offset;
    uint8_t *pixels;
    uint8_t *opaque;
} ShpFrame;

int shp_file_init(ShpFile *shp, const void *bytes, size_t length,
                  char *error, size_t error_capacity);
int shp_decode_frame(const ShpFile *shp, uint32_t frame_index, ShpFrame *frame,
                     char *error, size_t error_capacity);
void shp_frame_free(ShpFrame *frame);

#endif
