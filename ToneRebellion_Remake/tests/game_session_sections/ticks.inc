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
    source->source_flags = 0xdeadbeefU;
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
    assert(source->source_flags == 0xdeadbef0U);
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
    location->animation_rate = 2;
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
    item->cons.fallback_frame = 3; /* bldinf CONS parameter, source +0x0a */
    item->prod.present = 1;
    item->prod.threshold = 2;      /* bldinf PROD parameter, source +0x0c */

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
    catalog.item_count = 0x28;
    item = &catalog.items[0x25];
    item->item_id = 0x25;
    item->present = 1;
    item->prod.present = 1;
    item->prod.threshold = 2;

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
    assert(location->producer_cadence == 0);
    assert((location->source_flags & 0x002U) == 0);

    location->record_value_24 = 0;
    location->animation_rate = 2;
    for (tick = 0; tick < 10; ++tick) {
        game_session_tick_item_animations(&session, &catalog);
    }
    assert(location->producer_cadence == 0);
    assert((location->source_flags & 0x002U) != 0);

    location->source_flags = 0x411U;
    location->record_value_10 = 0x26;
    location->animation_rate = 1;
    location->record_value_24 = 0;
    location->production_progress = 0;
    item = &catalog.items[0x26];
    item->item_id = 0x26;
    item->present = 1;
    item->prod.present = 1;
    item->prod.threshold = 1;
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
    for (tick = 0; tick < 20; ++tick) {
        game_session_tick_item_animations(&session, &catalog);
    }
    game_session_tick_item_animations(&session, &catalog);
    assert(location->record_value_24 == 2);
}
