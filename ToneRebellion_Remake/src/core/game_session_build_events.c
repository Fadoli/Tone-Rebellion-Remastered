#include "game_session.h"

#include <string.h>

/* Deferred building-selection and island events. */

int game_session_queue_build_selection(GameSession *session,
                                      uint8_t player_slot,
                                      uint8_t island_index,
                                      uint16_t location_index,
                                      uint16_t item_id)
{
    GameBuildSelectionRequest *request;
    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT ||
        island_index >= session->island_count ||
        location_index >= session->islands[island_index].location_count ||
        session->build_selection_count >= GAME_SESSION_MAX_BUILD_SELECTIONS) {
        return 0;
    }
    request = &session->build_selections[session->build_selection_count++];
    request->category = 0;
    request->player_slot = player_slot;
    request->action_type = 5;
    request->island_index_a = island_index;
    request->reserved_zero = 0;
    request->island_index_b = island_index;
    request->location_index = location_index;
    request->item_id = item_id;
    return 1;
}

int game_session_pop_build_selection(GameSession *session,
                                     GameBuildSelectionRequest *out)
{
    if (session == NULL || out == NULL || session->build_selection_count == 0) {
        return 0;
    }
    *out = session->build_selections[0];
    --session->build_selection_count;
    if (session->build_selection_count != 0) {
        memmove(&session->build_selections[0], &session->build_selections[1],
                (size_t)session->build_selection_count *
                sizeof(session->build_selections[0]));
    }
    memset(&session->build_selections[session->build_selection_count], 0,
           sizeof(session->build_selections[0]));
    return 1;
}

unsigned int game_session_dispatch_build_selections(GameSession *session)
{
    GameBuildSelectionRequest request;
    unsigned int added = 0;

    if (session == NULL) return 0;
    while (game_session_pop_build_selection(session, &request)) {
        int slot;
        if (request.category != 0 || request.action_type != 5) continue;

        /* FUN_004662b7 copies packet byte offsets +2/+4/+8/+10/+12/+14
           into the task record, sets priority 1, and deduplicates type 5
           records by payload_0c, payload_0e, and payload_12. */
        slot = game_session_pending_event_add(
            session, (int16_t)request.player_slot,
            (int16_t)request.island_index_b,
            (int16_t)request.action_type,
            (int16_t)request.reserved_zero,
            (int16_t)request.location_index,
            (int16_t)request.item_id);
        if (slot >= 0) ++added;
    }
    return added;
}

int game_session_queue_island_event3_subtype0(GameSession *session,
                                              uint8_t player_slot,
                                              uint8_t island_index)
{
    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT ||
        island_index >= session->island_count) return 0;
    session->islands[island_index].source_event3_pending_parity[player_slot] ^= 1U;
    return 1;
}

void game_session_dispatch_island_events(GameSession *session)
{
    unsigned int island_index;
    if (session == NULL) return;
    for (island_index = 0; island_index < session->island_count; ++island_index) {
        GameRuntimeIsland *island = &session->islands[island_index];
        unsigned int player_slot;
        for (player_slot = 0; player_slot < GAME_START_PLAYER_COUNT; ++player_slot) {
            if (island->source_event3_pending_parity[player_slot] != 0) {
                island->source_event_state[player_slot] ^= 1U;
                island->source_event3_pending_parity[player_slot] = 0;
            }
        }
    }
}
