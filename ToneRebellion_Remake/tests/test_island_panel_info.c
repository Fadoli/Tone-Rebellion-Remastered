#include "island_panel_info.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    char key[16];
    char description[768];
    int sprite_x;
    int sprite_y;
    int roster_x;
    int roster_y;
    int task_label_x;
    int task_label_y;
    int task_icon_x;
    int task_icon_y;
    unsigned int gauge_fill;
    uint16_t construction_catalog_item_id;
    size_t construction_name_index;
    IslandHallResourceRow resource_row;
    IslandTaskRow task_row;
    IslandTaskRowPosition task_position;
    const char *task_title_key;
    const char *task_category_key;
    WindowTemplate info_panel = {0};
    IslandPanelSelection panel_selection = {7, -1};
    int panel_mode = WINDOW_ISLAND_PANEL_INVENTORY;
    int selected_inventory_item = 12;
    int hovered_inventory_item = 12;
    int hovered_command = WINDOW_ISLAND_PANEL_INVENTORY;
    static const unsigned char plot04[] =
        "PLOT03\r\nOther entry\r\nEND\r\n"
        "PLOT04 \r\nLanterne d'ether\r\n emits light. \r\nEND\r\n";
    static const unsigned char diplomacy_captions[] =
        "TRDIPHI\r\nAmis/Ennemis\r\nEND\r\n"
        "TRCOMHI\r\nCommuniquer ?\r\nEND\r\n";

    assert(strcmp(island_panel_info_default_key(WINDOW_ISLAND_PANEL_INVENTORY),
                  "COLLART") == 0);
    assert(strcmp(island_panel_info_default_key(WINDOW_ISLAND_PANEL_GLYPHS),
                  "GLYSTONE") == 0);
    assert(island_panel_info_default_key(WINDOW_ISLAND_PANEL_DIPLOMACY) == NULL);
    assert(island_panel_info_default_key(WINDOW_ISLAND_PANEL_TRADE) == NULL);
    assert(island_panel_info_default_key(WINDOW_ISLAND_PANEL_GENERAL) == NULL);
    assert(island_panel_player_for_mode(WINDOW_ISLAND_PANEL_TASKS, 2, -1) == 2);
    assert(island_panel_player_for_mode(WINDOW_ISLAND_PANEL_TASKS, 4, -1) == -1);
    assert(island_panel_player_for_mode(WINDOW_ISLAND_PANEL_GLYPHS, 2, -1) == -1);
    assert(island_panel_player_for_mode(WINDOW_ISLAND_PANEL_GLYPHS, 2, 2) == 2);
    assert(island_panel_repair_button_visible(0x25, 0, 0, 9, 10));
    assert(island_panel_repair_button_visible(0x35, 1, 1, 9, 10));
    assert(!island_panel_repair_button_visible(0x25, 0, 0, 10, 10));
    assert(!island_panel_repair_button_visible(0x25, 1, 0, 9, 10));
    assert(!island_panel_repair_button_visible(0x24, 0, 0, 9, 10));
    assert(!island_panel_repair_button_visible(0x35, 1, 1, 10, 10));
    assert(island_panel_onoff_button_visible(0x25, 0, 0, 0));
    assert(island_panel_onoff_button_visible(0x26, 0, 1, 1));
    assert(island_panel_onoff_button_visible(0x27, 0, 3, 3));
    assert(!island_panel_onoff_button_visible(0x24, 0, 0, 0));
    assert(!island_panel_onoff_button_visible(0x28, 0, 0, 0));
    assert(!island_panel_onoff_button_visible(0x25, 1, 0, 0));
    assert(!island_panel_onoff_button_visible(0x25, 2, 0, 0));
    assert(!island_panel_onoff_button_visible(0x25, 3, 0, 0));
    assert(!island_panel_onoff_button_visible(0x25, 0, 1, 0));
    assert(!island_panel_onoff_button_visible(0x25, 0, 4, 4));
    assert(!island_panel_onoff_button_visible(0x25, 0, 0, -1));
    assert(island_panel_info_cryptic_key(0, key, sizeof(key)));
    assert(strcmp(key, "CRYPTIC0") == 0);
    assert(island_panel_info_cryptic_key(1, key, sizeof(key)));
    assert(strcmp(key, "CRYPTIC1") == 0);
    assert(island_panel_info_cryptic_key(20, key, sizeof(key)));
    assert(strcmp(key, "CRYPTIC20") == 0);
    assert(!island_panel_info_cryptic_key(21, key, sizeof(key)));
    assert(!island_panel_info_cryptic_key(1, key, 8));
    assert(island_panel_location_action_control(0x25, 2, 2) ==
           ISLAND_LOCATION_ACTION_MOVE);
    assert(island_panel_location_action_control(0x2a, 2, 2) ==
           ISLAND_LOCATION_ACTION_HALL_MOVE);
    assert(island_panel_location_action_control(0x28, 2, 2) ==
           ISLAND_LOCATION_ACTION_NONE);
    assert(island_panel_location_action_control(0x25, 1, 2) ==
           ISLAND_LOCATION_ACTION_NONE);
    assert(island_panel_location_action_control(0, 2, 2) ==
           ISLAND_LOCATION_ACTION_NONE);
    assert(island_panel_location_action_control(1, 2, 2) ==
           ISLAND_LOCATION_ACTION_NONE);
    assert(island_panel_location_action_control(0x25, 2, -1) ==
           ISLAND_LOCATION_ACTION_NONE);
    island_panel_select_floater(&panel_selection, 3);
    assert(panel_selection.location_index == 7);
    assert(panel_selection.floater_index == 3);
    island_panel_select_floater(NULL, 9);
    island_panel_finish_inventory_target(&panel_mode, &selected_inventory_item,
                                         &hovered_inventory_item,
                                         &hovered_command);
    assert(panel_mode == WINDOW_ISLAND_PANEL_GENERAL);
    assert(selected_inventory_item == -1 && hovered_inventory_item == -1);
    assert(hovered_command == WINDOW_ISLAND_PANEL_NONE);
    island_panel_finish_inventory_target(NULL, NULL, NULL, NULL);
    assert(island_panel_info_roster_position(0, 0, &roster_x, &roster_y));
    assert(roster_x == 230 && roster_y == 21);
    assert(island_panel_info_roster_position(3, 0, &roster_x, &roster_y));
    assert(roster_x == 195 && roster_y == 35);
    assert(island_panel_info_roster_position(0, 1, &roster_x, &roster_y));
    assert(roster_x == 220 && roster_y == 28);
    assert(island_panel_info_roster_position(5, 1, &roster_x, &roster_y));
    assert(roster_x == 170 && roster_y == 55);
    assert(!island_panel_info_roster_position(6, 0, &roster_x, &roster_y));
    assert(island_panel_info_task_row(5, 0, &task_row));
    assert(strcmp(task_row.label_key, "CONSTR") == 0 &&
           task_row.task_icon_frame == 0);
    assert(island_panel_info_task_row(0x12, 0, &task_row));
    assert(strcmp(task_row.label_key, "REPAIR") == 0 &&
           task_row.task_icon_frame == 1);
    assert(island_panel_info_task_row(4, 5, &task_row));
    assert(strcmp(task_row.label_key, "DARTIFACT") == 0 &&
           task_row.task_icon_frame == 4);
    assert(island_panel_info_task_row(4, 33, &task_row));
    assert(!island_panel_info_task_row(4, 34, &task_row));
    assert(island_panel_info_stock_task_row(0, &task_row));
    assert(strcmp(task_row.label_key, "STOCK") == 0 &&
           task_row.task_icon_frame == 3 &&
           task_row.secondary_task_icon_frame == 7 &&
           task_row.resource_icon_type == 0);
    assert(island_panel_info_stock_task_row(2, &task_row));
    assert(task_row.resource_icon_type == 2);
    assert(!island_panel_info_stock_task_row(3, &task_row));
    assert(island_panel_info_stock_gauge_fill(0, 0, 70, &gauge_fill));
    assert(gauge_fill == 0);
    assert(island_panel_info_stock_gauge_fill(50, 0, 70, &gauge_fill));
    assert(gauge_fill == 23);
    assert(island_panel_info_stock_gauge_fill(200, 0, 70, &gauge_fill));
    assert(gauge_fill == 70);
    assert(!island_panel_info_stock_gauge_fill(50, -3, 70, &gauge_fill));
    assert(!island_panel_info_stock_gauge_fill(50, 0, 70, NULL));
    assert(island_panel_info_task_gauge_fill(0, 3, 70, &gauge_fill));
    assert(gauge_fill == 0);
    assert(island_panel_info_task_gauge_fill(1, 3, 70, &gauge_fill));
    assert(gauge_fill == 23);
    assert(island_panel_info_task_gauge_fill(1, 4, 70, &gauge_fill));
    assert(gauge_fill == 18);
    assert(island_panel_info_task_gauge_fill(3, 4, 70, &gauge_fill));
    assert(gauge_fill == 52);
    assert(island_panel_info_task_gauge_fill(3, 3, 70, &gauge_fill));
    assert(gauge_fill == 70);
    assert(island_panel_info_task_gauge_fill(8, 3, 70, &gauge_fill));
    assert(gauge_fill == 70);
    assert(!island_panel_info_task_gauge_fill(-1, 3, 70, &gauge_fill));
    assert(!island_panel_info_task_gauge_fill(1, 0, 70, &gauge_fill));
    assert(!island_panel_info_task_gauge_fill(1, 3, 70, NULL));
    assert(island_panel_info_task_row(0xd, 0, &task_row));
    assert(strcmp(task_row.label_key, "OARTIFACT") == 0 &&
           task_row.task_icon_frame == 4);
    assert(!island_panel_info_task_row(0xb, 0, &task_row));
    info_panel.pane.top = 368;
    info_panel.pane.bottom = 471;
    assert(island_panel_info_task_row_position(&info_panel, 7, 0,
                                               &task_position));
        assert(task_position.icon_x == 25 && task_position.label_x == 45 &&
           task_position.secondary_icon_x == 150 &&
           task_position.resource_icon_x == 135 && task_position.y == 6);
    {
        int highlight_top;
        int highlight_height;
        assert(island_panel_info_task_highlight_position(&info_panel, 7, 0,
                                                        &highlight_top,
                                                        &highlight_height));
        assert(highlight_top == 3 && highlight_height == 13);
        assert(island_panel_info_task_highlight_position(&info_panel, 7, 6,
                                                        &highlight_top,
                                                        &highlight_height));
        assert(highlight_top == 81 && highlight_height == 13);
        assert(!island_panel_info_task_highlight_position(&info_panel, 7, 7,
                                                         &highlight_top,
                                                         &highlight_height));
        assert(!island_panel_info_task_highlight_position(&info_panel, 0, 0,
                                                         &highlight_top,
                                                         &highlight_height));
    }
    assert(island_panel_info_task_row_position(&info_panel, 7, 6,
                                               &task_position));
    assert(task_position.y == 84);
    assert(!island_panel_info_task_row_position(&info_panel, 7, 7,
                                                &task_position));
    assert(!island_panel_info_task_row_position(&info_panel, 0, 0,
                                                &task_position));
    assert(island_panel_info_task_index_at_y(&info_panel, 374, 7, 0, 8) == 0);
    assert(island_panel_info_task_index_at_y(&info_panel, 387, 7, 2, 8) == 3);
    assert(island_panel_info_task_index_at_y(&info_panel, 470, 7, 0, 8) == 7);
    assert(island_panel_info_task_index_at_y(&info_panel, 470, 7, 0, 7) == -1);
    assert(island_panel_info_task_index_at_y(&info_panel, 374, 7, 0, 0) == -1);
    assert(island_panel_info_task_index_at_y(&info_panel, 374, 0, 0, 8) == -1);
    assert(strcmp(island_panel_info_task_priority_key(1), "TNORM") == 0);
    assert(strcmp(island_panel_info_task_priority_key(2), "THIGH") == 0);
    assert(strcmp(island_panel_info_task_priority_key(3), "TEXCL") == 0);
    assert(island_panel_info_task_transfer_keys(4, 5, &task_title_key,
                                                &task_category_key));
    assert(strcmp(task_title_key, "DELIVER") == 0 &&
           strcmp(task_category_key, "ARTIFACT") == 0);
    assert(island_panel_info_task_transfer_keys(4, 1, &task_title_key,
                                                &task_category_key));
    assert(strcmp(task_title_key, "DELIVER") == 0 &&
           strcmp(task_category_key, "STONE") == 0);
    assert(island_panel_info_task_transfer_keys(4, 2, &task_title_key,
                                                &task_category_key));
    assert(strcmp(task_title_key, "DELIVER") == 0 &&
           strcmp(task_category_key, "CTONE") == 0);
    assert(island_panel_info_task_transfer_keys(4, 3, &task_title_key,
                                                &task_category_key));
    assert(strcmp(task_title_key, "DELIVER") == 0 &&
           strcmp(task_category_key, "MTONE") == 0);
    assert(island_panel_info_task_artifact_frame(5) == 0);
    assert(island_panel_info_task_artifact_frame(33) == 28);
    assert(island_panel_info_task_artifact_frame(4) == -1);
    assert(island_panel_info_task_artifact_frame(34) == -1);
    info_panel.pane.left = 192;
    info_panel.pane.top = 368;
    info_panel.pane.right = 447;
    info_panel.pane.bottom = 471;
    assert(island_panel_info_task_icon_position(&info_panel, -2, 1,
        4, 3, 20, 15, 10, &task_icon_x, &task_icon_y));
    assert(task_icon_x == 319 && task_icon_y == 409);
    assert(island_panel_info_task_icon_position(&info_panel, -2, 1,
        4, 3, 20, 15, 0, &task_icon_x, &task_icon_y));
    assert(task_icon_x == 309 && task_icon_y == 409);
    assert(island_panel_info_task_icon_position(&info_panel, -2, 1,
        4, 3, 20, 15, 0, &task_icon_x, &task_icon_y));
    assert(task_icon_x == 309 && task_icon_y == 409);
    assert(!island_panel_info_task_icon_position(NULL, 0, 0,
        0, 0, 1, 1, 10, &task_icon_x, &task_icon_y));
    assert(island_panel_info_task_target_preview_position(&info_panel, 4, 0,
        &task_icon_x, &task_icon_y));
    assert(task_icon_x == 417 && task_icon_y == 461);
    assert(island_panel_info_task_target_preview_position(&info_panel, 0xd, 0,
        &task_icon_x, &task_icon_y));
    assert(!island_panel_info_task_target_preview_position(&info_panel, 4, -1,
        &task_icon_x, &task_icon_y));
    assert(!island_panel_info_task_target_preview_position(&info_panel, 4, 1,
        &task_icon_x, &task_icon_y));
    assert(!island_panel_info_task_target_preview_position(&info_panel, 5, 0,
        &task_icon_x, &task_icon_y));
    assert(!island_panel_info_task_target_preview_position(NULL, 4, 0,
        &task_icon_x, &task_icon_y));
    assert(island_panel_info_construction_task_indices(0x25, 0,
        &construction_catalog_item_id, &construction_name_index));
    assert(construction_catalog_item_id == 0x25 && construction_name_index == 0);
    assert(island_panel_info_construction_task_indices(0x34, 3,
        &construction_catalog_item_id, &construction_name_index));
    assert(construction_catalog_item_id == 0x64 && construction_name_index == 63);
    assert(!island_panel_info_construction_task_indices(0x24, 0,
        &construction_catalog_item_id, &construction_name_index));
    assert(!island_panel_info_construction_task_indices(0x35, 0,
        &construction_catalog_item_id, &construction_name_index));
    assert(!island_panel_info_construction_task_indices(0x25, 4,
        &construction_catalog_item_id, &construction_name_index));
    assert(island_panel_info_task_transfer_keys(0xd, 2, &task_title_key,
                                                &task_category_key));
    assert(strcmp(task_title_key, "RETRIEVE") == 0 &&
           strcmp(task_category_key, "CTONE") == 0);
    assert(island_panel_info_task_transfer_keys(4, 4, &task_title_key,
                                                &task_category_key));
    assert(strcmp(task_title_key, "DELIVER") == 0 &&
           task_category_key == NULL);
    assert(!island_panel_info_task_transfer_keys(5, 5, &task_title_key,
                                                 &task_category_key));
    assert(island_panel_info_roster_hit_test(192, 368, 422, 389, 0, 0x01) == 0);
    assert(island_panel_info_roster_hit_test(192, 368, 436, 403, 0, 0x01) == 0);
    assert(island_panel_info_roster_hit_test(192, 368, 437, 403, 0, 0x01) == -1);
    assert(island_panel_info_roster_hit_test(192, 368, 422, 389, 0, 0x03) == 0);
    assert(island_panel_info_roster_hit_test(192, 368, 422, 423, 0, 0x02) == 1);
    assert(island_panel_info_roster_hit_test(192, 368, 422, 457, 0, 0x04) == 2);
    assert(island_panel_info_roster_hit_test(192, 368, 387, 403, 0, 0x08) == 3);
    assert(island_panel_info_roster_hit_test(192, 368, 387, 440, 0, 0x10) == 4);
    assert(island_panel_info_roster_hit_test(192, 368, 352, 423, 0, 0x20) == 5);
    assert(island_panel_info_roster_hit_test(192, 368, 437, 422, 0, 0x02) == -1);
    assert(island_panel_info_roster_hit_test(192, 368, 422, 389, 0, 0) == -1);
    assert(island_panel_info_roster_hit_test(192, 368, 412, 396, 1, 0x01) == 0);
    assert(island_panel_info_roster_hit_test(192, 368, 412, 396, 1, 0x02) == -1);
    assert(island_panel_info_roster_hit_test(192, 368, 412, 450, 1, 0x08) == 3);
    assert(island_panel_info_roster_hit_test(192, 368, 362, 423, 1, 0x20) == 5);
    info_panel.pane.left = 192;
    info_panel.pane.top = 368;
    info_panel.pane.right = 447;
    info_panel.pane.bottom = 471;
    assert(island_panel_info_building_sprite_position(&info_panel,
                                                      &sprite_x, &sprite_y));
    assert(sprite_x == 397 && sprite_y == 424);
    assert(!island_panel_info_building_sprite_position(NULL,
                                                       &sprite_x, &sprite_y));
    assert(!island_panel_info_building_sprite_position(&info_panel, NULL,
                                                       &sprite_y));
    assert(island_panel_info_hall_resource_row(0, &resource_row));
    assert(resource_row.icon_frame == 24 && resource_row.icon_x == 41 &&
           resource_row.icon_y == 40 && resource_row.amount_x == 53 &&
           resource_row.amount_y == 34);
    assert(island_panel_info_hall_resource_row(1, &resource_row));
    assert(resource_row.icon_frame == 4 && resource_row.icon_x == 41 &&
           resource_row.icon_y == 70 && resource_row.amount_x == 53 &&
           resource_row.amount_y == 63);
    assert(island_panel_info_hall_resource_row(2, &resource_row));
    assert(resource_row.icon_frame == 4 && resource_row.icon_x == 41 &&
           resource_row.icon_y == 97 && resource_row.amount_x == 53 &&
           resource_row.amount_y == 90);
    assert(!island_panel_info_hall_resource_row(3, &resource_row));
    assert(!island_panel_info_hall_resource_row(0, NULL));
    {
        WindowTemplate task_info_panel = {0};
        task_info_panel.pane.left = 456;
        task_info_panel.pane.top = 328;
        task_info_panel.pane.right = 631;
        task_info_panel.pane.bottom = 395;
        assert(island_panel_info_empty_task_label_position(&task_info_panel, 105,
                   &task_label_x, &task_label_y));
        assert(task_label_x == 491 && task_label_y == 378);
        assert(!island_panel_info_empty_task_label_position(NULL, 105,
                   &task_label_x, &task_label_y));
    }
    assert(island_panel_info_inventory_key(5, key, sizeof(key)));
    assert(strcmp(key, "BRIDGE00") == 0);
    assert(island_panel_info_inventory_key(6, key, sizeof(key)));
    assert(strcmp(key, "PLOT00") == 0);
    assert(island_panel_info_inventory_key(33, key, sizeof(key)));
    assert(strcmp(key, "PLOT27") == 0);
    assert(!island_panel_info_inventory_key(4, key, sizeof(key)));
    assert(!island_panel_info_inventory_key(34, key, sizeof(key)));
    assert(island_panel_info_inventory_detail_index(
               ISLAND_PANEL_INFO_INVENTORY_DETAIL, 5) == 0);
    hovered_inventory_item = 12;
    assert(island_panel_info_inventory_detail_index(
               ISLAND_PANEL_INFO_INVENTORY_DETAIL, hovered_inventory_item) == 7);
    /* Leaving the grid sends -1 to mode 2; no item description remains. */
    hovered_inventory_item = -1;
    assert(island_panel_info_inventory_detail_index(
               ISLAND_PANEL_INFO_INVENTORY_DETAIL, hovered_inventory_item) == -1);
    assert(island_panel_info_inventory_detail_index(
               ISLAND_PANEL_INFO_INVENTORY_DEFAULT, 12) == -1);
    assert(island_panel_info_inventory_detail_index(
               ISLAND_PANEL_INFO_INVENTORY_DETAIL, 34) == -1);
    assert(island_panel_info_extract_entry(plot04, sizeof(plot04) - 1,
                                           "PLOT04", description,
                                           sizeof(description)));
    assert(strcmp(description, "Lanterne d'ether emits light.") == 0);
    assert(island_panel_info_extract_entry(diplomacy_captions,
        sizeof(diplomacy_captions) - 1, "TRDIPHI", description,
        sizeof(description)));
    assert(strcmp(description, "Amis/Ennemis") == 0);
    assert(island_panel_info_extract_entry(diplomacy_captions,
        sizeof(diplomacy_captions) - 1, "TRCOMHI", description,
        sizeof(description)));
    assert(strcmp(description, "Communiquer ?") == 0);
    if (argc > 1) {
        FILE *file = fopen(argv[1], "rb");
        unsigned char *bytes;
        long file_length;
        unsigned int item_id;
        assert(file != NULL);
        assert(fseek(file, 0, SEEK_END) == 0);
        file_length = ftell(file);
        assert(file_length >= 0);
        assert(fseek(file, 0, SEEK_SET) == 0);
        bytes = (unsigned char *)malloc((size_t)file_length);
        assert(bytes != NULL || file_length == 0);
        assert(fread(bytes, 1, (size_t)file_length, file) == (size_t)file_length);
        assert(fclose(file) == 0);
        for (item_id = 5; item_id <= 33; ++item_id) {
            assert(island_panel_info_inventory_key(item_id, key, sizeof(key)));
            assert(island_panel_info_extract_entry(bytes, (size_t)file_length,
                                                   key, description,
                                                   sizeof(description)));
            assert(description[0] != '\0');
        }
        free(bytes);
    }
    if (argc > 2) {
        FILE *file = fopen(argv[2], "rb");
        unsigned char *bytes;
        long file_length;
        unsigned int cryptic_id;
        static const char *const task_keys[] = {
            "CONSTR", "REPAIR", "DARTIFACT", "OARTIFACT", "STOCK",
            "BLDCONST", "TNORM", "THIGH", "TEXCL", "DELIVER", "RETRIEVE",
            "STONE", "CTONE", "MTONE", "ARTIFACT"
        };
        size_t task_key_index;
        assert(file != NULL);
        assert(fseek(file, 0, SEEK_END) == 0);
        file_length = ftell(file);
        assert(file_length >= 0);
        assert(fseek(file, 0, SEEK_SET) == 0);
        bytes = (unsigned char *)malloc((size_t)file_length);
        assert(bytes != NULL || file_length == 0);
        assert(fread(bytes, 1, (size_t)file_length, file) == (size_t)file_length);
        assert(fclose(file) == 0);
        assert(island_panel_info_extract_entry(bytes, (size_t)file_length,
                                               "POPSTR", description,
                                               sizeof(description)));
        assert(strcmp(description, "Pop") == 0);
        assert(island_panel_info_extract_entry(bytes, (size_t)file_length,
                                               "NOTASKS", description,
                                               sizeof(description)));
        assert(description[0] != '\0');
        for (task_key_index = 0;
             task_key_index < sizeof(task_keys) / sizeof(task_keys[0]);
             ++task_key_index) {
            assert(island_panel_info_extract_entry(bytes, (size_t)file_length,
                task_keys[task_key_index], description, sizeof(description)));
            assert(description[0] != '\0');
        }
        for (cryptic_id = 0; cryptic_id < ISLAND_PANEL_INFO_CRYPTIC_COUNT;
             ++cryptic_id) {
            assert(island_panel_info_cryptic_key(cryptic_id, key, sizeof(key)));
            assert(island_panel_info_extract_entry(bytes, (size_t)file_length,
                                                   key, description,
                                                   sizeof(description)));
            assert(description[0] != '\0');
        }
        free(bytes);
    }
    return 0;
}
