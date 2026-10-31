#include "render_surface.h"

#include <stddef.h>

void render_surface_init(RenderSurface *surface, uint32_t *pixels,
                         int width, int height, int stride)
{
    surface->pixels = pixels;
    surface->width = width;
    surface->height = height;
    surface->stride = stride;
    render_surface_reset_clip(surface);
}

void render_surface_reset_clip(RenderSurface *surface)
{
    surface->clip.left = 0;
    surface->clip.top = 0;
    surface->clip.right = surface->width;
    surface->clip.bottom = surface->height;
    surface->clip.mask = NULL;
    surface->clip.mask_left = 0;
    surface->clip.mask_top = 0;
    surface->clip.mask_stride = 0;
    surface->depth = 0;
}

int render_surface_save(RenderSurface *surface)
{
    if (surface->depth + 1 >= RENDER_SURFACE_CLIP_STACK) return 0;
    surface->saved[++surface->depth] = surface->clip;
    return surface->depth;
}

int render_surface_restore(RenderSurface *surface, int level)
{
    int target = level < 0 ? surface->depth + level + 1 : level;
    if (target < 1 || target > surface->depth) return 0;
    surface->clip = surface->saved[target];
    surface->depth = target - 1;
    return 1;
}

void render_surface_intersect_clip(RenderSurface *surface, int left, int top,
                                   int right, int bottom)
{
    RenderClip *clip = &surface->clip;
    if (left > clip->left) clip->left = left;
    if (top > clip->top) clip->top = top;
    if (right < clip->right) clip->right = right;
    if (bottom < clip->bottom) clip->bottom = bottom;
}

int render_surface_intersect_mask(RenderSurface *surface, const uint8_t *mask,
                                  int left, int top, int width, int height,
                                  int stride)
{
    if (surface->clip.mask != NULL || mask == NULL) return 0;
    render_surface_intersect_clip(surface, left, top, left + width,
                                  top + height);
    surface->clip.mask = mask;
    surface->clip.mask_left = left;
    surface->clip.mask_top = top;
    surface->clip.mask_stride = stride;
    return 1;
}

int render_surface_clip_box(const RenderSurface *surface, int *left, int *top,
                            int *right, int *bottom)
{
    const RenderClip *clip = &surface->clip;
    *left = clip->left < 0 ? 0 : clip->left;
    *top = clip->top < 0 ? 0 : clip->top;
    *right = clip->right > surface->width ? surface->width : clip->right;
    *bottom = clip->bottom > surface->height ? surface->height : clip->bottom;
    return *left < *right && *top < *bottom;
}

/* Mask row of surface row `y`, offset so it is indexed by surface x. */
static const uint8_t *clip_mask_row(const RenderClip *clip, int y)
{
    if (clip->mask == NULL) return NULL;
    return clip->mask + (ptrdiff_t)(y - clip->mask_top) * clip->mask_stride -
           clip->mask_left;
}

int render_surface_visible(const RenderSurface *surface, int x, int y)
{
    int left, top, right, bottom;
    const uint8_t *mask_row;
    if (!render_surface_clip_box(surface, &left, &top, &right, &bottom) ||
        x < left || x >= right || y < top || y >= bottom) return 0;
    mask_row = clip_mask_row(&surface->clip, y);
    return mask_row == NULL || mask_row[x] != 0U;
}

void render_surface_fill_rect(RenderSurface *surface, int left, int top,
                              int right, int bottom, uint32_t pixel)
{
    int clip_left, clip_top, clip_right, clip_bottom;
    int row;
    if (surface->pixels == NULL ||
        !render_surface_clip_box(surface, &clip_left, &clip_top, &clip_right,
                                 &clip_bottom)) return;
    if (left < clip_left) left = clip_left;
    if (top < clip_top) top = clip_top;
    if (right > clip_right) right = clip_right;
    if (bottom > clip_bottom) bottom = clip_bottom;
    for (row = top; row < bottom; ++row) {
        uint32_t *out = surface->pixels + (ptrdiff_t)row * surface->stride;
        const uint8_t *mask_row = clip_mask_row(&surface->clip, row);
        int column;
        if (mask_row == NULL) {
            for (column = left; column < right; ++column) out[column] = pixel;
        } else {
            for (column = left; column < right; ++column)
                if (mask_row[column] != 0U) out[column] = pixel;
        }
    }
}

void render_surface_frame_rect(RenderSurface *surface, int left, int top,
                               int right, int bottom, uint32_t pixel)
{
    if (right <= left || bottom <= top) return;
    render_surface_fill_rect(surface, left, top, right, top + 1, pixel);
    render_surface_fill_rect(surface, left, bottom - 1, right, bottom, pixel);
    render_surface_fill_rect(surface, left, top, left + 1, bottom, pixel);
    render_surface_fill_rect(surface, right - 1, top, right, bottom, pixel);
}

void render_surface_set_pixel(RenderSurface *surface, int x, int y,
                              uint32_t pixel)
{
    if (surface->pixels != NULL && render_surface_visible(surface, x, y))
        surface->pixels[(ptrdiff_t)y * surface->stride + x] = pixel;
}

int render_surface_get_pixel(const RenderSurface *surface, int x, int y,
                             uint32_t *pixel)
{
    if (surface->pixels == NULL || !render_surface_visible(surface, x, y))
        return 0;
    *pixel = surface->pixels[(ptrdiff_t)y * surface->stride + x];
    return 1;
}

/* Source offset of destination offset `offset` at a 16.16 scale. Offsets
   below 0x8000 keep the quotient in 32-bit arithmetic: a 64-bit division per
   pixel dominated scaled sprites. */
static int scaled_offset(int offset, uint32_t scale_16_16)
{
    if (scale_16_16 == 0x10000U) return offset;
    if (offset < 0x8000)
        return (int)(((uint32_t)offset << 16) / scale_16_16);
    return (int)(((uint64_t)(uint32_t)offset << 16) / scale_16_16);
}

static uint32_t blend_over(uint32_t pixel, uint32_t under)
{
    uint32_t alpha = pixel >> 24;
    uint32_t keep = 255U - alpha;
    return ((alpha + (((under >> 24) & 0xffU) * keep + 127U) / 255U) << 24) |
           ((((pixel >> 16) & 0xffU) +
             (((under >> 16) & 0xffU) * keep + 127U) / 255U) << 16) |
           ((((pixel >> 8) & 0xffU) +
             (((under >> 8) & 0xffU) * keep + 127U) / 255U) << 8) |
           ((pixel & 0xffU) + ((under & 0xffU) * keep + 127U) / 255U);
}

/* Blends one destination row span over out[left..right): source pixel
   in[columns[column - left]], or in[column] when `columns` is NULL (unscaled,
   `in` already offset by the caller). */
static void blit_span(uint32_t *out, const uint32_t *in, const int *columns,
                      int left, int right, const uint8_t *mask_row,
                      RenderPixelTransform transform, void *context)
{
    int column;
    if (columns == NULL && mask_row == NULL && transform == NULL) {
        for (column = left; column < right; ++column) {
            uint32_t pixel = in[column];
            uint32_t alpha = pixel >> 24;
            if (alpha == 0U) continue;
            out[column] = alpha == 255U ? pixel : blend_over(pixel, out[column]);
        }
        return;
    }
    for (column = left; column < right; ++column) {
        uint32_t pixel = columns != NULL ? in[columns[column - left]] : in[column];
        uint32_t alpha = pixel >> 24;
        if (alpha == 0U) continue;
        if (mask_row != NULL && mask_row[column] == 0U) continue;
        if (transform != NULL) {
            pixel = transform(pixel, context);
            alpha = pixel >> 24;
        }
        out[column] = alpha == 255U ? pixel : blend_over(pixel, out[column]);
    }
}

void render_surface_blit(RenderSurface *surface, const uint32_t *source,
                         int source_width, int source_height,
                         int source_stride, int source_x, int source_y,
                         int width, int height, int x, int y,
                         uint32_t scale_16_16,
                         RenderPixelTransform transform, void *context)
{
    /* 2 KB sampling table: keeps the stack frame under one 4 KB page, so
       MinGW does not probe the stack on every call. */
    enum { SPAN = 512 };
    int left = x;
    int right = x + width;
    int upper = y;
    int lower = y + height;
    int clip_left, clip_top, clip_right, clip_bottom;
    int row;
    int span_left;
    int columns[SPAN];
    if (surface->pixels == NULL || source == NULL || scale_16_16 == 0U ||
        source_width <= 0 || source_height <= 0 ||
        !render_surface_clip_box(surface, &clip_left, &clip_top, &clip_right,
                                 &clip_bottom)) return;
    if (left < clip_left) left = clip_left;
    if (upper < clip_top) upper = clip_top;
    if (right > clip_right) right = clip_right;
    if (lower > clip_bottom) lower = clip_bottom;
    if (left >= right || upper >= lower) return;
    if (scale_16_16 == 0x10000U && source_x >= 0 && source_y >= 0 &&
        source_x + width <= source_width && source_y + height <= source_height) {
        /* Plain copy inside the image: no sampling table or clamping. */
        for (row = upper; row < lower; ++row) {
            const uint32_t *in = source +
                (ptrdiff_t)(source_y + row - y) * source_stride + (source_x - x);
            blit_span(surface->pixels + (ptrdiff_t)row * surface->stride, in,
                      NULL, left, right, clip_mask_row(&surface->clip, row),
                      transform, context);
        }
        return;
    }
    for (span_left = left; span_left < right; span_left += SPAN) {
        int span_right = right - span_left > SPAN ? span_left + SPAN : right;
        int column;
        /* Source column of each destination column, computed once. */
        for (column = span_left; column < span_right; ++column) {
            int sample = source_x + scaled_offset(column - x, scale_16_16);
            if (sample >= source_width) sample = source_width - 1;
            columns[column - span_left] = sample;
        }
        for (row = upper; row < lower; ++row) {
            int sample_row = source_y + scaled_offset(row - y, scale_16_16);
            if (sample_row >= source_height) sample_row = source_height - 1;
            blit_span(surface->pixels + (ptrdiff_t)row * surface->stride,
                      source + (ptrdiff_t)sample_row * source_stride, columns,
                      span_left, span_right, clip_mask_row(&surface->clip, row),
                      transform, context);
        }
    }
}
