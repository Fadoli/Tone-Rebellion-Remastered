#include "game_inventory.h"

size_t game_inventory_collect(const uint16_t counts[GAME_INVENTORY_ITEM_COUNT],
                              GameInventoryEntry *out, size_t capacity)
{
    size_t count = 0;
    size_t index;
    if (counts == NULL) return 0;
    for (index = 0; index < GAME_INVENTORY_ITEM_COUNT; ++index) {
        if (counts[index] == 0) continue;
        if (count < capacity && out != NULL) {
            out[count].item_id = (uint8_t)(GAME_INVENTORY_ITEM_FIRST_ID + index);
            out[count].count = counts[index];
        }
        ++count;
    }
    return count;
}

size_t game_inventory_page_count(size_t entry_count)
{
    return entry_count / GAME_INVENTORY_PAGE_SIZE +
        (entry_count % GAME_INVENTORY_PAGE_SIZE != 0);
}

size_t game_inventory_page(const GameInventoryEntry *entries,
                           size_t entry_count, size_t page,
                           GameInventoryEntry out[GAME_INVENTORY_PAGE_SIZE])
{
    size_t page_count = game_inventory_page_count(entry_count);
    size_t first;
    size_t amount;
    size_t index;
    if (entries == NULL || out == NULL || page >= page_count) return 0;
    first = page * GAME_INVENTORY_PAGE_SIZE;
    amount = entry_count - first;
    if (amount > GAME_INVENTORY_PAGE_SIZE) amount = GAME_INVENTORY_PAGE_SIZE;
    for (index = 0; index < amount; ++index) out[index] = entries[first + index];
    return amount;
}

size_t game_inventory_next_page(size_t current_page, size_t entry_count)
{
    size_t pages = game_inventory_page_count(entry_count);
    if (pages < 2) return 0;
    return current_page + 1 < pages ? current_page + 1 : 0;
}

int game_inventory_hit_test(const GameInventoryEntry *entries,
                            size_t entry_count, size_t page,
                            int x, int y,
                            int pane_left, int pane_top,
                            int pane_right, int pane_bottom)
{
    int pane_width = pane_right - pane_left;
    int pane_height = pane_bottom - pane_top;
    int column_width;
    int row_height;
    size_t first;
    size_t slot;
    if (entries == NULL || page >= game_inventory_page_count(entry_count) ||
        pane_width <= 0 || pane_height <= 24 ||
        x < pane_left || x > pane_right ||
        y < pane_top + 24 || y > pane_bottom) return -1;
    column_width = pane_width / 5;
    row_height = (pane_height - 24) / 2;
    if (column_width <= 0 || row_height <= 0) return -1;
    first = page * GAME_INVENTORY_PAGE_SIZE;
    if ((x - pane_left) / column_width >= 5) return -1;
    slot = (size_t)((x - pane_left) / column_width) +
        (size_t)((y - (pane_top + 24)) / row_height) * 5;
    if (slot >= GAME_INVENTORY_PAGE_SIZE || first + slot >= entry_count) return -1;
    return entries[first + slot].item_id;
}

int game_inventory_click_selection(int selected_item_id, int hovered_item_id)
{
    if (hovered_item_id < GAME_INVENTORY_ITEM_FIRST_ID ||
        hovered_item_id >= GAME_INVENTORY_ITEM_FIRST_ID +
                               GAME_INVENTORY_ITEM_COUNT) {
        return selected_item_id;
    }
    return hovered_item_id;
}

int game_inventory_sprite_position(int cell_left, int cell_top,
                                   int cell_width, int cell_height,
                                   int frame_x_offset, int frame_y_offset,
                                   int opaque_left, int opaque_top,
                                   int opaque_right, int opaque_bottom,
                                   int *draw_x, int *draw_y)
{
    int opaque_width;
    int opaque_height;
    if (draw_x == NULL || draw_y == NULL || cell_width <= 0 || cell_height <= 0 ||
        opaque_right < opaque_left || opaque_bottom < opaque_top) return 0;
    /* FUN_0043d6a3 adds one to the endpoint difference returned by
       FUN_00405e11 before centering the opaque bounds within the cell. */
    opaque_width = opaque_right - opaque_left + 1;
    opaque_height = opaque_bottom - opaque_top + 1;
    *draw_x = cell_left + (cell_width - opaque_width) / 2 - opaque_left -
        frame_x_offset;
    *draw_y = cell_top + (cell_height - opaque_height) / 2 - opaque_top -
        frame_y_offset;
    return 1;
}
