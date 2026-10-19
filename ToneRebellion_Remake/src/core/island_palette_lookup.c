#include "island_palette_lookup.h"

#include <string.h>

static size_t hash_rgb24(uint32_t rgb24)
{
    return (size_t)((rgb24 * UINT32_C(2654435761)) >> 23);
}

void island_palette_lookup_build(IslandPaletteLookup *lookup,
                                 const uint32_t *palette_rgb24,
                                 size_t palette_count)
{
    size_t index;
    if (lookup == NULL) return;
    memset(lookup, 0, sizeof(*lookup));
    if (palette_rgb24 == NULL) return;
    if (palette_count > 256U) palette_count = 256U;
    lookup->source_palette_count = palette_count;
    for (index = 0; index < palette_count; ++index) {
        uint32_t key = palette_rgb24[index] & UINT32_C(0x00ffffff);
        size_t slot = hash_rgb24(key);
        size_t probes;
        lookup->source_palette_rgb24[index] = key;
        for (probes = 0; probes < ISLAND_PALETTE_LOOKUP_CAPACITY; ++probes) {
            if (lookup->occupied[slot] != 0) {
                if (lookup->rgb24[slot] == key) break;
            } else {
                lookup->rgb24[slot] = key;
                lookup->palette_index[slot] = (uint8_t)index;
                lookup->occupied[slot] = 1;
                break;
            }
            slot = (slot + 1U) & (ISLAND_PALETTE_LOOKUP_CAPACITY - 1U);
        }
    }
}

int island_palette_lookup_find(const IslandPaletteLookup *lookup,
                               uint32_t rgb24, uint8_t *out_index)
{
    uint32_t key = rgb24 & UINT32_C(0x00ffffff);
    size_t slot;
    size_t probes;
    if (lookup == NULL || out_index == NULL) return 0;
    slot = hash_rgb24(key);
    for (probes = 0; probes < ISLAND_PALETTE_LOOKUP_CAPACITY; ++probes) {
        if (lookup->occupied[slot] == 0) return 0;
        if (lookup->rgb24[slot] == key) {
            *out_index = lookup->palette_index[slot];
            return 1;
        }
        slot = (slot + 1U) & (ISLAND_PALETTE_LOOKUP_CAPACITY - 1U);
    }
    return 0;
}

int island_palette_lookup_nearest(IslandPaletteLookup *lookup,
                                  uint32_t rgb24, uint8_t *out_index)
{
    uint32_t key = rgb24 & UINT32_C(0x00ffffff);
    size_t slot;
    size_t index;
    uint8_t exact_index;
    uint8_t best_index = 0;
    uint32_t best_distance = UINT32_MAX;
    if (lookup == NULL || out_index == NULL ||
        lookup->source_palette_count == 0U) return 0;
    if (island_palette_lookup_find(lookup, key, &exact_index)) {
        *out_index = exact_index;
        return 1;
    }
    slot = hash_rgb24(key);
    if (lookup->nearest_occupied[slot] != 0 &&
        lookup->nearest_rgb24[slot] == key) {
        *out_index = lookup->nearest_palette_index[slot];
        return 1;
    }
    for (index = 0; index < lookup->source_palette_count; ++index) {
        uint32_t color = lookup->source_palette_rgb24[index];
        int red = (int)((key >> 16) & 0xffU) -
                  (int)((color >> 16) & 0xffU);
        int green = (int)((key >> 8) & 0xffU) -
                    (int)((color >> 8) & 0xffU);
        int blue = (int)(key & 0xffU) - (int)(color & 0xffU);
        uint32_t distance = (uint32_t)(red * red + green * green + blue * blue);
        if (distance < best_distance) {
            best_distance = distance;
            best_index = (uint8_t)index;
            if (distance == 0U) break;
        }
    }
    lookup->nearest_rgb24[slot] = key;
    lookup->nearest_palette_index[slot] = best_index;
    lookup->nearest_occupied[slot] = 1;
    *out_index = best_index;
    return 1;
}
