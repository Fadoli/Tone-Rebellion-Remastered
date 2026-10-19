#include "game_session.h"
#include "floater_motion.h"

#include <string.h>

/* Floater movement, order execution and selection queries. */
static int32_t source_chebyshev_distance(int32_t x1, int32_t y1,
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
            /* Category 4 is always accepted; the other class-pair cases
               depend on unmodeled DAT_00619290 values. */
            category_matches = candidate->type_index == 4;
        }
        if (index == source_index || candidate->island_index != source->island_index ||
            !category_matches || (candidate->source_runtime_flags & 0x809U) != 0) {
            continue;
        }
        if (source_chebyshev_distance(candidate->x, candidate->y,
                                      target_x, target_y) < 250) return (int)index;
    }
    return -1;
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
        distance = source_chebyshev_distance(location->x, location->y,
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
            /* FUN_0041e28e converts each positive bucket with __ftol, which
               rounds to the nearest integer under the default FP mode. */
            cumulative += (int32_t)((1000.0 / inverse_weight_sum) * raw_weight + 0.5);
            if (roll < cumulative) return (int)candidate_indices[location_index];
        }
    }
    return -1;
}

static void floater_set_approach_point(GameFloaterStart *floater,
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

static void game_session_advance_action9(GameSession *session,
                                         unsigned int floater_index)
{
    GameFloaterStart *floater = &session->floaters[floater_index];
    uint16_t target_x;
    uint16_t target_y;
    int target_index;

    if (floater->source_order_state_2c != 9 || floater->movement_state != 0 ||
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
        return;
    }
    if (floater->order_progress == 3) {
        floater->movement_state = 7;
        floater->order_progress = 1;
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
        floater_set_approach_point(floater, target->x, target->y);
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
        floater_set_approach_point(floater, target->x, target->y);
        floater->has_move_order = 1;
        floater->order_progress = 3;
        return;
    }

    /* Source progress returns to zero when neither follow-up target exists,
       so the packed coordinate can be approached and checked again later. */
    floater->order_progress = 0;
}

void game_session_tick_floater_moves(GameSession *session, uint32_t source_tick)
{
    unsigned int i;

    if (session == NULL) return;
    for (i = 0; i < session->floater_count; ++i) {
        GameFloaterStart *floater = &session->floaters[i];
        FloaterPosition position;
        FloaterPosition destination;
        FloaterMotionSpeedContext speed_context;
        uint16_t effective_speed;
        int arrived;
        int32_t dx;
        int32_t dy;
        int32_t distance;

        /* FUN_0041e569 polls FUN_0042219e while idle and once per ten ticks
           while moving. The bridge leaves the linked order pending during
           FA_Cast (0x13), then transfers it to the tick record at a later poll. */
        if (floater->source_order_pending &&
            floater->active_order_action != 0x13 &&
            (floater->movement_state == 0 || (source_tick + i) % 10U == 0)) {
            floater->source_order_pending = 0;
            if (floater->source_order_state_2c == 9 &&
                floater->source_order_island_28 == floater->island_index &&
                floater->island_index < session->island_count) {
                FloaterPosition waypoint;
                GameRuntimeIsland *island =
                    &session->islands[floater->island_index];
                int32_t raw_min_x = 0;
                int32_t raw_max_x = 0x9ff;
                int32_t anchor_x =
                    (int32_t)(floater->source_order_coordinate_30 >> 8) * 10;
                int32_t anchor_y =
                    (int32_t)(floater->source_order_coordinate_30 & 0xffU) * 10;

                if (floater->type_index != 4U &&
                    floater->type_index < GAME_FLOATER_CATEGORY_COUNT) {
                    raw_min_x = island->floater_min_x[floater->type_index];
                    raw_max_x = island->floater_max_x[floater->type_index];
                }

                floater->active_order_action = 9;
                floater->movement_state = 9;
                floater->stop_radius = 0;
                floater->has_wander_order = 0;
                floater->wander_timer = 0;
                floater->has_move_order = 1;
                floater->order_progress = 1;
                if (floater_motion_wander_destination(
                        &session->random_state, anchor_x, anchor_y,
                        raw_min_x, raw_max_x, &waypoint)) {
                    floater->destination_x = (uint16_t)waypoint.x;
                    floater->destination_y = (uint16_t)waypoint.y;
                    if (waypoint.x < floater->x) floater->facing_left = 1;
                    else if (waypoint.x > floater->x) floater->facing_left = 0;
                } else {
                    floater->source_order_state_2c = 0;
                    floater->active_order_action = 0;
                    floater->movement_state = 0;
                    floater->has_move_order = 0;
                    floater->order_progress = 0;
                }
            }
        }

        game_session_advance_action9(session, i);

        if (floater->has_move_order && floater->has_wander_order) {
            /* A newly assigned route replaces the idle fallback action. */
            floater->has_wander_order = 0;
            floater->wander_timer = 0;
            if (floater->movement_state == 0x0e) floater->movement_state = 0;
        }
        if (floater->has_wander_order && !floater->has_move_order) {
            if (floater->movement_state != 0x0e) {
                FloaterPosition wander_destination;
                GameRuntimeIsland *island;
                int32_t raw_min_x = 0;
                int32_t raw_max_x = 0x9ff;

                if (floater->island_index >= session->island_count ||
                    floater->type_index >= GAME_FLOATER_CATEGORY_COUNT) {
                    floater->has_wander_order = 0;
                    continue;
                }
                island = &session->islands[floater->island_index];
                /* FUN_00423068 skips the per-island/category table for
                   category 4 and keeps its global 0..0x9ff bounds. */
                if (floater->type_index != 4U) {
                    raw_min_x = island->floater_min_x[floater->type_index];
                    raw_max_x = island->floater_max_x[floater->type_index];
                }
                if (!floater_motion_wander_destination(
                        &session->random_state, floater->x, floater->y,
                        raw_min_x, raw_max_x, &wander_destination)) {
                    /* The source cancels FA_Wander when destination resolution
                       rejects the generated X coordinate. */
                    floater->has_wander_order = 0;
                    floater->movement_state = 0;
                    floater->wander_timer = 0;
                    continue;
                }
                floater->destination_x = (uint16_t)wander_destination.x;
                floater->destination_y = (uint16_t)wander_destination.y;
                if (wander_destination.x < floater->x) floater->facing_left = 1;
                else floater->facing_left = 0;
                floater->movement_state = 0x0e;
                floater->wander_timer = 60;
            }

            position.x = floater->x;
            position.y = floater->y;
            destination.x = floater->destination_x;
            destination.y = floater->destination_y;
            speed_context.unit_speed = floater->movement_speed;
            speed_context.state = 0x0e;
            speed_context.subtype = floater->source_subtype;
            speed_context.category_speed_modifier =
                floater->category_speed_modifier;
            speed_context.near_target_override = 0;
            speed_context.site_speed_bonus = floater->site_speed_bonus;
            effective_speed = floater_motion_effective_speed(&speed_context);
            arrived = floater_motion_step(&position, destination, effective_speed,
                                          source_tick);
            floater->x = (uint16_t)position.x;
            floater->y = (uint16_t)position.y;
            if (arrived && floater->wander_timer > 0) {
                --floater->wander_timer;
                if (floater->wander_timer == 0) {
                    /* Generic state completion clears runtime state; the
                       retained wander order selects another point next tick. */
                    floater->movement_state = 0;
                }
            }
            continue;
        }
        if (!floater->has_move_order) {
            continue;
        }
        dx = (int32_t)floater->destination_x - floater->x;
        dy = (int32_t)floater->destination_y - floater->y;
        /* FUN_00423068 updates facing from the destination independently of
           whether the movement state is already inside its stopping radius. */
        if (dx < 0) floater->facing_left = 1;
        else if (dx > 0) floater->facing_left = 0;
        distance = dx < 0 ? -dx : dx;
        if ((dy < 0 ? -dy : dy) > distance) distance = dy < 0 ? -dy : dy;
        if (distance <= floater->stop_radius) {
            floater->has_move_order = 0;
            if (floater->movement_state == 9 || floater->movement_state == 0x0f ||
                floater->movement_state == 0x10) floater->movement_state = 0;
            continue;
        }

        /* State 0x0f/0x10 tests its previously resolved destination against
           the arrival radius before refreshing the live target coordinates. */
        if (floater->movement_state == 0x0f &&
            floater->order_target_floater >= 0 &&
            (unsigned int)floater->order_target_floater < session->floater_count) {
            const GameFloaterStart *target =
                &session->floaters[(unsigned int)floater->order_target_floater];
            floater_set_approach_point(floater, target->x, target->y);
        } else if (floater->movement_state == 0x10 &&
                   floater->island_index < session->island_count &&
                   floater->order_target_location >= 0 &&
                   (uint16_t)floater->order_target_location <
                       session->islands[floater->island_index].location_count) {
            const GameRuntimeLocation *target =
                &session->islands[floater->island_index]
                     .locations[(uint16_t)floater->order_target_location];
            floater_set_approach_point(floater, target->x, target->y);
        }

        position.x = floater->x;
        position.y = floater->y;
        destination.x = floater->destination_x;
        destination.y = floater->destination_y;
        speed_context.unit_speed = floater->movement_speed;
        speed_context.state = floater->movement_state;
        speed_context.subtype = floater->source_subtype;
        speed_context.category_speed_modifier =
            floater->category_speed_modifier;
        if (floater->movement_state == 9) {
            int32_t anchor_x =
                (int32_t)(floater->source_order_coordinate_30 >> 8) * 10;
            int32_t anchor_y =
                (int32_t)(floater->source_order_coordinate_30 & 0xffU) * 10;
            speed_context.near_target_override =
                source_chebyshev_distance(floater->x, floater->y,
                                          anchor_x, anchor_y) < 100;
        } else {
            speed_context.near_target_override =
                floater->near_target_speed_override;
        }
        speed_context.site_speed_bonus = floater->site_speed_bonus;
        effective_speed = floater_motion_effective_speed(&speed_context);
        (void)floater_motion_step(&position, destination, effective_speed,
                                  source_tick);
        floater->x = (uint16_t)position.x;
        floater->y = (uint16_t)position.y;
        dx = (int32_t)floater->destination_x - floater->x;
        dy = (int32_t)floater->destination_y - floater->y;
        distance = dx < 0 ? -dx : dx;
        if ((dy < 0 ? -dy : dy) > distance) {
            distance = dy < 0 ? -dy : dy;
        }
        if (distance <= floater->stop_radius &&
            floater->movement_state != 0x0f &&
            floater->movement_state != 0x10) {
            floater->has_move_order = 0;
            if (floater->movement_state == 9 || floater->movement_state == 0x0f ||
                floater->movement_state == 0x10) floater->movement_state = 0;
        }

    }
}

int game_session_order_floater_to_coordinate(GameSession *session,
                                             uint8_t player_slot,
                                             uint8_t island_index,
                                             unsigned int floater_index,
                                             uint16_t x,
                                             uint16_t y)
{
    GameFloaterStart *floater;
    uint8_t packed_x;
    uint8_t packed_y;

    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT ||
        island_index >= session->island_count ||
        floater_index >= session->floater_count) {
        return 0;
    }

    floater = &session->floaters[floater_index];
    if (floater->owner_slot != player_slot ||
        floater->island_index != island_index ||
        floater->source_subtype == 0) {
        return 0;
    }

    /* FUN_0041e3eb computes (coordinate + 5) / 10, then keeps one byte per
       axis. FUN_0041e427 expands those bytes back to pixels by multiplying
       each by 10. Coordinates on the island are nonnegative. */
    packed_x = (uint8_t)(((uint32_t)x + 5U) / 10U);
    packed_y = (uint8_t)(((uint32_t)y + 5U) / 10U);
    floater->source_order_state_2c = 9;
    floater->source_order_island_28 = island_index;
    floater->source_order_coordinate_30 =
        (uint16_t)(((uint16_t)packed_x << 8) | packed_y);
    floater->source_order_parameter_32 = 0;
    floater->source_order_pending = 1;
    return 1;
}

int game_session_floater_at(const GameSession *session,
                            uint8_t island_index,
                            uint16_t x,
                            uint16_t y)
{
    unsigned int i;

    if (session == NULL || island_index >= session->island_count) return -1;
    for (i = 0; i < session->floater_count; ++i) {
        const GameFloaterStart *floater = &session->floaters[i];
        int32_t dx;
        int32_t dy;

        if (floater->island_index != island_index) continue;
        dx = (int32_t)x - floater->x;
        dy = (int32_t)y - floater->y;
        if (dx < 0) dx = -dx;
        if (dy < 0) dy = -dy;
        if ((dx > dy ? dx : dy) < 20) return (int)i;
    }
    return -1;
}

unsigned int game_session_count_player_floaters(const GameSession *session,
                                                uint8_t player_slot)
{
    unsigned int count = 0;
    unsigned int i;
    unsigned int limit;

    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT) return 0;
    limit = session->floater_count;
    if (limit > GAME_SESSION_MAX_FLOATERS) limit = GAME_SESSION_MAX_FLOATERS;
    for (i = 0; i < limit; ++i) {
        if (session->floaters[i].owner_slot == player_slot) ++count;
    }
    return count;
}

int game_session_floater_charge_values(const GameFloaterStart *floater,
                                       const FloaterCatalog *catalog,
                                       int16_t *current, int16_t *maximum)
{
    const FloaterStats *stats;
    if (floater == NULL || catalog == NULL || current == NULL ||
        maximum == NULL || floater->source_link_0c == -1) return 0;
    stats = floater_catalog_find(catalog, floater->type_index,
                                 floater->source_subtype);
    if (stats == NULL) return 0;
    *current = floater->charge_current;
    *maximum = stats->max_attack_points;
    return 1;
}

int game_session_workstr_summary(const GameSession *session,
                                 uint8_t type_index,
                                 unsigned int *count,
                                 unsigned int *total,
                                 unsigned int *percentage)
{
    unsigned int subtype_zero = 0;
    unsigned int type_total = 0;
    unsigned int limit;
    unsigned int i;

    if (count != NULL) *count = 0;
    if (total != NULL) *total = 0;
    if (percentage != NULL) *percentage = 0;
    if (session == NULL || type_index >= GAME_START_PLAYER_COUNT ||
        count == NULL || total == NULL || percentage == NULL) return 0;

    limit = session->floater_count;
    if (limit > GAME_SESSION_MAX_FLOATERS) limit = GAME_SESSION_MAX_FLOATERS;
    for (i = 0; i < limit; ++i) {
        const GameFloaterStart *floater = &session->floaters[i];
        if (floater->type_index != type_index) continue;
        ++type_total;
        if (floater->source_subtype == 0) ++subtype_zero;
    }
    *count = subtype_zero;
    *total = type_total;
    if (type_total > 0) {
        /* Source performs this ratio in floating point and converts the
           nonnegative result to int; integer division has same truncation. */
        *percentage = (subtype_zero * 100U) / type_total;
    }
    return 1;
}
