#include "game_session.h"
#include "game_session_events.h"

#include <string.h>

/* Deferred building-selection and island events. */

int game_session_queue_audio_event(GameSession *session, uint8_t kind,
                                   int16_t owner_id)
{
    unsigned int tail;
    GameSessionAudioEvent *event;

    if (session == NULL || session->audio_event_count >=
            GAME_SESSION_MAX_AUDIO_EVENTS ||
        (kind != GAME_SESSION_AUDIO_FLOATER_DEATH &&
         kind != GAME_SESSION_AUDIO_BUILD &&
         kind != GAME_SESSION_AUDIO_BRIDGE &&
         kind != GAME_SESSION_AUDIO_FLOATER_BIRTH)) return 0;
    tail = ((unsigned int)session->audio_event_head +
            session->audio_event_count) % GAME_SESSION_MAX_AUDIO_EVENTS;
    event = &session->audio_events[tail];
    event->kind = kind;
    event->owner_id = owner_id;
    ++session->audio_event_count;
    return 1;
}

int game_session_pop_audio_event(GameSession *session,
                                 GameSessionAudioEvent *out)
{
    if (session == NULL || out == NULL || session->audio_event_count == 0)
        return 0;
    *out = session->audio_events[session->audio_event_head];
    session->audio_event_head = (uint8_t)(
        ((unsigned int)session->audio_event_head + 1U) %
        GAME_SESSION_MAX_AUDIO_EVENTS);
    --session->audio_event_count;
    return 1;
}

int game_session_queue_world_event(GameSession *session, uint8_t kind,
                                   uint8_t island_index, int32_t payload)
{
    unsigned int tail;
    GameSessionWorldEvent *event;

    if (session == NULL ||
        (kind != GAME_SESSION_WORLD_EVENT_BUILDING_DESTROYED &&
         kind != GAME_SESSION_WORLD_EVENT_ISLAND_REACHED) ||
        island_index >= session->island_count ||
        session->world_event_count >= GAME_SESSION_MAX_WORLD_EVENTS) return 0;
    tail = ((unsigned int)session->world_event_head +
            session->world_event_count) % GAME_SESSION_MAX_WORLD_EVENTS;
    event = &session->world_events[tail];
    event->kind = kind;
    event->island_index = island_index;
    event->payload = payload;
    ++session->world_event_count;
    return 1;
}

int game_session_pop_world_event(GameSession *session,
                                 GameSessionWorldEvent *out)
{
    if (session == NULL || out == NULL || session->world_event_count == 0)
        return 0;
    *out = session->world_events[session->world_event_head];
    session->world_event_head = (uint8_t)(
        ((unsigned int)session->world_event_head + 1U) %
        GAME_SESSION_MAX_WORLD_EVENTS);
    --session->world_event_count;
    return 1;
}

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
    unsigned int read_index;
    unsigned int write_index = 0;
    unsigned int added = 0;
    unsigned int count;

    if (session == NULL) return 0;
    count = session->build_selection_count;
    for (read_index = 0; read_index < count; ++read_index) {
        GameBuildSelectionRequest request = session->build_selections[read_index];
        int slot;
        unsigned int other;
        int already_pending = 0;

        if (request.category != 0 || request.action_type != 5) continue;

        /* The native task table coalesces matching type-5 records. Treat an
           existing task as a successfully represented selection; otherwise
           preserve the outbox entry if the fixed task table is full. */
        for (other = 0; other < GAME_SESSION_MAX_PENDING_EVENTS; ++other) {
            const GamePendingEvent *candidate = &session->pending_events[other];
            if (candidate->active != 0 && candidate->action_type == 5 &&
                candidate->player_id == (int16_t)request.player_slot &&
                candidate->payload_0a == (int16_t)request.island_index_b &&
                candidate->payload_0c == (int16_t)request.reserved_zero &&
                candidate->payload_0e == (int16_t)request.location_index &&
                candidate->payload_12 == (int16_t)request.item_id) {
                already_pending = 1;
                break;
            }
        }
        if (already_pending) continue;

        /* FUN_004662b7 copies packet byte offsets +2/+4/+8/+10/+12/+14
           into the task record and sets priority 1. A building task belongs
           to one player and one island/site, so those fields participate in
           duplicate detection along with the site and building IDs. */
        slot = game_session_pending_event_add(
            session, (int16_t)request.player_slot,
            (int16_t)request.island_index_b,
            (int16_t)request.action_type,
            (int16_t)request.reserved_zero,
            (int16_t)request.location_index,
            (int16_t)request.item_id);
        if (slot >= 0) {
            ++added;
            continue;
        }

        /* The request remains queued when no pending-event slot is available.
           Keep it and every later request in their original order. */
        for (; read_index < count; ++read_index) {
            session->build_selections[write_index++] =
                session->build_selections[read_index];
        }
        break;
    }
    session->build_selection_count = (uint16_t)write_index;
    memset(&session->build_selections[write_index], 0,
           (size_t)(GAME_SESSION_MAX_BUILD_SELECTIONS - write_index) *
               sizeof(session->build_selections[0]));
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
    /* FUN_00453958 is a virtual active-state predicate. Keep the modeled
       active bit current before Hall requests are evaluated this tick. */
    (void)game_session_recalculate_active_locations(session);
}
