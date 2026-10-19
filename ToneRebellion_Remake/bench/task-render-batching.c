#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <wingdi.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 640
#define HEIGHT 480
#define ROWS 7
#define BLITS_PER_ROW 3
#define ITERATIONS 3000

typedef struct Surface { HDC dc; HBITMAP bitmap; HGDIOBJ previous; uint32_t *pixels; } Surface;

static int make_surface(HDC reference, int width, int height, Surface *surface)
{
    BITMAPINFO info;
    void *bits = NULL;
    memset(&info, 0, sizeof(info));
    info.bmiHeader.biSize = sizeof(info.bmiHeader);
    info.bmiHeader.biWidth = width;
    info.bmiHeader.biHeight = -height;
    info.bmiHeader.biPlanes = 1;
    info.bmiHeader.biBitCount = 32;
    info.bmiHeader.biCompression = BI_RGB;
    surface->dc = CreateCompatibleDC(reference);
    surface->bitmap = CreateDIBSection(reference, &info, DIB_RGB_COLORS,
                                       &bits, NULL, 0);
    surface->previous = NULL;
    surface->pixels = (uint32_t *)bits;
    if (surface->dc == NULL || surface->bitmap == NULL || bits == NULL) return 0;
    surface->previous = SelectObject(surface->dc, surface->bitmap);
    return surface->previous != NULL && surface->previous != HGDI_ERROR;
}

static void destroy_surface(Surface *surface)
{
    if (surface->dc != NULL && surface->previous != NULL)
        SelectObject(surface->dc, surface->previous);
    if (surface->bitmap != NULL) DeleteObject(surface->bitmap);
    if (surface->dc != NULL) DeleteDC(surface->dc);
}

static void draw_row_blits(HDC target, HDC source, int row)
{
    BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
    int blit;
    for (blit = 0; blit < BLITS_PER_ROW; ++blit) {
        int x = 20 + blit * 24;
        int y = 20 + row * 16;
        AlphaBlend(target, x, y, 20, 12, source, 0, 0, 20, 12, blend);
    }
}

static void draw_row_label(uint32_t *pixels, int row)
{
    int x, y;
    for (y = 0; y < 10; ++y) {
        uint32_t *line = pixels + (size_t)(20 + row * 16 + y) * WIDTH + 100;
        for (x = 0; x < 100; ++x) {
            if (((x * 13 + y * 7 + row) & 3) == 0)
                line[x] = UINT32_C(0xffb9cddc);
        }
    }
}

static double run(Surface *target, HDC source, int batched, uint64_t *checksum)
{
    LARGE_INTEGER frequency, start, finish;
    int iteration, row;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);
    for (iteration = 0; iteration < ITERATIONS; ++iteration) {
        memset(target->pixels, 0, (size_t)WIDTH * HEIGHT * sizeof(uint32_t));
        if (batched) {
            for (row = 0; row < ROWS; ++row) draw_row_blits(target->dc, source, row);
            GdiFlush();
            for (row = 0; row < ROWS; ++row) draw_row_label(target->pixels, row);
        } else {
            for (row = 0; row < ROWS; ++row) {
                draw_row_blits(target->dc, source, row);
                GdiFlush();
                draw_row_label(target->pixels, row);
            }
        }
    }
    GdiFlush();
    QueryPerformanceCounter(&finish);
    *checksum = UINT64_C(1469598103934665603);
    for (row = 0; row < WIDTH * HEIGHT; ++row) {
        *checksum ^= target->pixels[row];
        *checksum *= UINT64_C(1099511628211);
    }
    return (double)(finish.QuadPart - start.QuadPart) * 1000.0 /
           (double)frequency.QuadPart;
}

int main(void)
{
    Surface target = {0}, source = {0};
    uint64_t old_checksum, new_checksum;
    double old_ms, new_ms;
    int i;
    if (!make_surface(NULL, WIDTH, HEIGHT, &target) ||
        !make_surface(NULL, 20, 12, &source)) return 2;
    for (i = 0; i < 20 * 12; ++i) source.pixels[i] = UINT32_C(0xc0a040ff);
    old_ms = run(&target, source.dc, 0, &old_checksum);
    new_ms = run(&target, source.dc, 1, &new_checksum);
    printf("iterations=%d rows=%d blits_per_row=%d old_ms=%.2f batched_ms=%.2f speedup=%.2fx old_flushes=%d new_flushes=%d checksum_equal=%s\n",
           ITERATIONS, ROWS, BLITS_PER_ROW, old_ms, new_ms,
           new_ms > 0.0 ? old_ms / new_ms : 0.0,
           ROWS * ITERATIONS, ITERATIONS,
           old_checksum == new_checksum ? "yes" : "no");
    destroy_surface(&source);
    destroy_surface(&target);
    return old_checksum == new_checksum ? 0 : 3;
}
