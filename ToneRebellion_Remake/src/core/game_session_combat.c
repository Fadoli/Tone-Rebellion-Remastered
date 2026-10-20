#include "game_session.h"
#include "game_session_combat_internal.h"
#include "game_session_action9.h"

#include <math.h>
#include <stdint.h>

enum { GAME_FLOATER_STATE_ATTACK = 6, GAME_FLOATER_STATE_ATTACK_SITE = 7 };

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

static int32_t floater_site_attack_power(const GameSession *session,
                                         const GameFloaterStart *floater)
{
    int32_t power = 0;
    int32_t level = floater->attack_level_flags & 0x0fU;

    /* FUN_0041fde6 uses max_attack_points as its base, unlike the separate
       attack-strength formula used by FUN_00420217 for floater combat. Its
       linked source grants +3 when runtime flag 0x8000 is set. */
    if (floater->type_index == 4U ||
        (floater->source_subtype != 0 && floater->charge_current > 0)) {
        power = floater->max_attack_points;
    }
    if (floater->source_link_0c >= 0 &&
        floater->charge_source_island < session->island_count &&
        floater->charge_source_location <
            session->islands[floater->charge_source_island].location_count) {
        const GameRuntimeLocation *source = &session->islands[
            floater->charge_source_island].locations[
                floater->charge_source_location];
        if (source->source_location_slot_18 == floater->source_link_0c &&
            source->owner_id == (int32_t)floater->owner_slot &&
            (source->source_flags & 0x8000U) != 0) {
            /* FUN_0041fde6 adds three before applying level modifiers. */
            power += 3;
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
    int32_t power = floater_site_attack_power(session, attacker);
    int32_t damage_range = power > 0 ? power : 1;
    /* FUN_00467260 scales the shared 15-bit RNG by this range, truncates via
       __ftol, adds one, then caps the site damage at six. */
    int32_t damage = tone_rng_bounded(&session->random_state, damage_range) + 1;
    int32_t item_id = target->record_value_10;

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

void game_session_clear_cast_site(GameSession *session, uint8_t island_index,
                                  uint16_t location_index,
                                  GameRuntimeLocation *target)
{
    int32_t previous_owner = target->owner_id;
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
    for (task_type = 0; task_type < GAME_RESOURCE_TYPE_COUNT; ++task_type) {
        int16_t task_slot = target->source_task_slot[task_type];
        if (task_slot >= 0 && task_slot < GAME_SESSION_MAX_PENDING_EVENTS) {
            (void)game_session_pending_event_release(session,
                                                     (uint8_t)task_slot);
        }
        target->source_task_slot[task_type] = -1;
    }

    for (slot = 0; slot < 8; ++slot) {
        int16_t floater_index = target->charge_floater_slots[slot];
        if (floater_index >= 0 && (unsigned int)floater_index < session->floater_count)
            (void)game_session_unlink_floater_charge(session,
                                                     (unsigned int)floater_index);
        target->charge_floater_slots[slot] = -1;
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
    target->charge_floater_count = 0;
    target->charge_recent_floater = -1;
    target->resource_stock[GAME_RESOURCE_BUILD_TONE] = 0;
    target->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] = 0;
    target->resource_stock[GAME_RESOURCE_MAGIC_TONE] = 0;
    (void)game_session_recalculate_active_locations(session);
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

unsigned int game_session_apply_cast_blast(
    GameSession *session, unsigned int caster_index)
{
    GameFloaterStart *caster;
    const GameRuntimeIsland *island;
    int32_t level;
    int32_t radius;
    int32_t base_amount;
    unsigned int location_index;
    unsigned int affected = 0;
    unsigned int target_index;

    if (session == NULL || caster_index >= session->floater_count) return 0;
    caster = &session->floaters[caster_index];
    if (caster->island_index >= session->island_count) return 0;
    island = &session->islands[caster->island_index];

    /* FUN_004239e9 case 7 scales a 0x11 base by the caster's low-nibble
       level and applies linear attenuation beyond half of the radius. */
    level = caster->attack_level_flags & 0x0fU;
    radius = level * 0x32 + 200;
    base_amount = level * 5 + 0x11;

    /* FUN_004239e9 also calls FUN_004204bc for every other floater within
       the blast radius; this hit is direct and does not roll attack chance. */
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
        } else {
            target->current_hit_points = (uint8_t)remaining_hp;
        }
        ++affected;
    }

    for (location_index = 0; location_index < island->location_count;
         ++location_index) {
        const GameRuntimeLocation *target = &island->locations[location_index];
        int32_t distance = game_session_source_chebyshev_distance(
            caster->x, caster->y, target->x, target->y);
        int32_t effect_amount = base_amount;

        /* FUN_00450817 filters item IDs 0x17..0x24 before forwarding to
           FUN_00450847. */
        if (distance >= radius ||
            (target->record_value_10 >= 0x17 && target->record_value_10 <= 0x24)) {
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

    /* FUN_004239e9 case 7 calls FUN_004204bc with the caster's current HP,
       making the area cast consume its caster as part of the impact. */
    if (caster->current_hit_points > 0) {
        caster->current_hit_points = 0;
        caster->source_runtime_flags |= 0x008U;
        caster->source_death_timer = 0;
        ++affected;
    }
    return affected;
}

unsigned int game_session_resolve_cast_effect_step(
    GameSession *session, unsigned int caster_index, uint8_t step,
    int16_t target_location_index)
{
    GameFloaterStart *caster;
    const GameRuntimeLocation *target;

    if (session == NULL || caster_index >= session->floater_count) return 0;
    caster = &session->floaters[caster_index];
    if (step == 7) {
        if (caster->cast_spell_kind != 7) return 0;
        caster->source_runtime_flags |= 0x200U;
        return game_session_apply_cast_blast(session, caster_index);
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
        (step != 7 && step != 9 && step != 0x14 && step != 0x16) ||
        (odd_updates_until_impact == 0 && step != 0x16) ||
        (unsigned int)session->active_cast_effect_count +
                session->active_attack_effect_count >=
            GAME_SESSION_MAX_CAST_EFFECTS) {
        return 0;
    }
    if (step == 9) {
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
                                    uint32_t source_tick)
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
            session, effect->caster_index, effect->step,
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
