#include "cinepak.h"

#include <stdlib.h>
#include <string.h>

static uint32_t read_be16(const uint8_t *p) { return ((uint32_t)p[0] << 8) | p[1]; }
static uint32_t read_be24(const uint8_t *p)
{
    return ((uint32_t)p[0] << 16) | ((uint32_t)p[1] << 8) | p[2];
}
static uint32_t read_be32(const uint8_t *p)
{
    return ((uint32_t)p[0] << 24) | read_be24(p + 1);
}

static uint32_t clamp_rgb(int r, int g, int b)
{
    if (r < 0) r = 0; else if (r > 255) r = 255;
    if (g < 0) g = 0; else if (g > 255) g = 255;
    if (b < 0) b = 0; else if (b > 255) b = 255;
    return 0xFF000000U | ((uint32_t)r << 16) | ((uint32_t)g << 8) | (uint32_t)b;
}

int cinepak_init(CinepakDecoder *decoder, int width, int height)
{
    size_t count;
    memset(decoder, 0, sizeof(*decoder));
    if (width <= 0 || height <= 0 || width > 4096 || height > 4096) return 0;
    count = (size_t)width * (size_t)height;
    decoder->pixels = (uint32_t *)malloc(count * sizeof(uint32_t));
    if (decoder->pixels == NULL) return 0;
    for (size_t i = 0; i < count; ++i) decoder->pixels[i] = 0xFF000000U;
    decoder->width = width;
    decoder->height = height;
    return 1;
}

void cinepak_free(CinepakDecoder *decoder)
{
    free(decoder->pixels);
    decoder->pixels = NULL;
}

/* Chunks 0x20..0x27: bit 0 = selective update (a 32-bit flag word per 32
   entries), bit 2 = 4-byte greyscale entries instead of 6-byte Y4 U V. */
static void decode_codebook(uint32_t codebook[256][4], unsigned chunk_id,
                            const uint8_t *data, const uint8_t *end)
{
    const int entry_size = (chunk_id & 0x04U) ? 4 : 6;
    uint32_t flags = 0;
    uint32_t mask = 0;
    int i;
    for (i = 0; i < 256; ++i) {
        if ((chunk_id & 0x01U) && (mask >>= 1) == 0) {
            if (end - data < 4) return;
            flags = read_be32(data);
            data += 4;
            mask = 0x80000000U;
        }
        if ((chunk_id & 0x01U) && (flags & mask) == 0) continue;
        if (end - data < entry_size) return;
        if (entry_size == 4) {
            int k;
            for (k = 0; k < 4; ++k) codebook[i][k] = clamp_rgb(data[k], data[k], data[k]);
        } else {
            const int u = (int8_t)data[4];
            const int v = (int8_t)data[5];
            int k;
            for (k = 0; k < 4; ++k) {
                const int y = data[k];
                codebook[i][k] = clamp_rgb(y + v * 2, y - u / 2 - v, y + u * 2);
            }
        }
        data += entry_size;
    }
}

static void put_pixel(CinepakDecoder *decoder, int x, int y, uint32_t color)
{
    if (x < decoder->width && y < decoder->height)
        decoder->pixels[(size_t)y * (size_t)decoder->width + (size_t)x] = color;
}

/* A V1 entry scaled to 4x4: each of its pixels covers 2x2. */
static void put_v1(CinepakDecoder *decoder, int x, int y, const uint32_t entry[4])
{
    int dy;
    int dx;
    for (dy = 0; dy < 4; ++dy)
        for (dx = 0; dx < 4; ++dx)
            put_pixel(decoder, x + dx, y + dy, entry[(dy / 2) * 2 + dx / 2]);
}

/* Four V4 entries, one 2x2 block each, in reading order. */
static void put_v4(CinepakDecoder *decoder, int x, int y, const uint32_t *entries[4])
{
    int block;
    for (block = 0; block < 4; ++block) {
        const int bx = x + (block & 1) * 2;
        const int by = y + (block >> 1) * 2;
        put_pixel(decoder, bx, by, entries[block][0]);
        put_pixel(decoder, bx + 1, by, entries[block][1]);
        put_pixel(decoder, bx, by + 1, entries[block][2]);
        put_pixel(decoder, bx + 1, by + 1, entries[block][3]);
    }
}

/* Chunks 0x30..0x32: bit 0 = inter (a skip flag per block), bit 1 = every
   block is V1 (no V1/V4 flags). */
static int decode_vectors(CinepakDecoder *decoder, int strip, unsigned chunk_id,
                          int x1, int y1, int x2, int y2,
                          const uint8_t *data, const uint8_t *end)
{
    uint32_t flags = 0;
    uint32_t mask = 0;
    int x;
    int y;
    for (y = y1; y < y2; y += 4) {
        for (x = x1; x < x2; x += 4) {
            if ((chunk_id & 0x01U) && (mask >>= 1) == 0) {
                if (end - data < 4) return 0;
                flags = read_be32(data);
                data += 4;
                mask = 0x80000000U;
            }
            if ((chunk_id & 0x01U) && (flags & mask) == 0) continue;
            if (!(chunk_id & 0x02U) && (mask >>= 1) == 0) {
                if (end - data < 4) return 0;
                flags = read_be32(data);
                data += 4;
                mask = 0x80000000U;
            }
            if ((chunk_id & 0x02U) || (flags & mask) == 0) {
                if (end - data < 1) return 0;
                put_v1(decoder, x, y, decoder->v1[strip][*data++]);
            } else {
                const uint32_t *entries[4];
                if (end - data < 4) return 0;
                entries[0] = decoder->v4[strip][data[0]];
                entries[1] = decoder->v4[strip][data[1]];
                entries[2] = decoder->v4[strip][data[2]];
                entries[3] = decoder->v4[strip][data[3]];
                data += 4;
                put_v4(decoder, x, y, entries);
            }
        }
    }
    return 1;
}

int cinepak_decode(CinepakDecoder *decoder, const uint8_t *data, size_t size)
{
    const uint8_t *end = data + size;
    unsigned frame_flags;
    unsigned strip_count;
    unsigned strip;
    int y0 = 0;
    if (size == 0) return 1;
    if (size < 10 || decoder->pixels == NULL) return 0;
    frame_flags = data[0];
    strip_count = read_be16(data + 8);
    data += 10;
    if (strip_count > CINEPAK_MAX_STRIPS) strip_count = CINEPAK_MAX_STRIPS;
    for (strip = 0; strip < strip_count; ++strip) {
        const uint8_t *strip_end;
        uint32_t strip_size;
        int x1;
        int y1;
        int x2;
        int y2;
        if (end - data < 12) return 0;
        strip_size = read_be24(data + 1);
        y1 = (int)read_be16(data + 4);
        x1 = (int)read_be16(data + 6);
        y2 = (int)read_be16(data + 8);
        x2 = (int)read_be16(data + 10);
        /* A zero top is relative to the previous strip; the bottom field
           then holds the strip height. */
        if (y1 == 0) {
            y1 = y0;
            y2 = y0 + y2;
        }
        if (strip_size < 12) return 0;
        strip_end = (size_t)(end - data) < strip_size ? end : data + strip_size;
        data += 12;
        if (x2 > decoder->width) x2 = decoder->width;
        if (y2 > decoder->height) y2 = decoder->height;
        if (x1 >= x2 || y1 >= y2) return 0;
        /* Without frame flag 1 a strip starts from the previous strip's
           codebooks. */
        if (strip > 0 && !(frame_flags & 0x01U)) {
            memcpy(decoder->v1[strip], decoder->v1[strip - 1], sizeof(decoder->v1[strip]));
            memcpy(decoder->v4[strip], decoder->v4[strip - 1], sizeof(decoder->v4[strip]));
        }
        /* strip_end never passes end: a whole chunk header must fit in the
           strip, or data would step past strip_end below. */
        while (strip_end - data >= 4) {
            const unsigned chunk_id = data[0];
            uint32_t chunk_size = read_be24(data + 1);
            const uint8_t *chunk_end;
            if (chunk_size < 4) return 0;
            chunk_size -= 4;
            data += 4;
            chunk_end = (size_t)(strip_end - data) < chunk_size ? strip_end : data + chunk_size;
            if (chunk_id >= 0x20U && chunk_id <= 0x27U) {
                decode_codebook((chunk_id & 0x02U) ? decoder->v1[strip] : decoder->v4[strip],
                                chunk_id, data, chunk_end);
            } else if (chunk_id >= 0x30U && chunk_id <= 0x32U) {
                if (!decode_vectors(decoder, (int)strip, chunk_id, x1, y1, x2, y2,
                                    data, chunk_end)) return 0;
            }
            data = chunk_end;
        }
        data = strip_end;
        y0 = y2;
    }
    return 1;
}
