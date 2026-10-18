#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>

#include "cob_archive.h"
#include "building_render.h"
#include "font_image.h"
#include "island_data.h"
#include "island_haze.h"
#include "island_render_rules.h"
#include "curved_text_layout.h"
#include "game_music.h"
#include "game_inventory.h"
#include "game_trade.h"
#include "island_panel_info.h"
#include "game_session.h"
#include "game_glyph_inventory.h"
#include "iw_construct.h"
#include "shp_image.h"
#include "window_catalog.h"
#include "world_map.h"
#include "tone_rng.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mmsystem.h>

enum { LOGICAL_WIDTH = 640, LOGICAL_HEIGHT = 480, ISLAND_NAME_COUNT = 15,
       BUILDING_NAME_COUNT = 64, BUILDING_NAME_CAPACITY = 128 };
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
static SpriteSheet g_island_lilmap_art;
static SpriteSheet g_island_main_buttons;
static SpriteSheet g_island_realm_art;
static SpriteSheet g_hall_command_art;
static SpriteSheet g_glyph_inventory_art;
static SpriteSheet g_trade_button_art;
static SpriteSheet g_tone_field_art;
static SpriteSheet g_pad_art;
static SpriteSheet g_bridge_trigger_art;
static SpriteSheet g_temp_hole_art;
static SpriteSheet g_build_cycle_art;
static SpriteSheet g_task_scroll_art;
static SpriteSheet g_bildtone_art;
static SpriteSheet g_tone_crys_art;
static SpriteSheet g_magctone_art;
static SpriteSheet g_hall_stock_art;
static SpriteSheet g_inventory_item_art;
static SpriteSheet g_diplomacy_art;
static SpriteSheet g_building_art[PAD_CATALOG_MAX_ITEMS];
static SpriteSheet g_initial_floater_bodies[4];
static SpriteSheet g_initial_floater_legs[4];
static SpriteSheet g_initial_floater_bodies_flipped[4];
static SpriteSheet g_initial_floater_legs_flipped[4];
static SpriteSheet g_floater_info_art;
static SpriteSheet g_island_feature_art;
static SpriteSheet g_island_names_art;
static SpriteSheet g_load_save_art;
static SpriteSheet g_newgame_captions;
static SpriteSheet g_tribe_descriptions;
static SpriteSheet g_menu_help;
static COLORREF g_newgame_palette[256];
static COLORREF g_map_palette[256];
static COLORREF g_island_palette[256];
static uint32_t g_random_state;
static unsigned char *g_button_sound;
static unsigned char *g_fltbuild_sound;
static unsigned char *g_levbuild_sound;
static char g_music_directory[MAX_PATH];
static char g_current_tune[16];
static int g_music_device_open;
static int g_music_loops;
static BitmapFont g_bitmap_font;
static char g_help_text[HELP_ENTRY_COUNT][1024];
static char g_newgame_text[8][256];
static char g_empty_glyph_text[256];
static char g_empty_inventory_text[256];
static char g_hall_population_label[64];
static char g_inventory_info_text[768];
static char g_glyph_info_text[768];
static char g_cryptic_text[ISLAND_PANEL_INFO_CRYPTIC_COUNT][768];
static char g_diplomacy_policy_text[256];
static char g_diplomacy_recipient_text[256];
static char g_inventory_item_info_text[GAME_INVENTORY_ITEM_COUNT][768];
static char g_glyph_item_info_text[GAME_GLYPH_COUNT][768];
static char g_tribe_text[4][2][1024];
static char g_building_descriptions[PAD_CATALOG_MAX_ITEMS][768];
static char g_building_names[BUILDING_NAME_COUNT][BUILDING_NAME_CAPACITY];
static char g_island_names[ISLAND_NAME_COUNT][32];
static IslandData g_island_surface_data;
static GameSession g_game_session;
static GameMusicState g_game_music;
static int g_game_session_valid;
static int g_game_session_world_index = -1;
static WindowCatalog g_window_catalog;
static PadCatalog g_pad_catalog;
static BuildingRenderCatalog g_building_render_catalog;
static uint16_t g_island_draw_order[ISLAND_DATA_MAX_LOCATIONS];
static IslandHaze g_island_haze;
static unsigned char *g_island_height_data;
static size_t g_island_height_length;
static int g_island_surface_id = -1;
static int g_island_scroll_x;
static int g_hovered_location = -1;
static IslandLocationActionControl g_hovered_location_action =
    ISLAND_LOCATION_ACTION_NONE;
static int g_hovered_hall_stock = -1;
static int g_hovered_island_button = -1;
static int g_hovered_hall_command = -1;
static int g_island_panel_mode = WINDOW_ISLAND_PANEL_GENERAL;
static size_t g_inventory_page = 0;
static int g_hovered_inventory_item = -1;
static int g_selected_inventory_item = -1;
static int g_inventory_info_mode = ISLAND_PANEL_INFO_INVENTORY_DEFAULT;
static int g_hovered_glyph = -1;
static int g_glyph_info_default = 1;
static GameDiplomacyHit g_diplomacy_hover;
static int g_diplomacy_hover_valid;
static uint8_t g_floater_overlay_flags;
static int g_selected_location = -1;
static int g_selected_floater = -1;
static IwConstructState g_iw_construct;
static IwConstructInfoState g_iw_construct_info;
static int32_t g_iw_construct_items[IW_CONSTRUCT_BUILD_CANDIDATE_COUNT];
static size_t g_iw_construct_item_count;
static int g_iw_construct_open;
static int32_t g_pending_build_item_id = -1;
static int g_resume_available;
static unsigned char g_load_slot_valid[8];
static int g_hovered_help = -1;
static int g_hovered_newgame_text = -1;
static int g_hovered_island = -1;
static int g_mouse_inside;
static int g_mouse_x;
static int g_mouse_y;

static void update_window_title(HWND window);
static void set_background_tune(const char *tune_id);
static void set_background_tune_once(const char *tune_id);
static void stop_background_tune(void);
static void draw_location_action_panel(HDC dc);
static int load_game_session_for_selected_world(char *error, size_t error_capacity);
static int draw_building_preview(HDC dc, uint16_t item_id, uint8_t player_slot,
                                 int x, int y, uint32_t scale_16_16);

static int begin_new_game(HWND window)
{
    char error[256];
    if (!load_game_session_for_selected_world(error, sizeof(error))) {
        MessageBoxA(window, error, "Tone Rebellion remake - game setup error",
                    MB_OK | MB_ICONERROR);
        return 0;
    }
    g_menu.setup_accepted = 1;
    g_menu.selected_map_island = -1;
    g_hovered_island = -1;
    g_menu.screen = SCREEN_WORLD_MAP;
    update_window_title(window);
    InvalidateRect(window, NULL, FALSE);
    return 1;
}

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
    if (g_menu.screen != SCREEN_ISLAND) {
        /* FUN_004489c0 requests ambi1 for the title. The remake keeps this
           menu bed through setup/map screens. Island-entry music is selected
           once per realm using FUN_00470fe7's transition table. */
        set_background_tune("ambi1");
    }
}

typedef struct MusicTune {
    const char *id;
    const char *file_name;
} MusicTune;

static const MusicTune g_music_tunes[] = {
    {"tribe0", "PROTECT.WAV"}, {"tribe1", "SEEKERS.WAV"},
    {"tribe2", "MYSTICS.WAV"}, {"tribe3", "LIFEGIVE.WAV"},
    /* sound.txt deliberately maps act indices in reverse file order. */
    {"act1", "ACT4.WAV"}, {"act2", "ACT3.WAV"},
    {"act3", "ACT2.WAV"}, {"act4", "ACT1.WAV"},
    {"start", "START.WAV"}, {"ambi1", "AMBIENT1.WAV"},
    {"ambi2", "AMBIENT2.WAV"}, {"ambi3", "AMBIENT3.WAV"},
    {"ambi4", "AMBIENT4.WAV"}, {"levi", "LEVIATAN.WAV"},
    {"winend", "WINNER.WAV"}, {"loosend", "LOSEND.WAV"}
};

static int music_file_exists_in(const char *directory, const char *file_name,
                                char *path, size_t path_capacity)
{
    DWORD attributes;
    int written = snprintf(path, path_capacity, "%s\\%s", directory, file_name);
    if (written < 0 || (size_t)written >= path_capacity) return 0;
    attributes = GetFileAttributesA(path);
    return attributes != INVALID_FILE_ATTRIBUTES &&
           (attributes & FILE_ATTRIBUTE_DIRECTORY) == 0;
}

static int resolve_music_directory(const char *file_name,
                                   char *path, size_t path_capacity)
{
    char candidate[MAX_PATH];
    DWORD environment_length;
    DWORD executable_length;
    char *separator;

    if (g_music_directory[0] != '\0' &&
        music_file_exists_in(g_music_directory, file_name, path, path_capacity)) {
        return 1;
    }
    environment_length = GetEnvironmentVariableA(
        "TONE_REBELLION_THING2", candidate, (DWORD)sizeof(candidate));
    if (environment_length > 0 && environment_length < sizeof(candidate) &&
        music_file_exists_in(candidate, file_name, path, path_capacity)) {
        (void)strncpy(g_music_directory, candidate, sizeof(g_music_directory) - 1);
        g_music_directory[sizeof(g_music_directory) - 1] = '\0';
        return 1;
    }
    executable_length = GetModuleFileNameA(NULL, candidate, (DWORD)sizeof(candidate));
    if (executable_length > 0 && executable_length < sizeof(candidate)) {
        separator = strrchr(candidate, '\\');
        if (separator != NULL) {
            *separator = '\0';
            if (strlen(candidate) + sizeof("\\THING2") < sizeof(g_music_directory)) {
                (void)strcpy(g_music_directory, candidate);
                (void)strcat(g_music_directory, "\\THING2");
                if (music_file_exists_in(g_music_directory, file_name,
                                         path, path_capacity)) return 1;
            }
        }
    }
    if (music_file_exists_in("C:\\toneIso\\THING2", file_name,
                             path, path_capacity)) {
        (void)strcpy(g_music_directory, "C:\\toneIso\\THING2");
        return 1;
    }
    return 0;
}

static void stop_background_tune(void)
{
    if (g_music_device_open) {
        (void)mciSendStringA("stop tone_music", NULL, 0, NULL);
        (void)mciSendStringA("close tone_music", NULL, 0, NULL);
        g_music_device_open = 0;
    }
    g_current_tune[0] = '\0';
    g_music_loops = 0;
}

static void keep_background_tune_playing(void)
{
    char mode[32];
    MCIERROR result;

    if (!g_music_device_open || g_current_tune[0] == '\0') return;
    result = mciSendStringA("status tone_music mode", mode, sizeof(mode), NULL);
    if (result == 0 && strcmp(mode, "stopped") == 0) {
        if (g_music_loops) {
            (void)mciSendStringA("play tone_music", NULL, 0, NULL);
        } else {
            /* FUN_0041c46f requests the `start` tune once; the title handler
               then requests the looping `ambi1` menu bed. */
            stop_background_tune();
            set_background_tune("ambi1");
        }
    }
}

static void set_background_tune_mode(const char *tune_id, int loop)
{
    char path[MAX_PATH];
    char command[MAX_PATH + 64];
    size_t i;
    const char *file_name = NULL;
    MCIERROR result;

    if (tune_id == NULL || strcmp(g_current_tune, tune_id) == 0) return;
    for (i = 0; i < sizeof(g_music_tunes) / sizeof(g_music_tunes[0]); ++i) {
        if (strcmp(g_music_tunes[i].id, tune_id) == 0) {
            file_name = g_music_tunes[i].file_name;
            break;
        }
    }
    if (file_name == NULL ||
        !resolve_music_directory(file_name, path, sizeof(path))) return;

    stop_background_tune();
    {
        int command_length = snprintf(
            command, sizeof(command),
            "open \"%s\" type waveaudio alias tone_music", path);
        if (command_length < 0 || (size_t)command_length >= sizeof(command)) return;
    }
    result = mciSendStringA(command, NULL, 0, NULL);
    if (result != 0) return;
    g_music_device_open = 1;
    result = mciSendStringA("play tone_music", NULL, 0, NULL);
    if (result != 0) {
        stop_background_tune();
        return;
    }
    (void)strncpy(g_current_tune, tune_id, sizeof(g_current_tune) - 1);
    g_current_tune[sizeof(g_current_tune) - 1] = '\0';
    g_music_loops = loop;
}

static void set_background_tune(const char *tune_id)
{
    set_background_tune_mode(tune_id, 1);
}

static void set_background_tune_once(const char *tune_id)
{
    set_background_tune_mode(tune_id, 0);
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

/* FUN_00423068 stores facing-left in object flag 0x002, and FUN_0042704b
   passes a negative horizontal scale for that state. Cache equivalent flipped
   bitmaps so the Win32 renderer can preserve AlphaBlend transparency. */
static int mirror_sprite_sheet_horizontally(const SpriteSheet *source,
                                            SpriteSheet *out,
                                            char *error, size_t error_capacity)
{
    uint32_t frame_index;
    if (source == NULL || out == NULL || source->frames == NULL ||
        source->frame_count == 0) return 0;
    memset(out, 0, sizeof(*out));
    out->frames = (SpriteFrame *)calloc(source->frame_count, sizeof(*out->frames));
    if (out->frames == NULL) {
        (void)snprintf(error, error_capacity, "could not allocate mirrored floater frames");
        return 0;
    }
    out->frame_count = source->frame_count;
    for (frame_index = 0; frame_index < source->frame_count; ++frame_index) {
        const SpriteFrame *input = &source->frames[frame_index];
        SpriteFrame *output = &out->frames[frame_index];
        DIBSECTION dib;
        BITMAPINFO info;
        void *bitmap_bits = NULL;
        HBITMAP bitmap;
        int got;
        int y;

        if (input->bitmap == NULL || input->width <= 0 || input->height <= 0) {
            (void)snprintf(error, error_capacity,
                           "floater sprite has an invalid frame for horizontal mirroring");
            free_sprite_sheet(out);
            return 0;
        }
        ZeroMemory(&dib, sizeof(dib));
        got = GetObjectA(input->bitmap, sizeof(dib), &dib);
        if (got < (int)sizeof(BITMAP) || dib.dsBm.bmBits == NULL ||
            dib.dsBm.bmBitsPixel != 32 || dib.dsBm.bmWidthBytes < input->width * 4) {
            (void)snprintf(error, error_capacity,
                           "floater sprite frame is not a readable 32-bit DIB section");
            free_sprite_sheet(out);
            return 0;
        }
        ZeroMemory(&info, sizeof(info));
        info.bmiHeader.biSize = sizeof(info.bmiHeader);
        info.bmiHeader.biWidth = input->width;
        info.bmiHeader.biHeight = -input->height;
        info.bmiHeader.biPlanes = 1;
        info.bmiHeader.biBitCount = 32;
        info.bmiHeader.biCompression = BI_RGB;
        bitmap = CreateDIBSection(NULL, &info, DIB_RGB_COLORS,
                                  &bitmap_bits, NULL, 0);
        if (bitmap == NULL || bitmap_bits == NULL) {
            if (bitmap != NULL) DeleteObject(bitmap);
            (void)snprintf(error, error_capacity,
                           "could not create horizontally mirrored floater frame");
            free_sprite_sheet(out);
            return 0;
        }
        for (y = 0; y < input->height; ++y) {
            const DWORD *source_row = (const DWORD *)
                ((const unsigned char *)dib.dsBm.bmBits +
                 (size_t)y * (size_t)dib.dsBm.bmWidthBytes);
            DWORD *destination_row = (DWORD *)bitmap_bits +
                                     (size_t)y * (size_t)input->width;
            int x;
            for (x = 0; x < input->width; ++x) {
                destination_row[x] = source_row[input->width - 1 - x];
            }
        }
        *output = *input;
        output->bitmap = bitmap;
        output->x_offset = -input->x_offset;
        output->hit_left = input->width - input->hit_right;
        output->hit_right = input->width - input->hit_left;
    }
    return 1;
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

static void draw_sprite_scaled(HDC target, const SpriteSheet *sheet, uint32_t frame_index,
                               int x, int y, uint32_t scale_16_16)
{
    HDC source;
    HGDIOBJ previous;
    BLENDFUNCTION blend = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
    const SpriteFrame *frame;
    int width;
    int height;
    int offset_x;
    int offset_y;
    if (sheet == NULL || frame_index >= sheet->frame_count) return;
    frame = &sheet->frames[frame_index];
    if (frame->bitmap == NULL) return;
    width = (int)(((uint64_t)(unsigned)frame->width * scale_16_16) >> 16);
    height = (int)(((uint64_t)(unsigned)frame->height * scale_16_16) >> 16);
    if (width <= 0 || height <= 0) return;
    offset_x = (int)(((int64_t)frame->x_offset * scale_16_16) >> 16);
    offset_y = (int)(((int64_t)frame->y_offset * scale_16_16) >> 16);
    source = CreateCompatibleDC(target);
    if (source == NULL) return;
    previous = SelectObject(source, frame->bitmap);
    (void)AlphaBlend(target, x + offset_x, y + offset_y, width, height,
                     source, 0, 0, frame->width, frame->height, blend);
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

static int load_island_surface(int island_id, int map_island_index,
                               char *error, size_t error_capacity)
{
    static const uint8_t feature_frame_counts[ISLAND_NAME_COUNT] = {
        5, 3, 3, 2, 3, 3, 3, 3, 3, 3, 3, 4, 3, 3, 1
    };
    CobArchive archive = {0};
    SpriteSheet candidate = {0};
    SpriteSheet template_candidate = {0};
    SpriteSheet lilmap_candidate = {0};
    SpriteSheet main_buttons_candidate = {0};
    SpriteSheet realm_candidate = {0};
    SpriteSheet hall_command_candidate = {0};
    SpriteSheet glyph_inventory_candidate = {0};
    SpriteSheet trade_button_candidate = {0};
    SpriteSheet tone_candidate = {0};
    SpriteSheet pad_candidate = {0};
    SpriteSheet bridge_candidate = {0};
    SpriteSheet temp_hole_candidate = {0};
    SpriteSheet build_cycle_candidate = {0};
    SpriteSheet task_scroll_candidate = {0};
    SpriteSheet bildtone_candidate = {0};
    SpriteSheet tone_crys_candidate = {0};
    SpriteSheet magctone_candidate = {0};
    SpriteSheet hall_stock_candidate = {0};
    SpriteSheet inventory_item_candidate = {0};
    SpriteSheet diplomacy_candidate = {0};
    SpriteSheet floater_info_candidate = {0};
    SpriteSheet building_candidates[PAD_CATALOG_MAX_ITEMS] = {{0}};
    SpriteSheet floater_body_candidates[4] = {{0}};
    SpriteSheet floater_leg_candidates[4] = {{0}};
    SpriteSheet floater_body_flipped_candidates[4] = {{0}};
    SpriteSheet floater_leg_flipped_candidates[4] = {{0}};
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
    char template_shape_name[32];
    char height_name[48];
    char text_name[48];
    char feature_name[48];
    static const char *const floater_body_names[4] = {
        "data\\pbod.shp", "data\\sbod.shp", "data\\mbod.shp", "data\\lbod.shp"
    };
    static const char *const floater_leg_names[4] = {
        "data\\plegs.shp", "data\\slegs.shp", "data\\mlegs.shp", "data\\llegs.shp"
    };
    unsigned int hall_index;
    unsigned int item_id;
    int selected_player;
    const GameRuntimeIsland *runtime_island = NULL;
    const char *archive_path = "C:\\Program Files\\Tone\\TONE01.COB";
    int success = 0;

    if (island_id < 0 || island_id >= ISLAND_NAME_COUNT) {
        (void)snprintf(error, error_capacity, "island id is out of the supported range");
        return 0;
    }
    if (g_game_session_valid && g_game_session_world_index == g_menu.world_index &&
        map_island_index >= 0 && map_island_index < g_game_session.island_count) {
        runtime_island = &g_game_session.islands[map_island_index];
    }
    selected_player = g_game_session_valid
        ? (int)g_game_session.config.selected_tribe : g_menu.selected_tribe;
    if (selected_player < 0 || selected_player >= GAME_START_PLAYER_COUNT) {
        (void)snprintf(error, error_capacity, "selected tribe is out of range");
        return 0;
    }
    (void)snprintf(shape_name, sizeof(shape_name), "data\\island%02d.shp", island_id);
    (void)snprintf(palette_name, sizeof(palette_name), "data\\island%02d.pal", island_id);
    (void)snprintf(template_shape_name, sizeof(template_shape_name),
                   "data\\isletmp%d.shp", selected_player);
    (void)snprintf(height_name, sizeof(height_name), "data\\island%02d.hzt", island_id);
    (void)snprintf(text_name, sizeof(text_name), "data\\island%02d.txt", island_id);
    (void)snprintf(feature_name, sizeof(feature_name), "data\\i%02d-feat.shp", island_id);
    if (!cob_archive_open(archive_path, &archive, error, error_capacity)) return 0;
    if (!load_palette(&archive, palette_name, palette, palette_rgb6,
                      error, error_capacity) ||
        !load_sprite_sheet(&archive, shape_name, palette, &candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, template_shape_name, palette,
                           &template_candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\lilmap.shp", palette,
                           &lilmap_candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\mainbut0.shp", palette,
                           &main_buttons_candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\isrealm.shp", palette,
                           &realm_candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\fltinfo.shp", palette,
                           &floater_info_candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\thall0.shp", palette,
                           &hall_command_candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\glinv.shp", palette,
                           &glyph_inventory_candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\trade.shp", palette,
                           &trade_button_candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\tone.shp", palette, &tone_candidate,
                           error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\pad.shp", palette, &pad_candidate,
                           error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\br-trg01.shp", palette, &bridge_candidate,
                           error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\temphol0.shp", palette, &temp_hole_candidate,
                           error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\scarrow0.shp", palette, &build_cycle_candidate,
                           error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\scroll.shp", palette, &task_scroll_candidate,
                           error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\bildtone.shp", palette, &bildtone_candidate,
                           error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\tonecrys.shp", palette,
                           &tone_crys_candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\magctone.shp", palette,
                           &magctone_candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\thbutt.shp", palette, &hall_stock_candidate,
                           error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\alltrigs.shp", palette,
                           &inventory_item_candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, "data\\diploma.shp", palette,
                           &diplomacy_candidate, error, error_capacity) ||
        !load_sprite_sheet(&archive, feature_name, palette, &feature_candidate,
                           error, error_capacity)) {
        goto done;
    }
    if (inventory_item_candidate.frame_count < GAME_INVENTORY_ITEM_COUNT) {
        (void)snprintf(error, error_capacity,
                       "data\\alltrigs.shp has fewer frames than inventory IDs 5..33");
        goto done;
    }
    if (diplomacy_candidate.frame_count < 24) {
        (void)snprintf(error, error_capacity,
                       "data\\diploma.shp lacks diplomacy frames 0..23");
        goto done;
    }
    if (bildtone_candidate.frame_count <= 4 || tone_crys_candidate.frame_count <= 4 ||
        magctone_candidate.frame_count <= 4) {
        (void)snprintf(error, error_capacity,
                       "Trade resource sheets must provide source frame 4");
        goto done;
    }
    /* Load only item sheets referenced by this island's actual runtime records.
       bldinf.txt supplies their animation ranges; pad.txt supplies the SHP key. */
    if (runtime_island != NULL) {
        for (hall_index = 0; hall_index < runtime_island->location_count; ++hall_index) {
            int32_t raw_id = runtime_island->locations[hall_index].record_value_10;
            const BuildingRenderItem *definition;
            char item_shape[BUILDING_RENDER_SHAPE_CAPACITY];
            char item_member[48];
            char item_error[128];
            if (raw_id <= 0 || raw_id >= g_pad_catalog.item_count) continue;
            item_id = (unsigned int)raw_id;
            if (building_candidates[item_id].frames != NULL) continue;
            definition = building_render_find(&g_building_render_catalog,
                                               (uint16_t)item_id);
            if (definition == NULL || definition->shape_id[0] == '\0' ||
                strcmp(definition->shape_id, "noshape") == 0) continue;
            (void)snprintf(item_shape, sizeof(item_shape), "%s", definition->shape_id);
            {
                char *character;
                for (character = item_shape; *character != '\0'; ++character) {
                    if (*character >= 'A' && *character <= 'Z') {
                        *character = (char)(*character - 'A' + 'a');
                    }
                }
            }
            (void)snprintf(item_member, sizeof(item_member), "data\\%s.shp", item_shape);
            if (!load_sprite_sheet(&archive, item_member, palette,
                                   &building_candidates[item_id], item_error,
                                   sizeof(item_error))) {
                /* Some data entries are logical items without a drawable SHP. */
                free_sprite_sheet(&building_candidates[item_id]);
                continue;
            }
        }
    }

    /* IWConstruct's ordered candidates come from FUN_0045f121. Preload their
       selected player's actual item sheets so the grid can show source art. */
    if (g_game_session_valid) {
        static const uint8_t construction_candidates[IW_CONSTRUCT_BUILD_CANDIDATE_COUNT] = {
            40, 37, 39, 38, 44, 45, 46, 47
        };
        unsigned int candidate_index;
        for (candidate_index = 0;
             candidate_index < IW_CONSTRUCT_BUILD_CANDIDATE_COUNT; ++candidate_index) {
            const BuildingRenderItem *definition;
            char item_shape[BUILDING_RENDER_SHAPE_CAPACITY];
            char item_member[48];
            char item_error[128];
            item_id = construction_candidates[candidate_index] +
                      (unsigned int)g_game_session.config.selected_tribe * 16U;
            if (item_id >= PAD_CATALOG_MAX_ITEMS ||
                item_id >= g_pad_catalog.item_count ||
                building_candidates[item_id].frames != NULL) continue;
            definition = building_render_find(&g_building_render_catalog,
                                               (uint16_t)item_id);
            if (definition == NULL || definition->shape_id[0] == '\0' ||
                strcmp(definition->shape_id, "noshape") == 0) continue;
            (void)snprintf(item_shape, sizeof(item_shape), "%s", definition->shape_id);
            {
                char *character;
                for (character = item_shape; *character != '\0'; ++character) {
                    if (*character >= 'A' && *character <= 'Z') {
                        *character = (char)(*character - 'A' + 'a');
                    }
                }
            }
            (void)snprintf(item_member, sizeof(item_member), "data\\%s.shp", item_shape);
            if (!load_sprite_sheet(&archive, item_member, palette,
                                   &building_candidates[item_id], item_error,
                                   sizeof(item_error))) {
                free_sprite_sheet(&building_candidates[item_id]);
            }
        }
    }
    /* FUN_0042704b (fltdraw.cpp) draws tribe-specific body and legs sheets.
       shapeinf.txt specifies base-worker body frame 0 and hover frames 0..15. */
    for (hall_index = 0; hall_index < 4; ++hall_index) {
        if (!load_sprite_sheet(&archive, floater_body_names[hall_index], palette,
                               &floater_body_candidates[hall_index], error, error_capacity) ||
            !load_sprite_sheet(&archive, floater_leg_names[hall_index], palette,
                               &floater_leg_candidates[hall_index], error, error_capacity)) {
            goto done;
        }
        if (floater_body_candidates[hall_index].frame_count == 0 ||
            floater_leg_candidates[hall_index].frame_count < 16) {
            (void)snprintf(error, error_capacity,
                           "%s or %s lacks the base-worker or hover frames in shapeinf.txt",
                           floater_body_names[hall_index], floater_leg_names[hall_index]);
            goto done;
        }
        if (!mirror_sprite_sheet_horizontally(&floater_body_candidates[hall_index],
                                              &floater_body_flipped_candidates[hall_index],
                                              error, error_capacity) ||
            !mirror_sprite_sheet_horizontally(&floater_leg_candidates[hall_index],
                                              &floater_leg_flipped_candidates[hall_index],
                                              error, error_capacity)) {
            goto done;
        }
    }
    if (template_candidate.frame_count != 1 ||
        template_candidate.frames[0].width != LOGICAL_WIDTH ||
        template_candidate.frames[0].height != 160) {
        (void)snprintf(error, error_capacity,
                       "data\\isletmp0.shp does not match the 640x160 ISLETEMP pane");
        goto done;
    }
    if (lilmap_candidate.frame_count != 16 ||
        lilmap_candidate.frames[0].width != 256 ||
        lilmap_candidate.frames[0].height != 32) {
        (void)snprintf(error, error_capacity,
                       "data\\lilmap.shp does not match the 16 256x32 island-map frames");
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
    if (temp_hole_candidate.frame_count < 8 || build_cycle_candidate.frame_count < 2 ||
        task_scroll_candidate.frame_count < 4 ||
        hall_stock_candidate.frame_count < 6 || main_buttons_candidate.frame_count < 8 ||
        hall_command_candidate.frame_count < 10 ||
        floater_info_candidate.frame_count < 26 ||
        glyph_inventory_candidate.frame_count < 1U + GAME_GLYPH_COUNT * 2U ||
        trade_button_candidate.frame_count < 4 ||
        realm_candidate.frame_count < 1) {
        (void)snprintf(error, error_capacity,
                       "island controls lack the frames declared in windows.txt or shapes.txt");
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
    free_sprite_sheet(&g_island_lilmap_art);
    free_sprite_sheet(&g_island_main_buttons);
    free_sprite_sheet(&g_island_realm_art);
    free_sprite_sheet(&g_floater_info_art);
    free_sprite_sheet(&g_hall_command_art);
    free_sprite_sheet(&g_glyph_inventory_art);
    free_sprite_sheet(&g_trade_button_art);
    free_sprite_sheet(&g_tone_field_art);
    free_sprite_sheet(&g_pad_art);
    free_sprite_sheet(&g_bridge_trigger_art);
    free_sprite_sheet(&g_temp_hole_art);
    free_sprite_sheet(&g_build_cycle_art);
    free_sprite_sheet(&g_task_scroll_art);
    free_sprite_sheet(&g_bildtone_art);
    free_sprite_sheet(&g_tone_crys_art);
    free_sprite_sheet(&g_magctone_art);
    free_sprite_sheet(&g_hall_stock_art);
    free_sprite_sheet(&g_inventory_item_art);
    free_sprite_sheet(&g_diplomacy_art);
    for (hall_index = 0; hall_index < 4; ++hall_index) {
        free_sprite_sheet(&g_initial_floater_bodies[hall_index]);
        g_initial_floater_bodies[hall_index] = floater_body_candidates[hall_index];
        memset(&floater_body_candidates[hall_index], 0,
               sizeof(floater_body_candidates[hall_index]));
        free_sprite_sheet(&g_initial_floater_bodies_flipped[hall_index]);
        g_initial_floater_bodies_flipped[hall_index] =
            floater_body_flipped_candidates[hall_index];
        memset(&floater_body_flipped_candidates[hall_index], 0,
               sizeof(floater_body_flipped_candidates[hall_index]));
        free_sprite_sheet(&g_initial_floater_legs[hall_index]);
        g_initial_floater_legs[hall_index] = floater_leg_candidates[hall_index];
        memset(&floater_leg_candidates[hall_index], 0,
               sizeof(floater_leg_candidates[hall_index]));
        free_sprite_sheet(&g_initial_floater_legs_flipped[hall_index]);
        g_initial_floater_legs_flipped[hall_index] =
            floater_leg_flipped_candidates[hall_index];
        memset(&floater_leg_flipped_candidates[hall_index], 0,
               sizeof(floater_leg_flipped_candidates[hall_index]));
    }
    for (item_id = 0; item_id < PAD_CATALOG_MAX_ITEMS; ++item_id) {
        free_sprite_sheet(&g_building_art[item_id]);
        g_building_art[item_id] = building_candidates[item_id];
        memset(&building_candidates[item_id], 0, sizeof(building_candidates[item_id]));
    }
    free_sprite_sheet(&g_island_feature_art);
    free(g_island_height_data);
    g_island_surface_art = candidate;
    memset(&candidate, 0, sizeof(candidate));
    g_island_template_art = template_candidate;
    memset(&template_candidate, 0, sizeof(template_candidate));
    g_island_lilmap_art = lilmap_candidate;
    memset(&lilmap_candidate, 0, sizeof(lilmap_candidate));
    g_island_main_buttons = main_buttons_candidate;
    memset(&main_buttons_candidate, 0, sizeof(main_buttons_candidate));
    g_island_realm_art = realm_candidate;
    memset(&realm_candidate, 0, sizeof(realm_candidate));
    g_floater_info_art = floater_info_candidate;
    memset(&floater_info_candidate, 0, sizeof(floater_info_candidate));
    g_hall_command_art = hall_command_candidate;
    memset(&hall_command_candidate, 0, sizeof(hall_command_candidate));
    g_glyph_inventory_art = glyph_inventory_candidate;
    memset(&glyph_inventory_candidate, 0, sizeof(glyph_inventory_candidate));
    g_trade_button_art = trade_button_candidate;
    memset(&trade_button_candidate, 0, sizeof(trade_button_candidate));
    g_tone_field_art = tone_candidate;
    memset(&tone_candidate, 0, sizeof(tone_candidate));
    g_pad_art = pad_candidate;
    memset(&pad_candidate, 0, sizeof(pad_candidate));
    g_bridge_trigger_art = bridge_candidate;
    memset(&bridge_candidate, 0, sizeof(bridge_candidate));
    g_temp_hole_art = temp_hole_candidate;
    memset(&temp_hole_candidate, 0, sizeof(temp_hole_candidate));
    g_build_cycle_art = build_cycle_candidate;
    memset(&build_cycle_candidate, 0, sizeof(build_cycle_candidate));
    g_task_scroll_art = task_scroll_candidate;
    memset(&task_scroll_candidate, 0, sizeof(task_scroll_candidate));
    g_bildtone_art = bildtone_candidate;
    memset(&bildtone_candidate, 0, sizeof(bildtone_candidate));
    g_tone_crys_art = tone_crys_candidate;
    memset(&tone_crys_candidate, 0, sizeof(tone_crys_candidate));
    g_magctone_art = magctone_candidate;
    memset(&magctone_candidate, 0, sizeof(magctone_candidate));
    g_hall_stock_art = hall_stock_candidate;
    memset(&hall_stock_candidate, 0, sizeof(hall_stock_candidate));
    g_inventory_item_art = inventory_item_candidate;
    memset(&inventory_item_candidate, 0, sizeof(inventory_item_candidate));
    g_diplomacy_art = diplomacy_candidate;
    memset(&diplomacy_candidate, 0, sizeof(diplomacy_candidate));
    g_island_feature_art = feature_candidate;
    memset(&feature_candidate, 0, sizeof(feature_candidate));
    g_island_height_data = height_data;
    g_island_height_length = height_member->length;
    height_data = NULL;
    g_island_surface_data = parsed;
    build_island_draw_order();
    g_island_haze = haze_candidate;
    memcpy(g_island_palette, palette, sizeof(g_island_palette));
    g_island_surface_id = island_id;
    g_island_scroll_x = 0;
    g_selected_location = -1;
    g_hovered_location = -1;
    g_island_panel_mode = WINDOW_ISLAND_PANEL_GENERAL;
    g_hovered_inventory_item = -1;
    g_hovered_hall_command = -1;
    g_iw_construct_open = 0;
    g_iw_construct_item_count = 0;
    iw_construct_info_init(&g_iw_construct_info);
    success = 1;
done:
    free_sprite_sheet(&candidate);
    free_sprite_sheet(&template_candidate);
    free_sprite_sheet(&lilmap_candidate);
    free_sprite_sheet(&main_buttons_candidate);
    free_sprite_sheet(&realm_candidate);
    free_sprite_sheet(&floater_info_candidate);
    free_sprite_sheet(&hall_command_candidate);
    free_sprite_sheet(&glyph_inventory_candidate);
    free_sprite_sheet(&trade_button_candidate);
    free_sprite_sheet(&tone_candidate);
    free_sprite_sheet(&pad_candidate);
    free_sprite_sheet(&bridge_candidate);
    free_sprite_sheet(&temp_hole_candidate);
    free_sprite_sheet(&build_cycle_candidate);
    free_sprite_sheet(&task_scroll_candidate);
    free_sprite_sheet(&bildtone_candidate);
    free_sprite_sheet(&tone_crys_candidate);
    free_sprite_sheet(&magctone_candidate);
    free_sprite_sheet(&hall_stock_candidate);
    free_sprite_sheet(&inventory_item_candidate);
    free_sprite_sheet(&diplomacy_candidate);
    for (item_id = 0; item_id < PAD_CATALOG_MAX_ITEMS; ++item_id) {
        free_sprite_sheet(&building_candidates[item_id]);
    }
    for (hall_index = 0; hall_index < 4; ++hall_index) {
        free_sprite_sheet(&floater_body_candidates[hall_index]);
        free_sprite_sheet(&floater_leg_candidates[hall_index]);
        free_sprite_sheet(&floater_body_flipped_candidates[hall_index]);
        free_sprite_sheet(&floater_leg_flipped_candidates[hall_index]);
    }
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

static int32_t measure_curved_bitmap_text(void *context, const char *text,
                                          size_t length)
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
            width += (int32_t)((glyph_width * 12u + g_bitmap_font.height / 2u) /
                               g_bitmap_font.height);
    }
    return width;
}

static void draw_curved_bitmap_text_at(DWORD *pixels, int surface_width,
                                       int surface_height, const char *text,
                                       int x, int y, DWORD ink)
{
    const unsigned char *cursor = (const unsigned char *)text;
    while (*cursor != 0) {
        uint32_t source_width;
        const uint8_t *glyph_pixels;
        uint32_t code = *cursor < g_bitmap_font.glyph_count
            ? *cursor : (uint32_t)'?';
        if (bitmap_font_get_glyph(&g_bitmap_font, code, &source_width,
                                  &glyph_pixels)) {
            uint32_t width = (source_width * 12u + g_bitmap_font.height / 2u) /
                             g_bitmap_font.height;
            if (width == 0) width = 1;
            uint32_t row;
            for (row = 0; row < g_bitmap_font.height; ++row) {
                uint32_t col;
                for (col = 0; col < width; ++col) {
                    uint32_t source_col = col * source_width / width;
                    int px = x + (int)col;
                    int py = y + (int)row;
                    if (glyph_pixels[(size_t)row * source_width + source_col] == 1u &&
                        px >= 0 && px < surface_width &&
                        py >= 0 && py < surface_height) {
                        pixels[(size_t)py * (size_t)surface_width + (size_t)px] = ink;
                    }
                }
            }
            x += (int)width;
        }
        ++cursor;
    }
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
    int32_t single_space_width = measure_curved_bitmap_text(NULL, " ", 1);
    int x = line->x;
    for (i = cursor; i < end; ++i) if (text[i] == ' ') ++space_count;
    text_width = measure_curved_bitmap_text(NULL, text + cursor, end - cursor);
    extra = line->width - text_width;
    if (extra < 0) extra = 0;
    if (space_count == 0) {
        size_t length = end - cursor;
        if (length >= sizeof(word)) length = sizeof(word) - 1;
        memcpy(word, text + cursor, length);
        word[length] = '\0';
        draw_curved_bitmap_text_at(pixels, surface_width, surface_height,
                                   word, x, line->y, ink);
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
        draw_curved_bitmap_text_at(pixels, surface_width, surface_height,
                                   word, x, line->y, ink);
        word_width = measure_curved_bitmap_text(NULL, word, word_length);
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
    return island_panel_info_extract_entry(bytes, length, key,
                                           output, output_capacity);
}

static int load_island_panel_info_text(char *error, size_t error_capacity)
{
    CobArchive archive = {0};
    const CobMember *member;
    unsigned char *bytes = NULL;
    char inventory_text[sizeof(g_inventory_info_text)];
    char glyph_text[sizeof(g_glyph_info_text)];
    char diplomacy_policy_text[sizeof(g_diplomacy_policy_text)];
    char diplomacy_recipient_text[sizeof(g_diplomacy_recipient_text)];
    char item_text[sizeof(g_inventory_item_info_text[0])];
    char item_key[16];
    unsigned int item_id;
    unsigned int glyph_index;
    int success = 0;

    if (!cob_archive_open("C:\\Program Files\\Tone\\TONE00.COB", &archive,
                          error, error_capacity)) return 0;
    member = cob_archive_find(&archive, "newtext.txt");
    if (member == NULL) {
        (void)snprintf(error, error_capacity,
                       "newtext.txt was not found in TONE00.COB");
        goto done;
    }
    memset(inventory_text, 0, sizeof(inventory_text));
    memset(glyph_text, 0, sizeof(glyph_text));
    memset(diplomacy_policy_text, 0, sizeof(diplomacy_policy_text));
    memset(diplomacy_recipient_text, 0, sizeof(diplomacy_recipient_text));
    bytes = (unsigned char *)malloc(member->length == 0 ? 1 : member->length);
    if (bytes == NULL ||
        !cob_archive_read_member(&archive, member, bytes, member->length,
                                 error, error_capacity)) goto done;
    if (!extract_help_entry(bytes, member->length, "COLLART",
                            inventory_text, sizeof(inventory_text)) ||
        !extract_help_entry(bytes, member->length, "GLYSTONE",
                            glyph_text, sizeof(glyph_text)) ||
        !extract_help_entry(bytes, member->length, "TRDIPHI",
                            diplomacy_policy_text,
                            sizeof(diplomacy_policy_text)) ||
        !extract_help_entry(bytes, member->length, "TRCOMHI",
                            diplomacy_recipient_text,
                            sizeof(diplomacy_recipient_text))) {
        (void)snprintf(error, error_capacity,
                       "newtext.txt is missing a Hall panel caption");
        goto done;
    }
    memcpy(g_inventory_info_text, inventory_text, strlen(inventory_text) + 1);
    memcpy(g_glyph_info_text, glyph_text, strlen(glyph_text) + 1);
    memcpy(g_diplomacy_policy_text, diplomacy_policy_text,
           strlen(diplomacy_policy_text) + 1);
    memcpy(g_diplomacy_recipient_text, diplomacy_recipient_text,
           strlen(diplomacy_recipient_text) + 1);
    free(bytes);
    bytes = NULL;

    member = cob_archive_find(&archive, "plotobj.txt");
    if (member == NULL) {
        (void)snprintf(error, error_capacity,
                       "plotobj.txt was not found in TONE00.COB");
        goto done;
    }
    bytes = (unsigned char *)malloc(member->length == 0 ? 1 : member->length);
    if (bytes == NULL ||
        !cob_archive_read_member(&archive, member, bytes, member->length,
                                 error, error_capacity)) goto done;
    for (item_id = 5; item_id <= 33; ++item_id) {
        if (!island_panel_info_inventory_key(item_id, item_key,
                                             sizeof(item_key)) ||
            !extract_help_entry(bytes, member->length, item_key,
                               item_text, sizeof(item_text))) {
            (void)snprintf(error, error_capacity,
                           "plotobj.txt is missing inventory entry %s", item_key);
            goto done;
        }
        memcpy(g_inventory_item_info_text[item_id - 5], item_text,
               strlen(item_text) + 1);
    }
    for (glyph_index = 0; glyph_index < GAME_GLYPH_COUNT; ++glyph_index) {
        if (!game_glyph_inventory_key(glyph_index, item_key, sizeof(item_key)) ||
            !extract_help_entry(bytes, member->length, item_key,
                                item_text, sizeof(item_text))) {
            (void)snprintf(error, error_capacity,
                           "plotobj.txt is missing glyph entry %s", item_key);
            goto done;
        }
        memcpy(g_glyph_item_info_text[glyph_index], item_text,
               strlen(item_text) + 1);
    }
    success = 1;
done:
    free(bytes);
    cob_archive_close(&archive);
    return success;
}

static size_t extract_repeated_help_entries(const unsigned char *bytes, size_t length,
                                           const char *key,
                                           char (*outputs)[BUILDING_NAME_CAPACITY],
                                           size_t output_count)
{
    size_t cursor = 0;
    size_t key_length = strlen(key);
    size_t found = 0;

    while (cursor < length && found < output_count) {
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
                    outputs[found][used] = '\0';
                    ++found;
                    if (cursor < length) ++cursor;
                    break;
                }
                count = text_end - text_start;
                while (count > 0 && (bytes[text_start] == ' ' ||
                                     bytes[text_start] == '\t')) {
                    ++text_start;
                    --count;
                }
                while (count > 0 && (bytes[text_start + count - 1] == ' ' ||
                                     bytes[text_start + count - 1] == '\t')) --count;
                if (count != 0) {
                    if (used != 0 && used + 1 < BUILDING_NAME_CAPACITY) {
                        outputs[found][used++] = ' ';
                    }
                    if (count >= BUILDING_NAME_CAPACITY - used) {
                        count = BUILDING_NAME_CAPACITY - used - 1;
                    }
                    memcpy(outputs[found] + used, bytes + text_start, count);
                    used += count;
                }
                if (cursor < length) ++cursor;
            }
            continue;
        }
        if (cursor < length) ++cursor;
    }
    return found;
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
    if (!extract_help_entry(bytes, member->length, "NOKNOW",
                            g_empty_glyph_text, sizeof(g_empty_glyph_text))) {
        (void)snprintf(error, error_capacity,
                       "gamey.txt key NOKNOW is missing or empty");
        goto done;
    }
    if (!extract_help_entry(bytes, member->length, "NOART",
                            g_empty_inventory_text,
                            sizeof(g_empty_inventory_text))) {
        (void)snprintf(error, error_capacity,
                       "gamey.txt key NOART is missing or empty");
        goto done;
    }
    if (!extract_help_entry(bytes, member->length, "POPSTR",
                            g_hall_population_label,
                            sizeof(g_hall_population_label))) {
        (void)snprintf(error, error_capacity,
                       "gamey.txt key POPSTR is missing or empty");
        goto done;
    }
    for (i = 0; i < ISLAND_PANEL_INFO_CRYPTIC_COUNT; ++i) {
        char key[16] = {0};
        if (!island_panel_info_cryptic_key((unsigned int)i, key, sizeof(key)) ||
            !extract_help_entry(bytes, member->length, key, g_cryptic_text[i],
                                sizeof(g_cryptic_text[i]))) {
            (void)snprintf(error, error_capacity,
                           "gamey.txt key %s is missing or empty", key);
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
                                CURVED_TEXT_NEWGAME_LAST_LINE_Y,
                (int)g_bitmap_font.height,
                                measure_curved_bitmap_text, NULL, lines, MAX_LINES,
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
    return tone_rng_next15(&g_random_state);
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
            int help_index = template_help_index(window);
            int hovered = window_catalog_hover_frame(
                window->shape_frame, help_index, g_hovered_help) !=
                window->shape_frame;
            frame = window_catalog_control_frame(window, hovered);
        } else if (state == 1) {
            int caption_index = template_caption_index(window);
            int hovered = window_catalog_hover_frame(
                window->shape_frame, caption_index,
                g_hovered_newgame_text) != window->shape_frame;
            frame = window_catalog_control_frame(window, hovered);
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
    /* NEWGAMWND contributes the 640x73 frame-0 footer at y=407; do not draw
       it twice or let its unmapped hover index select frame 1. */
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
    /* FUN_00471536 uses angle - phase. Keep WORLDPOS immutable and advance
       the phase by 0.25 degree per 33 ms remake animation tick. */
    float angle = ((float)island->angle_degrees -
                   (float)(g_menu.animation_ticks % 1440u) * 0.25f) *
                  0.017453277f;
    float x_delta = (float)(cos((double)angle) * island->range * scale_x);
    float y_delta = (float)(sin((double)angle) * island->range * scale_y);
    float z_delta = (float)island->z * scale_y;
    *x = 320 + (int)(x_delta + 0.5f);
    *y = 240 - (int)(y_delta + z_delta + 0.5f);
}

static uint8_t world_map_player_mask(void)
{
    if (g_game_session.config.selected_tribe >= GAME_START_PLAYER_COUNT) return 0;
    return (uint8_t)(1U << g_game_session.config.selected_tribe);
}

/* Stable within a rendered frame but advanced by the map's 33 ms timer.
   Drawing must not consume the gameplay RNG because WM_PAINT can run for
   reasons unrelated to simulation time. */
static uint32_t world_map_visual_sample(uint32_t tick, size_t bridge_index,
                                        int step, int spark)
{
    uint32_t value = tick * UINT32_C(0x9e3779b9) +
                     (uint32_t)bridge_index * UINT32_C(0x85ebca6b) +
                     (uint32_t)step * UINT32_C(0xc2b2ae35) +
                     (uint32_t)spark * UINT32_C(0x27d4eb2f);
    value ^= value >> 16;
    value *= UINT32_C(0x7feb352d);
    value ^= value >> 15;
    value *= UINT32_C(0x846ca68b);
    return value ^ (value >> 16);
}

static uint32_t world_island_frame_index(size_t island_index, int shape_id,
                                         int hovered)
{
    int offset;
    if (!g_game_session_valid || island_index >= UINT8_MAX || shape_id < 0) return UINT32_MAX;
    offset = game_session_world_map_frame_offset(
        &g_game_session, (uint8_t)island_index, world_map_player_mask(),
        hovered);
    return offset < 0 ? UINT32_MAX : (uint32_t)offset + (uint32_t)shape_id;
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
        /* Use the non-hover image's bounds so changing to the highlighted
           frame cannot make the cursor fall out of its own hit target. */
        frame_index = world_island_frame_index(island_index, island->shape_id, 0);
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

static void draw_wrapped_bitmap_label(HDC dc, const char *text, int x, int y,
                                      int max_width, int max_lines, COLORREF color)
{
    const char *cursor = text;
    int line_height = (int)g_bitmap_font.height + 2;
    int line = 0;
    if (max_width <= 0 || max_lines <= 0) return;
    while (*cursor != '\0' && line < max_lines) {
        const char *line_start;
        const char *scan;
        const char *last_space = NULL;
        char buffer[256];
        size_t length;
        while (*cursor == ' ' || *cursor == '\t') ++cursor;
        line_start = cursor;
        scan = cursor;
        while (*scan != '\0' && *scan != '\r' && *scan != '\n') {
            const char *word_end = scan;
            while (*word_end != '\0' && *word_end != ' ' && *word_end != '\t' &&
                   *word_end != '\r' && *word_end != '\n') ++word_end;
            if (word_end == scan) {
                ++scan;
                continue;
            }
            if (measure_bitmap_text(NULL, line_start, (size_t)(word_end - line_start)) >
                max_width) {
                if (last_space != NULL && last_space > line_start) scan = last_space;
                else scan = word_end;
                break;
            }
            scan = word_end;
            if (*scan == ' ' || *scan == '\t') {
                last_space = scan;
                while (*scan == ' ' || *scan == '\t') ++scan;
            }
        }
        if (scan == line_start) break;
        length = (size_t)(scan - line_start);
        while (length > 0 && (line_start[length - 1] == ' ' ||
                              line_start[length - 1] == '\t')) --length;
        if (length >= sizeof(buffer)) length = sizeof(buffer) - 1;
        memcpy(buffer, line_start, length);
        buffer[length] = '\0';
        draw_bitmap_label(dc, buffer, x, y + line * line_height, color);
        ++line;
        cursor = scan;
        while (*cursor == ' ' || *cursor == '\t') ++cursor;
        if (*cursor == '\r' || *cursor == '\n') {
            if (*cursor == '\r') ++cursor;
            if (*cursor == '\n') ++cursor;
        }
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
    if (!g_game_session_valid || g_game_session_world_index != g_menu.world_index) {
        if (!load_game_session_for_selected_world(error, sizeof(error))) {
            MessageBoxA(window, error, "Tone Rebellion remake - game setup error",
                        MB_OK | MB_ICONERROR);
            return 0;
        }
    }
    if (!game_session_can_enter_island(&g_game_session,
                                       (uint8_t)map_island_index,
                                       (uint8_t)(1U << g_game_session.config.selected_tribe))) {
        return 0;
    }
    island_id = world->islands[map_island_index].shape_id;
    if (!load_island_surface(island_id, map_island_index, error, sizeof(error))) {
        MessageBoxA(window, error, "Tone Rebellion remake - island data error",
                    MB_OK | MB_ICONERROR);
        return 0;
    }
    g_menu.selected_map_island = map_island_index;
    g_selected_floater = -1;
    g_menu.screen = SCREEN_ISLAND;
    {
        char tune_id[16];
        if (game_music_enter_realm(&g_game_music, (uint8_t)island_id,
                                   (uint8_t)g_game_session.config.selected_tribe,
                                   &g_game_session.random_state,
                                   tune_id, sizeof(tune_id))) {
            if (tune_id[0] != '\0') set_background_tune(tune_id);
        }
    }
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

static IslandLocationActionControl selected_location_action(void)
{
    const GameRuntimeIsland *island;
    const GameRuntimeLocation *location;
    if (!g_game_session_valid || g_menu.screen != SCREEN_ISLAND ||
        g_menu.selected_tribe < 0 ||
        g_menu.selected_tribe >= GAME_START_PLAYER_COUNT ||
        g_menu.selected_map_island < 0 ||
        g_menu.selected_map_island >= g_game_session.island_count ||
        g_selected_location < 0) return ISLAND_LOCATION_ACTION_NONE;
    island = &g_game_session.islands[g_menu.selected_map_island];
    if (g_selected_location >= island->location_count) {
        return ISLAND_LOCATION_ACTION_NONE;
    }
    location = &island->locations[g_selected_location];
    return island_panel_location_action_control(
        location->record_value_10, location->owner_id, g_menu.selected_tribe);
}

static int update_location_action_hover(int x, int y)
{
    const char *const move_names[] = {"IWMove", "IWHallMove"};
    IslandLocationActionControl action = selected_location_action();
    const char *name = action == ISLAND_LOCATION_ACTION_HALL_MOVE
        ? "IWHallMove" : action == ISLAND_LOCATION_ACTION_MOVE
        ? "IWMove" : NULL;
    const WindowTemplate *control = name != NULL
        ? window_catalog_hit_test_names(&g_window_catalog, 3, x, y,
                                        move_names, 2)
        : NULL;
    IslandLocationActionControl hovered = ISLAND_LOCATION_ACTION_NONE;
    if (control != NULL && strcmp(control->name, name) == 0) hovered = action;
    if (hovered == g_hovered_location_action) return 0;
    g_hovered_location_action = hovered;
    return 1;
}

static int selected_hall_player(void)
{
    unsigned int player;
    const GameRuntimeIsland *island;
    const GameRuntimeLocation *hall;
    if (!g_game_session_valid || g_menu.screen != SCREEN_ISLAND ||
        g_menu.selected_tribe >= GAME_START_PLAYER_COUNT ||
        g_menu.selected_map_island < 0 ||
        g_menu.selected_map_island >= g_game_session.island_count ||
        g_selected_location < 0) return -1;
    player = g_menu.selected_tribe;
    if (g_game_session.economy[player].hall_island_index !=
            (uint8_t)g_menu.selected_map_island ||
        g_game_session.economy[player].hall_location_index !=
            (uint16_t)g_selected_location) return -1;
    island = &g_game_session.islands[g_menu.selected_map_island];
    if (g_selected_location >= island->location_count) return -1;
    hall = &island->locations[g_selected_location];
    if (hall->owner_id != (int32_t)player ||
        hall->record_value_10 != (int32_t)(0x2aU + player * 16U)) return -1;
    return (int)player;
}

/* The source roster query FUN_0045d7e8 selects entries from the player's
   list by level. The current session models only the four initial level-0
   workers, so their owner-list order is the only roster subset we can render. */
static uint8_t collect_initial_worker_roster(unsigned int player,
                                             int indices[ISLAND_PANEL_INFO_ROSTER_SLOT_COUNT])
{
    uint8_t count = 0;
    unsigned int i;
    if (indices == NULL || player >= GAME_START_PLAYER_COUNT ||
        !g_game_session_valid) return 0;
    for (i = 0; i < ISLAND_PANEL_INFO_ROSTER_SLOT_COUNT; ++i) indices[i] = -1;
    for (i = 0; i < g_game_session.floater_count &&
         count < ISLAND_PANEL_INFO_ROSTER_SLOT_COUNT; ++i) {
        const GameFloaterStart *floater = &g_game_session.floaters[i];
        if (floater->owner_slot != player || floater->type_index >= 4) continue;
        indices[count++] = (int)i;
    }
    return count;
}

static int selected_hall_roster_hit_test(int x, int y)
{
    int roster[ISLAND_PANEL_INFO_ROSTER_SLOT_COUNT];
    const WindowTemplate *info;
    int player = selected_hall_player();
    uint8_t count;
    uint8_t occupied = 0;
    uint8_t slot;
    int special_layout = 0;
    const GameRuntimeIsland *island;
    if (player < 0) return -1;
    count = collect_initial_worker_roster((unsigned int)player, roster);
    if (count == 0) return -1;
    for (slot = 0; slot < count; ++slot) occupied |= (uint8_t)(1u << slot);
    island = &g_game_session.islands[g_menu.selected_map_island];
    if ((uint16_t)g_selected_location < island->location_count) {
        special_layout = island->locations[g_selected_location].record_value_10 == 0x2f;
    }
    info = window_catalog_find(&g_window_catalog, "IWLocInfo", 3);
    if (info == NULL) return -1;
    slot = (uint8_t)island_panel_info_roster_hit_test(
        info->pane.left, info->pane.top, x, y, special_layout, occupied);
    return slot < ISLAND_PANEL_INFO_ROSTER_SLOT_COUNT ? roster[slot] : -1;
}

static int hall_stock_control_at(int x, int y)
{
    static const char *const names[] = {
        "BC_HallStkB", "BC_HallStkC", "BC_HallStkM"
    };
    const WindowTemplate *control = window_catalog_hit_test_names(
        &g_window_catalog, 3, x, y, names, sizeof(names) / sizeof(names[0]));
    if (control == NULL) return -1;
    if (strcmp(control->name, "BC_HallStkB") == 0) return GAME_RESOURCE_BUILD_TONE;
    if (strcmp(control->name, "BC_HallStkC") == 0) return GAME_RESOURCE_CRYSTAL_TONE;
    if (strcmp(control->name, "BC_HallStkM") == 0) return GAME_RESOURCE_MAGIC_TONE;
    return -1;
}

static int update_hall_stock_hover(int x, int y)
{
    int hovered = selected_hall_player() >= 0 ? hall_stock_control_at(x, y) : -1;
    if (hovered == g_hovered_hall_stock) return 0;
    g_hovered_hall_stock = hovered;
    return 1;
}

static int island_button_index(const char *name)
{
    return window_catalog_island_button(name);
}

static int update_island_button_hover(int x, int y)
{
    static const char *const names[] = {
        "GOTOMAP", "PANIC", "TOGREALM", "TASKLIST"
    };
    const WindowTemplate *control = window_catalog_hit_test_names(
        &g_window_catalog, 3, x, y, names, sizeof(names) / sizeof(names[0]));
    int hovered = control != NULL ? island_button_index(control->name) : -1;
    if (hovered == g_hovered_island_button) return 0;
    g_hovered_island_button = hovered;
    return 1;
}

static int update_hall_command_hover(int x, int y)
{
    static const char *const names[] = {
        "BC_GenInfo", "BC_Storage", "BC_Knowledge", "BC_Trade", "BC_Diplomacy"
    };
    const WindowTemplate *control = selected_hall_player() >= 0
        ? window_catalog_hit_test_names(&g_window_catalog, 3, x, y,
              names, sizeof(names) / sizeof(names[0])) : NULL;
    int hovered = control != NULL
        ? window_catalog_hall_panel_mode(control->name)
        : WINDOW_ISLAND_PANEL_NONE;
    if (hovered == g_hovered_hall_command) return 0;
    g_hovered_hall_command = hovered;
    return 1;
}

static int inventory_item_at(int x, int y)
{
    int hall_player = selected_hall_player();
    if (g_menu.screen == SCREEN_ISLAND && hall_player >= 0 &&
        g_island_panel_mode == WINDOW_ISLAND_PANEL_INVENTORY) {
        const WindowTemplate *panel = window_catalog_find(
            &g_window_catalog, "IWInventory", 3);
        if (panel != NULL) {
            GameInventoryEntry entries[GAME_INVENTORY_ITEM_COUNT];
            size_t entry_count = game_inventory_collect(
                g_game_session.economy[(unsigned int)hall_player].inventory_count,
                entries, GAME_INVENTORY_ITEM_COUNT);
            return game_inventory_hit_test(entries, entry_count,
                g_inventory_page, x, y, panel->pane.left, panel->pane.top,
                panel->pane.right, panel->pane.bottom);
        }
    }
    return -1;
}

static int update_inventory_hover(int x, int y)
{
    int hovered = inventory_item_at(x, y);
    if (hovered == g_hovered_inventory_item) return 0;
    g_hovered_inventory_item = hovered;
    /* FUN_0043d41a publishes the panel's selected item through global
       message 0x42; the source keeps that global after local hover clears. */
    if (hovered >= GAME_INVENTORY_ITEM_FIRST_ID) {
        g_selected_inventory_item = hovered;
    }
    g_inventory_info_mode = ISLAND_PANEL_INFO_INVENTORY_DETAIL;
    return 1;
}

static int update_glyph_hover(int x, int y)
{
    int hall_player = selected_hall_player();
    const WindowTemplate *panel;
    const GamePlayerEconomy *economy;
    GameGlyphCenter centers[GAME_GLYPH_COUNT];
    int pane_width;
    int pane_height;
    unsigned int glyph_index;
    int hovered;

    if (g_menu.screen != SCREEN_ISLAND || hall_player < 0 ||
        g_island_panel_mode != WINDOW_ISLAND_PANEL_GLYPHS) return 0;
    panel = window_catalog_find(&g_window_catalog, "IWGlyphs", 3);
    if (panel == NULL || x < panel->pane.left || x > panel->pane.right ||
        y < panel->pane.top || y > panel->pane.bottom) return 0;

    pane_width = panel->pane.right - panel->pane.left;
    pane_height = panel->pane.bottom - panel->pane.top;
    economy = &g_game_session.economy[(unsigned int)hall_player];
    for (glyph_index = 0; glyph_index < GAME_GLYPH_COUNT; ++glyph_index) {
        const SpriteFrame *frame = &g_glyph_inventory_art.frames[glyph_index + 1U];
        if (frame->hit_right <= frame->hit_left ||
            frame->hit_bottom <= frame->hit_top) {
            centers[glyph_index].x = -10000;
            centers[glyph_index].y = -10000;
            continue;
        }
        centers[glyph_index].x = pane_width + frame->x_offset + frame->hit_left +
            (frame->hit_right - frame->hit_left + 1) / 2;
        centers[glyph_index].y = pane_height + frame->y_offset + frame->hit_top +
            (frame->hit_bottom - frame->hit_top + 1) / 2;
    }
    hovered = game_glyph_inventory_hit_test(economy->glyph_mask, centers,
                                             x - panel->pane.left,
                                             y - panel->pane.top);
    if (hovered == g_hovered_glyph) return 0;
    g_hovered_glyph = hovered;
    g_glyph_info_default = 0;
    return 1;
}

static int adjust_trade_cell(int x, int y, int direction)
{
    const WindowTemplate *panel;
    uint8_t resource_row;
    uint8_t target_column;
    int hall_player = selected_hall_player();
    if (g_menu.screen != SCREEN_ISLAND || hall_player < 0 ||
        g_island_panel_mode != WINDOW_ISLAND_PANEL_TRADE) return 0;
    panel = window_catalog_find(&g_window_catalog, "IWTrade", 3);
    if (panel == NULL ||
        !game_trade_cell_at(x - panel->pane.left, y - panel->pane.top,
                            &resource_row, &target_column)) return 0;
    return game_session_adjust_trade_offer(&g_game_session,
        (uint8_t)hall_player, resource_row, target_column, direction);
}

static int update_diplomacy_hover(int x, int y)
{
    const WindowTemplate *panel;
    GameDiplomacyHit hit;
    int has_hit;
    int changed;
    if (g_menu.screen != SCREEN_ISLAND || selected_hall_player() < 0 ||
        g_island_panel_mode != WINDOW_ISLAND_PANEL_DIPLOMACY) {
        has_hit = 0;
    } else {
        panel = window_catalog_find(&g_window_catalog, "IWDiplomacy", 3);
        has_hit = panel != NULL && game_diplomacy_hit_test(
            x, y, panel->pane.left, panel->pane.top,
            panel->pane.right, panel->pane.bottom, &hit);
    }
    changed = has_hit != g_diplomacy_hover_valid;
    if (has_hit && (!g_diplomacy_hover_valid ||
        hit.action != g_diplomacy_hover.action ||
        hit.displayed_column != g_diplomacy_hover.displayed_column)) {
        g_diplomacy_hover = hit;
        changed = 1;
    }
    g_diplomacy_hover_valid = has_hit;
    return changed;
}

static int click_diplomacy_action(int x, int y, int player_slot)
{
    const WindowTemplate *panel;
    GameDiplomacyHit hit;
    uint8_t target_player;
    if (player_slot < 0 || g_island_panel_mode != WINDOW_ISLAND_PANEL_DIPLOMACY) {
        return 0;
    }
    panel = window_catalog_find(&g_window_catalog, "IWDiplomacy", 3);
    if (panel == NULL || !game_diplomacy_hit_test(
        x, y, panel->pane.left, panel->pane.top,
        panel->pane.right, panel->pane.bottom, &hit) ||
        !game_diplomacy_target_player((uint8_t)player_slot,
                                      hit.displayed_column, &target_player)) {
        return 0;
    }
    (void)game_session_toggle_diplomacy(&g_game_session,
        (uint8_t)player_slot, target_player, hit.action);
    return 1;
}

static int open_iw_construct(int location_index)
{
    const IslandLocation *site;
    const GameRuntimeIsland *runtime_island;
    char error[96];

    if (!g_game_session_valid || g_menu.selected_map_island < 0 ||
        g_menu.selected_map_island >= g_game_session.island_count ||
        location_index < 0 || location_index >= g_island_surface_data.location_count) {
        return 0;
    }
    site = &g_island_surface_data.locations[location_index];
    runtime_island = &g_game_session.islands[g_menu.selected_map_island];
    if (location_index >= runtime_island->location_count ||
        runtime_island->locations[location_index].renderer_class != 0 ||
        runtime_island->locations[location_index].record_value_10 != 0 ||
        runtime_island->locations[location_index].owner_id != -1) return 0;

    /* Initial new-game state gives each player one home island. The rule-set
       selector is still unresolved; at owned-island count 1 the only gated
       row that can pass is candidate 44, whose threshold is 1 in all tables. */
    if (!iw_construct_build_list_for_site(
            &g_pad_catalog, g_game_session.config.selected_tribe, site, 0, 1,
            g_iw_construct_items,
            sizeof(g_iw_construct_items) / sizeof(g_iw_construct_items[0]),
            &g_iw_construct_item_count) || g_iw_construct_item_count == 0) return 0;

    iw_construct_init(&g_iw_construct, g_iw_construct_item_count);
    iw_construct_info_init(&g_iw_construct_info);
    g_iw_construct_open = 1;
    return 1;
}

static int apply_iw_construct_messages(const IwConstructTransition *transition)
{
    unsigned int i;
    int old_item = g_iw_construct_info.item_id;
    if (transition == NULL) return 0;
    for (i = 0; i < transition->message_count; ++i) {
        if (transition->messages[i].code == IW_CONSTRUCT_MSG_SELECT_HOVER) {
            (void)iw_construct_info_handle_message(
                &g_iw_construct_info, IW_CONSTRUCT_INFO_MSG_ITEM,
                transition->messages[i].value);
        }
    }
    return transition->changed || old_item != g_iw_construct_info.item_id;
}

static int update_iw_construct_hover(int x, int y)
{
    const WindowTemplate *window;
    IwConstructTransition transition;

    if (!g_iw_construct_open) return 0;
    window = window_catalog_find(&g_window_catalog, "IWConstruct", 3);
    if (window == NULL) return 0;
    iw_construct_mouse_move(&g_iw_construct, &window->pane, x, y,
                            g_iw_construct_items, g_iw_construct_item_count,
                            &transition);
    return apply_iw_construct_messages(&transition);
}

static int select_iw_construct_item(void)
{
    IwConstructTransition transition;
    unsigned int i;
    int selected = 0;

    iw_construct_mouse_click(&g_iw_construct, g_game_session.config.selected_tribe,
                             &transition);
    for (i = 0; i < transition.message_count; ++i) {
        const IwConstructMessage *message = &transition.messages[i];
        if (message->code == IW_CONSTRUCT_MSG_SELECT_BUILD) {
            g_pending_build_item_id = message->value;
            selected = 1;
        } else if (message->code == IW_CONSTRUCT_MSG_CLEAR_BUILD && selected) {
            g_iw_construct_open = 0;
            (void)iw_construct_info_handle_message(&g_iw_construct_info, 1, 0);
        }
    }
    return selected;
}

static int place_pending_building(HWND window, int location_index)
{
    char error[128];
    int placed;

    if (g_pending_build_item_id < 0 || location_index < 0 ||
        location_index >= g_island_surface_data.location_count ||
        g_menu.selected_map_island < 0) return 0;
    placed = game_session_place_building(
        &g_game_session, &g_pad_catalog,
        (uint8_t)g_game_session.config.selected_tribe,
        (uint8_t)g_menu.selected_map_island, (uint16_t)location_index,
        &g_island_surface_data.locations[location_index],
        (uint16_t)g_pending_build_item_id, error, sizeof(error));
    if (!placed) {
        MessageBoxA(window, error, "Tone Rebellion remake - placement error",
                    MB_OK | MB_ICONINFORMATION);
        return 0;
    }
    /* FUN_004527ee emits event 2 only after its site validation succeeds;
       the current prototype treats this accepted click as action completion. */
    {
        const GameRuntimeLocation *placed =
            &g_game_session.islands[g_menu.selected_map_island].locations[location_index];
        const unsigned char *build_sound = placed->owner_id == 4
            ? g_levbuild_sound : g_fltbuild_sound;
        if (build_sound != NULL) {
            (void)PlaySoundA((LPCSTR)build_sound, NULL,
                         SND_MEMORY | SND_ASYNC | SND_NODEFAULT);
        }
    }
    g_pending_build_item_id = -1;
    return 1;
}

static void draw_hall_info_panel(HDC dc, int panel_state)
{
    const WindowTemplate *panel;
    const char *text = NULL;
    int pane_width;
    int pane_height;
    int line_height;
    int max_lines;

    if (panel_state == WINDOW_ISLAND_PANEL_INVENTORY) {
        if (g_inventory_info_mode == ISLAND_PANEL_INFO_INVENTORY_DETAIL) {
            if (g_hovered_inventory_item >= 5 && g_hovered_inventory_item <= 33) {
                text = g_inventory_item_info_text[g_hovered_inventory_item - 5];
            }
        } else {
            text = g_inventory_info_text;
        }
    } else if (panel_state == WINDOW_ISLAND_PANEL_GLYPHS) {
        if (g_hovered_glyph >= 0 && g_hovered_glyph < GAME_GLYPH_COUNT) {
            text = g_glyph_item_info_text[g_hovered_glyph];
        } else if (g_glyph_info_default) {
            text = g_glyph_info_text;
        }
    } else {
        return;
    }
    panel = window_catalog_find(&g_window_catalog, "IWTextInfo", 3);
    if (panel == NULL || panel->shape_frame < 0 ||
        (uint32_t)panel->shape_frame >= g_temp_hole_art.frame_count) return;
    draw_sprite(dc, &g_temp_hole_art, (uint32_t)panel->shape_frame,
                panel->pane.left, panel->pane.top);
    if (text == NULL || text[0] == '\0') return;

    /* FUN_00439673 puts the default text at (10,6) inside IWTextInfo and
       calls the shared wrapping renderer. Use a fixed inset and the known
       pane bounds here; the original callback's exact wrap metrics remain
       unresolved. */
    pane_width = panel->pane.right - panel->pane.left;
    pane_height = panel->pane.bottom - panel->pane.top;
    line_height = (int)g_bitmap_font.height + 2;
    max_lines = (pane_height - 12) / line_height;
    draw_wrapped_bitmap_label(dc, text, panel->pane.left + 8,
                              panel->pane.top + 6, pane_width - 16,
                              max_lines, g_island_palette[6]);
}

static void draw_diplomacy_initial_worker_icon(HDC dc,
                                               const GameFloaterStart *floater,
                                               int x, int y)
{
    const SpriteSheet *body_art;
    const SpriteSheet *leg_art;
    if (floater == NULL || floater->type_index >= GAME_START_PLAYER_COUNT) return;
    body_art = floater->facing_left
        ? &g_initial_floater_bodies_flipped[floater->type_index]
        : &g_initial_floater_bodies[floater->type_index];
    leg_art = floater->facing_left
        ? &g_initial_floater_legs_flipped[floater->type_index]
        : &g_initial_floater_legs[floater->type_index];
    if (body_art->frame_count == 0 || leg_art->frame_count == 0) return;
    /* FUN_0042704b uses frame zero for the observed initial worker pose.
       Its later per-object animation and status-dependent frames are not
       represented by the four-worker startup model. */
    draw_sprite(dc, leg_art, 0, x, y);
    draw_sprite(dc, body_art, 0, x, y);
}

static void draw_diplomacy_panel(HDC dc, const WindowTemplate *panel,
                                 int player_slot)
{
    static const int32_t emblem_x[GAME_TRADE_TARGET_COUNT] = {264, 301, 325};
    static const int32_t emblem_y[GAME_TRADE_TARGET_COUNT] = {378, 386, 379};
    static const int32_t action_x[GAME_TRADE_TARGET_COUNT] = {220, 300, 380};
    unsigned int column;
    int pane_width = panel->pane.right - panel->pane.left;
    int pane_height = panel->pane.bottom - panel->pane.top;
    const GameFloaterStart *player_floaters[GAME_START_PLAYER_COUNT] = {0};
    if (g_game_session_valid) {
        unsigned floater_index;
        for (floater_index = 0; floater_index < g_game_session.floater_count;
             ++floater_index) {
            const GameFloaterStart *floater =
                &g_game_session.floaters[floater_index];
            if (floater->owner_slot < GAME_START_PLAYER_COUNT &&
                floater->type_index < GAME_START_PLAYER_COUNT &&
                player_floaters[floater->owner_slot] == NULL) {
                player_floaters[floater->owner_slot] = floater;
            }
        }
    }
    {
        int32_t icon_x;
        int32_t icon_y;
        if (game_diplomacy_player_icon_position(0, panel->pane.left,
                pane_width, pane_height, &icon_x, &icon_y)) {
            draw_diplomacy_initial_worker_icon(dc, player_floaters[player_slot],
                panel->pane.left + (int)icon_x,
                panel->pane.top + (int)icon_y);
        }
    }
    for (column = 0; column < GAME_TRADE_TARGET_COUNT; ++column) {
        uint8_t target_player;
        uint32_t emblem_frame = column * 7U;
        uint32_t action_frame;
        int action_y = pane_height - (column == 1U ? 20 : 30) - 15;
        int32_t emblem_left = emblem_x[column] - panel->pane.left;
        int32_t emblem_top = emblem_y[column] - panel->pane.top;
        int32_t control_left = action_x[column] - panel->pane.left;
        if (!game_diplomacy_target_player((uint8_t)player_slot,
                                          (uint8_t)column, &target_player)) continue;

        /* FUN_0043e5aa draws each other-player group at frames 0, 7, and 14;
           the last frame in each group is its policy-row hover highlight. */
        if (g_diplomacy_hover_valid &&
            g_diplomacy_hover.action == GAME_DIPLOMACY_POLICY &&
            g_diplomacy_hover.displayed_column == column) {
            emblem_frame = (column + 1U) * 7U - 1U;
        }
        draw_sprite(dc, &g_diplomacy_art, emblem_frame,
                    (int)emblem_left, (int)emblem_top);

        if (g_diplomacy_hover_valid &&
            g_diplomacy_hover.action == GAME_DIPLOMACY_RECIPIENT &&
            g_diplomacy_hover.displayed_column == column) {
            draw_sprite(dc, &g_diplomacy_art, 23,
                        (int)control_left, action_y);
        }
        {
            int32_t icon_x;
            int32_t icon_y;
            if (game_diplomacy_player_icon_position((uint8_t)(column + 1U),
                    panel->pane.left, pane_width, pane_height,
                    &icon_x, &icon_y)) {
                /* FUN_0043e5aa draws each player icon before its policy state. */
                draw_diplomacy_initial_worker_icon(dc, player_floaters[target_player],
                    panel->pane.left + (int)icon_x,
                    panel->pane.top + (int)icon_y);
            }
        }
        action_frame =
            (g_game_session.diplomacy_policy_mask[player_slot] &
             (uint8_t)(1U << target_player)) != 0 ? 21U : 22U;
        /* FUN_0043e5aa draws recipient highlight frame 23 before the
           policy-state frame 21/22. The source's separate player-banner
           helper (FUN_00428191, flag 8) is not yet mapped to remake art. */
        draw_sprite(dc, &g_diplomacy_art, action_frame,
                    (int)control_left, action_y);
    }
    if (g_diplomacy_hover_valid) {
        /* The source condition chooses TRCOMHI for +0x72 (policy row) and
           TRDIPHI for +0x74 (recipient row), despite the labels' wording. */
        const char *caption = g_diplomacy_hover.action == GAME_DIPLOMACY_POLICY
            ? g_diplomacy_recipient_text : g_diplomacy_policy_text;
        int x = panel->pane.left + pane_width / 2 + 15;
        draw_bitmap_label(dc, caption, x, panel->pane.top + 7,
                          g_island_palette[6]);
    }
}

static void draw_hall_panel(HDC dc, int hall_player)
{
    const WindowTemplate *panel = NULL;
    const char *empty_message = NULL;
    int panel_state = g_island_panel_mode;
    if (panel_state == WINDOW_ISLAND_PANEL_TASKS ||
        panel_state == WINDOW_ISLAND_PANEL_EFFECT_DEBUG) {
        const char *const task_window_names[] = {
            "IWTasks", "IWTaskInfo", "IWTaskOptions"
        };
        const char *const effect_window_names[] = {
            "IWEffList", "IWSFXList"
        };
        static const char *const task_scroll_names[] = {
            "scrollup", "scrolldn", "escrollup", "escrolldn"
        };
        const WindowTemplate *hover_scroll = g_mouse_inside
            ? window_catalog_hit_test_names(&g_window_catalog, 3,
                  g_mouse_x, g_mouse_y, task_scroll_names,
                  sizeof(task_scroll_names) / sizeof(task_scroll_names[0]))
            : NULL;
        size_t task_index;
        if (panel_state == WINDOW_ISLAND_PANEL_TASKS) {
            for (task_index = 0;
                 task_index < sizeof(task_window_names) / sizeof(task_window_names[0]);
                 ++task_index) {
                const WindowTemplate *task_panel = window_catalog_find(
                    &g_window_catalog, task_window_names[task_index], 3);
                if (task_panel != NULL && task_panel->shape_frame >= 0 &&
                    g_temp_hole_art.frame_count > (uint32_t)task_panel->shape_frame) {
                    draw_sprite(dc, &g_temp_hole_art,
                                (uint32_t)task_panel->shape_frame,
                                task_panel->pane.left, task_panel->pane.top);
                }
            }
        } else {
            for (task_index = 0;
                 task_index < sizeof(effect_window_names) / sizeof(effect_window_names[0]);
                 ++task_index) {
                const WindowTemplate *effect_panel = window_catalog_find(
                    &g_window_catalog, effect_window_names[task_index], 3);
                if (effect_panel != NULL && effect_panel->shape_frame >= 0 &&
                    g_temp_hole_art.frame_count > (uint32_t)effect_panel->shape_frame) {
                    draw_sprite(dc, &g_temp_hole_art,
                                (uint32_t)effect_panel->shape_frame,
                                effect_panel->pane.left, effect_panel->pane.top);
                }
            }
        }
        for (task_index = 0;
             task_index < sizeof(task_scroll_names) / sizeof(task_scroll_names[0]);
             ++task_index) {
            const WindowTemplate *control = window_catalog_find(
                &g_window_catalog, task_scroll_names[task_index], 3);
            if (control != NULL &&
                window_catalog_scroll_panel_mode(control->name) == panel_state &&
                control->shape_frame >= 0) {
                int frame = window_catalog_control_frame(
                    control, control == hover_scroll);
                if (frame < 0 || g_task_scroll_art.frame_count <= (uint32_t)frame)
                    continue;
                /* FUN_0042fa0f routes each pair to its distinct list panel. */
                draw_sprite(dc, &g_task_scroll_art, (uint32_t)frame,
                            control->pane.left, control->pane.top);
            }
        }
        return;
    }
    if (hall_player < 0) return;
    if (panel_state == WINDOW_ISLAND_PANEL_INVENTORY) {
        panel = window_catalog_find(&g_window_catalog, "IWInventory", 3);
    } else if (panel_state == WINDOW_ISLAND_PANEL_GLYPHS) {
        panel = window_catalog_find(&g_window_catalog, "IWGlyphs", 3);
        if (g_game_session.economy[(unsigned int)hall_player].glyph_mask == 0) {
            /* FUN_0043dee3 draws TEMPHOLE/NOKNOW for a zero ownership mask. */
            empty_message = g_empty_glyph_text;
        }
    } else if (panel_state == WINDOW_ISLAND_PANEL_DIPLOMACY) {
        panel = window_catalog_find(&g_window_catalog, "IWDiplomacy", 3);
    } else if (panel_state == WINDOW_ISLAND_PANEL_TRADE) {
        panel = window_catalog_find(&g_window_catalog, "IWTrade", 3);
    }
    if (panel == NULL || panel->shape_frame < 0 ||
        g_temp_hole_art.frame_count <= (uint32_t)panel->shape_frame) return;
    draw_sprite(dc, &g_temp_hole_art, (uint32_t)panel->shape_frame,
                panel->pane.left, panel->pane.top);
    if (panel_state == WINDOW_ISLAND_PANEL_TRADE) {
        const SpriteSheet *const resource_sheets[GAME_RESOURCE_TYPE_COUNT] = {
            &g_bildtone_art, &g_tone_crys_art, &g_magctone_art
        };
        const GamePlayerEconomy *economy =
            &g_game_session.economy[(unsigned int)hall_player];
        unsigned int resource;
        unsigned int target;
        for (resource = 0; resource < GAME_RESOURCE_TYPE_COUNT; ++resource) {
            if (resource_sheets[resource]->frame_count > 4U) {
                /* FUN_0043edac draws frame 4 of each named Tone sheet. */
                draw_sprite(dc, resource_sheets[resource], 4,
                            panel->pane.left + 30,
                            panel->pane.top + 52 + (int)resource * 24);
            }
        }
        for (resource = 0; resource < GAME_RESOURCE_TYPE_COUNT; ++resource) {
            for (target = 0; target < GAME_TRADE_TARGET_COUNT; ++target) {
                char amount_text[8];
                unsigned int amount = economy->trade_offer[resource][target];
                int width;
                int x;
                int y;
                (void)snprintf(amount_text, sizeof(amount_text), "%u", amount);
                width = measure_bitmap_text(NULL, amount_text, strlen(amount_text));
                x = panel->pane.left + (int)target * 38 + 40 + (28 - width) / 2;
                y = panel->pane.top + (int)resource * 24 + 44;
                draw_bitmap_label(dc, amount_text, x, y, RGB(220, 232, 244));
            }
        }
    }
    if (panel_state == WINDOW_ISLAND_PANEL_INVENTORY) {
        GameInventoryEntry entries[GAME_INVENTORY_ITEM_COUNT];
        GameInventoryEntry page[GAME_INVENTORY_PAGE_SIZE];
        const GamePlayerEconomy *economy =
            &g_game_session.economy[(unsigned int)hall_player];
        size_t entry_count = game_inventory_collect(economy->inventory_count,
            entries, GAME_INVENTORY_ITEM_COUNT);
        size_t page_count = game_inventory_page_count(entry_count);
        size_t visible_count;
        size_t slot;
        const WindowTemplate *cycle = window_catalog_find(
            &g_window_catalog, "InvCycle", 3);
        const char *const cycle_names[] = {"InvCycle"};
        const WindowTemplate *hover_cycle = g_mouse_inside
            ? window_catalog_hit_test_names(&g_window_catalog, 3,
                  g_mouse_x, g_mouse_y, cycle_names, 1)
            : NULL;
        if (entry_count == 0) {
            int width = measure_bitmap_text(NULL, g_empty_inventory_text,
                                           strlen(g_empty_inventory_text));
            int height = (int)g_bitmap_font.height;
            int x = panel->pane.left +
                ((panel->pane.right - panel->pane.left) - width) / 2;
            int y = panel->pane.top +
                ((panel->pane.bottom - panel->pane.top) - height) / 2 - 6;
            draw_bitmap_label(dc, g_empty_inventory_text, x, y,
                              RGB(185, 205, 220));
        } else {
            size_t current_page = page_count == 0 ? 0 : g_inventory_page % page_count;
            int pane_width = panel->pane.right - panel->pane.left;
            int pane_height = panel->pane.bottom - panel->pane.top;
            int column_width = pane_width / 5;
            int row_height = (pane_height - 24) / 2;
            visible_count = game_inventory_page(entries, entry_count,
                                                 current_page, page);
            for (slot = 0; slot < visible_count; ++slot) {
                uint32_t frame_index = page[slot].item_id -
                    GAME_INVENTORY_ITEM_FIRST_ID;
                const SpriteFrame *icon = &g_inventory_item_art.frames[frame_index];
                int column = (int)(slot % 5);
                int row = (int)(slot / 5);
                int cell_left = panel->pane.left + column * column_width;
                int cell_top = panel->pane.top + 24 + row * row_height;
                int x;
                int y;
                if (!game_inventory_sprite_position(
                        cell_left, cell_top, column_width, row_height,
                        icon->x_offset, icon->y_offset,
                        icon->hit_left, icon->hit_top,
                        icon->hit_right, icon->hit_bottom,
                        &x, &y)) {
                    /* Empty SHP frames have no opaque bounds and contribute
                       no visible pixels; keep a deterministic cell origin. */
                    x = cell_left;
                    y = cell_top;
                }
                if (page[slot].item_id == (uint8_t)g_selected_inventory_item ||
                    page[slot].item_id == (uint8_t)g_hovered_inventory_item) {
                    int palette_index = page[slot].item_id ==
                        (uint8_t)g_selected_inventory_item ? 4 : 1;
                    HPEN outline = CreatePen(PS_SOLID, 1,
                                              g_island_palette[palette_index]);
                    if (outline != NULL) {
                        HGDIOBJ previous = SelectObject(dc, outline);
                        HGDIOBJ previous_brush = SelectObject(dc, GetStockObject(NULL_BRUSH));
                        Rectangle(dc, cell_left + 1, cell_top + 1,
                                  cell_left + column_width - 1,
                                  cell_top + row_height - 1);
                        SelectObject(dc, previous_brush);
                        SelectObject(dc, previous);
                        DeleteObject(outline);
                    }
                }
                draw_sprite(dc, &g_inventory_item_art, frame_index, x, y);
                if (page[slot].count > 1) {
                    char count_text[12];
                    (void)snprintf(count_text, sizeof(count_text), "%u",
                                   (unsigned int)page[slot].count);
                    draw_bitmap_label(dc, count_text,
                        x + 7, y - 21, RGB(235, 235, 220));
                }
            }
        }
        if (entry_count > GAME_INVENTORY_PAGE_SIZE && cycle != NULL) {
            int frame = window_catalog_control_frame(cycle, cycle == hover_cycle);
            if (frame >= 0 && g_build_cycle_art.frame_count > (uint32_t)frame) {
                draw_sprite(dc, &g_build_cycle_art, (uint32_t)frame,
                            cycle->pane.left, cycle->pane.top);
            }
        }
    }
    if (panel_state == WINDOW_ISLAND_PANEL_GLYPHS) {
        const GamePlayerEconomy *economy =
            &g_game_session.economy[(unsigned int)hall_player];
        uint16_t glyph_mask = economy->glyph_mask;
        int pane_width = panel->pane.right - panel->pane.left;
        int pane_height = panel->pane.bottom - panel->pane.top;
        unsigned int glyph_index;
        if (glyph_mask != 0) {
            int anchor_x = panel->pane.left + pane_width;
            int anchor_y = panel->pane.top + pane_height;
            draw_sprite(dc, &g_glyph_inventory_art, 0,
                        panel->pane.left, panel->pane.top);
            for (glyph_index = 0; glyph_index < GAME_GLYPH_COUNT; ++glyph_index) {
                uint32_t frame = game_glyph_inventory_frame(
                    glyph_mask, (int)glyph_index, g_hovered_glyph);
                if (frame != UINT32_MAX) {
                    draw_sprite(dc, &g_glyph_inventory_art, frame,
                                anchor_x, anchor_y);
                }
            }
        } else if (g_temp_hole_art.frame_count > 1U) {
            draw_sprite(dc, &g_temp_hole_art, 1,
                        panel->pane.left, panel->pane.top);
        }
    }
    if (panel_state == WINDOW_ISLAND_PANEL_DIPLOMACY) {
        draw_diplomacy_panel(dc, panel, hall_player);
    }
    if (empty_message != NULL && empty_message[0] != '\0') {
        int width = measure_bitmap_text(NULL, empty_message, strlen(empty_message));
        int x = panel->pane.left +
            ((panel->pane.right - panel->pane.left) - width) / 2;
        int y = panel->pane.top +
            ((panel->pane.bottom - panel->pane.top) -
             (int)g_bitmap_font.height) / 2 - 6;
        draw_bitmap_label(dc, empty_message, x, y, RGB(185, 205, 220));
    }
    if (panel_state == WINDOW_ISLAND_PANEL_TRADE) {
        static const char *const trade_names[] = {"TradeZERO", "TradeDOIT"};
        size_t index;
        for (index = 0; index < sizeof(trade_names) / sizeof(trade_names[0]); ++index) {
            const WindowTemplate *button = window_catalog_find(
                &g_window_catalog, trade_names[index], 3);
            const WindowTemplate *hover_control;
            int hovered;
            int frame;
            if (button == NULL) continue;
            hover_control = g_mouse_inside
                ? window_catalog_hit_test_names(&g_window_catalog, 3,
                    g_mouse_x, g_mouse_y, trade_names,
                    sizeof(trade_names) / sizeof(trade_names[0])) : NULL;
            hovered = hover_control == button;
            frame = window_catalog_control_frame(button, hovered);
            if (frame >= 0 && (uint32_t)frame < g_trade_button_art.frame_count) {
                draw_sprite(dc, &g_trade_button_art, (uint32_t)frame,
                            button->pane.left, button->pane.top);
            }
        }
    }
    draw_hall_info_panel(dc, panel_state);
}

static void draw_iw_construct(HDC dc)
{
    const WindowTemplate *window;
    const WindowTemplate *info_window;
    const WindowTemplate *cycle_window;
    const PadCatalogItem *info_item;
    unsigned int column;

    if (!g_iw_construct_open) return;
    window = window_catalog_find(&g_window_catalog, "IWConstruct", 3);
    info_window = window_catalog_find(&g_window_catalog, "IWConstructInfo", 3);
    cycle_window = window_catalog_find(&g_window_catalog, "BuildCycle", 3);
    if (window == NULL || info_window == NULL) return;

    /* The pane extents, backdrop frames, and optional cycle button come from
       windows.txt; the original draw loop lays out four columns per page. */
    draw_sprite(dc, &g_temp_hole_art, (uint32_t)window->shape_frame,
                window->pane.left, window->pane.top);
    for (column = 0; column < IW_CONSTRUCT_ITEMS_PER_PAGE; ++column) {
        size_t item_index = (size_t)g_iw_construct.page *
                            IW_CONSTRUCT_ITEMS_PER_PAGE + column;
        int pane_width = window->pane.right - window->pane.left;
        int column_width = pane_width / IW_CONSTRUCT_ITEMS_PER_PAGE;
        /* FUN_0043aee8 starts at pane_width/8 and advances pane_width/4. */
        int center_x = window->pane.left + pane_width / 8 +
                       pane_width * (int)column / IW_CONSTRUCT_ITEMS_PER_PAGE;
        if (item_index >= g_iw_construct_item_count) break;
        {
            uint16_t item_id = (uint16_t)(g_iw_construct_items[item_index] +
                (int32_t)g_game_session.config.selected_tribe * 16);
            if (item_id < PAD_CATALOG_MAX_ITEMS &&
                g_building_art[item_id].frame_count != 0 &&
                item_id < g_pad_catalog.item_count) {
                const PadCatalogItem *item = &g_pad_catalog.items[item_id];
                (void)draw_building_preview(dc, item_id,
                    (uint8_t)g_game_session.config.selected_tribe,
                    center_x, window->pane.top +
                    (window->pane.bottom - window->pane.top) - 0x23, 0x8000U);
                if (item->building_tone_cost > 0) {
                    int cost_frame = item->building_tone_cost - 1;
                    if (cost_frame > 0x31) cost_frame = 0x31;
                    if ((uint32_t)cost_frame < g_bildtone_art.frame_count) {
                        draw_sprite_scaled(dc, &g_bildtone_art, (uint32_t)cost_frame,
                            center_x, window->pane.top +
                            (window->pane.bottom - window->pane.top) - 0x0f, 0x8000U);
                    }
                }
            }
        }
        if ((int)column == g_iw_construct.hovered_column) {
            RECT highlight = {
                window->pane.left + column_width * (int)column,
                window->pane.top + 0x1a,
                window->pane.left + column_width * ((int)column + 1),
                window->pane.bottom - 10
            };
            HBRUSH brush = CreateSolidBrush(RGB(119, 199, 234));
            FrameRect(dc, &highlight, brush);
            DeleteObject(brush);
        }
    }
    if (g_iw_construct.cycle_button_visible && cycle_window != NULL) {
        draw_sprite(dc, &g_build_cycle_art, (uint32_t)cycle_window->shape_frame,
                    cycle_window->pane.left, cycle_window->pane.top);
    }

    draw_sprite(dc, &g_temp_hole_art, (uint32_t)info_window->shape_frame,
                info_window->pane.left, info_window->pane.top);
    info_item = g_iw_construct_info.item_id < 0 ? NULL : pad_catalog_find(
        &g_pad_catalog, (uint16_t)(g_iw_construct_info.item_id +
        (int32_t)g_game_session.config.selected_tribe * 16));
    if (info_item != NULL) {
        uint16_t item_id = info_item->item_id;
        if (item_id < PAD_CATALOG_MAX_ITEMS &&
            g_building_art[item_id].frame_count != 0) {
            (void)draw_building_preview(dc, item_id,
                (uint8_t)g_game_session.config.selected_tribe,
                info_window->pane.left +
                    (info_window->pane.right - info_window->pane.left) - 0x37,
                info_window->pane.top + 0x55, 0x10000U);
        }
        if (item_id < g_pad_catalog.item_count && info_item->building_tone_cost > 0) {
            int cost_frame = info_item->building_tone_cost - 1;
            if (cost_frame > 0x31) cost_frame = 0x31;
            if ((uint32_t)cost_frame < g_bildtone_art.frame_count) {
                draw_sprite(dc, &g_bildtone_art, (uint32_t)cost_frame,
                            info_window->pane.left + 0x2d,
                            info_window->pane.top + 0x4b);
            }
        }
        if (item_id < PAD_CATALOG_MAX_ITEMS &&
            g_building_descriptions[item_id][0] != '\0') {
            int text_width = (info_window->pane.right - info_window->pane.left) - 0x4f;
            int text_height = info_window->pane.bottom - info_window->pane.top - 0x60;
            int line_height = (int)g_bitmap_font.height + 2;
            int max_lines = line_height > 0 ? text_height / line_height : 0;
            draw_wrapped_bitmap_label(dc, g_building_descriptions[item_id],
                info_window->pane.left + 10, info_window->pane.top + 0x58,
                text_width, max_lines, RGB(232, 236, 244));
        }
    }
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

static int draw_runtime_item_scaled(HDC dc, const GameRuntimeLocation *runtime_location,
                                    int x, int y, uint32_t scale_16_16)
{
    int32_t raw_id;
    const BuildingRenderItem *item;
    const SpriteSheet *sheet;
    uint32_t frame;
    int drew = 0;

    if (runtime_location == NULL || (raw_id = runtime_location->record_value_10) <= 0 ||
        raw_id >= g_pad_catalog.item_count) return 0;
    item = building_render_find(&g_building_render_catalog, (uint16_t)raw_id);
    if (item == NULL || (unsigned int)raw_id >= PAD_CATALOG_MAX_ITEMS) return 0;
    sheet = &g_building_art[raw_id];
    if (sheet->frames == NULL || sheet->frame_count == 0) return 0;

    /* FUN_0040bf98 draws the static/base item layer and then the CHUG layer.
       The source divides the object's +0x3a progress by CHUG speed. The menu
       timer is only a provisional source for that per-object counter. */
    if (item->base.present) {
        frame = building_render_base_frame_for_state(item, runtime_location->base_progress,
                                                     runtime_location->source_flags);
        if (frame < sheet->frame_count) {
            draw_sprite_scaled(dc, sheet, frame, x, y, scale_16_16);
            drew = 1;
        }
    }
    if (item->chug.present) {
        frame = building_render_chug_frame(item, runtime_location->chug_progress);
        if (frame < sheet->frame_count) {
            draw_sprite_scaled(dc, sheet, frame, x, y, scale_16_16);
            drew = 1;
            /* Keep rendering later layers: GLYP is drawn after CHUG by
               FUN_0040bf98 and may be the visible top layer. */
        }
    }
    if (item->glyph.present) {
        frame = building_render_glyph_frame(item, runtime_location->glyph_progress);
        if (frame < sheet->frame_count) {
            draw_sprite_scaled(dc, sheet, frame, x, y, scale_16_16);
            drew = 1;
        }
    }
    /* FUN_0040bf98's remaining item layers are data-driven too. INCI uses
       +0x3e; CONS uses +0x40 and flag 0x004; PROD uses +0x42 and flag 0x002.
       The animated PROD frame stays at the item anchor; only its separate
       threshold effect uses the descriptor offset. OCCU is gated by flag 8.
       Initial counters remain zero until their game events are ported. */
    if (item->inci.present) {
        frame = building_render_inci_frame(item, runtime_location->inci_progress);
        if (frame < sheet->frame_count) {
            draw_sprite_scaled(dc, sheet, frame, x, y, scale_16_16);
            drew = 1;
        }
    }
    if (item->cons.present) {
        frame = building_render_cons_frame(item, runtime_location->construction_progress,
                                           runtime_location->source_flags);
        if (frame < sheet->frame_count) {
            draw_sprite_scaled(dc, sheet, frame, x, y, scale_16_16);
            drew = 1;
        }
    }
    if (item->prod.present) {
        BuildingRenderPoint prod_position =
            building_render_prod_frame_position(x, y);
        frame = building_render_prod_frame(item, runtime_location->production_progress,
                                           runtime_location->source_flags);
        if (frame < sheet->frame_count) {
            draw_sprite_scaled(dc, sheet, frame, prod_position.x, prod_position.y,
                               scale_16_16);
            drew = 1;
        }
    }
    if (item->occu.present && (runtime_location->source_flags & 8U) != 0) {
        frame = (uint32_t)item->occu.first_frame - 1U;
        if (frame < sheet->frame_count) {
            draw_sprite_scaled(dc, sheet, frame, x, y, scale_16_16);
            drew = 1;
        }
    }
    if (item->barg.present) {
        frame = building_render_barg_frame(item, runtime_location->barg_progress);
        if (frame < sheet->frame_count) {
            draw_sprite_scaled(dc, sheet, frame, x, y, scale_16_16);
            drew = 1;
        }
    }
    return drew;
}

static int draw_runtime_item(HDC dc, const GameRuntimeLocation *runtime_location,
                             int x, int y)
{
    return draw_runtime_item_scaled(dc, runtime_location, x, y, 0x10000U);
}

/* FUN_0040d3e1 builds a temporary default item and calls FUN_0040bf98 with
   animation disabled and the requested scale. This shows every declared
   static/idle layer, rather than drawing the asset's frame zero in isolation. */
static int draw_building_preview(HDC dc, uint16_t item_id, uint8_t player_slot,
                                 int x, int y, uint32_t scale_16_16)
{
    GameRuntimeLocation preview;
    memset(&preview, 0, sizeof(preview));
    preview.record_value_10 = item_id;
    preview.owner_id = player_slot;
    preview.source_flags = 0x410U;
    preview.animation_rate = 1;
    return draw_runtime_item_scaled(dc, &preview, x, y, scale_16_16);
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

static void draw_hall_stock_summary(HDC dc, int hall_player,
                                    const GameRuntimeIsland *island)
{
    static const SpriteSheet *const resource_sheets[GAME_RESOURCE_TYPE_COUNT] = {
        &g_bildtone_art, &g_tone_crys_art, &g_magctone_art
    };
    const WindowTemplate *info;
    const GameRuntimeLocation *hall;
    RECT pane;
    int saved_dc;
    unsigned int resource;

    if (hall_player < 0 || island == NULL ||
        g_island_panel_mode != WINDOW_ISLAND_PANEL_GENERAL ||
        g_selected_location < 0 ||
        (uint16_t)g_selected_location >= island->location_count) return;
    info = window_catalog_find(&g_window_catalog, "IWLocInfo", 3);
    if (info == NULL || g_temp_hole_art.frame_count <= 1U) return;

    hall = &island->locations[g_selected_location];
    pane.left = info->pane.left;
    pane.top = info->pane.top;
    pane.right = info->pane.right + 1;
    pane.bottom = info->pane.bottom + 1;
    saved_dc = SaveDC(dc);
    (void)IntersectClipRect(dc, pane.left, pane.top, pane.right, pane.bottom);
    draw_sprite(dc, &g_temp_hole_art, 1, info->pane.left, info->pane.top);
    for (resource = 0; resource < GAME_RESOURCE_TYPE_COUNT; ++resource) {
        IslandHallResourceRow row;
        char amount[8];
        if (!island_panel_info_hall_resource_row(resource, &row)) continue;
        if (resource_sheets[resource]->frame_count > row.icon_frame) {
            draw_sprite(dc, resource_sheets[resource], row.icon_frame,
                        info->pane.left + row.icon_x,
                        info->pane.top + row.icon_y);
        }
        (void)snprintf(amount, sizeof(amount), "%d",
            (int)(int16_t)hall->resource_stock[resource]);
        draw_bitmap_label(dc, amount,
                          info->pane.left + row.amount_x,
                          info->pane.top + row.amount_y,
                          RGB(230, 238, 255));
    }
    {
        char population[96];
        unsigned int count = game_session_count_player_floaters(
            &g_game_session, (uint8_t)hall_player);
        (void)snprintf(population, sizeof(population), "%s %u",
                       g_hall_population_label, count);
        draw_bitmap_label(dc, population,
                          info->pane.left + 0xb6,
                          info->pane.top + 0x29,
                          RGB(230, 238, 255));
    }
    RestoreDC(dc, saved_dc);
}

static void render_island_view(HDC dc)
{
    const int image_top = 0;
    const int status_top = 320;
    const IslandLocation *focus = NULL;
    const GameFloaterStart *selected_floater = NULL;
    int focus_index = g_hovered_location >= 0 ? g_hovered_location : g_selected_location;
    int hall_player = selected_hall_player();
    int saved_dc;
    uint16_t i;
    const GameRuntimeIsland *runtime_island = NULL;

    if (g_game_session_valid && g_menu.selected_map_island >= 0 &&
        g_menu.selected_map_island < g_game_session.island_count) {
        runtime_island = &g_game_session.islands[g_menu.selected_map_island];
        if (g_selected_floater >= 0 &&
            g_selected_floater < g_game_session.floater_count) {
            const GameFloaterStart *candidate =
                &g_game_session.floaters[g_selected_floater];
            if (candidate->island_index == g_menu.selected_map_island) {
                selected_floater = candidate;
            }
        }
    }

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
        uint16_t location_index = g_island_draw_order[i];
        const IslandLocation *location = &g_island_surface_data.locations[location_index];
        const GameRuntimeLocation *runtime_location =
            runtime_island != NULL && location_index < runtime_island->location_count
                ? &runtime_island->locations[location_index] : NULL;
        int x = (int)location->x - g_island_scroll_x;
        int y = image_top + (int)location->y;
        int pad_group = island_pad_group(location);
        int runtime_class = location->renderer_class;
        COLORREF color = island_location_color(location->type);
        int dx;
        int dy;
        if (location->renderer_class == 3 &&
            (location->renderer_variant == 4 || location->renderer_variant == 0x16)) {
            draw_island_feature(dc, g_island_surface_id, location,
                                -g_island_scroll_x, image_top);
            continue;
        }
        /* FUN_00461859 demotes unmatched class-2 records to class 0 at game
           startup. Draw the bridge trigger only for records still paired to a
           world-map neighbor; preserve the source class in the parsed data. */
        if (runtime_location != NULL && location->renderer_class == 2 &&
            runtime_location->bridge_neighbor_island < 0) {
            runtime_class = 0;
        }
        /* The pad catalog's PIT_Object (item 1) and PIT_FeatureTrigger
           (item 3) entries have no shape asset. These item IDs are distinct
           from an island record's renderer_class. */
        if (location->kind == ISLAND_LOCATION_PAD ||
            (location->renderer_class == 3 && location->renderer_variant == 3)) {
            if (runtime_location == NULL || runtime_location->record_value_10 <= 0) continue;
        }
        if (x < -4 || x >= LOGICAL_WIDTH + 4) continue;
        /* The original class-2 bridge site is distinct from class-0 pads.
           bldinf.txt defines BR-TRG01's static BASE as frame 1; the COB's
           corresponding SHP stores that frame at index 0. */
        if (runtime_class == 2 && g_bridge_trigger_art.frame_count == 23) {
            draw_sprite(dc, &g_bridge_trigger_art, 0, x, y);
            continue;
        }
        {
            int drew_location = 0;
        /* Island TXT `tone` rows denote unoccupied Tone pools. shapes.txt maps
           POOL to tone.shp; bldinf.txt gives the 2..40 ping-pong animation. */
        {
        int32_t runtime_item_id = runtime_location != NULL
            ? runtime_location->record_value_10 : 0;
        int covered_by_leviathan_building = runtime_item_id > 0 &&
            runtime_item_id < g_pad_catalog.item_count &&
            g_pad_catalog.items[runtime_item_id].tribe == PAD_TRIBE_LEVIATHAN;
        if (island_tone_pool_should_draw(location->kind == ISLAND_LOCATION_TONE,
                                         runtime_item_id,
                                         covered_by_leviathan_building) &&
            g_tone_field_art.frame_count == 40) {
            uint16_t render_counter = runtime_location != NULL
                ? island_tone_pool_render_counter(runtime_item_id,
                    runtime_location->owner_id,
                    runtime_location->tribe_visibility_mask,
                    g_game_session.config.selected_tribe,
                    runtime_location->chug_progress)
                : 0U;
            uint32_t frame = island_tone_pool_frame(runtime_item_id,
                render_counter);
            /* FUN_0040bf98 draws POOL's BASE segment, then composites CHUG on
               top. bldinf.txt stores BASE 1 1, hence frame zero in decoded SHP. */
            draw_sprite(dc, &g_tone_field_art, ISLAND_TONE_POOL_BASE_FRAME, x, y);
            draw_sprite(dc, &g_tone_field_art, frame, x, y);
            drew_location = 1;
        }
        }
        /* FUN_0040bf98 draws an installed runtime item at this record. Such an
           item occupies the construction site, so its sprite replaces PAD.SHP.
           Keep the animated ring only when no drawable item occupies the site. */
        {
            int occupied = runtime_location != NULL && runtime_location->record_value_10 > 0;
            int has_runtime_item = draw_runtime_item(dc, runtime_location, x, y);
            if (has_runtime_item || occupied) drew_location = 1;
            else if (island_site_should_draw_pad(pad_group, occupied) &&
                     g_pad_art.frame_count == 27) {
                uint32_t frame = island_pad_frame(g_menu.animation_ticks,
                                                  location->x,
                                                  (unsigned)pad_group,
                                                  location->renderer_subtype);
                draw_sprite(dc, &g_pad_art, frame, x, y);
                drew_location = 1;
            }
        }
        if (drew_location) continue;
        }
        for (dy = -2; dy <= 2; ++dy) {
            for (dx = -2; dx <= 2; ++dx) {
                if (dx * dx + dy * dy <= 5) (void)SetPixelV(dc, x + dx, y + dy, color);
            }
        }
    }
    /* FUN_0046466f creates four idle type-0 floaters for each player at the
       selected hall marker. FUN_0042704b draws their tribe-specific legs and
       body separately; shapeinf.txt defines body frame 0 and hover frames 0..15. */
    if (runtime_island != NULL && g_game_session_valid) {
        unsigned floater_index;
        for (floater_index = 0; floater_index < g_game_session.floater_count;
             ++floater_index) {
            const GameFloaterStart *floater = &g_game_session.floaters[floater_index];
            int floater_x;
            int floater_y;
            uint32_t leg_frame;
            const SpriteSheet *body_art;
            const SpriteSheet *leg_art;
            if (floater->island_index != g_menu.selected_map_island ||
                floater->type_index >= 4) continue;
            floater_x = (int)floater->x - g_island_scroll_x;
            if (floater_x < -64 || floater_x >= LOGICAL_WIDTH + 64) continue;
            floater_y = image_top + (int)floater->y;
            leg_frame = g_menu.animation_ticks % 16u;
            body_art = floater->facing_left
                           ? &g_initial_floater_bodies_flipped[floater->type_index]
                           : &g_initial_floater_bodies[floater->type_index];
            leg_art = floater->facing_left
                          ? &g_initial_floater_legs_flipped[floater->type_index]
                          : &g_initial_floater_legs[floater->type_index];
            draw_sprite(dc, leg_art, leg_frame, floater_x, floater_y);
            draw_sprite(dc, body_art, 0, floater_x, floater_y);
            /* FUN_0042822b calls FUN_0042704b with param_5=1 for world
               floaters. The first overlay global gates FLTINFO realm frames
               22..25; other overlay values need runtime state not modeled by
               the startup-floater record. */
            if (island_worker_realm_overlay_enabled(
                    g_floater_overlay_flags, 1) &&
                g_floater_info_art.frame_count >= 26 &&
                body_art->frame_count != 0) {
                const SpriteFrame *body_frame = &body_art->frames[0];
                int32_t body_left = floater_x + body_frame->x_offset +
                                    body_frame->hit_left;
                int32_t body_top = floater_y + body_frame->y_offset +
                                   body_frame->hit_top;
                int32_t body_right = floater_x + body_frame->x_offset +
                                     body_frame->hit_right;
                uint32_t realm_frame;
                int32_t badge_x;
                int32_t badge_y;
                if (island_worker_realm_badge_layout(
                        floater->type_index, 0, 0, floater->facing_left,
                        body_left, body_top, body_right,
                        &realm_frame, &badge_x, &badge_y) &&
                    realm_frame < g_floater_info_art.frame_count) {
                    draw_sprite(dc, &g_floater_info_art, realm_frame,
                                badge_x, badge_y);
                }
            }
            /* FUN_0042704b gates health FLTINFO frames with the second
               TOGREALM flag. Initial workers are created with +0x1c cleared
               by FUN_00466fe4/FUN_0041e4e4, so their world badge is eligible. */
            if (island_worker_health_overlay_enabled(
                    g_floater_overlay_flags, 1) &&
                g_floater_info_art.frame_count >= 26 &&
                body_art->frame_count != 0) {
                const SpriteFrame *body_frame = &body_art->frames[0];
                int32_t body_left = floater_x + body_frame->x_offset +
                                    body_frame->hit_left;
                int32_t body_top = floater_y + body_frame->y_offset +
                                   body_frame->hit_top;
                int32_t body_right = floater_x + body_frame->x_offset +
                                     body_frame->hit_right;
                uint32_t health_frame;
                int32_t badge_x;
                int32_t badge_y;
                if (island_worker_health_badge_layout(
                        floater->type_index, floater->max_hit_points,
                        floater->facing_left, body_left, body_top, body_right,
                        &health_frame, &badge_x, &badge_y) &&
                    health_frame < g_floater_info_art.frame_count) {
                    draw_sprite(dc, &g_floater_info_art, health_frame,
                                badge_x, badge_y);
                }
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

    /* windows.txt declares the always-present island controls separately from
       ISLETEMP. FUN_0042fa0f shows GOTOMAP/PANIC/TOGREALM/TASKLIST at entry to
       island state; mainbut0.shp supplies their normal and adjacent hover
       frames, while ISREALM is the companion left-panel artwork. */
    {
        const WindowTemplate *realm_panel = window_catalog_find(
            &g_window_catalog, "IWRealm", 3);
        static const char *const button_names[] = {
            "GOTOMAP", "PANIC", "TOGREALM", "TASKLIST"
        };
        size_t button_index;
        if (realm_panel != NULL && g_island_realm_art.frame_count != 0) {
            draw_sprite(dc, &g_island_realm_art,
                        (uint32_t)realm_panel->shape_frame,
                        realm_panel->pane.left, realm_panel->pane.top);
        }
        for (button_index = 0;
             button_index < sizeof(button_names) / sizeof(button_names[0]);
             ++button_index) {
            const WindowTemplate *button = window_catalog_find(
                &g_window_catalog, button_names[button_index], 3);
            int frame;
            if (button == NULL || button->shape_frame < 0) continue;
            frame = window_catalog_control_frame(
                button, (int)button_index == g_hovered_island_button);
            if (frame >= 0 && (uint32_t)frame < g_island_main_buttons.frame_count) {
                draw_sprite(dc, &g_island_main_buttons, (uint32_t)frame,
                            button->pane.left, button->pane.top);
            }
        }
    }

    draw_hall_panel(dc, hall_player);
    draw_hall_stock_summary(dc, hall_player, runtime_island);

    /* The five Hall command controls are clickable THALL frames from the
       active island palette. Their descriptors also own the hover bounds. */
    if (hall_player >= 0) {
        static const char *const command_names[] = {
            "BC_GenInfo", "BC_Storage", "BC_Knowledge",
            "BC_Diplomacy", "BC_Trade"
        };
        size_t command_index;
        for (command_index = 0;
             command_index < sizeof(command_names) / sizeof(command_names[0]);
             ++command_index) {
            const WindowTemplate *button = window_catalog_find(
                &g_window_catalog, command_names[command_index], 3);
            int frame;
            if (button == NULL) continue;
            frame = window_catalog_control_frame(button,
                window_catalog_hall_panel_mode(button->name) ==
                    g_hovered_hall_command);
            if (frame >= 0 && (uint32_t)frame < g_hall_command_art.frame_count) {
                draw_sprite(dc, &g_hall_command_art, (uint32_t)frame,
                            button->pane.left, button->pane.top);
            }
        }
    }

    /* windows.txt places IWLilMap at (192,328)-(447,359), and shapes.txt
       binds it to the 16-frame LILMAP sheet. The SHP frame is indexed by the
       selected island's existing surface id (the local 15-island corpus uses
       the corresponding first 15 frames). */
    if (g_island_surface_id >= 0 && g_island_surface_id < 16) {
        const WindowTemplate *mini_map = window_catalog_find(
            &g_window_catalog, "IWLilMap", 16);
        if (mini_map != NULL) {
            draw_sprite(dc, &g_island_lilmap_art,
                        (uint32_t)g_island_surface_id,
                        mini_map->pane.left, mini_map->pane.top);
        }
    }

    /* BC_HallStkB/C/M are the original Hall reserve controls. Their state
       selects THBUTT frames 1..3; windows.txt assigns hover frame 4. */
    if (hall_player >= 0 && g_hall_stock_art.frame_count >= 5) {
        static const char *const stock_control_names[GAME_RESOURCE_TYPE_COUNT] = {
            "BC_HallStkB", "BC_HallStkC", "BC_HallStkM"
        };
        unsigned int resource;
        for (resource = 0; resource < GAME_RESOURCE_TYPE_COUNT; ++resource) {
            const WindowTemplate *button = window_catalog_find(
                &g_window_catalog, stock_control_names[resource], 3);
            uint32_t frame;
            if (button == NULL) continue;
            frame = (uint32_t)button->shape_frame +
                g_game_session.economy[hall_player].stock_mode[resource];
            if ((int)resource == g_hovered_hall_stock && button->has_hilite_frame) {
                frame = (uint32_t)button->hilite_frame;
            }
            if (frame < g_hall_stock_art.frame_count) {
                draw_sprite(dc, &g_hall_stock_art, frame,
                            button->pane.left, button->pane.top);
            }
        }
    }

    draw_iw_construct(dc);
    if (selected_floater != NULL && selected_floater->type_index < 4) {
        const WindowTemplate *info = window_catalog_find(
            &g_window_catalog, "IWLocInfo", 3);
        if (info != NULL && g_temp_hole_art.frame_count > 1) {
            RECT pane = {info->pane.left, info->pane.top,
                         info->pane.right + 1, info->pane.bottom + 1};
            int saved_info_dc = SaveDC(dc);
            (void)IntersectClipRect(dc, pane.left, pane.top,
                                    pane.right, pane.bottom);
            draw_sprite(dc, &g_temp_hole_art, 1,
                        info->pane.left, info->pane.top);

            /* FUN_0044338b (Iwloc.cpp) draws the selected object's details in
               IWLocInfo. Initial workers are class 0, level 0, and have the
               four tribe-specific *work rows: 3 hit points and 0 strength.
               FUN_00466fe4 initializes current hits to FUN_00420f28's max. */
            draw_bitmap_label(dc, "WORKER",
                              info->pane.left + 5, info->pane.top + 3,
                              RGB(230, 238, 255));
            {
                char hit_points_label[24];
                char strength_label[24];
                (void)snprintf(hit_points_label, sizeof(hit_points_label),
                    "HITS %u/%u",
                    (unsigned int)selected_floater->current_hit_points,
                    (unsigned int)selected_floater->max_hit_points);
                (void)snprintf(strength_label, sizeof(strength_label),
                    "STRENGTH %u",
                    (unsigned int)selected_floater->attack_strength);
                draw_bitmap_label(dc, hit_points_label,
                                  info->pane.left + 5, info->pane.top + 23,
                                  RGB(230, 238, 255));
                draw_bitmap_label(dc, strength_label,
                                  info->pane.left + 5, info->pane.top + 33,
                                  RGB(230, 238, 255));
            }

            /* FUN_0044338b places the selected unit sprite to the right of
               the text. The island renderer's original base-worker sheets
               supply the same body and animated legs used in the world view. */
            {
                uint32_t leg_frame = g_menu.animation_ticks % 16u;
                int sprite_x = info->pane.right - 50;
                int sprite_y = info->pane.top +
                    (info->pane.bottom - info->pane.top) / 2;
                const SpriteSheet *body_art = selected_floater->facing_left
                    ? &g_initial_floater_bodies_flipped[selected_floater->type_index]
                    : &g_initial_floater_bodies[selected_floater->type_index];
                const SpriteSheet *leg_art = selected_floater->facing_left
                    ? &g_initial_floater_legs_flipped[selected_floater->type_index]
                    : &g_initial_floater_legs[selected_floater->type_index];
                const SpriteFrame *body_frame = &body_art->frames[0];
                draw_sprite(dc, leg_art, leg_frame, sprite_x, sprite_y);
                draw_sprite(dc, body_art, 0, sprite_x, sprite_y);
                /* FUN_0044338b enables the info flags around this sprite.
                   FUN_0042003c maps the startup *work row's realm to frames
                   22..25 and adjusts it from the retained current-location
                   flags when that location context is available. */
                if (g_floater_info_art.frame_count >= 26) {
                    uint32_t realm_frame;
                    int32_t badge_x;
                    int32_t badge_y;
                    const GameRuntimeLocation *current_location = NULL;
                    if (runtime_island != NULL && g_selected_location >= 0 &&
                        g_selected_location < runtime_island->location_count) {
                        current_location = &runtime_island->locations[g_selected_location];
                    }
                    int32_t body_left = sprite_x + body_frame->x_offset +
                                        body_frame->hit_left;
                    int32_t body_top = sprite_y + body_frame->y_offset +
                                       body_frame->hit_top;
                    int32_t body_right = sprite_x + body_frame->x_offset +
                                         body_frame->hit_right;
                    if (island_worker_realm_badge_layout(
                            selected_floater->type_index,
                            current_location != NULL,
                            current_location == NULL ? 0 : current_location->source_flags,
                            selected_floater->facing_left,
                            body_left, body_top, body_right,
                            &realm_frame, &badge_x, &badge_y) &&
                        realm_frame < g_floater_info_art.frame_count) {
                        draw_sprite(dc, &g_floater_info_art, realm_frame,
                                    badge_x, badge_y);
                    }
                }
                /* Health frame and anchor are independently derived from
                   FUN_0042704b / FUN_00420f28. */
                if (g_floater_info_art.frame_count >= 26) {
                    uint32_t health_frame;
                    int32_t badge_x;
                    int32_t badge_y;
                    int32_t body_left = sprite_x + body_frame->x_offset +
                                        body_frame->hit_left;
                    int32_t body_top = sprite_y + body_frame->y_offset +
                                       body_frame->hit_top;
                    int32_t body_right = sprite_x + body_frame->x_offset +
                                         body_frame->hit_right;
                    if (island_worker_health_badge_layout(
                            selected_floater->type_index,
                            selected_floater->max_hit_points,
                            selected_floater->facing_left,
                            body_left, body_top, body_right,
                            &health_frame, &badge_x, &badge_y) &&
                        health_frame < g_floater_info_art.frame_count) {
                        draw_sprite(dc, &g_floater_info_art, health_frame,
                                    badge_x, badge_y);
                    }
                }
            }
            if (saved_info_dc != 0) RestoreDC(dc, saved_info_dc);
        }
    } else if (runtime_island != NULL && g_selected_location >= 0 &&
               g_selected_location < runtime_island->location_count) {
        const GameRuntimeLocation *selected_location =
            &runtime_island->locations[g_selected_location];
        int32_t raw_item_id = selected_location->record_value_10;
        if (raw_item_id >= 0x25 && raw_item_id < g_pad_catalog.item_count) {
            char level_label[24];
            size_t name_index = (size_t)(raw_item_id - 0x25);
            const WindowTemplate *info = window_catalog_find(
                &g_window_catalog, "IWLocInfo", 3);
            if (name_index < BUILDING_NAME_COUNT &&
                g_building_names[name_index][0] != '\0' && info != NULL &&
                g_temp_hole_art.frame_count > 1) {
                RECT pane = {info->pane.left, info->pane.top,
                             info->pane.right + 1, info->pane.bottom + 1};
                int saved_info_dc = SaveDC(dc);
                (void)IntersectClipRect(dc, pane.left, pane.top,
                                        pane.right, pane.bottom);
                draw_sprite(dc, &g_temp_hole_art, 1,
                            info->pane.left, info->pane.top);
                /* FUN_0044338b reads BLDNAME through the per-tribe item
                   ordinal. Runtime item IDs in this port already include
                   the tribe's 16-item block, so subtracting PIT_BuildToneProducer
                   (0x25) selects the matching entry in bldname.txt. */
                draw_bitmap_label(dc, g_building_names[name_index],
                                  info->pane.left + 5, info->pane.top + 3,
                                  RGB(230, 238, 255));
                /* FUN_0044338b displays FUN_0041ff2e()+1 for LEVEL;
                   FUN_0041ff2e reads the selected runtime word at +0x0a,
                   masked to its low nibble. */
                (void)snprintf(level_label, sizeof(level_label), "LEVEL %u",
                    (unsigned int)game_session_location_display_level(selected_location));
                draw_bitmap_label(dc, level_label,
                                  info->pane.left + 5, info->pane.top + 18,
                                  RGB(230, 238, 255));
                /* The source paints the selected building in IWLocInfo via
                   FUN_0042704b. Reuse the same data-driven BASE/CHUG/etc.
                   layers already used by the island renderer. */
                {
                    int sprite_x;
                    int sprite_y;
                    if (island_panel_info_building_sprite_position(
                            info, &sprite_x, &sprite_y)) {
                        /* FUN_0044338b passes full scale (0x10000) and a
                           pane-relative width/height anchor to FUN_0042704b. */
                        (void)draw_runtime_item_scaled(dc, selected_location,
                            sprite_x, sprite_y, 0x10000U);
                    }
                }
                if (saved_info_dc != 0) RestoreDC(dc, saved_info_dc);
            }
        }
    }
    /* FUN_00440567 redraws the six IWLocInfo roster slots after preparing
       them in FUN_0044034e. This prototype has only the initial class-0
       workers, and the selected starting Hall is the only modeled roster
       context with a source-backed player list. */
    {
        int player = selected_hall_player();
        if (player >= 0) {
            const WindowTemplate *info = window_catalog_find(
                &g_window_catalog, "IWLocInfo", 3);
            int roster[ISLAND_PANEL_INFO_ROSTER_SLOT_COUNT];
            uint8_t count = collect_initial_worker_roster((unsigned int)player,
                                                          roster);
            uint8_t slot;
            if (info != NULL && count != 0) {
                RECT pane = {info->pane.left, info->pane.top,
                             info->pane.right + 1, info->pane.bottom + 1};
                int saved_roster_dc = SaveDC(dc);
                (void)IntersectClipRect(dc, pane.left, pane.top,
                                        pane.right, pane.bottom);
                for (slot = 0; slot < count; ++slot) {
                    const GameFloaterStart *floater =
                        &g_game_session.floaters[roster[slot]];
                    const SpriteSheet *body_art;
                    const SpriteSheet *leg_art;
                    int offset_x;
                    int offset_y;
                    if (!island_panel_info_roster_position(slot, 0,
                                                          &offset_x, &offset_y)) {
                        continue;
                    }
                    body_art = floater->facing_left
                        ? &g_initial_floater_bodies_flipped[floater->type_index]
                        : &g_initial_floater_bodies[floater->type_index];
                    leg_art = floater->facing_left
                        ? &g_initial_floater_legs_flipped[floater->type_index]
                        : &g_initial_floater_legs[floater->type_index];
                    if (leg_art->frame_count != 0) {
                        draw_sprite(dc, leg_art,
                            g_menu.animation_ticks % leg_art->frame_count,
                            info->pane.left + offset_x,
                            info->pane.top + offset_y);
                    }
                    if (body_art->frame_count != 0) {
                        draw_sprite(dc, body_art, 0,
                            info->pane.left + offset_x,
                            info->pane.top + offset_y);
                    }
                }
                if (saved_roster_dc != 0) RestoreDC(dc, saved_roster_dc);
            }
        }
    }
    draw_location_action_panel(dc);
}

static void draw_location_action_panel(HDC dc)
{
    const GameRuntimeIsland *island;
    const WindowTemplate *panel;
    const WindowTemplate *button;
    const WindowTemplate *text_panel;
    IslandLocationActionControl action;
    const char *button_name;

    if (!g_game_session_valid || g_menu.screen != SCREEN_ISLAND ||
        g_menu.selected_map_island < 0 ||
        g_menu.selected_map_island >= g_game_session.island_count ||
        g_selected_location < 0) return;
    island = &g_game_session.islands[g_menu.selected_map_island];
    if (g_selected_location >= island->location_count) return;
    panel = window_catalog_find(&g_window_catalog, "IWLocControl", 3);
    if (panel != NULL && panel->shape_frame >= 0 &&
        (uint32_t)panel->shape_frame < g_temp_hole_art.frame_count) {
        draw_sprite(dc, &g_temp_hole_art, (uint32_t)panel->shape_frame,
                    panel->pane.left, panel->pane.top);
    }

    action = selected_location_action();
    button_name = action == ISLAND_LOCATION_ACTION_HALL_MOVE
        ? "IWHallMove" : action == ISLAND_LOCATION_ACTION_MOVE
        ? "IWMove" : NULL;
    if (button_name == NULL) return;
    button = window_catalog_find(&g_window_catalog, button_name, 3);
    if (button != NULL && button->shape_frame >= 0 &&
        (uint32_t)button->shape_frame < g_hall_stock_art.frame_count) {
        /* windows.txt binds both move controls to THBUTT frame 5. */
        draw_sprite(dc, &g_hall_stock_art, (uint32_t)button->shape_frame,
                    button->pane.left, button->pane.top);
    }
    if (g_hovered_location_action != action) return;
    text_panel = window_catalog_find(&g_window_catalog, "IWTextInfo", 3);
    if (text_panel == NULL || text_panel->shape_frame < 0 ||
        (uint32_t)text_panel->shape_frame >= g_temp_hole_art.frame_count) return;
    draw_sprite(dc, &g_temp_hole_art, (uint32_t)text_panel->shape_frame,
                text_panel->pane.left, text_panel->pane.top);
    if (g_cryptic_text[1][0] != '\0') {
        size_t text_length = strlen(g_cryptic_text[1]);
        int text_width = measure_bitmap_text(NULL, g_cryptic_text[1], text_length);
        int text_height = (int)g_bitmap_font.height;
        int pane_width = text_panel->pane.right - text_panel->pane.left;
        int pane_height = text_panel->pane.bottom - text_panel->pane.top;
        draw_bitmap_label(dc, g_cryptic_text[1],
            text_panel->pane.left + (pane_width - text_width) / 2,
            text_panel->pane.top + (pane_height - text_height) / 2,
            g_island_palette[6]);
    }
}

/* The x87 helpers called by FUN_00471536 continue past Ghidra's short
   function boundaries: static disassembly shows FCOS at 0x477ad2 and FSIN at
   0x477332. The constructor supplies the two scale factors used here. */
static void render_world_map(HDC dc)
{
    const WorldDefinition *world;
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
            if (!game_session_world_bridge_is_renderable(&g_game_session,
                    (uint8_t)bridge_index, world->bridge_count,
                    bridge->island_a, bridge->island_b)) continue;
            const WorldIsland *a = &world->islands[bridge->island_a];
            const WorldIsland *b = &world->islands[bridge->island_b];
            int ax;
            int ay;
            int bx;
            int by;
            world_island_position(a, &ax, &ay);
            world_island_position(b, &bx, &by);
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
                unsigned color = bridge_colors[
                    world_map_visual_sample(g_menu.animation_ticks,
                                            bridge_index, step, -1) % 8u];
                int spark;
                for (spark = 0; spark < 10; ++spark) {
                    uint32_t random_value = world_map_visual_sample(
                        g_menu.animation_ticks, bridge_index, step, spark);
                    int x_jitter = (width + 1) / 2 -
                        (int)(random_value % (unsigned)(width + 1));
                    int y_jitter = (width + 1) / 2 -
                        (int)(((random_value >> 8) % (unsigned)(width + 1)));
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
        uint32_t frame = world_island_frame_index(
            island_index, island->shape_id, g_hovered_island == (int)island_index);
        world_island_position(island, &x, &y);
        draw_sprite(dc, &g_small_islands, frame, x, y);
    }
    {
        int island_index = g_hovered_island >= 0 ? g_hovered_island : g_menu.selected_map_island;
        if (island_index >= 0 && (size_t)island_index < world->island_count &&
            game_session_can_enter_island(&g_game_session,
                (uint8_t)island_index, world_map_player_mask())) {
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

static void dispatch_newgame_master_message(HWND window, int message)
{
    if (message == 52) {
        (void)begin_new_game(window);
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
            dispatch_newgame_master_message(window, control->send_message[0]);
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
        {
            IslandLocationActionControl action = selected_location_action();
            const char *action_name = action == ISLAND_LOCATION_ACTION_HALL_MOVE
                ? "IWHallMove" : action == ISLAND_LOCATION_ACTION_MOVE
                ? "IWMove" : NULL;
            if (action_name != NULL) {
                static const char *const action_names[] = {"IWMove", "IWHallMove"};
                const WindowTemplate *action_control =
                    window_catalog_hit_test_names(&g_window_catalog, 3, x, y,
                                                   action_names, 2);
                if (action_control != NULL &&
                    strcmp(action_control->name, action_name) == 0) {
                    /* The source action handler is not resolved. Consume this
                       control hit so it cannot fall through to location deselect. */
                    return;
                }
            }
        }
        if (adjust_trade_cell(x, y, 1)) {
            InvalidateRect(window, NULL, FALSE);
            return;
        }
        const WindowTemplate *construct = window_catalog_find(
            &g_window_catalog, "IWConstruct", 3);
        const WindowTemplate *cycle = window_catalog_find(&g_window_catalog,
                                                           "BuildCycle", 3);
        IwConstructClickTarget click_target = iw_construct_click_target(
            g_iw_construct_open,
            construct != NULL ? &construct->pane : NULL,
            cycle != NULL && g_iw_construct.cycle_button_visible
                ? &cycle->pane : NULL,
            x, y);
        if (click_target == IW_CONSTRUCT_CLICK_CYCLE) {
            IwConstructTransition transition;
            iw_construct_build_cycle(&g_iw_construct, g_iw_construct_item_count,
                                     &transition);
            (void)apply_iw_construct_messages(&transition);
            (void)update_iw_construct_hover(x, y);
        } else if (click_target == IW_CONSTRUCT_CLICK_GRID) {
            (void)update_iw_construct_hover(x, y);
            if (select_iw_construct_item()) {
                InvalidateRect(window, NULL, FALSE);
            }
        } else {
            /* IWConstruct overlaps the Hall's stock buttons in ISLETMP. Keep
               clicks modal only inside its panes; an outside click dismisses
               it and continues through the normal island/Hall hit routing.
               Without this, clicking the Hall location is swallowed and the
               Hall panel can never become selected after opening the grid. */
            if (g_iw_construct_open) {
                g_iw_construct_open = 0;
                g_iw_construct.hovered_column = -1;
                (void)iw_construct_info_handle_message(
                    &g_iw_construct_info, 1, 0);
            }
            static const char *const island_button_names[] = {
                "GOTOMAP", "PANIC", "TOGREALM", "TASKLIST"
            };
            static const char *const hall_command_names[] = {
                "BC_GenInfo", "BC_Storage", "BC_Knowledge", "BC_Trade", "BC_Diplomacy"
            };
            const WindowTemplate *island_control = window_catalog_hit_test_names(
                &g_window_catalog, 3, x, y, island_button_names,
                sizeof(island_button_names) / sizeof(island_button_names[0]));
            int hall_player = selected_hall_player();
            const WindowTemplate *hall_control = hall_player >= 0
                ? window_catalog_hit_test_names(&g_window_catalog, 3, x, y,
                    hall_command_names,
                    sizeof(hall_command_names) / sizeof(hall_command_names[0]))
                : NULL;
            static const char *const inventory_controls[] = {"InvCycle"};
            static const char *const trade_controls[] = {"TradeZERO", "TradeDOIT"};
            const WindowTemplate *inventory_cycle =
                hall_player >= 0 &&
                g_island_panel_mode == WINDOW_ISLAND_PANEL_INVENTORY
                ? window_catalog_hit_test_names(&g_window_catalog, 3, x, y,
                    inventory_controls, 1) : NULL;
            const WindowTemplate *trade_control =
                hall_player >= 0 &&
                g_island_panel_mode == WINDOW_ISLAND_PANEL_TRADE
                ? window_catalog_hit_test_names(&g_window_catalog, 3, x, y,
                    trade_controls, 2) : NULL;
            int button_index = island_control != NULL
                ? island_button_index(island_control->name) : -1;
            int stock_control = hall_player >= 0 ? hall_stock_control_at(x, y) : -1;
            int clicked_roster_floater = hall_player >= 0
                ? selected_hall_roster_hit_test(x, y) : -1;
            int hall_panel_mode = hall_control != NULL
                ? window_catalog_hall_panel_mode(hall_control->name)
                : WINDOW_ISLAND_PANEL_NONE;
            if (click_diplomacy_action(x, y, hall_player)) {
                /* FUN_0043e296 sends subtype 10 from the active local Hall. */
            } else if (trade_control != NULL) {
                if (strcmp(trade_control->name, "TradeZERO") == 0) {
                    (void)game_session_clear_trade_offers(
                        &g_game_session, (uint8_t)hall_player);
                } else {
                    /* FUN_0042fa0f(4011) queues type-0xb messages for each
                       recipient with a nonzero row, then clears the table.
                       The outbox is retained; multiplayer transport is not
                       present in this remake. */
                    (void)game_session_commit_trade_offers(
                        &g_game_session, (uint8_t)hall_player);
                }
            } else if (button_index >= 0) {
                if (button_index == WINDOW_ISLAND_BUTTON_MAP) {
                    g_menu.screen = SCREEN_WORLD_MAP;
                    g_selected_floater = -1;
                    g_selected_location = -1;
                    g_hovered_location = -1;
                    g_hovered_island_button = -1;
                    g_hovered_hall_command = -1;
                    g_hovered_inventory_item = -1;
                    g_selected_inventory_item = -1;
                    update_window_title(window);
                } else if (button_index == WINDOW_ISLAND_BUTTON_TASKS) {
                    g_island_panel_mode =
                        g_island_panel_mode == WINDOW_ISLAND_PANEL_TASKS
                        ? WINDOW_ISLAND_PANEL_GENERAL : WINDOW_ISLAND_PANEL_TASKS;
                } else if (button_index == WINDOW_ISLAND_BUTTON_REALM) {
                    /* FUN_0042fa0f assigns each source global (flag == 0),
                       independently normalizing and flipping all three. */
                    g_floater_overlay_flags =
                        island_toggle_realm_overlay_flags(g_floater_overlay_flags);
                } else if (button_index == WINDOW_ISLAND_BUTTON_PANIC) {
                    /* 2002 -> FUN_0042fa0f(0x3b) -> type 3/subtype 0.
                       FUN_00465793 toggles bit 0 in this player's raw island
                       word; what consumes or displays that bit is unknown. */
                    if (g_game_session_valid &&
                        g_menu.selected_tribe < GAME_START_PLAYER_COUNT &&
                        g_menu.selected_map_island >= 0 &&
                        g_menu.selected_map_island < g_game_session.island_count) {
                        (void)game_session_queue_island_event3_subtype0(
                            &g_game_session, g_menu.selected_tribe,
                            (uint8_t)g_menu.selected_map_island);
                    }
                }
            } else if (hall_panel_mode != WINDOW_ISLAND_PANEL_NONE) {
                g_iw_construct_open = 0;
                g_island_panel_mode = hall_panel_mode;
                g_hovered_hall_command = hall_panel_mode;
                g_diplomacy_hover_valid = 0;
                g_hovered_glyph = -1;
                g_glyph_info_default =
                    hall_panel_mode == WINDOW_ISLAND_PANEL_GLYPHS;
                if (hall_panel_mode == WINDOW_ISLAND_PANEL_INVENTORY) {
                    g_inventory_page = 0;
                    g_hovered_inventory_item = -1;
                    g_selected_inventory_item = -1;
                    g_inventory_info_mode = ISLAND_PANEL_INFO_INVENTORY_DEFAULT;
                } else {
                    g_selected_inventory_item = -1;
                }
            } else if (inventory_cycle != NULL &&
                game_inventory_collect(
                    g_game_session.economy[(unsigned int)hall_player].inventory_count,
                    NULL, 0) > GAME_INVENTORY_PAGE_SIZE) {
                g_inventory_page = game_inventory_next_page(g_inventory_page,
                    game_inventory_collect(
                        g_game_session.economy[(unsigned int)hall_player].inventory_count,
                        NULL, 0));
                g_hovered_inventory_item = -1;
            } else if (stock_control >= 0) {
                (void)game_session_cycle_resource_stock_mode(
                    &g_game_session, (uint8_t)hall_player,
                    (GameResourceType)stock_control);
            } else if (clicked_roster_floater >= 0) {
                IslandPanelSelection selection = {
                    g_selected_location, g_selected_floater
                };
                /* FUN_0042fa0f's 0x3f branch changes the floater selection
                   while retaining the selected IWLocInfo location context. */
                island_panel_select_floater(&selection,
                                             clicked_roster_floater);
                g_selected_location = selection.location_index;
                g_selected_floater = clicked_roster_floater;
                g_hovered_location = -1;
            } else {
                int clicked_floater = g_game_session_valid
                    ? game_session_floater_at(&g_game_session,
                        (uint8_t)g_menu.selected_map_island,
                        (uint16_t)(x + g_island_scroll_x), (uint16_t)y)
                    : -1;
                if (clicked_floater >= 0) {
                    IslandPanelSelection selection = {
                        g_selected_location, g_selected_floater
                    };
                    island_panel_select_floater(&selection, clicked_floater);
                    g_selected_location = selection.location_index;
                    g_selected_floater = clicked_floater;
                    g_hovered_location = -1;
                    InvalidateRect(window, NULL, FALSE);
                } else {
                    int clicked_location = island_location_at(x, y);
                    g_selected_floater = -1;
                    if (clicked_location >= 0) {
                        if (g_selected_inventory_item >=
                                GAME_INVENTORY_ITEM_FIRST_ID &&
                            g_selected_inventory_item <
                                GAME_INVENTORY_ITEM_FIRST_ID +
                                GAME_INVENTORY_ITEM_COUNT &&
                            g_menu.selected_tribe < GAME_START_PLAYER_COUNT) {
                            (void)game_session_queue_inventory_action(
                                &g_game_session, g_menu.selected_tribe,
                                (uint8_t)g_menu.selected_map_island,
                                (uint16_t)clicked_location,
                                (uint8_t)g_selected_inventory_item);
                            /* FUN_0042fa0f clears the selection and returns
                               to general mode even if the location guard
                               prevented the request from being queued. */
                            island_panel_finish_inventory_target(
                                &g_island_panel_mode,
                                &g_selected_inventory_item,
                                &g_hovered_inventory_item,
                                &g_hovered_hall_command);
                        } else if (g_pending_build_item_id >= 0) {
                            if (place_pending_building(window, clicked_location)) {
                                g_selected_location = clicked_location;
                            }
                        } else {
                            g_selected_location = clicked_location;
                            (void)open_iw_construct(clicked_location);
                        }
                        InvalidateRect(window, NULL, FALSE);
                    } else {
                        g_selected_location = -1;
                        InvalidateRect(window, NULL, FALSE);
                    }
                }
            }
        }
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
    (void)update_hall_stock_hover(x, y);
    (void)update_island_button_hover(x, y);
    (void)update_hall_command_hover(x, y);
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
        if (wparam == 2) {
            keep_background_tune_playing();
            return 0;
        }
        if (wparam == 1 && (g_menu.screen == SCREEN_NEW_GAME ||
                            g_menu.screen == SCREEN_WORLD_MAP ||
                            g_menu.screen == SCREEN_ISLAND)) {
            ++g_menu.animation_ticks;
            if (g_menu.screen == SCREEN_WORLD_MAP && g_mouse_inside) {
                /* Islands orbit under a stationary pointer. Re-hit-test each
                   animation tick so the hover frame follows the moving art. */
                (void)update_world_map_hover(g_mouse_x, g_mouse_y);
            }
            if (g_menu.screen == SCREEN_ISLAND && g_game_session_valid) {
                game_session_dispatch_island_events(&g_game_session);
                game_session_tick_item_animations(&g_game_session,
                                                  &g_building_render_catalog);
                game_session_tick_floater_moves(&g_game_session,
                                                g_menu.animation_ticks);
            }
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
            int construct_hover_changed = update_iw_construct_hover(-1, -1);
            int inventory_hover_changed = update_inventory_hover(-1, -1);
            int diplomacy_hover_changed = update_diplomacy_hover(-1, -1);
            int action_hover_changed = update_location_action_hover(-1, -1);
            if (g_mouse_inside || g_hovered_help != -1 || g_hovered_newgame_text != -1 ||
                g_hovered_island != -1 || g_hovered_location != -1 ||
                g_hovered_hall_stock != -1 || g_hovered_island_button != -1 ||
                g_hovered_hall_command != WINDOW_ISLAND_PANEL_NONE ||
                action_hover_changed ||
                inventory_hover_changed || diplomacy_hover_changed) {
                g_mouse_inside = 0;
                if (g_hovered_help != -1 || g_hovered_newgame_text != -1 ||
                    g_hovered_island != -1 || g_hovered_location != -1 ||
                    g_hovered_hall_stock != -1 || g_hovered_island_button != -1 ||
                    g_hovered_hall_command != WINDOW_ISLAND_PANEL_NONE ||
                    action_hover_changed ||
                    inventory_hover_changed || diplomacy_hover_changed) {
                    g_hovered_help = -1;
                    g_hovered_newgame_text = -1;
                    g_hovered_island = -1;
                    g_hovered_location = -1;
                    g_hovered_hall_stock = -1;
                    g_hovered_island_button = -1;
                    g_hovered_hall_command = WINDOW_ISLAND_PANEL_NONE;
                    g_hovered_location_action = ISLAND_LOCATION_ACTION_NONE;
                    InvalidateRect(window, NULL, FALSE);
                }
            }
            if (construct_hover_changed) InvalidateRect(window, NULL, FALSE);
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
            update_island_location_hover(g_mouse_x, g_mouse_y) |
            update_hall_stock_hover(g_mouse_x, g_mouse_y) |
            update_location_action_hover(g_mouse_x, g_mouse_y) |
            update_island_button_hover(g_mouse_x, g_mouse_y) |
            update_hall_command_hover(g_mouse_x, g_mouse_y) |
            update_inventory_hover(g_mouse_x, g_mouse_y) |
            update_glyph_hover(g_mouse_x, g_mouse_y) |
            update_diplomacy_hover(g_mouse_x, g_mouse_y) |
            update_iw_construct_hover(g_mouse_x, g_mouse_y)) {
            InvalidateRect(window, NULL, FALSE);
        }
        return 0;
    }
    case WM_MOUSELEAVE:
        g_mouse_inside = 0;
        (void)update_iw_construct_hover(-1, -1);
        (void)update_diplomacy_hover(-1, -1);
        if (g_hovered_help != -1 || g_hovered_newgame_text != -1 ||
            g_hovered_island != -1 || g_hovered_location != -1 ||
            g_hovered_hall_stock != -1 || g_hovered_island_button != -1 ||
            g_hovered_hall_command != WINDOW_ISLAND_PANEL_NONE ||
            g_hovered_location_action != ISLAND_LOCATION_ACTION_NONE ||
            g_hovered_inventory_item != -1 || g_diplomacy_hover_valid) {
            if (g_hovered_inventory_item != -1 &&
                g_island_panel_mode == WINDOW_ISLAND_PANEL_INVENTORY) {
                g_inventory_info_mode = ISLAND_PANEL_INFO_INVENTORY_DETAIL;
            }
            g_hovered_help = -1;
            g_hovered_newgame_text = -1;
            g_hovered_island = -1;
            g_hovered_location = -1;
            g_hovered_hall_stock = -1;
            g_hovered_island_button = -1;
            g_hovered_hall_command = WINDOW_ISLAND_PANEL_NONE;
            g_hovered_location_action = ISLAND_LOCATION_ACTION_NONE;
            g_hovered_inventory_item = -1;
            g_diplomacy_hover_valid = 0;
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
    case WM_RBUTTONDOWN:
        /* Right-click was incorrectly exposed as a worker order. The source
           input mode and class gates are not yet implemented. */
        return 0;
    case WM_RBUTTONUP: {
        RECT client;
        RECT viewport;
        int width;
        int height;
        int x;
        int y;
        GetClientRect(window, &client);
        width = client.right - client.left;
        height = client.bottom - client.top;
        if (!logical_viewport(width, height, &viewport) ||
            GET_X_LPARAM(lparam) < viewport.left ||
            GET_X_LPARAM(lparam) >= viewport.right ||
            GET_Y_LPARAM(lparam) < viewport.top ||
            GET_Y_LPARAM(lparam) >= viewport.bottom) return 0;
        x = ((GET_X_LPARAM(lparam) - viewport.left) * LOGICAL_WIDTH) /
            (viewport.right - viewport.left);
        y = ((GET_Y_LPARAM(lparam) - viewport.top) * LOGICAL_HEIGHT) /
            (viewport.bottom - viewport.top);
        if (adjust_trade_cell(x, y, -1) ||
            click_diplomacy_action(x, y, selected_hall_player())) {
            InvalidateRect(window, NULL, FALSE);
        }
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
                (void)begin_new_game(window);
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
            dispatch_newgame_master_message(window, 55);
            InvalidateRect(window, NULL, FALSE);
        } else if (g_menu.screen == SCREEN_NEW_GAME && wparam >= '1' && wparam <= '4') {
            dispatch_newgame_master_message(window, 60 + (int)(wparam - '1'));
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
        stop_background_tune();
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

static int load_game_session_for_selected_world(char *error, size_t error_capacity)
{
    CobArchive archive = {0};
    const WorldDefinition *world;
    IslandData island_records[WORLD_MAP_MAX_ISLANDS];
    GameSessionConfig config;
    GameSession session;
    unsigned int island_index;

    if (g_menu.world_index < 0 || g_menu.world_index >= g_menu.world_map.world_count) {
        (void)snprintf(error, error_capacity, "selected world is out of range");
        return 0;
    }
    world = &g_menu.world_map.worlds[g_menu.world_index];
    memset(island_records, 0, sizeof(island_records));
    if (!cob_archive_open("C:\\Program Files\\Tone\\TONE01.COB", &archive,
                          error, error_capacity)) return 0;

    for (island_index = 0; island_index < world->island_count; ++island_index) {
        char member_name[48];
        const CobMember *member;
        unsigned char *bytes;
        int shape_id = world->islands[island_index].shape_id;
        int parsed;

        if (shape_id < 0 || shape_id >= ISLAND_NAME_COUNT) {
            (void)snprintf(error, error_capacity,
                           "world island %u has unsupported shape ID %d",
                           island_index, shape_id);
            cob_archive_close(&archive);
            return 0;
        }
        (void)snprintf(member_name, sizeof(member_name), "data\\island%02d.txt", shape_id);
        member = cob_archive_find(&archive, member_name);
        if (member == NULL) {
            (void)snprintf(error, error_capacity, "%s was not found in TONE01.COB",
                           member_name);
            cob_archive_close(&archive);
            return 0;
        }
        bytes = (unsigned char *)malloc(member->length == 0 ? 1 : member->length);
        if (bytes == NULL) {
            (void)snprintf(error, error_capacity, "could not allocate %s buffer", member_name);
            cob_archive_close(&archive);
            return 0;
        }
        parsed = cob_archive_read_member(&archive, member, bytes, member->length,
                                         error, error_capacity) &&
                 island_data_load(bytes, member->length, &island_records[island_index],
                                  error, error_capacity);
        free(bytes);
        if (!parsed) {
            cob_archive_close(&archive);
            return 0;
        }
    }
    cob_archive_close(&archive);

    memset(&config, 0, sizeof(config));
    config.world_index = (uint8_t)g_menu.world_index;
    config.difficulty = (uint8_t)g_menu.difficulty;
    config.selected_tribe = (uint8_t)g_menu.selected_tribe;
    /* DAT_006136b0's runtime initializer remains unresolved in the source
       analysis. Keep the core's documented explicit default until that is
       resolved; do not infer it from the selected tribe. */
    config.home_island_index = 0;
    config.randomize_class0_assignment = 0;
    config.random_seed = g_random_state;
    if (!game_session_initialize(world, island_records, &config, &session,
                                 error, error_capacity)) return 0;

    g_game_session = session;
    game_music_state_init(&g_game_music);
    g_game_session_world_index = g_menu.world_index;
    g_game_session_valid = 1;
    return 1;
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

static int load_building_render_catalog(char *error, size_t error_capacity)
{
    CobArchive archive = {0};
    const CobMember *pad_member;
    const CobMember *animation_member;
    const CobMember *description_member;
    const CobMember *name_member;
    unsigned char *pad_bytes = NULL;
    unsigned char *animation_bytes = NULL;
    unsigned char *description_bytes = NULL;
    unsigned char *name_bytes = NULL;
    PadCatalog pads;
    BuildingRenderCatalog animations;
    int success = 0;

    if (!cob_archive_open("C:\\Program Files\\Tone\\TONE00.COB", &archive,
                          error, error_capacity)) return 0;
    pad_member = cob_archive_find(&archive, "pad.txt");
    animation_member = cob_archive_find(&archive, "bldinf.txt");
    description_member = cob_archive_find(&archive, "bldtxt.txt");
    name_member = cob_archive_find(&archive, "bldname.txt");
    if (pad_member == NULL || animation_member == NULL || description_member == NULL ||
        name_member == NULL) {
        (void)snprintf(error, error_capacity,
                       "pad.txt, bldinf.txt, bldtxt.txt or bldname.txt was not found in TONE00.COB");
        goto done;
    }
    pad_bytes = (unsigned char *)malloc(pad_member->length == 0 ? 1 : pad_member->length);
    animation_bytes = (unsigned char *)malloc(animation_member->length == 0
                                               ? 1 : animation_member->length);
    description_bytes = (unsigned char *)malloc(description_member->length == 0
                                                  ? 1 : description_member->length);
    name_bytes = (unsigned char *)malloc(name_member->length == 0
                                           ? 1 : name_member->length);
    if (pad_bytes == NULL || animation_bytes == NULL || description_bytes == NULL ||
        name_bytes == NULL ||
        !cob_archive_read_member(&archive, pad_member, pad_bytes, pad_member->length,
                                 error, error_capacity) ||
        !cob_archive_read_member(&archive, animation_member, animation_bytes,
                                 animation_member->length, error, error_capacity) ||
        !cob_archive_read_member(&archive, description_member, description_bytes,
                                 description_member->length, error, error_capacity) ||
        !cob_archive_read_member(&archive, name_member, name_bytes,
                                 name_member->length, error, error_capacity) ||
        !pad_catalog_load(pad_bytes, pad_member->length, &pads, error, error_capacity) ||
        !building_render_catalog_load(animation_bytes, animation_member->length,
                                       &pads, &animations, error, error_capacity)) {
        goto done;
    }
    memset(g_building_names, 0, sizeof(g_building_names));
    if (extract_repeated_help_entries(name_bytes, name_member->length, "BLDNAME",
                                      g_building_names, BUILDING_NAME_COUNT) !=
        BUILDING_NAME_COUNT) {
        (void)snprintf(error, error_capacity,
                       "bldname.txt did not contain all 64 BLDNAME entries");
        goto done;
    }
    memset(g_building_descriptions, 0, sizeof(g_building_descriptions));
    {
        uint16_t item_index;
        for (item_index = 0; item_index < pads.item_count; ++item_index) {
            const PadCatalogItem *item = &pads.items[item_index];
            if (item->text_id[0] != '\0') {
                (void)extract_help_entry(description_bytes, description_member->length,
                    item->text_id, g_building_descriptions[item->item_id],
                    sizeof(g_building_descriptions[item->item_id]));
            }
        }
    }
    g_pad_catalog = pads;
    g_building_render_catalog = animations;
    success = 1;
done:
    free(name_bytes);
    free(pad_bytes);
    free(animation_bytes);
    free(description_bytes);
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
        const CobMember *floater_build = cob_archive_find(&archive, "data\\fltbuild.wav");
        const CobMember *leviathan_build = cob_archive_find(&archive, "data\\levbuild.wav");
        if (button != NULL && button->length >= 44) {
            g_button_sound = (unsigned char *)malloc(button->length);
            if (g_button_sound == NULL ||
                !cob_archive_read_member(&archive, button, g_button_sound,
                                         button->length, error, error_capacity)) {
                free(g_button_sound);
                g_button_sound = NULL;
            }
        }
        if (floater_build != NULL && floater_build->length >= 44) {
            g_fltbuild_sound = (unsigned char *)malloc(floater_build->length);
            if (g_fltbuild_sound == NULL ||
                !cob_archive_read_member(&archive, floater_build, g_fltbuild_sound,
                                         floater_build->length, error, error_capacity)) {
                free(g_fltbuild_sound);
                g_fltbuild_sound = NULL;
            }
        }
        if (leviathan_build != NULL && leviathan_build->length >= 44) {
            g_levbuild_sound = (unsigned char *)malloc(leviathan_build->length);
            if (g_levbuild_sound == NULL ||
                !cob_archive_read_member(&archive, leviathan_build, g_levbuild_sound,
                                         leviathan_build->length, error, error_capacity)) {
                free(g_levbuild_sound);
                g_levbuild_sound = NULL;
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
        free(g_fltbuild_sound);
        g_fltbuild_sound = NULL;
        free(g_levbuild_sound);
        g_levbuild_sound = NULL;
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
        !load_building_render_catalog(error, sizeof(error)) ||
        !load_menu_art(error, sizeof(error)) ||
        !load_menu_help(error, sizeof(error)) ||
        !load_island_panel_info_text(error, sizeof(error)) ||
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
    /* The original main loop requests `start` without a repeat flag before
       the title menu settles on `ambi1`. */
    set_background_tune_once("start");
    (void)SetTimer(window, 1, 33, NULL);
    (void)SetTimer(window, 2, 1000, NULL);
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
    free_sprite_sheet(&g_island_lilmap_art);
    free_sprite_sheet(&g_island_main_buttons);
    free_sprite_sheet(&g_island_realm_art);
    free_sprite_sheet(&g_floater_info_art);
    free_sprite_sheet(&g_hall_command_art);
    free_sprite_sheet(&g_glyph_inventory_art);
    free_sprite_sheet(&g_trade_button_art);
    free_sprite_sheet(&g_tone_field_art);
    free_sprite_sheet(&g_pad_art);
    free_sprite_sheet(&g_bridge_trigger_art);
    free_sprite_sheet(&g_temp_hole_art);
    free_sprite_sheet(&g_build_cycle_art);
    free_sprite_sheet(&g_task_scroll_art);
    free_sprite_sheet(&g_bildtone_art);
    free_sprite_sheet(&g_tone_crys_art);
    free_sprite_sheet(&g_magctone_art);
    free_sprite_sheet(&g_hall_stock_art);
    free_sprite_sheet(&g_inventory_item_art);
    free_sprite_sheet(&g_diplomacy_art);
    {
        unsigned int hall_index;
        unsigned int item_index;
        for (hall_index = 0; hall_index < 4; ++hall_index) {
            free_sprite_sheet(&g_initial_floater_bodies[hall_index]);
            free_sprite_sheet(&g_initial_floater_legs[hall_index]);
            free_sprite_sheet(&g_initial_floater_bodies_flipped[hall_index]);
            free_sprite_sheet(&g_initial_floater_legs_flipped[hall_index]);
        }
        for (item_index = 0; item_index < PAD_CATALOG_MAX_ITEMS; ++item_index) {
            free_sprite_sheet(&g_building_art[item_index]);
        }
    }
    free_sprite_sheet(&g_island_feature_art);
    free_sprite_sheet(&g_island_names_art);
    free_sprite_sheet(&g_load_save_art);
    free_sprite_sheet(&g_menu_help);
    free_sprite_sheet(&g_newgame_captions);
    free_sprite_sheet(&g_tribe_descriptions);
    bitmap_font_free(&g_bitmap_font);
    stop_background_tune();
    (void)PlaySoundA(NULL, NULL, 0);
    free(g_button_sound);
    free(g_fltbuild_sound);
    free(g_levbuild_sound);
    free(g_island_height_data);
    return (int)message.wParam;
}
