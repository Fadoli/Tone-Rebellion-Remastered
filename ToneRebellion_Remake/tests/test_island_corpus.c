#include "island_data.h"
#include "game_start.h"
#include "game_session.h"
#include "pad_catalog.h"
#include "world_map.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned char *read_file(const char *path, size_t *length)
{
    FILE *file = fopen(path, "rb");
    long file_length;
    unsigned char *bytes;

    if (file == NULL) return NULL;
    if (fseek(file, 0, SEEK_END) != 0 || (file_length = ftell(file)) < 0 ||
        fseek(file, 0, SEEK_SET) != 0) {
        fclose(file);
        return NULL;
    }
    bytes = (unsigned char *)malloc(file_length == 0 ? 1U : (size_t)file_length);
    if (bytes == NULL || fread(bytes, 1, (size_t)file_length, file) !=
                         (size_t)file_length) {
        free(bytes);
        fclose(file);
        return NULL;
    }
    fclose(file);
    *length = (size_t)file_length;
    return bytes;
}

int main(int argc, char **argv)
{
    unsigned int island_id;
    unsigned int files_found = 0;
    unsigned int records_found = 0;
    IslandData initial_islands[GAME_START_PLAYER_COUNT];
    IslandData shape_islands[WORLD_MAP_MAX_ISLANDS];
    unsigned int initial_island_mask = 0;
    unsigned int shape_island_mask = 0;

    if (argc != 2) {
        (void)fprintf(stderr, "usage: test_island_corpus <original_content_directory>\n");
        return 2;
    }

    for (island_id = 0; island_id < 100; ++island_id) {
        char path[1024];
        size_t length = 0;
        unsigned char *bytes;
        IslandData data;
        char error[256];
        int written = snprintf(path, sizeof(path), "%s/ISLAND%02u.TXT",
                              argv[1], island_id);

        if (written < 0 || (size_t)written >= sizeof(path)) {
            (void)fprintf(stderr, "content directory path is too long\n");
            return 2;
        }
        bytes = read_file(path, &length);
        if (bytes == NULL) continue;
        ++files_found;
        if (!island_data_load(bytes, length, &data, error, sizeof(error))) {
            (void)fprintf(stderr, "%s: %s\n", path, error);
            free(bytes);
            return 1;
        }
        if (island_id < GAME_START_PLAYER_COUNT) {
            initial_islands[island_id] = data;
            initial_island_mask |= 1U << island_id;
        }
        if (island_id < WORLD_MAP_MAX_ISLANDS) {
            shape_islands[island_id] = data;
            shape_island_mask |= 1U << island_id;
        }
        records_found += data.location_count;
        free(bytes);
    }

    if (files_found == 0) {
        (void)fprintf(stderr, "no ISLANDnn.TXT files found in %s\n", argv[1]);
        return 1;
    }
    if (initial_island_mask != (1U << GAME_START_PLAYER_COUNT) - 1U) {
        (void)fprintf(stderr, "small-world start islands 0-3 are missing from the corpus\n");
        return 1;
    }
    {
        GameStartSetup setup;
        char error[256];
        if (!game_start_assign_locations(initial_islands, GAME_START_PLAYER_COUNT,
                                         0, 0, &setup, error, sizeof(error))) {
            (void)fprintf(stderr, "initial placement on small-world corpus islands failed: %s\n",
                          error);
            return 1;
        }
        (void)printf("resolved four initial starts from the original small-world islands\n");
    }
    {
        char path[1024];
        int written = snprintf(path, sizeof(path), "%s/WORLDPOS.TXT", argv[1]);
        WorldMap map;
        char error[256];
        unsigned int world_index;
        int32_t shape_ids[WORLD_MAP_MAX_ISLANDS];
        IslandData world_islands[WORLD_MAP_MAX_ISLANDS];
        GameSessionConfig config;
        GameSession session;
        PadCatalog pad_catalog;
        char pad_path[1024];
        unsigned char *pad_bytes;
        size_t pad_length;

        if (written < 0 || (size_t)written >= sizeof(path) ||
            !world_map_load_file(path, &map, error, sizeof(error))) {
            (void)fprintf(stderr, "could not load local WORLDPOS.TXT: %s\n", error);
            return 1;
        }
        if (map.world_count == 0) {
            (void)fprintf(stderr, "WORLDPOS.TXT contains no worlds\n");
            return 1;
        }
        written = snprintf(pad_path, sizeof(pad_path), "%s/pad.txt", argv[1]);
        pad_bytes = written < 0 || (size_t)written >= sizeof(pad_path)
            ? NULL : read_file(pad_path, &pad_length);
        if (pad_bytes == NULL ||
            !pad_catalog_load(pad_bytes, pad_length, &pad_catalog,
                              error, sizeof(error))) {
            (void)fprintf(stderr, "could not load local pad.txt: %s\n", error);
            free(pad_bytes);
            return 1;
        }
        free(pad_bytes);
        for (world_index = 0;
             world_index < map.worlds[0].island_count;
             ++world_index) {
            unsigned int shape_id = (unsigned int)map.worlds[0].islands[world_index].shape_id;
            if (shape_id >= WORLD_MAP_MAX_ISLANDS ||
                (shape_island_mask & (1U << shape_id)) == 0) {
                (void)fprintf(stderr, "world 0 references unavailable island shape %u\n", shape_id);
                return 1;
            }
            shape_ids[world_index] = (int32_t)shape_id;
            world_islands[world_index] = shape_islands[shape_id];
        }
        memset(&config, 0, sizeof(config));
        config.world_index = 0;
        config.home_island_index = 0; /* explicit fixture value; binary global is unresolved */
        config.random_seed = 1;
        if (!game_session_initialize(&map.worlds[0], world_islands,
                                     &pad_catalog, &config,
                                     &session, error, sizeof(error))) {
            (void)fprintf(stderr, "game session from local corpus failed: %s\n", error);
            return 1;
        }
        (void)printf("initialized world 0 from its %u local ISLANDnn records (%u bridge sites, %u class-0 assignments)\n",
                     session.island_count, map.worlds[0].bridge_count,
                     session.class0_assignments);
    }
    (void)printf("parsed %u island files (%u location rows)\n",
                 files_found, records_found);
    return 0;
}
