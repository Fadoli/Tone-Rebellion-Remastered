#include "game_session_delivery_internal.h"
#include "game_session_action9.h"
#include "game_session_events.h"
#include "game_session_internal.h"
#include "game_session_movement_internal.h"
#include "iw_construct.h"
#include "island_data.h"
#include "tone_rng.h"

static int location_is_player_hall(const GameRuntimeLocation *location)
{
    return location != NULL && location->owner_id >= 0 &&
        location->owner_id < GAME_START_PLAYER_COUNT &&
        location->record_value_10 == 0x2a + location->owner_id * 16;
}

static int construction_refill_source(GameSession *session,
                                      const GameFloaterStart *floater,
                                      uint8_t *source_island)
{
    const GamePlayerEconomy *economy;
    if (session == NULL || floater == NULL || source_island == NULL ||
        floater->owner_slot >= GAME_START_PLAYER_COUNT) return -1;
    economy = &session->economy[floater->owner_slot];
    if (economy->hall_island_index < session->island_count &&
        economy->hall_island_index == floater->island_index &&
        economy->hall_location_index <
            session->islands[economy->hall_island_index].location_count) {
        const GameRuntimeLocation *hall = &session->islands[
            economy->hall_island_index].locations[economy->hall_location_index];
        if (location_is_player_hall(hall) && hall->resource_stock[0] != 0) {
            *source_island = economy->hall_island_index;
            return (int)economy->hall_location_index;
        }
    }
    return refill_source(session, floater, 1, source_island);
}

int game_session_start_repair_supply(GameSession *session,
                                     GameFloaterStart *floater)
{
    uint8_t source_island;
    int source_index;
    const GameRuntimeLocation *source;

    if (session == NULL || floater == NULL ||
        floater->active_order_action != 0x12 ||
        floater->island_index >= session->island_count) return 0;
    source_island = floater->island_index;
    source_index = construction_refill_source(session, floater, &source_island);
    if (source_index < 0 || source_island >= session->island_count ||
        (uint16_t)source_index >= session->islands[source_island].location_count)
        return 0;

    source = &session->islands[source_island].locations[(unsigned int)source_index];
    floater->order_source_location = (int16_t)source_index;
    floater->order_source_island = source_island;
    floater->order_resource_code = 1;
    floater->order_timer = 0;
    if (source_island == floater->island_index) {
        floater_target_location(floater, source, 3);
        return 1;
    }

    floater->source_order_coordinate_30 = (uint16_t)(
        ((uint16_t)(((uint32_t)source->x + 5U) / 10U) << 8) |
        (uint16_t)(((uint32_t)source->y + 5U) / 10U));
    if (!game_session_begin_floater_handoff(session, floater, source_island))
        return 0;
    floater->handoff_resume_state = 3;
    return 1;
}

static int delivery_item_code_valid(int16_t item_code)
{
    return (item_code >= 1 && item_code <= GAME_RESOURCE_TYPE_COUNT) ||
        (item_code >= GAME_INVENTORY_ITEM_FIRST_ID &&
         item_code < GAME_INVENTORY_ITEM_FIRST_ID + GAME_INVENTORY_ITEM_COUNT);
}

static int location_is_producer_for_resource(
    const GameRuntimeLocation *location, int16_t player_id,
    int16_t resource_code)
{
    int32_t producer_item;

    if (location == NULL || location->renderer_class != 0 ||
        location->owner_id != player_id ||
        resource_code < 1 || resource_code > GAME_RESOURCE_TYPE_COUNT) return 0;
    producer_item = resource_code == 1 ? 0x25 :
                    resource_code == 2 ? 0x27 : 0x26;
    return game_session_base_item_id(location) == producer_item;
}

static int artifact_delivery_target_valid(const GameSession *session,
                                          const GameFloaterStart *floater,
                                          uint8_t island_index,
                                          int16_t location_index,
                                          int16_t resource_code)
{
    const GameRuntimeLocation *target;
    int32_t base_item_id;

    if (session == NULL || floater == NULL || island_index >= session->island_count ||
        location_index < 0 ||
        (uint16_t)location_index >= session->islands[island_index].location_count)
        return 0;
    target = &session->islands[island_index].locations[(uint16_t)location_index];
    if (target->renderer_class == 2) {
        /* FUN_004503bd routes class-2 deliveries through the bridge trigger:
           idle CONS consumes code 5 to start construction; every other
           artifact delivery follows the inventory-credit path. */
        return resource_code >= GAME_INVENTORY_ITEM_FIRST_ID;
    }
    if (target->renderer_class != 0) return 0;
    if (target->owner_id == -1 && target->record_value_10 == 0) return 1;
    if (target->owner_id != (int32_t)floater->owner_slot) return 0;
    base_item_id = target->record_value_10 - (int32_t)floater->owner_slot * 16;
    return location_is_player_hall(target) || base_item_id == 0x2c ||
        base_item_id == 0x2d || base_item_id == 0x2e ||
        base_item_id == 0x2f || base_item_id == 0x30;
}

static int construction_handoff_available(const GameSession *session,
                                           uint8_t island_index,
                                           uint8_t owner_slot)
{
    const GameRuntimeIsland *island;
    unsigned int location_index;

    if (session == NULL || island_index >= session->island_count ||
        owner_slot >= GAME_FLOATER_CATEGORY_COUNT) return 0;
    island = &session->islands[island_index];
    if (island->location_count > ISLAND_DATA_MAX_LOCATIONS) return 0;
    for (location_index = 0; location_index < island->location_count;
         ++location_index) {
        const GameRuntimeLocation *location = &island->locations[location_index];
        if (location->renderer_class == 2 && (location->source_flags & 1U) != 0 &&
            (int32_t)location->x >= island->floater_min_x[owner_slot] &&
            (int32_t)location->x <= island->floater_max_x[owner_slot]) return 1;
    }
    return 0;
}

static int assign_charge_task_for_floater(GameSession *session,
                                          GameFloaterStart *floater,
                                          unsigned int floater_index,
                                          unsigned int slot)
{
    GamePendingEvent *event = &session->pending_events[slot];
    GameRuntimeLocation *source;
    uint8_t target_island;
    int accepted;

    if (floater->source_subtype != 0 || event->active == 0 ||
        event->action_type != 0x0b || event->assigned_floater_count >= 1 ||
        event->player_id != floater->owner_slot || event->payload_0a < 0 ||
        event->payload_0a >= session->island_count || event->payload_0c < 0 ||
        (uint16_t)event->payload_0c >=
            session->islands[event->payload_0a].location_count) return 0;

    target_island = (uint8_t)event->payload_0a;
    source = &session->islands[target_island].locations[(uint16_t)event->payload_0c];
    if (source->charge_staff_task_handle != (int16_t)slot ||
        source->source_location_slot_18 < 0) return 0;
    if (target_island == floater->island_index) {
        accepted = game_session_order_floater_to_charge_site(
            session, floater->owner_slot, target_island, floater_index,
            (uint16_t)event->payload_0c);
    } else {
        accepted = game_session_begin_floater_handoff(
            session, floater, target_island);
        if (accepted) {
            floater->source_order_parameter_32 = (uint16_t)event->payload_0c;
            floater->handoff_resume_action = 0;
            floater->handoff_resume_state = 11;
        }
    }
    if (!accepted) return 0;

    /* FUN_00422031 admits subtype-0 workers to task 0xb. */
    floater->linked_task_slot = (int16_t)slot;
    floater->order_target_island = target_island;
    floater->order_target_location = event->payload_0c;
    event->assigned_floater_count = 1;
    return 1;
}

static int assign_delivery_task_for_floater(GameSession *session,
                                            GameFloaterStart *floater,
                                            unsigned int slot)
{
    GamePendingEvent *event = &session->pending_events[slot];
    uint8_t source_island = floater->island_index;
    GameRuntimeIsland *island;
    int source_index;

    if (event->active == 0 || event->action_type != 4 ||
        event->player_id != floater->owner_slot ||
        event->payload_0a != floater->island_index ||
        !delivery_item_code_valid(event->payload_12) ||
        event->payload_0a < 0 || event->payload_0a >= session->island_count ||
        event->payload_0e < 0 ||
        event->payload_0e >= session->islands[event->payload_0a].location_count)
        return 0;

    if (event->payload_12 >= GAME_INVENTORY_ITEM_FIRST_ID &&
        !artifact_delivery_target_valid(session, floater,
            (uint8_t)event->payload_0a, event->payload_0e,
            event->payload_12)) return 0;
    /* One artifact turns one empty target into PIT_Object. Do not let
       concurrent workers reserve duplicate deliveries to that site. */
    if (event->payload_12 >= GAME_INVENTORY_ITEM_FIRST_ID &&
        event->assigned_floater_count != 0) return 0;

    source_index = floater->carried_resource_code == event->payload_12
        ? -1
        : refill_source(session, floater, event->payload_12, &source_island);
    if (floater->carried_resource_code != event->payload_12 && source_index < 0)
        return 0;
    if (event->assigned_floater_count == INT16_MAX) return 0;

    island = &session->islands[floater->island_index];
    ++event->assigned_floater_count;
    floater->active_order_action = 4;
    floater->order_resource_code = event->payload_12;
    floater->linked_task_slot = (int16_t)slot;
    floater->order_target_location = event->payload_0e;
    floater->order_target_island = (uint8_t)event->payload_0a;
    floater->order_source_island = source_island;
    floater->order_timer = 0;
    if (floater->carried_resource_code == event->payload_12) {
        floater_target_location(floater,
            &island->locations[(uint16_t)event->payload_0e], 4);
    } else {
        floater->order_source_location = (int16_t)source_index;
        if (source_island == floater->island_index) {
            floater_target_location(floater,
                &island->locations[(unsigned int)source_index], 3);
        } else {
            const GameRuntimeLocation *source = &session->islands[source_island]
                .locations[(unsigned int)source_index];
            floater->source_order_coordinate_30 = (uint16_t)(
                ((uint16_t)(((uint32_t)source->x + 5U) / 10U) << 8) |
                (uint16_t)(((uint32_t)source->y + 5U) / 10U));
            if (!game_session_begin_floater_handoff(
                    session, floater, source_island)) {
                floater->active_order_action = 0;
                release_task_claim(session, floater);
                return 0;
            }
            floater->handoff_resume_state = 3;
        }
    }
    floater->has_wander_order = 0;
    floater->wander_timer = 0;
    return 1;
}

static void assign_resource_tasks(GameSession *session,
                                  const PadCatalog *catalog);

void game_session_assign_local_resource_tasks(GameSession *session,
                                               const PadCatalog *catalog)
{
    assign_resource_tasks(session, catalog);
}

static int construction_task_details(const GameSession *session,
                                     const PadCatalog *catalog,
                                     const GamePendingEvent *event,
                                     const GameRuntimeLocation **target_out,
                                     const PadCatalogItem **item_out)
{
    const GameRuntimeLocation *target;
    const PadCatalogItem *item;
    uint16_t item_id;

    if (session == NULL || catalog == NULL || event == NULL ||
        event->active == 0 || event->action_type != 5 ||
        event->player_id < 0 || event->player_id >= GAME_START_PLAYER_COUNT ||
        event->payload_0a < 0 || event->payload_0a >= session->island_count ||
        event->payload_0e < 0 || event->payload_12 < 0x25 ||
        event->payload_12 > 0x34) return 0;
    {
        const GameRuntimeIsland *island =
            &session->islands[event->payload_0a];
        if ((uint16_t)event->payload_0e >= island->location_count) return 0;
        target = &island->locations[(uint16_t)event->payload_0e];
    }
    if (target->renderer_class != 0 ||
        !game_session_build_target_available(target,
            (uint8_t)event->player_id) || target->construction_site_size > 2U)
        return 0;
    item_id = (uint16_t)(event->payload_12 + event->player_id * 16);
    item = pad_catalog_find(catalog, item_id);
    /* Keep assignment consistent with game_session_place_building: never
       dispatch a worker to a pad that cannot fit this construction site. */
    if (item == NULL || item->size < 0 ||
        item->size > target->construction_site_size ||
        item->building_tone_cost <= 0) return 0;
    /* FUN_004526de, called by FUN_00452794, also requires the pad's +0x0c
       maintenance cost to fit the player's remaining maintenance budget. */
    if (item->maintenance_tone_cost >
        session->economy[(uint8_t)event->player_id].source_maintenance_budget)
        return 0;
    if (target_out != NULL) *target_out = target;
    if (item_out != NULL) *item_out = item;
    return 1;
}

static int assign_construction_task_for_floater(
    GameSession *session, const PadCatalog *catalog,
    GameFloaterStart *floater, unsigned int slot)
{
    GamePendingEvent *event = &session->pending_events[slot];
    const GameRuntimeLocation *target;
    const PadCatalogItem *item;
    uint32_t reserved;
    uint8_t source_island = floater->island_index;
    int source_index;
    int finalize_building;

    if (event->player_id != floater->owner_slot ||
        !construction_task_details(session, catalog, event, &target, &item))
        return 0;
    finalize_building = target->resource_stock[GAME_RESOURCE_BUILD_TONE] >=
        (uint16_t)item->building_tone_cost;
    if (finalize_building) {
        /* The task's assigned count includes workers still returning from a
           source. Let those orders drain before assigning the single state-5
           finisher; otherwise several idle workers can queue for one site. */
        if (event->assigned_floater_count != 0) return 0;
        source_index = -1;
    } else {
        reserved = target->resource_stock[GAME_RESOURCE_BUILD_TONE] +
            (uint16_t)event->assigned_floater_count;
        if (reserved >= (uint16_t)item->building_tone_cost) return 0;
        source_index = floater->carried_resource_code == 1 ? -1 :
            construction_refill_source(session, floater, &source_island);
        if (floater->carried_resource_code != 1 && source_index < 0) return 0;
    }
    if (event->payload_0a != source_island &&
        !construction_handoff_available(session, source_island,
                                         floater->owner_slot)) return 0;

    ++event->assigned_floater_count;
    floater->active_order_action = 4;
    floater->order_resource_code = 1;
    floater->linked_task_slot = (int16_t)slot;
    floater->order_target_location = event->payload_0e;
    floater->order_target_island = (uint8_t)event->payload_0a;
    floater->order_source_island = source_island;
    floater->order_timer = 0;
    if (finalize_building) {
        if (event->payload_0a == floater->island_index) {
            floater_target_location(floater, target, 5);
        } else {
            floater->source_order_coordinate_30 = (uint16_t)(
                ((uint16_t)(((uint32_t)target->x + 5U) / 10U) << 8) |
                (uint16_t)(((uint32_t)target->y + 5U) / 10U));
            if (!game_session_begin_floater_handoff(
                    session, floater, (uint8_t)event->payload_0a)) {
                floater->active_order_action = 0;
                release_task_claim(session, floater);
                return 0;
            }
            floater->handoff_resume_action = 4;
            floater->handoff_resume_state = 5;
        }
    } else if (source_index < 0) {
        if (event->payload_0a == floater->island_index) {
            floater_target_location(floater, target, 4);
        } else {
            floater->source_order_coordinate_30 = (uint16_t)(
                ((uint16_t)(((uint32_t)target->x + 5U) / 10U) << 8) |
                (uint16_t)(((uint32_t)target->y + 5U) / 10U));
            if (!game_session_begin_floater_handoff(
                    session, floater, (uint8_t)event->payload_0a)) {
                floater->active_order_action = 0;
                release_task_claim(session, floater);
                return 0;
            }
            floater->handoff_resume_action = 4;
            floater->handoff_resume_state = 4;
        }
    } else {
        const GameRuntimeLocation *source = &session->islands[source_island]
            .locations[(unsigned int)source_index];
        floater->order_source_location = (int16_t)source_index;
        if (source_island == floater->island_index) {
            floater_target_location(floater, source, 3);
        } else {
            floater->source_order_coordinate_30 = (uint16_t)(
                ((uint16_t)(((uint32_t)source->x + 5U) / 10U) << 8) |
                (uint16_t)(((uint32_t)source->y + 5U) / 10U));
            if (!game_session_begin_floater_handoff(
                    session, floater, source_island)) {
                floater->active_order_action = 0;
                release_task_claim(session, floater);
                return 0;
            }
            floater->handoff_resume_state = 3;
        }
    }
    floater->has_wander_order = 0;
    floater->wander_timer = 0;
    return 1;
}

static int assign_repair_task_for_floater(GameSession *session,
                                         const PadCatalog *catalog,
                                         GameFloaterStart *floater,
                                         unsigned int slot)
{
    GamePendingEvent *event = &session->pending_events[slot];
    GameRuntimeLocation *target;
    int16_t current;
    int16_t maximum;

    /* FUN_00422031 admits REPAIR candidates only when floater subtype != 1. */
    if (floater->source_subtype == 1 ||
        event->active == 0 || event->action_type != 0x12 ||
        event->player_id != floater->owner_slot ||
        event->payload_0a < 0 || event->payload_0a >= session->island_count ||
        event->payload_0e < 0 ||
        (uint16_t)event->payload_0e >=
            session->islands[event->payload_0a].location_count ||
        event->assigned_floater_count == INT16_MAX ||
        !game_session_repair_task_values(session, catalog, event,
                                         &current, &maximum) ||
        current >= maximum) return 0;

    target = &session->islands[event->payload_0a]
                  .locations[(uint16_t)event->payload_0e];
    if (target->owner_id != floater->owner_slot) return 0;

    ++event->assigned_floater_count;
    floater->active_order_action = 0x12;
    floater->linked_task_slot = (int16_t)slot;
    floater->order_target_location = event->payload_0e;
    floater->order_target_island = (uint8_t)event->payload_0a;
    floater->order_resource_code = 1;
    floater->order_timer = 0;
    if (floater->carried_resource_code == 1 &&
        event->payload_0a == floater->island_index) {
        floater_target_location(floater, target, 4);
    } else if (floater->carried_resource_code == 1) {
        floater->source_order_coordinate_30 = (uint16_t)(
            ((uint16_t)(((uint32_t)target->x + 5U) / 10U) << 8) |
            (uint16_t)(((uint32_t)target->y + 5U) / 10U));
        if (!game_session_begin_floater_handoff(
                session, floater, (uint8_t)event->payload_0a)) {
            floater->active_order_action = 0;
            release_task_claim(session, floater);
            return 0;
        }
        floater->handoff_resume_state = 4;
    } else if (!game_session_start_repair_supply(session, floater)) {
        floater->active_order_action = 0;
        release_task_claim(session, floater);
        return 0;
    }
    floater->has_wander_order = 0;
    floater->wander_timer = 0;
    return 1;
}

static void assign_resource_tasks(GameSession *session,
                                  const PadCatalog *catalog)
{
    uint8_t priority_three_pending[GAME_FLOATER_CATEGORY_COUNT] = {0};
    unsigned int floater_index;
    unsigned int slot;

    if (session == NULL) return;
    for (slot = 0; slot < GAME_SESSION_MAX_PENDING_EVENTS; ++slot) {
        const GamePendingEvent *event = &session->pending_events[slot];
        if (event->active != 0 && event->priority == 3 &&
            event->player_id >= 0 &&
            event->player_id < GAME_FLOATER_CATEGORY_COUNT) {
            priority_three_pending[event->player_id] = 1;
        }
    }
    for (floater_index = 0; floater_index < session->floater_count;
         ++floater_index) {
        GameFloaterStart *floater = &session->floaters[floater_index];
        int idle_wander = floater->movement_state == 0x0e &&
            floater->has_wander_order && !floater->has_move_order;
        int replacing_move = floater->active_order_action == 9 &&
            floater->movement_state == 9;
        int can_take_local_task = floater->active_order_action == 0 &&
            (floater->movement_state == 0 || idle_wander);
        int can_take_construction =
            (floater->active_order_action == 0 || replacing_move) &&
            (floater->movement_state == 0 || floater->movement_state == 9 ||
             idle_wander) &&
            (floater->carried_resource_code == 0 ||
             floater->carried_resource_code == 1);

        if (!game_session_floater_is_active(floater) ||
            (floater->source_runtime_flags & 0x008U) != 0 ||
            floater->linked_task_slot != -1 || floater->source_link_0c != -1 ||
            floater->type_index == 4 || floater->source_subtype == 8 ||
            floater->owner_slot >= GAME_FLOATER_CATEGORY_COUNT ||
            floater->island_index >= session->island_count) continue;

        /* FUN_0042219e checks the first eligible row in slot order. Keep the
           task type's worker guards, but arbitrate CONSTR/CHARGE/delivery in
           that shared order instead of giving one type a fixed priority. */
        for (slot = 0; slot < GAME_SESSION_MAX_PENDING_EVENTS; ++slot) {
            GamePendingEvent *event = &session->pending_events[slot];
            int special_task = event->action_type == 0x0b ||
                (event->action_type == 4 && event->payload_12 >= 5 &&
                 event->payload_12 < 0x22);

            if (priority_three_pending[floater->owner_slot] &&
                event->priority != 3 && !special_task) continue;
            if (!special_task) {
                int assigned = event->assigned_floater_count;
                if (event->priority == 1) {
                    if (assigned >= 999) continue;
                } else if (event->priority == 2) {
                    /* With no current task, FUN_0042219e starts at
                       local_34=1000/priority=1 and accepts priority 2 while
                       assigned_count < local_34*2 - 2. */
                    if (assigned < 0 || assigned >= 1998) continue;
                } else if (event->priority != 3) {
                    continue;
                }
            }
            if (event->action_type == 0x0b && can_take_local_task &&
                assign_charge_task_for_floater(
                    session, floater, floater_index, slot)) break;
            if (event->action_type == 4 && can_take_local_task &&
                assign_delivery_task_for_floater(session, floater, slot)) break;
            if (event->action_type == 5 && catalog != NULL &&
                can_take_construction &&
                assign_construction_task_for_floater(
                    session, catalog, floater, slot)) break;
            if (event->action_type == 0x12 && catalog != NULL &&
                can_take_local_task &&
                assign_repair_task_for_floater(
                    session, catalog, floater, slot)) break;
        }
    }
}

static int deposit_construction_resource(GameSession *session,
                                         GameFloaterStart *floater,
                                         int16_t resource_code)
{
    GamePendingEvent *event;
    GameRuntimeLocation *target;
    int16_t slot = floater->linked_task_slot;

    if (slot < 0 || slot >= GAME_SESSION_MAX_PENDING_EVENTS) return 0;
    event = &session->pending_events[(uint8_t)slot];
    if (event->active == 0 || event->action_type != 5 ||
        event->player_id != floater->owner_slot || resource_code != 1 ||
        event->payload_0a != floater->order_target_island ||
        event->payload_0e != floater->order_target_location ||
        event->payload_0a < 0 || event->payload_0a >= session->island_count ||
        event->payload_0e < 0 ||
        (uint16_t)event->payload_0e >=
            session->islands[event->payload_0a].location_count) return 0;

    target = &session->islands[event->payload_0a]
        .locations[(uint16_t)event->payload_0e];
    if (target->renderer_class != 0 ||
        !game_session_build_target_available(target, floater->owner_slot) ||
        target->resource_stock[0] == UINT16_MAX)
        return 0;
    ++target->resource_stock[0];
    floater->carried_resource_code = 0;
    return 1;
}

static int floater_has_construction_task(const GameSession *session,
                                         const GameFloaterStart *floater)
{
    int16_t slot = floater->linked_task_slot;
    const GamePendingEvent *event;
    if (slot < 0 || slot >= GAME_SESSION_MAX_PENDING_EVENTS) return 0;
    event = &session->pending_events[(uint8_t)slot];
    return event->active != 0 && event->action_type == 5 &&
        event->player_id == floater->owner_slot &&
        event->payload_0a == floater->order_target_island &&
        event->payload_0e == floater->order_target_location;
}

static void credit_floater_delivery(GameSession *session,
                                    GameFloaterStart *floater,
                                    int16_t resource_code)
{
    if (floater_has_construction_task(session, floater)) {
        (void)deposit_construction_resource(session, floater, resource_code);
    } else if (resource_code >= 1 &&
               resource_code <= GAME_RESOURCE_TYPE_COUNT &&
               game_session_credit_resource(session, floater->owner_slot,
                   (GameResourceType)(resource_code - 1), 1)) {
        floater->carried_resource_code = 0;
    } else if (resource_code >= GAME_INVENTORY_ITEM_FIRST_ID &&
               resource_code < GAME_INVENTORY_ITEM_FIRST_ID +
                                   GAME_INVENTORY_ITEM_COUNT &&
               floater->owner_slot < GAME_START_PLAYER_COUNT &&
               floater->island_index < session->island_count &&
               floater->order_target_location >= 0 &&
               (uint16_t)floater->order_target_location <
                   session->islands[floater->island_index].location_count) {
        GameRuntimeLocation *target = &session->islands[floater->island_index]
            .locations[(uint16_t)floater->order_target_location];
        if (target->renderer_class == 2) {
            if (resource_code == 5 &&
                (target->source_flags & 0x004U) == 0) {
                /* FUN_004503bd case 2 stores the actor dword at raw +0x2c,
                   starts CONS and clears +0x40. +0x2c aliases the third
                   stock short in the runtime layout; on class 2 it is the
                   contributor slot, not stock. */
                target->resource_stock[GAME_RESOURCE_MAGIC_TONE] =
                    floater->owner_slot;
                target->source_flags |= 0x004U;
                target->construction_progress = 0;
                floater->carried_resource_code = 0;
            } else {
                /* If CONS is already active (or another artifact arrives),
                   FUN_004503bd falls through to FUN_0045f075(code, 1) and
                   credits the contributing player's artifact inventory. */
                ++session->economy[floater->owner_slot].inventory_count[
                    (unsigned int)(resource_code - GAME_INVENTORY_ITEM_FIRST_ID)];
                floater->carried_resource_code = 0;
            }
        } else if (target->renderer_class == 0 && target->owner_id == -1 &&
            target->record_value_10 == 0) {
            /* FUN_004503bd turns an empty class-0 record into PIT_Object and
               stores artifact IDs 5..33 in its +0x24 value. */
            target->record_value_10 = 1;
            target->record_value_24 = resource_code;
            floater->carried_resource_code = 0;
        } else if (target->renderer_class == 0 &&
                   target->owner_id == (int32_t)floater->owner_slot) {
            int32_t base_item_id = target->record_value_10 -
                (int32_t)floater->owner_slot * 16;
            if ((location_is_player_hall(target) ||
                 (base_item_id >= 0x2c && base_item_id <= 0x30)) &&
                session->economy[floater->owner_slot]
                    .inventory_count[(unsigned int)(resource_code -
                        GAME_INVENTORY_ITEM_FIRST_ID)] != UINT16_MAX) {
                /* FUN_004503bd routes artifacts at these receivers through
                   FUN_0045f075, which increments the owner's item count. */
                ++session->economy[floater->owner_slot]
                    .inventory_count[(unsigned int)(resource_code -
                        GAME_INVENTORY_ITEM_FIRST_ID)];
                floater->carried_resource_code = 0;
            }
        }
    }
}

void game_session_update_construction_tasks(GameSession *session,
                                             const PadCatalog *catalog)
{
    unsigned int slot;

    if (session == NULL || catalog == NULL) return;

    /* Keep valid CONSTR tasks queued until a worker reaches the target.
       FUN_0041e569's state-5 arrival calls FUN_004527ee to place the pad. */
    for (slot = 0; slot < GAME_SESSION_MAX_PENDING_EVENTS; ++slot) {
        GamePendingEvent *event = &session->pending_events[slot];
        if (event->active != 0 && event->action_type == 5 &&
            event->payload_0a >= 0 && event->payload_0a < session->island_count &&
            event->payload_0e >= 0 &&
            (uint16_t)event->payload_0e <
                session->islands[event->payload_0a].location_count) {
            const GameRuntimeLocation *target = &session->islands[event->payload_0a]
                .locations[(uint16_t)event->payload_0e];
            if (!game_session_build_target_available(target,
                    (uint8_t)event->player_id) ||
                target->construction_site_size > 2U) {
                /* FUN_00466533 detaches every floater whose active order
                   references this slot before the invalid CONSTR task goes. */
                GamePendingEvent expected = *event;
                (void)game_session_dispatch_task_command(
                    session, (uint8_t)slot, 12, &expected);
                continue;
            }
        }

    }

}

void game_session_advance_local_resource_task(GameSession *session,
                                       const PadCatalog *catalog,
                                       GameFloaterStart *floater)
{
    GameRuntimeIsland *island;
    GameRuntimeLocation *target;
    int16_t code;
    int recharge_order;

    if (session == NULL || floater == NULL) return;
    recharge_order = floater->active_order_action == 2 ||
        floater->active_order_action == 17;
    if ((floater->active_order_action != 4 && !recharge_order &&
         floater->active_order_action != 0x12) ||
        catalog == NULL ||
        floater->island_index >= session->island_count ||
        floater->x != floater->destination_x || floater->y != floater->destination_y)
        return;

    if (floater->active_order_action == 4 && floater->movement_state == 5) {
        int16_t slot = floater->linked_task_slot;
        GamePendingEvent *event;
        const GameRuntimeLocation *build_target;
        const PadCatalogItem *build_item;
        IslandLocation site = {0};

        if (slot < 0 || slot >= GAME_SESSION_MAX_PENDING_EVENTS) return;
        event = &session->pending_events[(uint8_t)slot];
        if (event->active == 0 || event->action_type != 5 ||
            event->player_id != floater->owner_slot ||
            event->payload_0a != floater->order_target_island ||
            event->payload_0e != floater->order_target_location ||
            !construction_task_details(session, catalog, event,
                                       &build_target, &build_item) ||
            build_target->resource_stock[GAME_RESOURCE_BUILD_TONE] <
                (uint16_t)build_item->building_tone_cost) {
            floater->active_order_action = 0;
            release_task_claim(session, floater);
            floater->movement_state = 0;
            floater->has_move_order = 0;
            return;
        }

        site.kind = ISLAND_LOCATION_PAD;
        site.renderer_subtype = build_target->construction_site_size;
        if (game_session_place_building(session, catalog,
                (uint8_t)event->player_id, (uint8_t)event->payload_0a,
                (uint16_t)event->payload_0e, &site,
                (uint16_t)event->payload_12, NULL, 0)) {
            GamePendingEvent expected = *event;
            (void)game_session_dispatch_task_command(
                session, (uint8_t)slot, 12, &expected);
        } else {
            floater->active_order_action = 0;
            release_task_claim(session, floater);
            floater->movement_state = 0;
            floater->has_move_order = 0;
        }
        return;
    }

    if (recharge_order && floater->movement_state == 2) {
        int special_receiver;

        if (floater->order_target_island != floater->island_index ||
            floater->order_target_location < 0 ||
            (uint16_t)floater->order_target_location >=
                session->islands[floater->island_index].location_count) return;
        island = &session->islands[floater->island_index];
        target = &island->locations[(uint16_t)floater->order_target_location];
        /* FUN_004211bb stores FA_Recharge's requested code in the floater
           +0x30 word. This field is also used by other states as packed data. */
        code = (int16_t)floater->source_order_coordinate_30;
        if (!delivery_item_code_valid(code)) {
            floater->active_order_action = 0;
            floater->movement_state = 0;
            floater->has_move_order = 0;
            floater->order_timer = 0;
            floater->source_runtime_flags &= ~1U;
            floater->has_wander_order = 1;
            floater->wander_timer = 0;
            return;
        }

        /* FUN_0041e569's state-2 case waits at Halls/linked sites, then uses
           FUN_00452c31/FUN_00452eac to withdraw one requested resource. */
        /* Native producer sources use their +0x36 retry counter while PROD
           completes. Do not route a linked producer through the fixed
           20-tick Hall/source wait, which can expire before its output exists. */
        special_receiver = location_is_player_hall(target) ||
            ((target->source_location_slot_18 != -1 ||
              (floater->source_runtime_flags & 1U) != 0) &&
             !location_is_producer_for_resource(target,
                 floater->owner_slot, code));
        if (special_receiver) {
            if (floater->order_timer == 0) {
                /* FUN_0041e569 calls FUN_00425084 before starting the 20-tick
                   Hall/source wait; that helper drops or stores carried items. */
                game_session_drop_carried_artifact(session, floater);
                floater->source_runtime_flags |= 1U;
                floater->order_timer = 1;
                return;
            }
            if (floater->order_timer < 20) {
                ++floater->order_timer;
                return;
            }
            if (target->renderer_class == 0 &&
                game_session_location_resource_available(session,
                    floater->island_index,
                    (uint16_t)floater->order_target_location, code) &&
                game_session_consume_location_resource(session,
                    floater->island_index,
                    (uint16_t)floater->order_target_location, code)) {
                floater->carried_resource_code = code;
            }
        } else {
            int available = 0;
            if (floater->order_timer < INT16_MAX) ++floater->order_timer;
            if (target->resource_retry_tick_36 <
                (int16_t)floater->order_timer) {
                /* FUN_00452e4d clears the source's raw +0x2c before checking
                   whether the requested output can be consumed this tick. */
                target->resource_stock[GAME_RESOURCE_MAGIC_TONE] = 0;
                available = game_session_location_resource_available(session,
                    floater->island_index,
                    (uint16_t)floater->order_target_location, code);
                if (available) {
                    target->resource_retry_tick_36 = 0;
                    available = game_session_consume_location_resource(session,
                        floater->island_index,
                        (uint16_t)floater->order_target_location, code);
                } else {
                    target->resource_retry_tick_36 =
                        (int16_t)floater->order_timer;
                }
            }
            if (available) {
                floater->carried_resource_code = code;
            } else if (local_refill_source_is_valid(session,
                           floater->island_index,
                           (uint16_t)floater->order_target_location,
                           floater->owner_slot, code)) {
                return;
            }
        }

        floater->active_order_action = 0;
        floater->movement_state = 0;
        floater->has_move_order = 0;
        floater->order_timer = 0;
        floater->source_runtime_flags &= ~1U;
        floater->has_wander_order = 1;
        floater->wander_timer = 0;
        return;
    }

    code = floater->order_resource_code;
    if (floater->movement_state == 3) {
        GameRuntimeLocation *source;
        if (floater->island_index != floater->order_source_island ||
            floater->order_source_island >= session->island_count ||
            floater->order_source_location < 0 ||
            (uint16_t)floater->order_source_location >=
                session->islands[floater->order_source_island].location_count)
            return;
        island = &session->islands[floater->order_source_island];
        if (floater->order_source_location < 0 ||
            (uint16_t)floater->order_source_location >= island->location_count)
            return;
        source = &island->locations[(uint16_t)floater->order_source_location];
        if (location_is_player_hall(source) ||
            ((source->source_location_slot_18 != -1 ||
              (floater->source_runtime_flags & 1U) != 0) &&
             !location_is_producer_for_resource(source,
                 floater->owner_slot, code))) {
            /* This branch counts to 20 after arrival before checking stock. */
            if (floater->order_timer == 0) {
                floater->source_runtime_flags |= 1U;
                floater->order_timer = 1;
            } else if (floater->order_timer < 20) {
                ++floater->order_timer;
            }
            if (floater->order_timer < 20) return;
            if (!game_session_location_resource_available(session,
                    floater->island_index,
                    (uint16_t)floater->order_source_location, code) ||
                !game_session_consume_location_resource(session,
                    floater->island_index,
                    (uint16_t)floater->order_source_location, code)) {
                floater->active_order_action = 0;
                release_task_claim(session, floater);
                floater->has_move_order = 0;
                floater->movement_state = 0;
                floater->source_runtime_flags &= ~1U;
                floater->has_wander_order = 1;
                floater->wander_timer = 0;
                floater->order_timer = 0;
                return;
            }
            floater->source_runtime_flags &= ~1U;
        } else {
            int available = 0;
            /* FUN_00452e4d compares source +0x36 with the floater pickup tick.
               It checks output availability when the counter advances, resets
               +0x36 on success, and records the attempted tick on failure.
               Runtime initialization of +0x36 is not established by the
               decompilation; the remake starts this modeled field at zero. */
            if (floater->order_timer < INT16_MAX) ++floater->order_timer;
            if (source->resource_retry_tick_36 < (int16_t)floater->order_timer) {
                available = game_session_location_resource_available(session,
                    floater->island_index,
                    (uint16_t)floater->order_source_location, code);
                if (available) {
                    source->resource_retry_tick_36 = 0;
                    available = game_session_consume_location_resource(session,
                        floater->island_index,
                        (uint16_t)floater->order_source_location, code);
                } else {
                    source->resource_retry_tick_36 = (int16_t)floater->order_timer;
                }
            }
            if (!available) {
                if (!local_refill_source_is_valid(session, floater->island_index,
                        (uint16_t)floater->order_source_location,
                        floater->owner_slot, code)) {
                    floater->active_order_action = 0;
                    release_task_claim(session, floater);
                    floater->has_move_order = 0;
                    floater->movement_state = 0;
                    floater->source_runtime_flags &= ~1U;
                    floater->has_wander_order = 1;
                    floater->wander_timer = 0;
                }
                return;
            }
        }
        floater->carried_resource_code = code;
        floater->order_timer = 0;
        if (floater->order_target_island != floater->island_index) {
            const GameRuntimeLocation *hall;
            if (floater->order_target_island >= session->island_count ||
                floater->order_target_location < 0 ||
                (uint16_t)floater->order_target_location >=
                    session->islands[floater->order_target_island].location_count)
                return;
            hall = &session->islands[floater->order_target_island]
                        .locations[(uint16_t)floater->order_target_location];
            floater->source_order_coordinate_30 = (uint16_t)(
                ((uint16_t)(((uint32_t)hall->x + 5U) / 10U) << 8) |
                (uint16_t)(((uint32_t)hall->y + 5U) / 10U));
            if (game_session_begin_floater_handoff(
                    session, floater, floater->order_target_island)) {
                floater->handoff_resume_state = 4;
                return;
            }
            floater->active_order_action = 0;
            release_task_claim(session, floater);
            floater->movement_state = 0;
            return;
        }
        island = &session->islands[floater->order_target_island];
        target = &island->locations[(uint16_t)floater->order_target_location];
        floater_target_location(floater, target, 4);
        return;
    }
    if (floater->movement_state != 4) return;

    if (floater->island_index != floater->order_target_island ||
        floater->order_target_island >= session->island_count ||
        floater->order_target_location < 0 ||
        (uint16_t)floater->order_target_location >=
            session->islands[floater->order_target_island].location_count)
        return;
    island = &session->islands[floater->order_target_island];
    target = &island->locations[(uint16_t)floater->order_target_location];

    if (floater->active_order_action == 0x12) {
        int16_t slot = floater->linked_task_slot;
        GamePendingEvent *event;
        if (slot < 0 || slot >= GAME_SESSION_MAX_PENDING_EVENTS) return;
        event = &session->pending_events[(uint8_t)slot];
        if (event->active == 0 || event->action_type != 0x12 ||
            event->player_id != floater->owner_slot ||
            event->payload_0a != floater->order_target_island ||
            event->payload_0e != floater->order_target_location ||
            floater->carried_resource_code != 1 ||
            target->owner_id != floater->owner_slot ||
            target->resource_stock[GAME_RESOURCE_BUILD_TONE] == UINT16_MAX) {
            floater->active_order_action = 0;
            release_task_claim(session, floater);
            floater->has_move_order = 0;
            floater->movement_state = 0;
            floater->order_timer = 0;
            floater->has_wander_order = 1;
            floater->wander_timer = 0;
            return;
        }

        /* FUN_004211bb sends a worker carrying Build Tone straight to the
           repair site; after arrival the local +0x28 stock receives it. */
        ++target->resource_stock[GAME_RESOURCE_BUILD_TONE];
        floater->carried_resource_code = GAME_RESOURCE_NONE;
        floater->order_timer = 0;
        floater->movement_state = 0x12;
        floater->has_move_order = 0;
        return;
    }

    /* FUN_0041e569 state 4 (switch case 3) reaches FUN_004503bd after exact
       arrival. For a Hall-class target it waits through the source's 20-tick
       phase, then attempts the resource credit; cargo is cleared only on
       success. FUN_004527ee belongs to the following state, not this deposit. */
    if (location_is_player_hall(target) ||
        target->source_location_slot_18 != -1 ||
        (floater->source_runtime_flags & 1U) != 0) {
        if (floater->order_timer == 0) {
            floater->source_runtime_flags |= 1U;
            floater->order_timer = 1;
            return;
        }
        if (floater->order_timer < 20) {
            ++floater->order_timer;
            return;
        }
        credit_floater_delivery(session, floater, code);
        floater->source_runtime_flags &= ~1U;
        floater->active_order_action = 0;
        release_task_claim(session, floater);
        floater->has_move_order = 0;
        floater->movement_state = 0;
        floater->order_timer = 0;
        floater->has_wander_order = 1;
        floater->wander_timer = 0;
        return;
    }

    /* The other state-4 path finishes on exact arrival and attempts the same
       receiver without the 20-tick Hall wait. */
    credit_floater_delivery(session, floater, code);
    floater->active_order_action = 0;
    release_task_claim(session, floater);
    floater->has_move_order = 0;
    floater->movement_state = 0;
    floater->order_timer = 0;
    floater->source_runtime_flags &= ~1U;
    floater->has_wander_order = 1;
    floater->wander_timer = 0;
}

#include "game_session_delivery_internal.h"

int local_refill_source_is_valid(const GameSession *session,
                                       uint8_t island_index,
                                       uint16_t location_index,
                                       int16_t player_id,
                                       int16_t resource_code)
{
    const GameRuntimeIsland *island;

    if (session == NULL || island_index >= session->island_count ||
        !delivery_item_code_valid(resource_code)) return 0;
    island = &session->islands[island_index];
    if (location_index >= island->location_count) return 0;
    if (resource_code >= GAME_INVENTORY_ITEM_FIRST_ID) {
        const GameRuntimeLocation *location = &island->locations[location_index];
        if (location->renderer_class == 0 && location->record_value_10 == 1 &&
            location->owner_id == -1 &&
            location->record_value_24 == resource_code &&
            game_session_location_resource_available(session, island_index,
                location_index, resource_code)) return 1;
        return location->owner_id == player_id &&
            (location_is_player_hall(location) ||
             location->source_location_slot_18 != -1) &&
            game_session_location_resource_available(session, island_index,
                location_index, resource_code);
    }
    {
        const GameRuntimeLocation *location = &island->locations[location_index];
        /* FUN_00452ceb accepts the owning player's Hall as a refill source for
           each resource when its corresponding raw stock is positive. The
           generic refill search visits connected islands too, so recognizing
           Hall stock here enables cross-island construction supply. */
        if (location->owner_id == player_id &&
            location_is_player_hall(location) &&
            location->resource_stock[resource_code - 1] != 0) return 1;
        return (location->source_flags & 1U) != 0 &&
            location_is_producer_for_resource(location, player_id,
                                               resource_code);
    }
}

static int local_refill_source_on_island(GameSession *session,
                                         uint8_t island_index,
                                         const GameFloaterStart *floater,
                                         int16_t resource_code)
{
    const GameRuntimeIsland *island;
    uint16_t candidate_indices[10];
    int32_t candidate_distances[10];
    int32_t candidate_weights[10];
    unsigned int candidate_count = 0;
    int32_t distance_sum = 0;
    double inverse_weight_sum = 0.0;
    int32_t roll;
    unsigned int location_index;

    if (island_index >= session->island_count ||
        floater == 0 || floater->type_index >= GAME_FLOATER_CATEGORY_COUNT ||
        !delivery_item_code_valid(resource_code)) return -1;
    island = &session->islands[island_index];
    /* FUN_00420a55 mode 0 filters by FUN_00452ceb and the floater's X window,
       keeps the ten lowest-distance candidates, then samples inversely by
       distance through FUN_0041e28e. */
    for (location_index = 0; location_index < island->location_count;
         ++location_index) {
        const GameRuntimeLocation *location = &island->locations[location_index];
        int32_t distance;
        unsigned int largest_index;
        unsigned int i;

        if (!local_refill_source_is_valid(session, island_index,
                (uint16_t)location_index, floater->owner_slot, resource_code) ||
            floater->owner_slot >= GAME_FLOATER_CATEGORY_COUNT ||
            (int32_t)location->x < island->floater_min_x[floater->owner_slot] ||
            (int32_t)location->x > island->floater_max_x[floater->owner_slot]) {
            continue;
        }
        distance = game_session_source_chebyshev_distance(
            floater->x, floater->y, location->x, location->y);
        if (distance == 0) continue;
        if (candidate_count < 10) {
            candidate_indices[candidate_count] = (uint16_t)location_index;
            candidate_distances[candidate_count] = distance;
            ++candidate_count;
            continue;
        }

        largest_index = 0;
        for (i = 1; i < candidate_count; ++i) {
            if (candidate_distances[i] > candidate_distances[largest_index])
                largest_index = i;
        }
        if (distance < candidate_distances[largest_index]) {
            candidate_indices[largest_index] = (uint16_t)location_index;
            candidate_distances[largest_index] = distance;
        }
    }
    if (candidate_count == 0) return -1;

    for (location_index = 0; location_index < candidate_count; ++location_index)
        distance_sum += candidate_distances[location_index];
    for (location_index = 0; location_index < candidate_count; ++location_index)
        inverse_weight_sum += (double)distance_sum /
                              (double)candidate_distances[location_index];

    /* FUN_0041e28e stores each normalized inverse-distance weight separately,
       then compares the same random roll against each weight in candidate
       order. It does not turn these weights into cumulative thresholds. */
    for (location_index = 0; location_index < candidate_count; ++location_index) {
        double raw_weight = (double)distance_sum /
                            (double)candidate_distances[location_index];
        candidate_weights[location_index] = (int32_t)(
            (1000.0 / inverse_weight_sum) * raw_weight);
    }

    roll = tone_rng_bounded(&session->random_state, 1000);
    for (location_index = 0; location_index < candidate_count; ++location_index)
        if (roll < candidate_weights[location_index])
            return (int)candidate_indices[location_index];
    return -1;
}

int refill_source(GameSession *session, const GameFloaterStart *floater,
                  int16_t resource_code, uint8_t *source_island)
{
    unsigned int island_index;
    uint8_t current_island;
    uint8_t access_bit;
    int location_index;

    if (session == 0 || floater == 0 || source_island == 0 ||
        floater->island_index >= session->island_count ||
        floater->owner_slot >= GAME_FLOATER_CATEGORY_COUNT)
        return -1;

    current_island = floater->island_index;
    location_index = local_refill_source_on_island(
        session, current_island, floater, resource_code);
    if (location_index >= 0) {
        *source_island = current_island;
        return location_index;
    }

    /* FUN_00420dbd checks the current island first, then accessible island
       records in global order. Runtime +0x29ac is indexed by player slot. */
    access_bit = (uint8_t)(1U << floater->owner_slot);
    for (island_index = 0; island_index < session->island_count; ++island_index) {
        if (island_index == current_island ||
            (session->islands[island_index].access_mask & access_bit) == 0)
            continue;
        location_index = local_refill_source_on_island(
            session, (uint8_t)island_index, floater, resource_code);
        if (location_index >= 0) {
            *source_island = (uint8_t)island_index;
            return location_index;
        }
    }
    return -1;
}

void floater_target_location(GameFloaterStart *floater,
                                    const GameRuntimeLocation *location,
                                    uint8_t state)
{
    floater->destination_x = location->x;
    floater->destination_y = location->y;
    floater->movement_state = state;
    floater->stop_radius = 0;
    floater->has_move_order = 1;
}

void release_task_claim(GameSession *session, GameFloaterStart *floater)
{
    int16_t slot = floater->linked_task_slot;
    if (slot >= 0 && slot < GAME_SESSION_MAX_PENDING_EVENTS) {
        GamePendingEvent *event = &session->pending_events[(uint8_t)slot];
        int matches_resource_task = event->action_type == 4 &&
            event->player_id == floater->owner_slot &&
            event->payload_0a == floater->order_target_island &&
            event->payload_0e == floater->order_target_location &&
            event->payload_12 == floater->order_resource_code;
        int matches_construction_task = event->action_type == 5 &&
            event->player_id == floater->owner_slot &&
            event->payload_0a == floater->order_target_island &&
            event->payload_0e == floater->order_target_location &&
            floater->order_resource_code == 1;
        int matches_charge_task = event->action_type == 0x0b &&
            event->player_id == floater->owner_slot &&
            event->payload_0a == floater->order_target_island &&
            event->payload_0c == floater->order_target_location;
        int matches_repair_task = event->action_type == 0x12 &&
            event->player_id == floater->owner_slot &&
            event->payload_0a == floater->order_target_island &&
            event->payload_0e == floater->order_target_location;
        if (event->active != 0 &&
            (matches_resource_task || matches_construction_task ||
             matches_charge_task || matches_repair_task) &&
            event->assigned_floater_count > 0) {
            --event->assigned_floater_count;
        }
    }
    floater->linked_task_slot = -1;
}
