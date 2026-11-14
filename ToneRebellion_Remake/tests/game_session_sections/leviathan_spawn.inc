/* Leviathan unit spawn rate: FUN_00460460 per-marker rate (+0x32) and the
   FUN_00450a71 threshold for class-1 items 6..9 (REA 2026-11-14, see
   docs/building-rendering.md "Spawn-rate recheck"). */

static void add_leviathan_unit(GameSession *session, unsigned int index,
                               uint8_t island, uint8_t subtype)
{
    GameFloaterStart *unit = &session->floaters[index];
    memset(unit, 0, sizeof(*unit));
    unit->is_active = 1;
    unit->island_index = island;
    unit->type_index = 4;
    unit->owner_slot = 4;
    unit->source_subtype = subtype;
    unit->current_hit_points = 20;
    unit->max_hit_points = 20;
    if (index >= session->floater_count)
        session->floater_count = (uint16_t)(index + 1U);
}

static void test_leviathan_rate_follows_tier_difficulty_and_marker_count(void)
{
    static GameSession session;
    GameRuntimeIsland *island;

    /* Slot 9 at difficulty 2: tier min(9 / 4, 2) = 2. Two Leviathan markers
       out of three class-1 sites: ((2 + 2) * 2 + 10) / 2 = 9 per tick. */
    memset(&session, 0, sizeof(session));
    session.island_count = 16;
    session.config.difficulty = 2;
    island = &session.islands[9];
    island->location_count = 3;
    make_leviathan_marker(&island->locations[0], 1, 6);
    make_leviathan_marker(&island->locations[1], 1, 7);
    make_leviathan_marker(&island->locations[2], 1, 0);
    island->locations[2].owner_id = -1;
    island->locations[2].source_value_14 = -1;
    game_session_recalculate_leviathan_island(&session, 9);
    assert(island->leviathan_marker_count == 2);
    assert(island->leviathan_remaining_markers == 1);
    assert(island->leviathan_site_budget == 2 * (2 * 2 + 4));
    assert(island->leviathan_admissible == 1);
    assert(island->leviathan_floater_budget == 4);
    assert(island->locations[0].source_value_32 == 9);
    assert(island->locations[1].source_value_32 == 9);
    assert(island->locations[2].source_value_32 == 1); /* not a marker */

    /* The tier is capped by the difficulty: slot 14 (Friid in a large world)
       at difficulty 1 uses tier 1: ((1 + 1) * 2 + 10) / 2 = 7. */
    session.config.difficulty = 1;
    session.islands[14] = *island;
    game_session_recalculate_leviathan_island(&session, 14);
    assert(session.islands[14].locations[0].source_value_32 == 7);

    /* A growing item-5 pool marker keeps rate 1 whatever the interval. */
    island->locations[1].record_value_10 = 5;
    session.config.difficulty = 2;
    game_session_recalculate_leviathan_island(&session, 9);
    assert(island->locations[0].source_value_32 == 9);
    assert(island->locations[1].source_value_32 == 1);
}

static void test_leviathan_contaminated_sites_use_up_the_site_budget(void)
{
    static GameSession session;
    GameRuntimeIsland *island;
    unsigned int index;

    /* Slot 0, difficulty 0: one marker allows 1 * (0 * 2 + 4) = 4 sites.
       Each class-0 site the Leviathan owns (a spore-contaminated pad, a
       defence tower) takes one. */
    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    island = &session.islands[0];
    island->location_count = 4;
    make_leviathan_marker(&island->locations[0], 1, 6);
    for (index = 1; index < 4; ++index) {
        make_leviathan_marker(&island->locations[index], 0, 0);
        island->locations[index].construction_site_size = 0;
    }
    game_session_recalculate_leviathan_island(&session, 0);
    assert(island->leviathan_site_budget == 4 - 3);

    /* Spore subtype 9 units never count toward the unit budget. */
    add_leviathan_unit(&session, 0, 0, 9);
    add_leviathan_unit(&session, 1, 0, 10);
    game_session_recalculate_leviathan_island(&session, 0);
    assert(island->leviathan_floater_count == 1);
    assert(island->leviathan_floater_budget == 2 - 1);
}

static void test_leviathan_rate_stays_zero_after_a_kill_until_recalculated(void)
{
    static GameSession session;
    GameRuntimeIsland *island;
    unsigned int index;

    /* One marker and no free class-1 site, four class-0 Leviathan sites (the
       whole site budget) and two units (the difficulty-0 table): every budget
       is spent, so FUN_00460460 writes rate 0. */
    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    island = &session.islands[0];
    island->location_count = 5;
    make_leviathan_marker(&island->locations[0], 1, 6);
    for (index = 1; index < 5; ++index)
        make_leviathan_marker(&island->locations[index], 0, 0x10);
    add_leviathan_unit(&session, 0, 0, 10);
    add_leviathan_unit(&session, 1, 0, 11);
    game_session_recalculate_leviathan_island(&session, 0);
    assert(island->leviathan_remaining_markers == 0);
    assert(island->leviathan_site_budget == 0);
    assert(island->leviathan_floater_budget == 0);
    assert(island->locations[0].source_value_32 == 0);

    /* A unit dying does not reach FUN_00460460 in the original
       (FUN_004204bc -> flag 8 -> FUN_00467101): the rate stays 0. */
    game_session_retire_floater(&session, 1);
    assert(island->locations[0].source_value_32 == 0);

    /* The next site event recomputes it: one unit below the cap, the single
       marker gets ((0 + 0) * 2 + 10) / 1 = 10 per tick again. */
    game_session_recalculate_leviathan_island(&session, 0);
    assert(island->leviathan_floater_budget == 1);
    assert(island->locations[0].source_value_32 == 10);
}

/* Ticks a lone class-1 item-6 spawner whose cadence starts two ticks below
   the threshold `expected` and checks production starts exactly there. */
static void assert_leviathan_spawn_threshold(GameSession *session,
                                             int expected)
{
    PadCatalog pads;
    BuildingRenderCatalog buildings;
    FloaterCatalog floaters = {0};
    GameRuntimeLocation *spawner = &session->islands[0].locations[0];
    unsigned int subtype;

    for (subtype = 9; subtype <= 17; ++subtype) {
        floaters.rows[subtype + 27U].hit_points = 20;
        floaters.rows[subtype + 27U].attack_strength = 3;
        floaters.rows[subtype + 27U].movement_speed = 2;
    }
    make_leviathan_pads(&pads);
    make_leviathan_buildings(&buildings);
    spawner->source_flags = 0x001U;
    spawner->source_value_32 = 1;
    spawner->charge_source_value_30 = (uint16_t)(expected - 2);
    session->islands[0].leviathan_floater_budget = 6;
    session->islands[0].leviathan_site_budget = 1;

    game_session_tick_item_animations_with_floaters(session, &buildings,
                                                    &floaters, &pads);
    assert((spawner->source_flags & 0x002U) == 0);
    assert(spawner->charge_source_value_30 == (uint16_t)(expected - 1));
    game_session_tick_item_animations_with_floaters(session, &buildings,
                                                    &floaters, &pads);
    assert((spawner->source_flags & 0x002U) != 0);
    assert(spawner->charge_source_value_30 == 0);
}

static void test_leviathan_spawn_threshold_follows_difficulty_time_and_pools(void)
{
    static GameSession session;
    GameRuntimeIsland *island;
    unsigned int index;

    /* Difficulty 1: 10000 - 400 = 9600, no time or visible-pool term. */
    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    session.config.difficulty = 1;
    session.simulation_tick = 400000U;
    island = &session.islands[0];
    island->location_count = 1;
    make_leviathan_marker(&island->locations[0], 1, 6);
    assert_leviathan_spawn_threshold(&session, 9600);

    /* Difficulty 2 at tick 150000 with two seen class-1 sites:
       (10000 - 800 - (150000 - 100000) / 100) * clamp(14 - 2 - 2) / 10
       = 8700. The tick advances by one before the comparison. */
    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    session.config.difficulty = 2;
    session.simulation_tick = 150000U - 1U;
    island = &session.islands[0];
    island->location_count = 2;
    make_leviathan_marker(&island->locations[0], 1, 6);
    make_leviathan_marker(&island->locations[1], 1, 0);
    island->locations[1].owner_id = -1;
    island->locations[1].source_value_14 = -1;
    assert_leviathan_spawn_threshold(&session, 8700);

    /* Difficulty 4, late game, six seen pools (counted up to five): the
       time term caps at 2400 and the factor floors at 5:
       (10000 - 1600 - 2400) * 5 / 10 = 3000. */
    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    session.config.difficulty = 4;
    session.simulation_tick = 400000U;
    island = &session.islands[0];
    island->location_count = 6;
    make_leviathan_marker(&island->locations[0], 1, 6);
    for (index = 1; index < 6; ++index) {
        make_leviathan_marker(&island->locations[index], 1, 0);
        island->locations[index].owner_id = -1;
        island->locations[index].source_value_14 = -1;
    }
    assert_leviathan_spawn_threshold(&session, 3000);

    /* An unseen pool (low byte of +0x22 clear) does not lower it: back to
       difficulty 2, tick 0, one seen site: 9200 * (14 - 2 - 1) / 10 capped
       at 10 = 9200. */
    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    session.config.difficulty = 2;
    island = &session.islands[0];
    island->location_count = 2;
    make_leviathan_marker(&island->locations[0], 1, 6);
    make_leviathan_marker(&island->locations[1], 1, 0);
    island->locations[1].owner_id = -1;
    island->locations[1].source_value_14 = -1;
    island->locations[1].source_value_22 = 0x0100;
    assert_leviathan_spawn_threshold(&session, 9200);
}
