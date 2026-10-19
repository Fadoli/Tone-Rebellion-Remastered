#include "game_session.h"

#include "floater_motion.h"
#include "iw_construct.h"
#include "island_render_rules.h"
#include "pad_catalog.h"

#include <stdio.h>
#include <string.h>

static void set_error(char *error, size_t capacity, const char *message)
{
    if (error == NULL || capacity == 0) return;
    (void)snprintf(error, capacity, "%s", message);
    error[capacity - 1] = '\0';
}

static int is_construction_location(const IslandLocation *location)
{
    uint8_t site_size;
    return iw_construct_site_size(location, &site_size);
}

static int island_has_typed_construction_sites(const IslandData *source)
{
    unsigned int index;
    for (index = 0; index < source->location_count; ++index) {
        if (source->locations[index].renderer_class == 0 &&
            is_construction_location(&source->locations[index])) return 1;
    }
    return 0;
}

static int choose_empty_class0(const IslandData *source,
                               GameRuntimeIsland *runtime,
                               ToneRng *rng,
                               unsigned int *location_index)
{
    unsigned int available = 0;
    unsigned int choice;
    unsigned int index;
    int prefer_typed_sites = island_has_typed_construction_sites(source);
    int selected;

    for (index = 0; index < source->location_count; ++index) {
        if (source->locations[index].renderer_class == 0 &&
            (!prefer_typed_sites || is_construction_location(&source->locations[index])) &&
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
            (prefer_typed_sites && !is_construction_location(&source->locations[index])) ||
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
            int prefer_typed_sites = island_has_typed_construction_sites(
                &sources[island_index]);
            for (location_index = 0; location_index < sources[island_index].location_count;
                 ++location_index) {
                if (sources[island_index].locations[location_index].renderer_class == 0 &&
                    (!prefer_typed_sites || is_construction_location(
                        &sources[island_index].locations[location_index])) &&
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

static int source_value_34_max(const PadCatalog *catalog,
                               const GameRuntimeLocation *location,
                               int16_t *maximum)
{
    const PadCatalogItem *item;
    int32_t base_item_id;
    int32_t value;

    if (catalog == NULL || location == NULL || maximum == NULL ||
        location->owner_id < -1 || location->owner_id > GAME_START_PLAYER_COUNT ||
        location->record_value_10 < 0) return 0;
    if (location->owner_id == -1) {
        *maximum = -1;
        return 1;
    }
    base_item_id = location->record_value_10;
    if (location->owner_id < GAME_START_PLAYER_COUNT)
        base_item_id -= location->owner_id * 16;
    if (base_item_id <= 1) {
        *maximum = -1;
        return 1;
    }
    item = pad_catalog_find(catalog, (uint16_t)location->record_value_10);
    if (item == NULL) return 0;
    /* FUN_0046303b stores the seventh parsed integer (pad.txt hit points)
       at record +0x0e; FUN_00450978 adds runtime +0x4a * 5. */
    value = (int32_t)item->hit_points +
            (int32_t)location->source_capacity_4a * 5;
    if (value < INT16_MIN || value > INT16_MAX) return 0;
    *maximum = (int16_t)value;
    return 1;
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
            floater->source_link_0c = -1;
            floater->charge_current = 0;
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
    if (!assign_initial_bridge_sites(world, runtime_layouts, &next, &rng,
                                     error, error_capacity) ||
        !assign_class0_links(world, runtime_layouts, shape_ids, &next, &rng,
                             error, error_capacity)) {
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
                !source_value_34_max(pad_catalog, state, &state->source_value_34)) {
                set_error(error, error_capacity,
                          "runtime item has no pad record for source field +0x34");
                return 0;
            }
        }
    }

    *out = next;
    return 1;
}

int game_session_repair_task_values(const GameSession *session,
                                    const PadCatalog *pad_catalog,
                                    const GamePendingEvent *event,
                                    int16_t *current, int16_t *maximum)
{
    if (session == NULL || pad_catalog == NULL || event == NULL ||
        current == NULL || maximum == NULL || event->active == 0 ||
        event->action_type != 0x12 || event->payload_0a < 0 ||
        event->payload_0e < 0 || event->payload_0a >= session->island_count) return 0;
    return game_session_repair_location_values(session, pad_catalog,
        (uint8_t)event->payload_0a, (uint16_t)event->payload_0e,
        current, maximum);
}

int game_session_repair_location_values(const GameSession *session,
                                        const PadCatalog *pad_catalog,
                                        uint8_t island_index,
                                        uint16_t location_index,
                                        int16_t *current, int16_t *maximum)
{
    const GameRuntimeIsland *island;
    const GameRuntimeLocation *location;
    int16_t computed_maximum;

    if (session == NULL || pad_catalog == NULL || current == NULL ||
        maximum == NULL || island_index >= session->island_count) return 0;
    island = &session->islands[island_index];
    if (location_index >= island->location_count) return 0;
    location = &island->locations[location_index];
    if (!source_value_34_max(pad_catalog, location, &computed_maximum) ||
        location->source_value_34 == -1 || computed_maximum <= 0) return 0;
    *current = location->source_value_34;
    *maximum = computed_maximum;
    return 1;
}

int game_session_construction_task_values(const GameSession *session,
                                          const PadCatalog *pad_catalog,
                                          const GamePendingEvent *event,
                                          int16_t *current, int16_t *maximum)
{
    const GameRuntimeLocation *location;
    const PadCatalogItem *item;
    int32_t item_id;
    if (session == NULL || pad_catalog == NULL || event == NULL ||
        current == NULL || maximum == NULL || event->active == 0 ||
        event->action_type != 5 || event->payload_0a < 0 ||
        event->payload_0e < 0 || event->payload_0a >= session->island_count ||
        event->player_id < 0 || event->player_id >= GAME_START_PLAYER_COUNT) return 0;
    if ((uint16_t)event->payload_0e >=
        session->islands[event->payload_0a].location_count) return 0;
    location = &session->islands[event->payload_0a].locations[event->payload_0e];
    item_id = (int32_t)event->payload_12 + (int32_t)event->player_id * 16;
    if (item_id < 0 || item_id > 100) return 0;
    item = pad_catalog_find(pad_catalog, (uint16_t)item_id);
    if (item == NULL || item->building_tone_cost <= 0) return 0;
    *current = (int16_t)location->resource_stock[0];
    *maximum = item->building_tone_cost;
    return *current >= 0;
}

int game_session_acquire_glyph(GameSession *session, uint8_t player_slot,
                               uint8_t glyph_index)
{
    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT ||
        glyph_index >= GAME_GLYPH_COUNT) return 0;
    session->economy[player_slot].glyph_mask = (uint16_t)(
        session->economy[player_slot].glyph_mask | (uint16_t)(1U << glyph_index));
    return 1;
}

int game_session_place_building(GameSession *session,
                                const PadCatalog *catalog,
                                uint8_t player_slot,
                                uint8_t island_index,
                                uint16_t location_index,
                                const struct IslandLocation *site,
                                uint16_t base_item_id,
                                char *error, size_t error_capacity)
{
    GameRuntimeLocation *runtime;
    const PadCatalogItem *item;
    uint8_t site_size;
    uint16_t runtime_item_id;

    if (error != NULL && error_capacity != 0) error[0] = '\0';
    if (session == NULL || catalog == NULL || site == NULL || player_slot >= 4 ||
        island_index >= session->island_count ||
        location_index >= session->islands[island_index].location_count) {
        set_error(error, error_capacity, "building placement target or player is out of range");
        return 0;
    }
    runtime = &session->islands[island_index].locations[location_index];
    if (runtime->renderer_class != 0 || runtime->record_value_10 != 0 ||
        runtime->owner_id != -1 ||
        !iw_construct_site_size(site, &site_size)) {
        set_error(error, error_capacity, "building placement requires an empty construction site");
        return 0;
    }
    if (base_item_id == 0) {
        set_error(error, error_capacity, "source rejects item ID zero for construction");
        return 0;
    }
    runtime_item_id = (uint16_t)(base_item_id + (uint16_t)player_slot * 16U);
    item = pad_catalog_find(catalog, runtime_item_id);
    if (item == NULL || item->size < 0 || item->size > site_size ||
        item->building_tone_cost == -1) {
        set_error(error, error_capacity, "building is not allowed on this site");
        return 0;
    }

    /* FUN_004528ca sets +0x32 to 1 and flags to 0x410. The source does not
       explicitly reset producer +0x0c; new remake placements start it at 0. */
    runtime->record_value_10 = runtime_item_id;
    runtime->owner_id = player_slot;
    runtime->source_capacity_4a = 0;
    if (!source_value_34_max(catalog, runtime, &runtime->source_value_34)) {
        set_error(error, error_capacity, "building has no usable source field +0x34");
        return 0;
    }
    runtime->record_value_24 = 0;
    runtime->source_flags = 0x410;
    runtime->base_progress = 0;
    runtime->producer_cadence = 0;
    runtime->chug_progress = 0;
    runtime->glyph_progress = 0;
    runtime->inci_progress = 0;
    runtime->construction_progress = 0;
    runtime->production_progress = 0;
    runtime->animation_rate = 1;
    runtime->barg_progress = 0.0;
    runtime->tribe_visibility_mask = 0;
    return 1;
}
