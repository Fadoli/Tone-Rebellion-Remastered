#include "game_session.h"
#include "game_trade.h"

#include <assert.h>
#include <string.h>

static void test_source_cell_geometry(void)
{
    uint8_t row = 0xff;
    uint8_t column = 0xff;
    assert(!game_trade_cell_at(39, 37, &row, &column));
    assert(!game_trade_cell_at(40, 36, &row, &column));
    assert(!game_trade_cell_at(40, 37, NULL, &column));
    assert(game_trade_cell_at(40, 37, &row, &column));
    assert(row == 0 && column == 0);
    assert(game_trade_cell_at(73, 56, &row, &column));
    assert(row == 1 && column == 1);
    assert(game_trade_cell_at(154, 109, &row, &column));
    assert(row == 2 && column == 2);
    assert(!game_trade_cell_at(155, 109, &row, &column));
    assert(!game_trade_cell_at(154, 110, &row, &column));
}

static void test_click_steps_and_clamps_are_player_local(void)
{
    GameSession session;
    memset(&session, 0, sizeof(session));
    assert(!game_session_adjust_trade_offer(NULL, 0, 0, 0, 1));
    assert(!game_session_adjust_trade_offer(&session, GAME_START_PLAYER_COUNT,
                                            0, 0, 1));
    assert(!game_session_adjust_trade_offer(&session, 0, 3, 0, 1));
    assert(!game_session_adjust_trade_offer(&session, 0, 0, 3, 1));
    assert(!game_session_adjust_trade_offer(&session, 0, 0, 0, 0));
    assert(game_session_adjust_trade_offer(&session, 1, 0, 2, -1));
    assert(session.economy[1].trade_offer[0][2] == 0);
    assert(game_session_adjust_trade_offer(&session, 1, 0, 2, 1));
    assert(session.economy[1].trade_offer[0][2] == 10);
    assert(session.economy[0].trade_offer[0][2] == 0);
    session.economy[1].trade_offer[1][0] = 995;
    assert(game_session_adjust_trade_offer(&session, 1, 1, 0, 1));
    assert(session.economy[1].trade_offer[1][0] == 1000);
    assert(game_session_adjust_trade_offer(&session, 1, 1, 0, -1));
    assert(session.economy[1].trade_offer[1][0] == 990);
    session.economy[1].trade_offer[1][0] = 5;
    assert(game_session_adjust_trade_offer(&session, 1, 1, 0, -1));
    assert(session.economy[1].trade_offer[1][0] == 0);
}

static void test_commit_emits_nonempty_targets_in_source_order(void)
{
    GameSession session;
    GameTradeRequest request;
    memset(&session, 0, sizeof(session));
    session.economy[2].trade_offer[0][0] = 20;
    session.economy[2].trade_offer[2][0] = 40;
    session.economy[2].trade_offer[1][2] = 70;
    assert(game_session_commit_trade_offers(&session, 2) == 2);
    assert(session.economy[2].trade_offer[0][0] == 0);
    assert(session.economy[2].trade_offer[1][2] == 0);
    assert(session.trade_request_count == 2);
    assert(game_session_pop_trade_request(&session, &request));
    assert(request.source_player == 2 && request.target_player == 0);
    assert(request.amount[0] == 20 && request.amount[1] == 0 &&
           request.amount[2] == 40);
    assert(game_session_pop_trade_request(&session, &request));
    assert(request.source_player == 2 && request.target_player == 3);
    assert(request.amount[0] == 0 && request.amount[1] == 70 &&
           request.amount[2] == 0);
    assert(!game_session_pop_trade_request(&session, &request));
    assert(game_session_commit_trade_offers(&session, 2) == 0);
    assert(game_session_clear_trade_offers(&session, 2));
    assert(game_session_commit_trade_offers(NULL, 2) == -1);
    assert(game_session_clear_trade_offers(NULL, 2) == 0);
}

static void test_full_outbox_preserves_offer_table(void)
{
    GameSession session;
    memset(&session, 0, sizeof(session));
    session.trade_request_count = GAME_SESSION_MAX_TRADE_REQUESTS;
    session.economy[0].trade_offer[0][0] = 10;
    assert(game_session_commit_trade_offers(&session, 0) == -1);
    assert(session.economy[0].trade_offer[0][0] == 10);
}

int main(void)
{
    test_source_cell_geometry();
    test_click_steps_and_clamps_are_player_local();
    test_commit_emits_nonempty_targets_in_source_order();
    test_full_outbox_preserves_offer_table();
    return 0;
}
