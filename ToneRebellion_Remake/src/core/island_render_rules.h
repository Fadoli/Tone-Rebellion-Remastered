#ifndef TONE_REBELLION_ISLAND_RENDER_RULES_H
#define TONE_REBELLION_ISLAND_RENDER_RULES_H

#include <stdint.h>

#include "island_data.h"

/* `POOL` in bldinf.txt animates SHP frames 2..40 at three ticks per frame,
   ping-ponging. The text format numbers frames from 1; SHP indexes from 0. */
uint32_t island_tone_pool_frame(uint32_t animation_ticks, uint16_t world_x);

/* Only explicit size tags select the three groups in PAD.SHP. */
int island_pad_size_group(IslandLocationKind kind);

/* PADS uses CHUG 1..9 from bldinf.txt and FUN_0040ab42 adds world_x % 23
   after dividing the source tick counter by (segment speed + object[+0x0c]).
   The island prototype supplies zero for that unresolved object modifier. */
uint32_t island_pad_frame(uint32_t animation_ticks, uint16_t world_x,
                          unsigned pad_group, unsigned speed_adjustment);
int island_site_should_draw_pad(int pad_group, int has_drawable_runtime_item);

#endif
