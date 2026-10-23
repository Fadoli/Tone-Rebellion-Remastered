#include "tone_rng.h"

/* FUN_00467260 (assembly 0x467274..0x46729b, ev_ea4dec92) loads the game seed
 * [0x4a4b78], stores it as the CRT seed (FUN_00474b80), steps the MSVC LCG
 * (FUN_00474b90: seed * 0x343fd + 0x269ec3, returns bits 16..30) and writes
 * that 15-bit RESULT back to [0x4a4b78]. The next draw therefore restarts the
 * LCG from the previous 15-bit output, not from the full 32-bit state. The
 * result is scaled by range / 32768.0f and __ftol truncates toward zero. */
void tone_rng_seed(ToneRng *rng, uint32_t seed)
{
    if (rng != 0) *rng = seed;
}

uint16_t tone_rng_next15(ToneRng *rng)
{
    if (rng == 0) return 0;
    uint32_t stepped = *rng * UINT32_C(0x343fd) + UINT32_C(0x269ec3);
    uint16_t out = (uint16_t)((stepped >> 16) & UINT32_C(0x7fff));
    *rng = out;
    return out;
}

int32_t tone_rng_bounded(ToneRng *rng, int32_t range)
{
    int64_t scaled;

    if (range == 0) range = 0x7fff;
    scaled = (int64_t)tone_rng_next15(rng) * (int64_t)range;
    return (int32_t)(scaled / INT64_C(32768));
}
