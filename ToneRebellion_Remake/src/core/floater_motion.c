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
    if (context->subtype == 0 && context->category_speed_modifier > 0) {
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
        step = distance / 4;
        if (step < 1) step = (int32_t)(source_tick & 1U);
    }

    dx = clamp_axis_delta(dx, step);
    dy = clamp_axis_delta(dy, step);
    position->x += dx;
    position->y += dy;
    return position->x == destination.x && position->y == destination.y;
}
