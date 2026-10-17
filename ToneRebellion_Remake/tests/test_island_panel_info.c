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
    WindowTemplate info_panel = {0};
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
    assert(island_panel_info_inventory_key(5, key, sizeof(key)));
    assert(strcmp(key, "BRIDGE00") == 0);
    assert(island_panel_info_inventory_key(6, key, sizeof(key)));
    assert(strcmp(key, "PLOT00") == 0);
    assert(island_panel_info_inventory_key(33, key, sizeof(key)));
    assert(strcmp(key, "PLOT27") == 0);
    assert(!island_panel_info_inventory_key(4, key, sizeof(key)));
    assert(!island_panel_info_inventory_key(34, key, sizeof(key)));
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
    return 0;
}
