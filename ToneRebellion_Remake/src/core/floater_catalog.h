#ifndef TONE_REBELLION_FLOATER_CATALOG_H
#define TONE_REBELLION_FLOATER_CATALOG_H

#include <stddef.h>
#include <stdint.h>

enum { FLOATER_CATALOG_ROW_COUNT = 45 };
enum { FLOATER_ANIMATION_CATALOG_MAX_ITEMS = 64 };
enum { FLOATER_IMPACT_REALM_COUNT = 4, FLOATER_IMPACT_LEVEL_COUNT = 4 };

typedef struct FloaterStats {
    char draw_id[9];
    int16_t attack_range;
    int16_t attack_realm;
    int16_t hit_points;
    int16_t max_attack_points;
    int16_t attack_strength;
    int16_t movement_speed;
    int16_t shape_info_index;
    uint16_t attack_period;
} FloaterStats;

typedef struct FloaterCatalog {
    FloaterStats rows[FLOATER_CATALOG_ROW_COUNT];
    uint8_t impact_frame_counts[FLOATER_IMPACT_REALM_COUNT]
                               [FLOATER_IMPACT_LEVEL_COUNT];
} FloaterCatalog;

/* Parse the 45 ordered records loaded by FUN_004633a7. */
int floater_catalog_load(const unsigned char *bytes, size_t length,
                         FloaterCatalog *out, char *error,
                         size_t error_capacity);

/* Resolve each floater.txt draw ID through the ordered item/attack entries
   parsed from fltinf.txt, matching FUN_004557bc and FUN_0042520e. */
int floater_catalog_load_animations(const unsigned char *bytes, size_t length,
                                    FloaterCatalog *catalog, char *error,
                                    size_t error_capacity);

/* Load the four realm IMPACT lifetimes used by state 6/7 attacks. */
int floater_catalog_load_impact_effects(const unsigned char *bytes,
                                        size_t length,
                                        FloaterCatalog *catalog,
                                        char *error,
                                        size_t error_capacity);

/* Mirrors FUN_00464242's row formula; caller supplies its two raw key fields. */
const FloaterStats *floater_catalog_find(const FloaterCatalog *catalog,
                                        int type_index, int subtype);

#endif
