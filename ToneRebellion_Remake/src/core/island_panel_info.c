#include "island_panel_info.h"

#include <stdio.h>
#include <string.h>

void island_panel_select_floater(IslandPanelSelection *selection,
                                int32_t floater_index)
{
    if (selection == NULL) return;
    selection->floater_index = floater_index;
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
                                             int selected_item_id)
{
    if (info_mode != ISLAND_PANEL_INFO_INVENTORY_DETAIL ||
        selected_item_id < 5 || selected_item_id > 33) return -1;
    return selected_item_id - 5;
}

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

int island_panel_info_empty_task_label_position(const WindowTemplate *panel,
                                               int text_width,
                                               int *x, int *y)
{
    int width;
    if (panel == NULL || x == NULL || y == NULL || text_width < 0) return 0;
    width = panel->pane.right - panel->pane.left;
    if (width <= 0) return 0;
    /* FUN_004469d6 measures NOTASKS, centers it in the task pane, and draws
       it at local y=0x32. */
    *x = panel->pane.left + (width - text_width) / 2;
    *y = panel->pane.top + 0x32;
    return 1;
}

int island_panel_info_extract_entry(const unsigned char *bytes, size_t length,
                                    const char *key,
                                    char *output, size_t output_capacity)
{
    size_t cursor = 0;
    size_t key_length;

    if (bytes == NULL || key == NULL || output == NULL || output_capacity == 0) {
        return 0;
    }
    output[0] = '\0';
    key_length = strlen(key);
    while (cursor < length) {
        size_t line_start = cursor;
        size_t line_end;
        while (cursor < length && bytes[cursor] != '\n') ++cursor;
        line_end = cursor;
        if (line_end > line_start && bytes[line_end - 1] == '\r') --line_end;
        while (line_end > line_start &&
               (bytes[line_end - 1] == ' ' || bytes[line_end - 1] == '\t')) {
            --line_end;
        }
        if (line_end - line_start == key_length &&
            memcmp(bytes + line_start, key, key_length) == 0) {
            size_t used = 0;
            if (cursor < length) ++cursor;
            while (cursor < length) {
                size_t text_start = cursor;
                size_t text_end;
                size_t count;
                while (cursor < length && bytes[cursor] != '\n') ++cursor;
                text_end = cursor;
                if (text_end > text_start && bytes[text_end - 1] == '\r') --text_end;
                if (text_end - text_start >= 3 &&
                    memcmp(bytes + text_start, "END", 3) == 0) {
                    output[used] = '\0';
                    return used != 0;
                }
                count = text_end - text_start;
                while (count > 0 && (bytes[text_start] == ' ' ||
                                     bytes[text_start] == '\t')) {
                    ++text_start;
                    --count;
                }
                while (count > 0 && (bytes[text_start + count - 1] == ' ' ||
                                     bytes[text_start + count - 1] == '\t')) --count;
                if (count != 0) {
                    if (used != 0 && used + 1 < output_capacity) output[used++] = ' ';
                    if (count >= output_capacity - used) {
                        count = output_capacity - used - 1;
                    }
                    memcpy(output + used, bytes + text_start, count);
                    used += count;
                }
                if (cursor < length) ++cursor;
            }
            output[0] = '\0';
            return 0;
        }
        if (cursor < length) ++cursor;
    }
    return 0;
}
