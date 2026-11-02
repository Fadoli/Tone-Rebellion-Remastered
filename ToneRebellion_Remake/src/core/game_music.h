#ifndef TONE_REBELLION_GAME_MUSIC_H
#define TONE_REBELLION_GAME_MUSIC_H

#include "tone_rng.h"

#include <stddef.h>
#include <stdint.h>

enum { GAME_MUSIC_REALM_COUNT = 15 };

typedef struct GameMusicState {
    uint16_t pending_realms;
    int8_t last_random_track;
} GameMusicState;

/* FUN_004702d9 marks all 15 realm IDs for a first-entry music transition. */
void game_music_state_init(GameMusicState *state);

/* Consume the original first-entry transition flag. Returns 1 when a realm
   was pending; an ordinary realm can leave out_tune_id empty when the source
   LCG gate elects not to change tracks. */
int game_music_enter_realm(GameMusicState *state, uint8_t realm_id,
                           uint8_t player_tribe, ToneRng *random_state,
                           char *out_tune_id, size_t out_capacity);

/* FUN_004334ce world event 0xc (island reached, FUN_00466b09): the
   argument is the island's WORLDPOS shape. Below 4 it names act<arg + 1>,
   0xe names levi; otherwise bit 0 of one LCG value decides whether
   FUN_0046ff6f(0) picks a random track. Returns 1 when out_tune_id names a
   track (ev_73dc398c). */
int game_music_island_reached(GameMusicState *state, int32_t shape_id,
                              uint8_t player_tribe, ToneRng *random_state,
                              char *out_tune_id, size_t out_capacity);

#endif
