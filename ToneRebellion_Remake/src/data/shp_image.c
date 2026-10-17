#include "shp_image.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static uint32_t read_u32(const uint8_t *p)
{
    return (uint32_t)p[0] | ((uint32_t)p[1] << 8) |
           ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24);
}

static int fail(char *error, size_t capacity, const char *message)
{
    if (capacity != 0) {
        (void)snprintf(error, capacity, "%s", message);
    }
    return 0;
}

int shp_file_init(ShpFile *shp, const void *bytes, size_t length,
                  char *error, size_t error_capacity)
{
    const uint8_t *data = (const uint8_t *)bytes;
    uint32_t count;
    uint32_t frame_index;
    size_t table_bytes;
    if (shp == NULL || data == NULL || length < 8) {
        return fail(error, error_capacity, "SHP header is truncated");
    }
    if (memcmp(data, "1.10", 4) != 0) {
        return fail(error, error_capacity, "unsupported SHP version (expected 1.10)");
    }
    count = read_u32(data + 4);
    if (count == 0 || (size_t)count > (SIZE_MAX - 8) / 8) {
        return fail(error, error_capacity, "invalid SHP frame count");
    }
    table_bytes = (size_t)count * 8;
    if (table_bytes > length - 8) {
        return fail(error, error_capacity, "SHP frame table exceeds the member length");
    }
    for (frame_index = 0; frame_index < count; ++frame_index) {
        uint32_t frame_offset = read_u32(data + 8 + (size_t)frame_index * 8);
        uint32_t previous_offset = frame_index == 0 ? 0 :
            read_u32(data + 8 + (size_t)(frame_index - 1) * 8);
        if (frame_offset < 8 + table_bytes || frame_offset > length ||
            length - frame_offset < 24 ||
            (frame_index != 0 && frame_offset < previous_offset)) {
            if (error != NULL && error_capacity != 0) {
                (void)snprintf(error, error_capacity,
                               "SHP frame %u offset %lu invalid (previous %lu, length %lu)",
                               (unsigned)frame_index, (unsigned long)frame_offset,
                               (unsigned long)previous_offset, (unsigned long)length);
                error[error_capacity - 1] = '\0';
            }
            return 0;
        }
    }
    shp->bytes = data;
    shp->length = length;
    shp->frame_count = count;
    return 1;
}

int shp_decode_frame(const ShpFile *shp, uint32_t frame_index, ShpFrame *frame,
                     char *error, size_t error_capacity)
{
    const uint8_t *data;
    size_t frame_offset;
    size_t frame_end;
    size_t cursor;
    size_t pixels_count;
    int32_t left;
    int32_t top;
    int32_t right;
    int32_t bottom;
    uint32_t x;
    uint32_t y;
    uint8_t pending_control = 0;
    int has_pending_control = 0;
    uint32_t next_index;

    if (shp == NULL || frame == NULL || shp->bytes == NULL ||
        frame_index >= shp->frame_count) {
        return fail(error, error_capacity, "SHP frame index or descriptor is invalid");
    }
    memset(frame, 0, sizeof(*frame));
    data = shp->bytes;
    frame_offset = (size_t)read_u32(data + 8 + (size_t)frame_index * 8);
    /* Some original sheets alias consecutive frames by storing the same
       offset more than once. Use the next distinct record as this frame's
       bound so aliases decode the shared image instead of an empty span. */
    next_index = frame_index + 1;
    while (next_index < shp->frame_count &&
           read_u32(data + 8 + (size_t)next_index * 8) == frame_offset) {
        ++next_index;
    }
    frame_end = next_index < shp->frame_count
                    ? (size_t)read_u32(data + 8 + (size_t)next_index * 8)
                    : shp->length;
    if (frame_offset > shp->length || shp->length - frame_offset < 24 ||
        frame_end < frame_offset + 24 || frame_end > shp->length) {
        return fail(error, error_capacity, "SHP frame header is outside the member");
    }
    left = (int32_t)read_u32(data + frame_offset + 8);
    top = (int32_t)read_u32(data + frame_offset + 12);
    right = (int32_t)read_u32(data + frame_offset + 16);
    bottom = (int32_t)read_u32(data + frame_offset + 20);
    if (right < left || bottom < top || right - left >= 8192 || bottom - top >= 8192) {
        return fail(error, error_capacity, "SHP frame bounds are invalid or excessive");
    }
    frame->width = (uint32_t)(right - left + 1);
    frame->height = (uint32_t)(bottom - top + 1);
    frame->x_offset = left;
    frame->y_offset = top;
    pixels_count = (size_t)frame->width * (size_t)frame->height;
    if (pixels_count / frame->width != frame->height) {
        return fail(error, error_capacity, "SHP frame dimensions overflow");
    }
    frame->pixels = (uint8_t *)calloc(pixels_count, 1);
    frame->opaque = (uint8_t *)calloc(pixels_count, 1);
    if (frame->pixels == NULL || frame->opaque == NULL) {
        shp_frame_free(frame);
        return fail(error, error_capacity, "unable to allocate SHP frame pixels");
    }

    /* Empty frames occur in original sheets such as BR-TRG01.SHP. Their
       offset spans the 24-byte SHP frame header and contains no RLE rows.
       The leading words are not dimensions (valid source frames can store
       zero there); the signed bounds at +8/+12/+16/+20 determine geometry. */
    if (frame_end == frame_offset + 24) {
        return 1;
    }

    cursor = frame_offset + 24;
    for (y = 0; y < frame->height; ++y) {
        x = 0;
        for (;;) {
            uint8_t control;
            uint32_t run;
            size_t row = (size_t)y * frame->width;
            if (cursor >= frame_end) {
                shp_frame_free(frame);
                return fail(error, error_capacity, "SHP RLE stream ended before the frame");
            }
            if (has_pending_control) {
                control = pending_control;
                has_pending_control = 0;
            } else {
                control = data[cursor++];
            }
            if (control == 0) {
                break;
            }
            run = (uint32_t)(control >> 1);
            if (run == 0) {
                uint8_t skip;
                if (cursor + 1 >= frame_end) {
                    shp_frame_free(frame);
                    return fail(error, error_capacity, "truncated SHP transparent run");
                }
                skip = data[cursor];
                pending_control = data[cursor + 1];
                has_pending_control = 1;
                cursor += 2; /* skip count and next control token */
                if (skip > frame->width - x) {
                    shp_frame_free(frame);
                    return fail(error, error_capacity, "SHP transparent run exceeds row width");
                }
                x += skip;
                continue;
            }
            if (run > frame->width - x) {
                char message[128];
                (void)snprintf(message, sizeof(message),
                               "SHP color run (%u) exceeds row %u at x=%u (width=%u)",
                               (unsigned)run, (unsigned)y, (unsigned)x,
                               (unsigned)frame->width);
                shp_frame_free(frame);
                return fail(error, error_capacity, message);
            }
            if ((control & 1u) != 0) {
                if (run > frame_end - cursor) {
                    shp_frame_free(frame);
                    return fail(error, error_capacity, "truncated SHP literal run");
                }
                memcpy(frame->pixels + row + x, data + cursor, run);
                memset(frame->opaque + row + x, 1, run);
                cursor += run;
            } else {
                uint8_t color;
                if (cursor >= frame_end) {
                    shp_frame_free(frame);
                    return fail(error, error_capacity, "truncated SHP repeated-color run");
                }
                color = data[cursor++];
                memset(frame->pixels + row + x, color, run);
                memset(frame->opaque + row + x, 1, run);
            }
            x += run;
        }
    }
    return 1;
}

void shp_frame_free(ShpFrame *frame)
{
    if (frame != NULL) {
        free(frame->pixels);
        free(frame->opaque);
        memset(frame, 0, sizeof(*frame));
    }
}
