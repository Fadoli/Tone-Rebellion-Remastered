#ifndef TONE_REBELLION_GAME_START_H
#define TONE_REBELLION_GAME_START_H

#include "island_data.h"

#include <stddef.h>
#include <stdint.h>

enum { GAME_START_PLAYER_COUNT = 4, GAME_START_MAX_ISLANDS = 16 };

typedef struct GamePlayerStart {
    uint8_t island_index;
    uint16_t marker_location_index;
    uint16_t nearest_site_location_index;
    uint16_t nearest_site_x;
    uint16_t nearest_site_y;
    uint16_t view_left;
    uint16_t view_right;
} GamePlayerStart;

typedef struct GameStartSetup {
    GamePlayerStart players[GAME_START_PLAYER_COUNT];
} GameStartSetup;

/*
 * Reproduces the location-selection portion of original FUN_0046466f.
 * Location indices refer to the original ISLANDnn.TXT row order.
 *
 * mode bit 0 selects the alternate island/pad rule from the original code;
 * ordinary new-game startup currently reaches this routine with mode == 0.
 * This function does not create the runtime structures or units that follow
 * selection in FLOAT.EXE.
 */
int game_start_assign_locations(const IslandData *islands, size_t island_count,
                                uint32_t mode, uint32_t alternate_island,
                                GameStartSetup *out,
                                char *error, size_t error_capacity);

#endif
