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

static unsigned int distance_chebyshev(const IslandLocation *a,
                                       const IslandLocation *b)
{
    unsigned int dx = a->x > b->x ? (unsigned int)a->x - b->x : (unsigned int)b->x - a->x;
    unsigned int dy = a->y > b->y ? (unsigned int)a->y - b->y : (unsigned int)b->y - a->y;
    return dx > dy ? dx : dy;
}

static int find_marker(const IslandData *island, unsigned int player,
                       uint32_t mode, uint16_t *marker_index)
{
    unsigned int ordinal = 0;
    unsigned int wanted;
    unsigned int index;

    if ((mode & 1U) == 0) {
        wanted = (player & 1U) == 0 ? 0U : 3U;
    } else {
        wanted = player / 2U + 1U;
    }

    for (index = 0; index < island->location_count; ++index) {
        if (island->locations[index].renderer_class != 1) continue;
        if (ordinal == wanted) {
            *marker_index = (uint16_t)index;
            return 1;
        }
        ++ordinal;
    }
    return 0;
}

int game_start_assign_locations(const IslandData *islands, size_t island_count,
                                uint32_t mode, uint32_t alternate_island,
                                GameStartSetup *out,
                                char *error, size_t error_capacity)
{
    GameStartSetup result;
    unsigned int player;

    if (error != NULL && error_capacity != 0) error[0] = '\0';
    if (islands == NULL || out == NULL) {
        set_error(error, error_capacity, "islands and output are required",
                  GAME_START_PLAYER_COUNT);
        return 0;
    }
    if (island_count > GAME_START_MAX_ISLANDS) {
        set_error(error, error_capacity, "island count exceeds the original world table",
                  GAME_START_PLAYER_COUNT);
        return 0;
    }

    memset(&result, 0, sizeof(result));
    for (player = 0; player < GAME_START_PLAYER_COUNT; ++player) {
        uint32_t selected_island = (mode & 1U) == 0
            ? player
            : alternate_island + (player & 1U);
        const IslandData *island;
        const IslandLocation *marker;
        unsigned int index;
        unsigned int nearest_distance = 9999U;
        unsigned int nearest_index = ISLAND_DATA_MAX_LOCATIONS;
        uint16_t marker_index;
        GamePlayerStart *start = &result.players[player];

        if (selected_island >= island_count || selected_island >= GAME_START_MAX_ISLANDS) {
            set_error(error, error_capacity, "selected island index is out of range", player);
            return 0;
        }
        island = &islands[selected_island];
        if (island->location_count > ISLAND_DATA_MAX_LOCATIONS) {
            set_error(error, error_capacity, "location count exceeds the original capacity", player);
            return 0;
        }
        if (!find_marker(island, player, mode, &marker_index)) {
            set_error(error, error_capacity, "required class-1 start marker is missing", player);
            return 0;
        }
        marker = &island->locations[marker_index];

        for (index = 0; index < island->location_count; ++index) {
            const IslandLocation *candidate = &island->locations[index];
            unsigned int distance;

            /* FUN_0046466f tests record class at +4 and a zero dword at +16. */
            if (candidate->renderer_class != 0 || candidate->renderer_variant != 0) continue;
            distance = distance_chebyshev(candidate, marker);
            if (distance < nearest_distance) {
                nearest_distance = distance;
                nearest_index = index;
            }
        }
        if (nearest_index == ISLAND_DATA_MAX_LOCATIONS) {
            set_error(error, error_capacity, "no eligible class-0 location is available", player);
            return 0;
        }

        start->island_index = (uint8_t)selected_island;
        start->marker_location_index = marker_index;
        start->nearest_site_location_index = (uint16_t)nearest_index;
        start->nearest_site_x = island->locations[nearest_index].x;
        start->nearest_site_y = island->locations[nearest_index].y;
        {
            int left = (int)start->nearest_site_x - 0x140;
            if (left < 0) left = 0;
            if (left > 0x780) left = 0x780;
            start->view_left = (uint16_t)left;
            start->view_right = (uint16_t)(left + 0x27f);
        }
    }

    *out = result;
    return 1;
}
