#ifndef TONE_REBELLION_NET_LOCKSTEP_H
#define TONE_REBELLION_NET_LOCKSTEP_H

#include "game_command.h"

#include <stddef.h>
#include <stdint.h>

/* In-game synchronisation (decompilation/behavior/multiplayer.md). Native model: every
   command is queued with a common future execution tick (FUN_004133f2), the
   host sends the latency period to everyone (channel 4 type 1 -> +0x1278),
   only validates the next period once each guest reported progress
   (FUN_00413088, types 2/6) and a lagging guest runs extra ticks
   (FUN_00413b68, DAT_004bf114). The remake keeps that shape: one turn per
   tick; the host gathers every player's commands into the bundle of turn
   + delay, where the delay follows the measured round trip, and nobody
   simulates a turn before holding its bundle. Bundles carry the host's
   state hash of the turn it just finished so guests detect a
   desynchronisation. Pure state machine; the platform moves bytes. */

enum {
    NET_TURN_TICKS = 1,          /* one 50 ms tick per turn */
    NET_TURN_START_DELAY = 2,    /* turns 0..1 run without a bundle */
    NET_TURN_MIN_DELAY = 1,
    NET_TURN_MAX_DELAY = 10,
    NET_TURN_HOST_LEAD = NET_TURN_MAX_DELAY + 4,  /* host waits for a guest this far behind */
    NET_TURN_WINDOW = 32,
    NET_TURN_MAX_COMMANDS = 48,
    NET_LOCKSTEP_MAX_PLAYERS = 4
};

enum {
    NET_RECORD_COMMAND = 0x50,   /* guest -> host: one GameCommand */
    NET_RECORD_TURN = 0x51,      /* host -> guests: bundle for one turn */
    NET_RECORD_TURN_ACK = 0x52,  /* guest -> host: turns completed */
    NET_RECORD_PING = 0x53,      /* host -> guest: host clock (ms) */
    NET_RECORD_PONG = 0x54       /* guest -> host: the same clock value */
};

typedef struct NetTurnBundle {
    uint8_t valid;
    uint8_t has_hash;
    uint8_t command_count;
    uint8_t delay;               /* host delay when the bundle was made */
    uint32_t turn;
    uint32_t hash_turn;          /* turn whose end state `hash` describes */
    uint32_t hash;
    GameCommand commands[NET_TURN_MAX_COMMANDS];
} NetTurnBundle;

typedef struct NetLockstep {
    uint8_t is_host;
    uint8_t peer_mask;           /* host: guest slots that must acknowledge */
    uint8_t desync;
    uint8_t delay;               /* host: turns between bundling and running;
                                    guest: the delay of the latest bundle */
    uint32_t desync_turn;
    uint32_t tick;               /* ticks simulated since the start */
    uint32_t latest_bundle_turn; /* highest bundle turn held, plus one */
    uint32_t acked[NET_LOCKSTEP_MAX_PLAYERS];   /* host: turns completed per guest */
    uint32_t local_hashes[NET_TURN_WINDOW];
    uint32_t local_hash_turns[NET_TURN_WINDOW];
    uint8_t local_hash_valid[NET_TURN_WINDOW];
    uint32_t remote_hashes[NET_TURN_WINDOW];
    uint32_t remote_hash_turns[NET_TURN_WINDOW];
    uint8_t remote_hash_valid[NET_TURN_WINDOW];
    NetTurnBundle bundles[NET_TURN_WINDOW];
    uint8_t pending_count;       /* host: commands for the next bundle */
    GameCommand pending[NET_TURN_MAX_COMMANDS];
} NetLockstep;

void net_lockstep_init(NetLockstep *lockstep, int is_host, uint8_t peer_mask);
uint32_t net_lockstep_turn(const NetLockstep *lockstep);
/* Host: turns of input delay covering half the slowest guest round trip
   plus one turn of margin, clamped to NET_TURN_MIN/MAX_DELAY. */
uint8_t net_lockstep_delay_for_round_trip(uint32_t round_trip_ms, uint32_t tick_ms);
void net_lockstep_set_delay(NetLockstep *lockstep, uint8_t delay);
/* Host: adds a command to the next bundle; 0 if the bundle is full. */
int net_lockstep_queue_command(NetLockstep *lockstep, const GameCommand *command);
/* 1 when the next tick may run (its turn's bundle is held and, for the host,
   no guest lags NET_TURN_HOST_LEAD turns or more). */
int net_lockstep_can_tick(const NetLockstep *lockstep);
/* Turns the guest could still run without waiting. */
uint32_t net_lockstep_turns_ready(const NetLockstep *lockstep);
/* Ticks to run this frame (1..3). A guest holding more than delay + 1
   turns lags the host (a frame that fired just before a bundle arrived
   stalled) and runs extra ticks until it is back within one turn, as
   FUN_00413b68 raises DAT_004bf114 for a lagging machine. */
unsigned net_lockstep_frame_ticks(const NetLockstep *lockstep);
/* Commands to apply before the next tick, or NULL (not a turn start). */
const NetTurnBundle *net_lockstep_turn_commands(const NetLockstep *lockstep);
/* After one simulated tick. Returns the number of bundles the host created
   (0..capacity, normally 1; more when the delay grew, 0 when it shrank) and
   copies them to `out`; a guest always gets 0. */
size_t net_lockstep_finish_tick(NetLockstep *lockstep, uint32_t session_hash,
                                NetTurnBundle *out, size_t capacity);
int net_lockstep_receive_bundle(NetLockstep *lockstep, const NetTurnBundle *bundle);
void net_lockstep_receive_ack(NetLockstep *lockstep, uint8_t slot, uint32_t turns_done);
void net_lockstep_drop_peer(NetLockstep *lockstep, uint8_t slot);
/* Reconnection (remake). Host: a guest that rejoins at `turn` (it receives
   the state at the start of that turn, then the bundles from it on). */
void net_lockstep_add_peer(NetLockstep *lockstep, uint8_t slot, uint32_t turn);
/* Host: the bundle of `turn` still in the window, or NULL. */
const NetTurnBundle *net_lockstep_bundle(const NetLockstep *lockstep, uint32_t turn);
/* Guest: restarts the lockstep at `turn` with no bundle held. */
void net_lockstep_resume_at(NetLockstep *lockstep, uint32_t turn);

size_t net_lockstep_encode_bundle(const NetTurnBundle *bundle, uint8_t *payload, size_t capacity);
int net_lockstep_decode_bundle(const uint8_t *payload, size_t length, NetTurnBundle *bundle);

#endif
