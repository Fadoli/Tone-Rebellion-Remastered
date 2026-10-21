#include "game_session.h"
#include "game_session_delivery_internal.h"

#include <string.h>

int game_session_pending_event_add(GameSession *session, int16_t player_id,
                                   int16_t payload_0a, int16_t action_type,
                                   int16_t payload_0c, int16_t payload_0e,
                                   int16_t payload_12)
{
    unsigned int slot;
    GamePendingEvent *event;

    if (session == NULL || session->pending_event_count >=
        GAME_SESSION_MAX_PENDING_EVENTS) return -1;
    for (slot = 0; slot < GAME_SESSION_MAX_PENDING_EVENTS; ++slot) {
        if (session->pending_events[slot].active == 0) break;
    }
    if (slot == GAME_SESSION_MAX_PENDING_EVENTS) return -1;

    event = &session->pending_events[slot];
    memset(event, 0, sizeof(*event));
    event->player_id = player_id;
    event->payload_0a = payload_0a;
    event->action_type = action_type;
    event->payload_0c = payload_0c;
    event->payload_0e = payload_0e;
    event->payload_12 = payload_12;
    event->active = 1;
    event->priority = 1;
    ++session->pending_event_count;

    if (action_type == 5 || action_type == 13) {
        unsigned int other;
        for (other = 0; other < GAME_SESSION_MAX_PENDING_EVENTS; ++other) {
            const GamePendingEvent *candidate = &session->pending_events[other];
            /* These modeled task records are scoped to a player and island;
               omitting either field aliases otherwise identical local IDs. */
            if (other == slot || candidate->active == 0 ||
                candidate->action_type != action_type ||
                candidate->player_id != player_id ||
                candidate->payload_0a != payload_0a ||
                candidate->payload_0c != payload_0c ||
                candidate->payload_0e != payload_0e ||
                candidate->payload_12 != payload_12) continue;
            event->active = 0;
            --session->pending_event_count;
            return -1;
        }
    }
    return (int)slot;
}

size_t game_session_collect_task_slots(const GameSession *session,
                                       int16_t player_id,
                                       uint8_t *slot_indices,
                                       size_t capacity)
{
    size_t count = 0;
    unsigned int slot;
    if (session == NULL) return 0;
    for (slot = 0; slot < GAME_SESSION_MAX_PENDING_EVENTS &&
         count < GAME_SESSION_MAX_TASKS; ++slot) {
        const GamePendingEvent *event = &session->pending_events[slot];
        if (event->active == 0 || event->player_id != player_id ||
            event->action_type == 0xb) continue;
        if (slot_indices != NULL && count < capacity)
            slot_indices[count] = (uint8_t)slot;
        ++count;
    }
    return count;
}

int game_session_dispatch_task_command(GameSession *session, uint8_t slot,
                                       uint8_t subtype,
                                       const GamePendingEvent *expected)
{
    GamePendingEvent *event;
    if (session == NULL || expected == NULL ||
        slot >= GAME_SESSION_MAX_PENDING_EVENTS ||
        subtype < 12 || subtype > 15) return 0;
    event = &session->pending_events[slot];
    if (event->active == 0 ||
        event->player_id != expected->player_id ||
        event->payload_0a != expected->payload_0a ||
        event->action_type != expected->action_type ||
        event->payload_12 != expected->payload_12) return 0;
    if (subtype == 12) {
        unsigned int player;
        unsigned int floater_index;
        if (event->action_type == 5 && event->payload_0a >= 0 &&
            (uint16_t)event->payload_0a < session->island_count) {
            GameRuntimeIsland *island =
                &session->islands[(uint16_t)event->payload_0a];
            if (event->payload_0e >= 0 &&
                (uint16_t)event->payload_0e < island->location_count) {
                GameRuntimeLocation *location =
                    &island->locations[(uint16_t)event->payload_0e];
                if (location->record_value_10 == 0 ||
                    location->record_value_10 == 1) {
                    /* FUN_00466533 clears the construction site's owner for
                       these two status values before releasing the slot. */
                    location->owner_id = -1;
                    location->source_value_14 = -1;
                }
            }
        }
        /* FUN_0045fb6f clears the matching Hall resource-request reference
           and returns that mode to 1. Other source link tables are unmodeled. */
        for (player = 0; player < GAME_START_PLAYER_COUNT; ++player) {
            GamePlayerEconomy *economy = &session->economy[player];
            unsigned int resource;
            for (resource = 0; resource < GAME_RESOURCE_TYPE_COUNT; ++resource) {
                if (economy->resource_task_slot[resource] == (int16_t)slot &&
                    event->player_id == (int16_t)player &&
                    event->action_type == 4 &&
                    event->payload_0a == economy->hall_island_index &&
                    event->payload_0e == economy->hall_location_index &&
                    event->payload_12 == (int16_t)(resource + 1U)) {
                    economy->resource_task_slot[resource] = -1;
                    economy->stock_mode[resource] = 1;
                    break;
                }
            }
        }
        /* FUN_00466533 calls FUN_00420669 for every live floater before
           releasing the pending slot. The native helper drops that floater's
           task claim and clears its active order when it points at this slot. */
        for (floater_index = 0; floater_index < session->floater_count &&
             floater_index < GAME_SESSION_MAX_FLOATERS; ++floater_index) {
            GameFloaterStart *floater = &session->floaters[floater_index];
            if (!game_session_floater_is_active(floater) ||
                floater->linked_task_slot != (int16_t)slot) continue;
            release_task_claim(session, floater);
            floater->active_order_action = 0;
            floater->order_target_floater = -1;
            floater->order_target_location = -1;
            floater->order_target_island = UINT8_MAX;
            floater->order_progress = 0;
            floater->order_resource_code = GAME_RESOURCE_NONE;
            floater->order_timer = 0;
            floater->source_order_state_2c = 0;
            floater->source_order_coordinate_30 = 0;
            floater->source_order_pending = 0;
            floater->source_runtime_flags &= ~0x065U;
            floater->has_move_order = 0;
            floater->handoff_target_island = UINT8_MAX;
            floater->handoff_departure_location = -1;
            floater->handoff_resume_action = 0;
            floater->handoff_resume_state = 0;
            floater->movement_state = 0;
            floater->has_wander_order = 1;
            floater->wander_timer = 0;
        }
        return game_session_pending_event_release(session, slot);
    }
    event->priority = (uint16_t)(subtype - 12);
    return 1;
}

unsigned int game_session_cancel_tasks_for_location(GameSession *session,
                                                    uint8_t island_index,
                                                    uint16_t location_index)
{
    unsigned int slot;
    unsigned int cancelled = 0;
    if (session == NULL || island_index >= session->island_count ||
        location_index >= session->islands[island_index].location_count) return 0;
    for (slot = 0; slot < GAME_SESSION_MAX_PENDING_EVENTS; ++slot) {
        GamePendingEvent *event = &session->pending_events[slot];
        int targets_location;
        if (event->active == 0 || event->payload_0a != island_index) continue;
        if (event->action_type == 0x0b) {
            targets_location = event->payload_0c == (int16_t)location_index;
        } else if (event->action_type == 4 || event->action_type == 5 ||
                   event->action_type == 0x12) {
            targets_location = event->payload_0e == (int16_t)location_index;
        } else {
            continue;
        }
        if (targets_location) {
            GamePendingEvent expected = *event;
            cancelled += (unsigned int)game_session_dispatch_task_command(
                session, (uint8_t)slot, 12, &expected);
        }
    }
    return cancelled;
}


int game_session_pending_event_release(GameSession *session, uint8_t slot)
{
    GamePendingEvent *event;
    if (session == NULL || slot >= GAME_SESSION_MAX_PENDING_EVENTS) return 0;
    event = &session->pending_events[slot];
    if (event->active == 0 || session->pending_event_count == 0) return 0;
    event->active = 0;
    --session->pending_event_count;
    return 1;
}
