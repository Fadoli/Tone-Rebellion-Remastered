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
    assert(ISLAND_TONE_POOL_BASE_FRAME == 0); /* bldinf BASE 1 1 -> SHP index 0 */
    assert(island_tone_pool_frame(ISLAND_TONE_POOL_ITEM_DEFAULT, 0) == 1);
    assert(island_tone_pool_frame(ISLAND_TONE_POOL_ITEM_DEFAULT, 3) == 2);
    assert(island_tone_pool_frame(ISLAND_TONE_POOL_ITEM_DEFAULT, 114) == 39);
    assert(island_tone_pool_frame(ISLAND_TONE_POOL_ITEM_DEFAULT, 117) == 38);
    assert(island_tone_pool_frame(ISLAND_TONE_POOL_ITEM_DEFAULT, 228) == 1);
    /* Source ID 0 only traverses counters 0..89, so its frames stop at 30. */
    assert(island_tone_pool_frame(ISLAND_TONE_POOL_ITEM_DEFAULT, 89) == 30);
    assert(island_tone_pool_next_counter(ISLAND_TONE_POOL_ITEM_DEFAULT, 89) == 0);
    /* Source ID 5 starts with a full sweep, then loops over 102..125. */
    assert(island_tone_pool_frame(ISLAND_TONE_POOL_ITEM_ALTERNATE, 114) == 39);
    assert(island_tone_pool_frame(ISLAND_TONE_POOL_ITEM_ALTERNATE, 125) == 36);
    assert(island_tone_pool_next_counter(ISLAND_TONE_POOL_ITEM_ALTERNATE, 125) == 102);
    assert(island_tone_pool_frame(ISLAND_TONE_POOL_ITEM_ALTERNATE, 102) == 35);
    assert(island_tone_pool_frame(99, 114) == 0);
    assert(island_tone_pool_should_draw(1, 0, 0));
    assert(island_tone_pool_should_draw(1, 5, 0));
    assert(!island_tone_pool_should_draw(1, 5, 1));
    assert(!island_tone_pool_should_draw(1, 6, 0));
    assert(!island_tone_pool_should_draw(0, 0, 0));
    assert(island_pad_frame(0, 0, 0, 0) == 0);
    assert(island_pad_frame(1, 0, 0, 0) == 1);
    assert(island_pad_frame(9, 0, 0, 0) == 0);
    assert(island_pad_frame(0, 1, 1, 0) == 10);
    assert(island_pad_frame(18, 0, 2, 1) == 18);
    assert(island_pad_frame(2, 0, 0, 0) == 2);
    assert(island_pad_frame(2, 0, 1, 1) == 10);
    assert(island_pad_frame(6, 0, 2, 2) == 20);
    assert(island_site_should_draw_pad(0, 0));
    /* Occupancy suppresses the site ring even if the item's SHP is unresolved. */
    assert(!island_site_should_draw_pad(0, 1));
    assert(!island_site_should_draw_pad(-1, 0));
    (void)puts("island render rule tests passed");
    return 0;
}
