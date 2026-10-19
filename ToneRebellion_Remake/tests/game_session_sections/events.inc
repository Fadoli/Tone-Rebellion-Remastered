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
