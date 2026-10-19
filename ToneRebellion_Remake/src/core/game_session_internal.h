#ifndef TONE_REBELLION_GAME_SESSION_INTERNAL_H
#define TONE_REBELLION_GAME_SESSION_INTERNAL_H

#include "game_session.h"
#include "pad_catalog.h"

#include <limits.h>

#include "game_session_layout_internal.h"

/* Shared runtime pad maximum used during session setup and building updates. */
static int game_session_source_value_34_max(const PadCatalog *catalog,
                                             const GameRuntimeLocation *location,
                                             int16_t *maximum)
{
    const PadCatalogItem *item;
    int32_t base_item_id;
    int32_t value;

    if (catalog == NULL || location == NULL || maximum == NULL ||
        location->owner_id < -1 || location->owner_id > GAME_START_PLAYER_COUNT ||
        location->record_value_10 < 0) return 0;
    if (location->owner_id == -1) {
        *maximum = -1;
        return 1;
    }
    base_item_id = location->record_value_10;
    if (location->owner_id < GAME_START_PLAYER_COUNT)
        base_item_id -= location->owner_id * 16;
    if (base_item_id <= 1) {
        *maximum = -1;
        return 1;
    }
    item = pad_catalog_find(catalog, (uint16_t)location->record_value_10);
    if (item == NULL) return 0;
    /* FUN_0046303b stores pad.txt hit points at +0x0e; FUN_00450978
       adds runtime +0x4a * 5. */
    value = (int32_t)item->hit_points +
            (int32_t)location->source_capacity_4a * 5;
    if (value < INT16_MIN || value > INT16_MAX) return 0;
    *maximum = (int16_t)value;
    return 1;
}

#endif
