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
    uint8_t ping_pong;
    uint8_t present;
} BuildingRenderSegment;

typedef struct BuildingRenderItem {
    uint16_t item_id;
    char shape_id[BUILDING_RENDER_SHAPE_CAPACITY];
    BuildingRenderSegment base;
    BuildingRenderSegment chug;
    BuildingRenderSegment glyph;
    uint8_t present;
} BuildingRenderItem;

typedef struct BuildingRenderCatalog {
    uint16_t item_count;
    BuildingRenderItem items[PAD_CATALOG_MAX_ITEMS];
} BuildingRenderCatalog;

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
/* Returns the animated CHUG frame selected by FUN_0040bf98 from its runtime
   progress counter divided by the segment speed. `animation_ticks` models
   the object's +0x3a progress field. */
uint32_t building_render_chug_frame(const BuildingRenderItem *item,
                                    uint32_t animation_ticks);
/* GLYP uses FUN_0040ab05(0, 20, object[+0x3c]) as a ping-pong phase, then
   FUN_0040aab0(first, last, 20, phase) to interpolate across its range. */
uint32_t building_render_glyph_frame(const BuildingRenderItem *item,
                                     uint32_t animation_ticks);

#endif
