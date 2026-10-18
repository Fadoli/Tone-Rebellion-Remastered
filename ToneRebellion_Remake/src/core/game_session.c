#include "game_session.h"

#include "building_render.h"
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
        for (location_index = 0; location_index < source->location_count; ++location_index) {
            const IslandLocation *location = &source->locations[location_index];
            GameRuntimeLocation *state = &runtime->locations[location_index];
            /* FUN_004500c4 initializes owner to -1 and clears +0x10 except for class 3. */
            state->record_value_10 = location->renderer_class == 3 ? location->renderer_variant : 0;
            state->owner_id = -1;
            state->source_location_slot_18 = -1;
            state->source_value_34 = -1;
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
            floater->x = start->marker_x;
            floater->y = start->marker_y;
            floater->destination_x = start->marker_x;
            floater->destination_y = start->marker_y;
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

int game_session_can_enter_island(const GameSession *session,
                                  uint8_t island_index,
                                  uint8_t player_mask)
{
    if (session == NULL || island_index >= session->island_count) return 0;
    return (session->islands[island_index].access_mask & player_mask) != 0;
}

int game_session_world_map_frame_offset(const GameSession *session,
                                        uint8_t island_index,
                                        uint8_t player_mask,
                                        int hovered)
{
    if (session == NULL || island_index >= session->island_count) return -1;
    if (!game_session_can_enter_island(session, island_index, player_mask)) return 15;
    return hovered ? 30 : 0;
}

int game_session_bridge_is_active(const GameSession *session,
                                  uint8_t bridge_index,
                                  uint8_t bridge_count)
{
    if (session == NULL || bridge_count > WORLD_MAP_MAX_BRIDGES ||
        bridge_index >= bridge_count) return 0;
    return (session->active_bridge_mask & (UINT32_C(1) << bridge_index)) != 0;
}

static int find_bridge_marker_index(const GameRuntimeIsland *island,
                                    uint8_t neighbor_island)
{
    unsigned int location_index;
    if (island == NULL) return -1;
    for (location_index = 0; location_index < island->location_count;
         ++location_index) {
        const GameRuntimeLocation *location = &island->locations[location_index];
        if (location->renderer_class == 2 &&
            location->bridge_neighbor_island == (int32_t)neighbor_island) {
            return (int)location_index;
        }
    }
    return -1;
}

int game_session_world_bridge_is_renderable(const GameSession *session,
                                            uint8_t bridge_index,
                                            uint8_t bridge_count,
                                            uint8_t island_a,
                                            uint8_t island_b)
{
    const GameRuntimeLocation *marker_a;
    const GameRuntimeLocation *marker_b;
    if (!game_session_bridge_is_active(session, bridge_index, bridge_count) ||
        island_a >= session->island_count || island_b >= session->island_count ||
        island_a == island_b) {
        return 0;
    }
    {
        int index_a = find_bridge_marker_index(&session->islands[island_a], island_b);
        int index_b = find_bridge_marker_index(&session->islands[island_b], island_a);
        if (index_a < 0 || index_b < 0) return 0;
        marker_a = &session->islands[island_a].locations[index_a];
        marker_b = &session->islands[island_b].locations[index_b];
    }
    return
           marker_a->bridge_constructed && marker_b->bridge_constructed;
}

int game_session_mark_bridge_constructed(GameSession *session,
                                         uint8_t bridge_index,
                                         uint8_t bridge_count,
                                         uint8_t island_a,
                                         uint8_t island_b)
{
    GameRuntimeLocation *marker_a;
    GameRuntimeLocation *marker_b;
    if (session == NULL || bridge_count > WORLD_MAP_MAX_BRIDGES ||
        bridge_index >= bridge_count || island_a >= session->island_count ||
        island_b >= session->island_count || island_a == island_b) {
        return 0;
    }
    {
        int index_a = find_bridge_marker_index(&session->islands[island_a], island_b);
        int index_b = find_bridge_marker_index(&session->islands[island_b], island_a);
        if (index_a < 0 || index_b < 0) return 0;
        marker_a = &session->islands[island_a].locations[index_a];
        marker_b = &session->islands[island_b].locations[index_b];
    }
    marker_a->bridge_constructed = 1;
    marker_b->bridge_constructed = 1;
    return game_session_set_bridge_active(session, bridge_index, bridge_count, 1);
}

int game_session_set_bridge_active(GameSession *session,
                                   uint8_t bridge_index,
                                   uint8_t bridge_count,
                                   int active)
{
    uint32_t bit;
    if (session == NULL || bridge_count > WORLD_MAP_MAX_BRIDGES ||
        bridge_index >= bridge_count) return 0;
    bit = UINT32_C(1) << bridge_index;
    if (active) session->active_bridge_mask |= bit;
    else session->active_bridge_mask &= ~bit;
    return 1;
}

int game_session_apply_world_bridge_message(GameSession *session,
                                            uint8_t bridge_count,
                                            uint32_t parameter_flags)
{
    uint32_t mask;
    if (session == NULL || bridge_count > WORLD_MAP_MAX_BRIDGES) return 0;
    if (bridge_count == 0) mask = 0;
    else if (bridge_count == WORLD_MAP_MAX_BRIDGES) mask = UINT32_MAX;
    else mask = (UINT32_C(1) << bridge_count) - UINT32_C(1);
    session->active_bridge_mask = (parameter_flags & UINT32_C(0x100)) == 0
        ? mask : 0;
    return 1;
}

static int producer_resource_code(const GameRuntimeLocation *state)
{
    int32_t base_item_id;
    if (state == NULL || state->renderer_class != 0 || state->owner_id < 0 ||
        state->owner_id >= GAME_START_PLAYER_COUNT) return 0;
    base_item_id = state->record_value_10 - state->owner_id * 16;
    if (base_item_id == 0x25) return 1; /* P-BLDTON -> Build Tone */
    if (base_item_id == 0x27) return 2; /* P-CRYTON -> Crystal Tone */
    if (base_item_id == 0x26) return 3; /* P-MAGTON -> Magic Tone */
    return 0;
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
                    /* FUN_00450a71 maps completed producer cycles into the
                       pending output code held in runtime +0x24. */
                    if (state->record_value_24 == 0)
                        state->record_value_24 = producer_resource_code(state);
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

void game_session_tick_floater_moves(GameSession *session, uint32_t source_tick)
{
    unsigned int i;

    if (session == NULL) return;
    for (i = 0; i < session->floater_count; ++i) {
        GameFloaterStart *floater = &session->floaters[i];
        FloaterPosition position;
        FloaterPosition destination;
        int32_t dx;
        int32_t dy;
        int32_t distance;

        if (!floater->has_move_order) {
            continue;
        }
        dx = (int32_t)floater->destination_x - floater->x;
        dy = (int32_t)floater->destination_y - floater->y;
        /* FUN_00423068 updates facing from the destination independently of
           whether the movement state is already inside its stopping radius. */
        if (dx < 0) floater->facing_left = 1;
        else if (dx > 0) floater->facing_left = 0;
        distance = dx < 0 ? -dx : dx;
        if ((dy < 0 ? -dy : dy) > distance) distance = dy < 0 ? -dy : dy;
        if (distance <= floater->stop_radius) {
            floater->has_move_order = 0;
            continue;
        }

        position.x = floater->x;
        position.y = floater->y;
        destination.x = floater->destination_x;
        destination.y = floater->destination_y;
        (void)floater_motion_step(&position, destination,
                                  floater->movement_speed, source_tick);
        floater->x = (uint16_t)position.x;
        floater->y = (uint16_t)position.y;
        dx = (int32_t)floater->destination_x - floater->x;
        dy = (int32_t)floater->destination_y - floater->y;
        if ((dx < 0 ? -dx : dx) <= floater->stop_radius &&
            (dy < 0 ? -dy : dy) <= floater->stop_radius) {
            floater->has_move_order = 0;
        }

    }
}

int game_session_floater_at(const GameSession *session,
                            uint8_t island_index,
                            uint16_t x,
                            uint16_t y)
{
    unsigned int i;

    if (session == NULL || island_index >= session->island_count) return -1;
    for (i = 0; i < session->floater_count; ++i) {
        const GameFloaterStart *floater = &session->floaters[i];
        int32_t dx;
        int32_t dy;

        if (floater->island_index != island_index) continue;
        dx = (int32_t)x - floater->x;
        dy = (int32_t)y - floater->y;
        if (dx < 0) dx = -dx;
        if (dy < 0) dy = -dy;
        if ((dx > dy ? dx : dy) < 20) return (int)i;
    }
    return -1;
}

unsigned int game_session_count_player_floaters(const GameSession *session,
                                                uint8_t player_slot)
{
    unsigned int count = 0;
    unsigned int i;
    unsigned int limit;

    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT) return 0;
    limit = session->floater_count;
    if (limit > GAME_SESSION_MAX_FLOATERS) limit = GAME_SESSION_MAX_FLOATERS;
    for (i = 0; i < limit; ++i) {
        if (session->floaters[i].owner_slot == player_slot) ++count;
    }
    return count;
}

int game_session_workstr_summary(const GameSession *session,
                                 uint8_t type_index,
                                 unsigned int *count,
                                 unsigned int *total,
                                 unsigned int *percentage)
{
    unsigned int subtype_zero = 0;
    unsigned int type_total = 0;
    unsigned int limit;
    unsigned int i;

    if (count != NULL) *count = 0;
    if (total != NULL) *total = 0;
    if (percentage != NULL) *percentage = 0;
    if (session == NULL || type_index >= GAME_START_PLAYER_COUNT ||
        count == NULL || total == NULL || percentage == NULL) return 0;

    limit = session->floater_count;
    if (limit > GAME_SESSION_MAX_FLOATERS) limit = GAME_SESSION_MAX_FLOATERS;
    for (i = 0; i < limit; ++i) {
        const GameFloaterStart *floater = &session->floaters[i];
        if (floater->type_index != type_index) continue;
        ++type_total;
        if (floater->source_subtype == 0) ++subtype_zero;
    }
    *count = subtype_zero;
    *total = type_total;
    if (type_total > 0) {
        /* Source performs this ratio in floating point and converts the
           nonnegative result to int; integer division has same truncation. */
        *percentage = (subtype_zero * 100U) / type_total;
    }
    return 1;
}

uint8_t game_session_location_display_level(const GameRuntimeLocation *location)
{
    if (location == NULL) return 0;
    return (uint8_t)((location->source_level_flags & 0x000fU) + 1U);
}

static GameRuntimeLocation *player_hall(GameSession *session, uint8_t player_slot)
{
    const GamePlayerEconomy *economy;
    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT) return NULL;
    economy = &session->economy[player_slot];
    if (economy->hall_island_index >= session->island_count ||
        economy->hall_location_index >=
            session->islands[economy->hall_island_index].location_count) return NULL;
    return &session->islands[economy->hall_island_index]
        .locations[economy->hall_location_index];
}

int game_session_credit_resource(GameSession *session, uint8_t player_slot,
                                 GameResourceType type, uint32_t amount)
{
    GameRuntimeLocation *hall = player_hall(session, player_slot);
    uint16_t *stock;
    if (hall == NULL || (int)type < GAME_RESOURCE_BUILD_TONE ||
        (int)type >= GAME_RESOURCE_TYPE_COUNT) return 0;
    stock = &hall->resource_stock[type];
    if (amount > UINT16_MAX - *stock) return 0;
    *stock = (uint16_t)(*stock + amount);
    return 1;
}

int game_session_debit_resource(GameSession *session, uint8_t player_slot,
                                 GameResourceType type, uint32_t amount)
{
    GameRuntimeLocation *hall = player_hall(session, player_slot);
    uint16_t *stock;
    if (hall == NULL || (int)type < GAME_RESOURCE_BUILD_TONE ||
        (int)type >= GAME_RESOURCE_TYPE_COUNT) return 0;
    stock = &hall->resource_stock[type];
    if (amount > *stock) return 0;
    *stock = (uint16_t)(*stock - amount);
    return 1;
}

int game_session_consume_location_resource(GameSession *session,
                                           uint8_t island_index,
                                           uint16_t location_index,
                                           int32_t resource_code)
{
    GameRuntimeLocation *location;
    if (session == NULL || island_index >= session->island_count ||
        location_index >= session->islands[island_index].location_count) return 0;
    location = &session->islands[island_index].locations[location_index];
    if (location->record_value_24 == resource_code) {
        location->record_value_24 = 0;
        return 1;
    }
    if (location->record_value_10 == 0x2a) {
        if (resource_code >= 1 && resource_code <= GAME_RESOURCE_TYPE_COUNT) {
            uint16_t *stock = &location->resource_stock[resource_code - 1];
            if (*stock > 0) {
                --*stock;
                return 1;
            }
        }
    }
    if (location->owner_id >= 0 &&
        location->owner_id < GAME_START_PLAYER_COUNT &&
        resource_code >= GAME_INVENTORY_ITEM_FIRST_ID &&
        resource_code < GAME_INVENTORY_ITEM_FIRST_ID + GAME_INVENTORY_ITEM_COUNT) {
        uint16_t *count = &session->economy[location->owner_id].inventory_count[
            resource_code - GAME_INVENTORY_ITEM_FIRST_ID];
        if (*count > 0) {
            --*count;
            return 1;
        }
    }
    return 0;
}

int game_session_location_resource_available(const GameSession *session,
                                             uint8_t island_index,
                                             uint16_t location_index,
                                             int32_t resource_code)
{
    const GameRuntimeLocation *location;
    if (session == NULL || island_index >= session->island_count ||
        location_index >= session->islands[island_index].location_count) return 0;
    location = &session->islands[island_index].locations[location_index];
    if (location->record_value_24 == resource_code) return 1;
    if (location->record_value_10 == 0x2a &&
        resource_code >= 1 && resource_code <= GAME_RESOURCE_TYPE_COUNT &&
        location->resource_stock[resource_code - 1] > 0) return 1;
    if (location->owner_id >= 0 && location->owner_id < GAME_START_PLAYER_COUNT &&
        (location->record_value_10 == 0x2a ||
         location->source_location_slot_18 != -1) &&
        resource_code >= GAME_INVENTORY_ITEM_FIRST_ID &&
        resource_code < GAME_INVENTORY_ITEM_FIRST_ID + GAME_INVENTORY_ITEM_COUNT &&
        session->economy[location->owner_id].inventory_count[
            resource_code - GAME_INVENTORY_ITEM_FIRST_ID] > 0) return 1;
    return 0;
}

int game_session_location_move_costs(const GameSession *session,
                                     const PadCatalog *catalog,
                                     uint8_t island_index,
                                     uint16_t location_index,
                                     int32_t costs[GAME_RESOURCE_TYPE_COUNT])
{
    const GameRuntimeLocation *location;
    const PadCatalogItem *item;
    int32_t result[GAME_RESOURCE_TYPE_COUNT];
    int32_t multiplier;
    unsigned int resource;

    if (session == NULL || catalog == NULL || costs == NULL ||
        island_index >= session->island_count ||
        location_index >= session->islands[island_index].location_count) {
        return 0;
    }
    location = &session->islands[island_index].locations[location_index];
    if (location->record_value_10 < 0 ||
        location->record_value_10 > INT32_C(65535))
        return 0;
    item = pad_catalog_find(catalog, (uint16_t)location->record_value_10);
    if (item == NULL) return 0;

    multiplier = (int32_t)location->source_capacity_4a + 1;
    for (resource = 0; resource < GAME_RESOURCE_TYPE_COUNT; ++resource) {
        result[resource] = (int32_t)item->movement_cost[resource] * multiplier;
    }
    memcpy(costs, result, sizeof(result));
    return 1;
}

int game_session_cycle_resource_stock_mode(GameSession *session,
                                           uint8_t player_slot,
                                           GameResourceType type)
{
    uint8_t *mode;
    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT ||
        (int)type < GAME_RESOURCE_BUILD_TONE || (int)type >= GAME_RESOURCE_TYPE_COUNT) {
        return -1;
    }
    mode = &session->economy[player_slot].stock_mode[type];
    if (*mode > 2) *mode = 0;
    else *mode = (uint8_t)((*mode + 1U) % 3U);
    return (int)*mode;
}

unsigned int game_session_update_resource_requests(GameSession *session)
{
    unsigned int changes = 0;
    unsigned int player;
    if (session == NULL) return 0;
    for (player = 0; player < GAME_START_PLAYER_COUNT; ++player) {
        GamePlayerEconomy *economy = &session->economy[player];
        GameRuntimeLocation *hall;
        unsigned int resource;
        if (economy->hall_island_index >= session->island_count ||
            economy->hall_location_index >=
                session->islands[economy->hall_island_index].location_count)
            continue;
        hall = &session->islands[economy->hall_island_index]
                    .locations[economy->hall_location_index];
        for (resource = 0; resource < GAME_RESOURCE_TYPE_COUNT; ++resource) {
            const int16_t linked_slot = economy->resource_task_slot[resource];
            const int request_active = economy->stock_mode[resource] == 2 &&
                (hall->source_flags & 1U) != 0 &&
                hall->resource_stock[resource] <
                    hall->source_capacity_4a * 50 + 150;
            if (request_active && linked_slot == -1) {
                const int slot = game_session_pending_event_add(
                    session, (int16_t)player,
                    (int16_t)economy->hall_island_index, 4, 0,
                    (int16_t)economy->hall_location_index,
                    (int16_t)(resource + 1U));
                if (slot >= 0) {
                    economy->resource_task_slot[resource] = (int16_t)slot;
                    ++changes;
                }
            } else if (!request_active && linked_slot != -1) {
                if (linked_slot >= 0 &&
                    linked_slot < GAME_SESSION_MAX_PENDING_EVENTS) {
                    (void)game_session_pending_event_release(
                        session, (uint8_t)linked_slot);
                }
                economy->resource_task_slot[resource] = -1;
                ++changes;
            }
        }
    }
    return changes;
}

int game_session_adjust_trade_offer(GameSession *session, uint8_t player_slot,
                                    uint8_t resource_row,
                                    uint8_t target_column, int direction)
{
    uint16_t *amount;
    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT ||
        resource_row >= GAME_RESOURCE_TYPE_COUNT ||
        target_column >= GAME_TRADE_TARGET_COUNT ||
        (direction != -1 && direction != 1)) return 0;
    amount = &session->economy[player_slot].trade_offer[resource_row][target_column];
    if (direction > 0) {
        if (*amount < 1000U) {
            *amount = (uint16_t)(*amount > 990U ? 1000U : *amount + 10U);
        }
    } else if (*amount > 0U) {
        *amount = (uint16_t)(*amount < 10U ? 0U : *amount - 10U);
    }
    return 1;
}

int game_session_clear_trade_offers(GameSession *session, uint8_t player_slot)
{
    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT) return 0;
    memset(session->economy[player_slot].trade_offer, 0,
           sizeof(session->economy[player_slot].trade_offer));
    return 1;
}

int game_session_commit_trade_offers(GameSession *session, uint8_t player_slot)
{
    const GamePlayerEconomy *economy;
    unsigned int column;
    unsigned int request_count = 0;
    unsigned int available_requests;
    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT) return -1;
    if ((unsigned int)session->trade_request_count >
        (unsigned int)GAME_SESSION_MAX_TRADE_REQUESTS) return -1;
    economy = &session->economy[player_slot];
    for (column = 0; column < GAME_TRADE_TARGET_COUNT; ++column) {
        unsigned int resource;
        int has_amount = 0;
        for (resource = 0; resource < GAME_RESOURCE_TYPE_COUNT; ++resource) {
            if (economy->trade_offer[resource][column] != 0) {
                has_amount = 1;
                break;
            }
        }
        if (has_amount) ++request_count;
    }
    available_requests = (unsigned int)GAME_SESSION_MAX_TRADE_REQUESTS -
                         (unsigned int)session->trade_request_count;
    if (request_count > available_requests) return -1;
    for (column = 0; column < GAME_TRADE_TARGET_COUNT; ++column) {
        GameTradeRequest *request;
        unsigned int resource;
        int has_amount = 0;
        for (resource = 0; resource < GAME_RESOURCE_TYPE_COUNT; ++resource) {
            if (economy->trade_offer[resource][column] != 0) {
                has_amount = 1;
                break;
            }
        }
        if (!has_amount) continue;
        request = &session->trade_requests[session->trade_request_count++];
        request->source_player = player_slot;
        request->target_player = (uint8_t)(column < player_slot ? column : column + 1U);
        for (resource = 0; resource < GAME_RESOURCE_TYPE_COUNT; ++resource) {
            request->amount[resource] = economy->trade_offer[resource][column];
        }
    }
    (void)game_session_clear_trade_offers(session, player_slot);
    return (int)request_count;
}

int game_session_pop_trade_request(GameSession *session, GameTradeRequest *out)
{
    if (session == NULL || out == NULL || session->trade_request_count == 0) return 0;
    *out = session->trade_requests[0];
    --session->trade_request_count;
    if (session->trade_request_count != 0) {
        memmove(&session->trade_requests[0], &session->trade_requests[1],
                (size_t)session->trade_request_count * sizeof(session->trade_requests[0]));
    }
    memset(&session->trade_requests[session->trade_request_count], 0,
           sizeof(session->trade_requests[0]));
    return 1;
}

int game_session_apply_trade_request(GameSession *session,
                                     const GameTradeRequest *request)
{
    GameRuntimeLocation *source;
    GameRuntimeLocation *target;
    unsigned int resource;

    if (session == NULL || request == NULL ||
        request->source_player >= GAME_START_PLAYER_COUNT ||
        request->target_player >= GAME_START_PLAYER_COUNT) return 0;
    source = player_hall(session, request->source_player);
    target = player_hall(session, request->target_player);
    if (source == NULL || target == NULL) return 0;

    for (resource = 0; resource < GAME_RESOURCE_TYPE_COUNT; ++resource) {
        int32_t amount = (int16_t)request->amount[resource];
        int32_t stock = (int16_t)source->resource_stock[resource];
        uint16_t transfer;

        if (amount < 0) amount = 0;
        if (stock < 0) stock = 0;
        if (amount > stock) amount = stock;
        transfer = (uint16_t)amount;
        source->resource_stock[resource] =
            (uint16_t)(source->resource_stock[resource] - transfer);
        target->resource_stock[resource] =
            (uint16_t)(target->resource_stock[resource] + transfer);
    }
    return 1;
}

int game_session_dispatch_trade_requests(GameSession *session)
{
    int dispatched = 0;

    if (session == NULL ||
        session->trade_request_count > GAME_SESSION_MAX_TRADE_REQUESTS) {
        return -1;
    }
    while (session->trade_request_count != 0) {
        GameTradeRequest *request = &session->trade_requests[0];
        if (!game_session_apply_trade_request(session, request)) break;
        /* Apply first so a request with a missing Hall is not lost. */
        {
            GameTradeRequest consumed;
            if (!game_session_pop_trade_request(session, &consumed)) break;
        }
        ++dispatched;
    }
    return dispatched;
}

int game_session_toggle_diplomacy(GameSession *session, uint8_t source_player,
                                  uint8_t target_player,
                                  GameDiplomacyAction action)
{
    uint8_t target_bit;
    uint8_t *mask;
    GameDiplomacyRequest *request;
    if (session == NULL || source_player >= GAME_START_PLAYER_COUNT ||
        target_player >= GAME_START_PLAYER_COUNT || source_player == target_player ||
        (action != GAME_DIPLOMACY_RECIPIENT && action != GAME_DIPLOMACY_POLICY) ||
        session->diplomacy_request_count >= GAME_SESSION_MAX_DIPLOMACY_REQUESTS) {
        return 0;
    }
    request = &session->diplomacy_requests[session->diplomacy_request_count++];
    request->source_player = source_player;
    request->target_player = target_player;
    request->action = (uint8_t)action;
    target_bit = (uint8_t)(1U << target_player);
    mask = action == GAME_DIPLOMACY_POLICY
        ? &session->diplomacy_policy_mask[source_player]
        : &session->message_recipient_mask[source_player];
    *mask ^= target_bit;
    return 1;
}

int game_session_pop_diplomacy_request(GameSession *session,
                                       GameDiplomacyRequest *out)
{
    if (session == NULL || out == NULL || session->diplomacy_request_count == 0) {
        return 0;
    }
    *out = session->diplomacy_requests[0];
    --session->diplomacy_request_count;
    if (session->diplomacy_request_count != 0) {
        memmove(&session->diplomacy_requests[0], &session->diplomacy_requests[1],
                (size_t)session->diplomacy_request_count *
                sizeof(session->diplomacy_requests[0]));
    }
    memset(&session->diplomacy_requests[session->diplomacy_request_count], 0,
           sizeof(session->diplomacy_requests[0]));
    return 1;
}

static uint16_t *player_inventory_count(GameSession *session,
                                        uint8_t player_slot,
                                        uint8_t item_id)
{
    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT ||
        item_id < GAME_INVENTORY_ITEM_FIRST_ID ||
        item_id >= GAME_INVENTORY_ITEM_FIRST_ID + GAME_INVENTORY_ITEM_COUNT) {
        return NULL;
    }
    return &session->economy[player_slot].inventory_count[
        item_id - GAME_INVENTORY_ITEM_FIRST_ID];
}

int game_session_inventory_credit(GameSession *session, uint8_t player_slot,
                                  uint8_t item_id, uint32_t amount)
{
    uint16_t *count = player_inventory_count(session, player_slot, item_id);
    if (count == NULL || amount > UINT16_MAX - *count) return 0;
    *count = (uint16_t)(*count + amount);
    return 1;
}

int game_session_inventory_debit(GameSession *session, uint8_t player_slot,
                                 uint8_t item_id, uint32_t amount)
{
    uint16_t *count = player_inventory_count(session, player_slot, item_id);
    if (count == NULL || amount > *count) return 0;
    *count = (uint16_t)(*count - amount);
    return 1;
}

int game_session_dispatch_inventory_result(
    GameSession *session, uint8_t player_slot, uint8_t item_id,
    GameInventoryResultApply apply, void *context)
{
    uint16_t *count = player_inventory_count(session, player_slot, item_id);
    if (count == NULL || *count == 0 || apply == NULL) return 0;
    if (!apply(context, player_slot, item_id)) return 0;
    --*count;
    return 1;
}

int game_session_pending_event_add(GameSession *session, int16_t player_id,
                                   int16_t payload_0a, int16_t action_type,
                                   int16_t payload_0c, int16_t payload_0e,
                                   int16_t payload_12)
{
    unsigned int slot;
    GamePendingEvent *event;

    if (session == NULL || session->pending_event_count >=
        GAME_SESSION_MAX_PENDING_EVENTS) return -1;
    for (slot = 0; slot < GAME_SESSION_MAX_PENDING_EVENTS; ++slot) {
        if (session->pending_events[slot].active == 0) break;
    }
    if (slot == GAME_SESSION_MAX_PENDING_EVENTS) return -1;

    event = &session->pending_events[slot];
    memset(event, 0, sizeof(*event));
    event->player_id = player_id;
    event->payload_0a = payload_0a;
    event->action_type = action_type;
    event->payload_0c = payload_0c;
    event->payload_0e = payload_0e;
    event->payload_12 = payload_12;
    event->active = 1;
    event->priority = 1;
    ++session->pending_event_count;

    if (action_type == 5 || action_type == 13) {
        unsigned int other;
        for (other = 0; other < GAME_SESSION_MAX_PENDING_EVENTS; ++other) {
            const GamePendingEvent *candidate = &session->pending_events[other];
            if (other == slot || candidate->active == 0 ||
                candidate->action_type != action_type ||
                candidate->payload_0c != payload_0c ||
                candidate->payload_0e != payload_0e ||
                candidate->payload_12 != payload_12) continue;
            event->active = 0;
            --session->pending_event_count;
            return -1;
        }
    }
    return (int)slot;
}

size_t game_session_collect_task_slots(const GameSession *session,
                                       int16_t player_id,
                                       uint8_t *slot_indices,
                                       size_t capacity)
{
    size_t count = 0;
    unsigned int slot;
    if (session == NULL) return 0;
    for (slot = 0; slot < GAME_SESSION_MAX_PENDING_EVENTS &&
         count < GAME_SESSION_MAX_TASKS; ++slot) {
        const GamePendingEvent *event = &session->pending_events[slot];
        if (event->active == 0 || event->player_id != player_id ||
            event->action_type == 0xb) continue;
        if (slot_indices != NULL && count < capacity)
            slot_indices[count] = (uint8_t)slot;
        ++count;
    }
    return count;
}

int game_session_dispatch_task_command(GameSession *session, uint8_t slot,
                                       uint8_t subtype,
                                       const GamePendingEvent *expected)
{
    GamePendingEvent *event;
    if (session == NULL || expected == NULL ||
        slot >= GAME_SESSION_MAX_PENDING_EVENTS ||
        subtype < 12 || subtype > 15) return 0;
    event = &session->pending_events[slot];
    if (event->active == 0 ||
        event->player_id != expected->player_id ||
        event->payload_0a != expected->payload_0a ||
        event->action_type != expected->action_type ||
        event->payload_12 != expected->payload_12) return 0;
    if (subtype == 12) {
        unsigned int player;
        if (event->action_type == 5 && event->payload_0a >= 0 &&
            (uint16_t)event->payload_0a < session->island_count) {
            GameRuntimeIsland *island =
                &session->islands[(uint16_t)event->payload_0a];
            if (event->payload_0e >= 0 &&
                (uint16_t)event->payload_0e < island->location_count) {
                GameRuntimeLocation *location =
                    &island->locations[(uint16_t)event->payload_0e];
                if (location->record_value_10 == 0 ||
                    location->record_value_10 == 1) {
                    /* FUN_00466533 clears the construction site's owner for
                       these two status values before releasing the slot. */
                    location->owner_id = -1;
                }
            }
        }
        /* FUN_0045fb6f clears the matching Hall resource-request reference
           and returns that mode to 1. Other source link tables are unmodeled. */
        for (player = 0; player < GAME_START_PLAYER_COUNT; ++player) {
            GamePlayerEconomy *economy = &session->economy[player];
            unsigned int resource;
            for (resource = 0; resource < GAME_RESOURCE_TYPE_COUNT; ++resource) {
                if (economy->resource_task_slot[resource] == (int16_t)slot &&
                    event->player_id == (int16_t)player &&
                    event->action_type == 4 &&
                    event->payload_0a == economy->hall_island_index &&
                    event->payload_0e == economy->hall_location_index &&
                    event->payload_12 == (int16_t)(resource + 1U)) {
                    economy->resource_task_slot[resource] = -1;
                    economy->stock_mode[resource] = 1;
                    break;
                }
            }
        }
        return game_session_pending_event_release(session, slot);
    }
    event->priority = (uint16_t)(subtype - 12);
    return 1;
}

int game_session_queue_inventory_action(GameSession *session,
                                        uint8_t player_slot,
                                        uint8_t island_index,
                                        uint16_t location_index,
                                        uint8_t item_id)
{
    const GameRuntimeIsland *island;
    const GameRuntimeLocation *location;

    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT ||
        island_index >= session->island_count ||
        item_id < GAME_INVENTORY_ITEM_FIRST_ID ||
        item_id >= GAME_INVENTORY_ITEM_FIRST_ID + GAME_INVENTORY_ITEM_COUNT) {
        return -1;
    }
    island = &session->islands[island_index];
    if (location_index >= island->location_count) return -1;

    location = &island->locations[location_index];
    /* FUN_0042fa0f(0x40) only rejects this exact class-0 state. Other
       location classes follow additional source rules that this check must
       not silently generalize. */
    if (location->renderer_class == 0 &&
        (location->record_value_10 != 0 || location->owner_id != -1)) return -1;

    /* Packet fields observed in FUN_0042fa0f: category 0, type 4, player,
       current island, zeroed +0x0c, clicked location, selected item. */
    return game_session_pending_event_add(session, (int16_t)player_slot,
        (int16_t)island_index, 4, 0, (int16_t)location_index, (int16_t)item_id);
}

int game_session_queue_glyph_action(GameSession *session,
                                    uint8_t player_slot,
                                    uint8_t island_index,
                                    uint16_t location_index,
                                    uint8_t glyph_index)
{
    GameGlyphActionRequest *request;
    const GameRuntimeIsland *island;

    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT ||
        island_index >= session->island_count || glyph_index >= GAME_GLYPH_COUNT ||
        (session->economy[player_slot].glyph_mask &
            (uint16_t)(1U << glyph_index)) == 0 ||
        session->glyph_action_count >= GAME_SESSION_MAX_GLYPH_ACTIONS) {
        return -1;
    }
    island = &session->islands[island_index];
    if (location_index >= island->location_count) return -1;

    /* FUN_0042fa0f's packet fields are category 3, player, type 3, clicked
       island/location, and DAT_0049e9c0 (the selected glyph). Keep only the
       payload here; the current model has no active record matching
       FUN_0046562b(player, 8): +0 == player and +4 == 8. */
    request = &session->glyph_actions[session->glyph_action_count++];
    request->player_slot = player_slot;
    request->island_index = island_index;
    request->location_index = location_index;
    request->glyph_index = glyph_index;
    return 1;
}

int game_session_pop_glyph_action(GameSession *session,
                                  GameGlyphActionRequest *out)
{
    if (session == NULL || out == NULL || session->glyph_action_count == 0) {
        return 0;
    }
    *out = session->glyph_actions[0];
    --session->glyph_action_count;
    if (session->glyph_action_count != 0) {
        memmove(&session->glyph_actions[0], &session->glyph_actions[1],
                (size_t)session->glyph_action_count * sizeof(session->glyph_actions[0]));
    }
    memset(&session->glyph_actions[session->glyph_action_count], 0,
           sizeof(session->glyph_actions[session->glyph_action_count]));
    return 1;
}

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

int game_session_queue_build_selection(GameSession *session,
                                      uint8_t player_slot,
                                      uint8_t island_index,
                                      uint16_t location_index,
                                      uint16_t item_id)
{
    GameBuildSelectionRequest *request;
    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT ||
        island_index >= session->island_count ||
        location_index >= session->islands[island_index].location_count ||
        session->build_selection_count >= GAME_SESSION_MAX_BUILD_SELECTIONS) {
        return 0;
    }
    request = &session->build_selections[session->build_selection_count++];
    request->category = 0;
    request->player_slot = player_slot;
    request->action_type = 5;
    request->island_index_a = island_index;
    request->reserved_zero = 0;
    request->island_index_b = island_index;
    request->location_index = location_index;
    request->item_id = item_id;
    return 1;
}

int game_session_pop_build_selection(GameSession *session,
                                     GameBuildSelectionRequest *out)
{
    if (session == NULL || out == NULL || session->build_selection_count == 0) {
        return 0;
    }
    *out = session->build_selections[0];
    --session->build_selection_count;
    if (session->build_selection_count != 0) {
        memmove(&session->build_selections[0], &session->build_selections[1],
                (size_t)session->build_selection_count *
                sizeof(session->build_selections[0]));
    }
    memset(&session->build_selections[session->build_selection_count], 0,
           sizeof(session->build_selections[0]));
    return 1;
}

unsigned int game_session_dispatch_build_selections(GameSession *session)
{
    GameBuildSelectionRequest request;
    unsigned int added = 0;

    if (session == NULL) return 0;
    while (game_session_pop_build_selection(session, &request)) {
        int slot;
        if (request.category != 0 || request.action_type != 5) continue;

        /* FUN_004662b7 copies packet byte offsets +2/+4/+8/+10/+12/+14
           into the task record, sets priority 1, and deduplicates type 5
           records by payload_0c, payload_0e, and payload_12. */
        slot = game_session_pending_event_add(
            session, (int16_t)request.player_slot,
            (int16_t)request.island_index_b,
            (int16_t)request.action_type,
            (int16_t)request.reserved_zero,
            (int16_t)request.location_index,
            (int16_t)request.item_id);
        if (slot >= 0) ++added;
    }
    return added;
}

int game_session_queue_island_event3_subtype0(GameSession *session,
                                              uint8_t player_slot,
                                              uint8_t island_index)
{
    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT ||
        island_index >= session->island_count) return 0;
    session->islands[island_index].source_event3_pending_parity[player_slot] ^= 1U;
    return 1;
}

void game_session_dispatch_island_events(GameSession *session)
{
    unsigned int island_index;
    if (session == NULL) return;
    for (island_index = 0; island_index < session->island_count; ++island_index) {
        GameRuntimeIsland *island = &session->islands[island_index];
        unsigned int player_slot;
        for (player_slot = 0; player_slot < GAME_START_PLAYER_COUNT; ++player_slot) {
            if (island->source_event3_pending_parity[player_slot] != 0) {
                island->source_event_state[player_slot] ^= 1U;
                island->source_event3_pending_parity[player_slot] = 0;
            }
        }
    }
}

int game_session_pending_event_release(GameSession *session, uint8_t slot)
{
    GamePendingEvent *event;
    if (session == NULL || slot >= GAME_SESSION_MAX_PENDING_EVENTS) return 0;
    event = &session->pending_events[slot];
    if (event->active == 0 || session->pending_event_count == 0) return 0;
    event->active = 0;
    --session->pending_event_count;
    return 1;
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
