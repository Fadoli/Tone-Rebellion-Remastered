#ifndef TONE_REBELLION_GAME_SESSION_H
#define TONE_REBELLION_GAME_SESSION_H

#include "game_session_types.h"

int game_session_initialize(const WorldDefinition *world,
                            const IslandData *islands_by_world_index,
                            const PadCatalog *pad_catalog,
                            const FloaterCatalog *floater_catalog,
                            const GameSessionConfig *config,
                            GameSession *out,
                            char *error, size_t error_capacity);

/* FUN_0044338b shows CHARGE only when source_link_0c != -1 and obtains its
   denominator from the floater type/subtype row's +0x08 value. */
int game_session_floater_charge_values(const GameFloaterStart *floater,
                                       const FloaterCatalog *catalog,
                                       int16_t *current, int16_t *maximum);

/* FUN_004459e6 uses payload +0x0a as island and +0x0e as location. Repair
   reads current +0x34 and FUN_00450978 maximum at that target. */
int game_session_repair_task_values(const GameSession *session,
                                    const PadCatalog *pad_catalog,
                                    const GamePendingEvent *event,
                                    int16_t *current, int16_t *maximum);
/* Reads the same runtime +0x34 / FUN_00450978 values for a location, without
   requiring a queued REPAIR event. */
int game_session_repair_location_values(const GameSession *session,
                                        const PadCatalog *pad_catalog,
                                        uint8_t island_index,
                                        uint16_t location_index,
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
/* Advance idle FA_Wander routes and simulation-assigned destinations through
   the FUN_00422d27 step kernel. Player input must not call this as an order. */
void game_session_tick_floater_moves(GameSession *session, uint32_t source_tick);
/* FUN_0042fa0f's map-ground mode 0x13 enters FUN_0045d8b2 with runtime state
   9 and a coordinate packed by FUN_0041e3eb (rounded to 10-pixel units).
   The remake exposes it only for non-worker floaters, matching the user's
   source-control constraint. Returns nonzero when the order is accepted. */
int game_session_order_floater_to_coordinate(GameSession *session,
                                             uint8_t player_slot,
                                             uint8_t island_index,
                                             unsigned int floater_index,
                                             uint16_t x,
                                             uint16_t y);
/* Hit test the visible island's active floaters in session order. The original
   FUN_00435581 uses Chebyshev distance < 0x14 (20) for floater selection. */
int game_session_floater_at(const GameSession *session,
                            uint8_t island_index,
                            uint16_t x,
                            uint16_t y);
/* Counts modeled floaters by remake owner_slot. The source Hall metric uses
   the floater type/subtype pair instead; see game_session_workstr_summary. */
unsigned int game_session_count_player_floaters(const GameSession *session,
                                                uint8_t player_slot);
/* FUN_00440567 displays WORKSTR from FUN_0046562b(category, 0) and
   FUN_0046562b(category, -1). `count` is subtype 0 and `total` is all modeled
   subtypes; percentage is meaningful only when total is nonzero. */
int game_session_workstr_summary(const GameSession *session,
                                 uint8_t type_index,
                                 unsigned int *count,
                                 unsigned int *total,
                                 unsigned int *percentage);
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
/* FUN_00465793 subtype 0xb: apply each nonnegative amount up to the source
   Hall's signed-short stock, moving it to the target Hall. */
int game_session_apply_trade_request(GameSession *session,
                                     const GameTradeRequest *request);
/* Consume queued local type-0xb requests in order. A request whose source or
   target Hall is unavailable remains queued for a later tick. */
int game_session_dispatch_trade_requests(GameSession *session);
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
/* FUN_00465793 category-3/subtype-4: only attempt an item result when its
   inventory count is positive, and debit one after the receiver succeeds.
   `apply` models FUN_004503bd and must not modify inventory_count itself. */
int game_session_dispatch_inventory_result(
    GameSession *session, uint8_t player_slot, uint8_t item_id,
    GameInventoryResultApply apply, void *context);
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
