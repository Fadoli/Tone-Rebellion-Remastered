#include "game_session.h"
#include "pad_catalog.h"

#include <string.h>

/* Deferred world actions, inventory commands, task slots and toggles. */
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

int game_session_queue_onoff_action(GameSession *session,
                                    uint8_t player_slot,
                                    uint8_t island_index,
                                    uint16_t location_index)
{
    GameOnOffActionRequest *request;
    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT ||
        island_index >= session->island_count ||
        location_index >= session->islands[island_index].location_count ||
        session->onoff_action_count >= GAME_SESSION_MAX_ONOFF_ACTIONS) {
        return 0;
    }
    request = &session->onoff_actions[session->onoff_action_count++];
    request->player_slot = player_slot;
    request->island_index = island_index;
    request->location_index = location_index;
    return 1;
}

int game_session_pop_onoff_action(GameSession *session,
                                  GameOnOffActionRequest *out)
{
    if (session == NULL || out == NULL || session->onoff_action_count == 0) {
        return 0;
    }
    *out = session->onoff_actions[0];
    --session->onoff_action_count;
    if (session->onoff_action_count != 0) {
        memmove(&session->onoff_actions[0], &session->onoff_actions[1],
                (size_t)session->onoff_action_count * sizeof(session->onoff_actions[0]));
    }
    memset(&session->onoff_actions[session->onoff_action_count], 0,
           sizeof(session->onoff_actions[session->onoff_action_count]));
    return 1;
}

static int game_session_recalculate_location_active(GameRuntimeLocation *location)
{
    uint32_t previous_flags;
    uint32_t current_flags;
    int can_be_active;

    if (location->renderer_class == 2 || location->renderer_class == 3) return 0;
    previous_flags = location->source_flags;
    current_flags = previous_flags & ~1U;
    can_be_active = (previous_flags & 0x90U) == 0 &&
        ((previous_flags & 0x400U) != 0 ||
         location->source_location_slot_18 != -1 ||
         location->renderer_class == 1) &&
        ((previous_flags & 0x100U) == 0 || location->source_value_44 < 20) &&
        location->source_value_58 == 0 && location->record_value_10 >= 2;

    if (can_be_active) {
        if (location->owner_id == 4 ||
            (location->owner_id >= 0 &&
             location->owner_id < GAME_START_PLAYER_COUNT &&
             (location->tribe_visibility_mask &
              (uint8_t)(1U << (unsigned int)location->owner_id)) != 0)) {
            current_flags |= 1U;
        }
    }
    location->source_flags = current_flags;
    return ((previous_flags ^ current_flags) & 1U) != 0;
}

unsigned int game_session_dispatch_onoff_actions(GameSession *session,
                                                 const PadCatalog *catalog)
{
    GameOnOffActionRequest request;
    unsigned int changed = 0;

    if (session == NULL || catalog == NULL) return 0;
    while (game_session_pop_onoff_action(session, &request)) {
        GameRuntimeLocation *location;
        const PadCatalogItem *item;
        int base_item_id;
        int was_enabled;
        int active_flag_changed;
        unsigned int subtype;

        if (request.player_slot >= GAME_START_PLAYER_COUNT ||
            request.island_index >= session->island_count ||
            request.location_index >=
                session->islands[request.island_index].location_count) {
            continue;
        }
        location = &session->islands[request.island_index]
                        .locations[request.location_index];
        base_item_id = location->record_value_10 -
                       (int)request.player_slot * 16;
        if (location->renderer_class != 0 ||
            location->owner_id != request.player_slot ||
            base_item_id < 0x25 || base_item_id > 0x27) {
            continue;
        }

        was_enabled = (location->source_flags & 0x400U) != 0;
        if ((location->source_flags & 0x400U) != 0) {
            location->source_flags &= ~0x400U;
        } else {
            item = location->record_value_10 >= 0 &&
                   location->record_value_10 <= (int32_t)UINT16_MAX
                ? pad_catalog_find(catalog, (uint16_t)location->record_value_10)
                : NULL;
            if (item != NULL && item->maintenance_tone_cost <=
                    session->economy[request.player_slot].source_maintenance_budget) {
                location->source_flags |= 0x400U;
            }
        }

        /* FUN_00450385 resolves the linked row; FUN_0045cbaa releases its
           subtype 1..3 task links only after the site has ended up OFF. */
        if (location->source_location_slot_18 != -1 &&
            (location->source_flags & 0x400U) == 0) {
            for (subtype = 0; subtype < GAME_RESOURCE_TYPE_COUNT; ++subtype) {
                int16_t linked_slot = location->source_task_slot[subtype];
                if (linked_slot >= 0 &&
                    linked_slot < GAME_SESSION_MAX_PENDING_EVENTS) {
                    (void)game_session_pending_event_release(
                        session, (uint8_t)linked_slot);
                }
                location->source_task_slot[subtype] = -1;
            }
        }
        active_flag_changed = game_session_recalculate_location_active(location);
        if (was_enabled != ((location->source_flags & 0x400U) != 0) ||
            active_flag_changed) ++changed;
    }
    return changed;
}

int game_session_queue_build_selection(GameSession *session,
                                      uint8_t player_slot,
                                      uint8_t island_index,
                                      uint16_t location_index,
                                      uint16_t item_id)
{
    GameBuildSelectionRequest *request;
    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT ||
        island_index >= session->island_count ||
        location_index >= session->islands[island_index].location_count ||
        session->build_selection_count >= GAME_SESSION_MAX_BUILD_SELECTIONS) {
        return 0;
    }
    request = &session->build_selections[session->build_selection_count++];
    request->category = 0;
    request->player_slot = player_slot;
    request->action_type = 5;
    request->island_index_a = island_index;
    request->reserved_zero = 0;
    request->island_index_b = island_index;
    request->location_index = location_index;
    request->item_id = item_id;
    return 1;
}

int game_session_pop_build_selection(GameSession *session,
                                     GameBuildSelectionRequest *out)
{
    if (session == NULL || out == NULL || session->build_selection_count == 0) {
        return 0;
    }
    *out = session->build_selections[0];
    --session->build_selection_count;
    if (session->build_selection_count != 0) {
        memmove(&session->build_selections[0], &session->build_selections[1],
                (size_t)session->build_selection_count *
                sizeof(session->build_selections[0]));
    }
    memset(&session->build_selections[session->build_selection_count], 0,
           sizeof(session->build_selections[0]));
    return 1;
}

unsigned int game_session_dispatch_build_selections(GameSession *session)
{
    GameBuildSelectionRequest request;
    unsigned int added = 0;

    if (session == NULL) return 0;
    while (game_session_pop_build_selection(session, &request)) {
        int slot;
        if (request.category != 0 || request.action_type != 5) continue;

        /* FUN_004662b7 copies packet byte offsets +2/+4/+8/+10/+12/+14
           into the task record, sets priority 1, and deduplicates type 5
           records by payload_0c, payload_0e, and payload_12. */
        slot = game_session_pending_event_add(
            session, (int16_t)request.player_slot,
            (int16_t)request.island_index_b,
            (int16_t)request.action_type,
            (int16_t)request.reserved_zero,
            (int16_t)request.location_index,
            (int16_t)request.item_id);
        if (slot >= 0) ++added;
    }
    return added;
}

int game_session_queue_island_event3_subtype0(GameSession *session,
                                              uint8_t player_slot,
                                              uint8_t island_index)
{
    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT ||
        island_index >= session->island_count) return 0;
    session->islands[island_index].source_event3_pending_parity[player_slot] ^= 1U;
    return 1;
}

void game_session_dispatch_island_events(GameSession *session)
{
    unsigned int island_index;
    if (session == NULL) return;
    for (island_index = 0; island_index < session->island_count; ++island_index) {
        GameRuntimeIsland *island = &session->islands[island_index];
        unsigned int player_slot;
        for (player_slot = 0; player_slot < GAME_START_PLAYER_COUNT; ++player_slot) {
            if (island->source_event3_pending_parity[player_slot] != 0) {
                island->source_event_state[player_slot] ^= 1U;
                island->source_event3_pending_parity[player_slot] = 0;
            }
        }
    }
}
