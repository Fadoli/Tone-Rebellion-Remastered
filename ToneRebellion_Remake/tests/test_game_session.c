#include "game_session.h"
#include "building_render.h"
#include "island_render_rules.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

static void set_location(IslandData *island, unsigned int index,
                         uint8_t renderer_class, uint16_t x, uint16_t y,
                         uint16_t initial_value)
{
    IslandLocation *location = &island->locations[index];
    memset(location, 0, sizeof(*location));
    location->id = (uint16_t)index;
    location->x = x;
    location->y = y;
    location->renderer_class = renderer_class;
    location->renderer_variant = initial_value;
    island->location_count = (uint16_t)(index + 1U);
}

static void make_world(WorldDefinition *world, IslandData islands[5])
{
    unsigned int island_index;

    memset(world, 0, sizeof(*world));
    memset(islands, 0, sizeof(IslandData) * 5U);
    world->island_count = 5;
    world->bridge_count = 1;
    world->bridges[0].island_a = 0;
    world->bridges[0].island_b = 1;
    for (island_index = 0; island_index < 5; ++island_index) {
        IslandData *island = &islands[island_index];
        unsigned int marker;
        uint16_t base_x = (uint16_t)(island_index * 100U);
        world->islands[island_index].shape_id = island_index == 1 || island_index == 4 ? 1 : 0;
        for (marker = 0; marker < 4; ++marker) {
            set_location(island, marker, 1, (uint16_t)(base_x + 300U + marker * 20U), 100, 77);
        }
        for (marker = 0; marker < 8; ++marker) {
            set_location(island, marker + 4U, 0,
                         (uint16_t)(base_x + 300U + marker * 20U),
                         (uint16_t)(102U + marker), 99);
        }
    }
    set_location(&islands[0], 12, 2, 10, 10, 0);
    set_location(&islands[1], 12, 2, 10, 10, 0);
    set_location(&islands[4], 12, 2, 10, 10, 0);
    set_location(&islands[4], 13, 3, 10, 10, 7);
}

static void test_session_initializes_player_starts_and_runtime_items(void)
{
    WorldDefinition world;
    IslandData islands[5];
    GameSessionConfig config;
    GameSession session;
    char error[160];
    unsigned int player;

    make_world(&world, islands);
    memset(&config, 0, sizeof(config));
    config.world_index = 1;
    config.difficulty = 2;
    config.selected_tribe = 3;
    config.home_island_index = 0;
    config.random_seed = 1;
    if (!game_session_initialize(&world, islands, &config, &session,
                                 error, sizeof(error))) {
        (void)fprintf(stderr, "session initialization failed: %s\n", error);
        assert(0);
    }

    assert(session.config.world_index == 1);
    assert(session.config.difficulty == 2);
    assert(session.config.selected_tribe == 3);
    assert(session.island_count == 5);
    assert(session.floater_count == 16);
    assert(session.tone_placements.placement_count == 5);
    for (player = 0; player < GAME_START_PLAYER_COUNT; ++player) {
        const GamePlayerStart *start = &session.player_starts.players[player];
        const GameRuntimeLocation *pad = &session.islands[start->island_index]
            .locations[start->nearest_site_location_index];
        const GameFloaterStart *floater = &session.floaters[player * GAME_START_FLOATERS_PER_PLAYER];
        assert(pad->record_value_10 ==
               GAME_START_INITIAL_PAD_ITEM_ID + (int32_t)player * 16);
        assert(pad->owner_id == (int32_t)player);
        assert(pad->source_flags == 0x410);
        assert(pad->chug_progress == 0 && pad->glyph_progress == 0);
        assert(pad->animation_rate == 1);
        assert(floater->island_index == start->island_index);
        assert(floater->type_index == player);
        assert(floater->x == start->marker_x);
        assert(floater->y == start->marker_y);
    }
    assert(session.islands[0].locations[12].record_value_10 == 2);
    assert(session.islands[1].locations[12].record_value_10 == 2);
    assert(session.islands[0].locations[12].bridge_neighbor_island == 1);
    assert(session.islands[1].locations[12].bridge_neighbor_island == 0);
    assert(session.islands[4].locations[12].record_value_10 == 0); /* unmatched class-2 site becomes class 0 */
    assert(session.islands[4].locations[12].bridge_neighbor_island == -1);
    assert(session.islands[4].locations[13].record_value_10 == 7);
    assert(session.islands[4].locations[13].owner_id == -1);
    assert(session.class0_assignments == 9);
    {
        unsigned int island_index;
        unsigned int special_site_count = 0;
        unsigned int link_site_count = 0;
        for (island_index = 0; island_index < session.island_count; ++island_index) {
            unsigned int location_index;
            for (location_index = 0;
                 location_index < session.islands[island_index].location_count;
                 ++location_index) {
                const GameRuntimeLocation *location =
                    &session.islands[island_index].locations[location_index];
                if (location->record_value_10 != 1) continue;
                if (location->record_value_24 == 5) ++special_site_count;
                if (location->record_value_24 >= 6) ++link_site_count;
            }
        }
        assert(special_site_count == world.bridge_count);
        assert(link_site_count == 2U * (world.island_count - 1U));
    }
    assert(islands[1].locations[4].renderer_variant == 99);
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

static void test_initialization_is_transactional_on_bad_world(void)
{
    WorldDefinition world;
    IslandData islands[5];
    GameSessionConfig config;
    GameSession session;
    GameSession before;
    char error[160];

    make_world(&world, islands);
    world.island_count = 3;
    memset(&config, 0, sizeof(config));
    config.home_island_index = 0;
    memset(&session, 0xa5, sizeof(session));
    before = session;
    assert(!game_session_initialize(&world, islands, &config, &session,
                                    error, sizeof(error)));
    assert(strstr(error, "cannot support the four start slots") != NULL);
    assert(memcmp(&session, &before, sizeof(session)) == 0);
}

int main(void)
{
    test_session_initializes_player_starts_and_runtime_items();
    test_item_animation_uses_source_flags_and_per_object_counters();
    test_tone_pool_uses_two_source_counter_sequences();
    test_active_cons_and_prod_counters_finish_at_source_limits();
    test_initialization_is_transactional_on_bad_world();
    (void)puts("game session unit tests passed");
    return 0;
}
