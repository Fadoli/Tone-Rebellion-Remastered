#include "floater_motion.h"

static int32_t clamp_axis_delta(int32_t delta, int32_t limit)
{
    if (delta < -limit) return -limit;
    if (delta > limit) return limit;
    return delta;
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
