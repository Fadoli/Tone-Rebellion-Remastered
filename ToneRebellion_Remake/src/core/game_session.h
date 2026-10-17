#ifndef TONE_REBELLION_GAME_SESSION_H
#define TONE_REBELLION_GAME_SESSION_H

#include "game_start.h"
#include "world_map.h"

#include <stddef.h>
#include <stdint.h>

enum { GAME_SESSION_MAX_FLOATERS = GAME_START_PLAYER_COUNT * GAME_START_FLOATERS_PER_PLAYER };

typedef struct GameSessionConfig {
    uint8_t world_index;
    uint8_t difficulty;
    uint8_t selected_tribe;
    uint32_t mode;
    uint32_t alternate_island;
    uint8_t home_island_index;
    uint8_t randomize_class0_assignment;
    uint32_t random_seed;
} GameSessionConfig;

typedef struct GameRuntimeLocation {
    int32_t record_value_10;
    int32_t owner_id;
    int32_t record_value_24;
    int32_t bridge_neighbor_island;
} GameRuntimeLocation;

typedef struct GameRuntimeIsland {
    uint16_t location_count;
    GameRuntimeLocation locations[ISLAND_DATA_MAX_LOCATIONS];
} GameRuntimeIsland;

typedef struct GameFloaterStart {
    uint8_t island_index;
    uint8_t type_index;
    uint16_t x;
    uint16_t y;
} GameFloaterStart;

typedef struct GameSession {
    GameSessionConfig config;
    uint8_t island_count;
    GameStartSetup player_starts;
    GameStartToneDistribution tone_placements;
    GameFloaterStart floaters[GAME_SESSION_MAX_FLOATERS];
    uint8_t floater_count;
    uint16_t class0_assignments;
    GameRuntimeIsland islands[WORLD_MAP_MAX_ISLANDS];
} GameSession;

/*
 * Builds the initial, mutable gameplay state from a selected WORLDPOS world
 * and its ISLANDnn.TXT records (ordered by world-island index). The port
 * models FUN_004500c4 field resets, FUN_0046466f start descriptors and initial
 * pads/floaters, applies FUN_00464b9e marker item placements, sets class-2
 * record state and reproduces the two class-0 assignment loops in
 * FUN_004637fc. All inputs remain unchanged and `out` changes only after the
 * full setup succeeds.
 *
 * `home_island_index` represents the unresolved runtime value compared with
 * DAT_006136b0 - 1. RNG draws before/inside the unported 0x17..0x19 loop are
 * outside this model, so this is a consistent initial state model rather than
 * a claim of whole-startup random-stream parity.
 */
int game_session_initialize(const WorldDefinition *world,
                            const IslandData *islands_by_world_index,
                            const GameSessionConfig *config,
                            GameSession *out,
                            char *error, size_t error_capacity);

#endif
