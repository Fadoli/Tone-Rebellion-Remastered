static void test_inci_animation_uses_source_counter_and_delayed_activation(void)
{
    GameSession session;
    BuildingRenderCatalog catalog;
    GameRuntimeLocation *location;
    BuildingRenderItem *item;
    ToneRng random_state;

    memset(&session, 0, sizeof(session));
    memset(&catalog, 0, sizeof(catalog));
    session.island_count = 1;
    session.islands[0].location_count = 1;
    location = &session.islands[0].locations[0];
    location->record_value_10 = 42;
    location->renderer_class = 0;
    location->source_value_3e = -1;
    catalog.item_count = 43;
    item = &catalog.items[42];
    item->item_id = 42;
    item->present = 1;
    item->inci.present = 1;
    item->inci.ticks_per_frame = 2;
    item->inci.fallback_frame = 0;

    /* The first RNG draw from seed 0 yields zero in [0, 5), activating frame
       zero. The next source tick exceeds threshold 0 and restores the sentinel. */
    session.random_state = 0;
    game_session_tick_item_animations(&session, &catalog);
    assert(location->source_value_3e == 0 && location->inci_progress == 0);
    game_session_tick_item_animations(&session, &catalog);
    assert(location->source_value_3e == -1 && location->inci_progress == 0);

    /* A byte delay >= 100 follows the increment/threshold path without RNG. */
    item->inci.ticks_per_frame = 100;
    item->inci.fallback_frame = 1;
    random_state = session.random_state;
    game_session_tick_item_animations(&session, &catalog);
    assert(location->source_value_3e == 0 && location->inci_progress == 0);
    assert(session.random_state == random_state);
    game_session_tick_item_animations(&session, &catalog);
    assert(location->source_value_3e == -1 && location->inci_progress == 0);
}

static void test_active_item_four_and_twenty_two_counter_stops_at_32(void)
{
    GameSession session;
    BuildingRenderCatalog catalog;
    GameRuntimeLocation *item_four;
    GameRuntimeLocation *item_twenty_two;
    GameRuntimeLocation *inactive_item_four;
    GameRuntimeLocation *negative_item_four;

    memset(&session, 0, sizeof(session));
    memset(&catalog, 0, sizeof(catalog));
    session.island_count = 1;
    session.islands[0].location_count = 4;
    item_four = &session.islands[0].locations[0];
    item_four->record_value_10 = 4;
    item_four->source_flags = 1;
    item_four->charge_source_value_30 = 30;
    item_twenty_two = &session.islands[0].locations[1];
    item_twenty_two->record_value_10 = 0x16;
    item_twenty_two->source_flags = 1;
    item_twenty_two->charge_source_value_30 = 31;
    inactive_item_four = &session.islands[0].locations[2];
    inactive_item_four->record_value_10 = 4;
    inactive_item_four->charge_source_value_30 = 7;
    negative_item_four = &session.islands[0].locations[3];
    negative_item_four->record_value_10 = 4;
    negative_item_four->source_flags = 1;
    negative_item_four->charge_source_value_30 = UINT16_MAX; /* signed -1 */

    game_session_tick_item_animations(&session, &catalog);
    assert(item_four->charge_source_value_30 == 31);
    assert(item_twenty_two->charge_source_value_30 == 32);
    assert(inactive_item_four->charge_source_value_30 == 7);
    assert(negative_item_four->charge_source_value_30 == 0);
    game_session_tick_item_animations(&session, &catalog);
    assert(item_four->charge_source_value_30 == 32);
    assert(item_twenty_two->charge_source_value_30 == 32);
}

static void test_class0_item5_spawns_neutral_item_after_difficulty_delay(void)
{
    GameSession session = {0};
    BuildingRenderCatalog buildings = {0};
    PadCatalog pads = {0};
    GameRuntimeLocation *source;
    unsigned int tick;

    session.island_count = 1;
    session.config.difficulty = 0;
    session.random_state = 0;
    session.islands[0].location_count = 1;
    source = &session.islands[0].locations[0];
    source->renderer_class = 0;
    source->record_value_10 = 5;
    source->owner_id = 4;
    source->source_value_14 = 4;
    source->source_value_22 = 0x00ff;
    source->record_value_24 = 7;
    source->source_flags = 0xdeadbe4fU; /* no 0x80/0x20: those start the destruction and upgrade timers */
    source->source_value_32 = 1;
    source->animation_rate = 1;
    source->producer_cadence = 19;
    source->barg_progress = 0.5;

    pads.item_count = 22;
    for (tick = 0; tick < pads.item_count; ++tick) {
        pads.items[tick].item_id = (uint16_t)tick;
        pads.items[tick].hit_points = 30;
    }

    for (tick = 0; tick < 1199; ++tick) {
        game_session_tick_item_animations_with_floaters(
            &session, &buildings, NULL, &pads);
    }
    assert(source->record_value_10 == 5);
    assert(source->charge_source_value_30 == 1199);

    game_session_tick_item_animations_with_floaters(
        &session, &buildings, NULL, &pads);
    assert(source->record_value_10 == 12 || source->record_value_10 == 16 ||
           source->record_value_10 == 11 || source->record_value_10 == 19 ||
           source->record_value_10 == 10 || source->record_value_10 == 20);
    assert(source->owner_id == 4 && source->source_value_14 == 4);
    assert(source->source_value_34 == 30 && source->source_value_32 == 1);
    assert(source->record_value_24 == 7);
    /* Replacement keeps 0x400 only (FUN_00452859 clears 0x10); the active bit is then recomputed. */
    assert(source->source_flags == 0xdeadbe41U);
    assert(source->source_value_22 == 0);
    assert(source->charge_source_value_30 == 0);
    assert(source->source_value_3a == 0 && source->source_value_3c == 0);
    assert(source->source_value_3e == -1);
    assert(source->animation_rate == 1);
    assert(source->producer_cadence == 19 && source->barg_progress == 0.5);
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
    /* The increment follows raw +0x32, not the render-facing animation_rate. */
    location->source_value_32 = 2;
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
    /* FUN_00455833 +0x0a: the CONS animation's length, 3 frames x 1 tick. */
    item->cons.first_frame = 1;
    item->cons.last_frame = 3;
    item->cons.ticks_per_frame = 1;
    item->cons.fallback_frame = 9; /* resting frame only, not the threshold */
    item->prod.present = 1;
    item->prod.threshold = 2;      /* bldinf PROD parameter, source +0x0c */
    /* The PROD cycle lasts as long as its animation: one frame, two ticks. */
    item->prod.first_frame = 1;
    item->prod.last_frame = 1;
    item->prod.ticks_per_frame = 2;

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

static void test_producer_cadence_starts_prod_and_waits_for_output_consumption(void)
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
    location->record_value_10 = 0x25;
    location->owner_id = 0;
    location->renderer_class = 0;
    location->source_flags = 0x411U;
    location->animation_rate = 1;
    location->source_value_32 = 1; /* the cadence adds raw +0x32 */
    catalog.item_count = 0x28;
    item = &catalog.items[0x25];
    item->item_id = 0x25;
    item->present = 1;
    item->prod.present = 1;
    item->prod.threshold = 2;
    item->prod.first_frame = 1; /* PROD lasts one frame, two ticks */
    item->prod.last_frame = 1;
    item->prod.ticks_per_frame = 2;

    location->source_flags = 0x410U;
    game_session_tick_item_animations(&session, &catalog);
    assert(location->producer_cadence == 0);
    assert((location->source_flags & 0x002U) == 0);
    location->source_flags = 0x411U;
    for (tick = 0; tick < 19; ++tick) {
        game_session_tick_item_animations(&session, &catalog);
    }
    assert(location->producer_cadence == 19);
    assert((location->source_flags & 0x002U) == 0);
    game_session_tick_item_animations(&session, &catalog);
    assert(location->producer_cadence == 0);
    assert((location->source_flags & 0x002U) != 0);
    assert(location->production_progress == 0);

    game_session_tick_item_animations(&session, &catalog);
    assert(location->production_progress == 1);
    assert(location->record_value_24 == 0);
    game_session_tick_item_animations(&session, &catalog);
    assert((location->source_flags & 0x002U) == 0);
    assert(location->record_value_24 == 1);
    for (tick = 0; tick < 25; ++tick) {
        game_session_tick_item_animations(&session, &catalog);
    }
    assert(location->record_value_24 == 1);
    /* The cadence check runs before the output is written, so the completion tick adds +0x32 once. */
    assert(location->producer_cadence == 1);
    assert((location->source_flags & 0x002U) == 0);

    location->record_value_24 = 0;
    location->animation_rate = 2;
    location->source_value_32 = 2;
    for (tick = 0; tick < 10; ++tick) {
        game_session_tick_item_animations(&session, &catalog);
    }
    assert(location->producer_cadence == 0);
    assert((location->source_flags & 0x002U) != 0);

    location->source_flags = 0x411U;
    location->record_value_10 = 0x26;
    location->animation_rate = 1;
    location->source_value_32 = 1;
    location->record_value_24 = 0;
    location->production_progress = 0;
    item = &catalog.items[0x26];
    item->item_id = 0x26;
    item->present = 1;
    item->prod.present = 1;
    item->prod.threshold = 1;
    item->prod.first_frame = 1;
    item->prod.last_frame = 1;
    item->prod.ticks_per_frame = 1;
    for (tick = 0; tick < 20; ++tick) {
        game_session_tick_item_animations(&session, &catalog);
    }
    game_session_tick_item_animations(&session, &catalog);
    assert(location->record_value_24 == 3);

    location->source_flags = 0x411U;
    location->record_value_10 = 0x27;
    location->record_value_24 = 0;
    location->production_progress = 0;
    item = &catalog.items[0x27];
    item->item_id = 0x27;
    item->present = 1;
    item->prod.present = 1;
    item->prod.threshold = 1;
    item->prod.first_frame = 1;
    item->prod.last_frame = 1;
    item->prod.ticks_per_frame = 1;
    for (tick = 0; tick < 20; ++tick) {
        game_session_tick_item_animations(&session, &catalog);
    }
    game_session_tick_item_animations(&session, &catalog);
    assert(location->record_value_24 == 2);
}

static void make_leviathan_pads(PadCatalog *pads)
{
    unsigned int item;
    memset(pads, 0, sizeof(*pads));
    pads->item_count = 22;
    for (item = 0; item < pads->item_count; ++item) {
        pads->items[item].item_id = (uint16_t)item;
        pads->items[item].hit_points = 30;
    }
}

/* Render rows are descriptor-less but present: items 0/1 only reach the
   neutral-replacement switch when the catalog has a row for them. */
static void make_leviathan_buildings(BuildingRenderCatalog *buildings)
{
    unsigned int item;
    memset(buildings, 0, sizeof(*buildings));
    buildings->item_count = 22;
    for (item = 0; item < buildings->item_count; ++item) {
        buildings->items[item].item_id = (uint16_t)item;
        buildings->items[item].present = 1;
    }
}

static void make_leviathan_marker(GameRuntimeLocation *marker,
                                  uint8_t renderer_class, int32_t item_id)
{
    memset(marker, 0, sizeof(*marker));
    marker->renderer_class = renderer_class;
    marker->record_value_10 = item_id;
    marker->owner_id = 4;
    marker->source_value_14 = 4;
    marker->source_value_22 = 0x00ff;
    marker->source_value_32 = 1;
    marker->source_flags = 0x4f;
    marker->animation_rate = 1;
    marker->leviathan_spawned_floater = -1;
}

static unsigned int ticks_until_marker_changes(GameSession *session,
                                               const PadCatalog *pads,
                                               const GameRuntimeLocation *marker,
                                               unsigned int limit)
{
    BuildingRenderCatalog buildings = {0};
    int32_t before = marker->record_value_10;
    unsigned int tick;
    make_leviathan_buildings(&buildings);
    for (tick = 1; tick <= limit; ++tick) {
        game_session_tick_item_animations_with_floaters(
            session, &buildings, NULL, pads);
        if (marker->record_value_10 != before) return tick;
    }
    return 0;
}

static void test_leviathan_marker_becomes_defense_building_with_time(void)
{
    /* Class-1 item 5 is the Leviathan seed: its +0x30 counter grows by +0x32
       per tick and fires at 0x4b0 - 100 * difficulty (FUN_00450a71 case 5). */
    unsigned int difficulty;
    for (difficulty = 0; difficulty < 5; ++difficulty) {
        GameSession session = {0};
        PadCatalog pads;
        GameRuntimeLocation *marker = &session.islands[0].locations[0];
        unsigned int fired;

        make_leviathan_pads(&pads);
        session.island_count = 1;
        session.config.difficulty = (uint8_t)difficulty;
        session.islands[0].location_count = 1;
        make_leviathan_marker(marker, 1, 5);

        fired = ticks_until_marker_changes(&session, &pads, marker, 2000);
        assert(fired == 0x4b0U - difficulty * 100U);
        /* Replacement stays Leviathan-owned and picks a spawner type 6..9. */
        assert(marker->record_value_10 >= 6 && marker->record_value_10 <= 9);
        assert(marker->owner_id == 4 && marker->source_value_14 == 4);
        assert(marker->charge_source_value_30 == 0);
        assert(marker->source_value_34 == 30);
    }
}

static void test_leviathan_spread_waits_while_marker_rate_is_zero(void)
{
    GameSession session = {0};
    PadCatalog pads;
    GameRuntimeLocation *marker = &session.islands[0].locations[0];

    make_leviathan_pads(&pads);
    session.island_count = 1;
    session.islands[0].location_count = 1;
    make_leviathan_marker(marker, 1, 5);
    marker->source_value_32 = 0;
    assert(ticks_until_marker_changes(&session, &pads, marker, 3000) == 0);
    assert(marker->charge_source_value_30 == 0);
}

static void test_neutral_pool_is_contaminated_then_matures(void)
{
    /* Neutral class-1 POOL (item 0) -> item 5 immediately, then item 5 ->
       defense building after the difficulty delay: full island takeover chain. */
    GameSession session = {0};
    PadCatalog pads;
    GameRuntimeLocation *pool = &session.islands[0].locations[0];
    unsigned int first;
    unsigned int second;

    make_leviathan_pads(&pads);
    session.island_count = 1;
    session.islands[0].location_count = 1;
    make_leviathan_marker(pool, 1, 0);

    first = ticks_until_marker_changes(&session, &pads, pool, 10);
    assert(first == 1 && pool->record_value_10 == 5);
    assert(pool->owner_id == 4 && (pool->source_flags & 0x400U) != 0);
    second = ticks_until_marker_changes(&session, &pads, pool, 2000);
    assert(second == 0x4b0U);
    assert(pool->record_value_10 >= 6 && pool->record_value_10 <= 9);
}

static void test_player_owned_pool_is_not_contaminated(void)
{
    GameSession session = {0};
    PadCatalog pads;
    GameRuntimeLocation *pool = &session.islands[0].locations[0];

    make_leviathan_pads(&pads);
    session.island_count = 1;
    session.islands[0].location_count = 1;
    make_leviathan_marker(pool, 1, 0);
    pool->owner_id = 0;
    pool->source_value_14 = 0;
    assert(ticks_until_marker_changes(&session, &pads, pool, 3000) == 0);
    assert(pool->record_value_10 == 0 && pool->owner_id == 0);
}

static void test_class0_neutral_pad_needs_fitting_leviathan_size(void)
{
    GameSession session = {0};
    PadCatalog pads;
    GameRuntimeLocation *pad = &session.islands[0].locations[0];

    make_leviathan_pads(&pads);
    pads.items[5].size = 2;
    pads.items[5].building_tone_cost = 40; /* not compared by FUN_00452656 */
    session.island_count = 1;
    session.islands[0].location_count = 1;
    make_leviathan_marker(pad, 0, 0);
    pad->construction_site_size = 1; /* PAD row size > raw +0x0c: refused */
    assert(ticks_until_marker_changes(&session, &pads, pad, 50) == 0);
    pad->construction_site_size = 2;
    assert(ticks_until_marker_changes(&session, &pads, pad, 50) == 1);
    assert(pad->record_value_10 == 5 && pad->owner_id == 4);
}

static void test_spore_claimed_noshape_pad_grows_without_render_rows(void)
{
    /* bldinf.txt has no rows for noshape items 0/1, yet FUN_00450a71 still
       runs case 0/1 for an owner-4 record: the claimed pad becomes V-INFECT
       (item 5) and then a Leviathan building after the difficulty delay. */
    unsigned int item;
    for (item = 0; item <= 1; ++item) {
        GameSession session = {0};
        PadCatalog pads;
        BuildingRenderCatalog buildings;
        GameRuntimeLocation *pad = &session.islands[0].locations[0];
        unsigned int tick;

        make_leviathan_pads(&pads);
        make_leviathan_buildings(&buildings);
        buildings.items[0].present = 0;
        buildings.items[1].present = 0;
        session.island_count = 1;
        session.islands[0].location_count = 1;
        make_leviathan_marker(pad, 0, (int32_t)item);
        pad->owner_id = -1; /* the Spore writes only raw +0x14 */
        pad->source_flags = 0;
        game_session_tick_item_animations_with_floaters(
            &session, &buildings, NULL, &pads);
        assert(pad->record_value_10 == 5);
        assert(pad->owner_id == 4 && pad->source_value_14 == 4);
        for (tick = 0; tick < 0x4b0 && pad->record_value_10 == 5; ++tick)
            game_session_tick_item_animations_with_floaters(
                &session, &buildings, NULL, &pads);
        assert(pad->record_value_10 >= 10 && pad->record_value_10 <= 21);
        assert(pad->owner_id == 4);
    }
}

static void test_leviathan_spread_only_converts_its_own_island(void)
{
    GameSession session = {0};
    PadCatalog pads;
    BuildingRenderCatalog buildings = {0};
    unsigned int tick;

    make_leviathan_buildings(&buildings);
    make_leviathan_pads(&pads);
    session.island_count = 2;
    session.islands[0].location_count = 1;
    session.islands[1].location_count = 1;
    make_leviathan_marker(&session.islands[0].locations[0], 1, 5);
    make_leviathan_marker(&session.islands[1].locations[0], 1, 0);
    session.islands[1].locations[0].owner_id = 0;
    session.islands[1].locations[0].source_value_14 = 0;
    for (tick = 0; tick < 0x4b0; ++tick)
        game_session_tick_item_animations_with_floaters(
            &session, &buildings, NULL, &pads);
    assert(session.islands[0].locations[0].record_value_10 >= 6);
    assert(session.islands[1].locations[0].record_value_10 == 0);
    assert(session.islands[1].locations[0].owner_id == 0);
}

static void test_leviathan_spawner_births_units_on_its_island_over_time(void)
{
    /* Class-1 items 6..9 accumulate +0x0c by their rate each tick and birth a
       type-4 unit at the site once the world-time/difficulty threshold is hit
       (10000 ticks at difficulty 0/1). */
    static GameSession session;
    PadCatalog pads;
    BuildingRenderCatalog buildings = {0};
    FloaterCatalog floaters = {0};
    GameRuntimeLocation *spawner;
    unsigned int tick;
    unsigned int subtype;

    for (subtype = 9; subtype <= 17; ++subtype) {
        floaters.rows[subtype + 27U].hit_points = 20;
        floaters.rows[subtype + 27U].attack_strength = 3;
        floaters.rows[subtype + 27U].movement_speed = 2;
    }
    memset(&session, 0, sizeof(session));
    make_leviathan_pads(&pads);
    make_leviathan_buildings(&buildings);
    session.island_count = 2;
    session.islands[1].location_count = 1;
    spawner = &session.islands[1].locations[0];
    make_leviathan_marker(spawner, 1, 6);
    spawner->x = 123;
    spawner->y = 45;
    spawner->source_flags = 0x001U;
    session.islands[1].leviathan_floater_budget = 6;
    session.islands[1].leviathan_site_budget = 1;

    for (tick = 0; tick < 9998; ++tick)
        game_session_tick_item_animations_with_floaters(
            &session, &buildings, &floaters, &pads);
    assert(session.floater_count == 0);
    for (tick = 0; tick < 4; ++tick)
        game_session_tick_item_animations_with_floaters(
            &session, &buildings, &floaters, &pads);
    assert(session.floater_count >= 1);
    assert(session.floaters[0].type_index == 4);
    assert(session.floaters[0].owner_slot == 4);
    assert(session.floaters[0].island_index == 1);
    assert(session.floaters[0].source_subtype >= 9 &&
           session.floaters[0].source_subtype <= 17);
    assert(session.floaters[0].current_hit_points >= 20);
}

static void add_test_worker(GameSession *session, unsigned int index,
                            uint8_t island, uint16_t x, uint16_t y, uint8_t owner)
{
    GameFloaterStart *worker = &session->floaters[index];
    memset(worker, 0, sizeof(*worker));
    worker->is_active = 1;
    worker->island_index = island;
    worker->type_index = 0;
    worker->owner_slot = owner;
    worker->x = x;
    worker->y = y;
    worker->current_hit_points = 200;
    worker->max_hit_points = 200;
    if (index >= session->floater_count)
        session->floater_count = (uint16_t)(index + 1U);
}

static void test_leviathan_defense_hurts_only_workers_in_reach_on_its_island(void)
{
    /* V-ATTCK (item 0x0a, class 0, owner 4) scans its own island's workers
       with the fixed Chebyshev gate < 0x3c, then hits at PROD tick 30. */
    static GameSession session;
    PadCatalog pads;
    BuildingRenderCatalog buildings = {0};
    GameRuntimeLocation *tower;
    unsigned int tick;

    memset(&session, 0, sizeof(session));
    make_leviathan_pads(&pads);
    make_leviathan_buildings(&buildings);
    pads.items[0].movement_cost[2] = 50; /* attack power vs. a tribe-0 worker */
    session.island_count = 2;
    session.islands[0].location_count = 1;
    tower = &session.islands[0].locations[0];
    make_leviathan_marker(tower, 0, 0x0a);
    tower->x = 500;
    tower->y = 500;
    tower->source_flags = 0x001U;
    add_test_worker(&session, 0, 0, 520, 480, 0); /* in reach */
    add_test_worker(&session, 1, 0, 500 + 0x3c, 500, 0); /* gate is strict */
    add_test_worker(&session, 2, 1, 505, 505, 0); /* other island */

    for (tick = 0; tick < 600; ++tick)
        game_session_tick_item_animations_with_floaters(
            &session, &buildings, NULL, &pads);
    assert(session.floaters[0].current_hit_points < 200);
    assert(session.floaters[1].current_hit_points == 200);
    assert(session.floaters[2].current_hit_points == 200);
}

static void test_leviathan_bolt_starts_at_the_prod_offset(void)
{
    /* FUN_00416342: a V-SHOT bolt starts at the site plus the PROD record's
       offset (bldinf.txt V-SHOT1 "-3,-50"). */
    static GameSession session;
    PadCatalog pads;
    BuildingRenderCatalog buildings = {0};
    GameRuntimeLocation *tower;
    unsigned int tick;
    unsigned int slot;
    int fired = 0;

    memset(&session, 0, sizeof(session));
    make_leviathan_pads(&pads);
    make_leviathan_buildings(&buildings);
    pads.items[0x10].movement_cost[0] = 150;
    pads.items[0].movement_cost[2] = 50;
    buildings.items[0x10].prod.present = 1;
    buildings.items[0x10].prod.threshold = 5;
    buildings.items[0x10].prod.first_frame = 1;
    buildings.items[0x10].prod.last_frame = 8;
    buildings.items[0x10].prod.ticks_per_frame = 2;
    buildings.items[0x10].prod.offset_x = -3;
    buildings.items[0x10].prod.offset_y = -50;
    session.island_count = 1;
    session.islands[0].location_count = 1;
    tower = &session.islands[0].locations[0];
    make_leviathan_marker(tower, 0, 0x10);
    tower->x = 500;
    tower->y = 500;
    tower->source_flags = 0x001U;
    tower->resource_retry_tick_36 = -1;
    add_test_worker(&session, 0, 0, 600, 500, 0);
    for (tick = 0; tick < 60 && !fired; ++tick) {
        game_session_tick_item_animations_with_floaters(
            &session, &buildings, NULL, &pads);
        for (slot = 0; slot < 32; ++slot) {
            const GameDefenseProjectile *bolt = &session.defense_projectiles[slot];
            if (bolt->active && bolt->impact_phase == 0) {
                /* At most one 5-pixel step toward the worker. */
                assert(bolt->y <= 450 && bolt->y >= 445);
                assert(bolt->x >= 497 && bolt->x <= 502);
                fired = 1;
            }
        }
    }
    assert(fired);
}

static void test_inactive_leviathan_defense_does_not_fire(void)
{
    static GameSession session;
    PadCatalog pads;
    BuildingRenderCatalog buildings = {0};
    GameRuntimeLocation *tower;
    unsigned int tick;

    memset(&session, 0, sizeof(session));
    make_leviathan_pads(&pads);
    make_leviathan_buildings(&buildings);
    pads.items[0].movement_cost[2] = 50;
    session.island_count = 1;
    session.islands[0].location_count = 1;
    tower = &session.islands[0].locations[0];
    make_leviathan_marker(tower, 0, 0x0a);
    tower->x = 500;
    tower->y = 500;
    tower->source_flags = 0; /* bit 0 clear: not running */
    add_test_worker(&session, 0, 0, 510, 510, 0);
    for (tick = 0; tick < 600; ++tick)
        game_session_tick_item_animations_with_floaters(
            &session, &buildings, NULL, &pads);
    assert(session.floaters[0].current_hit_points == 200);
}

static void test_tone_producers_output_their_own_resource_for_every_tribe(void)
{
    /* P-BLDTON/P-MAGTON/P-CRYTON (0x25/0x26/0x27) emit Build/Magic/Crystal
       Tone codes 1/2/3; owner-specific PAD ids (+16 per tribe) normalize. */
    static const struct { int32_t base; uint16_t code; } producers[3] = {
        {0x25, 1}, {0x26, 3}, {0x27, 2}
    };
    unsigned int producer;
    unsigned int owner;

    for (producer = 0; producer < 3; ++producer) {
        for (owner = 0; owner < GAME_START_PLAYER_COUNT; ++owner) {
            static GameSession session;
            BuildingRenderCatalog catalog = {0};
            GameRuntimeLocation *site;
            unsigned int tick;

            memset(&session, 0, sizeof(session));
            session.island_count = 1;
            session.islands[0].location_count = 1;
            site = &session.islands[0].locations[0];
            site->renderer_class = 0;
            site->record_value_10 = producers[producer].base + (int32_t)owner * 16;
            site->owner_id = (int32_t)owner;
            site->source_value_14 = (int32_t)owner;
            site->source_flags = 0x411U;
            site->source_value_32 = 1;
            site->animation_rate = 1;
            catalog.item_count = 0x60;
            {
                /* Render rows are looked up by the owner-specific id. */
                BuildingRenderItem *row =
                    &catalog.items[site->record_value_10];
                row->item_id = (uint16_t)site->record_value_10;
                row->present = 1;
                row->prod.present = 1;
                row->prod.threshold = 2;
                row->prod.first_frame = 1;
                row->prod.last_frame = 1;
                row->prod.ticks_per_frame = 2;
            }
            for (tick = 0; tick < 30 && site->record_value_24 == 0; ++tick)
                game_session_tick_item_animations(&session, &catalog);
            assert(site->record_value_24 == producers[producer].code);
        }
    }
}
