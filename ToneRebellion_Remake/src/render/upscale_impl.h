/* Internal entry points shared by upscale.c, upscale_xbr.c, upscale_hqx.c
 * and upscale_scalefx.c. Not part of the public upscaler API (upscale.h).
 * Pixels are 0x00RRGGBB, strides in pixels. */
#ifndef TONE_RENDER_UPSCALE_IMPL_H
#define TONE_RENDER_UPSCALE_IMPL_H

#include <stdint.h>

/* hq{k}x of source rows [y0, y1) (k = 2, 3 or 4) into dst, which holds the
 * k*sw x k*sh result; only output rows [k*y0, k*y1) are written. */
void upscale_hqx_rows(int k, const uint32_t *src, int ss, int sw, int sh,
                      uint32_t *dst, int ds, int y0, int y1);

/* xBR level 2 (k = 2, 3 or 4) of source rows [y0, y1) into dst, which holds
 * the k*sw x k*sh result; only output rows [k*y0, k*y1) are written. */
void upscale_xbr_rows(int k, const uint32_t *src, int ss, int sw, int sh,
                      uint32_t *dst, int ds, int y0, int y1);

/* ScaleFX (3x) intermediate buffers, sized by upscale_sfx_alloc. Each is
 * padded with copies of its edge texels (clamp-to-edge sampling). */
typedef struct SfxBuffers {
    int sw, sh;
    float *metric;     /* pass 0, 4 floats per texel, (sw+2) x (sh+2) */
    float *strength;   /* pass 1, 4 floats per texel, (sw+2) x (sh+2) */
    uint16_t *flags;   /* pass 2, four 4-bit fields, (sw+6) x (sh+6) */
    float unorm[256];  /* c / 255, the UNORM8 texel value */
} SfxBuffers;

int upscale_sfx_alloc(SfxBuffers *b, int sw, int sh);   /* 0 on failure */
void upscale_sfx_free(SfxBuffers *b);

/* Passes 0..2 of scalefx.slangp over source rows [y0, y1). */
void upscale_sfx_pass0(SfxBuffers *b, const uint32_t *src, int ss, int y0, int y1);
void upscale_sfx_pass1(SfxBuffers *b, int y0, int y1);
void upscale_sfx_pass2(SfxBuffers *b, int y0, int y1);
/* Passes 3 and 4 fused (pass 4 only reads its own pass-3 texel): source rows
 * [y0, y1) produce output rows [3*y0, 3*y1) of the 3*sw x 3*sh image dst. */
void upscale_sfx_pass34(const SfxBuffers *b, const uint32_t *src, int ss,
                        uint32_t *dst, int ds, int y0, int y1);

#endif
