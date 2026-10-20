static void test_source_capacity_cycle_uses_base_item_id_for_each_player(void)
{
    GameSession session = {0};
    unsigned int player;

    session.island_count = 1;
    session.islands[0].location_count = GAME_START_PLAYER_COUNT;
    for (player = 0; player < GAME_START_PLAYER_COUNT; ++player) {
        GameRuntimeLocation *location = &session.islands[0].locations[player];
        location->renderer_class = 0;
        location->owner_id = (int32_t)player;
        location->record_value_10 = 0x2c + (int32_t)player * 16;
        location->source_capacity_4a = 0;
        location->source_flags = 0x410U;
        location->source_value_48 = 23;
    }

    for (player = 0; player < GAME_START_PLAYER_COUNT; ++player) {
        GameRuntimeLocation *location = &session.islands[0].locations[player];
        unsigned int tier;
        for (tier = 1; tier <= 3; ++tier) {
            assert(game_session_cycle_source_capacity(&session, 0,
                                                       (uint16_t)player));
            assert(location->source_capacity_4a == (int16_t)tier);
            assert((location->source_flags & 0x20U) != 0);
            assert(location->source_value_48 == 0);
        }

        /* Wrapping 3→0 is a decrease, so the native setter leaves both
           the upgrade transition bit and cached +0x48 untouched. */
        location->source_flags &= ~0x20U;
        location->source_value_48 = 23;
        assert(game_session_cycle_source_capacity(&session, 0,
                                                   (uint16_t)player));
        assert(location->source_capacity_4a == 0);
        assert((location->source_flags & 0x20U) == 0);
        assert(location->source_value_48 == 23);
    }
}

static void test_cast_action_accepts_owner_variant_ids(void)
{
    GameSession session = {0};
    unsigned int player;

    session.island_count = 1;
    session.islands[0].location_count = GAME_START_PLAYER_COUNT;
    for (player = 0; player < GAME_START_PLAYER_COUNT; ++player) {
        GameRuntimeLocation *location = &session.islands[0].locations[player];
        location->renderer_class = 0;
        location->owner_id = (int32_t)player;
        location->source_location_slot_18 = 0;
        location->record_value_10 = 0x2f + (int32_t)player * 16;
        assert(game_session_queue_cast_action(&session, (uint8_t)player,
            0, (uint16_t)player, 0x15));
    }
    assert(session.cast_action_count == GAME_START_PLAYER_COUNT);
}

static void test_cast_kind_one_applies_area_and_expires_site_state(void)
{
    GameSession session = {0};
    GameFloaterStart *caster;
    GameRuntimeLocation *inside;
    GameRuntimeLocation *boundary;
    GameRuntimeLocation *other_item;
    GameRuntimeLocation *building;
    unsigned int tick;

    session.island_count = 1;
    session.floater_count = 1;
    session.islands[0].location_count = 5;
    session.economy[1].hall_island_index = 0;
    session.economy[1].hall_location_index = 0;
    session.islands[0].locations[0].record_value_10 = 0x2a + 16;
    session.islands[0].locations[0].owner_id = 1;
    session.islands[0].locations[0].resource_stock[GAME_RESOURCE_MAGIC_TONE] = 16;
    session.islands[0].locations[0].resource_stock[GAME_RESOURCE_CRYSTAL_TONE] = 11;
    caster = &session.floaters[0];
    caster->is_active = 1;
    caster->owner_slot = 1;
    caster->island_index = 0;
    building = &session.islands[0].locations[4];
    building->record_value_10 = 0x2f + 16;
    building->owner_id = 1;
    building->source_value_14 = 1;
    building->source_location_slot_18 = 0;
    building->charge_floater_slots[0] = 0;
    assert(game_session_queue_cast_action(&session, 1, 0, 4, 0x16));
    assert(game_session_dispatch_cast_actions(&session) == 1);
    assert(caster->cast_spell_kind == 1);

    session.islands[0].locations[0].x = 100;
    session.islands[0].locations[0].y = 100;
    inside = &session.islands[0].locations[1];
    inside->record_value_10 = 10;
    inside->owner_id = 4;
    inside->source_value_14 = 4;
    inside->source_location_slot_18 = 0;
    inside->x = 274; /* distance 174: included in radius 175 */
    inside->y = 100;
    boundary = &session.islands[0].locations[2];
    boundary->record_value_10 = 21;
    boundary->owner_id = 4;
    boundary->source_value_14 = 4;
    boundary->source_location_slot_18 = 0;
    boundary->x = 275; /* strict boundary: excluded */
    boundary->y = 100;
    other_item = &session.islands[0].locations[3];
    other_item->record_value_10 = 22;
    other_item->owner_id = 4;
    other_item->source_value_14 = 4;
    other_item->source_location_slot_18 = 0;
    other_item->x = 101;
    other_item->y = 100;

    assert(game_session_resolve_cast_effect_step(&session, NULL, 0, 1, 0) == 1);
    assert((caster->source_runtime_flags & 0x200U) != 0);
    assert((inside->source_flags & 0x100U) != 0);
    assert(inside->source_value_44 == 0);
    assert((inside->source_flags & 1U) != 0);
    assert((boundary->source_flags & 0x100U) == 0);
    assert((other_item->source_flags & 0x100U) == 0);

    for (tick = 0; tick < 19; ++tick)
        game_session_tick_site_effect_timers(&session);
    assert(inside->source_value_44 == 19);
    assert((inside->source_flags & 1U) != 0);
    game_session_tick_site_effect_timers(&session);
    assert(inside->source_value_44 == 20);
    assert((inside->source_flags & 1U) == 0);

    for (tick = 0; tick < 980; ++tick)
        game_session_tick_site_effect_timers(&session);
    assert(inside->source_value_44 == 0);
    assert((inside->source_flags & 0x100U) == 0);
    assert((inside->source_flags & 1U) != 0);
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
    assert(session.pending_events[first].assigned_floater_count == 0);
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
    for (index = 0; index < 60; ++index) {
        assert(game_session_pending_event_add(&session, 2, (int16_t)index,
            4, 0, 1, (int16_t)index) == index + 4);
    }

    assert(game_session_collect_task_slots(&session, 2, slots,
           GAME_SESSION_MAX_TASKS) == 62);
    assert(slots[0] == 0 && slots[1] == 3);
    for (index = 0; index < 60; ++index)
        assert(slots[index + 2] == index + 4);
    assert(game_session_collect_task_slots(&session, 2, short_output, 3) ==
           62);
    assert(short_output[0] == 0 && short_output[1] == 3 &&
           short_output[2] == 4 && short_output[3] == 0xff);
    assert(game_session_collect_task_slots(&session, 2, NULL, 0) ==
           62);
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

static void test_repair_task_repeats_supply_and_heals_after_40_ticks(void)
{
    GameSession session = {0};
    PadCatalog catalog = {0};
    GameRuntimeLocation *target;
    GameRuntimeLocation *hall;
    GameFloaterStart *floater;
    unsigned int tick;
    unsigned int movement_tick;
    int slot;

    session.island_count = 1;
    session.floater_count = 1;
    session.islands[0].location_count = 2;
    hall = &session.islands[0].locations[0];
    hall->renderer_class = 0;
    hall->record_value_10 = 0x2a;
    hall->owner_id = 0;
    hall->resource_stock[GAME_RESOURCE_BUILD_TONE] = 1;
    hall->x = 80;
    hall->y = 120;
    target = &session.islands[0].locations[1];
    target->renderer_class = 0;
    target->record_value_10 = 0x25;
    target->owner_id = 0;
    target->source_value_34 = 1;
    target->source_capacity_4a = 0;
    target->x = 100;
    target->y = 120;
    target->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] = 2;

    catalog.item_count = 0x26;
    catalog.items[0x25].item_id = 0x25;
    catalog.items[0x25].hit_points = 3;

    floater = &session.floaters[0];
    floater->is_active = 1;
    floater->owner_slot = 0;
    floater->island_index = 0;
    floater->type_index = 0;
    floater->source_link_0c = -1;
    floater->linked_task_slot = -1;
    floater->carried_resource_code = 1;
    floater->movement_speed = 3;
    floater->x = target->x;
    floater->y = target->y;

    slot = game_session_pending_event_add(&session, 0, 0, 0x12, 0, 1, 0);
    assert(slot == 0);
    game_session_assign_local_resource_tasks(&session, &catalog);
    assert(floater->active_order_action == 0x12);
    assert(floater->linked_task_slot == slot);
    assert(floater->movement_state == 4);
    assert(session.pending_events[slot].assigned_floater_count == 1);

    game_session_tick_floater_moves(&session, 1, &catalog);
    assert(target->resource_stock[GAME_RESOURCE_BUILD_TONE] == 1);
    assert(floater->carried_resource_code == GAME_RESOURCE_NONE);
    assert(floater->movement_state == 0x12);

    for (tick = 2; tick < 41; ++tick) {
        game_session_tick_floater_moves(&session, tick, &catalog);
        assert(target->source_value_34 == 1);
        assert(session.pending_events[slot].active == 1);
    }
    game_session_tick_floater_moves(&session, tick, &catalog);

    assert(target->source_value_34 == 2);
    assert(target->resource_stock[GAME_RESOURCE_BUILD_TONE] == 0);
    assert(target->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] == 1);
    assert(session.pending_events[slot].active == 1);
    assert(floater->active_order_action == 0x12);
    assert(floater->linked_task_slot == slot);
    assert(floater->movement_state == 3);

    /* A partial repair keeps the same task and fetches another Build Tone. */
    for (movement_tick = tick + 1; movement_tick < tick + 100;
         ++movement_tick) {
        game_session_tick_floater_moves(&session, movement_tick, &catalog);
        if (floater->carried_resource_code == 1 &&
            floater->movement_state == 4) break;
    }
    assert(hall->resource_stock[GAME_RESOURCE_BUILD_TONE] == 0);
    assert(floater->carried_resource_code == 1);
    assert(floater->movement_state == 4);

    for (++movement_tick; movement_tick < tick + 200; ++movement_tick) {
        game_session_tick_floater_moves(&session, movement_tick, &catalog);
        if (floater->movement_state == 0x12 &&
            floater->carried_resource_code == GAME_RESOURCE_NONE) break;
    }
    assert(target->resource_stock[GAME_RESOURCE_BUILD_TONE] == 1);
    assert(floater->carried_resource_code == GAME_RESOURCE_NONE);
    assert(floater->movement_state == 0x12);
    for (tick = 0; tick < 39; ++tick) {
        game_session_tick_floater_moves(&session, movement_tick + tick,
                                        &catalog);
        assert(target->source_value_34 == 2);
        assert(session.pending_events[slot].active == 1);
    }
    game_session_tick_floater_moves(&session, movement_tick + tick, &catalog);

    assert(target->source_value_34 == 3);
    assert(target->resource_stock[GAME_RESOURCE_BUILD_TONE] == 0);
    assert(target->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] == 0);
    assert(session.pending_events[slot].active == 0);
    assert(session.pending_event_count == 0);
    assert(floater->active_order_action == 0);
    assert(floater->linked_task_slot == -1);
}

static void test_site_damage_filters_player_variant_building_ids(void)
{
    GameSession session = {0};
    GameRuntimeLocation target = {0};
    GameFloaterStart *attacker;

    session.floater_count = 1;
    attacker = &session.floaters[0];
    attacker->is_active = 1;
    attacker->owner_slot = 1;
    target.renderer_class = 0;
    target.record_value_10 = 0x17 + 16;
    target.owner_id = 1;
    target.source_value_14 = 1;
    target.source_value_34 = 10;

    /* The native filter sees base ID 0x17 for every owner. */
    assert(game_session_damage_site(&session, 0, 0, 0, &target) == 0);
    assert(target.source_value_34 == 10);
}

static void test_code_five_delivery_starts_bridge_cons_for_its_owner(void)
{
    GameSession session = {0};
    GameRuntimeLocation *bridge;
    GameFloaterStart *floater;
    BuildingRenderCatalog catalog = {0};
    int slot;

    session.island_count = 2;
    session.floater_count = 1;
    session.islands[0].location_count = 2;
    session.islands[1].location_count = 1;
    session.world_bridge_count = 1;
    session.world_bridges[0].island_a = 0;
    session.world_bridges[0].island_b = 1;
    session.economy[1].hall_island_index = 0;
    session.economy[1].hall_location_index = 1;
    session.economy[1].inventory_count[0] = 1;
    session.islands[0].floater_max_x[1] = 0x9ff;
    bridge = &session.islands[0].locations[0];
    bridge->renderer_class = 2;
    bridge->record_value_10 = 2;
    bridge->owner_id = -1;
    bridge->bridge_neighbor_island = 1;
    bridge->source_location_slot_18 = -1;
    bridge->x = 200;
    bridge->y = 300;
    session.islands[0].locations[1].record_value_10 = 0x3a;
    session.islands[0].locations[1].owner_id = 1;
    session.islands[0].locations[1].source_location_slot_18 = -1;
    session.islands[0].locations[1].x = 100;
    session.islands[0].locations[1].y = 120;
    session.islands[1].locations[0].renderer_class = 2;
    session.islands[1].locations[0].record_value_10 = 2;
    session.islands[1].locations[0].owner_id = -1;
    session.islands[1].locations[0].bridge_neighbor_island = 0;

    catalog.item_count = 3;
    catalog.items[2].item_id = 2;
    catalog.items[2].present = 1;
    catalog.items[2].cons.present = 1;
    catalog.items[2].cons.fallback_frame = 2;
    catalog.items[2].prod.present = 1;
    catalog.items[2].prod.threshold = 2;

    floater = &session.floaters[0];
    floater->is_active = 1;
    floater->owner_slot = 1;
    floater->island_index = 0;
    floater->type_index = 0;
    floater->source_subtype = 0;
    floater->source_link_0c = -1;
    floater->linked_task_slot = -1;
    floater->carried_resource_code = 0;
    floater->x = session.islands[0].locations[1].x - 20;
    floater->y = session.islands[0].locations[1].y;

    slot = game_session_queue_inventory_action(&session, 1, 0, 0, 5);
    assert(slot == 0);
    game_session_assign_local_resource_tasks(&session, NULL);
    assert(floater->active_order_action == 4);
    assert(floater->linked_task_slot == slot);
    assert(floater->movement_state == 3);
    assert(session.pending_events[slot].assigned_floater_count == 1);

    /* The worker picks code 5 up from its Hall inventory before delivery. */
    floater->x = session.islands[0].locations[1].x;
    for (unsigned int tick = 0; tick < 20; ++tick)
        game_session_advance_local_resource_task(&session, floater);
    assert(session.economy[1].inventory_count[0] == 0);
    assert(floater->carried_resource_code == 5);
    assert(floater->movement_state == 4);

    /* Exact-arrival state 4 reaches the class-2/code-5 helper branch. */
    floater->x = bridge->x;
    floater->y = bridge->y;
    game_session_advance_local_resource_task(&session, floater);
    assert((bridge->source_flags & 0x004U) != 0);
    assert(bridge->construction_progress == 0);
    assert(bridge->resource_stock[GAME_RESOURCE_MAGIC_TONE] == 1);
    assert(floater->carried_resource_code == 0);
    assert(floater->active_order_action == 0);
    assert(floater->owner_slot == 1);
    assert(bridge->owner_id == -1); /* bridge contributor is stored at +0x2c */

    game_session_tick_item_animations(&session, &catalog);
    game_session_tick_item_animations(&session, &catalog);
    game_session_tick_item_animations(&session, &catalog);
    game_session_tick_item_animations(&session, &catalog);
    assert(bridge->bridge_constructed == 1);
    assert(session.islands[1].locations[0].bridge_constructed == 1);
    assert(game_session_bridge_is_active(&session, 0, 1));
    assert((session.islands[1].access_mask & (1U << 1)) != 0);
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
    PadCatalog catalog = {0};
    GameRuntimeLocation *site;
    unsigned int index;

    session.island_count = 1;
    session.islands[0].location_count = 2;
    site = &session.islands[0].locations[1];
    site->renderer_class = 0;
    site->record_value_10 = 0x45; /* item 0x25 for player 2 */
    site->owner_id = 2;
    site->source_value_22 = 1U << 2;
    site->source_flags = 0x410;
    catalog.item_count = 0x46;
    catalog.items[0x45].item_id = 0x45;
    catalog.items[0x45].maintenance_tone_cost = 0;

    /* The click queues the source message; effects remain deferred to tick. */
    assert(game_session_queue_onoff_action(&session, 2, 0, 1));
    assert(session.onoff_action_count == 1);
    assert(session.onoff_actions[0].player_slot == 2);
    assert(session.onoff_actions[0].island_index == 0);
    assert(session.onoff_actions[0].location_index == 1);
    assert(site->source_flags == 0x410);
    assert(game_session_pop_onoff_action(&session, &request));
    assert(request.player_slot == 2 && request.island_index == 0 &&
           request.location_index == 1);
    assert(!game_session_pop_onoff_action(&session, &request));
    assert(game_session_queue_onoff_action(&session, 2, 0, 1));
    assert(game_session_dispatch_onoff_actions(&session, &catalog) == 1);
    assert((site->source_flags & 0x400U) == 0);
    assert(game_session_queue_onoff_action(&session, 2, 0, 1));
    assert(game_session_dispatch_onoff_actions(&session, &catalog) == 1);
    assert((site->source_flags & 0x400U) != 0);
    assert(game_session_queue_onoff_action(&session, 2, 0, 1));
    assert(game_session_dispatch_onoff_actions(&session, &catalog) == 1);
    catalog.items[0x45].maintenance_tone_cost = 1;
    assert(game_session_queue_onoff_action(&session, 2, 0, 1));
    assert(game_session_dispatch_onoff_actions(&session, &catalog) == 0);
    assert((site->source_flags & 0x400U) == 0);
    assert(game_session_queue_onoff_action(&session, 1, 0, 1));
    assert(game_session_dispatch_onoff_actions(&session, &catalog) == 0);
    assert((site->source_flags & 0x400U) == 0);

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
