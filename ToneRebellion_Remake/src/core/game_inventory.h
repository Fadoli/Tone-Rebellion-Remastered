#ifndef TONE_REBELLION_GAME_INVENTORY_H
#define TONE_REBELLION_GAME_INVENTORY_H

#include "game_session.h"

#include <stddef.h>
#include <stdint.h>

enum { GAME_INVENTORY_PAGE_SIZE = 10 };

typedef struct GameInventoryEntry {
    uint8_t item_id;
    uint16_t count;
} GameInventoryEntry;

/* FUN_0043d59b lists nonzero possession counters in ascending IDs 5..33.
   Returns the total even if capacity is smaller, writing only what fits. */
size_t game_inventory_collect(const uint16_t counts[GAME_INVENTORY_ITEM_COUNT],
                              GameInventoryEntry *out, size_t capacity);
size_t game_inventory_page_count(size_t entry_count);
/* FUN_0043d6a3 displays page*10 through min(page*10+10,count). */
size_t game_inventory_page(const GameInventoryEntry *entries,
                           size_t entry_count, size_t page,
                           GameInventoryEntry out[GAME_INVENTORY_PAGE_SIZE]);
/* InvCycle (message 0x45) advances one page and wraps to zero. */
size_t game_inventory_next_page(size_t current_page, size_t entry_count);
/* FUN_0043d45c maps the pointer to a visible cell in the 5x2 page grid. */
int game_inventory_hit_test(const GameInventoryEntry *entries,
                            size_t entry_count, size_t page,
                            int x, int y,
                            int pane_left, int pane_top,
                            int pane_right, int pane_bottom);
/* FUN_0043d6a3 centers FUN_00405e11's opaque frame bounds in each cell.
   The returned origin is suitable for a renderer that adds frame offsets. */
int game_inventory_sprite_position(int cell_left, int cell_top,
                                   int cell_width, int cell_height,
                                   int frame_x_offset, int frame_y_offset,
                                   int opaque_left, int opaque_top,
                                   int opaque_right, int opaque_bottom,
                                   int *draw_x, int *draw_y);

#endif
