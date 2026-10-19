#include "game_session_delivery_internal.h"

void game_session_assign_local_resource_tasks(GameSession *session)
{
    unsigned int floater_index;

    for (floater_index = 0; floater_index < session->floater_count;
         ++floater_index) {
        GameFloaterStart *floater = &session->floaters[floater_index];
        unsigned int slot;

        if (floater->active_order_action != 0 || floater->linked_task_slot != -1 ||
            floater->source_link_0c != -1 ||
            floater->type_index == 4 || floater->source_subtype == 8 ||
            floater->movement_state == 6 || floater->movement_state == 7 ||
            floater->movement_state != 0 || floater->island_index >= session->island_count)
            continue;

        for (slot = 0; slot < GAME_SESSION_MAX_PENDING_EVENTS; ++slot) {
            const GamePendingEvent *event = &session->pending_events[slot];
            int source_index;
            GameRuntimeIsland *island;

            if (event->active == 0 || event->action_type != 4 ||
                event->player_id != floater->owner_slot ||
                event->payload_0a != floater->island_index ||
                event->payload_12 < 1 || event->payload_12 > GAME_RESOURCE_TYPE_COUNT ||
                event->payload_0a < 0 || event->payload_0a >= session->island_count ||
                event->payload_0e < 0 ||
                event->payload_0e >= session->islands[event->payload_0a].location_count)
                continue;

            source_index = floater->carried_resource_code == event->payload_12
                ? -1
                : local_refill_source(session, floater->island_index,
                                      event->player_id, event->payload_12);
            if (floater->carried_resource_code != event->payload_12 && source_index < 0)
                continue;
            if (event->assigned_floater_count == INT16_MAX) continue;

            island = &session->islands[floater->island_index];
            ++session->pending_events[slot].assigned_floater_count;
            floater->active_order_action = 4;
            floater->order_resource_code = event->payload_12;
            floater->linked_task_slot = (int16_t)slot;
            floater->order_target_location = event->payload_0e;
            floater->order_timer = 0;
            if (floater->carried_resource_code == event->payload_12) {
                floater_target_location(floater,
                    &island->locations[(uint16_t)event->payload_0e], 4);
            } else {
                floater->order_source_location = (int16_t)source_index;
                floater_target_location(floater,
                    &island->locations[(unsigned int)source_index], 3);
            }
            floater->has_wander_order = 0;
            floater->wander_timer = 0;
            break;
        }
    }
}

void game_session_advance_local_resource_task(GameSession *session,
                                       GameFloaterStart *floater)
{
    GameRuntimeIsland *island;
    GameRuntimeLocation *target;
    int16_t code;

    if (floater->active_order_action != 4 ||
        floater->island_index >= session->island_count ||
        floater->order_target_location < 0 ||
        (uint16_t)floater->order_target_location >=
            session->islands[floater->island_index].location_count ||
        floater->x != floater->destination_x || floater->y != floater->destination_y)
        return;

    island = &session->islands[floater->island_index];
    target = &island->locations[(uint16_t)floater->order_target_location];
    code = floater->order_resource_code;
    if (floater->movement_state == 3) {
        GameRuntimeLocation *source;
        if (floater->order_source_location < 0 ||
            (uint16_t)floater->order_source_location >= island->location_count)
            return;
        source = &island->locations[(uint16_t)floater->order_source_location];
        if (source->record_value_10 == 0x2a ||
            source->source_location_slot_18 != -1 ||
            (floater->source_runtime_flags & 1U) != 0) {
            /* This branch counts to 20 after arrival before checking stock. */
            if (floater->order_timer == 0) {
                floater->source_runtime_flags |= 1U;
                floater->order_timer = 1;
            } else if (floater->order_timer < 20) {
                ++floater->order_timer;
            }
            if (floater->order_timer < 20) return;
            if (!game_session_location_resource_available(session,
                    floater->island_index,
                    (uint16_t)floater->order_source_location, code) ||
                !game_session_consume_location_resource(session,
                    floater->island_index,
                    (uint16_t)floater->order_source_location, code)) {
                floater->active_order_action = 0;
                release_task_claim(session, floater);
                floater->has_move_order = 0;
                floater->movement_state = 0;
                floater->source_runtime_flags &= ~1U;
                floater->has_wander_order = 1;
                floater->wander_timer = 0;
                floater->order_timer = 0;
                return;
            }
            floater->source_runtime_flags &= ~1U;
        } else {
            int available = 0;
            /* FUN_00452e4d compares source +0x36 with the floater pickup tick.
               It checks output availability when the counter advances, resets
               +0x36 on success, and records the attempted tick on failure.
               Runtime initialization of +0x36 is not established by the
               decompilation; the remake starts this modeled field at zero. */
            if (floater->order_timer < INT16_MAX) ++floater->order_timer;
            if (source->resource_retry_tick_36 < (int16_t)floater->order_timer) {
                available = game_session_location_resource_available(session,
                    floater->island_index,
                    (uint16_t)floater->order_source_location, code);
                if (available) {
                    source->resource_retry_tick_36 = 0;
                    available = game_session_consume_location_resource(session,
                        floater->island_index,
                        (uint16_t)floater->order_source_location, code);
                } else {
                    source->resource_retry_tick_36 = (int16_t)floater->order_timer;
                }
            }
            if (!available) {
                if (!local_refill_source_is_valid(session, floater->island_index,
                        (uint16_t)floater->order_source_location,
                        floater->owner_slot, code)) {
                    floater->active_order_action = 0;
                    release_task_claim(session, floater);
                    floater->has_move_order = 0;
                    floater->movement_state = 0;
                    floater->source_runtime_flags &= ~1U;
                    floater->has_wander_order = 1;
                    floater->wander_timer = 0;
                }
                return;
            }
        }
        floater->carried_resource_code = code;
        floater->order_timer = 0;
        floater_target_location(floater, target, 4);
        return;
    }
    if (floater->movement_state != 4) return;

    /* FUN_0041e569 state 4 (switch case 3) reaches FUN_004503bd after exact
       arrival. For a Hall-class target it waits through the source's 20-tick
       phase, then attempts the resource credit; cargo is cleared only on
       success. FUN_004527ee belongs to the following state, not this deposit. */
    if (target->record_value_10 == 0x2a ||
        target->source_location_slot_18 != -1 ||
        (floater->source_runtime_flags & 1U) != 0) {
        if (floater->order_timer == 0) {
            floater->source_runtime_flags |= 1U;
            floater->order_timer = 1;
            return;
        }
        if (floater->order_timer < 20) {
            ++floater->order_timer;
            return;
        }
        if (target->owner_id == 0 && code >= 1 &&
            code <= GAME_RESOURCE_TYPE_COUNT &&
            game_session_credit_resource(session, floater->owner_slot,
                (GameResourceType)(code - 1), 1)) {
            floater->carried_resource_code = 0;
        }
        floater->source_runtime_flags &= ~1U;
        floater->active_order_action = 0;
        release_task_claim(session, floater);
        floater->has_move_order = 0;
        floater->movement_state = 0;
        floater->order_timer = 0;
        return;
    }

    /* The other state-4 path finishes on exact arrival and attempts the same
       receiver without the 20-tick Hall wait. */
    if (code >= 1 && code <= GAME_RESOURCE_TYPE_COUNT &&
        game_session_credit_resource(session, floater->owner_slot,
            (GameResourceType)(code - 1), 1)) {
        floater->carried_resource_code = 0;
    }
    floater->active_order_action = 0;
    release_task_claim(session, floater);
    floater->has_move_order = 0;
    floater->movement_state = 0;
    floater->order_timer = 0;
    floater->source_runtime_flags &= ~1U;
}

#include "game_session_delivery_internal.h"

int local_refill_source_is_valid(const GameSession *session,
                                       uint8_t island_index,
                                       uint16_t location_index,
                                       int16_t player_id,
                                       int16_t resource_code)
{
    const GameRuntimeIsland *island;
    int32_t producer_item;

    if (island_index >= session->island_count || resource_code < 1 ||
        resource_code > GAME_RESOURCE_TYPE_COUNT) return 0;
    island = &session->islands[island_index];
    if (location_index >= island->location_count) return 0;
    producer_item = resource_code == 1 ? 0x25 :
                    resource_code == 2 ? 0x27 : 0x26;
    {
        const GameRuntimeLocation *location = &island->locations[location_index];
        return location->owner_id == player_id &&
               location->record_value_10 == producer_item &&
               (location->source_flags & 1U) != 0;
    }
}

int local_refill_source(const GameSession *session, uint8_t island_index,
                               int16_t player_id, int16_t resource_code)
{
    const GameRuntimeIsland *island;
    unsigned int location_index;

    if (island_index >= session->island_count ||
        resource_code < 1 || resource_code > GAME_RESOURCE_TYPE_COUNT) return -1;
    island = &session->islands[island_index];
    /* FUN_00452ceb maps resource codes 1/2/3 to producer IDs 0x25/0x27/0x26.
       The current model does not have the source's per-player/island X bounds
       or weighted candidate selection, so retain the first eligible local
       producer in source-location order. */
    for (location_index = 0; location_index < island->location_count;
         ++location_index) {
        if (local_refill_source_is_valid(session, island_index,
                (uint16_t)location_index, player_id, resource_code)) {
            return (int)location_index;
        }
    }
    return -1;
}

void floater_target_location(GameFloaterStart *floater,
                                    const GameRuntimeLocation *location,
                                    uint8_t state)
{
    floater->destination_x = location->x;
    floater->destination_y = location->y;
    floater->movement_state = state;
    floater->stop_radius = 0;
    floater->has_move_order = 1;
}

void release_task_claim(GameSession *session, GameFloaterStart *floater)
{
    int16_t slot = floater->linked_task_slot;
    if (slot >= 0 && slot < GAME_SESSION_MAX_PENDING_EVENTS) {
        GamePendingEvent *event = &session->pending_events[(uint8_t)slot];
        if (event->active != 0 && event->action_type == 4 &&
            event->player_id == floater->owner_slot &&
            event->payload_0a == floater->island_index &&
            event->payload_0e == floater->order_target_location &&
            event->payload_12 == floater->order_resource_code &&
            event->assigned_floater_count > 0) {
            --event->assigned_floater_count;
        }
    }
    floater->linked_task_slot = -1;
}
