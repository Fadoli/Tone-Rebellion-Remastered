#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>

#include "cob_archive.h"
#include "building_render.h"
#include "font_image.h"
#include "bitmap_font_render.h"
#include "island_data.h"
#include "island_haze.h"
#include "island_palette_lookup.h"
#include "island_render_rules.h"
#include "curved_text_layout.h"
#include "game_music.h"
#include "game_inventory.h"
#include "game_trade.h"
#include "island_panel_info.h"
#include "game_session.h"
#include "game_session_delivery.h"
#include "game_session_action9.h"
#include "game_glyph_inventory.h"
#include "iw_construct.h"
#include "shp_image.h"
#include "window_catalog.h"
#include "world_map.h"
#include "tone_rng.h"

#include <math.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mmsystem.h>

enum { LOGICAL_WIDTH = 640, LOGICAL_HEIGHT = 480, ISLAND_NAME_COUNT = 15,
       BUILDING_NAME_COUNT = 64, BUILDING_NAME_CAPACITY = 128,
       LEVIATHAN_NAME_COUNT = 17, SITE_TEXT_COUNT = 8,
       SITE_TEXT_CAPACITY = 768 };
enum { SITE_TEXT_POOL, SITE_TEXT_POOL_INFECT, SITE_TEXT_PRIME_POOL,
       SITE_TEXT_BRIDGE, SITE_TEXT_SUPPLY0 };
enum { SCREEN_MAIN_MENU, SCREEN_NEW_GAME, SCREEN_WORLD_MAP, SCREEN_ISLAND, SCREEN_LOAD_GAME,
       SCREEN_LOGO, SCREEN_END_GAME };
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
static int g_island_access_notice_level = -1;
static unsigned int g_island_access_notice_until;
static unsigned int g_building_destroyed_notice_until;
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
/* data/acticon.shp (ACTICON): Hall summary activation icons. */
static SpriteSheet g_activation_icon_art;
/* data/bldgage.shp (BLDGAGE): building damage gauge in IWLocInfo. */
static SpriteSheet g_building_gauge_art;
/* data/bildicon.shp (BILDICON): dots for training-building numbering. */
static SpriteSheet g_building_number_art;
static SpriteSheet g_temp_hole_art;
static SpriteSheet g_build_cycle_art;
static SpriteSheet g_task_scroll_art;
static SpriteSheet g_task_icon_art;
static SpriteSheet g_task_priority_art;
static SpriteSheet g_bildtone_art;
static SpriteSheet g_tone_crys_art;
static SpriteSheet g_magctone_art;
static SpriteSheet g_crumble_art;
static SpriteSheet g_solidpad_art;
static SpriteSheet g_hall_stock_art;
static SpriteSheet g_repair_button_art;
static SpriteSheet g_upgrade_button_art;
static SpriteSheet g_building_command_art;
static SpriteSheet g_inventory_item_art;
static SpriteSheet g_diplomacy_art;
static SpriteSheet g_leviathan_projectile_art[4];
static SpriteSheet g_leviathan_impact_art[4];
static SpriteSheet g_building_art[PAD_CATALOG_MAX_ITEMS];
static SpriteSheet g_initial_floater_bodies[4];
static SpriteSheet g_initial_floater_legs[4];
static SpriteSheet g_initial_floater_bodies_flipped[4];
static SpriteSheet g_initial_floater_legs_flipped[4];
static SpriteSheet g_leviathan_body_art;
static SpriteSheet g_leviathan_body_art_flipped;
static SpriteSheet g_leviathan_legs[9];
static SpriteSheet g_leviathan_legs_flipped[9];
static SpriteSheet g_floater_info_art;
static SpriteSheet g_island_feature_art;
static SpriteSheet g_leviathan_reveal_art;
static SpriteSheet g_island_names_art;
static SpriteSheet g_load_save_art;
static SpriteSheet g_newgame_captions;
static SpriteSheet g_tribe_descriptions;
static SpriteSheet g_menu_help;
static COLORREF g_newgame_palette[256];
static COLORREF g_map_palette[256];
static COLORREF g_island_palette[256];
static IslandPaletteLookup g_island_palette_lookup;
static DWORD g_task_highlight_pixels[256];
static uint32_t g_random_state;
static unsigned char *g_button_sound;
static unsigned char *g_fltbuild_sound;
static unsigned char *g_levbuild_sound;
static unsigned char *g_fltbirth_sound;
static unsigned char *g_levbirth_sound;
static unsigned char *g_fltdeath_sound;
static unsigned char *g_levdeath_sound;
static unsigned char *g_bridge_sound;
/* PSPELL, SSPELL, MSPELL, LSPELL, FLTARMOR, FASTPROD, SACRIF, KILLBEAS,
   DESTSUPP, ASCEND (GameCastSoundId order). */
static unsigned char *g_cast_sounds[10];
static char g_music_directory[MAX_PATH];
static char g_current_tune[16];
static int g_music_device_open;
static int g_music_loops;
static BitmapFont g_bitmap_font;
/* data/smfont.fnt (8 px): the default UI font of IWTextInfo, the Diplomacy
   caption and most panels (FUN_0042de0d returns &DAT_005c30b8); its ink value
   is 243 and its colour is palette index 6 (FUN_0042da69). */
static BitmapFont g_small_font;
/* data/bigfont.fnt (11 px, DAT_005c2870): NOART in the Inventory panel. */
static BitmapFont g_big_font;
static char g_help_text[HELP_ENTRY_COUNT][1024];
static char g_newgame_text[8][256];
static char g_empty_glyph_text[256];
static char g_empty_inventory_text[256];
static char g_empty_task_text[256];
static char g_task_label_text[6][256];
static char g_task_stock_text[256];
static char g_task_building_const_text[256];
static char g_task_priority_text[3][256];
static char g_task_transfer_text[2][256];
static char g_task_category_text[4][256];
static char g_hall_population_label[64];
static char g_hall_work_label[64];
static char g_hall_surplus_label[64];
/* gamey.txt BC1: caption of the Move button (FUN_0042f150 index 1). */
static char g_move_button_text[128];
/* gamey.txt WORKER, AWAKE, LEVEL, HITS, STRENGTH, CHARGE (FUN_00429ebe). */
static char g_unit_label_text[6][64];
/* gamey.txt TRZERO and TRDOIT: Trade button hover captions (FUN_0043edac). */
static char g_trade_caption_text[2][64];
/* names.txt slots filled by FUN_0041d70d: tribes, then beasts. */
static char g_tribe_names[5][12];
static char g_beast_names[18][16];
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
/* bldname.txt LEVNAME entries, indexed by Leviathan pad item id - 5. */
static char g_leviathan_names[LEVIATHAN_NAME_COUNT][BUILDING_NAME_CAPACITY];
/* bldtxt.txt POOL, POOLINFECT, PRIMEPOOL, BRIDGE and SUPPLY0..3 entries. */
static char g_site_texts[SITE_TEXT_COUNT][SITE_TEXT_CAPACITY];
static char g_island_names[ISLAND_NAME_COUNT][32];
static IslandData g_island_surface_data;
static GameSession g_game_session;
static GameMusicState g_game_music;
static int g_game_session_valid;
static int g_game_session_world_index = -1;
static WindowCatalog g_window_catalog;
static PadCatalog g_pad_catalog;
static FloaterCatalog g_floater_catalog;
static BuildingRenderCatalog g_building_render_catalog;
static uint16_t g_island_draw_order[ISLAND_DATA_MAX_LOCATIONS];
static IslandHaze g_island_haze;
static unsigned char *g_island_height_data;
static size_t g_island_height_length;
static int g_island_surface_id = -1;
static int g_island_scroll_x;
/* Remake: left button held on the IWLilMap pane scrolls the island view. */
static int g_lilmap_drag;
static int g_hovered_location = -1;
static IslandLocationActionControl g_hovered_location_action =
    ISLAND_LOCATION_ACTION_NONE;
static int g_hovered_repair_control;
static int g_hovered_upgrade_control;
static int g_hovered_onoff_control;
/* Native spell kind under BC_Spell1..8, or -1. FUN_00440567's cost bars read
   the armed spell word (+0x74), set through message 0x350d (interpreted as
   the spell button's mouse-over context). */
static int g_hovered_spell_kind = -1;
/* Set when a world-map press already acted: the matching release is dropped,
   as the original pump never delivers it (FUN_00469f56). */
static int g_swallow_left_button_up;
/* DAT_004bf110: simulation ticks per 50 ms frame, 1..3 (keys 8/9). */
static unsigned g_sim_speed = 1U;
static int g_hovered_location_grab;
static int g_hovered_defend_area;
/* Ticks since the solo tribe lost its last floater (end sequence, FUN_00464e4d). */
static unsigned g_defeat_ticks;
static int g_hovered_upgspread;
static SpriteSheet g_clip_art;
static SpriteSheet g_bildicon_art;
/* 1 = BC_TrnStkC, 2 = BC_TrnStkM under the pointer. */
static int g_hovered_training_stock;
/* BC_DefendArea armed: the next island click sets the building's area order
   (FUN_0043530b mode 19). */
static int g_defend_area_armed;
static SpriteSheet g_trainb_art;
static int g_hovered_hall_stock = -1;
static int g_hovered_island_button = -1;
static int g_hovered_hall_command = -1;
static int g_island_panel_mode = WINDOW_ISLAND_PANEL_GENERAL;
static int g_task_scroll_offset;
static int g_selected_task_slot = -1;
static size_t g_inventory_page = 0;
static int g_hovered_inventory_item = -1;
static int g_selected_inventory_item = -1;
static int g_inventory_info_mode = ISLAND_PANEL_INFO_INVENTORY_DEFAULT;
static int g_hovered_glyph = -1;
static int g_selected_glyph = -1;
static int g_glyph_info_default = 1;
static HMODULE g_original_cursor_module;
#define GAME_CURSOR_SLOT_COUNT 17
static HCURSOR g_interaction_cursors[GAME_CURSOR_SLOT_COUNT];
static const WORD g_cursor_resource_ids[GAME_CURSOR_SLOT_COUNT] = {
    0x84, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c,
    0x7d, 0x7e, 0x7f, 0x74, 0x80, 0x81, 0x82, 0x83
};
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
static int g_resume_available;
static unsigned char g_load_slot_valid[8];
/* 1 = the slot is an original-game save (listed, not loadable). */
static unsigned char g_load_slot_native[8];
/* The Load/Save screen is shared: 1 = Save (state 5), 0 = Load (state 4). */
static int g_load_save_mode;
static int g_save_return_screen;
/* 1 = the Load screen was opened from a game (the panel), so Esc returns there. */
static int g_load_from_game;
/* SlideWindow toggles and volumes (DAT_0049c9a8 / ac / a0 / a4). */
static int g_music_enabled = 1;
static int g_sound_enabled = 1;
static int g_sound_volume = 100;
static char g_music_resume_tune[16];
static int g_music_resume_loop;
static void apply_music_volume(void);
static void load_audio_settings(void);
/* 1 = music slider, 2 = effects slider while the left button is held. */
static int g_slide_drag;
/* FUN_00458371: the 0x80-byte header and ctime-style date of each valid slot. */
static unsigned char g_load_slot_header[8][0x80];
static char g_load_slot_date[8][32];
static COLORREF g_load_save_palette[256];
static SpriteSheet g_load_title_art;
static SpriteSheet g_load_endgame_art;
static SpriteSheet g_load_tone_art[3];
static SpriteSheet g_load_floater_body[4];
static SpriteSheet g_load_floater_legs[4];
static int g_hovered_help = -1;
static int g_hovered_newgame_text = -1;
static int g_hovered_island = -1;
static int g_mouse_inside;
/* Reused DIB; direct pixel writes occur only while rendering a frame. */
static DWORD *g_paint_buffer_pixels;
static HDC g_paint_buffer_dc;
static HBITMAP g_paint_buffer_bitmap;
static HGDIOBJ g_paint_buffer_original_bitmap;
static HDC g_sprite_source_dc;

/* FUN_004595cc: volume 0..100 -> attenuation in 1/100 dB,
   ftol(1000 * log2(v / 100)) clamped to [-10000, 0]; 0 is silence. */
static int volume_attenuation(int volume)
{
    int attenuation;
    if (volume < 0 || volume > 100) return 0;
    if (volume == 0) return -10000;
    attenuation = (int)(1000.0 * log(volume / 100.0) / log(2.0));
    if (attenuation < -10000) attenuation = -10000;
    if (attenuation > 0) attenuation = 0;
    return attenuation;
}

/* Amplitude gain for an attenuation in 1/100 dB (10 ^ (dB / 20)). */
static double volume_gain(int volume)
{
    return volume <= 0 ? 0.0 : pow(10.0, volume_attenuation(volume) / 2000.0);
}

/* The SlideWindow sound toggle and effects slider act on every sound effect:
   in-memory WAV effects are copied and their PCM samples scaled by the slider
   attenuation (DirectSound-style volume, which PlaySound lacks). */
static BOOL play_effect_sound(LPCSTR sound, HMODULE module, DWORD flags)
{
    static unsigned char *ring[8];
    static size_t ring_capacity[8];
    static unsigned int ring_next;
    const unsigned char *wav = (const unsigned char *)sound;
    size_t total;
    size_t offset;
    unsigned int slot;
    unsigned int bits = 0;
    double gain;
    if (sound == NULL) return PlaySoundA(NULL, module, flags);
    if (!g_sound_enabled || g_sound_volume <= 0) return TRUE;
    if ((flags & SND_MEMORY) == 0 || g_sound_volume >= 100)
        return PlaySoundA(sound, module, flags);
    if (memcmp(wav, "RIFF", 4) != 0 || memcmp(wav + 8, "WAVE", 4) != 0)
        return PlaySoundA(sound, module, flags);
    total = 8U + (size_t)(wav[4] | (wav[5] << 8) | (wav[6] << 16) |
                          ((unsigned)wav[7] << 24));
    if (total < 44U || total > 64U * 1024U * 1024U)
        return PlaySoundA(sound, module, flags);
    slot = ring_next++ & 7U;
    if (ring_capacity[slot] < total) {
        unsigned char *grown = (unsigned char *)realloc(ring[slot], total);
        if (grown == NULL) return PlaySoundA(sound, module, flags);
        ring[slot] = grown;
        ring_capacity[slot] = total;
    }
    memcpy(ring[slot], wav, total);
    gain = volume_gain(g_sound_volume);
    for (offset = 12; offset + 8U <= total;) {
        size_t chunk = (size_t)(ring[slot][offset + 4] |
            (ring[slot][offset + 5] << 8) | (ring[slot][offset + 6] << 16) |
            ((unsigned)ring[slot][offset + 7] << 24));
        if (memcmp(ring[slot] + offset, "fmt ", 4) == 0 && chunk >= 16U &&
            offset + 8U + 16U <= total)
            bits = (unsigned)(ring[slot][offset + 8 + 14] |
                              (ring[slot][offset + 8 + 15] << 8));
        if (memcmp(ring[slot] + offset, "data", 4) == 0) {
            size_t start = offset + 8U;
            size_t end = start + chunk;
            size_t i;
            if (end > total) end = total;
            if (bits == 16U) {
                for (i = start; i + 1U < end; i += 2U) {
                    int sample = (short)(ring[slot][i] | (ring[slot][i + 1] << 8));
                    sample = (int)(sample * gain);
                    ring[slot][i] = (unsigned char)sample;
                    ring[slot][i + 1] = (unsigned char)(sample >> 8);
                }
            } else if (bits == 8U) {
                for (i = start; i < end; ++i)
                    ring[slot][i] = (unsigned char)(128 +
                        (int)(((int)ring[slot][i] - 128) * gain));
            }
            break;
        }
        offset += 8U + chunk + (chunk & 1U);
    }
    return PlaySoundA((LPCSTR)ring[slot], module, flags);
}
#define PlaySoundA(sound, module, flags) play_effect_sound((sound), (module), (flags))

/* Ordered source fragments share private Win32 state in this one
   translation unit; the split is organizational and keeps internal linkage. */
#include "menu_app_sections/sprite_primitives.inc"

#include "menu_app_sections/island_assets.inc"

#include "menu_app_sections/newgame_text_interaction.inc"

#include "menu_app_sections/bitmap_text_layout.inc"

#include "menu_app_sections/menu_help_loading.inc"

#include "menu_app_sections/newgame_content_text.inc"

#include "menu_app_sections/save_and_help_resources.inc"

#include "menu_app_sections/menu_render.inc"

#include "menu_app_sections/world_map_render.inc"

#include "menu_app_sections/island_interaction.inc"

#include "menu_app_sections/save_game.inc"

#include "menu_app_sections/slide_panel.inc"

#include "menu_app_sections/hall_support_render.inc"

/* The Hall, task, trade, inventory, unit-detail and construction panels draw
   their text with SMFONT in palette index 6 (REA: callers of the 0x4014c9
   accessor, see behavior/ui-fonts.md), so route their labels to it. */
#define draw_bitmap_label(dc, text, x, y, color) draw_small_label((dc), (text), (x), (y), panel_text_color(color))
#define draw_bitmap_label_pixels(text, x, y, color) draw_small_label_pixels((text), (x), (y), panel_text_color(color))
#define measure_bitmap_text(context, text, length) measure_small_text((text), (length))
#include "menu_app_sections/hall_panel_render.inc"

#include "menu_app_sections/island_item_render.inc"

#include "menu_app_sections/island_view_render.inc"
#undef draw_bitmap_label
#undef draw_bitmap_label_pixels
#undef measure_bitmap_text

#include "menu_app_sections/logo_splash.inc"
#include "menu_app_sections/end_game_screen.inc"

#include "menu_app_sections/render_dispatch.inc"

#include "menu_app_sections/window_interaction.inc"

#include "menu_app_sections/window_proc.inc"

#include "menu_app_sections/content_loading.inc"
