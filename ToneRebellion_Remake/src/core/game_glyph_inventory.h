#ifndef TONE_REBELLION_GAME_GLYPH_INVENTORY_H
#define TONE_REBELLION_GAME_GLYPH_INVENTORY_H

#include "game_session.h"

#include <stddef.h>
#include <stdint.h>

typedef struct GameGlyphCenter {
    int x;
    int y;
} GameGlyphCenter;

/* FUN_0043dee3 uses frame 0 as the mask background, 1..14 as glyph layers,
   and +14 variants for the currently selected glyph. UINT32_MAX means absent. */
uint32_t game_glyph_inventory_frame(uint16_t glyph_mask, int glyph_index,
                                    int selected_glyph);

/* FUN_0043ddcf tests a 32x31 box around each owned glyph center, in ID order. */
int game_glyph_inventory_hit_test(uint16_t glyph_mask,
                                  const GameGlyphCenter centers[GAME_GLYPH_COUNT],
                                  int x, int y);
/* The source handler runs only for pointer events inside IWGlyphs; an event
   outside the pane retains the prior hover. */
int game_glyph_inventory_update_hover(
    int previous_glyph, uint16_t glyph_mask,
    const GameGlyphCenter centers[GAME_GLYPH_COUNT], int event_in_pane,
    int x, int y);

/* FUN_00439673 resolves hovered glyph descriptions as GLYPH%02d. */
int game_glyph_inventory_key(unsigned int glyph_index,
                             char *output, size_t output_capacity);

/* FUN_0042fa0f selects interaction cursor slot 0x0b when either a glyph or
   inventory item is armed, and slot 0x0d otherwise. */
int game_glyph_inventory_cursor_slot(int selected_glyph,
                                     int selected_inventory_item);

#endif
