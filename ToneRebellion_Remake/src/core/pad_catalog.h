#ifndef TONE_REBELLION_PAD_CATALOG_H
#define TONE_REBELLION_PAD_CATALOG_H

#include <stddef.h>
#include <stdint.h>

enum { PAD_CATALOG_MAX_ITEMS = 128, PAD_CATALOG_TEXT_CAPACITY = 24 };

typedef enum PadTribe {
    PAD_TRIBE_NONE = 0,
    PAD_TRIBE_LEVIATHAN,
    PAD_TRIBE_PROTECTOR,
    PAD_TRIBE_SEEKER,
    PAD_TRIBE_MYSTIC,
    PAD_TRIBE_LIFEGIVER
} PadTribe;

typedef struct PadCatalogItem {
    /* `pad.txt` row order matches PIT item IDs: the first building starts at
       PIT_BuildToneProducer (0x25), as asserted by the original Iwconstr code. */
    uint16_t item_id;
    int8_t size;
    int16_t building_tone_cost;
    int16_t movement_cost[3];
    int16_t maintenance_tone_cost;
    int16_t hit_points;
    int16_t tone_range_extension;
    PadTribe tribe;
    char shape_id[PAD_CATALOG_TEXT_CAPACITY];
    char text_id[PAD_CATALOG_TEXT_CAPACITY];
} PadCatalogItem;

typedef struct PadCatalog {
    uint16_t item_count;
    PadCatalogItem items[PAD_CATALOG_MAX_ITEMS];
} PadCatalog;

/* Parse the local/source-format pad.txt bytes. The output changes only after
   every non-comment record has parsed and passed its field bounds. */
int pad_catalog_load(const unsigned char *bytes, size_t length, PadCatalog *out,
                     char *error, size_t error_capacity);

const PadCatalogItem *pad_catalog_find(const PadCatalog *catalog, uint16_t item_id);
size_t pad_catalog_tribe_item_count(const PadCatalog *catalog, PadTribe tribe);
const PadCatalogItem *pad_catalog_tribe_item_at(const PadCatalog *catalog,
                                               PadTribe tribe, size_t ordinal);
size_t pad_catalog_count_for(const PadCatalog *catalog, PadTribe tribe, int size);
const PadCatalogItem *pad_catalog_nth_for(const PadCatalog *catalog, PadTribe tribe,
                                          int size, size_t ordinal);

#endif
