#include "game_session.h"
#include "game_session_combat_internal.h"
#include "game_session_delivery.h"
#include "game_session_delivery_internal.h"
#include "game_session_movement_internal.h"
#include "iw_construct.h"
#include "building_render.h"
#include "island_render_rules.h"
#include "pad_catalog.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

_Static_assert(sizeof(GamePendingEvent) == 0x14,
               "pending event must match FUN_004662b7's 0x14-byte record");
_Static_assert(sizeof(GameBuildSelectionRequest) == 0x10,
               "build selection must preserve FUN_0042fa0f's 16-byte packet");

static void set_location(IslandData *island, unsigned int index,
                         uint8_t renderer_class, uint16_t x, uint16_t y,
                         uint16_t initial_value)
{
    IslandLocation *location = &island->locations[index];
    memset(location, 0, sizeof(*location));
    location->id = (uint16_t)index;
    location->x = x;
    location->y = y;
    location->renderer_class = renderer_class;
    location->renderer_variant = initial_value;
    island->location_count = (uint16_t)(index + 1U);
}

static void make_pad_catalog(PadCatalog *catalog)
{
    unsigned int item;
    memset(catalog, 0, sizeof(*catalog));
    catalog->item_count = 101;
    for (item = 0; item < catalog->item_count; ++item) {
        catalog->items[item].item_id = (uint16_t)item;
        catalog->items[item].movement_cost[0] = 15;
        catalog->items[item].hit_points = 15;
    }
}

static void make_floater_catalog(FloaterCatalog *catalog)
{
    unsigned int tribe;
    memset(catalog, 0, sizeof(*catalog));
    for (tribe = 0; tribe < GAME_START_PLAYER_COUNT; ++tribe) {
        FloaterStats *work = &catalog->rows[tribe * 9U];
        work->hit_points = (int16_t)(2U + tribe);
        work->attack_strength = (int16_t)tribe;
        work->movement_speed = (int16_t)(3U + tribe);
    }
}

static void make_world(WorldDefinition *world, IslandData islands[5])
{
    unsigned int island_index;

    memset(world, 0, sizeof(*world));
    memset(islands, 0, sizeof(IslandData) * 5U);
    world->island_count = 5;
    world->bridge_count = 1;
    world->bridges[0].island_a = 0;
    world->bridges[0].island_b = 1;
    for (island_index = 0; island_index < 5; ++island_index) {
        IslandData *island = &islands[island_index];
        unsigned int marker;
        uint16_t base_x = (uint16_t)(island_index * 100U);
        world->islands[island_index].shape_id = island_index == 1 || island_index == 4 ? 1 : 0;
        for (marker = 0; marker < 4; ++marker) {
            set_location(island, marker, 1, (uint16_t)(base_x + 300U + marker * 20U), 100, 77);
        }
        for (marker = 0; marker < 8; ++marker) {
            set_location(island, marker + 4U, 0,
                         (uint16_t)(base_x + 300U + marker * 20U),
                         (uint16_t)(102U + marker), 99);
        }
    }
    set_location(&islands[0], 12, 2, 10, 10, 0);
    set_location(&islands[1], 12, 2, 10, 10, 0);
    set_location(&islands[4], 12, 2, 10, 10, 0);
    set_location(&islands[4], 13, 3, 10, 10, 7);
}

static void test_session_initializes_player_starts_and_runtime_items(void)
{
    WorldDefinition world;
    IslandData islands[5];
    GameSessionConfig config;
    GameSession session;
    PadCatalog catalog;
    FloaterCatalog floater_catalog;
    char error[160];
    unsigned int player;
    unsigned int island_index;

    make_world(&world, islands);
    make_pad_catalog(&catalog);
    make_floater_catalog(&floater_catalog);
    memset(&config, 0, sizeof(config));
    config.world_index = 1;
    config.difficulty = 2;
    config.selected_tribe = 3;
    config.home_island_index = 0;
    config.random_seed = 1;
    if (!game_session_initialize(&world, islands, &catalog, &floater_catalog,
                                 &config, &session,
                                 error, sizeof(error))) {
        (void)fprintf(stderr, "session initialization failed: %s\n", error);
        assert(0);
    }

    assert(session.config.world_index == 1);
    assert(session.config.difficulty == 2);
    assert(session.config.selected_tribe == 3);
    assert(session.island_count == 5);
    assert(session.floater_count == 16);
    assert(session.economy[0].source_maintenance_capacity == 34);
    assert(session.economy[0].source_maintenance_budget == 30);
    assert(session.pending_event_count == 0);
    assert(session.pending_events[0].active == 0);
    /* Each tribe starts as its own friend, so soldiers never target it. */
    for (player = 0; player < GAME_START_PLAYER_COUNT; ++player)
        assert(session.diplomacy_policy_mask[player] == (uint8_t)(1U << player));
    assert(session.tone_placements.placement_count == 5);
    for (island_index = 0; island_index < session.tone_placements.placement_count;
         ++island_index) {
        const GameStartTonePlacement *placement =
            &session.tone_placements.placements[island_index];
        const GameRuntimeLocation *marker = &session.islands[
            placement->island_index].locations[placement->location_index];
        assert(marker->record_value_10 == placement->item_id);
        assert(marker->owner_id == placement->owner_id);
        assert(marker->source_value_14 == placement->owner_id);
        /* FUN_00460460 gives item 5 rate 1; other markers get the island spawn interval. */
        assert(marker->record_value_10 == 5 ? marker->source_value_32 == 1 :
               marker->source_value_32 >= 0);
        assert(marker->source_value_3e == -1);
    }
    for (island_index = 0; island_index < session.island_count; ++island_index) {
        for (player = 0; player < GAME_START_PLAYER_COUNT; ++player) {
            assert(session.islands[island_index].source_event_state[player] == 0);
            assert(session.islands[island_index].source_event3_pending_parity[player] == 0);
        }
    }
    for (player = 0; player < GAME_START_PLAYER_COUNT; ++player) {
        const GamePlayerStart *start = &session.player_starts.players[player];
        unsigned int resource;
        const GameRuntimeLocation *pad = &session.islands[start->island_index]
            .locations[start->nearest_site_location_index];
        const GameRuntimeLocation *marker = &session.islands[start->island_index]
            .locations[start->marker_location_index];
        const GameFloaterStart *floater = &session.floaters[player * GAME_START_FLOATERS_PER_PLAYER];
        for (resource = 0; resource < GAME_RESOURCE_TYPE_COUNT; ++resource)
            assert(session.economy[player].resource_task_slot[resource] == -1);
        assert((marker->tribe_visibility_mask & (uint8_t)(1U << player)) != 0);
        assert(pad->record_value_10 ==
               GAME_START_INITIAL_PAD_ITEM_ID + (int32_t)player * 16);
        assert(pad->owner_id == (int32_t)player);
        assert(pad->source_value_14 == (int32_t)player);
        assert(pad->source_value_32 == 1);
        assert(pad->source_value_3e == -1);
        assert(pad->source_flags == 0x410);
        assert((pad->source_flags & 0x001U) == 0);
        assert((pad->source_flags & 0x400U) != 0);
        assert(pad->chug_progress == 0 && pad->glyph_progress == 0);
        assert(pad->animation_rate == 1);
        assert(floater->island_index == start->island_index);
        assert(floater->type_index == player);
        assert(floater->source_subtype == 0);
        assert(floater->x == start->marker_x);
        assert(floater->y == start->marker_y);
        assert(floater->movement_speed == 3U + player);
        assert(game_session_count_player_floaters(&session, (uint8_t)player) == 4);
        {
            unsigned int work_count;
            unsigned int total_count;
            unsigned int percentage;
            assert(game_session_workstr_summary(&session, (uint8_t)player,
                &work_count, &total_count, &percentage));
            assert(work_count == 4 && total_count == 4 && percentage == 100);
        }
        {
            unsigned int unit;
            for (unit = 0; unit < start->floater_count; ++unit) {
                const GameFloaterStart *worker = &session.floaters[
                    player * GAME_START_FLOATERS_PER_PLAYER + unit];
                assert(worker->current_hit_points == 2U + player);
                assert(worker->max_hit_points == 2U + player);
                assert(worker->attack_strength == player);
                assert(worker->source_link_0c == -1);
                assert(worker->charge_current == 0);
                {
                    GameFloaterStart linked_worker = *worker;
                    int16_t current_charge;
                    int16_t maximum_charge;
                    const FloaterStats *stats = floater_catalog_find(
                        &floater_catalog, worker->type_index,
                        worker->source_subtype);
                    assert(!game_session_floater_charge_values(worker,
                        &floater_catalog, &current_charge, &maximum_charge));
                    assert(stats != NULL);
                    linked_worker.source_link_0c = 0;
                    linked_worker.charge_current = 2;
                    assert(game_session_floater_charge_values(&linked_worker,
                        &floater_catalog, &current_charge, &maximum_charge));
                    assert(current_charge == 2);
                    assert(maximum_charge == stats->max_attack_points);
                }
            }
        }
        assert(session.economy[player].hall_island_index == start->island_index);
        assert(session.economy[player].hall_location_index ==
               start->nearest_site_location_index);
        assert(session.islands[start->island_index]
                   .locations[start->nearest_site_location_index]
                   .resource_stock[GAME_RESOURCE_BUILD_TONE] == 50);
        assert(session.islands[start->island_index]
                   .locations[start->nearest_site_location_index]
                   .resource_stock[GAME_RESOURCE_CRYSTAL_TONE] == 0);
        assert(session.islands[start->island_index]
                   .locations[start->nearest_site_location_index]
                   .source_value_34 == 15);
        assert(session.islands[start->island_index]
                   .locations[start->nearest_site_location_index]
                   .resource_stock[GAME_RESOURCE_MAGIC_TONE] == 0);
        assert(floater->owner_slot == player);
        assert((session.islands[start->island_index].access_mask & (1U << player)) != 0);
        assert(game_session_can_enter_island(&session, start->island_index,
                                             (uint8_t)(1U << player)));
        assert(game_session_world_map_frame_offset(
                   &session, start->island_index, (uint8_t)(1U << player), 0) == 0);
        assert(game_session_world_map_frame_offset(
                   &session, start->island_index, (uint8_t)(1U << player), 1) == 30);
    }
    {
        GamePendingEvent repair;
        const GamePlayerEconomy *economy = &session.economy[0];
        GameRuntimeLocation *hall = &session.islands[economy->hall_island_index]
            .locations[economy->hall_location_index];
        int16_t current;
        int16_t maximum;
        memset(&repair, 0, sizeof(repair));
        repair.active = 1;
        repair.action_type = 0x12;
        repair.payload_0a = (int16_t)economy->hall_island_index;
        repair.payload_0e = (int16_t)economy->hall_location_index;
        hall->source_value_34 = 7;
        hall->source_capacity_4a = 2;
        assert(game_session_repair_task_values(&session, &catalog, &repair,
                                               &current, &maximum));
        assert(current == 7 && maximum == 25);
        assert(game_session_repair_location_values(
            &session, &catalog, (uint8_t)economy->hall_island_index,
            economy->hall_location_index, &current, &maximum));
        assert(current == 7 && maximum == 25);
        assert(!game_session_repair_location_values(
            &session, &catalog, UINT8_MAX, 0, &current, &maximum));
        assert(!game_session_repair_location_values(
            &session, &catalog, (uint8_t)economy->hall_island_index,
            UINT16_MAX, &current, &maximum));
        repair.payload_0a = INT16_MAX;
        assert(!game_session_repair_task_values(&session, &catalog, &repair,
                                                &current, &maximum));
        repair.payload_0a = (int16_t)economy->hall_island_index;
        repair.payload_0e = INT16_MAX;
        assert(!game_session_repair_task_values(&session, &catalog, &repair,
                                                &current, &maximum));
        repair.payload_0e = (int16_t)economy->hall_location_index;
        repair.action_type = 5;
        assert(!game_session_repair_task_values(&session, &catalog, &repair,
                                                &current, &maximum));
        repair.action_type = 0x12;
        hall->source_capacity_4a = -3;
        assert(!game_session_repair_task_values(&session, &catalog, &repair,
                                                &current, &maximum));
    }
    {
        GameSession task_session;
        PadCatalog task_catalog;
        GameRuntimeLocation *target;
        GamePendingEvent task;
        int16_t current;
        int16_t maximum;
        memset(&task_session, 0, sizeof(task_session));
        memset(&task_catalog, 0, sizeof(task_catalog));
        memset(&task, 0, sizeof(task));
        task_session.island_count = 2;
        task_session.islands[1].location_count = 3;
        target = &task_session.islands[1].locations[2];
        target->record_value_10 = 0x25;
        target->owner_id = 0;
        target->source_value_34 = 9;
        target->source_capacity_4a = 1;
        target->resource_stock[0] = 20;
        task_catalog.item_count = 0x36;
        task_catalog.items[0x25].item_id = 0x25;
        task_catalog.items[0x25].movement_cost[0] = 33;
        task_catalog.items[0x25].hit_points = 15;
        task_catalog.items[0x35].item_id = 0x35;
        task_catalog.items[0x35].building_tone_cost = 40;
        task.active = 1;
        task.player_id = 1;
        task.payload_0a = 1;
        task.payload_0e = 2;
        task.action_type = 0x12;
        assert(game_session_repair_task_values(&task_session, &task_catalog,
                                              &task, &current, &maximum));
        assert(current == 9 && maximum == 20);
        target->record_value_10 = 0;
        target->owner_id = -1;
        target->source_value_14 = -1;
        target->source_value_22 = (uint16_t)(1U << 1);
        target->construction_site_size = 1;
        task.action_type = 5;
        task.payload_0a = 1;
        task.payload_12 = 0x25;
        assert(game_session_construction_task_values(&task_session, &task_catalog,
                                                    &task, &current, &maximum));
        assert(current == 20 && maximum == 40);
        task.payload_0a = 2;
        assert(!game_session_construction_task_values(&task_session, &task_catalog,
                                                     &task, &current, &maximum));
        task.payload_0a = 1;
        task.payload_0e = 3;
        assert(!game_session_construction_task_values(&task_session, &task_catalog,
                                                     &task, &current, &maximum));
    }
    assert(game_session_count_player_floaters(NULL, 0) == 0);
    assert(game_session_count_player_floaters(&session,
               GAME_START_PLAYER_COUNT) == 0);
    {
        unsigned int island;
        int found_unassigned = 0;
        for (island = 0; island < session.island_count; ++island) {
            if (session.islands[island].access_mask == 0) {
                found_unassigned = 1;
                assert(!game_session_can_enter_island(
                    &session, (uint8_t)island, (uint8_t)(1U << config.selected_tribe)));
                assert(game_session_world_map_frame_offset(
                           &session, (uint8_t)island,
                           (uint8_t)(1U << config.selected_tribe), 0) == 15);
                assert(game_session_world_map_frame_offset(
                           &session, (uint8_t)island,
                           (uint8_t)(1U << config.selected_tribe), 1) == 15);
            }
        }
        assert(found_unassigned);
    }
    assert(!game_session_can_enter_island(&session, session.island_count, 0xff));
    assert(!game_session_can_enter_island(NULL, 0, 0xff));
    assert(game_session_world_map_frame_offset(&session, session.island_count,
                                               0xff, 1) == -1);
    assert(game_session_world_map_frame_offset(NULL, 0, 0xff, 1) == -1);
    assert(!game_session_bridge_is_active(&session, 0, world.bridge_count));
    assert(game_session_set_bridge_active(&session, 0, world.bridge_count, 1));
    assert(game_session_bridge_is_active(&session, 0, world.bridge_count));
    assert(game_session_set_bridge_active(&session, 0, world.bridge_count, 0));
    assert(!game_session_bridge_is_active(&session, 0, world.bridge_count));
    assert(!game_session_set_bridge_active(&session, world.bridge_count,
                                           world.bridge_count, 1));
    assert(!game_session_bridge_is_active(NULL, 0, world.bridge_count));
    assert(!game_session_bridge_is_active(&session, 0, WORLD_MAP_MAX_BRIDGES + 1));
    assert(game_session_apply_world_bridge_message(&session, world.bridge_count, 0));
    assert(game_session_bridge_is_active(&session, 0, world.bridge_count));
    assert(game_session_apply_world_bridge_message(&session, world.bridge_count, 0x100));
    assert(!game_session_bridge_is_active(&session, 0, world.bridge_count));
    assert(!game_session_apply_world_bridge_message(NULL, world.bridge_count, 0));
    assert(session.islands[0].locations[12].record_value_10 == 2);
    assert(session.islands[1].locations[12].record_value_10 == 2);
    assert(session.islands[0].locations[12].bridge_neighbor_island == 1);
    assert(session.islands[1].locations[12].bridge_neighbor_island == 0);
    assert(session.islands[4].locations[12].record_value_10 == 0); /* unmatched class-2 site becomes class 0 */
    assert(session.islands[4].locations[12].bridge_neighbor_island == -1);
    assert(session.islands[4].locations[13].record_value_10 == 7);
    assert(session.islands[4].locations[13].owner_id == -1);
    assert(session.islands[4].locations[13].source_location_slot_18 == -1);
    {
        GameRuntimeLocation *bridge_a = &session.islands[0].locations[12];
        GameRuntimeLocation *bridge_b = &session.islands[1].locations[12];
        assert(!game_session_world_bridge_is_renderable(
            &session, 0, world.bridge_count, 0, 1));
        assert(game_session_set_bridge_active(&session, 0, world.bridge_count, 1));
        /* A map-edge flag and paired possible bridge sites are not enough:
           the binary also marks both endpoint objects when the bridge exists. */
        assert(!game_session_world_bridge_is_renderable(
            &session, 0, world.bridge_count, 0, 1));
        assert(game_session_mark_bridge_constructed(
            &session, 0, world.bridge_count, 0, 1));
        assert(game_session_world_bridge_is_renderable(
            &session, 0, world.bridge_count, 0, 1));
        assert(session.islands[0].locations[12].bridge_constructed);
        assert(session.islands[1].locations[12].bridge_constructed);
        assert(game_session_set_bridge_active(&session, 0, world.bridge_count, 0));
        assert(!game_session_world_bridge_is_renderable(
            &session, 0, world.bridge_count, 0, 1));
        assert(game_session_set_bridge_active(&session, 0, world.bridge_count, 1));
        bridge_b->bridge_neighbor_island = -1;
        assert(!game_session_world_bridge_is_renderable(
            &session, 0, world.bridge_count, 0, 1));
        bridge_b->bridge_neighbor_island = 0;
        bridge_a->renderer_class = 0;
        assert(!game_session_world_bridge_is_renderable(
            &session, 0, world.bridge_count, 0, 1));
        bridge_a->renderer_class = 2;
        assert(!game_session_world_bridge_is_renderable(
            &session, 0, world.bridge_count, 1, 1));
        assert(!game_session_world_bridge_is_renderable(
            &session, world.bridge_count, world.bridge_count, 0, 1));
    }
    assert(session.class0_assignments == 9);
    {
        unsigned int island_index;
        unsigned int special_site_count = 0;
        unsigned int link_site_count = 0;
        for (island_index = 0; island_index < session.island_count; ++island_index) {
            unsigned int location_index;
            for (location_index = 0;
                 location_index < session.islands[island_index].location_count;
                 ++location_index) {
                const GameRuntimeLocation *location =
                    &session.islands[island_index].locations[location_index];
                if (location->record_value_10 != 1) continue;
                if (location->record_value_24 == 5) ++special_site_count;
                if (location->record_value_24 >= 6) ++link_site_count;
            }
        }
        assert(special_site_count == world.bridge_count);
        assert(link_site_count == 2U * (world.island_count - 1U));
    }
    assert(islands[1].locations[4].renderer_variant == 99);
}

/* Ordered test fragments keep shared fixture helpers in this translation unit. */
#include "game_session_sections/resources.inc"

#include "game_session_sections/events.inc"

#include "game_session_sections/ticks.inc"

#include "game_session_sections/construction.inc"

#include "game_session_sections/movement.inc"

#include "game_session_sections/worker_tasks.inc"
#include "game_session_sections/audio.inc"
#include "game_session_sections/spells.inc"

int main(void)
{
    test_session_initializes_player_starts_and_runtime_items();
    test_building_placement_matches_source_runtime_initialization();
    test_building_placement_links_every_player_and_source_record();
    test_full_source_record_table_still_completes_construction();
    test_source_record_capacity_is_per_player();
    test_several_workers_share_one_construction_task_from_the_hall();
    test_busy_worker_moves_to_a_task_with_two_fewer_workers();
    test_worker_tasks_and_panic();
    test_audio_effect_sounds();
    test_hall_resource_ledger_is_safe();
    test_hall_resource_modes_cycle_through_original_three_states();
    test_hall_stock_mode_creates_and_releases_linked_resource_tasks();
    test_inventory_counts_cover_source_item_id_range();
    test_inventory_result_debits_only_after_receiver_success();
    test_location_resource_consumption_matches_source_guards();
    test_location_move_costs_use_pad_tuple_and_runtime_multiplier();
    test_source_capacity_cycle_uses_base_item_id_for_each_player();
    test_last_island_seals_start_victory_sequence();
    test_leviathan_bond_notices_follow_world_tick();
    test_cast_action_accepts_owner_variant_ids();
    test_cast_kind_one_applies_area_and_expires_site_state();
    test_pending_event_table_matches_source_slots_and_deduplication();
    test_task_projection_matches_source_filter_and_cap();
    test_task_command_dispatch_guards_and_effects();
    test_inventory_action_reserves_source_payload_without_mutation();
    test_repair_task_repeats_supply_and_heals_after_40_ticks();
    test_site_damage_filters_player_variant_building_ids();
    test_code_five_delivery_starts_bridge_cons_for_its_owner();
    test_source_event3_subtype0_queues_and_toggles_only_player_bit();
    test_glyph_map_click_queues_packet_without_world_effect();
    test_glyph_ownership_mask_is_player_local_and_idempotent();
    test_onoff_action_queues_target_without_changing_location_flags();
    test_build_selection_queues_source_packet_without_placing_item();
    test_construct_click_item_becomes_queued_build_packet();
    test_cancelled_construction_releases_assigned_floater();
    test_inci_animation_uses_source_counter_and_delayed_activation();
    test_active_item_four_and_twenty_two_counter_stops_at_32();
    test_class0_item5_spawns_neutral_item_after_difficulty_delay();
    test_leviathan_marker_becomes_defense_building_with_time();
    test_leviathan_spread_waits_while_marker_rate_is_zero();
    test_neutral_pool_is_contaminated_then_matures();
    test_player_owned_pool_is_not_contaminated();
    test_class0_neutral_pad_needs_fitting_leviathan_size();
    test_spore_claimed_noshape_pad_grows_without_render_rows();
    test_leviathan_spread_only_converts_its_own_island();
    test_leviathan_spawner_births_units_on_its_island_over_time();
    test_leviathan_defense_hurts_only_workers_in_reach_on_its_island();
    test_inactive_leviathan_defense_does_not_fire();
    test_tone_producers_output_their_own_resource_for_every_tribe();
    test_item_animation_uses_source_flags_and_per_object_counters();
    test_tone_pool_uses_two_source_counter_sequences();
    test_active_cons_and_prod_counters_finish_at_source_limits();
    test_producer_cadence_starts_prod_and_waits_for_output_consumption();
    test_initialization_is_transactional_on_bad_world();
    test_player_source_building_keeps_native_id_for_island_state();
    test_construction_assignment_matches_source_candidate_guards();
    test_construction_task_delivers_cost_before_deferred_placement();
    test_tone_maintenance_surplus_tracks_regions_and_workers();
    test_recruitment_waits_for_surplus_then_creates_animated_worker();
    test_initialized_workers_build_from_queued_selection();
    test_construction_completes_on_native_empty_status_one_site();
    test_wandering_worker_with_stale_delivery_claim_rejoins_pool();
    test_charge_order_accepts_each_players_source_variant();
    test_bridge_crossing_keeps_soldier_hall_link();
    test_floater_pickup_order_collects_ground_artifact();
    test_obtain_task_crosses_bridge_to_ground_artifact();
    test_floater_move_state_advances_only_simulation_assigned_destinations();
    test_floater_selection_uses_original_hit_radius_and_island();
    test_initial_worker_accepts_coordinate_move_order();
    test_workstr_counts_subtype_zero_and_truncates_percentage();
    test_location_panel_level_uses_original_low_nibble_plus_one();
    test_worker_site_point_follows_bldinf_offsets_and_graspxy();
    test_cast_kind_table_follows_owner_and_action_subtype();
    test_cast_kind_costs_follow_spells_txt();
    test_cast_sound_ids_match_effect_names();
    test_cast_dispatch_debits_both_tones_only_when_both_suffice();
    test_cast_glyph_eight_discounts_magic_only();
    test_cast_pools_are_the_buildings_not_the_halls();
    test_cast_dispatch_needs_caster_level_and_free_worker();
    test_cast_queue_rejects_foreign_or_malformed_requests();
    test_kill_beast_cast_requires_a_leviathan_target();
    test_mass_heal_restores_owner_workers_up_to_the_level_cap();
    test_speed_cast_sets_owner_timer_by_level();
    test_timed_site_spells_store_level_scaled_timers();
    test_blast_cast_damages_by_distance_and_consumes_the_caster();
    test_blast_cast_radius_and_damage_grow_with_level();
    test_fixed_area_cast_hits_floaters_within_250_without_dying_itself();
    test_fixed_area_cast_kills_a_weak_floater();
    test_site_damage_drains_hp_then_destroys_or_clears();
    test_pool_drain_spell_needs_a_filled_pool_and_clears_when_empty();
    test_destroy_support_spell_targets_leviathan_spawner_sites();
    test_leviathan_spawner_freeze_hits_every_spawner_on_the_island();
    test_leviathan_reevaluation_cast_starts_the_island_timer();
    test_cast_steps_reject_invalid_callers();
    test_cast_visual_uses_owner_effect_and_one_frame_per_two_ticks();
    test_attack_impact_visual_steps_one_frame_per_odd_update();
    test_effect_defs_parse_types_levels_chain_and_speed();
    test_oneshot_attack_visual_plays_once_at_the_attacker();
    test_cast_attack_visual_chains_into_a_bullet_that_reaches_its_target();
    test_bullet_visual_applies_attxy_mirroring_and_timeout();
    test_lightning_visual_grows_toward_the_target_then_ends();
    test_missing_atteff_rows_are_not_spawned();
    test_arrived_bullet_turns_into_the_realm_impact_when_the_hit_landed();
    test_atteff_bullet_hit_is_resolved_on_arrival_not_at_the_strike();
    test_deferred_hit_is_deterministic_for_a_given_seed();
    test_dead_attacker_effect_deals_no_damage_and_frees_the_slot();
    test_weak_attackers_still_hit_at_the_strike();
    test_attack_bookkeeping_goes_to_the_attacker();
    test_out_of_range_caster_walks_then_casts();
    test_spore_deaths_go_through_the_native_damage_guard();
    test_spore_prefers_building_pads_until_markers_allow_sources();
    test_spore_skips_claimed_sites_and_its_own_position();
    test_moving_spore_retargets_only_on_its_cadence_once_claimed();
    test_targetless_spore_loses_one_hp_every_128_ticks();
    test_training_refreshes_the_new_subtype_combat_row();
    test_building_order_keeps_the_target_island();
    test_soldiers_fight_through_building_orders();
    test_building_order_crosses_a_bridge_and_keeps_the_link();
    test_wounded_soldier_heals_in_its_building();
    test_wounded_soldier_crosses_a_bridge_to_heal();
    test_effect_instances_queue_their_sound_with_position();
    (void)puts("game session unit tests passed");
    return 0;
}
