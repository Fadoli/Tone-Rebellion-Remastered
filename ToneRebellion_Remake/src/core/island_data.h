#ifndef TONE_REBELLION_ISLAND_DATA_H
#define TONE_REBELLION_ISLAND_DATA_H

#include <stddef.h>
#include <stdint.h>

enum { ISLAND_DATA_MAX_LOCATIONS = 100, ISLAND_LOCATION_TYPE_CAPACITY = 16 };

typedef struct IslandLocation {
    uint16_t id;
    uint16_t x;
    uint16_t y;
    int32_t special_value;
    char type[ISLAND_LOCATION_TYPE_CAPACITY];
} IslandLocation;

typedef struct IslandData {
    uint16_t location_count;
    IslandLocation locations[ISLAND_DATA_MAX_LOCATIONS];
} IslandData;

/* Parse a shipped ISLANDnn.TXT member without changing record order or IDs. */
int island_data_load(const unsigned char *bytes, size_t length, IslandData *out,
                     char *error, size_t error_capacity);

#endif
