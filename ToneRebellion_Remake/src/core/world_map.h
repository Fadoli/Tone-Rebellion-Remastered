#ifndef TONE_REBELLION_WORLD_MAP_H
#define TONE_REBELLION_WORLD_MAP_H

#include <stddef.h>
#include <stdint.h>

enum {
    WORLD_MAP_MAX_WORLDS = 3,
    WORLD_MAP_MAX_ISLANDS = 16,
    /* Ghidra's per-world bridge table reserves 0x100 bytes of 8-byte pairs. */
    WORLD_MAP_MAX_BRIDGES = 32
};

typedef struct WorldIsland {
    int32_t angle_degrees;
    int32_t range;
    int32_t z;
    int32_t shape_id;
} WorldIsland;

typedef struct WorldBridge {
    uint8_t island_a;
    uint8_t island_b;
} WorldBridge;

typedef struct WorldDefinition {
    uint8_t island_count;
    uint8_t bridge_count;
    WorldIsland islands[WORLD_MAP_MAX_ISLANDS];
    WorldBridge bridges[WORLD_MAP_MAX_BRIDGES];
} WorldDefinition;

typedef struct WorldMap {
    uint8_t world_count;
    WorldDefinition worlds[WORLD_MAP_MAX_WORLDS];
} WorldMap;

/*
 * Loads the legacy world table into a temporary value and assigns it to `out`
 * only after the complete file parses successfully. `error` is optional; when
 * supplied, it receives a NUL-terminated diagnostic of at most error_capacity
 * bytes. Returns 1 on success and 0 on failure.
 */
int world_map_load_file(const char *path, WorldMap *out,
                        char *error, size_t error_capacity);

/* Parses the same table directly from bytes read from a COB member. */
int world_map_load_data(const unsigned char *data, size_t length, WorldMap *out,
                        char *error, size_t error_capacity);

#endif
