#include "game_session.h"

int game_session_can_enter_island(const GameSession *session,
                                  uint8_t island_index,
                                  uint8_t player_mask)
{
    if (session == NULL || island_index >= session->island_count) return 0;
    return (session->islands[island_index].access_mask & player_mask) != 0;
}

int game_session_world_map_frame_offset(const GameSession *session,
                                        uint8_t island_index,
                                        uint8_t player_mask,
                                        int hovered)
{
    if (session == NULL || island_index >= session->island_count) return -1;
    if (!game_session_can_enter_island(session, island_index, player_mask)) return 15;
    return hovered ? 30 : 0;
}

int game_session_bridge_is_active(const GameSession *session,
                                  uint8_t bridge_index,
                                  uint8_t bridge_count)
{
    if (session == NULL || bridge_count > WORLD_MAP_MAX_BRIDGES ||
        bridge_index >= bridge_count) return 0;
    return (session->active_bridge_mask & (UINT32_C(1) << bridge_index)) != 0;
}

static int find_bridge_marker_index(const GameRuntimeIsland *island,
                                    uint8_t neighbor_island)
{
    unsigned int location_index;
    if (island == NULL) return -1;
    for (location_index = 0; location_index < island->location_count;
         ++location_index) {
        const GameRuntimeLocation *location = &island->locations[location_index];
        if (location->renderer_class == 2 &&
            location->bridge_neighbor_island == (int32_t)neighbor_island) {
            return (int)location_index;
        }
    }
    return -1;
}

int game_session_world_bridge_is_renderable(const GameSession *session,
                                            uint8_t bridge_index,
                                            uint8_t bridge_count,
                                            uint8_t island_a,
                                            uint8_t island_b)
{
    const GameRuntimeLocation *marker_a;
    const GameRuntimeLocation *marker_b;
    if (!game_session_bridge_is_active(session, bridge_index, bridge_count) ||
        island_a >= session->island_count || island_b >= session->island_count ||
        island_a == island_b) {
        return 0;
    }
    {
        int index_a = find_bridge_marker_index(&session->islands[island_a], island_b);
        int index_b = find_bridge_marker_index(&session->islands[island_b], island_a);
        if (index_a < 0 || index_b < 0) return 0;
        marker_a = &session->islands[island_a].locations[index_a];
        marker_b = &session->islands[island_b].locations[index_b];
    }
    return
           marker_a->bridge_constructed && marker_b->bridge_constructed;
}

int game_session_mark_bridge_constructed(GameSession *session,
                                         uint8_t bridge_index,
                                         uint8_t bridge_count,
                                         uint8_t island_a,
                                         uint8_t island_b)
{
    GameRuntimeLocation *marker_a;
    GameRuntimeLocation *marker_b;
    if (session == NULL || bridge_count > WORLD_MAP_MAX_BRIDGES ||
        bridge_index >= bridge_count || island_a >= session->island_count ||
        island_b >= session->island_count || island_a == island_b) {
        return 0;
    }
    {
        int index_a = find_bridge_marker_index(&session->islands[island_a], island_b);
        int index_b = find_bridge_marker_index(&session->islands[island_b], island_a);
        if (index_a < 0 || index_b < 0) return 0;
        marker_a = &session->islands[island_a].locations[index_a];
        marker_b = &session->islands[island_b].locations[index_b];
    }
    marker_a->bridge_constructed = 1;
    marker_b->bridge_constructed = 1;
    return game_session_set_bridge_active(session, bridge_index, bridge_count, 1);
}

int game_session_set_bridge_active(GameSession *session,
                                   uint8_t bridge_index,
                                   uint8_t bridge_count,
                                   int active)
{
    uint32_t bit;
    if (session == NULL || bridge_count > WORLD_MAP_MAX_BRIDGES ||
        bridge_index >= bridge_count) return 0;
    bit = UINT32_C(1) << bridge_index;
    if (active) session->active_bridge_mask |= bit;
    else session->active_bridge_mask &= ~bit;
    return 1;
}

int game_session_apply_world_bridge_message(GameSession *session,
                                            uint8_t bridge_count,
                                            uint32_t parameter_flags)
{
    uint32_t mask;
    if (session == NULL || bridge_count > WORLD_MAP_MAX_BRIDGES) return 0;
    if (bridge_count == 0) mask = 0;
    else if (bridge_count == WORLD_MAP_MAX_BRIDGES) mask = UINT32_MAX;
    else mask = (UINT32_C(1) << bridge_count) - UINT32_C(1);
    session->active_bridge_mask = (parameter_flags & UINT32_C(0x100)) == 0
        ? mask : 0;
    return 1;
}

