#include "game_session.h"
#include "game_session_economy_internal.h"

#include <string.h>

/* Trade offers, local transfer requests and diplomacy toggles. */

int game_session_adjust_trade_offer(GameSession *session, uint8_t player_slot,
                                    uint8_t resource_row,
                                    uint8_t target_column, int direction)
{
    uint16_t *amount;
    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT ||
        resource_row >= GAME_RESOURCE_TYPE_COUNT ||
        target_column >= GAME_TRADE_TARGET_COUNT ||
        (direction != -1 && direction != 1)) return 0;
    amount = &session->economy[player_slot].trade_offer[resource_row][target_column];
    if (direction > 0) {
        if (*amount < 1000U) {
            *amount = (uint16_t)(*amount > 990U ? 1000U : *amount + 10U);
        }
    } else if (*amount > 0U) {
        *amount = (uint16_t)(*amount < 10U ? 0U : *amount - 10U);
    }
    return 1;
}

int game_session_clear_trade_offers(GameSession *session, uint8_t player_slot)
{
    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT) return 0;
    memset(session->economy[player_slot].trade_offer, 0,
           sizeof(session->economy[player_slot].trade_offer));
    return 1;
}

int game_session_commit_trade_offers(GameSession *session, uint8_t player_slot)
{
    const GamePlayerEconomy *economy;
    unsigned int column;
    unsigned int request_count = 0;
    unsigned int available_requests;
    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT) return -1;
    if ((unsigned int)session->trade_request_count >
        (unsigned int)GAME_SESSION_MAX_TRADE_REQUESTS) return -1;
    economy = &session->economy[player_slot];
    for (column = 0; column < GAME_TRADE_TARGET_COUNT; ++column) {
        unsigned int resource;
        int has_amount = 0;
        for (resource = 0; resource < GAME_RESOURCE_TYPE_COUNT; ++resource) {
            if (economy->trade_offer[resource][column] != 0) {
                has_amount = 1;
                break;
            }
        }
        if (has_amount) ++request_count;
    }
    available_requests = (unsigned int)GAME_SESSION_MAX_TRADE_REQUESTS -
                         (unsigned int)session->trade_request_count;
    if (request_count > available_requests) return -1;
    for (column = 0; column < GAME_TRADE_TARGET_COUNT; ++column) {
        GameTradeRequest *request;
        unsigned int resource;
        int has_amount = 0;
        for (resource = 0; resource < GAME_RESOURCE_TYPE_COUNT; ++resource) {
            if (economy->trade_offer[resource][column] != 0) {
                has_amount = 1;
                break;
            }
        }
        if (!has_amount) continue;
        request = &session->trade_requests[session->trade_request_count++];
        request->source_player = player_slot;
        request->target_player = (uint8_t)(column < player_slot ? column : column + 1U);
        for (resource = 0; resource < GAME_RESOURCE_TYPE_COUNT; ++resource) {
            request->amount[resource] = economy->trade_offer[resource][column];
        }
    }
    (void)game_session_clear_trade_offers(session, player_slot);
    return (int)request_count;
}

int game_session_pop_trade_request(GameSession *session, GameTradeRequest *out)
{
    if (session == NULL || out == NULL || session->trade_request_count == 0) return 0;
    *out = session->trade_requests[0];
    --session->trade_request_count;
    if (session->trade_request_count != 0) {
        memmove(&session->trade_requests[0], &session->trade_requests[1],
                (size_t)session->trade_request_count * sizeof(session->trade_requests[0]));
    }
    memset(&session->trade_requests[session->trade_request_count], 0,
           sizeof(session->trade_requests[0]));
    return 1;
}

int game_session_apply_trade_request(GameSession *session,
                                     const GameTradeRequest *request)
{
    GameRuntimeLocation *source;
    GameRuntimeLocation *target;
    unsigned int resource;

    if (session == NULL || request == NULL ||
        request->source_player >= GAME_START_PLAYER_COUNT ||
        request->target_player >= GAME_START_PLAYER_COUNT) return 0;
    source = game_session_player_hall(session, request->source_player);
    target = game_session_player_hall(session, request->target_player);
    if (source == NULL || target == NULL) return 0;

    for (resource = 0; resource < GAME_RESOURCE_TYPE_COUNT; ++resource) {
        int32_t amount = (int16_t)request->amount[resource];
        int32_t stock = (int16_t)source->resource_stock[resource];
        uint16_t transfer;

        if (amount < 0) amount = 0;
        if (stock < 0) stock = 0;
        if (amount > stock) amount = stock;
        transfer = (uint16_t)amount;
        source->resource_stock[resource] =
            (uint16_t)(source->resource_stock[resource] - transfer);
        target->resource_stock[resource] =
            (uint16_t)(target->resource_stock[resource] + transfer);
    }
    return 1;
}

int game_session_dispatch_trade_requests(GameSession *session)
{
    int dispatched = 0;

    if (session == NULL ||
        session->trade_request_count > GAME_SESSION_MAX_TRADE_REQUESTS) {
        return -1;
    }
    while (session->trade_request_count != 0) {
        GameTradeRequest *request = &session->trade_requests[0];
        if (!game_session_apply_trade_request(session, request)) break;
        /* Apply first so a request with a missing Hall is not lost. */
        {
            GameTradeRequest consumed;
            if (!game_session_pop_trade_request(session, &consumed)) break;
        }
        ++dispatched;
    }
    return dispatched;
}

int game_session_toggle_diplomacy(GameSession *session, uint8_t source_player,
                                  uint8_t target_player,
                                  GameDiplomacyAction action)
{
    uint8_t target_bit;
    uint8_t *mask;
    GameDiplomacyRequest *request;
    if (session == NULL || source_player >= GAME_START_PLAYER_COUNT ||
        target_player >= GAME_START_PLAYER_COUNT || source_player == target_player ||
        (action != GAME_DIPLOMACY_RECIPIENT && action != GAME_DIPLOMACY_POLICY) ||
        session->diplomacy_request_count >= GAME_SESSION_MAX_DIPLOMACY_REQUESTS) {
        return 0;
    }
    request = &session->diplomacy_requests[session->diplomacy_request_count++];
    request->source_player = source_player;
    request->target_player = target_player;
    request->action = (uint8_t)action;
    target_bit = (uint8_t)(1U << target_player);
    mask = action == GAME_DIPLOMACY_POLICY
        ? &session->diplomacy_policy_mask[source_player]
        : &session->message_recipient_mask[source_player];
    *mask ^= target_bit;
    return 1;
}

int game_session_pop_diplomacy_request(GameSession *session,
                                       GameDiplomacyRequest *out)
{
    if (session == NULL || out == NULL || session->diplomacy_request_count == 0) {
        return 0;
    }
    *out = session->diplomacy_requests[0];
    --session->diplomacy_request_count;
    if (session->diplomacy_request_count != 0) {
        memmove(&session->diplomacy_requests[0], &session->diplomacy_requests[1],
                (size_t)session->diplomacy_request_count *
                sizeof(session->diplomacy_requests[0]));
    }
    memset(&session->diplomacy_requests[session->diplomacy_request_count], 0,
           sizeof(session->diplomacy_requests[0]));
    return 1;
}
