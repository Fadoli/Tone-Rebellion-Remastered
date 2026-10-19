#include "game_session.h"

#include "floater_motion.h"
#include "island_render_rules.h"
#include "pad_catalog.h"
#include "game_session_internal.h"

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
    unsigned int floater_cursor = 0;

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
    next.island_count = world->island_count;
    if (!game_session_prepare_runtime_layouts(world, islands_by_world_index, runtime_layouts,
                                 bridge_neighbors,
                                 error, error_capacity)) {
        return 0;
    }
    for (island_index = 0; island_index < world->island_count; ++island_index) {
        const IslandData *source = &runtime_layouts[island_index];
        GameRuntimeIsland *runtime = &next.islands[island_index];
        unsigned int location_index;

        if (source->location_count > ISLAND_DATA_MAX_LOCATIONS) {
            if (error != NULL && error_capacity != 0) {
                (void)snprintf(error, error_capacity,
                               "island %u exceeds the original location capacity", island_index);
                error[error_capacity - 1] = '\0';
            }
            return 0;
        }
        shape_ids[island_index] = world->islands[island_index].shape_id;
        if (shape_ids[island_index] < 0 || shape_ids[island_index] >= 16) {
            if (error != NULL && error_capacity != 0) {
                (void)snprintf(error, error_capacity,
                               "island %u has an unsupported shape ID", island_index);
                error[error_capacity - 1] = '\0';
            }
            return 0;
        }
        runtime->location_count = source->location_count;
        runtime->source_level = 0;
        {
            unsigned int category;
            for (category = 0; category < GAME_FLOATER_CATEGORY_COUNT; ++category) {
                /* Until the source's per-category island bounds are loaded,
                   use its sentinel values for global 0..0x9ff limits. */
                runtime->floater_min_x[category] = 0;
                runtime->floater_max_x[category] = 0x9ff;
            }
        }
        for (location_index = 0; location_index < source->location_count; ++location_index) {
            const IslandLocation *location = &source->locations[location_index];
            GameRuntimeLocation *state = &runtime->locations[location_index];
            /* FUN_004500c4 initializes owner to -1 and clears +0x10 except for class 3. */
            state->record_value_10 = location->renderer_class == 3 ? location->renderer_variant : 0;
            state->owner_id = -1;
            state->source_location_slot_18 = -1;
            state->source_value_34 = -1;
            state->source_task_slot[0] = -1;
            state->source_task_slot[1] = -1;
            state->source_task_slot[2] = -1;
            state->record_value_24 = 0;
            state->bridge_neighbor_island = bridge_neighbors[island_index][location_index];
            state->x = location->x;
            state->y = location->y;
            state->renderer_class = location->renderer_class;
        }
    }

    if (!game_start_assign_locations(runtime_layouts, world->island_count,
                                     config->mode, config->alternate_island,
                                     &next.player_starts, error, error_capacity)) {
        return 0;
    }
    for (island_index = 0; island_index < GAME_START_PLAYER_COUNT; ++island_index) {
        const GamePlayerStart *start = &next.player_starts.players[island_index];
        GameRuntimeIsland *runtime = &next.islands[start->island_index];
        unsigned int location_index = start->nearest_site_location_index;
        unsigned int unit;

        for (unit = 0; unit < GAME_RESOURCE_TYPE_COUNT; ++unit)
            next.economy[island_index].resource_task_slot[unit] = -1;

        /* FUN_0046466f sets island runtime +0x29ac + player*4 for each
           player's assigned starting island; FUN_0047117d reads this flag. */
        runtime->access_mask |= (uint8_t)(1U << island_index);

        if (location_index >= runtime->location_count ||
            runtime->locations[location_index].record_value_10 != 0) {
            set_error(error, error_capacity, "initial hall location is not empty at runtime");
            return 0;
        }
        /* FUN_0046466f marks each player's selected class-1 tone location in
           object byte +0x22 with that player's visibility bit. */
        if (start->marker_location_index < runtime->location_count) {
            runtime->locations[start->marker_location_index].tribe_visibility_mask |=
                (uint8_t)(1U << island_index);
        }
        /* FUN_0046466f calls FUN_00452859(0x2a, player); FUN_004641de
           resolves that base item into the player's 16-entry pad block. */
        runtime->locations[location_index].record_value_10 =
            (int32_t)start->initial_pad_item_id + (int32_t)island_index * 16;
        runtime->locations[location_index].owner_id = (int32_t)island_index;
        /* FUN_0046466f creates the Hall through FUN_004528ca, which clears
           +0x28/+0x2a/+0x2c; startup then sets only +0x28 to 50. */
        runtime->locations[location_index]
            .resource_stock[GAME_RESOURCE_BUILD_TONE] = 50;
        next.economy[island_index].hall_island_index = start->island_index;
        next.economy[island_index].hall_location_index = (uint16_t)location_index;
        next.economy[island_index].hall_x = runtime_layouts[start->island_index]
            .locations[location_index].x;
        next.economy[island_index].hall_y = runtime_layouts[start->island_index]
            .locations[location_index].y;
        for (unit = 0; unit < start->floater_count; ++unit) {
            GameFloaterStart *floater;
            const FloaterStats *stats = floater_catalog_find(
                floater_catalog, start->floater_type_index, 0);
            if (floater_cursor >= GAME_SESSION_MAX_FLOATERS) {
                set_error(error, error_capacity, "initial floater count exceeds session capacity");
                return 0;
            }
            if (stats == NULL || stats->hit_points < 0 ||
                stats->hit_points > (int16_t)UINT8_MAX ||
                stats->attack_strength < 0 ||
                stats->attack_strength > (int16_t)UINT8_MAX ||
                stats->movement_speed < 0) {
                set_error(error, error_capacity,
                          "initial floater stats are missing or out of range");
                return 0;
            }
            floater = &next.floaters[floater_cursor++];
            floater->island_index = start->island_index;
            floater->type_index = start->floater_type_index;
            floater->source_subtype = 0;
            floater->owner_slot = (uint8_t)island_index;
            /* FUN_00466fe4 initializes current hits to the loaded max HP.
               The type/subtype lookup uses the *work row in floater.txt. */
            floater->current_hit_points = (uint8_t)stats->hit_points;
            floater->max_hit_points = (uint8_t)stats->hit_points;
            floater->attack_strength = (uint8_t)stats->attack_strength;
            floater->attack_range = stats->attack_range;
            floater->attack_period = stats->attack_period;
            floater->source_link_0c = -1;
            floater->charge_current = 0;
            floater->carried_resource_code = 0;
            floater->order_resource_code = 0;
            floater->linked_task_slot = -1;
            floater->order_source_location = -1;
            floater->x = start->marker_x;
            floater->y = start->marker_y;
            floater->destination_x = start->marker_x;
            floater->destination_y = start->marker_y;
            floater->order_target_floater = -1;
            floater->order_target_location = -1;
            /* No task table is modeled yet; these unlinked initial floaters
               take the source's idle FA_Wander fallback. */
            floater->has_wander_order = 1;
            /* FUN_0046466f creates each initial unit with subtype 0;
               FUN_00422d27 reads speed through FUN_00464242 (+0x0c). */
            floater->movement_speed = (uint16_t)stats->movement_speed;
        }
    }
    next.floater_count = (uint8_t)floater_cursor;

    tone_rng_seed(&rng, config->random_seed);
    if (!game_start_distribute_tones(runtime_layouts, shape_ids,
                                     world->island_count, config->home_island_index,
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
        runtime->locations[placement->location_index].record_value_10 = placement->item_id;
        runtime->locations[placement->location_index].owner_id = placement->owner_id;
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
       zeroed animation fields, and animation-rate field +0x32 set to 1. */
    for (island_index = 0; island_index < next.island_count; ++island_index) {
        GameRuntimeIsland *runtime = &next.islands[island_index];
        unsigned int location_index;
        for (location_index = 0; location_index < runtime->location_count; ++location_index) {
            GameRuntimeLocation *state = &runtime->locations[location_index];
            if (state->record_value_10 > 0 && state->renderer_class <= 1) {
                state->source_flags = 0x410;
                state->chug_progress = 0;
                state->glyph_progress = 0;
                state->animation_rate = 1;
            }
            if (state->owner_id >= 0 &&
                state->record_value_10 > 0 &&
                !game_session_source_value_34_max(pad_catalog, state, &state->source_value_34)) {
                set_error(error, error_capacity,
                          "runtime item has no pad record for source field +0x34");
                return 0;
            }
        }
    }

    *out = next;
    return 1;
}
