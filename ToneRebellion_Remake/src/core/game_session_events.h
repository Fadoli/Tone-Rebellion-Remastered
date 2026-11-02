#ifndef TONE_REBELLION_GAME_SESSION_EVENTS_INCLUDED
#define TONE_REBELLION_GAME_SESSION_EVENTS_INCLUDED

#include "game_session_types.h"
#include "pad_catalog.h"

/* FUN_004455d1 projects active 0x14-byte slots for one player, omits action
   type 0xb, preserves table order, and caps the list at 32. Returns the total
   projected count, writing at most capacity source slot indices. */
size_t game_session_collect_task_slots(const GameSession *session,
                                       int16_t player_id,
                                       uint8_t *slot_indices,
                                       size_t capacity);
/* Remake addition (no native draw/click path found): slot of the player's
   active CONSTR (type 5) task on island/location, or -1. */
int game_session_construction_task_slot(const GameSession *session,
                                        int16_t player_id, uint16_t island,
                                        uint16_t location);
/* FUN_00465793 category-3 subtypes 12..15 match the queued record by player,
   payload_0a, action_type and payload_12 before cancelling or changing its
   priority. `expected` is the task snapshot used to form the command. */
int game_session_dispatch_task_command(GameSession *session, uint8_t slot,
                                       uint8_t subtype,
                                       const GamePendingEvent *expected);
/* FUN_0042fa0f(0x39): Obtain button on a selected PIT_Object. Posts a type
   0xd task record; a free worker attaches to it later (FUN_0042219e). Returns
   1 when a new task was queued, 0 for a duplicate, a full table or a site
   that is not a loose ground object. */
int game_session_queue_obtain_task(GameSession *session, uint8_t player_slot,
                                   uint8_t island_index,
                                   uint16_t location_index);
/* FUN_00460029 releases every modeled task record targeting one island site. */
unsigned int game_session_cancel_tasks_for_location(GameSession *session,
                                                    uint8_t island_index,
                                                    uint16_t location_index);
/* FUN_0042fa0f(0x40): queue an inventory-use request for a clicked island
   location. Mirrors its class-0 occupied-location rejection and stores the
   source's island/location/item payload; it does not apply the item effect or
   debit inventory before the later result event succeeds. */
int game_session_queue_inventory_action(GameSession *session,
                                        uint8_t player_slot,
                                        uint8_t island_index,
                                        uint16_t location_index,
                                        uint8_t item_id);
/* FUN_004672ef command type 3 cycles the supported player source records
   through capacity tiers 0..3. The source setter resets +0x48 and marks bit
   0x20 only when the tier increases. */
int game_session_cycle_source_capacity(GameSession *session,
                                       uint8_t island_index,
                                       uint16_t location_index);
/* FUN_0045c9b5 / FUN_0045ca1e toggle a Build Tone task on staff sources;
   completion is applied by the source tick once local stock exceeds 19. */
int game_session_toggle_staff_upgrade_request(GameSession *session,
                                              uint8_t player_slot,
                                              uint8_t island_index,
                                              uint16_t location_index);
/* UpgSpread (BC_UpgSpread, list index 20; FUN_00452bc5 gate, FUN_0045fe62
   entry): offered on another tribe's base-0x28 block while the player has
   neither finished nor refused it. The entry is a type-4 delivery task for
   item 1 on that block; ten deliveries (FUN_004503bd) set site flag
   0x800 << player and retire the entry. */
int game_session_upgspread_available(const GameSession *session,
                                     uint8_t player_slot, uint8_t island_index,
                                     uint16_t location_index);
int game_session_upgspread_active(const GameSession *session,
                                  uint8_t player_slot, uint8_t island_index,
                                  uint16_t location_index);
int game_session_toggle_upgspread(GameSession *session, uint8_t player_slot,
                                  uint8_t island_index, uint16_t location_index);
/* Repair (BC_Repair, FUN_00465793 cat 1 code 3): an owned building of item
   0x25..0x34 below its FUN_00450978 maximum toggles a repair entry; adding
   it queues a type-4 item-1 (Build Tone) row (FUN_0045fd91 ->
   FUN_004666c9), removing it frees that row (FUN_0045ff9b). */
int game_session_repair_available(const GameSession *session,
                                  const PadCatalog *catalog,
                                  uint8_t player_slot, uint8_t island_index,
                                  uint16_t location_index);
int game_session_repair_listed(const GameSession *session,
                               uint8_t player_slot, uint8_t island_index,
                               uint16_t location_index);
int game_session_toggle_repair(GameSession *session, const PadCatalog *catalog,
                               uint8_t player_slot, uint8_t island_index,
                               uint16_t location_index);
/* FUN_00460029: drop every repair entry (and its row) of a location. */
void game_session_clear_repair_entries(GameSession *session,
                                       uint8_t island_index,
                                       uint16_t location_index);
/* Returns nonzero when the task slot is the player's UpgSpread entry on the
   location and fills island/location. */
int game_session_upgspread_task_target(const GameSession *session,
                                       uint8_t player_slot, int16_t task_slot,
                                       uint8_t *island_index,
                                       uint16_t *location_index);
int game_session_complete_staff_upgrade(GameSession *session,
                                        const PadCatalog *catalog,
                                        uint8_t island_index,
                                        uint16_t location_index);
/* Applies FUN_00450847 to a resolved FA_Cast target using the effect amount
   chosen by the cast substep. Also mirrors the known FUN_00452ae7/
   FUN_00452a15 location reset when the effect consumes the site. */
int32_t game_session_apply_cast_site_effect(GameSession *session,
                                            uint8_t island_index,
                                            uint16_t location_index,
                                            int16_t effect_amount);
/* FUN_004239e9 case 7: apply direct distance-scaled damage to nearby floaters
   and route nearby sites through FUN_00450817. Returns affected targets. */
unsigned int game_session_apply_cast_blast(GameSession *session,
                                           unsigned int caster_index);
/* FUN_004239e9 cases 1 and 3..9, 0xc..0x13 apply reconstructed site state,
   source pulses, charge buffs, refill, timer, area-damage, pickup and
   selected-site effects; case 2 restores eligible floater HP; case 0x14
   refreshes the island's Leviathan reevaluation; case 0x15 boosts owner
   subtype-0 floaters; case 0x16 applies its site effect. */
unsigned int game_session_resolve_cast_effect_step(
    GameSession *session, const PadCatalog *catalog,
    unsigned int caster_index, uint8_t step,
    int16_t target_location_index);
/* FUN_0041660b at cast tick 10: reserve a shared effect slot at the
   caster. The slot plays the start sprite, travels to the target site and
   plays the finish sprite of its spell (FUN_0041760b); FUN_004239e9 applies
   the spell at the end of that animation. */
enum {
    GAME_CAST_PHASE_START = 0,
    GAME_CAST_PHASE_TRAVEL = 1,
    GAME_CAST_PHASE_FINISH = 2,
    GAME_CAST_PHASE_DESTSUPP_TRAVEL = 3,
    GAME_CAST_PHASE_FAROBT = 4,
    GAME_CAST_PHASE_KILLBEAS = 5
};
int game_session_schedule_cast_effect_step(
    GameSession *session, unsigned int caster_index, uint8_t step,
    int16_t target_location_index);
/* FUN_0041760b advances scheduled cast impacts on odd source ticks. */
void game_session_tick_cast_effects(GameSession *session,
                                    uint32_t source_tick,
                                    const PadCatalog *catalog);
/* FUN_0046290d/FUN_00450a71 advance per-site timers and the 0x100/+0x44 state. */
void game_session_tick_site_effect_timers(GameSession *session);
/* FUN_0042fa0f(0x40) emits category-3/type-3 with player, island, location,
   and selected glyph. The island dispatcher assigns kind 0x16 to the first
   matching subtype-8 floater; cast animation and impact timing remain open. */
int game_session_queue_glyph_action(GameSession *session,
                                    uint8_t player_slot,
                                    uint8_t island_index,
                                    uint16_t location_index,
                                    uint8_t glyph_index);
int game_session_pop_glyph_action(GameSession *session,
                                  GameGlyphActionRequest *out);
/* FUN_00465793 category-3/subtype-3 selects the first player subtype-8
   floater and assigns its FA_Cast glyph order. */
unsigned int game_session_dispatch_glyph_actions(GameSession *session);
/* Queue category-1 subtype 0x15..0x1c spell orders. */
int game_session_queue_cast_action(GameSession *session,
                                   uint8_t player_slot,
                                   uint8_t island_index,
                                   uint16_t location_index,
                                   uint8_t action_subtype);
int game_session_queue_cast_action_target(GameSession *session,
                                          uint8_t player_slot,
                                          uint8_t island_index,
                                          uint16_t location_index,
                                          uint8_t action_subtype,
                                          int16_t target_floater_index);
/* Same with an explicit target site (msg 0x40 armed pick); a negative
   target_location keeps the caster building as the target. */
int game_session_queue_cast_action_at(GameSession *session,
                                      uint8_t player_slot,
                                      uint8_t island_index,
                                      uint16_t location_index,
                                      uint8_t action_subtype,
                                      uint8_t target_island,
                                      int16_t target_location,
                                      int16_t target_floater_index);
/* DAT_004a2898[kind] read by FUN_0042fa0f / FUN_0043530b: 0 sends the cast
   at once, 1 arms a site pick (msg 0x40), 2 a floater pick (msg 0x41). */
int game_session_cast_kind_target_pick(int kind);
int game_session_cast_kind_for_action(uint8_t owner, uint8_t action_subtype);
/* effects.txt SOUND of the effect FUN_0041660b spawns for FA_Cast `kind`:
   0..3 are the owner-indexed PSPELL/SSPELL/MSPELL/LSPELL defaults, then
   FLTARMOR, FASTPROD, SACRIF, KILLBEAS, DESTSUPP, ASCEND. */
enum {
    GAME_CAST_SOUND_COUNT = 10
};
int game_session_cast_sound_id(uint8_t kind, uint8_t owner);
/* Cast visuals: effects.txt SPECIAL records. Indices 0..9 share the order of
   game_session_cast_sound_id (PCAST/SCAST/MCAST/LCAST, SPL6E, SPL13, SPL20,
   SPL5, SPL04, ACAST); then UPGRADE (SPL8B), FREEZESC (SPL21), FREEZELB,
   LOCPROT, BUILDTON, HYPERHEAL, REPAIR, STOCKUP, BLDARMOR, REVPLOT, FASTFLT,
   BLASTWB and FAROBT. Frames step once per odd update (FUN_00415063). */
enum { GAME_CAST_VISUAL_COUNT = 23 };
/* fltinf atteff visual (FUN_00415fc6 path A): def index into
   attack_effect_defs, absolute frame in that def's shape, world position.
   After arrival the slot turns into the realm IMPACT: `impact_realm` is then
   0..3 and `frame` indexes that realm's impact sheet (def is -1). */
int game_session_attack_visual(const GameSession *session, unsigned int slot,
                               int *def, unsigned int *frame, uint16_t *x,
                               uint16_t *y, uint8_t *island,
                               int *impact_realm);
/* One stacked LIGHTNING sprite (FUN_004182c8): world position, zero-based
   frame in the effect's shape and mirror flag. */
typedef struct GameLightningSegment {
    int32_t x;
    int32_t y;
    uint8_t frame;
    uint8_t mirrored;
} GameLightningSegment;
enum { GAME_LIGHTNING_MAX_SEGMENTS = 10 };
/* Visible segments of a LIGHTNING visual, bottom to top as drawn; returns the
   count (0 when the slot is not an active lightning). */
int game_session_lightning_segments(const GameSession *session,
                                    unsigned int slot,
                                    GameLightningSegment out[GAME_LIGHTNING_MAX_SEGMENTS]);
/* Horizontal mirror flag of an active attack visual (slot flag 0x1). */
int game_session_attack_visual_mirrored(const GameSession *session,
                                        unsigned int slot);
/* Hit IMPACT of an active floater attack (realm 0..3 = PHY/SUP/ETH/NAT,
   absolute frame in that realm's impact sheet, world x/y). */
int game_session_attack_effect_visual(const GameSession *session,
                                      unsigned int floater_index,
                                      unsigned int *realm,
                                      unsigned int *frame,
                                      uint16_t *x, uint16_t *y);
/* Visual id and zero-based frame of an active cast effect slot; returns 0
   when the slot has nothing to draw. */
int game_session_cast_effect_visual(const GameSession *session,
                                    unsigned int slot, int *visual,
                                    unsigned int *frame);
/* FUN_004182c8's KILLBEAS and FAROBT branches: up to three sprites in world
   coordinates. `visual` is a cast visual or GAME_CAST_SPRITE_OBJECT (the
   TRIGGERS object sheet); `stipple` 1..7 draws through the FUN_00410bd2
   reveal mask, 8 is opaque. Returns -1 for a slot drawn by
   game_session_cast_effect_visual. */
enum { GAME_CAST_SPRITE_OBJECT = -1 };
typedef struct GameCastSprite {
    int visual;
    unsigned int frame;
    int32_t x;
    int32_t y;
    uint8_t stipple;
} GameCastSprite;
int game_session_cast_special_sprites(const GameSession *session,
                                      unsigned int slot,
                                      GameCastSprite out[3]);
/* `island` is the caster's island: the sound is only audible while that island
   is being viewed. */
int game_session_queue_cast_audio(GameSession *session, uint8_t island,
                                  uint8_t sound);
/* spells.txt MagCost/CryCost for a native spell kind 0..21. */
/* FUN_0045d8f4 >= 0: a linked floater of the player can cast spell `kind`
   from that building (IWTextInfo mode 4 draws the name in colour 2 when
   not). */
int game_session_spell_has_caster(const GameSession *session,
                                  uint8_t island_index, uint16_t location_index,
                                  uint8_t player_slot, unsigned int kind);
int game_session_cast_kind_costs(int kind, uint16_t *magic_cost,
                                 uint16_t *crystal_cost);
unsigned int game_session_dispatch_cast_actions(GameSession *session);
/* BC_OnOff's established message route. */
int game_session_queue_onoff_action(GameSession *session,
                                    uint8_t player_slot,
                                    uint8_t island_index,
                                    uint16_t location_index);
int game_session_pop_onoff_action(GameSession *session,
                                  GameOnOffActionRequest *out);
/* Applies FUN_00453bf6: OFF clears bit 0x400; ON compares the pad maintenance
   value with the supplied per-player source budget. Also updates active bit 0
   through the observed FUN_00453958/FUN_004539e9 predicate and releases linked
   subtype 1..3 tasks on OFF. */
unsigned int game_session_dispatch_onoff_actions(GameSession *session,
                                                 const PadCatalog *catalog);
/* Recompute runtime active bit 0 using FUN_00453958's observed predicate. */
unsigned int game_session_recalculate_active_locations(GameSession *session);
/* FUN_00466b09 calls FUN_00462285 for the newly reached island and player. */
int game_session_recalculate_player_island_visibility(
    GameSession *session, uint8_t island_index, uint8_t player_slot);
/* Remake: 1 when map x (0..2559) lies in a cell the player has explored. */
int game_session_island_x_explored(const GameSession *session,
                                   uint8_t island_index, uint8_t player_slot,
                                   int x);
void game_session_recalculate_leviathan_island(GameSession *session,
                                               uint8_t island_index);
/* FUN_00464e4d victory branch (local L == 0): one world tick of sequence
   states 2..5. Returns the queued window state (2 = world view at tick 100
   of state 3, 7 = end screen at tick 100 of state 5) or -1. */
int game_session_tick_world_sequence(GameSession *session);
/* FUN_00464e4d's FUN_00410765 fade level (0 = normal, 256 = black) for the
   current world sequence state and tick; `local_tribe` selects the
   DAT_00619248 + tribe * 0x14a0 latch tested in state 5. */
int game_session_world_fade_level(const GameSession *session,
                                  uint8_t local_tribe);
/* FUN_00464e4d state 2 events, run before game_session_tick_world_sequence:
   tick 0 flags the last island's first seal site and kills its Leviathans;
   tick 40 pairs every player floater there (sub-type != 8) with a new
   Leviathan through FA_MergeWith. */
void game_session_world_sequence_state2_events(GameSession *session,
                                               const FloaterCatalog *catalog);
/* FUN_00460989 tail: on a world tick t (DAT_00618e44, read before
   FUN_00466ce2 increments it) with t % 6000 == 0 and k = t / 6000 - 1 < 8,
   queue world event 10 with argument k: -1 is the AWAKE<player> notice,
   0..7 the LEVIBRK + BOND<k> notice. Call after game_session_tick_leviathan_ai
   (simulation_tick is already t + 1 then). Returns 1 and sets *bond. */
int game_session_leviathan_bond_notice(const GameSession *session,
                                       int32_t *bond);
void game_session_tick_leviathan_ai(GameSession *session);
/* Queue/pop source event IDs 2 (build), 3 (bridge), and the modeled floater
   birth event for the platform audio adapter. */
int game_session_queue_effect_sound(GameSession *session, int def_index,
                                    uint8_t island, int32_t x);
int game_session_effect_def_index(const GameSession *session,
                                  const char *name);
int game_session_impact_def_index(const GameSession *session,
                                  unsigned int realm);
void game_session_set_last_audio_x(GameSession *session, int32_t x);
int game_session_queue_audio_event(GameSession *session, uint8_t kind,
                                   int16_t owner_id);
/* Same as above, tagged with the effect instance's island (+0x08). */
int game_session_queue_audio_event_at(GameSession *session, uint8_t kind,
                                      int16_t owner_id, uint8_t island);
/* FUN_004181a6's play gate for an event popped from the queue. */
int game_session_audio_event_is_audible(const GameSessionAudioEvent *event,
                                        int island_screen,
                                        int viewed_island);
int game_session_pop_audio_event(GameSession *session,
                                 GameSessionAudioEvent *out);
/* FUN_004655b2 queues world events; type 12 is emitted when a player reaches
   a new island and carries that island's WORLDPOS level in payload. */
int game_session_queue_world_event(GameSession *session, uint8_t kind,
                                   uint8_t island_index, int32_t payload);
int game_session_pop_world_event(GameSession *session,
                                 GameSessionWorldEvent *out);
/* Rebuild all player budgets after glyph, ownership, or site state changes. */
void game_session_refresh_player_maintenance_budgets(GameSession *session);
/* FUN_004539e9 updates one site's active bit, including its visibility gate. */
int game_session_recalculate_location_active_with_visibility(
    GameRuntimeLocation *location);
/* FUN_0042fa0f(0x34): retain the observed category-0/type-5 selection packet
   for the active island location. The final synchronized consumer is unknown. */
int game_session_queue_build_selection(GameSession *session,
                                       uint8_t player_slot,
                                       uint8_t island_index,
                                       uint16_t location_index,
                                       uint16_t item_id);
int game_session_pop_build_selection(GameSession *session,
                                     GameBuildSelectionRequest *out);
/* FUN_00466221 drains the local event queue; category 0 routes through
   FUN_00465793 to FUN_004662b7, which stores type-5 requests as task slots. */
unsigned int game_session_dispatch_build_selections(GameSession *session);
/* Advance local CONSTR resource deliveries and place completed buildings. */
void game_session_update_construction_tasks(GameSession *session,
                                             const PadCatalog *catalog);
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
