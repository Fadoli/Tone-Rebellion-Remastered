#include "game_session.h"
#include "floater_motion.h"
#include "game_session_delivery.h"

#include <string.h>

/* Floater movement, order execution and selection queries. */
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
                                uint16_t target_x, uint16_t target_y)
{
    const GameFloaterStart *source = &session->floaters[source_index];
    int source_level = -1;
    unsigned int index;

    /* FUN_00420829 scans the current-island candidate list and accepts the
       first class/flag/distance match. The source table order currently
       follows floater insertion order in this model. */
    if (source->island_index < session->island_count) {
        source_level = session->islands[source->island_index].source_level;
    }
    for (index = 0; index < session->floater_count; ++index) {
        const GameFloaterStart *candidate = &session->floaters[index];
        int category_matches;

        if (source->type_index == 4) {
            /* DAT_0061fa2e selects non-category-4 candidates below 0x65 and
               category 4 at or above it. Its loaded-image default is zero. */
            category_matches = source_level < 0x65
                ? candidate->type_index != 4 : candidate->type_index == 4;
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
                                      target_x, target_y) < 250) return (int)index;
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

        if (location->renderer_class != 4 || location->owner_id != 4 ||
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

static uint16_t floater_approach_radius(const GameFloaterStart *floater)
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

    if (floater->active_order_action == 4 ||
        floater->source_order_state_2c != 9 || floater->movement_state != 0 ||
        floater->has_move_order) return;

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

    target_x = (uint16_t)(floater->source_order_coordinate_30 >> 8) * 10U;
    target_y = (uint16_t)(floater->source_order_coordinate_30 & 0xffU) * 10U;
    target_index = action9_find_floater(session, floater_index, target_x, target_y);
    if (target_index >= 0) {
        GameFloaterStart *target = &session->floaters[target_index];
        floater->order_target_floater = (int16_t)target_index;
        floater->order_target_location = -1;
        floater->movement_state = 0x0f;
        floater->stop_radius = floater_approach_radius(floater);
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
        floater->stop_radius = floater_approach_radius(floater);
        game_session_set_approach_point(floater, target->x, target->y);
        floater->has_move_order = 1;
        floater->order_progress = 3;
        return;
    }

    /* Source progress returns to zero when neither follow-up target exists,
       so the packed coordinate can be approached and checked again later. */
    floater->order_progress = 0;
}

