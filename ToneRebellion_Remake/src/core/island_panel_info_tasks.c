#include "island_panel_info.h"

#include <limits.h>
#include <stdio.h>
#include <string.h>

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

int island_panel_info_task_row(int16_t action_type, int16_t item_id,
                               IslandTaskRow *row)
{
    IslandTaskRow value;
    if (row == NULL) return 0;
    value.label_key = NULL;
    value.task_icon_frame = -1;
    value.secondary_task_icon_frame = -1;
    value.resource_icon_type = -1;
    if (action_type == 5) {
        value.label_key = "CONSTR";
        value.task_icon_frame = 0;
    } else if (action_type == 0x12) {
        value.label_key = "REPAIR";
        value.task_icon_frame = 1;
    } else if (action_type == 4 && item_id >= 5 && item_id < 0x22) {
        value.label_key = "DARTIFACT";
        value.task_icon_frame = 4;
    } else if (action_type == 0xd) {
        value.label_key = "OARTIFACT";
        value.task_icon_frame = 4;
    } else {
        return 0;
    }
    *row = value;
    return 1;
}

int island_panel_info_stock_task_row(unsigned int resource_type,
                                     IslandTaskRow *row)
{
    if (row == NULL || resource_type >= 3) return 0;
    row->label_key = "STOCK";
    row->task_icon_frame = 3;
    row->secondary_task_icon_frame = 7;
    row->resource_icon_type = (int8_t)resource_type;
    return 1;
}

int island_panel_info_stock_gauge_fill(uint16_t stock,
                                       int16_t source_field_4a,
                                       unsigned int gauge_width,
                                       unsigned int *fill_width)
{
    int32_t denominator;
    uint64_t scaled;
    if (fill_width == NULL) return 0;
    denominator = (int32_t)source_field_4a * 50 + 150;
    if (denominator <= 0) return 0;
    if ((int32_t)stock >= denominator) {
        *fill_width = gauge_width;
        return 1;
    }
    scaled = (uint64_t)stock * gauge_width;
    *fill_width = (unsigned int)((scaled + (uint32_t)denominator / 2U) /
                                 (uint32_t)denominator);
    return 1;
}

int island_panel_info_task_gauge_fill(int16_t current, int16_t maximum,
                                      unsigned int gauge_width,
                                      unsigned int *fill_width)
{
    uint64_t scaled;
    uint64_t denominator;
    uint64_t whole;
    uint64_t remainder;
    if (fill_width == NULL || current < 0 || maximum <= 0) return 0;
    if (current >= maximum) {
        *fill_width = gauge_width;
        return 1;
    }
    scaled = (uint64_t)(uint16_t)current * gauge_width;
    denominator = (uint16_t)maximum;
    whole = scaled / denominator;
    remainder = scaled % denominator;
    /* FUN_004118df converts ratio*width through x87 __ftol (nearest, ties
       to even under the default Windows rounding mode). */
    if (remainder * 2U > denominator ||
        (remainder * 2U == denominator && (whole & 1U) != 0)) ++whole;
    *fill_width = (unsigned int)whole;
    return 1;
}

#include "island_panel_info.h"

#include <limits.h>
#include <stdio.h>
#include <string.h>

int island_panel_info_task_row_position(const WindowTemplate *panel,
                                       unsigned int visible_rows,
                                       unsigned int visible_index,
                                       IslandTaskRowPosition *position)
{
    int height;
    int row_y;
    if (panel == NULL || position == NULL || visible_rows == 0 ||
        visible_index >= visible_rows || visible_rows > INT_MAX / 13) return 0;
    height = panel->pane.bottom - panel->pane.top;
    if (height <= 0) return 0;
    row_y = (height - (int)visible_rows * 13) / 2 + (int)visible_index * 13;
    if (row_y < INT16_MIN || row_y > INT16_MAX) return 0;
    position->icon_x = 25;
    position->label_x = 45;
    position->secondary_icon_x = 150;
    position->resource_icon_x = 135;
    position->y = (int16_t)row_y;
    return 1;
}

int island_panel_info_task_highlight_position(const WindowTemplate *panel,
                                              unsigned int visible_rows,
                                              unsigned int visible_index,
                                              int *top, int *height)
{
    IslandTaskRowPosition row;
    if (top == NULL || height == NULL ||
        !island_panel_info_task_row_position(panel, visible_rows,
                                             visible_index, &row)) return 0;
    *top = row.y - 3;
    *height = 13;
    return 1;
}

int island_panel_info_task_index_at_y(const WindowTemplate *panel,
                                      int32_t y,
                                      unsigned int visible_rows,
                                      int scroll_offset,
                                      size_t task_count)
{
    int height;
    int row_origin;
    int64_t row_index;
    int64_t row_offset;
    if (panel == NULL || visible_rows == 0 || visible_rows > INT_MAX / 13 ||
        task_count > INT_MAX) return -1;
    height = panel->pane.bottom - panel->pane.top;
    if (height <= 0) return -1;
    row_origin = (height - (int)visible_rows * 13) / 2;
    row_index = ((int64_t)y - panel->pane.top - row_origin) / 13;
    if (row_index < 0) row_index = 0;
    row_offset = scroll_offset < 0 ? 0 : scroll_offset;
    row_index += row_offset;
    return row_index < (int64_t)task_count ? (int)row_index : -1;
}

const char *island_panel_info_task_priority_key(int16_t priority)
{
    if (priority == 2) return "THIGH";
    if (priority == 3) return "TEXCL";
    return "TNORM";
}

int island_panel_info_task_transfer_keys(int16_t action_type, int16_t item_id,
                                         const char **title_key,
                                         const char **category_key)
{
    const char *title;
    const char *category = NULL;
    if (action_type == 4) title = "DELIVER";
    else if (action_type == 0xd) title = "RETRIEVE";
    else return 0;

    if (item_id == 1) category = "STONE";
    else if (item_id == 2) category = "CTONE";
    else if (item_id == 3) category = "MTONE";
    else if (item_id >= 5 && item_id < 0x22) category = "ARTIFACT";
    if (title_key != NULL) *title_key = title;
    if (category_key != NULL) *category_key = category;
    return 1;
}

int island_panel_info_task_artifact_frame(int16_t item_id)
{
    if (item_id < 5 || item_id >= 0x22) return -1;
    return item_id - 5;
}

int island_panel_info_task_icon_position(const WindowTemplate *panel,
                                         int frame_x_offset,
                                         int frame_y_offset,
                                         int opaque_left, int opaque_top,
                                         int opaque_right, int opaque_bottom,
                                         int extra_x, int *draw_x, int *draw_y)
{
    int width;
    int height;
    int opaque_width;
    int opaque_height;
    if (panel == NULL || draw_x == NULL || draw_y == NULL ||
        opaque_right < opaque_left || opaque_bottom < opaque_top) return 0;
    width = panel->pane.right - panel->pane.left;
    height = panel->pane.bottom - panel->pane.top;
    if (width <= 0 || height <= 0) return 0;
    /* FUN_004119ba centers endpoint differences (without the +1 used by
       the Inventory grid's distinct FUN_0043d6a3 layout). */
    opaque_width = opaque_right - opaque_left;
    opaque_height = opaque_bottom - opaque_top;
    *draw_x = panel->pane.left + (width - opaque_width) / 2 -
        opaque_left - frame_x_offset + extra_x;
    *draw_y = panel->pane.top + (height - opaque_height) / 2 -
        opaque_top - frame_y_offset;
    return 1;
}

int island_panel_info_task_target_preview_position(const WindowTemplate *panel,
                                                   int16_t action_type,
                                                   int32_t owner_id,
                                                   int *draw_x, int *draw_y)
{
    if (panel == NULL || draw_x == NULL || draw_y == NULL ||
        (action_type != 4 && action_type != 0xd) || owner_id != 0 ||
        panel->pane.right - panel->pane.left < 0x1e ||
        panel->pane.bottom - panel->pane.top < 10) return 0;
    *draw_x = panel->pane.right - 0x1e;
    *draw_y = panel->pane.bottom - 10;
    return 1;
}

int island_panel_info_construction_task_indices(int16_t item_id,
                                                uint8_t player_slot,
                                                uint16_t *catalog_item_id,
                                                size_t *building_name_index)
{
    size_t index;
    if (item_id < 0x25 || item_id >= 0x35 || player_slot >= 4 ||
        catalog_item_id == NULL || building_name_index == NULL) return 0;
    index = (size_t)player_slot * 16U + (size_t)(item_id - 0x25);
    *catalog_item_id = (uint16_t)(0x25U + index);
    *building_name_index = index;
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
                {
                    size_t comment;
                    for (comment = text_start; comment + 1 < text_end; ++comment) {
                        if (bytes[comment] == '/' && bytes[comment + 1] == '/') {
                            text_end = comment;
                            break;
                        }
                    }
                }
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
