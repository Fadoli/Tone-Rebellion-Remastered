#include "iw_construct.h"

#include <string.h>

int iw_construct_build_list(const PadCatalog *catalog, uint8_t player_slot,
                            int32_t player_size_limit, uint8_t rule_set,
                            uint16_t owned_island_count,
                            int32_t *out_ids, size_t out_capacity,
                            size_t *out_count)
{
    static const uint8_t candidates[IW_CONSTRUCT_BUILD_CANDIDATE_COUNT] = {
        40, 37, 39, 38, 44, 45, 46, 47
    };
    static const uint8_t island_thresholds[3][4] = {
        {1, 2, 20, 3},
        {1, 2, 8, 3},
        {1, 2, 8, 3}
    };
    int32_t result[IW_CONSTRUCT_BUILD_CANDIDATE_COUNT];
    size_t result_count = 0;
    size_t i;

    if (out_count != NULL) *out_count = 0;
    if (catalog == NULL || catalog->item_count < 101 || player_slot >= 4 ||
        rule_set >= 3 || out_ids == NULL || out_capacity < IW_CONSTRUCT_BUILD_CANDIDATE_COUNT ||
        out_count == NULL) return 0;

    for (i = 0; i < IW_CONSTRUCT_BUILD_CANDIDATE_COUNT; ++i) {
        uint16_t base_id = candidates[i];
        uint16_t resolved_id = (uint16_t)(base_id + (uint16_t)player_slot * 16U);
        const PadCatalogItem *item = &catalog->items[resolved_id];

        if (item->size > player_size_limit || item->building_tone_cost == -1) continue;
        if (base_id >= 44 &&
            owned_island_count < island_thresholds[rule_set][base_id - 44]) continue;
        result[result_count++] = base_id;
    }

    memcpy(out_ids, result, result_count * sizeof(result[0]));
    *out_count = result_count;
    return 1;
}

static void clear_transition(IwConstructTransition *transition)
{
    if (transition != NULL) memset(transition, 0, sizeof(*transition));
}

static void emit(IwConstructTransition *transition, uint16_t code, int32_t value)
{
    if (transition == NULL || transition->message_count >= 2) return;
    transition->messages[transition->message_count].code = code;
    transition->messages[transition->message_count].value = value;
    ++transition->message_count;
}

void iw_construct_init(IwConstructState *state, size_t item_count)
{
    if (state == NULL) return;
    state->page = 0;
    state->hovered_column = -1;
    state->hovered_item_id = -1;
    state->cycle_button_visible = item_count > IW_CONSTRUCT_ITEMS_PER_PAGE;
    state->dirty = 1;
}

void iw_construct_mouse_move(IwConstructState *state, const WindowPane *pane,
                             int32_t x, int32_t y,
                             const int32_t *item_ids, size_t item_count,
                             IwConstructTransition *transition)
{
    int32_t column = -1;
    int32_t item_id = -1;
    int32_t width;
    int32_t column_width;
    size_t item_index;
    clear_transition(transition);
    if (state == NULL || pane == NULL) return;

    if (pane->right >= pane->left && pane->bottom >= pane->top &&
        x >= pane->left && x <= pane->right && y >= pane->top + 0x1a &&
        y <= pane->bottom - 10) {
        width = pane->right - pane->left;
        column_width = (width + (width < 0 ? 3 : 0)) / IW_CONSTRUCT_ITEMS_PER_PAGE;
        if (column_width > 0) {
            column = (x - pane->left) / column_width;
            if (column >= 0 && column < IW_CONSTRUCT_ITEMS_PER_PAGE) {
                item_index = (size_t)state->page * IW_CONSTRUCT_ITEMS_PER_PAGE +
                             (size_t)column;
                if (item_ids != NULL && item_index < item_count) {
                    item_id = item_ids[item_index];
                }
            }
        }
    }

    if (column == state->hovered_column) return;
    state->hovered_column = (int16_t)column;
    state->dirty = 1;
    if (item_id == state->hovered_item_id) return;
    state->hovered_item_id = item_id;
    if (transition != NULL) transition->changed = 1;
    emit(transition, IW_CONSTRUCT_MSG_SELECT_HOVER,
         item_id < 0 ? -2 : item_id);
}

void iw_construct_mouse_click(const IwConstructState *state,
                              int32_t tribe_slot,
                              IwConstructTransition *transition)
{
    int32_t item_id;
    clear_transition(transition);
    if (state == NULL || state->hovered_item_id < 0) return;
    item_id = state->hovered_item_id;
    if (item_id > 0x34) item_id -= tribe_slot * 0x10;
    if (transition != NULL) transition->changed = 1;
    emit(transition, IW_CONSTRUCT_MSG_SELECT_BUILD, item_id);
    emit(transition, IW_CONSTRUCT_MSG_CLEAR_BUILD, 0);
}

void iw_construct_build_cycle(IwConstructState *state, size_t item_count,
                              IwConstructTransition *transition)
{
    size_t next_page;
    clear_transition(transition);
    if (state == NULL) return;
    next_page = (size_t)state->page + 1u;
    if (item_count <= next_page * IW_CONSTRUCT_ITEMS_PER_PAGE) next_page = 0;
    state->page = (uint16_t)next_page;
    state->hovered_column = -1;
    state->hovered_item_id = -1;
    state->dirty = 1;
    if (transition != NULL) transition->changed = 1;
    emit(transition, IW_CONSTRUCT_MSG_SELECT_HOVER, -2);
}

void iw_construct_info_init(IwConstructInfoState *state)
{
    if (state == NULL) return;
    state->item_id = -1;
    state->dirty = 1;
}

int iw_construct_info_handle_message(IwConstructInfoState *state,
                                     uint16_t message, int32_t value)
{
    if (state == NULL) return 0;
    if (message == 1) {
        state->item_id = -1;
        state->dirty = 1;
        return 1;
    }
    if (message == IW_CONSTRUCT_INFO_MSG_ITEM) {
        state->item_id = value;
        state->dirty = 1;
        return 1;
    }
    return 0;
}

const PadCatalogItem *iw_construct_info_item(const IwConstructInfoState *state,
                                             const PadCatalog *catalog)
{
    if (state == NULL || state->item_id < 0 ||
        state->item_id > (int32_t)UINT16_MAX) return NULL;
    return pad_catalog_find(catalog, (uint16_t)state->item_id);
}
