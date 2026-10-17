#ifndef TONE_REBELLION_FLOATER_MOTION_H
#define TONE_REBELLION_FLOATER_MOTION_H

#include <stdint.h>

typedef struct FloaterPosition {
    int32_t x;
    int32_t y;
} FloaterPosition;

/* One coordinate update from FUN_00422d27 after its caller has resolved the
   destination and effective speed. The original clamps each axis separately,
   uses Chebyshev distance to reduce speed near the target, and alternates a
   one-pixel step when the reduced speed would otherwise be zero. */
int floater_motion_step(FloaterPosition *position,
                        FloaterPosition destination,
                        uint16_t effective_speed,
                        uint32_t source_tick);

#endif
