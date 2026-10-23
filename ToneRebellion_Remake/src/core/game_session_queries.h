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

/* FUN_0045f849's end-game score for one player. Observation: the native inputs
   are the island count, owned glyphs, tribe floater total, FUN_004204bc's loss
   and per-subtype kill counters, and DAT_004bf11c (level L), which has no
   writer in the binary (the port keeps 0). */
typedef struct GameEndGameScore {
    uint16_t visited_islands;
    uint16_t glyphs;
    uint16_t tribe_floaters;
    uint16_t losses;
    uint16_t shadow_total;      /* sum of the four weighted kill pairs */
    uint16_t shadow_card_total; /* FUN_0041a8df: leviathan subtypes 9..12 */
    int32_t points_visited;     /* p3 */
    int32_t points_level;       /* p4 */
    int32_t points_glyphs;      /* p5 */
    int32_t points_tribe;       /* p7 */
    int32_t points_losses;      /* p8, subtracted */
    int32_t points_kills[4];    /* p9..p12 */
    int32_t total;              /* p1, clamped at 0 */
    uint8_t grade;              /* p2, 0..9 */
} GameEndGameScore;
int game_session_end_game_score(const GameSession *session, uint8_t player_slot,
                                GameEndGameScore *score);

/* Clipboard (CLIPSEL1-3 / CLIPBD1-3). Selecting an owned, built 0x2c..0x32
   building remembers it in the first empty slot of the active group
   (FUN_00438120 via FUN_0042f755; no duplicates, silent when full). */
void game_session_clip_remember(GameSession *session, uint8_t player_slot,
                                uint8_t island_index, uint16_t location_index);
void game_session_clip_set_group(GameSession *session, unsigned int group);
/* Column 0..2 of the active group; drops stale slots (the building was lost
   or changed hands). Returns the dot count (source subslot + 1) or 0 if empty. */
unsigned int game_session_clip_slot(GameSession *session, uint8_t player_slot,
                                    unsigned int column, uint8_t *island_index,
                                    uint16_t *location_index);

#endif
