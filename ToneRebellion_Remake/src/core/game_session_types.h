#ifndef TONE_REBELLION_GAME_SESSION_TYPES_H
#define TONE_REBELLION_GAME_SESSION_TYPES_H

#include "game_start.h"
#include "game_diplomacy.h"
#include "floater_catalog.h"
#include "world_map.h"

#include <stddef.h>
#include <stdint.h>

enum { GAME_SESSION_MAX_FLOATERS = GAME_START_PLAYER_COUNT * GAME_START_FLOATERS_PER_PLAYER,
       GAME_FLOATER_CATEGORY_COUNT = GAME_START_PLAYER_COUNT + 1 };
enum { GAME_SESSION_MAX_PENDING_EVENTS = 64, GAME_SESSION_MAX_TASKS = 32 };
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

/* FUN_0042fa0f(0x40) emits category 3/type 3 when a glyph is selected.
   This outbox preserves the target payload; FUN_00465793's active-record
   filter (+0 == player, +4 == 8) and resulting runtime order are not simulated. */
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

typedef struct GameRuntimeLocation {
    int32_t record_value_10;
    int32_t owner_id;
    /* Source signed short +0x18. FUN_00452c31 requires this != -1 before
       owner Inventory is available on non-Hall locations; FUN_004528ca sets
       it for source item IDs 0x2c..0x32. Slot assignment is not yet modeled. */
    int16_t source_location_slot_18;
    /* On producer items 0x25/0x26/0x27, FUN_00450a71 stores a pending
       resource code 1/3/2 here when PROD completes; other classes use the
       same runtime field for different purposes. */
    int32_t record_value_24;
    int32_t bridge_neighbor_island;
    uint16_t x;
    uint16_t y;
    /* Runtime +0x1c bitword. Bit 0x400 is changed by FUN_00453bf6;
       FUN_0045eaa7 separately checks bit 0x001 for Hall stock requests. */
    uint32_t source_flags;
    /* FUN_00453958 reads these runtime shorts at +0x44 and +0x58 when
       recomputing active bit 0. Their field meanings are not established. */
    int16_t source_value_44;
    int16_t source_value_58;
    /* FUN_0045cbaa clears the three subtype 1..3 links when a site is turned
       off. -1 means the source has no linked task for that subtype. */
    int16_t source_task_slot[GAME_RESOURCE_TYPE_COUNT];
    /* FUN_0041ff2e reads the selected record's word at +0x0a and displays
       its low nibble plus one as LEVEL. */
    uint16_t source_level_flags;
    uint16_t base_progress;
    /* Three stock values observed in the hall runtime record at +0x28/+0x2a/
       +0x2c. Ghidra reads them as short fields; exact signedness/caps remain
       unconfirmed. */
    uint16_t resource_stock[GAME_RESOURCE_TYPE_COUNT];
    /* Raw Hall threshold read by FUN_0045eaa7. */
    int16_t source_capacity_4a;
    /* FUN_004528ca initializes runtime +0x34 from FUN_00450978; repair task
       rows later read this mutable short from their target location. */
    int16_t source_value_34;
    /* FUN_00452e4d stores the last floater pickup tick it checked for a
       resource output at runtime +0x36. */
    int16_t resource_retry_tick_36;
    /* Producer items 0x25..0x27 use source +0x0c to start PROD after the
       running object's cadence reaches 20; separate from BASE +0x4a. */
    uint16_t producer_cadence;
    uint16_t chug_progress;
    uint16_t glyph_progress;
    uint16_t inci_progress;
    uint16_t construction_progress;
    uint16_t production_progress;
    uint16_t animation_rate;
    double barg_progress;
    uint8_t renderer_class;
    uint8_t tribe_visibility_mask;
    /* FUN_004669bd sets bit 0 at runtime record +0x1c on both paired
       class-2 bridge objects once the bridge link is established. */
    uint8_t bridge_constructed;
} GameRuntimeLocation;

typedef struct GameRuntimeIsland {
    uint16_t location_count;
    /* FUN_00423068 reads horizontal wander limits by floater category and
       island. Zero / 0x9ff retain the source's global fallback on each side;
       the data loader for the original per-category limits is not modeled. */
    int32_t floater_min_x[GAME_FLOATER_CATEGORY_COUNT];
    int32_t floater_max_x[GAME_FLOATER_CATEGORY_COUNT];
    /* FUN_00420991 uses DAT_0061fa2e[island] to decide whether a category-4
       floater seeks a different category or another category-4 floater. The
       loaded image initializes all 15 entries to zero; no direct writer was
       found, though indirect runtime updates remain possible. */
    int16_t source_level;
    /* FUN_0047117d checks one per-player access dword at island +0x29ac. */
    uint8_t access_mask;
    /* FUN_00465793 message type 3/subtype 0 toggles bit 0 in one raw dword
       per player at island +0x29bc. Its gameplay/display meaning is unknown. */
    uint32_t source_event_state[GAME_START_PLAYER_COUNT];
    /* Pending type-3/subtype-0 events are represented by parity: each source
       event only XORs bit 0, so coalescing preserves the post-drain raw word. */
    uint8_t source_event3_pending_parity[GAME_START_PLAYER_COUNT];
    GameRuntimeLocation locations[ISLAND_DATA_MAX_LOCATIONS];
} GameRuntimeIsland;

typedef struct GameFloaterStart {
    uint8_t island_index;
    uint8_t type_index;
    /* FUN_00466fe4 stores the subtype in the second floater dword. The four
       initial units created for each category by FUN_0046466f use subtype 0. */
    uint8_t source_subtype;
    uint8_t owner_slot;
    /* Initial stats come from the four local *work rows. Current HP is
       mutable; XP is not exposed by IWLocInfo's worker branch and is not
       modeled here. */
    uint8_t current_hit_points;
    uint8_t max_hit_points;
    uint8_t attack_strength;
    int16_t attack_range;
    /* Floater runtime short +0x0c gates IWLocInfo CHARGE through
       FUN_004207f2; +0x22 is the mutable charge counter. Initial workers
       start at -1 and 0 respectively. Assignment and charge ticks are not
       modeled yet. */
    int16_t source_link_0c;
    int16_t charge_current;
    uint16_t x;
    uint16_t y;
    uint16_t destination_x;
    uint16_t destination_y;
    uint16_t movement_speed;
    /* Action-9 post-arrival stages mirror tick +0x46 and +0x32. The target
       candidate table/policy for non-enemy units is only partly reconstructed. */
    uint8_t order_progress;
    /* Tick record +0x3c. FUN_0042219e does not replace FA_Cast (0x13). */
    uint8_t active_order_action;
    int16_t order_target_floater;
    int16_t order_target_location;
    /* FA_Deliver's action-4 order uses the tick record's +0x18 cargo, +0x34
       pickup counter and +0x46 subphase. Only local resource codes 1..3 are
       currently dispatched from Hall refill requests. */
    int16_t carried_resource_code;
    int16_t order_resource_code;
    int16_t linked_task_slot;
    uint16_t order_timer;
    int16_t order_source_location;
    uint32_t source_runtime_flags;
    /* FUN_00422d27's speed context is resolved before its coordinate step.
       Initial workers start idle and take the fallback FA_Wander route on
       their first simulation tick. Remaining modifiers stay zero until their
       runtime sources are modeled by the session. */
    uint8_t movement_state;
    int16_t category_speed_modifier;
    uint8_t near_target_speed_override;
    uint8_t site_speed_bonus;
    uint16_t stop_radius;
    /* FUN_0045d8b2's linked 100-byte record fields. FUN_0042219e copies a
       changed coordinate order into the separate tick record; this pending
       flag lets the remake preserve that source boundary before applying it. */
    uint8_t source_order_state_2c;
    uint8_t source_order_island_28;
    uint16_t source_order_coordinate_30;
    uint16_t source_order_parameter_32;
    uint8_t source_order_pending;
    uint8_t has_move_order;
    /* Idle fallback order FA_Wander (14), runtime state 0x0e and +0x34 timer. */
    uint8_t has_wander_order;
    uint16_t wander_timer;
    uint8_t facing_left;
} GameFloaterStart;

typedef struct GameSession {
    GameSessionConfig config;
    /* Shared LCG after modeled world-start draws; simulation randomness
       advances it, including FA_Wander destination generation. */
    ToneRng random_state;
    uint8_t island_count;
    GameStartSetup player_starts;
    GameStartToneDistribution tone_placements;
    GameFloaterStart floaters[GAME_SESSION_MAX_FLOATERS];
    uint8_t floater_count;
    GamePlayerEconomy economy[GAME_START_PLAYER_COUNT];
    /* FUN_004662b7's 64-slot deferred-action table, initially zeroed by
       FUN_004637fc. This stores requests only; effect processing is separate. */
    uint16_t pending_event_count;
    GamePendingEvent pending_events[GAME_SESSION_MAX_PENDING_EVENTS];
    uint16_t trade_request_count;
    GameTradeRequest trade_requests[GAME_SESSION_MAX_TRADE_REQUESTS];
    uint8_t diplomacy_policy_mask[GAME_START_PLAYER_COUNT];
    uint8_t message_recipient_mask[GAME_START_PLAYER_COUNT];
    uint8_t diplomacy_request_count;
    GameDiplomacyRequest diplomacy_requests[GAME_SESSION_MAX_DIPLOMACY_REQUESTS];
    uint8_t glyph_action_count;
    GameGlyphActionRequest glyph_actions[GAME_SESSION_MAX_GLYPH_ACTIONS];
    uint8_t onoff_action_count;
    GameOnOffActionRequest onoff_actions[GAME_SESSION_MAX_ONOFF_ACTIONS];
    uint16_t build_selection_count;
    GameBuildSelectionRequest build_selections[GAME_SESSION_MAX_BUILD_SELECTIONS];
    uint16_t class0_assignments;
    /* FUN_004718eb reads one active flag per WORLDPOS bridge pair. */
    uint32_t active_bridge_mask;
    GameRuntimeIsland islands[WORLD_MAP_MAX_ISLANDS];
} GameSession;

/*
 * Builds the initial, mutable gameplay state from a selected WORLDPOS world,
 * its ISLANDnn.TXT records (ordered by world-island index), and parsed pad
 * records required to initialize source runtime fields. The port
 * models FUN_004500c4 field resets, FUN_0046466f start descriptors and initial
 * pads/floaters, applies FUN_00464b9e marker item placements, sets class-2
 * record state and reproduces the two class-0 assignment loops in
 * FUN_004637fc. All inputs remain unchanged and `out` changes only after the
 * full setup succeeds.
 *
 * `home_island_index` represents the unresolved runtime value compared with
 * DAT_006136b0 - 1. `random_state` preserves the LCG after the modeled draws
 * and is advanced by later simulation draws. RNG draws before/inside the unported
 * 0x17..0x19 loop are outside this model, so this is not whole-startup stream
 * parity.
 */

#endif
