#include "game_trade.h"

int game_trade_cell_at(int32_t pane_x, int32_t pane_y,
                       uint8_t *resource_row, uint8_t *target_column)
{
    int32_t column;
    int32_t row;
    if (resource_row == 0 || target_column == 0 || pane_x < 40 || pane_x > 154 ||
        pane_y < 37 || pane_y > 109) return 0;
    column = (pane_x - 40) / 33;
    row = (pane_y - 37) / 19;
    if (column > 2) column = 2;
    if (row > 2) row = 2;
    *resource_row = (uint8_t)row;
    *target_column = (uint8_t)column;
    return 1;
}
