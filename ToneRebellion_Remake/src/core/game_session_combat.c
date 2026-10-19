#include "game_session.h"
#include "game_session_combat_internal.h"

#include <stdint.h>

enum { GAME_FLOATER_STATE_ATTACK = 6, GAME_FLOATER_STATE_ATTACK_SITE = 7 };

void game_session_tick_floater_combat(GameSession *session,
                                      unsigned int floater_index)
{
    GameFloaterStart *floater;
    uint8_t state;

    if (session == NULL || floater_index >= session->floater_count) return;
    floater = &session->floaters[floater_index];
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
            damage = game_session_damage_floater(
                session, floater_index,
                (unsigned int)floater->order_target_floater);
        } else if (state == GAME_FLOATER_STATE_ATTACK_SITE &&
                   floater->island_index < session->island_count &&
                   floater->order_target_location >= 0 &&
                   (uint16_t)floater->order_target_location <
                       session->islands[floater->island_index].location_count) {
            damage = game_session_damage_site(
                session, floater_index,
                &session->islands[floater->island_index].locations[
                    (uint16_t)floater->order_target_location]);
        }
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

static int32_t floater_attack_power(const GameFloaterStart *floater)
{
    int32_t power;
    int32_t level = floater->attack_level_flags & 0x0fU;

    /* FUN_004207c2 suppresses the row's base attack value except for class 4
       and charged nonzero subtypes. FUN_0041fde6 then adds the source level
       contribution. Site/research modifiers are not represented yet. */
    if (floater->type_index == 4U ||
        (floater->source_subtype != 0 && floater->charge_current > 0)) {
        power = floater->attack_strength;
    } else {
        power = 0;
    }
    if (floater->type_index == 4U) {
        power += level * 3;
        power += (((floater->attack_level_flags >> 4) & 0x0fU) * power) / 22;
    } else {
        power += level * 2;
    }
    return power;
}

static int32_t difficulty_attack_modifier(int32_t power, uint8_t difficulty)
{
    int32_t modifier;
    int32_t floor_value;

    if (difficulty == 0) {
        modifier = power / 4;
        floor_value = 1;
    } else if (difficulty == 1) {
        modifier = power / 2;
        floor_value = 2;
    } else {
        modifier = (power * 2) / 3;
        floor_value = 3;
    }
    return modifier < floor_value ? floor_value : modifier;
}

static int32_t source_round_to_int(double value)
{
    int32_t whole = (int32_t)value;
    double fraction = value - whole;
    if (fraction > 0.5 || (fraction == 0.5 && (whole & 1) != 0)) ++whole;
    else if (fraction < -0.5 || (fraction == -0.5 && (whole & 1) != 0)) --whole;
    return whole;
}

static int floater_attack_hits(GameSession *session,
                               const GameFloaterStart *attacker,
                               const GameFloaterStart *target,
                               int32_t attack_power)
{
    double score = (double)(attack_power + 7 - floater_attack_power(target));
    int32_t modifier = difficulty_attack_modifier(attack_power,
                                                   session->config.difficulty);
    int32_t attack_realm = attacker->attack_realm & 3;
    int32_t target_realm = target->attack_realm & 3;
    int32_t chance;

    if ((target->source_runtime_flags & 0x108U) != 0) return 0;

    if (((attack_realm + 1) & 3) == target_realm) {
        score += modifier;
    } else if (((attack_realm + 3) & 3) == target_realm) {
        score -= modifier;
    } else if (attack_realm != target_realm) {
        /* FUN_00420217 uses one of two research-derived corrections. Both
           globals are zero in the loaded image; classes 2..4 reverse its sign. */
        score += (attacker->type_index > 1U ? 0.5 : -0.5) * attack_power;
    }
    chance = source_round_to_int((60.0 * score) / 14.0) + 10;
    return tone_rng_bounded(&session->random_state, 100) < chance;
}

int32_t game_session_damage_floater(GameSession *session,
                              unsigned int attacker_index,
                              unsigned int target_index)
{
    GameFloaterStart *attacker = &session->floaters[attacker_index];
    GameFloaterStart *target = &session->floaters[target_index];
    int32_t power = floater_attack_power(attacker);
    int32_t random_range = power - 1;
    int32_t damage;

    if (!floater_attack_hits(session, attacker, target, power)) return 0;
    if (random_range < 1) random_range = 1;
    damage = (tone_rng_bounded(&session->random_state, random_range) +
              tone_rng_bounded(&session->random_state, random_range) + 3 +
              tone_rng_bounded(&session->random_state, random_range)) / 3;
    if (damage > 10) damage = 10;
    if (damage < 0) damage = 0;
    if (target->current_hit_points > (uint8_t)damage) {
        target->current_hit_points =
            (uint8_t)(target->current_hit_points - (uint8_t)damage);
    } else if ((target->source_runtime_flags & 0x008U) == 0) {
        target->current_hit_points = 0;
        target->source_runtime_flags |= 0x008U;
        target->source_death_timer = 0;
    }
    return damage;
}

int32_t game_session_damage_site(GameSession *session,
                           unsigned int attacker_index,
                           GameRuntimeLocation *target)
{
    GameFloaterStart *attacker = &session->floaters[attacker_index];
    int32_t power = floater_attack_power(attacker);
    int32_t damage_range = power > 0 ? power : 1;
    int32_t damage = tone_rng_bounded(&session->random_state, damage_range) + 1;
    int32_t item_id = target->record_value_10;

    if (damage > 6) damage = 6;
    /* FUN_00450847 accepts nonempty sites owned by source class 0/1 and
       rejects flags 0x290. Item 1 uses the separately modeled short at +0x28. */
    if (target->owner_id < 0 || target->owner_id > 1 || item_id < 0x17 ||
        item_id > 0x24 || (target->source_flags & 0x290U) != 0 ||
        target->record_value_10 == 0) return 0;
    if (target->source_value_34 < 1) return 0;

    target->source_value_34 = (int16_t)(target->source_value_34 - damage);
    if (target->source_value_34 < 1) {
        target->source_flags |= 0x80U;
    }
    return damage;
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
        session->active_attack_effect_count >= 32U ||
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
        if (!floater->attack_effect_active) continue;
        if (floater->attack_effect_odd_updates_remaining > 0)
            --floater->attack_effect_odd_updates_remaining;
        if (floater->attack_effect_odd_updates_remaining == 0) {
            floater->attack_effect_active = 0;
            if (session->active_attack_effect_count > 0)
                --session->active_attack_effect_count;
        }
    }
}
