#ifndef TONE_CINEPAK_H
#define TONE_CINEPAK_H

#include <stddef.h>
#include <stdint.h>

/* Cinepak ('cvid') video decoder for THING2\INTRO.AVI (640x480, 24-bit,
   15 frames/s). The original plays the file through DirectShow
   (FUN_00449b80); the port decodes it itself. Frames are decoded in order:
   inter frames update the previous picture and the strip codebooks. */

enum { CINEPAK_MAX_STRIPS = 32 };

typedef struct CinepakDecoder {
    int width;
    int height;
    /* 0xFFRRGGBB, width * height, kept between frames. */
    uint32_t *pixels;
    /* Per strip: 256 entries of 2x2 pixels (top-left, top-right,
       bottom-left, bottom-right). */
    uint32_t v1[CINEPAK_MAX_STRIPS][256][4];
    uint32_t v4[CINEPAK_MAX_STRIPS][256][4];
} CinepakDecoder;

int cinepak_init(CinepakDecoder *decoder, int width, int height);
void cinepak_free(CinepakDecoder *decoder);
/* Decodes one frame into decoder->pixels; 0 on malformed data (the picture
   keeps what was decoded). An empty frame repeats the previous picture. */
int cinepak_decode(CinepakDecoder *decoder, const uint8_t *data, size_t size);

#endif
