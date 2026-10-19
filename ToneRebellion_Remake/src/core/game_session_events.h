#ifndef TONE_REBELLION_GAME_SESSION_EVENTS_INCLUDED
#define TONE_REBELLION_GAME_SESSION_EVENTS_INCLUDED

#include "game_session_types.h"

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
/* FUN_004239e9 cases 7/9 resolve the blast and selected-site impacts; case
   0x16 applies the 30000 site effect when the item matches the player key. */
unsigned int game_session_resolve_cast_effect_step(
    GameSession *session, unsigned int caster_index, uint8_t step,
    int16_t target_location_index);
/* Reserve a source effect slot. For case 7/9/0x16, a positive delay counts odd
   effect updates; case 0x16 with delay 0 runs ASCEND, UPGRADE travel and the
   FREEZESC impact transition from the loaded source descriptors. */
int game_session_schedule_cast_effect_step(
    GameSession *session, unsigned int caster_index, uint8_t step,
    int16_t target_location_index, uint8_t odd_updates_until_impact);
/* FUN_0041760b advances scheduled cast impacts on odd source ticks. */
void game_session_tick_cast_effects(GameSession *session,
                                    uint32_t source_tick);
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
