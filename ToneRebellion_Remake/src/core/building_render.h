#ifndef TONE_REBELLION_BUILDING_RENDER_H
#define TONE_REBELLION_BUILDING_RENDER_H

#include "pad_catalog.h"

#include <stddef.h>
#include <stdint.h>

enum { BUILDING_RENDER_SHAPE_CAPACITY = 24 };

typedef struct BuildingRenderSegment {
    uint16_t first_frame;
    uint16_t last_frame;
    uint16_t ticks_per_frame;
    uint16_t fallback_frame;
    uint16_t threshold;
    int16_t parameter_a;
    int16_t parameter_b;
    int16_t offset_x;
    int16_t offset_y;
    uint8_t ping_pong;
    uint8_t present;
} BuildingRenderSegment;

typedef struct BuildingRenderItem {
    uint16_t item_id;
    char shape_id[BUILDING_RENDER_SHAPE_CAPACITY];
    BuildingRenderSegment base;
    BuildingRenderSegment chug;
    BuildingRenderSegment glyph;
    BuildingRenderSegment inci;
    BuildingRenderSegment cons;
    BuildingRenderSegment prod;
    BuildingRenderSegment occu;
    BuildingRenderSegment barg;
    uint8_t present;
} BuildingRenderItem;

typedef struct BuildingRenderCatalog {
    uint16_t item_count;
    BuildingRenderItem items[PAD_CATALOG_MAX_ITEMS];
} BuildingRenderCatalog;

typedef struct BuildingRenderPoint {
    int x;
    int y;
} BuildingRenderPoint;

/* Parses BASE/CHUG/GLYP segments from local bldinf.txt, joining item records to
   pad.txt row IDs by the bldinf `item` identifier. */
int building_render_catalog_load(const unsigned char *bytes, size_t length,
                                 const PadCatalog *pads, BuildingRenderCatalog *out,
                                 char *error, size_t error_capacity);
const BuildingRenderItem *building_render_find(const BuildingRenderCatalog *catalog,
                                               uint16_t item_id);

/* Returns the first frame of the static BASE segment as a zero-based SHP
   index. This does not assume that FUN_0040ab42 animates arbitrary items. */
uint32_t building_render_base_frame(const BuildingRenderItem *item);
uint32_t building_render_base_frame_for_state(const BuildingRenderItem *item,
                                              int16_t source_value_4a,
                                              uint32_t source_flags);
/* Returns the animated CHUG frame selected by FUN_0040bf98 from its runtime
   progress counter divided by the segment speed. `animation_ticks` models
   the object's +0x3a progress field. */
uint32_t building_render_chug_frame(const BuildingRenderItem *item,
                                    uint32_t animation_ticks);
/* Total runtime duration stored by bldinf's CHUG descriptor, in object ticks. */
uint32_t building_render_chug_duration(const BuildingRenderItem *item);
/* GLYP uses FUN_0040ab05(0, 20, object[+0x3c]) as a ping-pong phase, then
   FUN_0040aab0(first, last, 20, phase) to interpolate across its range. */
uint32_t building_render_glyph_frame(const BuildingRenderItem *item,
                                     uint32_t animation_ticks);
/* Frame selection for the source renderer's INCI, CONS and PROD layers.
   PROD's optional inactive frame is returned when production flag bit 1 is
   clear. */
uint32_t building_render_inci_frame(const BuildingRenderItem *item,
                                    uint32_t animation_ticks);
uint32_t building_render_cons_frame(const BuildingRenderItem *item,
                                    uint32_t animation_ticks, uint32_t source_flags);
/* Duration of one complete CONS cycle in object ticks. */
uint32_t building_render_cons_duration(const BuildingRenderItem *item);
uint32_t building_render_prod_frame(const BuildingRenderItem *item,
                                    uint32_t animation_ticks, uint32_t source_flags);
/* Native PROD descriptor +0x0c: total frame-cycle ticks, used as the
   Leviathan spawn/reveal mask divisor. */
uint32_t building_render_prod_duration(const BuildingRenderItem *item);
/* FUN_0040bf98 draws the animated PROD layer at the item anchor. The
   descriptor offset belongs to its conditional threshold effect instead. */
BuildingRenderPoint building_render_prod_frame_position(int anchor_x, int anchor_y);
BuildingRenderPoint building_render_prod_threshold_position(const BuildingRenderItem *item,
                                                            int anchor_x, int anchor_y);
/* Returns the resource marker selected by FUN_0040bf98 when PROD reaches its
   threshold, or when an inactive producer has a pending output. */
int building_render_visible_resource_code(const BuildingRenderItem *item,
                                          int32_t runtime_item_id,
                                          int32_t owner_id,
                                          uint32_t production_progress,
                                          uint32_t source_flags,
                                          int32_t pending_resource_code);
/* BARG frame mapping observed in FUN_0040bf98: FISTP(round-to-even) of
   (last-first+2) * object[+0x50], offset from the first frame and clamped. */
uint32_t building_render_barg_frame(const BuildingRenderItem *item,
                                    double barg_progress);
uint32_t building_render_crumble_frame(uint8_t renderer_class, int8_t item_size,
                                      int16_t destruction_ticks);

#endif
