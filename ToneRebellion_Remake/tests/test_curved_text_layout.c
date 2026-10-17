#include "curved_text_layout.h"

#include <assert.h>
#include <string.h>

static int32_t fixed_width(void *context, const char *text, size_t length)
{
    int32_t glyph_width = *(const int32_t *)context;
    size_t i;
    int32_t width = 0;
    for (i = 0; i < length; ++i) width += text[i] == ' ' ? glyph_width / 2 : glyph_width;
    return width;
}

static void test_circle_band_geometry(void)
{
    const int32_t width = 8;
    CurvedTextLine lines[CURVED_TEXT_MAX_LINES];
    size_t count;
    int32_t x;
    int32_t available;
    const char *sample = "one two three four five six seven eight nine ten eleven twelve thirteen fourteen fifteen sixteen seventeen eighteen";

    assert(curved_text_bounds(CURVED_TEXT_LEFT, 240, &x, &available));
    assert(x == 20 && available == 95);
    assert(curved_text_bounds(CURVED_TEXT_RIGHT, 240, &x, &available));
    assert(x == 525 && available == 95);
    assert(curved_text_bounds(CURVED_TEXT_LEFT, 40, &x, &available));
    assert(x == 20 && available == 295);
    assert(curved_text_bounds(CURVED_TEXT_RIGHT, 440, &x, &available));
    assert(x == 325 && available == 295);
    assert(!curved_text_bounds(CURVED_TEXT_LEFT, 39, &x, &available));
    assert(!curved_text_bounds(CURVED_TEXT_RIGHT, 441, &x, &available));
    assert(curved_text_layout(sample, CURVED_TEXT_LEFT, 410, 8,
                              fixed_width, (void *)&width, lines,
                              CURVED_TEXT_MAX_LINES, &count));
    assert(count > 1);
    assert(lines[0].y >= 40 && lines[count - 1].y <= 440);
    {
        size_t i;
        size_t consumed = 0;
        for (i = 0; i < count; ++i) {
            consumed += lines[i].length;
        }
        assert(consumed > 0);
    }

    assert(curved_text_layout(sample, CURVED_TEXT_RIGHT, 410, 8,
                              fixed_width, (void *)&width, lines,
                              CURVED_TEXT_MAX_LINES, &count));
    assert(count > 1);
    assert(lines[0].x >= 325 && lines[0].x <= 525);
    assert(lines[0].y >= 40 && lines[count - 1].y <= 440);
}

static void test_input_bounds(void)
{
    const int32_t width = 8;
    CurvedTextLine lines[2];
    size_t count = 0;
    assert(!curved_text_layout("some words", CURVED_TEXT_LEFT, 410, 8,
                               fixed_width, (void *)&width, lines, 0, &count));
    assert(curved_text_layout("", CURVED_TEXT_LEFT, 410, 8,
                              fixed_width, (void *)&width, lines, 2, &count));
    assert(count == 0);
}

int main(void)
{
    test_circle_band_geometry();
    test_input_bounds();
    return 0;
}
