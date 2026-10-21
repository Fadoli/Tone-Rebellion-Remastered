#ifndef TONE_REBELLION_GAME_SESSION_COMBAT_INTERNAL_H
#define TONE_REBELLION_GAME_SESSION_COMBAT_INTERNAL_H

#include "game_session_types.h"

#include <stdint.h>

int32_t game_session_damage_floater(GameSession *session,
                                    unsigned int attacker_index,
                                    unsigned int target_index);
int32_t game_session_damage_floater_from_power(GameSession *session,
                                               unsigned int target_index,
                                               int32_t attack_power);
int32_t game_session_damage_site(GameSession *session,
                                 unsigned int attacker_index,
                                 uint8_t island_index,
                                 uint16_t location_index,
                                 GameRuntimeLocation *target);
int32_t game_session_damage_site_from_power(GameSession *session,
                                            uint8_t island_index,
                                            uint16_t location_index,
                                            int32_t attack_power);

void game_session_clear_cast_site(GameSession *session,
                                  uint8_t island_index,
                                  uint16_t location_index,
                                  GameRuntimeLocation *target);

void game_session_start_attack_effect(GameSession *session,
                                     GameFloaterStart *attacker,
                                     int32_t damage);

#endif
