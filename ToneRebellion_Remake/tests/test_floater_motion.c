#include "floater_motion.h"

#include <assert.h>

int main(void)
{
    FloaterPosition position = { 100, 100 };
    FloaterPosition destination = { 120, 80 };

    /* Normal step: each axis is independently clamped to the effective speed. */
    assert(!floater_motion_step(&position, destination, 3, 1));
    assert(position.x == 103 && position.y == 97);

    /* Close-range reduction uses Chebyshev distance and truncates distance / 4
       (FUN_00422d27 0x422f8c..0x422f92). */
    position.x = 100;
    position.y = 100;
    destination.x = 109;
    destination.y = 99;
    assert(!floater_motion_step(&position, destination, 3, 0));
    assert(position.x == 102 && position.y == 99);

    /* A reduced speed of zero moves one pixel only on odd source ticks. */
    position.x = 7;
    position.y = 9;
    destination.x = 8;
    destination.y = 9;
    assert(!floater_motion_step(&position, destination, 2, 0));
    assert(position.x == 7 && position.y == 9);
    assert(floater_motion_step(&position, destination, 2, 1));
    assert(position.x == 8 && position.y == 9);

    assert(floater_motion_step(&position, destination, 2, 0));
    assert(!floater_motion_step(0, destination, 2, 0));
    return 0;
}
