#include "game_session_setup_internal.h"
#include "iw_construct.h"

#include <stdio.h>
#include <string.h>

static void set_error(char *error, size_t capacity, const char *message)
{
    if (error == NULL || capacity == 0) return;
    (void)snprintf(error, capacity, "%s", message);
    error[capacity - 1] = '\0';
}

int game_session_initialize_start_players(
    GameSession *session, const IslandData *runtime_layouts,
    const FloaterCatalog *floater_catalog,
    char *error, size_t error_capacity)
{
    unsigned int island_index;
    unsigned int floater_cursor = 0;
    for (island_index = 0; island_index < GAME_START_PLAYER_COUNT; ++island_index) {
        const GamePlayerStart *start = &session->player_starts.players[island_index];
        GameRuntimeIsland *runtime = &session->islands[start->island_index];
        unsigned int location_index = start->nearest_site_location_index;
        unsigned int unit;

        for (unit = 0; unit < GAME_RESOURCE_TYPE_COUNT; ++unit)
            session->economy[island_index].resource_task_slot[unit] = -1;

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
            runtime->locations[start->marker_location_index].source_value_22 =
                runtime->locations[start->marker_location_index].tribe_visibility_mask;
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
        session->economy[island_index].hall_island_index = start->island_index;
        session->economy[island_index].hall_location_index = (uint16_t)location_index;
        session->economy[island_index].hall_x = runtime_layouts[start->island_index]
            .locations[location_index].x;
        session->economy[island_index].hall_y = runtime_layouts[start->island_index]
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
            floater = &session->floaters[floater_cursor++];
            floater->is_active = 1;
            floater->island_index = start->island_index;
            floater->type_index = start->floater_type_index;
            floater->source_subtype = 0;
            floater->owner_slot = (uint8_t)island_index;
            /* FUN_00466fe4 initializes current hits to the loaded max HP.
               The type/subtype lookup uses the *work row in floater.txt. */
            floater->current_hit_points = (uint8_t)stats->hit_points;
            floater->max_hit_points = (uint8_t)stats->hit_points;
            floater->attack_strength = (uint8_t)stats->attack_strength;
            floater->source_progress_08 = 0;
            floater->max_attack_points = stats->max_attack_points;
            floater->attack_realm = stats->attack_realm;
            if (stats->attack_realm >= 0 && stats->attack_realm < 4) {
                memcpy(floater->attack_impact_frame_counts,
                       floater_catalog->impact_frame_counts[stats->attack_realm],
                       sizeof(floater->attack_impact_frame_counts));
            }
            floater->attack_range = stats->attack_range;
            floater->attack_period = stats->attack_period;
            floater->source_link_0c = -1;
            floater->charge_source_island = UINT8_MAX;
            floater->charge_source_location = UINT16_MAX;
            floater->charge_current = 0;
            floater->carried_resource_code = 0;
            floater->order_resource_code = 0;
            floater->linked_task_slot = -1;
            floater->order_source_location = -1;
            floater->order_target_island = start->island_index;
            floater->order_source_island = start->island_index;
            floater->handoff_departure_location = -1;
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
    session->floater_count = (uint8_t)floater_cursor;

    return 1;
}

#include "game_session_setup_internal.h"

#include <stdio.h>
#include <string.h>

int game_session_initialize_start_islands(
    GameSession *session, const WorldDefinition *world,
    const IslandData *runtime_layouts,
    int32_t bridge_neighbors[WORLD_MAP_MAX_ISLANDS][ISLAND_DATA_MAX_LOCATIONS],
    int32_t shape_ids[WORLD_MAP_MAX_ISLANDS],
    char *error, size_t error_capacity)
{
    unsigned int island_index;
    for (island_index = 0; island_index < world->island_count; ++island_index) {
        const IslandData *source = &runtime_layouts[island_index];
        GameRuntimeIsland *runtime = &session->islands[island_index];
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
            state->source_category_slot_60 = -1;
            state->source_value_34 = -1;
            state->source_progress_08 = 0;
            state->source_value_22 = 0;
            state->source_task_slot[0] = -1;
            state->source_task_slot[1] = -1;
            state->source_task_slot[2] = -1;
            {
                unsigned int slot;
                for (slot = 0; slot < 8; ++slot)
                    state->charge_floater_slots[slot] = -1;
            }
            state->charge_floater_count = 0;
            state->charge_recent_floater = -1;
            state->charge_staff_task_handle = -1;
            state->record_value_24 = 0;
            state->bridge_neighbor_island = bridge_neighbors[island_index][location_index];
            state->x = location->x;
            state->y = location->y;
            state->renderer_class = location->renderer_class;
            state->construction_site_size = UINT8_MAX;
            {
                uint8_t site_size;
                if (iw_construct_site_size(location, &site_size))
                    state->construction_site_size = site_size;
            }
        }
    }

    return 1;
}
