#include "tone_rng.h"

/* FUN_00474b90 uses 32-bit wraparound and returns the updated seed's bits
 * 16..30. FUN_00467260 scales that output by range / 32768.0f, then __ftol
 * truncates toward zero. */
void tone_rng_seed(ToneRng *rng, uint32_t seed)
{
    if (rng != 0) *rng = seed;
}

uint16_t tone_rng_next15(ToneRng *rng)
{
    if (rng == 0) return 0;
    *rng = *rng * UINT32_C(0x343fd) + UINT32_C(0x269ec3);
    return (uint16_t)((*rng >> 16) & UINT32_C(0x7fff));
}

int32_t tone_rng_bounded(ToneRng *rng, int32_t range)
{
    int64_t scaled;

    if (range == 0) range = 0x7fff;
    scaled = (int64_t)tone_rng_next15(rng) * (int64_t)range;
    return (int32_t)(scaled / INT64_C(32768));
}
