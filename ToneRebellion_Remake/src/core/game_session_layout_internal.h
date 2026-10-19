#ifndef TONE_REBELLION_GAME_SESSION_LAYOUT_INTERNAL_H
#define TONE_REBELLION_GAME_SESSION_LAYOUT_INTERNAL_H

#include "game_session.h"

int game_session_prepare_runtime_layouts(
    const WorldDefinition *world, const IslandData *sources, IslandData *layouts,
    int32_t bridge_neighbors[WORLD_MAP_MAX_ISLANDS][ISLAND_DATA_MAX_LOCATIONS],
    char *error, size_t error_capacity);
int game_session_assign_initial_sites(
    const WorldDefinition *world, const IslandData *sources,
    const int32_t shape_ids[WORLD_MAP_MAX_ISLANDS], GameSession *session,
    ToneRng *rng, char *error, size_t error_capacity);


#endif
