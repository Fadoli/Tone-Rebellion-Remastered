/* CPU image upscaler for the presented game frame.
 *
 * Pixels are 32-bit 0x00RRGGBB; the source top byte is ignored and every
 * written pixel has a zero top byte. Strides are in pixels (uint32_t units).
 *
 * Usage per paint:
 *   upscale_prepare(ctx, filter, src_w, src_h, dst_w, dst_h);   cheap when unchanged
 *   stage 1 over source rows [0, upscale_stage1_rows(ctx)) (split across threads),
 *   barrier,
 *   stage 2 over destination rows [0, dst_h) (split across threads).
 * Calls covering disjoint row ranges of the same stage may run concurrently.
 * Stage 1 writes internal buffers that stage 2 reads, so stage 2 must not start
 * before every stage 1 slice has finished.
 *
 * Stage 1 is used by every filter except NEAREST: the pixel-art filters
 * prescale there, the separable filters run their horizontal pass there.
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

/* Stage 1: source rows [y0, y1). No-op for filters that do not need it. */
void upscale_run_stage1(UpscaleContext *ctx, const uint32_t *src, int src_stride,
                        int y0, int y1);

/* Number of source rows stage 1 is split over (0 when stage 1 is a no-op). */
int upscale_stage1_rows(const UpscaleContext *ctx);

/* Stage 2: destination rows [y0, y1). */
void upscale_run_stage2(UpscaleContext *ctx, const uint32_t *src, int src_stride,
                        uint32_t *dst, int dst_stride, int y0, int y1);

/* Single-thread convenience: both stages over the whole image. */
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
