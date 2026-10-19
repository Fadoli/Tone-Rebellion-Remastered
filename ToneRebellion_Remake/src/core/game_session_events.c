#include "game_session.h"
#include "pad_catalog.h"

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
            if (!game_session_floater_is_active(floater) ||
                (floater->source_runtime_flags & 0x008U) != 0 ||
                floater->owner_slot != request.player_slot ||
                floater->source_subtype != 8) continue;

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
