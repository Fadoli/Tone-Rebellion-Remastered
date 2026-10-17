#ifndef TONE_REBELLION_TONE_RNG_H
#define TONE_REBELLION_TONE_RNG_H

#include <stdint.h>

/* The original runtime keeps one 32-bit seed and exposes a 15-bit MSVC LCG. */
typedef uint32_t ToneRng;

void tone_rng_seed(ToneRng *rng, uint32_t seed);
uint16_t tone_rng_next15(ToneRng *rng);

/* Mirrors FUN_00467260: range zero is replaced with 0x7fff, then
 * (next15 * range) / 32768 is truncated toward zero. */
int32_t tone_rng_bounded(ToneRng *rng, int32_t range);

#endif
