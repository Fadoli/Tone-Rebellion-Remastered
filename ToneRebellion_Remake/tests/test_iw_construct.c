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

int main(void)
{
    test_hover_click_and_pages();
    test_bounds_and_info_messages();
    test_cycle_button_threshold();
    return 0;
}
