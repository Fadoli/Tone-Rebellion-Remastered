#include "game_session_action9.h"

/* Logic tests for worker reallocation stability and PANIC (remake rules). */

/* Two delivery tasks (A: slot 0, B: slot 1) and `count` workers on A. */
static int setup_two_delivery_tasks(GameSession *session,
                                    unsigned int count,
                                    int16_t movement_state)
{
    GameRuntimeLocation *hall;
    unsigned int index;
    int slot_a;
    int slot_b;

    memset(session, 0, sizeof(*session));
    session->island_count = 1;
    session->floater_count = (uint16_t)count;
    session->islands[0].location_count = 3;
    hall = &session->islands[0].locations[2];
    hall->record_value_10 = 0x2a;
    hall->owner_id = 0;
    for (index = 0; index < 2; ++index) {
        GameRuntimeLocation *target = &session->islands[0].locations[index];
        target->owner_id = 0;
        target->record_value_10 = 0x25;
    }
    slot_a = game_session_pending_event_add(session, 0, 0, 4, 0, 0, 1);
    slot_b = game_session_pending_event_add(session, 0, 0, 4, 0, 1, 1);
    assert(slot_a == 0 && slot_b == 1);
    for (index = 0; index < count; ++index) {
        GameFloaterStart *floater = &session->floaters[index];
        floater->is_active = 1;
        floater->owner_slot = 0;
        floater->island_index = 0;
        floater->source_link_0c = -1;
        floater->carried_resource_code = 1;
        floater->active_order_action = 4;
        floater->movement_state = movement_state;
        floater->has_move_order = 1;
        floater->linked_task_slot = (int16_t)slot_a;
        floater->order_resource_code = 1;
        floater->order_target_island = 0;
        floater->order_target_location = 0;
    }
    session->pending_events[slot_a].assigned_floater_count = (int16_t)count;
    return slot_a;
}

static unsigned int workers_on_slot(const GameSession *session, int slot)
{
    unsigned int index;
    unsigned int total = 0;
    for (index = 0; index < session->floater_count; ++index)
        if (session->floaters[index].linked_task_slot == slot) ++total;
    return total;
}

static void test_reallocation_does_not_wait_for_the_ten_tick_phase(void)
{
    GameSession session;
    int slot_a = setup_two_delivery_tasks(&session, 3, 3);

    /* Floater 0 is not due at tick 5 under the source cadence; the remake
       evaluates busy workers every tick, so it still moves to task B. */
    session.simulation_tick = 5;
    game_session_assign_local_resource_tasks(&session, NULL);
    assert(session.floaters[0].linked_task_slot == slot_a + 1);
    assert(workers_on_slot(&session, slot_a) == 2);
}

static void test_delivering_worker_is_reallocated_after_commitment(void)
{
    GameSession session;
    int slot_a = setup_two_delivery_tasks(&session, 3, 4);

    /* A worker walking a delivery (state 4) is not blocked by its trip. */
    session.simulation_tick = 0;
    game_session_assign_local_resource_tasks(&session, NULL);
    assert(session.floaters[0].linked_task_slot == slot_a + 1);
}

static void test_fresh_assignment_is_stable_for_the_commit_window(void)
{
    GameSession session;
    int slot_a = setup_two_delivery_tasks(&session, 3, 3);
    unsigned int index;

    /* Every worker just got its task: nobody may leave it, however lopsided
       the counts are, until the commitment window has passed. */
    for (index = 0; index < 3; ++index)
        session.floaters[index].task_commit_tick =
            GAME_SESSION_TASK_COMMIT_TICKS;
    for (session.simulation_tick = 0;
         session.simulation_tick < GAME_SESSION_TASK_COMMIT_TICKS;
         session.simulation_tick += 7) {
        game_session_assign_local_resource_tasks(&session, NULL);
        assert(workers_on_slot(&session, slot_a) == 3);
        assert(session.pending_events[slot_a].assigned_floater_count == 3);
    }
    session.simulation_tick = GAME_SESSION_TASK_COMMIT_TICKS;
    game_session_assign_local_resource_tasks(&session, NULL);
    assert(workers_on_slot(&session, slot_a) < 3);
}

static void test_reallocated_worker_gets_a_new_commit_window(void)
{
    GameSession session;
    int slot_a = setup_two_delivery_tasks(&session, 3, 3);

    session.simulation_tick = 100;
    game_session_assign_local_resource_tasks(&session, NULL);
    assert(session.floaters[0].linked_task_slot == slot_a + 1);
    assert(session.floaters[0].task_commit_tick ==
           100U + GAME_SESSION_TASK_COMMIT_TICKS);
}

static void test_balanced_workers_never_change_task(void)
{
    GameSession session;
    int slot_a = setup_two_delivery_tasks(&session, 4, 3);
    unsigned int tick;

    /* Settle: 4 workers on A, 0 on B move until counts differ by < 2. */
    for (tick = 0; tick < 4U * GAME_SESSION_TASK_COMMIT_TICKS; ++tick) {
        session.simulation_tick = tick;
        game_session_assign_local_resource_tasks(&session, NULL);
    }
    assert(workers_on_slot(&session, slot_a) == 2);
    assert(workers_on_slot(&session, slot_a + 1) == 2);
    /* Nothing changes any more: no ping-pong between equal tasks. */
    {
        int16_t before[4];
        unsigned int index;
        for (index = 0; index < 4; ++index)
            before[index] = session.floaters[index].linked_task_slot;
        for (; tick < 12U * GAME_SESSION_TASK_COMMIT_TICKS; ++tick) {
            session.simulation_tick = tick;
            game_session_assign_local_resource_tasks(&session, NULL);
        }
        for (index = 0; index < 4; ++index)
            assert(session.floaters[index].linked_task_slot == before[index]);
    }
}

static void test_worker_at_build_site_is_never_reallocated(void)
{
    GameSession session;
    int slot_a = setup_two_delivery_tasks(&session, 3, 5);

    /* State 5 is the build/finish step: long tasks must complete. */
    session.simulation_tick = 10U * GAME_SESSION_TASK_COMMIT_TICKS;
    game_session_assign_local_resource_tasks(&session, NULL);
    assert(workers_on_slot(&session, slot_a) == 3);
    assert(session.pending_events[slot_a].assigned_floater_count == 3);
}

static void test_combat_and_handoff_workers_are_not_reallocated(void)
{
    GameSession session;
    int slot_a = setup_two_delivery_tasks(&session, 3, 6);

    session.floaters[1].movement_state = 7;
    session.floaters[2].active_order_action = 9;
    session.floaters[2].movement_state = 3;
    session.floaters[2].handoff_resume_action = 4;
    session.simulation_tick = 10U * GAME_SESSION_TASK_COMMIT_TICKS;
    game_session_assign_local_resource_tasks(&session, NULL);
    assert(workers_on_slot(&session, slot_a) == 3);
}

static void make_workers_idle(GameSession *session)
{
    unsigned int index;
    for (index = 0; index < session->floater_count; ++index) {
        GameFloaterStart *floater = &session->floaters[index];
        floater->active_order_action = 0;
        floater->movement_state = 0;
        floater->has_move_order = 0;
        floater->linked_task_slot = -1;
        floater->order_target_location = -1;
        floater->order_target_island = UINT8_MAX;
    }
    session->pending_events[0].assigned_floater_count = 0;
    session->pending_events[1].assigned_floater_count = 0;
}

static void test_idle_workers_spread_evenly_over_tasks(void)
{
    GameSession session;
    int slot_a = setup_two_delivery_tasks(&session, 6, 3);

    make_workers_idle(&session);
    game_session_assign_local_resource_tasks(&session, NULL);
    assert(workers_on_slot(&session, slot_a) == 3);
    assert(workers_on_slot(&session, slot_a + 1) == 3);

    setup_two_delivery_tasks(&session, 5, 3);
    make_workers_idle(&session);
    game_session_assign_local_resource_tasks(&session, NULL);
    assert(workers_on_slot(&session, slot_a) +
           workers_on_slot(&session, slot_a + 1) == 5);
    assert(workers_on_slot(&session, slot_a) >= 2 &&
           workers_on_slot(&session, slot_a + 1) >= 2);
}

static void test_three_three_split_never_swaps_workers(void)
{
    GameSession session;
    int slot_a = setup_two_delivery_tasks(&session, 6, 3);
    int16_t before[6];
    unsigned int index;
    unsigned int tick;

    make_workers_idle(&session);
    game_session_assign_local_resource_tasks(&session, NULL);
    for (index = 0; index < 6; ++index)
        before[index] = session.floaters[index].linked_task_slot;
    assert(workers_on_slot(&session, slot_a) == 3);
    /* Long run, far past every commitment window: nobody moves A <-> B. */
    for (tick = 1; tick < 20U * GAME_SESSION_TASK_COMMIT_TICKS; ++tick) {
        session.simulation_tick = tick;
        game_session_assign_local_resource_tasks(&session, NULL);
        for (index = 0; index < 6; ++index)
            assert(session.floaters[index].linked_task_slot == before[index]);
    }
}

/* Island with four floaters: three workers (owner 0) and Leviathan units. */
static void setup_panic_island(GameSession *session, unsigned int workers,
                               unsigned int leviathans)
{
    unsigned int index;

    memset(session, 0, sizeof(*session));
    session->island_count = 1;
    session->floater_count = (uint16_t)(workers + leviathans);
    for (index = 0; index < session->floater_count; ++index) {
        GameFloaterStart *floater = &session->floaters[index];
        floater->is_active = 1;
        floater->island_index = 0;
        floater->source_link_0c = -1;
        floater->linked_task_slot = -1;
        floater->order_target_floater = -1;
        floater->defend_target_floater = -1;
        floater->x = (uint16_t)(100U + index * 100U);
        floater->y = 100;
        if (index < workers) {
            floater->owner_slot = 0;
            floater->type_index = 0;
        } else {
            floater->owner_slot = 4;
            floater->type_index = 4;
        }
    }
}

static void test_panic_sends_workers_to_the_nearest_enemy(void)
{
    GameSession session;

    setup_panic_island(&session, 2, 2);
    /* FUN_0042219e panic: action 6 against the nearest valid candidate on the
       island. Workers at x=100/200, leviathans at x=300 (index 2) and x=90
       (index 3): worker 0 is nearest to index 3 (10); worker 1 ties between
       worker 0 and index 2 (100) and takes the first. */
    session.floaters[3].x = 90;
    session.islands[0].source_event_state[0] = 1;
    game_session_apply_panic_orders(&session);
    assert(session.floaters[0].active_order_action == 6);
    assert(session.floaters[0].order_target_floater == 3);
    assert(session.floaters[1].active_order_action == 6);
    assert(session.floaters[1].order_target_floater == 0);
}

static void test_panic_is_per_player_and_per_island(void)
{
    GameSession session;

    setup_panic_island(&session, 2, 1);
    session.floaters[1].owner_slot = 1;
    session.floaters[1].type_index = 1;
    session.islands[0].source_event_state[0] = 1;
    game_session_apply_panic_orders(&session);
    assert(session.floaters[0].active_order_action == 6);
    assert(session.floaters[1].active_order_action == 0);

    setup_panic_island(&session, 1, 1);
    session.island_count = 2;
    session.floaters[1].island_index = 1;
    session.islands[0].source_event_state[0] = 1;
    game_session_apply_panic_orders(&session);
    assert(session.floaters[0].active_order_action == 0);
}

static void test_panic_skips_friends_but_not_leviathans(void)
{
    GameSession session;

    setup_panic_island(&session, 2, 1);
    session.floaters[1].owner_slot = 1;
    session.floaters[1].type_index = 1;
    session.floaters[1].x = 110;
    /* DAT_00619290[0][1] set = friend: the nearby player-1 worker is skipped
       and the Leviathan (category 4, always a candidate) is chosen. */
    session.diplomacy_policy_mask[0] = 1U << 1;
    session.islands[0].source_event_state[0] = 1;
    game_session_apply_panic_orders(&session);
    assert(session.floaters[0].active_order_action == 6);
    assert(session.floaters[0].order_target_floater == 2);
}

static void test_panic_releases_the_task_claim(void)
{
    GameSession session;
    int slot_a = setup_two_delivery_tasks(&session, 2, 3);

    session.floater_count = 3;
    session.floaters[2].is_active = 1;
    session.floaters[2].island_index = 0;
    session.floaters[2].owner_slot = 4;
    session.floaters[2].type_index = 4;
    session.floaters[2].source_link_0c = -1;
    session.floaters[2].linked_task_slot = -1;
    session.floaters[2].x = 50;
    session.islands[0].source_event_state[0] = 1;
    game_session_apply_panic_orders(&session);
    assert(session.floaters[0].active_order_action == 6);
    assert(session.floaters[0].linked_task_slot == -1);
    assert(session.pending_events[slot_a].assigned_floater_count == 0);
}

static void test_panic_off_cancels_the_attack_orders(void)
{
    GameSession session;

    setup_panic_island(&session, 2, 1);
    session.islands[0].source_event_state[0] = 1;
    game_session_apply_panic_orders(&session);
    assert(session.floaters[0].active_order_action == 6);
    session.islands[0].source_event_state[0] = 0;
    game_session_apply_panic_orders(&session);
    assert(session.floaters[0].active_order_action == 0);
    assert(session.floaters[1].active_order_action == 0);
}

static void test_panic_event_toggles_the_visible_state(void)
{
    GameSession session;

    setup_panic_island(&session, 1, 1);
    assert(!game_session_panic_active(&session, 0, 0));
    assert(game_session_queue_island_event3_subtype0(&session, 0, 0));
    game_session_dispatch_island_events(&session);
    assert(game_session_panic_active(&session, 0, 0));
    assert(!game_session_panic_active(&session, 1, 0));
    assert(game_session_queue_island_event3_subtype0(&session, 0, 0));
    game_session_dispatch_island_events(&session);
    assert(!game_session_panic_active(&session, 0, 0));
}

static void test_cancelled_task_workers_take_the_remaining_task(void)
{
    GameSession session;
    int slot_a = setup_two_delivery_tasks(&session, 3, 3);
    GamePendingEvent expected = session.pending_events[slot_a];
    unsigned int index;

    assert(game_session_dispatch_task_command(&session, (uint8_t)slot_a, 12,
                                              &expected));
    for (index = 0; index < 3; ++index) {
        assert(session.floaters[index].linked_task_slot == -1);
        assert(session.floaters[index].active_order_action == 0);
    }
    game_session_assign_local_resource_tasks(&session, NULL);
    assert(workers_on_slot(&session, slot_a + 1) == 3);
    assert(session.pending_events[slot_a + 1].assigned_floater_count == 3);
}

static void test_home_wander_fallback_worker_is_idle(void)
{
    GameSession session;
    int slot_a = setup_two_delivery_tasks(&session, 2, 3);

    make_workers_idle(&session);
    /* Idle fallback (FA_Wander, action 0x0e) with no route must not block
       task assignment. A worker still on a route (handoff) stays untouched. */
    session.floaters[0].active_order_action = 0x0e;
    session.floaters[0].has_wander_order = 1;
    session.floaters[1].active_order_action = 0x0e;
    session.floaters[1].has_move_order = 1;
    game_session_assign_local_resource_tasks(&session, NULL);
    assert(session.floaters[0].linked_task_slot >= slot_a);
    assert(session.floaters[0].active_order_action == 4);
    assert(session.floaters[1].linked_task_slot == -1);
    assert(session.floaters[1].active_order_action == 0x0e);
}

static void test_orphaned_order_without_claim_is_released(void)
{
    GameSession session;

    setup_two_delivery_tasks(&session, 1, 0);
    /* Claim dropped by another path while the delivery order stayed set. */
    session.floaters[0].linked_task_slot = -1;
    session.floaters[0].has_move_order = 0;
    session.pending_events[0].assigned_floater_count = 0;
    game_session_assign_local_resource_tasks(&session, NULL);
    assert(session.floaters[0].linked_task_slot >= 0);
    assert(session.floaters[0].active_order_action == 4);
    assert(session.floaters[0].has_move_order == 1);
}

static void test_worker_tasks_and_panic(void)
{
    test_reallocation_does_not_wait_for_the_ten_tick_phase();
    test_delivering_worker_is_reallocated_after_commitment();
    test_fresh_assignment_is_stable_for_the_commit_window();
    test_reallocated_worker_gets_a_new_commit_window();
    test_balanced_workers_never_change_task();
    test_idle_workers_spread_evenly_over_tasks();
    test_three_three_split_never_swaps_workers();
    test_worker_at_build_site_is_never_reallocated();
    test_combat_and_handoff_workers_are_not_reallocated();
    test_panic_sends_workers_to_the_nearest_enemy();
    test_panic_is_per_player_and_per_island();
    test_panic_skips_friends_but_not_leviathans();
    test_panic_releases_the_task_claim();
    test_panic_off_cancels_the_attack_orders();
    test_panic_event_toggles_the_visible_state();
    test_cancelled_task_workers_take_the_remaining_task();
    test_home_wander_fallback_worker_is_idle();
    test_orphaned_order_without_claim_is_released();
}
