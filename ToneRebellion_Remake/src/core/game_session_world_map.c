#include "game_session.h"
#include "game_session_events.h"

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

static int mark_bridge_constructed_with_contributor(
    GameSession *session, uint8_t bridge_index, uint8_t bridge_count,
    uint8_t island_a, uint8_t island_b, uint16_t contributor_slot)
{
    GameRuntimeLocation *marker_a;
    GameRuntimeLocation *marker_b;
    int was_constructed;
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
    was_constructed = marker_a->bridge_constructed &&
                      marker_b->bridge_constructed;
    marker_a->bridge_constructed = 1;
    marker_b->bridge_constructed = 1;
    marker_a->source_flags |= 1U;
    marker_b->source_flags |= 1U;
    if (!game_session_set_bridge_active(session, bridge_index, bridge_count, 1))
        return 0;
    /* FUN_004669bd reads +0x2c from the marker whose PROD just completed.
       Class-2 markers store that contributor in the aliased third stock word. */
    if (contributor_slot < GAME_START_PLAYER_COUNT) {
        (void)game_session_acquire_island_access(
            session, (uint8_t)contributor_slot, island_a, island_b);
    }
    /* FUN_004669bd refreshes both endpoint islands through FUN_00466c8b. */
    game_session_refresh_player_maintenance_budgets(session);
    game_session_recalculate_leviathan_island(session, island_a);
    game_session_recalculate_leviathan_island(session, island_b);
    if (!was_constructed)
        (void)game_session_queue_audio_event(
            session, GAME_SESSION_AUDIO_BRIDGE, -1);
    return 1;
}

int game_session_mark_bridge_constructed(GameSession *session,
                                         uint8_t bridge_index,
                                         uint8_t bridge_count,
                                         uint8_t island_a,
                                         uint8_t island_b)
{
    int marker_index;
    uint16_t contributor_slot;
    if (session == NULL || island_a >= session->island_count) return 0;
    marker_index = find_bridge_marker_index(&session->islands[island_a],
                                            island_b);
    if (marker_index < 0) return 0;
    contributor_slot = session->islands[island_a]
        .locations[marker_index].resource_stock[GAME_RESOURCE_MAGIC_TONE];
    return mark_bridge_constructed_with_contributor(
        session, bridge_index, bridge_count, island_a, island_b,
        contributor_slot);
}

int game_session_mark_bridge_constructed_at(GameSession *session,
                                            uint8_t island_index,
                                            uint16_t location_index)
{
    const GameRuntimeIsland *island;
    const GameRuntimeLocation *marker;
    unsigned int bridge_index;

    if (session == NULL || island_index >= session->island_count) return 0;
    island = &session->islands[island_index];
    if (location_index >= island->location_count) return 0;
    marker = &island->locations[location_index];
    if (marker->renderer_class != 2 || marker->bridge_neighbor_island < 0 ||
        marker->bridge_neighbor_island >= session->island_count) return 0;

    for (bridge_index = 0; bridge_index < session->world_bridge_count;
         ++bridge_index) {
        const WorldBridge *bridge = &session->world_bridges[bridge_index];
        if ((bridge->island_a == island_index &&
             bridge->island_b == marker->bridge_neighbor_island) ||
            (bridge->island_b == island_index &&
             bridge->island_a == marker->bridge_neighbor_island)) {
            return mark_bridge_constructed_with_contributor(
                session, (uint8_t)bridge_index, session->world_bridge_count,
                island_index, (uint8_t)marker->bridge_neighbor_island,
                marker->resource_stock[GAME_RESOURCE_MAGIC_TONE]);
        }
    }
    return 0;
}

int game_session_acquire_island_access(GameSession *session,
                                       uint8_t player_slot,
                                       uint8_t source_island,
                                       uint8_t target_island)
{
    GameRuntimeIsland *target;
    uint8_t player_bit;
    int marker_index;

    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT ||
        source_island >= session->island_count ||
        target_island >= session->island_count ||
        source_island == target_island) return 0;
    target = &session->islands[target_island];
    player_bit = (uint8_t)(1U << player_slot);
    if ((target->access_mask & player_bit) != 0) return 0;

    target->access_mask |= player_bit;
    marker_index = find_bridge_marker_index(target, source_island);
    if (marker_index >= 0) {
        int32_t min_x = (int32_t)target->locations[marker_index].x - 0x140;
        if (min_x < 0) min_x = 0;
        if (min_x > 0x780) min_x = 0x780;
        target->floater_min_x[player_slot] = min_x;
        target->floater_max_x[player_slot] = min_x + 0x27f;
    }
    (void)game_session_recalculate_player_island_visibility(
        session, target_island, player_slot);
    return 1;
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

