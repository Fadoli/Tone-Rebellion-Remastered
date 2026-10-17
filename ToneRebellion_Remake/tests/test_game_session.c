#include "game_session.h"
#include "building_render.h"
#include "island_render_rules.h"
#include "pad_catalog.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

_Static_assert(sizeof(GamePendingEvent) == 0x14,
               "pending event must match FUN_004662b7's 0x14-byte record");

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
    char error[160];
    unsigned int player;
    unsigned int island_index;

    make_world(&world, islands);
    memset(&config, 0, sizeof(config));
    config.world_index = 1;
    config.difficulty = 2;
    config.selected_tribe = 3;
    config.home_island_index = 0;
    config.random_seed = 1;
    if (!game_session_initialize(&world, islands, &config, &session,
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
        const GameRuntimeLocation *pad = &session.islands[start->island_index]
            .locations[start->nearest_site_location_index];
        const GameRuntimeLocation *marker = &session.islands[start->island_index]
            .locations[start->marker_location_index];
        const GameFloaterStart *floater = &session.floaters[player * GAME_START_FLOATERS_PER_PLAYER];
        assert((marker->tribe_visibility_mask & (uint8_t)(1U << player)) != 0);
        assert(pad->record_value_10 ==
               GAME_START_INITIAL_PAD_ITEM_ID + (int32_t)player * 16);
        assert(pad->owner_id == (int32_t)player);
        assert(pad->source_flags == 0x410);
        assert(pad->chug_progress == 0 && pad->glyph_progress == 0);
        assert(pad->animation_rate == 1);
        assert(floater->island_index == start->island_index);
        assert(floater->type_index == player);
        assert(floater->x == start->marker_x);
        assert(floater->y == start->marker_y);
        assert(floater->movement_speed == 3); /* four initial *work rows in floater.txt */
        {
            unsigned int unit;
            for (unit = 0; unit < start->floater_count; ++unit) {
                const GameFloaterStart *worker = &session.floaters[
                    player * GAME_START_FLOATERS_PER_PLAYER + unit];
                assert(worker->current_hit_points == 3);
                assert(worker->max_hit_points == 3);
                assert(worker->attack_strength == 0);
            }
        }
        assert(session.economy[player].hall_island_index == start->island_index);
        assert(session.economy[player].hall_location_index ==
               start->nearest_site_location_index);
        assert(session.islands[start->island_index]
                   .locations[start->nearest_site_location_index]
                   .resource_stock[GAME_RESOURCE_BUILD_TONE] == 0); /* model default; source start stock unresolved */
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
    assert(session.pending_events[first].reserved_one == 1);
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
       mutate the location or debit inventory before a later result event. */
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

static void test_initialization_is_transactional_on_bad_world(void)
{
    WorldDefinition world;
    IslandData islands[5];
    GameSessionConfig config;
    GameSession session;
    GameSession before;
    char error[160];

    make_world(&world, islands);
    world.island_count = 3;
    memset(&config, 0, sizeof(config));
    config.home_island_index = 0;
    memset(&session, 0xa5, sizeof(session));
    before = session;
    assert(!game_session_initialize(&world, islands, &config, &session,
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
    runtime->source_flags = 0x7ff;
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
    site.kind = ISLAND_LOCATION_PAD_SMALL;
    site.renderer_subtype = 0;

    assert(game_session_place_building(&session, &catalog, 2, 0, 0,
                                       &site, 40, error, sizeof(error)));
    assert(runtime->record_value_10 == 72);
    assert(runtime->owner_id == 2);
    assert(runtime->source_flags == 0x410);
    assert(runtime->record_value_24 == 0);
    assert(runtime->base_progress == 0 && runtime->chug_progress == 0);
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
    test_inventory_counts_cover_source_item_id_range();
    test_pending_event_table_matches_source_slots_and_deduplication();
    test_inventory_action_reserves_source_payload_without_mutation();
    test_source_event3_subtype0_queues_and_toggles_only_player_bit();
    test_glyph_ownership_mask_is_player_local_and_idempotent();
    test_item_animation_uses_source_flags_and_per_object_counters();
    test_tone_pool_uses_two_source_counter_sequences();
    test_active_cons_and_prod_counters_finish_at_source_limits();
    test_initialization_is_transactional_on_bad_world();
    test_building_placement_matches_source_runtime_initialization();
    test_floater_move_state_advances_only_simulation_assigned_destinations();
    test_floater_selection_uses_original_hit_radius_and_island();
    test_location_panel_level_uses_original_low_nibble_plus_one();
    (void)puts("game session unit tests passed");
    return 0;
}
