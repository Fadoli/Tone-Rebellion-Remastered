#include "net_lockstep.h"

#include <string.h>

void net_lockstep_init(NetLockstep *lockstep, int is_host, uint8_t peer_mask)
{
    if (lockstep == NULL) return;
    memset(lockstep, 0, sizeof(*lockstep));
    lockstep->is_host = is_host != 0;
    lockstep->peer_mask = is_host ? peer_mask : 0;
    lockstep->delay = NET_TURN_START_DELAY;
    /* Turns before NET_TURN_START_DELAY have no bundle: nobody could have
       issued a command for them. */
    lockstep->latest_bundle_turn = NET_TURN_START_DELAY;
}

uint8_t net_lockstep_delay_for_round_trip(uint32_t round_trip_ms, uint32_t tick_ms)
{
    uint32_t delay;
    if (tick_ms == 0U) tick_ms = 1U;
    delay = 1U + (round_trip_ms / 2U + tick_ms - 1U) / tick_ms;
    if (delay < NET_TURN_MIN_DELAY) delay = NET_TURN_MIN_DELAY;
    if (delay > NET_TURN_MAX_DELAY) delay = NET_TURN_MAX_DELAY;
    return (uint8_t)delay;
}

void net_lockstep_set_delay(NetLockstep *lockstep, uint8_t delay)
{
    if (lockstep == NULL || !lockstep->is_host) return;
    if (delay < NET_TURN_MIN_DELAY) delay = NET_TURN_MIN_DELAY;
    if (delay > NET_TURN_MAX_DELAY) delay = NET_TURN_MAX_DELAY;
    lockstep->delay = delay;
}

uint32_t net_lockstep_turn(const NetLockstep *lockstep)
{
    return lockstep != NULL ? lockstep->tick / NET_TURN_TICKS : 0;
}

int net_lockstep_queue_command(NetLockstep *lockstep, const GameCommand *command)
{
    if (lockstep == NULL || command == NULL || !lockstep->is_host ||
        lockstep->pending_count >= NET_TURN_MAX_COMMANDS) return 0;
    lockstep->pending[lockstep->pending_count++] = *command;
    return 1;
}

static int bundle_held(const NetLockstep *lockstep, uint32_t turn)
{
    const NetTurnBundle *bundle = &lockstep->bundles[turn % NET_TURN_WINDOW];
    return turn < NET_TURN_START_DELAY || (bundle->valid && bundle->turn == turn);
}

int net_lockstep_can_tick(const NetLockstep *lockstep)
{
    uint32_t turn;
    unsigned slot;
    if (lockstep == NULL || lockstep->desync) return 0;
    if (lockstep->tick % NET_TURN_TICKS != 0U) return 1;
    turn = lockstep->tick / NET_TURN_TICKS;
    if (!bundle_held(lockstep, turn)) return 0;
    if (lockstep->is_host) {
        for (slot = 0; slot < NET_LOCKSTEP_MAX_PLAYERS; ++slot)
            if ((lockstep->peer_mask & (1U << slot)) &&
                lockstep->acked[slot] + NET_TURN_HOST_LEAD <= turn) return 0;
    }
    return 1;
}

uint32_t net_lockstep_turns_ready(const NetLockstep *lockstep)
{
    uint32_t turn = net_lockstep_turn(lockstep);
    if (lockstep == NULL || lockstep->latest_bundle_turn <= turn) return 0;
    return lockstep->latest_bundle_turn - turn;
}

unsigned net_lockstep_frame_ticks(const NetLockstep *lockstep)
{
    uint32_t ready = net_lockstep_turns_ready(lockstep);
    uint32_t lag;
    if (lockstep == NULL || lockstep->is_host || ready <= (uint32_t)lockstep->delay + 1U)
        return 1;
    lag = ready - lockstep->delay;
    return lag >= 4U ? 3U : 2U;
}

const NetTurnBundle *net_lockstep_turn_commands(const NetLockstep *lockstep)
{
    uint32_t turn;
    const NetTurnBundle *bundle;
    if (lockstep == NULL || lockstep->tick % NET_TURN_TICKS != 0U) return NULL;
    turn = lockstep->tick / NET_TURN_TICKS;
    bundle = &lockstep->bundles[turn % NET_TURN_WINDOW];
    return bundle->valid && bundle->turn == turn ? bundle : NULL;
}

static void compare_hash(NetLockstep *lockstep, uint32_t turn)
{
    unsigned index = turn % NET_TURN_WINDOW;
    if (lockstep->local_hash_valid[index] && lockstep->local_hash_turns[index] == turn &&
        lockstep->remote_hash_valid[index] && lockstep->remote_hash_turns[index] == turn &&
        lockstep->local_hashes[index] != lockstep->remote_hashes[index] &&
        !lockstep->desync) {
        lockstep->desync = 1;
        lockstep->desync_turn = turn;
    }
}

size_t net_lockstep_finish_tick(NetLockstep *lockstep, uint32_t session_hash,
                                NetTurnBundle *out, size_t capacity)
{
    uint32_t turn;
    uint32_t target;
    unsigned index;
    size_t created = 0;
    if (lockstep == NULL) return 0;
    ++lockstep->tick;
    if (lockstep->tick % NET_TURN_TICKS != 0U) return 0;
    turn = lockstep->tick / NET_TURN_TICKS - 1U;
    index = turn % NET_TURN_WINDOW;
    lockstep->local_hashes[index] = session_hash;
    lockstep->local_hash_turns[index] = turn;
    lockstep->local_hash_valid[index] = 1;
    compare_hash(lockstep, turn);
    if (!lockstep->is_host) return 0;
    /* One bundle per turn, none skipped: a grown delay emits the missing
       turns empty; a shrunk delay emits nothing and keeps the commands. */
    target = turn + lockstep->delay;
    while (lockstep->latest_bundle_turn <= target) {
        NetTurnBundle *bundle =
            &lockstep->bundles[lockstep->latest_bundle_turn % NET_TURN_WINDOW];
        memset(bundle, 0, sizeof(*bundle));
        bundle->valid = 1;
        bundle->turn = lockstep->latest_bundle_turn++;
        bundle->delay = lockstep->delay;
        if (created == 0U) {
            bundle->has_hash = 1;
            bundle->hash_turn = turn;
            bundle->hash = session_hash;
            bundle->command_count = lockstep->pending_count;
            memcpy(bundle->commands, lockstep->pending,
                   sizeof(GameCommand) * lockstep->pending_count);
            lockstep->pending_count = 0;
        }
        if (out != NULL && created < capacity) out[created] = *bundle;
        ++created;
    }
    return created < capacity ? created : capacity;
}

int net_lockstep_receive_bundle(NetLockstep *lockstep, const NetTurnBundle *bundle)
{
    if (lockstep == NULL || bundle == NULL || lockstep->is_host || !bundle->valid ||
        bundle->turn < net_lockstep_turn(lockstep) ||
        bundle->turn >= net_lockstep_turn(lockstep) + NET_TURN_WINDOW) return 0;
    lockstep->bundles[bundle->turn % NET_TURN_WINDOW] = *bundle;
    if (bundle->turn + 1U > lockstep->latest_bundle_turn) {
        lockstep->latest_bundle_turn = bundle->turn + 1U;
        lockstep->delay = bundle->delay;
    }
    if (bundle->has_hash) {
        unsigned index = bundle->hash_turn % NET_TURN_WINDOW;
        lockstep->remote_hashes[index] = bundle->hash;
        lockstep->remote_hash_turns[index] = bundle->hash_turn;
        lockstep->remote_hash_valid[index] = 1;
        compare_hash(lockstep, bundle->hash_turn);
    }
    return 1;
}

void net_lockstep_receive_ack(NetLockstep *lockstep, uint8_t slot, uint32_t turns_done)
{
    if (lockstep == NULL || slot >= NET_LOCKSTEP_MAX_PLAYERS) return;
    if (turns_done > lockstep->acked[slot]) lockstep->acked[slot] = turns_done;
}

void net_lockstep_drop_peer(NetLockstep *lockstep, uint8_t slot)
{
    if (lockstep == NULL || slot >= NET_LOCKSTEP_MAX_PLAYERS) return;
    lockstep->peer_mask &= (uint8_t)~(1U << slot);
}

void net_lockstep_add_peer(NetLockstep *lockstep, uint8_t slot, uint32_t turn)
{
    if (lockstep == NULL || !lockstep->is_host || slot >= NET_LOCKSTEP_MAX_PLAYERS) return;
    lockstep->peer_mask |= (uint8_t)(1U << slot);
    lockstep->acked[slot] = turn;
}

const NetTurnBundle *net_lockstep_bundle(const NetLockstep *lockstep, uint32_t turn)
{
    const NetTurnBundle *bundle;
    if (lockstep == NULL) return NULL;
    bundle = &lockstep->bundles[turn % NET_TURN_WINDOW];
    return bundle->valid && bundle->turn == turn ? bundle : NULL;
}

void net_lockstep_resume_at(NetLockstep *lockstep, uint32_t turn)
{
    if (lockstep == NULL) return;
    net_lockstep_init(lockstep, 0, 0);
    lockstep->tick = turn * NET_TURN_TICKS;
    lockstep->latest_bundle_turn = turn;
}

/* Payload: turn, hash turn, hash (LE dwords), has_hash, count, delay, commands. */
size_t net_lockstep_encode_bundle(const NetTurnBundle *bundle, uint8_t *payload, size_t capacity)
{
    size_t offset = 15;
    unsigned i;
    const uint32_t words[3] = {bundle != NULL ? bundle->turn : 0,
                               bundle != NULL ? bundle->hash_turn : 0,
                               bundle != NULL ? bundle->hash : 0};
    if (bundle == NULL || payload == NULL ||
        capacity < 15U + (size_t)bundle->command_count * GAME_COMMAND_ENCODED_SIZE) return 0;
    for (i = 0; i < 3U; ++i) {
        payload[4 * i] = (uint8_t)(words[i] & 0xffU);
        payload[4 * i + 1] = (uint8_t)((words[i] >> 8) & 0xffU);
        payload[4 * i + 2] = (uint8_t)((words[i] >> 16) & 0xffU);
        payload[4 * i + 3] = (uint8_t)(words[i] >> 24);
    }
    payload[12] = bundle->has_hash;
    payload[13] = bundle->command_count;
    payload[14] = bundle->delay;
    for (i = 0; i < bundle->command_count; ++i)
        offset += game_command_encode(&bundle->commands[i], payload + offset, capacity - offset);
    return offset;
}

static uint32_t read_u32(const uint8_t *bytes)
{
    return (uint32_t)bytes[0] | ((uint32_t)bytes[1] << 8) |
           ((uint32_t)bytes[2] << 16) | ((uint32_t)bytes[3] << 24);
}

int net_lockstep_decode_bundle(const uint8_t *payload, size_t length, NetTurnBundle *bundle)
{
    unsigned i;
    size_t offset = 15;
    if (payload == NULL || bundle == NULL || length < 15U ||
        payload[13] > NET_TURN_MAX_COMMANDS ||
        length != 15U + (size_t)payload[13] * GAME_COMMAND_ENCODED_SIZE) return 0;
    memset(bundle, 0, sizeof(*bundle));
    bundle->valid = 1;
    bundle->turn = read_u32(payload);
    bundle->hash_turn = read_u32(payload + 4);
    bundle->hash = read_u32(payload + 8);
    bundle->has_hash = payload[12] != 0U;
    bundle->command_count = payload[13];
    bundle->delay = payload[14];
    for (i = 0; i < bundle->command_count; ++i) {
        if (!game_command_decode(payload + offset, length - offset, &bundle->commands[i]))
            return 0;
        offset += GAME_COMMAND_ENCODED_SIZE;
    }
    return 1;
}
