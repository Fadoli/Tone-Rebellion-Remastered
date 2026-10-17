#include "island_haze.h"

#include <stdio.h>
#include <string.h>

static void set_error(char *error, size_t capacity, const char *message)
{
    if (error != NULL && capacity != 0) {
        (void)snprintf(error, capacity, "%s", message);
        error[capacity - 1] = '\0';
    }
}

static uint8_t nearest_palette_index(const uint8_t *palette, unsigned target)
{
    unsigned best_distance = ~0u;
    unsigned best_index = 0;
    unsigned index;

    /* FUN_0041081b searches palette entries 0..254. Index 255 is reserved by
       the caller as transparent and is written explicitly to the final slot. */
    for (index = 0; index < 255; ++index) {
        int red_delta = (int)palette[index * 3] - (int)target;
        int green_delta = (int)palette[index * 3 + 1] - (int)target;
        int blue_delta = (int)palette[index * 3 + 2] - (int)target;
        unsigned distance = (unsigned)(red_delta * red_delta +
                                       green_delta * green_delta +
                                       blue_delta * blue_delta);
        if (distance < best_distance) {
            best_distance = distance;
            best_index = index;
            if (distance == 0) break;
        }
    }
    return (uint8_t)best_index;
}

int island_haze_load(const uint8_t *hzt, size_t hzt_length,
                     const uint8_t palette_rgb6[ISLAND_HAZE_PALETTE_BYTES],
                     IslandHaze *out, char *error, size_t error_capacity)
{
    IslandHaze parsed;

    if (error != NULL && error_capacity != 0) error[0] = '\0';
    if (hzt == NULL || palette_rgb6 == NULL || out == NULL) {
        set_error(error, error_capacity, "HZT bytes, palette, and output are required");
        return 0;
    }
    if (hzt_length != ISLAND_HAZE_FILE_BYTES) {
        set_error(error, error_capacity, "HZT member must contain two 0x700-byte tables");
        return 0;
    }

    /* FUN_00410510 reads the first seven levels into DAT_004b20f0 and the
       next seven into DAT_004bc530. FUN_004106dd selector 1 selects the first
       table; selector 0 selects the second. */
    memcpy(parsed.remap[ISLAND_HAZE_WHITE_BANK], hzt, 0x700);
    memcpy(parsed.remap[ISLAND_HAZE_BLACK_BANK], hzt + 0x700, 0x700);
    memset(parsed.remap[ISLAND_HAZE_WHITE_BANK][7],
           nearest_palette_index(palette_rgb6, 63), 255);
    parsed.remap[ISLAND_HAZE_WHITE_BANK][7][255] = 255;
    memset(parsed.remap[ISLAND_HAZE_BLACK_BANK][7],
           nearest_palette_index(palette_rgb6, 0), 255);
    parsed.remap[ISLAND_HAZE_BLACK_BANK][7][255] = 255;

    *out = parsed;
    return 1;
}

uint8_t island_haze_remap(const IslandHaze *haze, int selector, int level,
                          uint8_t palette_index)
{
    int bank = selector == 0 ? ISLAND_HAZE_BLACK_BANK : ISLAND_HAZE_WHITE_BANK;
    if (haze == NULL || level < 0 || level >= ISLAND_HAZE_LEVEL_COUNT) {
        return palette_index;
    }
    return haze->remap[bank][level][palette_index];
}
