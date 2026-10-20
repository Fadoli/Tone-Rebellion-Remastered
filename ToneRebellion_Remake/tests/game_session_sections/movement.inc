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
