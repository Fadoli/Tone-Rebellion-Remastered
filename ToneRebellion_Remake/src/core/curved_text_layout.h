#ifndef TONE_REBELLION_CURVED_TEXT_LAYOUT_H
#define TONE_REBELLION_CURVED_TEXT_LAYOUT_H

#include <stddef.h>
#include <stdint.h>

enum {
    CURVED_TEXT_MAX_LINES = 64,
    /* Preserve native glyph rows; narrow translated text to fit the arc. */
    CURVED_TEXT_NEWGAME_RENDER_HEIGHT = 13,
    CURVED_TEXT_NEWGAME_WIDTH_NUMERATOR = 11,
    CURVED_TEXT_NEWGAME_WIDTH_DENOMINATOR = 13,
    /* Keeps translated paragraphs clear of the top icons at native height. */
    CURVED_TEXT_NEWGAME_LINE_GAP = 1,
    /* Calibrated to the supplied original-game capture. The numeric source
       global used by FUN_0044ec5d is not resolved in the exported evidence. */
    CURVED_TEXT_NEWGAME_LAST_LINE_Y = 392
};

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
