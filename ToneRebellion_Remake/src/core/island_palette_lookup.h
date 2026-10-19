#ifndef TONE_REBELLION_ISLAND_PALETTE_LOOKUP_H
#define TONE_REBELLION_ISLAND_PALETTE_LOOKUP_H

#include <stddef.h>
#include <stdint.h>

enum { ISLAND_PALETTE_LOOKUP_CAPACITY = 512 };

typedef struct IslandPaletteLookup {
    uint32_t rgb24[ISLAND_PALETTE_LOOKUP_CAPACITY];
    uint8_t palette_index[ISLAND_PALETTE_LOOKUP_CAPACITY];
    uint8_t occupied[ISLAND_PALETTE_LOOKUP_CAPACITY];
    uint32_t source_palette_rgb24[256];
    uint32_t nearest_rgb24[ISLAND_PALETTE_LOOKUP_CAPACITY];
    uint8_t nearest_palette_index[ISLAND_PALETTE_LOOKUP_CAPACITY];
    uint8_t nearest_occupied[ISLAND_PALETTE_LOOKUP_CAPACITY];
    size_t source_palette_count;
} IslandPaletteLookup;

/* Build an exact RGB24-to-index map. Duplicate colors keep the first index,
   matching the original nearest-color search's zero-distance early exit. */
void island_palette_lookup_build(IslandPaletteLookup *lookup,
                                 const uint32_t *palette_rgb24,
                                 size_t palette_count);

int island_palette_lookup_find(const IslandPaletteLookup *lookup,
                               uint32_t rgb24, uint8_t *out_index);

/* Return an exact index when present, otherwise preserve the original
   nearest-RGB result and memoize it for repeated non-palette colors. */
int island_palette_lookup_nearest(IslandPaletteLookup *lookup,
                                 uint32_t rgb24, uint8_t *out_index);

#endif
