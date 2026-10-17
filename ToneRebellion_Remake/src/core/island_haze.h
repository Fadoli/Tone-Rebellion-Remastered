#ifndef TONE_REBELLION_ISLAND_HAZE_H
#define TONE_REBELLION_ISLAND_HAZE_H

#include <stddef.h>
#include <stdint.h>

enum {
    ISLAND_HAZE_BANK_COUNT = 2,
    ISLAND_HAZE_LEVEL_COUNT = 8,
    ISLAND_HAZE_PALETTE_SIZE = 256,
    ISLAND_HAZE_PALETTE_BYTES = 768,
    ISLAND_HAZE_FILE_BYTES = 0x0e00
};

/* The selector follows FUN_004106dd: zero chooses the second (black-endpoint)
   table; any nonzero selector chooses the first (white-endpoint) table. */
enum { ISLAND_HAZE_BLACK_BANK = 0, ISLAND_HAZE_WHITE_BANK = 1 };

typedef struct IslandHaze {
    uint8_t remap[ISLAND_HAZE_BANK_COUNT][ISLAND_HAZE_LEVEL_COUNT]
                 [ISLAND_HAZE_PALETTE_SIZE];
} IslandHaze;

/* Reconstruct the two 0x800-byte lookup tables created by FUN_00410510 from
   the 0x0e00-byte HZT and 256 RGB6 triples. Output changes only on success. */
int island_haze_load(const uint8_t *hzt, size_t hzt_length,
                     const uint8_t palette_rgb6[ISLAND_HAZE_PALETTE_BYTES],
                     IslandHaze *out, char *error, size_t error_capacity);

uint8_t island_haze_remap(const IslandHaze *haze, int selector, int level,
                          uint8_t palette_index);

#endif
