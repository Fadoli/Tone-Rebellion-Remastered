#include "game_session_movement_internal.h"

#include "game_session_action9.h"
#include "game_session_delivery_internal.h"
#include "game_session_events.h"

static int location_inside_floater_bounds(const GameRuntimeIsland *island,
                                          uint8_t player_slot,
                                          const GameRuntimeLocation *location)
{
    if (player_slot >= GAME_FLOATER_CATEGORY_COUNT) return 0;
    return (int32_t)location->x >= island->floater_min_x[player_slot] &&
           (int32_t)location->x <= island->floater_max_x[player_slot];
}

static int find_departure_bridge(const GameSession *session,
                                 const GameFloaterStart *floater,
                                 uint8_t target_island)
{
    const GameRuntimeIsland *island;
    int best_index = -1;
    int32_t best_distance = 6000;
    unsigned int index;

    if (floater->island_index >= session->island_count) return -1;
    island = &session->islands[floater->island_index];
    if (island->location_count > ISLAND_DATA_MAX_LOCATIONS) return -1;

    for (index = 0; index < island->location_count; ++index) {
        const GameRuntimeLocation *location = &island->locations[index];
        int32_t distance;

        if (location->renderer_class != 2 ||
            (location->source_flags & 1U) == 0 ||
            !location_inside_floater_bounds(island, floater->owner_slot,
                                            location)) {
            continue;
        }
        if (location->bridge_neighbor_island == (int32_t)target_island) {
            return (int)index;
        }
        distance = game_session_source_chebyshev_distance(
            floater->x, floater->y, location->x, location->y);
        if (distance < best_distance) {
            best_index = (int)index;
            best_distance = distance;
        }
    }
    return best_index;
}

static int find_linked_bridge(const GameSession *session,
                              uint8_t island_index,
                              uint8_t neighbor_island)
{
    const GameRuntimeIsland *island;
    unsigned int index;

    if (island_index >= session->island_count) return -1;
    island = &session->islands[island_index];
    if (island->location_count > ISLAND_DATA_MAX_LOCATIONS) return -1;
    for (index = 0; index < island->location_count; ++index) {
        const GameRuntimeLocation *location = &island->locations[index];
        if (location->renderer_class == 2 &&
            location->bridge_neighbor_island == (int32_t)neighbor_island) {
            return (int)index;
        }
    }
    return -1;
}

int game_session_begin_floater_handoff(GameSession *session,
                                       GameFloaterStart *floater,
                                       uint8_t target_island)
{
    const GameRuntimeIsland *source_island;
    const GameRuntimeLocation *departure;
    int departure_index;

    if (session == NULL || floater == NULL ||
        !game_session_floater_is_active(floater) ||
        (floater->source_runtime_flags & 0x008U) != 0 ||
        floater->island_index >= session->island_count ||
        target_island >= session->island_count ||
        floater->type_index >= GAME_FLOATER_CATEGORY_COUNT) {
        return 0;
    }
    if (target_island == floater->island_index) return 1;

    departure_index = find_departure_bridge(session, floater, target_island);
    if (departure_index < 0) return 0;
    source_island = &session->islands[floater->island_index];
    departure = &source_island->locations[departure_index];

    floater->handoff_target_island = target_island;
    floater->handoff_departure_location = (int16_t)departure_index;
    floater->handoff_resume_action = floater->active_order_action == 0
        ? 9 : floater->active_order_action;
    floater->handoff_resume_state = 9;
    floater->order_timer = 0;
    floater->movement_state = 0x11;
    floater->active_order_action = 9;
    floater->destination_x = departure->x;
    floater->destination_y = departure->y;
    floater->stop_radius = 0;
    floater->has_move_order = 1;
    floater->has_wander_order = 0;
    floater->wander_timer = 0;
    return 1;
}

static int find_handoff_arrival(const GameSession *session,
                                const GameFloaterStart *floater,
                                int preferred_arrival)
{
    const GameRuntimeIsland *island =
        &session->islands[floater->handoff_target_island];
    unsigned int index;
    int best_index = -1;
    int32_t best_distance = 8000;
    int32_t reference_x = 0x500;
    int32_t reference_y = 0xa0;

    if (island->location_count > ISLAND_DATA_MAX_LOCATIONS) return -1;
    if (preferred_arrival >= 0 &&
        (unsigned int)preferred_arrival < island->location_count &&
        (island->locations[preferred_arrival].source_flags & 1U) != 0) {
        return preferred_arrival;
    }

    if (floater->handoff_resume_action == 6 ||
        floater->handoff_resume_action == 8) {
        if (floater->order_target_floater >= 0 &&
            (unsigned int)floater->order_target_floater <
                session->floater_count) {
            const GameFloaterStart *target =
                &session->floaters[(unsigned int)floater->order_target_floater];
            reference_x = target->x;
            reference_y = target->y;
        }
    } else if (floater->handoff_resume_action == 9) {
        reference_x =
            (int32_t)(floater->source_order_coordinate_30 >> 8) * 10;
        reference_y =
            (int32_t)(floater->source_order_coordinate_30 & 0xffU) * 10;
    } else if (floater->handoff_resume_action != 0x0e &&
               floater->order_target_location >= 0 &&
               (uint16_t)floater->order_target_location <
                   island->location_count) {
        const GameRuntimeLocation *target =
            &island->locations[(uint16_t)floater->order_target_location];
        reference_x = target->x;
        reference_y = target->y;
    }

    if (island->location_count > ISLAND_DATA_MAX_LOCATIONS) return -1;
    for (index = 0; index < island->location_count; ++index) {
        const GameRuntimeLocation *location = &island->locations[index];
        int32_t distance;
        if (location->renderer_class != 2 ||
            (location->source_flags & 1U) == 0 ||
            !location_inside_floater_bounds(island, floater->owner_slot,
                                            location)) {
            continue;
        }
        distance = game_session_source_chebyshev_distance(
            location->x, location->y, reference_x, reference_y);
        if (distance < best_distance) {
            best_index = (int)index;
            best_distance = distance;
        }
    }
    return best_index;
}

static void cancel_handoff(GameSession *session, GameFloaterStart *floater)
{
    if (floater->linked_task_slot != -1) release_task_claim(session, floater);
    floater->movement_state = 0;
    floater->has_move_order = 0;
    floater->active_order_action = 0;
    floater->order_timer = 0;
    floater->source_order_pending = 0;
    floater->handoff_departure_location = -1;
}

int game_session_tick_floater_handoff(GameSession *session,
                                      GameFloaterStart *floater)
{
    const GameRuntimeLocation *departure;
    int preferred_arrival;

    if (session == NULL || floater == NULL || floater->movement_state != 0x11)
        return 0;
    if (floater->island_index >= session->island_count ||
        session->islands[floater->island_index].location_count >
            ISLAND_DATA_MAX_LOCATIONS ||
        floater->handoff_target_island >= session->island_count ||
        session->islands[floater->handoff_target_island].location_count >
            ISLAND_DATA_MAX_LOCATIONS ||
        floater->handoff_departure_location < 0 ||
        (uint16_t)floater->handoff_departure_location >=
            session->islands[floater->island_index].location_count) {
        cancel_handoff(session, floater);
        return 1;
    }

    departure = &session->islands[floater->island_index]
                     .locations[(uint16_t)floater->handoff_departure_location];
    if (floater->has_move_order) {
        if (floater->x != departure->x || floater->y != departure->y) return 0;
        floater->has_move_order = 0;
    }

    if (floater->order_timer == 0) {
        if ((departure->source_flags & 1U) == 0) {
            cancel_handoff(session, floater);
        } else {
            floater->order_timer = 1;
        }
        return 1;
    }
    if (floater->order_timer < 60) {
        ++floater->order_timer;
        return 1;
    }
    if (floater->order_timer == 60) {
        preferred_arrival = find_linked_bridge(
            session, floater->handoff_target_island, floater->island_index);
        if (preferred_arrival >= 0 &&
            (unsigned int)preferred_arrival <
                session->islands[floater->handoff_target_island].location_count &&
            (session->islands[floater->handoff_target_island]
                 .locations[preferred_arrival].source_flags & 1U) != 0) {
            floater->order_timer = 320;
        } else {
            floater->order_timer = 620;
        }
        return 1;
    }

    if (floater->order_timer == 120) {
        GameRuntimeIsland *target_island =
            &session->islands[floater->handoff_target_island];
        preferred_arrival = find_linked_bridge(
            session, floater->handoff_target_island, floater->island_index);
        int arrival_index = find_handoff_arrival(session, floater,
                                                 preferred_arrival);
        if (arrival_index < 0 ||
            (unsigned int)arrival_index >= target_island->location_count) {
            cancel_handoff(session, floater);
            return 1;
        }
        {
            const GameRuntimeLocation *arrival =
                &target_island->locations[arrival_index];
            uint16_t arrival_y = (uint16_t)(arrival->y - 30U);
            floater->x = arrival->x;
            floater->y = arrival_y;
            floater->destination_x = arrival->x;
            floater->destination_y = arrival_y;
            /* The session's CHARGE source index is local to the current
               island; release it before switching island tables. */
            (void)game_session_unlink_floater_charge(
                session, (unsigned int)(floater - session->floaters));
            floater->island_index = floater->handoff_target_island;
        }
    }

    --floater->order_timer;
    if (floater->order_timer == 60) {
        uint8_t resume_action = floater->handoff_resume_action;
        uint8_t resume_state = floater->handoff_resume_state;
        floater->order_timer = 0;
        floater->handoff_departure_location = -1;
        if ((resume_action == 4 || resume_action == 0x12) &&
            (resume_state == 3 || resume_state == 4)) {
            uint8_t destination_island = resume_state == 3
                ? floater->order_source_island : floater->order_target_island;
            int16_t destination_location = resume_state == 3
                ? floater->order_source_location : floater->order_target_location;
            if (destination_island >= session->island_count ||
                destination_island != floater->island_index ||
                destination_location < 0 ||
                (uint16_t)destination_location >=
                    session->islands[destination_island].location_count) {
                cancel_handoff(session, floater);
                return 1;
            }
            {
                const GameRuntimeLocation *location =
                    &session->islands[destination_island]
                         .locations[(uint16_t)destination_location];
                floater->destination_x = location->x;
                floater->destination_y = location->y;
            }
            floater->movement_state = resume_state;
            floater->active_order_action = resume_action;
        } else if (resume_action == 0 && resume_state == 11 &&
                   floater->source_order_parameter_32 <
                       session->islands[floater->island_index].location_count) {
            floater->movement_state = 11;
            floater->active_order_action = 0;
        } else if (resume_action == 0x0e) {
            floater->movement_state = 0;
            floater->active_order_action = 0x0e;
            floater->has_wander_order = 1;
            floater->wander_timer = 0;
        } else {
            floater->movement_state = 9;
            floater->active_order_action = 9;
            floater->destination_x =
                (uint16_t)(floater->source_order_coordinate_30 >> 8) * 10U;
            floater->destination_y =
                (uint16_t)(floater->source_order_coordinate_30 & 0xffU) * 10U;
        }
        floater->stop_radius = 0;
        floater->has_move_order = (uint8_t)(resume_action != 0x0e);
    }
    return 1;
}
