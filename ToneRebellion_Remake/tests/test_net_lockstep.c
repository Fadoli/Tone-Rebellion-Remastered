#include "net_lockstep.h"

#include <assert.h>
#include <string.h>

/* Toy simulation: the state folds in every applied command and each tick. */
typedef struct Toy {
    uint32_t state;
    uint32_t applied_at_tick[16];
    unsigned applied;
} Toy;

static NetLockstep host;
static NetLockstep guest;
static Toy host_toy;
static Toy guest_toy;

static void run_tick(NetLockstep *lockstep, Toy *toy)
{
    const NetTurnBundle *bundle = net_lockstep_turn_commands(lockstep);
    NetTurnBundle created[NET_TURN_MAX_DELAY + 1];
    size_t count;
    size_t i;
    if (bundle != NULL) {
        for (i = 0; i < bundle->command_count; ++i) {
            toy->state = toy->state * 31U + (uint32_t)bundle->commands[i].args[0];
            toy->applied_at_tick[toy->applied++] = lockstep->tick;
        }
    }
    toy->state = toy->state * 17U + 1U;
    count = net_lockstep_finish_tick(lockstep, toy->state, created,
                                     sizeof(created) / sizeof(created[0]));
    if (lockstep->is_host) {
        for (i = 0; i < count; ++i) {
            uint8_t bytes[4096];
            NetTurnBundle decoded;
            size_t length = net_lockstep_encode_bundle(&created[i], bytes, sizeof(bytes));
            assert(net_lockstep_decode_bundle(bytes, length, &decoded));
            assert(net_lockstep_receive_bundle(&guest, &decoded));
        }
    } else {
        net_lockstep_receive_ack(&host, 1, net_lockstep_turn(lockstep));
    }
}

/* Alternate host and guest ticks until both reached `turn`. */
static void run_both_to(uint32_t turn)
{
    while (net_lockstep_turn(&host) < turn || net_lockstep_turn(&guest) < turn) {
        int moved = 0;
        if (net_lockstep_turn(&host) < turn && net_lockstep_can_tick(&host)) {
            run_tick(&host, &host_toy);
            moved = 1;
        }
        if (net_lockstep_turn(&guest) < turn && net_lockstep_can_tick(&guest)) {
            run_tick(&guest, &guest_toy);
            moved = 1;
        }
        assert(moved);
    }
}

static void host_command(int32_t value)
{
    GameCommand command = game_command_make(GAME_COMMAND_QUEUE_OBTAIN_TASK, 1, &value);
    assert(net_lockstep_queue_command(&host, &command));
}

int main(void)
{
    GameCommand command;
    GameCommand round_trip;
    uint8_t bytes[4096];
    int32_t args[GAME_COMMAND_ARG_COUNT];
    unsigned step;

    /* Command encodings round-trip; unknown kinds are refused. */
    for (step = 0; step < GAME_COMMAND_ARG_COUNT; ++step) args[step] = (int32_t)step * -7;
    command = game_command_make(GAME_COMMAND_SET_BUILDING_ORDER, GAME_COMMAND_ARG_COUNT, args);
    assert(game_command_encode(&command, bytes, sizeof(bytes)) == GAME_COMMAND_ENCODED_SIZE);
    memset(&round_trip, 0, sizeof(round_trip));
    assert(game_command_decode(bytes, GAME_COMMAND_ENCODED_SIZE, &round_trip));
    assert(memcmp(&command, &round_trip, sizeof(command)) == 0);
    bytes[0] = GAME_COMMAND_KIND_COUNT;
    assert(!game_command_decode(bytes, GAME_COMMAND_ENCODED_SIZE, &round_trip));
    assert(game_command_apply(NULL, NULL, &command) == 0);

    /* Delay = 1 + half the round trip in ticks, clamped. */
    assert(net_lockstep_delay_for_round_trip(0, 50) == 1);
    assert(net_lockstep_delay_for_round_trip(2, 50) == 2);
    assert(net_lockstep_delay_for_round_trip(100, 50) == 2);
    assert(net_lockstep_delay_for_round_trip(102, 50) == 3);
    assert(net_lockstep_delay_for_round_trip(100000, 50) == NET_TURN_MAX_DELAY);

    memset(&host_toy, 0, sizeof(host_toy));
    memset(&guest_toy, 0, sizeof(guest_toy));
    net_lockstep_init(&host, 1, 1U << 1);
    net_lockstep_init(&guest, 0, 0);
    net_lockstep_set_delay(&host, 1);

    /* The first turns need no bundle; the guest then waits for the host. */
    for (step = 0; step < NET_TURN_START_DELAY; ++step) {
        assert(net_lockstep_can_tick(&guest));
        run_tick(&guest, &guest_toy);
    }
    assert(!net_lockstep_can_tick(&guest));

    /* Delay 1: a command bundled at the end of turn t runs at turn t + 1. */
    run_both_to(4);
    host_command(5);
    run_both_to(8);
    assert(host_toy.applied == 1 && guest_toy.applied == 1);
    assert(host_toy.applied_at_tick[0] == 5U * NET_TURN_TICKS);
    assert(guest_toy.applied_at_tick[0] == host_toy.applied_at_tick[0]);

    /* Growing the delay emits the skipped turns empty; shrinking it emits
       nothing until the bundled turns are reached. No turn is ever missing. */
    net_lockstep_set_delay(&host, 4);
    host_command(7);
    run_both_to(12);
    assert(host_toy.applied == 2 && host_toy.applied_at_tick[1] == 9U * NET_TURN_TICKS);
    net_lockstep_set_delay(&host, 1);
    host_command(9);
    run_both_to(20);
    /* Turns 13..15 were already bundled, so the command waits for turn 16. */
    assert(host_toy.applied == 3 && host_toy.applied_at_tick[2] == 16U * NET_TURN_TICKS);
    assert(guest_toy.applied == 3);
    assert(memcmp(host_toy.applied_at_tick, guest_toy.applied_at_tick,
                  sizeof(host_toy.applied_at_tick)) == 0);
    assert(host_toy.state == guest_toy.state && !guest.desync);

    /* A guest holding more than delay + 1 turns runs extra ticks. */
    assert(net_lockstep_frame_ticks(&host) == 1U);
    assert(guest.delay == 1U && net_lockstep_frame_ticks(&guest) == 1U);
    run_tick(&host, &host_toy);
    run_tick(&host, &host_toy);
    assert(net_lockstep_turns_ready(&guest) == 3U && net_lockstep_frame_ticks(&guest) == 2U);
    run_tick(&host, &host_toy);
    run_tick(&host, &host_toy);
    assert(net_lockstep_frame_ticks(&guest) == 3U);
    run_both_to(24);

    /* The host stops once the guest lags NET_TURN_HOST_LEAD turns. */
    while (net_lockstep_can_tick(&host)) run_tick(&host, &host_toy);
    assert(net_lockstep_turn(&host) == 24U + NET_TURN_HOST_LEAD);
    assert(net_lockstep_turns_ready(&guest) == NET_TURN_HOST_LEAD + 1U);
    net_lockstep_drop_peer(&host, 1);
    assert(net_lockstep_can_tick(&host));

    /* A diverging guest state is reported at the first compared turn. */
    guest_toy.state ^= 1U;
    while (!guest.desync && net_lockstep_can_tick(&guest)) run_tick(&guest, &guest_toy);
    assert(guest.desync && guest.desync_turn == 24U);
    assert(!net_lockstep_can_tick(&guest));
    return 0;
}
