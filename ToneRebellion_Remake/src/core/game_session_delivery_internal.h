#ifndef TONE_REBELLION_GAME_SESSION_DELIVERY_INTERNAL_H
#define TONE_REBELLION_GAME_SESSION_DELIVERY_INTERNAL_H

#include "game_session_delivery.h"

int local_refill_source_is_valid(const GameSession *session, uint8_t island_index,
                                 uint16_t location_index, int16_t player_id,
                                 int16_t resource_code);
int local_refill_source(const GameSession *session, uint8_t island_index,
                        int16_t player_id, int16_t resource_code);
void floater_target_location(GameFloaterStart *floater,
                             const GameRuntimeLocation *location, uint8_t state);
void release_task_claim(GameSession *session, GameFloaterStart *floater);

#endif
