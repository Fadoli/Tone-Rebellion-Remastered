#include "game_diplomacy.h"
#include "game_session.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>

static void test_displayed_player_order(void)
{
    static const uint8_t expected[GAME_START_PLAYER_COUNT][GAME_START_PLAYER_COUNT - 1] = {
        {1, 2, 3}, {0, 2, 3}, {0, 1, 3}, {0, 1, 2}
    };
    uint8_t local;
    for (local = 0; local < GAME_START_PLAYER_COUNT; ++local) {
        uint8_t column;
        for (column = 0; column < GAME_START_PLAYER_COUNT - 1U; ++column) {
            uint8_t target = UINT8_MAX;
            assert(game_diplomacy_target_player(local, column, &target));
            assert(target == expected[local][column]);
            assert(target != local);
        }
    }
    {
        uint8_t target = 33;
        assert(!game_diplomacy_target_player(0, 3, &target));
        assert(target == 33);
        assert(!game_diplomacy_target_player(GAME_START_PLAYER_COUNT, 0,
                                             &target));
    }
}

static void test_source_player_icon_positions(void)
{
    static const int32_t expected_x[4] = {127, 46, 126, 206};
    static const int32_t expected_y[4] = {10, 73, 83, 73};
    uint8_t slot;
    for (slot = 0; slot < 4; ++slot) {
        int32_t x = -1;
        int32_t y = -1;
        assert(game_diplomacy_player_icon_position(slot, 192, 255, 103,
                                                    &x, &y));
        assert(x == expected_x[slot] && y == expected_y[slot]);
    }
    {
        int32_t x = 77;
        int32_t y = 88;
        assert(!game_diplomacy_player_icon_position(4, 192, 255, 103,
                                                    &x, &y));
        assert(x == 77 && y == 88);
        assert(!game_diplomacy_player_icon_position(0, 192, 0, 103,
                                                    &x, &y));
    }
}

static void test_source_hover_zones(void)
{
    const int32_t left = 192;
    const int32_t top = 368;
    const int32_t right = 447;
    const int32_t bottom = 471;
    GameDiplomacyHit hit;
    assert(game_diplomacy_hit_test(266, 399, left, top, right, bottom, &hit));
    assert(hit.action == GAME_DIPLOMACY_POLICY && hit.displayed_column == 0);
    assert(game_diplomacy_hit_test(295, 428, left, top, right, bottom, &hit));
    assert(hit.action == GAME_DIPLOMACY_POLICY && hit.displayed_column == 0);
    assert(game_diplomacy_hit_test(313, 432, left, top, right, bottom, &hit));
    assert(hit.action == GAME_DIPLOMACY_POLICY && hit.displayed_column == 1);
    assert(game_diplomacy_hit_test(329, 432, left, top, right, bottom, &hit));
    assert(hit.action == GAME_DIPLOMACY_POLICY && hit.displayed_column == 1);
    assert(game_diplomacy_hit_test(347, 428, left, top, right, bottom, &hit));
    assert(hit.action == GAME_DIPLOMACY_POLICY && hit.displayed_column == 2);
    assert(!game_diplomacy_hit_test(330, 432, left, top, right, bottom, &hit));
    assert(!game_diplomacy_hit_test(296, 428, left, top, right, bottom, &hit));
    assert(game_diplomacy_hit_test(313, 433, left, top, right, bottom, &hit));
    assert(hit.action == GAME_DIPLOMACY_RECIPIENT && hit.displayed_column == 1);

    assert(game_diplomacy_hit_test(left, 433, left, top, right, bottom, &hit));
    assert(hit.action == GAME_DIPLOMACY_RECIPIENT && hit.displayed_column == 0);
    assert(game_diplomacy_hit_test(left + 85, 450, left, top, right, bottom, &hit));
    assert(hit.action == GAME_DIPLOMACY_RECIPIENT && hit.displayed_column == 0);
    assert(game_diplomacy_hit_test(left + 86, 450, left, top, right, bottom, &hit));
    assert(hit.action == GAME_DIPLOMACY_RECIPIENT && hit.displayed_column == 1);
    assert(game_diplomacy_hit_test(left + 170, 470, left, top, right, bottom, &hit));
    assert(hit.action == GAME_DIPLOMACY_RECIPIENT && hit.displayed_column == 1);
    assert(game_diplomacy_hit_test(left + 171, 470, left, top, right, bottom, &hit));
    assert(hit.action == GAME_DIPLOMACY_RECIPIENT && hit.displayed_column == 2);
    assert(!game_diplomacy_hit_test(left, top, left, top, right, bottom, NULL));
    assert(!game_diplomacy_hit_test(left, bottom + 1, left, top, right, bottom,
                                    &hit));
    assert(!game_diplomacy_hit_test(right, 450, left, top, right, bottom,
                                    &hit));
    assert(!game_diplomacy_hit_test(left, bottom, left, top, right, bottom,
                                    &hit));
}

static void test_session_toggles_and_outbox(void)
{
    GameSession session = {0};
    GameDiplomacyRequest request;
    unsigned int i;
    assert(game_session_toggle_diplomacy(&session, 2, 3,
                                         GAME_DIPLOMACY_POLICY));
    assert((session.diplomacy_policy_mask[2] & (1U << 3)) != 0);
    assert(session.message_recipient_mask[2] == 0);
    assert(game_session_toggle_diplomacy(&session, 2, 3,
                                         GAME_DIPLOMACY_POLICY));
    assert((session.diplomacy_policy_mask[2] & (1U << 3)) == 0);
    assert(game_session_toggle_diplomacy(&session, 2, 3,
                                         GAME_DIPLOMACY_RECIPIENT));
    assert((session.message_recipient_mask[2] & (1U << 3)) != 0);
    assert(session.diplomacy_request_count == 3);
    assert(game_session_pop_diplomacy_request(&session, &request));
    assert(request.source_player == 2 && request.target_player == 3 &&
           request.action == GAME_DIPLOMACY_POLICY);
    assert(game_session_pop_diplomacy_request(&session, &request));
    assert(request.action == GAME_DIPLOMACY_POLICY);
    assert(game_session_pop_diplomacy_request(&session, &request));
    assert(request.action == GAME_DIPLOMACY_RECIPIENT);
    assert(!game_session_pop_diplomacy_request(&session, &request));

    assert(!game_session_toggle_diplomacy(&session, 1, 1,
                                          GAME_DIPLOMACY_RECIPIENT));
    assert(!game_session_toggle_diplomacy(&session, 0, 4,
                                          GAME_DIPLOMACY_RECIPIENT));
    assert(!game_session_toggle_diplomacy(&session, 0, 1,
                                          (GameDiplomacyAction)2));
    for (i = 0; i < GAME_SESSION_MAX_DIPLOMACY_REQUESTS; ++i) {
        assert(game_session_toggle_diplomacy(&session, 0, 1,
            (i & 1U) ? GAME_DIPLOMACY_POLICY : GAME_DIPLOMACY_RECIPIENT));
    }
    assert(!game_session_toggle_diplomacy(&session, 0, 1,
                                          GAME_DIPLOMACY_POLICY));
    assert(session.diplomacy_request_count == GAME_SESSION_MAX_DIPLOMACY_REQUESTS);
    assert(game_session_pop_diplomacy_request(&session, &request));
    assert(request.source_player == 0 && request.target_player == 1 &&
           request.action == GAME_DIPLOMACY_RECIPIENT);
    puts("game diplomacy tests passed");
}

int main(void)
{
    test_displayed_player_order();
    test_source_player_icon_positions();
    test_source_hover_zones();
    test_session_toggles_and_outbox();
    return 0;
}
