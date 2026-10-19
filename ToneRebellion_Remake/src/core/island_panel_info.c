#include "island_panel_info.h"
#include "game_start.h"

#include <limits.h>
#include <stdio.h>
#include <string.h>

void island_panel_select_floater(IslandPanelSelection *selection,
                                int32_t floater_index)
{
    if (selection == NULL) return;
    selection->floater_index = floater_index;
}

int island_panel_player_for_mode(int panel_mode, int active_player,
                                 int selected_hall_player)
{
    if (panel_mode == WINDOW_ISLAND_PANEL_TASKS) {
        return active_player >= 0 && active_player < GAME_START_PLAYER_COUNT
            ? active_player : -1;
    }
    return selected_hall_player;
}

int island_panel_repair_button_visible(int item_id, int owner_id,
                                       int current_player_id,
                                       int current_hit_points,
                                       int maximum_hit_points)
{
    int player_item_id;
    if (current_player_id < 0 || current_player_id >= GAME_START_PLAYER_COUNT ||
        owner_id != current_player_id || current_hit_points < 0 ||
        maximum_hit_points <= 0 || current_hit_points >= maximum_hit_points) {
        return 0;
    }
    player_item_id = item_id - owner_id * 16;
    return player_item_id >= 0x25 && player_item_id <= 0x34;
}

int island_panel_onoff_button_visible(int item_id, int renderer_class,
                                      int owner_id, int current_player_id)
{
    return current_player_id >= 0 && current_player_id < GAME_START_PLAYER_COUNT &&
        renderer_class == 0 && owner_id == current_player_id &&
        item_id - owner_id * 16 >= 0x25 && item_id - owner_id * 16 <= 0x27;
}

void island_panel_finish_inventory_target(int *panel_mode,
                                          int *selected_item_id,
                                          int *hovered_item_id,
                                          int *hovered_command_mode)
{
    if (panel_mode != NULL) *panel_mode = WINDOW_ISLAND_PANEL_GENERAL;
    if (selected_item_id != NULL) *selected_item_id = -1;
    if (hovered_item_id != NULL) *hovered_item_id = -1;
    if (hovered_command_mode != NULL) *hovered_command_mode =
        WINDOW_ISLAND_PANEL_NONE;
}

int island_panel_info_roster_position(unsigned int slot, int special_layout,
                                      int *x, int *y)
{
    static const int normal_x[ISLAND_PANEL_INFO_ROSTER_SLOT_COUNT] =
        {230, 230, 230, 195, 195, 160};
    static const int normal_y[ISLAND_PANEL_INFO_ROSTER_SLOT_COUNT] =
        {21, 55, 89, 35, 72, 55};
    static const int special_x[ISLAND_PANEL_INFO_ROSTER_SLOT_COUNT] =
        {220, 999, 999, 220, 999, 170};
    static const int special_y[ISLAND_PANEL_INFO_ROSTER_SLOT_COUNT] =
        {28, 999, 999, 82, 999, 55};

    if (slot >= ISLAND_PANEL_INFO_ROSTER_SLOT_COUNT || x == NULL || y == NULL) {
        return 0;
    }
    *x = special_layout ? special_x[slot] : normal_x[slot];
    *y = special_layout ? special_y[slot] : normal_y[slot];
    return 1;
}

int island_panel_info_roster_hit_test(int32_t pane_x, int32_t pane_y,
                                      int32_t x, int32_t y,
                                      int special_layout,
                                      uint8_t occupied_slots)
{
    unsigned int slot;
    for (slot = 0; slot < ISLAND_PANEL_INFO_ROSTER_SLOT_COUNT; ++slot) {
        int anchor_x;
        int anchor_y;
        int64_t dx;
        int64_t dy;
        if ((occupied_slots & (uint8_t)(1u << slot)) == 0 ||
            !island_panel_info_roster_position(slot, special_layout,
                                               &anchor_x, &anchor_y) ||
            anchor_x == 999 || anchor_y == 999) {
            continue;
        }
        dx = (int64_t)x - pane_x - anchor_x;
        dy = (int64_t)y - pane_y - anchor_y;
        if (dx < 0) dx = -dx;
        if (dy < 0) dy = -dy;
        if (dx < 15 && dy < 15) return (int)slot;
    }
    return -1;
}

#include "island_panel_info.h"

#include <limits.h>
#include <stdio.h>
#include <string.h>

int island_panel_info_cryptic_key(unsigned int cryptic_id,
                                  char *output, size_t output_capacity)
{
    int written;
    if (output == NULL || output_capacity == 0) return 0;
    output[0] = '\0';
    if (cryptic_id >= ISLAND_PANEL_INFO_CRYPTIC_COUNT) return 0;
    written = snprintf(output, output_capacity, "CRYPTIC%u", cryptic_id);
    if (written < 0 || (size_t)written >= output_capacity) {
        output[0] = '\0';
        return 0;
    }
    return 1;
}

IslandLocationActionControl island_panel_location_action_control(
    int32_t item_id, int32_t owner_id, int32_t current_player_id)
{
    if (current_player_id < 0 || owner_id != current_player_id ||
        item_id == 0 || item_id == 1 || item_id == 0x28) {
        return ISLAND_LOCATION_ACTION_NONE;
    }
    return item_id == 0x2a ? ISLAND_LOCATION_ACTION_HALL_MOVE
                           : ISLAND_LOCATION_ACTION_MOVE;
}

const char *island_panel_info_default_key(int panel_mode)
{
    switch (panel_mode) {
    case WINDOW_ISLAND_PANEL_INVENTORY:
        return "COLLART";
    case WINDOW_ISLAND_PANEL_GLYPHS:
        return "GLYSTONE";
    default:
        return NULL;
    }
}

int island_panel_info_inventory_key(unsigned int item_id,
                                    char *output, size_t output_capacity)
{
    const char *prefix;
    unsigned int suffix;
    int written;

    if (output == NULL || output_capacity == 0) return 0;
    output[0] = '\0';
    if (item_id == 5) {
        prefix = "BRIDGE";
        suffix = 0;
    } else if (item_id >= 6 && item_id <= 33) {
        prefix = "PLOT";
        suffix = item_id - 6;
    } else {
        return 0;
    }
    written = snprintf(output, output_capacity, "%s%02u", prefix, suffix);
    if (written < 0 || (size_t)written >= output_capacity) {
        output[0] = '\0';
        return 0;
    }
    return 1;
}

int island_panel_info_inventory_detail_index(int info_mode,
                                             int hovered_item_id)
{
    if (info_mode != ISLAND_PANEL_INFO_INVENTORY_DETAIL ||
        hovered_item_id < 5 || hovered_item_id > 33) return -1;
    return hovered_item_id - 5;
}

#include "island_panel_info.h"

#include <limits.h>
#include <stdio.h>
#include <string.h>

int island_panel_info_building_sprite_position(const WindowTemplate *panel,
                                               int *x, int *y)
{
    int width;
    int height;

    if (panel == NULL || x == NULL || y == NULL) return 0;
    width = panel->pane.right - panel->pane.left;
    height = panel->pane.bottom - panel->pane.top;
    if (width <= 0 || height <= 0) return 0;
    /* FUN_0044338b passes (pane width - 0x32, pane height / 2 + 5)
       to FUN_0042704b; that renderer's coordinates are pane-local. */
    *x = panel->pane.left + width - 0x32;
    *y = panel->pane.top + height / 2 + 5;
    return 1;
}

int island_panel_info_hall_resource_row(unsigned int resource,
                                        IslandHallResourceRow *row)
{
    static const IslandHallResourceRow rows[ISLAND_PANEL_INFO_HALL_RESOURCE_COUNT] = {
        {24, 41, 40, 53, 34},
        {4, 41, 70, 53, 63},
        {4, 41, 97, 53, 90}
    };

    if (resource >= ISLAND_PANEL_INFO_HALL_RESOURCE_COUNT || row == NULL) return 0;
    *row = rows[resource];
    return 1;
}
