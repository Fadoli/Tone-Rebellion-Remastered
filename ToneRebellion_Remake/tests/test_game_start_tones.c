#include "game_start.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

static void add_marker(IslandData *island, unsigned int index, uint16_t item_id)
{
    IslandLocation *location = &island->locations[index];
    memset(location, 0, sizeof(*location));
    location->id = (uint16_t)index;
    location->renderer_class = 1;
    location->renderer_variant = item_id;
    island->location_count = (uint16_t)(index + 1U);
}

static void test_primary_markers_and_table_candidates(void)
{
    IslandData islands[4];
    int32_t shapes[4] = {0, 0, 0, 0};
    GameStartToneDistribution distribution;
    ToneRng rng;
    char error[128];
    unsigned int i;

    memset(islands, 0, sizeof(islands));
    for (i = 0; i < 4; ++i) {
        add_marker(&islands[i], 0, 0);
        add_marker(&islands[i], 1, 0);
        add_marker(&islands[i], 2, 0);
        add_marker(&islands[i], 3, 0);
    }
    tone_rng_seed(&rng, 1);
    assert(game_start_distribute_tones(islands, shapes, 4, 0, 0, &rng,
                                       &distribution, error, sizeof(error)));
    assert(distribution.placement_count == 4);
    assert(distribution.placements[0].location_index == 3);
    assert(distribution.placements[1].location_index == 0);
    assert(distribution.placements[2].location_index == 3);
    assert(distribution.placements[3].location_index == 0);
    assert(distribution.placements[0].owner_id == 4);
    assert(distribution.placements[1].item_id == 6);
    assert(distribution.placements[2].item_id == 6);
    assert(distribution.placements[3].item_id == 6);
}

static void test_alternate_mode_adds_opposite_marker(void)
{
    IslandData islands[4];
    int32_t shapes[4] = {0, 0, 0, 0};
    GameStartToneDistribution distribution;
    ToneRng rng;
    char error[128];
    unsigned int i;

    memset(islands, 0, sizeof(islands));
    for (i = 0; i < 4; ++i) {
        add_marker(&islands[i], 0, 0);
        add_marker(&islands[i], 1, 0);
        add_marker(&islands[i], 2, 0);
        add_marker(&islands[i], 3, 0);
    }
    tone_rng_seed(&rng, 1);
    assert(game_start_distribute_tones(islands, shapes, 4, 0, 1, &rng,
                                       &distribution, error, sizeof(error)));
    assert(distribution.placement_count == 8);
    assert(distribution.placements[0].island_index == 0);
    assert(distribution.placements[0].location_index == 3);
    assert(distribution.placements[1].island_index == 0);
    assert(distribution.placements[1].location_index == 0);
    assert(distribution.placements[2].island_index == 1);
    assert(distribution.placements[2].location_index == 0);
    assert(distribution.placements[3].island_index == 1);
    assert(distribution.placements[3].location_index == 3);
}

static void test_runtime_item_balance_and_five_marker_limit(void)
{
    IslandData islands[5];
    int32_t shapes[5] = {0, 1, 0, 0, 0};
    GameStartToneDistribution distribution;
    ToneRng rng;
    char error[128];
    unsigned int i;

    memset(islands, 0, sizeof(islands));
    for (i = 0; i < 4; ++i) add_marker(&islands[0], i, 0);
    for (i = 0; i < 4; ++i) add_marker(&islands[1], i, 0);
    islands[1].locations[4] = islands[1].locations[0];
    islands[1].locations[4].renderer_class = 3;
    islands[1].locations[4].renderer_variant = 7;
    islands[1].locations[5] = islands[1].locations[0];
    islands[1].locations[5].renderer_class = 0;
    islands[1].locations[5].renderer_variant = 8;
    islands[1].location_count = 6;
    for (i = 0; i < 6; ++i) add_marker(&islands[4], i, 0);
    tone_rng_seed(&rng, 7);
    assert(game_start_distribute_tones(islands, shapes, 5, 0, 0, &rng,
                                       &distribution, error, sizeof(error)));
    assert(distribution.placement_count == 3);
    assert(distribution.placements[1].island_index == 1);
    assert(distribution.placements[1].item_id == 8); /* class 3 retains item 7; class 0 is reset first */
    assert(distribution.placements[2].island_index == 4);
    assert(distribution.placements[2].location_index < 5); /* FUN_00464b9e considers only the first five */
}

static void test_rejects_invalid_shape_without_partial_output(void)
{
    IslandData islands[1];
    int32_t shapes[1] = {16};
    GameStartToneDistribution distribution;
    GameStartToneDistribution before;
    ToneRng rng;
    char error[128];

    memset(islands, 0, sizeof(islands));
    add_marker(&islands[0], 0, 0);
    memset(&distribution, 0xa5, sizeof(distribution));
    before = distribution;
    tone_rng_seed(&rng, 1);
    assert(!game_start_distribute_tones(islands, shapes, 1, 0, 0, &rng,
                                        &distribution, error, sizeof(error)));
    assert(strstr(error, "island 0: island shape ID") != NULL);
    assert(memcmp(&distribution, &before, sizeof(distribution)) == 0);
}

int main(void)
{
    test_primary_markers_and_table_candidates();
    test_alternate_mode_adds_opposite_marker();
    test_runtime_item_balance_and_five_marker_limit();
    test_rejects_invalid_shape_without_partial_output();
    (void)puts("game start tone distribution tests passed");
    return 0;
}
