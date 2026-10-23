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
    int16_t current_hit_points;
    int16_t max_hit_points;
    uint8_t attack_strength;
    /* Raw short +0x08; FUN_004200d2 increments it after a positive attack
       result. Its gameplay meaning is not established yet. */
    uint16_t source_progress_08;
    int16_t max_attack_points;
    /* Immutable catalog row used to recalculate FUN_00420f28 after level or
       island-feature bonus state changes. */
    int16_t base_max_attack_points;
    int16_t attack_realm;
    /* Raw source +0x0a: low nibble is unit level; high nibble is the Leviathan
       attack rank that FUN_0042000b advances up to 11. */
    uint16_t attack_level_flags;
    int16_t attack_range;
    /* FUN_0042520e's state-6/7 cadence, resolved from the draw ID's fltinf
       attack animation during session initialization. */
    uint16_t attack_period;
    /* fltinf attack segment used by FUN_0042704b while state 6/7 is active. */
    uint16_t attack_frame_first;
    uint16_t attack_frame_last;
    uint16_t attack_frame_ticks_per_frame;
    uint16_t attack_frame_duration;
    uint8_t attack_frame_ping_pong;
    /* State +0x34's attack phase in the port; kept separate from impact slots. */
    uint16_t attack_timer;
    /* The source impact instance finishes after its frame span plus the
       completion-check update. It advances on odd global effect ticks. */
    uint8_t attack_impact_frame_counts[4];
    uint8_t attack_effect_active;
    uint8_t attack_effect_odd_updates_remaining;
    /* Raw floater +0x24: death timer for flag 0x008 and pulse counter for
       FA_Cast kind 0x13's flag 0x2000. */
    uint16_t source_death_timer;
    /* Floater runtime short +0x0c gates IWLocInfo CHARGE through
       FUN_004207f2; +0x22 is the mutable charge counter. Initial workers
       start at -1 and 0 respectively. State-6 attacks decrement the target's
       +0x22 through the same 0x4c-byte floater table. */
    int16_t source_link_0c;
    /* Port-side island key for resolving source_link_0c, which stores the
       per-owner 100-byte source-row index returned by FUN_0045c325. */
    uint8_t charge_source_island;
    uint16_t charge_source_location;
    int16_t charge_current;
    uint16_t x;
    uint16_t y;
    uint16_t destination_x;
    uint16_t destination_y;
    uint16_t movement_speed;
    /* FA_DefendFlt keeps its protected floater separate from the current
       combat target resolved into order_target_floater. */
    int16_t defend_target_floater;
    /* FA_DefendFlt state 8: FUN_00423068 stores a random (rand(200) - 100)
       offset pair in +0x28/+0x2a; FUN_00422d27 adds the protected floater's
       position to it every step. */
    int16_t follow_offset_x;
    int16_t follow_offset_y;
    /* Action-9 post-arrival stages mirror tick +0x46 and +0x32. The target
       candidate table/policy for non-enemy units is only partly reconstructed. */
    uint8_t order_progress;
    /* Tick record +0x3c. FUN_0042219e does not replace FA_Cast (0x13). */
    uint8_t active_order_action;
    int16_t order_target_floater;
    int16_t order_target_location;
    uint8_t order_target_island;
    /* FUN_00465793 subtype-3 starts FA_Cast (0x13), glyph spell kind 0x16. */
    uint8_t cast_spell_kind;
    /* FA_Deliver's action-4 order uses the tick record's +0x18 cargo, +0x34
       pickup counter and +0x46 subphase. Hall refill routes can cross islands. */
    int16_t carried_resource_code;
    int16_t order_resource_code;
    int16_t linked_task_slot;
    /* Remake: earliest simulation tick at which a worker may be moved off its
       current task, so long tasks are not abandoned by constant rebalancing. */
    uint32_t task_commit_tick;
    uint16_t order_timer;
    int16_t order_source_location;
    uint8_t order_source_island;
    uint32_t source_runtime_flags;
    /* FUN_00422d27's speed context is resolved before its coordinate step.
       Site bonuses come from the linked source and the owner's glyph mask. */
    uint8_t movement_state;
    /* Remake bookkeeping: state at the previous tick, used to detect the
       FUN_0041e569 post-switch (state finished -> subtype 8 returns to Hall). */
    uint8_t previous_movement_state;
    /* FUN_00466fe4 gives each new world floater a random +0x05 animation phase. */
    uint8_t animation_seed;
    uint8_t near_target_speed_override;
    uint16_t stop_radius;
    /* FUN_0045d8b2's linked 100-byte record fields. FUN_0042219e copies a
       changed coordinate order into the separate tick record; this pending
       flag lets the remake preserve that source boundary before applying it. */
    uint8_t source_order_state_2c;
    uint8_t source_order_island_28;
    uint16_t source_order_coordinate_30;
    /* FUN_0041e569 resolves the source location from floater +0x32 for
       runtime CHARGE states 11/12. */
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
    /* Stable slot lifetime: native death cleanup frees a floater record while
       other records may still keep references to its index. */
    uint8_t is_active;
} GameFloaterStart;

typedef struct GameDefenseProjectile {
    uint8_t active;
    uint8_t island_index;
    uint8_t effect_sheet_index;
    uint8_t animation_tick;
    uint8_t movement_speed;
    uint8_t impact_phase;
    uint8_t impact_realm_index;
    uint8_t impact_frame_start;
    uint8_t impact_frame_count;
    int16_t target_floater;
    int16_t target_location;
    int16_t attack_power;
    uint16_t x;
    uint16_t y;
} GameDefenseProjectile;

static inline int game_session_floater_is_active(
    const GameFloaterStart *floater)
{
    return floater != 0 && floater->is_active != 0;
}

typedef struct GameSession {
    GameSessionConfig config;
    /* Shared LCG after modeled world-start draws; simulation randomness
       advances it, including FA_Wander destination generation. */
    ToneRng random_state;
    /* Island simulation clock for source transitions keyed to the low byte
       of the global tick. */
    uint32_t simulation_tick;
    uint8_t island_count;
    GameStartSetup player_starts;
    GameStartToneDistribution tone_placements;
    /* Baseline type-0 rows used by FUN_00462a87 when recruitment allocates a
       new worker. Keep them separate from mutable live floater state. */
    FloaterStats worker_birth_stats[GAME_START_PLAYER_COUNT];
    uint8_t worker_birth_impact_frame_counts[GAME_START_PLAYER_COUNT][4];
    uint8_t effect_impact_frame_counts[4][4];
    uint8_t effect_impact_frame_starts[4][4];
    GameFloaterStart floaters[GAME_SESSION_MAX_FLOATERS];
    /* Native floater table reserves 256 records; count is a high-water mark
       and needs 16 bits to represent a full table. */
    uint16_t floater_count;
    /* FUN_0041760b's 32 slots are shared between modeled attack and cast
       effects; unmodeled visual instances still remain outside this count. */
    uint8_t active_attack_effect_count;
    /* FUN_0041760b uses the same 32 shared slots for non-attack effects. */
    struct GameCastEffectState {
        uint8_t active;
        uint8_t caster_index;
        uint8_t step;
        uint8_t odd_updates_remaining;
        /* Zero is the fixed-delay path; 1/2/3 model ASCEND, travel, FREEZESC. */
        uint8_t animation_phase;
        uint8_t phase_odd_updates_remaining;
        int16_t target_location_index;
        uint16_t effect_x;
        uint16_t effect_y;
    } cast_effects[GAME_SESSION_MAX_CAST_EFFECTS];
    uint8_t active_cast_effect_count;
    /* Tower bolts reuse the source effect's per-frame target pursuit and
       impact damage path; the platform resolves the source EFFECTS SHP art. */
    GameDefenseProjectile defense_projectiles[32];
    /* FUN_00416a9a's source sound events are drained by the platform adapter. */
    uint8_t audio_event_head;
    uint8_t audio_event_count;
    GameSessionAudioEvent audio_events[GAME_SESSION_MAX_AUDIO_EVENTS];
    /* FUN_004655b2 discovery events drained by FUN_0046bdee's active-window
       type-5 callback. */
    uint8_t world_event_head;
    uint8_t world_event_count;
    GameSessionWorldEvent world_events[GAME_SESSION_MAX_WORLD_EVENTS];
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
    uint8_t cast_action_count;
    GameCastActionRequest cast_actions[GAME_SESSION_MAX_CAST_ACTIONS];
    uint8_t onoff_action_count;
    GameOnOffActionRequest onoff_actions[GAME_SESSION_MAX_ONOFF_ACTIONS];
    /* The IWLocInfo grab/place flow holds one owned building between clicks. */
    uint8_t location_move_active;
    uint8_t location_move_player;
    uint8_t location_move_source_island;
    uint16_t location_move_source_index;
    int16_t location_move_previous_source_46;
    int16_t location_move_previous_source_58;
    uint16_t build_selection_count;
    GameBuildSelectionRequest build_selections[GAME_SESSION_MAX_BUILD_SELECTIONS];
    uint16_t class0_assignments;
    /* Ordered WORLDPOS topology, retained so runtime class-2 completion can
       resolve its reciprocal marker back to the source bridge-table slot. */
    uint8_t world_bridge_count;
    WorldBridge world_bridges[WORLD_MAP_MAX_BRIDGES];
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
