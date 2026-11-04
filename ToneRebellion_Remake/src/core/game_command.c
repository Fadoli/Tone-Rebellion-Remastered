#include "game_command.h"

#include <stddef.h>
#include <string.h>

GameCommand game_command_make(GameCommandKind kind, size_t count, const int32_t *args)
{
    GameCommand command;
    size_t i;
    memset(&command, 0, sizeof(command));
    command.kind = (uint8_t)kind;
    if (count > GAME_COMMAND_ARG_COUNT) count = GAME_COMMAND_ARG_COUNT;
    for (i = 0; i < count; ++i) command.args[i] = args[i];
    return command;
}

int game_command_apply(GameSession *session, const GameCommandContext *context,
                       const GameCommand *command)
{
    const int32_t *a;
    const PadCatalog *pads = context != NULL ? context->pads : NULL;
    if (session == NULL || command == NULL) return 0;
    a = command->args;
    switch ((GameCommandKind)command->kind) {
    case GAME_COMMAND_SET_BUILDING_ORDER:
        return game_session_set_building_order(session, (uint8_t)a[0], (uint8_t)a[1],
            (uint16_t)a[2], (unsigned int)a[3], (uint8_t)a[4], (unsigned int)a[5],
            (unsigned int)a[6]);
    case GAME_COMMAND_ADJUST_TRADE_OFFER:
        return game_session_adjust_trade_offer(session, (uint8_t)a[0], (uint8_t)a[1],
                                               (uint8_t)a[2], (int)a[3]);
    case GAME_COMMAND_TOGGLE_DIPLOMACY:
        return game_session_toggle_diplomacy(session, (uint8_t)a[0], (uint8_t)a[1],
                                             (GameDiplomacyAction)a[2]);
    case GAME_COMMAND_QUEUE_BUILD_SELECTION:
        return game_session_queue_build_selection(session, (uint8_t)a[0], (uint8_t)a[1],
                                                  (uint16_t)a[2], (uint16_t)a[3]);
    case GAME_COMMAND_QUEUE_OBTAIN_TASK:
        return game_session_queue_obtain_task(session, (uint8_t)a[0], (uint8_t)a[1],
                                              (uint16_t)a[2]);
    case GAME_COMMAND_TOGGLE_UPGSPREAD:
        return game_session_toggle_upgspread(session, (uint8_t)a[0], (uint8_t)a[1],
                                             (uint16_t)a[2]);
    case GAME_COMMAND_TOGGLE_TRAINING_STOCK:
        return game_session_toggle_training_stock(session, (uint8_t)a[0], (uint8_t)a[1],
                                                  (uint16_t)a[2], (int)a[3]);
    case GAME_COMMAND_FINISH_LOCATION_MOVE:
        return game_session_finish_location_move(session, (uint8_t)a[0], (uint8_t)a[1],
                                                 (uint16_t)a[2]);
    case GAME_COMMAND_DISPATCH_TASK_COMMAND: {
        GamePendingEvent expected;
        memset(&expected, 0, sizeof(expected));
        expected.active = (uint32_t)a[2];
        expected.assigned_floater_count = (int16_t)a[3];
        expected.priority = (uint16_t)a[4];
        expected.player_id = (int16_t)a[5];
        expected.payload_0a = (int16_t)a[6];
        expected.payload_0c = (int16_t)a[7];
        expected.payload_0e = (int16_t)a[8];
        expected.action_type = (int16_t)a[9];
        expected.payload_12 = (int16_t)a[10];
        {
            /* FUN_00465793 calls FUN_0045fb6f on a player cancel: a training
               SUPPLY task linked from +0x52 / +0x54 also clears TrnStkC /
               TrnStkM (+0x58 / +0x5c). The tick's own cancel keeps them. */
            GameRuntimeLocation *supply = NULL;
            const uint8_t slot = (uint8_t)a[0];
            int result;
            if (a[1] == 12 && slot < GAME_SESSION_MAX_PENDING_EVENTS) {
                const GamePendingEvent *event = &session->pending_events[slot];
                if (event->active != 0 && event->action_type == 4 &&
                    (event->payload_12 == 2 || event->payload_12 == 3) &&
                    event->payload_0a >= 0 &&
                    event->payload_0a < session->island_count &&
                    event->payload_0e >= 0 &&
                    (uint16_t)event->payload_0e <
                        session->islands[event->payload_0a].location_count) {
                    supply = &session->islands[event->payload_0a]
                                  .locations[(uint16_t)event->payload_0e];
                    if (supply->source_task_slot[event->payload_12 - 1] !=
                        (int16_t)slot) supply = NULL;
                }
            }
            result = game_session_dispatch_task_command(session, slot,
                                                        (uint8_t)a[1], &expected);
            if (result && supply != NULL) {
                if (expected.payload_12 == 2) supply->training_stock_crystal = 0;
                else supply->training_stock_magic = 0;
            }
            return result;
        }
    }
    case GAME_COMMAND_QUEUE_CAST_ACTION:
        return game_session_queue_cast_action_at(session, (uint8_t)a[0], (uint8_t)a[1],
            (uint16_t)a[2], (uint8_t)a[3], (uint8_t)a[5], (int16_t)a[6],
            (int16_t)a[4]);
    case GAME_COMMAND_QUEUE_ONOFF_ACTION:
        return game_session_queue_onoff_action(session, (uint8_t)a[0], (uint8_t)a[1],
                                               (uint16_t)a[2]);
    case GAME_COMMAND_TOGGLE_STAFF_UPGRADE:
        return game_session_toggle_staff_upgrade_request(session, (uint8_t)a[0],
                                                         (uint8_t)a[1], (uint16_t)a[2]);
    case GAME_COMMAND_CYCLE_SOURCE_CAPACITY:
        return game_session_cycle_source_capacity(session, (uint8_t)a[0], (uint16_t)a[1]);
    case GAME_COMMAND_PENDING_EVENT_ADD:
        return game_session_pending_event_add(session, (int16_t)a[0], (int16_t)a[1],
            (int16_t)a[2], (int16_t)a[3], (int16_t)a[4], (int16_t)a[5]);
    case GAME_COMMAND_CANCEL_LOCATION_MOVE:
        return game_session_cancel_location_move(session, pads);
    case GAME_COMMAND_BEGIN_LOCATION_MOVE:
        return game_session_begin_location_move(session, pads, (uint8_t)a[0],
                                                (uint8_t)a[1], (uint16_t)a[2]);
    case GAME_COMMAND_CLEAR_TRADE_OFFERS:
        return game_session_clear_trade_offers(session, (uint8_t)a[0]);
    case GAME_COMMAND_COMMIT_TRADE_OFFERS:
        return game_session_commit_trade_offers(session, (uint8_t)a[0]);
    case GAME_COMMAND_QUEUE_ISLAND_EVENT3:
        return game_session_queue_island_event3_subtype0(session, (uint8_t)a[0],
                                                         (uint8_t)a[1]);
    case GAME_COMMAND_CYCLE_RESOURCE_STOCK:
        return game_session_cycle_resource_stock_mode(session, (uint8_t)a[0],
                                                      (GameResourceType)a[1]);
    case GAME_COMMAND_QUEUE_GLYPH_ACTION:
        return game_session_queue_glyph_action(session, (uint8_t)a[0], (uint8_t)a[1],
                                               (uint16_t)a[2], (uint8_t)a[3]);
    case GAME_COMMAND_QUEUE_INVENTORY_ACTION:
        return game_session_queue_inventory_action(session, (uint8_t)a[0], (uint8_t)a[1],
                                                   (uint16_t)a[2], (uint8_t)a[3]);
    case GAME_COMMAND_ORDER_FLOATER_TO_MERGE:
        return game_session_order_floater_to_merge(session, (uint8_t)a[0], (uint8_t)a[1],
            (unsigned int)a[2], (unsigned int)a[3]);
    case GAME_COMMAND_TOGGLE_REPAIR:
        return game_session_toggle_repair(session, pads, (uint8_t)a[0],
                                          (uint8_t)a[1], (uint16_t)a[2]);
    case GAME_COMMAND_HAND_BACK_PLAYER:
        if (a[0] < 0 || a[0] >= GAME_START_PLAYER_COUNT) return 0;
        game_session_hand_back_player_holdings(session, (unsigned int)a[0]);
        return 1;
    case GAME_COMMAND_START_END_SEQUENCE:
        /* World command 0x15, sent by the network debug key 'W'
           (FUN_0046a5b7 0x46a92a): DAT_006191b4 = 3, DAT_006191b6 = 0 on
           every machine, skipping state 2 (seal reset, 1000 ticks). */
        session->world_sequence_state = 3;
        session->world_sequence_tick = 0;
        return 1;
    default:
        return 0;
    }
}

size_t game_command_encode(const GameCommand *command, uint8_t *out, size_t capacity)
{
    size_t i;
    if (command == NULL || out == NULL || capacity < GAME_COMMAND_ENCODED_SIZE) return 0;
    out[0] = command->kind;
    for (i = 0; i < GAME_COMMAND_ARG_COUNT; ++i) {
        uint32_t value = (uint32_t)command->args[i];
        out[1 + 4 * i] = (uint8_t)(value & 0xffU);
        out[2 + 4 * i] = (uint8_t)((value >> 8) & 0xffU);
        out[3 + 4 * i] = (uint8_t)((value >> 16) & 0xffU);
        out[4 + 4 * i] = (uint8_t)(value >> 24);
    }
    return GAME_COMMAND_ENCODED_SIZE;
}

int game_command_decode(const uint8_t *bytes, size_t length, GameCommand *command)
{
    size_t i;
    if (bytes == NULL || command == NULL || length < GAME_COMMAND_ENCODED_SIZE ||
        bytes[0] == GAME_COMMAND_NONE || bytes[0] >= GAME_COMMAND_KIND_COUNT) return 0;
    command->kind = bytes[0];
    for (i = 0; i < GAME_COMMAND_ARG_COUNT; ++i)
        command->args[i] = (int32_t)((uint32_t)bytes[1 + 4 * i] |
                                     ((uint32_t)bytes[2 + 4 * i] << 8) |
                                     ((uint32_t)bytes[3 + 4 * i] << 16) |
                                     ((uint32_t)bytes[4 + 4 * i] << 24));
    return 1;
}

static uint32_t fnv1a(uint32_t hash, const uint8_t *bytes, size_t length)
{
    size_t i;
    for (i = 0; i < length; ++i) {
        hash ^= bytes[i];
        hash *= UINT32_C(16777619);
    }
    return hash;
}

uint32_t game_session_sync_hash(const GameSession *session)
{
    const uint8_t *base = (const uint8_t *)session;
    size_t start = offsetof(GameSession, random_state);
    size_t clip_start = offsetof(GameSession, clip_group);
    size_t clip_end = offsetof(GameSession, location_move_active);
    uint32_t hash = UINT32_C(2166136261);
    if (session == NULL) return 0;
    hash = fnv1a(hash, base + start, clip_start - start);
    return fnv1a(hash, base + clip_end, sizeof(GameSession) - clip_end);
}
