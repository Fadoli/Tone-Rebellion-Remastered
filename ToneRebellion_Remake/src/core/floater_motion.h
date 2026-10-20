#ifndef TONE_REBELLION_FLOATER_MOTION_H
#define TONE_REBELLION_FLOATER_MOTION_H

#include <stdint.h>
#include "tone_rng.h"

typedef struct FloaterPosition {
    int32_t x;
    int32_t y;
} FloaterPosition;

/* Inputs already resolved by the caller from the floater, target and island
   state. near_target_override is the source's < 100 distance branch for
   states 8/9; site_speed_bonus is true only when the owner upgrade bit and
   current site item match one of the three source pairs. */
typedef struct FloaterMotionSpeedContext {
    uint16_t unit_speed;
    uint8_t owner_slot;
    uint8_t floater_subtype;
    uint8_t state;
    /* Positive DAT_00618f5a entry doubles speed for floater subtype 0. */
    int16_t owner_speed_modifier;
    uint8_t near_target_override;
    uint8_t site_speed_bonus;
} FloaterMotionSpeedContext;

/* Resolve FUN_00422d27's state and unit modifiers before the shared coordinate
   kernel. The caller remains responsible for destination resolution and for
   deriving the two conditional booleans above. */
uint16_t floater_motion_effective_speed(
    const FloaterMotionSpeedContext *context);

/* One coordinate update from FUN_00422d27 after its caller has resolved the
   destination and effective speed. The original clamps each axis separately,
   uses Chebyshev distance to reduce speed near the target, and alternates a
   one-pixel step when the reduced speed would otherwise be zero. */
int floater_motion_step(FloaterPosition *position,
                        FloaterPosition destination,
                        uint16_t effective_speed,
                        uint32_t source_tick);

/* Resolve FUN_00423068's state-0x0e random waypoint. Raw horizontal limits
   are the category/island pair read by the source; zero and 0x9ff select its
   global fallback limits. The RNG advances twice, including rejected points. */
int floater_motion_wander_destination(ToneRng *random_state,
                                      int32_t current_x,
                                      int32_t current_y,
                                      int32_t raw_min_x,
                                      int32_t raw_max_x,
                                      FloaterPosition *destination);

#endif
