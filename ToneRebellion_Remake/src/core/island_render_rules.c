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
