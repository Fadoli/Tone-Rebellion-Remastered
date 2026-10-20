#include "game_session.h"
#include "game_session_internal.h"
#include "game_session_action9.h"
#include "floater_motion.h"
#include "game_session_delivery.h"

#include <string.h>

/* Floater movement, order execution and selection queries. */
uint16_t game_session_floater_approach_radius(
    const GameFloaterStart *floater);

int32_t game_session_source_chebyshev_distance(int32_t x1, int32_t y1,
                                         int32_t x2, int32_t y2)
{
    int32_t dx = x1 - x2;
    int32_t dy = y1 - y2;
    if (dx < 0) dx = -dx;
    if (dy < 0) dy = -dy;
    return dx > dy ? dx : dy;
}

static int action9_find_floater(const GameSession *session,
                                unsigned int source_index,
                                uint16_t target_x, uint16_t target_y,
                                int32_t max_distance)
{
    const GameFloaterStart *source = &session->floaters[source_index];
    unsigned int index;

    /* FUN_00420829 scans the current-island candidate list and accepts the
       first class/flag/distance match. The source table order currently
       follows floater insertion order in this model. */
    for (index = 0; index < session->floater_count; ++index) {
        const GameFloaterStart *candidate = &session->floaters[index];
        int category_matches;
        if (!game_session_floater_is_active(candidate) ||
            (candidate->source_runtime_flags & 0x008U) != 0) continue;

        if (source->type_index == 4) {
            /* FUN_00420991 indexes DAT_0061fa2e by source subtype. All 15
               loaded-image entries are zero, so category 4 targets other
               categories; no runtime writer has been established. */
            category_matches = candidate->type_index != 4;
        } else {
            /* FUN_00420991 accepts category 4 or a zero in the source/target
               category matrix. The 5x5 entries read from FLOAT.EXE are all
               zero, so every modeled category is initially eligible. */
            category_matches =
                candidate->type_index < GAME_FLOATER_CATEGORY_COUNT;
        }
        if (index == source_index || candidate->island_index != source->island_index ||
            !category_matches || (candidate->source_runtime_flags & 0x809U) != 0) {
            continue;
        }
        if (game_session_source_chebyshev_distance(candidate->x, candidate->y,
                                      target_x, target_y) < max_distance) return (int)index;
    }
    return -1;
}

static int32_t action9_round_source_float(double value)
{
    int32_t whole = (int32_t)value;
    double fraction = value - whole;
    if (fraction > 0.5 || (fraction == 0.5 && (whole & 1) != 0)) ++whole;
    else if (fraction < -0.5 || (fraction == -0.5 && (whole & 1) != 0)) --whole;
    return whole;
}

static int action9_find_enemy_site(GameSession *session,
                                   const GameFloaterStart *floater,
                                   uint16_t target_x, uint16_t target_y)
{
    uint16_t candidate_indices[10];
    int32_t candidate_distances[10];
    unsigned int candidate_count = 0;
    int32_t distance_sum = 0;
    double inverse_weight_sum = 0.0;
    int32_t roll;
    unsigned int island_index = floater->island_index;
    GameRuntimeIsland *island;
    unsigned int location_index;

    if (island_index >= session->island_count) return -1;
    island = &session->islands[island_index];
    for (location_index = 0; location_index < island->location_count; ++location_index) {
        const GameRuntimeLocation *location = &island->locations[location_index];
        int32_t distance;
        unsigned int largest_index;
        unsigned int i;

        if (location->source_value_14 != 4 ||
            location->record_value_10 >= 0x16 ||
            (location->source_flags & 0x90U) != 0) continue;
        distance = game_session_source_chebyshev_distance(location->x, location->y,
                                             target_x, target_y);
        /* FUN_00420a55's inverse-distance weighting divides by distance. */
        if (distance == 0 || distance >= 90) continue;
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

    for (location_index = 0; location_index < candidate_count; ++location_index) {
        distance_sum += candidate_distances[location_index];
    }
    for (location_index = 0; location_index < candidate_count; ++location_index) {
        inverse_weight_sum += (double)distance_sum /
                              (double)candidate_distances[location_index];
    }
    roll = tone_rng_bounded(&session->random_state, 1000);
    {
        int32_t cumulative = 0;
        for (location_index = 0; location_index < candidate_count; ++location_index) {
            double raw_weight = (double)distance_sum /
                                (double)candidate_distances[location_index];
            /* FUN_0041e28e converts each positive bucket with __ftol; ties
               follow the source's round-to-nearest-even FP mode. */
            cumulative += action9_round_source_float(
                (1000.0 / inverse_weight_sum) * raw_weight);
            if (roll < cumulative) return (int)candidate_indices[location_index];
        }
    }
    return -1;
}

static int action9_find_category4_site(GameSession *session,
                                       const GameFloaterStart *floater,
                                       int32_t max_distance)
{
    uint16_t candidate_indices[10];
    int32_t candidate_distances[10];
    unsigned int candidate_count = 0;
    int32_t distance_sum = 0;
    double inverse_weight_sum = 0.0;
    int32_t roll;
    GameRuntimeIsland *island;
    unsigned int index;

    if (floater->island_index >= session->island_count) return -1;
    island = &session->islands[floater->island_index];
    for (index = 0; index < island->location_count; ++index) {
        const GameRuntimeLocation *location = &island->locations[index];
        int32_t distance;
        int32_t base_item_id = game_session_base_item_id(location);
        unsigned int largest_index;
        unsigned int candidate;

        if (location->renderer_class != 0 || location->source_value_14 == 4 ||
            base_item_id < 0x25 || base_item_id > 0x34 ||
            base_item_id == 0x2a) continue;
        distance = game_session_source_chebyshev_distance(
            floater->x, floater->y, location->x, location->y);
        if (distance == 0 || distance >= max_distance) continue;
        if (candidate_count < 10U) {
            candidate_indices[candidate_count] = (uint16_t)index;
            candidate_distances[candidate_count] = distance;
            ++candidate_count;
            continue;
        }
        largest_index = 0;
        for (candidate = 1; candidate < candidate_count; ++candidate) {
            if (candidate_distances[candidate] >
                candidate_distances[largest_index]) largest_index = candidate;
        }
        if (distance < candidate_distances[largest_index]) {
            candidate_indices[largest_index] = (uint16_t)index;
            candidate_distances[largest_index] = distance;
        }
    }
    if (candidate_count == 0) return -1;

    for (index = 0; index < candidate_count; ++index)
        distance_sum += candidate_distances[index];
    for (index = 0; index < candidate_count; ++index)
        inverse_weight_sum += (double)distance_sum /
                              (double)candidate_distances[index];
    roll = tone_rng_bounded(&session->random_state, 1000);
    {
        int32_t cumulative = 0;
        for (index = 0; index < candidate_count; ++index) {
            double weight = (double)distance_sum /
                            (double)candidate_distances[index];
            cumulative += action9_round_source_float(
                (1000.0 / inverse_weight_sum) * weight);
            if (roll < cumulative) return (int)candidate_indices[index];
        }
    }
    return -1;
}

static int action9_find_category4_subtype9_site(
    GameSession *session, const GameFloaterStart *floater, int32_t site_class)
{
    uint16_t candidate_indices[10];
    int32_t candidate_distances[10];
    unsigned int candidate_count = 0;
    int32_t distance_sum = 0;
    double inverse_weight_sum = 0.0;
    int32_t roll;
    GameRuntimeIsland *island;
    unsigned int index;

    if (floater->island_index >= session->island_count) return -1;
    island = &session->islands[floater->island_index];
    for (index = 0; index < island->location_count; ++index) {
        const GameRuntimeLocation *location = &island->locations[index];
        int32_t distance;
        unsigned int largest_index;
        unsigned int candidate;

        if (location->renderer_class != site_class ||
            (location->source_value_14 != -1 &&
             !(location->record_value_10 == 1 &&
               location->record_value_24 == 1))) continue;
        distance = game_session_source_chebyshev_distance(
            floater->x, floater->y, location->x, location->y);
        if (distance == 0) continue;
        if (candidate_count < 10U) {
            candidate_indices[candidate_count] = (uint16_t)index;
            candidate_distances[candidate_count] = distance;
            ++candidate_count;
            continue;
        }
        largest_index = 0;
        for (candidate = 1; candidate < candidate_count; ++candidate) {
            if (candidate_distances[candidate] >
                candidate_distances[largest_index]) largest_index = candidate;
        }
        if (distance < candidate_distances[largest_index]) {
            candidate_indices[largest_index] = (uint16_t)index;
            candidate_distances[largest_index] = distance;
        }
    }
    if (candidate_count == 0) return -1;

    for (index = 0; index < candidate_count; ++index)
        distance_sum += candidate_distances[index];
    for (index = 0; index < candidate_count; ++index)
        inverse_weight_sum += (double)distance_sum /
                              (double)candidate_distances[index];
    roll = tone_rng_bounded(&session->random_state, 1000);
    {
        int32_t cumulative = 0;
        for (index = 0; index < candidate_count; ++index) {
            double weight = (double)distance_sum /
                            (double)candidate_distances[index];
            cumulative += action9_round_source_float(
                (1000.0 / inverse_weight_sum) * weight);
            if (roll < cumulative) return (int)candidate_indices[index];
        }
    }
    return -1;
}

int game_session_assign_category4_subtype9_order(
    GameSession *session, unsigned int floater_index, uint32_t source_tick)
{
    GameFloaterStart *floater;
    int target_class1;
    int target_class0;

    if (session == NULL || floater_index >= session->floater_count) return 0;
    floater = &session->floaters[floater_index];
    if (!game_session_floater_is_active(floater) || floater->type_index != 4U ||
        floater->source_subtype != 9U ||
        (floater->source_runtime_flags & 0x008U) != 0 ||
        (floater->active_order_action != 0 &&
         floater->active_order_action != 0x0e) ||
        floater->movement_state != 0 || floater->has_move_order ||
        floater->island_index >= session->island_count) return 0;

    /* FUN_0042219e queries site class 1 before class 0. Its class-1 preference
       globals are zero in FLOAT.EXE's loaded image and have no direct writers. */
    target_class1 = action9_find_category4_subtype9_site(session, floater, 1);
    target_class0 = action9_find_category4_subtype9_site(session, floater, 0);
    (void)target_class1;
    if (target_class0 >= 0) {
        GameRuntimeLocation *target = &session->islands[
            floater->island_index].locations[(unsigned int)target_class0];
        floater->active_order_action = 1;
        floater->order_target_location = (int16_t)target_class0;
        floater->order_target_floater = -1;
        floater->order_target_island = floater->island_index;
        floater->source_order_parameter_32 = (uint16_t)target_class0;
        floater->order_progress = 1;
        floater->movement_state = 1;
        floater->stop_radius = 0;
        floater->destination_x = target->x;
        floater->destination_y = target->y;
        floater->has_move_order = 1;
        floater->has_wander_order = 0;
        floater->wander_timer = 0;
        return 1;
    }

    floater->active_order_action = 0;
    floater->order_target_location = -1;
    floater->order_target_floater = -1;
    if ((source_tick & 0x7fU) == 0 && floater->current_hit_points != 0) {
        --floater->current_hit_points;
        if (floater->current_hit_points == 0) {
            floater->source_runtime_flags |= 0x008U;
            floater->source_death_timer = 0;
        }
    }
    return 0;
}

int game_session_assign_category4_autonomous_order(
    GameSession *session, unsigned int floater_index)
{
    GameFloaterStart *floater;
    int32_t search_distance;
    int target_floater;
    int target_location;

    if (session == NULL || floater_index >= session->floater_count) return 0;
    floater = &session->floaters[floater_index];
    if (!game_session_floater_is_active(floater) ||
        (floater->source_runtime_flags & (0x008U | 0x010U)) != 0 ||
        floater->type_index != 4U || floater->source_subtype == 9U ||
        (floater->active_order_action != 0 &&
         floater->active_order_action != 0x0e) ||
        floater->movement_state != 0 || floater->has_move_order ||
        floater->island_index >= session->island_count) return 0;

    search_distance = (floater->source_runtime_flags & 0x080U) != 0
        ? 3000 : 0x96;
    target_floater = action9_find_floater(
        session, floater_index, floater->x, floater->y, search_distance);
    target_location = action9_find_category4_site(
        session, floater, search_distance);
    if (target_location >= 0 && target_floater >= 0 &&
        tone_rng_bounded(&session->random_state, 3U) == 0) {
        target_location = -1;
    }

    if (target_location >= 0) {
        const GameRuntimeLocation *target = &session->islands[
            floater->island_index].locations[(unsigned int)target_location];
        floater->active_order_action = 7;
        floater->order_target_location = (int16_t)target_location;
        floater->order_target_floater = -1;
        floater->movement_state = 0x10;
        floater->stop_radius = game_session_floater_approach_radius(floater);
        game_session_set_approach_point(floater, target->x, target->y);
    } else if (target_floater >= 0) {
        const GameFloaterStart *target = &session->floaters[target_floater];
        floater->active_order_action = 6;
        floater->order_target_floater = (int16_t)target_floater;
        floater->order_target_location = -1;
        floater->movement_state = 0x0f;
        floater->stop_radius = game_session_floater_approach_radius(floater);
        floater->source_runtime_flags |= 0x004U;
        game_session_set_approach_point(floater, target->x, target->y);
    } else {
        return 0;
    }
    floater->order_target_island = floater->island_index;
    floater->order_timer = 0;
    floater->order_progress = 1;
    floater->has_move_order = 1;
    floater->has_wander_order = 0;
    floater->wander_timer = 0;
    return 1;
}

void game_session_advance_category4_autonomous_order(
    GameSession *session, unsigned int floater_index)
{
    GameFloaterStart *floater;

    if (session == NULL || floater_index >= session->floater_count) return;
    floater = &session->floaters[floater_index];
    if (!game_session_floater_is_active(floater) ||
        (floater->source_runtime_flags & 0x008U) != 0 ||
        (floater->active_order_action != 6 &&
         floater->active_order_action != 7)) return;

    if (floater->order_progress == 1 && floater->movement_state == 0 &&
        !floater->has_move_order) {
        if (floater->active_order_action == 6 &&
            (floater->order_target_floater < 0 ||
             (unsigned int)floater->order_target_floater >=
                 session->floater_count ||
             !game_session_floater_is_active(&session->floaters[
                 (unsigned int)floater->order_target_floater]) ||
             (session->floaters[(unsigned int)floater->order_target_floater]
                  .source_runtime_flags & 0x008U) != 0)) {
            floater->order_progress = 2;
        } else if (floater->active_order_action == 7 &&
                   (floater->island_index >= session->island_count ||
                    floater->order_target_location < 0 ||
                    (uint16_t)floater->order_target_location >=
                        session->islands[floater->island_index].location_count)) {
            floater->order_progress = 2;
        } else {
            floater->movement_state = floater->active_order_action;
            floater->attack_timer = 0;
            floater->order_progress = 2;
        }
        return;
    }
    if (floater->order_progress == 2 && floater->movement_state == 0 &&
        !floater->has_move_order) {
        floater->active_order_action = 0;
        floater->order_target_floater = -1;
        floater->order_target_location = -1;
        floater->order_progress = 0;
        floater->source_runtime_flags &= ~0x004U;
        floater->has_wander_order = 1;
        floater->wander_timer = 0;
    }
}

void game_session_set_approach_point(GameFloaterStart *floater,
                                       int32_t target_x, int32_t target_y)
{
    int32_t approach_x = target_x;
    if (floater->x < target_x) {
        approach_x -= 43;
        floater->facing_left = 0;
    } else if (floater->x > target_x) {
        approach_x += 43;
        floater->facing_left = 1;
    } else {
        approach_x -= 43;
    }
    if (approach_x < 0) approach_x = 0;
    if (approach_x > 0x9ff) approach_x = 0x9ff;
    if (target_y < 0x28) target_y = 0x28;
    if (target_y > 0x122) target_y = 0x122;
    floater->destination_x = (uint16_t)approach_x;
    floater->destination_y = (uint16_t)target_y;
}

uint16_t game_session_floater_approach_radius(
    const GameFloaterStart *floater)
{
    if (floater->type_index == 4U ||
        (floater->source_subtype != 0 && floater->charge_current > 0)) {
        if (floater->attack_range > 0) return (uint16_t)floater->attack_range;
    }
    return 10;
}

void game_session_advance_action9(GameSession *session,
                                         unsigned int floater_index)
{
    GameFloaterStart *floater = &session->floaters[floater_index];
    uint16_t target_x;
    uint16_t target_y;
    int target_index;

    if (!game_session_floater_is_active(floater) ||
        (floater->source_runtime_flags & 0x008U) != 0 ||
        floater->active_order_action == 4 ||
        floater->source_order_state_2c != 9 ||
        (floater->movement_state != 0 && floater->movement_state != 9 &&
         floater->movement_state != 6 && floater->movement_state != 7 &&
         floater->movement_state != 0x0f &&
         floater->movement_state != 0x10)) return;

    if (floater->order_progress == 0) {
        floater->destination_x =
            (uint16_t)(floater->source_order_coordinate_30 >> 8) * 10U;
        floater->destination_y =
            (uint16_t)(floater->source_order_coordinate_30 & 0xffU) * 10U;
        floater->movement_state = 9;
        floater->stop_radius = 0;
        floater->source_runtime_flags &= ~0x004U;
        floater->has_wander_order = 0;
        floater->wander_timer = 0;
        floater->has_move_order = 1;
        floater->order_progress = 1;
        return;
    }
    if (floater->order_progress == 2) {
        floater->movement_state = 6;
        floater->order_progress = 1;
        floater->attack_timer = 0;
        return;
    }
    if (floater->order_progress == 3) {
        floater->movement_state = 7;
        floater->order_progress = 1;
        floater->attack_timer = 0;
        return;
    }
    if (floater->order_progress != 1) return;
    if (floater->movement_state == 0x0f || floater->movement_state == 0x10)
        return;

    target_x = (uint16_t)(floater->source_order_coordinate_30 >> 8) * 10U;
    target_y = (uint16_t)(floater->source_order_coordinate_30 & 0xffU) * 10U;
    target_index = action9_find_floater(session, floater_index, target_x, target_y,
                                        250);
    if (target_index >= 0) {
        GameFloaterStart *target = &session->floaters[target_index];
        floater->order_target_floater = (int16_t)target_index;
        floater->order_target_location = -1;
        floater->movement_state = 0x0f;
        floater->stop_radius = game_session_floater_approach_radius(floater);
        floater->source_runtime_flags |= 0x004U;
        game_session_set_approach_point(floater, target->x, target->y);
        floater->has_move_order = 1;
        floater->order_progress = 2;
        return;
    }

    target_index = action9_find_enemy_site(session, floater, target_x, target_y);
    if (target_index >= 0) {
        const GameRuntimeLocation *target =
            &session->islands[floater->island_index].locations[target_index];
        floater->order_target_location = (int16_t)target_index;
        floater->order_target_floater = -1;
        floater->movement_state = 0x10;
        floater->stop_radius = game_session_floater_approach_radius(floater);
        game_session_set_approach_point(floater, target->x, target->y);
        floater->has_move_order = 1;
        floater->order_progress = 3;
        return;
    }

    /* Source progress returns to zero when neither follow-up target exists,
       so the packed coordinate can be approached and checked again later. */
    floater->order_progress = 0;
}

void game_session_advance_merge_order(GameSession *session,
                                      unsigned int floater_index)
{
    GameFloaterStart *floater;
    GameFloaterStart *target;

    if (session == NULL || floater_index >= session->floater_count) return;
    floater = &session->floaters[floater_index];
    if (floater->active_order_action != 0x14 || floater->has_move_order ||
        floater->movement_state != 0) return;

    if (floater->order_progress == 0) {
        if (floater->order_target_floater < 0 ||
            (unsigned int)floater->order_target_floater >= session->floater_count) {
            floater->active_order_action = 0;
            return;
        }
        target = &session->floaters[
            (unsigned int)floater->order_target_floater];
        if (!game_session_floater_is_active(target) ||
            (target->source_runtime_flags & 0x008U) != 0 ||
            target == floater || target->island_index != floater->island_index) {
            floater->active_order_action = 0;
            return;
        }
        floater->movement_state = 0x0f;
        floater->stop_radius = 0;
        floater->has_wander_order = 0;
        floater->wander_timer = 0;
        game_session_set_approach_point(floater, target->x, target->y);
        floater->has_move_order = 1;
        floater->order_progress = 1;
    } else if (floater->order_progress == 1) {
        floater->order_progress = 2;
        if (floater->source_subtype == 8) {
            /* FA_MergeWith keeps owning the random state-0x0e roam. */
            floater->movement_state = 0;
            floater->has_wander_order = 1;
            floater->wander_timer = 0;
        } else {
            /* The source's other-subtype terminal state is 0x15. */
            floater->movement_state = 0x15;
            floater->order_timer = 0;
            floater->has_wander_order = 0;
            floater->wander_timer = 0;
        }
    }
}

static void cancel_defend_order(GameFloaterStart *floater)
{
    /* FUN_00421ec1(-1) clears the linked action/state and source flags; clear
       the port's resolved destination too so a dead target cannot be chased. */
    floater->active_order_action = 0;
    floater->movement_state = 0;
    floater->order_target_floater = -1;
    floater->defend_target_floater = -1;
    floater->order_target_location = -1;
    floater->order_target_island = UINT8_MAX;
    floater->order_progress = 0;
    floater->source_order_state_2c = 0;
    floater->source_order_coordinate_30 = 0;
    floater->source_order_pending = 0;
    floater->source_runtime_flags &= ~0x065U;
    floater->has_move_order = 0;
    floater->has_wander_order = 1;
    floater->wander_timer = 0;
}

void game_session_advance_defend_order(GameSession *session,
                                       unsigned int floater_index)
{
    GameFloaterStart *floater;
    GameFloaterStart *target;
    int candidate_index;

    if (session == NULL || floater_index >= session->floater_count) return;
    floater = &session->floaters[floater_index];
    if (floater->active_order_action != 8) return;

    if (floater->order_progress == 0) {
        if (floater->defend_target_floater < 0 ||
            (unsigned int)floater->defend_target_floater >= session->floater_count) {
            cancel_defend_order(floater);
            return;
        }
        target = &session->floaters[
            (unsigned int)floater->defend_target_floater];
        if (target == floater || target->island_index != floater->island_index) {
            cancel_defend_order(floater);
            return;
        }
        floater->order_target_floater = floater->defend_target_floater;
        floater->movement_state = 8;
        floater->stop_radius = 0;
        floater->source_runtime_flags &= ~0x004U;
        floater->has_move_order = 0;
        floater->order_progress = 1;
        return;
    }

    if (floater->order_progress == 1) {
        if (floater->defend_target_floater < 0 ||
            (unsigned int)floater->defend_target_floater >= session->floater_count) {
            cancel_defend_order(floater);
            return;
        }
        target = &session->floaters[
            (unsigned int)floater->defend_target_floater];
        if (!game_session_floater_is_active(target) ||
            (target->source_runtime_flags & 0x008U) != 0 ||
            target->island_index != floater->island_index) {
            cancel_defend_order(floater);
            return;
        }
        candidate_index = action9_find_floater(
            session, floater_index, target->x, target->y, 250);
        if (candidate_index < 0) {
            floater->order_progress = 0;
            return;
        }
        target = &session->floaters[candidate_index];
        floater->order_target_floater = (int16_t)candidate_index;
        floater->movement_state = 0x0f;
        floater->stop_radius = game_session_floater_approach_radius(floater);
        floater->source_runtime_flags |= 0x004U;
        game_session_set_approach_point(floater, target->x, target->y);
        floater->has_move_order = 1;
        floater->order_progress = 2;
        return;
    }

    if (floater->order_progress == 2) {
        floater->movement_state = 6;
        floater->attack_timer = 0;
        floater->order_progress = 1;
    }
}

