#ifndef TONE_REBELLION_GAME_SESSION_ACTION9_H
#define TONE_REBELLION_GAME_SESSION_ACTION9_H

#include "game_session.h"

int32_t game_session_source_chebyshev_distance(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
void game_session_set_approach_point(GameFloaterStart *floater, int32_t target_x, int32_t target_y);
uint16_t game_session_floater_approach_radius(
    const GameSession *session, const GameFloaterStart *floater);
int game_session_pick_inverse_distance(GameSession *session,
                                       const int32_t *distances,
                                       unsigned int count);
void game_session_advance_action9(GameSession *session, unsigned int floater_index);
void game_session_advance_merge_order(GameSession *session,
                                     unsigned int floater_index);
void game_session_advance_defend_order(GameSession *session,
                                       unsigned int floater_index);
/* Remake interpretation of PANIC: bit 0 of source_event_state sends the
   player's workers on that island against the nearest Leviathan unit. */
int game_session_panic_active(const GameSession *session, uint8_t player_slot,
                              uint8_t island_index);
void game_session_apply_panic_orders(GameSession *session);
/* FUN_0042219e's autonomous category-4 floater target selection. */
int game_session_assign_category4_autonomous_order(
    GameSession *session, unsigned int floater_index);
void game_session_advance_category4_autonomous_order(
    GameSession *session, unsigned int floater_index);
int game_session_assign_category4_subtype9_order(
    GameSession *session, unsigned int floater_index, uint32_t source_tick);

/* FUN_0042219e copy of a building's genre 6/7/8 order (FUN_0045d867 /
   FUN_0045d8b2) into a linked floater: 6 attacks a floater, 7 a location,
   8 defends a floater. `target` is the floater or location index. */
void game_session_adopt_building_attack_order(GameSession *session,
                                              unsigned int floater_index,
                                              unsigned int genre,
                                              unsigned int target);

#endif
