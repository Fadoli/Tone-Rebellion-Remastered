#ifndef TONE_REBELLION_GAME_SESSION_ACTION9_H
#define TONE_REBELLION_GAME_SESSION_ACTION9_H

#include "game_session.h"

int32_t game_session_source_chebyshev_distance(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
void game_session_set_approach_point(GameFloaterStart *floater, int32_t target_x, int32_t target_y);
void game_session_advance_action9(GameSession *session, unsigned int floater_index);
void game_session_advance_merge_order(GameSession *session,
                                     unsigned int floater_index);
void game_session_advance_defend_order(GameSession *session,
                                       unsigned int floater_index);

#endif
