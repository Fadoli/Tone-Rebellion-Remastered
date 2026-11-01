#ifndef TONE_REBELLION_GAME_SESSION_COMBAT_INTERNAL_H
#define TONE_REBELLION_GAME_SESSION_COMBAT_INTERNAL_H

#include "game_session_types.h"

#include <stdint.h>

int32_t game_session_damage_floater(GameSession *session,
                                    unsigned int attacker_index,
                                    unsigned int target_index);
void game_session_apply_floater_damage(GameSession *session,
                                       GameFloaterStart *floater,
                                       int32_t amount,
                                       int32_t killer_faction);
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
/* FUN_00452ae7: queues world event 8 for the site, then clears it. */
void game_session_destroy_site(GameSession *session, uint8_t island_index,
                               uint16_t location_index,
                               GameRuntimeLocation *target);

/* attacker_index >= 0 defers the hit to the visual's arrival; -1 keeps the
   visual cosmetic with `damage` as its impact level source. */
int game_session_spawn_attack_visual(GameSession *session,
                                     const GameFloaterStart *attacker,
                                     int attacker_index, uint8_t state,
                                     uint16_t target_x, uint16_t target_y,
                                     int32_t damage);
int game_session_spawn_effect_visual(GameSession *session, int def_index,
                                     uint8_t island_index, uint16_t x,
                                     uint16_t y);
/* Tower effect slot whose arrival hit uses the tower's attack power. */
int game_session_spawn_defense_effect(GameSession *session, int def_index,
                                      uint8_t island_index, uint16_t x,
                                      uint16_t y, unsigned int target_index,
                                      int32_t attack_power,
                                      uint8_t impact_realm);
/* Strike-time or arrival-time hit of FUN_004200d2 / FUN_00420188 with the
   targets named explicitly; returns the damage dealt. */
int32_t game_session_resolve_attack_hit(GameSession *session,
                                        unsigned int floater_index,
                                        uint8_t state, int target_floater,
                                        int target_location);

void game_session_start_attack_effect(GameSession *session,
                                     GameFloaterStart *attacker,
                                     int32_t damage,
                                     uint16_t target_x, uint16_t target_y);

#endif
