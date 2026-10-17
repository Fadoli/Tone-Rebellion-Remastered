#ifndef TONE_REBELLION_GAME_SESSION_H
#define TONE_REBELLION_GAME_SESSION_H

#include "game_start.h"
#include "world_map.h"

#include <stddef.h>
#include <stdint.h>

enum { GAME_SESSION_MAX_FLOATERS = GAME_START_PLAYER_COUNT * GAME_START_FLOATERS_PER_PLAYER };
enum { GAME_RESOURCE_TYPE_COUNT = 3, GAME_RESOURCE_NONE = 0xff };

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
    /* FUN_0045f755 cycles each Hall reserve mode through raw values 0..2;
       FUN_0045eaa7 treats mode 2 as an active fill request. */
    uint8_t stock_mode[GAME_RESOURCE_TYPE_COUNT];
} GamePlayerEconomy;

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
    uint16_t class0_assignments;
    /* FUN_004718eb reads one active flag per WORLDPOS bridge pair. */
    uint32_t active_bridge_mask;
    GameRuntimeIsland islands[WORLD_MAP_MAX_ISLANDS];
} GameSession;

/*
 * Builds the initial, mutable gameplay state from a selected WORLDPOS world
 * and its ISLANDnn.TXT records (ordered by world-island index). The port
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
                            const GameSessionConfig *config,
                            GameSession *out,
                            char *error, size_t error_capacity);

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
/* FUN_0041ff2e masks the source level word with 0x000f; IWLocInfo displays
   that value plus one. Returns 0 for a null record. */
uint8_t game_session_location_display_level(const GameRuntimeLocation *location);
/* Resource stock fields are attached to each player's initial Hall runtime
   record. Starting values, caps and mutation rules remain to be verified. */
int game_session_credit_resource(GameSession *session, uint8_t player_slot,
                                 GameResourceType type, uint32_t amount);
int game_session_debit_resource(GameSession *session, uint8_t player_slot,
                                 GameResourceType type, uint32_t amount);
/* FUN_0045f755: advance one Hall resource mode modulo three. Returns the new
   raw mode, or -1 for an invalid player/resource. */
int game_session_cycle_resource_stock_mode(GameSession *session,
                                           uint8_t player_slot,
                                           GameResourceType type);
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
