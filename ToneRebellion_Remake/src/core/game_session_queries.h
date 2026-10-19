#ifndef TONE_REBELLION_GAME_SESSION_QUERIES_INCLUDED
#define TONE_REBELLION_GAME_SESSION_QUERIES_INCLUDED

#include "game_session_types.h"

/* Hit test the visible island's active floaters in session order. The original
   FUN_00435581 uses Chebyshev distance < 0x14 (20) for floater selection. */
int game_session_floater_at(const GameSession *session,
                            uint8_t island_index,
                            uint16_t x,
                            uint16_t y);
/* Counts modeled floaters by remake owner_slot. The source Hall metric uses
   the floater type/subtype pair instead; see game_session_workstr_summary. */
unsigned int game_session_count_player_floaters(const GameSession *session,
                                                uint8_t player_slot);
/* FUN_00440567 displays WORKSTR from FUN_0046562b(category, 0) and
   FUN_0046562b(category, -1). `count` is subtype 0 and `total` is all modeled
   subtypes; percentage is meaningful only when total is nonzero. */
int game_session_workstr_summary(const GameSession *session,
                                 uint8_t type_index,
                                 unsigned int *count,
                                 unsigned int *total,
                                 unsigned int *percentage);
/* FUN_0041ff2e masks the source level word with 0x000f; IWLocInfo displays
   that value plus one. Returns 0 for a null record. */
uint8_t game_session_location_display_level(const GameRuntimeLocation *location);

#endif
