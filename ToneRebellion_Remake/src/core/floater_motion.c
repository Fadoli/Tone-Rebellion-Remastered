#include "floater_motion.h"

static int32_t clamp_axis_delta(int32_t delta, int32_t limit)
{
    if (delta < -limit) return -limit;
    if (delta > limit) return limit;
    return delta;
}

uint16_t floater_motion_effective_speed(
    const FloaterMotionSpeedContext *context)
{
    uint16_t speed;

    if (context == 0) return 0;

    if (context->state == 0x0e ||
        ((context->state == 8 || context->state == 9) &&
         context->near_target_override)) {
        speed = 1;
    } else {
        speed = context->unit_speed;
    }

    /* The original stores each adjustment back to a 16-bit unsigned value. */
    if (context->owner_slot == 0 && context->owner_speed_modifier > 0) {
        speed = (uint16_t)(speed << 1);
    }
    if (context->site_speed_bonus) {
        speed = (uint16_t)(speed + 1U);
    }
    return speed;
}

int floater_motion_step(FloaterPosition *position,
                        FloaterPosition destination,
                        uint16_t effective_speed,
                        uint32_t source_tick)
{
    int32_t dx;
    int32_t dy;
    int32_t distance;
    int32_t step;

    if (position == 0) return 0;

    dx = destination.x - position->x;
    dy = destination.y - position->y;
    if (dx == 0 && dy == 0) return 1;

    distance = dx < 0 ? -dx : dx;
    if ((dy < 0 ? -dy : dy) > distance) {
        distance = dy < 0 ? -dy : dy;
    }

    step = effective_speed;
    if (distance < step * 4) {
        /* FUN_00422d27 rounds the reduced speed up: (distance + 3) / 4.
           This avoids slowing a floater one extra tick when its remaining
           Chebyshev distance is not a multiple of four. */
        step = (distance + 3) / 4;
        if (step < 1) step = (int32_t)(source_tick & 1U);
    }

    dx = clamp_axis_delta(dx, step);
    dy = clamp_axis_delta(dy, step);
    position->x += dx;
    position->y += dy;
    return position->x == destination.x && position->y == destination.y;
}

int floater_motion_wander_destination(ToneRng *random_state,
                                      int32_t current_x,
                                      int32_t current_y,
                                      int32_t raw_min_x,
                                      int32_t raw_max_x,
                                      FloaterPosition *destination)
{
    int32_t min_x = raw_min_x > 0 ? raw_min_x : 0;
    int32_t max_x = raw_max_x < 0x9ff ? raw_max_x : 0x9ff;
    int32_t center_x = current_x;
    int32_t x;
    int32_t y;

    if (random_state == 0 || destination == 0) return 0;

    if (center_x < min_x + 100) center_x = min_x + 100;
    if (center_x > max_x - 100) center_x = max_x - 100;
    x = center_x - 100 + tone_rng_bounded(random_state, 200);
    y = current_y - 100 + tone_rng_bounded(random_state, 200);
    if (y < 0x28) y = 0x28;
    if (y > 0x122) y = 0x122;
    if (x < min_x || x > max_x) return 0;

    destination->x = x;
    destination->y = y;
    return 1;
}
