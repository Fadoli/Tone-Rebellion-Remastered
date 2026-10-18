#ifndef TONE_REBELLION_GAME_SESSION_H
#define TONE_REBELLION_GAME_SESSION_H

#include "game_start.h"
#include "game_diplomacy.h"
#include "world_map.h"

#include <stddef.h>
#include <stdint.h>

enum { GAME_SESSION_MAX_FLOATERS = GAME_START_PLAYER_COUNT * GAME_START_FLOATERS_PER_PLAYER };
enum { GAME_SESSION_MAX_PENDING_EVENTS = 64, GAME_SESSION_MAX_TASKS = 32 };
enum { GAME_SESSION_MAX_GLYPH_ACTIONS = 64 };
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

/* FUN_0042fa0f's TradeDOIT path emits category-3/type-0xb packets. This
   outbox records those messages for a future multiplayer transport; it does
   not apply the transfer locally. */
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

/* FUN_004662b7 reserves one of 64 world-action records (stride 0x14).
   Priority is initialized to 1 there and read as such by FUN_004469d6. */
typedef struct GamePendingEvent {
    uint32_t active;
    uint16_t reserved_zero;
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
    uint32_t source_flags;
    /* FUN_0041ff2e reads the selected record's word at +0x0a and displays
       its low nibble plus one as LEVEL. */
    uint16_t source_level_flags;
    uint16_t base_progress;
    /* Three stock values observed in the hall runtime record at +0x28/+0x2a/
       +0x2c. Ghidra reads them as short fields; exact signedness/caps remain
       unconfirmed. */
    uint16_t resource_stock[GAME_RESOURCE_TYPE_COUNT];
    /* Raw Hall fields read by FUN_0045eaa7. The active-bit writer is still
       unknown, so these begin at the zeroed runtime value. */
    int16_t source_capacity_4a;
    /* FUN_004528ca initializes runtime +0x34 from FUN_00450978; repair task
       rows later read this mutable short from their target location. */
    int16_t source_value_34;
    uint32_t source_flags_1c;
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
    uint8_t owner_slot;
    /* Initial class-0 worker fields observed in FUN_00466fe4 and the four
       *work rows in floater.txt. Current HP is mutable; XP is not exposed by
       IWLocInfo's worker branch and is deliberately not modeled here. */
    uint8_t current_hit_points;
    uint8_t max_hit_points;
    uint8_t attack_strength;
    uint16_t x;
    uint16_t y;
    uint16_t destination_x;
    uint16_t destination_y;
    uint16_t movement_speed;
    uint16_t stop_radius;
    uint8_t has_move_order;
    uint8_t facing_left;
} GameFloaterStart;

typedef struct GameSession {
    GameSessionConfig config;
    /* Shared LCG state after the world-start draws modeled by this port. */
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
 * for subsequent realm-music selection. RNG draws before/inside the unported
 * 0x17..0x19 loop are outside this model, so this is not whole-startup stream
 * parity.
 */
int game_session_initialize(const WorldDefinition *world,
                            const IslandData *islands_by_world_index,
                            const PadCatalog *pad_catalog,
                            const GameSessionConfig *config,
                            GameSession *out,
                            char *error, size_t error_capacity);

/* FUN_004459e6 uses payload +0x0a as island and +0x0e as location. Repair
   reads current +0x34 and FUN_00450978 maximum at that target. */
int game_session_repair_task_values(const GameSession *session,
                                    const PadCatalog *pad_catalog,
                                    const GamePendingEvent *event,
                                    int16_t *current, int16_t *maximum);
/* Construction rows read target +0x28 and pad record +0x04 via
   FUN_004641de(player,payload+0x12). */
int game_session_construction_task_values(const GameSession *session,
                                          const PadCatalog *pad_catalog,
                                          const GamePendingEvent *event,
                                          int16_t *current, int16_t *maximum);

/* Models FUN_0047117d: any player bit in player_mask with island access set
   permits entry. The UI passes the selected human tribe's bit. */
int game_session_can_enter_island(const GameSession *session,
                                  uint8_t island_index,
                                  uint8_t player_mask);

/* Models FUN_00471e66's SMISLE variant selection: inaccessible islands use
   frame group +15, accessible islands +0, and a hovered accessible island
   +30. Returns -1 when the island index is outside the initialized session. */
int game_session_world_map_frame_offset(const GameSession *session,
                                        uint8_t island_index,
                                        uint8_t player_mask,
                                        int hovered);
int game_session_bridge_is_active(const GameSession *session,
                                  uint8_t bridge_index,
                                  uint8_t bridge_count);
/* A WORLDPOS possibility is drawable only when its runtime flag is active and
   both endpoint islands contain the reciprocal class-2 bridge markers paired
   by FUN_00461859. */
int game_session_world_bridge_is_renderable(const GameSession *session,
                                            uint8_t bridge_index,
                                            uint8_t bridge_count,
                                            uint8_t island_a,
                                            uint8_t island_b);
/* Models the paired-object state change observed in FUN_004669bd. */
int game_session_mark_bridge_constructed(GameSession *session,
                                         uint8_t bridge_index,
                                         uint8_t bridge_count,
                                         uint8_t island_a,
                                         uint8_t island_b);
int game_session_set_bridge_active(GameSession *session,
                                   uint8_t bridge_index,
                                   uint8_t bridge_count,
                                   int active);
/* Models FUN_004702d9's WORLDWIN message 0x4f: all counted bridge flags are
   enabled when parameter bit 0x100 is clear and disabled when it is set. */
int game_session_apply_world_bridge_message(GameSession *session,
                                            uint8_t bridge_count,
                                            uint32_t parameter_flags);

/* Advance the per-location animation fields updated by FUN_00450a71. */
void game_session_tick_item_animations(GameSession *session,
                                       const struct BuildingRenderCatalog *catalog);
/* Advance destinations assigned by the simulation using the FUN_00422d27
   step kernel. Player input must not call this as a worker-order command. */
void game_session_tick_floater_moves(GameSession *session, uint32_t source_tick);
/* Hit test the visible island's active floaters in session order. The original
   FUN_00435581 uses Chebyshev distance < 0x14 (20) for floater selection. */
int game_session_floater_at(const GameSession *session,
                            uint8_t island_index,
                            uint16_t x,
                            uint16_t y);
/* FUN_0046562b(player,-1) counts all active player-owned floater records.
   This session contains only the modeled active floaters. */
unsigned int game_session_count_player_floaters(const GameSession *session,
                                                uint8_t player_slot);
/* FUN_0041ff2e masks the source level word with 0x000f; IWLocInfo displays
   that value plus one. Returns 0 for a null record. */
uint8_t game_session_location_display_level(const GameRuntimeLocation *location);
/* Resource stock fields are attached to each player's initial Hall runtime
   record. Starting values, caps and mutation rules remain to be verified. */
int game_session_credit_resource(GameSession *session, uint8_t player_slot,
                                 GameResourceType type, uint32_t amount);
int game_session_debit_resource(GameSession *session, uint8_t player_slot,
                                 GameResourceType type, uint32_t amount);
/* FUN_00452eac: consume a matching output, Hall stock (1..3), or owner
   Inventory item (5..33), following the source branch order. */
int game_session_consume_location_resource(GameSession *session,
                                           uint8_t island_index,
                                           uint16_t location_index,
                                           int32_t resource_code);
/* FUN_00452c31: test pending output, Hall stock, or owner Inventory; the raw
   +0x18 eligibility guard is represented, but slot allocation is not. */
int game_session_location_resource_available(const GameSession *session,
                                             uint8_t island_index,
                                             uint16_t location_index,
                                             int32_t resource_code);
/* FUN_0045f2a1 reads this location's pad.txt movement tuple and multiplies
   each short by runtime +0x4a + 1. The order matches stocks +0x28/+0x2a/+0x2c.
   This calculates costs only; source eligibility remains a separate check. */
int game_session_location_move_costs(const GameSession *session,
                                     const PadCatalog *catalog,
                                     uint8_t island_index,
                                     uint16_t location_index,
                                     int32_t costs[GAME_RESOURCE_TYPE_COUNT]);
/* FUN_0045f755: advance one Hall resource mode modulo three. Returns the new
   raw mode, or -1 for an invalid player/resource. */
int game_session_cycle_resource_stock_mode(GameSession *session,
                                           uint8_t player_slot,
                                           GameResourceType type);
/* FUN_0045eaa7: create/cancel deferred type-4 resource requests from each
   player's Hall modes, stocks, slot references, and raw Hall guards. */
unsigned int game_session_update_resource_requests(GameSession *session);
/* FUN_0043ec78: left/right cell clicks add/subtract 10 and clamp to 0..1000.
   target_column is the displayed column after omitting player_slot. */
int game_session_adjust_trade_offer(GameSession *session, uint8_t player_slot,
                                    uint8_t resource_row,
                                    uint8_t target_column, int direction);
/* FUN_0042fa0f messages 4010/4011 clear or enqueue nonzero per-target
   type-0xb requests and then clear the 3x3 offer table. Returns packet count,
   or -1 if invalid/full (offers remain intact on failure). */
int game_session_clear_trade_offers(GameSession *session, uint8_t player_slot);
int game_session_commit_trade_offers(GameSession *session, uint8_t player_slot);
int game_session_pop_trade_request(GameSession *session, GameTradeRequest *out);
/* FUN_0043e4f0 / FUN_00465793: enqueue one subtype-10 toggle and update the
   corresponding local flag as if the queued event had been dispatched. */
int game_session_toggle_diplomacy(GameSession *session, uint8_t source_player,
                                  uint8_t target_player,
                                  GameDiplomacyAction action);
int game_session_pop_diplomacy_request(GameSession *session,
                                       GameDiplomacyRequest *out);
/* FUN_0043d59b reads counts for IDs 5..33; FUN_00425084 increments a count
   when a produced item cannot be placed, and FUN_00452eac decrements it when
   an inventory item is consumed. These helpers model those count changes. */
int game_session_inventory_credit(GameSession *session, uint8_t player_slot,
                                  uint8_t item_id, uint32_t amount);
int game_session_inventory_debit(GameSession *session, uint8_t player_slot,
                                  uint8_t item_id, uint32_t amount);
/* Models the record reservation and duplicate rule in FUN_004662b7. Returns
   the reserved slot, or -1 when full/duplicate/invalid. Only action types 5
   and 13 are deduplicated by the source table. */
int game_session_pending_event_add(GameSession *session, int16_t player_id,
                                   int16_t payload_0a, int16_t action_type,
                                   int16_t payload_0c, int16_t payload_0e,
                                   int16_t payload_12);
/* FUN_004455d1 projects active 0x14-byte slots for one player, omits action
   type 0xb, preserves table order, and caps the list at 32. Returns the total
   projected count, writing at most capacity source slot indices. */
size_t game_session_collect_task_slots(const GameSession *session,
                                       int16_t player_id,
                                       uint8_t *slot_indices,
                                       size_t capacity);
/* FUN_00465793 category-3 subtypes 12..15 match the queued record by player,
   payload_0a, action_type and payload_12 before cancelling or changing its
   priority. `expected` is the task snapshot used to form the command. */
int game_session_dispatch_task_command(GameSession *session, uint8_t slot,
                                       uint8_t subtype,
                                       const GamePendingEvent *expected);
/* FUN_0042fa0f(0x40): queue an inventory-use request for a clicked island
   location. Mirrors its class-0 occupied-location rejection and stores the
   source's island/location/item payload; it does not apply the item effect or
   debit inventory before the later result event succeeds. */
int game_session_queue_inventory_action(GameSession *session,
                                        uint8_t player_slot,
                                        uint8_t island_index,
                                        uint16_t location_index,
                                        uint8_t item_id);
/* FUN_0042fa0f(0x40) emits category-3/type-3 with player, island, location,
   and selected glyph. This records the request only; the receiver's active
   record filter (+0 == player, +4 == 8) and runtime effect remain unmodeled. */
int game_session_queue_glyph_action(GameSession *session,
                                    uint8_t player_slot,
                                    uint8_t island_index,
                                    uint16_t location_index,
                                    uint8_t glyph_index);
int game_session_pop_glyph_action(GameSession *session,
                                  GameGlyphActionRequest *out);
/* PANIC message 0x3b queues type 3/subtype 0. Parity coalescing retains the
   same state after FUN_00466221 drains the local action queue. */
int game_session_queue_island_event3_subtype0(GameSession *session,
                                              uint8_t player_slot,
                                              uint8_t island_index);
/* Apply the queued type-3/subtype-0 effects at an island simulation tick. */
void game_session_dispatch_island_events(GameSession *session);
/* Clears a modelled pending slot and updates its active count. This does not
   reproduce FUN_00466533's unrelated engine callbacks. */
int game_session_pending_event_release(GameSession *session, uint8_t slot);
/* FUN_004503bd sets one ownership bit after the source acquisition condition. */
int game_session_acquire_glyph(GameSession *session, uint8_t player_slot,
                               uint8_t glyph_index);
/* FUN_00452656 validation and FUN_004528ca runtime initialization. */
int game_session_place_building(GameSession *session,
                                const PadCatalog *catalog,
                                uint8_t player_slot,
                                uint8_t island_index,
                                uint16_t location_index,
                                const struct IslandLocation *site,
                                uint16_t base_item_id,
                                char *error, size_t error_capacity);

#endif
