#include "curved_text_layout.h"
#include "cob_archive.h"
#include "font_image.h"
#include "island_panel_info.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int32_t fixed_width(void *context, const char *text, size_t length)
{
    int32_t glyph_width = *(const int32_t *)context;
    size_t i;
    int32_t width = 0;
    for (i = 0; i < length; ++i) width += text[i] == ' ' ? glyph_width / 2 : glyph_width;
    return width;
}

static unsigned char *read_file(const char *path, size_t *length)
{
    FILE *file = fopen(path, "rb");
    long file_length;
    unsigned char *bytes;
    if (file == NULL || fseek(file, 0, SEEK_END) != 0 ||
        (file_length = ftell(file)) < 0 || fseek(file, 0, SEEK_SET) != 0) {
        if (file != NULL) fclose(file);
        return NULL;
    }
    bytes = (unsigned char *)malloc(file_length == 0 ? 1u : (size_t)file_length);
    if (bytes == NULL || fread(bytes, 1, (size_t)file_length, file) !=
                             (size_t)file_length) {
        free(bytes);
        fclose(file);
        return NULL;
    }
    fclose(file);
    *length = (size_t)file_length;
    return bytes;
}

static int32_t measure_curved_font(void *context, const char *text, size_t length)
{
    enum { CURVED_HEIGHT = 11 };
    const BitmapFont *font = (const BitmapFont *)context;
    int32_t width = 0;
    size_t i;
    for (i = 0; i < length; ++i) {
        uint32_t glyph_width;
        const uint8_t *pixels;
        uint32_t code = (unsigned char)text[i];
        uint32_t scaled_width;
        if (code >= font->glyph_count) code = (uint32_t)'?';
        if (!bitmap_font_get_glyph(font, code, &glyph_width, &pixels)) continue;
        scaled_width = (glyph_width * CURVED_HEIGHT + font->height / 2u) /
                       font->height;
        width += (int32_t)(scaled_width == 0 ? 1 : scaled_width);
    }
    return width;
}

static void test_original_description_bytes(const unsigned char *font_bytes,
                                           size_t font_length,
                                           const unsigned char *text_bytes,
                                           size_t text_length)
{
    static const char *const keys[8] = {
        "PROTECT0", "PROTECT1", "SEEKER0", "SEEKER1",
        "MYSTIC0", "MYSTIC1", "LIFE0", "LIFE1"
    };
    enum { TEXT_CAPACITY = 2048, FOOTER_TOP = 407, CURVED_HEIGHT = 11,
           MIN_FIRST_LINE_Y = 80 };
    BitmapFont font = {0};
    char error[128];
    char text[TEXT_CAPACITY];
    int entry;

    assert(font_bytes != NULL && text_bytes != NULL);
    assert(bitmap_font_init(&font, font_bytes, font_length,
                            error, sizeof(error)));
    for (entry = 0; entry < 8; ++entry) {
        CurvedTextLine lines[CURVED_TEXT_MAX_LINES];
        size_t line_count = 0;
        size_t line;
        CurvedTextSide side = entry % 2 == 0
            ? CURVED_TEXT_LEFT : CURVED_TEXT_RIGHT;
        assert(island_panel_info_extract_entry(text_bytes, text_length,
                                               keys[entry], text,
                                               sizeof(text)));
        assert(curved_text_layout(text, side,
                                  CURVED_TEXT_NEWGAME_LAST_LINE_Y,
                                  CURVED_HEIGHT, measure_curved_font, &font,
                                  lines, CURVED_TEXT_MAX_LINES, &line_count));
        assert(line_count != 0);
        if (lines[0].y < MIN_FIRST_LINE_Y)
            fprintf(stderr, "%s: first line y=%d, lines=%lu\n", keys[entry],
                    (int)lines[0].y, (unsigned long)line_count);
        assert(lines[0].y >= MIN_FIRST_LINE_Y);
        for (line = 0; line < line_count; ++line) {
            int32_t expected_x;
            int32_t expected_width;
            assert(curved_text_bounds(side, lines[line].y,
                                      &expected_x, &expected_width));
            assert(lines[line].x == expected_x &&
                   lines[line].width == expected_width);
            assert(lines[line].y + CURVED_HEIGHT <= FOOTER_TOP);
        }
    }
    bitmap_font_free(&font);
}

static void test_original_descriptions(const char *font_path,
                                      const char *text_path)
{
    unsigned char *font_bytes;
    unsigned char *text_bytes;
    size_t font_length;
    size_t text_length;
    font_bytes = read_file(font_path, &font_length);
    text_bytes = read_file(text_path, &text_length);
    assert(font_bytes != NULL && text_bytes != NULL);
    test_original_description_bytes(font_bytes, font_length,
                                    text_bytes, text_length);
    free(font_bytes);
    free(text_bytes);
}

static void test_original_archives(const char *text_archive_path,
                                   const char *font_archive_path)
{
    CobArchive text_archive = {0};
    CobArchive font_archive = {0};
    const CobMember *text_member;
    const CobMember *font_member;
    unsigned char *text_bytes;
    unsigned char *font_bytes;
    char error[256];

    assert(cob_archive_open(text_archive_path, &text_archive,
                            error, sizeof(error)));
    assert(cob_archive_open(font_archive_path, &font_archive,
                            error, sizeof(error)));
    text_member = cob_archive_find(&text_archive, "newgame.txt");
    font_member = cob_archive_find(&font_archive, "data\\bgoutfnt.fnt");
    assert(text_member != NULL && font_member != NULL);
    text_bytes = (unsigned char *)malloc(text_member->length);
    font_bytes = (unsigned char *)malloc(font_member->length);
    assert(text_bytes != NULL && font_bytes != NULL);
    assert(cob_archive_read_member(&text_archive, text_member, text_bytes,
                                   text_member->length, error, sizeof(error)));
    assert(cob_archive_read_member(&font_archive, font_member, font_bytes,
                                   font_member->length, error, sizeof(error)));
    test_original_description_bytes(font_bytes, font_member->length,
                                    text_bytes, text_member->length);
    free(text_bytes);
    free(font_bytes);
    cob_archive_close(&text_archive);
    cob_archive_close(&font_archive);
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
            int32_t expected_x;
            int32_t expected_width;
            assert(curved_text_bounds(CURVED_TEXT_LEFT, lines[i].y,
                                      &expected_x, &expected_width));
            assert(lines[i].x == expected_x && lines[i].width == expected_width);
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
    {
        size_t i;
        for (i = 0; i < count; ++i) {
            int32_t expected_x;
            int32_t expected_width;
            assert(curved_text_bounds(CURVED_TEXT_RIGHT, lines[i].y,
                                      &expected_x, &expected_width));
            assert(lines[i].x == expected_x && lines[i].width == expected_width);
        }
    }
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

static void test_single_line_ends_at_bottom_target(void)
{
    const int32_t width = 8;
    CurvedTextLine lines[CURVED_TEXT_MAX_LINES];
    size_t count = 0;
    assert(curved_text_layout("one", CURVED_TEXT_LEFT, 410, 8,
                              fixed_width, (void *)&width, lines,
                              CURVED_TEXT_MAX_LINES, &count));
    assert(count == 1);
    assert(lines[0].y == 410);
}

static void test_newgame_text_clears_footer(void)
{
    const int32_t glyph_width = 8;
    const int32_t font_height = 11;
    const int32_t footer_frame_y = 407;
    CurvedTextLine lines[CURVED_TEXT_MAX_LINES];
    size_t count = 0;
    size_t line;
    const char *sample =
        "Tarks the Protectors survived on the new island and fought the Leviathan";
    assert(curved_text_layout(sample, CURVED_TEXT_LEFT,
                              CURVED_TEXT_NEWGAME_LAST_LINE_Y, font_height,
                              fixed_width, (void *)&glyph_width, lines,
                              CURVED_TEXT_MAX_LINES, &count));
    assert(count > 0);
    assert(lines[count - 1].y == CURVED_TEXT_NEWGAME_LAST_LINE_Y);
    for (line = 0; line < count; ++line)
        assert(lines[line].y + font_height <= footer_frame_y);
}

static void test_bottom_anchor_for_nonconverging_paragraphs(void)
{
    const int32_t width = 8;
    CurvedTextLine lines[CURVED_TEXT_MAX_LINES];
    char text[2048];
    size_t count;
    size_t words;
    size_t successful_layouts = 0;
    for (words = 1; words < 100; ++words) {
        size_t length = 0;
        size_t i;
        for (i = 0; i < words; ++i) {
            memcpy(text + length, "words ", 6);
            length += 6;
        }
        text[length - 1] = '\0';
        if (!curved_text_layout(text, CURVED_TEXT_RIGHT, 410, 8,
                                fixed_width, (void *)&width, lines,
                                CURVED_TEXT_MAX_LINES, &count)) continue;
        ++successful_layouts;
        assert(count > 0);
        {
            size_t line;
            for (line = 0; line < count; ++line)
                /* 410 is the remake baseline target; footer art starts below
                   y=430 in the New Game layout. */
                assert(lines[line].y + 8 <= 430);
        }
    }
    assert(successful_layouts >= 40);
}

int main(int argc, char **argv)
{
    assert(argc == 1 || argc == 3 || argc == 4);
    test_circle_band_geometry();
    test_input_bounds();
    test_single_line_ends_at_bottom_target();
    test_newgame_text_clears_footer();
    test_bottom_anchor_for_nonconverging_paragraphs();
    if (argc == 3) test_original_descriptions(argv[1], argv[2]);
    if (argc == 4 && strcmp(argv[1], "--archives") == 0)
        test_original_archives(argv[2], argv[3]);
    else if (argc == 4)
        assert(!"expected --archives <TONE00.COB> <TONE01.COB>");
    return 0;
}
