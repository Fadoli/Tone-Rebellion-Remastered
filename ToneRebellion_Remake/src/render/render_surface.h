#ifndef TONE_RENDER_SURFACE_H
#define TONE_RENDER_SURFACE_H

#include <stdint.h>

/* Portable software render target: 32-bit pixels 0xAARRGGBB (B, G, R, A in
   memory, the layout of a top-down 32-bit Windows DIB), rows top-down,
   `stride` pixels apart. The platform layer owns the memory and presents it.

   Drawing honours a clip: a rectangle plus an optional per-pixel mask,
   saved and restored as a stack (the SaveDC/RestoreDC/IntersectClipRect and
   ExtSelectClipRgn(RGN_AND) rules the Win32 renderer used). Fills, frames
   and single pixels store alpha 0, like GDI on a 32-bit DIB. */

enum { RENDER_SURFACE_CLIP_STACK = 64 };

typedef struct RenderClip {
    int left;
    int top;
    int right;
    int bottom;
    /* NULL, or a pixel is drawn only where mask[(y - mask_top) * mask_stride
       + (x - mask_left)] != 0. The box never extends past the mask. */
    const uint8_t *mask;
    int mask_left;
    int mask_top;
    int mask_stride;
} RenderClip;

typedef struct RenderSurface {
    uint32_t *pixels;
    int width;
    int height;
    int stride;
    RenderClip clip;
    RenderClip saved[RENDER_SURFACE_CLIP_STACK];
    int depth;
} RenderSurface;

/* Per-pixel colour transform applied to opaque-or-blended source pixels
   before blending; returns the new premultiplied pixel. */
typedef uint32_t (*RenderPixelTransform)(uint32_t pixel, void *context);

void render_surface_init(RenderSurface *surface, uint32_t *pixels,
                         int width, int height, int stride);
/* Whole surface, no mask, empty save stack. */
void render_surface_reset_clip(RenderSurface *surface);
/* Pushes the clip; returns the new level (1, 2, ...) or 0 when full. */
int render_surface_save(RenderSurface *surface);
/* Pops back to `level`; a negative level counts back from the top (-1 is
   the last save). Returns 0 for a level that was not saved. */
int render_surface_restore(RenderSurface *surface, int level);
void render_surface_intersect_clip(RenderSurface *surface, int left, int top,
                                   int right, int bottom);
/* ANDs a `width` x `height` mask placed at (left, top) into the clip.
   Only one mask can be active; returns 0 (clip unchanged) if one already
   is. The mask must stay valid until the clip is restored. */
int render_surface_intersect_mask(RenderSurface *surface, const uint8_t *mask,
                                  int left, int top, int width, int height,
                                  int stride);

/* Visible rectangle of [left, right) x [top, bottom); 0 when empty. */
int render_surface_clip_box(const RenderSurface *surface, int *left, int *top,
                            int *right, int *bottom);
int render_surface_visible(const RenderSurface *surface, int x, int y);

void render_surface_fill_rect(RenderSurface *surface, int left, int top,
                              int right, int bottom, uint32_t pixel);
/* One-pixel border inside [left, right) x [top, bottom), as GDI FrameRect
   (and Rectangle with a one-pixel pen and no brush). */
void render_surface_frame_rect(RenderSurface *surface, int left, int top,
                               int right, int bottom, uint32_t pixel);
void render_surface_set_pixel(RenderSurface *surface, int x, int y,
                              uint32_t pixel);
/* 0 when (x, y) is clipped out, like GetPixel's CLR_INVALID. */
int render_surface_get_pixel(const RenderSurface *surface, int x, int y,
                             uint32_t *pixel);

/* Source-over blend of premultiplied source pixels (AlphaBlend with
   AC_SRC_ALPHA). The destination rectangle (x, y, width, height) samples
   source (source_x + (column << 16) / scale, source_y + (row << 16) / scale)
   with nearest-pixel scaling, clamped to the image; scale_16_16 = 0x10000 is
   a plain copy. `transform` (may be NULL) recolours each non-transparent
   source pixel first. */
void render_surface_blit(RenderSurface *surface, const uint32_t *source,
                         int source_width, int source_height,
                         int source_stride, int source_x, int source_y,
                         int width, int height, int x, int y,
                         uint32_t scale_16_16,
                         RenderPixelTransform transform, void *context);

#endif
