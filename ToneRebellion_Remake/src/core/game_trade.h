#ifndef TONE_REBELLION_GAME_TRADE_H
#define TONE_REBELLION_GAME_TRADE_H

#include <stdint.h>

/* FUN_0043ec78 accepts pane-relative x=40..154 and y=37..109, then maps
   them to one of the 3x3 resource/other-player amount cells. */
int game_trade_cell_at(int32_t pane_x, int32_t pane_y,
                       uint8_t *resource_row, uint8_t *target_column);

#endif
