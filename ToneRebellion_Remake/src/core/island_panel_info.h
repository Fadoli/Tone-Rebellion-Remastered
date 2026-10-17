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

/* Reads one key-delimited text entry, trimming horizontal whitespace on keys. */
int island_panel_info_extract_entry(const unsigned char *bytes, size_t length,
                                    const char *key,
                                    char *output, size_t output_capacity);

#endif
