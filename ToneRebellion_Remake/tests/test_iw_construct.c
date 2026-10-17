#include "iw_construct.h"

#include <assert.h>
#include <string.h>

static void test_hover_click_and_pages(void)
{
    const WindowPane pane = {192, 368, 447, 471};
    const int32_t items[] = {37, 38, 39, 40, 41, 42, 43};
    IwConstructState state;
    IwConstructTransition event;

    iw_construct_init(&state, 7);
    assert(state.page == 0 && state.hovered_column == -1 && state.dirty);
    assert(state.cycle_button_visible);
    iw_construct_mouse_move(&state, &pane, 192, 394, items, 7, &event);
    assert(event.changed && event.message_count == 1);
    assert(event.messages[0].code == 0x3c && event.messages[0].value == 37);
    iw_construct_mouse_move(&state, &pane, 193, 394, items, 7, &event);
    assert(!event.changed && event.message_count == 0);

    iw_construct_mouse_move(&state, &pane, 381, 394, items, 7, &event);
    assert(event.changed && state.hovered_column == 3 && state.hovered_item_id == 40);
    iw_construct_mouse_click(&state, 0, &event);
    assert(event.message_count == 2);
    assert(event.messages[0].code == 0x34 && event.messages[0].value == 40);
    assert(event.messages[1].code == 0x33 && event.messages[1].value == 0);

    iw_construct_build_cycle(&state, 7, &event);
    assert(state.page == 1 && state.hovered_item_id == -1 && state.dirty);
    assert(event.message_count == 1 && event.messages[0].code == 0x3c &&
           event.messages[0].value == -2);
    iw_construct_mouse_move(&state, &pane, 192, 394, items, 7, &event);
    assert(event.changed && state.hovered_item_id == 41);
    iw_construct_mouse_click(&state, 1, &event);
    assert(event.message_count == 2 && event.messages[0].value == 41);
    iw_construct_build_cycle(&state, 7, &event);
    assert(state.page == 0);
}

static void test_bounds_and_info_messages(void)
{
    const WindowPane pane = {192, 368, 447, 471};
    const int32_t items[] = {37, 38, 39, 40};
    IwConstructState state;
    IwConstructInfoState info;
    IwConstructTransition event;

    iw_construct_init(&state, 4);
    assert(!state.cycle_button_visible);
    iw_construct_mouse_move(&state, &pane, 192, 393, items, 4, &event);
    assert(state.hovered_item_id == -1 && event.message_count == 0);
    iw_construct_mouse_move(&state, &pane, 447, 394, items, 4, &event);
    assert(state.hovered_item_id == -1 && event.message_count == 0);

    iw_construct_info_init(&info);
    assert(info.item_id == -1);
    assert(iw_construct_info_handle_message(&info, 0x9a4, 39));
    assert(info.item_id == 39 && info.dirty);
    assert(!iw_construct_info_handle_message(&info, 0x9a3, 40));
    assert(iw_construct_info_handle_message(&info, 1, 0));
    assert(info.item_id == -1);
}

static void test_cycle_button_threshold(void)
{
    IwConstructState state;
    iw_construct_init(&state, 5);
    assert(state.cycle_button_visible);
    iw_construct_init(&state, 0);
    assert(!state.cycle_button_visible);
}

static void test_source_build_list_order_and_unlock_rules(void)
{
    static const int32_t initial_expected[] = {40, 37, 39, 38, 44};
    static const int32_t medium_expected[] = {40, 37, 39, 38, 44, 45};
    PadCatalog catalog;
    int32_t items[IW_CONSTRUCT_BUILD_CANDIDATE_COUNT];
    size_t item_count;
    unsigned int i;

    memset(&catalog, 0, sizeof(catalog));
    catalog.item_count = 101;
    for (i = 0; i < catalog.item_count; ++i) {
        catalog.items[i].item_id = (uint16_t)i;
        catalog.items[i].size = 0;
        catalog.items[i].building_tone_cost = 1;
    }
    assert(iw_construct_build_list(&catalog, 0, 0, 0, 1,
                                   items, IW_CONSTRUCT_BUILD_CANDIDATE_COUNT,
                                   &item_count));
    assert(item_count == sizeof(initial_expected) / sizeof(initial_expected[0]));
    assert(memcmp(items, initial_expected, sizeof(initial_expected)) == 0);

    assert(iw_construct_build_list(&catalog, 0, 0, 1, 2,
                                   items, IW_CONSTRUCT_BUILD_CANDIDATE_COUNT,
                                   &item_count));
    assert(item_count == sizeof(medium_expected) / sizeof(medium_expected[0]));
    assert(memcmp(items, medium_expected, sizeof(medium_expected)) == 0);

    /* Tribe-specific records are resolved by player slot, while window
       messages still carry the unshifted IDs from the original candidate table. */
    catalog.items[40 + 2 * 16].size = 1;
    catalog.items[45 + 2 * 16].building_tone_cost = -1;
    assert(iw_construct_build_list(&catalog, 2, 0, 2, 8,
                                   items, IW_CONSTRUCT_BUILD_CANDIDATE_COUNT,
                                   &item_count));
    assert(item_count == 6);
    assert(items[0] == 37 && items[1] == 39 && items[2] == 38 &&
           items[3] == 44 && items[4] == 46 && items[5] == 47);

    item_count = 99;
    assert(!iw_construct_build_list(&catalog, 4, 0, 0, 1,
                                    items, IW_CONSTRUCT_BUILD_CANDIDATE_COUNT,
                                    &item_count));
    assert(item_count == 0);
}

static void test_build_list_uses_selected_site_size(void)
{
    static const int32_t small_expected[] = {37, 39, 38, 44};
    PadCatalog catalog;
    IslandLocation site;
    int32_t items[IW_CONSTRUCT_BUILD_CANDIDATE_COUNT];
    size_t item_count;
    uint8_t site_size;
    unsigned int i;

    memset(&catalog, 0, sizeof(catalog));
    catalog.item_count = 101;
    for (i = 0; i < catalog.item_count; ++i) {
        catalog.items[i].item_id = (uint16_t)i;
        catalog.items[i].size = 0;
        catalog.items[i].building_tone_cost = 1;
    }
    catalog.items[40].size = 1;
    memset(&site, 0, sizeof(site));
    site.kind = ISLAND_LOCATION_PAD;
    assert(iw_construct_site_size(&site, &site_size) && site_size == 0);
    site.kind = ISLAND_LOCATION_PAD_SMALL;
    site.renderer_subtype = 0;
    assert(iw_construct_site_size(&site, &site_size) && site_size == 0);
    assert(iw_construct_build_list_for_site(&catalog, 0, &site, 0, 1,
                                            items, IW_CONSTRUCT_BUILD_CANDIDATE_COUNT,
                                            &item_count));
    assert(item_count == sizeof(small_expected) / sizeof(small_expected[0]));
    assert(memcmp(items, small_expected, sizeof(small_expected)) == 0);

    site.kind = ISLAND_LOCATION_PAD_LARGE;
    site.renderer_subtype = 2;
    assert(iw_construct_site_size(&site, &site_size) && site_size == 2);
    site.kind = ISLAND_LOCATION_PAD_MEDIUM;
    site.renderer_subtype = 1;
    assert(iw_construct_site_size(&site, &site_size) && site_size == 1);
    site.renderer_subtype = 3;
    assert(!iw_construct_site_size(&site, &site_size) && site_size == 0);
    site.kind = ISLAND_LOCATION_TONE;
    site.renderer_subtype = 0;
    item_count = 99;
    assert(!iw_construct_build_list_for_site(&catalog, 0, &site, 0, 1,
                                             items, IW_CONSTRUCT_BUILD_CANDIDATE_COUNT,
                                             &item_count));
    assert(item_count == 0);
}

int main(void)
{
    test_hover_click_and_pages();
    test_bounds_and_info_messages();
    test_cycle_button_threshold();
    test_source_build_list_order_and_unlock_rules();
    test_build_list_uses_selected_site_size();
    return 0;
}
