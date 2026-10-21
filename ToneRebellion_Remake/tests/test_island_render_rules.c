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
    assert(island_tone_pool_render_counter(0, -1, 0, 0, 42) == 0);
    assert(island_tone_pool_render_counter(0, -1, 1, 0, 42) == 42);
    assert(island_tone_pool_render_counter(0, 3, 0, 0, 42) == 42);
    assert(island_tone_pool_render_counter(5, -1, 0, 0, 42) == 42);
    assert(island_tone_pool_render_counter(0, -1, 0, 0, 90) == 90);
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
    assert(island_toggle_realm_overlay_flags(0) == 7);
    assert(island_toggle_realm_overlay_flags(7) == 0);
    assert(island_toggle_realm_overlay_flags(1) == 6);
    assert(island_toggle_realm_overlay_flags(2) == 5);
    assert(island_toggle_realm_overlay_flags(4) == 3);
    /* The source compares each global with zero; nonzero values normalize. */
    assert(island_toggle_realm_overlay_flags(0xff) == 0);
    assert(island_worker_realm_overlay_enabled(0, 1) == 0);
    assert(island_worker_realm_overlay_enabled(
               ISLAND_FLOATER_OVERLAY_REALM, 1) == 1);
    assert(island_worker_realm_overlay_enabled(
               ISLAND_FLOATER_OVERLAY_HEALTH, 1) == 0);
    assert(island_worker_realm_overlay_enabled(
               ISLAND_FLOATER_OVERLAY_REALM, 0) == 0);
    assert(island_worker_health_overlay_enabled(0, 1) == 0);
    assert(island_worker_health_overlay_enabled(
               ISLAND_FLOATER_OVERLAY_HEALTH, 1) == 1);
    assert(island_worker_health_overlay_enabled(
               ISLAND_FLOATER_OVERLAY_REALM, 1) == 0);
    assert(island_worker_health_overlay_enabled(
               ISLAND_FLOATER_OVERLAY_HEALTH, 0) == 0);
    {
        uint32_t frame = 0;
        int32_t x = 0;
        int32_t y = 0;
        /* Initial workers have 3 HP: source frame 21-3, left-edge anchor. */
        assert(island_worker_stat_badge_layout(0, 3, 0, 12, 27, 33,
                                                 &frame, &x, &y));
        assert(frame == 18 && x == 6 && y == 27);
        /* Nonzero worker types use the source's separate health-badge offset. */
        assert(island_worker_stat_badge_layout(1, 3, 0, 12, 27, 33,
                                                 &frame, &x, &y));
        assert(frame == 18 && x == 9 && y == 27);
        /* Mirrored nonzero types use the inclusive opaque right edge directly. */
        assert(island_worker_stat_badge_layout(1, 3, 1, 12, 27, 33,
                                                 &frame, &x, &y));
        assert(frame == 18 && x == 32 && y == 27);
        assert(island_worker_stat_badge_layout(8, 3, 1, 12, 27, 33,
                                                 &frame, &x, &y));
        assert(frame == 18 && x == 34 && y == 27);
        /* FUN_0042704b caps max HP at ten before selecting FLTINFO art. */
        assert(island_worker_stat_badge_layout(0, 255, 0, 12, 27, 33,
                                                 &frame, &x, &y));
        assert(frame == 11);
        assert(!island_worker_stat_badge_layout(0, 3, 0, 12, 27, 12,
                                                  &frame, &x, &y));
        assert(!island_worker_stat_badge_layout(9, 3, 0, 12, 27, 33,
                                                 &frame, &x, &y));
    }
    {
        uint32_t frame = 0;
        int32_t x = 0;
        int32_t y = 0;
        unsigned realm;
        for (realm = 0; realm < 4; ++realm) {
            assert(island_worker_realm_badge_layout((uint8_t)realm, 0, 0, 0,
                                                     12, 27, 33,
                                                     &frame, &x, &y));
            assert(frame == 22U + realm && x == 4 && y == 27);
            assert(island_worker_realm_badge_layout((uint8_t)realm, 0, 0, 1,
                                                     12, 27, 33,
                                                     &frame, &x, &y));
            assert(frame == 22U + realm && x == 32 && y == 27);
        }
        assert(!island_worker_realm_badge_layout(4, 0, 0, 0, 12, 27, 33,
                                                 &frame, &x, &y));
        assert(!island_worker_realm_badge_layout(0, 0, 0, 0, 12, 27, 12,
                                                 &frame, &x, &y));
        assert(island_worker_realm_badge_layout(0, 1, 0x10000u, 0,
                                                 12, 27, 33,
                                                 &frame, &x, &y));
        assert(frame == 23);
        assert(island_worker_realm_badge_layout(3, 1, 0x10000u, 0,
                                                 12, 27, 33,
                                                 &frame, &x, &y));
        assert(frame == 22); /* increment wraps from realm 3 to realm 0 */
        assert(island_worker_realm_badge_layout(0, 1, 0x20000u, 0,
                                                 12, 27, 33,
                                                 &frame, &x, &y));
        assert(frame == 25); /* decrement wraps from realm 0 to realm 3 */
        assert(island_worker_realm_badge_layout(0, 1, 0x30000u, 0,
                                                 12, 27, 33,
                                                 &frame, &x, &y));
        assert(frame == 23); /* 0x10000 takes precedence when both are set */
        assert(island_worker_realm_badge_layout(0, 0, 0x20000u, 0,
                                                 12, 27, 33,
                                                 &frame, &x, &y));
        assert(frame == 22); /* flags do not act without selected-location context */
    }
    (void)puts("island render rule tests passed");
    return 0;
}
