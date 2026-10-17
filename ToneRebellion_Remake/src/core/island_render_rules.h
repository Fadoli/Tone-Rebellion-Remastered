#ifndef TONE_REBELLION_ISLAND_RENDER_RULES_H
#define TONE_REBELLION_ISLAND_RENDER_RULES_H

#include <stdint.h>

#include "island_data.h"

/* `POOL` in bldinf.txt animates SHP frames 2..40 at three ticks per frame,
   ping-ponging. The text format numbers frames from 1; SHP indexes from 0. */
uint32_t island_tone_pool_frame(uint32_t animation_ticks, uint16_t world_x);

/* Only explicit size tags select the three groups in PAD.SHP. */
int island_pad_size_group(IslandLocationKind kind);

#endif
