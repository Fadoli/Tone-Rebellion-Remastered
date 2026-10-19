#include "game_session.h"
#include "floater_motion.h"
#include "game_session_delivery.h"
#include "game_session_action9.h"
#include "game_session_movement_internal.h"
#include "tone_rng.h"

#include <string.h>

static void game_session_apply_charge_debit(GameFloaterStart *floater,
                                            GameRuntimeLocation *source)
{
    source->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] -= 10U;
    source->charge_source_value_30 = 0;
    floater->source_runtime_flags |= 0x21U;
    if (floater->source_subtype == 0 &&
        (floater->source_runtime_flags & 0x100U) != 0) {
        floater->source_runtime_flags &= ~0x100U;
    }
}

static int game_session_tick_floater_charge(GameSession *session,
                                            unsigned int floater_index)
{
    GameFloaterStart *floater = &session->floaters[floater_index];
    int succeeded;

    if (floater->movement_state != 11 && floater->movement_state != 12) return 0;

    /* FUN_0041e569 cases 10/11 retry only when the +0x34 short wraps to zero;
       otherwise they advance it once per floater update. */
    if (floater->order_timer != 0) {
        ++floater->order_timer;
        return 1;
    }

    if (floater->island_index >= session->island_count ||
        floater->source_order_parameter_32 >=
            session->islands[floater->island_index].location_count) {
        succeeded = 0;
    } else if (floater->movement_state == 11) {
        GameRuntimeLocation *target = &session->islands[floater->island_index]
            .locations[floater->source_order_parameter_32];
        if (floater->x != target->x || floater->y != target->y) {
            floater->destination_x = target->x;
            floater->destination_y = target->y;
            floater->stop_radius = 0;
            floater->has_move_order = 1;
            return 0;
        }
        floater->has_move_order = 0;
        succeeded = game_session_link_floater_charge(
            session, floater_index, floater->source_order_parameter_32);
    } else {
        succeeded = floater->charge_source_island == floater->island_index &&
            floater->charge_source_location == floater->source_order_parameter_32 &&
            game_session_refill_floater_charge(session, floater_index);
    }

    if (succeeded) {
        floater->order_timer = 1;
    } else {
        floater->movement_state = 0;
        floater->order_timer = 0;
        floater->has_move_order = 0;
    }
    return 1;
}

int game_session_link_floater_charge(GameSession *session,
                                     unsigned int floater_index,
                                     uint16_t source_location_index)
{
    GameFloaterStart *floater;
    GameRuntimeIsland *island;
    GameRuntimeLocation *source;
    unsigned int slot;

    if (session == NULL || floater_index >= session->floater_count ||
        floater_index >= GAME_SESSION_MAX_FLOATERS) return 0;
    floater = &session->floaters[floater_index];
    if (floater->island_index >= session->island_count ||
        floater->source_link_0c != -1) return 0;
    island = &session->islands[floater->island_index];
    if (source_location_index >= island->location_count) return 0;
    source = &island->locations[source_location_index];
    if (source->source_location_slot_18 < 0 ||
        source->owner_id != (int32_t)floater->owner_slot ||
        source->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] < 10U ||
        source->charge_floater_count >= 8U) return 0;

    for (slot = 0; slot < 8; ++slot) {
        if (source->charge_floater_slots[slot] == -1) break;
    }
    if (slot == 8) return 0;

    source->charge_floater_slots[slot] = (int16_t)floater_index;
    ++source->charge_floater_count;
    source->charge_recent_floater = (int16_t)floater_index;
    floater->source_link_0c = source->source_location_slot_18;
    floater->charge_source_island = floater->island_index;
    floater->charge_source_location = source_location_index;
    game_session_apply_charge_debit(floater, source);
    return 1;
}

int game_session_refill_floater_charge(GameSession *session,
                                       unsigned int floater_index)
{
    GameFloaterStart *floater;
    GameRuntimeIsland *island;
    GameRuntimeLocation *source;
    unsigned int slot;

    if (session == NULL || floater_index >= session->floater_count ||
        floater_index >= GAME_SESSION_MAX_FLOATERS) return 0;
    floater = &session->floaters[floater_index];
    if (floater->source_link_0c < 0 ||
        floater->charge_source_island >= session->island_count) return 0;
    if (floater->island_index != floater->charge_source_island) return 0;
    island = &session->islands[floater->charge_source_island];
    if (floater->charge_source_location >= island->location_count) return 0;
    source = &island->locations[floater->charge_source_location];
    if (source->source_location_slot_18 != floater->source_link_0c ||
        source->owner_id != (int32_t)floater->owner_slot) return 0;
    if (source->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] < 10U) return 0;

    for (slot = 0; slot < 8; ++slot) {
        if (source->charge_floater_slots[slot] == (int16_t)floater_index) break;
    }
    if (slot == 8) return 0;

    game_session_apply_charge_debit(floater, source);
    return 1;
}

int game_session_unlink_floater_charge(GameSession *session,
                                       unsigned int floater_index)
{
    GameFloaterStart *floater;
    GameRuntimeIsland *island;
    GameRuntimeLocation *source;
    unsigned int slot;

    if (session == NULL || floater_index >= session->floater_count ||
        floater_index >= GAME_SESSION_MAX_FLOATERS) return 0;
    floater = &session->floaters[floater_index];
    if (floater->source_link_0c < 0 ||
        floater->charge_source_island >= session->island_count) return 0;
    if (floater->island_index != floater->charge_source_island) return 0;
    island = &session->islands[floater->charge_source_island];
    if (floater->charge_source_location >= island->location_count) return 0;
    source = &island->locations[floater->charge_source_location];
    if (source->source_location_slot_18 != floater->source_link_0c ||
        source->owner_id != (int32_t)floater->owner_slot) return 0;

    for (slot = 0; slot < 8; ++slot) {
        if (source->charge_floater_slots[slot] == (int16_t)floater_index) break;
    }
    if (slot == 8) return 0;

    source->charge_floater_slots[slot] = -1;
    if (source->charge_floater_count != 0) --source->charge_floater_count;
    if (source->charge_recent_floater == (int16_t)floater_index)
        source->charge_recent_floater = -1;
    floater->source_link_0c = -1;
    floater->charge_source_island = UINT8_MAX;
    floater->charge_source_location = UINT16_MAX;
    return 1;
}

static int game_session_resolve_cast_destination(
    GameSession *session, GameFloaterStart *floater)
{
    static const uint8_t target_modes[23] = {
        0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01,
        0x04, 0x05, 0x06, 0x01, 0x01, 0x01, 0x00, 0x01,
        0x05, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01
    };
    int32_t target_x = floater->x;
    int32_t target_y = floater->y;
    int32_t facing_x;
    uint8_t mode;

    if (floater->cast_spell_kind >= 23U ||
        floater->island_index >= session->island_count) return 0;
    mode = target_modes[floater->cast_spell_kind];
    if ((mode & 2U) != 0) {
        if (floater->order_target_floater < 0 ||
            (unsigned int)floater->order_target_floater >= session->floater_count) {
            return 0;
        }
        target_x = session->floaters[
            (unsigned int)floater->order_target_floater].x;
        target_y = session->floaters[
            (unsigned int)floater->order_target_floater].y;
    } else if ((mode & 1U) != 0) {
        const GameRuntimeIsland *island =
            &session->islands[floater->island_index];
        if (floater->order_target_location < 0 ||
            (uint16_t)floater->order_target_location >= island->location_count) {
            return 0;
        }
        target_x = island->locations[
            (uint16_t)floater->order_target_location].x;
        target_y = island->locations[
            (uint16_t)floater->order_target_location].y;
    }
    facing_x = target_x;
    if ((mode & 4U) != 0) {
        target_x = (int32_t)floater->x - 100 +
            (int32_t)tone_rng_bounded(&session->random_state, 200);
        target_y = (int32_t)floater->y - 100 +
            (int32_t)tone_rng_bounded(&session->random_state, 200);
        if (target_x < 0x1e) target_x = 0x1e;
        if (target_x > 0x9e2) target_x = 0x9e2;
        if (target_y < 0x28) target_y = 0x28;
        if (target_y > 0x122) target_y = 0x122;
    }

    floater->facing_left = (uint8_t)(floater->x > (uint16_t)facing_x);
    if (floater->owner_slot != 4U &&
        floater->owner_slot < GAME_FLOATER_CATEGORY_COUNT) {
        const GameRuntimeIsland *island =
            &session->islands[floater->island_index];
        int32_t min_x = island->floater_min_x[floater->owner_slot];
        int32_t max_x = island->floater_max_x[floater->owner_slot];
        if ((min_x > 0 && target_x < min_x + 0x28) ||
            (max_x < 0x9ff && target_x > max_x - 0x28)) return 0;
    }

    floater->destination_x = (uint16_t)target_x;
    floater->destination_y = (uint16_t)target_y;
    return 1;
}

static void game_session_cancel_cast_order(GameFloaterStart *floater)
{
    floater->active_order_action = 0;
    floater->movement_state = 0;
    floater->order_target_floater = -1;
    floater->order_target_location = -1;
    floater->cast_spell_kind = 0;
    floater->order_progress = 0;
    floater->source_order_pending = 0;
    floater->has_move_order = 0;
    floater->source_runtime_flags &= ~0x065U;
}

void game_session_tick_floater_moves(GameSession *session, uint32_t source_tick)
{
    unsigned int i;

    if (session == NULL) return;
    game_session_assign_local_resource_tasks(session);
    game_session_tick_combat_effects(session, source_tick);
    game_session_tick_cast_effects(session, source_tick);
    for (i = 0; i < session->floater_count; ++i) {
        GameFloaterStart *floater = &session->floaters[i];
        FloaterPosition position;
        FloaterPosition destination;
        FloaterMotionSpeedContext speed_context;
        uint16_t effective_speed;
        int32_t dx;
        int32_t dy;
        int32_t distance;

        if (game_session_tick_floater_charge(session, i)) continue;

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

                if (floater->owner_slot != 4U &&
                    floater->owner_slot < GAME_FLOATER_CATEGORY_COUNT) {
                    raw_min_x = island->floater_min_x[floater->owner_slot];
                    raw_max_x = island->floater_max_x[floater->owner_slot];
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

        if (floater->active_order_action == 0x13 &&
            floater->movement_state == 0x13) {
            if ((floater->source_runtime_flags & 0x200U) != 0) {
                game_session_cancel_cast_order(floater);
            } else if (!game_session_resolve_cast_destination(session, floater)) {
                game_session_cancel_cast_order(floater);
            } else if (game_session_source_chebyshev_distance(
                           floater->x, floater->y,
                           floater->destination_x,
                           floater->destination_y) <= 30) {
                /* FUN_0042383d uses DAT_0049d230[kind] (30 for kind 0x16)
                   and starts FUN_0041660b on the tenth in-range tick. */
                if (floater->order_timer < 400U) ++floater->order_timer;
                if (floater->order_timer == 10U) {
                    (void)game_session_schedule_cast_effect_step(
                        session, i, 0x16, floater->order_target_location, 0);
                }
                if (floater->order_timer >= 400U)
                    game_session_cancel_cast_order(floater);
            }
            continue;
        }

        game_session_advance_action9(session, i);
        game_session_tick_floater_combat(session, i);
        if (game_session_tick_floater_handoff(session, floater)) continue;
        if (floater->active_order_action == 4 && !floater->has_move_order) {
            game_session_advance_local_resource_task(session, floater);
            if (!floater->has_move_order) continue;
        }

        if (game_session_tick_floater_wander(session, floater, source_tick))
            continue;
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
            if (floater->movement_state == 3 || floater->movement_state == 4) {
                game_session_advance_local_resource_task(session, floater);
                continue;
            }
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
            game_session_set_approach_point(floater, target->x, target->y);
        } else if (floater->movement_state == 0x10 &&
                   floater->island_index < session->island_count &&
                   floater->order_target_location >= 0 &&
                   (uint16_t)floater->order_target_location <
                       session->islands[floater->island_index].location_count) {
            const GameRuntimeLocation *target =
                &session->islands[floater->island_index]
                     .locations[(uint16_t)floater->order_target_location];
            game_session_set_approach_point(floater, target->x, target->y);
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
                game_session_source_chebyshev_distance(floater->x, floater->y,
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
        game_session_advance_local_resource_task(session, floater);

    }
}

#include "game_session_movement_internal.h"
#include "floater_motion.h"

int game_session_tick_floater_wander(GameSession *session,
                                    GameFloaterStart *floater,
                                    uint32_t source_tick)
{
    FloaterPosition position;
    FloaterPosition destination;
    FloaterMotionSpeedContext speed_context;
    uint16_t effective_speed;
    int arrived;

    if (floater->has_move_order && floater->has_wander_order) {
        /* A newly assigned route replaces the idle fallback action. */
        floater->has_wander_order = 0;
        floater->wander_timer = 0;
        if (floater->movement_state == 0x0e) floater->movement_state = 0;
    }
    if (!floater->has_wander_order || floater->has_move_order) return 0;
    if (floater->movement_state != 0x0e) {
        FloaterPosition wander_destination;
        GameRuntimeIsland *island;
        int32_t raw_min_x = 0;
        int32_t raw_max_x = 0x9ff;

        if (floater->island_index >= session->island_count ||
            floater->type_index >= GAME_FLOATER_CATEGORY_COUNT) {
            floater->has_wander_order = 0;
            return 1;
        }
        island = &session->islands[floater->island_index];
        /* FUN_00423068 skips the per-island/player table for player slot 4
           and keeps its global 0..0x9ff bounds. */
        if (floater->owner_slot != 4U &&
            floater->owner_slot < GAME_FLOATER_CATEGORY_COUNT) {
            raw_min_x = island->floater_min_x[floater->owner_slot];
            raw_max_x = island->floater_max_x[floater->owner_slot];
        }
        if (!floater_motion_wander_destination(
                &session->random_state, floater->x, floater->y,
                raw_min_x, raw_max_x, &wander_destination)) {
            /* The source cancels FA_Wander when destination resolution
               rejects the generated X coordinate. */
            floater->has_wander_order = 0;
            floater->movement_state = 0;
            floater->wander_timer = 0;
            return 1;
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
    speed_context.category_speed_modifier = floater->category_speed_modifier;
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
            /* The retained wander order selects another point next tick. */
            floater->movement_state = 0;
        }
    }
    return 1;
}

#include "game_session.h"

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
    if (floater->owner_slot != player_slot || floater->source_subtype == 0) {
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
    floater->source_order_pending = 0;

    if (floater->island_index != island_index) {
        floater->active_order_action = 9;
        if (!game_session_begin_floater_handoff(session, floater,
                                                island_index)) {
            floater->source_order_state_2c = 0;
            floater->source_order_coordinate_30 = 0;
            floater->active_order_action = 0;
            return 0;
        }
        return 1;
    }

    floater->source_order_pending = 1;
    return 1;
}

int game_session_order_floater_to_charge_site(GameSession *session,
                                              uint8_t player_slot,
                                              uint8_t island_index,
                                              unsigned int floater_index,
                                              uint16_t location_index)
{
    GameFloaterStart *floater;
    const GameRuntimeIsland *island;
    const GameRuntimeLocation *source;
    uint8_t charge_state;

    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT ||
        island_index >= session->island_count ||
        floater_index >= session->floater_count ||
        floater_index >= GAME_SESSION_MAX_FLOATERS) return 0;
    floater = &session->floaters[floater_index];
    island = &session->islands[island_index];
    if (location_index >= island->location_count ||
        floater->owner_slot != player_slot || floater->island_index != island_index ||
        floater->active_order_action != 0 || floater->linked_task_slot != -1) return 0;
    source = &island->locations[location_index];
    if (source->owner_id != player_slot ||
        source->record_value_10 < 0x2c || source->record_value_10 > 0x32 ||
        source->source_location_slot_18 < 0) return 0;

    if (floater->source_link_0c == -1) {
        charge_state = 11;
    } else {
        if (floater->charge_source_island != island_index ||
            floater->charge_source_location != location_index ||
            floater->x != source->x || floater->y != source->y) return 0;
        charge_state = 12;
    }

    floater->source_order_parameter_32 = location_index;
    floater->movement_state = charge_state;
    floater->order_timer = 0;
    floater->destination_x = source->x;
    floater->destination_y = source->y;
    floater->stop_radius = 0;
    floater->has_move_order = (uint8_t)(charge_state == 11 &&
        (floater->x != source->x || floater->y != source->y));
    floater->source_order_pending = 0;
    floater->has_wander_order = 0;
    floater->wander_timer = 0;
    return 1;
}
