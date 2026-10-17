#include "island_render_rules.h"

#include <assert.h>
#include <stdio.h>

int main(void)
{
    assert(island_pad_size_group(ISLAND_LOCATION_PAD_SMALL) == 0);
    assert(island_pad_size_group(ISLAND_LOCATION_PAD_MEDIUM) == 1);
    assert(island_pad_size_group(ISLAND_LOCATION_PAD_LARGE) == 2);
    assert(island_pad_size_group(ISLAND_LOCATION_TONE) == -1);
    assert(island_pad_size_group(ISLAND_LOCATION_LEVEL_SHIELD) == -1);
    assert(island_pad_size_group(ISLAND_LOCATION_PAD) == -1);
    assert(island_tone_pool_frame(0, 0) == 1);
    assert(island_tone_pool_frame(3, 0) == 2);
    assert(island_tone_pool_frame(114, 0) == 39);
    assert(island_tone_pool_frame(117, 0) == 38);
    assert(island_tone_pool_frame(0, 1) == 2);
    assert(island_tone_pool_frame(228, 0) == 1);
    assert(island_pad_frame(0, 0, 0, 0) == 0);
    assert(island_pad_frame(1, 0, 0, 0) == 1);
    assert(island_pad_frame(9, 0, 0, 0) == 0);
    assert(island_pad_frame(0, 1, 1, 0) == 10);
    assert(island_pad_frame(18, 0, 2, 1) == 18);
    assert(island_site_should_draw_pad(0, 0));
    assert(!island_site_should_draw_pad(0, 1));
    assert(!island_site_should_draw_pad(-1, 0));
    (void)puts("island render rule tests passed");
    return 0;
}
