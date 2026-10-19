#ifndef TONE_REBELLION_GAME_SESSION_SETUP_INTERNAL_H
#define TONE_REBELLION_GAME_SESSION_SETUP_INTERNAL_H

#include "game_session.h"

int game_session_initialize_start_islands(
    GameSession *session, const WorldDefinition *world,
    const IslandData *runtime_layouts,
    int32_t bridge_neighbors[WORLD_MAP_MAX_ISLANDS][ISLAND_DATA_MAX_LOCATIONS],
    int32_t shape_ids[WORLD_MAP_MAX_ISLANDS], char *error, size_t error_capacity);
int game_session_initialize_start_players(
    GameSession *session,
    const IslandData *runtime_layouts, const FloaterCatalog *floater_catalog,
    char *error, size_t error_capacity);

#endif
