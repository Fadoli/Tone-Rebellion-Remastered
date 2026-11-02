#include "game_session.h"
#include "game_session_combat_internal.h"
#include "game_session_action9.h"
#include "game_session_events.h"
#include "game_session_internal.h"
#include "game_session_delivery_internal.h"

#include <math.h>
#include <stdint.h>
#include <string.h>

enum { GAME_FLOATER_STATE_ATTACK = 6, GAME_FLOATER_STATE_ATTACK_SITE = 7 };

static void record_floater_death(GameSession *session,
                                 const GameFloaterStart *floater,
                                 int32_t killer_faction)
{
    if (session == NULL || floater == NULL) return;
    /* FUN_00416a9a selects levdeath for raw type 4, fltdeath otherwise, and
       tags the instance with the floater's island. */
    if (game_session_queue_audio_event_at(session,
            GAME_SESSION_AUDIO_FLOATER_DEATH, (int16_t)floater->type_index,
            floater->island_index))
        game_session_set_last_audio_x(session, floater->x);
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

/* FUN_004204bc: an already dying floater (flag 0x8) is left alone; otherwise
   the amount is subtracted and a result below 1 starts the death state with
   its sound and tallies (ev_2016a3eb). Hit points are kept at 0 rather than
   negative, as in game_session_damage_floater. */
void game_session_apply_floater_damage(GameSession *session,
                                       GameFloaterStart *floater,
                                       int32_t amount,
                                       int32_t killer_faction)
{
    int32_t hit_points;

    if (session == NULL || floater == NULL ||
        (floater->source_runtime_flags & 0x008U) != 0) return;
    hit_points = (int32_t)floater->current_hit_points - amount;
    if (hit_points >= 1) {
        floater->current_hit_points = (int16_t)hit_points;
        return;
    }
    floater->current_hit_points = 0;
    floater->source_runtime_flags |= 0x008U;
    floater->source_death_timer = 0;
    record_floater_death(session, floater, killer_faction);
}

int32_t game_session_resolve_attack_hit(GameSession *session,
                                        unsigned int floater_index,
                                        uint8_t state, int target_floater,
                                        int target_location)
{
    GameFloaterStart *floater;
    int32_t damage = 0;

    if (session == NULL || floater_index >= session->floater_count) return 0;
    floater = &session->floaters[floater_index];
    /* FUN_0041e569 calls FUN_004200d2 / FUN_00420188 with ECX = the attacker
       and the target as argument (call site 0x41ec64, ev_89fd8492); both
       bump the attacker's +0x08 on a positive hit and consume one attacker
       charge (+0x22) per attempt (ev_7eebf882, ev_8a27f55e). */
    if (state == GAME_FLOATER_STATE_ATTACK && target_floater >= 0 &&
        (unsigned int)target_floater < session->floater_count) {
        damage = game_session_damage_floater(session, floater_index,
                                             (unsigned int)target_floater);
    } else if (state == GAME_FLOATER_STATE_ATTACK_SITE &&
               floater->island_index < session->island_count &&
               target_location >= 0 &&
               (uint16_t)target_location <
                   session->islands[floater->island_index].location_count) {
        GameRuntimeLocation *target =
            &session->islands[floater->island_index].locations[
                (uint16_t)target_location];
        damage = game_session_damage_site(session, floater_index,
            floater->island_index, (uint16_t)target_location, target);
    } else {
        return 0;
    }
    if (damage > 0) ++floater->source_progress_08;
    if (floater->charge_current > 0) --floater->charge_current;
    return damage;
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
        uint16_t impact_x = floater->x;
        uint16_t impact_y = floater->y;
        int target_floater = -1;
        int target_site = -1;
        /* FUN_0041e569 path A: FUN_004207c2() == 0 (category 4 or a charged
           nonzero subtype) with an atteff def spawns that effect instead of
           the realm IMPACT, whether or not the hit lands. */
        int uses_atteff = floater->type_index == 4U ||
            (floater->source_subtype != 0 && floater->charge_current > 0);
        if (state == GAME_FLOATER_STATE_ATTACK &&
            floater->order_target_floater >= 0 &&
            (unsigned int)floater->order_target_floater < session->floater_count) {
            target_floater = floater->order_target_floater;
            impact_x = session->floaters[target_floater].x;
            impact_y = session->floaters[target_floater].y;
        } else if (state == GAME_FLOATER_STATE_ATTACK_SITE &&
                   floater->island_index < session->island_count &&
                   floater->order_target_location >= 0 &&
                   (uint16_t)floater->order_target_location <
                       session->islands[floater->island_index].location_count) {
            const GameRuntimeLocation *site = &session->islands[
                floater->island_index].locations[
                    (uint16_t)floater->order_target_location];
            target_site = floater->order_target_location;
            impact_x = site->x;
            impact_y = site->y;
        }
        if (uses_atteff && (target_floater >= 0 || target_site >= 0) &&
            !floater->attack_effect_active &&
            game_session_spawn_attack_visual(session, floater,
                (int)floater_index, state, impact_x, impact_y, 0)) {
            /* FUN_00416ff8 resolves the hit when the effect arrives; the
               attacker keeps its attack state until the slot is gone. */
            floater->attack_effect_active = 1;
            floater->attack_effect_hidden = 1;
            floater->attack_effect_waits_visual = 1;
            ++session->active_attack_effect_count;
        } else {
            damage = game_session_resolve_attack_hit(session, floater_index,
                state, target_floater, target_site);
            if (damage > 0)
                game_session_start_attack_effect(session, floater, damage,
                                                 impact_x, impact_y);
        }
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
   behind subtracts it, the opposite realm adds (V / C - 0.5) * term with
   V / C = DAT_00618e4c / 10000 for an odd attacker realm, else
   DAT_00618e50 / 8000, negated when the attacker realm is above 1
   (ev_d4bb6e22). attack_realm -1 means "same as the target", which removes
   the realm term. */
static int32_t native_hit_chance(const GameSession *session,
                                 int32_t attack_power,
                                 int32_t attack_realm, int32_t defense_power,
                                 int32_t target_realm)
{
    uint8_t difficulty = session->config.difficulty;
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
        double correction = ((attack_realm & 1) != 0
            ? (double)session->realm_cycle_a / 10000.0
            : (double)session->realm_cycle_b / 8000.0) - 0.5;
        correction *= term;
        if (attack_realm > 1) correction = -correction;
        score += correction;
    }
    return (int32_t)((60.0 * score) / 14.0) + 10;
}

/* FUN_0042003c(subtype): the realm column (+2) of FUN_00464242(type,
   subtype), then +1 (wrapping 3 -> 0) when the linked source has flag
   0x10000, else -1 (wrapping 0 -> 3) with flag 0x20000 (ev_d094e67f).
   FUN_004200d2 passes subtype 0 for an attacker FUN_004207c2 accepts, i.e.
   anything but category 4 or a charged nonzero subtype (ev_7eebf882). */
static int32_t floater_combat_realm(const GameSession *session,
                                    const GameFloaterStart *floater,
                                    int attacker_rule)
{
    int32_t realm = floater->attack_realm;

    if (attacker_rule && floater->type_index < GAME_START_PLAYER_COUNT &&
        !(floater->source_subtype != 0 && floater->charge_current > 0))
        realm = session->worker_birth_stats[floater->type_index].attack_realm;
    if (floater->source_link_0c >= 0 &&
        floater->charge_source_island < session->island_count &&
        floater->charge_source_location <
            session->islands[floater->charge_source_island].location_count) {
        const GameRuntimeLocation *source = &session->islands[
            floater->charge_source_island].locations[
                floater->charge_source_location];
        if ((source->source_flags & 0x10000U) != 0) {
            if (++realm > 3) realm = 0;
        } else if ((source->source_flags & 0x20000U) != 0) {
            if (--realm < 0) realm = 3;
        }
    }
    return realm & 3;
}

static int floater_attack_hits(GameSession *session,
                               const GameFloaterStart *attacker,
                               const GameFloaterStart *target,
                               int32_t attack_power)
{
    int32_t attack_realm = floater_combat_realm(session, attacker, 1);
    int32_t target_realm = floater_combat_realm(session, target, 0);
    int32_t defense_power = (target->source_subtype == 0 ||
                             target->source_subtype == 9)
        ? 0 : floater_attack_power(session, target);

    if ((target->source_runtime_flags & 0x108U) != 0) return 0;
    /* FUN_00420217 treats a subtype-9 target as sharing the attacker realm. */
    if (target->source_subtype == 9) target_realm = attack_realm;
    return tone_rng_bounded(&session->random_state, 100) <
        native_hit_chance(session, attack_power,
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
    chance = native_hit_chance(session, attack_power, -1,
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

/* FUN_00450847 queues message 7 with (island << 16) | site; the island view
   (FUN_0042fa0f message 5) turns it into FUN_00416a9a world event 7, the
   SoundOnly CRUMBLE effect, for the viewed island only. The audible-event
   filter applies that island gate. */
static void mark_site_destroyed(GameSession *session,
                                GameRuntimeLocation *target,
                                uint8_t island_index)
{
    target->source_flags |= 0x80U;
    target->source_value_48 = 0;
    (void)game_session_queue_effect_sound(session,
        game_session_effect_def_index(session, "CRUMBLE"), island_index,
        target->x);
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
            /* FUN_00450847 routes an exhausted PIT_Object through
               FUN_00452ae7, as the cast resolver does. */
            game_session_destroy_site(session, island_index, location_index, target);
        }
        return 1;
    }

    target->source_value_34 = (int16_t)(target->source_value_34 - damage);
    if (target->source_value_34 < 1) {
        if (item_id == 5) {
            game_session_destroy_site(session, island_index, location_index, target);
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

/* FUN_00452ae7 queues message 8 with (island << 16) | site, runs
   FUN_0045efd2 for an owned site (not modeled), then FUN_00452a15. The island
   view (FUN_0042fa0f message 5) only drops that site's selection. */
void game_session_destroy_site(GameSession *session, uint8_t island_index,
                               uint16_t location_index,
                               GameRuntimeLocation *target)
{
    (void)game_session_queue_world_event(session,
        GAME_SESSION_WORLD_EVENT_BUILDING_DESTROYED, island_index,
        (int32_t)(((uint32_t)island_index << 16) | (uint32_t)location_index));
    game_session_clear_cast_site(session, island_index, location_index, target);
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
            /* FUN_00452ae7 queues world event 8, then FUN_00452a15 clears
               the placed runtime object. */
            game_session_destroy_site(session, island_index, location_index, target);
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
            game_session_destroy_site(session, island_index, location_index, target);
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
        /* FUN_004239e9 compares item-0x17 with DAT_0061a634[owner], the
           word P+0x147c = 0x146c + 2 * 8: FUN_004204bc's kill counter for
           subtype 8, so seal k breaks only after k such kills. */
        caster->source_runtime_flags |= 0x200U;
        if (caster->type_index >= GAME_START_PLAYER_COUNT ||
            target->record_value_10 - 0x17 != (int32_t)session->economy[
                caster->type_index].leviathan_kills_by_subtype[8]) return 0;
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

/* FUN_0041760b (ev_821b6030, ev_9605cef5): effects.txt pass lengths in odd
   updates (LEVELFRAMES frame counts) and travel SPEEDs. The loader
   FUN_004153b8 stores SPEED 5 for a def without a SPEED line. */
static unsigned int cast_start_pass_length(uint8_t step, uint8_t owner)
{
    static const uint8_t frames[10] = { 17, 16, 17, 24, 15, 8, 17, 17, 4, 42 };
    int id = game_session_cast_sound_id(step, owner);
    return id >= 0 && id < 10 ? frames[id] : 17U;
}

/* The phase 0x400 sprite by spell, or -1 for a spell applied after its
   start pass. Spells 5, 6 and 9 play their second LEVELFRAMES level. */
static int cast_finish_pass_length(uint8_t step)
{
    switch (step) {
    case 0: return 17;          /* REPAIR */
    case 1: return 15;          /* FLTARMOR */
    case 3: return 9;           /* STOCKUP */
    case 4: return 18;          /* BLDARMOR */
    case 5: return 21;          /* LOCPROT 2..22 */
    case 6: return 31;          /* BUILDTON 2..32 */
    case 7: case 0x12: return 17; /* BLASTWB, no travel */
    case 9: return 16;          /* HYPERHEAL 8..23 */
    case 0x0b: return 17;       /* REVPLOT */
    case 0x0c: return 15;       /* FASTFLT */
    case 0x0d: case 0x13: return 17; /* FREEZESC (0x13 backwards) */
    case 0x0f: return 17;       /* BLASTWB */
    default: return -1;
    }
}

static int cast_travel_speed(uint8_t step)
{
    switch (step) {
    case 1: return 15;          /* FREEZELB */
    case 5: case 6: return 5;   /* LOCPROT, BUILDTON: loader default */
    case 9: return 20;          /* HYPERHEAL */
    default: return 8;          /* UPGRADE */
    }
}

int game_session_schedule_cast_effect_step(
    GameSession *session, unsigned int caster_index, uint8_t step,
    int16_t target_location_index)
{
    unsigned int slot;
    const GameFloaterStart *caster;

    if (session == NULL || caster_index >= session->floater_count ||
        step > 0x16 ||
        (unsigned int)session->active_cast_effect_count +
                session->active_attack_effect_count >=
            GAME_SESSION_MAX_CAST_EFFECTS) {
        return 0;
    }
    caster = &session->floaters[caster_index];
    if (step == 1 || step == 3 || step == 4 || step == 5 || step == 6 ||
        step == 8 || step == 9 || step == 0x10 || step == 0x12 ||
        step == 0x13 || step == 0x16) {
        if (caster->island_index >= session->island_count ||
            target_location_index < 0 ||
            (uint16_t)target_location_index >=
                session->islands[caster->island_index].location_count ||
            /* FUN_004239e9's kind-9 target guard is renderer class zero. */
            (step == 9 && session->islands[caster->island_index]
                .locations[(uint16_t)target_location_index].renderer_class != 0)) {
            return 0;
        }
    } else if (step == 2 || step == 7 || step == 0x0e || step == 0x11 ||
               step == 0x14 || step == 0x15 ||
               caster->island_index >= session->island_count ||
               target_location_index < 0 ||
               (uint16_t)target_location_index >=
                   session->islands[caster->island_index].location_count) {
        /* FUN_0041660b stores no target for these; kinds 0, 0xa..0xd and
           0xf keep the caster's +0x32 site as their travel target. */
        target_location_index = -1;
    }

    for (slot = 0; slot < GAME_SESSION_MAX_CAST_EFFECTS; ++slot) {
        struct GameCastEffectState *effect = &session->cast_effects[slot];
        if (effect->active) continue;
        memset(effect, 0, sizeof(*effect));
        effect->active = 1;
        effect->caster_index = (uint8_t)caster_index;
        effect->step = step;
        effect->target_location_index = target_location_index;
        effect->effect_x = caster->x;
        effect->effect_y = caster->y;
        effect->mirrored = caster->facing_left ? 1U : 0U;
        if (step == 0x10) {
            /* DESTSUPP has no 0x100 start pass: it travels at once. */
            effect->animation_phase = GAME_CAST_PHASE_DESTSUPP_TRAVEL;
        } else if (step == 0x0a) {
            effect->animation_phase = GAME_CAST_PHASE_KILLBEAS;
        } else {
            effect->animation_phase = GAME_CAST_PHASE_START;
            effect->phase_odd_updates_remaining = (uint8_t)
                cast_start_pass_length(step, caster->owner_slot);
        }
        ++session->active_cast_effect_count;
        return 1;
    }
    return 0;
}

/* FUN_00414fbf with flag 2: the target site's x/y. Returns 0 without one. */
static int cast_effect_target(const GameSession *session,
                              const struct GameCastEffectState *effect,
                              int32_t *x, int32_t *y)
{
    const GameFloaterStart *caster = &session->floaters[effect->caster_index];
    const GameRuntimeLocation *site;

    if (caster->island_index >= session->island_count ||
        effect->target_location_index < 0 ||
        (uint16_t)effect->target_location_index >=
            session->islands[caster->island_index].location_count) return 0;
    site = &session->islands[caster->island_index]
                .locations[(uint16_t)effect->target_location_index];
    *x = site->x;
    *y = site->y;
    return 1;
}

/* FUN_0041511b steps `speed` along the normalized vector, rounding each
   coordinate via __ftol, then FUN_004672a6 tests the Chebyshev distance:
   returns 1 on arrival (under 6). */
static int cast_effect_travel(struct GameCastEffectState *effect,
                              int32_t target_x, int32_t target_y, int speed)
{
    int32_t dx = target_x - effect->effect_x;
    int32_t dy = target_y - effect->effect_y;
    double distance = sqrt((double)dx * dx + (double)dy * dy);

    if (distance <= (double)speed) {
        effect->effect_x = (uint16_t)target_x;
        effect->effect_y = (uint16_t)target_y;
    } else {
        effect->effect_x = (uint16_t)((int32_t)effect->effect_x +
            cast_round_to_even((double)dx * speed / distance));
        effect->effect_y = (uint16_t)((int32_t)effect->effect_y +
            cast_round_to_even((double)dy * speed / distance));
    }
    dx = target_x - effect->effect_x;
    dy = target_y - effect->effect_y;
    return (dx < 0 ? -dx : dx) < 6 && (dy < 0 ? -dy : dy) < 6;
}

static void cast_effect_enter_phase(struct GameCastEffectState *effect,
                                    uint8_t phase, unsigned int pass_length)
{
    effect->animation_phase = phase;
    effect->phase_odd_updates_remaining = (uint8_t)pass_length;
    effect->odd_updates_remaining = 0;
}

/* FUN_004239e9 runs only while the caster still casts (+0x2c == 0x13,
   flag 0x200 clear); the slot is freed either way. */
static void cast_effect_apply(GameSession *session, const PadCatalog *catalog,
                              struct GameCastEffectState *effect)
{
    const GameFloaterStart *caster = &session->floaters[effect->caster_index];

    if (caster->active_order_action == 0x13 &&
        (caster->source_runtime_flags & 0x200U) == 0)
        (void)game_session_resolve_cast_effect_step(
            session, catalog, effect->caster_index, effect->step,
            effect->target_location_index);
}

static void cast_effect_free(GameSession *session,
                             struct GameCastEffectState *effect)
{
    effect->active = 0;
    if (session->active_cast_effect_count > 0)
        --session->active_cast_effect_count;
}

void game_session_tick_cast_effects(GameSession *session,
                                    uint32_t source_tick,
                                    const PadCatalog *catalog)
{
    unsigned int slot;
    int odd = (source_tick & 1U) != 0;

    if (session == NULL) return;
    for (slot = 0; slot < GAME_SESSION_MAX_CAST_EFFECTS; ++slot) {
        struct GameCastEffectState *effect = &session->cast_effects[slot];
        int32_t target_x;
        int32_t target_y;

        if (!effect->active) continue;
        if (effect->caster_index >= session->floater_count) {
            cast_effect_free(session, effect);
            continue;
        }
        if (effect->visual_phase != effect->animation_phase) {
            effect->visual_phase = effect->animation_phase;
            effect->animation_ticks = 0;
        }
        if (effect->animation_ticks < UINT16_MAX) ++effect->animation_ticks;
        switch (effect->animation_phase) {
        case GAME_CAST_PHASE_START: {
            int finish = cast_finish_pass_length(effect->step);
            if (!odd || --effect->phase_odd_updates_remaining != 0) break;
            if (finish < 0) {
                /* 2, 8 aside, 0xe, 0x11, 0x14..0x16: one pass, then apply. */
                if (effect->step == 8) {
                    /* FAROBT: a tick counter replaces the frame stepping;
                       effect_y keeps the overlay selector ([2], -1). */
                    effect->effect_y = UINT16_MAX;
                    cast_effect_enter_phase(effect, GAME_CAST_PHASE_FAROBT, 0);
                    break;
                }
                cast_effect_apply(session, catalog, effect);
                cast_effect_free(session, effect);
            } else if (effect->step == 7 || effect->step == 0x12) {
                /* SACRIF then BLASTWB in place. */
                cast_effect_enter_phase(effect, GAME_CAST_PHASE_FINISH,
                                        (unsigned int)finish);
            } else {
                cast_effect_enter_phase(effect, GAME_CAST_PHASE_TRAVEL, 0);
            }
            break;
        }
        case GAME_CAST_PHASE_TRAVEL:
            /* Every tick, not only odd ones (FUN_0041521a). */
            if (!cast_effect_target(session, effect, &target_x, &target_y) ||
                cast_effect_travel(effect, target_x, target_y,
                                   cast_travel_speed(effect->step)))
                cast_effect_enter_phase(effect, GAME_CAST_PHASE_FINISH,
                    (unsigned int)cast_finish_pass_length(effect->step));
            break;
        case GAME_CAST_PHASE_DESTSUPP_TRAVEL:
            /* Frames 0..3 loop at the default SPEED 5; arrival switches to
               frames 14..17, a four-update pass. */
            if (!cast_effect_target(session, effect, &target_x, &target_y) ||
                cast_effect_travel(effect, target_x, target_y, 5))
                cast_effect_enter_phase(effect, GAME_CAST_PHASE_FINISH, 4);
            break;
        case GAME_CAST_PHASE_FINISH:
            if (!odd || --effect->phase_odd_updates_remaining != 0) break;
            cast_effect_apply(session, catalog, effect);
            cast_effect_free(session, effect);
            break;
        case GAME_CAST_PHASE_FAROBT:
            /* Counter from the transition: apply at 0x44, free at 0x7a. */
            ++effect->odd_updates_remaining;
            if (effect->odd_updates_remaining == 0x44) {
                /* [2] = the site's +0x24 object, drawn over the sprite. */
                const GameFloaterStart *caster =
                    &session->floaters[effect->caster_index];
                if (cast_effect_target(session, effect, &target_x, &target_y))
                    effect->effect_y = (uint16_t)(int16_t)session->islands[
                        caster->island_index].locations[
                        (uint16_t)effect->target_location_index].record_value_24;
                cast_effect_apply(session, catalog, effect);
            }
            else if (effect->odd_updates_remaining >= 0x7a)
                cast_effect_free(session, effect);
            break;
        case GAME_CAST_PHASE_KILLBEAS:
            /* [5], [6] and [3] are the three counters, kept in effect_x,
               effect_y and odd_updates_remaining. The first call draws the
               level [2] = rand(8) (kept + 1 in phase_odd_updates_remaining),
               then sets them to -rand(30); each later tick raises them and
               all must pass 75. */
            if (effect->phase_odd_updates_remaining == 0) {
                effect->phase_odd_updates_remaining = (uint8_t)
                    (tone_rng_bounded(&session->random_state, 8) + 1);
                effect->effect_x = (uint16_t)(int16_t)
                    -tone_rng_bounded(&session->random_state, 30);
                effect->effect_y = (uint16_t)(int16_t)
                    -tone_rng_bounded(&session->random_state, 30);
                effect->odd_updates_remaining = (uint8_t)(int8_t)
                    -tone_rng_bounded(&session->random_state, 30);
                break;
            }
            effect->effect_x = (uint16_t)((int16_t)effect->effect_x + 1);
            effect->effect_y = (uint16_t)((int16_t)effect->effect_y + 1);
            effect->odd_updates_remaining =
                (uint8_t)((int8_t)effect->odd_updates_remaining + 1);
            if ((int16_t)effect->effect_x <= 75 ||
                (int16_t)effect->effect_y <= 75 ||
                (int8_t)effect->odd_updates_remaining <= 75) break;
            cast_effect_apply(session, catalog, effect);
            cast_effect_free(session, effect);
            break;
        default:
            cast_effect_free(session, effect);
            break;
        }
    }
}


#include "game_session.h"
#include "game_session_combat_internal.h"

static uint16_t visual_random15(GameSession *session)
{
    uint32_t state = session->visual_random_state;
    if (state == 0) state = 0x9e3779b9U;
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;
    session->visual_random_state = state;
    return (uint16_t)(state & 0x7fffU);
}

static void init_lightning_visual(GameSession *session,
                                  struct GameAttackVisual *visual)
{
    /* FUN_00416ff8/FUN_00415fc6 start a LIGHTNING slot with random s5/s6;
       the bolt is anchored on the target (FUN_004182c8). */
    visual->bolt_seed = visual_random15(session);
    visual->bolt_bits = visual_random15(session);
    visual->x = visual->target_x;
    visual->y = visual->target_y;
    visual->ticks = 0;
}

static int attack_effect_row(const GameFloaterStart *floater)
{
    int row = floater->type_index == 4U ? (int)floater->source_subtype + 27
                                        : (int)floater->type_index * 9 +
                                          (int)floater->source_subtype;
    return row >= 0 && row < FLOATER_CATALOG_ROW_COUNT ? row : -1;
}

static uint8_t attack_visual_level(const FloaterEffectDef *def, uint8_t wanted)
{
    return def->level_count == 0 ? 0
        : wanted < def->level_count ? wanted : (uint8_t)(def->level_count - 1U);
}

int game_session_spawn_attack_visual(GameSession *session,
                                     const GameFloaterStart *attacker,
                                     int attacker_index, uint8_t state,
                                     uint16_t target_x, uint16_t target_y,
                                     int32_t damage)
{
    const FloaterEffectDef *def;
    int row;
    int def_index;
    unsigned int slot;

    if (session == NULL || attacker == NULL) return 0;
    row = attack_effect_row(attacker);
    if (row < 0) return 0;
    def_index = session->attack_effect_row_def[row];
    if (def_index < 0 || def_index >= FLOATER_EFFECT_MAX) return 0;
    def = &session->attack_effect_defs[def_index];
    /* IMPACT/SPECIAL defs are not attack effects. */
    if (def->type != FLOATER_EFFECT_ONESHOT &&
        def->type != FLOATER_EFFECT_BULLET &&
        def->type != FLOATER_EFFECT_LIGHTNING &&
        def->type != FLOATER_EFFECT_CAST) return 0;
    if (def->level_count == 0) return 0;
    for (slot = 0; slot < GAME_SESSION_MAX_CAST_EFFECTS; ++slot) {
        struct GameAttackVisual *visual = &session->attack_visuals[slot];
        int32_t x = attacker->x;
        int32_t y = attacker->y;
        if (visual->active) continue;
        if (def->type == FLOATER_EFFECT_BULLET) {
            /* FUN_00415fc6 adds shape +0x4e/+0x50, negated when mirrored. */
            int32_t sign = attacker->facing_left ? -1 : 1;
            x += sign * session->attack_effect_row_offset_x[row];
            y += sign * session->attack_effect_row_offset_y[row];
        }
        memset(visual, 0, sizeof(*visual));
        visual->active = 1;
        visual->def = (int16_t)def_index;
        /* FUN_0041ff2e picks the level; the attacker's level nibble is an
           interpretation. */
        visual->level = attack_visual_level(def,
            (uint8_t)(attacker->attack_level_flags & 0x0fU));
        visual->frame = def->level_start[visual->level];
        visual->x = (uint16_t)(x < 0 ? 0 : x);
        visual->y = (uint16_t)(y < 0 ? 0 : y);
        visual->island_index = attacker->island_index;
        visual->mirrored = attacker->facing_left ? 1U : 0U;
        visual->target_floater = state == GAME_FLOATER_STATE_ATTACK
            ? attacker->order_target_floater : -1;
        visual->target_x = target_x;
        visual->target_y = target_y;
        visual->impact_damage = (int16_t)(damage > INT16_MAX ? INT16_MAX : damage);
        visual->impact_realm = attacker->attack_realm >= 0 &&
                               attacker->attack_realm < 4
            ? (int8_t)attacker->attack_realm : (int8_t)-1;
        visual->attacker = (int16_t)attacker_index;
        visual->strike_state = state;
        visual->target_location = (int16_t)attacker->order_target_location;
        visual->pending_hit = attacker_index >= 0 ? 1U : 0U;
        if (def->type == FLOATER_EFFECT_LIGHTNING)
            init_lightning_visual(session, visual);
        /* FUN_004181a6: the attack effect SOUND on its first tick. */
        (void)game_session_queue_effect_sound(session, def_index,
            attacker->island_index, visual->x);
        return 1;
    }
    return 0;
}

/* FUN_00416342(site, 0, 1) for a defense whose PROD names an effect (e.g.
   V-ATTCK6 DEVIL): the slot starts at the site plus the PROD offset, keeps
   the target floater from site +0x36 and sets flags 0x8|0x10, so the hit
   waits for FUN_00416ff8's arrival (ev_4c6d730c, ev_04c78e7b). */
int game_session_spawn_defense_effect(GameSession *session, int def_index,
                                      uint8_t island_index, uint16_t x,
                                      uint16_t y, unsigned int target_index,
                                      int32_t attack_power,
                                      uint8_t impact_realm)
{
    const FloaterEffectDef *def;
    const GameFloaterStart *target;
    unsigned int slot;
    if (session == NULL || def_index < 0 || def_index >= FLOATER_EFFECT_MAX ||
        target_index >= session->floater_count) return 0;
    def = &session->attack_effect_defs[def_index];
    if ((def->type != FLOATER_EFFECT_ONESHOT &&
         def->type != FLOATER_EFFECT_LIGHTNING) || def->level_count == 0)
        return 0;
    target = &session->floaters[target_index];
    for (slot = 0; slot < GAME_SESSION_MAX_CAST_EFFECTS; ++slot) {
        struct GameAttackVisual *visual = &session->attack_visuals[slot];
        if (visual->active) continue;
        memset(visual, 0, sizeof(*visual));
        visual->active = 1;
        visual->def = (int16_t)def_index;
        visual->frame = def->level_start[0];
        visual->x = x;
        visual->y = y;
        visual->island_index = island_index;
        visual->target_floater = (int16_t)target_index;
        visual->target_x = target->x;
        visual->target_y = target->y;
        visual->impact_realm = impact_realm < 4U ? (int8_t)impact_realm : -1;
        visual->attacker = -1;
        visual->strike_state = GAME_FLOATER_STATE_ATTACK;
        visual->target_location = -1;
        visual->tower_power = (int16_t)(attack_power > INT16_MAX ? INT16_MAX
                                                                 : attack_power);
        visual->pending_hit = 1;
        if (def->type == FLOATER_EFFECT_LIGHTNING)
            init_lightning_visual(session, visual);
        (void)game_session_queue_effect_sound(session, def_index,
                                              island_index, visual->x);
        return 1;
    }
    return 0;
}

/* A world-event effect instance (FUN_00416a9a) at a fixed point: no hit,
   no impact; it plays its SOUND on its first tick and ends with its frames. */
int game_session_spawn_effect_visual(GameSession *session, int def_index,
                                     uint8_t island_index, uint16_t x,
                                     uint16_t y)
{
    const FloaterEffectDef *def;
    unsigned int slot;
    if (session == NULL || def_index < 0 || def_index >= FLOATER_EFFECT_MAX)
        return 0;
    def = &session->attack_effect_defs[def_index];
    if (def->type != FLOATER_EFFECT_ONESHOT || def->level_count == 0) return 0;
    for (slot = 0; slot < GAME_SESSION_MAX_CAST_EFFECTS; ++slot) {
        struct GameAttackVisual *visual = &session->attack_visuals[slot];
        if (visual->active) continue;
        memset(visual, 0, sizeof(*visual));
        visual->active = 1;
        visual->def = (int16_t)def_index;
        visual->frame = def->level_start[0];
        visual->x = x;
        visual->y = y;
        visual->island_index = island_index;
        visual->target_x = x;
        visual->target_y = y;
        visual->impact_realm = -1;
        visual->attacker = -1;
        visual->target_floater = -1;
        visual->target_location = -1;
        (void)game_session_queue_effect_sound(session, def_index,
                                              island_index, x);
        return 1;
    }
    return 0;
}

/* FUN_00416ff8: a positive hit turns the arrived slot into the realm IMPACT
   (level value / 2, one frame per odd update); otherwise the slot is freed. */
static void finish_attack_visual(GameSession *session,
                                 struct GameAttackVisual *visual)
{
    unsigned int level;
    unsigned int realm;
    if (visual->pending_hit) {
        /* FUN_00416ff8 arrival branch: FUN_004200d2 / FUN_00420188 now. A
           dead attacker's effects are gone, so no hit lands. */
        visual->pending_hit = 0;
        visual->impact_damage = 0;
        if (visual->attacker >= 0 &&
            (unsigned int)visual->attacker < session->floater_count &&
            game_session_floater_is_active(&session->floaters[visual->attacker]) &&
            (session->floaters[visual->attacker].source_runtime_flags & 0x008U) == 0) {
            int32_t damage = game_session_resolve_attack_hit(session,
                (unsigned int)visual->attacker, visual->strike_state,
                visual->target_floater, visual->target_location);
            visual->impact_damage = (int16_t)(damage > INT16_MAX ? INT16_MAX
                                                                  : damage);
        } else if (visual->attacker < 0 && visual->tower_power > 0 &&
                   visual->target_floater >= 0) {
            visual->impact_damage = (int16_t)
                game_session_damage_floater_from_power(session,
                    (unsigned int)visual->target_floater, visual->tower_power);
        }
    }
    if (visual->impact_damage <= 0 || visual->impact_realm < 0) {
        visual->active = 0;
        return;
    }
    realm = (unsigned int)visual->impact_realm & 3U;
    level = (unsigned int)visual->impact_damage / 2U;
    if (level > 3U) level = 3U;
    if (session->effect_impact_frame_counts[realm][level] == 0) {
        visual->active = 0;
        return;
    }
    if (visual->def >= 0 && visual->def < FLOATER_EFFECT_MAX &&
        session->attack_effect_defs[visual->def].type != FLOATER_EFFECT_BULLET) {
        /* FUN_00416ff8 (ev_e14a0501): a non-bullet effect (a melee swing
           drawn on the attacker) places its IMPACT on the target (FUN_00414fbf:
           the live floater, or the site for a site strike) offset by
           FUN_00467260(0xf) - 7 on each axis. A bullet has already arrived. */
        int32_t target_x = visual->x;
        int32_t target_y = visual->y;
        if (visual->strike_state == GAME_FLOATER_STATE_ATTACK &&
            visual->target_floater >= 0 &&
            (unsigned int)visual->target_floater < session->floater_count) {
            target_x = session->floaters[visual->target_floater].x;
            target_y = session->floaters[visual->target_floater].y;
        } else if (visual->target_location >= 0 &&
                   visual->island_index < session->island_count &&
                   (uint16_t)visual->target_location <
                       session->islands[visual->island_index].location_count) {
            const GameRuntimeLocation *site = &session->islands[
                visual->island_index].locations[(uint16_t)visual->target_location];
            target_x = site->x;
            target_y = site->y;
        }
        target_x += tone_rng_bounded(&session->random_state, 15) - 7;
        target_y += tone_rng_bounded(&session->random_state, 15) - 7;
        visual->x = (uint16_t)(target_x < 0 ? 0 : target_x);
        visual->y = (uint16_t)(target_y < 0 ? 0 : target_y);
    }
    visual->impact_phase = 1;
    visual->frame = session->effect_impact_frame_starts[realm][level];
    visual->impact_frames_left = session->effect_impact_frame_counts[realm][level];
    visual->def = -1;
    /* The IMPACT instance plays its realm SOUND on its first tick. */
    (void)game_session_queue_effect_sound(session,
        game_session_impact_def_index(session, realm), visual->island_index,
        visual->x);
}

/* FUN_00415f6d steps every effect instance through FUN_00416ff8 on each sim
   tick; only the frame advance (FUN_00415063/FUN_0041521a) waits for an odd
   DAT_00618e44. Movement (FUN_0041511b), the s9 timeout counter and the
   lightning reveal (FUN_004152bd) run every tick. */
static void tick_attack_visuals(GameSession *session, int odd_tick)
{
    unsigned int slot;
    for (slot = 0; slot < GAME_SESSION_MAX_CAST_EFFECTS; ++slot) {
        struct GameAttackVisual *visual = &session->attack_visuals[slot];
        const FloaterEffectDef *def;
        unsigned int last;
        if (!visual->active) continue;
        if (visual->impact_phase) {
            if (!odd_tick) continue;
            ++visual->frame;
            if (visual->impact_frames_left > 0) --visual->impact_frames_left;
            if (visual->impact_frames_left == 0) visual->active = 0;
            continue;
        }
        if (visual->def < 0 || visual->def >= FLOATER_EFFECT_MAX) {
            visual->active = 0;
            continue;
        }
        def = &session->attack_effect_defs[visual->def];
        last = (unsigned int)def->level_start[visual->level] +
               def->level_frames[visual->level] - 1U;
        /* FUN_00415063/FUN_0041521a advance one frame per odd update. */
        if (odd_tick) ++visual->frame;
        if (def->type == FLOATER_EFFECT_LIGHTNING) {
            /* FUN_004152bd: reveal counter s3 grows and s6 is redrawn each
               update; FUN_00416ecf ends the bolt once s3 > 19. The bolt
               follows its target floater. */
            if (visual->target_floater >= 0 &&
                (unsigned int)visual->target_floater < session->floater_count &&
                game_session_floater_is_active(
                    &session->floaters[visual->target_floater])) {
                visual->target_x = session->floaters[visual->target_floater].x;
                visual->target_y = session->floaters[visual->target_floater].y;
                visual->x = visual->target_x;
                visual->y = visual->target_y;
            }
            visual->bolt_bits = visual_random15(session);
            if (++visual->ticks > 19U) finish_attack_visual(session, visual);
        } else if (def->type == FLOATER_EFFECT_BULLET) {
            int32_t dx;
            int32_t dy;
            double distance;
            if (visual->frame > last) visual->frame = def->level_start[visual->level];
            if (visual->target_floater >= 0 &&
                (unsigned int)visual->target_floater < session->floater_count &&
                game_session_floater_is_active(
                    &session->floaters[visual->target_floater])) {
                visual->target_x = session->floaters[visual->target_floater].x;
                visual->target_y = session->floaters[visual->target_floater].y;
            }
            /* FUN_0041511b: SPEED toward the target, snapping within it, then
               FUN_00416ecf: arrived when both axes are within 6. The
               200-update timeout mirrors FUN_00416ff8's s9 > 200 check. */
            dx = (int32_t)visual->target_x - visual->x;
            dy = (int32_t)visual->target_y - visual->y;
            distance = sqrt((double)dx * dx + (double)dy * dy);
            if (distance <= (double)def->speed) {
                visual->x = visual->target_x;
                visual->y = visual->target_y;
            } else {
                visual->x = (uint16_t)((int32_t)visual->x +
                    cast_round_to_even((double)dx * def->speed / distance));
                visual->y = (uint16_t)((int32_t)visual->y +
                    cast_round_to_even((double)dy * def->speed / distance));
            }
            dx = (int32_t)visual->target_x - visual->x;
            dy = (int32_t)visual->target_y - visual->y;
            if ((dx < 0 ? -dx : dx) < 6 && (dy < 0 ? -dy : dy) < 6)
                finish_attack_visual(session, visual);
            else if (++visual->ticks > 200U)
                visual->active = 0;
        } else if (visual->frame > last) {
            /* ONESHOT ends; CAST chains into its CHAIN def (FUN_00416ff8). */
            if (def->type == FLOATER_EFFECT_CAST && def->chain >= 0 &&
                def->chain < FLOATER_EFFECT_MAX) {
                const FloaterEffectDef *next =
                    &session->attack_effect_defs[def->chain];
                if ((next->type == FLOATER_EFFECT_BULLET ||
                     next->type == FLOATER_EFFECT_ONESHOT ||
                     next->type == FLOATER_EFFECT_LIGHTNING) &&
                    next->level_count != 0) {
                    visual->def = def->chain;
                    visual->level = attack_visual_level(next, visual->level);
                    visual->frame = next->level_start[visual->level];
                    visual->ticks = 0;
                    /* The CHAIN def is a new instance with its own SOUND. */
                    (void)game_session_queue_effect_sound(session, visual->def,
                        visual->island_index, visual->x);
                    if (next->type == FLOATER_EFFECT_LIGHTNING)
                        init_lightning_visual(session, visual);
                    continue;
                }
            }
            /* ONESHOT (flag 0x20) ends through the same arrival branch. */
            finish_attack_visual(session, visual);
        }
    }
}

int game_session_lightning_segments(const GameSession *session,
                                    unsigned int slot,
                                    GameLightningSegment out[GAME_LIGHTNING_MAX_SEGMENTS])
{
    /* FUN_004182c8 tables DAT_0049bd78/80 (frame, dx; ev_81b0a826,
       ev_8cb8f9b8). Index >= 3 is drawn mirrored (DAT_0049bd88). */
    static const uint8_t frame_by_index[6] = {0, 2, 4, 0, 2, 4};
    static const int8_t dx_by_index[6] = {0, 19, 38, 1, -18, -37};
    const struct GameAttackVisual *visual;
    uint32_t pattern = 0;
    int32_t x;
    int32_t y;
    int count = 0;
    unsigned int iteration;

    if (session == NULL || out == NULL ||
        slot >= GAME_SESSION_MAX_CAST_EFFECTS) return 0;
    visual = &session->attack_visuals[slot];
    if (!visual->active || visual->impact_phase || visual->def < 0 ||
        visual->def >= FLOATER_EFFECT_MAX ||
        session->attack_effect_defs[visual->def].type != FLOATER_EFFECT_LIGHTNING)
        return 0;
    x = visual->target_x;
    y = visual->target_y;
    for (iteration = 0; iteration < GAME_LIGHTNING_MAX_SEGMENTS; ++iteration) {
        unsigned int local = 9U - iteration; /* the original's local_20 */
        unsigned int index;
        int mirrored;
        if (iteration == 0 || local == 5U) pattern = visual->bolt_seed;
        y -= 0x28;
        if (y < 0) break;
        index = ((pattern & 7U) % 6U);
        pattern >>= 3;
        x += dx_by_index[index];
        mirrored = index > 2U;
        if (local <= visual->ticks) {
            out[count].x = x;
            out[count].y = y;
            out[count].frame = (uint8_t)(frame_by_index[index] +
                ((visual->bolt_bits >> iteration) & 1U));
            out[count].mirrored = (uint8_t)mirrored;
            ++count;
        }
        if (mirrored) x -= 1;
    }
    return count;
}

int game_session_attack_visual_mirrored(const GameSession *session,
                                        unsigned int slot)
{
    return session != NULL && slot < GAME_SESSION_MAX_CAST_EFFECTS &&
           session->attack_visuals[slot].active &&
           session->attack_visuals[slot].mirrored;
}

int game_session_attack_visual(const GameSession *session, unsigned int slot,
                               int *def, unsigned int *frame, uint16_t *x,
                               uint16_t *y, uint8_t *island,
                               int *impact_realm)
{
    const struct GameAttackVisual *visual;
    if (session == NULL || def == NULL || frame == NULL || x == NULL ||
        y == NULL || island == NULL || impact_realm == NULL ||
        slot >= GAME_SESSION_MAX_CAST_EFFECTS) return 0;
    visual = &session->attack_visuals[slot];
    if (!visual->active) return 0;
    *impact_realm = visual->impact_phase ? visual->impact_realm : -1;
    *def = visual->def;
    *frame = visual->frame;
    *x = visual->x;
    *y = visual->y;
    *island = visual->island_index;
    return 1;
}

void game_session_start_attack_effect(GameSession *session,
                                     GameFloaterStart *attacker,
                                     int32_t damage,
                                     uint16_t target_x, uint16_t target_y)
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
    attacker->attack_effect_hidden = 0;
    attacker->attack_effect_level = (uint8_t)level;
    attacker->attack_effect_x = target_x;
    attacker->attack_effect_y = target_y;
    /* FUN_00415063 tests completion only after stepping past the last frame. */
    attacker->attack_effect_odd_updates_remaining = (uint8_t)(frame_count + 1U);
    ++session->active_attack_effect_count;
    (void)game_session_queue_effect_sound(session,
        game_session_impact_def_index(session,
            (unsigned int)attacker->attack_realm & 3U),
        attacker->island_index, target_x);
}

void game_session_tick_combat_effects(GameSession *session,
                                     uint32_t source_tick)
{
    unsigned int i;

    if (session == NULL) return;
    tick_attack_visuals(session, (source_tick & 1U) != 0);
    if ((source_tick & 1U) == 0) return;
    for (i = 0; i < session->floater_count; ++i) {
        GameFloaterStart *floater = &session->floaters[i];
        if (floater->attack_effect_waits_visual) {
            unsigned int slot;
            int alive = 0;
            for (slot = 0; slot < GAME_SESSION_MAX_CAST_EFFECTS; ++slot) {
                if (session->attack_visuals[slot].active &&
                    session->attack_visuals[slot].attacker == (int16_t)i) {
                    alive = 1;
                    break;
                }
            }
            if (!alive) {
                floater->attack_effect_waits_visual = 0;
                floater->attack_effect_active = 0;
                if (session->active_attack_effect_count > 0)
                    --session->active_attack_effect_count;
            }
            continue;
        }
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

int game_session_attack_effect_visual(const GameSession *session,
                                      unsigned int floater_index,
                                      unsigned int *realm,
                                      unsigned int *frame,
                                      uint16_t *x, uint16_t *y)
{
    const GameFloaterStart *floater;
    unsigned int level;
    unsigned int frame_count;
    unsigned int elapsed;
    unsigned int impact_realm;

    if (session == NULL || realm == NULL || frame == NULL || x == NULL ||
        y == NULL || floater_index >= session->floater_count) return 0;
    floater = &session->floaters[floater_index];
    if (!game_session_floater_is_active(floater) ||
        !floater->attack_effect_active || floater->attack_effect_hidden ||
        floater->attack_effect_level > 3U) return 0;
    level = floater->attack_effect_level;
    frame_count = floater->attack_impact_frame_counts[level];
    if (frame_count == 0 || floater->attack_realm < 0) return 0;
    impact_realm = (unsigned int)floater->attack_realm & 3U;
    /* The slot starts with frame_count + 1 odd updates left; one frame per
       odd update (FUN_00415063), clamped to the last impact frame. */
    elapsed = frame_count + 1U - floater->attack_effect_odd_updates_remaining;
    if (elapsed >= frame_count) elapsed = frame_count - 1U;
    *realm = impact_realm;
    *frame = (unsigned int)session->effect_impact_frame_starts[impact_realm][level] +
             elapsed;
    *x = floater->attack_effect_x;
    *y = floater->attack_effect_y;
    return 1;
}
