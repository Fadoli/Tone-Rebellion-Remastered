#include "game_session.h"

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
                            const GameSessionConfig *config,
                            GameSession *out,
                            char *error, size_t error_capacity)
{
    GameSession next;
    ToneRng rng;
    int32_t shape_ids[WORLD_MAP_MAX_ISLANDS];
    unsigned int island_index;
    unsigned int floater_cursor = 0;

    if (error != NULL && error_capacity != 0) error[0] = '\0';
    if (world == NULL || islands_by_world_index == NULL || config == NULL || out == NULL) {
        set_error(error, error_capacity, "world, island records, config and output are required");
        return 0;
    }
    if (world->island_count < GAME_START_PLAYER_COUNT ||
        world->island_count > WORLD_MAP_MAX_ISLANDS) {
        set_error(error, error_capacity, "world island count cannot support the four start slots");
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
    for (island_index = 0; island_index < world->island_count; ++island_index) {
        const IslandData *source = &islands_by_world_index[island_index];
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
        runtime->location_count = source->location_count;
        for (location_index = 0; location_index < source->location_count; ++location_index) {
            const IslandLocation *location = &source->locations[location_index];
            GameRuntimeLocation *state = &runtime->locations[location_index];
            /* FUN_004500c4 initializes owner to -1 and clears +0x10 except for class 3. */
            state->item_id = location->renderer_class == 3 ? location->renderer_variant : 0;
            state->owner_id = -1;
        }
    }

    if (!game_start_assign_locations(islands_by_world_index, world->island_count,
                                     config->mode, config->alternate_island,
                                     &next.player_starts, error, error_capacity)) {
        return 0;
    }
    for (island_index = 0; island_index < GAME_START_PLAYER_COUNT; ++island_index) {
        const GamePlayerStart *start = &next.player_starts.players[island_index];
        GameRuntimeIsland *runtime = &next.islands[start->island_index];
        unsigned int location_index = start->nearest_site_location_index;
        unsigned int unit;

        if (location_index >= runtime->location_count ||
            runtime->locations[location_index].item_id != 0) {
            set_error(error, error_capacity, "initial hall location is not empty at runtime");
            return 0;
        }
        runtime->locations[location_index].item_id = start->initial_pad_item_id;
        runtime->locations[location_index].owner_id = (int32_t)island_index;
        for (unit = 0; unit < start->floater_count; ++unit) {
            GameFloaterStart *floater;
            if (floater_cursor >= GAME_SESSION_MAX_FLOATERS) {
                set_error(error, error_capacity, "initial floater count exceeds session capacity");
                return 0;
            }
            floater = &next.floaters[floater_cursor++];
            floater->island_index = start->island_index;
            floater->type_index = start->floater_type_index;
            floater->x = start->marker_x;
            floater->y = start->marker_y;
        }
    }
    next.floater_count = (uint8_t)floater_cursor;

    tone_rng_seed(&rng, config->random_seed);
    if (!game_start_distribute_tones(islands_by_world_index, shape_ids,
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
        runtime->locations[placement->location_index].item_id = placement->item_id;
        runtime->locations[placement->location_index].owner_id = placement->owner_id;
    }

    *out = next;
    return 1;
}
