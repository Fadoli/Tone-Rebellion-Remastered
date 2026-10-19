#ifndef TONE_REBELLION_GAME_SESSION_FLOATER_TYPES_H
#define TONE_REBELLION_GAME_SESSION_FLOATER_TYPES_H

#include "game_session_world_types.h"

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
    int16_t attack_realm;
    /* Raw source +0x0a: low nibble is the level and the high nibble is its
       attack modifier. Initial runtime floaters currently start at zero. */
    uint16_t attack_level_flags;
    int16_t attack_range;
    /* FUN_0042520e's state-6/7 cadence, resolved from the draw ID's fltinf
       attack animation during session initialization. */
    uint16_t attack_period;
    uint16_t attack_timer;
    /* The source impact instance finishes after its frame span plus the
       completion-check update. It advances on odd global effect ticks. */
    uint8_t attack_impact_frame_counts[4];
    uint8_t attack_effect_active;
    uint8_t attack_effect_odd_updates_remaining;
    uint16_t source_death_timer;
    /* Floater runtime short +0x0c gates IWLocInfo CHARGE through
       FUN_004207f2; +0x22 is the mutable charge counter. Initial workers
       start at -1 and 0 respectively. Assignment and charge ticks are not
       modeled yet. The charge maintenance helpers decrement counters on
       category/source records, not this floater field. */
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
    uint8_t order_target_island;
    /* FA_Deliver's action-4 order uses the tick record's +0x18 cargo, +0x34
       pickup counter and +0x46 subphase. Hall refill routes can cross islands. */
    int16_t carried_resource_code;
    int16_t order_resource_code;
    int16_t linked_task_slot;
    uint16_t order_timer;
    int16_t order_source_location;
    uint8_t order_source_island;
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
    /* FUN_004210a9's state-0x11 inter-island bridge handoff. */
    uint8_t handoff_target_island;
    int16_t handoff_departure_location;
    uint8_t handoff_resume_action;
    uint8_t handoff_resume_state;
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
    /* Source effect manager has 32 shared active slots. This tracks modeled
       state-6/7 impact instances; unrelated visual effects are not included. */
    uint8_t active_attack_effect_count;
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
