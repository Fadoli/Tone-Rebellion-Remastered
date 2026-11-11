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
/* Remake-only leg carrying an Obtain artifact to an owned Hall/recruiter,
   crossing to the Hall island when the current island has none. */
int game_session_start_artifact_delivery(GameSession *session,
                                         GameFloaterStart *floater);
void game_session_drop_carried_artifact(GameSession *session,
                                        GameFloaterStart *floater);
/* FUN_004211bb action 0xc on +0x40 == +0x0e: state 12 at the building
   (+0x42). Returns 0 when the building is gone. */
int game_session_plan_linked_level_up(GameSession *session,
                                      GameFloaterStart *floater);
int game_session_plan_defend_waypoint(GameSession *session,
                                      GameFloaterStart *floater);
int game_session_defend_area_has_target(GameSession *session,
                                        unsigned int floater_index);

#endif
