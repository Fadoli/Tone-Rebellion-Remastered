#include "game_session.h"
#include "game_session_combat_internal.h"
#include "game_session_action9.h"
#include "game_session_events.h"
#include "game_session_internal.h"
#include "game_session_delivery_internal.h"

#include <math.h>
#include <stdint.h>

enum { GAME_FLOATER_STATE_ATTACK = 6, GAME_FLOATER_STATE_ATTACK_SITE = 7 };

static void record_floater_death(GameSession *session,
                                 const GameFloaterStart *floater,
                                 int32_t killer_faction)
{
    if (session == NULL || floater == NULL) return;
    /* FUN_00416a9a selects levdeath for raw type 4, fltdeath otherwise. */
    (void)game_session_queue_audio_event(session,
        GAME_SESSION_AUDIO_FLOATER_DEATH, (int16_t)floater->type_index);
    if (floater->type_index < GAME_START_PLAYER_COUNT) {
        ++session->economy[floater->type_index].floater_losses;
    }
    if (killer_faction < 0 || killer_faction >= GAME_START_PLAYER_COUNT) return;
    if (floater->type_index == 4U) {
        if (floater->source_subtype < 18U)
            ++session->economy[killer_faction]
                .leviathan_kills_by_subtype[floater->source_subtype];
    } else if (floater->type_index < GAME_START_PLAYER_COUNT) {
        ++session->economy[killer_faction]
            .floater_kills_by_faction[floater->type_index];
    }
}

static int attack_calls_charge_helper(const GameFloaterStart *attacker)
{
    /* FUN_004207c2 returns nonzero unless this is category 4 or a charged
       nonzero subtype. FUN_0041e569 still calls FUN_004200d2 for those cases
       when the resolved max-attack-points field is -1. */
    if (attacker->type_index == 4U ||
        (attacker->source_subtype != 0 && attacker->charge_current > 0)) {
        return attacker->max_attack_points == -1;
    }
    return 1;
}

void game_session_tick_floater_combat(GameSession *session,
                                      unsigned int floater_index)
{
    GameFloaterStart *floater;
    uint8_t state;

    if (session == NULL || floater_index >= session->floater_count) return;
    floater = &session->floaters[floater_index];
    if (!game_session_floater_is_active(floater) ||
        (floater->source_runtime_flags & 0x008U) != 0) return;
    state = floater->movement_state;
    if (state != GAME_FLOATER_STATE_ATTACK &&
        state != GAME_FLOATER_STATE_ATTACK_SITE) return;

    /* FUN_0041e569 fires once at timer == FUN_0042520e(state), then waits for
       its IMPACT instance to finish and release the shared effect slot. */
    if (floater->attack_timer == floater->attack_period) {
        int32_t damage = 0;
        if (state == GAME_FLOATER_STATE_ATTACK &&
            floater->order_target_floater >= 0 &&
            (unsigned int)floater->order_target_floater < session->floater_count) {
            GameFloaterStart *target =
                &session->floaters[(unsigned int)floater->order_target_floater];
            damage = game_session_damage_floater(
                session, floater_index,
                (unsigned int)floater->order_target_floater);
            /* FUN_004200d2 reads +0x22 on the indexed target floater and
               consumes one charge after resolving this attack attempt. */
            if (attack_calls_charge_helper(floater)) {
                if (damage > 0) ++target->source_progress_08;
                if (target->charge_current > 0) --target->charge_current;
            }
        } else if (state == GAME_FLOATER_STATE_ATTACK_SITE &&
                   floater->island_index < session->island_count &&
                   floater->order_target_location >= 0 &&
                   (uint16_t)floater->order_target_location <
                       session->islands[floater->island_index].location_count) {
            if (attack_calls_charge_helper(floater)) {
                GameRuntimeLocation *target =
                    &session->islands[floater->island_index].locations[
                        (uint16_t)floater->order_target_location];
                damage = game_session_damage_site(session, floater_index,
                    floater->island_index,
                    (uint16_t)floater->order_target_location, target);
                if (damage > 0) ++target->source_progress_08;
                /* FUN_00420188 decrements raw +0x22 after every state-7
                   site attack, even though its low byte also backs the
                   remake's visibility mirror. */
                if (target->source_value_22 > 0) {
                    --target->source_value_22;
                    target->tribe_visibility_mask =
                        (uint8_t)target->source_value_22;
                }
            }
        }
        if (damage > 0)
            game_session_start_attack_effect(session, floater, damage);
    } else if (floater->attack_timer > floater->attack_period &&
               !floater->attack_effect_active) {
        floater->movement_state = 0;
        floater->source_runtime_flags &= ~0x040U;
    }
    if (floater->attack_timer < UINT16_MAX) ++floater->attack_timer;
}

#include "game_session.h"
#include "tone_rng.h"

#include <stdint.h>

/* FUN_0041fde6 (ev_6840e960) is the one power function behind both
   FUN_004200d2 (floater attacks) and FUN_00420188 (site attacks): base pad row
   +0x0a (attack_strength) only for category 4 or a charged nonzero subtype
   (FUN_004207c2 == 0); +3 when the linked source has flag 0x8000; +1 for the
   owner's glyph bit 0x01/0x40/0x400 matching a linked 0x2c/0x2d/0x2e source;
   then level * 3 plus a 1/22 research share per level nibble for category 4,
   or level * 2 for everything else. */
static int32_t floater_attack_power(const GameSession *session,
                                    const GameFloaterStart *floater)
{
    int32_t power = 0;
    int32_t level = floater->attack_level_flags & 0x0fU;

    if (floater->type_index == 4U ||
        (floater->source_subtype != 0 && floater->charge_current > 0)) {
        power = floater->attack_strength;
    }
    if (session != NULL && floater->source_link_0c >= 0 &&
        floater->charge_source_island < session->island_count &&
        floater->charge_source_location <
            session->islands[floater->charge_source_island].location_count) {
        const GameRuntimeLocation *source = &session->islands[
            floater->charge_source_island].locations[
                floater->charge_source_location];
        if (source->source_location_slot_18 == floater->source_link_0c &&
            source->owner_id == (int32_t)floater->owner_slot) {
            int32_t source_item = game_session_base_item_id(source);
            uint16_t glyph_mask = floater->owner_slot < GAME_START_PLAYER_COUNT
                ? session->economy[floater->owner_slot].glyph_mask : 0U;
            if ((source->source_flags & 0x8000U) != 0) power += 3;
            if (((glyph_mask & 0x0001U) != 0 && source_item == 0x2c) ||
                ((glyph_mask & 0x0040U) != 0 && source_item == 0x2d) ||
                ((glyph_mask & 0x0400U) != 0 && source_item == 0x2e))
                power += 1;
        }
    }
    if (floater->type_index == 4U) {
        power += level * 3;
        power += (((floater->attack_level_flags >> 4) & 0x0fU) * power) / 22;
    } else {
        power += level * 2;
    }
    return power;
}

/* FUN_00420217 (assembly 0x4202a7..0x4203f5, ev_d4bb6e22): the hit chance is
   (int)(60 * score / 14) + 10 with __ftol (0x472c6c) truncating toward zero.
   score = attack + 7 - defense; the difficulty term is a double:
   difficulty 0: attack / 4 (floor 1), 1 and 2: attack / 2 (floor 2),
   3 and 4: attack * 2 / 3 (floor 3). Realm 1 ahead of the target adds it, 1
   behind subtracts it, any other mismatch adds a signed half of it
   (DAT_00618e4c / DAT_00618e50 are zero at load: (0 / limit - 0.5) * term,
   negated when the attacker realm is above 1). attack_realm -1 means "same as
   the target", which removes the realm term. */
static int32_t native_hit_chance(uint8_t difficulty, int32_t attack_power,
                                 int32_t attack_realm, int32_t defense_power,
                                 int32_t target_realm)
{
    double term = (double)attack_power;
    double floor_value;
    double score = (double)(attack_power + 7 - defense_power);

    if (difficulty > 4U) difficulty = 4U;
    if (difficulty == 0U) {
        term /= 4.0;
        floor_value = 1.0;
    } else if (difficulty <= 2U) {
        term /= 2.0;
        floor_value = 2.0;
    } else {
        term = term * 2.0 / 3.0;
        floor_value = 3.0;
    }
    if (floor_value > term) term = floor_value;
    if (attack_realm == -1) attack_realm = target_realm;
    if (((attack_realm + 1) & 3) == target_realm) {
        score += term;
    } else if (((attack_realm + 3) & 3) == target_realm) {
        score -= term;
    } else if (attack_realm != target_realm) {
        double correction = (0.0 / 10000.0 - 0.5) * term;
        if (attack_realm > 1) correction = -correction;
        score += correction;
    }
    return (int32_t)((60.0 * score) / 14.0) + 10;
}

static int floater_attack_hits(GameSession *session,
                               const GameFloaterStart *attacker,
                               const GameFloaterStart *target,
                               int32_t attack_power)
{
    int32_t attack_realm = attacker->attack_realm & 3;
    int32_t target_realm = target->attack_realm & 3;
    int32_t defense_power = (target->source_subtype == 0 ||
                             target->source_subtype == 9)
        ? 0 : floater_attack_power(session, target);

    if ((target->source_runtime_flags & 0x108U) != 0) return 0;
    /* FUN_00420217 treats a subtype-9 target as sharing the attacker realm. */
    if (target->source_subtype == 9) target_realm = attack_realm;
    return tone_rng_bounded(&session->random_state, 100) <
        native_hit_chance(session->config.difficulty, attack_power,
                          attack_realm, defense_power, target_realm);
}

int32_t game_session_damage_floater(GameSession *session,
                              unsigned int attacker_index,
                              unsigned int target_index)
{
    GameFloaterStart *attacker = &session->floaters[attacker_index];
    GameFloaterStart *target = &session->floaters[target_index];
    int32_t power = floater_attack_power(session, attacker);
    int32_t random_range = power - 1;
    int32_t damage;

    if (!game_session_floater_is_active(attacker) ||
        !game_session_floater_is_active(target) ||
        (attacker->source_runtime_flags & 0x008U) != 0 ||
        (target->source_runtime_flags & 0x008U) != 0) return 0;
    if (!floater_attack_hits(session, attacker, target, power)) return 0;
    if (random_range < 1) random_range = 1;
    damage = (tone_rng_bounded(&session->random_state, random_range) +
              tone_rng_bounded(&session->random_state, random_range) + 3 +
              tone_rng_bounded(&session->random_state, random_range)) / 3;
    if (damage > 10) damage = 10;
    if (damage < 0) damage = 0;
    if ((int32_t)target->current_hit_points > damage) {
        target->current_hit_points = (int16_t)(
            target->current_hit_points - damage);
    } else if ((target->source_runtime_flags & 0x008U) == 0) {
        target->current_hit_points = 0;
        target->source_runtime_flags |= 0x008U;
        target->source_death_timer = 0;
        record_floater_death(session, target, attacker->type_index);
    }
    return damage;
}

int32_t game_session_damage_floater_from_power(GameSession *session,
                                               unsigned int target_index,
                                               int32_t attack_power)
{
    GameFloaterStart *target;
    int32_t defense_power;
    int32_t chance;
    int32_t random_range;
    int32_t damage;

    if (session == NULL || target_index >= session->floater_count) return 0;
    target = &session->floaters[target_index];
    if (!game_session_floater_is_active(target) || attack_power < 0 ||
        (target->source_runtime_flags & 0x108U) != 0) return 0;

    /* FUN_00420217 with realm argument -1 (FUN_004533a8, the tower path):
       the realm term disappears and only attack + 7 - defense remains. */
    defense_power = (target->source_subtype == 0 ||
                     target->source_subtype == 9)
        ? 0 : floater_attack_power(session, target);
    chance = native_hit_chance(session->config.difficulty, attack_power, -1,
                               defense_power, target->attack_realm & 3);
    if (tone_rng_bounded(&session->random_state, 100) >= chance) return 0;

    random_range = attack_power - 1;
    if (random_range < 1) random_range = 1;
    damage = (tone_rng_bounded(&session->random_state, random_range) +
              tone_rng_bounded(&session->random_state, random_range) + 3 +
              tone_rng_bounded(&session->random_state, random_range)) / 3;
    if (damage > 10) damage = 10;
    if (damage < 0) damage = 0;
    if ((int32_t)target->current_hit_points > damage) {
        target->current_hit_points = (int16_t)(
            target->current_hit_points - damage);
    } else {
        target->current_hit_points = 0;
        target->source_runtime_flags |= 0x008U;
        target->source_death_timer = 0;
        record_floater_death(session, target, -1);
    }
    return damage;
}

void game_session_clear_cast_site(GameSession *session, uint8_t island_index,
                                  uint16_t location_index,
                                  GameRuntimeLocation *target);

static void mark_site_destroyed(GameSession *session,
                                GameRuntimeLocation *target,
                                uint8_t island_index)
{
    target->source_flags |= 0x80U;
    target->source_value_48 = 0;
    if (game_session_recalculate_location_active_with_visibility(target)) {
        if (target->source_value_14 == 4) {
            game_session_recalculate_leviathan_island(session, island_index);
        } else {
            game_session_refresh_player_maintenance_budgets(session);
        }
    }
}

int32_t game_session_damage_site(GameSession *session,
                           unsigned int attacker_index,
                           uint8_t island_index,
                           uint16_t location_index,
                           GameRuntimeLocation *target)
{
    GameFloaterStart *attacker = &session->floaters[attacker_index];
    int32_t power = floater_attack_power(session, attacker);
    int32_t damage_range = power > 0 ? power : 1;
    /* FUN_00467260 scales the shared 15-bit RNG by this range, truncates via
       __ftol, adds one, then caps the site damage at six. */
    int32_t damage = tone_rng_bounded(&session->random_state, damage_range) + 1;
    int32_t item_id = game_session_base_item_id(target);

    if (!game_session_floater_is_active(attacker) ||
        (attacker->source_runtime_flags & 0x008U) != 0) return 0;
    if (damage > 6) damage = 6;
    /* FUN_00450817 filters out ordinary building IDs 0x17..0x24 before
       forwarding to FUN_00450847. The helper accepts visible, nonempty
       renderer classes 0/1 and rejects flags 0x290. */
    if (target->renderer_class > 1U || item_id == 0 ||
        (item_id >= 0x17 && item_id <= 0x24) ||
        (target->source_flags & 0x290U) != 0) return 0;
    if (item_id == 1) {
        uint16_t *stock =
            &target->resource_stock[GAME_RESOURCE_BUILD_TONE];
        if (target->record_value_24 != 1) return 0;
        if (damage * 2 < (int16_t)*stock) {
            *stock = (uint16_t)((int32_t)*stock - damage * 2);
        } else {
            /* FUN_00450847 routes an exhausted PIT_Object through the same
               site-clear path used by the cast resolver. */
            game_session_clear_cast_site(session, island_index, location_index, target);
        }
        return 1;
    }

    target->source_value_34 = (int16_t)(target->source_value_34 - damage);
    if (target->source_value_34 < 1) {
        if (item_id == 5) {
            game_session_clear_cast_site(session, island_index, location_index, target);
        } else {
            mark_site_destroyed(session, target, attacker->island_index);
        }
    }
    return damage;
}

int32_t game_session_damage_site_from_power(GameSession *session,
                                            uint8_t island_index,
                                            uint16_t location_index,
                                            int32_t attack_power)
{
    GameRuntimeLocation *target;
    int32_t item_id;
    int32_t random_range;
    int32_t damage;

    if (session == NULL || island_index >= session->island_count ||
        location_index >= session->islands[island_index].location_count)
        return 0;
    target = &session->islands[island_index].locations[location_index];
    item_id = game_session_base_item_id(target);
    /* FUN_004533a8 routes impact damage through FUN_00420217 and then the
       same site death state consumed by FUN_00450a71. */
    if (target->renderer_class > 1U || target->owner_id < 0 ||
        target->owner_id >= GAME_START_PLAYER_COUNT || item_id == 0 ||
        (item_id >= 0x17 && item_id <= 0x24) ||
        (target->source_flags & 0x290U) != 0) return 0;

    /* FUN_00420217 rolls three values from the target pad's +0x0a field,
       averages them with the source's +3 bias, and caps damage at ten. */
    random_range = attack_power - 1;
    if (random_range < 1) random_range = 1;
    damage = (tone_rng_bounded(&session->random_state, random_range) +
              tone_rng_bounded(&session->random_state, random_range) + 3 +
              tone_rng_bounded(&session->random_state, random_range)) / 3;
    if (damage > 10) damage = 10;
    if (damage < 0) damage = 0;
    target->source_value_34 = (int16_t)(target->source_value_34 - damage);
    if (target->source_value_34 < 1)
        mark_site_destroyed(session, target, island_index);
    return damage;
}

static void clear_destroyed_staff_worker(GameSession *session,
                                         GameRuntimeLocation *source,
                                         unsigned int floater_index,
                                         int32_t source_owner)
{
    GameFloaterStart *floater;
    int released_task = 0;

    if (session == NULL || source == NULL ||
        floater_index >= session->floater_count ||
        floater_index >= GAME_SESSION_MAX_FLOATERS) return;
    floater = &session->floaters[floater_index];
    if (floater->owner_slot != (uint8_t)source_owner) return;

    /* FUN_00421ec1(-1) also removes a carried-artifact task when the worker
       is replacing a resource/pickup order. Validate the reused slot first. */
    if (floater->carried_resource_code >= GAME_INVENTORY_ITEM_FIRST_ID &&
        floater->carried_resource_code < GAME_INVENTORY_ITEM_FIRST_ID +
            GAME_INVENTORY_ITEM_COUNT &&
        (floater->active_order_action == 4 ||
         floater->active_order_action == 0x0d) &&
        floater->linked_task_slot >= 0 &&
        floater->linked_task_slot < GAME_SESSION_MAX_PENDING_EVENTS) {
        uint8_t task_slot = (uint8_t)floater->linked_task_slot;
        GamePendingEvent *event = &session->pending_events[task_slot];
        if (event->active != 0 &&
            (event->action_type == 4 || event->action_type == 0x0d) &&
            event->player_id == floater->owner_slot &&
            event->payload_0a == floater->order_target_island &&
            event->payload_0e == floater->order_target_location) {
            GamePendingEvent expected = *event;
            released_task = game_session_dispatch_task_command(
                session, task_slot, 12, &expected);
        }
    }
    if (!released_task) release_task_claim(session, floater);

    if (floater->source_link_0c == source->source_location_slot_18 &&
        floater->source_link_0c >= 0) {
        if (!game_session_unlink_floater_charge(session, floater_index)) {
            floater->source_link_0c = -1;
            floater->charge_source_island = UINT8_MAX;
            floater->charge_source_location = UINT16_MAX;
        }
    }
    floater->source_subtype = 0;
    floater->attack_level_flags &= 0xfff0U;
    if (floater->owner_slot < GAME_START_PLAYER_COUNT) {
        const FloaterStats *birth_stats =
            &session->worker_birth_stats[floater->owner_slot];
        if (floater->current_hit_points > birth_stats->hit_points)
            floater->current_hit_points = birth_stats->hit_points;
        if (floater->charge_current > birth_stats->attack_strength)
            floater->charge_current = birth_stats->attack_strength;
    }
    floater->source_runtime_flags &= ~0x065U;
    floater->active_order_action = 0;
    floater->movement_state = 0;
    floater->order_target_floater = -1;
    floater->order_target_location = -1;
    floater->order_target_island = floater->island_index;
    floater->order_progress = 0;
    floater->source_order_pending = 0;
    floater->has_move_order = 0;
    floater->order_resource_code = 0;
    floater->source_order_state_2c = 0;
}

void game_session_clear_cast_site(GameSession *session, uint8_t island_index,
                                  uint16_t location_index,
                                  GameRuntimeLocation *target)
{
    int32_t previous_owner = target->owner_id;
    int32_t previous_base_item_id = game_session_base_item_id(target);
    int32_t retained_item = target->record_value_24;
    unsigned int slot;
    unsigned int task_type;

    /* FUN_00452a15 cancels every pending task for this island/location via
       FUN_00460029 before it clears the site. */
    (void)game_session_cancel_tasks_for_location(
        session, island_index, location_index);

    if (target->charge_staff_task_handle >= 0 &&
        target->charge_staff_task_handle < GAME_SESSION_MAX_PENDING_EVENTS) {
        (void)game_session_pending_event_release(
            session, (uint8_t)target->charge_staff_task_handle);
        target->charge_staff_task_handle = -1;
    }
    if (target->upgrade_task_handle >= 0 &&
        target->upgrade_task_handle < GAME_SESSION_MAX_PENDING_EVENTS) {
        GamePendingEvent *event = &session->pending_events[
            (uint8_t)target->upgrade_task_handle];
        if (event->active != 0) {
            GamePendingEvent expected = *event;
            (void)game_session_dispatch_task_command(session,
                (uint8_t)target->upgrade_task_handle, 12, &expected);
        }
        target->upgrade_task_handle = -1;
    }
    for (task_type = 0; task_type < GAME_RESOURCE_TYPE_COUNT; ++task_type) {
        int16_t task_slot = target->source_task_slot[task_type];
        if (task_slot >= 0 && task_slot < GAME_SESSION_MAX_PENDING_EVENTS) {
            (void)game_session_pending_event_release(session,
                                                     (uint8_t)task_slot);
        }
        target->source_task_slot[task_type] = -1;
    }

    /* FUN_0045efd2 resolves the site's owner source row by island/location;
       FUN_0045c5b8 then clears its current worker and all eight row links.
       The remake keeps both views, so reconcile the current pointer, slots,
       and row-linked floaters before releasing the source record. */
    if (target->charge_recent_floater >= 0)
        clear_destroyed_staff_worker(session, target,
            (unsigned int)target->charge_recent_floater, previous_owner);
    for (slot = 0; slot < 8; ++slot) {
        int16_t floater_index = target->charge_floater_slots[slot];
        if (floater_index >= 0)
            clear_destroyed_staff_worker(session, target,
                (unsigned int)floater_index, previous_owner);
        target->charge_floater_slots[slot] = -1;
    }
    if (target->source_location_slot_18 >= 0) {
        for (slot = 0; slot < session->floater_count &&
             slot < GAME_SESSION_MAX_FLOATERS; ++slot) {
            GameFloaterStart *floater = &session->floaters[slot];
            if (floater->source_link_0c != target->source_location_slot_18 ||
                floater->owner_slot != (uint8_t)previous_owner) continue;
            clear_destroyed_staff_worker(session, target, slot, previous_owner);
        }
    }

    /* FUN_00452a15 releases owner/source links and keeps item 1 only for the
       observed owner-4 pad payload range. Cast validation itself accepts
       owners 0/1, so those sites normally become empty. */
    target->owner_id = -1;
    target->source_value_14 = -1;
    target->maintenance_tone_cost = 0;
    if (previous_owner == 4 && retained_item > 4 && retained_item < 0x22) {
        target->record_value_10 = 1;
    } else {
        target->record_value_10 = 0;
        target->record_value_24 = 0;
    }
    target->source_location_slot_18 = -1;
    target->source_category_slot_60 = -1;
    target->charge_source_value_30 = 0;
    target->new_build_animation_ticks = 0;
    target->charge_floater_count = 0;
    target->charge_recent_floater = -1;
    if (target->leviathan_spawned_floater >= 0 &&
        (unsigned int)target->leviathan_spawned_floater < session->floater_count) {
        game_session_retire_floater(session,
            (unsigned int)target->leviathan_spawned_floater);
    }
    target->leviathan_spawned_floater = -1;
    target->resource_stock[GAME_RESOURCE_BUILD_TONE] = 0;
    target->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] = 0;
    target->resource_stock[GAME_RESOURCE_MAGIC_TONE] = 0;
    (void)game_session_recalculate_active_locations(session);
    /* FUN_00452a15 invokes FUN_00466c8b after clearing the record; that
       callback refreshes Leviathan budgets and marker rates for this island. */
    game_session_recalculate_leviathan_island(session, island_index);
    /* FUN_00466c8b also rebuilds player maintenance budgets. A destroyed
       building can remain marked for its crumble animation for 100 ticks;
       when the record is finally cleared here, release its maintenance even
       if the site's active bit did not change in the earlier damage update. */
    if (previous_owner >= 0 && previous_owner < GAME_START_PLAYER_COUNT)
        game_session_refresh_player_maintenance_budgets(session);
    if (previous_base_item_id == 0x28 && previous_owner >= 0 &&
        previous_owner < GAME_START_PLAYER_COUNT) {
        (void)game_session_recalculate_player_island_visibility(
            session, island_index, (uint8_t)previous_owner);
    }
}

static int32_t cast_round_to_even(double value)
{
    int32_t whole = (int32_t)value;
    double fraction = value - whole;

    if (fraction > 0.5 || (fraction == 0.5 && (whole & 1) != 0)) ++whole;
    else if (fraction < -0.5 ||
             (fraction == -0.5 && (whole & 1) != 0)) --whole;
    return whole;
}

int32_t game_session_apply_cast_site_effect(GameSession *session,
                                            uint8_t island_index,
                                            uint16_t location_index,
                                            int16_t effect_amount)
{
    GameRuntimeLocation *target;
    int32_t item_id;

    if (session == NULL || island_index >= session->island_count ||
        location_index >= session->islands[island_index].location_count) return 0;
    target = &session->islands[island_index].locations[location_index];
    if ((target->source_flags & 0x290U) != 0 ||
        target->record_value_10 == 0 ||
        target->renderer_class > 1U) return 0;

    item_id = target->record_value_10;
    if (item_id == 1) {
        int32_t drain = (int32_t)effect_amount * 2;
        if (target->record_value_24 != 1) return 0;
        if (drain < (int16_t)target->resource_stock[GAME_RESOURCE_BUILD_TONE]) {
            target->resource_stock[GAME_RESOURCE_BUILD_TONE] =
                (uint16_t)((int32_t)target->resource_stock[GAME_RESOURCE_BUILD_TONE] - drain);
        } else {
            /* FUN_00452ae7/FUN_00452a15 clear the placed runtime object. Its
               four engine callbacks and queued type-8 notification are not
               part of this session model. */
            game_session_clear_cast_site(session, island_index, location_index, target);
        }
        return 1;
    }

    {
        int32_t result = (int32_t)target->source_value_34 - effect_amount;
        uint16_t result_bits = (uint16_t)result;
        target->source_value_34 = result_bits <= (uint16_t)INT16_MAX
            ? (int16_t)result_bits
            : (int16_t)((int32_t)result_bits - (INT32_C(1) << 16));
    }
    if (target->source_value_34 < 1) {
        if (item_id == 5) {
            game_session_clear_cast_site(session, island_index, location_index, target);
        } else {
            mark_site_destroyed(session, target, island_index);
        }
    }
    return effect_amount;
}

static unsigned int game_session_apply_cast_area_damage(
    GameSession *session, unsigned int caster_index,
    int32_t radius, int32_t base_amount)
{
    GameFloaterStart *caster;
    const GameRuntimeIsland *island;
    unsigned int location_index;
    unsigned int affected = 0;
    unsigned int target_index;

    if (session == NULL || caster_index >= session->floater_count) return 0;
    caster = &session->floaters[caster_index];
    if (caster->island_index >= session->island_count) return 0;
    island = &session->islands[caster->island_index];

    /* FUN_004239e9 also calls FUN_004204bc for every other floater within
       the cast radius; direct damage does not roll normal attack chance. */
    for (target_index = 0; target_index < session->floater_count;
         ++target_index) {
        GameFloaterStart *target = &session->floaters[target_index];
        int32_t distance;
        int32_t effect_amount = base_amount;
        int32_t remaining_hp;

        if (!game_session_floater_is_active(target) ||
            target_index == caster_index ||
            target->island_index != caster->island_index ||
            (target->source_runtime_flags & 0x008U) != 0) continue;
        distance = game_session_source_chebyshev_distance(
            caster->x, caster->y, target->x, target->y);
        if (distance >= radius) continue;
        if (radius / 2 < distance) {
            effect_amount -= ((distance * 2 - radius) * 7) / radius;
        }
        remaining_hp = (int32_t)target->current_hit_points - effect_amount;
        if (remaining_hp < 1) {
            target->current_hit_points = 0;
            target->source_runtime_flags |= 0x008U;
            target->source_death_timer = 0;
            record_floater_death(session, target, caster->type_index);
        } else {
            target->current_hit_points = (int16_t)remaining_hp;
        }
        ++affected;
    }

    for (location_index = 0; location_index < island->location_count;
         ++location_index) {
        const GameRuntimeLocation *target = &island->locations[location_index];
        int32_t base_item_id = game_session_base_item_id(target);
        int32_t distance = game_session_source_chebyshev_distance(
            caster->x, caster->y, target->x, target->y);
        int32_t effect_amount = base_amount;

        /* FUN_00450817 filters item IDs 0x17..0x24 before forwarding to
           FUN_00450847. */
        if (distance >= radius ||
            (base_item_id >= 0x17 && base_item_id <= 0x24)) {
            continue;
        }
        if (radius / 2 < distance) {
            effect_amount -= ((distance * 2 - radius) * 7) / radius;
        }
        if (game_session_apply_cast_site_effect(
                session, caster->island_index, (uint16_t)location_index,
                (int16_t)effect_amount) != 0) {
            ++affected;
        }
    }

    return affected;
}

static GameRuntimeLocation *game_session_cast_source_site(
    GameSession *session, const GameFloaterStart *caster)
{
    GameRuntimeLocation *source;

    if (session == NULL || caster == NULL ||
        caster->owner_slot >= GAME_START_PLAYER_COUNT ||
        caster->source_link_0c < 0 ||
        caster->charge_source_island >= session->island_count ||
        caster->charge_source_location >=
            session->islands[caster->charge_source_island].location_count)
        return NULL;
    source = &session->islands[caster->charge_source_island].locations[
        caster->charge_source_location];
    if (source->owner_id != caster->owner_slot ||
        source->source_location_slot_18 != caster->source_link_0c)
        return NULL;
    return source;
}

static unsigned int game_session_pulse_cast_source_floaters(
    GameSession *session, const GameRuntimeLocation *source)
{
    unsigned int slot;
    unsigned int affected = 0;

    for (slot = 0; slot < 8; ++slot) {
        int16_t floater_index = source->charge_floater_slots[slot];
        GameFloaterStart *linked;
        if (floater_index < 0 ||
            (unsigned int)floater_index >= session->floater_count) continue;
        linked = &session->floaters[(unsigned int)floater_index];
        if (!game_session_floater_is_active(linked) ||
            (linked->source_runtime_flags & 0x908U) != 0) continue;
        linked->source_runtime_flags |= 0x2000U;
        linked->source_death_timer = 0;
        ++affected;
    }
    return affected;
}

unsigned int game_session_apply_cast_blast(
    GameSession *session, unsigned int caster_index)
{
    GameFloaterStart *caster;
    int32_t level;
    int32_t radius;
    int32_t base_amount;
    unsigned int affected;

    if (session == NULL || caster_index >= session->floater_count) return 0;
    caster = &session->floaters[caster_index];
    if (caster->island_index >= session->island_count) return 0;
    /* FUN_004239e9 case 7 scales a 0x11 base and radius by caster level. */
    level = caster->attack_level_flags & 0x0fU;
    radius = level * 0x32 + 200;
    base_amount = level * 5 + 0x11;
    affected = game_session_apply_cast_area_damage(
        session, caster_index, radius, base_amount);

    /* FUN_004239e9 case 7 calls FUN_004204bc with the caster's current HP,
       making the area cast consume its caster as part of the impact. */
    if (caster->current_hit_points > 0) {
        caster->current_hit_points = 0;
        caster->source_runtime_flags |= 0x008U;
        caster->source_death_timer = 0;
        record_floater_death(session, caster, caster->type_index);
        ++affected;
    }
    return affected;
}

unsigned int game_session_resolve_cast_effect_step(
    GameSession *session, const PadCatalog *catalog,
    unsigned int caster_index, uint8_t step,
    int16_t target_location_index)
{
    GameFloaterStart *caster;
    const GameRuntimeLocation *target;

    if (session == NULL || caster_index >= session->floater_count) return 0;
    caster = &session->floaters[caster_index];
    if (step == 0) {
        unsigned int slot;
        unsigned int healed = 0;
        GameRuntimeLocation *source;

        if (caster->cast_spell_kind != 0) return 0;
        caster->source_runtime_flags |= 0x200U;
        if (caster->owner_slot >= GAME_START_PLAYER_COUNT ||
            caster->source_link_0c < 0 ||
            caster->charge_source_island >= session->island_count ||
            caster->charge_source_location >=
                session->islands[caster->charge_source_island].location_count)
            return 1;

        source = &session->islands[caster->charge_source_island]
            .locations[caster->charge_source_location];
        if (source->owner_id != (int32_t)caster->owner_slot ||
            source->source_location_slot_18 != caster->source_link_0c)
            return 1;

        /* FUN_004239e9 case 0 follows the caster's +0x18 source record and
           heals each linked floater by (level + 2) / 4 of its maximum HP. */
        for (slot = 0; slot < 8; ++slot) {
            int16_t target_index = source->charge_floater_slots[slot];
            GameFloaterStart *target;
            int32_t maximum;
            uint32_t restored;

            if (target_index < 0 ||
                (unsigned int)target_index >= session->floater_count) continue;
            target = &session->floaters[(unsigned int)target_index];
            maximum = target->max_hit_points;
            if (!game_session_floater_is_active(target) || maximum <= 0 ||
                target->current_hit_points >= maximum) continue;

            caster->order_target_floater = target_index;
            restored = (uint32_t)target->current_hit_points +
                (((uint32_t)(caster->attack_level_flags & 0x000fU) + 2U) *
                 (uint32_t)maximum >> 2);
            if (restored > (uint32_t)maximum) restored = (uint32_t)maximum;
            target->current_hit_points = (int16_t)restored;
            if ((target->source_runtime_flags & 0x908U) == 0) {
                target->source_runtime_flags |= 0x2000U;
                target->source_death_timer = 0;
            }
            ++healed;
        }
        return healed + 1U;
    }
    if (step == 1) {
        GameRuntimeIsland *island;
        GameRuntimeLocation *target_site;
        int32_t radius;
        unsigned int location_index;
        unsigned int affected = 0;

        if (caster->cast_spell_kind != 1 ||
            caster->island_index >= session->island_count ||
            target_location_index < 0 ||
            (uint16_t)target_location_index >=
                session->islands[caster->island_index].location_count) return 0;
        caster->source_runtime_flags |= 0x200U;
        island = &session->islands[caster->island_index];
        target_site = &island->locations[(uint16_t)target_location_index];
        radius = (int32_t)(caster->attack_level_flags & 0x000fU) * 50 + 0xaf;
        for (location_index = 0; location_index < island->location_count;
             ++location_index) {
            GameRuntimeLocation *site = &island->locations[location_index];
            int32_t dx;
            int32_t dy;

            /* FUN_004239e9 case 1 accepts raw item IDs 10..21 and uses a
               strict Chebyshev radius around the selected site's +0x32. */
            if (site->record_value_10 <= 9 || site->record_value_10 >= 22)
                continue;
            dx = (int32_t)site->x - target_site->x;
            dy = (int32_t)site->y - target_site->y;
            if (dx < 0) dx = -dx;
            if (dy < 0) dy = -dy;
            if ((dx > dy ? dx : dy) >= radius) continue;

            /* FUN_00453ade starts the 0x100/+0x44 site state and immediately
               recalculates its active bit. */
            site->source_flags |= 0x100U;
            site->source_value_44 = 0;
            ++affected;
        }
        if (affected != 0)
            (void)game_session_recalculate_active_locations(session);
        return affected;
    }
    if (step == 2) {
        unsigned int floater_index;
        unsigned int healed = 0;
        unsigned int limit;
        uint32_t level;

        if (caster->cast_spell_kind != 2 ||
            caster->owner_slot >= GAME_START_PLAYER_COUNT) return 0;
        caster->source_runtime_flags |= 0x200U;
        level = caster->attack_level_flags & 0x000fU;
        limit = (level + 1U) * 5U;
        /* FUN_004239e9 case 2 scans the owner's roster in native slot order,
           restores subtype-0 floaters to their resolved max HP, and caps the
           number treated at five times (level + 1). */
        for (floater_index = 0; floater_index < session->floater_count;
             ++floater_index) {
            GameFloaterStart *target = &session->floaters[floater_index];
            if (!game_session_floater_is_active(target) ||
                target->owner_slot != caster->owner_slot ||
                target->source_subtype != 0 ||
                target->current_hit_points >= target->max_hit_points) continue;
            target->current_hit_points = target->max_hit_points;
            if ((target->source_runtime_flags & 0x908U) == 0) {
                target->source_runtime_flags |= 0x2000U;
                target->source_death_timer = 0;
            }
            ++healed;
            if (healed >= limit) break;
        }
        return healed + 1U;
    }
    if (step == 0x11) {
        GameRuntimeIsland *island;
        unsigned int location_index;
        unsigned int affected = 0;

        if (caster->cast_spell_kind != 0x11 ||
            caster->island_index >= session->island_count) return 0;
        island = &session->islands[caster->island_index];
        for (location_index = 0; location_index < island->location_count;
             ++location_index) {
            GameRuntimeLocation *site = &island->locations[location_index];

            /* FUN_004239e9 case 0x11 affects every raw item ID 6..9 on the
               caster's island, without filtering by owner or distance. */
            if (site->record_value_10 <= 5 || site->record_value_10 >= 10)
                continue;
            site->source_flags |= 0x100U;
            site->source_value_44 = 0;
            ++affected;
        }
        caster->source_runtime_flags |= 0x200U;
        if (affected != 0)
            (void)game_session_recalculate_active_locations(session);
        return affected;
    }
    if (step == 0x10) {
        GameRuntimeLocation *site;
        if (caster->cast_spell_kind != 0x10 ||
            caster->island_index >= session->island_count ||
            target_location_index < 0 ||
            (uint16_t)target_location_index >=
                session->islands[caster->island_index].location_count) return 0;
        caster->source_runtime_flags |= 0x200U;
        site = &session->islands[caster->island_index]
                    .locations[(uint16_t)target_location_index];
        /* FUN_004239e9 case 0x10 forwards the selected type-6..9 site's own
           +0x34 to FUN_00450847, draining that value and destroying it. */
        if (site->record_value_10 <= 5 || site->record_value_10 >= 10)
            return 0;
        return game_session_apply_cast_site_effect(
            session, caster->island_index, (uint16_t)target_location_index,
            site->source_value_34);
    }
    if (step == 4 || step == 5 || step == 6) {
        GameRuntimeLocation *site;
        uint32_t level;
        if (caster->cast_spell_kind != step ||
            caster->island_index >= session->island_count ||
            target_location_index < 0 ||
            (uint16_t)target_location_index >=
                session->islands[caster->island_index].location_count) return 0;
        site = &session->islands[caster->island_index]
                    .locations[(uint16_t)target_location_index];
        level = (uint32_t)(caster->attack_level_flags & 0x000fU);
        /* FUN_00453b09 is shared by kinds 4..6: set site bit 0x200 and store
           (level + 1) * 1000 at +0x38; FUN_00450a71 clears it on expiry. */
        site->source_flags |= 0x200U;
        site->source_effect_timer_38 = (level + 1U) * 1000U;
        caster->source_runtime_flags |= 0x200U;
        return 1;
    }
    if (step == 7) {
        if (caster->cast_spell_kind != 7) return 0;
        caster->source_runtime_flags |= 0x200U;
        return game_session_apply_cast_blast(session, caster_index);
    }
    if (step == 0x12) {
        unsigned int affected;
        if (caster->cast_spell_kind != 0x12 ||
            caster->island_index >= session->island_count) return 0;
        /* Kind 0x12 uses a fixed 250 Chebyshev radius and base 17 damage;
           its cast animation is centered on the caster, not the target site. */
        affected = game_session_apply_cast_area_damage(
            session, caster_index, 250, 17);
        caster->source_runtime_flags &= ~0x100U;
        caster->source_runtime_flags |= 0x200U;
        return affected;
    }
    if (step == 0x13) {
        GameRuntimeLocation *site;
        int32_t owner;
        int16_t record_slot;
        uint32_t level;
        unsigned int slot;
        unsigned int affected = 0;

        if (caster->cast_spell_kind != 0x13 ||
            caster->island_index >= session->island_count ||
            target_location_index < 0 ||
            (uint16_t)target_location_index >=
                session->islands[caster->island_index].location_count) return 0;
        caster->source_runtime_flags |= 0x200U;
        site = &session->islands[caster->island_index]
                    .locations[(uint16_t)target_location_index];
        owner = site->source_value_14;
        record_slot = site->source_location_slot_18;
        /* FUN_00450385 resolves the selected site's player row and +0x18
           record. The native code has no bounds checks; keep malformed links
           from indexing outside the remake's modeled table. */
        if (owner < 0 || owner >= GAME_START_PLAYER_COUNT ||
            record_slot < 0 || record_slot >= GAME_SOURCE_RECORDS_PER_PLAYER)
            return 0;

        level = caster->attack_level_flags & 0x000fU;
        /* FUN_00453bb6 sets site bit 0x20000 and the shared +0x38 timer. */
        site->source_flags |= 0x20000U;
        site->source_effect_timer_38 = level * 500U + 1000U;

        /* FUN_0045d53c pulses each linked floater that is not dying or in
           either excluded state; +0x24 is shared with the death counter. */
        for (slot = 0; slot < 8; ++slot) {
            int16_t floater_index = site->charge_floater_slots[slot];
            GameFloaterStart *linked;
            if (floater_index < 0 ||
                (unsigned int)floater_index >= session->floater_count) continue;
            linked = &session->floaters[(unsigned int)floater_index];
            if (!game_session_floater_is_active(linked) ||
                (linked->source_runtime_flags & 0x908U) != 0) continue;
            linked->source_runtime_flags |= 0x2000U;
            linked->source_death_timer = 0;
            ++affected;
        }
        return affected + 1U;
    }
    if (step == 0x14) {
        if (caster->cast_spell_kind != 0x14 ||
            caster->island_index >= session->island_count) return 0;
        /* FUN_004239e9 case 0x14 starts the island's 22-tick Leviathan timer,
           then reevaluates its category-4 floaters. The movement tick runs
           after this effect callback and performs that same reevaluation. */
        caster->source_runtime_flags |= 0x200U;
        session->islands[caster->island_index].leviathan_periodic_timer = 0x16;
        return 1;
    }
    if (step == 0x15) {
        unsigned int floater_index;
        unsigned int affected = 0;
        uint32_t level;
        if (caster->cast_spell_kind != 0x15 ||
            caster->owner_slot >= GAME_START_PLAYER_COUNT) return 0;

        level = caster->attack_level_flags & 0x000fU;
        /* FUN_004239e9 stores level*1000+1000 in the owner's speed timer. */
        session->economy[caster->owner_slot].floater_speed_boost_timer =
            (int16_t)(level * 1000U + 1000U);
        /* The native owner query includes all islands; only subtype-0 floaters
           without the excluded flags receive the temporary pulse. */
        for (floater_index = 0; floater_index < session->floater_count;
             ++floater_index) {
            GameFloaterStart *target = &session->floaters[floater_index];
            if (!game_session_floater_is_active(target) ||
                target->owner_slot != caster->owner_slot ||
                target->source_subtype != 0 ||
                (target->source_runtime_flags & 0x908U) != 0) continue;
            target->source_runtime_flags |= 0x2000U;
            target->source_death_timer = 0;
            ++affected;
        }
        caster->source_runtime_flags |= 0x200U;
        return affected + 1U;
    }
    if (step == 0x0c || step == 0x0d) {
        GameRuntimeLocation *source;
        uint32_t level;
        uint32_t flag = step == 0x0c ? 0x8000U : 0x10000U;

        if (caster->cast_spell_kind != step) return 0;
        caster->source_runtime_flags |= 0x200U;
        source = game_session_cast_source_site(session, caster);
        if (source == NULL) return 0;
        level = caster->attack_level_flags & 0x000fU;
        /* FUN_00453b38/00453b76 set distinct timed source flags; both then
           pulse every linked floater through FUN_0045d53c. */
        source->source_flags |= flag;
        source->source_effect_timer_38 = level * 500U + 1000U;
        return game_session_pulse_cast_source_floaters(session, source) + 1U;
    }
    if (step == 0x0e) {
        unsigned int floater_index;
        unsigned int affected = 0;
        uint32_t level;

        if (caster->cast_spell_kind != 0x0e ||
            caster->owner_slot >= GAME_START_PLAYER_COUNT) return 0;
        caster->source_runtime_flags |= 0x200U;
        level = caster->attack_level_flags & 0x000fU;
        /* FUN_004239e9 case 0xe marks eligible owned subtype-0 floaters;
           at level 2 it adds both source flags, and always resets +0x24. */
        for (floater_index = 0; floater_index < session->floater_count;
             ++floater_index) {
            GameFloaterStart *target = &session->floaters[floater_index];
            if (!game_session_floater_is_active(target) ||
                target->owner_slot != caster->owner_slot ||
                target->source_subtype != 0 ||
                (target->source_runtime_flags & 0x808U) != 0) continue;
            if (level < 2U) target->source_runtime_flags |= 0x100U;
            else if (level == 2U)
                target->source_runtime_flags |= 0x1100U;
            target->source_death_timer = 0;
            ++affected;
        }
        return affected + 1U;
    }
    if (step == 0x0f) {
        GameRuntimeLocation *source;
        unsigned int slot;
        unsigned int affected = 0;
        int32_t multiplier;

        if (caster->cast_spell_kind != 0x0f) return 0;
        caster->source_runtime_flags |= 0x200U;
        source = game_session_cast_source_site(session, caster);
        if (source == NULL) return 0;
        multiplier = (int32_t)(caster->attack_level_flags & 0x000fU) + 3;
        /* FUN_004239e9 case 0xf multiplies each linked floater's +0x2a,
           capped at four times its raw max-attack-points catalog value. */
        for (slot = 0; slot < 8; ++slot) {
            int16_t floater_index = source->charge_floater_slots[slot];
            GameFloaterStart *linked;
            int32_t value;
            int32_t maximum;
            if (floater_index < 0 ||
                (unsigned int)floater_index >= session->floater_count) continue;
            linked = &session->floaters[(unsigned int)floater_index];
            if (!game_session_floater_is_active(linked) ||
                linked->owner_slot >= GAME_START_PLAYER_COUNT ||
                linked->source_subtype > 8U) continue;
            value = (int16_t)((uint32_t)(uint16_t)linked->charge_current *
                              (uint32_t)multiplier);
            maximum = (int32_t)linked->base_max_attack_points * 4;
            if (maximum < value) value = maximum;
            linked->charge_current = (int16_t)value;
            if ((linked->source_runtime_flags & 0x908U) == 0) {
                linked->source_runtime_flags |= 0x2000U;
                linked->source_death_timer = 0;
            }
            ++affected;
        }
        return affected + 1U;
    }
    if (step == 0x0a) {
        int16_t target_index;
        GameFloaterStart *target_floater;

        if (caster->cast_spell_kind != 0x0a) return 0;
        caster->source_runtime_flags |= 0x200U;
        target_index = caster->order_target_floater;
        if (target_index < 0 ||
            (unsigned int)target_index >= session->floater_count) return 0;
        target_floater = &session->floaters[(unsigned int)target_index];
        /* FUN_004239e9 case 0xa only calls FUN_004204bc for owner/faction 4,
           passing the target's full current HP so the target dies at impact. */
        if (!game_session_floater_is_active(target_floater) ||
            target_floater->owner_slot != 4U) return 0;
        if (target_floater->current_hit_points > 0) {
            target_floater->current_hit_points = 0;
            target_floater->source_runtime_flags |= 0x008U;
            target_floater->source_death_timer = 0;
            record_floater_death(session, target_floater, caster->type_index);
            return 2;
        }
        return 1;
    }
    if (step == 0x0b) {
        GameRuntimeLocation *source;
        unsigned int slot;
        unsigned int affected = 0;
        uint32_t multiplier;

        if (caster->cast_spell_kind != 0x0b) return 0;
        caster->source_runtime_flags |= 0x200U;
        source = game_session_cast_source_site(session, caster);
        if (source == NULL) return 0;
        multiplier = (uint32_t)(caster->attack_level_flags & 0x000fU) + 1U;
        /* FUN_004239e9 case 0xb multiplies each linked floater's charge by
           level + 1, then caps it at twice FUN_00420f28's max-HP result. */
        for (slot = 0; slot < 8; ++slot) {
            int16_t floater_index = source->charge_floater_slots[slot];
            GameFloaterStart *linked;
            int32_t value;
            int32_t maximum;

            if (floater_index < 0 ||
                (unsigned int)floater_index >= session->floater_count) continue;
            linked = &session->floaters[(unsigned int)floater_index];
            if (!game_session_floater_is_active(linked) ||
                linked->owner_slot >= GAME_START_PLAYER_COUNT ||
                linked->max_hit_points <= 0) continue;

            caster->order_target_floater = floater_index;
            value = (int16_t)((uint32_t)(uint16_t)linked->charge_current *
                              multiplier);
            maximum = (int32_t)linked->max_hit_points * 2;
            if (value > maximum) value = maximum;
            linked->charge_current = (int16_t)value;
            if ((linked->source_runtime_flags & 0x908U) == 0) {
                linked->source_runtime_flags |= 0x2000U;
                linked->source_death_timer = 0;
            }
            ++affected;
        }
        return affected + 1U;
    }
    if (step == 8) {
        GameRuntimeLocation *pit_object;
        int32_t item_id;
        uint16_t *inventory_count;
        if (caster->cast_spell_kind != 8 ||
            caster->owner_slot >= GAME_START_PLAYER_COUNT ||
            caster->island_index >= session->island_count ||
            target_location_index < 0 ||
            (uint16_t)target_location_index >=
                session->islands[caster->island_index].location_count) return 0;
        caster->source_runtime_flags |= 0x200U;
        pit_object = &session->islands[caster->island_index]
                          .locations[(uint16_t)target_location_index];
        if (pit_object->record_value_10 != 1) return 0;
        item_id = pit_object->record_value_24;
        if (item_id < 5 || item_id > 33) return 0;

        /* FUN_0045f075 increments the owner's short counter without a cap. */
        inventory_count = &session->economy[caster->owner_slot]
            .inventory_count[(unsigned int)(item_id -
                GAME_INVENTORY_ITEM_FIRST_ID)];
        *inventory_count = (uint16_t)(*inventory_count + 1U);
        game_session_clear_cast_site(session, caster->island_index,
            (uint16_t)target_location_index, pit_object);
        return 1;
    }
    if (step == 3) {
        GameRuntimeLocation *site;
        int32_t base_item_id;
        int16_t maximum;
        if (caster->cast_spell_kind != 3 ||
            caster->island_index >= session->island_count ||
            target_location_index < 0 ||
            (uint16_t)target_location_index >=
                session->islands[caster->island_index].location_count) return 0;
        caster->source_runtime_flags |= 0x200U;
        site = &session->islands[caster->island_index]
                    .locations[(uint16_t)target_location_index];
        base_item_id = game_session_base_item_id(site);
        /* FUN_004239e9 restores +0x34 from FUN_00450978 for item IDs
           0x26..0x34; its exact gameplay label is not established. */
        if (base_item_id < 0x26 || base_item_id > 0x34 || catalog == NULL ||
            !game_session_source_value_34_max(catalog, site, &maximum)) return 0;
        site->source_value_34 = maximum;
        return 1;
    }
    if ((step != 9 && step != 0x16) ||
        caster->island_index >= session->island_count ||
        target_location_index < 0 ||
        (uint16_t)target_location_index >=
            session->islands[caster->island_index].location_count) return 0;

    target = &session->islands[caster->island_index]
                  .locations[(uint16_t)target_location_index];
    if (step == 0x16) {
        /* FUN_004239e9 compares item-0x17 with DAT_0061a634[player]. All four
           loaded player entries are zero; runtime writers remain unknown. */
        caster->source_runtime_flags |= 0x200U;
        if (target->record_value_10 != 0x17) return 0;
        return game_session_apply_cast_site_effect(
            session, caster->island_index, (uint16_t)target_location_index,
            30000) != 0 ? 1U : 0U;
    }
    /* FUN_004239e9 completes kind 9 even when its selected site is
       ineligible; eligible targets have raw site +0x04 == 0. */
    caster->source_runtime_flags |= 0x200U;
    if (target->renderer_class != 0) return 0;
    return game_session_apply_cast_site_effect(
        session, caster->island_index, (uint16_t)target_location_index,
        target->source_value_34) != 0 ? 1U : 0U;
}

int game_session_schedule_cast_effect_step(
    GameSession *session, unsigned int caster_index, uint8_t step,
    int16_t target_location_index, uint8_t odd_updates_until_impact)
{
    unsigned int slot;

    if (session == NULL || caster_index >= session->floater_count ||
        (step != 0 && step != 1 && step != 2 && step != 3 && step != 4 && step != 5 && step != 6 &&
         step != 7 && step != 8 && step != 9 &&
         step != 0x0a && step != 0x0b && step != 0x0c && step != 0x0d && step != 0x0e && step != 0x0f &&
         step != 0x10 &&
         step != 0x11 && step != 0x12 && step != 0x13 &&
         step != 0x14 && step != 0x15 && step != 0x16) ||
        (odd_updates_until_impact == 0 && step != 0x16) ||
        (unsigned int)session->active_cast_effect_count +
                session->active_attack_effect_count >=
            GAME_SESSION_MAX_CAST_EFFECTS) {
        return 0;
    }
    if (step == 1 || step == 3 || step == 4 || step == 5 || step == 6 ||
        step == 8 || step == 0x10 || step == 0x12 || step == 0x13) {
        const GameFloaterStart *caster = &session->floaters[caster_index];
        if (caster->island_index >= session->island_count ||
            target_location_index < 0 ||
            (uint16_t)target_location_index >=
                session->islands[caster->island_index].location_count) {
            return 0;
        }
    } else if (step == 9) {
        const GameFloaterStart *caster = &session->floaters[caster_index];
        if (caster->island_index >= session->island_count ||
            target_location_index < 0 ||
            (uint16_t)target_location_index >=
                session->islands[caster->island_index].location_count ||
            /* FUN_004239e9's kind-9 target guard is renderer class zero. */
            session->islands[caster->island_index]
                .locations[(uint16_t)target_location_index].renderer_class != 0) {
            return 0;
        }
    } else if (step == 0x16) {
        const GameFloaterStart *caster = &session->floaters[caster_index];
        if (caster->island_index >= session->island_count ||
            target_location_index < 0 ||
            (uint16_t)target_location_index >=
                session->islands[caster->island_index].location_count) {
            return 0;
        }
    } else {
        target_location_index = -1;
    }

    for (slot = 0; slot < GAME_SESSION_MAX_CAST_EFFECTS; ++slot) {
        struct GameCastEffectState *effect = &session->cast_effects[slot];
        if (effect->active) continue;
        effect->active = 1;
        effect->caster_index = (uint8_t)caster_index;
        effect->step = step;
        effect->odd_updates_remaining = odd_updates_until_impact;
        effect->target_location_index = target_location_index;
        effect->animation_phase = 0;
        effect->phase_odd_updates_remaining = 0;
        effect->effect_x = session->floaters[caster_index].x;
        effect->effect_y = session->floaters[caster_index].y;
        if (step == 0x16 && odd_updates_until_impact == 0) {
            /* TONE00.COB effects.txt: ASCEND has 42 frames. FUN_00415063
               checks completion only after advancing once past the last. */
            effect->animation_phase = 1;
            effect->phase_odd_updates_remaining = 43;
        }
        ++session->active_cast_effect_count;
        return 1;
    }
    return 0;
}

void game_session_tick_cast_effects(GameSession *session,
                                    uint32_t source_tick,
                                    const PadCatalog *catalog)
{
    unsigned int slot;

    if (session == NULL) return;
    for (slot = 0; slot < GAME_SESSION_MAX_CAST_EFFECTS; ++slot) {
        struct GameCastEffectState *effect = &session->cast_effects[slot];
        if (!effect->active) continue;
        if (effect->animation_phase == 0) {
            if ((source_tick & 1U) == 0) continue;
            if (effect->odd_updates_remaining > 0)
                --effect->odd_updates_remaining;
            if (effect->odd_updates_remaining != 0) continue;
        } else if (effect->animation_phase == 1) {
            if ((source_tick & 1U) == 0) continue;
            if (effect->phase_odd_updates_remaining > 0)
                --effect->phase_odd_updates_remaining;
            if (effect->phase_odd_updates_remaining != 0) continue;
            effect->animation_phase = 2;
            continue;
        } else if (effect->animation_phase == 2) {
            const GameFloaterStart *caster =
                &session->floaters[effect->caster_index];
            const GameRuntimeIsland *island;
            int32_t dx;
            int32_t dy;
            double distance;

            if (caster->island_index >= session->island_count ||
                effect->target_location_index < 0 ||
                (uint16_t)effect->target_location_index >=
                    session->islands[caster->island_index].location_count) {
                effect->animation_phase = 3;
                continue;
            }
            island = &session->islands[caster->island_index];
            dx = (int32_t)island->locations[
                (uint16_t)effect->target_location_index].x - effect->effect_x;
            dy = (int32_t)island->locations[
                (uint16_t)effect->target_location_index].y - effect->effect_y;
            distance = sqrt((double)dx * dx + (double)dy * dy);
            /* The UPGRADE descriptor uses SPEED 8. FUN_0041511b advances
               along the normalized vector, rounding each coordinate via
               source __ftol, then FUN_004672a6 tests Chebyshev distance. */
            if (distance <= 8.0) {
                effect->effect_x = island->locations[
                    (uint16_t)effect->target_location_index].x;
                effect->effect_y = island->locations[
                    (uint16_t)effect->target_location_index].y;
            } else {
                effect->effect_x = (uint16_t)((int32_t)effect->effect_x +
                    cast_round_to_even((double)dx * 8.0 / distance));
                effect->effect_y = (uint16_t)((int32_t)effect->effect_y +
                    cast_round_to_even((double)dy * 8.0 / distance));
            }
            dx = (int32_t)island->locations[
                (uint16_t)effect->target_location_index].x - effect->effect_x;
            dy = (int32_t)island->locations[
                (uint16_t)effect->target_location_index].y - effect->effect_y;
            if ((dx < 0 ? -dx : dx) < 6 && (dy < 0 ? -dy : dy) < 6)
                effect->animation_phase = 3;
            continue;
        } else if ((source_tick & 1U) == 0) {
            continue;
        }

        (void)game_session_resolve_cast_effect_step(
            session, catalog, effect->caster_index, effect->step,
            effect->target_location_index);
        effect->active = 0;
        if (session->active_cast_effect_count > 0)
            --session->active_cast_effect_count;
    }
}

#include "game_session.h"
#include "game_session_combat_internal.h"

void game_session_start_attack_effect(GameSession *session,
                                     GameFloaterStart *attacker,
                                     int32_t damage)
{
    unsigned int level;
    uint8_t frame_count;

    if (session == NULL || attacker == NULL || damage <= 0 ||
        (unsigned int)session->active_attack_effect_count +
                session->active_cast_effect_count >= 32U ||
        attacker->attack_effect_active) return;
    level = (unsigned int)(damage / 2);
    if (level >= 4U) level = 3U;
    frame_count = attacker->attack_impact_frame_counts[level];
    if (frame_count == 0) return;
    attacker->attack_effect_active = 1;
    /* FUN_00415063 tests completion only after stepping past the last frame. */
    attacker->attack_effect_odd_updates_remaining = (uint8_t)(frame_count + 1U);
    ++session->active_attack_effect_count;
}

void game_session_tick_combat_effects(GameSession *session,
                                     uint32_t source_tick)
{
    unsigned int i;

    if (session == NULL || (source_tick & 1U) == 0) return;
    for (i = 0; i < session->floater_count; ++i) {
        GameFloaterStart *floater = &session->floaters[i];
        if (!game_session_floater_is_active(floater) ||
            !floater->attack_effect_active) continue;
        if (floater->attack_effect_odd_updates_remaining > 0)
            --floater->attack_effect_odd_updates_remaining;
        if (floater->attack_effect_odd_updates_remaining == 0) {
            floater->attack_effect_active = 0;
            if (session->active_attack_effect_count > 0)
                --session->active_attack_effect_count;
        }
    }
}
