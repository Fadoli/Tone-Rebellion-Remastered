#ifndef TONE_REBELLION_GAME_COMMAND_H
#define TONE_REBELLION_GAME_COMMAND_H

#include "game_session.h"

#include <stddef.h>
#include <stdint.h>

/* One player action that changes the shared GameSession. The original sends
   such actions as channel-1 records (FUN_00414081) and every machine runs
   them at the same scheduled tick (FUN_00466221 -> FUN_00465793 /
   FUN_004672ef; behavior/multiplayer.md). The remake wraps the existing
   session mutators so a solo click and a networked command take the same
   path. Kinds and argument order are the remake's own. */

typedef enum GameCommandKind {
    GAME_COMMAND_NONE = 0,
    GAME_COMMAND_SET_BUILDING_ORDER,      /* player, island, location, genre, target island, target, target y */
    GAME_COMMAND_ADJUST_TRADE_OFFER,      /* player, row, column, direction */
    GAME_COMMAND_TOGGLE_DIPLOMACY,        /* source, target, action */
    GAME_COMMAND_QUEUE_BUILD_SELECTION,   /* player, island, location, item */
    GAME_COMMAND_QUEUE_OBTAIN_TASK,       /* player, island, location */
    GAME_COMMAND_TOGGLE_UPGSPREAD,        /* player, island, location */
    GAME_COMMAND_TOGGLE_TRAINING_STOCK,   /* player, island, location, magic */
    GAME_COMMAND_FINISH_LOCATION_MOVE,    /* player, island, location */
    GAME_COMMAND_DISPATCH_TASK_COMMAND,   /* slot, subtype, expected record (9 fields) */
    GAME_COMMAND_QUEUE_CAST_ACTION,       /* player, island, location, action, target floater */
    GAME_COMMAND_QUEUE_ONOFF_ACTION,      /* player, island, location */
    GAME_COMMAND_TOGGLE_STAFF_UPGRADE,    /* player, island, location */
    GAME_COMMAND_CYCLE_SOURCE_CAPACITY,   /* island, location */
    GAME_COMMAND_PENDING_EVENT_ADD,       /* player, 0a, action type, 0c, 0e, 12 */
    GAME_COMMAND_CANCEL_LOCATION_MOVE,    /* (none) */
    GAME_COMMAND_BEGIN_LOCATION_MOVE,     /* player, island, location */
    GAME_COMMAND_CLEAR_TRADE_OFFERS,      /* player */
    GAME_COMMAND_COMMIT_TRADE_OFFERS,     /* player */
    GAME_COMMAND_QUEUE_ISLAND_EVENT3,     /* player, island */
    GAME_COMMAND_CYCLE_RESOURCE_STOCK,    /* player, resource type */
    GAME_COMMAND_QUEUE_GLYPH_ACTION,      /* player, island, location, glyph */
    GAME_COMMAND_QUEUE_INVENTORY_ACTION,  /* player, island, location, item */
    GAME_COMMAND_ORDER_FLOATER_TO_MERGE,  /* player, island, floater, target floater */
    GAME_COMMAND_HAND_BACK_PLAYER,        /* player (FUN_004121b7 case 2) */
    GAME_COMMAND_KIND_COUNT
} GameCommandKind;

enum { GAME_COMMAND_ARG_COUNT = 11, GAME_COMMAND_ENCODED_SIZE = 1 + 4 * GAME_COMMAND_ARG_COUNT };

typedef struct GameCommand {
    uint8_t kind;
    int32_t args[GAME_COMMAND_ARG_COUNT];
} GameCommand;

typedef struct GameCommandContext {
    const PadCatalog *pads;
} GameCommandContext;

/* Builds a command from up to GAME_COMMAND_ARG_COUNT arguments. */
GameCommand game_command_make(GameCommandKind kind, size_t count, const int32_t *args);
/* Runs the wrapped mutator; returns its result (0 for an unknown kind). */
int game_command_apply(GameSession *session, const GameCommandContext *context,
                       const GameCommand *command);

size_t game_command_encode(const GameCommand *command, uint8_t *out, size_t capacity);
int game_command_decode(const uint8_t *bytes, size_t length, GameCommand *command);

/* FNV-1a over the simulation state shared by every machine: everything
   after `config` except the clipboard groups, which stay local UI state. */
uint32_t game_session_sync_hash(const GameSession *session);

#endif
