#include "tone_rng.h"

#include <assert.h>
#include <stdint.h>

int main(void)
{
    ToneRng rng;

    tone_rng_seed(&rng, 1);
    assert(tone_rng_next15(&rng) == 41);
    assert(tone_rng_next15(&rng) == 172);
    assert(tone_rng_next15(&rng) == 600);

    tone_rng_seed(&rng, 1);
    assert(tone_rng_bounded(&rng, 10) == 0);
    assert(tone_rng_bounded(&rng, 10) == 0);

    tone_rng_seed(&rng, 1);
    assert(tone_rng_bounded(&rng, 0) == 40);
    assert(tone_rng_bounded(&rng, 32768) == 172);

    return 0;
}
