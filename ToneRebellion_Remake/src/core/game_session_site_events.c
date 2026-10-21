#include "game_session.h"
#include "game_session_events.h"
#include "game_session_internal.h"
#include "pad_catalog.h"

#include <string.h>

/* Site On/Off commands and their active-state recalculation. */

int game_session_queue_onoff_action(GameSession *session,
                                    uint8_t player_slot,
                                    uint8_t island_index,
                                    uint16_t location_index)
{
    GameOnOffActionRequest *request;
    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT ||
        island_index >= session->island_count ||
        location_index >= session->islands[island_index].location_count ||
        session->onoff_action_count >= GAME_SESSION_MAX_ONOFF_ACTIONS) {
        return 0;
    }
    request = &session->onoff_actions[session->onoff_action_count++];
    request->player_slot = player_slot;
    request->island_index = island_index;
    request->location_index = location_index;
    return 1;
}

int game_session_pop_onoff_action(GameSession *session,
                                  GameOnOffActionRequest *out)
{
    if (session == NULL || out == NULL || session->onoff_action_count == 0) {
        return 0;
    }
    *out = session->onoff_actions[0];
    --session->onoff_action_count;
    if (session->onoff_action_count != 0) {
        memmove(&session->onoff_actions[0], &session->onoff_actions[1],
                (size_t)session->onoff_action_count * sizeof(session->onoff_actions[0]));
    }
    memset(&session->onoff_actions[session->onoff_action_count], 0,
           sizeof(session->onoff_actions[session->onoff_action_count]));
    return 1;
}

static int game_session_location_active_predicate(
    const GameRuntimeLocation *location)
{
    uint32_t flags = location->source_flags;
    return (flags & 0x90U) == 0 &&
        ((flags & 0x400U) != 0 ||
         location->source_location_slot_18 != -1 ||
         location->renderer_class == 1) &&
        ((flags & 0x100U) == 0 || location->source_value_44 < 20) &&
        location->source_value_58 == 0 && location->record_value_10 >= 2;
}

static int game_session_recalculate_location_active(GameRuntimeLocation *location)
{
    uint32_t previous_flags = location->source_flags;
    uint32_t current_flags = previous_flags & ~1U;

    if (game_session_location_active_predicate(location)) current_flags |= 1U;
    location->source_flags = current_flags;
    return ((previous_flags ^ current_flags) & 1U) != 0;
}

static int visibility_x_is_spanned(int32_t x, const int32_t *span_min,
                                   const int32_t *span_max, unsigned int count)
{
    unsigned int i;
    for (i = 0; i < count; ++i) {
        if (span_min[i] <= x && x <= span_max[i]) return 1;
    }
    return 0;
}

static void add_visibility_span(int32_t low, int32_t high,
                                int32_t *span_min, int32_t *span_max,
                                unsigned int *count)
{
    unsigned int i;
    if (low < 0) low = 0;
    if (high > 0x9ff) high = 0x9ff;
    for (i = 0; i < *count; ++i) {
        if ((low < span_min[i] && span_min[i] <= high) ||
            (span_max[i] < high && low <= span_max[i])) {
            if (low < span_min[i]) span_min[i] = low;
            if (span_max[i] < high) span_max[i] = high;
            return;
        }
    }
    if (*count < 32U) {
        span_min[*count] = low;
        span_max[*count] = high;
        ++*count;
    }
}

static int recalculate_island_visibility_for_player(
    const GameSession *session, GameRuntimeIsland *island,
    uint8_t player_slot)
{
    /* FUN_00462285 grows visible x spans from class-1 markers, constructed
       bridges, and active owned item 0x28 sites, then writes +0x22 masks. */
    uint8_t visible[ISLAND_DATA_MAX_LOCATIONS] = {0};
    int32_t span_min[32];
    int32_t span_max[32];
    unsigned int span_count = 0;
    unsigned int index;
    unsigned int capacity = 0;
    uint32_t player_bit = 1U << player_slot;
    int expanded;

    if (session->economy[player_slot].island_visibility_override != 0) {
        for (index = 0; index < island->location_count; ++index) {
            GameRuntimeLocation *location = &island->locations[index];
            if (location->source_value_14 == 4)
                location->source_value_22 &= (uint16_t)~player_bit;
            else
                location->source_value_22 |= (uint16_t)player_bit;
            location->tribe_visibility_mask = (uint8_t)location->source_value_22;
            (void)game_session_recalculate_location_active_with_visibility(location);
        }
        return 10;
    }

    do {
        expanded = 0;
        for (index = 0; index < island->location_count; ++index) {
            GameRuntimeLocation *location = &island->locations[index];
            int connects = 0;
            int radius = 0;

            if (visible[index] != 0 || location->source_value_14 == 4) continue;
            if (location->renderer_class == 1) {
                connects = (location->source_value_22 & player_bit) != 0 ||
                    visibility_x_is_spanned(location->x, span_min,
                                            span_max, span_count);
                radius = 150;
            } else if (location->renderer_class == 2) {
                connects = (location->source_flags & 1U) != 0;
                radius = 100;
            } else if (location->renderer_class == 0 &&
                       (location->source_value_14 == player_slot ||
                        (location->source_flags & (0x800U << player_slot)) != 0) &&
                       game_session_base_item_id(location) == 0x28 &&
                       game_session_location_active_predicate(location) &&
                       visibility_x_is_spanned(location->x, span_min,
                                               span_max, span_count)) {
                connects = 1;
                radius = 300;
            }
            if (!connects) continue;
            visible[index] = 1;
            add_visibility_span((int32_t)location->x - radius,
                                (int32_t)location->x + radius,
                                span_min, span_max, &span_count);
            if (location->renderer_class == 1) ++capacity;
            expanded = 1;
        }
    } while (expanded != 0);

    for (index = 0; index < island->location_count; ++index) {
        GameRuntimeLocation *location = &island->locations[index];
        if (visible[index] == 0 && location->renderer_class == 0 &&
            location->source_value_14 != 4 &&
            visibility_x_is_spanned(location->x, span_min,
                                    span_max, span_count)) {
            visible[index] = 1;
        }
        if (visible[index] != 0) location->source_value_22 |= (uint16_t)player_bit;
        else location->source_value_22 &= (uint16_t)~player_bit;
        location->tribe_visibility_mask = (uint8_t)location->source_value_22;
        (void)game_session_recalculate_location_active_with_visibility(location);
    }
    return (int)capacity;
}

int game_session_recalculate_player_island_visibility(
    GameSession *session, uint8_t island_index, uint8_t player_slot)
{
    GameRuntimeIsland *island;

    if (session == NULL || island_index >= session->island_count ||
        player_slot >= GAME_START_PLAYER_COUNT ||
        session->islands[island_index].location_count >
            ISLAND_DATA_MAX_LOCATIONS) return 0;
    island = &session->islands[island_index];
    return recalculate_island_visibility_for_player(session, island,
                                                    player_slot);
}

void game_session_tick_site_effect_timers(GameSession *session)
{
    unsigned int island_index;
    int recalculate_active = 0;

    if (session == NULL || session->island_count > WORLD_MAP_MAX_ISLANDS) return;
    for (island_index = 0; island_index < session->island_count;
         ++island_index) {
        GameRuntimeIsland *island = &session->islands[island_index];
        unsigned int location_index;

        if (island->location_count > ISLAND_DATA_MAX_LOCATIONS) continue;
        for (location_index = 0; location_index < island->location_count;
             ++location_index) {
            GameRuntimeLocation *location = &island->locations[location_index];
            uint32_t timer_flag;

            /* FUN_00450a71 advances the 0x100/+0x44 state before its
               mutually exclusive +0x38 timer chain. It recalculates activity
               on every tick that began with 0x100 set, including expiry. */
            if ((location->source_flags & 0x100U) != 0) {
                ++location->source_value_44;
                if (location->source_value_44 > 999) {
                    location->source_value_44 = 0;
                    location->source_flags &= ~0x100U;
                }
                recalculate_active = 1;
            }

            /* FUN_00450a71 consumes one timed site state per update, in this
               priority order, using the shared +0x38 timer. */
            if ((location->source_flags & 0x200U) != 0) {
                timer_flag = 0x200U;
            } else if ((location->source_flags & 0x8000U) != 0) {
                timer_flag = 0x8000U;
            } else if ((location->source_flags & 0x20000U) != 0) {
                timer_flag = 0x20000U;
            } else if ((location->source_flags & 0x10000U) != 0) {
                timer_flag = 0x10000U;
            } else {
                continue;
            }

            if (location->source_effect_timer_38 > 0)
                --location->source_effect_timer_38;
            if (location->source_effect_timer_38 == 0)
                location->source_flags &= ~timer_flag;
        }
    }
    if (recalculate_active)
        (void)game_session_recalculate_active_locations(session);
}

static void game_session_recalculate_player_maintenance_budgets(
    GameSession *session)
{
    /* This remake model currently assigns capacity per accessible region.
       Native assembly instead passes a region sum and 0.5 to FUN_00477599;
       its wrapper loads the second double, then multiplies by 20.0, so the
       observed +0x3c write is 10 regardless of the region sum. Keep this
       divergence explicit pending a separate parity decision. */
    int32_t capacities[GAME_START_PLAYER_COUNT] = {0};
    int32_t maintenance[GAME_START_PLAYER_COUNT] = {0};
    int32_t capacity_budget[GAME_START_PLAYER_COUNT] = {0};
    unsigned int island_index;
    unsigned int floater_index;
    unsigned int player_slot;

    /* First finish all players' visibility updates so each budget observes
       the final active bits for every island. */
    for (player_slot = 0; player_slot < GAME_START_PLAYER_COUNT; ++player_slot) {
        for (island_index = 0; island_index < session->island_count;
             ++island_index) {
            GameRuntimeIsland *island = &session->islands[island_index];
            if (island->location_count > ISLAND_DATA_MAX_LOCATIONS) continue;
            capacities[player_slot] +=
                recalculate_island_visibility_for_player(
                    session, island, (uint8_t)player_slot);
        }
    }

    for (player_slot = 0; player_slot < GAME_START_PLAYER_COUNT; ++player_slot) {
        capacity_budget[player_slot] = capacities[player_slot] * 10;
        session->economy[player_slot].source_maintenance_capacity =
            capacity_budget[player_slot];

        uint32_t owned_flag = 0x800U << player_slot;
        for (island_index = 0; island_index < session->island_count;
             ++island_index) {
            const GameRuntimeIsland *island = &session->islands[island_index];
            unsigned int location_index;
            if (island->location_count > ISLAND_DATA_MAX_LOCATIONS) continue;
            for (location_index = 0; location_index < island->location_count;
                 ++location_index) {
                const GameRuntimeLocation *location =
                    &island->locations[location_index];
                if (location->renderer_class != 0 ||
                    location->record_value_10 == 0 ||
                    (location->source_flags & 1U) == 0 ||
                    (location->source_value_14 != (int32_t)player_slot &&
                     (location->source_flags & owned_flag) == 0)) continue;
                maintenance[player_slot] += location->maintenance_tone_cost;
            }
        }
        /* FUN_0045e6d3 discounts site maintenance by 15% when the player's
           glyph-ownership mask at +0x8a contains bit 13 (0x2000). */
        if ((session->economy[player_slot].glyph_mask & 0x2000U) != 0)
            maintenance[player_slot] = (maintenance[player_slot] * 0x11) / 0x14;
        for (floater_index = 0; floater_index < session->floater_count;
             ++floater_index) {
            const GameFloaterStart *floater = &session->floaters[floater_index];
            if (game_session_floater_is_active(floater) &&
                floater->type_index == player_slot) ++maintenance[player_slot];
        }
        if (maintenance[player_slot] > capacity_budget[player_slot])
            maintenance[player_slot] = capacity_budget[player_slot];
        session->economy[player_slot].source_maintenance_budget =
            capacity_budget[player_slot] - maintenance[player_slot];
    }
}

void game_session_refresh_player_maintenance_budgets(GameSession *session)
{
    if (session != NULL)
        game_session_recalculate_player_maintenance_budgets(session);
}

int game_session_recalculate_location_active_with_visibility(
    GameRuntimeLocation *location)
{
    uint32_t visibility_bit;

    if (location == NULL) return 0;
    if (location->renderer_class == 2 || location->renderer_class == 3) return 0;
    /* FUN_004539e9 refuses to set the active bit when raw +0x14 is -1,
       even if the source flags and visibility mask would otherwise qualify. */
    if (location->source_value_14 == -1) {
        uint32_t previous_flags = location->source_flags;
        location->source_flags &= ~1U;
        return (previous_flags & 1U) != 0;
    }
    visibility_bit = 1U << ((unsigned int)location->source_value_14 & 31U);
    if (location->source_value_14 != 4 &&
        (location->source_value_22 & visibility_bit) == 0) {
        uint32_t previous_flags = location->source_flags;
        location->source_flags &= ~1U;
        return (previous_flags & 1U) != 0;
    }
    return game_session_recalculate_location_active(location);
}

void game_session_recalculate_leviathan_island(GameSession *session,
                                               uint8_t island_index)
{
    static const int16_t baseline_tables[3][4][6] = {
        {{2, 2, 2, 2, 2, 2}, {3, 3, 3, 4, 4, 5},
         {3, 4, 4, 5, 5, 7}, {4, 5, 5, 6, 7, 8}},
        {{2, 3, 4, 4, 4, 5}, {4, 4, 5, 6, 7, 8},
         {5, 6, 7, 9, 10, 11}, {7, 9, 11, 12, 13, 14}},
        {{2, 3, 4, 4, 4, 5}, {4, 4, 5, 7, 9, 10},
         {5, 7, 9, 14, 16, 17}, {7, 9, 13, 17, 21, 23}}
    };
    GameRuntimeIsland *island;
    int16_t marker_locations[6];
    int marker_limit = 0;
    int class0_leviathan_sites = 0;
    int marker_count = 0;
    int floater_count = 0;
    int admissible = 1;
    int has_leviathan_order = 0;
    int difficulty;
    int island_tier;
    int baseline_table;
    int previous_admissible;
    unsigned int index;

    if (session == NULL || island_index >= session->island_count) return;
    island = &session->islands[island_index];
    if (island->location_count > ISLAND_DATA_MAX_LOCATIONS) return;
    previous_admissible = island->leviathan_admissible;
    difficulty = session->config.difficulty;
    if (difficulty < 0) difficulty = 0;
    if (difficulty > 3) difficulty = 3;
    island_tier = island_index / 4;
    if (island_tier > difficulty) island_tier = difficulty;

    for (index = 0; index < island->location_count; ++index) {
        const GameRuntimeLocation *location = &island->locations[index];
        int item_id = game_session_base_item_id(location);
        int owner = location->source_value_14;
        if (location->renderer_class == 1 && marker_limit < 6) {
            ++marker_limit;
            if (owner == 4) marker_locations[marker_count++] = (int16_t)index;
        } else if (location->renderer_class == 0 && owner == 4) {
            ++class0_leviathan_sites;
        } else if (owner == -1 ||
                   ((item_id != 0x2a || owner < 0 || owner >= GAME_START_PLAYER_COUNT) &&
                    (item_id < 0x2c || item_id > 0x2e))) {
            if (owner != -1 && item_id > 0x24 && item_id < 0x36 &&
                owner >= 0 && owner < GAME_START_PLAYER_COUNT) {
                admissible = 0;
            }
        } else {
            admissible = 0;
            has_leviathan_order = 1;
        }
    }

    for (index = 0; index < session->floater_count; ++index) {
        const GameFloaterStart *floater = &session->floaters[index];
        if (game_session_floater_is_active(floater) &&
            floater->island_index == island_index && floater->type_index == 4 &&
            floater->source_subtype != 9) ++floater_count;
    }

    island->leviathan_marker_count = (int16_t)marker_count;
    island->leviathan_remaining_markers = (int16_t)(marker_limit - marker_count);
    island->leviathan_site_budget = marker_count != 0
        ? (int16_t)((marker_count * (island_tier * 2 + 4)) -
                    class0_leviathan_sites)
        : 0;
    if (island->leviathan_site_budget < 0) island->leviathan_site_budget = 0;
    island->leviathan_floater_count = (int16_t)floater_count;
    island->leviathan_admissible = (int8_t)admissible;
    if (previous_admissible != 0 && admissible == 0)
        island->leviathan_wait_timer = -1;
    baseline_table = admissible ? 0 : (has_leviathan_order ? 2 : 1);
    if (marker_count != 0) {
        island->leviathan_floater_budget = (int16_t)
            (baseline_tables[baseline_table][difficulty][marker_count - 1] -
             floater_count);
        {
            int interval = ((island_tier + difficulty) * 2 + 10) / marker_count;
            if (island->leviathan_remaining_markers == 0 &&
                island->leviathan_site_budget == 0 &&
                island->leviathan_floater_budget == 0) interval = 0;
            for (index = 0; index < (unsigned int)marker_count; ++index) {
                GameRuntimeLocation *location = &island->locations[marker_locations[index]];
                location->leviathan_spawn_interval =
                    location->record_value_10 == 5 ? 1 : (uint16_t)interval;
            }
        }
    }
}

void game_session_tick_leviathan_ai(GameSession *session)
{
    unsigned int island_index;
    if (session == NULL) return;
    for (island_index = 0; island_index < session->island_count; ++island_index) {
        GameRuntimeIsland *island = &session->islands[island_index];
        int floater_count = 0;
        unsigned int floater_index;
        if (island->location_count > ISLAND_DATA_MAX_LOCATIONS) continue;
        if (island->leviathan_periodic_timer != 0) {
            --island->leviathan_periodic_timer;
            if (island->leviathan_periodic_timer < 2) {
                island->leviathan_periodic_timer = 0x834;
            } else if (island->leviathan_periodic_timer > 0x32 &&
                       island->leviathan_periodic_timer < 100) {
                island->leviathan_periodic_timer = 0;
            }
        }
        if (island->leviathan_admissible == 0) {
            if (island->leviathan_wait_timer < 0) {
                island->leviathan_wait_timer =
                    tone_rng_bounded(&session->random_state, 0x960) + 0x4b0;
            } else if (island->leviathan_wait_timer == 0) {
                int difficulty = session->config.difficulty;
                int island_tier = (int)island_index / 4;
                int threshold;
                int selected = 0;
                if (difficulty > 3) difficulty = 3;
                if (island_tier > difficulty) island_tier = difficulty;
                threshold = (island_tier + 2 + difficulty) / 2;
                threshold += tone_rng_bounded(&session->random_state, threshold);
                for (floater_index = 0;
                     floater_index < session->floater_count; ++floater_index) {
                    GameFloaterStart *floater = &session->floaters[floater_index];
                    if (!game_session_floater_is_active(floater) ||
                        floater->island_index != island_index ||
                        floater->type_index != 4 || floater->source_subtype == 9)
                        continue;
                    floater->source_runtime_flags |= 0x80U;
                    if (++selected >= threshold) break;
                }
                island->leviathan_wait_timer = -1;
            } else {
                for (floater_index = 0;
                     floater_index < session->floater_count; ++floater_index) {
                    const GameFloaterStart *floater = &session->floaters[floater_index];
                    if (game_session_floater_is_active(floater) &&
                        floater->island_index == island_index &&
                        floater->type_index == 4 && floater->source_subtype != 9)
                        ++floater_count;
                }
                if (floater_count > 2) --island->leviathan_wait_timer;
            }
        }
    }
}

unsigned int game_session_recalculate_active_locations(GameSession *session)
{
    unsigned int island_index;
    unsigned int changed = 0;
    int visibility_changed = 0;

    if (session == NULL) return 0;
    for (island_index = 0; island_index < session->island_count; ++island_index) {
        GameRuntimeIsland *island = &session->islands[island_index];
        unsigned int location_index;
        uint8_t visibility_refresh = 0;

        for (location_index = 0; location_index < island->location_count;
             ++location_index) {
            GameRuntimeLocation *location = &island->locations[location_index];
            int was_active = (location->source_flags & 1U) != 0;
            /* FUN_00453a5f recalculates through FUN_004539e9, including the
               owner-visibility gate, for each changed site. */
            changed += (unsigned int)
                game_session_recalculate_location_active_with_visibility(
                    location);
            if (was_active != ((location->source_flags & 1U) != 0) &&
                location->renderer_class == 0 &&
                game_session_base_item_id(location) == 0x28 &&
                location->owner_id >= 0 &&
                location->owner_id < GAME_START_PLAYER_COUNT) {
                visibility_refresh |= (uint8_t)(1U << location->owner_id);
            }
        }
        if (visibility_refresh != 0) {
            unsigned int player_slot;
            visibility_changed = 1;
            for (player_slot = 0; player_slot < GAME_START_PLAYER_COUNT;
                 ++player_slot) {
                if ((visibility_refresh & (uint8_t)(1U << player_slot)) != 0) {
                    (void)game_session_recalculate_player_island_visibility(
                        session, (uint8_t)island_index, (uint8_t)player_slot);
                }
            }
        }
        game_session_recalculate_leviathan_island(session, (uint8_t)island_index);
    }
    if (changed != 0 || visibility_changed)
        game_session_recalculate_player_maintenance_budgets(session);
    return changed;
}

unsigned int game_session_dispatch_onoff_actions(GameSession *session,
                                                 const PadCatalog *catalog)
{
    GameOnOffActionRequest request;
    unsigned int changed = 0;

    if (session == NULL || catalog == NULL) return 0;
    while (game_session_pop_onoff_action(session, &request)) {
        GameRuntimeLocation *location;
        const PadCatalogItem *item;
        int base_item_id;
        int was_enabled;
        int active_flag_changed;
        unsigned int subtype;

        if (request.player_slot >= GAME_START_PLAYER_COUNT ||
            request.island_index >= session->island_count ||
            request.location_index >=
                session->islands[request.island_index].location_count) {
            continue;
        }
        location = &session->islands[request.island_index]
                        .locations[request.location_index];
        base_item_id = location->record_value_10 -
                       (int)request.player_slot * 16;
        if (location->renderer_class != 0 ||
            location->owner_id != request.player_slot ||
            base_item_id < 0x25 || base_item_id > 0x27) {
            continue;
        }

        /* FUN_00453bf6 compares ON against the current +0x40 player balance.
           The source recomputes that balance when a site's active bit changes;
           refresh before evaluating this request as well so a new session has
           the same derived budget before its first toggle. */
        game_session_recalculate_player_maintenance_budgets(session);
        was_enabled = (location->source_flags & 0x400U) != 0;
        if ((location->source_flags & 0x400U) != 0) {
            location->source_flags &= ~0x400U;
        } else {
            item = location->record_value_10 >= 0 &&
                   location->record_value_10 <= (int32_t)UINT16_MAX
                ? pad_catalog_find(catalog, (uint16_t)location->record_value_10)
                : NULL;
            if (item != NULL && item->maintenance_tone_cost <=
                    session->economy[request.player_slot].source_maintenance_budget) {
                location->source_flags |= 0x400U;
            }
        }

        /* FUN_00450385 resolves the linked row; FUN_0045cbaa releases its
           subtype 1..3 task links only after the site has ended up OFF. */
        if (location->source_location_slot_18 != -1 &&
            (location->source_flags & 0x400U) == 0) {
            for (subtype = 0; subtype < GAME_RESOURCE_TYPE_COUNT; ++subtype) {
                int16_t linked_slot = location->source_task_slot[subtype];
                if (linked_slot >= 0 &&
                    linked_slot < GAME_SESSION_MAX_PENDING_EVENTS) {
                    (void)game_session_pending_event_release(
                        session, (uint8_t)linked_slot);
                }
                location->source_task_slot[subtype] = -1;
            }
        }
        /* FUN_00453bf6 ends in FUN_00453a5f/FUN_004539e9, which also
           gates the active bit by the site's +0x22 owner visibility mask. */
        active_flag_changed =
            game_session_recalculate_location_active_with_visibility(location);
        if (active_flag_changed) {
            game_session_recalculate_player_maintenance_budgets(session);
        }
        if (was_enabled != ((location->source_flags & 0x400U) != 0) ||
            active_flag_changed) ++changed;
    }
    return changed;
}
