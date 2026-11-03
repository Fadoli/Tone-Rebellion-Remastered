#include "game_session.h"

#include "floater_motion.h"
#include "island_render_rules.h"
#include "pad_catalog.h"
#include "game_session_internal.h"
#include "game_session_events.h"
#include "game_session_setup_internal.h"

#include <stdio.h>
#include <string.h>

static void set_error(char *error, size_t capacity, const char *message)
{
    if (error == NULL || capacity == 0) return;
    (void)snprintf(error, capacity, "%s", message);
    error[capacity - 1] = '\0';
}

int game_session_initialize(const WorldDefinition *world,
                            const IslandData *islands_by_world_index,
                            const PadCatalog *pad_catalog,
                            const FloaterCatalog *floater_catalog,
                            const GameSessionConfig *config,
                            GameSession *out,
                            char *error, size_t error_capacity)
{
    GameSession next;
    ToneRng rng;
    int32_t shape_ids[WORLD_MAP_MAX_ISLANDS];
    int32_t bridge_neighbors[WORLD_MAP_MAX_ISLANDS][ISLAND_DATA_MAX_LOCATIONS];
    IslandData runtime_layouts[WORLD_MAP_MAX_ISLANDS];
    unsigned int island_index;

    if (error != NULL && error_capacity != 0) error[0] = '\0';
    if (world == NULL || islands_by_world_index == NULL || pad_catalog == NULL ||
        floater_catalog == NULL ||
        config == NULL || out == NULL) {
        set_error(error, error_capacity,
                  "world, island records, pad/floater catalogs, config and output are required");
        return 0;
    }
    if (world->island_count < GAME_START_PLAYER_COUNT ||
        world->island_count > WORLD_MAP_MAX_ISLANDS) {
        set_error(error, error_capacity, "world island count cannot support the four start slots");
        return 0;
    }
    if (world->bridge_count > WORLD_MAP_MAX_BRIDGES) {
        set_error(error, error_capacity, "world bridge count exceeds the original table capacity");
        return 0;
    }
    if (config->world_index >= WORLD_MAP_MAX_WORLDS || config->selected_tribe >= 4 ||
        config->home_island_index >= world->island_count) {
        set_error(error, error_capacity, "world, tribe or home-island selection is out of range");
        return 0;
    }

    memset(&next, 0, sizeof(next));
    next.config = *config;
    /* FUN_0046466f (ev_ca19bd63) sets every entry of DAT_00619290 (+0xd8,
       policy, 1 = friend) and DAT_006192a0 (+0xe8, message recipients) to 1
       for each player p and tribe k in 0..3, self included: every tribe
       starts allied with every other. FUN_00465793 subcode 10 toggles them. */
    {
        unsigned int slot;
        for (slot = 0; slot < GAME_START_PLAYER_COUNT; ++slot) {
            next.diplomacy_policy_mask[slot] =
                (uint8_t)((1U << GAME_START_PLAYER_COUNT) - 1U);
            next.message_recipient_mask[slot] =
                (uint8_t)((1U << GAME_START_PLAYER_COUNT) - 1U);
        }
    }
    {
        unsigned int row;
        memcpy(next.attack_effect_defs, floater_catalog->effects,
               sizeof(next.attack_effect_defs));
        for (row = 0; row < FLOATER_CATALOG_ROW_COUNT; ++row) {
            next.attack_effect_row_def[row] =
                floater_catalog->rows[row].attack_effect_def;
            next.attack_effect_row_offset_x[row] =
                floater_catalog->rows[row].attack_offset_x;
            next.attack_effect_row_offset_y[row] =
                floater_catalog->rows[row].attack_offset_y;
            next.grasp_row_offset_x[row] =
                floater_catalog->rows[row].grasp_offset_x;
            next.grasp_row_offset_y[row] =
                floater_catalog->rows[row].grasp_offset_y;
        }
    }
    memcpy(next.effect_impact_frame_counts, floater_catalog->impact_frame_counts,
           sizeof(next.effect_impact_frame_counts));
    memcpy(next.effect_impact_frame_starts, floater_catalog->impact_frame_starts,
           sizeof(next.effect_impact_frame_starts));
    next.island_count = world->island_count;
    next.world_bridge_count = world->bridge_count;
    memcpy(next.world_bridges, world->bridges,
           (size_t)world->bridge_count * sizeof(world->bridges[0]));
    if (!game_session_prepare_runtime_layouts(world, islands_by_world_index, runtime_layouts,
                                 bridge_neighbors,
                                 error, error_capacity)) {
        return 0;
    }
    if (!game_session_initialize_start_islands(&next, world, runtime_layouts,
            bridge_neighbors, shape_ids, error, error_capacity)) return 0;

    if (!game_start_assign_locations(runtime_layouts, world->island_count,
                                     config->mode, config->alternate_island,
                                     &next.player_starts, error, error_capacity)) {
        return 0;
    }
    if (!game_session_initialize_start_players(&next, runtime_layouts,
            floater_catalog, error, error_capacity)) return 0;

    tone_rng_seed(&rng, config->random_seed);
    /* FUN_004637fc: (-(rand(2) != 0) & 2) - 1 for each step. */
    next.realm_cycle_a = 5000;
    next.realm_cycle_b = 4000;
    next.realm_step_a = tone_rng_bounded(&rng, 2) != 0 ? 1 : -1;
    next.realm_step_b = tone_rng_bounded(&rng, 2) != 0 ? 1 : -1;
    /* FUN_00464b9e first places one seal per other island on the last
       island: rand(record count) until a class-0 record with size +0x0c 0,
       then +0x10 = 0x17 + island, +0x14 = 4 and +0x34 = 30000. It neither
       tests that the record is free (a repeated pick overwrites the earlier
       seal) nor runs FUN_004528ca. The native loop never ends without a
       candidate; the port skips placement then. */
    if (world->island_count > 1) {
        const IslandData *layout = &runtime_layouts[world->island_count - 1];
        GameRuntimeIsland *last = &next.islands[world->island_count - 1];
        unsigned int candidates = 0;
        unsigned int seal;
        for (seal = 0; seal < layout->location_count; ++seal) {
            if (layout->locations[seal].renderer_class == 0 &&
                layout->locations[seal].renderer_subtype == 0) ++candidates;
        }
        for (seal = 0; candidates != 0 &&
                 seal + 1U < (unsigned int)world->island_count; ++seal) {
            int32_t pick;
            do {
                pick = tone_rng_bounded(&rng, (int32_t)layout->location_count);
            } while (layout->locations[pick].renderer_class != 0 ||
                     layout->locations[pick].renderer_subtype != 0);
            last->locations[pick].record_value_10 = (int32_t)(0x17U + seal);
            last->locations[pick].owner_id = 4;
            last->locations[pick].source_value_14 = 4;
            last->locations[pick].source_value_34 = 30000;
        }
    }
    if (!game_start_distribute_tones(runtime_layouts, shape_ids,
                                     world->island_count,
                                     /* FUN_004535e4 opens all four families
                                        on island DAT_006136b0 - 1: the
                                        island count minus one, i.e. the
                                        Leviathan's last island. */
                                     (size_t)world->island_count - 1U,
                                     config->mode, &rng, &next.tone_placements,
                                     error, error_capacity)) {
        return 0;
    }
    for (island_index = 0; island_index < next.tone_placements.placement_count; ++island_index) {
        const GameStartTonePlacement *placement = &next.tone_placements.placements[island_index];
        GameRuntimeIsland *runtime;
        if (placement->island_index >= next.island_count) {
            set_error(error, error_capacity, "tone placement references a missing island");
            return 0;
        }
        runtime = &next.islands[placement->island_index];
        if (placement->location_index >= runtime->location_count) {
            set_error(error, error_capacity, "tone placement references a missing location");
            return 0;
        }
        {
            GameRuntimeLocation *location =
                &runtime->locations[placement->location_index];
            /* FUN_00464b9e creates neutral class-1 marker items through
               FUN_00452859(item, 4), whose FUN_004528ca initializer stores
               the same owner at +0x14 and sets +0x32/+0x3e. */
            location->record_value_10 = placement->item_id;
            location->owner_id = placement->owner_id;
            location->source_value_14 = placement->owner_id;
            location->source_value_32 = 1;
            location->source_value_3e = -1;
        }
    }

    for (island_index = 0; island_index < world->island_count; ++island_index) {
        unsigned int location_index;
        for (location_index = 0; location_index < runtime_layouts[island_index].location_count;
             ++location_index) {
            if (runtime_layouts[island_index].locations[location_index].renderer_class == 2) {
                next.islands[island_index].locations[location_index].record_value_10 = 2;
            }
        }
    }
    if (!game_session_assign_initial_sites(world, runtime_layouts, shape_ids,
                                           &next, &rng, error, error_capacity)) {
        return 0;
    }
    next.random_state = rng;

    /* FUN_004528ca starts newly instantiated pad objects with flags 0x410,
       zeroed animation fields, and animation-rate field +0x32 set to 1.
       Buildings present at game start show no placement ramp (0x10):
       FUN_0046466f clears it on each starting Hall right after
       FUN_00452859 (0x464abc..0x464ac5), and the island loader FUN_00461b3b
       never sets it (REA haiku 2026-11-03, ev_3cb7946b, ev_4d4899a8). */
    for (island_index = 0; island_index < next.island_count; ++island_index) {
        GameRuntimeIsland *runtime = &next.islands[island_index];
        unsigned int location_index;
        for (location_index = 0; location_index < runtime->location_count; ++location_index) {
            GameRuntimeLocation *state = &runtime->locations[location_index];
            const PadCatalogItem *pad_item = NULL;
            state->resource_retry_tick_36 = -1;
            if (state->record_value_10 > 0 &&
                state->record_value_10 <= (int32_t)UINT16_MAX &&
                state->renderer_class <= 1) {
                pad_item = pad_catalog_find(pad_catalog,
                    (uint16_t)state->record_value_10);
            }
            state->maintenance_tone_cost = pad_item != NULL
                ? pad_item->maintenance_tone_cost : 0;
            state->new_build_animation_ticks = 0;
            if (state->record_value_10 > 0 && state->renderer_class <= 1) {
                state->source_flags = 0x400;
                state->chug_progress = 0;
                state->glyph_progress = 0;
                state->animation_rate = 1;
            }
            if (state->owner_id >= 0 &&
                state->record_value_10 > 0 &&
                !game_session_is_leviathan_seal(state->record_value_10) &&
                !game_session_source_value_34_max(pad_catalog, state, &state->source_value_34)) {
                set_error(error, error_capacity,
                          "runtime item has no pad record for source field +0x34");
                return 0;
            }
        }
    }

    for (island_index = 0; island_index < next.island_count; ++island_index) {
        next.islands[island_index].leviathan_wait_timer = -1;
        game_session_recalculate_leviathan_island(&next, (uint8_t)island_index);
    }
    for (island_index = 0; island_index < GAME_START_PLAYER_COUNT; ++island_index) {
        const GamePlayerStart *start = &next.player_starts.players[island_index];
        (void)game_session_recalculate_player_island_visibility(
            &next, start->island_index, (uint8_t)island_index);
    }
    game_session_refresh_player_maintenance_budgets(&next);
    *out = next;
    return 1;
}
