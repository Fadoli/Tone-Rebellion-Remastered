#include "game_start.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

static IslandLocation location(uint16_t id, uint16_t x, uint16_t y,
                               uint8_t renderer_class, uint16_t variant)
{
    IslandLocation value;
    memset(&value, 0, sizeof(value));
    value.id = id;
    value.x = x;
    value.y = y;
    value.renderer_class = renderer_class;
    value.renderer_variant = variant;
    return value;
}

static void populate_island(IslandData *island, uint16_t base_x)
{
    memset(island, 0, sizeof(*island));
    island->location_count = 6;
    island->locations[0] = location(0, base_x + 100, 100, 1, 0);
    island->locations[1] = location(1, base_x + 200, 100, 1, 0);
    island->locations[2] = location(2, base_x + 300, 100, 1, 0);
    island->locations[3] = location(3, base_x + 400, 100, 1, 0);
    island->locations[4] = location(4, base_x + 260, 120, 0, 0);
    island->locations[5] = location(5, base_x + 200, 101, 0, 0);
}

static void test_classic_four_player_assignment(void)
{
    IslandData islands[4];
    GameStartSetup setup;
    char error[128];
    unsigned int i;

    for (i = 0; i < 4; ++i) populate_island(&islands[i], (uint16_t)(i * 500));
    assert(game_start_assign_locations(islands, 4, 0, 0, &setup, error, sizeof(error)));
    for (i = 0; i < GAME_START_PLAYER_COUNT; ++i) {
        uint16_t expected_site = (i & 1U) != 0 ? 4 : 5;
        int expected_left = (int)islands[i].locations[expected_site].x - 0x140;
        if (expected_left < 0) expected_left = 0;
        if (expected_left > 0x780) expected_left = 0x780;
        assert(setup.players[i].island_index == i);
        assert(setup.players[i].marker_location_index == (i & 1U ? 3 : 0));
        assert(setup.players[i].nearest_site_location_index == expected_site);
        assert(setup.players[i].nearest_site_x == islands[i].locations[expected_site].x);
        assert(setup.players[i].nearest_site_y == (expected_site == 5 ? 101 : 120));
        assert(setup.players[i].marker_x == islands[i].locations[i & 1U ? 3 : 0].x);
        assert(setup.players[i].marker_y == 100);
        assert(setup.players[i].initial_pad_item_id == 0x2a);
        assert(setup.players[i].floater_type_index == i);
        assert(setup.players[i].floater_count == 4);
        assert(setup.players[i].view_left == expected_left);
        assert(setup.players[i].view_right == setup.players[i].view_left + 0x27f);
    }
}

static void test_chebyshev_distance_and_first_tie(void)
{
    IslandData islands[4];
    GameStartSetup setup;
    char error[128];
    unsigned int i;

    for (i = 0; i < 4; ++i) populate_island(&islands[i], 0);
    islands[0].locations[0] = location(0, 100, 100, 1, 0);
    islands[0].locations[4] = location(4, 120, 110, 0, 0);
    islands[0].locations[5] = location(5, 110, 120, 0, 0);
    assert(game_start_assign_locations(islands, 4, 0, 0, &setup, error, sizeof(error)));
    /* Both are 20 units away under max(dx,dy); lower source row wins the tie. */
    assert(setup.players[0].nearest_site_location_index == 4);
}

static void test_rejects_missing_pad_without_partial_output(void)
{
    IslandData islands[4];
    GameStartSetup setup;
    GameStartSetup before;
    char error[128];
    unsigned int i;

    for (i = 0; i < 4; ++i) populate_island(&islands[i], 0);
    islands[2].locations[0].renderer_class = 0;
    islands[2].locations[0].renderer_variant = 1;
    islands[2].locations[1].renderer_class = 0;
    islands[2].locations[1].renderer_variant = 1;
    islands[2].locations[2].renderer_class = 0;
    islands[2].locations[2].renderer_variant = 1;
    islands[2].locations[3].renderer_class = 0;
    islands[2].locations[3].renderer_variant = 1;
    memset(&setup, 0xa5, sizeof(setup));
    before = setup;
    assert(!game_start_assign_locations(islands, 4, 0, 0, &setup, error, sizeof(error)));
    assert(strstr(error, "player 2: required class-1 start marker is missing") != NULL);
    assert(memcmp(&setup, &before, sizeof(setup)) == 0);
}

static void test_alternate_island_rule(void)
{
    IslandData islands[4];
    GameStartSetup setup;
    char error[128];
    unsigned int i;

    for (i = 0; i < 4; ++i) populate_island(&islands[i], 0);
    assert(game_start_assign_locations(islands, 4, 1, 1, &setup, error, sizeof(error)));
    assert(setup.players[0].island_index == 1);
    assert(setup.players[1].island_index == 2);
    assert(setup.players[2].island_index == 1);
    assert(setup.players[3].island_index == 2);
    assert(setup.players[0].marker_location_index == 1);
    assert(setup.players[1].marker_location_index == 1);
    assert(setup.players[2].marker_location_index == 2);
    assert(setup.players[3].marker_location_index == 2);
}

int main(void)
{
    test_classic_four_player_assignment();
    test_chebyshev_distance_and_first_tie();
    test_rejects_missing_pad_without_partial_output();
    test_alternate_island_rule();
    (void)puts("game start unit tests passed");
    return 0;
}
