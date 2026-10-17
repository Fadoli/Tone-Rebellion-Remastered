#ifndef TONE_REBELLION_GAME_DIPLOMACY_H
#define TONE_REBELLION_GAME_DIPLOMACY_H

#include <stdint.h>

typedef enum GameDiplomacyAction {
    /* FUN_00465793 stores source subtype 10 / field 7 = 0 at player +0xd8. */
    GAME_DIPLOMACY_RECIPIENT = 0,
    /* FUN_00465793 stores source subtype 10 / field 7 = 1 at player +0xe8. */
    GAME_DIPLOMACY_POLICY = 1
} GameDiplomacyAction;

typedef struct GameDiplomacyHit {
    GameDiplomacyAction action;
    uint8_t displayed_column;
} GameDiplomacyHit;

/* Maps the three displayed players to global player IDs, skipping local_player. */
int game_diplomacy_target_player(uint8_t local_player, uint8_t displayed_column,
                                 uint8_t *target_player);

/* Mirrors FUN_0043e399's absolute screen-coordinate hover zones. The panel
   descriptor supplies its pane; the upper Amis/Ennemis row uses the three
   explicit source rectangles and the lower Communiquer row divides the pane
   into thirds. Returns zero outside the source-active controls. */
int game_diplomacy_hit_test(int32_t x, int32_t y,
                            int32_t pane_left, int32_t pane_top,
                            int32_t pane_right, int32_t pane_bottom,
                            GameDiplomacyHit *hit);

#endif
