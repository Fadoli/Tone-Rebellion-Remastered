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
    assert(runtime->base_progress == 0 && runtime->producer_cadence == 0);
    assert(runtime->chug_progress == 0);
    assert(runtime->glyph_progress == 0 && runtime->inci_progress == 0);
    assert(runtime->construction_progress == 0 && runtime->production_progress == 0);
    assert(runtime->animation_rate == 1 && runtime->barg_progress == 0.0);

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
