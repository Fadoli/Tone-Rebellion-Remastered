#ifndef TONE_REBELLION_GAME_SESSION_WORLD_INCLUDED
#define TONE_REBELLION_GAME_SESSION_WORLD_INCLUDED

#include "game_session_types.h"

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
/* Models the paired-object state change observed in FUN_004669bd; this direct
   helper reads the contributor from the island_a endpoint. The completion
   path below passes the contributor from the actual PROD-completing marker. */
int game_session_mark_bridge_constructed(GameSession *session,
                                         uint8_t bridge_index,
                                         uint8_t bridge_count,
                                         uint8_t island_a,
                                         uint8_t island_b);
/* Resolve a completed class-2 marker through retained WORLDPOS order, then
   apply FUN_004669bd to that marker and its reciprocal endpoint. */
int game_session_mark_bridge_constructed_at(GameSession *session,
                                            uint8_t island_index,
                                            uint16_t location_index);
/* FUN_004669bd reads the contributor/faction slot stored at marker +0x2c and
   acquires the neighbor island for that player. */
int game_session_acquire_island_access(GameSession *session,
                                       uint8_t player_slot,
                                       uint8_t source_island,
                                       uint8_t target_island);
int game_session_set_bridge_active(GameSession *session,
                                   uint8_t bridge_index,
                                   uint8_t bridge_count,
                                   int active);
/* Models FUN_004702d9's WORLDWIN message 0x4f: all counted bridge flags are
   enabled when parameter bit 0x100 is clear and disabled when it is set. */
int game_session_apply_world_bridge_message(GameSession *session,
                                            uint8_t bridge_count,
                                            uint32_t parameter_flags);

#endif
