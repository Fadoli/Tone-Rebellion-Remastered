#include "game_session.h"

#include "building_render.h"
#include "island_render_rules.h"

#include <stdio.h>
#include <string.h>

static void set_error(char *error, size_t capacity, const char *message)
{
    if (error == NULL || capacity == 0) return;
    (void)snprintf(error, capacity, "%s", message);
    error[capacity - 1] = '\0';
}

static int choose_empty_class0(const IslandData *source,
                               GameRuntimeIsland *runtime,
                               ToneRng *rng,
                               unsigned int *location_index)
{
    unsigned int available = 0;
    unsigned int choice;
    unsigned int index;
    int selected;

    for (index = 0; index < source->location_count; ++index) {
        if (source->locations[index].renderer_class == 0 &&
            runtime->locations[index].owner_id == -1 &&
            runtime->locations[index].record_value_10 == 0) {
            ++available;
        }
    }
    if (available == 0) return 0;
    selected = tone_rng_bounded(rng, (int32_t)available);
    if (selected < 0 || (unsigned int)selected >= available) return 0;
    choice = (unsigned int)selected;
    for (index = 0; index < source->location_count; ++index) {
        if (source->locations[index].renderer_class != 0 ||
            runtime->locations[index].owner_id != -1 ||
            runtime->locations[index].record_value_10 != 0) continue;
        if (choice == 0) {
            *location_index = index;
            return 1;
        }
        --choice;
    }
    return 0;
}

static int prepare_runtime_layouts(const WorldDefinition *world,
                                   const IslandData *sources,
                                   IslandData *layouts,
                                   int32_t bridge_neighbors[WORLD_MAP_MAX_ISLANDS][ISLAND_DATA_MAX_LOCATIONS],
                                   char *error, size_t error_capacity)
{
    unsigned int island_index;
    for (island_index = 0; island_index < world->island_count; ++island_index) {
        uint16_t class2_locations[ISLAND_DATA_MAX_LOCATIONS];
        unsigned int class2_count = 0;
        unsigned int incident_count = 0;
        unsigned int location_index;
        unsigned int bridge_index;
        uint8_t incident_neighbors[WORLD_MAP_MAX_BRIDGES];
        unsigned int incident_neighbor_count = 0;

        for (location_index = 0; location_index < ISLAND_DATA_MAX_LOCATIONS; ++location_index) {
            bridge_neighbors[island_index][location_index] = -1;
        }

        if (sources[island_index].location_count > ISLAND_DATA_MAX_LOCATIONS) {
            if (error != NULL && error_capacity != 0) {
                (void)snprintf(error, error_capacity,
                               "island %u exceeds the original location capacity", island_index);
                error[error_capacity - 1] = '\0';
            }
            return 0;
        }
        layouts[island_index] = sources[island_index];
        for (location_index = 0; location_index < layouts[island_index].location_count;
             ++location_index) {
            if (layouts[island_index].locations[location_index].renderer_class == 2) {
                unsigned int insert_at = class2_count;
                uint16_t source_index = (uint16_t)location_index;
                while (insert_at > 0 &&
                       layouts[island_index].locations[class2_locations[insert_at - 1U]].x >
                       layouts[island_index].locations[source_index].x) {
                    class2_locations[insert_at] = class2_locations[insert_at - 1U];
                    --insert_at;
                }
                class2_locations[insert_at] = source_index;
                ++class2_count;
            }
        }
        for (bridge_index = 0; bridge_index < world->bridge_count; ++bridge_index) {
            const WorldBridge *bridge = &world->bridges[bridge_index];
            if (bridge->island_a >= world->island_count ||
                bridge->island_b >= world->island_count ||
                bridge->island_a == bridge->island_b) {
                set_error(error, error_capacity, "world bridge has an invalid island endpoint");
                return 0;
            }
            if (bridge->island_a == island_index || bridge->island_b == island_index) {
                uint8_t neighbor = bridge->island_a == island_index
                    ? bridge->island_b : bridge->island_a;
                unsigned int insert_at = incident_neighbor_count;
                while (insert_at > 0 &&
                       world->islands[incident_neighbors[insert_at - 1U]].angle_degrees >
                       world->islands[neighbor].angle_degrees) {
                    incident_neighbors[insert_at] = incident_neighbors[insert_at - 1U];
                    --insert_at;
                }
                incident_neighbors[insert_at] = neighbor;
                ++incident_neighbor_count;
                ++incident_count;
            }
        }
        /* FUN_00461859 sorts class-2 records by X and demotes the surplus first. */
        if (class2_count > incident_count) {
            unsigned int demote_count = class2_count - incident_count;
            for (location_index = 0; location_index < demote_count; ++location_index) {
                layouts[island_index].locations[class2_locations[location_index]].renderer_class = 0;
            }
        }
        for (location_index = 0;
             location_index < class2_count - (class2_count > incident_count
                                               ? class2_count - incident_count : 0U);
             ++location_index) {
            unsigned int retained_index = location_index +
                (class2_count > incident_count ? class2_count - incident_count : 0U);
            if (location_index < incident_neighbor_count) {
                bridge_neighbors[island_index][class2_locations[retained_index]] =
                    (int32_t)incident_neighbors[location_index];
            }
        }
    }
    return 1;
}

static int assign_initial_bridge_sites(const WorldDefinition *world,
                                       const IslandData *sources,
                                       GameSession *session,
                                       ToneRng *rng,
                                       char *error, size_t error_capacity)
{
    unsigned int ordinal;
    unsigned int island_count = world->island_count;
    unsigned int wrap_span = island_count - 1U;

    for (ordinal = 0; ordinal < world->bridge_count; ++ordinal) {
        unsigned int target_island = ordinal;
        unsigned int location_index;
        while (target_island >= wrap_span) {
            unsigned int previous = target_island;
            target_island = target_island - wrap_span + 4U;
            if (target_island >= previous) {
                set_error(error, error_capacity, "bridge-site wrap rule does not converge for this world");
                return 0;
            }
        }
        if (!choose_empty_class0(&sources[target_island], &session->islands[target_island],
                                 rng, &location_index)) {
            if (error != NULL && error_capacity != 0) {
                (void)snprintf(error, error_capacity,
                               "island %u has no free class-0 record for bridge setup", target_island);
                error[error_capacity - 1] = '\0';
            }
            return 0;
        }
        session->islands[target_island].locations[location_index].record_value_10 = 1;
        session->islands[target_island].locations[location_index].record_value_24 = 5;
        ++session->class0_assignments;
    }
    return 1;
}

static int assign_class0_links(const WorldDefinition *world,
                               const IslandData *sources,
                               const int32_t shape_ids[WORLD_MAP_MAX_ISLANDS],
                               GameSession *session,
                               ToneRng *rng,
                               char *error, size_t error_capacity)
{
    unsigned int ordinal;
    unsigned int count = ((unsigned int)world->island_count - 1U) * 2U;
    unsigned int total_free = 0;

    if (session->config.randomize_class0_assignment != 0) {
        unsigned int island_index;
        for (island_index = 0; island_index + 1U < world->island_count; ++island_index) {
            unsigned int location_index;
            for (location_index = 0; location_index < sources[island_index].location_count;
                 ++location_index) {
                if (sources[island_index].locations[location_index].renderer_class == 0 &&
                    session->islands[island_index].locations[location_index].owner_id == -1 &&
                    session->islands[island_index].locations[location_index].record_value_10 == 0) {
                    ++total_free;
                }
            }
        }
        if (total_free < count) {
            set_error(error, error_capacity, "not enough free class-0 records for randomized link setup");
            return 0;
        }
    }

    for (ordinal = 0; ordinal < count; ++ordinal) {
        unsigned int target_island = ordinal / 2U;
        unsigned int location_index;
        int selected = 0;

        while (!selected) {
            if (session->config.randomize_class0_assignment != 0) {
                int random_island = tone_rng_bounded(rng, (int32_t)world->island_count - 1);
                if (random_island < 0 || random_island >= (int)world->island_count - 1) {
                    set_error(error, error_capacity, "random island index is out of range");
                    return 0;
                }
                target_island = (unsigned int)random_island;
            }
            if (choose_empty_class0(&sources[target_island], &session->islands[target_island],
                                    rng, &location_index)) {
                selected = 1;
            } else if (session->config.randomize_class0_assignment == 0) {
                if (error != NULL && error_capacity != 0) {
                    (void)snprintf(error, error_capacity,
                                   "island %u has no free class-0 record for link setup", target_island);
                    error[error_capacity - 1] = '\0';
                }
                return 0;
            }
        }
        session->islands[target_island].locations[location_index].record_value_10 = 1;
        session->islands[target_island].locations[location_index].record_value_24 =
            6 + shape_ids[ordinal / 2U] * 2 + (int32_t)(ordinal & 1U);
        ++session->class0_assignments;
    }
    return 1;
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
    int32_t bridge_neighbors[WORLD_MAP_MAX_ISLANDS][ISLAND_DATA_MAX_LOCATIONS];
    IslandData runtime_layouts[WORLD_MAP_MAX_ISLANDS];
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
    if (!prepare_runtime_layouts(world, islands_by_world_index, runtime_layouts,
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
        for (location_index = 0; location_index < source->location_count; ++location_index) {
            const IslandLocation *location = &source->locations[location_index];
            GameRuntimeLocation *state = &runtime->locations[location_index];
            /* FUN_004500c4 initializes owner to -1 and clears +0x10 except for class 3. */
            state->record_value_10 = location->renderer_class == 3 ? location->renderer_variant : 0;
            state->owner_id = -1;
            state->record_value_24 = 0;
            state->bridge_neighbor_island = bridge_neighbors[island_index][location_index];
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

        if (location_index >= runtime->location_count ||
            runtime->locations[location_index].record_value_10 != 0) {
            set_error(error, error_capacity, "initial hall location is not empty at runtime");
            return 0;
        }
        /* FUN_0046466f calls FUN_00452859(0x2a, player); FUN_004641de
           resolves that base item into the player's 16-entry pad block. */
        runtime->locations[location_index].record_value_10 =
            (int32_t)start->initial_pad_item_id + (int32_t)island_index * 16;
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
    if (!assign_initial_bridge_sites(world, runtime_layouts, &next, &rng,
                                     error, error_capacity) ||
        !assign_class0_links(world, runtime_layouts, shape_ids, &next, &rng,
                             error, error_capacity)) {
        return 0;
    }

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
        }
    }

    *out = next;
    return 1;
}

void game_session_tick_item_animations(GameSession *session,
                                       const struct BuildingRenderCatalog *catalog)
{
    unsigned int island_index;
    if (session == NULL || catalog == NULL) return;
    for (island_index = 0; island_index < session->island_count; ++island_index) {
        GameRuntimeIsland *island = &session->islands[island_index];
        unsigned int location_index;
        for (location_index = 0; location_index < island->location_count; ++location_index) {
            GameRuntimeLocation *state = &island->locations[location_index];
            const BuildingRenderItem *item;
            uint32_t duration;

            if (state->renderer_class > 1) continue;

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

            if (state->record_value_10 <= 0 ||
                state->record_value_10 >= catalog->item_count) continue;
            item = building_render_find(catalog, (uint16_t)state->record_value_10);
            if (item == NULL) continue;

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
                continue;
            }

            /* FUN_00450a71 increments class-0 CHUG only while source flag bit 0
               is set; objects created by FUN_004528ca begin with it clear. */
            if ((state->source_flags & 1U) != 0 && item->chug.present) {
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
            if (item->glyph.present &&
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
                }
            }

            /* The same source tick advances CONS (+0x40) while flag 0x004 is
               set. FUN_00456b8d resolves a construction descriptor; its +0x0a
               threshold is stored as CONS's first parameter by bldinf.txt. */
            if ((state->source_flags & 0x004U) != 0) {
                ++state->construction_progress;
                if (item->cons.present &&
                    item->cons.fallback_frame <= state->construction_progress) {
                    state->source_flags &= ~0x004U;
                }
            }
        }
    }
}
