/* Playtest fixes of 2026-11-11: cross-island casts, level-up return,
   melee counter-attacks and freed Leviathan sites. */

/* Island 0: the hall (0) and the casting building (1) from
   setup_cast_dispatch, plus a bridge (2) to island 1, which holds the
   other end (0). */
static void link_cast_islands(GameSession *session)
{
    GameRuntimeLocation *bridge;
    unsigned int player;
    session->island_count = 2;
    session->islands[0].location_count = 3;
    session->islands[1].location_count = 1;
    for (player = 0; player < 5; ++player) {
        session->islands[0].floater_max_x[player] = 0x9ff;
        session->islands[1].floater_max_x[player] = 0x9ff;
    }
    session->islands[0].locations[1].x = 600;
    session->islands[0].locations[1].y = 200;
    bridge = &session->islands[0].locations[2];
    bridge->renderer_class = 2;
    bridge->source_flags = 1;
    bridge->owner_id = -1;
    bridge->bridge_neighbor_island = 1;
    bridge->x = 900;
    bridge->y = 200;
    bridge = &session->islands[1].locations[0];
    bridge->renderer_class = 2;
    bridge->source_flags = 1;
    bridge->owner_id = -1;
    bridge->bridge_neighbor_island = 0;
    bridge->x = 300;
    bridge->y = 230;
}

static void test_caster_on_another_island_crosses_before_casting(void)
{
    /* FUN_004211bb crosses first for any action but 4/5/0xd/0x12 whose
       +0x40 differs from +0x0e, FA_Cast (0x13) included (ev_96f90fdc). */
    static GameSession session;
    PadCatalog pads;
    GameFloaterStart *caster;
    GameRuntimeLocation *building;
    unsigned int tick;
    int resumed = 0;

    make_pad_catalog(&pads);
    setup_cast_dispatch(&session, 1, 0, 20, 20);
    link_cast_islands(&session);
    building = &session.islands[0].locations[1];
    caster = &session.floaters[0];
    caster->island_index = 1;
    caster->x = 500;
    caster->y = 200;
    caster->movement_speed = 4;
    /* A real caster: trained (subtype 4) and linked to the building, so
       the worker scheduler leaves it alone. */
    caster->source_subtype = 4;
    caster->source_link_0c = 0;
    caster->charge_source_island = 0;
    caster->charge_source_location = 1;
    caster->linked_task_slot = -1;
    building->charge_recent_floater = -1;
    building->charge_staff_task_handle = -1;

    /* Owner 1 subtype 0x15 is kind 0, aimed at the building (island 0). */
    assert(game_session_queue_cast_action(&session, 1, 0, 1, 0x15));
    assert(game_session_dispatch_cast_actions(&session) == 1);
    assert(caster->movement_state == 0x11);
    assert(caster->handoff_resume_action == 0x13);
    assert(caster->handoff_target_island == 0);
    assert(caster->cast_spell_kind == 0);
    assert(building->resource_stock[GAME_RESOURCE_MAGIC_TONE] == 20 - 9);
    assert(building->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] == 20 - 7);

    for (tick = 1; tick <= 3000 && !resumed; ++tick) {
        game_session_tick_floater_moves(&session, tick, &pads);
        /* No cast while still on island 1. */
        if (caster->island_index == 1)
            assert(caster->movement_state != 0x13);
        if (caster->island_index == 0 && caster->movement_state == 0x13 &&
            caster->active_order_action == 0x13) resumed = 1;
    }
    assert(resumed);
    assert(caster->order_target_location == 1);
}

static void test_caster_without_route_keeps_the_pools(void)
{
    static GameSession session;
    GameRuntimeLocation *building;

    setup_cast_dispatch(&session, 1, 0, 20, 20);
    session.island_count = 2;
    session.islands[1].location_count = 1;
    session.islands[0].locations[1].x = 600;
    session.floaters[0].island_index = 1; /* no bridge between them */
    building = &session.islands[0].locations[1];
    assert(game_session_queue_cast_action(&session, 1, 0, 1, 0x15));
    assert(game_session_dispatch_cast_actions(&session) == 0);
    assert(building->resource_stock[GAME_RESOURCE_MAGIC_TONE] == 20);
    assert(building->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] == 20);
    assert(session.floaters[0].active_order_action == 0);
    assert(session.floaters[0].movement_state == 0);
}

static void test_level_up_candidate_returns_to_its_building(void)
{
    /* FUN_0042219e 0x4229b2..0x422a1d (ev_fe744a5b): the building's current
       floater (+0x4c) without 0x20 gets action 0xc; state 12 refills at the
       building (0x20), then FUN_0045cd75 raises the level at 251. */
    static GameSession session;
    static FloaterCatalog floaters;
    PadCatalog pads;
    BuildingRenderCatalog buildings = {0};
    GameRuntimeLocation *home;
    GameFloaterStart *trained;
    unsigned int tick;
    unsigned int index;
    int refilled = 0;

    make_pad_catalog(&pads);
    make_floater_catalog(&floaters);
    floaters.rows[1].hit_points = 9; /* type 0, subtype 1 */
    floaters.rows[1].max_attack_points = 4;
    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    session.islands[0].location_count = 1;
    for (index = 0; index < 5; ++index)
        session.islands[0].floater_max_x[index] = 0x9ff;
    home = school(&session, 0, 0, 600);
    home->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] = 50;
    home->source_value_32 = 251; /* one training tick reaches 251 */
    soldier(&session, 0, 0, 900, 0);
    trained = &session.floaters[0];
    trained->attack_level_flags = 0;
    trained->has_wander_order = 1;
    home->charge_floater_slots[0] = 0;
    home->charge_floater_count = 1;
    home->charge_recent_floater = 0; /* picked as level-up candidate */

    for (tick = 1; tick <= 2000 && !refilled; ++tick) {
        game_session_tick_floater_moves(&session, tick, &pads);
        if ((trained->source_runtime_flags & 0x20U) != 0) refilled = 1;
    }
    assert(refilled);
    assert(trained->x == home->x && trained->y == home->y);
    assert(trained->active_order_action == 0x0c);
    assert(home->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] == 40);

    game_session_tick_item_animations_with_floaters(&session, &buildings,
                                                    &floaters, &pads);
    assert((trained->attack_level_flags & 0x0fU) == 1);
    assert(home->charge_recent_floater == -1);
    assert(trained->active_order_action == 0);
    assert((trained->source_runtime_flags & 0x20U) == 0);
}

static void test_level_up_candidate_crosses_a_bridge_home(void)
{
    static GameSession session;
    PadCatalog pads;
    GameRuntimeLocation *home;
    GameRuntimeLocation *bridge;
    GameFloaterStart *trained;
    unsigned int tick;
    unsigned int index;
    int refilled = 0;

    make_pad_catalog(&pads);
    memset(&session, 0, sizeof(session));
    session.island_count = 2;
    session.islands[0].location_count = 2;
    session.islands[1].location_count = 1;
    for (index = 0; index < 5; ++index) {
        session.islands[0].floater_max_x[index] = 0x9ff;
        session.islands[1].floater_max_x[index] = 0x9ff;
    }
    home = school(&session, 0, 0, 600);
    home->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] = 50;
    bridge = &session.islands[0].locations[1];
    bridge->renderer_class = 2;
    bridge->source_flags = 1;
    bridge->owner_id = -1;
    bridge->bridge_neighbor_island = 1;
    bridge->x = 900;
    bridge->y = 200;
    bridge = &session.islands[1].locations[0];
    bridge->renderer_class = 2;
    bridge->source_flags = 1;
    bridge->owner_id = -1;
    bridge->bridge_neighbor_island = 0;
    bridge->x = 300;
    bridge->y = 230;
    soldier(&session, 0, 0, 700, 0);
    trained = &session.floaters[0];
    trained->island_index = 1;
    trained->attack_level_flags = 0;
    home->charge_floater_slots[0] = 0;
    home->charge_floater_count = 1;
    home->charge_recent_floater = 0;

    for (tick = 1; tick <= 4000 && !refilled; ++tick) {
        game_session_tick_floater_moves(&session, tick, &pads);
        if ((trained->source_runtime_flags & 0x20U) != 0) refilled = 1;
    }
    assert(refilled);
    assert(trained->island_index == 0);
    assert(trained->x == home->x);
}

static void test_held_floater_reaches_its_holder_and_strikes(void)
{
    /* FUN_0041e569 states 0xf/0x10 test arrival (0x41edf0) before the 0x411
       step skip (0x41ee8a, ev_89fd8492): a floater pinned in melee that
       answers its holder arrives, marks its own hold (0x40) and strikes,
       instead of staying in state 0xf for as long as the holder strikes. */
    static GameSession session;
    PadCatalog pads;
    GameFloaterStart *held;
    GameFloaterStart *holder;
    unsigned int index;
    unsigned int tick;
    int marked = 0;
    int struck = 0;

    make_pad_catalog(&pads);
    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    session.islands[0].location_count = 1;
    for (index = 0; index < 5; ++index)
        session.islands[0].floater_max_x[index] = 0x9ff;
    (void)school(&session, 0, 0, 600);
    soldier(&session, 0, 0, 1000, 0); /* linked to the school */
    soldier(&session, 1, 4, 1005, 0); /* a melee Leviathan */
    held = &session.floaters[0];
    holder = &session.floaters[1];
    held->attack_range = 0;
    holder->type_index = 4;
    holder->source_subtype = 1;
    holder->source_link_0c = -1;
    holder->attack_range = 0;
    holder->movement_state = 6;
    holder->active_order_action = 6;
    holder->order_target_floater = 0;
    holder->attack_period = 2000; /* still striking during the test */
    holder->order_progress = 2;
    holder->source_runtime_flags = 0x040U;
    held->source_runtime_flags = 0x010U;
    held->active_order_action = 6;
    held->movement_state = 0x0f;
    held->order_target_floater = 1;
    held->destination_x = holder->x;
    held->destination_y = holder->y;
    held->stop_radius = 10;
    held->has_move_order = 1;
    held->order_progress = 1;

    for (tick = 1; tick <= 5; ++tick) {
        game_session_tick_floater_moves(&session, tick, &pads);
        if ((held->source_runtime_flags & 0x040U) != 0) marked = 1;
        if (held->movement_state == 6) struck = 1;
    }
    assert(marked);
    assert(struck);
    assert((holder->source_runtime_flags & 0x010U) != 0);
}

static GameRuntimeLocation *leviathan_site(GameSession *session,
                                           uint16_t index, uint8_t renderer_class,
                                           uint16_t x, int32_t item)
{
    GameRuntimeLocation *site = &session->islands[0].locations[index];
    unsigned int slot;
    memset(site, 0, sizeof(*site));
    site->renderer_class = renderer_class;
    site->x = x;
    site->y = 200;
    site->owner_id = 4;
    site->source_value_14 = 4;
    site->record_value_10 = item;
    site->source_location_slot_18 = -1;
    site->source_category_slot_60 = -1;
    site->charge_recent_floater = -1;
    site->charge_staff_task_handle = -1;
    site->upgrade_task_handle = -1;
    site->leviathan_spawned_floater = -1;
    site->bridge_neighbor_island = -1;
    for (slot = 0; slot < 8; ++slot) site->charge_floater_slots[slot] = -1;
    for (slot = 0; slot < GAME_RESOURCE_TYPE_COUNT; ++slot)
        site->source_task_slot[slot] = -1;
    return site;
}

static void test_freed_leviathan_sites_become_visible_again(void)
{
    /* FUN_00452a15 -> FUN_00466c8b -> FUN_0045e6d3(island) runs
       FUN_00462285 for players 0..3 once the record is cleared (ev_d3776e7d):
       a Leviathan pad or pool, hidden from every player while owner 4 holds
       it, shows again inside the player's span. */
    static GameSession session;
    GameRuntimeLocation *marker;
    GameRuntimeLocation *pad;
    GameRuntimeLocation *pool;
    unsigned int index;

    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    session.islands[0].location_count = 3;
    for (index = 0; index < 5; ++index)
        session.islands[0].floater_max_x[index] = 0x9ff;
    marker = leviathan_site(&session, 0, 1, 1000, 0);
    marker->owner_id = -1;
    marker->source_value_14 = -1;
    marker->source_value_22 = 0x01; /* player 0 holds this region */
    pad = leviathan_site(&session, 1, 0, 1060, 0x10);   /* V-SHOT1 */
    pool = leviathan_site(&session, 2, 1, 1100, 0x06);  /* a Leviathan pool */
    pad->source_value_22 = 0x01;
    pool->source_value_22 = 0x01;

    assert(game_session_recalculate_player_island_visibility(&session, 0, 0) >= 0);
    assert((pad->tribe_visibility_mask & 1U) == 0);
    assert((pool->tribe_visibility_mask & 1U) == 0);

    game_session_clear_cast_site(&session, 0, 1, pad);
    assert(pad->owner_id == -1 && pad->record_value_10 == 0);
    assert((pad->tribe_visibility_mask & 1U) != 0);

    game_session_clear_cast_site(&session, 0, 2, pool);
    assert(pool->owner_id == -1);
    assert((pool->tribe_visibility_mask & 1U) != 0);
}

static void test_wizard_does_not_attack_on_its_own(void)
{
    /* FUN_0041e569 0x41f9ba..0x41fa7b rewrites a subtype-4 floater's home
       order (action 9, stage 0) after every finished state, without an
       action-9 test (ev_8578fcc7): it never reaches action 9's target pick
       near the anchor, so an enemy beside its building is left alone. */
    static GameSession session;
    PadCatalog pads;
    GameFloaterStart *wizard;
    GameFloaterStart *enemy;
    unsigned int tick;
    unsigned int index;

    make_pad_catalog(&pads);
    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    session.islands[0].location_count = 2;
    session.random_state = 5;
    for (index = 0; index < 5; ++index)
        session.islands[0].floater_max_x[index] = 0x9ff;
    (void)school(&session, 0, 0, 600);
    (void)school(&session, 1, 1, 1800);
    session.islands[0].locations[0].record_value_10 = 0x2f;
    soldier(&session, 0, 0, 700, 0);
    soldier(&session, 1, 1, 640, 1); /* an enemy soldier near the tower */
    wizard = &session.floaters[0];
    enemy = &session.floaters[1];
    wizard->source_subtype = 4;
    wizard->attack_range = 0;
    wizard->previous_movement_state = 9; /* a state just finished */
    enemy->attack_range = 0;
    /* The tower guards its own spot (BC_DefendArea, genre 9). */
    assert(game_session_set_building_order(&session, 0, 0, 0, 9, 0, 600, 200));

    for (tick = 1; tick <= 600; ++tick) {
        game_session_tick_floater_moves(&session, tick, &pads);
        assert(wizard->movement_state != 0x0f && wizard->movement_state != 6);
        assert(wizard->order_target_floater != 1);
    }
    assert(enemy->current_hit_points == 60);
}

/* Fires one Leviathan bolt tower (pad.txt range, strength) at a fresh 3-HP
   worker until it dies or `limit` ticks pass; returns the largest HP loss
   seen in a single tick, and the number of hits through *hits. */
static int32_t largest_bolt_hit_on_a_worker(int32_t item_id, int16_t range,
                                            int16_t strength, uint32_t seed,
                                            unsigned int *hits)
{
    static GameSession session;
    PadCatalog pads;
    BuildingRenderCatalog buildings = {0};
    GameRuntimeLocation *tower;
    GameFloaterStart *worker;
    int32_t largest = 0;
    unsigned int tick;

    memset(&session, 0, sizeof(session));
    tone_rng_seed(&session.random_state, seed);
    make_leviathan_pads(&pads);
    make_leviathan_buildings(&buildings);
    pads.items[item_id].movement_cost[0] = range;
    pads.items[item_id].movement_cost[1] = strength;
    /* bldinf.txt V-SHOT1: PROD 15 21 2 L 0 20 -3,-50 VSHT1B. */
    buildings.items[item_id].prod.present = 1;
    buildings.items[item_id].prod.first_frame = 15;
    buildings.items[item_id].prod.last_frame = 21;
    buildings.items[item_id].prod.ticks_per_frame = 2;
    buildings.items[item_id].prod.threshold = 10;
    buildings.items[item_id].prod.offset_x = -3;
    buildings.items[item_id].prod.offset_y = -50;
    session.island_count = 1;
    session.islands[0].location_count = 1;
    tower = &session.islands[0].locations[0];
    make_leviathan_marker(tower, 0, item_id);
    tower->x = 500;
    tower->y = 500;
    tower->source_flags = 0x001U;
    tower->resource_retry_tick_36 = -1;
    add_test_worker(&session, 0, 0, 580, 500, 0);
    worker = &session.floaters[0];
    worker->current_hit_points = 3; /* floater.txt pwork: 3 HP */
    worker->max_hit_points = 3;
    *hits = 0;
    for (tick = 0; tick < 4000 && (worker->source_runtime_flags & 0x008U) == 0;
         ++tick) {
        int16_t before = worker->current_hit_points;
        game_session_tick_item_animations_with_floaters(
            &session, &buildings, NULL, &pads);
        if (worker->current_hit_points < before) {
            ++*hits;
            if (before - worker->current_hit_points > largest)
                largest = before - worker->current_hit_points;
        }
    }
    return largest;
}

static void test_plasid_never_kills_a_fresh_worker_in_one_hit(void)
{
    /* Playtest 2026-11-11: "a Plasid shot killed a worker in one hit".
       Plasid (V-SHOT1, pad.txt "150,2,0") has strength 2: FUN_00420217
       rolls (r(1) + r(1) + 3 + r(1)) / 3 = 1 on every hit, so a 3-HP worker
       takes three hits. Mesron (V-ROD2, "200,4,0") fires the same VSHT1B
       bolt with strength 4 and can deal 3 in one hit. */
    uint32_t seed;
    int mesron_one_shot = 0;
    for (seed = 1; seed <= 12; ++seed) {
        unsigned int hits;
        assert(largest_bolt_hit_on_a_worker(0x10, 150, 2, seed, &hits) == 1);
        assert(hits == 3);
    }
    /* Mesron's strength-4 roll (the damage function the bolt calls) deals 1
       to 3; a 3 needs all three draws at 2, about 3 % of hits. */
    for (seed = 0; seed < 4000 && !mesron_one_shot; ++seed) {
        static GameSession session;
        memset(&session, 0, sizeof(session));
        session.random_state = seed * 1000003U;
        add_test_worker(&session, 0, 0, 0, 0, 0);
        session.floaters[0].current_hit_points = 3;
        session.floaters[0].max_hit_points = 3;
        if (game_session_damage_floater_from_power(&session, 0, 4) == 3) {
            assert((session.floaters[0].source_runtime_flags & 0x008U) != 0);
            mesron_one_shot = 1;
        }
    }
    assert(mesron_one_shot);
}

static void test_shared_glyphs_pool_the_bonuses_of_the_sharing_tribes(void)
{
    /* Network host option: tribes 0 and 2 share their glyph bonuses. Tribe 2
       holds Tal (bit 0, Train 1 +1 strength), Lod (bit 8, spell magic cost)
       and the feature bit of Dre (bit 1, Train 1 HP); tribe 3, outside the
       pool, holds Vinya (bit 13). Ownership itself stays per tribe. */
    static GameSession session;
    memset(&session, 0, sizeof(session));
    session.economy[2].glyph_mask = 0x0101U;
    session.economy[2].special_feature_island_mask = 0x0002U;
    session.economy[3].glyph_mask = 0x2000U;
    assert(game_session_glyph_effect_mask(&session, 0) == 0);
    session.glyph_share_mask = 0x05U;
    assert(game_session_glyph_effect_mask(&session, 0) == 0x0101U);
    assert(game_session_glyph_effect_mask(&session, 2) == 0x0101U);
    assert(game_session_feature_effect_mask(&session, 0) == 0x0002U);
    assert(game_session_glyph_effect_mask(&session, 1) == 0);
    assert(game_session_glyph_effect_mask(&session, 3) == 0x2000U);
    assert(session.economy[0].glyph_mask == 0);
}

static void test_unit_panel_power_grows_with_the_level(void)
{
    /* Playtest 2026-11-12: "levelled-up units keep their level-1 stats".
       FUN_0044338b shows FUN_0041fde6 on the STRENGTH row: a charged Train 1
       unit of strength 5 shows 5 at level 1, 7 at level 2, 9 at level 3;
       without charge only the level part remains. */
    static GameSession session;
    GameFloaterStart *unit;
    memset(&session, 0, sizeof(session));
    session.floater_count = 1;
    unit = &session.floaters[0];
    unit->is_active = 1;
    unit->type_index = 0;
    unit->owner_slot = 0;
    unit->source_subtype = 1;
    unit->source_link_0c = -1;
    unit->attack_strength = 5;
    unit->charge_current = 10;
    assert(game_session_floater_power(&session, unit) == 5);
    unit->attack_level_flags = 1;
    assert(game_session_floater_power(&session, unit) == 7);
    unit->attack_level_flags = 2;
    assert(game_session_floater_power(&session, unit) == 9);
    unit->charge_current = 0;
    assert(game_session_floater_power(&session, unit) == 4);
}

static void test_recharging_units_level_up_only_into_free_places(void)
{
    /* Playtest 2026-11-12: three warriors could level up at once. A tier-1
       Train 1 school keeps 2 units at level 2 (Niveau 2). Three level-1
       units with enough experience come back together to recharge (flag
       0x21, FUN_0045c797): the native 251 step raised all three; the remake
       promotes two and only recharges the third. */
    static GameSession session;
    static FloaterCatalog floaters;
    PadCatalog pads;
    BuildingRenderCatalog buildings = {0};
    GameRuntimeLocation *home;
    unsigned int index;
    unsigned int promoted = 0;

    make_pad_catalog(&pads);
    make_floater_catalog(&floaters);
    floaters.rows[1].hit_points = 9;
    floaters.rows[1].max_attack_points = 4;
    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    session.islands[0].location_count = 1;
    home = school(&session, 0, 0, 600);
    home->source_capacity_4a = 1;
    home->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] = 50;
    home->source_value_32 = 251;
    for (index = 0; index < 3; ++index) {
        GameFloaterStart *unit;
        soldier(&session, index, 0, 600, 0);
        unit = &session.floaters[index];
        unit->attack_level_flags = 0;
        unit->source_progress_08 = 100;
        unit->charge_current = 0;
        unit->source_runtime_flags |= 0x21U;
        home->charge_floater_slots[index] = (int16_t)index;
    }
    home->charge_floater_count = 3;

    game_session_tick_item_animations_with_floaters(&session, &buildings,
                                                    &floaters, &pads);
    for (index = 0; index < 3; ++index) {
        const GameFloaterStart *unit = &session.floaters[index];
        if ((unit->attack_level_flags & 0x0fU) == 1) ++promoted;
        assert(unit->charge_current == 4);
        assert((unit->source_runtime_flags & 0x20U) == 0);
    }
    assert(promoted == 2);
}

static void test_courage_boosts_the_targeted_school(void)
{
    /* Playtest 2026-11-12: Courage of the Brave (kind 0xc) boosted the
       caster's own school. FUN_004239e9 flags the TARGET site (caster +0x32)
       with 0x8000 and pulses its linked floaters (ev_66861927, ev_5b35a523). */
    static GameSession session;
    PadCatalog pads;
    GameRuntimeLocation *wizard_school;
    GameRuntimeLocation *warrior_school;
    GameFloaterStart *caster;
    GameFloaterStart *warrior;

    make_pad_catalog(&pads);
    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    session.islands[0].location_count = 2;
    wizard_school = school(&session, 0, 0, 300);
    wizard_school->record_value_10 = 0x2f;
    warrior_school = school(&session, 1, 0, 700);
    warrior_school->source_location_slot_18 = 1;
    soldier(&session, 0, 0, 300, 0);           /* the wizard */
    caster = &session.floaters[0];
    caster->source_subtype = 4;
    caster->cast_spell_kind = 0x0c;
    caster->active_order_action = 0x13;
    wizard_school->charge_floater_slots[0] = 0;
    soldier(&session, 1, 0, 700, 1);           /* a warrior of the target */
    warrior = &session.floaters[1];
    warrior->source_link_0c = 1;
    warrior_school->charge_floater_slots[0] = 1;

    assert(game_session_resolve_cast_effect_step(&session, &pads, 0, 0x0c, 1) != 0);
    assert((warrior_school->source_flags & 0x8000U) != 0);
    assert((wizard_school->source_flags & 0x8000U) == 0);
    assert((warrior->source_runtime_flags & 0x2000U) != 0);
    assert((caster->source_runtime_flags & 0x2000U) == 0);
}

static void test_tone_pool_release_bolt_loops_level_two_in_flight(void)
{
    /* Playtest 2026-11-12: DESTSUPP plays frames 1..4 once, loops 5..14
       while it flies (FUN_0041521a steps the level-2 frame on odd updates
       and wraps it), then 15..18 on the pool (ev_df9c9036, ev_37c4c47f). */
    static GameSession session;
    PadCatalog pads;
    uint32_t tick;
    int visual;
    unsigned int frame;
    unsigned int seen_level_two = 0;
    int wrapped = 0;
    unsigned int previous = 0;
    int finished = 0;

    make_pad_catalog(&pads);
    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    session.islands[0].location_count = 1;
    session.islands[0].locations[0].x = 900;
    session.islands[0].locations[0].y = 200;
    add_test_worker(&session, 0, 0, 100, 200, 0);
    session.floaters[0].cast_spell_kind = 0x10;
    assert(game_session_schedule_cast_effect_step(&session, 0, 0x10, 0));
    for (tick = 1; tick < 600 && session.cast_effects[0].active; ++tick) {
        game_session_tick_cast_effects(&session, tick, &pads);
        if (!game_session_cast_effect_visual(&session, 0, &visual, &frame))
            continue;
        assert(visual == 8);
        if (session.cast_effects[0].animation_phase ==
            GAME_CAST_PHASE_DESTSUPP_TRAVEL) {
            assert(frame <= 13U);
            if (frame >= 4U) seen_level_two |= 1U << frame;
            if (previous == 13U && frame == 4U) wrapped = 1;
            previous = frame;
        } else {
            assert(frame >= 14U && frame <= 17U);
            finished = 1;
        }
    }
    assert(seen_level_two == 0x3ff0U);   /* every frame 5..14 */
    assert(wrapped);
    assert(finished);
}

/* Spell audit 2026-11-13: a wizard school of `owner` with one linked level-0
   wizard (floater 0) and full pools, at site 0; other sites are free. */
static GameRuntimeLocation *spell_audit_school(GameSession *session,
                                               int32_t owner)
{
    GameRuntimeLocation *home;
    memset(session, 0, sizeof(*session));
    session->island_count = 1;
    session->islands[0].location_count = 4;
    home = school(session, 0, owner, 300);
    home->record_value_10 = 0x2f + owner * 16;
    home->resource_stock[GAME_RESOURCE_MAGIC_TONE] = 200;
    home->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] = 200;
    soldier(session, 0, (uint8_t)owner, 300, 0);
    session->floaters[0].source_subtype = 4;
    session->floaters[0].attack_level_flags = 0;
    home->charge_floater_slots[0] = 0;
    home->charge_floater_count = 1;
    return home;
}

static void test_spell_pre_checks_spend_nothing_on_a_wrong_target(void)
{
    /* FUN_0045da80 (ev_d00b4069): Silent Shield (kind 5, Cephean button 3)
       needs an empty class-0 pad; anything else is refused before the
       caster is chosen and before the pools are spent. */
    static GameSession session;
    GameRuntimeLocation *home = spell_audit_school(&session, 2);
    GameRuntimeLocation *built = &session.islands[0].locations[1];
    GameRuntimeLocation *empty = &session.islands[0].locations[2];
    built->renderer_class = 0;
    built->record_value_10 = 0x25;
    empty->renderer_class = 0;
    empty->record_value_10 = 0;
    assert(game_session_queue_cast_action_at(&session, 2, 0, 0, 0x17, 0, 1, -1));
    assert(game_session_dispatch_cast_actions(&session) == 0);
    assert(home->resource_stock[GAME_RESOURCE_MAGIC_TONE] == 200);
    assert(session.floaters[0].active_order_action != 0x13);
    assert(game_session_queue_cast_action_at(&session, 2, 0, 0, 0x17, 0, 2, -1));
    assert(game_session_dispatch_cast_actions(&session) == 1);
    assert(home->resource_stock[GAME_RESOURCE_MAGIC_TONE] == 200 - 12);
    assert(session.floaters[0].cast_spell_kind == 5);
}

static void test_sacrifice_protects_its_caster_from_the_start(void)
{
    /* FUN_0045da80: kinds 7 and 0x12 set flag 0x100 and +0x24 = -4000. */
    static GameSession session;
    GameFloaterStart *caster;
    (void)spell_audit_school(&session, 0);
    assert(game_session_queue_cast_action_at(&session, 0, 0, 0, 0x16, 0, 1, -1));
    assert(game_session_dispatch_cast_actions(&session) == 1);
    caster = &session.floaters[0];
    assert(caster->cast_spell_kind == 7);
    assert((caster->source_runtime_flags & 0x100U) != 0);
    assert((int16_t)caster->source_death_timer == -4000);
}

static void test_spiritual_awakening_raises_hit_points(void)
{
    /* FUN_004239e9 case 0xb multiplies the linked units' hit points (+0x20)
       by level + 1, capped at twice their maximum; the charge is untouched. */
    static GameSession session;
    GameRuntimeLocation *target;
    GameFloaterStart *warrior;
    (void)spell_audit_school(&session, 0);
    session.floaters[0].cast_spell_kind = 0x0b;
    session.floaters[0].attack_level_flags = 1;
    target = school(&session, 1, 0, 600);
    target->source_location_slot_18 = 1;
    soldier(&session, 1, 0, 600, 1);
    warrior = &session.floaters[1];
    warrior->current_hit_points = 25;
    warrior->max_hit_points = 30;
    warrior->charge_current = 7;
    target->charge_floater_slots[0] = 1;
    assert(game_session_resolve_cast_effect_step(&session, NULL, 0, 0x0b, 1) != 0);
    assert(warrior->current_hit_points == 50);
    assert(warrior->charge_current == 7);
    warrior->current_hit_points = 40;
    session.floaters[0].source_runtime_flags &= ~0x200U;
    assert(game_session_resolve_cast_effect_step(&session, NULL, 0, 0x0b, 1) != 0);
    assert(warrior->current_hit_points == 60);   /* capped at 2 * 30 */
}

static void test_repair_on_open_ground_heals_workers(void)
{
    /* FUN_004239e9 case 3 (asm 0x42444b..0x42457d): a target that is not a
       building heals the owner's damaged workers, up to 2 * level + 2. */
    static GameSession session;
    unsigned int index;
    unsigned int healed = 0;
    (void)spell_audit_school(&session, 3);
    session.floaters[0].cast_spell_kind = 3;
    session.islands[0].locations[1].record_value_10 = 0;   /* empty pad */
    for (index = 1; index <= 4; ++index) {
        add_test_worker(&session, index, 0, 400, 200, 3);
        session.floaters[index].type_index = 3;
        session.floaters[index].current_hit_points = 1;
        session.floaters[index].max_hit_points = 3;
    }
    assert(game_session_resolve_cast_effect_step(&session, NULL, 0, 3, 1) != 0);
    for (index = 1; index <= 4; ++index)
        if (session.floaters[index].current_hit_points == 3) ++healed;
    assert(healed == 2);   /* level 0: 2 * 0 + 2 */
}

static void run_playtest_fix_tests(void)
{
    test_spell_pre_checks_spend_nothing_on_a_wrong_target();
    test_sacrifice_protects_its_caster_from_the_start();
    test_spiritual_awakening_raises_hit_points();
    test_repair_on_open_ground_heals_workers();
    test_tone_pool_release_bolt_loops_level_two_in_flight();
    test_courage_boosts_the_targeted_school();
    test_recharging_units_level_up_only_into_free_places();
    test_unit_panel_power_grows_with_the_level();
    test_shared_glyphs_pool_the_bonuses_of_the_sharing_tribes();
    test_plasid_never_kills_a_fresh_worker_in_one_hit();
    test_wizard_does_not_attack_on_its_own();
    test_freed_leviathan_sites_become_visible_again();
    test_caster_on_another_island_crosses_before_casting();
    test_caster_without_route_keeps_the_pools();
    test_level_up_candidate_returns_to_its_building();
    test_level_up_candidate_crosses_a_bridge_home();
    test_held_floater_reaches_its_holder_and_strikes();
}
