#ifndef TONE_REBELLION_GAME_SESSION_BASE_TYPES_H
#define TONE_REBELLION_GAME_SESSION_BASE_TYPES_H

#include "game_start.h"
#include "game_diplomacy.h"
#include "floater_catalog.h"
#include "world_map.h"

#include <stddef.h>
#include <stdint.h>

enum { GAME_SESSION_MAX_FLOATERS = GAME_START_PLAYER_COUNT * GAME_START_FLOATERS_PER_PLAYER,
       GAME_FLOATER_CATEGORY_COUNT = GAME_START_PLAYER_COUNT + 1 };
enum { GAME_SESSION_MAX_PENDING_EVENTS = 64, GAME_SESSION_MAX_TASKS = 32 };
enum { GAME_SESSION_MAX_CAST_EFFECTS = 32 };
enum { GAME_SESSION_MAX_GLYPH_ACTIONS = 64 };
enum { GAME_SESSION_MAX_ONOFF_ACTIONS = 64 };
enum { GAME_SESSION_MAX_BUILD_SELECTIONS = 64 };
enum { GAME_TRADE_TARGET_COUNT = GAME_START_PLAYER_COUNT - 1,
       GAME_SESSION_MAX_TRADE_REQUESTS = GAME_START_PLAYER_COUNT * GAME_TRADE_TARGET_COUNT };
enum { GAME_SESSION_MAX_DIPLOMACY_REQUESTS =
       GAME_START_PLAYER_COUNT * GAME_TRADE_TARGET_COUNT * 2 };
enum { GAME_RESOURCE_TYPE_COUNT = 3, GAME_RESOURCE_NONE = 0xff };
enum { GAME_INVENTORY_ITEM_FIRST_ID = 5, GAME_INVENTORY_ITEM_COUNT = 29,
       GAME_GLYPH_COUNT = 14 };

typedef enum GameResourceType {
    GAME_RESOURCE_BUILD_TONE = 0,
    GAME_RESOURCE_CRYSTAL_TONE = 1,
    GAME_RESOURCE_MAGIC_TONE = 2
} GameResourceType;

typedef struct GamePlayerEconomy {
    /* FUN_0046466f assigns one initial hall per player. These indices bind
       the player's resource storage to that runtime hall record. */
    uint8_t hall_island_index;
    uint16_t hall_location_index;
    uint16_t hall_x;
    uint16_t hall_y;
    /* FUN_00453bf6 compares pad.txt maintenance against player +0x6191f8.
       The observed static dword is zero; a runtime writer remains unknown. */
    int32_t source_maintenance_budget;
    /* FUN_0043d59b enumerates player-owned inventory counts for item IDs 5..33.
       The UI count table is distinct from resources and island placements. */
    uint16_t inventory_count[GAME_INVENTORY_ITEM_COUNT];
    /* FUN_0043dee3 reads the player's 14-bit glyph-ownership mask. */
    uint16_t glyph_mask;
    /* FUN_00465793 stores the last glyph accepted by the subtype-3 action. */
    uint8_t selected_glyph_index;
    /* FUN_0045f755 cycles each Hall reserve mode through raw values 0..2;
       FUN_0045eaa7 treats mode 2 as an active fill request. */
    uint8_t stock_mode[GAME_RESOURCE_TYPE_COUNT];
    /* FUN_0045eaa7 stores the slot reserved for each of its three type-4
       stock requests; -1 means no request is linked. */
    int16_t resource_task_slot[GAME_RESOURCE_TYPE_COUNT];
    /* IWTrade keeps three resource amounts for each of the three other
       players. Columns use the source display order with the local player
       omitted (FUN_0043edac / FUN_0043ec78). */
    uint16_t trade_offer[GAME_RESOURCE_TYPE_COUNT][GAME_TRADE_TARGET_COUNT];
} GamePlayerEconomy;

/* FUN_0042fa0f's TradeDOIT path emits category-3/type-0xb requests. The
   remake queues them and applies resolvable Hall-to-Hall transfers locally
   during its island tick; network transport remains outside this model. */
typedef struct GameTradeRequest {
    uint8_t source_player;
    uint8_t target_player;
    uint16_t amount[GAME_RESOURCE_TYPE_COUNT];
} GameTradeRequest;

/* FUN_0043e4f0 emits subtype-10 diplomacy requests. The local arrays mirror
   the two source per-player flag groups after FUN_00465793 applies a toggle. */
typedef struct GameDiplomacyRequest {
    uint8_t source_player;
    uint8_t target_player;
    uint8_t action;
} GameDiplomacyRequest;

/* FUN_0042fa0f emits category 3/type 3 when a glyph is selected. The island
   tick dispatches this payload to the first matching player/subtype-8 floater;
   the later cast animation and impact remain separate. */
typedef struct GameGlyphActionRequest {
    uint8_t player_slot;
    uint8_t island_index;
    uint16_t location_index;
    uint8_t glyph_index;
} GameGlyphActionRequest;

/* FUN_0042fa0f's BC_OnOff command reaches FUN_00465793 as type-1/subtype-0.
   Keep its target as a request until the island tick dispatches it. */
typedef struct GameOnOffActionRequest {
    uint8_t player_slot;
    uint8_t island_index;
    uint16_t location_index;
} GameOnOffActionRequest;

/* FUN_0042fa0f(0x34) sends this 16-byte category-0/type-5 packet. The local
   tick dispatcher stores its fields in a 64-slot task record; placement is
   still unresolved, so this request does not mutate the site. */
typedef struct GameBuildSelectionRequest {
    uint16_t category;
    uint16_t player_slot;
    uint16_t action_type;
    uint16_t island_index_a;
    uint16_t reserved_zero;
    uint16_t island_index_b;
    uint16_t location_index;
    uint16_t item_id;
} GameBuildSelectionRequest;

/* The source type-3/subtype-4 dispatcher invokes an item receiver before it
   debits DAT_006191fc. The receiver effect is still caller-owned. */
typedef int (*GameInventoryResultApply)(void *context, uint8_t player_slot,
                                        uint8_t item_id);

/* FUN_004662b7 reserves one of 64 world-action records (stride 0x14).
   Priority is initialized to 1 there and read as such by FUN_004469d6. */
typedef struct GamePendingEvent {
    uint32_t active;
    /* FUN_00421ec1 increments/decrements slot +0x04 as floaters attach. */
    int16_t assigned_floater_count;
    uint16_t priority;
    int16_t player_id;
    int16_t payload_0a;
    int16_t payload_0c;
    int16_t payload_0e;
    int16_t action_type;
    int16_t payload_12;
} GamePendingEvent;

struct BuildingRenderCatalog;
struct IslandLocation;
typedef struct PadCatalog PadCatalog;

typedef struct GameSessionConfig {
    uint8_t world_index;
    uint8_t difficulty;
    uint8_t selected_tribe;
    uint32_t mode;
    uint32_t alternate_island;
    uint8_t home_island_index;
    uint8_t randomize_class0_assignment;
    uint32_t random_seed;
} GameSessionConfig;

#endif
