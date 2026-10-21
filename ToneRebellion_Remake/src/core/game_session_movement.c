#include "game_session.h"
#include "game_session_internal.h"
#include "floater_motion.h"
#include "game_session_delivery.h"
#include "game_session_delivery_internal.h"
#include "game_session_action9.h"
#include "game_session_combat_internal.h"
#include "game_session_events.h"
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

static void game_session_remove_floater(GameSession *session,
                                        unsigned int floater_index);
void game_session_retire_floater(GameSession *session,
                                 unsigned int floater_index)
{
    game_session_remove_floater(session, floater_index);
}

static void game_session_remove_floater(GameSession *session,
                                        unsigned int floater_index)
{
    GameFloaterStart *floater = &session->floaters[floater_index];
    unsigned int index;
    unsigned int effect_slot;

    /* FUN_00467101 unlinks the source slot, releases the floater's task claim,
       and clears target references held by surviving floaters. */
    release_task_claim(session, floater);
    (void)game_session_unlink_floater_charge(session, floater_index);
    for (index = 0; index < session->floater_count; ++index) {
        GameFloaterStart *other = &session->floaters[index];
        if (index == floater_index ||
            !game_session_floater_is_active(other)) continue;
        if (other->defend_target_floater == (int16_t)floater_index &&
            other->active_order_action == 8) {
            /* A defend order keeps a second target index outside the linked
               order field. Cancel it now so a newly spawned unit cannot
               inherit the old target when this floater slot is reused. */
            other->active_order_action = 0;
            other->movement_state = 0;
            other->order_target_floater = -1;
            other->defend_target_floater = -1;
            other->order_target_location = -1;
            other->order_target_island = UINT8_MAX;
            other->order_progress = 0;
            other->source_order_state_2c = 0;
            other->source_order_coordinate_30 = 0;
            other->source_order_pending = 0;
            other->source_runtime_flags &= ~0x065U;
            other->has_move_order = 0;
            other->has_wander_order = 1;
            other->wander_timer = 0;
        }
        if (other->order_target_floater != (int16_t)floater_index ||
            (other->source_runtime_flags & 0x004U) == 0) continue;
        /* FUN_004206b2 routes this through FUN_00421ec1(-1): drop the
           linked order/claim and clear its target bookkeeping and flags. */
        release_task_claim(session, other);
        other->active_order_action = 0;
        other->movement_state = 0;
        other->has_move_order = 0;
        other->order_target_floater = -1;
        other->order_target_location = -1;
        other->order_target_island = UINT8_MAX;
        other->order_progress = 0;
        other->source_order_state_2c = 0;
        other->source_order_coordinate_30 = 0;
        other->source_order_pending = 0;
        other->source_runtime_flags &= ~0x065U;
        other->has_wander_order = 1;
        other->wander_timer = 0;
    }
    for (effect_slot = 0; effect_slot < 32; ++effect_slot) {
        GameDefenseProjectile *projectile =
            &session->defense_projectiles[effect_slot];
        if (projectile->active != 0 &&
            projectile->target_floater == (int16_t)floater_index) {
            /* FUN_00418921 invalidates effect-table entries that still target
               the removed floater; do not let a tower bolt retarget a reused
               slot on the next island tick. */
            projectile->active = 0;
        }
    }
    /* FUN_00467101 calls FUN_00425084 before freeing the slot. Drop carried
       artifacts at the nearest empty neutral site (or back to inventory when
       no site is available), and clear the carried-item field for all cargo. */
    game_session_drop_carried_artifact(session, floater);
    floater->is_active = 0;
    floater->movement_state = 0;
    floater->active_order_action = 0;
    floater->has_move_order = 0;
    floater->has_wander_order = 0;
    if (floater->owner_slot < GAME_START_PLAYER_COUNT)
        game_session_refresh_player_maintenance_budgets(session);
    if (floater->attack_effect_active &&
        session->active_attack_effect_count != 0) {
        --session->active_attack_effect_count;
    }
    floater->attack_effect_active = 0;
    for (effect_slot = 0; effect_slot < GAME_SESSION_MAX_CAST_EFFECTS;
         ++effect_slot) {
        struct GameCastEffectState *effect = &session->cast_effects[effect_slot];
        if (effect->active == 0 || effect->caster_index != floater_index) continue;
        effect->active = 0;
        if (session->active_cast_effect_count != 0)
            --session->active_cast_effect_count;
    }
}

static int game_session_advance_category4_subtype9_order(
    GameSession *session, unsigned int floater_index)
{
    GameFloaterStart *floater = &session->floaters[floater_index];
    GameRuntimeLocation *target;

    if (floater->active_order_action != 1 || floater->movement_state != 1 ||
        floater->has_move_order) return 0;
    if (floater->island_index >= session->island_count ||
        floater->order_target_location < 0 ||
        (uint16_t)floater->order_target_location >=
            session->islands[floater->island_index].location_count) {
        floater->active_order_action = 0;
        floater->movement_state = 0;
        floater->order_target_location = -1;
        floater->order_progress = 0;
        return 0;
    }

    target = &session->islands[floater->island_index].locations[
        (uint16_t)floater->order_target_location];
    if ((target->renderer_class != 0 && target->renderer_class != 1) ||
        (target->record_value_10 != 0 && target->record_value_10 != 1)) {
        floater->active_order_action = 0;
        floater->movement_state = 0;
        floater->order_target_location = -1;
        floater->order_progress = 0;
        return 0;
    }

    if ((target->source_flags & 0x200U) != 0) {
        floater->current_hit_points = 0;
        floater->source_runtime_flags |= 0x008U;
        floater->source_death_timer = 0;
        return 0;
    }

    /* FUN_0041e569 writes location +0x14=4, clears flag 2, then calls
       FUN_00453a5f before FUN_00467101 removes this subtype-9 floater. */
    target->source_value_14 = 4;
    target->source_flags &= ~0x002U;
    (void)game_session_recalculate_active_locations(session);
    game_session_remove_floater(session, floater_index);
    return 1;
}

static int game_session_tick_floater_death(GameSession *session,
                                           unsigned int floater_index)
{
    GameFloaterStart *floater = &session->floaters[floater_index];

    if (!game_session_floater_is_active(floater)) return 1;
    if ((floater->source_runtime_flags & 0x008U) == 0) return 0;

    /* FUN_0041e569 increments the death counter and removes the floater after
       FUN_00425296(8) == 40 ticks. */
    ++floater->source_death_timer;
    if (floater->source_death_timer > 40U)
        game_session_remove_floater(session, floater_index);
    return 1;
}

static void game_session_tick_floater_cast_pulse(GameFloaterStart *floater)
{
    if ((floater->source_runtime_flags & 0x2000U) == 0) return;
    /* FUN_0041e569 increments +0x24 through 46, then clears 0x2000 on the
       following update when the old counter is already above 45. */
    if (floater->source_death_timer <= 45U) {
        ++floater->source_death_timer;
    } else {
        floater->source_runtime_flags &= ~0x2000U;
    }
}

static void game_session_tick_player_speed_boosts(GameSession *session)
{
    unsigned int player_slot;
    /* Port-side duration: REA found the native timer's writer and readers,
       but no direct expiry writer for DAT_00618f5a. */
    for (player_slot = 0; player_slot < GAME_START_PLAYER_COUNT;
         ++player_slot) {
        int16_t *timer =
            &session->economy[player_slot].floater_speed_boost_timer;
        if (*timer > 0) --*timer;
    }
}

static void game_session_tick_timed_movement_state(GameFloaterStart *floater)
{
    uint16_t timer;

    if (floater->movement_state != 0x0a) return;
    /* FUN_0041e569 switch case 9 decrements the signed +0x34 short each tick;
       when it falls below 1, the common tail clears runtime state 10. */
    timer = (uint16_t)(floater->order_timer - 1U);
    floater->order_timer = timer;
    if (timer == 0 || timer >= 0x8000U) floater->movement_state = 0;
}

static void game_session_restore_regular_floater_home_order(
    GameSession *session, GameFloaterStart *floater)
{
    uint8_t home_island;

    if (!game_session_floater_is_active(floater) ||
        floater->owner_slot >= GAME_START_PLAYER_COUNT ||
        floater->type_index == 4U ||
        floater->source_subtype == 8U || floater->source_link_0c != -1 ||
        (floater->source_runtime_flags & (0x008U | 0x010U)) != 0 ||
        (floater->active_order_action != 0 &&
         floater->active_order_action != 0x0e) ||
        (floater->movement_state != 0 && floater->movement_state != 0x0e) ||
        floater->has_move_order || floater->linked_task_slot != -1) return;

    home_island = session->economy[floater->owner_slot].hall_island_index;
    if (home_island >= session->island_count ||
        (floater->island_index == home_island &&
         floater->order_target_island == home_island)) return;

    /* FUN_0042219e falls back to FA_Wander targeted at the player's home
       island when no task row is claimed. The source game remains responsible
       for choosing the fallback task; this ports its observable home route. */
    floater->active_order_action = 0x0e;
    floater->order_target_island = home_island;
    floater->order_target_floater = -1;
    floater->order_target_location = -1;
    floater->order_progress = 0;
    floater->source_order_state_2c = 0;
    floater->source_order_pending = 0;
    floater->has_wander_order = 1;
    floater->wander_timer = 0;
    if (floater->island_index != home_island)
        (void)game_session_begin_floater_handoff(session, floater, home_island);
}

static int game_session_tick_repair_task(GameSession *session,
                                         GameFloaterStart *floater,
                                         const PadCatalog *catalog)
{
    int16_t slot;
    GamePendingEvent *event;
    GameRuntimeLocation *target;
    int16_t current;
    int16_t maximum;

    if (floater->active_order_action != 0x12) return 0;
    slot = floater->linked_task_slot;
    if (slot < 0 || slot >= GAME_SESSION_MAX_PENDING_EVENTS) goto cancel;
    event = &session->pending_events[(uint8_t)slot];
    if (event->active == 0 || event->action_type != 0x12 ||
        event->player_id != floater->owner_slot ||
        event->payload_0a != floater->order_target_island ||
        event->payload_0e != floater->order_target_location ||
        floater->order_target_island >= session->island_count ||
        floater->order_target_location < 0 ||
        (uint16_t)floater->order_target_location >=
            session->islands[floater->order_target_island].location_count) {
        goto cancel;
    }

    target = &session->islands[floater->order_target_island]
                  .locations[(uint16_t)floater->order_target_location];
    if (target->owner_id != floater->owner_slot ||
        !game_session_repair_task_values(session, catalog, event,
                                         &current, &maximum)) goto cancel;
    if (current >= maximum) goto complete;
    if (floater->movement_state == 3 || floater->movement_state == 4 ||
        floater->movement_state == 11 || floater->carried_resource_code == 1)
        return 0;
    if (floater->island_index != floater->order_target_island) goto cancel;
    if (floater->has_move_order) return 0;
    if (floater->x != target->x || floater->y != target->y) {
        floater_target_location(floater, target, 4);
        return 0;
    }
    if (floater->movement_state != 0x12) {
        floater->movement_state = 0x12;
        floater->order_timer = 0;
    }

    /* FUN_0041e569's switch uses state - 1: runtime state 0x12 advances
       after 40 ticks and calls
       FUN_004509da(1): debit both tone stocks, clamp at zero, then add one HP. */
    if (floater->order_timer < 39U) {
        ++floater->order_timer;
        return 1;
    }
    floater->order_timer = 0;
    if (target->resource_stock[GAME_RESOURCE_BUILD_TONE] != 0)
        --target->resource_stock[GAME_RESOURCE_BUILD_TONE];
    if (target->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] != 0)
        --target->resource_stock[GAME_RESOURCE_CRYSTAL_TONE];
    if (target->source_value_34 < maximum) ++target->source_value_34;
    if (target->source_value_34 >= maximum) goto complete;
    /* Completing runtime state 0x12 returns the action to state 0. The still
       linked REPAIR task then routes the worker to another Build Tone pickup. */
    floater->movement_state = 0;
    if (!game_session_start_repair_supply(session, floater)) goto cancel;
    return 1;

complete:
    (void)game_session_pending_event_release(session, (uint8_t)slot);
cancel:
    release_task_claim(session, floater);
    floater->active_order_action = 0;
    floater->movement_state = 0;
    floater->has_move_order = 0;
    floater->order_timer = 0;
    floater->has_wander_order = 1;
    floater->wander_timer = 0;
    return 1;
}

static int game_session_tick_floater_charge(GameSession *session,
                                            unsigned int floater_index)
{
    GameFloaterStart *floater = &session->floaters[floater_index];
    int succeeded;

    if (floater->active_order_action == 0x12 ||
        (floater->active_order_action == 9 &&
         floater->handoff_resume_action == 0x12)) return 0;
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
        if (floater->movement_state == 11) floater->linked_task_slot = -1;
        floater->order_timer = 1;
    } else {
        release_task_claim(session, floater);
        floater->movement_state = 0;
        floater->order_timer = 0;
        floater->has_move_order = 0;
        if (floater->source_link_0c == -1) {
            /* FUN_0041e569's failure tail assigns FA_MoveTo only to subtypes
               4 and 8: subtype 4 returns to this source; subtype 8 returns to
               its home Hall. Other kinds take the ordinary idle path. */
            if (floater->source_subtype == 4 &&
                floater->island_index < session->island_count &&
                floater->source_order_parameter_32 <
                    session->islands[floater->island_index].location_count) {
                const GameRuntimeLocation *target =
                    &session->islands[floater->island_index]
                         .locations[floater->source_order_parameter_32];
                (void)game_session_order_floater_to_coordinate(
                    session, floater->owner_slot, floater->island_index,
                    floater_index, target->x, target->y);
            } else if (floater->source_subtype == 8 &&
                       floater->owner_slot < GAME_START_PLAYER_COUNT) {
                const GamePlayerEconomy *home =
                    &session->economy[floater->owner_slot];
                if (home->hall_island_index < session->island_count) {
                    (void)game_session_order_floater_to_coordinate(
                        session, floater->owner_slot, home->hall_island_index,
                        floater_index, home->hall_x, home->hall_y);
                }
            }
        }
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
    /* FUN_0042219e keeps a newer linked order deferred while FA_Cast owns
       the tick record; let the next floater poll consume it after the cast. */
    floater->has_move_order = 0;
    floater->source_runtime_flags &= ~0x065U;
}

static int game_session_order_floater_home(GameSession *session,
                                           unsigned int floater_index)
{
    GameFloaterStart *floater = &session->floaters[floater_index];
    const GamePlayerEconomy *home;

    if (floater->owner_slot >= GAME_START_PLAYER_COUNT) return 0;
    home = &session->economy[floater->owner_slot];
    if (home->hall_island_index >= session->island_count) return 0;
    floater->has_wander_order = 0;
    floater->wander_timer = 0;
    return game_session_order_floater_to_coordinate(
        session, floater->owner_slot, home->hall_island_index,
        floater_index, home->hall_x, home->hall_y);
}

void game_session_drop_carried_artifact(GameSession *session,
                                        GameFloaterStart *floater)
{
    GameRuntimeIsland *island;
    GameRuntimeLocation *nearest = NULL;
    int32_t nearest_distance = INT32_MAX;
    int16_t item_id = floater->carried_resource_code;
    unsigned int i;

    if (item_id > 4 && item_id < 0x22 &&
        floater->island_index < session->island_count) {
        island = &session->islands[floater->island_index];
        for (i = 0; i < island->location_count; ++i) {
            GameRuntimeLocation *location = &island->locations[i];
            int32_t dx;
            int32_t dy;
            int32_t distance;

            if (location->renderer_class != 0 || location->owner_id != -1 ||
                location->record_value_10 != 0) continue;
            dx = (int32_t)floater->x - location->x;
            dy = (int32_t)floater->y - location->y;
            if (dx < 0) dx = -dx;
            if (dy < 0) dy = -dy;
            distance = dx > dy ? dx : dy;
            if (nearest == NULL || distance < nearest_distance) {
                nearest = location;
                nearest_distance = distance;
            }
        }

        if (nearest != NULL) {
            /* FUN_004503bd turns an empty neutral record into PIT_Object and
               stores the carried item ID in its +0x24 value. */
            nearest->record_value_10 = 1;
            nearest->record_value_24 = item_id;
        } else if (floater->owner_slot < GAME_START_PLAYER_COUNT) {
            ++session->economy[floater->owner_slot]
                .inventory_count[(unsigned int)(item_id - 5)];
        }
    }
    /* FUN_00425084 clears raw floater +0x18 even when it was not an artifact. */
    floater->carried_resource_code = 0;
}

static void game_session_cancel_ground_pickup_order(GameSession *session,
                                                    GameFloaterStart *floater)
{
    int16_t old_task_slot = floater->linked_task_slot;
    int release_old_task = floater->carried_resource_code > 4 &&
        floater->carried_resource_code < 0x22 && old_task_slot >= 0 &&
        old_task_slot < GAME_SESSION_MAX_PENDING_EVENTS &&
        (floater->active_order_action == 4 ||
         floater->active_order_action == 0x0d);
    GamePendingEvent expected;

    if (release_old_task != 0)
        expected = session->pending_events[(uint8_t)old_task_slot];
    release_task_claim(session, floater);
    floater->active_order_action = 0;
    floater->movement_state = 0;
    floater->has_move_order = 0;
    floater->source_order_state_2c = 0;
    floater->order_target_floater = -1;
    floater->source_runtime_flags &= ~0x065U;
    floater->has_wander_order = 1;
    floater->wander_timer = 0;
    if (release_old_task != 0 && expected.active != 0)
        (void)game_session_dispatch_task_command(session,
            (uint8_t)old_task_slot, 12, &expected);
}

static int game_session_tick_ground_object_pickup(
    GameSession *session, GameFloaterStart *floater, int arrived)
{
    GameRuntimeLocation *target;
    int32_t item_id;

    if (floater->movement_state != 13) return 0;
    if (floater->island_index >= session->island_count ||
        floater->source_order_parameter_32 >=
            session->islands[floater->island_index].location_count) {
        game_session_cancel_ground_pickup_order(session, floater);
        return 1;
    }
    target = &session->islands[floater->island_index].locations[
        floater->source_order_parameter_32];
    item_id = target->record_value_10 == 1 ? target->record_value_24 : 0;
    if (item_id == 0) {
        /* FUN_004502dc returns zero for non-PIT_Object targets; the tick then
           takes FUN_00421ec1(-1) and drops its current task/order link. */
        game_session_cancel_ground_pickup_order(session, floater);
        return 1;
    }
    if (!arrived) return 0;

    /* FUN_00425084 first places any previously carried artifact on the
       nearest empty class-0 site (or credits Inventory), then clears +0x18. */
    game_session_drop_carried_artifact(session, floater);
    if (item_id > 4 && item_id < 0x22)
        floater->carried_resource_code = (int16_t)item_id;
    /* FUN_00452a15 runs only for artifact IDs 5..33. */
    if (item_id > 4 && item_id < 0x22) {
        game_session_clear_cast_site(session, floater->island_index,
            floater->source_order_parameter_32, target);
    }
    floater->movement_state = 0;
    floater->has_move_order = 0;
    /* FUN_0041e569 sends subtype 8 back to its Hall after a completed
       non-cast state when the native global order gate is open. The remake
       reaches this handler only while simulation ticks are advancing. */
    if (floater->source_subtype == 8U &&
        floater->active_order_action != 0x13U)
        (void)game_session_order_floater_home(
            session, (unsigned int)(floater - session->floaters));
    return 1;
}

static int game_session_tick_merge_completion(GameSession *session,
                                              unsigned int floater_index,
                                              GameFloaterStart *floater)
{
    if (floater->movement_state != 0x15) return 0;

    if (floater->order_timer < 50U) ++floater->order_timer;
    if (floater->order_timer == 25U) {
        if (floater->owner_slot == 4U) {
            /* FUN_0041e569 removes the neutral merged floater at tick 25. */
            game_session_remove_floater(session, floater_index);
            return 1;
        }
        /* Player-owned floaters become subtype 8 at the same transition. */
        floater->source_subtype = 8;
        floater->attack_level_flags &= 0xfff0U;
        game_session_drop_carried_artifact(session, floater);
    }
    if (floater->order_timer < 50U) return 1;

    floater->movement_state = 0;
    floater->order_timer = 0;
    floater->order_progress = 0;
    if (floater->source_subtype == 8 &&
        game_session_order_floater_home(session, floater_index)) return 1;

    floater->active_order_action = 0;
    floater->has_move_order = 0;
    return 1;
}

static int game_session_floater_has_site_speed_bonus(
    const GameSession *session, const GameFloaterStart *floater)
{
    const GameRuntimeLocation *site;
    uint16_t glyph_mask;

    if (session == NULL || floater == NULL ||
        floater->owner_slot >= GAME_START_PLAYER_COUNT ||
        floater->source_link_0c < 0 ||
        floater->source_link_0c >= GAME_SOURCE_RECORDS_PER_PLAYER ||
        floater->charge_source_island >= session->island_count ||
        floater->charge_source_location >=
            session->islands[floater->charge_source_island].location_count) {
        return 0;
    }

    site = &session->islands[floater->charge_source_island]
                .locations[floater->charge_source_location];
    glyph_mask = session->economy[floater->owner_slot].glyph_mask;
    {
        int32_t base_item_id = game_session_base_item_id(site);
        return ((glyph_mask & 0x0008U) != 0 && base_item_id == 0x2c) ||
               ((glyph_mask & 0x0020U) != 0 && base_item_id == 0x2d) ||
               ((glyph_mask & 0x0200U) != 0 && base_item_id == 0x2e);
    }
}

static int game_session_find_birth_location(const GameSession *session,
                                            uint8_t player_slot,
                                            uint8_t island_index)
{
    const GameRuntimeIsland *island;
    const GamePlayerEconomy *economy;
    int best_location = -1;
    uint32_t best_distance = UINT32_MAX;
    unsigned int location_index;

    if (island_index >= session->island_count) return -1;
    island = &session->islands[island_index];
    economy = &session->economy[player_slot];
    for (location_index = 0; location_index < island->location_count;
         ++location_index) {
        const GameRuntimeLocation *location = &island->locations[location_index];
        int32_t dx;
        int32_t dy;
        uint32_t distance_x;
        uint32_t distance_y;
        uint32_t distance;

        /* FUN_0045e6d3 selects a visible class-1 marker nearest the Hall's
           anchor. FUN_004532e2 rejects creation targets of other classes. */
        if (location->renderer_class != 1 ||
            (location->source_value_22 & (uint16_t)(1U << player_slot)) == 0)
            continue;
        dx = (int32_t)location->x - economy->hall_x;
        dy = (int32_t)location->y - economy->hall_y;
        distance_x = (uint32_t)(dx < 0 ? -dx : dx);
        distance_y = (uint32_t)(dy < 0 ? -dy : dy);
        /* FUN_004672a6 uses the same Chebyshev metric as start-site selection. */
        distance = distance_x > distance_y ? distance_x : distance_y;
        if (best_location < 0 || distance < best_distance) {
            best_location = (int)location_index;
            best_distance = distance;
        }
    }
    return best_location;
}

static int game_session_create_recruited_worker(GameSession *session,
                                                 uint8_t player_slot,
                                                 uint8_t island_index,
                                                 uint16_t location_index)
{
    const FloaterStats *stats;
    GameFloaterStart *floater;
    GameRuntimeLocation *location;
    unsigned int floater_index;
    uint8_t type_index;

    if (player_slot >= GAME_START_PLAYER_COUNT ||
        island_index >= session->island_count ||
        location_index >= session->islands[island_index].location_count)
        return 0;
    type_index = session->player_starts.players[player_slot].floater_type_index;
    stats = &session->worker_birth_stats[player_slot];
    if (stats == NULL || stats->hit_points < 0 ||
        stats->hit_points > (int16_t)UINT8_MAX ||
        stats->attack_strength < 0 ||
        stats->attack_strength > (int16_t)UINT8_MAX ||
        stats->movement_speed < 0) return 0;

    for (floater_index = 0; floater_index < GAME_SESSION_MAX_FLOATERS;
         ++floater_index) {
        if (floater_index >= session->floater_count ||
            !game_session_floater_is_active(&session->floaters[floater_index]))
            break;
    }
    if (floater_index == GAME_SESSION_MAX_FLOATERS) return 0;

    location = &session->islands[island_index].locations[location_index];
    floater = &session->floaters[floater_index];
    memset(floater, 0, sizeof(*floater));
    floater->is_active = 1;
    floater->island_index = island_index;
    floater->type_index = type_index;
    floater->source_subtype = 0;
    floater->owner_slot = player_slot;
    floater->current_hit_points = stats->hit_points;
    floater->max_hit_points = stats->hit_points;
    floater->attack_strength = (uint8_t)stats->attack_strength;
    floater->max_attack_points = stats->max_attack_points;
    floater->base_max_attack_points = stats->max_attack_points;
    floater->attack_realm = stats->attack_realm;
    if (stats->attack_realm >= 0 && stats->attack_realm < 4) {
        memcpy(floater->attack_impact_frame_counts,
               session->worker_birth_impact_frame_counts[player_slot],
               sizeof(floater->attack_impact_frame_counts));
    }
    floater->attack_range = stats->attack_range;
    floater->attack_period = stats->attack_period;
    floater->attack_frame_first = stats->attack_frame_first;
    floater->attack_frame_last = stats->attack_frame_last;
    floater->attack_frame_ticks_per_frame = stats->attack_frame_ticks_per_frame;
    floater->attack_frame_duration = stats->attack_frame_duration;
    floater->attack_frame_ping_pong = stats->attack_frame_ping_pong;
    floater->source_link_0c = -1;
    floater->charge_source_island = UINT8_MAX;
    floater->charge_source_location = UINT16_MAX;
    floater->linked_task_slot = -1;
    floater->order_source_location = -1;
    floater->order_target_location = -1;
    floater->order_target_floater = -1;
    floater->order_target_island = island_index;
    floater->order_source_island = island_index;
    floater->handoff_departure_location = -1;
    floater->x = location->x;
    floater->y = location->y;
    floater->destination_x = location->x;
    floater->destination_y = location->y;
    floater->movement_speed = (uint16_t)stats->movement_speed;
    floater->has_wander_order = 1;
    /* FUN_004532e2 holds the floater with 0x801, links it at site +0x2e, sets
       site flag 2 and clears +0x42. The class-1 PROD cycle (100 ticks) then
       releases it at (x, y - 0x28) via release_leviathan_floater. */
    floater->source_runtime_flags = 0x801U;
    if (floater_index >= session->floater_count)
        session->floater_count = (uint16_t)(floater_index + 1U);
    location->leviathan_spawned_floater = (int16_t)floater_index;
    location->source_flags |= 0x002U;
    location->production_progress = 0;
    location->source_value_42 = 0;
    game_session_refresh_player_maintenance_budgets(session);
    (void)game_session_queue_audio_event(
        session, GAME_SESSION_AUDIO_FLOATER_BIRTH, player_slot);
    return 1;
}

static void game_session_tick_floater_recruitment(
    GameSession *session)
{
    unsigned int player_slot;

    for (player_slot = 0; player_slot < GAME_START_PLAYER_COUNT; ++player_slot) {
        const GamePlayerEconomy *economy = &session->economy[player_slot];
        uint8_t island_index = economy->hall_island_index;
        unsigned int floater_index;
        unsigned int owned_count = 0;
        unsigned int worker_count = 0;
        int birth_location;

        if (economy->source_maintenance_capacity < 1 ||
            island_index >= session->island_count) continue;
        for (floater_index = 0; floater_index < session->floater_count;
             ++floater_index) {
            const GameFloaterStart *floater = &session->floaters[floater_index];
            if (!game_session_floater_is_active(floater) ||
                floater->owner_slot != player_slot) continue;
            ++owned_count;
            if (floater->source_subtype == 0) ++worker_count;
        }
        /* FUN_0045eaa7 gates on positive total count, then compares subtype-0
           count with floor(gross capacity / 2), not half the current unit
           count. A class-1 recruiter marker must also be available. */
        if (owned_count == 0) continue;
        birth_location = game_session_find_birth_location(
            session, (uint8_t)player_slot, island_index);
        if (birth_location < 0) continue;
        if (economy->source_maintenance_budget > 4 &&
            worker_count < (unsigned int)economy->source_maintenance_capacity / 2U &&
            session->economy[player_slot].floater_birth_timer < UINT32_MAX) {
            ++session->economy[player_slot].floater_birth_timer;
        }
        if (session->economy[player_slot].floater_birth_timer > 300U) {
            (void)game_session_create_recruited_worker(
                session, (uint8_t)player_slot, island_index,
                (uint16_t)birth_location);
            session->economy[player_slot].floater_birth_timer = 0;
        }
    }
}

void game_session_tick_floater_moves(GameSession *session, uint32_t source_tick,
                                     const PadCatalog *catalog)
{
    unsigned int i;

    if (session == NULL) return;
    game_session_tick_player_speed_boosts(session);
    game_session_assign_local_resource_tasks(session, catalog);
    game_session_tick_site_effect_timers(session);
    game_session_tick_combat_effects(session, source_tick);
    game_session_tick_cast_effects(session, source_tick, catalog);
    game_session_tick_floater_recruitment(session);
    for (i = 0; i < session->floater_count; ++i) {
        GameFloaterStart *floater = &session->floaters[i];
        FloaterPosition position;
        FloaterPosition destination;
        FloaterMotionSpeedContext speed_context;
        uint16_t effective_speed;
        int32_t dx;
        int32_t dy;
        int32_t distance;

        if ((floater->source_runtime_flags & 0x800U) != 0) {
            /* FUN_0041e569 holds newly produced Leviathan floaters while
               their building's PROD animation is still running. The native
               +0x24 counter advances during that hold and removes the unit
               at 0xc9 if the producer never releases it. This check precedes
               ordinary death handling even when both flags 0x800 and 0x008
               are set. */
            ++floater->source_death_timer;
            if (floater->source_death_timer >= 0xc9U)
                game_session_remove_floater(session, i);
            continue;
        }
        if (game_session_tick_floater_death(session, i)) continue;
        game_session_tick_floater_cast_pulse(floater);
        if (game_session_tick_ground_object_pickup(session, floater, 0))
            continue;
        if (game_session_tick_repair_task(session, floater, catalog)) continue;
        if (game_session_tick_floater_charge(session, i)) continue;
        if (game_session_tick_merge_completion(session, i, floater)) continue;
        if (game_session_advance_category4_subtype9_order(session, i)) continue;
        game_session_advance_category4_autonomous_order(session, i);
        (void)game_session_assign_category4_autonomous_order(session, i);
        (void)game_session_assign_category4_subtype9_order(
            session, i, source_tick);

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
                int32_t anchor_x =
                    (int32_t)(floater->source_order_coordinate_30 >> 8) * 10;
                int32_t anchor_y =
                    (int32_t)(floater->source_order_coordinate_30 & 0xffU) * 10;

                floater->active_order_action = 9;
                floater->movement_state = 9;
                floater->destination_x = (uint16_t)anchor_x;
                floater->destination_y = (uint16_t)anchor_y;
                floater->stop_radius = 0;
                floater->has_wander_order = 0;
                floater->wander_timer = 0;
                floater->has_move_order = 1;
                floater->order_progress = 1;
            }
        }

        if (floater->active_order_action == 0x13 &&
            floater->movement_state == 0x13 &&
            (floater->cast_spell_kind == 0 ||
             floater->cast_spell_kind == 1 ||
             floater->cast_spell_kind == 2 ||
             floater->cast_spell_kind == 3 ||
             floater->cast_spell_kind == 4 ||
             floater->cast_spell_kind == 5 ||
             floater->cast_spell_kind == 6 ||
             floater->cast_spell_kind == 7 ||
             floater->cast_spell_kind == 8 ||
             floater->cast_spell_kind == 9 ||
             floater->cast_spell_kind == 0x0a ||
             floater->cast_spell_kind == 0x0b ||
             floater->cast_spell_kind == 0x0c ||
             floater->cast_spell_kind == 0x0d ||
             floater->cast_spell_kind == 0x0e ||
             floater->cast_spell_kind == 0x0f ||
             floater->cast_spell_kind == 0x10 ||
             floater->cast_spell_kind == 0x11 ||
             floater->cast_spell_kind == 0x12 ||
             floater->cast_spell_kind == 0x13 ||
             floater->cast_spell_kind == 0x14 ||
             floater->cast_spell_kind == 0x15 ||
             floater->cast_spell_kind == 0x16)) {
            static const int16_t cast_ranges[23] = {
                300, -1, -1, 300, 300, -1, -1, 20,
                -1, -1, -1, 300, 300, 300, -1, 300,
                -1, -1, 20, 300, -1, -1, 30
            };
            int16_t range = cast_ranges[floater->cast_spell_kind];
            if ((floater->source_runtime_flags & 0x200U) != 0) {
                game_session_cancel_cast_order(floater);
            } else if (!game_session_resolve_cast_destination(session, floater)) {
                game_session_cancel_cast_order(floater);
            } else if (range == -1 ||
                       game_session_source_chebyshev_distance(
                           floater->x, floater->y,
                           floater->destination_x,
                           floater->destination_y) <= range) {
                /* FUN_0042383d uses -1 for unlimited range, then starts
                   FUN_0041660b on the tenth in-range tick. Kind 4 applies its
                   selected-site flag and timer after the same cast wait. */
                if (floater->order_timer < 400U) ++floater->order_timer;
                if (floater->order_timer == 10U) {
                    (void)game_session_schedule_cast_effect_step(
                        session, i, floater->cast_spell_kind,
                        floater->order_target_location,
                        floater->cast_spell_kind == 0x16 ? 0 : 1);
                }
                if (floater->order_timer >= 400U)
                    game_session_cancel_cast_order(floater);
            }
            continue;
        }

        game_session_advance_merge_order(session, i);
        game_session_advance_defend_order(session, i);
        game_session_advance_action9(session, i);
        game_session_tick_floater_combat(session, i);
        if (game_session_tick_floater_handoff(session, floater)) continue;
        if ((floater->active_order_action == 4 ||
             (floater->active_order_action == 0x12 &&
              (floater->movement_state == 3 || floater->movement_state == 4))) &&
            !floater->has_move_order) {
            game_session_advance_local_resource_task(session, catalog, floater);
            if (!floater->has_move_order) continue;
        }

        game_session_restore_regular_floater_home_order(session, floater);

        if (game_session_tick_floater_wander(session, floater, source_tick))
            continue;

        if (floater->movement_state == 9 &&
            floater->source_order_state_2c == 9) {
            FloaterPosition waypoint;
            int32_t raw_min_x = 0;
            int32_t raw_max_x = 0x9ff;
            int32_t anchor_x =
                (int32_t)(floater->source_order_coordinate_30 >> 8) * 10;
            int32_t anchor_y =
                (int32_t)(floater->source_order_coordinate_30 & 0xffU) * 10;

            if (floater->island_index < session->island_count &&
                floater->owner_slot != 4U &&
                floater->owner_slot < GAME_FLOATER_CATEGORY_COUNT) {
                GameRuntimeIsland *island =
                    &session->islands[floater->island_index];
                raw_min_x = island->floater_min_x[floater->owner_slot];
                raw_max_x = island->floater_max_x[floater->owner_slot];
            }
            /* FUN_00423068 recomputes this destination on every state-9
               update, centered on the packed order anchor. */
            if (!floater_motion_wander_destination(
                    &session->random_state, anchor_x, anchor_y,
                    raw_min_x, raw_max_x, &waypoint)) {
                floater->source_order_state_2c = 0;
                floater->active_order_action = 0;
                floater->movement_state = 0;
                floater->has_move_order = 0;
                floater->order_progress = 0;
                continue;
            }
            floater->destination_x = (uint16_t)waypoint.x;
            floater->destination_y = (uint16_t)waypoint.y;
            floater->stop_radius = 0;
            floater->has_move_order = 1;
            if (waypoint.x < floater->x) floater->facing_left = 1;
            else if (waypoint.x > floater->x) floater->facing_left = 0;
        }

        if (floater->movement_state == 8) {
            int32_t raw_min_x = 0;
            int32_t raw_max_x = 0x9ff;
            int32_t target_x;
            int32_t target_y;

            if (floater->island_index >= session->island_count) {
                floater->active_order_action = 0;
                floater->movement_state = 0;
                floater->has_move_order = 0;
                continue;
            }
            if (floater->owner_slot != 4U &&
                floater->owner_slot < GAME_FLOATER_CATEGORY_COUNT) {
                GameRuntimeIsland *island =
                    &session->islands[floater->island_index];
                raw_min_x = island->floater_min_x[floater->owner_slot];
                raw_max_x = island->floater_max_x[floater->owner_slot];
            }
            /* FUN_00423068 resolves state 8 to a fresh +/-100 step around
               the defender, then rejects X outside the owner's island span.
               Keep the unsigned position model inside the world at Y=0. */
            target_x = (int32_t)floater->x - 100 +
                (int32_t)tone_rng_bounded(&session->random_state, 200);
            target_y = (int32_t)floater->y - 100 +
                (int32_t)tone_rng_bounded(&session->random_state, 200);
            if (raw_min_x > 0 && target_x < raw_min_x) {
                floater->active_order_action = 0;
                floater->movement_state = 0;
                floater->has_move_order = 0;
                continue;
            }
            if (raw_max_x < 0x9ff && target_x > raw_max_x) {
                floater->active_order_action = 0;
                floater->movement_state = 0;
                floater->has_move_order = 0;
                continue;
            }
            if (target_y < 0) target_y = 0;
            floater->destination_x = (uint16_t)target_x;
            floater->destination_y = (uint16_t)target_y;
            floater->stop_radius = 0;
            floater->has_move_order = 1;
        }

        if (floater->movement_state == 6 &&
            floater->order_target_floater >= 0 &&
            (unsigned int)floater->order_target_floater <
                session->floater_count) {
            const GameFloaterStart *target = &session->floaters[
                (unsigned int)floater->order_target_floater];
            if (game_session_floater_is_active(target) &&
                target->island_index == floater->island_index) {
                game_session_set_approach_point(floater, target->x, target->y);
                floater->stop_radius =
                    game_session_floater_approach_radius(floater);
                dx = (int32_t)floater->destination_x - floater->x;
                dy = (int32_t)floater->destination_y - floater->y;
                distance = dx < 0 ? -dx : dx;
                if ((dy < 0 ? -dy : dy) > distance)
                    distance = dy < 0 ? -dy : dy;
                floater->has_move_order =
                    (uint8_t)(distance > floater->stop_radius);
            }
        } else if (floater->movement_state == 7 &&
                   floater->island_index < session->island_count &&
                   floater->order_target_location >= 0 &&
                   (uint16_t)floater->order_target_location <
                       session->islands[floater->island_index].location_count) {
            const GameRuntimeLocation *target =
                &session->islands[floater->island_index].locations[
                    (uint16_t)floater->order_target_location];
            game_session_set_approach_point(floater, target->x, target->y);
            floater->stop_radius =
                game_session_floater_approach_radius(floater);
            dx = (int32_t)floater->destination_x - floater->x;
            dy = (int32_t)floater->destination_y - floater->y;
            distance = dx < 0 ? -dx : dx;
            if ((dy < 0 ? -dy : dy) > distance)
                distance = dy < 0 ? -dy : dy;
            floater->has_move_order =
                (uint8_t)(distance > floater->stop_radius);
        }
        if (!floater->has_move_order) {
            game_session_tick_timed_movement_state(floater);
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
            if (game_session_tick_ground_object_pickup(session, floater, 1))
                continue;
            if (floater->movement_state == 3 || floater->movement_state == 4 ||
                floater->movement_state == 5) {
                game_session_advance_local_resource_task(session, catalog, floater);
                continue;
            }
            if (floater->movement_state == 9 || floater->movement_state == 0x0f ||
                floater->movement_state == 0x10) floater->movement_state = 0;
            game_session_tick_timed_movement_state(floater);
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
        speed_context.owner_slot = floater->owner_slot;
        speed_context.floater_subtype = floater->source_subtype;
        speed_context.state = floater->movement_state;
        speed_context.owner_speed_modifier =
            floater->owner_slot < GAME_START_PLAYER_COUNT
                ? session->economy[floater->owner_slot]
                    .floater_speed_boost_timer : 0;
        if (floater->movement_state == 8 &&
            floater->order_target_floater >= 0 &&
            (unsigned int)floater->order_target_floater < session->floater_count) {
            const GameFloaterStart *target = &session->floaters[
                (unsigned int)floater->order_target_floater];
            speed_context.near_target_override =
                game_session_source_chebyshev_distance(
                    floater->x, floater->y, target->x, target->y) < 100;
        } else if (floater->movement_state == 9) {
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
        speed_context.site_speed_bonus =
            (uint8_t)game_session_floater_has_site_speed_bonus(session, floater);
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
            if (game_session_tick_ground_object_pickup(session, floater, 1))
                continue;
            if (floater->movement_state == 9 || floater->movement_state == 0x0f ||
                floater->movement_state == 0x10) floater->movement_state = 0;
        }
        game_session_advance_local_resource_task(session, catalog, floater);
        game_session_tick_timed_movement_state(floater);

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
    FloaterPosition wander_destination;
    GameRuntimeIsland *island;
    uint16_t effective_speed;
    int32_t raw_min_x = 0;
    int32_t raw_max_x = 0x9ff;
    int arrived;

    if (floater->has_move_order && floater->has_wander_order) {
        /* A newly assigned route replaces the idle fallback action. */
        floater->has_wander_order = 0;
        floater->wander_timer = 0;
        if (floater->movement_state == 0x0e) floater->movement_state = 0;
    }
    if (!floater->has_wander_order || floater->has_move_order) return 0;
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
    if (floater->movement_state != 0x0e) {
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
        else if (wander_destination.x > floater->x) floater->facing_left = 0;
        floater->movement_state = 0x0e;
        floater->wander_timer = 60;
    }

    position.x = floater->x;
    position.y = floater->y;
    destination.x = floater->destination_x;
    destination.y = floater->destination_y;
    speed_context.unit_speed = floater->movement_speed;
    speed_context.owner_slot = floater->owner_slot;
    speed_context.floater_subtype = floater->source_subtype;
    speed_context.state = 0x0e;
    speed_context.owner_speed_modifier =
        floater->owner_slot < GAME_START_PLAYER_COUNT
            ? session->economy[floater->owner_slot]
                .floater_speed_boost_timer : 0;
    speed_context.near_target_override = 0;
    speed_context.site_speed_bonus =
        (uint8_t)game_session_floater_has_site_speed_bonus(session, floater);
    effective_speed = floater_motion_effective_speed(&speed_context);
    arrived = floater_motion_step(&position, destination, effective_speed,
                                  source_tick);
    floater->x = (uint16_t)position.x;
    floater->y = (uint16_t)position.y;

    if (floater->active_order_action == 0x14) {
        int32_t dx = (int32_t)floater->destination_x - floater->x;
        int32_t dy = (int32_t)floater->destination_y - floater->y;
        int32_t distance = dx < 0 ? -dx : dx;
        if ((dy < 0 ? -dy : dy) > distance)
            distance = dy < 0 ? -dy : dy;

        /* FUN_0041e569 gives state 0x0e an exact-arrival radius for
           FA_MergeWith. Until arrival, FUN_00423068 selects a fresh point
           around the floater and FUN_00422d27 performs a second step. */
        if (distance == 0) {
            floater->movement_state = 0;
            return 1;
        }
        if (!floater_motion_wander_destination(
                &session->random_state, floater->x, floater->y,
                raw_min_x, raw_max_x, &wander_destination)) {
            floater->active_order_action = 0;
            floater->has_wander_order = 0;
            floater->movement_state = 0;
            floater->wander_timer = 0;
            floater->order_target_floater = -1;
            floater->order_target_location = -1;
            floater->order_progress = 0;
            floater->source_runtime_flags &= ~0x065U;
            return 1;
        }
        floater->destination_x = (uint16_t)wander_destination.x;
        floater->destination_y = (uint16_t)wander_destination.y;
        if (wander_destination.x < floater->x) floater->facing_left = 1;
        else if (wander_destination.x > floater->x) floater->facing_left = 0;

        if ((floater->source_runtime_flags & 0x411U) == 0) {
            position.x = floater->x;
            position.y = floater->y;
            destination.x = floater->destination_x;
            destination.y = floater->destination_y;
            (void)floater_motion_step(&position, destination,
                                      effective_speed, source_tick);
            floater->x = (uint16_t)position.x;
            floater->y = (uint16_t)position.y;
        }
    } else {
        /* FUN_004211bb keeps the resolved destination while FA_Wander is
           active. The state timer advances only after exact coordinate
           arrival; the next destination is selected after that timer ends. */
        if (arrived && floater->wander_timer > 0) {
            --floater->wander_timer;
            if (floater->wander_timer == 0) {
                floater->movement_state = 0;
            }
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
    if (!game_session_floater_is_active(floater) ||
        (floater->source_runtime_flags & 0x008U) != 0 ||
        floater->owner_slot != player_slot) {
        return 0;
    }

    /* FUN_0043530b enables coordinate mode 0x13 without a subtype check;
       FUN_00435826 sends 0x4c with FUN_0041e3eb's packed destination. That
       helper rounds each nonnegative coordinate with (coordinate + 5) / 10;
       FUN_0041e427 expands the bytes back to pixels by multiplying by 10. */
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

int game_session_order_floater_to_merge(GameSession *session,
                                        uint8_t player_slot,
                                        uint8_t island_index,
                                        unsigned int floater_index,
                                        unsigned int target_floater_index)
{
    GameFloaterStart *floater;
    const GameFloaterStart *target;

    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT ||
        island_index >= session->island_count ||
        floater_index >= session->floater_count ||
        target_floater_index >= session->floater_count ||
        floater_index == target_floater_index) return 0;
    floater = &session->floaters[floater_index];
    target = &session->floaters[target_floater_index];
    if (!game_session_floater_is_active(floater) ||
        !game_session_floater_is_active(target) ||
        (floater->source_runtime_flags & 0x008U) != 0 ||
        (target->source_runtime_flags & 0x008U) != 0 ||
        floater->owner_slot != player_slot || floater->source_subtype == 0 ||
        target->owner_slot != player_slot ||
        floater->island_index != island_index || target->island_index != island_index ||
        floater->active_order_action != 0 || floater->linked_task_slot != -1) {
        return 0;
    }

    floater->active_order_action = 0x14;
    floater->movement_state = 0;
    floater->order_target_floater = (int16_t)target_floater_index;
    floater->order_target_location = -1;
    floater->order_progress = 0;
    floater->source_order_pending = 0;
    floater->has_move_order = 0;
    floater->has_wander_order = 0;
    floater->wander_timer = 0;
    return 1;
}

int game_session_order_floater_to_defend(GameSession *session,
                                         uint8_t player_slot,
                                         uint8_t island_index,
                                         unsigned int floater_index,
                                         unsigned int target_floater_index)
{
    GameFloaterStart *floater;
    const GameFloaterStart *target;

    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT ||
        island_index >= session->island_count ||
        floater_index >= session->floater_count ||
        target_floater_index >= session->floater_count ||
        floater_index == target_floater_index) return 0;
    floater = &session->floaters[floater_index];
    target = &session->floaters[target_floater_index];
    if (!game_session_floater_is_active(floater) ||
        !game_session_floater_is_active(target) ||
        (floater->source_runtime_flags & 0x008U) != 0 ||
        (target->source_runtime_flags & 0x008U) != 0 ||
        floater->owner_slot != player_slot || floater->source_subtype == 0 ||
        target->owner_slot != player_slot ||
        floater->island_index != island_index || target->island_index != island_index ||
        floater->active_order_action != 0 || floater->linked_task_slot != -1) {
        return 0;
    }

    floater->active_order_action = 8;
    floater->movement_state = 0;
    floater->order_target_floater = (int16_t)target_floater_index;
    floater->defend_target_floater = (int16_t)target_floater_index;
    floater->order_target_location = -1;
    floater->order_progress = 0;
    floater->source_order_pending = 0;
    floater->has_move_order = 0;
    floater->has_wander_order = 0;
    floater->wander_timer = 0;
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
    int32_t base_item_id;

    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT ||
        island_index >= session->island_count ||
        floater_index >= session->floater_count ||
        floater_index >= GAME_SESSION_MAX_FLOATERS) return 0;
    floater = &session->floaters[floater_index];
    island = &session->islands[island_index];
    if (!game_session_floater_is_active(floater) ||
        (floater->source_runtime_flags & 0x008U) != 0) return 0;
    if (location_index >= island->location_count ||
        floater->owner_slot != player_slot || floater->island_index != island_index ||
        floater->active_order_action != 0 || floater->linked_task_slot != -1) return 0;
    source = &island->locations[location_index];
    base_item_id = game_session_base_item_id(source);
    if (source->owner_id != player_slot ||
        base_item_id < 0x2c || base_item_id > 0x32 ||
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

int game_session_can_order_floater_to_ground_object(
    const GameSession *session, uint8_t player_slot, uint8_t island_index,
    unsigned int floater_index, uint16_t location_index)
{
    const GameRuntimeIsland *island;
    const GameFloaterStart *floater;
    const GameRuntimeLocation *target;
    int32_t item_id;

    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT ||
        island_index >= session->island_count ||
        floater_index >= session->floater_count ||
        location_index >= session->islands[island_index].location_count)
        return 0;
    floater = &session->floaters[floater_index];
    island = &session->islands[island_index];
    target = &island->locations[location_index];
    item_id = target->record_value_10 == 1 ? target->record_value_24 : 0;
    if (!game_session_floater_is_active(floater) ||
        (floater->source_runtime_flags & 0x008U) != 0 ||
        floater->owner_slot != player_slot ||
        floater->island_index != island_index ||
        floater->linked_task_slot != -1 ||
        (floater->active_order_action != 0 &&
         floater->active_order_action != 0x0d) ||
        target->renderer_class != 0 || target->owner_id != -1 ||
        item_id < 5 || item_id > 33) return 0;
    return 1;
}

int game_session_order_floater_to_ground_object(GameSession *session,
                                                uint8_t player_slot,
                                                uint8_t island_index,
                                                unsigned int floater_index,
                                                uint16_t location_index)
{
    GameFloaterStart *floater;
    const GameRuntimeLocation *target;

    if (!game_session_can_order_floater_to_ground_object(session, player_slot,
            island_index, floater_index, location_index)) return 0;
    floater = &session->floaters[floater_index];
    target = &session->islands[island_index].locations[location_index];

    /* The consumer's arrival path reads the target from +0x32 and expects
       state 13. Action 0x0d is also the task class released by cancellation. */
    floater->active_order_action = 0x0d;
    floater->movement_state = 13;
    floater->source_order_parameter_32 = location_index;
    floater->order_target_location = (int16_t)location_index;
    floater->order_target_floater = -1;
    floater->destination_x = target->x;
    floater->destination_y = target->y;
    floater->stop_radius = 0;
    floater->order_timer = 0;
    floater->has_move_order = 1;
    floater->source_order_pending = 0;
    floater->has_wander_order = 0;
    floater->wander_timer = 0;
    return 1;
}
