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
/* FUN_00426fd0: vertical hover offset from (DAT_00618e44 + phase byte +0x14)
   mod 48, unless flag 8 is set (then 0). Range -2..3. */
int island_worker_hover_bob(uint32_t animation_ticks, uint8_t phase);
uint32_t island_worker_attack_legs_frame(uint16_t first_frame,
                                         uint16_t last_frame,
                                         uint16_t ticks_per_frame,
                                         int ping_pong,
                                         uint32_t attack_progress);

/* FUN_0042704b draws every floater's health badge (Leviathans included)
   using FUN_00420f28: FLTINFO frame 0x15-stat, with stat capped at ten.
   `worker_type` is the subtype (+4): 0 and 8 use a +2 X offset; any other
   subtype uses +5 when normal and +0 when mirrored. */
int island_worker_stat_badge_layout(uint8_t worker_type,
                                    int16_t combat_stat, int facing_left,
                                    int32_t body_hit_left,
                                    int32_t body_hit_top,
                                    int32_t body_hit_right_exclusive,
                                    uint32_t *frame,
                                    int32_t *x, int32_t *y);

/* FUN_0042704b's third overlay-enable global (flag bit 2) gates a second
   FLTINFO gauge for non-spore floaters with a nonzero subtype: frame
   10 - stat (stat capped at ten), beside the combat-stat badge at the opposite
   X offset (+5 when mirrored, +0 otherwise). The stat is
   __ftol(11.0 * charge / max) (DAT_00494158 = 11.0, asm 0x427b07..0x427bde),
   so a full charge gives 11, capped at ten. */
int island_worker_state_overlay_enabled(uint8_t flags,
                                        int renderer_allows_overlays);
/* FUN_0042704b's pink Leviathan gauge (asm 0x427c2e..0x427d5c, same gate as
   the charge gauge but type 4, subtype 10..17 and rank n > 0): FLTINFO frame
   0x2a - min(10, n), n = the attack rank (high nibble of +0x0a), at the
   charge gauge's spot. Returns 0 when not drawn. */
int island_leviathan_rank_badge_layout(uint8_t subtype, uint16_t level_flags,
                                       int facing_left,
                                       int32_t body_hit_left,
                                       int32_t body_hit_top,
                                       int32_t body_hit_right_exclusive,
                                       uint32_t *frame,
                                       int32_t *x, int32_t *y);
int island_worker_charge_badge_layout(uint8_t floater_type,
                                      uint8_t worker_type,
                                      int16_t charge_stat, int facing_left,
                                      int32_t body_hit_left,
                                      int32_t body_hit_top,
                                      int32_t body_hit_right_exclusive,
                                      uint32_t *frame,
                                      int32_t *x, int32_t *y);

/* FUN_0042704b draws the body shape at fltinf.txt's `base lo hi` for the
   (class, subtype) item (floater.txt row -> item, e.g. Protector subtype 1 is
   ptrain1, base 1 4), at lo + level clamped to hi, level being the low nibble
   of record +0x0a (FUN_0041ff2e). Subtype 8 (ascend) has no body line.
   Returns 0 when no body shape is drawn. Table transcribed from fltinf.txt and
   floater.txt. */
int island_floater_body_frame(uint8_t floater_class, uint8_t subtype,
                              unsigned level, uint32_t *frame);

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
