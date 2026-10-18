#include "island_render_rules.h"

int island_pad_size_group(IslandLocationKind kind)
{
    switch (kind) {
    case ISLAND_LOCATION_PAD_SMALL: return 0;
    case ISLAND_LOCATION_PAD_MEDIUM: return 1;
    case ISLAND_LOCATION_PAD_LARGE: return 2;
    default: return -1;
    }
}

uint16_t island_tone_pool_next_counter(int32_t runtime_item_id,
                                       uint16_t chug_progress)
{
    if (runtime_item_id == ISLAND_TONE_POOL_ITEM_DEFAULT) {
        /* FUN_00450a71's ID 0 sequence: 0..89, then restart at 0. */
        if (chug_progress < 0x5aU) {
            ++chug_progress;
            if (chug_progress > 0x59U) chug_progress = 0;
        } else {
            --chug_progress;
            if (chug_progress < 0x5aU) chug_progress = 0;
        }
    } else if (runtime_item_id == ISLAND_TONE_POOL_ITEM_ALTERNATE) {
        /* ID 5 has a long first run, then loops over counters 102..125. */
        ++chug_progress;
        if (chug_progress > 0x7dU) chug_progress = 0x66U;
    }
    return chug_progress;
}

uint16_t island_tone_pool_render_counter(int32_t runtime_item_id,
                                         int32_t owner_id,
                                         uint8_t tribe_visibility_mask,
                                         unsigned active_tribe,
                                         uint16_t chug_progress)
{
    /* FUN_0040bf98 holds an unowned ID-0 Tone pool at its first CHUG frame
       while the active tribe's bit is absent and its counter is below 90. */
    if (runtime_item_id == ISLAND_TONE_POOL_ITEM_DEFAULT && owner_id == -1 &&
        active_tribe < 8U &&
        (tribe_visibility_mask & (uint8_t)(1U << active_tribe)) == 0 &&
        chug_progress < 0x5aU) {
        return 0;
    }
    return chug_progress;
}

uint32_t island_tone_pool_frame(int32_t runtime_item_id,
                                uint32_t chug_progress)
{
    enum { SOURCE_FIRST_FRAME = 2, SOURCE_LAST_FRAME = 40,
           TICKS_PER_FRAME = 3 };
    if (runtime_item_id != ISLAND_TONE_POOL_ITEM_DEFAULT &&
        runtime_item_id != ISLAND_TONE_POOL_ITEM_ALTERNATE) return 0;
    /* FUN_0040bf98 applies FUN_0040ab05 over the inclusive source range,
       then SHP drawing uses zero-based frame indices. */
    {
        const uint32_t span = SOURCE_LAST_FRAME - SOURCE_FIRST_FRAME;
        const uint32_t cycle = span * 2;
        uint32_t phase = chug_progress / TICKS_PER_FRAME;
        uint32_t offset = phase % cycle;

        if (offset > span) offset = cycle - offset;
        return SOURCE_FIRST_FRAME + offset - 1;
    }
}

int island_tone_pool_should_draw(int is_tone_location,
                                 int32_t runtime_item_id,
                                 int covered_by_leviathan_building)
{
    int uses_pool_shape = runtime_item_id == ISLAND_TONE_POOL_ITEM_DEFAULT ||
                          runtime_item_id == ISLAND_TONE_POOL_ITEM_ALTERNATE;
    return is_tone_location && uses_pool_shape && !covered_by_leviathan_building;
}

uint32_t island_pad_frame(uint32_t animation_ticks, uint16_t world_x,
                          unsigned pad_group, unsigned speed_adjustment)
{
    enum { FIRST_FRAME = 0, FRAMES_PER_GROUP = 9, TICKS_PER_FRAME = 1 };
    unsigned divisor = TICKS_PER_FRAME + speed_adjustment;
    uint32_t phase;

    if (divisor == 0) divisor = TICKS_PER_FRAME;
    phase = animation_ticks / divisor + world_x % 23u;
    return (uint32_t)pad_group * FRAMES_PER_GROUP + phase % FRAMES_PER_GROUP;
}

int island_site_should_draw_pad(int pad_group, int site_occupied_by_item)
{
    return pad_group >= 0 && !site_occupied_by_item;
}

uint8_t island_toggle_realm_overlay_flags(uint8_t flags)
{
    uint8_t toggled = 0;
    unsigned bit;
    for (bit = 0; bit < 3; ++bit) {
        if ((flags & (uint8_t)(1u << bit)) == 0)
            toggled |= (uint8_t)(1u << bit);
    }
    return toggled;
}

int island_worker_realm_overlay_enabled(uint8_t flags,
                                        int renderer_allows_overlays)
{
    return renderer_allows_overlays &&
           (flags & ISLAND_FLOATER_OVERLAY_REALM) != 0;
}

int island_worker_health_overlay_enabled(uint8_t flags,
                                         int renderer_allows_overlays)
{
    return renderer_allows_overlays &&
           (flags & ISLAND_FLOATER_OVERLAY_HEALTH) != 0;
}

int island_worker_health_badge_layout(uint8_t worker_type,
                                      uint8_t max_hit_points, int facing_left,
                                      int32_t body_hit_left,
                                      int32_t body_hit_top,
                                      int32_t body_hit_right_exclusive,
                                      uint32_t *frame,
                                      int32_t *x, int32_t *y)
{
    uint8_t hp = max_hit_points;
    int horizontal_offset;
    if (worker_type > 8U || frame == NULL || x == NULL || y == NULL ||
        body_hit_right_exclusive <= body_hit_left) return 0;
    if (hp > 10u) hp = 10u;
    horizontal_offset = worker_type == 0U || worker_type == 8U
        ? 2 : (facing_left ? 0 : 5);
    *frame = 0x15u - hp;
    *x = (facing_left ? body_hit_right_exclusive - 1 : body_hit_left - 8) +
         horizontal_offset;
    *y = body_hit_top;
    return 1;
}

int island_worker_realm_badge_layout(uint8_t realm,
                                     int has_current_location,
                                     uint32_t current_location_flags,
                                     int facing_left,
                                     int32_t body_hit_left,
                                     int32_t body_hit_top,
                                     int32_t body_hit_right_exclusive,
                                     uint32_t *frame,
                                     int32_t *x, int32_t *y)
{
    if (realm >= 4u || frame == NULL || x == NULL || y == NULL ||
        body_hit_right_exclusive <= body_hit_left) return 0;
    if (has_current_location) {
        if ((current_location_flags & UINT32_C(0x10000)) != 0) {
            realm = (uint8_t)((realm + 1u) & 3u);
        } else if ((current_location_flags & UINT32_C(0x20000)) != 0) {
            realm = (uint8_t)((realm + 3u) & 3u);
        }
    }
    *frame = 0x16u + realm;
    *x = facing_left ? body_hit_right_exclusive - 1 : body_hit_left - 8;
    *y = body_hit_top;
    return 1;
}
