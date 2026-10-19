#include "game_session.h"
#include "game_session_economy_internal.h"
#include "pad_catalog.h"

#include <string.h>

/* Location resources, Hall stock modes and refill requests. */
uint8_t game_session_location_display_level(const GameRuntimeLocation *location)
{
    if (location == NULL) return 0;
    return (uint8_t)((location->source_level_flags & 0x000fU) + 1U);
}

GameRuntimeLocation *game_session_player_hall(GameSession *session,
                                             uint8_t player_slot)
{
    const GamePlayerEconomy *economy;
    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT) return NULL;
    economy = &session->economy[player_slot];
    if (economy->hall_island_index >= session->island_count ||
        economy->hall_location_index >=
            session->islands[economy->hall_island_index].location_count) return NULL;
    return &session->islands[economy->hall_island_index]
        .locations[economy->hall_location_index];
}

int game_session_credit_resource(GameSession *session, uint8_t player_slot,
                                 GameResourceType type, uint32_t amount)
{
    GameRuntimeLocation *hall = game_session_player_hall(session, player_slot);
    uint16_t *stock;
    if (hall == NULL || (int)type < GAME_RESOURCE_BUILD_TONE ||
        (int)type >= GAME_RESOURCE_TYPE_COUNT) return 0;
    stock = &hall->resource_stock[type];
    if (amount > UINT16_MAX - *stock) return 0;
    *stock = (uint16_t)(*stock + amount);
    return 1;
}

int game_session_debit_resource(GameSession *session, uint8_t player_slot,
                                 GameResourceType type, uint32_t amount)
{
    GameRuntimeLocation *hall = game_session_player_hall(session, player_slot);
    uint16_t *stock;
    if (hall == NULL || (int)type < GAME_RESOURCE_BUILD_TONE ||
        (int)type >= GAME_RESOURCE_TYPE_COUNT) return 0;
    stock = &hall->resource_stock[type];
    if (amount > *stock) return 0;
    *stock = (uint16_t)(*stock - amount);
    return 1;
}

int game_session_consume_location_resource(GameSession *session,
                                           uint8_t island_index,
                                           uint16_t location_index,
                                           int32_t resource_code)
{
    GameRuntimeLocation *location;
    if (session == NULL || island_index >= session->island_count ||
        location_index >= session->islands[island_index].location_count) return 0;
    location = &session->islands[island_index].locations[location_index];
    if (location->record_value_24 == resource_code) {
        location->record_value_24 = 0;
        return 1;
    }
    if (location->record_value_10 == 0x2a) {
        if (resource_code >= 1 && resource_code <= GAME_RESOURCE_TYPE_COUNT) {
            uint16_t *stock = &location->resource_stock[resource_code - 1];
            if (*stock > 0) {
                --*stock;
                return 1;
            }
        }
    }
    if (location->owner_id >= 0 &&
        location->owner_id < GAME_START_PLAYER_COUNT &&
        resource_code >= GAME_INVENTORY_ITEM_FIRST_ID &&
        resource_code < GAME_INVENTORY_ITEM_FIRST_ID + GAME_INVENTORY_ITEM_COUNT) {
        uint16_t *count = &session->economy[location->owner_id].inventory_count[
            resource_code - GAME_INVENTORY_ITEM_FIRST_ID];
        if (*count > 0) {
            --*count;
            return 1;
        }
    }
    return 0;
}

int game_session_location_resource_available(const GameSession *session,
                                             uint8_t island_index,
                                             uint16_t location_index,
                                             int32_t resource_code)
{
    const GameRuntimeLocation *location;
    if (session == NULL || island_index >= session->island_count ||
        location_index >= session->islands[island_index].location_count) return 0;
    location = &session->islands[island_index].locations[location_index];
    if (location->record_value_24 == resource_code) return 1;
    if (location->record_value_10 == 0x2a &&
        resource_code >= 1 && resource_code <= GAME_RESOURCE_TYPE_COUNT &&
        location->resource_stock[resource_code - 1] > 0) return 1;
    if (location->owner_id >= 0 && location->owner_id < GAME_START_PLAYER_COUNT &&
        (location->record_value_10 == 0x2a ||
         location->source_location_slot_18 != -1) &&
        resource_code >= GAME_INVENTORY_ITEM_FIRST_ID &&
        resource_code < GAME_INVENTORY_ITEM_FIRST_ID + GAME_INVENTORY_ITEM_COUNT &&
        session->economy[location->owner_id].inventory_count[
            resource_code - GAME_INVENTORY_ITEM_FIRST_ID] > 0) return 1;
    return 0;
}

int game_session_location_move_costs(const GameSession *session,
                                     const PadCatalog *catalog,
                                     uint8_t island_index,
                                     uint16_t location_index,
                                     int32_t costs[GAME_RESOURCE_TYPE_COUNT])
{
    const GameRuntimeLocation *location;
    const PadCatalogItem *item;
    int32_t result[GAME_RESOURCE_TYPE_COUNT];
    int32_t multiplier;
    unsigned int resource;

    if (session == NULL || catalog == NULL || costs == NULL ||
        island_index >= session->island_count ||
        location_index >= session->islands[island_index].location_count) {
        return 0;
    }
    location = &session->islands[island_index].locations[location_index];
    if (location->record_value_10 < 0 ||
        location->record_value_10 > INT32_C(65535))
        return 0;
    item = pad_catalog_find(catalog, (uint16_t)location->record_value_10);
    if (item == NULL) return 0;

    multiplier = (int32_t)location->source_capacity_4a + 1;
    for (resource = 0; resource < GAME_RESOURCE_TYPE_COUNT; ++resource) {
        result[resource] = (int32_t)item->movement_cost[resource] * multiplier;
    }
    memcpy(costs, result, sizeof(result));
    return 1;
}

int game_session_cycle_resource_stock_mode(GameSession *session,
                                           uint8_t player_slot,
                                           GameResourceType type)
{
    uint8_t *mode;
    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT ||
        (int)type < GAME_RESOURCE_BUILD_TONE || (int)type >= GAME_RESOURCE_TYPE_COUNT) {
        return -1;
    }
    mode = &session->economy[player_slot].stock_mode[type];
    if (*mode > 2) *mode = 0;
    else *mode = (uint8_t)((*mode + 1U) % 3U);
    return (int)*mode;
}

unsigned int game_session_update_resource_requests(GameSession *session)
{
    unsigned int changes = 0;
    unsigned int player;
    if (session == NULL) return 0;
    for (player = 0; player < GAME_START_PLAYER_COUNT; ++player) {
        GamePlayerEconomy *economy = &session->economy[player];
        GameRuntimeLocation *hall;
        unsigned int resource;
        if (economy->hall_island_index >= session->island_count ||
            economy->hall_location_index >=
                session->islands[economy->hall_island_index].location_count)
            continue;
        hall = &session->islands[economy->hall_island_index]
                    .locations[economy->hall_location_index];
        for (resource = 0; resource < GAME_RESOURCE_TYPE_COUNT; ++resource) {
            const int16_t linked_slot = economy->resource_task_slot[resource];
            const int request_active = economy->stock_mode[resource] == 2 &&
                (hall->source_flags & 1U) != 0 &&
                hall->resource_stock[resource] <
                    hall->source_capacity_4a * 50 + 150;
            if (request_active && linked_slot == -1) {
                const int slot = game_session_pending_event_add(
                    session, (int16_t)player,
                    (int16_t)economy->hall_island_index, 4, 0,
                    (int16_t)economy->hall_location_index,
                    (int16_t)(resource + 1U));
                if (slot >= 0) {
                    economy->resource_task_slot[resource] = (int16_t)slot;
                    ++changes;
                }
            } else if (!request_active && linked_slot != -1) {
                if (linked_slot >= 0 &&
                    linked_slot < GAME_SESSION_MAX_PENDING_EVENTS) {
                    (void)game_session_pending_event_release(
                        session, (uint8_t)linked_slot);
                }
                economy->resource_task_slot[resource] = -1;
                ++changes;
            }
        }
    }
    return changes;
}
