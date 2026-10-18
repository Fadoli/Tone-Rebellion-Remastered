#ifndef TONE_REBELLION_FLOATER_CATALOG_H
#define TONE_REBELLION_FLOATER_CATALOG_H

#include <stddef.h>
#include <stdint.h>

enum { FLOATER_CATALOG_ROW_COUNT = 45 };

typedef struct FloaterStats {
    int16_t attack_range;
    int16_t attack_realm;
    int16_t hit_points;
    int16_t max_attack_points;
    int16_t attack_strength;
    int16_t movement_speed;
} FloaterStats;

typedef struct FloaterCatalog {
    FloaterStats rows[FLOATER_CATALOG_ROW_COUNT];
} FloaterCatalog;

/* Parse the 45 ordered records loaded by FUN_004633a7. */
int floater_catalog_load(const unsigned char *bytes, size_t length,
                         FloaterCatalog *out, char *error,
                         size_t error_capacity);

/* Mirrors FUN_00464242's row formula; caller supplies its two raw key fields. */
const FloaterStats *floater_catalog_find(const FloaterCatalog *catalog,
                                        int type_index, int subtype);

#endif
