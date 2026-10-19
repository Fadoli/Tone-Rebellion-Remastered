#include "building_render.h"

#include <stdint.h>

uint32_t building_render_base_frame(const BuildingRenderItem *item)
{
    return building_render_base_frame_for_state(item, 0, 0);
}

uint32_t building_render_base_frame_for_state(const BuildingRenderItem *item,
                                              uint16_t base_progress,
                                              uint32_t source_flags)
{
    const BuildingRenderSegment *segment;
    uint32_t frame;
    if (item == NULL) return 0;
    segment = &item->base;
    if (!segment->present || segment->first_frame == 0 ||
        segment->last_frame < segment->first_frame) return 0;
    frame = (uint32_t)segment->first_frame - 1U + base_progress;
    if ((source_flags & 0x20U) != 0 && frame != 0) --frame;
    if (frame < (uint32_t)segment->first_frame - 1U) {
        frame = (uint32_t)segment->first_frame - 1U;
    }
    if (frame > (uint32_t)segment->last_frame - 1U) {
        frame = (uint32_t)segment->last_frame - 1U;
    }
    return frame;
}

uint32_t building_render_chug_frame(const BuildingRenderItem *item,
                                    uint32_t animation_ticks)
{
    const BuildingRenderSegment *segment;
    uint32_t first;
    uint32_t last;
    uint32_t span;
    uint32_t step;
    uint32_t offset;

    if (item == NULL || !item->chug.present || item->chug.first_frame == 0 ||
        item->chug.last_frame < item->chug.first_frame ||
        item->chug.ticks_per_frame == 0) return 0;
    segment = &item->chug;
    first = (uint32_t)segment->first_frame - 1U;
    last = (uint32_t)segment->last_frame - 1U;
    span = last - first;
    step = animation_ticks / (uint32_t)segment->ticks_per_frame;
    if (segment->ping_pong != 0 && span != 0) {
        uint32_t cycle = span * 2U;
        offset = step % cycle;
        if (offset > span) offset = cycle - offset;
    } else {
        offset = step % (span + 1U);
    }
    return first + offset;
}

uint32_t building_render_chug_duration(const BuildingRenderItem *item)
{
    uint32_t span;
    uint32_t frame_steps;
    if (item == NULL || !item->chug.present || item->chug.first_frame == 0 ||
        item->chug.last_frame < item->chug.first_frame ||
        item->chug.ticks_per_frame == 0) return 0;
    span = (uint32_t)item->chug.last_frame - item->chug.first_frame;
    frame_steps = item->chug.ping_pong != 0 ? span * 2U : span + 1U;
    return frame_steps * item->chug.ticks_per_frame;
}

uint32_t building_render_glyph_frame(const BuildingRenderItem *item,
                                     uint32_t animation_ticks)
{
    uint32_t first;
    uint32_t last;
    uint32_t phase;
    uint32_t scaled;
    uint32_t offset;
    uint32_t remainder;

    if (item == NULL || !item->glyph.present || item->glyph.first_frame == 0 ||
        item->glyph.last_frame < item->glyph.first_frame) return 0;
    first = (uint32_t)item->glyph.first_frame - 1U;
    last = (uint32_t)item->glyph.last_frame - 1U;
    phase = animation_ticks % 40U;
    if (phase > 20U) phase = 40U - phase;
    /* FUN_0040aab0 returns __ftol(delta * phase / 20). x87 FISTP rounds
       ties to even under the default control word; a plain C cast truncates. */
    scaled = (last - first) * phase;
    offset = scaled / 20U;
    remainder = scaled % 20U;
    if (remainder > 10U || (remainder == 10U && (offset & 1U) != 0)) ++offset;
    return first + offset;
}

static uint32_t segment_frame(const BuildingRenderSegment *segment, uint32_t ticks)
{
    uint32_t first;
    uint32_t last;
    uint32_t span;
    uint32_t step;
    uint32_t offset;
    uint32_t cycle;
    if (segment == NULL || !segment->present || segment->first_frame == 0 ||
        segment->last_frame < segment->first_frame || segment->ticks_per_frame == 0) return 0;
    first = (uint32_t)segment->first_frame - 1U;
    last = (uint32_t)segment->last_frame - 1U;
    span = last - first;
    step = ticks / segment->ticks_per_frame;
    if (segment->ping_pong && span != 0) {
        cycle = span * 2U;
        offset = step % cycle;
        if (offset > span) offset = cycle - offset;
    } else {
        offset = step % (span + 1U);
    }
    return first + offset;
}

uint32_t building_render_inci_frame(const BuildingRenderItem *item,
                                    uint32_t animation_ticks)
{
    return item == NULL ? 0 : segment_frame(&item->inci, animation_ticks);
}

uint32_t building_render_cons_frame(const BuildingRenderItem *item,
                                    uint32_t animation_ticks, uint32_t source_flags)
{
    if (item == NULL || !item->cons.present) return 0;
    if ((source_flags & 4U) == 0 || item->cons.ticks_per_frame == 0) {
        return item->cons.fallback_frame == 0 ? UINT32_MAX
                                               : (uint32_t)item->cons.fallback_frame - 1U;
    }
    return segment_frame(&item->cons, animation_ticks);
}

uint32_t building_render_prod_frame(const BuildingRenderItem *item,
                                    uint32_t animation_ticks, uint32_t source_flags)
{
    if (item == NULL || !item->prod.present) return 0;
    if ((source_flags & 2U) == 0 || item->prod.ticks_per_frame == 0) {
        return item->prod.fallback_frame == 0 ? UINT32_MAX
                                               : (uint32_t)item->prod.fallback_frame - 1U;
    }
    return segment_frame(&item->prod, animation_ticks);
}

BuildingRenderPoint building_render_prod_frame_position(int anchor_x, int anchor_y)
{
    BuildingRenderPoint position = {anchor_x, anchor_y};
    return position;
}

BuildingRenderPoint building_render_prod_threshold_position(const BuildingRenderItem *item,
                                                            int anchor_x, int anchor_y)
{
    BuildingRenderPoint position = {anchor_x, anchor_y};
    if (item != NULL && item->prod.present) {
        position.x += item->prod.offset_x;
        position.y += item->prod.offset_y;
    }
    return position;
}

uint32_t building_render_barg_frame(const BuildingRenderItem *item,
                                    double barg_progress)
{
    uint32_t first;
    uint32_t last;
    uint32_t span_steps;
    uint32_t ticks;
    double scaled;
    double fractional;

    if (item == NULL || !item->barg.present || item->barg.first_frame == 0 ||
        item->barg.last_frame < item->barg.first_frame ||
        barg_progress != barg_progress) return UINT32_MAX;
    first = (uint32_t)item->barg.first_frame - 1U;
    last = (uint32_t)item->barg.last_frame - 1U;
    span_steps = last - first + 2U;
    scaled = (double)span_steps * barg_progress;
    /* The original FISTP result is discarded when it is not positive or
       overflows its signed 32-bit destination. */
    if (!(scaled > 0.0)) return UINT32_MAX;
    if (scaled >= (double)INT32_MAX + 0.5) return UINT32_MAX;
    if (scaled >= (double)span_steps) return last;
    ticks = (uint32_t)scaled;
    fractional = scaled - (double)ticks;
    if (fractional > 0.5 || (fractional == 0.5 && (ticks & 1U) != 0)) ++ticks;
    if (ticks == 0) return UINT32_MAX;
    if (ticks - 1U > last - first) return last;
    return first + ticks - 1U;
}
