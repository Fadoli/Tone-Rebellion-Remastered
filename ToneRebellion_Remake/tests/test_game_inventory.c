#include "game_inventory.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

static void test_collects_owned_items_in_source_order(void)
{
    uint16_t counts[GAME_INVENTORY_ITEM_COUNT] = {0};
    GameInventoryEntry entries[GAME_INVENTORY_ITEM_COUNT];
    counts[0] = 2;
    counts[10] = 1;
    counts[28] = 4;
    assert(game_inventory_collect(counts, entries, GAME_INVENTORY_ITEM_COUNT) == 3);
    assert(entries[0].item_id == 5 && entries[0].count == 2);
    assert(entries[1].item_id == 15 && entries[1].count == 1);
    assert(entries[2].item_id == 33 && entries[2].count == 4);
    assert(game_inventory_collect(counts, entries, 2) == 3);
    assert(entries[1].item_id == 15);
}

static void test_ten_item_pages_and_wrap(void)
{
    GameInventoryEntry entries[GAME_INVENTORY_ITEM_COUNT];
    GameInventoryEntry page[GAME_INVENTORY_PAGE_SIZE];
    size_t index;
    for (index = 0; index < GAME_INVENTORY_ITEM_COUNT; ++index) {
        entries[index].item_id = (uint8_t)(GAME_INVENTORY_ITEM_FIRST_ID + index);
        entries[index].count = (uint16_t)(index + 1);
    }
    assert(game_inventory_page_count(0) == 0);
    assert(game_inventory_page_count(10) == 1);
    assert(game_inventory_page_count(11) == 2);
    assert(game_inventory_page_count(29) == 3);
    assert(game_inventory_page(entries, 29, 0, page) == 10);
    assert(page[0].item_id == 5 && page[9].item_id == 14);
    assert(game_inventory_page(entries, 29, 2, page) == 9);
    assert(page[0].item_id == 25 && page[8].item_id == 33);
    assert(game_inventory_page(entries, 29, 3, page) == 0);
    assert(game_inventory_next_page(0, 10) == 0);
    assert(game_inventory_next_page(0, 11) == 1);
    assert(game_inventory_next_page(1, 11) == 0);
    assert(game_inventory_next_page(8, 29) == 0);
}

static void test_shrunk_inventory_keeps_source_page_until_cycle(void)
{
    GameInventoryEntry entries[GAME_INVENTORY_ITEM_COUNT];
    GameInventoryEntry page[GAME_INVENTORY_PAGE_SIZE];
    size_t index;

    for (index = 0; index < GAME_INVENTORY_ITEM_COUNT; ++index) {
        entries[index].item_id = (uint8_t)(GAME_INVENTORY_ITEM_FIRST_ID + index);
        entries[index].count = 1;
    }

    /* Source FUN_0043d59b refreshes the item count without resetting +0xec;
       FUN_0043d6a3 therefore draws no entries until InvCycle wraps to zero. */
    assert(game_inventory_page(entries, 9, 1, page) == 0);
    assert(game_inventory_hit_test(entries, 9, 1, 110, 130,
                                   100, 100, 600, 324) == -1);
    assert(game_inventory_next_page(1, 9) == 0);
    assert(game_inventory_page(entries, 9, 0, page) == 9);
    assert(page[0].item_id == GAME_INVENTORY_ITEM_FIRST_ID);
}

static void test_empty_and_null_inputs(void)
{
    uint16_t counts[GAME_INVENTORY_ITEM_COUNT] = {0};
    GameInventoryEntry entries[GAME_INVENTORY_PAGE_SIZE];
    assert(game_inventory_collect(counts, entries, GAME_INVENTORY_PAGE_SIZE) == 0);
    assert(game_inventory_collect(NULL, entries, GAME_INVENTORY_PAGE_SIZE) == 0);
    assert(game_inventory_page(NULL, 0, 0, entries) == 0);
    assert(game_inventory_page(entries, 0, 0, entries) == 0);
}

static void test_source_inventory_cell_hit_test(void)
{
    GameInventoryEntry entries[GAME_INVENTORY_ITEM_COUNT];
    size_t index;
    for (index = 0; index < GAME_INVENTORY_ITEM_COUNT; ++index) {
        entries[index].item_id = (uint8_t)(GAME_INVENTORY_ITEM_FIRST_ID + index);
        entries[index].count = 1;
    }
    assert(game_inventory_hit_test(entries, 29, 0, 110, 130,
                                   100, 100, 600, 324) == 5);
    assert(game_inventory_hit_test(entries, 29, 0, 550, 130,
                                   100, 100, 600, 324) == 9);
    assert(game_inventory_hit_test(entries, 29, 0, 110, 224,
                                   100, 100, 600, 324) == 10);
    assert(game_inventory_hit_test(entries, 29, 0, 200, 224,
                                   100, 100, 600, 324) == 11);
    assert(game_inventory_hit_test(entries, 29, 1, 110, 130,
                                   100, 100, 600, 324) == 15);
    assert(game_inventory_hit_test(entries, 29, 2, 410, 224,
                                   100, 100, 600, 324) == 33);
    assert(game_inventory_hit_test(entries, 29, 2, 510, 224,
                                   100, 100, 600, 324) == -1);
    assert(game_inventory_hit_test(entries, 29, 0, 99, 130,
                                   100, 100, 600, 324) == -1);
    assert(game_inventory_hit_test(entries, 29, 0, 110, 123,
                                   100, 100, 600, 324) == -1);
    assert(game_inventory_hit_test(entries, 29, 3, 110, 130,
                                   100, 100, 600, 324) == -1);
}

static void test_icons_are_centered_by_opaque_bounds(void)
{
    int draw_x = -1;
    int draw_y = -1;
    int bitmap_x;
    int bitmap_y;
    assert(game_inventory_sprite_position(100, 200, 50, 40, 2, -2,
                                         3, 4, 13, 14,
                                         &draw_x, &draw_y));
    /* Add the SHP frame offsets as draw_sprite does, then inspect the
       opaque bounds. Source code uses (max-min)+1 for the cell centering. */
    bitmap_x = draw_x + 2;
    bitmap_y = draw_y - 2;
    assert(bitmap_x + 3 == 119);
    assert(bitmap_y + 4 == 214);
    assert(bitmap_x + 13 == 129);
    assert(bitmap_y + 14 == 224);
    assert(!game_inventory_sprite_position(100, 200, 50, 40, 0, 0,
                                          8, 8, 7, 9,
                                          &draw_x, &draw_y));
    assert(!game_inventory_sprite_position(100, 200, 50, 40, 0, 0,
                                          0, 0, 1, 1, NULL, &draw_y));
}

static void test_click_selects_hovered_item(void)
{
    int selected = game_inventory_click_selection(-1, 12);
    assert(selected == 12);
    /* FUN_0043d41a emits no selection event when no item is hovered. */
    assert(game_inventory_click_selection(selected, -1) == 12);
    assert(game_inventory_click_selection(selected, 34) == 12);
}

int main(void)
{
    test_collects_owned_items_in_source_order();
    test_ten_item_pages_and_wrap();
    test_shrunk_inventory_keeps_source_page_until_cycle();
    test_empty_and_null_inputs();
    test_source_inventory_cell_hit_test();
    test_icons_are_centered_by_opaque_bounds();
    test_click_selects_hovered_item();
    puts("game_inventory tests passed");
    return 0;
}
