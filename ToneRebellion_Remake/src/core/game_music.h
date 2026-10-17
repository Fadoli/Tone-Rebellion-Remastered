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

/* Select the original tune on the first entry into a realm. Returns 1 and
   writes a sound.txt tune ID when a transition is pending, otherwise 0. */
int game_music_enter_realm(GameMusicState *state, uint8_t realm_id,
                           uint8_t player_tribe, ToneRng *random_state,
                           char *out_tune_id, size_t out_capacity);

#endif
