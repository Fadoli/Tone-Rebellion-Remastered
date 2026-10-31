#include "net_lockstep.h"

#include <assert.h>
#include <string.h>

/* Toy simulation: the state folds in every applied command and each tick. */
typedef struct Toy {
    uint32_t state;
    uint32_t applied_at_tick[8];
    unsigned applied;
} Toy;

static void run_tick(NetLockstep *lockstep, Toy *toy, NetTurnBundle *broadcast, int *sent)
{
    const NetTurnBundle *bundle = net_lockstep_turn_commands(lockstep);
    unsigned i;
    if (bundle != NULL) {
        for (i = 0; i < bundle->command_count; ++i) {
            toy->state = toy->state * 31U + (uint32_t)bundle->commands[i].args[0];
            toy->applied_at_tick[toy->applied++] = lockstep->tick;
        }
    }
    toy->state = toy->state * 17U + 1U;
    *sent = net_lockstep_finish_tick(lockstep, toy->state, broadcast) && lockstep->is_host;
}

int main(void)
{
    NetLockstep host;
    NetLockstep guest;
    Toy host_toy;
    Toy guest_toy;
    NetTurnBundle bundle;
    NetTurnBundle decoded;
    GameCommand command;
    GameCommand round_trip;
    uint8_t bytes[4096];
    int32_t args[GAME_COMMAND_ARG_COUNT];
    size_t length;
    int sent;
    unsigned step;

    /* Command and bundle encodings round-trip; unknown kinds are refused. */
    for (step = 0; step < GAME_COMMAND_ARG_COUNT; ++step) args[step] = (int32_t)step * -7;
    command = game_command_make(GAME_COMMAND_SET_BUILDING_ORDER, GAME_COMMAND_ARG_COUNT, args);
    assert(game_command_encode(&command, bytes, sizeof(bytes)) == GAME_COMMAND_ENCODED_SIZE);
    assert(game_command_decode(bytes, GAME_COMMAND_ENCODED_SIZE, &round_trip));
    assert(memcmp(&command, &round_trip, sizeof(command)) == 0);
    bytes[0] = GAME_COMMAND_KIND_COUNT;
    assert(!game_command_decode(bytes, GAME_COMMAND_ENCODED_SIZE, &round_trip));
    assert(game_command_apply(NULL, NULL, &command) == 0);

    memset(&host_toy, 0, sizeof(host_toy));
    memset(&guest_toy, 0, sizeof(guest_toy));
    net_lockstep_init(&host, 1, 1U << 1);
    net_lockstep_init(&guest, 0, 0);

    /* The first NET_TURN_DELAY turns need no bundle. */
    for (step = 0; step < NET_TURN_DELAY * NET_TURN_TICKS; ++step) {
        assert(net_lockstep_can_tick(&guest));
        run_tick(&guest, &guest_toy, &bundle, &sent);
    }
    assert(!net_lockstep_can_tick(&guest));   /* waits for bundle 3 */

    /* Host turn 0 issues a command (args[0] = 5) and bundles it for turn 3. */
    args[0] = 5;
    command = game_command_make(GAME_COMMAND_QUEUE_OBTAIN_TASK, 1, args);
    assert(net_lockstep_queue_command(&host, &command));
    for (step = 0; step < NET_TURN_TICKS; ++step) run_tick(&host, &host_toy, &bundle, &sent);
    assert(sent && bundle.turn == NET_TURN_DELAY && bundle.command_count == 1);
    assert(bundle.has_hash && bundle.hash_turn == 0);
    length = net_lockstep_encode_bundle(&bundle, bytes, sizeof(bytes));
    assert(net_lockstep_decode_bundle(bytes, length, &decoded));
    assert(decoded.turn == bundle.turn && decoded.hash == bundle.hash &&
           decoded.commands[0].args[0] == 5);
    assert(!net_lockstep_decode_bundle(bytes, length - 1U, &decoded));
    assert(net_lockstep_receive_bundle(&guest, &decoded));
    assert(net_lockstep_turns_ready(&guest) == 1U);
    assert(net_lockstep_can_tick(&guest));

    /* Run both to turn 8, relaying each new host bundle and the guest acks;
       the command lands at the same tick on both machines. */
    while (net_lockstep_turn(&host) < 8U || net_lockstep_turn(&guest) < 8U) {
        if (net_lockstep_turn(&host) < 8U && net_lockstep_can_tick(&host)) {
            run_tick(&host, &host_toy, &bundle, &sent);
            if (sent) assert(net_lockstep_receive_bundle(&guest, &bundle));
        }
        if (net_lockstep_turn(&guest) < 8U && net_lockstep_can_tick(&guest)) {
            run_tick(&guest, &guest_toy, &bundle, &sent);
            net_lockstep_receive_ack(&host, 1, net_lockstep_turn(&guest));
        }
    }
    assert(host_toy.applied == 1 && guest_toy.applied == 1);
    assert(host_toy.applied_at_tick[0] == NET_TURN_DELAY * NET_TURN_TICKS);
    assert(guest_toy.applied_at_tick[0] == host_toy.applied_at_tick[0]);
    assert(host_toy.state == guest_toy.state);
    assert(!guest.desync);

    /* The host stops once the guest lags NET_TURN_HOST_LEAD turns. */
    while (net_lockstep_can_tick(&host)) {
        run_tick(&host, &host_toy, &bundle, &sent);
        if (sent) (void)net_lockstep_receive_bundle(&guest, &bundle);
    }
    assert(net_lockstep_turn(&host) == 8U + NET_TURN_HOST_LEAD);
    assert(net_lockstep_turns_ready(&guest) == NET_TURN_HOST_LEAD + NET_TURN_DELAY);
    net_lockstep_drop_peer(&host, 1);
    assert(net_lockstep_can_tick(&host));

    /* A diverging guest state is reported at the first compared turn. */
    guest_toy.state ^= 1U;
    while (!guest.desync && net_lockstep_can_tick(&guest))
        run_tick(&guest, &guest_toy, &bundle, &sent);
    assert(guest.desync && guest.desync_turn == 8U);
    assert(!net_lockstep_can_tick(&guest));
    return 0;
}
