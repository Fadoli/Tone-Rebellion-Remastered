#include "game_session.h"
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
    assert(session.pending_event_count == 0);
    assert(session.pending_events[0].active == 0);
    assert(session.tone_placements.placement_count == 5);
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
        task.action_type = 5;
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

static void test_hall_resource_ledger_is_safe(void)
{
    GameSession session;

    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    session.islands[0].location_count = 1;
    session.economy[2].hall_island_index = 0;
    session.economy[2].hall_location_index = 0;

    assert(game_session_credit_resource(&session, 2, GAME_RESOURCE_BUILD_TONE, 25));
    assert(session.islands[0].locations[0]
               .resource_stock[GAME_RESOURCE_BUILD_TONE] == 25);
    assert(!game_session_debit_resource(&session, 2, GAME_RESOURCE_BUILD_TONE, 26));
    assert(session.islands[0].locations[0]
               .resource_stock[GAME_RESOURCE_BUILD_TONE] == 25);
    assert(game_session_debit_resource(&session, 2, GAME_RESOURCE_BUILD_TONE, 5));
    assert(session.islands[0].locations[0]
               .resource_stock[GAME_RESOURCE_BUILD_TONE] == 20);
    assert(!game_session_credit_resource(&session, 4, GAME_RESOURCE_BUILD_TONE, 1));
    assert(!game_session_credit_resource(&session, 2, (GameResourceType)9, 1));
    session.islands[0].locations[0]
        .resource_stock[GAME_RESOURCE_BUILD_TONE] = UINT16_MAX;
    assert(!game_session_credit_resource(&session, 2, GAME_RESOURCE_BUILD_TONE, 1));
}

static void test_hall_resource_modes_cycle_through_original_three_states(void)
{
    GameSession session = {0};

    assert(session.economy[1].stock_mode[GAME_RESOURCE_BUILD_TONE] == 0);
    assert(game_session_cycle_resource_stock_mode(
               &session, 1, GAME_RESOURCE_BUILD_TONE) == 1);
    assert(game_session_cycle_resource_stock_mode(
               &session, 1, GAME_RESOURCE_BUILD_TONE) == 2);
    assert(game_session_cycle_resource_stock_mode(
               &session, 1, GAME_RESOURCE_BUILD_TONE) == 0);
    assert(game_session_cycle_resource_stock_mode(
               &session, 1, GAME_RESOURCE_CRYSTAL_TONE) == 1);
    assert(session.economy[1].stock_mode[GAME_RESOURCE_BUILD_TONE] == 0);
    assert(session.economy[0].stock_mode[GAME_RESOURCE_CRYSTAL_TONE] == 0);
    assert(game_session_cycle_resource_stock_mode(
               &session, GAME_START_PLAYER_COUNT, GAME_RESOURCE_BUILD_TONE) == -1);
    assert(game_session_cycle_resource_stock_mode(
               &session, 1, (GameResourceType)7) == -1);
}

static void test_hall_stock_mode_creates_and_releases_linked_resource_tasks(void)
{
    GameSession session = {0};
    GamePlayerEconomy *economy = &session.economy[1];
    GameRuntimeLocation *hall;
    GamePendingEvent expected;
    int slot;
    unsigned int resource;
    unsigned int player;

    session.island_count = 1;
    session.islands[0].location_count = 1;
    for (player = 0; player < GAME_START_PLAYER_COUNT; ++player) {
        for (resource = 0; resource < GAME_RESOURCE_TYPE_COUNT; ++resource)
            session.economy[player].resource_task_slot[resource] = -1;
    }
    economy->hall_island_index = 0;
    economy->hall_location_index = 0;
    hall = &session.islands[0].locations[0];
    hall->source_flags = 0x410;
    economy->stock_mode[GAME_RESOURCE_BUILD_TONE] = 2;
    hall->resource_stock[GAME_RESOURCE_BUILD_TONE] = 149;

    /* FUN_0045eaa7 uses strict stock < (short(+0x4a) * 50 + 150). */
    /* The constructor's 0x400 state bit is not the separate 0x001 request
       gate; both are bits in the same source +0x1c word. */
    assert(game_session_update_resource_requests(&session) == 0);
    hall->source_flags |= 1U;
    assert(game_session_update_resource_requests(&session) == 1);
    assert(session.pending_event_count == 1);
    slot = economy->resource_task_slot[GAME_RESOURCE_BUILD_TONE];
    assert(slot == 0);
    assert(session.pending_events[slot].player_id == 1);
    assert(session.pending_events[slot].payload_0a == 0);
    assert(session.pending_events[slot].payload_0c == 0);
    assert(session.pending_events[slot].action_type == 4);
    assert(session.pending_events[slot].payload_0e == 0);
    assert(session.pending_events[slot].payload_12 == 1);
    assert(game_session_update_resource_requests(&session) == 0);

    hall->resource_stock[GAME_RESOURCE_BUILD_TONE] = 150;
    assert(game_session_update_resource_requests(&session) == 1);
    assert(session.pending_event_count == 0);
    assert(economy->resource_task_slot[GAME_RESOURCE_BUILD_TONE] == -1);
    assert(economy->stock_mode[GAME_RESOURCE_BUILD_TONE] == 2);

    hall->resource_stock[GAME_RESOURCE_BUILD_TONE] = 149;
    assert(game_session_update_resource_requests(&session) == 1);
    slot = economy->resource_task_slot[GAME_RESOURCE_BUILD_TONE];
    expected = session.pending_events[slot];
    assert(game_session_dispatch_task_command(&session, (uint8_t)slot,
                                               12, &expected));
    assert(economy->resource_task_slot[GAME_RESOURCE_BUILD_TONE] == -1);
    assert(economy->stock_mode[GAME_RESOURCE_BUILD_TONE] == 1);
    assert(session.pending_event_count == 0);
    assert(game_session_update_resource_requests(&session) == 0);

    economy->stock_mode[GAME_RESOURCE_CRYSTAL_TONE] = 2;
    hall->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] = 0;
    hall->source_flags = 0x410;
    assert(game_session_update_resource_requests(&session) == 0);
    assert(economy->resource_task_slot[GAME_RESOURCE_CRYSTAL_TONE] == -1);
}

static void test_inventory_counts_cover_source_item_id_range(void)
{
    GameSession session = {0};
    assert(game_session_inventory_credit(&session, 1, 5, 2));
    assert(game_session_inventory_credit(&session, 1, 33, 3));
    assert(session.economy[1].inventory_count[0] == 2);
    assert(session.economy[1].inventory_count[28] == 3);
    assert(!game_session_inventory_debit(&session, 1, 5, 3));
    assert(session.economy[1].inventory_count[0] == 2);
    assert(game_session_inventory_debit(&session, 1, 5, 2));
    assert(session.economy[1].inventory_count[0] == 0);
    session.economy[1].inventory_count[28] = UINT16_MAX;
    assert(!game_session_inventory_credit(&session, 1, 33, 1));
    assert(!game_session_inventory_credit(&session, 1, 4, 1));
    assert(!game_session_inventory_debit(&session, 1, 34, 1));
    assert(!game_session_inventory_credit(&session, GAME_START_PLAYER_COUNT, 5, 1));
}

typedef struct InventoryResultProbe {
    uint8_t expected_player;
    uint8_t expected_item;
    int result;
    unsigned int calls;
} InventoryResultProbe;

static int apply_inventory_result_probe(void *context, uint8_t player_slot,
                                        uint8_t item_id)
{
    InventoryResultProbe *probe = (InventoryResultProbe *)context;
    assert(probe != NULL);
    assert(player_slot == probe->expected_player);
    assert(item_id == probe->expected_item);
    ++probe->calls;
    return probe->result;
}

static void test_inventory_result_debits_only_after_receiver_success(void)
{
    GameSession session = {0};
    InventoryResultProbe probe = {2, 17, 1, 0};

    assert(game_session_inventory_credit(&session, probe.expected_player,
                                         probe.expected_item, 1));
    assert(game_session_dispatch_inventory_result(
        &session, probe.expected_player, probe.expected_item,
        apply_inventory_result_probe, &probe));
    assert(probe.calls == 1);
    assert(session.economy[probe.expected_player].inventory_count[12] == 0);

    assert(game_session_inventory_credit(&session, probe.expected_player,
                                         probe.expected_item, 1));
    probe.result = 0;
    assert(!game_session_dispatch_inventory_result(
        &session, probe.expected_player, probe.expected_item,
        apply_inventory_result_probe, &probe));
    assert(probe.calls == 2);
    assert(session.economy[probe.expected_player].inventory_count[12] == 1);

    assert(game_session_inventory_debit(&session, probe.expected_player,
                                        probe.expected_item, 1));
    assert(!game_session_dispatch_inventory_result(
        &session, probe.expected_player, probe.expected_item,
        apply_inventory_result_probe, &probe));
    assert(probe.calls == 2);
    assert(!game_session_dispatch_inventory_result(
        &session, probe.expected_player, 34,
        apply_inventory_result_probe, &probe));
    assert(!game_session_dispatch_inventory_result(
        &session, probe.expected_player, probe.expected_item, NULL, &probe));
    assert(probe.calls == 2);
}

static void test_location_resource_consumption_matches_source_guards(void)
{
    GameSession session = {0};
    GameRuntimeLocation *location;
    session.island_count = 1;
    session.islands[0].location_count = 2;
    location = &session.islands[0].locations[0];
    location->record_value_10 = 0x25;
    location->record_value_24 = 2;

    assert(game_session_location_resource_available(&session, 0, 0, 2));
    assert(!game_session_location_resource_available(&session, 0, 0, 1));
    assert(!game_session_consume_location_resource(&session, 0, 0, 1));
    assert(location->record_value_24 == 2);
    assert(game_session_consume_location_resource(&session, 0, 0, 2));
    assert(location->record_value_24 == 0);
    assert(!game_session_location_resource_available(&session, 0, 0, 2));
    assert(!game_session_consume_location_resource(&session, 0, 0, 2));

    location = &session.islands[0].locations[1];
    location->record_value_10 = 0x2a;
    location->owner_id = 0;
    location->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] = 1;
    assert(game_session_location_resource_available(&session, 0, 1, 2));
    assert(game_session_consume_location_resource(&session, 0, 1, 2));
    assert(location->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] == 0);
    assert(!game_session_location_resource_available(&session, 0, 1, 2));
    assert(!game_session_consume_location_resource(&session, 0, 1, 2));
    assert(!game_session_consume_location_resource(&session, 0, 1, 4));

    session.economy[0].inventory_count[0] = 1;
    assert(game_session_location_resource_available(&session, 0, 1, 5));
    assert(game_session_consume_location_resource(&session, 0, 1, 5));
    assert(session.economy[0].inventory_count[0] == 0);
    assert(!game_session_location_resource_available(&session, 0, 1, 5));
    assert(!game_session_consume_location_resource(&session, 0, 1, 5));

    /* FUN_00452c31 gates non-Hall inventory availability on source +0x18,
       but FUN_00452eac's debit path does not repeat that gate. */
    location = &session.islands[0].locations[0];
    location->record_value_10 = 0x2c;
    location->owner_id = 0;
    location->source_location_slot_18 = -1;
    session.economy[0].inventory_count[0] = 1;
    assert(!game_session_location_resource_available(&session, 0, 0, 5));
    assert(game_session_consume_location_resource(&session, 0, 0, 5));
    assert(session.economy[0].inventory_count[0] == 0);
    session.economy[0].inventory_count[0] = 1;
    location->source_location_slot_18 = 3;
    assert(game_session_location_resource_available(&session, 0, 0, 5));
    assert(game_session_consume_location_resource(&session, 0, 0, 5));
    assert(session.economy[0].inventory_count[0] == 0);

    assert(!game_session_consume_location_resource(&session, 0, 1, 34));
    assert(!game_session_consume_location_resource(&session, 0, 2, 2));
    assert(!game_session_consume_location_resource(&session, 1, 0, 2));
    assert(!game_session_consume_location_resource(NULL, 0, 0, 2));
    assert(!game_session_location_resource_available(&session, 0, 2, 2));
    assert(!game_session_location_resource_available(NULL, 0, 0, 2));
}

static void test_location_move_costs_use_pad_tuple_and_runtime_multiplier(void)
{
    static const uint16_t hall_item_ids[GAME_START_PLAYER_COUNT] = {
        0x2a, 0x3a, 0x4a, 0x5a
    };
    GameSession session = {0};
    PadCatalog catalog = {0};
    unsigned int player;

    session.island_count = 1;
    session.islands[0].location_count = GAME_START_PLAYER_COUNT;
    catalog.item_count = 0x5b;
    for (player = 0; player < GAME_START_PLAYER_COUNT; ++player) {
        GameRuntimeLocation *hall = &session.islands[0].locations[player];
        PadCatalogItem *item = &catalog.items[hall_item_ids[player]];
        int32_t costs[GAME_RESOURCE_TYPE_COUNT] = {-1, -1, -1};

        hall->record_value_10 = hall_item_ids[player];
        hall->source_capacity_4a = (int16_t)player;
        item->item_id = hall_item_ids[player];
        item->movement_cost[0] = 15;
        item->movement_cost[1] = 0;
        item->movement_cost[2] = 15;
        assert(game_session_location_move_costs(&session, &catalog, 0,
                                                (uint16_t)player, costs));
        assert(costs[0] == (int32_t)(player + 1U) * 15);
        assert(costs[1] == 0);
        assert(costs[2] == (int32_t)(player + 1U) * 15);
    }

    {
        int32_t costs[GAME_RESOURCE_TYPE_COUNT] = {7, 8, 9};
        assert(!game_session_location_move_costs(&session, &catalog, 1, 0,
                                                 costs));
        assert(costs[0] == 7 && costs[1] == 8 && costs[2] == 9);
        session.islands[0].locations[0].record_value_10 = 0xffff;
        assert(!game_session_location_move_costs(&session, &catalog, 0, 0,
                                                 costs));
        assert(costs[0] == 7 && costs[1] == 8 && costs[2] == 9);
        assert(!game_session_location_move_costs(&session, &catalog, 0, 0,
                                                 NULL));
    }
}

static void test_pending_event_table_matches_source_slots_and_deduplication(void)
{
    GameSession session;
    int first;
    int second;
    int i;

    memset(&session, 0, sizeof(session));
    first = game_session_pending_event_add(&session, 2, 17, 4, 33, 45, 9);
    assert(first == 0);
    assert(session.pending_event_count == 1);
    assert(session.pending_events[first].active == 1);
    assert(session.pending_events[first].reserved_zero == 0);
    assert(session.pending_events[first].priority == 1);
    assert(session.pending_events[first].player_id == 2);
    assert(session.pending_events[first].payload_0a == 17);
    assert(session.pending_events[first].action_type == 4);
    assert(session.pending_events[first].payload_0c == 33);
    assert(session.pending_events[first].payload_0e == 45);
    assert(session.pending_events[first].payload_12 == 9);

    /* FUN_004662b7 only deduplicates action types 5 and 13. */
    second = game_session_pending_event_add(&session, 2, 17, 4, 33, 45, 9);
    assert(second == 1);
    assert(session.pending_event_count == 2);
    assert(game_session_pending_event_add(&session, 2, 17, 5, 33, 45, 9) == 2);
    assert(game_session_pending_event_add(&session, 3, 99, 5, 33, 45, 9) == -1);
    assert(session.pending_event_count == 3);
    assert(session.pending_events[3].active == 0);
    assert(session.pending_events[3].player_id == 3);
    assert(session.pending_events[3].payload_0a == 99);
    assert(game_session_pending_event_add(&session, 2, 17, 13, 33, 45, 9) == 3);
    assert(game_session_pending_event_add(&session, 2, 17, 13, 33, 45, 9) == -1);
    assert(session.pending_event_count == 4);

    assert(game_session_pending_event_release(&session, (uint8_t)second));
    assert(!game_session_pending_event_release(&session, (uint8_t)second));
    assert(session.pending_events[second].payload_12 == 9);
    assert(!game_session_pending_event_release(&session,
                                               GAME_SESSION_MAX_PENDING_EVENTS));
    assert(session.pending_event_count == 3);
    assert(!game_session_pending_event_release(NULL, 0));

    memset(&session, 0, sizeof(session));
    for (i = 0; i < GAME_SESSION_MAX_PENDING_EVENTS; ++i) {
        assert(game_session_pending_event_add(&session, 0, (int16_t)i, 4,
                                              0, 0, (int16_t)i) == i);
    }
    assert(session.pending_event_count == GAME_SESSION_MAX_PENDING_EVENTS);
    assert(game_session_pending_event_add(&session, 0, 0, 4, 0, 0, 0) == -1);
    assert(game_session_pending_event_add(NULL, 0, 0, 4, 0, 0, 0) == -1);
}

static void test_task_projection_matches_source_filter_and_cap(void)
{
    GameSession session = {0};
    uint8_t slots[GAME_SESSION_MAX_TASKS];
    uint8_t short_output[4] = {0xff, 0xff, 0xff, 0xff};
    int index;

    assert(game_session_pending_event_add(&session, 2, 0, 4, 0, 1, 5) == 0);
    assert(game_session_pending_event_add(&session, 2, 0, 0xb, 0, 1, 5) == 1);
    assert(game_session_pending_event_add(&session, 3, 0, 4, 0, 1, 5) == 2);
    assert(game_session_pending_event_add(&session, 2, 0, 13, 0, 1, 5) == 3);
    for (index = 0; index < 36; ++index) {
        assert(game_session_pending_event_add(&session, 2, (int16_t)index,
            4, 0, 1, (int16_t)index) == index + 4);
    }

    assert(game_session_collect_task_slots(&session, 2, slots,
           GAME_SESSION_MAX_TASKS) == GAME_SESSION_MAX_TASKS);
    assert(slots[0] == 0 && slots[1] == 3);
    for (index = 0; index < 30; ++index)
        assert(slots[index + 2] == index + 4);
    assert(game_session_collect_task_slots(&session, 2, short_output, 3) ==
           GAME_SESSION_MAX_TASKS);
    assert(short_output[0] == 0 && short_output[1] == 3 &&
           short_output[2] == 4 && short_output[3] == 0xff);
    assert(game_session_collect_task_slots(&session, 2, NULL, 0) ==
           GAME_SESSION_MAX_TASKS);
    assert(game_session_collect_task_slots(&session, 3, slots,
           GAME_SESSION_MAX_TASKS) == 1);
    assert(slots[0] == 2);
    assert(game_session_collect_task_slots(NULL, 2, slots,
           GAME_SESSION_MAX_TASKS) == 0);
}

static void test_task_command_dispatch_guards_and_effects(void)
{
    GameSession session = {0};
    GamePendingEvent expected;
    int slot = game_session_pending_event_add(&session, 2, 17, 4,
                                               33, 45, 9);
    assert(slot == 0);
    expected = session.pending_events[slot];

    assert(game_session_dispatch_task_command(&session, (uint8_t)slot,
                                               13, &expected));
    assert(session.pending_events[slot].priority == 1);
    assert(game_session_dispatch_task_command(&session, (uint8_t)slot,
                                               14, &expected));
    assert(session.pending_events[slot].priority == 2);
    assert(game_session_dispatch_task_command(&session, (uint8_t)slot,
                                               15, &expected));
    assert(session.pending_events[slot].priority == 3);
    assert(session.pending_event_count == 1);

    /* FUN_00465793 compares the command identity before touching a reused slot. */
    session.pending_events[slot].payload_0a++;
    assert(!game_session_dispatch_task_command(&session, (uint8_t)slot,
                                                12, &expected));
    assert(session.pending_events[slot].active == 1);
    assert(session.pending_event_count == 1);
    session.pending_events[slot].payload_0a = expected.payload_0a;
    session.pending_events[slot].player_id++;
    assert(!game_session_dispatch_task_command(&session, (uint8_t)slot,
                                                13, &expected));
    session.pending_events[slot].player_id = expected.player_id;
    expected.action_type++;
    assert(!game_session_dispatch_task_command(&session, (uint8_t)slot,
                                                13, &expected));
    expected.action_type = session.pending_events[slot].action_type;
    expected.payload_12++;
    assert(!game_session_dispatch_task_command(&session, (uint8_t)slot,
                                                13, &expected));
    expected = session.pending_events[slot];

    assert(!game_session_dispatch_task_command(&session,
        GAME_SESSION_MAX_PENDING_EVENTS, 13, &expected));
    assert(!game_session_dispatch_task_command(&session, (uint8_t)slot,
                                               11, &expected));
    assert(!game_session_dispatch_task_command(NULL, (uint8_t)slot,
                                               13, &expected));
    assert(!game_session_dispatch_task_command(&session, (uint8_t)slot,
                                               13, NULL));

    assert(game_session_dispatch_task_command(&session, (uint8_t)slot,
                                               12, &expected));
    assert(session.pending_events[slot].active == 0);
    assert(session.pending_events[slot].priority == 3);
    assert(session.pending_event_count == 0);
    assert(!game_session_dispatch_task_command(&session, (uint8_t)slot,
                                                12, &expected));

    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    session.islands[0].location_count = 2;
    session.islands[0].locations[1].record_value_10 = 1;
    session.islands[0].locations[1].owner_id = 2;
    slot = game_session_pending_event_add(&session, 2, 0, 5,
                                           0, 1, 44);
    assert(slot == 0);
    expected = session.pending_events[slot];
    assert(game_session_dispatch_task_command(&session, (uint8_t)slot,
                                               12, &expected));
    assert(session.islands[0].locations[1].owner_id == -1);
    assert(session.pending_event_count == 0);

    /* FUN_00466533 clears the site owner only for status 0 or 1. */
    session.islands[0].locations[0].record_value_10 = 2;
    session.islands[0].locations[0].owner_id = 3;
    slot = game_session_pending_event_add(&session, 2, 0, 5,
                                           0, 0, 45);
    assert(slot == 0);
    expected = session.pending_events[slot];
    assert(game_session_dispatch_task_command(&session, (uint8_t)slot,
                                               12, &expected));
    assert(session.islands[0].locations[0].owner_id == 3);
    assert(session.pending_event_count == 0);

    session.islands[0].locations[0].record_value_10 = 0;
    session.islands[0].locations[0].owner_id = 1;
    slot = game_session_pending_event_add(&session, 2, 0, 5,
                                           0, 0, 46);
    assert(slot == 0);
    expected = session.pending_events[slot];
    assert(game_session_dispatch_task_command(&session, (uint8_t)slot,
                                               12, &expected));
    assert(session.islands[0].locations[0].owner_id == -1);
    assert(session.pending_event_count == 0);
}

static void test_inventory_action_reserves_source_payload_without_mutation(void)
{
    GameSession session = {0};
    GameRuntimeIsland *island;
    GameRuntimeLocation *location;
    int slot;

    session.island_count = 1;
    island = &session.islands[0];
    island->location_count = 3;
    location = &island->locations[0];
    location->renderer_class = 0;
    location->owner_id = -1;
    location->record_value_10 = 0;
    session.economy[1].inventory_count[0] = 2;

    /* FUN_0042fa0f(0x40): empty class-0 location queues type 4. It does not
       mutate the location or debit inventory in this click handler. */
    slot = game_session_queue_inventory_action(&session, 1, 0, 0, 5);
    assert(slot == 0);
    assert(session.pending_event_count == 1);
    assert(session.pending_events[slot].player_id == 1);
    assert(session.pending_events[slot].payload_0a == 0);
    assert(session.pending_events[slot].action_type == 4);
    assert(session.pending_events[slot].payload_0c == 0);
    assert(session.pending_events[slot].payload_0e == 0);
    assert(session.pending_events[slot].payload_12 == 5);
    assert(session.economy[1].inventory_count[0] == 2);
    assert(location->record_value_10 == 0 && location->owner_id == -1);

    /* Both source rejection alternatives must be retained. */
    location = &island->locations[1];
    location->renderer_class = 0;
    location->record_value_10 = 7;
    location->owner_id = -1;
    assert(game_session_queue_inventory_action(&session, 1, 0, 1, 5) == -1);
    location->record_value_10 = 0;
    location->owner_id = 0;
    assert(game_session_queue_inventory_action(&session, 1, 0, 1, 5) == -1);
    assert(session.pending_event_count == 1);

    /* The source condition is specific to renderer class 0. */
    location = &island->locations[2];
    location->renderer_class = 1;
    location->record_value_10 = 9;
    location->owner_id = 0;
    assert(game_session_queue_inventory_action(&session, 1, 0, 2, 33) == 1);
    assert(session.pending_events[1].payload_0e == 2);
    assert(session.pending_events[1].payload_12 == 33);

    assert(game_session_queue_inventory_action(NULL, 1, 0, 0, 5) == -1);
    assert(game_session_queue_inventory_action(&session, GAME_START_PLAYER_COUNT,
                                               0, 0, 5) == -1);
    assert(game_session_queue_inventory_action(&session, 1, 1, 0, 5) == -1);
    assert(game_session_queue_inventory_action(&session, 1, 0, 3, 5) == -1);
    assert(game_session_queue_inventory_action(&session, 1, 0, 0, 4) == -1);
    assert(game_session_queue_inventory_action(&session, 1, 0, 0, 34) == -1);
    assert(session.pending_event_count == 2);
}

static void test_source_event3_subtype0_queues_and_toggles_only_player_bit(void)
{
    GameSession session = {0};
    session.island_count = 2;
    session.islands[1].source_event_state[2] = 0xa4U;

    assert(game_session_queue_island_event3_subtype0(&session, 2, 1));
    assert(session.islands[1].source_event_state[2] == 0xa4U);
    assert(session.islands[1].source_event3_pending_parity[2] == 1);
    assert(session.islands[1].source_event3_pending_parity[0] == 0);
    assert(session.islands[0].source_event3_pending_parity[2] == 0);
    game_session_dispatch_island_events(&session);
    assert(session.islands[1].source_event_state[2] == 0xa5U);
    assert(session.islands[1].source_event_state[0] == 0);
    assert(session.islands[0].source_event_state[2] == 0);
    assert(session.islands[1].source_event3_pending_parity[2] == 0);

    assert(game_session_queue_island_event3_subtype0(&session, 2, 1));
    game_session_dispatch_island_events(&session);
    assert(session.islands[1].source_event_state[2] == 0xa4U);

    assert(game_session_queue_island_event3_subtype0(&session, 2, 1));
    assert(game_session_queue_island_event3_subtype0(&session, 2, 1));
    assert(session.islands[1].source_event3_pending_parity[2] == 0);
    game_session_dispatch_island_events(&session);
    assert(session.islands[1].source_event_state[2] == 0xa4U);

    assert(!game_session_queue_island_event3_subtype0(NULL, 0, 0));
    assert(!game_session_queue_island_event3_subtype0(&session,
        GAME_START_PLAYER_COUNT, 0));
    assert(!game_session_queue_island_event3_subtype0(&session, 0, 2));
    game_session_dispatch_island_events(NULL);
}

static void test_glyph_map_click_queues_packet_without_world_effect(void)
{
    GameSession session = {0};
    GameGlyphActionRequest request;
    unsigned int index;

    session.island_count = 1;
    session.islands[0].location_count = 2;
    session.economy[1].glyph_mask = (uint16_t)((1U << 2) | (1U << 9));

    /* FUN_0042fa0f case 0x40 emits category 3/type 3 with these payload
       fields. The downstream record filter (+0 == player, +4 == 8) remains
       outside this test; queueing does not mutate island state. */
    assert(game_session_queue_glyph_action(&session, 1, 0, 1, 9));
    assert(session.glyph_action_count == 1);
    assert(session.glyph_actions[0].player_slot == 1);
    assert(session.glyph_actions[0].island_index == 0);
    assert(session.glyph_actions[0].location_index == 1);
    assert(session.glyph_actions[0].glyph_index == 9);
    assert(session.economy[1].glyph_mask == ((1U << 2) | (1U << 9)));
    assert(session.islands[0].source_event_state[1] == 0);
    assert(game_session_pop_glyph_action(&session, &request));
    assert(request.player_slot == 1 && request.island_index == 0 &&
           request.location_index == 1 && request.glyph_index == 9);
    assert(!game_session_pop_glyph_action(&session, &request));

    assert(game_session_queue_glyph_action(NULL, 1, 0, 0, 2) == -1);
    assert(game_session_queue_glyph_action(&session, GAME_START_PLAYER_COUNT,
                                            0, 0, 2) == -1);
    assert(game_session_queue_glyph_action(&session, 1, 1, 0, 2) == -1);
    assert(game_session_queue_glyph_action(&session, 1, 0, 2, 2) == -1);
    assert(game_session_queue_glyph_action(&session, 1, 0, 0,
                                            GAME_GLYPH_COUNT) == -1);
    assert(game_session_queue_glyph_action(&session, 1, 0, 0, 3) == -1);

    for (index = 0; index < GAME_SESSION_MAX_GLYPH_ACTIONS; ++index) {
        assert(game_session_queue_glyph_action(&session, 1, 0, 0, 2));
    }
    assert(session.glyph_action_count == GAME_SESSION_MAX_GLYPH_ACTIONS);
    assert(game_session_queue_glyph_action(&session, 1, 0, 0, 2) == -1);
}

static void test_glyph_ownership_mask_is_player_local_and_idempotent(void)
{
    GameSession session = {0};
    assert(session.economy[0].glyph_mask == 0);
    assert(game_session_acquire_glyph(&session, 0, 0));
    assert(game_session_acquire_glyph(&session, 0, 13));
    assert(game_session_acquire_glyph(&session, 0, 13));
    assert(session.economy[0].glyph_mask == 0x2001U);
    assert(session.economy[1].glyph_mask == 0);
    assert(!game_session_acquire_glyph(&session, 0, 14));
    assert(!game_session_acquire_glyph(&session, GAME_START_PLAYER_COUNT, 0));
    assert(!game_session_acquire_glyph(NULL, 0, 0));
}

static void test_onoff_action_queues_target_without_changing_location_flags(void)
{
    GameSession session = {0};
    GameOnOffActionRequest request;
    unsigned int index;

    session.island_count = 1;
    session.islands[0].location_count = 2;
    session.islands[0].locations[1].source_flags = 0x410;
    /* FUN_0042fa0f's BC_OnOff message route reaches the type-1/subtype-0
       receiver. Capture the target, but do not guess the unknown flow gate. */
    assert(game_session_queue_onoff_action(&session, 2, 0, 1));
    assert(session.onoff_action_count == 1);
    assert(session.onoff_actions[0].player_slot == 2);
    assert(session.onoff_actions[0].island_index == 0);
    assert(session.onoff_actions[0].location_index == 1);
    assert(session.islands[0].locations[1].source_flags == 0x410);
    assert(game_session_pop_onoff_action(&session, &request));
    assert(request.player_slot == 2 && request.island_index == 0 &&
           request.location_index == 1);
    assert(!game_session_pop_onoff_action(&session, &request));

    assert(!game_session_queue_onoff_action(NULL, 0, 0, 0));
    assert(!game_session_queue_onoff_action(&session,
        GAME_START_PLAYER_COUNT, 0, 0));
    assert(!game_session_queue_onoff_action(&session, 0, 1, 0));
    assert(!game_session_queue_onoff_action(&session, 0, 0, 2));
    for (index = 0; index < GAME_SESSION_MAX_ONOFF_ACTIONS; ++index) {
        assert(game_session_queue_onoff_action(&session, 0, 0, 0));
    }
    assert(session.onoff_action_count == GAME_SESSION_MAX_ONOFF_ACTIONS);
    assert(!game_session_queue_onoff_action(&session, 0, 0, 0));
}

static void test_build_selection_queues_source_packet_without_placing_item(void)
{
    GameSession session = {0};
    GameBuildSelectionRequest request;
    GameRuntimeLocation *site;
    uint8_t task_slots[GAME_SESSION_MAX_TASKS];
    unsigned int index;

    session.island_count = 1;
    session.islands[0].location_count = 2;
    site = &session.islands[0].locations[1];
    site->record_value_10 = 0;
    site->owner_id = -1;

    /* FUN_0042fa0f(0x34) queues category 0/type 5 for the already-selected
       location. The local tick allocates a task slot, but its placement
       consumer remains unresolved and must not be replaced with local pose. */
    assert(game_session_queue_build_selection(&session, 2, 0, 1, 44));
    assert(session.build_selection_count == 1);
    assert(session.build_selections[0].category == 0);
    assert(session.build_selections[0].player_slot == 2);
    assert(session.build_selections[0].action_type == 5);
    assert(session.build_selections[0].island_index_a == 0);
    assert(session.build_selections[0].reserved_zero == 0);
    assert(session.build_selections[0].island_index_b == 0);
    assert(session.build_selections[0].location_index == 1);
    assert(session.build_selections[0].item_id == 44);
    assert(site->record_value_10 == 0 && site->owner_id == -1);
    assert(game_session_dispatch_build_selections(&session) == 1);
    assert(session.build_selection_count == 0);
    assert(session.pending_event_count == 1);
    assert(session.pending_events[0].active == 1);
    assert(session.pending_events[0].player_id == 2);
    assert(session.pending_events[0].priority == 1);
    assert(session.pending_events[0].payload_0a == 0);
    assert(session.pending_events[0].payload_0c == 0);
    assert(session.pending_events[0].payload_0e == 1);
    assert(session.pending_events[0].action_type == 5);
    assert(session.pending_events[0].payload_12 == 44);
    assert(game_session_collect_task_slots(&session, 2, task_slots,
                                           GAME_SESSION_MAX_TASKS) == 1);
    assert(task_slots[0] == 0);
    assert(site->record_value_10 == 0 && site->owner_id == -1);

    /* Source duplicate matching ignores player and island fields, and keys
       the type-5 slot by payload_0c, payload_0e, and payload_12. */
    assert(game_session_queue_build_selection(&session, 3, 0, 1, 44));
    assert(game_session_dispatch_build_selections(&session) == 0);
    assert(session.build_selection_count == 0);
    assert(session.pending_event_count == 1);
    assert(session.pending_events[1].active == 0);

    assert(game_session_queue_build_selection(&session, 2, 0, 1, 45));
    assert(game_session_pop_build_selection(&session, &request));
    assert(request.category == 0 && request.player_slot == 2 &&
           request.action_type == 5 && request.island_index_a == 0 &&
           request.reserved_zero == 0 && request.island_index_b == 0 &&
           request.location_index == 1 && request.item_id == 45);
    assert(!game_session_pop_build_selection(&session, &request));

    assert(!game_session_queue_build_selection(NULL, 0, 0, 0, 44));
    assert(!game_session_queue_build_selection(&session,
        GAME_START_PLAYER_COUNT, 0, 0, 44));
    assert(!game_session_queue_build_selection(&session, 0, 1, 0, 44));
    assert(!game_session_queue_build_selection(&session, 0, 0, 2, 44));

    for (index = 0; index < GAME_SESSION_MAX_BUILD_SELECTIONS; ++index) {
        assert(game_session_queue_build_selection(&session, 0, 0, 0, 44));
    }
    assert(session.build_selection_count == GAME_SESSION_MAX_BUILD_SELECTIONS);
    assert(!game_session_queue_build_selection(&session, 0, 0, 0, 44));
    assert(game_session_dispatch_build_selections(NULL) == 0);
}

static void test_construct_click_item_becomes_queued_build_packet(void)
{
    const WindowPane pane = {192, 368, 447, 471};
    const int32_t item_ids[] = {71};
    GameSession session = {0};
    IwConstructState state;
    IwConstructTransition transition;

    session.island_count = 1;
    session.islands[0].location_count = 1;
    session.islands[0].locations[0].owner_id = -1;
    iw_construct_init(&state, 1);
    iw_construct_mouse_move(&state, &pane, 192, 394, item_ids, 1, &transition);
    assert(transition.changed && transition.message_count == 1);
    assert(transition.messages[0].code == IW_CONSTRUCT_MSG_SELECT_HOVER);
    assert(transition.messages[0].value == 71);

    iw_construct_mouse_click(&state, 2, &transition);
    assert(transition.message_count == 2);
    assert(transition.messages[0].code == IW_CONSTRUCT_MSG_SELECT_BUILD);
    assert(transition.messages[0].value == 39);
    assert(transition.messages[1].code == IW_CONSTRUCT_MSG_CLEAR_BUILD);
    assert(game_session_queue_build_selection(
        &session, 2, 0, 0, (uint16_t)transition.messages[0].value));
    assert(session.build_selection_count == 1);
    assert(game_session_dispatch_build_selections(&session) == 1);
    assert(session.build_selection_count == 0);
    assert(session.pending_event_count == 1);
    assert(session.pending_events[0].player_id == 2);
    assert(session.pending_events[0].action_type == 5);
    assert(session.pending_events[0].payload_0a == 0);
    assert(session.pending_events[0].payload_0c == 0);
    assert(session.pending_events[0].payload_0e == 0);
    assert(session.pending_events[0].payload_12 == 39);
    assert(session.islands[0].locations[0].record_value_10 == 0);
    assert(session.islands[0].locations[0].owner_id == -1);
}

static void test_item_animation_uses_source_flags_and_per_object_counters(void)
{
    GameSession session;
    BuildingRenderCatalog catalog;
    BuildingRenderItem *item;
    GameRuntimeLocation *location;
    unsigned int tick;

    memset(&session, 0, sizeof(session));
    memset(&catalog, 0, sizeof(catalog));
    session.island_count = 1;
    session.islands[0].location_count = 1;
    location = &session.islands[0].locations[0];
    location->record_value_10 = 42;
    location->owner_id = 0;
    location->renderer_class = 0;
    location->source_flags = 0x410;
    location->animation_rate = 1;

    catalog.item_count = 43;
    item = &catalog.items[42];
    item->item_id = 42;
    item->present = 1;
    item->chug.present = 1;
    item->chug.first_frame = 1;
    item->chug.last_frame = 3;
    item->chug.ticks_per_frame = 2;
    item->glyph.present = 1;
    item->glyph.first_frame = 1;
    item->glyph.last_frame = 3;

    /* FUN_004528ca starts with bit 0 clear, so the source tick does not yet
       advance construction CHUG or initialize the idle GLYP counter. */
    game_session_tick_item_animations(&session, &catalog);
    assert(location->chug_progress == 0 && location->glyph_progress == 0);

    location->source_flags |= 1U;
    game_session_tick_item_animations(&session, &catalog);
    assert(location->chug_progress == 1 && location->glyph_progress == 1);
    for (tick = 0; tick < 5; ++tick) {
        game_session_tick_item_animations(&session, &catalog);
    }
    assert(location->chug_progress == 0); /* 3-frame loop at two ticks/frame */
    for (tick = 0; tick < 34; ++tick) {
        game_session_tick_item_animations(&session, &catalog);
    }
    assert(location->glyph_progress == 0); /* source GLYP phase wraps at 40 */
    location->chug_progress = 0;
    location->animation_rate = 2;
    game_session_tick_item_animations(&session, &catalog);
    assert(location->chug_progress == 2); /* source adds CHUG speed at rate >= 2 */
}

static void test_tone_pool_uses_two_source_counter_sequences(void)
{
    GameSession session;
    BuildingRenderCatalog catalog;
    GameRuntimeLocation *idle_pool;
    GameRuntimeLocation *alternate_pool;
    unsigned int tick;

    memset(&session, 0, sizeof(session));
    memset(&catalog, 0, sizeof(catalog));
    session.island_count = 1;
    session.islands[0].location_count = 2;
    idle_pool = &session.islands[0].locations[0];
    alternate_pool = &session.islands[0].locations[1];
    idle_pool->renderer_class = 1;
    idle_pool->record_value_10 = ISLAND_TONE_POOL_ITEM_DEFAULT;
    alternate_pool->renderer_class = 1;
    alternate_pool->record_value_10 = ISLAND_TONE_POOL_ITEM_ALTERNATE;

    for (tick = 0; tick < 89; ++tick) game_session_tick_item_animations(&session, &catalog);
    assert(idle_pool->chug_progress == 89);
    assert(alternate_pool->chug_progress == 89);
    assert(island_tone_pool_frame(idle_pool->record_value_10,
                                  idle_pool->chug_progress) == 30);
    assert(island_tone_pool_frame(alternate_pool->record_value_10,
                                  alternate_pool->chug_progress) == 30);

    game_session_tick_item_animations(&session, &catalog);
    assert(idle_pool->chug_progress == 0); /* class-1 ID 0 wraps at tick 90 */
    assert(alternate_pool->chug_progress == 90);
    assert(island_tone_pool_frame(idle_pool->record_value_10,
                                  idle_pool->chug_progress) == 1);
    assert(island_tone_pool_frame(alternate_pool->record_value_10,
                                  alternate_pool->chug_progress) == 31);

    for (tick = 90; tick < 126; ++tick) game_session_tick_item_animations(&session, &catalog);
    assert(alternate_pool->chug_progress == 102); /* ID 5 jumps from 126 back to 102 */
    assert(island_tone_pool_frame(alternate_pool->record_value_10,
                                  alternate_pool->chug_progress) == 35);
    for (tick = 0; tick < 12; ++tick) game_session_tick_item_animations(&session, &catalog);
    assert(alternate_pool->chug_progress == 114);
    assert(island_tone_pool_frame(alternate_pool->record_value_10,
                                  alternate_pool->chug_progress) == 39);
}

static void test_active_cons_and_prod_counters_finish_at_source_limits(void)
{
    GameSession session;
    BuildingRenderCatalog catalog;
    GameRuntimeLocation *location;
    BuildingRenderItem *item;
    unsigned int tick;

    memset(&session, 0, sizeof(session));
    memset(&catalog, 0, sizeof(catalog));
    session.island_count = 1;
    session.islands[0].location_count = 1;
    location = &session.islands[0].locations[0];
    location->record_value_10 = 42;
    location->renderer_class = 0;
    location->source_flags = 0x006U;
    catalog.item_count = 43;
    item = &catalog.items[42];
    item->item_id = 42;
    item->present = 1;
    item->cons.present = 1;
    item->cons.fallback_frame = 3; /* bldinf CONS parameter, source +0x0a */
    item->prod.present = 1;
    item->prod.threshold = 2;      /* bldinf PROD parameter, source +0x0c */

    game_session_tick_item_animations(&session, &catalog);
    assert(location->construction_progress == 1);
    assert(location->production_progress == 1);
    assert(location->source_flags == 0x006U);
    game_session_tick_item_animations(&session, &catalog);
    assert(location->construction_progress == 2);
    assert(location->production_progress == 2);
    assert((location->source_flags & 0x002U) == 0);
    assert((location->source_flags & 0x004U) != 0);
    game_session_tick_item_animations(&session, &catalog);
    assert(location->construction_progress == 3);
    assert((location->source_flags & 0x004U) == 0);

    /* With no PROD descriptor the original tick uses a 0x28 fallback. */
    location->source_flags = 0x002U;
    location->production_progress = 0;
    item->prod.present = 0;
    for (tick = 0; tick < 0x27U; ++tick) {
        game_session_tick_item_animations(&session, &catalog);
    }
    assert(location->production_progress == 0x27U);
    assert((location->source_flags & 0x002U) != 0);
    game_session_tick_item_animations(&session, &catalog);
    assert(location->production_progress == 0x28U);
    assert((location->source_flags & 0x002U) == 0);
}

static void test_producer_cadence_starts_prod_and_waits_for_output_consumption(void)
{
    GameSession session;
    BuildingRenderCatalog catalog;
    GameRuntimeLocation *location;
    BuildingRenderItem *item;
    unsigned int tick;

    memset(&session, 0, sizeof(session));
    memset(&catalog, 0, sizeof(catalog));
    session.island_count = 1;
    session.islands[0].location_count = 1;
    location = &session.islands[0].locations[0];
    location->record_value_10 = 0x25;
    location->owner_id = 0;
    location->renderer_class = 0;
    location->source_flags = 0x411U;
    location->animation_rate = 1;
    catalog.item_count = 0x28;
    item = &catalog.items[0x25];
    item->item_id = 0x25;
    item->present = 1;
    item->prod.present = 1;
    item->prod.threshold = 2;

    location->source_flags = 0x410U;
    game_session_tick_item_animations(&session, &catalog);
    assert(location->producer_cadence == 0);
    assert((location->source_flags & 0x002U) == 0);
    location->source_flags = 0x411U;
    for (tick = 0; tick < 19; ++tick) {
        game_session_tick_item_animations(&session, &catalog);
    }
    assert(location->producer_cadence == 19);
    assert((location->source_flags & 0x002U) == 0);
    game_session_tick_item_animations(&session, &catalog);
    assert(location->producer_cadence == 0);
    assert((location->source_flags & 0x002U) != 0);
    assert(location->production_progress == 0);

    game_session_tick_item_animations(&session, &catalog);
    assert(location->production_progress == 1);
    assert(location->record_value_24 == 0);
    game_session_tick_item_animations(&session, &catalog);
    assert((location->source_flags & 0x002U) == 0);
    assert(location->record_value_24 == 1);
    for (tick = 0; tick < 25; ++tick) {
        game_session_tick_item_animations(&session, &catalog);
    }
    assert(location->record_value_24 == 1);
    assert(location->producer_cadence == 0);
    assert((location->source_flags & 0x002U) == 0);

    location->record_value_24 = 0;
    location->animation_rate = 2;
    for (tick = 0; tick < 10; ++tick) {
        game_session_tick_item_animations(&session, &catalog);
    }
    assert(location->producer_cadence == 0);
    assert((location->source_flags & 0x002U) != 0);

    location->source_flags = 0x411U;
    location->record_value_10 = 0x26;
    location->animation_rate = 1;
    location->record_value_24 = 0;
    location->production_progress = 0;
    item = &catalog.items[0x26];
    item->item_id = 0x26;
    item->present = 1;
    item->prod.present = 1;
    item->prod.threshold = 1;
    for (tick = 0; tick < 20; ++tick) {
        game_session_tick_item_animations(&session, &catalog);
    }
    game_session_tick_item_animations(&session, &catalog);
    assert(location->record_value_24 == 3);

    location->source_flags = 0x411U;
    location->record_value_10 = 0x27;
    location->record_value_24 = 0;
    location->production_progress = 0;
    item = &catalog.items[0x27];
    item->item_id = 0x27;
    item->present = 1;
    item->prod.present = 1;
    item->prod.threshold = 1;
    for (tick = 0; tick < 20; ++tick) {
        game_session_tick_item_animations(&session, &catalog);
    }
    game_session_tick_item_animations(&session, &catalog);
    assert(location->record_value_24 == 2);
}

static void test_initialization_is_transactional_on_bad_world(void)
{
    WorldDefinition world;
    IslandData islands[5];
    GameSessionConfig config;
    GameSession session;
    GameSession before;
    PadCatalog catalog;
    FloaterCatalog floater_catalog;
    char error[160];

    make_world(&world, islands);
    make_pad_catalog(&catalog);
    make_floater_catalog(&floater_catalog);
    world.island_count = 3;
    memset(&config, 0, sizeof(config));
    config.home_island_index = 0;
    memset(&session, 0xa5, sizeof(session));
    before = session;
    assert(!game_session_initialize(&world, islands, &catalog, &floater_catalog,
                                    &config, &session,
                                    error, sizeof(error)));
    assert(strstr(error, "cannot support the four start slots") != NULL);
    assert(memcmp(&session, &before, sizeof(session)) == 0);
}

static void test_building_placement_matches_source_runtime_initialization(void)
{
    GameSession session;
    PadCatalog catalog;
    IslandLocation site;
    GameRuntimeLocation *runtime;
    char error[128];

    memset(&session, 0, sizeof(session));
    memset(&catalog, 0, sizeof(catalog));
    memset(&site, 0, sizeof(site));
    session.island_count = 1;
    session.islands[0].location_count = 1;
    runtime = &session.islands[0].locations[0];
    runtime->renderer_class = 0;
    runtime->record_value_10 = 0;
    runtime->owner_id = -1;
    runtime->source_location_slot_18 = -1;
    runtime->source_flags = 0x7ff;
    runtime->source_capacity_4a = 3;
    runtime->base_progress = 3;
    runtime->chug_progress = 4;
    runtime->glyph_progress = 5;
    runtime->inci_progress = 6;
    runtime->construction_progress = 7;
    runtime->production_progress = 8;
    runtime->animation_rate = 9;
    runtime->barg_progress = 0.75;
    catalog.item_count = PAD_CATALOG_MAX_ITEMS;
    catalog.items[72].item_id = 72; /* base item 40 + player slot 2 * 16 */
    catalog.items[72].size = 0;
    catalog.items[72].building_tone_cost = 10;
    catalog.items[72].movement_cost[0] = 25;
    catalog.items[72].hit_points = 17;
    site.kind = ISLAND_LOCATION_PAD_SMALL;
    site.renderer_subtype = 0;

    assert(game_session_place_building(&session, &catalog, 2, 0, 0,
                                       &site, 40, error, sizeof(error)));
    assert(runtime->record_value_10 == 72);
    assert(runtime->owner_id == 2);
    assert(runtime->source_location_slot_18 == -1);
    assert(runtime->source_value_34 == 17);
    assert(runtime->source_capacity_4a == 0);
    assert(runtime->source_flags == 0x410);
    assert(runtime->record_value_24 == 0);
    assert(runtime->base_progress == 0 && runtime->producer_cadence == 0);
    assert(runtime->chug_progress == 0);
    assert(runtime->glyph_progress == 0 && runtime->inci_progress == 0);
    assert(runtime->construction_progress == 0 && runtime->production_progress == 0);
    assert(runtime->animation_rate == 1 && runtime->barg_progress == 0.0);

    runtime->record_value_10 = 0;
    runtime->owner_id = -1;
    catalog.items[72].size = 1;
    assert(!game_session_place_building(&session, &catalog, 2, 0, 0,
                                        &site, 40, error, sizeof(error)));
    assert(runtime->record_value_10 == 0 && runtime->owner_id == -1);
    catalog.items[72].size = 0;
    runtime->owner_id = 1;
    assert(!game_session_place_building(&session, &catalog, 2, 0, 0,
                                        &site, 40, error, sizeof(error)));
    assert(runtime->record_value_10 == 0 && runtime->owner_id == 1);
    runtime->owner_id = -1;
    catalog.items[72].building_tone_cost = -1;
    assert(!game_session_place_building(&session, &catalog, 2, 0, 0,
                                        &site, 40, error, sizeof(error)));
    assert(runtime->record_value_10 == 0 && runtime->owner_id == -1);
}

static void test_floater_move_state_advances_only_simulation_assigned_destinations(void)
{
    GameSession session;
    GameFloaterStart *floater;
    GameFloaterStart *idle_floater;
    uint16_t idle_x;

    memset(&session, 0, sizeof(session));
    session.floater_count = 2;
    floater = &session.floaters[0];
    floater->island_index = 0;
    floater->x = 100;
    floater->y = 100;
    /* The original simulation assigns movement targets through its unit/task
       state machine. This fixture exercises only the movement kernel; it does
       not model a player-issued order. */
    floater->destination_x = 120;
    floater->destination_y = 80;
    floater->movement_speed = 3;
    floater->has_move_order = 1;
    idle_floater = &session.floaters[1];
    idle_floater->island_index = 1;
    idle_floater->x = 200;
    idle_floater->y = 200;
    idle_x = idle_floater->x;

    game_session_tick_floater_moves(&session, 1);
    assert(floater->x == 103 && floater->y == 97);
    assert(!floater->facing_left);
    assert(idle_floater->x == idle_x && !idle_floater->has_move_order);

    floater->destination_x = 100;
    floater->destination_y = 96;
    floater->movement_speed = 3;
    floater->stop_radius = 10;
    floater->has_move_order = 1;
    game_session_tick_floater_moves(&session, 2);
    assert(floater->x == 103 && floater->y == 97);
    assert(!floater->has_move_order); /* destination is within the stop radius */
    assert(floater->facing_left); /* facing follows target even when stationary */

    floater->destination_x = 100;
    floater->destination_y = 97;
    floater->stop_radius = 0;
    floater->has_move_order = 1;
    game_session_tick_floater_moves(&session, 3);
    assert(floater->facing_left);
    game_session_tick_floater_moves(&session, 4);
    game_session_tick_floater_moves(&session, 5);
    game_session_tick_floater_moves(&session, 6);
    game_session_tick_floater_moves(&session, 7);
    assert(floater->x == 100 && floater->y == 97);

}

static void test_floater_selection_uses_original_hit_radius_and_island(void)
{
    GameSession session;

    memset(&session, 0, sizeof(session));
    session.island_count = 2;
    session.floater_count = 3;
    session.floaters[0].island_index = 0;
    session.floaters[0].x = 100;
    session.floaters[0].y = 100;
    session.floaters[1].island_index = 0;
    session.floaters[1].x = 140;
    session.floaters[1].y = 100;
    session.floaters[2].island_index = 1;
    session.floaters[2].x = 100;
    session.floaters[2].y = 100;

    assert(game_session_floater_at(&session, 0, 119, 119) == 0);
    assert(game_session_floater_at(&session, 0, 120, 100) == -1);
    assert(game_session_floater_at(&session, 1, 100, 100) == 2);
    assert(game_session_floater_at(&session, 2, 100, 100) == -1);
    assert(game_session_floater_at(NULL, 0, 100, 100) == -1);
}

static void test_workstr_counts_subtype_zero_and_truncates_percentage(void)
{
    GameSession session;
    unsigned int count = 99;
    unsigned int total = 99;
    unsigned int percentage = 99;

    memset(&session, 0, sizeof(session));
    session.floater_count = 4;
    session.floaters[0].type_index = 1;
    session.floaters[0].source_subtype = 0;
    session.floaters[1].type_index = 1;
    session.floaters[1].source_subtype = 1;
    session.floaters[2].type_index = 1;
    session.floaters[2].source_subtype = 2;
    session.floaters[3].type_index = 2;
    session.floaters[3].source_subtype = 0;

    assert(game_session_workstr_summary(&session, 1,
        &count, &total, &percentage));
    assert(count == 1 && total == 3 && percentage == 33);
    assert(game_session_workstr_summary(&session, 3,
        &count, &total, &percentage));
    assert(count == 0 && total == 0 && percentage == 0);
    assert(!game_session_workstr_summary(NULL, 1,
        &count, &total, &percentage));
    assert(!game_session_workstr_summary(&session, GAME_START_PLAYER_COUNT,
        &count, &total, &percentage));
    assert(!game_session_workstr_summary(&session, 1,
        NULL, &total, &percentage));
}

static void test_location_panel_level_uses_original_low_nibble_plus_one(void)
{
    GameRuntimeLocation location;

    memset(&location, 0, sizeof(location));
    assert(game_session_location_display_level(&location) == 1);
    location.source_level_flags = 0xabceU;
    assert(game_session_location_display_level(&location) == 15);
    assert(game_session_location_display_level(NULL) == 0);
}

int main(void)
{
    test_session_initializes_player_starts_and_runtime_items();
    test_hall_resource_ledger_is_safe();
    test_hall_resource_modes_cycle_through_original_three_states();
    test_hall_stock_mode_creates_and_releases_linked_resource_tasks();
    test_inventory_counts_cover_source_item_id_range();
    test_inventory_result_debits_only_after_receiver_success();
    test_location_resource_consumption_matches_source_guards();
    test_location_move_costs_use_pad_tuple_and_runtime_multiplier();
    test_pending_event_table_matches_source_slots_and_deduplication();
    test_task_projection_matches_source_filter_and_cap();
    test_task_command_dispatch_guards_and_effects();
    test_inventory_action_reserves_source_payload_without_mutation();
    test_source_event3_subtype0_queues_and_toggles_only_player_bit();
    test_glyph_map_click_queues_packet_without_world_effect();
    test_glyph_ownership_mask_is_player_local_and_idempotent();
    test_onoff_action_queues_target_without_changing_location_flags();
    test_build_selection_queues_source_packet_without_placing_item();
    test_construct_click_item_becomes_queued_build_packet();
    test_item_animation_uses_source_flags_and_per_object_counters();
    test_tone_pool_uses_two_source_counter_sequences();
    test_active_cons_and_prod_counters_finish_at_source_limits();
    test_producer_cadence_starts_prod_and_waits_for_output_consumption();
    test_initialization_is_transactional_on_bad_world();
    test_building_placement_matches_source_runtime_initialization();
    test_floater_move_state_advances_only_simulation_assigned_destinations();
    test_floater_selection_uses_original_hit_radius_and_island();
    test_workstr_counts_subtype_zero_and_truncates_percentage();
    test_location_panel_level_uses_original_low_nibble_plus_one();
    (void)puts("game session unit tests passed");
    return 0;
}
