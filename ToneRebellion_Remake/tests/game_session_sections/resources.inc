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
