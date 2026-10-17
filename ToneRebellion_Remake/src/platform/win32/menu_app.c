#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>

#include "cob_archive.h"
#include "shp_image.h"
#include "world_map.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mmsystem.h>

enum { LOGICAL_WIDTH = 640, LOGICAL_HEIGHT = 480 };
enum { SCREEN_MAIN_MENU, SCREEN_NEW_GAME, SCREEN_WORLD_MAP, SCREEN_LOAD_GAME };

typedef struct SpriteFrame {
    HBITMAP bitmap;
    int width;
    int height;
    int x_offset;
    int y_offset;
} SpriteFrame;

typedef struct SpriteSheet {
    SpriteFrame *frames;
    uint32_t frame_count;
} SpriteSheet;

typedef struct MenuState {
    WorldMap world_map;
    int world_index;
    int difficulty;
    int selected_tribe;
    int setup_accepted;
    int screen;
    unsigned animation_ticks;
} MenuState;

static MenuState g_menu;
static SpriteSheet g_title_art;
static SpriteSheet g_new_background;
static SpriteSheet g_new_buttons;
static SpriteSheet g_glyphs;
static SpriteSheet g_realm_art;
static SpriteSheet g_big_floaters;
static SpriteSheet g_difficulty_art;
static SpriteSheet g_map_background;
static SpriteSheet g_small_islands;
static SpriteSheet g_load_save_art;
static COLORREF g_newgame_palette[256];
static COLORREF g_map_palette[256];
static uint32_t g_random_state;
static unsigned char *g_button_sound;
static HFONT g_menu_font;

static const int g_difficulty_count = 5;

static void update_window_title(HWND window)
{
    const char *title = "Tone Rebellion - Title";
    if (g_menu.screen == SCREEN_NEW_GAME) title = "Tone Rebellion - New Game";
    else if (g_menu.screen == SCREEN_WORLD_MAP) title = "Tone Rebellion - World Map (Esc: setup, Left/Right: size)";
    else if (g_menu.screen == SCREEN_LOAD_GAME) title = "Tone Rebellion - Load Game (Esc: back)";
    SetWindowTextA(window, title);
}

static int load_palette(CobArchive *archive, const char *member_name,
                        COLORREF palette[256], char *error, size_t error_capacity)
{
    const CobMember *member = cob_archive_find(archive, member_name);
    unsigned char bytes[768];
    size_t i;
    if (member == NULL || member->length != sizeof(bytes) ||
        !cob_archive_read_member(archive, member, bytes, sizeof(bytes), error, error_capacity)) {
        if (member == NULL) {
            (void)snprintf(error, error_capacity, "%s was not found in TONE01.COB", member_name);
        } else if (member->length != sizeof(bytes)) {
            (void)snprintf(error, error_capacity, "%s has an unexpected palette size", member_name);
        }
        return 0;
    }
    for (i = 0; i < 256; ++i) {
        unsigned r = bytes[i * 3] > 63 ? 255u : (unsigned)bytes[i * 3] * 255u / 63u;
        unsigned g = bytes[i * 3 + 1] > 63 ? 255u : (unsigned)bytes[i * 3 + 1] * 255u / 63u;
        unsigned b = bytes[i * 3 + 2] > 63 ? 255u : (unsigned)bytes[i * 3 + 2] * 255u / 63u;
        palette[i] = RGB(r, g, b);
    }
    return 1;
}

static int load_sprite_sheet(CobArchive *archive, const char *member_name,
                             const COLORREF palette[256], SpriteSheet *sheet,
                             char *error, size_t error_capacity)
{
    const CobMember *member = cob_archive_find(archive, member_name);
    unsigned char *bytes;
    ShpFile source;
    uint32_t frame_index;
    if (member == NULL) {
        (void)snprintf(error, error_capacity, "%s was not found in TONE01.COB", member_name);
        return 0;
    }
    bytes = (unsigned char *)malloc(member->length == 0 ? 1 : member->length);
    if (bytes == NULL || !cob_archive_read_member(archive, member, bytes, member->length,
                                                   error, error_capacity)) {
        free(bytes);
        return 0;
    }
    if (!shp_file_init(&source, bytes, member->length, error, error_capacity)) {
        free(bytes);
        return 0;
    }
    sheet->frames = (SpriteFrame *)calloc(source.frame_count, sizeof(*sheet->frames));
    if (sheet->frames == NULL) {
        free(bytes);
        (void)snprintf(error, error_capacity, "could not allocate sprite frame table");
        return 0;
    }
    sheet->frame_count = source.frame_count;
    for (frame_index = 0; frame_index < source.frame_count; ++frame_index) {
        ShpFrame decoded;
        BITMAPINFO info;
        void *bitmap_bits = NULL;
        HBITMAP bitmap;
        size_t p;
        if (!shp_decode_frame(&source, frame_index, &decoded, error, error_capacity)) {
            free(bytes);
            return 0;
        }
        ZeroMemory(&info, sizeof(info));
        info.bmiHeader.biSize = sizeof(info.bmiHeader);
        info.bmiHeader.biWidth = (LONG)decoded.width;
        info.bmiHeader.biHeight = -(LONG)decoded.height;
        info.bmiHeader.biPlanes = 1;
        info.bmiHeader.biBitCount = 32;
        info.bmiHeader.biCompression = BI_RGB;
        bitmap = CreateDIBSection(NULL, &info, DIB_RGB_COLORS, &bitmap_bits, NULL, 0);
        if (bitmap == NULL || bitmap_bits == NULL) {
            if (bitmap != NULL) DeleteObject(bitmap);
            shp_frame_free(&decoded);
            free(bytes);
            (void)snprintf(error, error_capacity, "could not create a GDI sprite bitmap");
            return 0;
        }
        for (p = 0; p < (size_t)decoded.width * decoded.height; ++p) {
            DWORD *pixel = (DWORD *)bitmap_bits + p;
            COLORREF color = palette[decoded.pixels[p]];
            if (decoded.opaque[p]) {
                *pixel = 0xff000000u | ((DWORD)GetRValue(color) << 16) |
                         ((DWORD)GetGValue(color) << 8) | (DWORD)GetBValue(color);
            } else {
                *pixel = 0;
            }
        }
        sheet->frames[frame_index].bitmap = bitmap;
        sheet->frames[frame_index].width = (int)decoded.width;
        sheet->frames[frame_index].height = (int)decoded.height;
        sheet->frames[frame_index].x_offset = decoded.x_offset;
        sheet->frames[frame_index].y_offset = decoded.y_offset;
        shp_frame_free(&decoded);
    }
    free(bytes);
    return 1;
}

static void free_sprite_sheet(SpriteSheet *sheet)
{
    uint32_t i;
    if (sheet->frames != NULL) {
        for (i = 0; i < sheet->frame_count; ++i) {
            if (sheet->frames[i].bitmap != NULL) DeleteObject(sheet->frames[i].bitmap);
        }
        free(sheet->frames);
    }
    memset(sheet, 0, sizeof(*sheet));
}

static void draw_sprite(HDC target, const SpriteSheet *sheet, uint32_t frame_index,
                        int x, int y)
{
    HDC source;
    HGDIOBJ previous;
    BLENDFUNCTION blend = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
    const SpriteFrame *frame;
    if (sheet == NULL || frame_index >= sheet->frame_count) return;
    frame = &sheet->frames[frame_index];
    if (frame->bitmap == NULL) return;
    source = CreateCompatibleDC(target);
    if (source == NULL) return;
    previous = SelectObject(source, frame->bitmap);
    (void)AlphaBlend(target, x + frame->x_offset, y + frame->y_offset,
                     frame->width, frame->height, source, 0, 0,
                     frame->width, frame->height, blend);
    SelectObject(source, previous);
    DeleteDC(source);
}

static void fill_rect(HDC dc, int left, int top, int right, int bottom, COLORREF color)
{
    RECT rect = {left, top, right, bottom};
    HBRUSH brush = CreateSolidBrush(color);
    FillRect(dc, &rect, brush);
    DeleteObject(brush);
}

static void draw_menu_label(HDC dc, const wchar_t *text, int left, int top,
                            int right, int bottom)
{
    RECT rect = {left, top, right, bottom};
    HGDIOBJ previous_font = NULL;
    COLORREF previous_color;
    int previous_background;
    if (g_menu_font != NULL) previous_font = SelectObject(dc, g_menu_font);
    previous_color = SetTextColor(dc, RGB(238, 221, 166));
    previous_background = SetBkMode(dc, TRANSPARENT);
    DrawTextW(dc, text, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
    SetBkMode(dc, previous_background);
    SetTextColor(dc, previous_color);
    if (previous_font != NULL) SelectObject(dc, previous_font);
}

/* FUN_00474b90 is the game's 15-bit MSVC-style LCG. The original seeds it
   from QueryPerformanceCounter before entering the message loop. */
static unsigned game_random(void)
{
    g_random_state = g_random_state * 0x343fdu + 0x269ec3u;
    return (g_random_state >> 16) & 0x7fffu;
}

static int logical_viewport(int client_width, int client_height, RECT *viewport)
{
    if (client_width <= 0 || client_height <= 0 || viewport == NULL) return 0;
    if ((int64_t)client_width * LOGICAL_HEIGHT <=
        (int64_t)client_height * LOGICAL_WIDTH) {
        viewport->left = 0;
        viewport->right = client_width;
        viewport->top = (client_height - client_width * LOGICAL_HEIGHT / LOGICAL_WIDTH) / 2;
        viewport->bottom = viewport->top + client_width * LOGICAL_HEIGHT / LOGICAL_WIDTH;
    } else {
        viewport->top = 0;
        viewport->bottom = client_height;
        viewport->left = (client_width - client_height * LOGICAL_WIDTH / LOGICAL_HEIGHT) / 2;
        viewport->right = viewport->left + client_height * LOGICAL_WIDTH / LOGICAL_HEIGHT;
    }
    return viewport->right > viewport->left && viewport->bottom > viewport->top;
}

static void render_main_menu(HDC dc)
{
    fill_rect(dc, 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT, RGB(0, 0, 0));
    draw_sprite(dc, &g_title_art, 0, 0, 0);
    draw_sprite(dc, &g_title_art, 2, 262, 269);
    draw_sprite(dc, &g_title_art, 4, 99, 337);
    draw_sprite(dc, &g_title_art, 6, 402, 337);
    draw_sprite(dc, &g_title_art, 8, 255, 407);
}

static void render_new_game(HDC dc)
{
    static const POINT tribe_centers[4] = {{170, 240}, {320, 90}, {470, 240}, {320, 390}};
    static const int orbit_radii[3] = {150, 170, 130};
    int tribe;
    int ring;
    int angle_step;
    fill_rect(dc, 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT, RGB(0, 0, 0));
    draw_sprite(dc, &g_new_background, 0, 0, 0);
    for (ring = 0; ring < 3; ++ring) {
        const int radius = orbit_radii[ring];
        COLORREF color = g_newgame_palette[0];
        for (angle_step = 2; angle_step < 16; ++angle_step) {
            float angle = (float)(angle_step * 5) * 0.017453292f;
            int dx = (int)(sin((double)angle) * radius);
            int dy = (int)(cos((double)angle) * radius);
            const int xs[4] = {315 + dx, 315 - dx, 315 - dx, 315 + dx};
            const int ys[4] = {236 + dy, 236 + dy, 236 - dy, 236 - dy};
            int quadrant;
            for (quadrant = 0; quadrant < 4; ++quadrant) {
                RECT dot = {xs[quadrant], ys[quadrant], xs[quadrant] + 10, ys[quadrant] + 8};
                HBRUSH brush = CreateSolidBrush(color);
                FillRect(dc, &dot, brush);
                DeleteObject(brush);
            }
            /* The original emits ten randomized pixels for each quadrant,
               using FUN_00474b90's LCG. Its palette byte is 0xb6..0xc6. */
            if (ring <= g_menu.world_index) {
                int speck;
                for (speck = 0; speck < 10; ++speck) {
                    int side;
                    for (side = 0; side < 4; ++side) {
                        int sx;
                        int sy;
                        unsigned color = game_random() % 17u + 0xb6u;
                        unsigned y_jitter = game_random() % 6u;
                        unsigned x_jitter = game_random() % 7u;
                        sx = (side == 0 || side == 3 ? 325 + dx : 325 - dx) - (int)x_jitter;
                        sy = (side < 2 ? 244 + dy : 244 - dy) - (int)y_jitter;
                        SetPixelV(dc, sx, sy, g_newgame_palette[color]);
                    }
                }
            }
        }
    }
    draw_sprite(dc, &g_new_buttons, 0, 0, 0);
    draw_sprite(dc, &g_new_buttons, 1, 7, 423);
    draw_sprite(dc, &g_new_buttons, 3, 76, 423);
    draw_sprite(dc, &g_new_buttons, 5, 143, 443);
    draw_sprite(dc, &g_new_buttons, 7, 196, 445);
    draw_sprite(dc, &g_new_buttons, 9, 391, 441);
    draw_sprite(dc, &g_new_buttons, 11, 444, 440);
    draw_sprite(dc, &g_new_buttons, 13, 495, 420);
    draw_sprite(dc, &g_new_buttons, 15, 564, 419);
    /* FUN_0044ec5d registers these named text controls for the button panes. */
    draw_menu_label(dc, L"Quitter", 7, 405, 75, 423);
    draw_menu_label(dc, L"Monde", 76, 405, 142, 423);
    draw_menu_label(dc, L"Tarks", 143, 425, 195, 443);
    draw_menu_label(dc, L"Zygons", 196, 425, 250, 443);
    draw_menu_label(dc, L"Céphéens", 391, 422, 443, 440);
    draw_menu_label(dc, L"Dyla", 444, 421, 494, 439);
    draw_menu_label(dc, L"Difficulté", 495, 402, 562, 420);
    draw_menu_label(dc, L"Jouer", 564, 401, 633, 419);
    draw_sprite(dc, &g_realm_art, (uint32_t)g_menu.selected_tribe, 60, 40);
    draw_sprite(dc, &g_realm_art,
                (uint32_t)((g_menu.selected_tribe + 1) % 4), 140, 40);
    draw_sprite(dc, &g_difficulty_art, (uint32_t)g_menu.difficulty, 320, 240);
    {
        uint32_t tribe_frame = (uint32_t)(g_menu.selected_tribe * 17);
        uint32_t animation_frame = tribe_frame + ((g_menu.animation_ticks / 2u) % 16u) + 1u;
        unsigned game_tick = g_menu.animation_ticks / 2u;
        int floater_y = 38 + (int)(sin((double)(game_tick % 24u) *
                                       0.261799388) * 5.0) -
                        (g_menu.selected_tribe == 3 ? 5 : 0);
        /* FUN_0044ec5d draws the tribe's base frame and a cycling overlay
           frame at the same point; drawing only the overlay loses half of
           the original floater artwork. */
        draw_sprite(dc, &g_big_floaters, tribe_frame, 530, floater_y);
        draw_sprite(dc, &g_big_floaters, animation_frame, 530, floater_y);
    }
    for (tribe = 0; tribe < 4; ++tribe) {
        draw_sprite(dc, &g_glyphs,
                    (uint32_t)(tribe * 20 + (g_menu.animation_ticks / 3u) % 20u),
                    tribe_centers[tribe].x, tribe_centers[tribe].y);
    }
}

/* The x87 helpers called by FUN_00471536 continue past Ghidra's short
   function boundaries: static disassembly shows FCOS at 0x477ad2 and FSIN at
   0x477332. The constructor supplies the two scale factors used here. */
static void render_world_map(HDC dc)
{
    const WorldDefinition *world;
    const float scale_x = 0.12999999523162842f; /* 0x3e051eb8 */
    const float scale_y = 0.06000000238418579f; /* 0x3d75c28f */
    size_t island_index;

    fill_rect(dc, 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT, RGB(0, 0, 0));
    draw_sprite(dc, &g_map_background, 0, 0, 0);
    if (g_menu.world_index < 0 || g_menu.world_index >= g_menu.world_map.world_count) return;
    world = &g_menu.world_map.worlds[g_menu.world_index];
    /* WorldWindow display type 1 (FUN_00471b74) renders explicit bridge pairs
       as animated palette-color pixels. Draw these before the islands so the
       island sprites cover the bridge endpoints. */
    {
        BYTE bridge_colors[8];
        int ramp;
        for (ramp = 0; ramp < 8; ++ramp) {
            int red = (5 + ramp * 7) * 255 / 63;
            int green = (5 + ramp * 2) * 255 / 63;
            int blue = (45 + ramp * 2) * 255 / 63;
            int best_index = 0;
            unsigned best_distance = 0xffffffffu;
            int palette_index;
            for (palette_index = 0; palette_index < 255; ++palette_index) {
                int dr = red - (int)GetRValue(g_map_palette[palette_index]);
                int dg = green - (int)GetGValue(g_map_palette[palette_index]);
                int db = blue - (int)GetBValue(g_map_palette[palette_index]);
                unsigned distance = (unsigned)(dr * dr + dg * dg + db * db);
                if (distance < best_distance) {
                    best_distance = distance;
                    best_index = palette_index;
                }
            }
            bridge_colors[ramp] = (BYTE)best_index;
        }
        for (size_t bridge_index = 0; bridge_index < world->bridge_count; ++bridge_index) {
            const WorldBridge *bridge = &world->bridges[bridge_index];
            const WorldIsland *a = &world->islands[bridge->island_a];
            const WorldIsland *b = &world->islands[bridge->island_b];
            float angle_a = (float)a->angle_degrees * 0.017453277f;
            float angle_b = (float)b->angle_degrees * 0.017453277f;
            int ax = 320 + (int)(cos((double)angle_a) * a->range * scale_x + 0.5f);
            int ay = 240 - (int)(sin((double)angle_a) * a->range * scale_y +
                                  a->z * scale_y + 0.5f);
            int bx = 320 + (int)(cos((double)angle_b) * b->range * scale_x + 0.5f);
            int by = 240 - (int)(sin((double)angle_b) * b->range * scale_y +
                                  b->z * scale_y + 0.5f);
            int dx = bx - ax;
            int dy = by - ay;
            int length = (int)sqrt((double)dx * dx + (double)dy * dy);
            int step;
            if (ax < 0 || ax >= LOGICAL_WIDTH || bx < 0 || bx >= LOGICAL_WIDTH ||
                ay < 0 || ay >= LOGICAL_HEIGHT || by < 0 || by >= LOGICAL_HEIGHT ||
                length <= 0) {
                continue;
            }
            for (step = 0; step < length; ++step) {
                int center_x = ax + dx * step / length;
                int center_y = ay + dy * step / length;
                int width = step * 20 / length;
                unsigned color = bridge_colors[game_random() % 8u];
                int spark;
                for (spark = 0; spark < 10; ++spark) {
                    unsigned rx = game_random();
                    int x_jitter = (width + 1) / 2 - (int)(rx % (unsigned)(width + 1));
                    int y_jitter = (width + 1) / 2 -
                        (int)(((rx >> 8) % (unsigned)(width + 1)));
                    SetPixelV(dc, center_x + x_jitter, center_y + y_jitter,
                              g_map_palette[color]);
                }
            }
        }
    }
    for (island_index = 0; island_index < world->island_count; ++island_index) {
        const WorldIsland *island = &world->islands[island_index];
        float angle = (float)island->angle_degrees * 0.017453277f;
        float x_delta = (float)(cos((double)angle) * island->range * scale_x);
        float y_delta = (float)(sin((double)angle) * island->range * scale_y);
        float z_delta = (float)island->z * scale_y;
        int x = 320 + (int)(x_delta + 0.5f);
        int y = 240 - (int)(y_delta + z_delta + 0.5f);
        uint32_t frame_base;
        if (island_index < 4) {
            frame_base = island_index == (size_t)g_menu.selected_tribe ? 30u : 0u;
        } else {
            frame_base = 15u;
        }
        uint32_t frame = frame_base + (uint32_t)island->shape_id;
        draw_sprite(dc, &g_small_islands, frame, x, y);
    }
}

static void render_load_game(HDC dc)
{
    fill_rect(dc, 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT, RGB(0, 0, 0));
    /* windows.txt state 4 layers LOADSAVE frame 0 and frame 1 full-screen. */
    draw_sprite(dc, &g_load_save_art, 0, 0, 0);
    draw_sprite(dc, &g_load_save_art, 1, 0, 0);
}
static void paint_window(HWND window)
{
    PAINTSTRUCT paint;
    HDC screen = BeginPaint(window, &paint);
    RECT client;
    GetClientRect(window, &client);
    {
        int width = client.right - client.left;
        int height = client.bottom - client.top;
        RECT viewport;
        HDC back = CreateCompatibleDC(screen);
        HBITMAP bitmap = CreateCompatibleBitmap(screen, LOGICAL_WIDTH, LOGICAL_HEIGHT);
        HGDIOBJ old_bitmap;
        if (back == NULL || bitmap == NULL) {
            if (bitmap != NULL) DeleteObject(bitmap);
            if (back != NULL) DeleteDC(back);
            EndPaint(window, &paint);
            return;
        }
        old_bitmap = SelectObject(back, bitmap);
        if (g_menu.screen == SCREEN_MAIN_MENU) {
            render_main_menu(back);
        } else if (g_menu.screen == SCREEN_NEW_GAME) {
            render_new_game(back);
        } else if (g_menu.screen == SCREEN_WORLD_MAP) {
            render_world_map(back);
        } else {
            render_load_game(back);
        }
        if (logical_viewport(width, height, &viewport)) {
            /* Clearing the whole client before each StretchBlt exposed a black
               frame on every animated paint. Only clear the letterbox bars. */
            if (viewport.top > 0) {
                RECT bar = {client.left, client.top, client.right, viewport.top};
                FillRect(screen, &bar, (HBRUSH)GetStockObject(BLACK_BRUSH));
            }
            if (viewport.bottom < height) {
                RECT bar = {client.left, viewport.bottom, client.right, client.bottom};
                FillRect(screen, &bar, (HBRUSH)GetStockObject(BLACK_BRUSH));
            }
            if (viewport.left > 0) {
                RECT bar = {client.left, viewport.top, viewport.left, viewport.bottom};
                FillRect(screen, &bar, (HBRUSH)GetStockObject(BLACK_BRUSH));
            }
            if (viewport.right < width) {
                RECT bar = {viewport.right, viewport.top, client.right, viewport.bottom};
                FillRect(screen, &bar, (HBRUSH)GetStockObject(BLACK_BRUSH));
            }
            SetStretchBltMode(screen, HALFTONE);
            StretchBlt(screen, viewport.left, viewport.top,
                       viewport.right - viewport.left, viewport.bottom - viewport.top,
                       back, 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT, SRCCOPY);
        }
        SelectObject(back, old_bitmap);
        DeleteObject(bitmap);
        DeleteDC(back);
    }
    EndPaint(window, &paint);
}

static void handle_click(HWND window, int x, int y)
{
    if (g_button_sound != NULL) {
        (void)PlaySoundA((LPCSTR)g_button_sound, NULL,
                        SND_MEMORY | SND_ASYNC | SND_NODEFAULT);
    }
    if (g_menu.screen == SCREEN_MAIN_MENU) {
        if (y >= 337 && y <= 399 && x >= 99 && x <= 240) {
            g_menu.screen = SCREEN_NEW_GAME;
            g_menu.setup_accepted = 0;
        } else if (y >= 337 && y <= 399 && x >= 402 && x <= 540) {
            g_menu.screen = SCREEN_LOAD_GAME;
        } else if (y >= 407 && y <= 469 && x >= 255 && x <= 375) {
            PostMessageA(window, WM_CLOSE, 0, 0);
        }
    } else if (g_menu.screen == SCREEN_NEW_GAME && y >= 423 && y <= 465 && x >= 7 && x <= 75) {
        g_menu.screen = SCREEN_MAIN_MENU;
        g_menu.setup_accepted = 0;
    } else if (g_menu.screen == SCREEN_NEW_GAME && y >= 423 && y <= 464 && x >= 76 && x <= 142) {
        g_menu.world_index = (g_menu.world_index + 1) % g_menu.world_map.world_count;
        g_menu.setup_accepted = 0;
    } else if (g_menu.screen == SCREEN_NEW_GAME && y >= 443 && y <= 476 && x >= 143 && x <= 195) {
        g_menu.selected_tribe = 0;
        g_menu.setup_accepted = 0;
    } else if (g_menu.screen == SCREEN_NEW_GAME && y >= 443 && y <= 476 && x >= 196 && x <= 250) {
        g_menu.selected_tribe = 1;
        g_menu.setup_accepted = 0;
    } else if (g_menu.screen == SCREEN_NEW_GAME && y >= 441 && y <= 474 && x >= 391 && x <= 443) {
        g_menu.selected_tribe = 2;
        g_menu.setup_accepted = 0;
    } else if (g_menu.screen == SCREEN_NEW_GAME && y >= 440 && y <= 476 && x >= 444 && x <= 494) {
        g_menu.selected_tribe = 3;
        g_menu.setup_accepted = 0;
    } else if (g_menu.screen == SCREEN_NEW_GAME && y >= 420 && y <= 464 && x >= 495 && x <= 562) {
        g_menu.difficulty = (g_menu.difficulty + 1) % g_difficulty_count;
        g_menu.setup_accepted = 0;
    } else if (g_menu.screen == SCREEN_NEW_GAME && y >= 419 && y <= 464 && x >= 564 && x <= 633) {
        g_menu.setup_accepted = 1;
        g_menu.screen = SCREEN_WORLD_MAP;
    }
    update_window_title(window);
    InvalidateRect(window, NULL, FALSE);
}

static LRESULT CALLBACK menu_window_proc(HWND window, UINT message,
                                          WPARAM wparam, LPARAM lparam)
{
    switch (message) {
    case WM_PAINT:
        paint_window(window);
        return 0;
    case WM_ERASEBKGND:
        return 1;
    case WM_TIMER:
        if (wparam == 1 && g_menu.screen == SCREEN_NEW_GAME) {
            ++g_menu.animation_ticks;
            InvalidateRect(window, NULL, FALSE);
        }
        return 0;
    case WM_LBUTTONUP: {
        RECT client;
        RECT viewport;
        int width;
        int height;
        int x;
        int y;
        GetClientRect(window, &client);
        width = client.right - client.left;
        height = client.bottom - client.top;
        if (!logical_viewport(width, height, &viewport)) return 0;
        if (GET_X_LPARAM(lparam) < viewport.left || GET_X_LPARAM(lparam) >= viewport.right ||
            GET_Y_LPARAM(lparam) < viewport.top || GET_Y_LPARAM(lparam) >= viewport.bottom) {
            return 0;
        }
        x = ((GET_X_LPARAM(lparam) - viewport.left) * LOGICAL_WIDTH) /
            (viewport.right - viewport.left);
        y = ((GET_Y_LPARAM(lparam) - viewport.top) * LOGICAL_HEIGHT) /
            (viewport.bottom - viewport.top);
        handle_click(window, x, y);
        return 0;
    }
    case WM_KEYDOWN:
        if (wparam == VK_ESCAPE) {
            if (g_menu.screen == SCREEN_LOAD_GAME) {
                g_menu.screen = SCREEN_MAIN_MENU;
                InvalidateRect(window, NULL, FALSE);
            } else if (g_menu.screen == SCREEN_WORLD_MAP) {
                g_menu.screen = SCREEN_NEW_GAME;
                g_menu.setup_accepted = 0;
                InvalidateRect(window, NULL, FALSE);
            } else if (g_menu.screen == SCREEN_NEW_GAME) {
                g_menu.screen = SCREEN_MAIN_MENU;
                g_menu.setup_accepted = 0;
                InvalidateRect(window, NULL, FALSE);
            } else {
                PostMessageA(window, WM_CLOSE, 0, 0);
            }
        } else if (wparam == VK_RETURN) {
            if (g_menu.screen == SCREEN_MAIN_MENU) {
                g_menu.screen = SCREEN_NEW_GAME;
            } else if (g_menu.screen == SCREEN_NEW_GAME) {
                g_menu.setup_accepted = 1;
                g_menu.screen = SCREEN_WORLD_MAP;
            } else if (g_menu.screen == SCREEN_LOAD_GAME) {
                g_menu.screen = SCREEN_MAIN_MENU;
            } else {
                g_menu.screen = SCREEN_NEW_GAME;
            }
            InvalidateRect(window, NULL, FALSE);
        } else if (g_menu.screen == SCREEN_MAIN_MENU && wparam == 'N') {
            g_menu.screen = SCREEN_NEW_GAME;
            InvalidateRect(window, NULL, FALSE);
        } else if (g_menu.screen == SCREEN_MAIN_MENU && wparam == 'L') {
            g_menu.screen = SCREEN_LOAD_GAME;
            InvalidateRect(window, NULL, FALSE);
        } else if (g_menu.screen == SCREEN_WORLD_MAP &&
                   (wparam == VK_LEFT || wparam == VK_RIGHT)) {
            const int count = g_menu.world_map.world_count;
            g_menu.world_index = (g_menu.world_index + count +
                (wparam == VK_RIGHT ? 1 : -1)) % count;
            InvalidateRect(window, NULL, FALSE);
        } else if (g_menu.screen == SCREEN_NEW_GAME &&
                   (wparam == VK_LEFT || wparam == VK_RIGHT)) {
            const int count = g_menu.world_map.world_count;
            g_menu.world_index = (g_menu.world_index + count +
                (wparam == VK_RIGHT ? 1 : -1)) % count;
            g_menu.setup_accepted = 0;
            InvalidateRect(window, NULL, FALSE);
        } else if (g_menu.screen == SCREEN_NEW_GAME && wparam == 'D') {
            g_menu.difficulty = (g_menu.difficulty + 1) % g_difficulty_count;
            g_menu.setup_accepted = 0;
            InvalidateRect(window, NULL, FALSE);
        } else if (g_menu.screen == SCREEN_NEW_GAME && wparam >= '1' && wparam <= '4') {
            g_menu.selected_tribe = (int)(wparam - '1');
            g_menu.setup_accepted = 0;
            InvalidateRect(window, NULL, FALSE);
        }
        update_window_title(window);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProcA(window, message, wparam, lparam);
    }
}

static int load_world_map(char *error, size_t error_capacity)
{
    CobArchive archive = {0};
    const CobMember *member;
    unsigned char *data;
    const char *archive_path = "C:\\Program Files\\Tone\\TONE01.COB";
    int success;
    if (!cob_archive_open(archive_path, &archive, error, error_capacity)) {
        return 0;
    }
    member = cob_archive_find(&archive, "data\\worldpos.txt");
    if (member == NULL) {
        (void)snprintf(error, error_capacity, "data\\worldpos.txt was not found in TONE01.COB");
        cob_archive_close(&archive);
        return 0;
    }
    data = (unsigned char *)malloc(member->length == 0 ? 1 : member->length);
    if (data == NULL) {
        (void)snprintf(error, error_capacity, "could not allocate world table buffer");
        cob_archive_close(&archive);
        return 0;
    }
    success = cob_archive_read_member(&archive, member, data, member->length,
                                      error, error_capacity) &&
              world_map_load_data(data, member->length, &g_menu.world_map,
                                  error, error_capacity);
    free(data);
    cob_archive_close(&archive);
    return success;
}

static int load_menu_art(char *error, size_t error_capacity)
{
    CobArchive archive = {0};
    COLORREF title_palette[256];
    COLORREF newgame_palette[256];
    COLORREF mainmap_palette[256];
    const char *path = "C:\\Program Files\\Tone\\TONE01.COB";
    int success = 0;
    if (!cob_archive_open(path, &archive, error, error_capacity)) return 0;
    if (!load_palette(&archive, "data\\titscrn.pal", title_palette, error, error_capacity) ||
        !load_palette(&archive, "data\\newgame.pal", newgame_palette, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\titscrn.shp", title_palette,
                           &g_title_art, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\loadsav0.shp", title_palette,
                           &g_load_save_art, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\newback.shp", newgame_palette,
                           &g_new_background, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\ngmeintr.shp", newgame_palette,
                           &g_new_buttons, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\glyphs.shp", newgame_palette,
                           &g_glyphs, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\ngrealms.shp", newgame_palette,
                           &g_realm_art, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\bigfloat.shp", newgame_palette,
                           &g_big_floaters, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\levidif.shp", newgame_palette,
                           &g_difficulty_art, error, error_capacity) ||
        !load_palette(&archive, "data\\mainmap.pal", mainmap_palette, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\mapback.shp", mainmap_palette,
                           &g_map_background, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\smisle.shp", mainmap_palette,
                           &g_small_islands, error, error_capacity)) {
        goto done;
    }
    {
        const CobMember *button = cob_archive_find(&archive, "data\\button.wav");
        if (button != NULL && button->length >= 44) {
            g_button_sound = (unsigned char *)malloc(button->length);
            if (g_button_sound == NULL ||
                !cob_archive_read_member(&archive, button, g_button_sound,
                                         button->length, error, error_capacity)) {
                free(g_button_sound);
                g_button_sound = NULL;
            }
        }
    }
    memcpy(g_newgame_palette, newgame_palette, sizeof(g_newgame_palette));
    memcpy(g_map_palette, mainmap_palette, sizeof(g_map_palette));
    success = 1;
done:
    cob_archive_close(&archive);
    if (!success) {
        free_sprite_sheet(&g_title_art);
        free_sprite_sheet(&g_new_background);
        free_sprite_sheet(&g_new_buttons);
        free_sprite_sheet(&g_glyphs);
        free_sprite_sheet(&g_realm_art);
        free_sprite_sheet(&g_big_floaters);
        free_sprite_sheet(&g_difficulty_art);
        free_sprite_sheet(&g_map_background);
        free_sprite_sheet(&g_small_islands);
        free_sprite_sheet(&g_load_save_art);
    }
    return success;
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous_instance,
                   LPSTR command_line, int show_command)
{
    WNDCLASSA window_class;
    HWND window;
    MSG message;
    char error[256];
    (void)previous_instance;
    (void)command_line;

    if (!load_world_map(error, sizeof(error)) || !load_menu_art(error, sizeof(error))) {
        MessageBoxA(NULL, error, "Tone Rebellion remake - data error", MB_OK | MB_ICONERROR);
        return 1;
    }
    g_menu.world_index = 0;
    g_menu.difficulty = 0;
    g_menu.selected_tribe = 0;
    g_menu_font = CreateFontW(-10, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                              DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                              ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
    {
        LARGE_INTEGER seed;
        QueryPerformanceCounter(&seed);
        g_random_state = (uint32_t)seed.LowPart;
    }

    memset(&window_class, 0, sizeof(window_class));
    window_class.lpfnWndProc = menu_window_proc;
    window_class.hInstance = instance;
    window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
    window_class.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    window_class.lpszClassName = "ToneRebellionRemakeMenu";
    if (!RegisterClassA(&window_class)) {
        MessageBoxA(NULL, "Could not register the menu window class.",
                    "Tone Rebellion remake", MB_OK | MB_ICONERROR);
        return 1;
    }
    window = CreateWindowExA(0, window_class.lpszClassName,
                             "Tone Rebellion - New Game",
                             WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                             1040, 820, NULL, NULL, instance, NULL);
    if (window == NULL) {
        MessageBoxA(NULL, "Could not create the menu window.",
                    "Tone Rebellion remake", MB_OK | MB_ICONERROR);
        return 1;
    }
    update_window_title(window);
    (void)SetTimer(window, 1, 33, NULL);
    ShowWindow(window, show_command);
    UpdateWindow(window);
    while (GetMessageA(&message, NULL, 0, 0) > 0) {
        TranslateMessage(&message);
        DispatchMessageA(&message);
    }
    free_sprite_sheet(&g_title_art);
    free_sprite_sheet(&g_new_background);
    free_sprite_sheet(&g_new_buttons);
    free_sprite_sheet(&g_glyphs);
    free_sprite_sheet(&g_realm_art);
    free_sprite_sheet(&g_big_floaters);
    free_sprite_sheet(&g_difficulty_art);
    free_sprite_sheet(&g_map_background);
    free_sprite_sheet(&g_small_islands);
    free_sprite_sheet(&g_load_save_art);
    (void)PlaySoundA(NULL, NULL, 0);
    if (g_menu_font != NULL) DeleteObject(g_menu_font);
    free(g_button_sound);
    return (int)message.wParam;
}
