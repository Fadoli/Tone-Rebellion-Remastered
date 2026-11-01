/* Worker scheduler (FUN_0042219e / FUN_00422031) outputs and task-leg
   behaviour (FUN_004211bb cases 3/4). See behavior/island-tasks.md,
   "Répartition des ouvriers (refonte 2026-11-01)". */

enum {
    SCHED_PAD = 0,
    SCHED_HALL = 1,
    SCHED_TARGET = 2
};

/* One island: an empty pad (construction site), player 0's Hall holding
   Build Tone, and a plain owned site used as delivery target. Workers stand
   between the Hall and the target. Pad item 0x25 costs 2 Build Tone. */
static void make_scheduler_island(GameSession *session, PadCatalog *catalog,
                                  unsigned int worker_count)
{
    GameRuntimeIsland *island;
    GameRuntimeLocation *pad;
    GameRuntimeLocation *hall;
    GameRuntimeLocation *target;
    unsigned int index;

    memset(session, 0, sizeof(*session));
    memset(catalog, 0, sizeof(*catalog));
    session->island_count = 1;
    session->floater_count = (uint16_t)worker_count;
    island = &session->islands[0];
    island->location_count = 3;
    island->floater_max_x[0] = 0x9ff;
    session->economy[0].hall_island_index = 0;
    session->economy[0].hall_location_index = SCHED_HALL;
    session->economy[0].source_maintenance_capacity = 10;
    session->economy[0].source_maintenance_budget = 10;

    pad = &island->locations[SCHED_PAD];
    pad->renderer_class = 0;
    pad->record_value_10 = 1;
    pad->record_value_24 = 5;
    pad->owner_id = -1;
    pad->source_value_14 = -1;
    pad->source_value_22 = 1;
    pad->construction_site_size = 0;
    pad->upgrade_task_handle = -1;
    pad->x = 300;
    pad->y = 120;

    hall = &island->locations[SCHED_HALL];
    hall->renderer_class = 0;
    hall->record_value_10 = 0x2a;
    hall->owner_id = 0;
    hall->upgrade_task_handle = -1;
    hall->resource_stock[GAME_RESOURCE_BUILD_TONE] = 10;
    hall->x = 100;
    hall->y = 120;

    target = &island->locations[SCHED_TARGET];
    target->renderer_class = 0;
    target->record_value_10 = 0x25;
    target->owner_id = 0;
    target->source_location_slot_18 = -1;
    target->upgrade_task_handle = -1;
    target->source_task_slot[0] = -1;
    target->source_task_slot[1] = -1;
    target->source_task_slot[2] = -1;
    target->x = 200;
    target->y = 120;

    catalog->item_count = 0x26;
    catalog->items[0x25].item_id = 0x25;
    catalog->items[0x25].size = 0;
    catalog->items[0x25].building_tone_cost = 2;
    catalog->items[0x25].maintenance_tone_cost = 1;
    catalog->items[0x25].hit_points = 4;

    for (index = 0; index < worker_count; ++index) {
        GameFloaterStart *floater = &session->floaters[index];
        floater->is_active = 1;
        floater->owner_slot = 0;
        floater->island_index = 0;
        floater->type_index = 0;
        floater->source_subtype = 0;
        floater->source_link_0c = -1;
        floater->linked_task_slot = -1;
        floater->order_target_location = -1;
        floater->order_target_island = UINT8_MAX;
        floater->movement_speed = 30;
        floater->x = 150;
        floater->y = 120;
    }
}

static int add_delivery_row(GameSession *session, int16_t code, int priority)
{
    int slot = game_session_pending_event_add(session, 0, 0, 4, 0,
                                              SCHED_TARGET, code);
    assert(slot >= 0);
    session->pending_events[slot].priority = (uint16_t)priority;
    return slot;
}

/* --- Scheduler outputs (FUN_0042219e / FUN_00422031) -------------------- */

static void test_scheduler_ignores_the_task_island(void)
{
    GameSession session;
    PadCatalog catalog;
    GameFloaterStart *worker;
    int slot;

    make_scheduler_island(&session, &catalog, 1);
    session.island_count = 2;
    worker = &session.floaters[0];
    worker->island_index = 1;
    worker->carried_resource_code = 1;
    slot = add_delivery_row(&session, 1, 1);

    /* FUN_00422031 has no island test: a worker on island 1 carrying the
       code is attached to a row on island 0. */
    game_session_assign_local_resource_tasks(&session, NULL);
    assert(worker->linked_task_slot == slot);
    assert(worker->active_order_action == 4);
    assert(worker->order_target_island == 0);
    assert(worker->order_target_location == SCHED_TARGET);
    assert(worker->order_resource_code == 1);
    assert(worker->movement_state == 0);
    assert(worker->task_step == 0);
    assert(session.pending_events[slot].assigned_floater_count == 1);
}

static void test_scheduler_admits_only_with_cargo_or_a_source(void)
{
    GameSession session;
    PadCatalog catalog;
    GameRuntimeLocation *hall;
    GameFloaterStart *worker;
    int slot;

    make_scheduler_island(&session, &catalog, 1);
    hall = &session.islands[0].locations[SCHED_HALL];
    worker = &session.floaters[0];
    slot = add_delivery_row(&session, 1, 1);

    /* Empty Hall: no FUN_00420dbd source, no cargo, no admission. */
    hall->resource_stock[GAME_RESOURCE_BUILD_TONE] = 0;
    game_session_assign_local_resource_tasks(&session, NULL);
    assert(worker->linked_task_slot == -1);

    /* Hall stock but stock mode != 0: FUN_00452ceb refuses the Hall. */
    hall->resource_stock[GAME_RESOURCE_BUILD_TONE] = 5;
    session.economy[0].stock_mode[GAME_RESOURCE_BUILD_TONE] = 1;
    game_session_assign_local_resource_tasks(&session, NULL);
    assert(worker->linked_task_slot == -1);

    /* Carrying the code needs no source. */
    worker->carried_resource_code = 1;
    game_session_assign_local_resource_tasks(&session, NULL);
    assert(worker->linked_task_slot == slot);

    /* A Hall in mode 0 with stock is a source for an empty-handed worker. */
    worker->linked_task_slot = -1;
    worker->active_order_action = 0;
    worker->carried_resource_code = 0;
    session.pending_events[slot].assigned_floater_count = 0;
    session.economy[0].stock_mode[GAME_RESOURCE_BUILD_TONE] = 0;
    game_session_assign_local_resource_tasks(&session, NULL);
    assert(worker->linked_task_slot == slot);
}

static void test_scheduler_charge_row_needs_subtype_zero(void)
{
    GameSession session;
    PadCatalog catalog;
    GameFloaterStart *worker;
    int charge_slot;
    int delivery_slot;

    make_scheduler_island(&session, &catalog, 1);
    worker = &session.floaters[0];
    worker->source_subtype = 1;
    worker->carried_resource_code = 1;
    charge_slot = game_session_pending_event_add(&session, 0, 0, 0x0b,
                                                 SCHED_TARGET, 0, 0);
    delivery_slot = add_delivery_row(&session, 1, 1);
    assert(charge_slot == 0 && delivery_slot == 1);

    /* FUN_00422031 case 0xb rejects subtype 1, so the next row in slot
       order takes the worker. */
    game_session_assign_local_resource_tasks(&session, NULL);
    assert(worker->linked_task_slot == delivery_slot);
    assert(session.pending_events[charge_slot].assigned_floater_count == 0);
}

static void test_scheduler_priority_three_masks_other_rows(void)
{
    GameSession session;
    PadCatalog catalog;
    GameFloaterStart *worker;
    int low;
    int high;

    make_scheduler_island(&session, &catalog, 1);
    worker = &session.floaters[0];
    worker->carried_resource_code = 1;
    low = add_delivery_row(&session, 1, 1);
    high = add_delivery_row(&session, 1, 3);

    /* While the player has a priority-3 row, slot 0 (class 1) is skipped. */
    game_session_assign_local_resource_tasks(&session, NULL);
    assert(worker->linked_task_slot == high);
    assert(session.pending_events[low].assigned_floater_count == 0);
    assert(session.pending_events[high].assigned_floater_count == 1);
}

/* Worker linked to row A (class/count given), row B (class/count given):
   returns 1 when one scheduler pass moves the worker to B. */
static int scheduler_swaps(int a_class, int a_count, int b_class, int b_count)
{
    GameSession session;
    PadCatalog catalog;
    GameFloaterStart *worker;
    int slot_a;
    int slot_b;

    make_scheduler_island(&session, &catalog, 1);
    worker = &session.floaters[0];
    worker->carried_resource_code = 1;
    slot_a = add_delivery_row(&session, 1, a_class);
    slot_b = add_delivery_row(&session, 1, b_class);
    worker->linked_task_slot = (int16_t)slot_a;
    worker->active_order_action = 4;
    worker->order_resource_code = 1;
    worker->order_target_island = 0;
    worker->order_target_location = SCHED_TARGET;
    session.pending_events[slot_a].assigned_floater_count = (int16_t)a_count;
    session.pending_events[slot_b].assigned_floater_count = (int16_t)b_count;
    game_session_assign_local_resource_tasks(&session, NULL);
    if (worker->linked_task_slot == slot_b) {
        assert(session.pending_events[slot_a].assigned_floater_count ==
               a_count - 1);
        assert(session.pending_events[slot_b].assigned_floater_count ==
               b_count + 1);
        return 1;
    }
    assert(worker->linked_task_slot == slot_a);
    assert(session.pending_events[slot_a].assigned_floater_count == a_count);
    return 0;
}

static void test_scheduler_count_rule_by_class(void)
{
    /* Same class: at least two workers fewer. */
    assert(scheduler_swaps(1, 3, 1, 1));
    assert(!scheduler_swaps(1, 3, 1, 2));
    assert(scheduler_swaps(2, 4, 2, 2));
    /* Class 2 row against a class 1 task: count < current * 2 - 2. */
    assert(scheduler_swaps(1, 3, 2, 3));
    assert(!scheduler_swaps(1, 3, 2, 4));
    /* Class 1 row against a class 2 task: count * 2 < current - 1. */
    assert(scheduler_swaps(2, 5, 1, 1));
    assert(!scheduler_swaps(2, 5, 1, 2));
    /* Class 3 rows: same-class rule among themselves. */
    assert(scheduler_swaps(3, 9, 3, 7));
    assert(!scheduler_swaps(3, 9, 3, 8));
}

static void test_scheduler_class_three_row_takes_any_class_one_worker(void)
{
    /* A class 3 row beats a class 1 or 2 task whatever its count. */
    assert(scheduler_swaps(1, 1, 3, 50));
    assert(scheduler_swaps(2, 1, 3, 50));
}

static void test_scheduler_idle_worker_is_evaluated_on_every_tick(void)
{
    GameSession session;
    PadCatalog catalog;
    GameFloaterStart *worker;
    int slot;

    make_scheduler_island(&session, &catalog, 1);
    worker = &session.floaters[0];
    worker->carried_resource_code = 1;
    slot = add_delivery_row(&session, 1, 1);
    /* Tick 7 is not floater 0's ten-tick phase, but state 0 always runs
       FUN_0042219e. A wandering worker (state 0x0e) waits for its phase. */
    session.simulation_tick = 7;
    worker->movement_state = 0x0e;
    worker->active_order_action = 0x0e;
    worker->has_wander_order = 1;
    game_session_assign_local_resource_tasks(&session, NULL);
    assert(worker->linked_task_slot == -1);
    worker->movement_state = 0;
    game_session_assign_local_resource_tasks(&session, NULL);
    assert(worker->linked_task_slot == slot);
}

static void test_scheduler_has_no_per_row_worker_cap(void)
{
    GameSession session;
    PadCatalog catalog;
    GameRuntimeLocation *target;
    unsigned int index;
    int slot;

    make_scheduler_island(&session, &catalog, 6);
    target = &session.islands[0].locations[SCHED_TARGET];
    slot = add_delivery_row(&session, 1, 1);
    /* An UPGRADE row (item 1, site handle) one unit from its 20-unit goal:
       the old remake refused workers once stock + assigned reached 20. */
    target->upgrade_task_handle = (int16_t)slot;
    target->resource_stock[GAME_RESOURCE_BUILD_TONE] = 19;
    for (index = 0; index < 6; ++index)
        session.floaters[index].carried_resource_code = 1;
    game_session_assign_local_resource_tasks(&session, NULL);
    assert(workers_on_slot(&session, slot) == 6);
    assert(session.pending_events[slot].assigned_floater_count == 6);
}

static void test_scheduler_admits_many_workers_to_one_construction(void)
{
    GameSession session;
    PadCatalog catalog;
    int slot;

    make_scheduler_island(&session, &catalog, 4);
    slot = game_session_pending_event_add(&session, 0, 0, 5, 0, SCHED_PAD,
                                          0x25);
    /* Cost 2 but four workers: FUN_00422031 case 5 has no cost reservation. */
    game_session_assign_local_resource_tasks(&session, &catalog);
    assert(workers_on_slot(&session, slot) == 4);
    assert(session.floaters[0].order_resource_code == 1);
}

/* --- Task legs (FUN_004211bb) -------------------------------------------- */

static void test_construction_leg_follows_pad_state(void)
{
    GameSession session;
    PadCatalog catalog;
    GameRuntimeLocation *pad;
    GameFloaterStart *worker;
    int slot;

    make_scheduler_island(&session, &catalog, 1);
    pad = &session.islands[0].locations[SCHED_PAD];
    worker = &session.floaters[0];
    slot = game_session_pending_event_add(&session, 0, 0, 5, 0, SCHED_PAD,
                                          0x25);

    /* Empty-handed, pad short of tone: fetch at the Hall (state 3). */
    game_session_assign_local_resource_tasks(&session, &catalog);
    assert(worker->linked_task_slot == slot && worker->movement_state == 0);
    game_session_advance_local_resource_task(&session, &catalog, worker);
    assert(worker->movement_state == 3);
    assert(worker->order_source_island == 0);
    assert(worker->order_source_location == SCHED_HALL);
    assert(worker->has_move_order == 1);

    /* Carrying Build Tone: deposit on the pad (state 4). */
    worker->movement_state = 0;
    worker->has_move_order = 0;
    worker->carried_resource_code = 1;
    game_session_advance_local_resource_task(&session, &catalog, worker);
    assert(worker->movement_state == 4);

    /* Pad complete (FUN_00452794): build (state 5) even with tone in hand. */
    worker->movement_state = 0;
    worker->has_move_order = 0;
    pad->resource_stock[GAME_RESOURCE_BUILD_TONE] = 2;
    game_session_advance_local_resource_task(&session, &catalog, worker);
    assert(worker->movement_state == 5);
    assert(worker->linked_task_slot == slot);
}

static void test_construction_leg_deletes_an_unbuildable_row(void)
{
    GameSession session;
    PadCatalog catalog;
    GameFloaterStart *worker;
    int slot;

    make_scheduler_island(&session, &catalog, 1);
    worker = &session.floaters[0];
    worker->carried_resource_code = 1;
    slot = game_session_pending_event_add(&session, 0, 0, 5, 0, SCHED_PAD,
                                          0x25);
    game_session_assign_local_resource_tasks(&session, &catalog);
    assert(worker->linked_task_slot == slot);

    /* FUN_004526de now fails (upkeep over budget): FUN_004211bb detaches the
       worker and deletes the row; the cargo stays with the worker. */
    session.economy[0].source_maintenance_budget = 0;
    game_session_advance_local_resource_task(&session, &catalog, worker);
    assert(session.pending_events[slot].active == 0);
    assert(session.pending_event_count == 0);
    assert(worker->linked_task_slot == -1);
    assert(worker->active_order_action == 0);
    assert(worker->carried_resource_code == 1);
    assert(worker->has_wander_order == 1);
}

static void run_scheduler_ticks(GameSession *session, const PadCatalog *catalog,
                                unsigned int first, unsigned int last)
{
    unsigned int tick;
    for (tick = first; tick <= last; ++tick) {
        session->simulation_tick = tick;
        game_session_update_construction_tasks(session, catalog);
        game_session_tick_floater_moves(session, tick, catalog);
    }
}

static void test_delivery_worker_loops_on_its_task(void)
{
    GameSession session;
    PadCatalog catalog;
    GameRuntimeLocation *hall;
    GameFloaterStart *worker;
    unsigned int tick;
    unsigned int deposits = 0;
    int16_t previous_cargo = 0;
    int slot;

    make_scheduler_island(&session, &catalog, 1);
    hall = &session.islands[0].locations[SCHED_HALL];
    worker = &session.floaters[0];
    slot = add_delivery_row(&session, 1, 1);

    /* Hall -> target round trips. The deposit credits the player's Hall
       (game_session_credit_resource), so the stock stays at 10 minus cargo.
       The worker never leaves the row between trips (step +0x46 loops). */
    for (tick = 1; tick <= 3000; ++tick) {
        run_scheduler_ticks(&session, &catalog, tick, tick);
        if (tick > 1) {
            assert(worker->linked_task_slot == slot);
            assert(session.pending_events[slot].assigned_floater_count == 1);
        }
        if (previous_cargo == 1 && worker->carried_resource_code == 0)
            ++deposits;
        previous_cargo = worker->carried_resource_code;
        assert(hall->resource_stock[GAME_RESOURCE_BUILD_TONE] +
               (worker->carried_resource_code == 1 ? 1 : 0) == 10);
    }
    assert(deposits >= 3);
}

static void test_refused_deposit_detaches_with_cargo(void)
{
    GameSession session;
    PadCatalog catalog;
    GameFloaterStart *worker;
    unsigned int tick;
    int slot;
    int detached = 0;

    make_scheduler_island(&session, &catalog, 1);
    worker = &session.floaters[0];
    worker->carried_resource_code = 1;
    slot = add_delivery_row(&session, 1, 1);
    /* No Hall: game_session_credit_resource refuses the deposit. */
    session.economy[0].hall_location_index = 99;

    /* Step 1 sees the cargo still held, step 2 detaches (FUN_00421ec1(-1)). */
    for (tick = 1; tick <= 500 && !detached; ++tick) {
        int was_linked = worker->linked_task_slot == slot;
        run_scheduler_ticks(&session, &catalog, tick, tick);
        if (was_linked && worker->linked_task_slot == -1) {
            detached = 1;
            assert(worker->carried_resource_code == 1);
            assert(worker->active_order_action == 0);
            assert(worker->task_step == 0);
            assert(session.pending_events[slot].active != 0);
            assert(session.pending_events[slot].assigned_floater_count == 0);
        } else if (was_linked && worker->linked_task_slot == slot &&
                   worker->task_step == 2) {
            assert(worker->movement_state == 0);
        }
    }
    assert(detached);
}

static void test_cancelled_row_detaches_its_workers_with_cargo(void)
{
    GameSession session;
    PadCatalog catalog;
    GamePendingEvent expected;
    unsigned int index;
    int slot;

    make_scheduler_island(&session, &catalog, 3);
    for (index = 0; index < 3; ++index)
        session.floaters[index].carried_resource_code = 1;
    slot = add_delivery_row(&session, 1, 1);
    game_session_assign_local_resource_tasks(&session, NULL);
    assert(workers_on_slot(&session, slot) == 3);

    /* FUN_00466533 detaches every worker of the row; +0x18 is kept. */
    expected = session.pending_events[slot];
    assert(game_session_dispatch_task_command(&session, (uint8_t)slot, 12,
                                              &expected));
    for (index = 0; index < 3; ++index) {
        assert(session.floaters[index].linked_task_slot == -1);
        assert(session.floaters[index].active_order_action == 0);
        assert(session.floaters[index].carried_resource_code == 1);
    }
}

static void test_two_workers_build_one_pad_and_keep_surplus_cargo(void)
{
    GameSession session;
    PadCatalog catalog;
    GameRuntimeLocation *pad;
    GameRuntimeLocation *hall;
    unsigned int tick;
    unsigned int index;
    unsigned int carried = 0;
    int max_workers = 0;
    int slot;

    make_scheduler_island(&session, &catalog, 2);
    pad = &session.islands[0].locations[SCHED_PAD];
    hall = &session.islands[0].locations[SCHED_HALL];
    session.floaters[1].x = 120;
    slot = game_session_pending_event_add(&session, 0, 0, 5, 0, SCHED_PAD,
                                          0x25);

    for (tick = 1; tick < 4000 && pad->owner_id == -1; ++tick) {
        run_scheduler_ticks(&session, &catalog, tick, tick);
        if (session.pending_events[slot].active != 0 &&
            session.pending_events[slot].assigned_floater_count > max_workers)
            max_workers = session.pending_events[slot].assigned_floater_count;
    }
    assert(tick < 4000);
    /* Both workers served the same CONSTR row at once. */
    assert(max_workers == 2);
    assert(pad->owner_id == 0);
    assert(pad->record_value_10 == 0x25);
    assert(session.pending_events[slot].active == 0);
    for (index = 0; index < 2; ++index) {
        assert(session.floaters[index].linked_task_slot == -1);
        if (session.floaters[index].carried_resource_code == 1) ++carried;
    }
    /* Cost 2 left the Hall; units fetched after the pad completed stay in
       the workers' hands (or went to the pad before it was placed). */
    assert(hall->resource_stock[GAME_RESOURCE_BUILD_TONE] + carried <= 8);
}

/* --- Tasks on another island (FUN_004210a9 crossings) -------------------- */

enum {
    SCHED_BRIDGE_0 = 3,  /* island 0: bridge toward island 1 */
    SCHED_REMOTE_PAD = 0,
    SCHED_REMOTE_SITE = 1,
    SCHED_BRIDGE_1 = 2   /* island 1: bridge toward island 0 */
};

static void set_bridge(GameRuntimeLocation *bridge, int32_t neighbor,
                       uint16_t x, uint16_t y)
{
    bridge->renderer_class = 2;
    bridge->source_flags = 1;
    bridge->bridge_neighbor_island = neighbor;
    bridge->owner_id = -1;
    bridge->upgrade_task_handle = -1;
    bridge->x = x;
    bridge->y = y;
}

/* make_scheduler_island plus island 1, joined by an active bridge pair and
   accessible to player 0. Island 1 holds an empty pad and an empty site; it
   has no Build Tone source, so every fetch leg returns to the Hall. */
static void make_bridged_islands(GameSession *session, PadCatalog *catalog,
                                 unsigned int worker_count)
{
    GameRuntimeIsland *remote;
    GameRuntimeLocation *pad;
    GameRuntimeLocation *site;
    unsigned int index;

    make_scheduler_island(session, catalog, worker_count);
    session->island_count = 2;
    session->islands[0].location_count = 4;
    session->islands[0].access_mask = 1;
    set_bridge(&session->islands[0].locations[SCHED_BRIDGE_0], 1, 600, 150);

    remote = &session->islands[1];
    remote->location_count = 3;
    remote->access_mask = 1;
    remote->floater_max_x[0] = 0x9ff;
    pad = &remote->locations[SCHED_REMOTE_PAD];
    pad->record_value_10 = 1;
    pad->record_value_24 = 5;
    pad->owner_id = -1;
    pad->source_value_14 = -1;
    pad->source_value_22 = 1;
    pad->upgrade_task_handle = -1;
    pad->x = 300;
    pad->y = 120;
    site = &remote->locations[SCHED_REMOTE_SITE];
    site->owner_id = -1;
    site->source_location_slot_18 = -1;
    site->upgrade_task_handle = -1;
    site->x = 400;
    site->y = 120;
    set_bridge(&remote->locations[SCHED_BRIDGE_1], 0, 100, 150);

    for (index = 0; index < worker_count; ++index) {
        session->floaters[index].handoff_target_island = UINT8_MAX;
        session->floaters[index].handoff_departure_location = -1;
    }
}

/* Runs ticks until `done` or the limit; returns the first tick past it. */
static unsigned int run_until_island(GameSession *session,
                                     const PadCatalog *catalog,
                                     const GameFloaterStart *worker,
                                     unsigned int first, uint8_t island)
{
    unsigned int tick;
    for (tick = first; tick < first + 2000 && worker->island_index != island;
         ++tick)
        run_scheduler_ticks(session, catalog, tick, tick);
    assert(worker->island_index == island);
    return tick;
}

static void test_remote_construction_is_built_through_the_bridge(void)
{
    GameSession session;
    PadCatalog catalog;
    GameRuntimeLocation *pad;
    unsigned int tick;
    int crossed = 0;
    int slot;

    make_bridged_islands(&session, &catalog, 1);
    pad = &session.islands[1].locations[SCHED_REMOTE_PAD];
    slot = game_session_pending_event_add(&session, 0, 1, 5, 0,
                                          SCHED_REMOTE_PAD, 0x25);
    for (tick = 1; tick < 6000 && pad->owner_id == -1; ++tick) {
        run_scheduler_ticks(&session, &catalog, tick, tick);
        if (session.floaters[0].island_index == 1) crossed = 1;
    }
    /* Cost 2 from the Hall on island 0: two round trips over the bridge. */
    assert(tick < 6000);
    assert(crossed);
    assert(pad->owner_id == 0);
    assert(pad->record_value_10 == 0x25);
    assert(session.pending_events[slot].active == 0);
    assert(session.islands[0].locations[SCHED_HALL]
               .resource_stock[GAME_RESOURCE_BUILD_TONE] == 8);
    assert(session.floaters[0].linked_task_slot == -1);
}

static void test_crossing_worker_keeps_its_task_and_replans_on_arrival(void)
{
    GameSession session;
    PadCatalog catalog;
    GameFloaterStart *worker;
    unsigned int tick;
    int slot;

    make_bridged_islands(&session, &catalog, 1);
    worker = &session.floaters[0];
    worker->carried_resource_code = 1;
    slot = game_session_pending_event_add(&session, 0, 1, 5, 0,
                                          SCHED_REMOTE_PAD, 0x25);
    game_session_assign_local_resource_tasks(&session, &catalog);
    assert(worker->linked_task_slot == slot);
    game_session_advance_local_resource_task(&session, &catalog, worker);

    /* FUN_004210a9 writes only +0x2c/+0x30/+0x32: the task, its target and
       step stay; the port parks action 4 as resume action 4, state 0. */
    assert(worker->movement_state == 0x11);
    assert(worker->active_order_action == 9);
    assert(worker->handoff_target_island == 1);
    assert(worker->handoff_departure_location == SCHED_BRIDGE_0);
    assert(worker->handoff_resume_action == 4);
    assert(worker->handoff_resume_state == 0);
    assert(worker->order_target_island == 1);
    assert(worker->order_target_location == SCHED_REMOTE_PAD);
    assert(worker->task_step == 0);

    for (tick = 1; tick < 2000 && worker->movement_state == 0x11; ++tick) {
        run_scheduler_ticks(&session, &catalog, tick, tick);
        assert(worker->linked_task_slot == slot);
        assert(session.pending_events[slot].assigned_floater_count == 1);
        assert(worker->carried_resource_code == 1);
    }
    assert(worker->island_index == 1);
    /* State 0 again: FUN_004211bb sends the carrier to the pad (state 4). */
    run_scheduler_ticks(&session, &catalog, tick, tick);
    assert(worker->active_order_action == 4);
    assert(worker->movement_state == 4);
    assert(worker->linked_task_slot == slot);
}

static void test_remote_worker_crosses_back_to_fetch(void)
{
    GameSession session;
    PadCatalog catalog;
    GameFloaterStart *worker;
    unsigned int tick;
    int slot;

    make_bridged_islands(&session, &catalog, 1);
    worker = &session.floaters[0];
    worker->island_index = 1;
    worker->x = 300;
    slot = game_session_pending_event_add(&session, 0, 1, 5, 0,
                                          SCHED_REMOTE_PAD, 0x25);

    /* FUN_00420dbd finds no Build Tone on island 1 and returns the Hall on
       island 0: the worker crosses, then fetches there (state 3). */
    run_scheduler_ticks(&session, &catalog, 1, 1);
    assert(worker->linked_task_slot == slot);
    assert(worker->movement_state == 0x11);
    assert(worker->handoff_target_island == 0);
    assert(worker->handoff_departure_location == SCHED_BRIDGE_1);
    tick = run_until_island(&session, &catalog, worker, 2, 0);
    for (; tick < 2000 && worker->movement_state == 0x11; ++tick)
        run_scheduler_ticks(&session, &catalog, tick, tick);
    run_scheduler_ticks(&session, &catalog, tick, tick);
    assert(worker->movement_state == 3);
    assert(worker->order_source_island == 0);
    assert(worker->order_source_location == SCHED_HALL);
    assert(worker->linked_task_slot == slot);
}

static void test_non_adjacent_island_is_reached_in_one_crossing(void)
{
    GameSession session;
    PadCatalog catalog;
    GameFloaterStart *worker;
    GameRuntimeLocation *far_pad;
    unsigned int tick;
    int visited_middle = 0;
    int slot;

    /* Islands 0-1-2 in a chain; the pad is on island 2. */
    make_bridged_islands(&session, &catalog, 1);
    session.island_count = 3;
    session.islands[2].location_count = 2;
    session.islands[2].access_mask = 1;
    session.islands[2].floater_max_x[0] = 0x9ff;
    far_pad = &session.islands[2].locations[0];
    *far_pad = session.islands[1].locations[SCHED_REMOTE_PAD];
    set_bridge(&session.islands[2].locations[1], 1, 200, 150);
    worker = &session.floaters[0];
    worker->carried_resource_code = 1;
    slot = game_session_pending_event_add(&session, 0, 2, 5, 0, 0, 0x25);

    /* FUN_004210a9 takes the nearest active bridge (no endpoint toward 2);
       at t = 0x78 the native writes +0x0e = +0x30, so the floater lands on
       island 2 without passing island 1. No reciprocal marker: 500 hold. */
    run_scheduler_ticks(&session, &catalog, 1, 1);
    assert(worker->linked_task_slot == slot);
    assert(worker->handoff_target_island == 2);
    assert(worker->handoff_departure_location == SCHED_BRIDGE_0);
    for (tick = 2; tick < 3000 && worker->island_index == 0; ++tick) {
        run_scheduler_ticks(&session, &catalog, tick, tick);
        if (worker->movement_state == 0x11 && worker->order_timer > 320)
            assert(worker->order_timer <= 620);
    }
    for (; tick < 3000 && worker->island_index != 2; ++tick) {
        if (worker->island_index == 1) visited_middle = 1;
        run_scheduler_ticks(&session, &catalog, tick, tick);
    }
    assert(!visited_middle);
    assert(worker->island_index == 2);
    assert(worker->x == 200 && worker->y == 120);
}

static void test_remote_artifact_row_is_delivered(void)
{
    GameSession session;
    PadCatalog catalog;
    GameFloaterStart *worker;
    GameRuntimeLocation *site;
    unsigned int tick;
    int slot;

    make_bridged_islands(&session, &catalog, 1);
    session.islands[0].locations[SCHED_HALL].source_value_14 = 0;
    session.economy[0].inventory_count[6 - GAME_INVENTORY_ITEM_FIRST_ID] = 1;
    site = &session.islands[1].locations[SCHED_REMOTE_SITE];
    worker = &session.floaters[0];
    slot = game_session_pending_event_add(&session, 0, 1, 4, 0,
                                          SCHED_REMOTE_SITE, 6);

    /* FUN_00422031 has no island test: the artifact row on island 1 takes
       the worker on island 0 (it was refused before, which also hid every
       later row from that worker). */
    run_scheduler_ticks(&session, &catalog, 1, 1);
    assert(worker->linked_task_slot == slot);
    assert(worker->movement_state == 3);
    for (tick = 2; tick < 3000 && session.pending_events[slot].active != 0;
         ++tick)
        run_scheduler_ticks(&session, &catalog, tick, tick);
    assert(tick < 3000);
    assert(worker->island_index == 1);
    assert(worker->carried_resource_code == 0);
    assert(worker->linked_task_slot == -1);
    assert(session.economy[0].inventory_count[6 - GAME_INVENTORY_ITEM_FIRST_ID] == 0);
    assert(site->record_value_10 != 0);
}

static void test_unreachable_routed_row_does_not_hide_later_rows(void)
{
    GameSession session;
    PadCatalog catalog;
    GameFloaterStart *worker;
    int charge;
    int build;

    make_scheduler_island(&session, &catalog, 1);
    worker = &session.floaters[0];
    /* A CHARGE row whose source no longer names it (stale handle): the
       routed leg fails. The later CONSTR row must still take the worker. */
    session.islands[0].locations[SCHED_HALL].source_location_slot_18 = 0;
    session.islands[0].locations[SCHED_HALL].charge_staff_task_handle = -1;
    charge = game_session_pending_event_add(&session, 0, 0, 0x0b, SCHED_HALL,
                                            SCHED_HALL, 0);
    build = game_session_pending_event_add(&session, 0, 0, 5, 0, SCHED_PAD,
                                           0x25);
    assert(charge >= 0 && build > charge);
    game_session_assign_local_resource_tasks(&session, &catalog);
    assert(worker->linked_task_slot == build);
    assert(session.pending_events[charge].assigned_floater_count == 0);
    assert(session.pending_events[build].assigned_floater_count == 1);
}

static void test_row_cancelled_during_a_crossing_frees_the_worker(void)
{
    GameSession session;
    PadCatalog catalog;
    GameFloaterStart *worker;
    GamePendingEvent expected;
    unsigned int tick;
    int slot;

    make_bridged_islands(&session, &catalog, 1);
    worker = &session.floaters[0];
    worker->carried_resource_code = 1;
    slot = game_session_pending_event_add(&session, 0, 1, 5, 0,
                                          SCHED_REMOTE_PAD, 0x25);
    for (tick = 1; tick < 500 && !(worker->movement_state == 0x11 &&
                                   worker->order_timer > 10); ++tick)
        run_scheduler_ticks(&session, &catalog, tick, tick);
    assert(worker->movement_state == 0x11 && worker->island_index == 0);

    /* FUN_00466533 -> FUN_00420669 -> FUN_00421ec1(-1): state 0 where the
       floater stands; the cargo stays. */
    expected = session.pending_events[slot];
    assert(game_session_dispatch_task_command(&session, (uint8_t)slot, 12,
                                              &expected));
    assert(worker->linked_task_slot == -1);
    assert(worker->movement_state == 0);
    assert(worker->active_order_action == 0);
    assert(worker->handoff_target_island == UINT8_MAX);
    assert(worker->handoff_departure_location == -1);
    assert(worker->island_index == 0);
    assert(worker->carried_resource_code == 1);
    for (; tick < 1500; ++tick)
        run_scheduler_ticks(&session, &catalog, tick, tick);
    assert(worker->island_index == 0);
    assert(worker->movement_state != 0x11);
}

/* Every row's attach count equals the workers linked to it: a leaked count
   would make FUN_0042219e's count rule move workers for no reason. */
static void assert_task_counts_match_links(const GameSession *session)
{
    unsigned int slot;
    for (slot = 0; slot < GAME_SESSION_MAX_PENDING_EVENTS; ++slot) {
        if (session->pending_events[slot].active == 0) continue;
        assert(session->pending_events[slot].assigned_floater_count ==
               (int)workers_on_slot(session, (int)slot));
    }
}

static void test_new_row_does_not_take_a_crossing_worker(void)
{
    GameSession session;
    PadCatalog catalog;
    GameFloaterStart *worker;
    unsigned int tick;
    int remote;
    int local;

    make_bridged_islands(&session, &catalog, 1);
    worker = &session.floaters[0];
    worker->carried_resource_code = 1;
    remote = game_session_pending_event_add(&session, 0, 1, 5, 0,
                                            SCHED_REMOTE_PAD, 0x25);
    run_scheduler_ticks(&session, &catalog, 1, 1);
    assert(worker->linked_task_slot == remote);
    assert(worker->movement_state == 0x11);

    /* A local row added while the worker walks to the bridge: its count 0
       is not below 1 - 1, so FUN_0042219e keeps the worker on its row
       through the walk, the crossing and the replanning on arrival. */
    local = game_session_pending_event_add(&session, 0, 0, 5, 0, SCHED_PAD,
                                           0x25);
    assert(local > remote);
    for (tick = 2; tick < 2000 && worker->island_index == 0; ++tick) {
        run_scheduler_ticks(&session, &catalog, tick, tick);
        assert(worker->linked_task_slot == remote);
        assert(worker->carried_resource_code == 1);
    }
    for (; tick < 2000 && worker->movement_state == 0x11; ++tick)
        run_scheduler_ticks(&session, &catalog, tick, tick);
    run_scheduler_ticks(&session, &catalog, tick, tick);
    assert(worker->island_index == 1);
    assert(worker->linked_task_slot == remote);
    assert(worker->movement_state == 4);
    assert(session.pending_events[local].assigned_floater_count == 0);
}

static void test_workers_keep_their_rows_across_bridges(void)
{
    GameSession session;
    PadCatalog catalog;
    int16_t settled[2];
    unsigned int tick;
    unsigned int index;
    unsigned int crossings = 0;
    uint8_t previous_island[2] = {0, 0};
    int remote;
    int local;

    /* Two pads of cost 6, one per island, two workers. The first scan puts
       both on the first row; the next re-evaluation moves one to the empty
       row (0 < 2 - 1). From then on the rows are balanced 1/1 and no worker
       may change row, whatever its leg, crossing or cargo, until a row ends. */
    make_bridged_islands(&session, &catalog, 2);
    catalog.items[0x25].building_tone_cost = 6;
    /* The local pad (item 0x26) costs more, so it outlasts several remote
       round trips. */
    catalog.item_count = 0x27;
    catalog.items[0x26] = catalog.items[0x25];
    catalog.items[0x26].item_id = 0x26;
    catalog.items[0x26].building_tone_cost = 30;
    session.islands[0].locations[SCHED_HALL]
        .resource_stock[GAME_RESOURCE_BUILD_TONE] = 50;
    session.floaters[1].x = 120;
    remote = game_session_pending_event_add(&session, 0, 1, 5, 0,
                                            SCHED_REMOTE_PAD, 0x25);
    local = game_session_pending_event_add(&session, 0, 0, 5, 0, SCHED_PAD,
                                           0x26);
    for (tick = 1; tick <= 20; ++tick) {
        run_scheduler_ticks(&session, &catalog, tick, tick);
        assert_task_counts_match_links(&session);
    }
    assert(workers_on_slot(&session, remote) == 1);
    assert(workers_on_slot(&session, local) == 1);
    settled[0] = session.floaters[0].linked_task_slot;
    settled[1] = session.floaters[1].linked_task_slot;

    for (; tick < 8000; ++tick) {
        run_scheduler_ticks(&session, &catalog, tick, tick);
        assert_task_counts_match_links(&session);
        /* A finished row frees its worker: that is a reason to move. */
        if (session.pending_events[remote].active == 0 ||
            session.pending_events[local].active == 0) break;
        for (index = 0; index < 2; ++index) {
            const GameFloaterStart *worker = &session.floaters[index];
            assert(worker->linked_task_slot == settled[index]);
            if (worker->island_index != previous_island[index]) ++crossings;
            previous_island[index] = worker->island_index;
        }
    }
    assert(tick < 8000);
    /* The remote builder fetched from the Hall: several round trips. */
    assert(crossings >= 4);
}

static void test_worker_scheduler(void)
{
    test_scheduler_ignores_the_task_island();
    test_scheduler_admits_only_with_cargo_or_a_source();
    test_scheduler_charge_row_needs_subtype_zero();
    test_scheduler_priority_three_masks_other_rows();
    test_scheduler_count_rule_by_class();
    test_scheduler_class_three_row_takes_any_class_one_worker();
    test_scheduler_idle_worker_is_evaluated_on_every_tick();
    test_scheduler_has_no_per_row_worker_cap();
    test_scheduler_admits_many_workers_to_one_construction();
    test_construction_leg_follows_pad_state();
    test_construction_leg_deletes_an_unbuildable_row();
    test_delivery_worker_loops_on_its_task();
    test_refused_deposit_detaches_with_cargo();
    test_cancelled_row_detaches_its_workers_with_cargo();
    test_two_workers_build_one_pad_and_keep_surplus_cargo();
    test_remote_construction_is_built_through_the_bridge();
    test_crossing_worker_keeps_its_task_and_replans_on_arrival();
    test_remote_worker_crosses_back_to_fetch();
    test_non_adjacent_island_is_reached_in_one_crossing();
    test_remote_artifact_row_is_delivered();
    test_unreachable_routed_row_does_not_hide_later_rows();
    test_row_cancelled_during_a_crossing_frees_the_worker();
    test_new_row_does_not_take_a_crossing_worker();
    test_workers_keep_their_rows_across_bridges();
}
