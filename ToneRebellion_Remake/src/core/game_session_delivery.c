#include "game_session_delivery_internal.h"
#include "game_session_action9.h"
#include "game_session_movement_internal.h"
#include "tone_rng.h"

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
            uint8_t source_island = floater->island_index;
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
                : refill_source(session, floater, event->payload_12,
                                &source_island);
            if (floater->carried_resource_code != event->payload_12 && source_index < 0)
                continue;
            if (event->assigned_floater_count == INT16_MAX) continue;

            island = &session->islands[floater->island_index];
            ++session->pending_events[slot].assigned_floater_count;
            floater->active_order_action = 4;
            floater->order_resource_code = event->payload_12;
            floater->linked_task_slot = (int16_t)slot;
            floater->order_target_location = event->payload_0e;
            floater->order_target_island = (uint8_t)event->payload_0a;
            floater->order_source_island = source_island;
            floater->order_timer = 0;
            if (floater->carried_resource_code == event->payload_12) {
                floater_target_location(floater,
                    &island->locations[(uint16_t)event->payload_0e], 4);
            } else {
                floater->order_source_location = (int16_t)source_index;
                if (source_island == floater->island_index) {
                    floater_target_location(floater,
                        &island->locations[(unsigned int)source_index], 3);
                } else {
                    const GameRuntimeLocation *source =
                        &session->islands[source_island]
                             .locations[(unsigned int)source_index];
                    floater->source_order_coordinate_30 = (uint16_t)(
                        ((uint16_t)(((uint32_t)source->x + 5U) / 10U) << 8) |
                        (uint16_t)(((uint32_t)source->y + 5U) / 10U));
                    if (!game_session_begin_floater_handoff(
                            session, floater, source_island)) {
                        floater->active_order_action = 0;
                        release_task_claim(session, floater);
                        continue;
                    }
                    floater->handoff_resume_state = 3;
                }
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
        floater->x != floater->destination_x || floater->y != floater->destination_y)
        return;

    code = floater->order_resource_code;
    if (floater->movement_state == 3) {
        GameRuntimeLocation *source;
        if (floater->island_index != floater->order_source_island ||
            floater->order_source_island >= session->island_count ||
            floater->order_source_location < 0 ||
            (uint16_t)floater->order_source_location >=
                session->islands[floater->order_source_island].location_count)
            return;
        island = &session->islands[floater->order_source_island];
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
        if (floater->order_target_island != floater->island_index) {
            const GameRuntimeLocation *hall;
            if (floater->order_target_island >= session->island_count ||
                floater->order_target_location < 0 ||
                (uint16_t)floater->order_target_location >=
                    session->islands[floater->order_target_island].location_count)
                return;
            hall = &session->islands[floater->order_target_island]
                        .locations[(uint16_t)floater->order_target_location];
            floater->source_order_coordinate_30 = (uint16_t)(
                ((uint16_t)(((uint32_t)hall->x + 5U) / 10U) << 8) |
                (uint16_t)(((uint32_t)hall->y + 5U) / 10U));
            if (game_session_begin_floater_handoff(
                    session, floater, floater->order_target_island)) {
                floater->handoff_resume_state = 4;
                return;
            }
            floater->active_order_action = 0;
            release_task_claim(session, floater);
            floater->movement_state = 0;
            return;
        }
        island = &session->islands[floater->order_target_island];
        target = &island->locations[(uint16_t)floater->order_target_location];
        floater_target_location(floater, target, 4);
        return;
    }
    if (floater->movement_state != 4) return;

    if (floater->island_index != floater->order_target_island ||
        floater->order_target_island >= session->island_count ||
        floater->order_target_location < 0 ||
        (uint16_t)floater->order_target_location >=
            session->islands[floater->order_target_island].location_count)
        return;
    island = &session->islands[floater->order_target_island];
    target = &island->locations[(uint16_t)floater->order_target_location];

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
        if (target->renderer_class == 0 && code >= 1 &&
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
        floater->has_wander_order = 1;
        floater->wander_timer = 0;
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
    floater->has_wander_order = 1;
    floater->wander_timer = 0;
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

static int local_refill_source_on_island(GameSession *session,
                                         uint8_t island_index,
                                         const GameFloaterStart *floater,
                                         int16_t resource_code)
{
    const GameRuntimeIsland *island;
    uint16_t candidate_indices[10];
    int32_t candidate_distances[10];
    unsigned int candidate_count = 0;
    int32_t distance_sum = 0;
    double inverse_weight_sum = 0.0;
    int32_t roll;
    unsigned int location_index;

    if (island_index >= session->island_count ||
        floater == 0 || floater->type_index >= GAME_FLOATER_CATEGORY_COUNT ||
        resource_code < 1 || resource_code > GAME_RESOURCE_TYPE_COUNT) return -1;
    island = &session->islands[island_index];
    /* FUN_00420a55 mode 0 filters by FUN_00452ceb and the floater's X window,
       keeps the ten lowest-distance candidates, then samples inversely by
       distance through FUN_0041e28e. */
    for (location_index = 0; location_index < island->location_count;
         ++location_index) {
        const GameRuntimeLocation *location = &island->locations[location_index];
        int32_t distance;
        unsigned int largest_index;
        unsigned int i;

        if (!local_refill_source_is_valid(session, island_index,
                (uint16_t)location_index, floater->owner_slot, resource_code) ||
            floater->owner_slot >= GAME_FLOATER_CATEGORY_COUNT ||
            (int32_t)location->x < island->floater_min_x[floater->owner_slot] ||
            (int32_t)location->x > island->floater_max_x[floater->owner_slot]) {
            continue;
        }
        distance = game_session_source_chebyshev_distance(
            floater->x, floater->y, location->x, location->y);
        if (distance == 0) continue;
        if (candidate_count < 10) {
            candidate_indices[candidate_count] = (uint16_t)location_index;
            candidate_distances[candidate_count] = distance;
            ++candidate_count;
            continue;
        }

        largest_index = 0;
        for (i = 1; i < candidate_count; ++i) {
            if (candidate_distances[i] > candidate_distances[largest_index])
                largest_index = i;
        }
        if (distance < candidate_distances[largest_index]) {
            candidate_indices[largest_index] = (uint16_t)location_index;
            candidate_distances[largest_index] = distance;
        }
    }
    if (candidate_count == 0) return -1;

    for (location_index = 0; location_index < candidate_count; ++location_index)
        distance_sum += candidate_distances[location_index];
    for (location_index = 0; location_index < candidate_count; ++location_index)
        inverse_weight_sum += (double)distance_sum /
                              (double)candidate_distances[location_index];

    roll = tone_rng_bounded(&session->random_state, 1000);
    {
        int32_t cumulative = 0;
        for (location_index = 0; location_index < candidate_count; ++location_index) {
            double raw_weight = (double)distance_sum /
                                (double)candidate_distances[location_index];
            cumulative += (int32_t)((1000.0 / inverse_weight_sum) * raw_weight + 0.5);
            if (roll < cumulative) return (int)candidate_indices[location_index];
        }
    }
    return -1;
}

int refill_source(GameSession *session, const GameFloaterStart *floater,
                  int16_t resource_code, uint8_t *source_island)
{
    unsigned int island_index;
    uint8_t current_island;
    uint8_t access_bit;
    int location_index;

    if (session == 0 || floater == 0 || source_island == 0 ||
        floater->island_index >= session->island_count ||
        floater->owner_slot >= GAME_FLOATER_CATEGORY_COUNT)
        return -1;

    current_island = floater->island_index;
    location_index = local_refill_source_on_island(
        session, current_island, floater, resource_code);
    if (location_index >= 0) {
        *source_island = current_island;
        return location_index;
    }

    /* FUN_00420dbd checks the current island first, then accessible island
       records in global order. Runtime +0x29ac is indexed by player slot. */
    access_bit = (uint8_t)(1U << floater->owner_slot);
    for (island_index = 0; island_index < session->island_count; ++island_index) {
        if (island_index == current_island ||
            (session->islands[island_index].access_mask & access_bit) == 0)
            continue;
        location_index = local_refill_source_on_island(
            session, (uint8_t)island_index, floater, resource_code);
        if (location_index >= 0) {
            *source_island = (uint8_t)island_index;
            return location_index;
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
            event->payload_0a == floater->order_target_island &&
            event->payload_0e == floater->order_target_location &&
            event->payload_12 == floater->order_resource_code &&
            event->assigned_floater_count > 0) {
            --event->assigned_floater_count;
        }
    }
    floater->linked_task_slot = -1;
}
