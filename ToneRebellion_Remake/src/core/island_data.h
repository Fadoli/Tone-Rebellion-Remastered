#ifndef TONE_REBELLION_ISLAND_DATA_H
#define TONE_REBELLION_ISLAND_DATA_H

#include <stddef.h>
#include <stdint.h>

enum { ISLAND_DATA_MAX_LOCATIONS = 100, ISLAND_LOCATION_TYPE_CAPACITY = 16 };

typedef enum IslandLocationKind {
    ISLAND_LOCATION_UNKNOWN = 0,
    ISLAND_LOCATION_TONE,
    ISLAND_LOCATION_PAD,
    ISLAND_LOCATION_PAD_SMALL,
    ISLAND_LOCATION_PAD_MEDIUM,
    ISLAND_LOCATION_PAD_LARGE,
    ISLAND_LOCATION_SPECIAL,
    ISLAND_LOCATION_BRIDGE,
    ISLAND_LOCATION_LEVEL_HUB,
    ISLAND_LOCATION_LEVEL_SHIELD,
    ISLAND_LOCATION_FEATURE,
    ISLAND_LOCATION_FEATURE_TRIGGER
} IslandLocationKind;

typedef struct IslandLocation {
    uint16_t id;
    uint16_t x;
    uint16_t y;
    int32_t special_value;
    IslandLocationKind kind;
    uint8_t renderer_class;
    uint8_t renderer_subtype;
    uint16_t renderer_variant;
    char type[ISLAND_LOCATION_TYPE_CAPACITY];
} IslandLocation;

typedef struct IslandData {
    uint16_t location_count;
    IslandLocation locations[ISLAND_DATA_MAX_LOCATIONS];
} IslandData;

/* Parse an ISLANDnn.TXT member without changing row order or IDs. Unknown tags
 * are retained in each location's type field and use the renderer fallback. */
int island_data_load(const unsigned char *bytes, size_t length, IslandData *out,
                     char *error, size_t error_capacity);

/* FUN_00461b3b accepts only the original ISLANDnn.TXT type tags. */
IslandLocationKind island_location_kind(const char *type);

#endif
