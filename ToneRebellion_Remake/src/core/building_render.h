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
    uint8_t present;
} BuildingRenderItem;

typedef struct BuildingRenderCatalog {
    uint16_t item_count;
    BuildingRenderItem items[PAD_CATALOG_MAX_ITEMS];
} BuildingRenderCatalog;

/* Parses BASE/CHUG segments from local bldinf.txt, joining item records to
   pad.txt row IDs by the bldinf `item` identifier. */
int building_render_catalog_load(const unsigned char *bytes, size_t length,
                                 const PadCatalog *pads, BuildingRenderCatalog *out,
                                 char *error, size_t error_capacity);
const BuildingRenderItem *building_render_find(const BuildingRenderCatalog *catalog,
                                               uint16_t item_id);

/* Returns a zero-based SHP frame. Matches FUN_0040ab42's inclusive segment,
   location phase, per-state divisor, and optional ping-pong behavior. */
uint32_t building_render_frame(const BuildingRenderSegment *segment,
                               uint32_t game_ticks, uint16_t world_x,
                               uint32_t state);

#endif
