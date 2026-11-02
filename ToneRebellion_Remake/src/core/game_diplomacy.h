#ifndef TONE_REBELLION_GAME_DIPLOMACY_H
#define TONE_REBELLION_GAME_DIPLOMACY_H

#include <stdint.h>

typedef enum GameDiplomacyAction {
    /* FUN_00465793 subcode 10 with field 7 != 0 toggles player +0xe8
       (DAT_006192a0, message recipients). */
    GAME_DIPLOMACY_RECIPIENT = 0,
    /* FUN_00465793 subcode 10 with field 7 == 0 toggles player +0xd8
       (DAT_00619290, policy, set = friend). The enum values are the port's own
       and do not encode field 7. */
    GAME_DIPLOMACY_POLICY = 1
} GameDiplomacyAction;

typedef struct GameDiplomacyHit {
    GameDiplomacyAction action;
    uint8_t displayed_column;
} GameDiplomacyHit;

/* Maps the three displayed players to global player IDs, skipping local_player. */
int game_diplomacy_target_player(uint8_t local_player, uint8_t displayed_column,
                                 uint8_t *target_player);

/* FUN_0043e5aa calls FUN_00428191 for the local player at the upper center,
   then for each of the three displayed opponents around the lower panel.
   Coordinates returned here are relative to the diplomacy pane. */
int game_diplomacy_player_icon_position(uint8_t displayed_slot,
                                        int32_t pane_left,
                                        int32_t pane_width,
                                        int32_t pane_height,
                                        int32_t *x, int32_t *y);

/* Mirrors FUN_0043e399's absolute screen-coordinate hover zones. The panel
   descriptor supplies its pane; the upper Amis/Ennemis row uses the three
   explicit source rectangles and the lower Communiquer row divides the pane
   into thirds. Returns zero outside the source-active controls. */
int game_diplomacy_hit_test(int32_t x, int32_t y,
                            int32_t pane_left, int32_t pane_top,
                            int32_t pane_right, int32_t pane_bottom,
                            GameDiplomacyHit *hit);

#endif
