#ifndef TONE_REBELLION_ISLAND_PANEL_INFO_H
#define TONE_REBELLION_ISLAND_PANEL_INFO_H

#include "window_catalog.h"

#include <stddef.h>
#include <stdint.h>

enum {
    ISLAND_PANEL_INFO_INVENTORY_DETAIL = 2,
    ISLAND_PANEL_INFO_CRYPTIC = 5,
    ISLAND_PANEL_INFO_INVENTORY_DEFAULT = 6,
    ISLAND_PANEL_INFO_CRYPTIC_COUNT = 21,
    ISLAND_PANEL_INFO_HALL_RESOURCE_COUNT = 3,
    ISLAND_PANEL_INFO_ROSTER_SLOT_COUNT = 6
};

typedef struct IslandHallResourceRow {
    uint8_t icon_frame;
    int16_t icon_x;
    int16_t icon_y;
    int16_t amount_x;
    int16_t amount_y;
} IslandHallResourceRow;

typedef struct IslandTaskRow {
    const char *label_key;
    int8_t task_icon_frame;
    int8_t secondary_task_icon_frame;
    int8_t resource_icon_type;
} IslandTaskRow;

typedef struct IslandTaskRowPosition {
    int16_t icon_x;
    int16_t label_x;
    int16_t secondary_icon_x;
    int16_t resource_icon_x;
    int16_t y;
} IslandTaskRowPosition;

typedef enum IslandLocationActionControl {
    ISLAND_LOCATION_ACTION_NONE = 0,
    ISLAND_LOCATION_ACTION_MOVE = 1,
    ISLAND_LOCATION_ACTION_HALL_MOVE = 2
} IslandLocationActionControl;

typedef struct IslandPanelSelection {
    int32_t location_index;
    int32_t floater_index;
} IslandPanelSelection;

/* FUN_0042fa0f handles floater-selection message 0x3f by replacing only the
   selected-floater pointer; its selected-location pointer remains intact. */
void island_panel_select_floater(IslandPanelSelection *selection,
                                int32_t floater_index);

/* FUN_0042fa0f's map-click path clears the selected inventory item and
   returns to panel mode 0 after an inventory-target attempt. */
void island_panel_finish_inventory_target(int *panel_mode,
                                          int *selected_item_id,
                                          int *hovered_item_id,
                                          int *hovered_command_mode);

/* FUN_00440567 and FUN_00440451 use these six IWLocInfo-relative anchors.
   Their hit boxes are strict 15-pixel half-width/height rectangles, and the
   source item ID 0x2f selects a separate anchor table. */
int island_panel_info_roster_position(unsigned int slot, int special_layout,
                                      int *x, int *y);
int island_panel_info_roster_hit_test(int32_t pane_x, int32_t pane_y,
                                      int32_t x, int32_t y,
                                      int special_layout,
                                      uint8_t occupied_slots);

/* Default IWTextInfo descriptions selected when these Hall panels open. */
const char *island_panel_info_default_key(int panel_mode);

/* FUN_00439673 formats Inventory hover IDs 5..33 as BRIDGE00/PLOT00..27. */
int island_panel_info_inventory_key(unsigned int item_id,
                                    char *output, size_t output_capacity);
/* FUN_0043d45c sends the selected ID to IWTextInfo mode 2; selection is
   separate from the current pointer hover. Returns the text-array index. */
int island_panel_info_inventory_detail_index(int info_mode,
                                             int selected_item_id);

/* FUN_0042f150 loads CRYPTIC0..20; FUN_00439673 uses these in mode 5. */
int island_panel_info_cryptic_key(unsigned int cryptic_id,
                                  char *output, size_t output_capacity);

/* FUN_0044003d shows a move control only for an owned, nonempty location.
   Item 0x2a selects the Hall-specific control; item 0x28 suppresses it. */
IslandLocationActionControl island_panel_location_action_control(
    int32_t item_id, int32_t owner_id, int32_t current_player_id);

/* FUN_0044338b places the selected location sprite inside IWLocInfo using
   the pane width/height-relative anchor recovered from its draw call. */
int island_panel_info_building_sprite_position(const WindowTemplate *panel,
                                               int *x, int *y);

/* FUN_00440567 draws the three Hall stock icons and short counters in
   IWLocInfo-relative coordinates. */
int island_panel_info_hall_resource_row(unsigned int resource,
                                        IslandHallResourceRow *row);

/* FUN_004469d6 centers NOTASKS in IWTaskInfo at pane-local y=50 when no task
   reference is selected. */
int island_panel_info_empty_task_label_position(const WindowTemplate *panel,
                                               int text_width,
                                               int *x, int *y);

/* FUN_004459e6 row branches with explicit gamey.txt labels and taskicon frames. */
int island_panel_info_task_row(int16_t action_type, int16_t item_id,
                               IslandTaskRow *row);
/* FUN_004459e6's Hall-reserve request row uses TASKICON frames 3 and 7 and
   one of the three resource shapes. */
int island_panel_info_stock_task_row(unsigned int resource_type,
                                     IslandTaskRow *row);
/* FUN_004459e6 uses stock / (short(Hall+0x4a) * 50 + 150), capped at 1,
   for the TASKICON frame-9 gauge. Returns false for a nonpositive divisor. */
int island_panel_info_stock_gauge_fill(uint16_t stock,
                                       int16_t source_field_4a,
                                       unsigned int gauge_width,
                                       unsigned int *fill_width);
/* FUN_004459e6 centers visible 13px rows vertically and draws the icon at x=25,
   label at x=45; returned y is the pane-local row origin. */
int island_panel_info_task_row_position(const WindowTemplate *panel,
                                       unsigned int visible_rows,
                                       unsigned int visible_index,
                                       IslandTaskRowPosition *position);
/* FUN_0044590d's 13px row lookup, including its negative-index clamp and
   source-slot scroll offset. Returns -1 when the projected index is absent. */
int island_panel_info_task_index_at_y(const WindowTemplate *panel,
                                      int32_t y,
                                      unsigned int visible_rows,
                                      int scroll_offset,
                                      size_t task_count);
/* FUN_004469d6 priority and transfer-detail keys. category_key may be NULL. */
const char *island_panel_info_task_priority_key(int16_t priority);
int island_panel_info_task_transfer_keys(int16_t action_type, int16_t item_id,
                                         const char **title_key,
                                         const char **category_key);
/* FUN_004469d6/FUN_004119ba centers the transfer icon's opaque bounds in
   IWTaskInfo; the source adds a 10px x offset for resource IDs 1..3. */
int island_panel_info_task_icon_position(const WindowTemplate *panel,
                                         int frame_x_offset,
                                         int frame_y_offset,
                                         int opaque_left, int opaque_top,
                                         int opaque_right, int opaque_bottom,
                                         int extra_x, int *draw_x, int *draw_y);
/* FUN_004469d6 normalizes construction task IDs from 0x25..0x34 and indexes
   the 16-entry BLDNAME block for the task's player. */
int island_panel_info_construction_task_indices(int16_t item_id,
                                                uint8_t player_slot,
                                                uint16_t *catalog_item_id,
                                                size_t *building_name_index);

/* Reads one key-delimited text entry, trimming horizontal whitespace on keys. */
int island_panel_info_extract_entry(const unsigned char *bytes, size_t length,
                                    const char *key,
                                    char *output, size_t output_capacity);

#endif
