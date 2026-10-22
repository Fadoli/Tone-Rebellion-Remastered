#include "game_session.h"
#include "pad_catalog.h"

#include "game_session_economy_internal.h"
#include "game_session_internal.h"
#include "game_session_delivery_internal.h"

#include <string.h>

/* Player inventory, item-result and glyph action requests. */
static uint16_t *player_inventory_count(GameSession *session,
                                        uint8_t player_slot,
                                        uint8_t item_id)
{
    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT ||
        item_id < GAME_INVENTORY_ITEM_FIRST_ID ||
        item_id >= GAME_INVENTORY_ITEM_FIRST_ID + GAME_INVENTORY_ITEM_COUNT) {
        return NULL;
    }
    return &session->economy[player_slot].inventory_count[
        item_id - GAME_INVENTORY_ITEM_FIRST_ID];
}

int game_session_inventory_credit(GameSession *session, uint8_t player_slot,
                                  uint8_t item_id, uint32_t amount)
{
    uint16_t *count = player_inventory_count(session, player_slot, item_id);
    if (count == NULL || amount > UINT16_MAX - *count) return 0;
    *count = (uint16_t)(*count + amount);
    return 1;
}

int game_session_inventory_debit(GameSession *session, uint8_t player_slot,
                                 uint8_t item_id, uint32_t amount)
{
    uint16_t *count = player_inventory_count(session, player_slot, item_id);
    if (count == NULL || amount > *count) return 0;
    *count = (uint16_t)(*count - amount);
    return 1;
}

int game_session_dispatch_inventory_result(
    GameSession *session, uint8_t player_slot, uint8_t item_id,
    GameInventoryResultApply apply, void *context)
{
    uint16_t *count = player_inventory_count(session, player_slot, item_id);
    if (count == NULL || *count == 0 || apply == NULL) return 0;
    if (!apply(context, player_slot, item_id)) return 0;
    --*count;
    return 1;
}


int game_session_queue_inventory_action(GameSession *session,
                                        uint8_t player_slot,
                                        uint8_t island_index,
                                        uint16_t location_index,
                                        uint8_t item_id)
{
    const GameRuntimeIsland *island;
    const GameRuntimeLocation *location;

    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT ||
        island_index >= session->island_count ||
        item_id < GAME_INVENTORY_ITEM_FIRST_ID ||
        item_id >= GAME_INVENTORY_ITEM_FIRST_ID + GAME_INVENTORY_ITEM_COUNT) {
        return -1;
    }
    island = &session->islands[island_index];
    if (location_index >= island->location_count) return -1;

    location = &island->locations[location_index];
    /* FUN_0042fa0f(0x40) only rejects this exact class-0 state. Other
       location classes follow additional source rules that this check must
       not silently generalize. */
    if (location->renderer_class == 0 &&
        (location->record_value_10 != 0 || location->owner_id != -1)) return -1;

    /* Packet fields observed in FUN_0042fa0f: category 0, type 4, player,
       current island, zeroed +0x0c, clicked location, selected item. */
    return game_session_pending_event_add(session, (int16_t)player_slot,
        (int16_t)island_index, 4, 0, (int16_t)location_index, (int16_t)item_id);
}

int game_session_cycle_source_capacity(GameSession *session,
                                       uint8_t island_index,
                                       uint16_t location_index)
{
    GameRuntimeIsland *island;
    GameRuntimeLocation *location;
    int16_t next_tier;

    if (session == NULL || island_index >= session->island_count) return 0;
    island = &session->islands[island_index];
    if (location_index >= island->location_count) return 0;
    location = &island->locations[location_index];

    /* FUN_004672ef checks the native base item at +0x10; the player variant
       is a catalog lookup detail represented by the port's shifted ID. */
    {
        int32_t base_item_id = game_session_base_item_id(location);
        if (location->renderer_class != 0 ||
            (base_item_id != 0x2a &&
             (base_item_id < 0x2c || base_item_id > 0x30))) return 0;
    }

    next_tier = location->source_capacity_4a >= 0
        ? (int16_t)((location->source_capacity_4a + 1) & 3) : 0;

    /* FUN_00453cba marks the source for its tier-up transition only when the
       new tier is greater, and clears the cached value at +0x48 then. */
    if (next_tier > location->source_capacity_4a) {
        location->source_flags |= 0x20U;
        location->source_value_48 = 0;
    }
    location->source_capacity_4a = next_tier;
    return 1;
}

static const uint8_t staff_upgrade_max_tier[4] = {2, 2, 1, 2};
static const uint8_t staff_upgrade_island_thresholds[3][12] = {
    {1, 4, 6, 2, 5, 20, 20, 20, 3, 20, 20, 20},
    {1, 4, 7, 2, 5, 9, 8, 20, 20, 3, 6, 20},
    {1, 4, 7, 2, 5, 9, 8, 11, 20, 3, 6, 10}
};

static int staff_upgrade_eligible(const GameSession *session,
                                  uint8_t player_slot,
                                  uint8_t island_index,
                                  const GameRuntimeLocation *location)
{
    int32_t base_item_id;
    int32_t next_tier;
    unsigned int accessible_islands = 0;
    unsigned int i;
    unsigned int type_index;
    unsigned int world_index;

    if (session == NULL || location == NULL ||
        player_slot >= GAME_START_PLAYER_COUNT ||
        island_index >= session->island_count || location->owner_id != player_slot ||
        location->renderer_class != 0) return 0;
    base_item_id = game_session_base_item_id(location);
    if (base_item_id < 0x2c || base_item_id > 0x2f) return 0;
    type_index = (unsigned int)(base_item_id - 0x2c);
    next_tier = (int32_t)location->source_capacity_4a + 1;
    world_index = session->config.world_index;
    if (next_tier < 1 || next_tier > staff_upgrade_max_tier[type_index] ||
        world_index >= 3) return 0;

    for (i = 0; i < session->island_count; ++i) {
        if ((session->islands[i].access_mask &
             (uint8_t)(1U << player_slot)) != 0) ++accessible_islands;
    }
    return accessible_islands >= staff_upgrade_island_thresholds[world_index]
        [type_index * 3U + (unsigned int)next_tier];
}

static int staff_upgrade_task_matches(const GameSession *session,
                                      const GameRuntimeLocation *location,
                                      uint8_t player_slot,
                                      uint8_t island_index,
                                      uint16_t location_index)
{
    int16_t slot;
    const GamePendingEvent *event;

    if (session == NULL || location == NULL) return 0;
    slot = location->upgrade_task_handle;
    if (slot < 0 || slot >= GAME_SESSION_MAX_PENDING_EVENTS) return 0;
    event = &session->pending_events[(uint8_t)slot];
    return event->active != 0 && event->player_id == player_slot &&
        event->payload_0a == (int16_t)island_index &&
        event->action_type == 4 &&
        event->payload_0e == (int16_t)location_index &&
        event->payload_12 == 1;
}

int game_session_toggle_staff_upgrade_request(GameSession *session,
                                              uint8_t player_slot,
                                              uint8_t island_index,
                                              uint16_t location_index)
{
    GameRuntimeLocation *location;
    GamePendingEvent expected;
    int16_t task_slot;

    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT ||
        island_index >= session->island_count ||
        location_index >= session->islands[island_index].location_count)
        return 0;
    location = &session->islands[island_index].locations[location_index];
    task_slot = location->upgrade_task_handle;
    if (task_slot >= 0 && task_slot < GAME_SESSION_MAX_PENDING_EVENTS &&
        staff_upgrade_task_matches(session, location, player_slot,
                                   island_index, location_index)) {
        expected = session->pending_events[(uint8_t)task_slot];
        (void)game_session_dispatch_task_command(session, (uint8_t)task_slot,
                                                 12, &expected);
        location->upgrade_task_handle = -1;
        return 1;
    }
    location->upgrade_task_handle = -1;
    if (!staff_upgrade_eligible(session, player_slot, island_index, location))
        return 0;
    task_slot = (int16_t)game_session_pending_event_add(session,
        (int16_t)player_slot, (int16_t)island_index, 4, 0,
        (int16_t)location_index, 1);
    if (task_slot < 0) return 0;
    location->upgrade_task_handle = task_slot;
    return 1;
}

int game_session_complete_staff_upgrade(GameSession *session,
                                        const PadCatalog *catalog,
                                        uint8_t island_index,
                                        uint16_t location_index)
{
    GameRuntimeLocation *location;
    GamePendingEvent expected;
    int16_t old_maximum;
    int16_t new_maximum;
    int16_t next_tier;
    int16_t task_slot;

    if (session == NULL || catalog == NULL || island_index >= session->island_count ||
        location_index >= session->islands[island_index].location_count) return 0;
    location = &session->islands[island_index].locations[location_index];
    task_slot = location->upgrade_task_handle;
    if (location->owner_id < 0 || location->owner_id >= GAME_START_PLAYER_COUNT ||
        !staff_upgrade_task_matches(session, location,
            (uint8_t)location->owner_id, island_index, location_index) ||
        location->resource_stock[GAME_RESOURCE_BUILD_TONE] <= 19U ||
        !staff_upgrade_eligible(session, (uint8_t)location->owner_id,
                                island_index, location) ||
        !game_session_source_value_34_max(catalog, location, &old_maximum))
        return 0;

    next_tier = (int16_t)(location->source_capacity_4a + 1);
    location->source_capacity_4a = next_tier;
    if (!game_session_source_value_34_max(catalog, location, &new_maximum)) {
        --location->source_capacity_4a;
        return 0;
    }
    if (location->source_value_34 >= 0) {
        int32_t durability = (int32_t)location->source_value_34 +
            ((int32_t)new_maximum - old_maximum);
        if (durability > INT16_MAX) durability = INT16_MAX;
        if (durability < INT16_MIN) durability = INT16_MIN;
        location->source_value_34 = (int16_t)durability;
    }
    location->source_flags |= 0x020U;
    location->source_value_48 = 0;
    location->resource_stock[GAME_RESOURCE_BUILD_TONE] = 0;
    expected = session->pending_events[(uint8_t)task_slot];
    (void)game_session_dispatch_task_command(session, (uint8_t)task_slot,
                                             12, &expected);
    location->upgrade_task_handle = -1;
    return 1;
}

int game_session_queue_glyph_action(GameSession *session,
                                    uint8_t player_slot,
                                    uint8_t island_index,
                                    uint16_t location_index,
                                    uint8_t glyph_index)
{
    GameGlyphActionRequest *request;
    const GameRuntimeIsland *island;

    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT ||
        island_index >= session->island_count || glyph_index >= GAME_GLYPH_COUNT ||
        (session->economy[player_slot].glyph_mask &
            (uint16_t)(1U << glyph_index)) == 0 ||
        session->glyph_action_count >= GAME_SESSION_MAX_GLYPH_ACTIONS) {
        return -1;
    }
    island = &session->islands[island_index];
    if (location_index >= island->location_count) return -1;

    /* FUN_0042fa0f's packet fields are category 3, player, type 3, clicked
       island/location, and DAT_0049e9c0 (the selected glyph). Keep only the
       payload here; the current model has no active record matching
       FUN_0046562b(player, 8): +0 == player and +4 == 8. */
    request = &session->glyph_actions[session->glyph_action_count++];
    request->player_slot = player_slot;
    request->island_index = island_index;
    request->location_index = location_index;
    request->glyph_index = glyph_index;
    return 1;
}

int game_session_pop_glyph_action(GameSession *session,
                                  GameGlyphActionRequest *out)
{
    if (session == NULL || out == NULL || session->glyph_action_count == 0) {
        return 0;
    }
    *out = session->glyph_actions[0];
    --session->glyph_action_count;
    if (session->glyph_action_count != 0) {
        memmove(&session->glyph_actions[0], &session->glyph_actions[1],
                (size_t)session->glyph_action_count * sizeof(session->glyph_actions[0]));
    }
    memset(&session->glyph_actions[session->glyph_action_count], 0,
           sizeof(session->glyph_actions[session->glyph_action_count]));
    return 1;
}

unsigned int game_session_dispatch_glyph_actions(GameSession *session)
{
    GameGlyphActionRequest request;
    unsigned int dispatched = 0;

    if (session == NULL) return 0;
    while (game_session_pop_glyph_action(session, &request)) {
        unsigned int floater_index;

        if (request.player_slot >= GAME_START_PLAYER_COUNT ||
            request.island_index >= session->island_count ||
            request.location_index >=
                session->islands[request.island_index].location_count ||
            request.glyph_index >= GAME_GLYPH_COUNT ||
            (session->economy[request.player_slot].glyph_mask &
                (uint16_t)(1U << request.glyph_index)) == 0) {
            continue;
        }

        /* FUN_0046562b(player, 8) builds the matching floater list in table
           order; the dispatcher assigns the order to its first entry. */
        for (floater_index = 0; floater_index < session->floater_count;
             ++floater_index) {
            GameFloaterStart *floater = &session->floaters[floater_index];
            int16_t old_task_slot;
            int release_old_task;
            GamePendingEvent expected;

            if (!game_session_floater_is_active(floater) ||
                floater->owner_slot != request.player_slot ||
                floater->source_subtype != 8) continue;

            /* FUN_00465793 calls FUN_00421ec1(-1) before replacing this
               order. Besides dropping the linked claim, that reset cancels
               an old resource task for carried inventory items. */
            old_task_slot = floater->linked_task_slot;
            release_old_task = floater->carried_resource_code > 4 &&
                floater->carried_resource_code < 0x22 && old_task_slot >= 0 &&
                old_task_slot < GAME_SESSION_MAX_PENDING_EVENTS &&
                (floater->active_order_action == 4 ||
                 floater->active_order_action == 0x0d);
            if (release_old_task != 0)
                expected = session->pending_events[(uint8_t)old_task_slot];
            release_task_claim(session, floater);
            floater->active_order_action = 0;
            floater->order_target_floater = -1;
            floater->order_target_location = -1;
            floater->order_target_island = UINT8_MAX;
            floater->source_order_state_2c = 0;
            floater->source_order_coordinate_30 = 0;
            floater->source_order_pending = 0;
            floater->source_runtime_flags &= ~0x065U;
            floater->has_move_order = 0;
            if (release_old_task != 0 && expected.active != 0)
                (void)game_session_dispatch_task_command(session,
                    (uint8_t)old_task_slot, 12, &expected);

            floater->active_order_action = 0x13;
            floater->order_target_island = request.island_index;
            floater->order_target_location = (int16_t)request.location_index;
            floater->order_target_floater = -1;
            floater->cast_spell_kind = 0x16;
            floater->movement_state = 0x13;
            floater->order_progress = UINT8_MAX;
            floater->order_timer = 0;
            floater->source_runtime_flags &= ~0x200U;
            floater->has_move_order = 0;
            floater->has_wander_order = 0;
            floater->wander_timer = 0;
            session->economy[request.player_slot].selected_glyph_index =
                request.glyph_index;
            ++dispatched;
            break;
        }
    }
    return dispatched;
}

int game_session_cast_kind_for_action(uint8_t owner, uint8_t action_subtype)
{
    static const uint8_t cast_kinds[4][8] = {
        {4, 7, 9, 10, 11, 12, 14, 20},
        {0, 1, 8, 15, 13, 14, 18, 21},
        {1, 4, 5, 17, 12, 16, 20, 19},
        {0, 2, 3, 6, 11, 13, 16, 21}
    };
    if (owner >= 4 || action_subtype < 0x15 || action_subtype > 0x1c)
        return -1;
    return cast_kinds[owner][action_subtype - 0x15];
}

/* spells.txt is in native kind order (MagCost and CryCost). FUN_0045da80
   debits these after it has found a caster; kind 22 is the separate glyph
   path and has no spell record in the corpus. */
static const uint8_t cast_magic_costs[22] = {
    9, 16, 12, 9, 10, 12, 14, 11, 9, 11, 7,
    33, 28, 34, 36, 22, 27, 35, 39, 43, 59, 46
};

static const uint8_t cast_crystal_costs[22] = {
    7, 11, 9, 12, 9, 7, 10, 17, 14, 13, 13,
    13, 17, 12, 17, 19, 17, 12, 18, 18, 33, 22
};

/* spells.txt row `kind`: the MagCost and CryCost shown by the IWLocInfo bars
   (FUN_00440567 reads 0x6188e2/0x6188e4 + s*0x2c). */
int game_session_cast_kind_costs(int kind, uint16_t *magic_cost,
                                 uint16_t *crystal_cost)
{
    if (kind < 0 || kind >= 22 || magic_cost == NULL ||
        crystal_cost == NULL) return 0;
    *magic_cost = cast_magic_costs[kind];
    *crystal_cost = cast_crystal_costs[kind];
    return 1;
}

int game_session_queue_cast_action(GameSession *session,
                                   uint8_t player_slot,
                                   uint8_t island_index,
                                   uint16_t location_index,
                                   uint8_t action_subtype)
{
    return game_session_queue_cast_action_target(session, player_slot,
        island_index, location_index, action_subtype, -1);
}

int game_session_queue_cast_action_target(GameSession *session,
                                          uint8_t player_slot,
                                          uint8_t island_index,
                                          uint16_t location_index,
                                          uint8_t action_subtype,
                                          int16_t target_floater_index)
{
    GameCastActionRequest *request;
    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT ||
        island_index >= session->island_count ||
        location_index >= session->islands[island_index].location_count ||
        action_subtype < 0x15 || action_subtype > 0x1c ||
        session->cast_action_count >= GAME_SESSION_MAX_CAST_ACTIONS) return 0;
    {
        const GameRuntimeLocation *building =
            &session->islands[island_index].locations[location_index];
        if (building->owner_id != player_slot ||
            building->source_location_slot_18 < 0 ||
            (game_session_base_item_id(building) != 0x2f &&
             game_session_base_item_id(building) != 0x30)) return 0;
    }

    request = &session->cast_actions[session->cast_action_count++];
    request->player_slot = player_slot;
    request->action_subtype = action_subtype;
    request->island_index = island_index;
    request->location_index = location_index;
    request->target_floater_index = target_floater_index;
    return 1;
}

unsigned int game_session_dispatch_cast_actions(GameSession *session)
{
    unsigned int dispatched = 0;
    unsigned int request_index;
    if (session == NULL) return 0;

    for (request_index = 0; request_index < session->cast_action_count;
         ++request_index) {
        const GameCastActionRequest request = session->cast_actions[request_index];
        GameRuntimeIsland *building_island;
        GameRuntimeLocation *building;
        GameRuntimeLocation *hall;
        GameFloaterStart *caster = NULL;
        uint8_t kind;
        uint32_t magic_cost;
        uint32_t crystal_cost;
        unsigned int slot;
        if (request.player_slot >= GAME_START_PLAYER_COUNT ||
            request.island_index >= session->island_count ||
            request.location_index >=
                session->islands[request.island_index].location_count)
            continue;

        building_island = &session->islands[request.island_index];
        building = &building_island->locations[request.location_index];
        if (building->owner_id != request.player_slot ||
            building->source_value_14 < 0 || building->source_value_14 >= 4)
            continue;
        kind = (uint8_t)game_session_cast_kind_for_action(
            (uint8_t)building->source_value_14, request.action_subtype);
        /* Kinds 0..0x16 now have reconstructed FA_Cast tick and impact
           effects, except kind 0x0a requests its target floater from the UI. */
        if (kind > 0x15) continue;
        if (kind == 0x0a &&
            (request.target_floater_index < 0 ||
             (unsigned int)request.target_floater_index >= session->floater_count ||
             !game_session_floater_is_active(
                 &session->floaters[(unsigned int)request.target_floater_index]) ||
             session->floaters[(unsigned int)request.target_floater_index]
                 .owner_slot != 4U)) continue;

        magic_cost = cast_magic_costs[kind];
        crystal_cost = cast_crystal_costs[kind];
        /* FUN_0045d9c1 applies the glyph-8 discount to magic only. */
        if ((session->economy[request.player_slot].glyph_mask & 0x0100U) != 0)
            magic_cost = (magic_cost * 2U) / 3U;

        /* FUN_0045d8f4 scans the building's eight floater links in order and
           skips a unit already executing FA_Cast. The source level thresholds
           are held in an unresolved table; the image values are zero. */
        for (slot = 0; slot < 8; ++slot) {
            int16_t linked = building->charge_floater_slots[slot];
            GameFloaterStart *floater;
            if (linked < 0 || (unsigned int)linked >= session->floater_count)
                continue;
            floater = &session->floaters[(unsigned int)linked];
            if (!game_session_floater_is_active(floater) ||
                floater->owner_slot != request.player_slot ||
                floater->active_order_action == 0x13) continue;
            /* FUN_0045d8f4 tests DAT_006188e0[kind] <= worker level L (low
               nibble of +0xa). The table is spells.txt Level - 1 (REA, loader
               FUN_00463563): 0 for kinds 0..10, 1 for 11..17, 2 for 18..21.
               Class 1 casting kind 15 and class 2 casting kind 17 skip it. */
            if (!((floater->type_index == 1U && kind == 15U) ||
                  (floater->type_index == 2U && kind == 17U)) &&
                (kind >= 18U ? 2U : kind >= 11U ? 1U : 0U) >
                    (floater->attack_level_flags & 0x0fU)) continue;
            caster = floater;
            break;
        }
        if (caster == NULL) continue;

        /* Native validation and caster selection precede both stock debits.
           Check together so a failed request cannot spend only one resource. */
        hall = game_session_player_hall(session, request.player_slot);
        if (hall == NULL ||
            hall->resource_stock[GAME_RESOURCE_MAGIC_TONE] < magic_cost ||
            hall->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] < crystal_cost)
            continue;
        hall->resource_stock[GAME_RESOURCE_MAGIC_TONE] =
            (uint16_t)(hall->resource_stock[GAME_RESOURCE_MAGIC_TONE] - magic_cost);
        hall->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] =
            (uint16_t)(hall->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] - crystal_cost);

        caster->active_order_action = 0x13;
        caster->movement_state = 0x13;
        caster->cast_spell_kind = kind;
        /* FUN_0042fa0f repeats the selected site's island/location in
           packet words +0x0e/+0x10 for FUN_0045da80. */
        caster->order_target_island = request.island_index;
        caster->order_target_location = (int16_t)request.location_index;
        caster->order_target_floater = kind == 0x0a
            ? request.target_floater_index : -1;
        caster->order_progress = UINT8_MAX;
        caster->order_timer = 0;
        caster->source_runtime_flags &= ~0x200U;
        caster->has_move_order = 0;
        caster->has_wander_order = 0;
        caster->wander_timer = 0;
        ++dispatched;
    }
    memset(session->cast_actions, 0, sizeof(session->cast_actions));
    session->cast_action_count = 0;
    return dispatched;
}
