#ifndef TONE_REBELLION_FLOATER_CATALOG_H
#define TONE_REBELLION_FLOATER_CATALOG_H

#include <stddef.h>
#include <stdint.h>

enum { FLOATER_CATALOG_ROW_COUNT = 45 };
enum { FLOATER_ANIMATION_CATALOG_MAX_ITEMS = 64 };
enum { FLOATER_IMPACT_REALM_COUNT = 4, FLOATER_IMPACT_LEVEL_COUNT = 4 };
enum { FLOATER_EFFECT_MAX = 96, FLOATER_EFFECT_NAME_CAPACITY = 17 };

/* effects.txt TYPE values in FUN_004153b8's numbering. */
enum {
    FLOATER_EFFECT_ONESHOT = 0, FLOATER_EFFECT_BULLET = 1,
    FLOATER_EFFECT_LIGHTNING = 2, FLOATER_EFFECT_IMPACT = 3,
    FLOATER_EFFECT_CAST = 4, FLOATER_EFFECT_SPECIAL = 5,
    FLOATER_EFFECT_SOUNDONLY = 6
};

/* One effects.txt record (FUN_004153b8's 0x30-byte def). Frames are 0-based. */
typedef struct FloaterEffectDef {
    char name[FLOATER_EFFECT_NAME_CAPACITY];
    char shape[FLOATER_EFFECT_NAME_CAPACITY];
    /* SOUND id (sound.txt), played on the instance's first tick by
       FUN_004181a6; empty when the def has none. */
    char sound[FLOATER_EFFECT_NAME_CAPACITY];
    uint8_t type;
    uint8_t level_count;
    uint8_t level_start[FLOATER_IMPACT_LEVEL_COUNT];
    uint8_t level_frames[FLOATER_IMPACT_LEVEL_COUNT];
    int16_t speed;  /* SPEED, default 5 */
    int16_t chain;  /* CHAIN target def index or -1 */
} FloaterEffectDef;

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
    uint16_t attack_frame_first;
    uint16_t attack_frame_last;
    uint16_t attack_frame_ticks_per_frame;
    uint16_t attack_frame_duration;
    uint8_t attack_frame_ping_pong;
    /* fltinf.txt atteff/attxy resolved against effects.txt (shape record
       +0x48 and +0x4e/+0x50 in FUN_00454d1f); def is -1 when absent. */
    char attack_effect_name[FLOATER_EFFECT_NAME_CAPACITY];
    int16_t attack_effect_def;
    int16_t attack_offset_x;
    int16_t attack_offset_y;
    /* fltinf.txt graspxy: cargo hand point, shape record +0x4a/+0x4c. */
    int16_t grasp_offset_x;
    int16_t grasp_offset_y;
} FloaterStats;

typedef struct FloaterCatalog {
    FloaterStats rows[FLOATER_CATALOG_ROW_COUNT];
    uint8_t impact_frame_counts[FLOATER_IMPACT_REALM_COUNT]
                               [FLOATER_IMPACT_LEVEL_COUNT];
    uint8_t impact_frame_starts[FLOATER_IMPACT_REALM_COUNT]
                               [FLOATER_IMPACT_LEVEL_COUNT];
    FloaterEffectDef effects[FLOATER_EFFECT_MAX];
    uint8_t effect_count;
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

/* Parse every effects.txt record and resolve each row's fltinf atteff name
   (call after floater_catalog_load_animations). */
int floater_catalog_load_effect_defs(const unsigned char *bytes, size_t length,
                                     FloaterCatalog *catalog, char *error,
                                     size_t error_capacity);

/* Mirrors FUN_00464242's row formula; caller supplies its two raw key fields. */
const FloaterStats *floater_catalog_find(const FloaterCatalog *catalog,
                                        int type_index, int subtype);

#endif
