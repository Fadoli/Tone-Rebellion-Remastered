static void test_initialization_is_transactional_on_bad_world(void)
{
    WorldDefinition world;
    IslandData islands[5];
    GameSessionConfig config;
    GameSession session;
    GameSession before;
    PadCatalog catalog;
    FloaterCatalog floater_catalog;
    char error[160];

    make_world(&world, islands);
    make_pad_catalog(&catalog);
    make_floater_catalog(&floater_catalog);
    world.island_count = 3;
    memset(&config, 0, sizeof(config));
    config.home_island_index = 0;
    memset(&session, 0xa5, sizeof(session));
    before = session;
    assert(!game_session_initialize(&world, islands, &catalog, &floater_catalog,
                                    &config, &session,
                                    error, sizeof(error)));
    assert(strstr(error, "cannot support the four start slots") != NULL);
    assert(memcmp(&session, &before, sizeof(session)) == 0);
}

static void test_building_placement_matches_source_runtime_initialization(void)
{
    GameSession session;
    PadCatalog catalog;
    IslandLocation site;
    GameRuntimeLocation *runtime;
    char error[128];

    memset(&session, 0, sizeof(session));
    memset(&catalog, 0, sizeof(catalog));
    memset(&site, 0, sizeof(site));
    session.island_count = 1;
    session.islands[0].location_count = 1;
    runtime = &session.islands[0].locations[0];
    runtime->renderer_class = 0;
    runtime->record_value_10 = 0;
    runtime->owner_id = -1;
    runtime->source_value_14 = -1;
    runtime->source_location_slot_18 = -1;
    runtime->source_category_slot_60 = -1;
    runtime->source_value_22 = (uint16_t)(1U << 2);
    runtime->source_flags = 0x7df;
    runtime->source_capacity_4a = 3;
    runtime->resource_stock[GAME_RESOURCE_BUILD_TONE] = 11;
    runtime->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] = 12;
    runtime->resource_stock[GAME_RESOURCE_MAGIC_TONE] = 13;
    runtime->charge_source_value_30 = 14;
    runtime->source_value_3a = 15;
    runtime->source_value_3c = 16;
    runtime->source_value_3e = 17;
    runtime->source_value_40 = 18;
    runtime->source_value_42 = 19;
    runtime->source_value_44 = 12;
    runtime->source_value_46 = 20;
    runtime->source_value_48 = 21;
    runtime->producer_cadence = 22;
    runtime->source_value_58 = 1;
    runtime->source_value_44 = 12;
    runtime->source_value_58 = 1;
    runtime->base_progress = 3;
    runtime->chug_progress = 4;
    runtime->glyph_progress = 5;
    runtime->inci_progress = 6;
    runtime->construction_progress = 7;
    runtime->production_progress = 8;
    runtime->animation_rate = 9;
    runtime->barg_progress = 0.75;
    catalog.item_count = PAD_CATALOG_MAX_ITEMS;
    catalog.items[76].item_id = 76; /* base item 0x2c + player slot 2 * 16 */
    catalog.items[76].size = 0;
    catalog.items[76].building_tone_cost = 10;
    catalog.items[76].movement_cost[0] = 25;
    catalog.items[76].hit_points = 17;
    site.kind = ISLAND_LOCATION_PAD_SMALL;
    site.renderer_subtype = 0;

    assert(game_session_place_building(&session, &catalog, 2, 0, 0,
                                       &site, 0x2c, error, sizeof(error)));
    assert(runtime->record_value_10 == 76);
    assert(runtime->owner_id == 2);
    assert(runtime->source_value_14 == 2);
    assert(runtime->source_value_32 == 1);
    assert(runtime->source_location_slot_18 == 0);
    assert(runtime->source_category_slot_60 == 0);
    assert(runtime->source_value_34 == 17);
    assert(runtime->source_capacity_4a == 0);
    assert(runtime->source_flags == 0x7d0);
    assert(runtime->source_value_44 == 0);
    assert(runtime->resource_stock[GAME_RESOURCE_BUILD_TONE] == 0);
    assert(runtime->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] == 0);
    assert(runtime->resource_stock[GAME_RESOURCE_MAGIC_TONE] == 0);
    assert(runtime->charge_source_value_30 == 0);
    assert(runtime->source_value_3a == 0 && runtime->source_value_3c == 0);
    assert(runtime->source_value_3e == -1);
    assert(runtime->source_value_40 == 0 && runtime->source_value_42 == 0);
    assert(runtime->source_value_46 == 0 && runtime->source_value_48 == 0);
    assert(runtime->source_value_58 == 1); /* native placement leaves +0x58 intact */
    assert(runtime->source_value_44 == 0);
    assert(runtime->source_value_58 == 1); /* native placement leaves +0x58 intact */
    assert(runtime->record_value_24 == 0);
    assert(runtime->base_progress == 0 && runtime->producer_cadence == 22);
    assert(runtime->chug_progress == 0);
    assert(runtime->glyph_progress == 0 && runtime->inci_progress == 0);
    assert(runtime->construction_progress == 0 && runtime->production_progress == 0);
    assert(runtime->animation_rate == 1 && runtime->barg_progress == 0.75);

    runtime->record_value_10 = 0;
    runtime->owner_id = -1;
    runtime->source_value_14 = -1;
    runtime->source_location_slot_18 = -1;
    runtime->source_category_slot_60 = -1;
    catalog.items[76].size = 1;
    assert(!game_session_place_building(&session, &catalog, 2, 0, 0,
                                        &site, 0x2c, error, sizeof(error)));
    assert(runtime->record_value_10 == 0 && runtime->owner_id == -1);
    catalog.items[76].size = 0;
    runtime->owner_id = 1;
    assert(!game_session_place_building(&session, &catalog, 2, 0, 0,
                                        &site, 0x2c, error, sizeof(error)));
    assert(runtime->record_value_10 == 0 && runtime->owner_id == 1);
    runtime->owner_id = -1;
    catalog.items[76].building_tone_cost = -1;
    assert(!game_session_place_building(&session, &catalog, 2, 0, 0,
                                        &site, 0x2c, error, sizeof(error)));
    assert(runtime->record_value_10 == 0 && runtime->owner_id == -1);
}

static void test_building_placement_links_every_player_and_source_record(void)
{
    GameSession session = {0};
    PadCatalog catalog = {0};
    IslandLocation site = {0};
    char error[128];
    unsigned int player;

    session.island_count = 1;
    session.islands[0].location_count = GAME_START_PLAYER_COUNT;
    catalog.item_count = PAD_CATALOG_MAX_ITEMS;
    site.kind = ISLAND_LOCATION_PAD_SMALL;
    site.renderer_subtype = 0;

    for (player = 0; player < GAME_START_PLAYER_COUNT; ++player) {
        GameRuntimeLocation *runtime = &session.islands[0].locations[player];
        runtime->renderer_class = 0;
        runtime->record_value_10 = 0;
        runtime->owner_id = -1;
        runtime->source_value_14 = -1;
        runtime->source_location_slot_18 = -1;
        runtime->source_category_slot_60 = -1;
        runtime->source_value_22 = 0;
        runtime->source_flags = 0xa5a5ffffU;
        runtime->record_value_24 = 0x1234;
        runtime->resource_stock[GAME_RESOURCE_BUILD_TONE] = 7;
        runtime->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] = 8;
        runtime->resource_stock[GAME_RESOURCE_MAGIC_TONE] = 9;
        runtime->charge_source_value_30 = 10;
        runtime->source_value_32 = -11;
        runtime->source_value_3a = 12;
        runtime->source_value_3c = 13;
        runtime->source_value_3e = 14;
        runtime->source_value_40 = 15;
        runtime->source_value_42 = 16;
        runtime->source_value_44 = 17;
        runtime->source_value_46 = 18;
        runtime->source_value_48 = 19;
        runtime->source_capacity_4a = 20;
    }

    for (player = 0; player < GAME_START_PLAYER_COUNT; ++player) {
        unsigned int item_id = 0x2cU + player * 16U;
        GameRuntimeLocation *runtime = &session.islands[0].locations[player];
        PadCatalogItem *item = &catalog.items[item_id];

        item->item_id = (uint16_t)item_id;
        item->size = 0;
        item->building_tone_cost = 5;
        item->hit_points = 17;
        runtime->source_value_22 = (uint16_t)(1U << player);
        if (!game_session_place_building(&session, &catalog,
                (uint8_t)player, 0, (uint16_t)player, &site,
                0x2c, error, sizeof(error))) {
            (void)fprintf(stderr, "player %u construction failed: %s\n",
                           player, error);
            assert(0);
        }
        assert(runtime->record_value_10 == (int32_t)item_id);
        assert(runtime->owner_id == (int32_t)player);
        assert(runtime->source_value_14 == (int32_t)player);
        assert(runtime->source_location_slot_18 == (int16_t)player);
        assert(runtime->source_category_slot_60 == 0);
        assert(runtime->source_value_34 == 17);
        assert(runtime->source_flags == ((0xa5a5ffffU & ~0x0fU) | 0x410U));
        assert(runtime->record_value_24 == 0);
        assert(runtime->resource_stock[GAME_RESOURCE_BUILD_TONE] == 0);
        assert(runtime->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] == 0);
        assert(runtime->resource_stock[GAME_RESOURCE_MAGIC_TONE] == 0);
        assert(runtime->charge_source_value_30 == 0);
        assert(runtime->source_value_32 == 1);
        assert(runtime->source_value_3a == 0);
        assert(runtime->source_value_3c == 0);
        assert(runtime->source_value_3e == -1);
        assert(runtime->source_value_40 == 0);
        assert(runtime->source_value_42 == 0);
        assert(runtime->source_value_44 == 0);
        assert(runtime->source_value_46 == 0);
        assert(runtime->source_value_48 == 0);
        assert(runtime->source_capacity_4a == 0);
    }
}

static void test_full_source_record_table_still_completes_construction(void)
{
    GameSession session = {0};
    PadCatalog catalog = {0};
    GameRuntimeLocation *site;
    GamePendingEvent *event;
    unsigned int index;

    session.island_count = 1;
    session.islands[0].location_count = GAME_SOURCE_RECORDS_PER_ISLAND + 1U;
    catalog.item_count = PAD_CATALOG_MAX_ITEMS;
    catalog.items[0x2c].item_id = 0x2c;
    catalog.items[0x2c].size = 0;
    catalog.items[0x2c].building_tone_cost = 1;
    catalog.items[0x2c].hit_points = 17;

    for (index = 0; index < GAME_SOURCE_RECORDS_PER_ISLAND; ++index) {
        GameRuntimeLocation *building = &session.islands[0].locations[index];
        building->owner_id = 0;
        building->record_value_10 = 0x2c;
        building->source_location_slot_18 = (int16_t)index;
        building->source_category_slot_60 = (int16_t)(
            index % GAME_SOURCE_SUBSLOTS_PER_ITEM);
    }

    site = &session.islands[0].locations[GAME_SOURCE_RECORDS_PER_ISLAND];
    site->renderer_class = 0;
    site->record_value_10 = 1;
    site->owner_id = -1;
    site->source_value_14 = -1;
    site->source_location_slot_18 = -1;
    site->source_category_slot_60 = -1;
    site->source_value_22 = 1;
    site->construction_site_size = 0;
    site->resource_stock[GAME_RESOURCE_BUILD_TONE] = 1;

    event = &session.pending_events[0];
    event->active = 1;
    event->player_id = 0;
    event->action_type = 5;
    event->payload_0a = 0;
    event->payload_0e = GAME_SOURCE_RECORDS_PER_ISLAND;
    event->payload_12 = 0x2c;
    session.pending_event_count = 1;

    game_session_update_construction_tasks(&session, &catalog);

    /* Native placement initializes +0x10/+0x14 before the full-table return;
       its caller ignores that return and completes the building. */
    assert(site->record_value_10 == 0x2c);
    assert(site->owner_id == 0 && site->source_value_14 == 0);
    assert(site->source_location_slot_18 == -1);
    assert(site->source_category_slot_60 == -1);
    assert(site->source_value_32 == 1 && site->source_value_34 == 17);
    assert(session.pending_events[0].active == 0);
}

static void test_source_record_capacity_is_per_island(void)
{
    GameSession session = {0};
    PadCatalog catalog = {0};
    IslandLocation site = {0};
    GameRuntimeLocation *runtime;
    char error[128];
    unsigned int index;

    session.island_count = 2;
    session.islands[0].location_count = GAME_SOURCE_RECORDS_PER_ISLAND;
    session.islands[1].location_count = 1;
    catalog.item_count = PAD_CATALOG_MAX_ITEMS;
    catalog.items[0x2c + 2 * 16].item_id = 0x2c + 2 * 16;
    catalog.items[0x2c + 2 * 16].size = 0;
    catalog.items[0x2c + 2 * 16].building_tone_cost = 1;
    catalog.items[0x2c + 2 * 16].hit_points = 17;

    for (index = 0; index < GAME_SOURCE_RECORDS_PER_ISLAND; ++index) {
        GameRuntimeLocation *building = &session.islands[0].locations[index];
        building->owner_id = 2;
        building->record_value_10 = 0x2c + 2 * 16;
        building->source_location_slot_18 = (int16_t)index;
    }

    runtime = &session.islands[1].locations[0];
    runtime->renderer_class = 0;
    runtime->record_value_10 = 0;
    runtime->owner_id = -1;
    runtime->source_value_14 = -1;
    runtime->source_location_slot_18 = -1;
    runtime->source_category_slot_60 = -1;
    runtime->source_value_22 = 1U << 2;
    runtime->construction_site_size = 0;
    site.kind = ISLAND_LOCATION_PAD_SMALL;
    site.renderer_subtype = 0;

    assert(game_session_place_building(&session, &catalog, 2, 1, 0,
        &site, 0x2c, error, sizeof(error)));
    assert(runtime->owner_id == 2);
    assert(runtime->source_value_14 == 2);
    assert(runtime->source_location_slot_18 == 0);
    assert(runtime->source_category_slot_60 == 0);
}

static void test_player_source_building_keeps_native_id_for_island_state(void)
{
    GameSession session = {0};
    GameRuntimeIsland *island;
    GameRuntimeLocation *marker;
    GameRuntimeLocation *source;

    session.island_count = 1;
    session.config.difficulty = 0;
    island = &session.islands[0];
    island->location_count = 2;
    marker = &island->locations[0];
    marker->renderer_class = 1;
    marker->record_value_10 = 5;
    marker->owner_id = 4;
    marker->source_value_14 = 4;
    source = &island->locations[1];
    source->renderer_class = 0;
    source->record_value_10 = 0x2c + 16;
    source->owner_id = 1;
    source->source_value_14 = 1;

    /* Native +0x10 remains 0x2c for every player; the runtime stores the
       owner-specific catalog ID, so gameplay predicates must normalize it. */
    game_session_recalculate_leviathan_island(&session, 0);
    assert(island->leviathan_admissible == 0);
    assert(island->leviathan_marker_count == 1);
}

static void test_construction_assignment_matches_source_candidate_guards(void)
{
    GameSession session = {0};
    PadCatalog catalog = {0};
    GameRuntimeLocation *site;
    GameRuntimeLocation *hall;
    GameFloaterStart *floater;
    GameFloaterStart *other_floater;
    int slot;

    session.island_count = 1;
    session.floater_count = 2;
    session.islands[0].location_count = 2;
    session.economy[0].hall_island_index = 0;
    session.economy[0].hall_location_index = 1;
    site = &session.islands[0].locations[0];
    site->renderer_class = 0;
    site->record_value_10 = 1;
    site->record_value_24 = 5;
    site->owner_id = -1;
    site->source_value_14 = -1;
    site->source_value_22 = 1;
    site->construction_site_size = 0;
    hall = &session.islands[0].locations[1];
    hall->renderer_class = 0;
    hall->record_value_10 = 0x2a;
    hall->owner_id = 0;
    hall->resource_stock[GAME_RESOURCE_BUILD_TONE] = 1;

    catalog.item_count = 0x26;
    catalog.items[0x25].item_id = 0x25;
    catalog.items[0x25].size = 0;
    catalog.items[0x25].building_tone_cost = 2;
    catalog.items[0x25].maintenance_tone_cost = 1;
    session.economy[0].source_maintenance_budget = 1;

    floater = &session.floaters[0];
    floater->is_active = 1;
    floater->owner_slot = 0;
    floater->island_index = 0;
    floater->type_index = 0;
    floater->source_subtype = 0;
    floater->source_link_0c = -1;
    floater->linked_task_slot = -1;
    floater->carried_resource_code = 0;
    other_floater = &session.floaters[1];
    other_floater->owner_slot = 0;
    other_floater->island_index = 0;
    other_floater->type_index = 0;
    other_floater->source_subtype = 0;
    other_floater->source_link_0c = -1;
    other_floater->linked_task_slot = -1;
    other_floater->carried_resource_code = 0;

    slot = game_session_pending_event_add(&session, 0, 0, 5, 0, 0, 0x25);
    assert(slot == 0);

    /* FUN_00422031 case 5 validates site visibility/ownership, pad fit,
       maintenance budget, and an accessible Build Tone source. REA evidence:
       ev_c3e639203801f9e7012f337ff4f53cd454b839fc47ba82be8af18534e5ed1081. */
    game_session_assign_local_resource_tasks(&session, &catalog);
    assert(floater->active_order_action == 4);
    assert(floater->linked_task_slot == slot);
    assert(floater->movement_state == 3);
    assert(session.pending_events[slot].assigned_floater_count == 1);

    other_floater->is_active = 1;
    other_floater->owner_slot = 1;
    game_session_assign_local_resource_tasks(&session, &catalog);
    assert(other_floater->active_order_action == 0);
    other_floater->owner_slot = 0;

    /* A second worker cannot over-reserve the remaining Build Tone cost. */
    site->resource_stock[GAME_RESOURCE_BUILD_TONE] = 1;
    game_session_assign_local_resource_tasks(&session, &catalog);
    assert(other_floater->active_order_action == 0);

    /* FUN_004526de / FUN_00452794 reject an invisible site and over-budget pad. */
    site->resource_stock[GAME_RESOURCE_BUILD_TONE] = 0;
    session.pending_events[slot].assigned_floater_count = 0;
    site->source_value_22 = 0;
    game_session_assign_local_resource_tasks(&session, &catalog);
    assert(other_floater->active_order_action == 0);
    site->source_value_22 = 1;
    site->source_value_14 = 1;
    game_session_assign_local_resource_tasks(&session, &catalog);
    assert(other_floater->active_order_action == 0);
    site->source_value_14 = -1;
    session.economy[0].source_maintenance_budget = 0;
    game_session_assign_local_resource_tasks(&session, &catalog);
    assert(other_floater->active_order_action == 0);

    /* The task cannot claim a pad larger than the marked construction site. */
    session.economy[0].source_maintenance_budget = 1;
    catalog.items[0x25].size = 1;
    game_session_assign_local_resource_tasks(&session, &catalog);
    assert(other_floater->active_order_action == 0);

    catalog.items[0x25].size = 0;
    hall->resource_stock[GAME_RESOURCE_BUILD_TONE] = 0;
    game_session_assign_local_resource_tasks(&session, &catalog);
    assert(other_floater->active_order_action == 0);
}

static void test_construction_task_delivers_cost_before_deferred_placement(void)
{
    GameSession session = {0};
    PadCatalog catalog = {0};
    GameRuntimeLocation *site;
    GameRuntimeLocation *hall;
    GameFloaterStart *floater;
    unsigned int tick;
    int slot;

    session.island_count = 1;
    session.floater_count = 1;
    session.islands[0].location_count = 2;
    session.economy[0].hall_island_index = 0;
    session.economy[0].hall_location_index = 1;
    site = &session.islands[0].locations[0];
    site->renderer_class = 0;
    site->record_value_10 = 1;
    site->record_value_24 = 5;
    site->owner_id = -1;
    site->source_value_14 = -1;
    site->source_value_22 = 1;
    site->construction_site_size = 0;
    site->x = 200;
    site->y = 120;
    hall = &session.islands[0].locations[1];
    hall->renderer_class = 0;
    hall->record_value_10 = 0x2a;
    hall->owner_id = 0;
    hall->resource_stock[GAME_RESOURCE_BUILD_TONE] = 2;
    hall->x = 100;
    hall->y = 120;

    catalog.item_count = 0x26;
    catalog.items[0x25].item_id = 0x25;
    catalog.items[0x25].size = 0;
    catalog.items[0x25].hit_points = 4;
    catalog.items[0x25].building_tone_cost = 2;

    floater = &session.floaters[0];
    floater->is_active = 1;
    floater->owner_slot = 0;
    floater->island_index = 0;
    floater->type_index = 0;
    floater->source_subtype = 0;
    floater->source_link_0c = -1;
    floater->linked_task_slot = -1;
    floater->movement_speed = 30;
    floater->x = hall->x;
    floater->y = hall->y;

    slot = game_session_pending_event_add(&session, 0, 0, 5, 0, 0, 0x25);
    assert(slot == 0);

    /* Match window_proc's order: deferred construction update, then movement. */
    for (tick = 1; tick < 300 && site->owner_id == -1; ++tick) {
        game_session_update_construction_tasks(&session, &catalog);
        game_session_tick_floater_moves(&session, tick, &catalog);
        if (site->resource_stock[GAME_RESOURCE_BUILD_TONE] == 1)
            assert(site->owner_id == -1 && site->record_value_10 == 1);
    }

    assert(tick < 300);
    assert(site->owner_id == 0);
    assert(site->source_value_14 == 0);
    assert(site->record_value_10 == 0x25);
    assert(site->resource_stock[GAME_RESOURCE_BUILD_TONE] == 0);
    assert(hall->resource_stock[GAME_RESOURCE_BUILD_TONE] == 0);
    assert(session.pending_events[slot].active == 0);
    assert(session.pending_event_count == 0);
    assert(floater->active_order_action == 0);
    assert(floater->linked_task_slot == -1);
    assert(floater->carried_resource_code == 0);
}

static void test_construction_completes_on_native_empty_status_one_site(void)
{
    GameSession session = {0};
    PadCatalog catalog = {0};
    GameRuntimeLocation *site;
    int slot;

    session.island_count = 1;
    session.islands[0].location_count = 1;
    site = &session.islands[0].locations[0];
    site->renderer_class = 0;
    site->record_value_10 = 1;
    site->record_value_24 = 5;
    site->owner_id = -1;
    site->source_value_14 = -1;
    site->source_value_22 = 1U << 2;
    site->construction_site_size = 0;

    catalog.item_count = 77;
    catalog.items[76].item_id = 76; /* base 0x2c, player 2 */
    catalog.items[76].size = 0;
    catalog.items[76].building_tone_cost = 1;
    catalog.items[76].hit_points = 17;

    slot = game_session_pending_event_add(&session, 2, 0, 5, 0, 0, 0x2c);
    assert(slot == 0);
    game_session_update_construction_tasks(&session, &catalog);
    assert(session.pending_events[slot].active == 1);
    assert(site->owner_id == -1 && site->record_value_10 == 1);

    site->resource_stock[GAME_RESOURCE_BUILD_TONE] = 1;
    game_session_update_construction_tasks(&session, &catalog);
    assert(site->record_value_10 == 76);
    assert(site->owner_id == 2);
    assert(site->source_value_14 == 2);
    assert(site->source_value_34 == 17);
    assert(site->source_value_32 == 1);
    assert(site->source_flags == 0x410);
    assert(session.pending_events[slot].active == 0);
}

static void test_cancelled_construction_releases_assigned_floater(void)
{
    GameSession session = {0};
    PadCatalog catalog = {0};
    GameRuntimeLocation *site;
    GameRuntimeLocation *hall;
    GameFloaterStart *floater;
    GamePendingEvent expected;
    int slot;

    session.island_count = 1;
    session.floater_count = 1;
    session.islands[0].location_count = 2;
    session.economy[0].hall_island_index = 0;
    session.economy[0].hall_location_index = 1;
    site = &session.islands[0].locations[0];
    site->source_value_22 = 1;
    site->owner_id = -1;
    site->source_value_14 = -1;
    hall = &session.islands[0].locations[1];
    hall->record_value_10 = 0x2a;
    hall->owner_id = 0;
    hall->resource_stock[GAME_RESOURCE_BUILD_TONE] = 1;
    catalog.item_count = 0x26;
    catalog.items[0x25].item_id = 0x25;
    catalog.items[0x25].size = 0;
    catalog.items[0x25].building_tone_cost = 2;
    floater = &session.floaters[0];
    floater->is_active = 1;
    floater->owner_slot = 0;
    floater->island_index = 0;
    floater->source_link_0c = -1;
    floater->linked_task_slot = -1;

    slot = game_session_pending_event_add(&session, 0, 0, 5, 0, 0, 0x25);
    assert(slot == 0);
    game_session_assign_local_resource_tasks(&session, &catalog);
    assert(floater->active_order_action == 4);
    assert(floater->linked_task_slot == slot);
    assert(session.pending_events[slot].assigned_floater_count == 1);
    expected = session.pending_events[slot];

    /* FUN_00466533 detaches workers referencing the cancelled CONSTR slot. */
    assert(game_session_dispatch_task_command(&session, (uint8_t)slot,
                                              12, &expected));
    assert(session.pending_event_count == 0);
    assert(session.pending_events[slot].active == 0);
    assert(floater->active_order_action == 0);
    assert(floater->linked_task_slot == -1);
    assert(floater->order_target_location == -1);
    assert(floater->movement_state == 0);
    assert(floater->has_move_order == 0);
    assert(floater->has_wander_order == 1);
    assert(site->owner_id == -1 && site->source_value_14 == -1);
    assert(site->record_value_10 == 0);
    assert(hall->resource_stock[GAME_RESOURCE_BUILD_TONE] == 1);

    game_session_assign_local_resource_tasks(&session, &catalog);
    assert(floater->active_order_action == 0);
    assert(hall->resource_stock[GAME_RESOURCE_BUILD_TONE] == 1);
}
