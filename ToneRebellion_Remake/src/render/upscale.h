/* CPU image upscaler for the presented game frame.
 *
 * Pixels are 32-bit 0x00RRGGBB; the source top byte is ignored and every
 * written pixel has a zero top byte. Strides are in pixels (uint32_t units).
 *
 * Usage per paint:
 *   upscale_prepare(ctx, filter, src_w, src_h, dst_w, dst_h);   cheap when unchanged
 *   for pass in [0, upscale_pass_count(ctx)):
 *       upscale_run_pass(ctx, pass, ...) over rows [0, upscale_pass_rows(ctx, pass)),
 *       split across threads; barrier.
 * Calls covering disjoint row ranges of the same pass may run concurrently.
 * Earlier passes write internal buffers read by later passes, possibly at
 * neighbouring rows, so pass k+1 must not start before every slice of pass k
 * has finished. Only the last pass writes dst (its rows are destination rows);
 * earlier passes are split over source rows. Output does not depend on how a
 * pass is sliced.
 */
#ifndef TONE_RENDER_UPSCALE_H
#define TONE_RENDER_UPSCALE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum UpscaleFilter {
    UPSCALE_NEAREST,
    UPSCALE_BILINEAR,
    UPSCALE_SHARP_BILINEAR,
    UPSCALE_BICUBIC,   /* Catmull-Rom */
    UPSCALE_LANCZOS3,
    UPSCALE_XBR,
    UPSCALE_HQX,
    UPSCALE_SCALEFX,
    UPSCALE_FILTER_COUNT
} UpscaleFilter;

typedef struct UpscaleContext UpscaleContext; /* opaque */

UpscaleContext *upscale_create(void);
void upscale_destroy(UpscaleContext *ctx);

/* (Re)builds tables and scratch buffers when anything changed.
 * Returns 0 on allocation failure or invalid sizes (the context is then
 * unusable until a later successful prepare), 1 otherwise. */
int upscale_prepare(UpscaleContext *ctx, UpscaleFilter filter,
                    int src_w, int src_h, int dst_w, int dst_h);

/* Number of passes of the prepared filter (>= 1). */
int upscale_pass_count(const UpscaleContext *ctx);

/* Number of rows pass `pass` is split over (0 for an invalid pass/context). */
int upscale_pass_rows(const UpscaleContext *ctx, int pass);

/* Runs rows [y0, y1) of pass `pass`. src is read by the passes that need the
 * source (every pass gets the same src/dst arguments); dst is written only by
 * the last pass. */
void upscale_run_pass(UpscaleContext *ctx, int pass, const uint32_t *src, int src_stride,
                      uint32_t *dst, int dst_stride, int y0, int y1);

/* Single-thread convenience: every pass over the whole image. */
void upscale_run(UpscaleContext *ctx, const uint32_t *src, int src_stride,
                 uint32_t *dst, int dst_stride);

/* Short English name ("Bilinear", "xBR", ...); "?" for an invalid value. */
const char *upscale_filter_name(UpscaleFilter filter);

/* Prescale factor of the pixel-art filters (xBR/HQx 2..4, ScaleFX 3), else 1. */
int upscale_filter_factor(const UpscaleContext *ctx);

#ifdef __cplusplus
}
#endif

#endif
