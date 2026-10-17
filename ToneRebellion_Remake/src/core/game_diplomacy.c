#include "game_diplomacy.h"

#include "game_start.h"

int game_diplomacy_target_player(uint8_t local_player, uint8_t displayed_column,
                                 uint8_t *target_player)
{
    uint8_t target;
    if (target_player == 0 || local_player >= GAME_START_PLAYER_COUNT ||
        displayed_column >= GAME_START_PLAYER_COUNT - 1U) return 0;
    target = displayed_column;
    if (target >= local_player) ++target;
    if (target >= GAME_START_PLAYER_COUNT) return 0;
    *target_player = target;
    return 1;
}

static int inside(int32_t x, int32_t y,
                  int32_t left, int32_t top, int32_t right, int32_t bottom)
{
    return x >= left && x <= right && y >= top && y <= bottom;
}

int game_diplomacy_hit_test(int32_t x, int32_t y,
                            int32_t pane_left, int32_t pane_top,
                            int32_t pane_right, int32_t pane_bottom,
                            GameDiplomacyHit *hit)
{
    int32_t width;
    int32_t relative_x;
    uint8_t column;
    GameDiplomacyAction action;
    if (hit == 0 || pane_right <= pane_left || pane_bottom <= pane_top ||
        x < pane_left || x >= pane_right || y < pane_top || y >= pane_bottom) {
        return 0;
    }

    if (y < 0x1b1) {
        if (inside(x, y, 0x10a, 399, 0x127, 0x1ac)) column = 0;
        else if (inside(x, y, 0x139, 399, 0x149, 0x1b1)) column = 1;
        else if (inside(x, y, 0x15b, 399, 0x178, 0x1ac)) column = 2;
        else return 0;
        action = GAME_DIPLOMACY_POLICY;
    } else {
        width = pane_right - pane_left;
        relative_x = x - pane_left;
        column = 0;
        if ((width * 2) / 3 < relative_x) column = 2;
        else if (width / 3 < relative_x) column = 1;
        action = GAME_DIPLOMACY_RECIPIENT;
    }
    hit->action = action;
    hit->displayed_column = column;
    return 1;
}
