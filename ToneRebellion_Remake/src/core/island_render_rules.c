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

uint32_t island_tone_pool_frame(uint32_t animation_ticks, uint16_t world_x)
{
    enum { FIRST_FRAME = 1, LAST_FRAME = 39, TICKS_PER_FRAME = 3 };
    const uint32_t span = LAST_FRAME - FIRST_FRAME;
    const uint32_t cycle = span * 2;
    uint32_t phase = animation_ticks / TICKS_PER_FRAME + world_x % 23u;
    uint32_t offset = phase % cycle;

    if (offset > span) offset = cycle - offset;
    return FIRST_FRAME + offset;
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

int island_site_should_draw_pad(int pad_group, int has_drawable_runtime_item)
{
    return pad_group >= 0 && !has_drawable_runtime_item;
}
