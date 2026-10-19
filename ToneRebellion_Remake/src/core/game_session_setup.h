#ifndef TONE_REBELLION_GAME_SESSION_SETUP_INCLUDED
#define TONE_REBELLION_GAME_SESSION_SETUP_INCLUDED

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

#endif
