#include "game_music.h"

#include <stdio.h>

static void copy_tune(char *out_tune_id, size_t out_capacity,
                      const char *tune_id)
{
    size_t i;

    if (out_tune_id == NULL || out_capacity == 0) return;
    for (i = 0; i + 1 < out_capacity && tune_id[i] != '\0'; ++i) {
        out_tune_id[i] = tune_id[i];
    }
    out_tune_id[i] = '\0';
}

void game_music_state_init(GameMusicState *state)
{
    if (state == NULL) return;
    state->pending_realms = (uint16_t)((1U << GAME_MUSIC_REALM_COUNT) - 1U);
    state->last_random_track = -1;
}

static int choose_random_realm_tune(GameMusicState *state,
                                    uint8_t player_tribe,
                                    ToneRng *random_state,
                                    char *out_tune_id,
                                    size_t out_capacity)
{
    static const char *const fixed_tunes[6] = {
        "act1", "act2", "act3", "act4", "ambi1", "ambi2"
    };
    unsigned int choice;

    if (random_state == NULL) return 0;

    /* FUN_0046ff6f selects from nine 10-byte entries: the selected tribe
       twice, its corresponding act once, acts 1..4, then ambi1 and ambi2.
       It repeats the draw if it would reuse the previous random entry. */
    do {
        choice = tone_rng_next15(random_state) % 9U;
    } while ((int8_t)choice == state->last_random_track);
    state->last_random_track = (int8_t)choice;

    if (choice < 2U) {
        (void)snprintf(out_tune_id, out_capacity, "tribe%u",
                       (unsigned int)(player_tribe < 4 ? player_tribe : 3));
    } else if (choice == 2U) {
        (void)snprintf(out_tune_id, out_capacity, "act%u",
                       (unsigned int)(player_tribe + 1U));
    } else {
        copy_tune(out_tune_id, out_capacity, fixed_tunes[choice - 3U]);
    }
    return 1;
}

int game_music_enter_realm(GameMusicState *state, uint8_t realm_id,
                           uint8_t player_tribe, ToneRng *random_state,
                           char *out_tune_id, size_t out_capacity)
{
    uint16_t realm_bit;

    if (out_tune_id != NULL && out_capacity > 0) out_tune_id[0] = '\0';
    if (state == NULL || out_tune_id == NULL || out_capacity == 0 ||
        realm_id >= GAME_MUSIC_REALM_COUNT || player_tribe >= 4) {
        return 0;
    }
    realm_bit = (uint16_t)(1U << realm_id);
    if ((state->pending_realms & realm_bit) == 0) return 0;

    if (realm_id == 14) {
        copy_tune(out_tune_id, out_capacity, "levi");
    } else if (realm_id == player_tribe) {
        (void)snprintf(out_tune_id, out_capacity, "tribe%u",
                       (unsigned int)player_tribe);
    } else if (realm_id < 4) {
        (void)snprintf(out_tune_id, out_capacity, "act%u",
                       (unsigned int)realm_id + 1U);
    } else {
        /* FUN_00470fe7 first consumes one LCG value and only invokes
           FUN_0046ff6f when bit 0 is set. Either way, the realm's pending
           transition flag is consumed below. */
        if (random_state == NULL) return 0;
        if ((tone_rng_next15(random_state) & 1U) != 0 &&
            !choose_random_realm_tune(state, player_tribe, random_state,
                                      out_tune_id, out_capacity)) {
            return 0;
        }
    }

    state->pending_realms = (uint16_t)(state->pending_realms & ~realm_bit);
    return 1;
}
