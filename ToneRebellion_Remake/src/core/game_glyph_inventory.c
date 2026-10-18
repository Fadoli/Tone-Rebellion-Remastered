#include "game_glyph_inventory.h"

#include <stdio.h>

uint32_t game_glyph_inventory_frame(uint16_t glyph_mask, int glyph_index,
                                    int selected_glyph)
{
    if (glyph_index < 0 || glyph_index >= GAME_GLYPH_COUNT ||
        (glyph_mask & (uint16_t)(1U << (unsigned int)glyph_index)) == 0) {
        return UINT32_MAX;
    }
    return (uint32_t)glyph_index + 1U +
           (glyph_index == selected_glyph ? GAME_GLYPH_COUNT : 0U);
}

int game_glyph_inventory_hit_test(uint16_t glyph_mask,
                                  const GameGlyphCenter centers[GAME_GLYPH_COUNT],
                                  int x, int y)
{
    unsigned int glyph_index;
    if (centers == NULL) return -1;
    for (glyph_index = 0; glyph_index < GAME_GLYPH_COUNT; ++glyph_index) {
        int dx;
        int dy;
        if ((glyph_mask & (uint16_t)(1U << glyph_index)) == 0) continue;
        dx = x - centers[glyph_index].x;
        dy = y - centers[glyph_index].y;
        if (dx > -16 && dx < 16 && dy > -16 && dy < 15) {
            return (int)glyph_index;
        }
    }
    return -1;
}

int game_glyph_inventory_update_hover(
    int previous_glyph, uint16_t glyph_mask,
    const GameGlyphCenter centers[GAME_GLYPH_COUNT], int event_in_pane,
    int x, int y)
{
    if (!event_in_pane) return previous_glyph;
    return game_glyph_inventory_hit_test(glyph_mask, centers, x, y);
}

int game_glyph_inventory_click_selection(int *selected_glyph,
                                         int hovered_glyph,
                                         int event_in_pane)
{
    if (!event_in_pane) return 0;
    if (selected_glyph != NULL && hovered_glyph >= 0 &&
        hovered_glyph < GAME_GLYPH_COUNT) {
        *selected_glyph = hovered_glyph;
    }
    return 1;
}

int game_glyph_inventory_mouse_leave(int *hovered_glyph,
                                     int *info_is_default)
{
    int changed;
    if (hovered_glyph == NULL || info_is_default == NULL) return 0;
    changed = *hovered_glyph != -1 || !*info_is_default;
    *hovered_glyph = -1;
    *info_is_default = 1;
    return changed;
}

int game_glyph_inventory_key(unsigned int glyph_index,
                             char *output, size_t output_capacity)
{
    int written;
    if (output == NULL || output_capacity == 0) return 0;
    output[0] = '\0';
    if (glyph_index >= GAME_GLYPH_COUNT) return 0;
    written = snprintf(output, output_capacity, "GLYPH%02u", glyph_index);
    if (written < 0 || (size_t)written >= output_capacity) {
        output[0] = '\0';
        return 0;
    }
    return 1;
}

int game_glyph_inventory_cursor_slot(int selected_glyph,
                                     int selected_inventory_item)
{
    return selected_glyph != -1 || selected_inventory_item != -1 ? 0x0b : 0x0d;
}
