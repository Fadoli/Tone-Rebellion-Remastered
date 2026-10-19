#include "game_session_delivery_internal.h"

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
