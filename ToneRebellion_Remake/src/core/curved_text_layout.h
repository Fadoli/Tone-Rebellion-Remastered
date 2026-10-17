#ifndef TONE_REBELLION_CURVED_TEXT_LAYOUT_H
#define TONE_REBELLION_CURVED_TEXT_LAYOUT_H

#include <stddef.h>
#include <stdint.h>

enum { CURVED_TEXT_MAX_LINES = 64 };

typedef enum CurvedTextSide {
    CURVED_TEXT_LEFT = 0,
    CURVED_TEXT_RIGHT = 1
} CurvedTextSide;

typedef struct CurvedTextLine {
    size_t offset;
    size_t length;
    int32_t x;
    int32_t y;
    int32_t width;
} CurvedTextLine;

typedef int32_t (*CurvedTextMeasure)(void *context, const char *text,
                                     size_t length);

int curved_text_bounds(CurvedTextSide side, int32_t y,
                       int32_t *x, int32_t *width);

/* Reproduces FUN_0044e613's per-line curved text bounds and FUN_00428baa's
   word wrapping. The line boxes are horizontally justified by the renderer. */
int curved_text_layout(const char *text, CurvedTextSide side,
                       int32_t bottom_y, int32_t font_height,
                       CurvedTextMeasure measure, void *measure_context,
                       CurvedTextLine *lines, size_t line_capacity,
                       size_t *line_count);

#endif
