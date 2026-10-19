#include "game_start.h"

#include <stdio.h>
#include <string.h>

static void set_error(char *error, size_t capacity, const char *message,
                      unsigned int player)
{
    if (error == NULL || capacity == 0) return;
    if (player == GAME_START_PLAYER_COUNT) {
        (void)snprintf(error, capacity, "%s", message);
    } else {
        (void)snprintf(error, capacity, "player %u: %s", player, message);
    }
    error[capacity - 1] = '\0';
}

static void set_island_error(char *error, size_t capacity, const char *message,
                             unsigned int island)
{
    if (error == NULL || capacity == 0) return;
    (void)snprintf(error, capacity, "island %u: %s", island, message);
    error[capacity - 1] = '\0';
}

static const int8_t marker_item_table_a[16] = {
    0, 1, -1, -1, 3, 2, 0, 2, 1, 1, 3, 3, 1, 2, -1, 0
};

static const int8_t marker_item_table_b[16] = {
    -1, 2, 3, 1, 3, 1, 0, 2, 0, 0, 2, 3, 0, -1, 0, 0
};

static unsigned int count_marker_item_ids(const IslandData *island,
                                          const GameStartToneDistribution *placements,
                                          unsigned int island_index,
                                          unsigned int item_id)
{
    unsigned int count = 0;
    unsigned int i;

    for (i = 0; i < island->location_count; ++i) {
        const IslandLocation *location = &island->locations[i];
        /* FUN_004500c4 clears +0x10 except on class 3 before placement begins. */
        unsigned int current = location->renderer_class == 3
            ? location->renderer_variant
            : 0U;
        if (current == item_id) ++count;
    }
    for (i = 0; i < placements->placement_count; ++i) {
        const GameStartTonePlacement *placement = &placements->placements[i];
        if (placement->island_index == island_index && placement->item_id == item_id) ++count;
    }
    return count;
}

static int choose_marker_item_id(const IslandData *island,
                                 const GameStartToneDistribution *placements,
                                 unsigned int island_index,
                                 int32_t shape_id,
                                 unsigned int home_island_index,
                                 ToneRng *rng,
                                 uint16_t *item_id)
{
    unsigned char allowed[4] = {0, 0, 0, 0};
    unsigned char missing[4];
    unsigned int allowed_count = 0;
    unsigned int missing_count = 0;
    unsigned int candidate_index;
    int random_index;

    if (shape_id < 0 || shape_id >= 16) return 0;
    if (island_index == home_island_index) {
        for (candidate_index = 0; candidate_index < 4; ++candidate_index) allowed[candidate_index] = 1;
    } else {
        int first = marker_item_table_a[shape_id];
        int second = marker_item_table_b[shape_id];
        if (first >= 0 && first < 4) allowed[first] = 1;
        if (second >= 0 && second < 4) allowed[second] = 1;
    }
    for (candidate_index = 0; candidate_index < 4; ++candidate_index) {
        if (!allowed[candidate_index]) continue;
        ++allowed_count;
        if (count_marker_item_ids(island, placements, island_index, 6U + candidate_index) == 0) {
            missing[missing_count++] = (unsigned char)candidate_index;
        }
    }
    if (allowed_count == 0) return 0;
    if (missing_count == 0) {
        for (candidate_index = 0; candidate_index < 4; ++candidate_index) {
            if (allowed[candidate_index]) missing[missing_count++] = (unsigned char)candidate_index;
        }
    }
    random_index = tone_rng_bounded(rng, (int32_t)missing_count);
    if (random_index < 0 || (unsigned int)random_index >= missing_count) return 0;
    *item_id = (uint16_t)(6U + missing[random_index]);
    return 1;
}

int game_start_distribute_tones(const IslandData *islands,
                                const int32_t *shape_ids,
                                size_t island_count,
                                size_t home_island_index,
                                uint32_t mode,
                                ToneRng *rng,
                                GameStartToneDistribution *out,
                                char *error, size_t error_capacity)
{
    GameStartToneDistribution result;
    unsigned int island_index;

    if (error != NULL && error_capacity != 0) error[0] = '\0';
    if (islands == NULL || shape_ids == NULL || rng == NULL || out == NULL) {
        set_error(error, error_capacity, "islands, shape IDs, RNG and output are required",
                  GAME_START_PLAYER_COUNT);
        return 0;
    }
    if (island_count > WORLD_MAP_MAX_ISLANDS || home_island_index >= island_count) {
        set_error(error, error_capacity, "island count or home island index is out of range",
                  GAME_START_PLAYER_COUNT);
        return 0;
    }
    memset(&result, 0, sizeof(result));

    for (island_index = 0; island_index < island_count; ++island_index) {
        const IslandData *island = &islands[island_index];
        uint16_t markers[5];
        unsigned int marker_count = 0;
        unsigned int location_index;
        unsigned int selection_count;
        unsigned int selection;

        if (island->location_count > ISLAND_DATA_MAX_LOCATIONS) {
            set_island_error(error, error_capacity, "location count exceeds the original capacity", island_index);
            return 0;
        }
        if (shape_ids[island_index] < 0 || shape_ids[island_index] >= 16) {
            set_island_error(error, error_capacity, "island shape ID is outside the verified item tables", island_index);
            return 0;
        }
        for (location_index = 0; location_index < island->location_count && marker_count < 5; ++location_index) {
            if (island->locations[location_index].renderer_class == 1) {
                markers[marker_count++] = (uint16_t)location_index;
            }
        }
        if (marker_count == 0) continue;

        selection_count = island_index < GAME_START_PLAYER_COUNT
            ? (((mode & 1U) != 0 && marker_count > 1) ? 2U : 1U)
            : 1U;
        for (selection = 0; selection < selection_count; ++selection) {
            unsigned int marker_ordinal;
            uint16_t item_id;
            GameStartTonePlacement *placement;

            if (island_index >= GAME_START_PLAYER_COUNT) {
                int chosen = tone_rng_bounded(rng, (int32_t)marker_count);
                if (chosen < 0 || (unsigned int)chosen >= marker_count) {
                    set_island_error(error, error_capacity, "random marker index is out of range", island_index);
                    return 0;
                }
                marker_ordinal = (unsigned int)chosen;
            } else {
                int primary_is_last = (island_index & 1U) == 0;
                if (selection == 0) marker_ordinal = primary_is_last ? marker_count - 1U : 0U;
                else marker_ordinal = primary_is_last ? 0U : marker_count - 1U;
            }
            if (result.placement_count >= GAME_START_MAX_DISTRIBUTED_TONES) {
                set_island_error(error, error_capacity, "distribution exceeds original marker capacity", island_index);
                return 0;
            }
            if (!choose_marker_item_id(island, &result, island_index, shape_ids[island_index],
                                       (unsigned int)home_island_index, rng, &item_id)) {
                set_island_error(error, error_capacity, "no table-selected item can be chosen for marker", island_index);
                return 0;
            }
            placement = &result.placements[result.placement_count++];
            placement->island_index = (uint8_t)island_index;
            placement->location_index = markers[marker_ordinal];
            placement->item_id = item_id;
            placement->owner_id = 4;
        }
    }
    *out = result;
    return 1;
}
