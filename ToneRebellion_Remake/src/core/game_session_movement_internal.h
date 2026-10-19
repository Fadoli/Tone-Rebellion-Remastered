#ifndef TONE_REBELLION_GAME_SESSION_MOVEMENT_INTERNAL_H
#define TONE_REBELLION_GAME_SESSION_MOVEMENT_INTERNAL_H

#include "game_session_types.h"

#include <stdint.h>

int game_session_tick_floater_wander(GameSession *session,
                                    GameFloaterStart *floater,
                                    uint32_t source_tick);
int game_session_begin_floater_handoff(GameSession *session,
                                       GameFloaterStart *floater,
                                       uint8_t target_island);
int game_session_tick_floater_handoff(GameSession *session,
                                      GameFloaterStart *floater);

#endif
