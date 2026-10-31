static void test_charge_order_accepts_each_players_source_variant(void)
{
    GameSession session = {0};
    unsigned int player;

    session.island_count = 1;
    session.floater_count = GAME_START_PLAYER_COUNT;
    session.islands[0].location_count = GAME_START_PLAYER_COUNT;
    for (player = 0; player < GAME_START_PLAYER_COUNT; ++player) {
        GameRuntimeLocation *source = &session.islands[0].locations[player];
        GameFloaterStart *floater = &session.floaters[player];
        source->record_value_10 = 0x2c + (int32_t)player * 16;
        source->owner_id = (int32_t)player;
        source->source_location_slot_18 = (int16_t)player;
        floater->island_index = 0;
        floater->owner_slot = (uint8_t)player;
        floater->source_subtype = 1;
        floater->is_active = 1;
        floater->linked_task_slot = -1;
        floater->source_link_0c = -1;
    }

    for (player = 0; player < GAME_START_PLAYER_COUNT; ++player) {
        GameFloaterStart *floater = &session.floaters[player];
        assert(game_session_order_floater_to_charge_site(&session,
            (uint8_t)player, 0, player, (uint16_t)player));
        assert(floater->movement_state == 11);
        assert(floater->source_order_parameter_32 == (int32_t)player);
    }
}

static void test_bridge_crossing_keeps_soldier_hall_link(void)
{
    GameSession session = {0};
    GameRuntimeLocation *hall;
    GameFloaterStart *soldier;
    unsigned int tick;
    unsigned int slot;

    session.island_count = 2;
    session.floater_count = 1;
    session.islands[0].location_count = 2;
    session.islands[1].location_count = 1;
    session.islands[0].floater_max_x[0] = 0x9ff;
    session.islands[1].floater_max_x[0] = 0x9ff;
    session.islands[0].locations[0].renderer_class = 2;
    session.islands[0].locations[0].source_flags = 1;
    session.islands[0].locations[0].bridge_neighbor_island = 1;
    session.islands[0].locations[0].x = 300;
    session.islands[0].locations[0].y = 200;
    session.islands[1].locations[0].renderer_class = 2;
    session.islands[1].locations[0].source_flags = 1;
    session.islands[1].locations[0].bridge_neighbor_island = 0;
    session.islands[1].locations[0].x = 500;
    session.islands[1].locations[0].y = 260;
    hall = &session.islands[0].locations[1];
    hall->owner_id = 0;
    hall->source_location_slot_18 = 3;
    hall->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] = 20;
    hall->charge_recent_floater = -1;
    for (slot = 0; slot < 8; ++slot) hall->charge_floater_slots[slot] = -1;

    soldier = &session.floaters[0];
    soldier->is_active = 1;
    soldier->island_index = 0;
    soldier->type_index = 0;
    soldier->owner_slot = 0;
    soldier->source_subtype = 1;
    soldier->source_link_0c = -1;
    soldier->linked_task_slot = -1;
    soldier->order_target_floater = -1;
    soldier->order_target_location = -1;
    assert(game_session_link_floater_charge(&session, 0, 1));
    assert(hall->charge_floater_count == 1);

    /* FUN_0041e569 state 0x11 never writes +0x0c: the soldier keeps its
       home source while it lives on the neighbor island. */
    assert(game_session_begin_floater_handoff(&session, soldier, 1));
    soldier->x = soldier->destination_x;
    soldier->y = soldier->destination_y;
    for (tick = 0; tick < 1000 && soldier->movement_state == 0x11; ++tick)
        (void)game_session_tick_floater_handoff(&session, soldier);
    assert(soldier->movement_state != 0x11);
    assert(soldier->island_index == 1);
    assert(soldier->source_link_0c == 3);
    assert(soldier->charge_source_island == 0);
    assert(soldier->charge_source_location == 1);
    assert(hall->charge_floater_count == 1);
    assert(hall->charge_floater_slots[0] == 0);

    /* Death away from home still frees the hall's charge slot. */
    game_session_retire_floater(&session, 0);
    assert(hall->charge_floater_count == 0);
    assert(hall->charge_floater_slots[0] == -1);
}

static void test_floater_pickup_order_collects_ground_artifact(void)
{
    GameSession session = {0};
    GameFloaterStart *floater;
    GameRuntimeLocation *object;
    unsigned int slot;

    session.island_count = 1;
    session.floater_count = 1;
    session.islands[0].location_count = 2;
    session.islands[0].locations[1].owner_id = -1;
    session.islands[0].locations[1].source_value_14 = -1;
    session.islands[0].locations[1].charge_staff_task_handle = -1;
    floater = &session.floaters[0];
    floater->island_index = 0;
    floater->owner_slot = 2;
    /* Initial workers are created with subtype 0 and must still be allowed
       to pick up a ground artifact through the player order. */
    floater->source_subtype = 0;
    floater->is_active = 1;
    floater->linked_task_slot = -1;
    floater->source_link_0c = -1;
    floater->carried_resource_code = 5;
    floater->x = 100;
    floater->y = 100;
    object = &session.islands[0].locations[0];
    object->renderer_class = 0;
    object->owner_id = -1;
    object->record_value_10 = 1;
    object->record_value_24 = 6;
    object->x = 100;
    object->y = 100;
    object->charge_staff_task_handle = -1;
    object->leviathan_spawned_floater = -1; /* runtime sites start at -1, not slot 0 */
    object->source_location_slot_18 = -1;
    object->source_category_slot_60 = -1;
    for (slot = 0; slot < 8; ++slot)
        object->charge_floater_slots[slot] = -1;
    for (slot = 0; slot < GAME_RESOURCE_TYPE_COUNT; ++slot)
        object->source_task_slot[slot] = -1;

    /* Obtain is a type-0xd task; the scheduler attaches the free worker. */
    assert(game_session_queue_obtain_task(&session, 2, 0, 0));
    assert(!game_session_queue_obtain_task(&session, 2, 0, 0));
    game_session_tick_floater_moves(&session, 1, NULL);
    assert(floater->active_order_action == 0x0d || floater->carried_resource_code == 6);
    game_session_tick_floater_moves(&session, 2, NULL);
    assert(floater->carried_resource_code == 6);
    assert(object->record_value_10 == 0 && object->record_value_24 == 0);
    assert(!game_session_queue_obtain_task(&session, 2, 0, 0));
    assert(session.pending_event_count == 0);
    assert(session.islands[0].locations[1].record_value_10 == 1);
    assert(session.islands[0].locations[1].record_value_24 == 5);
}

static void test_obtain_task_crosses_bridge_to_ground_artifact(void)
{
    GameSession session = {0};
    GameFloaterStart *floater;
    GameRuntimeLocation *object;
    unsigned int slot;
    unsigned int tick;

    session.island_count = 2;
    session.floater_count = 1;
    session.islands[0].location_count = 1;
    session.islands[1].location_count = 2;
    session.islands[0].floater_max_x[2] = 0x9ff;
    session.islands[1].floater_max_x[2] = 0x9ff;
    session.islands[0].locations[0].renderer_class = 2;
    session.islands[0].locations[0].source_flags = 1;
    session.islands[0].locations[0].bridge_neighbor_island = 1;
    session.islands[0].locations[0].x = 300;
    session.islands[0].locations[0].y = 200;
    session.islands[1].locations[0].renderer_class = 2;
    session.islands[1].locations[0].source_flags = 1;
    session.islands[1].locations[0].bridge_neighbor_island = 0;
    session.islands[1].locations[0].x = 500;
    session.islands[1].locations[0].y = 260;
    floater = &session.floaters[0];
    floater->island_index = 0;
    floater->owner_slot = 2;
    floater->source_subtype = 0;
    floater->is_active = 1;
    floater->linked_task_slot = -1;
    floater->source_link_0c = -1;
    floater->order_target_floater = -1;
    floater->order_target_location = -1;
    floater->x = 300;
    floater->y = 200;
    floater->movement_speed = 3;
    object = &session.islands[1].locations[1];
    object->renderer_class = 0;
    object->owner_id = -1;
    object->record_value_10 = 1;
    object->record_value_24 = 6;
    object->x = 520;
    object->y = 230;
    object->charge_staff_task_handle = -1;
    object->leviathan_spawned_floater = -1;
    object->source_location_slot_18 = -1;
    object->source_category_slot_60 = -1;
    object->source_value_14 = -1;
    for (slot = 0; slot < 8; ++slot)
        object->charge_floater_slots[slot] = -1;
    for (slot = 0; slot < GAME_RESOURCE_TYPE_COUNT; ++slot)
        object->source_task_slot[slot] = -1;

    /* The scheduler sends the worker over the bridge (state 0x11, resume
       action 0xd); the task claim must survive the crossing. */
    assert(game_session_queue_obtain_task(&session, 2, 1, 1));
    game_session_tick_floater_moves(&session, 1, NULL);
    assert(floater->movement_state == 0x11);
    assert(floater->handoff_resume_action == 0x0d);
    for (tick = 2; tick < 2000 && floater->carried_resource_code != 6; ++tick) {
        game_session_tick_floater_moves(&session, tick, NULL);
        if (floater->movement_state == 0x11) assert(floater->linked_task_slot >= 0);
    }
    assert(floater->island_index == 1);
    assert(floater->carried_resource_code == 6);
    assert(object->record_value_10 == 0 && object->record_value_24 == 0);
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
    floater->is_active = 1;
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

    game_session_tick_floater_moves(&session, 1, NULL);
    assert(floater->x == 103 && floater->y == 97);
    assert(!floater->facing_left);
    assert(idle_floater->x == idle_x && !idle_floater->has_move_order);

    floater->destination_x = 100;
    floater->destination_y = 96;
    floater->movement_speed = 3;
    floater->stop_radius = 10;
    floater->has_move_order = 1;
    game_session_tick_floater_moves(&session, 2, NULL);
    assert(floater->x == 103 && floater->y == 97);
    assert(!floater->has_move_order); /* destination is within the stop radius */
    assert(floater->facing_left); /* facing follows target even when stationary */

    floater->destination_x = 100;
    floater->destination_y = 97;
    floater->stop_radius = 0;
    floater->has_move_order = 1;
    game_session_tick_floater_moves(&session, 3, NULL);
    assert(floater->facing_left);
    game_session_tick_floater_moves(&session, 4, NULL);
    game_session_tick_floater_moves(&session, 5, NULL);
    game_session_tick_floater_moves(&session, 6, NULL);
    game_session_tick_floater_moves(&session, 7, NULL);
    assert(floater->x == 100 && floater->y == 97);

}

static void test_idle_floater_keeps_wander_target_until_exact_arrival(void)
{
    GameSession session = {0};
    GameFloaterStart *floater;
    uint16_t target_x;
    uint16_t target_y;

    session.island_count = 1;
    session.floater_count = 1;
    floater = &session.floaters[0];
    floater->island_index = 0;
    floater->owner_slot = 0;
    floater->type_index = 0;
    floater->is_active = 1;
    floater->x = 500;
    floater->y = 500;
    floater->movement_speed = 3;
    floater->has_wander_order = 1;

    game_session_tick_floater_moves(&session, 1, NULL);
    assert(floater->movement_state == 0x0e);
    assert(floater->wander_timer == 60);
    target_x = floater->destination_x;
    target_y = floater->destination_y;
    assert(floater->x != 500 || floater->y != 500);

    game_session_tick_floater_moves(&session, 2, NULL);
    assert(floater->destination_x == target_x);
    assert(floater->destination_y == target_y);
    assert(floater->movement_state == 0x0e);
    assert(floater->wander_timer == 60);
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
    session.floaters[0].is_active = 1;
    session.floaters[1].island_index = 0;
    session.floaters[1].x = 140;
    session.floaters[1].y = 100;
    session.floaters[1].is_active = 1;
    session.floaters[2].island_index = 1;
    session.floaters[2].x = 100;
    session.floaters[2].y = 100;
    session.floaters[2].is_active = 1;

    assert(game_session_floater_at(&session, 0, 119, 119) == 0);
    assert(game_session_floater_at(&session, 0, 120, 100) == -1);
    assert(game_session_floater_at(&session, 1, 100, 100) == 2);
    assert(game_session_floater_at(&session, 2, 100, 100) == -1);
    assert(game_session_floater_at(NULL, 0, 100, 100) == -1);
}

static void test_initial_worker_accepts_coordinate_move_order(void)
{
    GameSession session = {0};
    GameFloaterStart *worker;

    session.island_count = 1;
    session.floater_count = 1;
    worker = &session.floaters[0];
    worker->is_active = 1;
    worker->owner_slot = 2;
    worker->source_subtype = 0;
    worker->island_index = 0;

    assert(game_session_order_floater_to_coordinate(
        &session, 2, 0, 0, 350, 120));
    assert(worker->source_order_state_2c == 9);
    assert(worker->source_order_island_28 == 0);
    assert(worker->source_order_coordinate_30 == (uint16_t)(0x23U << 8 | 0x0cU));
    assert(worker->source_order_pending == 1);
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
    session.floaters[0].is_active = 1;
    session.floaters[0].source_subtype = 0;
    session.floaters[1].type_index = 1;
    session.floaters[1].is_active = 1;
    session.floaters[1].source_subtype = 1;
    session.floaters[2].type_index = 1;
    session.floaters[2].is_active = 1;
    session.floaters[2].source_subtype = 2;
    session.floaters[3].type_index = 2;
    session.floaters[3].is_active = 1;
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
