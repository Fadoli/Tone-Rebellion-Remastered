#ifndef TONE_REBELLION_GAME_SESSION_ECONOMY_INCLUDED
#define TONE_REBELLION_GAME_SESSION_ECONOMY_INCLUDED

#include "game_session_types.h"

/* Return the player's Hall runtime location, or NULL when it is unavailable. */
GameRuntimeLocation *game_session_player_hall(GameSession *session,
                                              uint8_t player_slot);
/* Resource stock fields are attached to each player's initial Hall runtime
   record. Starting values, caps and mutation rules remain to be verified. */
int game_session_credit_resource(GameSession *session, uint8_t player_slot,
                                 GameResourceType type, uint32_t amount);
int game_session_debit_resource(GameSession *session, uint8_t player_slot,
                                 GameResourceType type, uint32_t amount);
/* FUN_00452eac: consume a matching output, Hall stock (1..3), or owner
   Inventory item (5..33), following the source branch order. */
int game_session_consume_location_resource(GameSession *session,
                                           uint8_t island_index,
                                           uint16_t location_index,
                                           int32_t resource_code);
/* FUN_00452c31: test pending output, Hall stock, or owner Inventory; the raw
   +0x18 eligibility guard is represented, but slot allocation is not. */
int game_session_location_resource_available(const GameSession *session,
                                             uint8_t island_index,
                                             uint16_t location_index,
                                             int32_t resource_code);
/* FUN_0045f2a1 reads this location's pad.txt movement tuple and multiplies
   each short by runtime +0x4a + 1. The order matches stocks +0x28/+0x2a/+0x2c.
   This calculates costs only; source eligibility remains a separate check. */
int game_session_location_move_costs(const GameSession *session,
                                     const PadCatalog *catalog,
                                     uint8_t island_index,
                                     uint16_t location_index,
                                     int32_t costs[GAME_RESOURCE_TYPE_COUNT]);
/* IWLocInfo action 6: begin holding an owned building after paying its move
   costs, then place it on a visible, free class-0 site. PIT_Object/item 1 is
   accepted only as a placement target. */
int game_session_begin_location_move(GameSession *session,
                                     const PadCatalog *catalog,
                                     uint8_t player_slot,
                                     uint8_t island_index,
                                     uint16_t location_index);
int game_session_finish_location_move(GameSession *session,
                                      uint8_t player_slot,
                                      uint8_t island_index,
                                      uint16_t location_index);
int game_session_cancel_location_move(GameSession *session,
                                      const PadCatalog *catalog);
/* FUN_0045f755: advance one Hall resource mode modulo three. Returns the new
   raw mode, or -1 for an invalid player/resource. */
int game_session_cycle_resource_stock_mode(GameSession *session,
                                           uint8_t player_slot,
                                           GameResourceType type);
/* FUN_0045eaa7: create/cancel deferred type-4 resource requests from each
   player's Hall modes, stocks, slot references, and raw Hall guards. */
unsigned int game_session_update_resource_requests(GameSession *session);
/* FUN_0043ec78: left/right cell clicks add/subtract 10 and clamp to 0..1000.
   target_column is the displayed column after omitting player_slot. */
int game_session_adjust_trade_offer(GameSession *session, uint8_t player_slot,
                                    uint8_t resource_row,
                                    uint8_t target_column, int direction);
/* FUN_0042fa0f messages 4010/4011 clear or enqueue nonzero per-target
   type-0xb requests and then clear the 3x3 offer table. Returns packet count,
   or -1 if invalid/full (offers remain intact on failure). */
int game_session_clear_trade_offers(GameSession *session, uint8_t player_slot);
int game_session_commit_trade_offers(GameSession *session, uint8_t player_slot);
int game_session_pop_trade_request(GameSession *session, GameTradeRequest *out);
/* FUN_00465793 subtype 0xb: apply each nonnegative amount up to the source
   Hall's signed-short stock, moving it to the target Hall. */
int game_session_apply_trade_request(GameSession *session,
                                     const GameTradeRequest *request);
/* Consume queued local type-0xb requests in order. A request whose source or
   target Hall is unavailable remains queued for a later tick. */
int game_session_dispatch_trade_requests(GameSession *session);
/* FUN_0043e4f0 / FUN_00465793: enqueue one subtype-10 toggle and update the
   corresponding local flag as if the queued event had been dispatched. */
int game_session_toggle_diplomacy(GameSession *session, uint8_t source_player,
                                  uint8_t target_player,
                                  GameDiplomacyAction action);
int game_session_pop_diplomacy_request(GameSession *session,
                                       GameDiplomacyRequest *out);
/* FUN_0043d59b reads counts for IDs 5..33; FUN_00425084 increments a count
   when a produced item cannot be placed, and FUN_00452eac decrements it when
   an inventory item is consumed. These helpers model those count changes. */
int game_session_inventory_credit(GameSession *session, uint8_t player_slot,
                                  uint8_t item_id, uint32_t amount);
int game_session_inventory_debit(GameSession *session, uint8_t player_slot,
                                  uint8_t item_id, uint32_t amount);
/* FUN_00465793 category-3/subtype-4: only attempt an item result when its
   inventory count is positive, and debit one after the receiver succeeds.
   `apply` models FUN_004503bd and must not modify inventory_count itself. */
int game_session_dispatch_inventory_result(
    GameSession *session, uint8_t player_slot, uint8_t item_id,
    GameInventoryResultApply apply, void *context);
/* Models the record reservation and duplicate rule in FUN_004662b7. Returns
   the reserved slot, or -1 when full/duplicate/invalid. Only action types 5
   and 13 are deduplicated by the source table. */
int game_session_pending_event_add(GameSession *session, int16_t player_id,
                                   int16_t payload_0a, int16_t action_type,
                                   int16_t payload_0c, int16_t payload_0e,
                                   int16_t payload_12);

#endif
