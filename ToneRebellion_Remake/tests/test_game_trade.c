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

static void test_dispatch_clamps_and_transfers_hall_stocks(void)
{
    GameSession session;
    GameTradeRequest request = {0};
    GameRuntimeLocation *source;
    GameRuntimeLocation *target;

    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    session.islands[0].location_count = 2;
    session.economy[1].hall_location_index = 0;
    session.economy[2].hall_location_index = 1;
    source = &session.islands[0].locations[0];
    target = &session.islands[0].locations[1];
    source->resource_stock[0] = 15;
    source->resource_stock[1] = 7;
    source->resource_stock[2] = 0;
    target->resource_stock[0] = 3;
    request.source_player = 1;
    request.target_player = 2;
    request.amount[0] = 20;
    request.amount[1] = 5;
    request.amount[2] = 9;

    assert(game_session_apply_trade_request(&session, &request));
    assert(source->resource_stock[0] == 0 && target->resource_stock[0] == 18);
    assert(source->resource_stock[1] == 2 && target->resource_stock[1] == 5);
    assert(source->resource_stock[2] == 0 && target->resource_stock[2] == 0);

    request.amount[0] = UINT16_MAX; /* Signed-short negative: zero transfer. */
    request.amount[1] = 0;
    request.amount[2] = 0;
    source->resource_stock[0] = 10;
    target->resource_stock[0] = 4;
    assert(game_session_apply_trade_request(&session, &request));
    assert(source->resource_stock[0] == 10 && target->resource_stock[0] == 4);

    request.source_player = GAME_START_PLAYER_COUNT;
    assert(!game_session_apply_trade_request(&session, &request));
    request.source_player = 1;
    session.economy[2].hall_location_index = 2;
    assert(!game_session_apply_trade_request(&session, &request));
    assert(!game_session_apply_trade_request(NULL, &request));
    assert(!game_session_apply_trade_request(&session, NULL));
}

static void test_queued_transfers_dispatch_on_local_tick(void)
{
    GameSession session;
    GameRuntimeLocation *source;
    GameRuntimeLocation *target;

    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    session.islands[0].location_count = 2;
    session.economy[1].hall_location_index = 0;
    session.economy[2].hall_location_index = 1;
    source = &session.islands[0].locations[0];
    target = &session.islands[0].locations[1];
    source->resource_stock[0] = 12;
    source->resource_stock[1] = 6;
    session.economy[1].trade_offer[0][1] = 20;
    session.economy[1].trade_offer[1][1] = 4;

    assert(game_session_commit_trade_offers(&session, 1) == 1);
    assert(source->resource_stock[0] == 12 && target->resource_stock[0] == 0);
    assert(session.trade_request_count == 1);
    assert(game_session_dispatch_trade_requests(&session) == 1);
    assert(source->resource_stock[0] == 0 && target->resource_stock[0] == 12);
    assert(source->resource_stock[1] == 2 && target->resource_stock[1] == 4);
    assert(session.trade_request_count == 0);
    assert(game_session_dispatch_trade_requests(&session) == 0);
    assert(game_session_dispatch_trade_requests(NULL) == -1);

    /* A missing receiver context leaves the oldest request pending. */
    session.trade_requests[0].source_player = 1;
    session.trade_requests[0].target_player = 2;
    session.trade_request_count = 1;
    session.economy[2].hall_location_index = 2;
    assert(game_session_dispatch_trade_requests(&session) == 0);
    assert(session.trade_request_count == 1);
    session.economy[2].hall_location_index = 1;
    assert(game_session_dispatch_trade_requests(&session) == 1);
    assert(session.trade_request_count == 0);
}

int main(void)
{
    test_source_cell_geometry();
    test_click_steps_and_clamps_are_player_local();
    test_commit_emits_nonempty_targets_in_source_order();
    test_full_outbox_preserves_offer_table();
    test_dispatch_clamps_and_transfers_hall_stocks();
    test_queued_transfers_dispatch_on_local_tick();
    return 0;
}
