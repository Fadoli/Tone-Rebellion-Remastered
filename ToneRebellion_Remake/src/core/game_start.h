#ifndef TONE_REBELLION_GAME_START_H
#define TONE_REBELLION_GAME_START_H

#include "island_data.h"
#include "tone_rng.h"
#include "world_map.h"

#include <stddef.h>
#include <stdint.h>

enum {
    GAME_START_PLAYER_COUNT = 4,
    GAME_START_MAX_ISLANDS = 16,
    GAME_START_INITIAL_PAD_ITEM_ID = 0x2a,
    GAME_START_FLOATERS_PER_PLAYER = 4
};

typedef struct GamePlayerStart {
    uint8_t island_index;
    uint16_t marker_location_index;
    uint16_t nearest_site_location_index;
    uint16_t nearest_site_x;
    uint16_t nearest_site_y;
    uint16_t marker_x;
    uint16_t marker_y;
    uint16_t initial_pad_item_id;
    uint8_t floater_type_index;
    uint8_t floater_count;
    uint16_t view_left;
    uint16_t view_right;
} GamePlayerStart;

typedef struct GameStartSetup {
    GamePlayerStart players[GAME_START_PLAYER_COUNT];
} GameStartSetup;

enum { GAME_START_MAX_DISTRIBUTED_TONES = WORLD_MAP_MAX_ISLANDS * 2 };

typedef struct GameStartTonePlacement {
    uint8_t island_index;
    uint16_t location_index;
    uint16_t item_id;
    uint8_t owner_id;
} GameStartTonePlacement;

typedef struct GameStartToneDistribution {
    uint8_t placement_count;
    GameStartTonePlacement placements[GAME_START_MAX_DISTRIBUTED_TONES];
} GameStartToneDistribution;

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

/*
 * Reproduces the marker-distribution phase of FUN_00464b9e. `home_island_index`
 * corresponds to DAT_006136b0 - 1 in FUN_004535e4; the original global's runtime
 * initializer is not yet identified, so callers supply the observed slot.
 * `shape_ids` come from the selected WORLDPOS island table. Existing item IDs
 * 6..9 in a location's renderer_variant participate in per-island balancing.
 * `rng` is the same stream used by surrounding new-game startup. This phase
 * does not consume draws from FUN_00464b9e's earlier 0x17..0x19 loop; exact
 * whole-startup RNG parity therefore awaits that loop's port.
 * Results are committed only on success; source island records are not changed.
 */
int game_start_distribute_tones(const IslandData *islands,
                                const int32_t *shape_ids,
                                size_t island_count,
                                size_t home_island_index,
                                uint32_t mode,
                                ToneRng *rng,
                                GameStartToneDistribution *out,
                                char *error, size_t error_capacity);

#endif
