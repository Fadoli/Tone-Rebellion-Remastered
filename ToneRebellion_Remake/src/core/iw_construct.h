#ifndef TONE_REBELLION_IW_CONSTRUCT_H
#define TONE_REBELLION_IW_CONSTRUCT_H

#include "pad_catalog.h"
#include "window_catalog.h"

#include <stddef.h>
#include <stdint.h>

enum {
    IW_CONSTRUCT_ITEMS_PER_PAGE = 4,
    IW_CONSTRUCT_MSG_SELECT_HOVER = 0x3c,
    IW_CONSTRUCT_MSG_SELECT_BUILD = 0x34,
    IW_CONSTRUCT_MSG_CLEAR_BUILD = 0x33,
    IW_CONSTRUCT_MSG_BUILD_CYCLE = 0x45,
    IW_CONSTRUCT_INFO_MSG_ITEM = 0x9a4
};

typedef struct IwConstructMessage {
    uint16_t code;
    int32_t value;
} IwConstructMessage;

typedef struct IwConstructTransition {
    uint8_t changed;
    uint8_t message_count;
    IwConstructMessage messages[2];
} IwConstructTransition;

typedef struct IwConstructState {
    uint16_t page;
    int16_t hovered_column;
    int32_t hovered_item_id;
    uint8_t cycle_button_visible;
    uint8_t dirty;
} IwConstructState;

typedef struct IwConstructInfoState {
    int32_t item_id;
    uint8_t dirty;
} IwConstructInfoState;

/* State and event codes follow Ghidra's FUN_0043aa9f, FUN_0043ad79,
   FUN_0043acea, and FUN_0043b2d1 observations. `item_ids` is the active
   player's ordered build list supplied by game state; it is not synthesized
   from every record in pad.txt. */
void iw_construct_init(IwConstructState *state, size_t item_count);
void iw_construct_mouse_move(IwConstructState *state, const WindowPane *pane,
                             int32_t x, int32_t y,
                             const int32_t *item_ids, size_t item_count,
                             IwConstructTransition *transition);
void iw_construct_mouse_click(const IwConstructState *state,
                              int32_t tribe_slot,
                              IwConstructTransition *transition);
void iw_construct_build_cycle(IwConstructState *state, size_t item_count,
                              IwConstructTransition *transition);

void iw_construct_info_init(IwConstructInfoState *state);
int iw_construct_info_handle_message(IwConstructInfoState *state,
                                     uint16_t message, int32_t value);
const PadCatalogItem *iw_construct_info_item(const IwConstructInfoState *state,
                                             const PadCatalog *catalog);

#endif
