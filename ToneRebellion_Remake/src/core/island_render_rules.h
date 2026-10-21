#ifndef TONE_REBELLION_ISLAND_RENDER_RULES_H
#define TONE_REBELLION_ISLAND_RENDER_RULES_H

#include <stdint.h>

#include "island_data.h"

enum {
    ISLAND_TONE_POOL_ITEM_DEFAULT = 0,
    ISLAND_TONE_POOL_ITEM_ALTERNATE = 5,
    /* bldinf.txt's BASE 1 1 is one-based; decoded SHP frames are zero-based. */
    ISLAND_TONE_POOL_BASE_FRAME = 0
};

enum {
    ISLAND_FLOATER_OVERLAY_REALM = 1u << 0,
    ISLAND_FLOATER_OVERLAY_HEALTH = 1u << 1,
    ISLAND_FLOATER_OVERLAY_STATE = 1u << 2
};

/* FUN_0040bf98 composites POOL's BASE 1 1 before its animated CHUG layer.
   FUN_00450a71 gives POOL runtime IDs 0 and 5 distinct counter sequences.
   FUN_0040bf98 maps the selected counter through POOL CHUG 2..40, speed 3,
   ping-pong (FUN_0040ab05); this returns that overlay frame zero-based. */
uint16_t island_tone_pool_next_counter(int32_t runtime_item_id,
                                       uint16_t chug_progress);
uint16_t island_tone_pool_render_counter(int32_t runtime_item_id,
                                         int32_t owner_id,
                                         uint8_t tribe_visibility_mask,
                                         unsigned active_tribe,
                                         uint16_t chug_progress);
uint32_t island_tone_pool_frame(int32_t runtime_item_id,
                                uint32_t chug_progress);
int island_tone_pool_should_draw(int is_tone_location,
                                 int32_t runtime_item_id,
                                 int covered_by_leviathan_building);

/* Only explicit size tags select the three groups in PAD.SHP. */
int island_pad_size_group(IslandLocationKind kind);

/* PADS uses CHUG 1..9 from bldinf.txt and FUN_0040ab42 adds world_x % 23
   after dividing source ticks by (segment speed + object[+0x0c]). FUN_00461b3b
   stores the pad-size subtype at +0x0c: small=0, medium=1, large=2. */
uint32_t island_pad_frame(uint32_t animation_ticks, uint16_t world_x,
                          unsigned pad_group, unsigned speed_adjustment);
int island_site_should_draw_pad(int pad_group, int site_occupied_by_item);

/* FUN_0042fa0f (message 2003) normalizes and flips each of the three
   independent FUN_0042704b overlay-enable globals. */
uint8_t island_toggle_realm_overlay_flags(uint8_t flags);
int island_worker_realm_overlay_enabled(uint8_t flags,
                                        int renderer_allows_overlays);
int island_worker_health_overlay_enabled(uint8_t flags,
                                         int renderer_allows_overlays);

/* FUN_0042704b chooses fltinf.txt's hover or carry leg range from cargo
   (+0x18), then wraps the source tick phase at the descriptor speed. The
   remake's initial worker records do not yet retain native phase byte +0x14. */
uint32_t island_worker_legs_frame(uint8_t worker_type, int has_cargo,
                                  uint32_t animation_ticks);
uint32_t island_worker_attack_legs_frame(uint16_t first_frame,
                                         uint16_t last_frame,
                                         uint16_t ticks_per_frame,
                                         int ping_pong,
                                         uint32_t attack_progress);

/* FUN_0042704b draws a class-0 worker's combat-stat badge using
   FUN_00420f28: FLTINFO frame 0x15-stat, with stat capped at ten. Type 0/8
   uses a +2 X offset; other types use +5 when normal and +0 when mirrored. */
int island_worker_stat_badge_layout(uint8_t worker_type,
                                    int16_t combat_stat, int facing_left,
                                    int32_t body_hit_left,
                                    int32_t body_hit_top,
                                    int32_t body_hit_right_exclusive,
                                    uint32_t *frame,
                                    int32_t *x, int32_t *y);

/* FUN_0042003c resolves the starting *work row's realm to FLTINFO frames
   22..25. When a current location is available, 0x10000 increments the realm
   modulo four and takes precedence over 0x20000, which decrements it. */
int island_worker_realm_badge_layout(uint8_t realm,
                                     int has_current_location,
                                     uint32_t current_location_flags,
                                     int facing_left,
                                     int32_t body_hit_left,
                                     int32_t body_hit_top,
                                     int32_t body_hit_right_exclusive,
                                     uint32_t *frame,
                                     int32_t *x, int32_t *y);

#endif
