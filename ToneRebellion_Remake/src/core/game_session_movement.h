#ifndef TONE_REBELLION_GAME_SESSION_MOVEMENT_INCLUDED
#define TONE_REBELLION_GAME_SESSION_MOVEMENT_INCLUDED

#include "game_session_types.h"

/* Advance the per-location animation fields updated by FUN_00450a71. */
void game_session_tick_item_animations(GameSession *session,
                                       const struct BuildingRenderCatalog *catalog);
/* Advance idle FA_Wander routes and simulation-assigned destinations through
   the FUN_00422d27 step kernel. Player input must not call this as an order. */
void game_session_tick_floater_moves(GameSession *session, uint32_t source_tick);
/* Resolve state 6/7 attack timing and damage for one floater. */
void game_session_tick_floater_combat(GameSession *session,
                                      unsigned int floater_index);
/* Advance the source effect manager before per-floater state updates. */
void game_session_tick_combat_effects(GameSession *session,
                                     uint32_t source_tick);
/* FUN_0042fa0f's map-ground mode 0x13 enters FUN_0045d8b2 with runtime state
   9 and a coordinate packed by FUN_0041e3eb (rounded to 10-pixel units).
   The remake exposes it only for non-worker floaters, matching the user's
   source-control constraint. Returns nonzero when the order is accepted. */
int game_session_order_floater_to_coordinate(GameSession *session,
                                             uint8_t player_slot,
                                             uint8_t island_index,
                                             unsigned int floater_index,
                                             uint16_t x,
                                             uint16_t y);

#endif
