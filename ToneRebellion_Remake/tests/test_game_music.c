#include "game_music.h"

#include <assert.h>
#include <string.h>

int main(void)
{
    GameMusicState state;
    ToneRng rng;
    char tune[16];
    int8_t previous_random_track;

    tone_rng_seed(&rng, 1);
    game_music_state_init(&state);
    assert(state.pending_realms == 0x7fffU);
    assert(game_music_enter_realm(&state, 2, 2, &rng, tune, sizeof(tune)));
    assert(strcmp(tune, "tribe2") == 0);
    assert(!game_music_enter_realm(&state, 2, 2, &rng, tune, sizeof(tune)));
    assert(tune[0] == '\0');

    assert(game_music_enter_realm(&state, 0, 2, &rng, tune, sizeof(tune)));
    assert(strcmp(tune, "act1") == 0);
    assert(game_music_enter_realm(&state, 14, 2, &rng, tune, sizeof(tune)));
    assert(strcmp(tune, "levi") == 0);

    assert(game_music_enter_realm(&state, 4, 2, &rng, tune, sizeof(tune)));
    assert(strcmp(tune, "tribe2") == 0); /* gate 41 is odd; next draw 172 % 9 == 1 */
    assert(state.last_random_track == 1);
    previous_random_track = state.last_random_track;
    assert(game_music_enter_realm(&state, 5, 2, &rng, tune, sizeof(tune)));
    assert(tune[0] == '\0'); /* gate 600 is even: consume flag, keep current tune */
    assert(state.last_random_track == previous_random_track);
    assert(!game_music_enter_realm(&state, 5, 2, &rng, tune, sizeof(tune)));
    assert(!game_music_enter_realm(&state, 15, 2, &rng, tune, sizeof(tune)));
    assert(!game_music_enter_realm(&state, 1, 4, &rng, tune, sizeof(tune)));

    return 0;
}
