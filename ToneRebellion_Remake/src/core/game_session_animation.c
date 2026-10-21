#include "game_session.h"

#include "building_render.h"
#include "game_session_combat_internal.h"
#include "game_session_internal.h"
#include "island_render_rules.h"
#include "game_session_world.h"
#include "pad_catalog.h"
#include "tone_rng.h"

#include <math.h>
#include <string.h>

static const uint8_t source_staff_target_counts[8][3][3] = {
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{3, 0, 0}, {3, 2, 0}, {3, 2, 1}},
    {{3, 0, 0}, {3, 2, 0}, {3, 2, 1}},
    {{3, 0, 0}, {3, 2, 0}, {0, 0, 0}},
    {{1, 0, 0}, {1, 1, 0}, {1, 1, 1}},
    {{1, 0, 0}, {1, 1, 0}, {1, 1, 1}},
    {{1, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{1, 0, 0}, {0, 0, 0}, {0, 0, 0}}
};

static const int16_t source_staff_level_caps[9] = {0, 2, 2, 1, 2, 2, 0, 0, 0};
static const int16_t source_staff_threshold_low[9][3] = {
    {0, 0, 0}, {25, 100, 0}, {30, 120, 0}, {40, -1, 0},
    {25, 100, 0}, {25, 100, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}
};
static const int16_t source_staff_threshold_high[9][3] = {
    {0, 0, 0}, {75, 200, 0}, {90, 240, 0}, {120, -1, 0},
    {75, 200, 0}, {75, 200, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}
};

static int choose_neutral_item5_spawn(GameSession *session,
                                      unsigned int island_index)
{
    static const uint8_t item_ids[12] = {
        12, 16, 11, 19, 10, 20, 13, 21, 14, 17, 15, 18
    };
    int32_t base = 12;
    int32_t cohort;
    int32_t island_cohort;
    int32_t candidate_count;
    int32_t selection;

    if (session->config.difficulty == 1) base = 10;
    else if (session->config.difficulty == 0) base = 6;
    cohort = ((int32_t)session->island_count - 1) >> 2;
    island_cohort = (int32_t)island_index >> 2;
    if (cohort == 0) {
        cohort = 1;
        island_cohort = 1;
    }
    candidate_count = base / 2 + ((base - base / 2) * island_cohort) / cohort;
    if (candidate_count < 1) candidate_count = 1;
    if (candidate_count > 12) candidate_count = 12;
    selection = tone_rng_bounded(&session->random_state, candidate_count);
    if (selection < 0 || selection >= candidate_count) return -1;
    return item_ids[selection];
}

static int choose_class1_item5_spawn(GameSession *session,
                                     const GameRuntimeIsland *island,
                                     unsigned int island_index)
{
    static const int8_t first_type_by_shape[15] = {
        0, 1, -1, 3, 2, 0, 2, 1, 1, 3, 3, 1, 2, -1, -1
    };
    static const int8_t second_type_by_shape[15] = {
        -1, 2, 3, 1, 3, 1, 0, 2, 0, 0, 2, 3, 0, -1, -1
    };
    uint8_t required_types[4] = {0, 0, 0, 0};
    uint16_t present_counts[4] = {0, 0, 0, 0};
    int16_t shape_id = island->leviathan_marker_shape_id;
    int16_t first_type;
    int16_t second_type;
    int candidate_ids[4];
    int candidate_count = 0;
    unsigned int index;
    int selection;

    if (island_index + 1U == session->island_count) {
        required_types[0] = 1;
        required_types[1] = 1;
        required_types[2] = 1;
        required_types[3] = 1;
    } else {
        if (shape_id < 0) shape_id = 0;
        if (shape_id > 14) shape_id = 14;
        first_type = first_type_by_shape[shape_id];
        second_type = second_type_by_shape[shape_id];
        if (first_type < -1) first_type = -1;
        if (first_type > 3) first_type = 3;
        if (second_type < -1) second_type = -1;
        if (second_type > 3) second_type = 3;
        if (first_type >= 0) required_types[first_type] = 1;
        if (second_type >= 0) required_types[second_type] = 1;
    }

    for (index = 0; index < island->location_count; ++index) {
        int32_t item_id = island->locations[index].record_value_10;
        if (item_id > 5 && item_id < 10)
            ++present_counts[(unsigned int)(item_id - 6)];
    }
    for (index = 0; index < 4; ++index) {
        if (required_types[index] != 0 && present_counts[index] == 0)
            candidate_ids[candidate_count++] = (int)index;
    }
    if (candidate_count == 0) {
        for (index = 0; index < 4; ++index) {
            if (required_types[index] != 0)
                candidate_ids[candidate_count++] = (int)index;
        }
    }
    /* Shape 13 has no configured pair in either native table. The original
       then indexes an uninitialized stack candidate; use all four types to
       keep the remaining class-1 item-5 sites playable and deterministic. */
    if (candidate_count == 0) {
        candidate_ids[0] = 0;
        candidate_ids[1] = 1;
        candidate_ids[2] = 2;
        candidate_ids[3] = 3;
        candidate_count = 4;
    }
    selection = tone_rng_bounded(&session->random_state, candidate_count);
    if (selection < 0 || selection >= candidate_count) return -1;
    return candidate_ids[selection] + 6;
}

static int tick_item5_spawn(GameSession *session,
                            const PadCatalog *pad_catalog,
                            GameRuntimeLocation *state,
                            unsigned int island_index)
{
    int32_t threshold;
    int32_t next_progress;
    int32_t spawned_item_id;
    const PadCatalogItem *item;
    const GameRuntimeIsland *island;

    if (pad_catalog == NULL || state->renderer_class > 1 ||
        state->record_value_10 != 5 || island_index >= session->island_count)
        return 0;
    threshold = 0x4b0 - (int32_t)session->config.difficulty * 100;
    next_progress = (int16_t)state->charge_source_value_30 +
        (int16_t)state->animation_rate;
    state->charge_source_value_30 = (uint16_t)next_progress;
    if ((int16_t)state->charge_source_value_30 < threshold) return 0;

    island = &session->islands[island_index];
    spawned_item_id = state->renderer_class == 1
        ? choose_class1_item5_spawn(session, island, island_index)
        : choose_neutral_item5_spawn(session, island_index);
    if (spawned_item_id < 0) return 0;
    item = pad_catalog_find(pad_catalog, (uint16_t)spawned_item_id);
    if (item == NULL) return 0;

    /* FUN_00452859(spawned_item_id, 4) replaces this object in place. */
    state->record_value_10 = spawned_item_id;
    state->owner_id = 4;
    state->source_value_14 = 4;
    state->source_capacity_4a = 0;
    state->source_value_32 = 1;
    if (state->record_value_24 < 5 || state->record_value_24 > 0x21)
        state->record_value_24 = 0;
    state->source_flags = (state->source_flags & ~0x0fU) | 0x410U;
    state->source_value_34 = item->hit_points;
    state->maintenance_tone_cost = 0;
    state->resource_stock[GAME_RESOURCE_BUILD_TONE] = 0;
    state->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] = 0;
    state->resource_stock[GAME_RESOURCE_MAGIC_TONE] = 0;
    state->charge_source_value_30 = 0;
    state->leviathan_spawned_floater = -1;
    state->source_value_3a = 0;
    state->source_value_3c = 0;
    state->source_value_3e = -1;
    state->source_value_40 = 0;
    state->source_value_42 = 0;
    state->source_value_44 = 0;
    state->source_value_46 = 0;
    state->source_value_48 = 0;
    state->chug_progress = 0;
    state->glyph_progress = 0;
    state->inci_progress = 0;
    state->construction_progress = 0;
    state->production_progress = 0;
    state->animation_rate = 1;
    if (state->renderer_class == 0)
        state->source_value_22 &= 0xff00U;
    state->tribe_visibility_mask = (uint8_t)state->source_value_22;
    (void)game_session_recalculate_location_active_with_visibility(state);
    (void)game_session_recalculate_active_locations(session);
    return 1;
}

static int producer_resource_code(const GameRuntimeLocation *state)
{
    int32_t base_item_id;
    if (state == NULL || state->renderer_class != 0 || state->owner_id < 0 ||
        state->owner_id >= GAME_START_PLAYER_COUNT) return 0;
    /* FUN_00450a71 and FUN_00452ceb switch on the exact shared producer IDs;
       the tribe is carried separately in runtime +0x14. The remake stores
       owner-specific PAD IDs in +0x10, so normalize before this source switch. */
    base_item_id = game_session_base_item_id(state);
    if (base_item_id == 0x25) return 1; /* P-BLDTON -> Build Tone */
    if (base_item_id == 0x27) return 2; /* P-CRYTON -> Crystal Tone */
    if (base_item_id == 0x26) return 3; /* P-MAGTON -> Magic Tone */
    return 0;
}

static int leviathan_spawn_threshold(const GameSession *session,
                                    const GameRuntimeIsland *island)
{
    int difficulty = session->config.difficulty;
    int active_floaters = 0;
    int threshold;
    unsigned int index;

    if (difficulty > 4) difficulty = 4;
    threshold = 10000 - difficulty * 400;
    if (difficulty > 1) {
        uint32_t late_game_reduction = session->simulation_tick < 100001U
            ? 0U : (session->simulation_tick - 100000U) / 100U;
        if (late_game_reduction > 2400U) late_game_reduction = 2400U;
        threshold -= (int)late_game_reduction;

        /* FUN_00450a71 tightens the interval as the island population grows;
           its source scan is capped at five active floater records. */
        for (index = 0; index < session->floater_count; ++index) {
            const GameFloaterStart *floater = &session->floaters[index];
            if (game_session_floater_is_active(floater) &&
                floater->island_index == (uint8_t)(island - session->islands) &&
                floater->current_hit_points != 0) {
                ++active_floaters;
                if (active_floaters == 5) break;
            }
        }
        {
            int multiplier = 14 - difficulty - active_floaters;
            if (multiplier < 5) multiplier = 5;
            if (multiplier > 10) multiplier = 10;
            threshold = (threshold * multiplier) / 10;
        }
    }
    return threshold;
}

static int leviathan_spawn_subtype(GameSession *session,
                                  const GameRuntimeIsland *island,
                                  const GameRuntimeLocation *site)
{
    uint16_t site_counts[4] = {0, 0, 0, 0};
    uint16_t unit_counts[4] = {0, 0, 0, 0};
    unsigned int index;
    unsigned int group = site->record_value_10 - 6;
    unsigned int least_group = 0;
    uint32_t least_ratio = UINT32_MAX;

    for (index = 0; index < island->location_count; ++index) {
        const GameRuntimeLocation *candidate = &island->locations[index];
        if (candidate->record_value_10 >= 6 && candidate->record_value_10 <= 9)
            ++site_counts[(unsigned int)candidate->record_value_10 - 6U];
    }
    for (index = 0; index < session->floater_count; ++index) {
        const GameFloaterStart *floater = &session->floaters[index];
        unsigned int unit_group;
        if (!game_session_floater_is_active(floater) || floater->type_index != 4 ||
            floater->island_index != (uint8_t)(island - session->islands) ||
            floater->source_subtype < 10 || floater->source_subtype > 17) continue;
        unit_group = (unsigned int)(floater->source_subtype - 10U) / 2U;
        ++unit_counts[unit_group];
    }
    for (index = 0; index < 4; ++index) {
        uint32_t ratio;
        if (site_counts[index] == 0) continue;
        ratio = (uint32_t)unit_counts[index] * 100U / site_counts[index];
        if (ratio < least_ratio) {
            least_ratio = ratio;
            least_group = index;
        }
    }

    /* The native selector emits subtype 9 when this site is not the least
       represented marker family. Otherwise it chooses the pair associated
       with the family, with FUN_00467260 selecting between the pair. */
    if (group != least_group) return 9;
    return 10 + (int)(group * 2U) +
        tone_rng_bounded(&session->random_state, 2);
}

static int spawn_leviathan_floater(GameSession *session,
                                  const FloaterCatalog *catalog,
                                  GameRuntimeIsland *island,
                                  GameRuntimeLocation *site)
{
    const FloaterStats *stats;
    GameFloaterStart *floater;
    unsigned int index;
    unsigned int count = 0;
    int subtype;

    if (session == NULL || catalog == NULL || island == NULL || site == NULL)
        return -1;
    for (index = 0; index < session->floater_count; ++index) {
        const GameFloaterStart *existing = &session->floaters[index];
        if (game_session_floater_is_active(existing) &&
            existing->type_index == 4) ++count;
    }
    /* FUN_00462a87 refuses another category-4 floater above 128 records. */
    if (count > 128U) return -1;
    subtype = leviathan_spawn_subtype(session, island, site);
    stats = floater_catalog_find(catalog, 4, subtype);
    if (stats == NULL || stats->hit_points <= 0 ||
        stats->hit_points > (int16_t)UINT8_MAX ||
        stats->attack_strength < 0 ||
        stats->attack_strength > (int16_t)UINT8_MAX ||
        stats->movement_speed < 0) return -1;

    for (index = 0; index < GAME_SESSION_MAX_FLOATERS; ++index) {
        if (index >= session->floater_count ||
            !game_session_floater_is_active(&session->floaters[index])) break;
    }
    if (index == GAME_SESSION_MAX_FLOATERS) return -1;
    floater = &session->floaters[index];
    memset(floater, 0, sizeof(*floater));
    floater->is_active = 1;
    floater->island_index = (uint8_t)(island - session->islands);
    floater->type_index = 4;
    floater->source_subtype = (uint8_t)subtype;
    floater->owner_slot = 4;
    floater->current_hit_points = (uint8_t)stats->hit_points;
    floater->max_hit_points = (uint8_t)stats->hit_points;
    floater->attack_strength = (uint8_t)stats->attack_strength;
    floater->max_attack_points = stats->max_attack_points;
    floater->attack_realm = stats->attack_realm;
    floater->attack_range = stats->attack_range;
    floater->attack_period = stats->attack_period;
    floater->attack_frame_first = stats->attack_frame_first;
    floater->attack_frame_last = stats->attack_frame_last;
    floater->attack_frame_ticks_per_frame = stats->attack_frame_ticks_per_frame;
    floater->attack_frame_duration = stats->attack_frame_duration;
    floater->attack_frame_ping_pong = stats->attack_frame_ping_pong;
    if (stats->attack_realm >= 0 && stats->attack_realm < 4) {
        memcpy(floater->attack_impact_frame_counts,
               catalog->impact_frame_counts[stats->attack_realm],
               sizeof(floater->attack_impact_frame_counts));
    }
    floater->source_link_0c = -1;
    floater->charge_source_island = UINT8_MAX;
    floater->charge_source_location = UINT16_MAX;
    floater->linked_task_slot = -1;
    floater->order_source_location = -1;
    floater->order_target_location = -1;
    floater->order_target_floater = -1;
    floater->order_target_island = floater->island_index;
    floater->order_source_island = floater->island_index;
    floater->handoff_departure_location = -1;
    floater->x = site->x;
    floater->y = site->y;
    floater->destination_x = site->x;
    floater->destination_y = site->y;
    floater->movement_speed = (uint16_t)stats->movement_speed;
    floater->source_runtime_flags = 0x801U;
    if (index >= session->floater_count)
        session->floater_count = (uint16_t)(index + 1U);
    (void)game_session_queue_audio_event(
        session, GAME_SESSION_AUDIO_BUILD, 4);
    return (int)index;
}

static void release_leviathan_floater(GameSession *session,
                                      GameRuntimeLocation *site,
                                      const BuildingRenderItem *item)
{
    GameFloaterStart *floater;
    int32_t index = site->leviathan_spawned_floater;
    if (index < 0 || (unsigned int)index >= session->floater_count) return;
    floater = &session->floaters[(unsigned int)index];
    if (!game_session_floater_is_active(floater)) return;
    floater->x = (uint16_t)((int32_t)site->x +
        (item->prod.present ? item->prod.offset_x : 0));
    floater->y = (uint16_t)((int32_t)site->y +
        (item->prod.present ? item->prod.offset_y : 0));
    floater->destination_x = floater->x;
    floater->destination_y = floater->y;
    floater->source_runtime_flags &= ~0x801U;
    floater->has_wander_order = 1;
    site->leviathan_spawned_floater = -1;
}

static int is_leviathan_defense(const GameRuntimeLocation *state)
{
    int32_t item_id;
    if (state == NULL || state->renderer_class != 0 ||
        state->source_value_14 != 4) return 0;
    item_id = game_session_base_item_id(state);
    /* V-ATTCK1..6 use the same source defense scan as the ranged V-SHOT and
       V-ROD items; their PROD phase ends in a close hit instead of a bolt. */
    return item_id >= 0x0a && item_id <= 0x15;
}

static int32_t chebyshev_distance(uint16_t ax, uint16_t ay,
                                  uint16_t bx, uint16_t by)
{
    int32_t dx = (int32_t)ax - (int32_t)bx;
    int32_t dy = (int32_t)ay - (int32_t)by;
    if (dx < 0) dx = -dx;
    if (dy < 0) dy = -dy;
    return dx > dy ? dx : dy;
}

static uint8_t leviathan_projectile_sheet(int32_t item_id)
{
    /* effects.txt and shapes.txt: VSHT1B/VSHROD/VSPIRL/VSHT2B resolve to
       V-SHOT1B/V-MNRB/JOIN4/V-SHT2FX respectively. */
    static const uint8_t sheet_by_item[6] = {0, 1, 1, 2, 0, 3};
    if (item_id < 0x10 || item_id > 0x15) return UINT8_MAX;
    return sheet_by_item[item_id - 0x10];
}

static uint8_t leviathan_projectile_impact_realm(int32_t item_id)
{
    /* VSHT2B is SUP; VSHT1B, VSHROD and VSPIRL are ETH. */
    return item_id == 0x11 || item_id == 0x12 ? 1U : 2U;
}

static GameDefenseProjectile *allocate_defense_projectile(GameSession *session)
{
    unsigned int index;
    unsigned int active_count = 0;
    for (index = 0; index < 32; ++index) {
        if (session->defense_projectiles[index].active != 0) ++active_count;
    }
    if (active_count + session->active_cast_effect_count +
            session->active_attack_effect_count >= 32U) return NULL;
    for (index = 0; index < 32; ++index)
        if (session->defense_projectiles[index].active == 0)
            return &session->defense_projectiles[index];
    return NULL;
}

static void begin_defense_impact(GameSession *session,
                                GameDefenseProjectile *projectile,
                                uint8_t realm,
                                int32_t damage,
                                uint16_t x,
                                uint16_t y)
{
    unsigned int level;
    if (session == NULL || projectile == NULL || damage <= 0 || realm >= 4U)
        return;
    level = (unsigned int)damage / 2U;
    if (level >= 4U) level = 3U;
    projectile->impact_phase = 1;
    projectile->effect_sheet_index = realm;
    projectile->animation_tick = 0;
    projectile->impact_frame_start =
        session->effect_impact_frame_starts[realm][level];
    projectile->impact_frame_count =
        session->effect_impact_frame_counts[realm][level];
    projectile->x = x;
    projectile->y = y;
}

static void tick_defense_projectiles(GameSession *session)
{
    unsigned int index;
    for (index = 0; index < 32; ++index) {
        GameDefenseProjectile *projectile = &session->defense_projectiles[index];
        GameFloaterStart *floater_target = NULL;
        GameRuntimeLocation *site_target = NULL;
        uint16_t target_x;
        uint16_t target_y;
        int32_t dx;
        int32_t dy;
        double distance;
        int32_t step_x;
        int32_t step_y;
        int32_t chebyshev;
        if (projectile->active == 0) continue;
        if (projectile->impact_phase != 0) {
            unsigned int impact_lifetime =
                ((unsigned int)projectile->impact_frame_count + 1U) * 2U;
            if (projectile->animation_tick < UINT8_MAX)
                ++projectile->animation_tick;
            if (projectile->animation_tick >= impact_lifetime)
                projectile->active = 0;
            continue;
        }
        if (projectile->target_floater >= 0) {
            if ((unsigned int)projectile->target_floater >= session->floater_count) {
                projectile->active = 0;
                continue;
            }
            floater_target = &session->floaters[
                (unsigned int)projectile->target_floater];
            if (!game_session_floater_is_active(floater_target) ||
                (floater_target->source_runtime_flags & 0x008U) != 0 ||
                floater_target->island_index != projectile->island_index) {
                projectile->active = 0;
                continue;
            }
            target_x = floater_target->x;
            target_y = floater_target->y;
        } else {
            if (projectile->island_index >= session->island_count ||
                projectile->target_location < 0 ||
                (uint16_t)projectile->target_location >=
                    session->islands[projectile->island_index].location_count) {
                projectile->active = 0;
                continue;
            }
            site_target = &session->islands[projectile->island_index].locations[
                (uint16_t)projectile->target_location];
            if (site_target->renderer_class != 0 || site_target->owner_id < 0 ||
                site_target->owner_id >= GAME_START_PLAYER_COUNT ||
                (site_target->source_flags & 0x280U) != 0) {
                projectile->active = 0;
                continue;
            }
            target_x = site_target->x;
            target_y = site_target->y;
        }
        dx = (int32_t)target_x - (int32_t)projectile->x;
        dy = (int32_t)target_y - (int32_t)projectile->y;
        chebyshev = dx < 0 ? -dx : dx;
        if ((dy < 0 ? -dy : dy) > chebyshev)
            chebyshev = dy < 0 ? -dy : dy;
        if (chebyshev < 6) {
            if (floater_target != NULL) {
                int32_t damage = game_session_damage_floater_from_power(session,
                    (unsigned int)projectile->target_floater,
                    projectile->attack_power);
                begin_defense_impact(session, projectile,
                    projectile->impact_realm_index, damage, target_x, target_y);
                if (projectile->impact_phase != 0) continue;
            } else if (site_target != NULL) {
                int32_t damage = game_session_damage_site_from_power(session,
                    projectile->island_index,
                    (uint16_t)projectile->target_location,
                    projectile->attack_power > 0
                        ? projectile->attack_power : 1);
                begin_defense_impact(session, projectile,
                    projectile->impact_realm_index, damage, target_x, target_y);
                if (projectile->impact_phase != 0) continue;
            }
            projectile->active = 0;
            continue;
        }
        distance = sqrt((double)dx * dx + (double)dy * dy);
        if ((double)projectile->movement_speed >= distance) {
            projectile->x = target_x;
            projectile->y = target_y;
        } else if (distance > 0.0) {
            double scale = (double)projectile->movement_speed / distance;
            double x_delta = (double)dx * scale;
            double y_delta = (double)dy * scale;
            int32_t x_whole = (int32_t)x_delta;
            int32_t y_whole = (int32_t)y_delta;
            double x_fraction = x_delta - x_whole;
            double y_fraction = y_delta - y_whole;
            if (x_fraction > 0.5 || (x_fraction == 0.5 && (x_whole & 1)))
                ++x_whole;
            else if (x_fraction < -0.5 ||
                     (x_fraction == -0.5 && (x_whole & 1))) --x_whole;
            if (y_fraction > 0.5 || (y_fraction == 0.5 && (y_whole & 1)))
                ++y_whole;
            else if (y_fraction < -0.5 ||
                     (y_fraction == -0.5 && (y_whole & 1))) --y_whole;
            step_x = x_whole;
            step_y = y_whole;
            projectile->x = (uint16_t)((int32_t)projectile->x + step_x);
            projectile->y = (uint16_t)((int32_t)projectile->y + step_y);
        }
        if (projectile->animation_tick < UINT8_MAX)
            ++projectile->animation_tick;
    }
}

static void tick_leviathan_defense(GameSession *session,
                                  const PadCatalog *pad_catalog,
                                  GameRuntimeIsland *island,
                                  GameRuntimeLocation *state,
                                  const BuildingRenderItem *item,
                                  unsigned int location_index)
{
    int16_t candidate_floaters[5];
    unsigned int candidate_count = 0;
    unsigned int candidate_index;
    int32_t item_id = game_session_base_item_id(state);
    const PadCatalogItem *pad = pad_catalog_find(
        pad_catalog, (uint16_t)state->record_value_10);
    int32_t reach = pad != NULL ? pad->movement_cost[0] : 0;
    int32_t attack_tick = item->prod.present
        ? (int32_t)item->prod.ticks_per_frame : 30;
    int32_t cycle_limit = item->prod.present
        ? (int32_t)item->prod.threshold : 40;
    uint8_t island_index = (uint8_t)(island - session->islands);
    int started_cycle = 0;

    if (reach < 0) reach = 0;
    if ((state->source_flags & 1U) == 0) return;

    /* FUN_00450a71 scans this island's active floater table. Its target
       record +0x36 is a floater slot, not a pad/location index. */
    if ((state->source_flags & 0x002U) == 0 &&
        state->resource_retry_tick_36 == -1 &&
        (session->simulation_tick + 10U - (location_index % 10U)) % 10U == 0) {
        for (candidate_index = 0; candidate_index < session->floater_count;
             ++candidate_index) {
            const GameFloaterStart *target = &session->floaters[candidate_index];
            if (!game_session_floater_is_active(target) ||
                target->owner_slot >= GAME_START_PLAYER_COUNT ||
                target->type_index >= 4U || target->island_index != island_index ||
                (target->source_runtime_flags & 0x108U) != 0 ||
                chebyshev_distance(state->x, state->y,
                                   target->x, target->y) > reach) continue;
            candidate_floaters[candidate_count++] = (int16_t)candidate_index;
            break;
        }
        if (candidate_count != 0) {
            if (item_id >= 0x10) state->resource_retry_tick_36 =
                candidate_floaters[0];
            state->source_flags |= 0x002U;
            state->production_progress = 0;
            state->source_value_42 = 0;
            started_cycle = 1;
        }
    }

    /* The native update advances PROD before its item-specific switch can
       start a new cycle, so the first progress tick is the following update. */
    if (started_cycle) return;
    if ((state->source_flags & 0x002U) == 0) return;
    if (item_id >= 0x10 && (state->resource_retry_tick_36 < 0 ||
        (unsigned int)state->resource_retry_tick_36 >= session->floater_count ||
        !game_session_floater_is_active(&session->floaters[
            (unsigned int)state->resource_retry_tick_36]) ||
        session->floaters[(unsigned int)state->resource_retry_tick_36].owner_slot >=
            GAME_START_PLAYER_COUNT ||
        session->floaters[(unsigned int)state->resource_retry_tick_36].type_index >= 4U ||
        session->floaters[(unsigned int)state->resource_retry_tick_36].island_index !=
            island_index ||
        (session->floaters[(unsigned int)state->resource_retry_tick_36].source_runtime_flags &
         0x108U) != 0)) {
        state->resource_retry_tick_36 = -1;
        state->source_flags &= ~0x002U;
        state->production_progress = 0;
        state->source_value_42 = 0;
        return;
    }

    if (state->production_progress < UINT16_MAX) ++state->production_progress;
    state->source_value_42 = (int16_t)state->production_progress;
    if (cycle_limit <= 0) cycle_limit = 30;
    if ((int32_t)state->production_progress == attack_tick) {
        unsigned int target_index = (unsigned int)state->resource_retry_tick_36;
        if (item_id < 0x10) {
            candidate_count = 0;
            for (candidate_index = 0; candidate_index < session->floater_count;
                 ++candidate_index) {
                const GameFloaterStart *target =
                    &session->floaters[candidate_index];
                if (!game_session_floater_is_active(target) ||
                    target->owner_slot >= GAME_START_PLAYER_COUNT ||
                    target->type_index >= 4U ||
                    target->island_index != island_index ||
                    (target->source_runtime_flags & 0x108U) != 0 ||
                    chebyshev_distance(state->x, state->y,
                                       target->x, target->y) > reach) continue;
                if (candidate_count < 5U)
                    candidate_floaters[candidate_count++] =
                        (int16_t)candidate_index;
            }
            if (candidate_count != 0) {
                target_index = (unsigned int)candidate_floaters[
                    tone_rng_bounded(&session->random_state,
                        (int32_t)candidate_count)];
                {
                    GameFloaterStart *target = &session->floaters[target_index];
                    int32_t damage = game_session_damage_floater_from_power(
                        session, target_index, target->attack_strength);
                    GameDefenseProjectile *impact =
                        damage > 0 ? allocate_defense_projectile(session) : NULL;
                    if (impact != NULL) {
                        impact->active = 1;
                        impact->island_index = island_index;
                        impact->impact_realm_index =
                            leviathan_projectile_impact_realm(item_id);
                        impact->target_floater = -1;
                        impact->target_location = -1;
                        impact->attack_power = 0;
                        impact->movement_speed = 0;
                        begin_defense_impact(session, impact,
                            impact->impact_realm_index, damage,
                            target->x, target->y);
                    }
                }
            }
        } else {
            uint8_t sheet = leviathan_projectile_sheet(item_id);
            int32_t attack_power =
                session->floaters[target_index].attack_strength;
            if (sheet != UINT8_MAX) {
                GameDefenseProjectile *projectile =
                    allocate_defense_projectile(session);
                if (projectile != NULL) {
                    projectile->active = 1;
                    projectile->island_index = island_index;
                    projectile->effect_sheet_index = sheet;
                    projectile->animation_tick = 0;
                    projectile->impact_phase = 0;
                    projectile->impact_realm_index =
                        leviathan_projectile_impact_realm(item_id);
                    projectile->impact_frame_start = 0;
                    projectile->impact_frame_count = 0;
                    projectile->target_floater = (int16_t)target_index;
                    projectile->target_location = -1;
                    projectile->attack_power = (int16_t)attack_power;
                    /* FUN_004153b8 initializes each effect's SPEED to 5;
                       the four Leviathan bullet definitions omit SPEED. */
                    projectile->movement_speed = 5;
                    projectile->x = state->x;
                    projectile->y = state->y;
                } else {
                    (void)game_session_damage_floater_from_power(session,
                        target_index, attack_power);
                }
            } else {
                (void)game_session_damage_floater_from_power(session,
                    target_index, attack_power);
            }
        }
    }
    if ((int32_t)state->production_progress >= cycle_limit) {
        state->resource_retry_tick_36 = -1;
        state->source_flags &= ~0x002U;
        state->production_progress = 0;
        state->source_value_42 = 0;
    }
}

static void tick_inci_animation(GameSession *session,
                                GameRuntimeLocation *state,
                                const BuildingRenderItem *item)
{
    uint8_t delay;
    int16_t threshold;

    if (!item->inci.present) return;

    /* FUN_00450a71 stores an inactive sentinel in +0x3e. For delays below
       100 it rolls delay*delay+1 and starts the INCI phase only on zero. */
    delay = (uint8_t)item->inci.ticks_per_frame;
    threshold = (int16_t)item->inci.fallback_frame;
    if (state->source_value_3e == -1 && delay < 100U) {
        uint32_t range = (uint32_t)delay * delay + 1U;
        if (tone_rng_bounded(&session->random_state, (int32_t)range) == 0)
            state->source_value_3e = 0;
    } else {
        if (state->source_value_3e == INT16_MAX)
            state->source_value_3e = INT16_MIN;
        else
            ++state->source_value_3e;
        if (threshold <= state->source_value_3e)
            state->source_value_3e = -1;
    }

    /* Keep the render-facing mirror synchronized while preserving the raw
       source sentinel, which means the INCI layer is currently inactive. */
    state->inci_progress = state->source_value_3e < 0
        ? 0U : (uint16_t)state->source_value_3e;
}

static void tick_source_staff_cycle(GameSession *session,
                                    GameRuntimeLocation *source,
                                    const FloaterCatalog *floater_catalog,
                                    uint8_t island_index,
                                    unsigned int location_index)
{
    unsigned int slot;
    int32_t base_item_id;
    int16_t existing_by_level[3] = {0, 0, 0};
    int16_t need_by_level[3];
    int32_t source_level;
    int32_t difficulty;
    int32_t stock_available;
    unsigned int worker_index;
    int current_worker_active = 0;

    if (source->owner_id < 0 || source->owner_id >= GAME_START_PLAYER_COUNT)
        return;
    base_item_id = source->record_value_10 - source->owner_id * 16;
    if (base_item_id < 0x2c || base_item_id > 0x32 ||
        (source->source_flags & 0x90U) != 0) return;

    /* FUN_0045cd75 clears OCCU at the start of each staff-building update,
       then sets it again if a worker occupies the training slot. */
    source->source_flags &= ~0x008U;

    source_level = source->source_capacity_4a;
    if (source_level < 0) source_level = 0;
    if (source_level > 2) source_level = 2;
    difficulty = session->config.difficulty;
    if (difficulty > 4) difficulty = 4;
    stock_available = source->resource_stock[1] > 9;
    for (slot = 0; slot < 8; ++slot) {
        int16_t index = source->charge_floater_slots[slot];
        if (index < 0 || (unsigned int)index >= session->floater_count) continue;
        worker_index = (unsigned int)index;
        {
            uint16_t level = session->floaters[worker_index].attack_level_flags & 0x0fU;
            if (level < 3U) ++existing_by_level[level];
        }
    }
    for (slot = 0; slot < 3; ++slot)
        need_by_level[slot] = (int16_t)(
            source_staff_target_counts[base_item_id - 0x2b][source_level][slot] -
            existing_by_level[slot]);

    for (slot = 0; slot < 8; ++slot) {
        int16_t index = source->charge_floater_slots[slot];
        GameFloaterStart *floater;
        const FloaterStats *stats;
        uint32_t progress;
        uint32_t increment;
        uint16_t level;

        if (index < 0 || (unsigned int)index >= session->floater_count) continue;
        floater = &session->floaters[(unsigned int)index];
        if ((floater->source_runtime_flags & 0x20U) == 0) {
            int32_t threshold;
            int32_t weighted_threshold;

            if (floater->source_subtype == 2U &&
                (source->source_flags & 1U) != 0)
                source->source_flags |= 0x008U;

            level = (uint16_t)(floater->attack_level_flags & 0x0fU);
            if (source->charge_recent_floater != -1 ||
                source->charge_staff_task_handle != -1 ||
                level >= 2U || level >= source_staff_level_caps[
                    floater->source_subtype <= 8 ? floater->source_subtype : 0] ||
                level >= (uint16_t)source_level || need_by_level[level + 1U] == 0 ||
                !stock_available || floater->source_subtype > 8) continue;

            weighted_threshold = (4 - difficulty) *
                source_staff_threshold_low[floater->source_subtype][level] +
                difficulty * source_staff_threshold_high[floater->source_subtype][level];
            threshold = weighted_threshold / 4;
            if (threshold <= 0 ||
                threshold > (int16_t)floater->source_progress_08) continue;
            source->charge_recent_floater = index;
            continue;
        }

        /* The active worker is visible through the building's OCCU layer. */
        source->source_flags |= 0x008U;

        /* FUN_0045cd75 adds source +0x32 (initialized to 1 by FUN_004528ca)
           for each linked worker in the active-work branch. */
        increment = source->animation_rate;
        if (increment == 0) increment = 1;
        progress = (uint32_t)source->charge_source_value_30 + increment;
        source->charge_source_value_30 = (uint16_t)progress;
        if ((int16_t)source->charge_source_value_30 < 251) {
            /* FUN_0045cd75 writes native BARG double +0x50 from +0x30 / 250
               only below 251; at/above the threshold +0x30 still keeps the
               incremented short while the training side effect runs. */
            source->barg_progress =
                (double)(int16_t)source->charge_source_value_30 / 250.0;
            continue;
        }

        /* At 251, FUN_0045cd75 trains subtype 0 to the source class, then
           advances an already trained floater's low-nibble level. */
        if (floater->source_subtype == 0) {
            floater->source_subtype = (uint8_t)(base_item_id - 0x2b);
            floater->attack_level_flags &= 0xfff0U;
        } else {
            level = (uint16_t)(floater->attack_level_flags & 0x0fU);
            if (level < 5U) ++level;
            else level = 5U;
            floater->attack_level_flags = (uint16_t)(
                (floater->attack_level_flags & 0xfff0U) | level);
        }

        stats = floater_catalog_find(floater_catalog, floater->type_index,
                                     floater->source_subtype);
        if (stats != NULL) {
            int32_t trained_strength;
            level = (uint16_t)(floater->attack_level_flags & 0x0fU);
            floater->charge_current = stats->attack_strength;
            /* FUN_00420f28 scales max-attack-points with the trained level.
               Category 4 uses its distinct 7n+10 multiplier. Its tribe and
               linked-building bonuses require mask bits from DAT_00619242;
               that table is zero in the loaded image, and no runtime writer
               is established, so those conditional bonuses remain unmodeled. */
            if (floater->type_index == 4) {
                trained_strength = (stats->max_attack_points *
                                    ((int32_t)level * 7 + 10)) / 10;
            } else {
                trained_strength = (stats->max_attack_points *
                                    ((int32_t)level + 2)) / 2;
            }
            if (trained_strength > INT16_MAX) trained_strength = INT16_MAX;
            if (trained_strength < INT16_MIN) trained_strength = INT16_MIN;
            floater->max_attack_points = (int16_t)trained_strength;
            level = (uint16_t)(floater->attack_level_flags & 0x0fU);
            if (level > 0 && level <= 3U)
                --need_by_level[level - 1U];
        }
        /* FUN_0045c82f clears the current worker, then FUN_00421ec1(-1)
           ends its active source action and clears runtime mask 0x65. */
        floater->source_runtime_flags &= ~0x65U;
        floater->movement_state = 0;
        floater->active_order_action = 0;
        floater->has_move_order = 0;
        source->charge_recent_floater = -1;
        if (source->charge_staff_task_handle >= 0 &&
            source->charge_staff_task_handle < GAME_SESSION_MAX_PENDING_EVENTS) {
            (void)game_session_pending_event_release(
                session, (uint8_t)source->charge_staff_task_handle);
            source->charge_staff_task_handle = -1;
        }
    }

    {
        int16_t current = source->charge_recent_floater;
        if (current >= 0 && (unsigned int)current < session->floater_count)
            current_worker_active =
                (session->floaters[(unsigned int)current].source_runtime_flags &
                 0x20U) != 0;
    }
    /* FUN_0045cd75 fades +0x50 by 0.25 when its current worker is no longer
       active; FUN_0040bf98 maps that normalized value onto BARG frames. */
    if (source->barg_progress > 0.0) {
        if (!current_worker_active) {
            source->barg_progress -= 0.25;
            if (source->barg_progress < 0.0) source->barg_progress = 0.0;
        }
    }

    if (source->resource_stock[1] <= 9U &&
        source->charge_staff_task_handle >= 0 &&
        !current_worker_active) {
        (void)game_session_pending_event_release(
            session, (uint8_t)source->charge_staff_task_handle);
        source->charge_staff_task_handle = -1;
    } else if (need_by_level[0] != 0 &&
               source->charge_recent_floater == -1 &&
               source->charge_staff_task_handle == -1 && stock_available) {
        /* FUN_0045c325 confirms source-table header words [0]/[1] are the
           island and location indices used by this task's payload. */
        int task_slot = game_session_pending_event_add(
            session, (int16_t)source->owner_id, (int16_t)island_index, 0x0b,
            (int16_t)location_index, 0, 0);
        if (task_slot >= 0) source->charge_staff_task_handle = (int16_t)task_slot;
    }
}

void game_session_tick_item_animations_with_floaters(
    GameSession *session, const struct BuildingRenderCatalog *catalog,
    const FloaterCatalog *floater_catalog, const PadCatalog *pad_catalog)
{
    unsigned int island_index;
    if (session == NULL || catalog == NULL) return;
    ++session->simulation_tick;
    tick_defense_projectiles(session);
    for (island_index = 0; island_index < session->island_count; ++island_index) {
        GameRuntimeIsland *island = &session->islands[island_index];
        unsigned int location_index;
        for (location_index = 0; location_index < island->location_count; ++location_index) {
            GameRuntimeLocation *state = &island->locations[location_index];
            const BuildingRenderItem *item;
            uint32_t duration;
            int construction_completed = 0;
            int production_completed = 0;
            int active_flag_changed;

            if (state->renderer_class > 2) continue;

            /* FUN_00450a71's raw item 0x2a case generates one Build Tone
               every 256 global ticks, capped at 20 in source +0x28. */
            if (game_session_base_item_id(state) == 0x2a &&
                (session->simulation_tick & 0xffU) == 0 &&
                state->resource_stock[GAME_RESOURCE_BUILD_TONE] < 20U) {
                ++state->resource_stock[GAME_RESOURCE_BUILD_TONE];
            }

            /* FUN_00450a71 shares +0x48 between the initial 0x010 timer and
               the upgrade 0x020 timer. At exactly 100, FUN_00452fcb clears
               layer counters and flags 1..3 before the caller clears 0x010. */
            if ((state->source_flags & 0x010U) != 0) {
                state->source_value_48 = (int16_t)(
                    (uint16_t)state->source_value_48 + 1U);
                if (state->source_value_48 == 100) {
                    uint16_t preserved_chug = state->chug_progress;
                    state->source_flags &= ~0x00eU;
                    state->source_value_3a = 0;
                    state->source_value_3c = 0;
                    state->source_value_3e = -1;
                    state->source_value_40 = 0;
                    state->source_value_42 = 0;
                    state->source_value_44 = 0;
                    state->source_value_46 = 0;
                    state->source_value_48 = 0;
                    state->chug_progress = 0;
                    if (state->renderer_class == 1 &&
                        state->record_value_10 == 5) {
                        state->source_value_3a = preserved_chug;
                        state->chug_progress = preserved_chug;
                    }
                    state->glyph_progress = 0;
                    state->inci_progress = 0;
                    state->construction_progress = 0;
                    state->production_progress = 0;
                    state->source_flags &= ~0x010U;
                    (void)game_session_recalculate_location_active_with_visibility(
                        state);
                }
            }

            /* FUN_00450a71 advances runtime +0x48 while upgrade bit 0x020 is
               set, then clears the bit after the counter passes 0x17. BASE
               rendering uses that bit to show the transition frame. */
            if ((state->source_flags & 0x020U) != 0) {
                state->source_value_48 = (int16_t)(
                    (uint16_t)state->source_value_48 + 1U);
                if (state->source_value_48 > 0x17)
                    state->source_flags &= ~0x020U;
            }

            /* Lethal site damage sets 0x080 and resets +0x48. The native tick
               clears the site once the shared short passes 100, through
               FUN_00452ae7/FUN_00452a15. */
            if ((state->source_flags & 0x080U) != 0) {
                state->source_value_48 = (int16_t)(
                    (uint16_t)state->source_value_48 + 1U);
                if (state->source_value_48 > 100) {
                    state->source_flags &= ~0x080U;
                    game_session_clear_cast_site(session,
                        (uint8_t)island_index, (uint16_t)location_index, state);
                    continue;
                }
            }

            /* FUN_00450a71 has two POOL-specific class-1 counter sequences.
               ID 0 loops 0..89; ID 5 advances to 125 then restarts at 102.
               FUN_0040bf98 later maps each counter through POOL's CHUG segment. */
            if (state->renderer_class == 1 &&
                (state->record_value_10 == 0 ||
                 state->record_value_10 == ISLAND_TONE_POOL_ITEM_ALTERNATE)) {
                state->chug_progress = island_tone_pool_next_counter(
                    state->record_value_10, state->chug_progress);
                continue;
            }

            if (state->renderer_class == 0 && floater_catalog != NULL)
                tick_source_staff_cycle(session, state, floater_catalog,
                                        (uint8_t)island_index, location_index);

            /* FUN_00450a71's item-5 growth switch runs for both class-0 and
               class-1 sites. Class-1 POOL animation has its own early path
               below, so resolve the spawn before that path can return. */
            if (tick_item5_spawn(session, pad_catalog, state,
                                 island_index)) continue;

            /* FUN_00450a71 advances raw +0x30 for runtime item IDs 4 and
               0x16 while active, stopping at 0x20. */
            if ((state->record_value_10 == 4 ||
                 state->record_value_10 == 0x16) &&
                (state->source_flags & 1U) != 0 &&
                (int16_t)state->charge_source_value_30 < 0x20) {
                state->charge_source_value_30 = (uint16_t)(
                    state->charge_source_value_30 + 1U);
            }

            if (state->record_value_10 <= 0 ||
                state->record_value_10 >= catalog->item_count) continue;
            item = building_render_find(catalog, (uint16_t)state->record_value_10);
            if (item == NULL) continue;

            /* INCI (+0x3e) is advanced before the class-specific item switch
               in FUN_00450a71, independently of CHUG/CONS/PROD handling. */
            tick_inci_animation(session, state, item);

            if (is_leviathan_defense(state)) {
                tick_leviathan_defense(session, pad_catalog, island,
                                       state, item, location_index);
                /* Defense PROD is the visible projectile/charge animation;
                   the specialized cycle above owns its threshold and impact. */
                continue;
            }

            /* FUN_00450a71 has a separate class-1 path: items 6..9 animate
               their CHUG layer every source tick and wrap at the descriptor
               duration. They do not use the class-0 construction flag gate. */
            if (state->renderer_class == 1) {
                if (item->chug.present) {
                    duration = building_render_chug_duration(item);
                    if (duration != 0) {
                        state->chug_progress = (uint16_t)(state->chug_progress + 1U);
                        if (state->chug_progress >= duration) state->chug_progress = 0;
                    }
                }
                /* IDs 6..9 continue into the common CONS/PROD counters and
                   their item switch in FUN_00450a71 after the class-1 CHUG
                   update. POOL IDs 0 and 5 have already taken their own path. */
                if (state->record_value_10 < 6 || state->record_value_10 > 9)
                    continue;
            }

            /* FUN_00450a71 increments class-0 CHUG only while source flag bit 0
               is set; objects created by FUN_004528ca begin with it clear. */
            if (state->renderer_class == 0 &&
                (state->source_flags & 1U) != 0 && item->chug.present) {
                uint32_t increment = state->owner_id == 4 || state->animation_rate < 2
                    ? 1U : item->chug.ticks_per_frame;
                duration = building_render_chug_duration(item);
                if (duration != 0) {
                    state->chug_progress = (uint16_t)(state->chug_progress + increment);
                    if (state->chug_progress >= duration) state->chug_progress = 0;
                }
            }

            /* GLYP's +0x3c counter runs only after it is active or when both
               source flags 0x400 and 0x001 are set; it wraps at 40 ticks. */
            if (state->renderer_class == 0 && item->glyph.present &&
                (state->glyph_progress > 0 ||
                 (state->source_flags & 0x401U) == 0x401U)) {
                ++state->glyph_progress;
                if (state->glyph_progress == 40) state->glyph_progress = 0;
            }

            /* FUN_00450a71 advances PROD (+0x42) while flag 0x002 is set,
               then clears that flag at the item's +0x0c limit. The catalog's
               PROD threshold is that value. A missing descriptor uses the
               observed fallback limit 0x28. Completion side effects later in
               the source switch are still outside this animation tick port. */
            if ((state->source_flags & 0x002U) != 0) {
                uint32_t limit = item->prod.present ? item->prod.threshold : 0x28U;
                ++state->production_progress;
                if (limit <= state->production_progress) {
                    state->source_flags &= ~0x002U;
                    production_completed = 1;
                }
            }

            /* FUN_00450a71's 0x25..0x27 switch also advances raw +0x2c while
               the producer is active. After eleven ticks it resets that
               scratch counter and +0x36, allowing a waiting floater to retry
               collection instead of remaining stuck on an earlier miss. */
            if (producer_resource_code(state) != 0 &&
                (state->source_flags & 0x001U) != 0) {
                uint16_t *retry_counter = &state->resource_stock[
                    GAME_RESOURCE_MAGIC_TONE];
                ++*retry_counter;
                if (*retry_counter > 10U) {
                    *retry_counter = 0;
                    state->resource_retry_tick_36 = 0;
                }
            }

            /* FUN_00450a71 starts producer PROD cycles from source +0x0c
               when the object is running, no output is pending, and PROD is
               idle. It adds +0x32 and starts at a strict value > 0x13. */
            if (producer_resource_code(state) != 0 &&
                state->record_value_24 == 0 &&
                (state->source_flags & 0x001U) != 0 &&
                (state->source_flags & 0x002U) == 0) {
                state->producer_cadence = (uint16_t)(state->producer_cadence +
                                                     state->animation_rate);
                if (state->producer_cadence > 0x13U) {
                    state->source_flags |= 0x002U;
                    state->production_progress = 0;
                    state->producer_cadence = 0;
                }
            }

            /* In FUN_00450a71's producer switch, the next cadence check runs
               before the just-completed output is written to +0x24. A site
               reused with a preserved near-threshold cadence can therefore
               begin its next PROD cycle on this same tick. */
            if (production_completed && producer_resource_code(state) != 0 &&
                state->record_value_24 == 0) {
                state->record_value_24 = producer_resource_code(state);
            }

            /* The same source tick advances CONS (+0x40) while flag 0x004 is
               set. FUN_00456b8d resolves a construction descriptor; its +0x0a
               threshold is stored as CONS's first parameter by bldinf.txt. */
            if ((state->source_flags & 0x004U) != 0) {
                ++state->construction_progress;
                if (item->cons.present &&
                    item->cons.fallback_frame <= state->construction_progress) {
                    state->source_flags &= ~0x004U;
                    construction_completed = 1;
                }
            }

            /* FUN_00450a71 starts autonomous production on class-1 item IDs
               6..9 from +0x0c. Its interval contracts with world time,
               difficulty and island population; the chosen type-4 unit stays
               hidden under runtime flag 0x800 until PROD completes. */
            if (state->renderer_class == 1 &&
                state->record_value_10 >= 6 && state->record_value_10 <= 9 &&
                (state->source_flags & 3U) == 1U) {
                int16_t rate = state->source_value_32;
                int16_t cadence;
                int threshold;
                if (rate != 0) {
                    cadence = (int16_t)(state->producer_cadence + rate);
                    state->producer_cadence = (uint16_t)cadence;
                    threshold = leviathan_spawn_threshold(session, island);
                    if (threshold <= cadence) {
                        state->source_flags |= 0x002U;
                        state->production_progress = 0;
                        state->producer_cadence = 0;
                        state->leviathan_spawned_floater =
                            (int16_t)spawn_leviathan_floater(
                                session, floater_catalog, island, state);
                    }
                }
            }

            /* FUN_00450a71 moves the retained type-4 record to the PROD
               output offset and clears hidden/queued bits on completion. */
            if (production_completed && state->renderer_class == 1 &&
                state->record_value_10 >= 6 && state->record_value_10 <= 9)
                release_leviathan_floater(session, state, item);

            /* FUN_00450a71 case 2 chains CONS into PROD for an unbuilt class-2
               bridge marker, then FUN_004669bd activates its paired link and
               grants access using the contributor slot stored at raw +0x2c. */
            if (state->renderer_class == 2 && state->record_value_10 == 2 &&
                (state->source_flags & 1U) == 0) {
                if (construction_completed) {
                    state->source_flags |= 0x002U;
                    state->production_progress = 0;
                } else if (production_completed) {
                    (void)game_session_mark_bridge_constructed_at(
                        session, (uint8_t)island_index, (uint16_t)location_index);
                }
            }

            /* FUN_00450a71 advances +0x46 every 16 updates while +0x58 is
               positive. State 2 rechecks activity; state 3 clears the site.
               The source tick skips ordinary empty pads unless another source
               record or timed effect keeps the object in its update path. */
            if (state->renderer_class == 0 && state->source_value_58 > 0 &&
                (state->renderer_class != 0 ||
                 (state->record_value_10 != 0 && state->record_value_10 != 1) ||
                 state->source_value_14 != -1 ||
                 (state->source_flags & 0x200U) != 0)) {
                state->source_value_46 = (int16_t)(
                    (uint16_t)state->source_value_46 + 1U);
                if (state->source_value_46 >= 16) {
                    state->source_value_46 = 0;
                    if (state->source_value_58 == 2) {
                        state->source_value_58 = 0;
                        active_flag_changed =
                            game_session_recalculate_location_active_with_visibility(
                                state);
                        if (active_flag_changed) {
                            if (state->source_value_14 == 4) {
                                game_session_recalculate_leviathan_island(session,
                                    (uint8_t)island_index);
                            } else {
                                game_session_refresh_player_maintenance_budgets(
                                    session);
                            }
                        }
                    } else if (state->source_value_58 == 3) {
                        state->source_value_58 = 0;
                        game_session_clear_cast_site(session,
                            (uint8_t)island_index, (uint16_t)location_index,
                            state);
                        continue;
                    }
                }
            }
        }
    }
}

void game_session_tick_item_animations(GameSession *session,
                                       const struct BuildingRenderCatalog *catalog)
{
    game_session_tick_item_animations_with_floaters(session, catalog, NULL, NULL);
}

