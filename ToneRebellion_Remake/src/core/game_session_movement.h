#ifndef TONE_REBELLION_GAME_SESSION_MOVEMENT_INCLUDED
#define TONE_REBELLION_GAME_SESSION_MOVEMENT_INCLUDED

#include "game_session_types.h"

/* Advance the per-location animation fields updated by FUN_00450a71. */
void game_session_tick_item_animations(GameSession *session,
                                       const struct BuildingRenderCatalog *catalog);
/* UI entry point with the source stats needed by completed floater training. */
void game_session_tick_item_animations_with_floaters(
    GameSession *session, const struct BuildingRenderCatalog *catalog,
    const FloaterCatalog *floater_catalog, const PadCatalog *pad_catalog);
/* Advance idle FA_Wander routes and simulation-assigned destinations through
   the FUN_00422d27 step kernel. Player input must not call this as an order. */
void game_session_tick_floater_moves(GameSession *session, uint32_t source_tick,
                                     const PadCatalog *catalog);
/* Port of the state-11/12 CHARGE link operation for a floater at a source. */
int game_session_link_floater_charge(GameSession *session,
                                     unsigned int floater_index,
                                     uint16_t source_location_index);
/* Port of the state-12 CHARGE debit on an already linked source. */
int game_session_refill_floater_charge(GameSession *session,
                                       unsigned int floater_index);
/* Remove the floater's slot and invalidate its local source proxy. */
int game_session_unlink_floater_charge(GameSession *session,
                                       unsigned int floater_index);
/* Resolve state 6/7 attack timing and damage for one floater. */
void game_session_tick_floater_combat(GameSession *session,
                                      unsigned int floater_index);
/* Advance the source effect manager before per-floater state updates. */
void game_session_tick_combat_effects(GameSession *session,
                                     uint32_t source_tick);
/* Orders a player-controlled worker to a map coordinate. A local destination
   enters state 9 directly; a remote destination walks to a bridge, transfers
   to the target island, then resumes the coordinate order. Coordinates use
   the source's rounded 10-pixel packing. Returns nonzero when accepted. */
int game_session_order_floater_to_coordinate(GameSession *session,
                                             uint8_t player_slot,
                                             uint8_t island_index,
                                             unsigned int floater_index,
                                             uint16_t x,
                                             uint16_t y);
/* Schedule the source FA_MergeWith (0x14) follow-up for a local target. */
int game_session_order_floater_to_merge(GameSession *session,
                                        uint8_t player_slot,
                                        uint8_t island_index,
                                        unsigned int floater_index,
                                        unsigned int target_floater_index);
/* Assign FA_DefendFlt (8), which guards a local floater and nearby candidates. */
int game_session_order_floater_to_defend(GameSession *session,
                                         uint8_t player_slot,
                                         uint8_t island_index,
                                         unsigned int floater_index,
                                         unsigned int target_floater_index);
/* Order an unlinked local floater to a player-owned charge source (state 11).
   Repeating the order on that same site requests a state-12 debit. */
int game_session_order_floater_to_charge_site(GameSession *session,
                                              uint8_t player_slot,
                                              uint8_t island_index,
                                              unsigned int floater_index,
                                              uint16_t location_index);
/* Order an owned floater to pick up a visible PIT_Object on its island.
   The runtime consumer is observed; the native player-order producer remains
   unresolved, so this is a remake-side interaction inferred from that state. */
int game_session_order_floater_to_ground_object(GameSession *session,
                                                uint8_t player_slot,
                                                uint8_t island_index,
                                                unsigned int floater_index,
                                                uint16_t location_index);

#endif
