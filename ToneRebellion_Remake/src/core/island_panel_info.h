#ifndef TONE_REBELLION_ISLAND_PANEL_INFO_H
#define TONE_REBELLION_ISLAND_PANEL_INFO_H

#include "window_catalog.h"

#include <stddef.h>
#include <stdint.h>

enum {
    ISLAND_PANEL_INFO_INVENTORY_DETAIL = 2,
    ISLAND_PANEL_INFO_INVENTORY_DEFAULT = 6
};

/* Default IWTextInfo descriptions selected when these Hall panels open. */
const char *island_panel_info_default_key(int panel_mode);

/* FUN_00439673 formats Inventory hover IDs 5..33 as BRIDGE00/PLOT00..27. */
int island_panel_info_inventory_key(unsigned int item_id,
                                    char *output, size_t output_capacity);

/* FUN_0044338b places the selected location sprite inside IWLocInfo using
   the pane width/height-relative anchor recovered from its draw call. */
int island_panel_info_building_sprite_position(const WindowTemplate *panel,
                                               int *x, int *y);

/* Reads one key-delimited text entry, trimming horizontal whitespace on keys. */
int island_panel_info_extract_entry(const unsigned char *bytes, size_t length,
                                    const char *key,
                                    char *output, size_t output_capacity);

#endif
