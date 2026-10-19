#include "bitmap_font_render.h"

#include <windows.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { WIDTH = 640, HEIGHT = 480, FONT_HEIGHT = 12, GLYPH_WIDTH = 8 };

static uint8_t font_bytes[16 + 256 * 4 + 4 + FONT_HEIGHT * GLYPH_WIDTH];

static void write_u32_le(uint8_t *out, uint32_t value)
{
    out[0] = (uint8_t)value;
    out[1] = (uint8_t)(value >> 8);
    out[2] = (uint8_t)(value >> 16);
    out[3] = (uint8_t)(value >> 24);
}

static void initialize_font(BitmapFont *font)
{
    uint32_t glyph;
    uint32_t table_end = 16 + 256 * 4;
    uint32_t glyph_offset = table_end;
    font_bytes[0] = '1';
    font_bytes[1] = '.';
    write_u32_le(font_bytes + 4, 256);
    write_u32_le(font_bytes + 8, FONT_HEIGHT);
    write_u32_le(font_bytes + 12, GLYPH_WIDTH);
    for (glyph = 0; glyph < 256; ++glyph)
        write_u32_le(font_bytes + 16 + (size_t)glyph * 4, glyph_offset);
    write_u32_le(font_bytes + glyph_offset, GLYPH_WIDTH);
    for (glyph = 0; glyph < FONT_HEIGHT * GLYPH_WIDTH; ++glyph)
        font_bytes[glyph_offset + 4 + glyph] = (uint8_t)(glyph % 3U != 0U);
    font->bytes = font_bytes;
    font->length = sizeof(font_bytes);
    font->glyph_count = 256;
    font->height = FONT_HEIGHT;
    font->max_glyph_width = GLYPH_WIDTH;
}

static size_t render_setpixel(HDC dc, const BitmapFont *font, const char *text,
                              int x, int y, COLORREF color)
{
    const unsigned char *cursor = (const unsigned char *)text;
    size_t count = 0;
    while (*cursor != '\0') {
        uint32_t width;
        const uint8_t *pixels;
        if (bitmap_font_get_glyph(font, *cursor, &width, &pixels)) {
            uint32_t row;
            uint32_t col;
            for (row = 0; row < font->height; ++row) {
                for (col = 0; col < width; ++col) {
                    if (pixels[(size_t)row * width + col] == 1U) {
                        (void)SetPixelV(dc, x + (int)col, y + (int)row, color);
                        ++count;
                    }
                }
            }
            x += (int)width;
        }
        ++cursor;
    }
    return count;
}

static double elapsed_ms(LARGE_INTEGER start, LARGE_INTEGER end,
                         LARGE_INTEGER frequency)
{
    return 1000.0 * (double)(end.QuadPart - start.QuadPart) /
           (double)frequency.QuadPart;
}

int main(int argc, char **argv)
{
    static const char text[] = "TASK CONSTRUCTION REPAIR RESOURCES";
    BitmapFont font;
    BITMAPINFO info;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    HDC dc;
    HBITMAP bitmap;
    HGDIOBJ old_bitmap;
    uint32_t *pixels = NULL;
    uint32_t *expected_pixels;
    int pixels_equal;
    uint32_t iterations = argc > 1 ? (uint32_t)strtoul(argv[1], NULL, 10) : 500U;
    uint32_t iteration;
    size_t api_pixels = 0;
    size_t direct_pixels = 0;
    if (iterations == 0U) return 2;
    initialize_font(&font);
    memset(&info, 0, sizeof(info));
    info.bmiHeader.biSize = sizeof(info.bmiHeader);
    info.bmiHeader.biWidth = WIDTH;
    info.bmiHeader.biHeight = -HEIGHT;
    info.bmiHeader.biPlanes = 1;
    info.bmiHeader.biBitCount = 32;
    info.bmiHeader.biCompression = BI_RGB;
    dc = CreateCompatibleDC(NULL);
    if (dc == NULL) return 3;
    bitmap = CreateDIBSection(dc, &info, DIB_RGB_COLORS,
                              (void **)&pixels, NULL, 0);
    if (bitmap == NULL || pixels == NULL) return 4;
    expected_pixels = (uint32_t *)malloc((size_t)WIDTH * HEIGHT * sizeof(uint32_t));
    if (expected_pixels == NULL) return 6;
    old_bitmap = SelectObject(dc, bitmap);
    QueryPerformanceFrequency(&frequency);

    QueryPerformanceCounter(&start);
    for (iteration = 0; iteration < iterations; ++iteration)
        api_pixels += render_setpixel(dc, &font, text, 24, 32, RGB(185, 205, 220));
    (void)GdiFlush();
    QueryPerformanceCounter(&end);
    {
        double api_ms = elapsed_ms(start, end, frequency);
        double direct_ms;
        memcpy(expected_pixels, pixels,
               (size_t)WIDTH * HEIGHT * sizeof(uint32_t));

        QueryPerformanceCounter(&start);
        for (iteration = 0; iteration < iterations; ++iteration) {
            direct_pixels += bitmap_font_render_pixels(&font, text, pixels,
                WIDTH, HEIGHT, WIDTH, 24, 32, UINT32_C(0x00b9cddc));
        }
        QueryPerformanceCounter(&end);
        direct_ms = elapsed_ms(start, end, frequency);
        pixels_equal = memcmp(expected_pixels, pixels,
                              (size_t)WIDTH * HEIGHT * sizeof(uint32_t)) == 0;
        printf("iterations=%lu setpixel_ms=%.3f direct_ms=%.3f speedup=%.2fx pixels_equal=%s setpixel_calls=%llu direct_stores=%llu\n",
               (unsigned long)iterations, api_ms, direct_ms,
               api_ms / direct_ms,
               pixels_equal ? "yes" : "no",
               (unsigned long long)api_pixels,
               (unsigned long long)direct_pixels);
    }

    free(expected_pixels);
    (void)SelectObject(dc, old_bitmap);
    DeleteObject(bitmap);
    DeleteDC(dc);
    return api_pixels == direct_pixels && pixels_equal ? 0 : 5;
}
