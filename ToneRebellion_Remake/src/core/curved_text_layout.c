#include "curved_text_layout.h"

#include <string.h>

enum {
    TEXT_LEFT_MARGIN = 20,
    TEXT_LEFT_EDGE = 315,
    TEXT_RIGHT_EDGE = 620,
    TEXT_RIGHT_MARGIN = 325,
    TEXT_CENTER_Y = 240,
    TEXT_RADIUS_SQUARED = 40000,
    TEXT_LINE_GAP = 3
};

static int32_t integer_sqrt(int32_t value)
{
    int32_t low = 0;
    int32_t high = 200;
    while (low < high) {
        int32_t middle = low + (high - low + 1) / 2;
        if (middle * middle <= value) low = middle;
        else high = middle - 1;
    }
    return low;
}

int curved_text_bounds(CurvedTextSide side, int32_t y,
                       int32_t *x, int32_t *width)
{
    int32_t delta = y - TEXT_CENTER_Y;
    int32_t radial;
    int32_t right;
    if (x == NULL || width == NULL ||
        (side != CURVED_TEXT_LEFT && side != CURVED_TEXT_RIGHT)) return 0;
    if (delta > 200 || delta < -200) return 0;
    radial = integer_sqrt(TEXT_RADIUS_SQUARED - delta * delta);
    if (side == CURVED_TEXT_LEFT) {
        *x = TEXT_LEFT_MARGIN;
        right = TEXT_LEFT_EDGE - radial;
    } else {
        *x = TEXT_RIGHT_MARGIN + radial;
        right = TEXT_RIGHT_EDGE;
    }
    *width = right - *x;
    return *width > 0;
}

static size_t layout_from(const char *text, CurvedTextSide side,
                          int32_t start_y, int32_t font_height,
                          CurvedTextMeasure measure, void *measure_context,
                          CurvedTextLine *lines, size_t capacity)
{
    size_t text_length = strlen(text);
    size_t cursor = 0;
    size_t count = 0;
    int32_t y = start_y;

    while (cursor < text_length && count < capacity) {
        int32_t x;
        int32_t available;
        size_t end = cursor;
        size_t next = cursor;
        size_t i;
        y += TEXT_LINE_GAP + font_height;
        if (!curved_text_bounds(side, y, &x, &available)) return 0;

        for (i = cursor; i <= text_length; ++i) {
            if (i != text_length && text[i] != ' ') continue;
            if (measure(measure_context, text + cursor, i - cursor) > available) break;
            end = i;
            next = i == text_length ? i : i + 1;
        }

        if (end == cursor && cursor < text_length) {
            /* A malformed/oversized word should still make bounded progress. */
            end = cursor + 1;
            while (end < text_length && text[end] != ' ' &&
                   measure(measure_context, text + cursor, end + 1 - cursor) <= available)
                ++end;
            next = end < text_length && text[end] == ' ' ? end + 1 : end;
        }
        if (end <= cursor) return 0;
        lines[count++] = (CurvedTextLine){cursor, end - cursor, x, y, available};
        cursor = next;
        while (cursor < text_length && text[cursor] == ' ') ++cursor;
    }
    return cursor == text_length ? count : 0;
}

int curved_text_layout(const char *text, CurvedTextSide side,
                       int32_t bottom_y, int32_t font_height,
                       CurvedTextMeasure measure, void *measure_context,
                       CurvedTextLine *lines, size_t line_capacity,
                       size_t *line_count)
{
    CurvedTextLine candidate[CURVED_TEXT_MAX_LINES];
    CurvedTextLine best[CURVED_TEXT_MAX_LINES];
    size_t best_count = 0;
    size_t best_distance = (size_t)-1;
    size_t guess;
    int32_t step;

    if (text == NULL || measure == NULL || lines == NULL || line_count == NULL ||
        line_capacity == 0 || line_capacity > CURVED_TEXT_MAX_LINES ||
        font_height <= 0 || (side != CURVED_TEXT_LEFT && side != CURVED_TEXT_RIGHT))
        return 0;
    if (text[0] == '\0') {
        *line_count = 0;
        return 1;
    }
    step = TEXT_LINE_GAP + font_height;

    /* The original asks the font object for the wrapped paragraph height
       first, then starts at bottom_y - height. Find that stable line count. */
    for (guess = 1; guess <= line_capacity; ++guess) {
        size_t actual;
        size_t distance;
        /* FUN_00428baa starts from bottom_y - measured_text_height. The line
           callback advances by font_height + 3 before returning its baseline;
           do not subtract another glyph height here or the whole paragraph
           moves upward by one row and collides with the tribe emblems. */
        int32_t start_y = bottom_y - (int32_t)guess * step;
        actual = layout_from(text, side, start_y, font_height, measure,
                             measure_context, candidate, line_capacity);
        if (actual == 0) continue;
        if (actual == guess) {
            memcpy(lines, candidate, actual * sizeof(*lines));
            *line_count = actual;
            return 1;
        }
        /* A non-converging wrap can gain a line when the guessed start moves
           into a narrower part of the curve. Keep the closest candidate that
           ends at or above the callback baseline anchor. The New Game footer
           begins below that anchor; its room must not be taken by moving the
           entire paragraph upward. Bounds remain those used to wrap it. */
        if (actual < guess) {
            distance = guess - actual;
            if (distance < best_distance) {
                best_distance = distance;
                best_count = actual;
                memcpy(best, candidate, actual * sizeof(*best));
            }
        }
    }
    if (best_count == 0 || best_count > line_capacity) return 0;
    memcpy(lines, best, best_count * sizeof(*lines));
    *line_count = best_count;
    return 1;
}
