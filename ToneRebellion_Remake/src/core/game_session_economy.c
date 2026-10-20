#include "game_session.h"
#include "game_session_economy_internal.h"
#include "pad_catalog.h"

#include <string.h>

/* Location resources, Hall stock modes and refill requests. */
static int location_is_player_hall(const GameRuntimeLocation *location)
{
    return location != NULL && location->owner_id >= 0 &&
        location->owner_id < GAME_START_PLAYER_COUNT &&
        location->record_value_10 == 0x2a + location->owner_id * 16;
}

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
    if (location_is_player_hall(location)) {
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
    if (location_is_player_hall(location) &&
        resource_code >= 1 && resource_code <= GAME_RESOURCE_TYPE_COUNT &&
        location->resource_stock[resource_code - 1] > 0) return 1;
    if (location->owner_id >= 0 && location->owner_id < GAME_START_PLAYER_COUNT &&
        (location_is_player_hall(location) ||
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

static int location_visible_to_player(const GameRuntimeLocation *location,
                                      uint8_t player_slot)
{
    return location != NULL &&
        (location->source_value_22 & (uint16_t)(1U << player_slot)) != 0;
}

static int location_move_source_valid(const GameRuntimeLocation *location,
                                      uint8_t player_slot)
{
    int32_t item_id;
    if (location == NULL || location->owner_id != player_slot ||
        !location_visible_to_player(location, player_slot) ||
        (location->source_flags & 0x90U) != 0) return 0;
    item_id = location->record_value_10 - (int32_t)player_slot * 16;
    return item_id >= 0x25 && item_id <= 0x34 && item_id != 0x28;
}

static int location_move_target_valid(const GameRuntimeLocation *location,
                                      uint8_t player_slot)
{
    if (location == NULL || location->renderer_class != 0 ||
        location->owner_id != -1 ||
        !location_visible_to_player(location, player_slot)) return 0;
    if (location->record_value_10 == 0) return 1;
    return location->record_value_10 == 1 &&
        location->record_value_24 >= GAME_INVENTORY_ITEM_FIRST_ID &&
        location->record_value_24 < GAME_INVENTORY_ITEM_FIRST_ID +
                                        GAME_INVENTORY_ITEM_COUNT;
}

int game_session_begin_location_move(GameSession *session,
                                     const PadCatalog *catalog,
                                     uint8_t player_slot,
                                     uint8_t island_index,
                                     uint16_t location_index)
{
    GameRuntimeLocation *location;
    const GameRuntimeLocation *hall;
    int32_t costs[GAME_RESOURCE_TYPE_COUNT];
    unsigned int resource;
    if (session == NULL || catalog == NULL ||
        player_slot >= GAME_START_PLAYER_COUNT ||
        island_index >= session->island_count || session->location_move_active ||
        location_index >= session->islands[island_index].location_count) return 0;
    location = &session->islands[island_index].locations[location_index];
    if (!location_move_source_valid(location, player_slot) ||
        !game_session_location_move_costs(session, catalog, island_index,
                                           location_index, costs)) return 0;
    hall = game_session_player_hall(session, player_slot);
    if (hall == NULL) return 0;
    for (resource = 0; resource < GAME_RESOURCE_TYPE_COUNT; ++resource) {
        if (costs[resource] < 0 ||
            (uint32_t)costs[resource] > hall->resource_stock[resource]) return 0;
    }
    for (resource = 0; resource < GAME_RESOURCE_TYPE_COUNT; ++resource) {
        if (!game_session_debit_resource(session, player_slot,
                (GameResourceType)resource, (uint32_t)costs[resource])) {
            unsigned int refund;
            for (refund = 0; refund < resource; ++refund) {
                (void)game_session_credit_resource(session, player_slot,
                    (GameResourceType)refund, (uint32_t)costs[refund]);
            }
            return 0;
        }
    }
    session->location_move_active = 1;
    session->location_move_player = player_slot;
    session->location_move_source_island = island_index;
    session->location_move_source_index = location_index;
    return 1;
}

int game_session_finish_location_move(GameSession *session,
                                      uint8_t player_slot,
                                      uint8_t island_index,
                                      uint16_t location_index)
{
    GameRuntimeLocation *source;
    GameRuntimeLocation *target;
    GameRuntimeLocation moved;
    unsigned int task_type;
    uint16_t target_x;
    uint16_t target_y;
    uint16_t old_hall_x = 0;
    uint16_t old_hall_y = 0;
    uint8_t target_class;
    uint8_t target_site_size;
    int moves_hall;
    GamePlayerEconomy *player_economy;
    if (session == NULL || !session->location_move_active ||
        player_slot >= GAME_START_PLAYER_COUNT ||
        player_slot != session->location_move_player ||
        island_index >= session->island_count ||
        session->location_move_source_island >= session->island_count ||
        island_index != session->location_move_source_island ||
        location_index >= session->islands[island_index].location_count ||
        session->location_move_source_index >=
            session->islands[session->location_move_source_island].location_count)
        return 0;
    source = &session->islands[session->location_move_source_island]
        .locations[session->location_move_source_index];
    target = &session->islands[island_index].locations[location_index];
    if (!location_move_source_valid(source, player_slot) ||
        !location_move_target_valid(target, player_slot)) return 0;
    player_economy = &session->economy[player_slot];
    /* FUN_00452a15 clears the source site through FUN_00460029, which also
       cancels pending tasks and detaches workers targeting the old location. */
    (void)game_session_cancel_tasks_for_location(session,
        session->location_move_source_island,
        session->location_move_source_index);
    moves_hall = player_economy->hall_island_index ==
                     session->location_move_source_island &&
                 player_economy->hall_location_index ==
                     session->location_move_source_index;
    if (moves_hall) {
        unsigned int resource;
        old_hall_x = player_economy->hall_x;
        old_hall_y = player_economy->hall_y;
        for (resource = 0; resource < GAME_RESOURCE_TYPE_COUNT; ++resource) {
            int16_t task_slot = player_economy->resource_task_slot[resource];
            if (task_slot >= 0 && task_slot < GAME_SESSION_MAX_PENDING_EVENTS) {
                (void)game_session_pending_event_release(session,
                                                         (uint8_t)task_slot);
            }
            player_economy->resource_task_slot[resource] = -1;
        }
    }
    if (source->charge_staff_task_handle >= 0 &&
        source->charge_staff_task_handle < GAME_SESSION_MAX_PENDING_EVENTS) {
        (void)game_session_pending_event_release(
            session, (uint8_t)source->charge_staff_task_handle);
        source->charge_staff_task_handle = -1;
    }
    for (task_type = 0; task_type < GAME_RESOURCE_TYPE_COUNT; ++task_type) {
        int16_t task_slot = source->source_task_slot[task_type];
        if (task_slot >= 0 && task_slot < GAME_SESSION_MAX_PENDING_EVENTS) {
            (void)game_session_pending_event_release(session,
                                                     (uint8_t)task_slot);
        }
        source->source_task_slot[task_type] = -1;
    }

    moved = *source;
    moved.charge_staff_task_handle = -1;
    for (task_type = 0; task_type < GAME_RESOURCE_TYPE_COUNT; ++task_type)
        moved.source_task_slot[task_type] = -1;
    target_x = target->x;
    target_y = target->y;
    target_class = target->renderer_class;
    target_site_size = target->construction_site_size;
    *target = moved;
    target->x = target_x;
    target->y = target_y;
    target->renderer_class = target_class;
    target->construction_site_size = target_site_size;
    if (moves_hall) {
        player_economy->hall_island_index = island_index;
        player_economy->hall_location_index = location_index;
        player_economy->hall_x = target_x;
        player_economy->hall_y = target_y;
    }
    {
        unsigned int floater_index;
        const uint16_t old_location_index = session->location_move_source_index;
        for (floater_index = 0; floater_index < session->floater_count;
             ++floater_index) {
            GameFloaterStart *floater = &session->floaters[floater_index];
            if (!game_session_floater_is_active(floater)) continue;
            if (floater->charge_source_island == island_index &&
                floater->charge_source_location == old_location_index &&
                floater->source_link_0c == target->source_location_slot_18) {
                floater->charge_source_location = location_index;
            }
            if (floater->island_index == island_index &&
                (floater->movement_state == 11 || floater->movement_state == 12) &&
                floater->source_order_parameter_32 == old_location_index) {
                floater->source_order_parameter_32 = location_index;
                floater->destination_x = target_x;
                floater->destination_y = target_y;
            }
            if (moves_hall && floater->owner_slot == player_slot &&
                floater->source_subtype == 8 && floater->movement_state == 9 &&
                floater->has_move_order && floater->destination_x == old_hall_x &&
                floater->destination_y == old_hall_y) {
                floater->destination_x = target_x;
                floater->destination_y = target_y;
            }
        }
    }

    /* The source helper's indirect cleanup is not fully reconstructed. The
       remake applies the user-facing move operation and leaves an empty site. */
    source->record_value_10 = 0;
    source->owner_id = -1;
    source->source_value_14 = -1;
    source->maintenance_tone_cost = 0;
    source->source_location_slot_18 = -1;
    source->source_category_slot_60 = -1;
    source->record_value_24 = 0;
    source->source_flags = 0;
    source->source_value_34 = -1;
    source->source_value_22 = 0;
    source->resource_stock[0] = 0;
    source->resource_stock[1] = 0;
    source->resource_stock[2] = 0;
    source->charge_source_value_30 = 0;
    source->charge_floater_count = 0;
    source->charge_recent_floater = -1;
    source->charge_staff_task_handle = -1;
    source->source_capacity_4a = 0;
    source->source_progress_08 = 0;
    source->source_level_flags = 0;
    source->source_value_44 = 0;
    /* FUN_004533fb clears +0x46, sets +0x58, then recomputes the active bit. */
    source->source_value_46 = 0;
    source->source_value_58 = 1;
    source->producer_cadence = 0;
    source->base_progress = 0;
    source->chug_progress = 0;
    source->glyph_progress = 0;
    source->inci_progress = 0;
    source->construction_progress = 0;
    source->production_progress = 0;
    source->animation_rate = 0;
    source->barg_progress = 0.0;
    source->bridge_neighbor_island = -1;
    source->tribe_visibility_mask = 0;
    source->bridge_constructed = 0;
    source->source_task_slot[0] = -1;
    source->source_task_slot[1] = -1;
    source->source_task_slot[2] = -1;
    source->charge_floater_slots[0] = -1;
    source->charge_floater_slots[1] = -1;
    source->charge_floater_slots[2] = -1;
    source->charge_floater_slots[3] = -1;
    source->charge_floater_slots[4] = -1;
    source->charge_floater_slots[5] = -1;
    source->charge_floater_slots[6] = -1;
    source->charge_floater_slots[7] = -1;
    session->location_move_active = 0;
    (void)game_session_recalculate_location_active_with_visibility(source);
    (void)game_session_recalculate_active_locations(session);
    return 1;
}

int game_session_cancel_location_move(GameSession *session,
                                      const PadCatalog *catalog)
{
    int32_t costs[GAME_RESOURCE_TYPE_COUNT];
    unsigned int resource;
    uint8_t player_slot;
    uint8_t island_index;
    uint16_t location_index;
    if (session == NULL || !session->location_move_active) return 0;
    player_slot = session->location_move_player;
    island_index = session->location_move_source_island;
    location_index = session->location_move_source_index;
    if (catalog != NULL && game_session_location_move_costs(session, catalog,
            island_index, location_index, costs)) {
        for (resource = 0; resource < GAME_RESOURCE_TYPE_COUNT; ++resource) {
            if (costs[resource] >= 0) {
                (void)game_session_credit_resource(session, player_slot,
                    (GameResourceType)resource, (uint32_t)costs[resource]);
            }
        }
    }
    session->location_move_active = 0;
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
