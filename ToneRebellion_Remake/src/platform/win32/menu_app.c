#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>

#include "cob_archive.h"
#include "font_image.h"
#include "island_data.h"
#include "island_haze.h"
#include "island_render_rules.h"
#include "curved_text_layout.h"
#include "shp_image.h"
#include "window_catalog.h"
#include "world_map.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mmsystem.h>

enum { LOGICAL_WIDTH = 640, LOGICAL_HEIGHT = 480, ISLAND_NAME_COUNT = 15 };
enum { SCREEN_MAIN_MENU, SCREEN_NEW_GAME, SCREEN_WORLD_MAP, SCREEN_ISLAND, SCREEN_LOAD_GAME };
enum { HELP_MAIN_NEWGAME, HELP_MAIN_RESUME, HELP_MAIN_LOAD, HELP_MAIN_EXIT,
       HELP_NEW_EXIT, HELP_NEW_WORLD, HELP_NEW_TRIBE0,
       HELP_NEW_TRIBE1, HELP_NEW_TRIBE2, HELP_NEW_TRIBE3, HELP_NEW_DIFFICULTY,
       HELP_NEW_BEGIN, HELP_ENTRY_COUNT };

typedef struct SpriteFrame {
    HBITMAP bitmap;
    int width;
    int height;
    int x_offset;
    int y_offset;
    int hit_left;
    int hit_top;
    int hit_right;
    int hit_bottom;
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
    int selected_map_island;
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
static SpriteSheet g_island_surface_art;
static SpriteSheet g_island_template_art;
static SpriteSheet g_tone_field_art;
static SpriteSheet g_pad_art;
static SpriteSheet g_bridge_trigger_art;
static SpriteSheet g_island_feature_art;
static SpriteSheet g_island_names_art;
static SpriteSheet g_load_save_art;
static SpriteSheet g_newgame_captions;
static SpriteSheet g_tribe_descriptions;
static SpriteSheet g_menu_help;
static COLORREF g_newgame_palette[256];
static COLORREF g_map_palette[256];
static uint32_t g_random_state;
static unsigned char *g_button_sound;
static BitmapFont g_bitmap_font;
static char g_help_text[HELP_ENTRY_COUNT][1024];
static char g_newgame_text[8][256];
static char g_tribe_text[4][2][1024];
static char g_island_names[ISLAND_NAME_COUNT][32];
static IslandData g_island_surface_data;
static WindowCatalog g_window_catalog;
static uint16_t g_island_draw_order[ISLAND_DATA_MAX_LOCATIONS];
static IslandHaze g_island_haze;
static unsigned char *g_island_height_data;
static size_t g_island_height_length;
static int g_island_surface_id = -1;
static int g_island_scroll_x;
static int g_hovered_location = -1;
static int g_selected_location = -1;
static int g_resume_available;
static unsigned char g_load_slot_valid[8];
static int g_hovered_help = -1;
static int g_hovered_newgame_text = -1;
static int g_hovered_island = -1;
static int g_mouse_inside;
static int g_mouse_x;
static int g_mouse_y;

static const int g_difficulty_count = 5;
static void update_window_title(HWND window)
{
    const char *title = "Tone Rebellion - Title";
    if (g_menu.screen == SCREEN_NEW_GAME) title = "Tone Rebellion - New Game";
    else if (g_menu.screen == SCREEN_WORLD_MAP) title = "Tone Rebellion - World Map (Esc: setup, Left/Right: size)";
    else if (g_menu.screen == SCREEN_ISLAND)
        title = "Tone Rebellion - Island (arrows: scroll, Esc: map)";
    else if (g_menu.screen == SCREEN_LOAD_GAME) title = "Tone Rebellion - Load Game (Esc: back)";
    SetWindowTextA(window, title);
}

static int load_palette(CobArchive *archive, const char *member_name,
                        COLORREF palette[256], uint8_t palette_rgb6[768],
                        char *error, size_t error_capacity)
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
    if (palette_rgb6 != NULL) memcpy(palette_rgb6, bytes, sizeof(bytes));
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
        int hit_left;
        int hit_top;
        int hit_right = -1;
        int hit_bottom = -1;
        if (!shp_decode_frame(&source, frame_index, &decoded, error, error_capacity)) {
            free(bytes);
            return 0;
        }
        hit_left = (int)decoded.width;
        hit_top = (int)decoded.height;
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
                int pixel_x = (int)(p % decoded.width);
                int pixel_y = (int)(p / decoded.width);
                *pixel = 0xff000000u | ((DWORD)GetRValue(color) << 16) |
                         ((DWORD)GetGValue(color) << 8) | (DWORD)GetBValue(color);
                if (pixel_x < hit_left) hit_left = pixel_x;
                if (pixel_y < hit_top) hit_top = pixel_y;
                if (pixel_x + 1 > hit_right) hit_right = pixel_x + 1;
                if (pixel_y + 1 > hit_bottom) hit_bottom = pixel_y + 1;
            } else {
                *pixel = 0;
            }
        }
        sheet->frames[frame_index].bitmap = bitmap;
        sheet->frames[frame_index].width = (int)decoded.width;
        sheet->frames[frame_index].height = (int)decoded.height;
        sheet->frames[frame_index].x_offset = decoded.x_offset;
        sheet->frames[frame_index].y_offset = decoded.y_offset;
        sheet->frames[frame_index].hit_left = hit_left;
        sheet->frames[frame_index].hit_top = hit_top;
        sheet->frames[frame_index].hit_right = hit_right;
        sheet->frames[frame_index].hit_bottom = hit_bottom;
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

/* FUN_00432940 is the original location comparator: ascending Y coordinate. */
static void build_island_draw_order(void)
{
    uint16_t i;
    for (i = 0; i < g_island_surface_data.location_count; ++i) {
        uint16_t index = i;
        uint16_t j = i;
        while (j > 0 &&
               g_island_surface_data.locations[g_island_draw_order[j - 1]].y >
                   g_island_surface_data.locations[index].y) {
            g_island_draw_order[j] = g_island_draw_order[j - 1];
            --j;
        }
        g_island_draw_order[j] = index;
    }
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

static void draw_sprite_region(HDC target, const SpriteSheet *sheet, uint32_t frame_index,
                               int source_x, int source_y, int width, int height,
                               int destination_x, int destination_y)
{
    HDC source;
    HGDIOBJ previous;
    BLENDFUNCTION blend = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
    const SpriteFrame *frame;
    if (sheet == NULL || frame_index >= sheet->frame_count || width <= 0 || height <= 0) return;
    frame = &sheet->frames[frame_index];
    if (frame->bitmap == NULL || source_x < 0 || source_y < 0 ||
        source_x + width > frame->width || source_y + height > frame->height) return;
    source = CreateCompatibleDC(target);
    if (source == NULL) return;
    previous = SelectObject(source, frame->bitmap);
    (void)AlphaBlend(target, destination_x, destination_y, width, height,
                     source, source_x, source_y, width, height, blend);
    SelectObject(source, previous);
    DeleteDC(source);
}

static int load_island_surface(int island_id, char *error, size_t error_capacity)
{
    static const uint8_t feature_frame_counts[ISLAND_NAME_COUNT] = {
        5, 3, 3, 2, 3, 3, 3, 3, 3, 3, 3, 4, 3, 3, 1
    };
    CobArchive archive = {0};
    SpriteSheet candidate = {0};
    SpriteSheet template_candidate = {0};
    SpriteSheet tone_candidate = {0};
    SpriteSheet pad_candidate = {0};
    SpriteSheet bridge_candidate = {0};
    SpriteSheet feature_candidate = {0};
    COLORREF palette[256];
    uint8_t palette_rgb6[ISLAND_HAZE_PALETTE_BYTES];
    IslandData parsed;
    IslandHaze haze_candidate;
    unsigned char *height_data = NULL;
    unsigned char *text_data = NULL;
    const CobMember *height_member;
    const CobMember *text_member;
    char shape_name[48];
    char palette_name[48];
    char height_name[48];
    char text_name[48];
    char feature_name[48];
    const char *archive_path = "C:\\Program Files\\Tone\\TONE01.COB";
    int success = 0;

    if (island_id < 0 || island_id >= ISLAND_NAME_COUNT) {
        (void)snprintf(error, error_capacity, "island id is out of the supported range");
        return 0;
    }
    (void)snprintf(shape_name, sizeof(shape_name), "data\\island%02d.shp", island_id);
    (void)snprintf(palette_name, sizeof(palette_name), "data\\island%02d.pal", island_id);
    (void)snprintf(height_name, sizeof(height_name), "data\\island%02d.hzt", island_id);
    (void)snprintf(text_name, sizeof(text_name), "data\\island%02d.txt", island_id);
    (void)snprintf(feature_name, sizeof(feature_name), "data\\i%02d-feat.shp", island_id);
    if (!cob_archive_open(archive_path, &archive, error, error_capacity)) return 0;
    if (!load_palette(&archive, palette_name, palette, palette_rgb6,
                      error, error_capacity) ||
        !load_sprite_sheet(&archive, shape_name, palette, &candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\isletmp0.shp", palette,
                           &template_candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\tone.shp", palette, &tone_candidate,
                           error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\pad.shp", palette, &pad_candidate,
                           error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\br-trg01.shp", palette, &bridge_candidate,
                           error, error_capacity) ||
        !load_sprite_sheet(&archive, feature_name, palette, &feature_candidate,
                           error, error_capacity)) {
        goto done;
    }
    if (template_candidate.frame_count != 1 ||
        template_candidate.frames[0].width != LOGICAL_WIDTH ||
        template_candidate.frames[0].height != 160) {
        (void)snprintf(error, error_capacity,
                       "data\\isletmp0.shp does not match the 640x160 ISLETEMP pane");
        goto done;
    }
    if (pad_candidate.frame_count != 27) {
        (void)snprintf(error, error_capacity,
                       "data\\pad.shp does not contain the 27 frames used by the pad renderer");
        goto done;
    }
    if (tone_candidate.frame_count != 40) {
        (void)snprintf(error, error_capacity,
                       "data\\tone.shp does not contain the 40 POOL frames from bldinf.txt");
        goto done;
    }
    if (bridge_candidate.frame_count != 23) {
        (void)snprintf(error, error_capacity,
                       "data\\br-trg01.shp does not contain its 23 declared animation frames");
        goto done;
    }
    if (candidate.frame_count != 1 || candidate.frames[0].width != 2560 ||
        candidate.frames[0].height != 320) {
        (void)snprintf(error, error_capacity,
                       "%s does not contain the expected 2560x320 island panorama", shape_name);
        goto done;
    }
    if (feature_candidate.frame_count != feature_frame_counts[island_id]) {
        (void)snprintf(error, error_capacity,
                       "%s has an unexpected island feature frame count", feature_name);
        goto done;
    }
    height_member = cob_archive_find(&archive, height_name);
    text_member = cob_archive_find(&archive, text_name);
    if (height_member == NULL || text_member == NULL) {
        (void)snprintf(error, error_capacity, "island height or location member is missing");
        goto done;
    }
    if (height_member->length != ISLAND_HAZE_FILE_BYTES) {
        (void)snprintf(error, error_capacity, "%s has an unexpected HZT length", height_name);
        goto done;
    }
    height_data = (unsigned char *)malloc(height_member->length == 0 ? 1 : height_member->length);
    text_data = (unsigned char *)malloc(text_member->length == 0 ? 1 : text_member->length);
    if (height_data == NULL || text_data == NULL ||
        !cob_archive_read_member(&archive, height_member, height_data, height_member->length,
                                error, error_capacity) ||
        !cob_archive_read_member(&archive, text_member, text_data, text_member->length,
                                error, error_capacity) ||
        !island_haze_load(height_data, height_member->length, palette_rgb6,
                          &haze_candidate, error, error_capacity) ||
        !island_data_load(text_data, text_member->length, &parsed, error, error_capacity)) {
        goto done;
    }

    free_sprite_sheet(&g_island_surface_art);
    free_sprite_sheet(&g_island_template_art);
    free_sprite_sheet(&g_tone_field_art);
    free_sprite_sheet(&g_pad_art);
    free_sprite_sheet(&g_bridge_trigger_art);
    free_sprite_sheet(&g_island_feature_art);
    free(g_island_height_data);
    g_island_surface_art = candidate;
    memset(&candidate, 0, sizeof(candidate));
    g_island_template_art = template_candidate;
    memset(&template_candidate, 0, sizeof(template_candidate));
    g_tone_field_art = tone_candidate;
    memset(&tone_candidate, 0, sizeof(tone_candidate));
    g_pad_art = pad_candidate;
    memset(&pad_candidate, 0, sizeof(pad_candidate));
    g_bridge_trigger_art = bridge_candidate;
    memset(&bridge_candidate, 0, sizeof(bridge_candidate));
    g_island_feature_art = feature_candidate;
    memset(&feature_candidate, 0, sizeof(feature_candidate));
    g_island_height_data = height_data;
    g_island_height_length = height_member->length;
    height_data = NULL;
    g_island_surface_data = parsed;
    build_island_draw_order();
    g_island_haze = haze_candidate;
    g_island_surface_id = island_id;
    g_island_scroll_x = 0;
    g_selected_location = -1;
    g_hovered_location = -1;
    success = 1;
done:
    free_sprite_sheet(&candidate);
    free_sprite_sheet(&template_candidate);
    free_sprite_sheet(&tone_candidate);
    free_sprite_sheet(&pad_candidate);
    free_sprite_sheet(&bridge_candidate);
    free_sprite_sheet(&feature_candidate);
    free(height_data);
    free(text_data);
    cob_archive_close(&archive);
    return success;
}

static int update_hover_help(int x, int y)
{
    int help = -1;
    if (g_menu.screen == SCREEN_MAIN_MENU) {
        const WindowTemplate *control = window_catalog_hit_test(&g_window_catalog, 0, x, y);
        if (control != NULL && strcmp(control->name, "NEWGAME") == 0) help = HELP_MAIN_NEWGAME;
        else if (control != NULL && strcmp(control->name, "RESUME") == 0 && g_resume_available)
            help = HELP_MAIN_RESUME;
        else if (control != NULL && strcmp(control->name, "LOADGAME") == 0) help = HELP_MAIN_LOAD;
        else if (control != NULL && strcmp(control->name, "EXITAPP") == 0) help = HELP_MAIN_EXIT;
    }
    if (help == g_hovered_help) return 0;
    g_hovered_help = help;
    return 1;
}

static int tribe_icon_at(int x, int y)
{
    static const POINT centers[4] = {{170, 240}, {320, 90}, {470, 240}, {320, 390}};
    int tribe;
    for (tribe = 0; tribe < 4; ++tribe) {
        int dx = x - centers[tribe].x;
        int dy = y - centers[tribe].y;
        if (dx * dx + dy * dy < 2500) return tribe;
    }
    return -1;
}

static int newgame_text_index_at(int x, int y)
{
    int tribe = tribe_icon_at(x, y);
    const WindowTemplate *control;
    if (tribe >= 0) return tribe;
    {
        int dx = x - 320;
        int dy = y - 240;
        int distance_squared = dx * dx + dy * dy;
        if (distance_squared < 100) return 4;
        if (distance_squared < 200) return 5;
    }
    control = window_catalog_hit_test(&g_window_catalog, 1, x, y);
    if (control == NULL) return -1;
    if (strcmp(control->message_destination, "WINMGR") == 0 &&
        control->send_message[0] == 1 && control->send_message[1] == 0) return 6;
    if (strcmp(control->message_destination, "MASTER") != 0) return -1;
    if (control->send_message[0] == 52) return 7;
    if (control->send_message[0] == 53) return 5;
    if (control->send_message[0] == 55) return 4;
    if (control->send_message[0] >= 60 && control->send_message[0] <= 63)
        return control->send_message[0] - 60;
    return -1;
}

static int update_newgame_text(int x, int y)
{
    int text_index = g_menu.screen == SCREEN_NEW_GAME ? newgame_text_index_at(x, y) : -1;
    if (text_index == g_hovered_newgame_text) return 0;
    g_hovered_newgame_text = text_index;
    return 1;
}

static void draw_hover_help(HDC dc)
{
    if (g_menu.screen != SCREEN_MAIN_MENU || !g_mouse_inside || g_hovered_help < 0 ||
        (uint32_t)g_hovered_help >= g_menu_help.frame_count) return;
    /* Keep contextual help away from the title buttons and their baked-in
       captions. Anchoring it to the pointer covered the active control. */
    draw_sprite(dc, &g_menu_help, (uint32_t)g_hovered_help,
                12, 12);
}

static void draw_newgame_text(HDC dc)
{
    if (g_menu.screen != SCREEN_NEW_GAME || !g_mouse_inside ||
        g_hovered_newgame_text < 0 || g_hovered_newgame_text >= 8) return;
    draw_sprite(dc, &g_newgame_captions, (uint32_t)g_hovered_newgame_text, 160, 430);
}

static void draw_tribe_descriptions(HDC dc)
{
    int left_index;
    int right_index;
    if (g_menu.screen != SCREEN_NEW_GAME || g_menu.selected_tribe < 0 ||
        g_menu.selected_tribe >= 4) return;
    left_index = g_menu.selected_tribe * 2;
    right_index = left_index + 1;
    if ((uint32_t)right_index >= g_tribe_descriptions.frame_count) return;
    draw_sprite(dc, &g_tribe_descriptions, (uint32_t)left_index, 0, 0);
    draw_sprite(dc, &g_tribe_descriptions, (uint32_t)right_index, 0, 0);
}

static void fill_rect(HDC dc, int left, int top, int right, int bottom, COLORREF color)
{
    RECT rect = {left, top, right, bottom};
    HBRUSH brush = CreateSolidBrush(color);
    FillRect(dc, &rect, brush);
    DeleteObject(brush);
}

static void draw_bitmap_text_at(DWORD *pixels, int surface_width, int surface_height,
                                const char *text, int x, int y, DWORD ink)
{
    const unsigned char *cursor = (const unsigned char *)text;
    while (*cursor != 0) {
        uint32_t glyph_width;
        const uint8_t *glyph_pixels;
        uint32_t code = *cursor < g_bitmap_font.glyph_count ? *cursor : (uint32_t)'?';
        uint32_t row;
        if (bitmap_font_get_glyph(&g_bitmap_font, code, &glyph_width, &glyph_pixels)) {
            uint32_t col;
            for (row = 0; row < g_bitmap_font.height; ++row) {
                for (col = 0; col < glyph_width; ++col) {
                    /* BGOUTFNT masks distinguish ink (1), background (0),
                       and transparent padding (0xff). Treating zero as ink
                       filled each glyph's entire bounding box. */
                    if (glyph_pixels[(size_t)row * glyph_width + col] == 1u) {
                        int px = x + (int)col;
                        int py = y + (int)row;
                        if (px >= 0 && px < surface_width && py >= 0 && py < surface_height) {
                            pixels[(size_t)py * (size_t)surface_width + (size_t)px] = ink;
                        }
                    }
                }
            }
            x += (int)glyph_width;
        }
        ++cursor;
    }
}

static int32_t measure_bitmap_text(void *context, const char *text, size_t length)
{
    size_t i;
    int32_t width = 0;
    (void)context;
    for (i = 0; i < length; ++i) {
        uint32_t glyph_width;
        const uint8_t *glyph_pixels;
        uint32_t code = (unsigned char)text[i];
        if (code >= g_bitmap_font.glyph_count) code = (uint32_t)'?';
        if (bitmap_font_get_glyph(&g_bitmap_font, code, &glyph_width, &glyph_pixels))
            width += (int32_t)glyph_width;
    }
    return width;
}

static void draw_justified_bitmap_line(DWORD *pixels, int surface_width,
                                       int surface_height, const char *text,
                                       const CurvedTextLine *line, DWORD ink)
{
    char word[1024];
    size_t cursor = line->offset;
    size_t end = line->offset + line->length;
    size_t space_count = 0;
    size_t i;
    size_t remainder;
    int32_t text_width;
    int32_t extra;
    int32_t per_space;
    int32_t single_space_width = measure_bitmap_text(NULL, " ", 1);
    int x = line->x;
    for (i = cursor; i < end; ++i) if (text[i] == ' ') ++space_count;
    text_width = measure_bitmap_text(NULL, text + cursor, end - cursor);
    extra = line->width - text_width;
    if (extra < 0) extra = 0;
    if (space_count == 0) {
        size_t length = end - cursor;
        if (length >= sizeof(word)) length = sizeof(word) - 1;
        memcpy(word, text + cursor, length);
        word[length] = '\0';
        draw_bitmap_text_at(pixels, surface_width, surface_height, word,
                            x, line->y, ink);
        return;
    }
    per_space = extra / (int32_t)space_count;
    remainder = (size_t)(extra - per_space * (int32_t)space_count);
    while (cursor < end) {
        size_t word_end = cursor;
        size_t word_length;
        int32_t word_width;
        while (word_end < end && text[word_end] != ' ') ++word_end;
        word_length = word_end - cursor;
        if (word_length >= sizeof(word)) word_length = sizeof(word) - 1;
        memcpy(word, text + cursor, word_length);
        word[word_length] = '\0';
        draw_bitmap_text_at(pixels, surface_width, surface_height, word,
                            x, line->y, ink);
        word_width = measure_bitmap_text(NULL, word, word_length);
        x += word_width;
        if (word_end < end) {
            x += single_space_width + per_space;
            if (remainder != 0) {
                ++x;
                --remainder;
            }
        }
        cursor = word_end + 1;
    }
}

static int extract_help_entry(const unsigned char *bytes, size_t length,
                              const char *key, char *output, size_t output_capacity)
{
    size_t cursor = 0;
    size_t key_length = strlen(key);
    while (cursor < length) {
        size_t line_start = cursor;
        size_t line_end;
        while (cursor < length && bytes[cursor] != '\n') ++cursor;
        line_end = cursor;
        if (line_end > line_start && bytes[line_end - 1] == '\r') --line_end;
        if (line_end - line_start == key_length &&
            memcmp(bytes + line_start, key, key_length) == 0) {
            size_t used = 0;
            if (cursor < length) ++cursor;
            while (cursor < length) {
                size_t text_start = cursor;
                size_t text_end;
                size_t count;
                while (cursor < length && bytes[cursor] != '\n') ++cursor;
                text_end = cursor;
                if (text_end > text_start && bytes[text_end - 1] == '\r') --text_end;
                if (text_end - text_start >= 3 &&
                    memcmp(bytes + text_start, "END", 3) == 0) {
                    output[used] = '\0';
                    return used != 0;
                }
                count = text_end - text_start;
                while (count > 0 && (bytes[text_start] == ' ' || bytes[text_start] == '\t')) {
                    ++text_start;
                    --count;
                }
                while (count > 0 && (bytes[text_start + count - 1] == ' ' ||
                                     bytes[text_start + count - 1] == '\t')) --count;
                if (count != 0) {
                    if (used != 0 && used + 1 < output_capacity) output[used++] = ' ';
                    if (count >= output_capacity - used) count = output_capacity - used - 1;
                    memcpy(output + used, bytes + text_start, count);
                    used += count;
                }
                if (cursor < length) ++cursor;
            }
            break;
        }
        if (cursor < length) ++cursor;
    }
    if (output_capacity != 0) output[0] = '\0';
    return 0;
}

static int load_menu_help(char *error, size_t error_capacity)
{
    static const char *keys[HELP_ENTRY_COUNT] = {
        "NEWGAME", "RESUME", "LOADGAME", "EXITAPP",
        "EXITNEWGAME", "WORLDSIZE", "TRIBE0", "TRIBE1", "TRIBE2",
        "TRIBE3", "DIFFICULTY", "BEGINGAME"
    };
    CobArchive archive = {0};
    const CobMember *member;
    unsigned char *bytes;
    int i;
    int success = 0;
    if (!cob_archive_open("C:\\Program Files\\Tone\\TONE00.COB", &archive,
                          error, error_capacity)) return 0;
    member = cob_archive_find(&archive, "tonehelp.txt");
    if (member == NULL) {
        (void)snprintf(error, error_capacity, "tonehelp.txt was not found in TONE00.COB");
        goto done;
    }
    bytes = (unsigned char *)malloc(member->length);
    if (bytes == NULL || !cob_archive_read_member(&archive, member, bytes,
                                                  member->length, error,
                                                  error_capacity)) {
        free(bytes);
        goto done;
    }
    for (i = 0; i < HELP_ENTRY_COUNT; ++i) {
        if (!extract_help_entry(bytes, member->length, keys[i], g_help_text[i],
                                sizeof(g_help_text[i]))) {
            (void)snprintf(error, error_capacity, "help text key %s is missing or empty", keys[i]);
            free(bytes);
            goto done;
        }
    }
    free(bytes);
    success = 1;
done:
    cob_archive_close(&archive);
    return success;
}

static int load_newgame_captions(char *error, size_t error_capacity)
{
    CobArchive archive = {0};
    const CobMember *member;
    unsigned char *bytes = NULL;
    int success = 0;
    int i;
    if (!cob_archive_open("C:\\Program Files\\Tone\\TONE00.COB", &archive,
                          error, error_capacity)) return 0;
    member = cob_archive_find(&archive, "gamey.txt");
    if (member == NULL) {
        (void)snprintf(error, error_capacity, "gamey.txt was not found in TONE00.COB");
        goto done;
    }
    bytes = (unsigned char *)malloc(member->length == 0 ? 1 : member->length);
    if (bytes == NULL || !cob_archive_read_member(&archive, member, bytes, member->length,
                                                   error, error_capacity)) goto done;
    for (i = 0; i < 8; ++i) {
        char key[16];
        (void)snprintf(key, sizeof(key), "NEWGAME%d", i);
        if (!extract_help_entry(bytes, member->length, key, g_newgame_text[i],
                                sizeof(g_newgame_text[i]))) {
            (void)snprintf(error, error_capacity, "gamey.txt key %s is missing or empty", key);
            goto done;
        }
    }
    success = 1;
done:
    free(bytes);
    cob_archive_close(&archive);
    return success;
}

static int load_tribe_descriptions(char *error, size_t error_capacity)
{
    static const char *keys[4][2] = {
        {"PROTECT0", "PROTECT1"}, {"SEEKER0", "SEEKER1"},
        {"MYSTIC0", "MYSTIC1"}, {"LIFE0", "LIFE1"}
    };
    CobArchive archive = {0};
    const CobMember *member;
    unsigned char *bytes = NULL;
    int tribe;
    int part;
    int success = 0;
    if (!cob_archive_open("C:\\Program Files\\Tone\\TONE00.COB", &archive,
                          error, error_capacity)) return 0;
    member = cob_archive_find(&archive, "newgame.txt");
    if (member == NULL) {
        (void)snprintf(error, error_capacity, "newgame.txt was not found in TONE00.COB");
        goto done;
    }
    bytes = (unsigned char *)malloc(member->length == 0 ? 1 : member->length);
    if (bytes == NULL || !cob_archive_read_member(&archive, member, bytes,
                                                  member->length, error,
                                                  error_capacity)) goto done;
    for (tribe = 0; tribe < 4; ++tribe) {
        for (part = 0; part < 2; ++part) {
            if (!extract_help_entry(bytes, member->length, keys[tribe][part],
                                    g_tribe_text[tribe][part],
                                    sizeof(g_tribe_text[tribe][part]))) {
                (void)snprintf(error, error_capacity,
                               "newgame.txt key %s is missing or empty",
                               keys[tribe][part]);
                goto done;
            }
        }
    }
    success = 1;
done:
    free(bytes);
    cob_archive_close(&archive);
    return success;
}

static int parse_island_names(const unsigned char *bytes, size_t length)
{
    size_t cursor = 0;
    int in_island_section = 0;
    int name_count = 0;
    while (cursor < length) {
        size_t line_start = cursor;
        size_t line_end;
        size_t first;
        size_t last;
        while (cursor < length && bytes[cursor] != '\n') ++cursor;
        line_end = cursor;
        if (cursor < length) ++cursor;
        if (line_end > line_start && bytes[line_end - 1] == '\r') --line_end;
        first = line_start;
        last = line_end;
        while (first < last && (bytes[first] == ' ' || bytes[first] == '\t')) ++first;
        while (last > first && (bytes[last - 1] == ' ' || bytes[last - 1] == '\t')) --last;
        if (!in_island_section) {
            static const char section[] = "// Island Names";
            if (last - first >= sizeof(section) - 1 &&
                memcmp(bytes + first, section, sizeof(section) - 1) == 0) {
                in_island_section = 1;
            }
            continue;
        }
        if (first == last || bytes[first] == ';' ||
            (last - first >= 2 && bytes[first] == '/' && bytes[first + 1] == '/')) {
            continue;
        }
        if (name_count >= ISLAND_NAME_COUNT || last - first >= sizeof(g_island_names[0])) {
            return 0;
        }
        memcpy(g_island_names[name_count], bytes + first, last - first);
        g_island_names[name_count][last - first] = '\0';
        ++name_count;
        if (name_count == ISLAND_NAME_COUNT) return 1;
    }
    return 0;
}

static int load_island_names(char *error, size_t error_capacity)
{
    CobArchive archive = {0};
    const CobMember *member;
    unsigned char *bytes = NULL;
    int success = 0;
    if (!cob_archive_open("C:\\Program Files\\Tone\\TONE00.COB", &archive,
                          error, error_capacity)) return 0;
    member = cob_archive_find(&archive, "names.txt");
    if (member == NULL) {
        (void)snprintf(error, error_capacity, "names.txt was not found in TONE00.COB");
        goto done;
    }
    bytes = (unsigned char *)malloc(member->length == 0 ? 1 : member->length);
    if (bytes == NULL || !cob_archive_read_member(&archive, member, bytes, member->length,
                                                  error, error_capacity)) goto done;
    if (!parse_island_names(bytes, member->length)) {
        (void)snprintf(error, error_capacity,
                       "names.txt does not contain the expected 15 island names");
        goto done;
    }
    success = 1;
done:
    free(bytes);
    cob_archive_close(&archive);
    return success;
}

static int create_tribe_description_sheet(SpriteSheet *sheet,
                                          char *error, size_t error_capacity)
{
    enum { TEXT_WIDTH = 640, TEXT_HEIGHT = 480, MAX_LINES = CURVED_TEXT_MAX_LINES };
    COLORREF description_color = g_newgame_palette[0xbf];
    DWORD ink = 0xff000000u | ((DWORD)GetRValue(description_color) << 16) |
                ((DWORD)GetGValue(description_color) << 8) |
                (DWORD)GetBValue(description_color);
    int entry;
    sheet->frames = (SpriteFrame *)calloc(8, sizeof(*sheet->frames));
    if (sheet->frames == NULL) {
        (void)snprintf(error, error_capacity, "could not allocate tribe descriptions");
        return 0;
    }
    sheet->frame_count = 8;
    for (entry = 0; entry < 8; ++entry) {
        const char *text = g_tribe_text[entry / 2][entry % 2];
        CurvedTextLine lines[MAX_LINES];
        size_t line_count = 0;
        BITMAPINFO info;
        void *bitmap_bits = NULL;
        HBITMAP bitmap;
        size_t line;
        if (!curved_text_layout(text,
                                entry % 2 == 0 ? CURVED_TEXT_LEFT : CURVED_TEXT_RIGHT,
                                410, (int32_t)g_bitmap_font.height,
                                measure_bitmap_text, NULL, lines, MAX_LINES,
                                &line_count)) {
            (void)snprintf(error, error_capacity,
                           "could not lay out curved tribe description %d", entry);
            return 0;
        }
        ZeroMemory(&info, sizeof(info));
        info.bmiHeader.biSize = sizeof(info.bmiHeader);
        info.bmiHeader.biWidth = TEXT_WIDTH;
        info.bmiHeader.biHeight = -TEXT_HEIGHT;
        info.bmiHeader.biPlanes = 1;
        info.bmiHeader.biBitCount = 32;
        info.bmiHeader.biCompression = BI_RGB;
        bitmap = CreateDIBSection(NULL, &info, DIB_RGB_COLORS, &bitmap_bits, NULL, 0);
        if (bitmap == NULL || bitmap_bits == NULL) {
            if (bitmap != NULL) DeleteObject(bitmap);
            (void)snprintf(error, error_capacity, "could not create tribe description bitmap");
            return 0;
        }
        memset(bitmap_bits, 0, (size_t)TEXT_WIDTH * TEXT_HEIGHT * sizeof(DWORD));
        for (line = 0; line < line_count; ++line)
            draw_justified_bitmap_line((DWORD *)bitmap_bits, TEXT_WIDTH,
                                       TEXT_HEIGHT, text, &lines[line], ink);
        sheet->frames[entry].bitmap = bitmap;
        sheet->frames[entry].width = TEXT_WIDTH;
        sheet->frames[entry].height = TEXT_HEIGHT;
    }
    return 1;
}

static int create_newgame_caption_sheet(SpriteSheet *sheet,
                                        char *error, size_t error_capacity)
{
    int entry;
    sheet->frames = (SpriteFrame *)calloc(8, sizeof(*sheet->frames));
    if (sheet->frames == NULL) {
        (void)snprintf(error, error_capacity, "could not allocate New Game captions");
        return 0;
    }
    sheet->frame_count = 8;
    for (entry = 0; entry < 8; ++entry) {
        BITMAPINFO info;
        void *bitmap_bits = NULL;
        HBITMAP bitmap;
        int text_width = 0;
        int x = 0;
        const unsigned char *cursor = (const unsigned char *)g_newgame_text[entry];
        while (*cursor != 0) {
            uint32_t glyph_width;
            const uint8_t *glyph_pixels;
            uint32_t code = *cursor < g_bitmap_font.glyph_count ? *cursor : (uint32_t)'?';
            if (bitmap_font_get_glyph(&g_bitmap_font, code, &glyph_width, &glyph_pixels)) {
                text_width += (int)glyph_width;
            }
            ++cursor;
        }
        ZeroMemory(&info, sizeof(info));
        info.bmiHeader.biSize = sizeof(info.bmiHeader);
        info.bmiHeader.biWidth = 320;
        info.bmiHeader.biHeight = -(LONG)g_bitmap_font.height;
        info.bmiHeader.biPlanes = 1;
        info.bmiHeader.biBitCount = 32;
        info.bmiHeader.biCompression = BI_RGB;
        bitmap = CreateDIBSection(NULL, &info, DIB_RGB_COLORS, &bitmap_bits, NULL, 0);
        if (bitmap == NULL || bitmap_bits == NULL) {
            if (bitmap != NULL) DeleteObject(bitmap);
            (void)snprintf(error, error_capacity, "could not create New Game caption bitmap");
            return 0;
        }
        memset(bitmap_bits, 0, (size_t)320 * g_bitmap_font.height * sizeof(DWORD));
        x = (320 - text_width) / 2;
        if (x < 0) x = 0;
        draw_bitmap_text_at((DWORD *)bitmap_bits, 320, (int)g_bitmap_font.height,
                            g_newgame_text[entry], x, 0, 0xffffe88au);
        sheet->frames[entry].bitmap = bitmap;
        sheet->frames[entry].width = 320;
        sheet->frames[entry].height = (int)g_bitmap_font.height;
    }
    return 1;
}

static int create_island_name_sheet(SpriteSheet *sheet,
                                    char *error, size_t error_capacity)
{
    enum { TEXT_WIDTH = 640 };
    int entry;
    sheet->frames = (SpriteFrame *)calloc(ISLAND_NAME_COUNT, sizeof(*sheet->frames));
    if (sheet->frames == NULL) {
        (void)snprintf(error, error_capacity, "could not allocate island-name frames");
        return 0;
    }
    sheet->frame_count = ISLAND_NAME_COUNT;
    for (entry = 0; entry < ISLAND_NAME_COUNT; ++entry) {
        BITMAPINFO info;
        void *bitmap_bits = NULL;
        HBITMAP bitmap;
        int text_width = 0;
        int x;
        const unsigned char *cursor = (const unsigned char *)g_island_names[entry];
        while (*cursor != 0) {
            uint32_t glyph_width;
            const uint8_t *glyph_pixels;
            uint32_t code = *cursor < g_bitmap_font.glyph_count ? *cursor : (uint32_t)'?';
            if (bitmap_font_get_glyph(&g_bitmap_font, code, &glyph_width, &glyph_pixels)) {
                text_width += (int)glyph_width;
            }
            ++cursor;
        }
        ZeroMemory(&info, sizeof(info));
        info.bmiHeader.biSize = sizeof(info.bmiHeader);
        info.bmiHeader.biWidth = TEXT_WIDTH;
        info.bmiHeader.biHeight = -(LONG)g_bitmap_font.height;
        info.bmiHeader.biPlanes = 1;
        info.bmiHeader.biBitCount = 32;
        info.bmiHeader.biCompression = BI_RGB;
        bitmap = CreateDIBSection(NULL, &info, DIB_RGB_COLORS, &bitmap_bits, NULL, 0);
        if (bitmap == NULL || bitmap_bits == NULL) {
            if (bitmap != NULL) DeleteObject(bitmap);
            (void)snprintf(error, error_capacity, "could not create island-name bitmap");
            return 0;
        }
        memset(bitmap_bits, 0, (size_t)TEXT_WIDTH * g_bitmap_font.height * sizeof(DWORD));
        x = (TEXT_WIDTH - text_width) / 2;
        if (x < 0) x = 0;
        draw_bitmap_text_at((DWORD *)bitmap_bits, TEXT_WIDTH, (int)g_bitmap_font.height,
                            g_island_names[entry], x, 0, 0xffe8e8d8u);
        sheet->frames[entry].bitmap = bitmap;
        sheet->frames[entry].width = TEXT_WIDTH;
        sheet->frames[entry].height = (int)g_bitmap_font.height;
    }
    return 1;
}

/* FUN_004489c0 reads a 0x80-byte resume header and enables RESUME only when
   its final dword matches FUN_00457490's 0x378b8 value. */
static int resume_header_is_valid(void)
{
    unsigned char header[0x80];
    FILE *file = fopen("C:\\Program Files\\Tone\\resume.gam", "rb");
    size_t count;
    uint32_t marker;
    if (file == NULL) return 0;
    count = fread(header, 1, sizeof(header), file);
    (void)fclose(file);
    if (count != sizeof(header)) return 0;
    marker = (uint32_t)header[0x7c] | ((uint32_t)header[0x7d] << 8) |
             ((uint32_t)header[0x7e] << 16) | ((uint32_t)header[0x7f] << 24);
    return marker == 0x000378b8u;
}

/* FUN_00458371 scans slots 00.sav through 07.sav. It accepts a slot only
   when the 0x80-byte header has the game's marker and 1.16 version prefix. */
static int save_header_is_valid(const char *path)
{
    unsigned char header[0x80];
    FILE *file = fopen(path, "rb");
    size_t count;
    uint32_t marker;
    if (file == NULL) return 0;
    count = fread(header, 1, sizeof(header), file);
    (void)fclose(file);
    if (count != sizeof(header) || memcmp(header, "1.16", 4) != 0) return 0;
    marker = (uint32_t)header[0x7c] | ((uint32_t)header[0x7d] << 8) |
             ((uint32_t)header[0x7e] << 16) | ((uint32_t)header[0x7f] << 24);
    return marker == 0x000378b8u;
}

static void scan_load_slots(void)
{
    int slot;
    for (slot = 0; slot < 8; ++slot) {
        char path[MAX_PATH];
        (void)snprintf(path, sizeof(path), "C:\\Program Files\\Tone\\%02d.SAV", slot);
        g_load_slot_valid[slot] = (unsigned char)save_header_is_valid(path);
    }
}

static int create_help_sheet(SpriteSheet *sheet, char *error, size_t error_capacity)
{
    int entry;
    sheet->frames = (SpriteFrame *)calloc(HELP_ENTRY_COUNT, sizeof(*sheet->frames));
    if (sheet->frames == NULL) {
        (void)snprintf(error, error_capacity, "could not allocate contextual help frames");
        return 0;
    }
    sheet->frame_count = HELP_ENTRY_COUNT;
    for (entry = 0; entry < HELP_ENTRY_COUNT; ++entry) {
        char lines[16][256];
        const char *text = g_help_text[entry];
        size_t text_length = strlen(text);
        size_t cursor = 0;
        int line_count = 0;
        int height;
        BITMAPINFO info;
        void *bitmap_bits = NULL;
        HBITMAP bitmap;
        int line;
        while (cursor < text_length && line_count < 16) {
            size_t start;
            size_t last_space = SIZE_MAX;
            size_t i;
            int width = 0;
            while (cursor < text_length && text[cursor] == ' ') ++cursor;
            start = cursor;
            for (i = start; i < text_length; ++i) {
                uint32_t glyph_width;
                const uint8_t *glyph_pixels;
                uint32_t code = (unsigned char)text[i];
                if (!bitmap_font_get_glyph(&g_bitmap_font, code, &glyph_width,
                                           &glyph_pixels)) {
                    code = '?';
                    (void)bitmap_font_get_glyph(&g_bitmap_font, code, &glyph_width,
                                                &glyph_pixels);
                }
                if (width + (int)glyph_width > 304 && i > start) break;
                width += (int)glyph_width;
                if (text[i] == ' ') last_space = i;
            }
            if (i < text_length && last_space != SIZE_MAX && last_space >= start) i = last_space;
            if (i == start && i < text_length) ++i;
            {
                size_t count = i - start;
                if (count >= sizeof(lines[line_count])) count = sizeof(lines[line_count]) - 1;
                memcpy(lines[line_count], text + start, count);
                lines[line_count][count] = '\0';
                ++line_count;
            }
            cursor = i;
            while (cursor < text_length && text[cursor] == ' ') ++cursor;
        }
        if (line_count == 0) continue;
        height = 12 + line_count * ((int)g_bitmap_font.height + 2);
        ZeroMemory(&info, sizeof(info));
        info.bmiHeader.biSize = sizeof(info.bmiHeader);
        info.bmiHeader.biWidth = 320;
        info.bmiHeader.biHeight = -height;
        info.bmiHeader.biPlanes = 1;
        info.bmiHeader.biBitCount = 32;
        info.bmiHeader.biCompression = BI_RGB;
        bitmap = CreateDIBSection(NULL, &info, DIB_RGB_COLORS, &bitmap_bits, NULL, 0);
        if (bitmap == NULL || bitmap_bits == NULL) {
            if (bitmap != NULL) DeleteObject(bitmap);
            (void)snprintf(error, error_capacity, "could not create contextual help bitmap");
            return 0;
        }
        memset(bitmap_bits, 0, (size_t)320 * (size_t)height * 4);
        {
            DWORD *surface = (DWORD *)bitmap_bits;
            int x;
            int y;
            const DWORD background = 0xe80b1320u;
            const DWORD border = 0xffe8d79au;
            for (y = 0; y < height; ++y) {
                for (x = 0; x < 320; ++x) {
                    if (x < 2 || x >= 318 || y < 2 || y >= height - 2)
                        surface[(size_t)y * 320 + x] = border;
                    else
                        surface[(size_t)y * 320 + x] = background;
                }
            }
            for (line = 0; line < line_count; ++line) {
                draw_bitmap_text_at(surface, 320, height, lines[line], 8,
                                    6 + line * ((int)g_bitmap_font.height + 2),
                                    0xffe5e7eau);
            }
        }
        sheet->frames[entry].bitmap = bitmap;
        sheet->frames[entry].width = 320;
        sheet->frames[entry].height = height;
    }
    return 1;
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

static int template_is_in_state(const WindowTemplate *window, int state)
{
    size_t i;
    for (i = 0; i < window->state_count; ++i) {
        if (window->states[i] == state) return 1;
    }
    return 0;
}

static int template_help_index(const WindowTemplate *window)
{
    if (strcmp(window->name, "RESUME") == 0) return HELP_MAIN_RESUME;
    if (strcmp(window->name, "NEWGAME") == 0) return HELP_MAIN_NEWGAME;
    if (strcmp(window->name, "LOADGAME") == 0) return HELP_MAIN_LOAD;
    if (strcmp(window->name, "EXITAPP") == 0) return HELP_MAIN_EXIT;
    return -1;
}

static int template_caption_index(const WindowTemplate *window)
{
    if (strcmp(window->message_destination, "WINMGR") == 0 &&
        window->send_message[0] == 1 && window->send_message[1] == 0) return 6;
    if (strcmp(window->message_destination, "MASTER") != 0) return -1;
    if (window->send_message[0] == 52) return 7;
    if (window->send_message[0] == 53) return 5;
    if (window->send_message[0] == 55) return 4;
    if (window->send_message[0] >= 60 && window->send_message[0] <= 63)
        return window->send_message[0] - 60;
    return -1;
}

static void draw_configured_buttons(HDC dc, int state, const char *shape_id,
                                    SpriteSheet *sheet)
{
    size_t i;
    for (i = 0; i < g_window_catalog.count; ++i) {
        const WindowTemplate *window = &g_window_catalog.windows[i];
        int frame;
        if (!template_is_in_state(window, state) ||
            strcmp(window->shape_id, shape_id) != 0 || window->shape_frame < 0) continue;
        frame = window->shape_frame;
        if (state == 0) {
            frame = window_catalog_hover_frame(
                frame, template_help_index(window), g_hovered_help);
        } else if (state == 1) {
            frame = window_catalog_hover_frame(
                frame, template_caption_index(window), g_hovered_newgame_text);
        }
        draw_sprite(dc, sheet, (uint32_t)frame, window->pane.left, window->pane.top);
    }
}

static void render_main_menu(HDC dc)
{
    fill_rect(dc, 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT, RGB(0, 0, 0));
    draw_configured_buttons(dc, 0, "TITSCRN", &g_title_art);
    draw_hover_help(dc);
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
    draw_configured_buttons(dc, 1, "NEWBUTT", &g_new_buttons);
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
    draw_tribe_descriptions(dc);
    draw_hover_help(dc);
    draw_newgame_text(dc);
}

static void world_island_position(const WorldIsland *island, int *x, int *y)
{
    const float scale_x = 0.12999999523162842f;
    const float scale_y = 0.06000000238418579f;
    float angle = (float)island->angle_degrees * 0.017453277f;
    float x_delta = (float)(cos((double)angle) * island->range * scale_x);
    float y_delta = (float)(sin((double)angle) * island->range * scale_y);
    float z_delta = (float)island->z * scale_y;
    *x = 320 + (int)(x_delta + 0.5f);
    *y = 240 - (int)(y_delta + z_delta + 0.5f);
}

static uint32_t world_island_frame_base(size_t island_index)
{
    if (island_index < 4) {
        return island_index == (size_t)g_menu.selected_tribe ? 30u : 0u;
    }
    return 15u;
}

/* FUN_00472013 walks display items back-to-front and checks the opaque SHP
   bounds prepared by FUN_00405e11. The remake uses the same opaque bounds. */
static int world_island_at(int x, int y)
{
    const WorldDefinition *world;
    size_t island_index;
    if (g_menu.world_index < 0 || g_menu.world_index >= g_menu.world_map.world_count) return -1;
    world = &g_menu.world_map.worlds[g_menu.world_index];
    island_index = world->island_count;
    while (island_index > 0) {
        const WorldIsland *island;
        uint32_t frame_index;
        const SpriteFrame *frame;
        int island_x;
        int island_y;
        int left;
        int top;
        int right;
        int bottom;
        --island_index;
        island = &world->islands[island_index];
        frame_index = world_island_frame_base(island_index) + (uint32_t)island->shape_id;
        if (frame_index >= g_small_islands.frame_count) continue;
        frame = &g_small_islands.frames[frame_index];
        if (frame->hit_right <= frame->hit_left || frame->hit_bottom <= frame->hit_top) continue;
        world_island_position(island, &island_x, &island_y);
        left = island_x + frame->x_offset + frame->hit_left;
        top = island_y + frame->y_offset + frame->hit_top;
        right = island_x + frame->x_offset + frame->hit_right;
        bottom = island_y + frame->y_offset + frame->hit_bottom;
        if (left < x && x < right && top < y && y < bottom) return (int)island_index;
    }
    return -1;
}

static int update_world_map_hover(int x, int y)
{
    int island = g_menu.screen == SCREEN_WORLD_MAP ? world_island_at(x, y) : -1;
    if (island == g_hovered_island) return 0;
    g_hovered_island = island;
    return 1;
}

static void draw_bitmap_label(HDC dc, const char *text, int x, int y, COLORREF color)
{
    const unsigned char *cursor = (const unsigned char *)text;
    while (*cursor != '\0') {
        uint32_t code = *cursor < g_bitmap_font.glyph_count ? *cursor : (uint32_t)'?';
        uint32_t glyph_width;
        const uint8_t *glyph_pixels;
        if (bitmap_font_get_glyph(&g_bitmap_font, code, &glyph_width, &glyph_pixels)) {
            uint32_t row;
            uint32_t col;
            for (row = 0; row < g_bitmap_font.height; ++row) {
                for (col = 0; col < glyph_width; ++col) {
                    if (glyph_pixels[(size_t)row * glyph_width + col] == 1u) {
                        int px = x + (int)col;
                        int py = y + (int)row;
                        if (px >= 0 && px < LOGICAL_WIDTH && py >= 0 && py < LOGICAL_HEIGHT) {
                            (void)SetPixelV(dc, px, py, color);
                        }
                    }
                }
            }
            x += (int)glyph_width;
        }
        ++cursor;
    }
}

static int open_island_view(HWND window, int map_island_index)
{
    const WorldDefinition *world;
    int island_id;
    char error[256];
    if (g_menu.world_index < 0 || g_menu.world_index >= g_menu.world_map.world_count) return 0;
    world = &g_menu.world_map.worlds[g_menu.world_index];
    if (map_island_index < 0 || map_island_index >= world->island_count) return 0;
    island_id = world->islands[map_island_index].shape_id;
    if (!load_island_surface(island_id, error, sizeof(error))) {
        MessageBoxA(window, error, "Tone Rebellion remake - island data error",
                    MB_OK | MB_ICONERROR);
        return 0;
    }
    g_menu.selected_map_island = map_island_index;
    g_menu.screen = SCREEN_ISLAND;
    update_window_title(window);
    InvalidateRect(window, NULL, FALSE);
    return 1;
}

static int island_location_at(int x, int y)
{
    int map_x = x + g_island_scroll_x;
    int map_y = y;
    int index = (int)g_island_surface_data.location_count - 1;
    if (x < 0 || x >= LOGICAL_WIDTH || map_y < 0 || map_y >= 320) return -1;
    for (; index >= 0; --index) {
        const IslandLocation *location = &g_island_surface_data.locations[index];
        int dx = map_x - location->x;
        int dy = map_y - location->y;
        if (dx * dx + dy * dy <= 100) return index;
    }
    return -1;
}

static int update_island_location_hover(int x, int y)
{
    int location = g_menu.screen == SCREEN_ISLAND ? island_location_at(x, y) : -1;
    if (location == g_hovered_location) return 0;
    g_hovered_location = location;
    return 1;
}

static COLORREF island_location_color(const char *type)
{
    if (strcmp(type, "tone") == 0) return RGB(255, 202, 68);
    if (strcmp(type, "bridge") == 0) return RGB(61, 218, 248);
    if (strcmp(type, "special") == 0 || strcmp(type, "levhub") == 0) {
        return RGB(238, 95, 218);
    }
    if (strcmp(type, "feature") == 0 || strcmp(type, "feattrig") == 0) {
        return RGB(131, 237, 116);
    }
    return RGB(104, 174, 255);
}

/* Only explicit size tags use PAD.SHP. Class/subtype alone is insufficient:
   Tone pools and Leviathan shields share class-0/subtype-0 in the source. */
static int island_pad_group(const IslandLocation *location)
{
    return island_pad_size_group(location->kind);
}

/* FUN_0040b345 draws feature layers at fixed world coordinates from the
   island-window origin. The object contributes its special-value bits. This
   renders only the static branch (object flag bit 0 clear); triggered and
   altitude-hazed variants depend on live game state. */
static void draw_island_feature(HDC dc, int island_id, const IslandLocation *site,
                                int world_origin_x, int world_origin_y)
{
    const int bit0 = (site->special_value & 1) != 0;
    const int bit1 = (site->special_value & 2) != 0;
    const SpriteSheet *art = &g_island_feature_art;

#define FEATURE_FRAME(frame, dx, dy) \
    do { if ((uint32_t)(frame) < art->frame_count) \
        draw_sprite(dc, art, (uint32_t)(frame), world_origin_x + (dx), \
                    world_origin_y + (dy)); } while (0)

    switch (island_id) {
    case 0:
        FEATURE_FRAME(bit0 ? 2 : 0, 0x6b3, 100);
        FEATURE_FRAME(bit1 ? 3 : 1, 0x6b3, 100);
        break;
    case 1:
        if (bit0) FEATURE_FRAME(0, 0x11a, 0xe9);
        if (bit1) FEATURE_FRAME(1, 0x169, 0xf6);
        break;
    case 2:
        if (bit0) FEATURE_FRAME(0, 0x4c, 0);
        if (bit1) FEATURE_FRAME(1, 0x144, 0);
        break;
    case 3:
        if (bit0 || bit1) FEATURE_FRAME(0, 0x8f, 99);
        break;
    case 4:
        if (bit0) FEATURE_FRAME(0, 0x529, 0x8c);
        if (bit1) FEATURE_FRAME(1, 0x5c2, 0x90);
        break;
    case 5:
        if (bit0) FEATURE_FRAME(0, 0x2d4, 0xd5);
        if (bit1) FEATURE_FRAME(1, 0x33e, 0xd5);
        break;
    case 6:
        if (bit0) FEATURE_FRAME(0, 0x40, 0x6c);
        if (bit1) FEATURE_FRAME(1, 0xa0, 0x69);
        break;
    case 7:
        if (bit0) FEATURE_FRAME(0, 0x8f, 0xa2);
        if (bit1) FEATURE_FRAME(1, 0xf5, 0xa5);
        break;
    case 8:
        if (bit0) FEATURE_FRAME(0, 0x4a1, 0x43);
        if (bit1) FEATURE_FRAME(1, 0x51a, 0x9e);
        break;
    case 9:
        if (bit0) FEATURE_FRAME(0, 0x42a, 0x74);
        if (bit1) FEATURE_FRAME(1, 0x4d6, 0x7f);
        break;
    case 10:
        if (bit0) FEATURE_FRAME(0, 0x421, 0x87);
        if (bit1) FEATURE_FRAME(1, 0x43b, 0x18);
        break;
    case 11:
        FEATURE_FRAME(0, 0x57b, 0xf0);
        if (bit0) FEATURE_FRAME(1, 0x57b, 0xf0);
        if (bit1) FEATURE_FRAME(2, 0x57b, 0xf0);
        break;
    case 12:
        if (bit0) FEATURE_FRAME(0, 0x4e7, 0xa0);
        if (bit1) FEATURE_FRAME(1, 0x4e7, 0xa0);
        break;
    case 13:
        if (bit0 || bit1) FEATURE_FRAME(0, 0x463, 0x82);
        break;
    case 14:
    default:
        break;
    }
#undef FEATURE_FRAME
}

static void render_island_view(HDC dc)
{
    const int image_top = 0;
    const int status_top = 320;
    const IslandLocation *focus = NULL;
    int focus_index = g_hovered_location >= 0 ? g_hovered_location : g_selected_location;
    int saved_dc;
    char text[160];
    uint16_t i;

    fill_rect(dc, 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT, RGB(0, 0, 0));
    if (g_island_height_data == NULL ||
        g_island_height_length != ISLAND_HAZE_FILE_BYTES) {
        draw_sprite(dc, &g_island_template_art, 0, 0, status_top);
        return;
    }
    draw_sprite_region(dc, &g_island_surface_art, 0, g_island_scroll_x, 0,
                       LOGICAL_WIDTH, 320, 0, image_top);

    if (focus_index >= 0 && focus_index < g_island_surface_data.location_count) {
        focus = &g_island_surface_data.locations[focus_index];
    }
    /* windows.txt defines ISLEVIEW as the 640x320 upper pane. Clip sprites to
       that view so tall SHP frames cannot overwrite the ISLETEMP controls. */
    saved_dc = SaveDC(dc);
    (void)IntersectClipRect(dc, 0, 0, LOGICAL_WIDTH, status_top);
    for (i = 0; i < g_island_surface_data.location_count; ++i) {
        const IslandLocation *location =
            &g_island_surface_data.locations[g_island_draw_order[i]];
        int x = (int)location->x - g_island_scroll_x;
        int y = image_top + (int)location->y;
        int pad_group = island_pad_group(location);
        COLORREF color = island_location_color(location->type);
        int dx;
        int dy;
        if (location->renderer_class == 3 &&
            (location->renderer_variant == 4 || location->renderer_variant == 0x16)) {
            draw_island_feature(dc, g_island_surface_id, location,
                                -g_island_scroll_x, image_top);
            continue;
        }
        /* The pad catalog's PIT_Object (item 1) and PIT_FeatureTrigger
           (item 3) entries have no shape asset. These item IDs are distinct
           from an island record's renderer_class. */
        if (location->kind == ISLAND_LOCATION_PAD ||
            (location->renderer_class == 3 && location->renderer_variant == 3)) {
            continue;
        }
        if (x < -4 || x >= LOGICAL_WIDTH + 4) continue;
        /* The original class-2 bridge site is distinct from class-0 pads.
           bldinf.txt defines BR-TRG01's static BASE as frame 1; the COB's
           corresponding SHP stores that frame at index 0. */
        if (location->renderer_class == 2 &&
            g_bridge_trigger_art.frame_count == 23) {
            draw_sprite(dc, &g_bridge_trigger_art, 0, x, y);
            continue;
        }
        /* Island TXT `tone` rows denote unoccupied Tone pools. shapes.txt maps
           POOL to tone.shp; bldinf.txt gives the 2..40 ping-pong animation. */
        if (location->kind == ISLAND_LOCATION_TONE &&
            g_tone_field_art.frame_count == 40) {
            uint32_t frame = island_tone_pool_frame(g_menu.animation_ticks,
                                                    location->x);
            draw_sprite(dc, &g_tone_field_art, frame, x, y);
            continue;
        }
        if (pad_group >= 0 && g_pad_art.frame_count == 27) {
            unsigned phase =
                (g_menu.animation_ticks / (unsigned)(1 + pad_group) + location->x % 23u) % 9u;
            uint32_t frame = (uint32_t)pad_group * 9u + phase;
            draw_sprite(dc, &g_pad_art, frame, x, y);
            continue;
        }
        for (dy = -2; dy <= 2; ++dy) {
            for (dx = -2; dx <= 2; ++dx) {
                if (dx * dx + dy * dy <= 5) (void)SetPixelV(dc, x + dx, y + dy, color);
            }
        }
    }
    if (focus != NULL) {
        int x = (int)focus->x - g_island_scroll_x;
        int y = image_top + (int)focus->y;
        HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
        HGDIOBJ old_pen = SelectObject(dc, pen);
        HGDIOBJ old_brush = SelectObject(dc, GetStockObject(NULL_BRUSH));
        Ellipse(dc, x - 8, y - 8, x + 9, y + 9);
        SelectObject(dc, old_brush);
        SelectObject(dc, old_pen);
        DeleteObject(pen);
    }
    if (saved_dc != 0) RestoreDC(dc, saved_dc);

    /* ISLETMP is the original 640x160 bottom template at y=320, matching the
       ISLETMP pane in windows.txt. It uses the active island palette. */
    draw_sprite(dc, &g_island_template_art, 0, 0, status_top);

    if (g_island_surface_id >= 0 && g_island_surface_id < ISLAND_NAME_COUNT) {
        (void)snprintf(text, sizeof(text), "%s   ISLAND %02d",
                       g_island_names[g_island_surface_id], g_island_surface_id);
    } else {
        (void)snprintf(text, sizeof(text), "ISLAND %02d", g_island_surface_id);
    }
    draw_bitmap_label(dc, text, 12, status_top + 8, RGB(230, 238, 255));
    (void)snprintf(text, sizeof(text), "VIEW X=%04d / 1920     ARROWS: SCROLL     ESC: WORLD MAP",
                   g_island_scroll_x);
    draw_bitmap_label(dc, text, 12, status_top + 27, RGB(143, 181, 217));
    if (focus != NULL) {
        (void)snprintf(text, sizeof(text), "LOCATION %02u  %s  X=%u Y=%u",
                       (unsigned)focus->id, focus->type,
                       (unsigned)focus->x, (unsigned)focus->y);
        draw_bitmap_label(dc, text, 12, status_top + 140, RGB(244, 216, 131));
    } else {
        draw_bitmap_label(dc, "CLICK A MARKER TO INSPECT THIS LOCATION",
                          12, status_top + 140, RGB(143, 181, 217));
    }
    draw_bitmap_label(dc, "SITE MARKERS USE THE SHIPPED ISLANDnn.TXT COORDINATES",
                      12, status_top + 150, RGB(111, 135, 166));
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
        int x;
        int y;
        uint32_t frame = world_island_frame_base(island_index) + (uint32_t)island->shape_id;
        world_island_position(island, &x, &y);
        draw_sprite(dc, &g_small_islands, frame, x, y);
    }
    {
        int island_index = g_hovered_island >= 0 ? g_hovered_island : g_menu.selected_map_island;
        if (island_index >= 0 && (size_t)island_index < world->island_count) {
            int name_index = world->islands[island_index].shape_id;
            if (name_index >= 0 && name_index < ISLAND_NAME_COUNT) {
                /* FUN_004711e2 centers the current island name at y=0x3c. */
                draw_sprite(dc, &g_island_names_art, (uint32_t)name_index, 0, 48);
            }
        }
    }
    draw_bitmap_label(dc, "CLICK AN ISLAND TO SELECT  ENTER OR CLICK AGAIN TO OPEN",
                      12, 454, RGB(160, 190, 222));
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
        } else if (g_menu.screen == SCREEN_ISLAND) {
            render_island_view(back);
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

static void dispatch_newgame_master_message(int message)
{
    if (message == 52) {
        g_menu.setup_accepted = 1;
        g_menu.selected_map_island = -1;
        g_hovered_island = -1;
        g_menu.screen = SCREEN_WORLD_MAP;
    } else if (message == 53) {
        g_menu.world_index = (g_menu.world_index + 1) % g_menu.world_map.world_count;
        g_menu.setup_accepted = 0;
    } else if (message == 55) {
        g_menu.difficulty = (g_menu.difficulty + 1) % g_difficulty_count;
        g_menu.setup_accepted = 0;
    } else if (message >= 60 && message <= 63) {
        g_menu.selected_tribe = message - 60;
        g_menu.setup_accepted = 0;
    }
}

static void handle_click(HWND window, int x, int y)
{
    int clicked_tribe = g_menu.screen == SCREEN_NEW_GAME ? tribe_icon_at(x, y) : -1;
    const WindowTemplate *control = NULL;
    g_mouse_inside = 1;
    g_mouse_x = x;
    g_mouse_y = y;
    (void)update_hover_help(x, y);
    (void)update_newgame_text(x, y);
    if (g_button_sound != NULL) {
        (void)PlaySoundA((LPCSTR)g_button_sound, NULL,
                        SND_MEMORY | SND_ASYNC | SND_NODEFAULT);
    }
    if (g_menu.screen == SCREEN_MAIN_MENU) {
        control = window_catalog_hit_test(&g_window_catalog, 0, x, y);
        if (control != NULL && strcmp(control->message_destination, "WINMGR") == 0) {
            if (control->send_message[0] == 5) {
                g_menu.screen = SCREEN_NEW_GAME;
                g_menu.setup_accepted = 0;
            } else if (control->send_message[0] == 1 &&
                       control->send_message[1] == 4) {
                g_menu.screen = SCREEN_LOAD_GAME;
            } else if (control->send_message[0] == 2) {
                PostMessageA(window, WM_CLOSE, 0, 0);
            }
        } else if (control != NULL && strcmp(control->name, "RESUME") == 0 &&
                   g_resume_available) {
            MessageBoxA(window, "La reprise d'une sauvegarde n'est pas encore prise en charge.",
                        "Tone Rebellion remake", MB_OK | MB_ICONINFORMATION);
        }
    } else if (g_menu.screen == SCREEN_NEW_GAME && clicked_tribe >= 0) {
        /* NewGameWin's custom mouse handler resolves the animated tribe glyphs. */
        g_menu.selected_tribe = clicked_tribe;
        g_menu.setup_accepted = 0;
    } else if (g_menu.screen == SCREEN_NEW_GAME &&
               (x - 320) * (x - 320) + (y - 240) * (y - 240) < 100) {
        /* The NewGameWin handler assigns this inner hit region to difficulty. */
        g_menu.difficulty = (g_menu.difficulty + 1) % g_difficulty_count;
        g_menu.setup_accepted = 0;
    } else if (g_menu.screen == SCREEN_NEW_GAME &&
               (x - 320) * (x - 320) + (y - 240) * (y - 240) < 200) {
        /* The surrounding NewGameWin hit region changes world size. */
        g_menu.world_index = (g_menu.world_index + 1) % g_menu.world_map.world_count;
        g_menu.setup_accepted = 0;
    } else if (g_menu.screen == SCREEN_NEW_GAME) {
        control = window_catalog_hit_test(&g_window_catalog, 1, x, y);
        if (control != NULL && strcmp(control->message_destination, "WINMGR") == 0 &&
            control->send_message[0] == 1 && control->send_message[1] == 0) {
            g_menu.screen = SCREEN_MAIN_MENU;
            g_menu.setup_accepted = 0;
        } else if (control != NULL && strcmp(control->message_destination, "MASTER") == 0) {
            dispatch_newgame_master_message(control->send_message[0]);
        }
    } else if (g_menu.screen == SCREEN_WORLD_MAP) {
        int clicked_island = world_island_at(x, y);
        if (clicked_island >= 0) {
            if (clicked_island == g_menu.selected_map_island) {
                (void)open_island_view(window, clicked_island);
            } else {
                g_menu.selected_map_island = clicked_island;
            }
        }
    } else if (g_menu.screen == SCREEN_ISLAND) {
        int clicked_location = island_location_at(x, y);
        if (clicked_location >= 0) g_selected_location = clicked_location;
    } else if (g_menu.screen == SCREEN_LOAD_GAME) {
        /* FUN_00458162 maps the two columns and four rows to slots 00..07.
           An empty slot closes the load/save screen; a valid slot is kept
           here with an explicit notice until savegame restoration is ported. */
        if (y >= 35) {
            int slot = (y - 28) / 112 + (x / 320) * 4;
            if (slot >= 0 && slot < 8 && g_load_slot_valid[slot]) {
                MessageBoxA(window,
                            "Cette sauvegarde est valide, mais son chargement n'est pas encore pris en charge.",
                            "Tone Rebellion remake", MB_OK | MB_ICONINFORMATION);
            } else {
                g_menu.screen = SCREEN_MAIN_MENU;
            }
        } else {
            g_menu.screen = SCREEN_MAIN_MENU;
        }
    }
    (void)update_hover_help(x, y);
    (void)update_newgame_text(x, y);
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
        if (wparam == 1 && (g_menu.screen == SCREEN_NEW_GAME ||
                            g_menu.screen == SCREEN_ISLAND)) {
            ++g_menu.animation_ticks;
            InvalidateRect(window, NULL, FALSE);
        }
        return 0;
    case WM_MOUSEMOVE: {
        RECT client;
        RECT viewport;
        TRACKMOUSEEVENT track;
        int width;
        int height;
        int x;
        int y;
        GetClientRect(window, &client);
        width = client.right - client.left;
        height = client.bottom - client.top;
        if (!logical_viewport(width, height, &viewport)) return 0;
        x = GET_X_LPARAM(lparam);
        y = GET_Y_LPARAM(lparam);
        if (x < viewport.left || x >= viewport.right || y < viewport.top || y >= viewport.bottom) {
            if (g_mouse_inside || g_hovered_help != -1 || g_hovered_newgame_text != -1 ||
                g_hovered_island != -1 || g_hovered_location != -1) {
                g_mouse_inside = 0;
                if (g_hovered_help != -1 || g_hovered_newgame_text != -1 ||
                    g_hovered_island != -1 || g_hovered_location != -1) {
                    g_hovered_help = -1;
                    g_hovered_newgame_text = -1;
                    g_hovered_island = -1;
                    g_hovered_location = -1;
                    InvalidateRect(window, NULL, FALSE);
                }
            }
            return 0;
        }
        g_mouse_x = (x - viewport.left) * LOGICAL_WIDTH / (viewport.right - viewport.left);
        g_mouse_y = (y - viewport.top) * LOGICAL_HEIGHT / (viewport.bottom - viewport.top);
        g_mouse_inside = 1;
        ZeroMemory(&track, sizeof(track));
        track.cbSize = sizeof(track);
        track.dwFlags = TME_LEAVE;
        track.hwndTrack = window;
        (void)TrackMouseEvent(&track);
        if (update_hover_help(g_mouse_x, g_mouse_y) |
            update_newgame_text(g_mouse_x, g_mouse_y) |
            update_world_map_hover(g_mouse_x, g_mouse_y) |
            update_island_location_hover(g_mouse_x, g_mouse_y)) {
            InvalidateRect(window, NULL, FALSE);
        }
        return 0;
    }
    case WM_MOUSELEAVE:
        g_mouse_inside = 0;
        if (g_hovered_help != -1 || g_hovered_newgame_text != -1 ||
            g_hovered_island != -1 || g_hovered_location != -1) {
            g_hovered_help = -1;
            g_hovered_newgame_text = -1;
            g_hovered_island = -1;
            g_hovered_location = -1;
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
    case WM_MOUSEWHEEL:
        if (g_menu.screen == SCREEN_ISLAND) {
            int direction = GET_WHEEL_DELTA_WPARAM(wparam) > 0 ? -1 : 1;
            g_island_scroll_x += direction * 128;
            if (g_island_scroll_x < 0) g_island_scroll_x = 0;
            if (g_island_scroll_x > 1920) g_island_scroll_x = 1920;
            g_hovered_location = -1;
            InvalidateRect(window, NULL, FALSE);
        }
        return 0;
    case WM_KEYDOWN:
        if (wparam == VK_ESCAPE) {
            if (g_menu.screen == SCREEN_LOAD_GAME) {
                g_menu.screen = SCREEN_MAIN_MENU;
                InvalidateRect(window, NULL, FALSE);
            } else if (g_menu.screen == SCREEN_ISLAND) {
                g_menu.screen = SCREEN_WORLD_MAP;
                g_hovered_location = -1;
                InvalidateRect(window, NULL, FALSE);
            } else if (g_menu.screen == SCREEN_WORLD_MAP) {
                g_hovered_island = -1;
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
                g_menu.selected_map_island = -1;
                g_hovered_island = -1;
                g_menu.screen = SCREEN_WORLD_MAP;
            } else if (g_menu.screen == SCREEN_LOAD_GAME) {
                g_menu.screen = SCREEN_MAIN_MENU;
            } else if (g_menu.screen == SCREEN_WORLD_MAP) {
                int selected = g_menu.selected_map_island;
                if (selected < 0) selected = g_menu.selected_tribe;
                (void)open_island_view(window, selected);
            } else if (g_menu.screen == SCREEN_ISLAND) {
                if (g_selected_location >= 0) g_hovered_location = g_selected_location;
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
            g_menu.selected_map_island = -1;
            g_hovered_island = -1;
            InvalidateRect(window, NULL, FALSE);
        } else if (g_menu.screen == SCREEN_ISLAND &&
                   (wparam == VK_LEFT || wparam == VK_RIGHT)) {
            g_island_scroll_x += wparam == VK_RIGHT ? 160 : -160;
            if (g_island_scroll_x < 0) g_island_scroll_x = 0;
            if (g_island_scroll_x > 1920) g_island_scroll_x = 1920;
            g_hovered_location = -1;
            InvalidateRect(window, NULL, FALSE);
        } else if (g_menu.screen == SCREEN_NEW_GAME &&
                   (wparam == VK_LEFT || wparam == VK_RIGHT)) {
            const int count = g_menu.world_map.world_count;
            g_menu.world_index = (g_menu.world_index + count +
                (wparam == VK_RIGHT ? 1 : -1)) % count;
            g_menu.setup_accepted = 0;
            InvalidateRect(window, NULL, FALSE);
        } else if (g_menu.screen == SCREEN_NEW_GAME && wparam == 'D') {
            dispatch_newgame_master_message(55);
            InvalidateRect(window, NULL, FALSE);
        } else if (g_menu.screen == SCREEN_NEW_GAME && wparam >= '1' && wparam <= '4') {
            dispatch_newgame_master_message(60 + (int)(wparam - '1'));
            InvalidateRect(window, NULL, FALSE);
        }
        if (g_mouse_inside && (update_hover_help(g_mouse_x, g_mouse_y) |
                               update_newgame_text(g_mouse_x, g_mouse_y) |
                               update_world_map_hover(g_mouse_x, g_mouse_y) |
                               update_island_location_hover(g_mouse_x, g_mouse_y))) {
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

static int load_window_catalog(char *error, size_t error_capacity)
{
    CobArchive archive = {0};
    const CobMember *member;
    unsigned char *bytes = NULL;
    int success = 0;

    if (!cob_archive_open("C:\\Program Files\\Tone\\TONE00.COB", &archive,
                          error, error_capacity)) return 0;
    member = cob_archive_find(&archive, "windows.txt");
    if (member == NULL) {
        (void)snprintf(error, error_capacity, "windows.txt was not found in TONE00.COB");
        goto done;
    }
    bytes = (unsigned char *)malloc(member->length == 0 ? 1 : member->length);
    if (bytes == NULL || !cob_archive_read_member(&archive, member, bytes,
                                                   member->length, error,
                                                   error_capacity)) goto done;
    success = window_catalog_load(bytes, member->length, &g_window_catalog,
                                  error, error_capacity);
done:
    free(bytes);
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
    if (!load_palette(&archive, "data\\titscrn.pal", title_palette, NULL,
                      error, error_capacity) ||
        !load_palette(&archive, "data\\newgame.pal", newgame_palette, NULL,
                      error, error_capacity) ||
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
        !load_palette(&archive, "data\\mainmap.pal", mainmap_palette, NULL,
                      error, error_capacity) ||
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
    {
        const CobMember *font = cob_archive_find(&archive, "data\\bgoutfnt.fnt");
        unsigned char *bytes = NULL;
        if (font == NULL) {
            (void)snprintf(error, error_capacity, "data\\bgoutfnt.fnt was not found in TONE01.COB");
            goto done;
        }
        bytes = (unsigned char *)malloc(font->length);
        if (bytes == NULL ||
            !cob_archive_read_member(&archive, font, bytes, font->length,
                                     error, error_capacity) ||
            !bitmap_font_init(&g_bitmap_font, bytes, font->length,
                              error, error_capacity)) {
            free(bytes);
            goto done;
        }
        free(bytes);
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
        bitmap_font_free(&g_bitmap_font);
        free(g_button_sound);
        g_button_sound = NULL;
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

    if (!load_world_map(error, sizeof(error)) ||
        !load_window_catalog(error, sizeof(error)) ||
        !load_menu_art(error, sizeof(error)) ||
        !load_menu_help(error, sizeof(error)) ||
        !create_help_sheet(&g_menu_help, error, sizeof(error)) ||
        !load_newgame_captions(error, sizeof(error)) ||
        !create_newgame_caption_sheet(&g_newgame_captions, error, sizeof(error)) ||
        !load_island_names(error, sizeof(error)) ||
        !create_island_name_sheet(&g_island_names_art, error, sizeof(error)) ||
        !load_tribe_descriptions(error, sizeof(error)) ||
        !create_tribe_description_sheet(&g_tribe_descriptions,
                                        error, sizeof(error))) {
        MessageBoxA(NULL, error, "Tone Rebellion remake - data error", MB_OK | MB_ICONERROR);
        return 1;
    }
    g_resume_available = resume_header_is_valid();
    scan_load_slots();
    g_menu.world_index = 0;
    g_menu.difficulty = 0;
    g_menu.selected_tribe = 0;
    g_menu.selected_map_island = -1;
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
    free_sprite_sheet(&g_island_surface_art);
    free_sprite_sheet(&g_island_template_art);
    free_sprite_sheet(&g_tone_field_art);
    free_sprite_sheet(&g_pad_art);
    free_sprite_sheet(&g_island_feature_art);
    free_sprite_sheet(&g_island_names_art);
    free_sprite_sheet(&g_load_save_art);
    free_sprite_sheet(&g_menu_help);
    free_sprite_sheet(&g_newgame_captions);
    free_sprite_sheet(&g_tribe_descriptions);
    bitmap_font_free(&g_bitmap_font);
    (void)PlaySoundA(NULL, NULL, 0);
    free(g_button_sound);
    free(g_island_height_data);
    return (int)message.wParam;
}
