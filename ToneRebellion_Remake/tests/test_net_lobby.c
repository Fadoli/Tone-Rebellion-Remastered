#include "net_lobby.h"

#include <assert.h>
#include <string.h>

static void deliver(NetFrameReader *reader, const uint8_t *bytes, size_t length,
                    NetFrame *frame)
{
    /* Split the stream to exercise reassembly. */
    assert(net_frame_reader_push(reader, bytes, 3));
    assert(net_frame_reader_next(reader, frame) == 0);
    assert(net_frame_reader_push(reader, bytes + 3, length - 3U));
    assert(net_frame_reader_next(reader, frame) == 1);
    assert(net_frame_reader_next(reader, frame) == 0);
}

int main(void)
{
    NetLobby host;
    NetLobby client;
    NetFrameReader reader;
    NetFrame frame;
    NetGameStart start;
    NetGameStart received;
    uint8_t bytes[NET_FRAME_MAX_SIZE];
    uint8_t reason = 0;
    size_t length;
    int slot;

    memset(&reader, 0, sizeof(reader));
    net_lobby_host_init(&host, "Host", 0x12345678U);
    net_lobby_client_init(&client);
    assert(host.local_slot == 0 && host.players[0].tribe == 0);
    assert(client.local_slot == NET_LOBBY_NO_SLOT);
    assert(!net_lobby_can_start(&host));

    /* Join: HELLO -> slot 1 with the first free tribe, WELCOME, list. */
    length = net_lobby_encode_hello(bytes, sizeof(bytes), "Guest\x01");
    deliver(&reader, bytes, length, &frame);
    slot = net_lobby_host_add_player(&host, 1, &frame);
    assert(slot == 1);
    assert(host.players[1].tribe == 1);
    assert(strcmp(host.players[1].name, "Guest?") == 0);
    length = net_lobby_encode_welcome(bytes, sizeof(bytes), (uint8_t)slot);
    deliver(&reader, bytes, length, &frame);
    assert(net_lobby_client_handle(&client, &frame, &received, &reason) ==
           NET_LOBBY_EVENT_WELCOME);
    assert(client.local_slot == 1);

    /* Host options: shared glyphs on by default; the list carries them. */
    assert(host.options == NET_LOBBY_OPTION_SHARED_GLYPHS);
    net_lobby_set_options(&host, 0);
    length = net_lobby_encode_player_list(&host, bytes, sizeof(bytes));
    deliver(&reader, bytes, length, &frame);
    assert(net_lobby_client_handle(&client, &frame, &received, &reason) ==
           NET_LOBBY_EVENT_STATE);
    assert(client.options == 0);
    net_lobby_set_options(&host, NET_LOBBY_OPTION_SHARED_GLYPHS);

    net_lobby_set_world(&host, 2, 3);
    length = net_lobby_encode_player_list(&host, bytes, sizeof(bytes));
    deliver(&reader, bytes, length, &frame);
    assert(net_lobby_client_handle(&client, &frame, &received, &reason) ==
           NET_LOBBY_EVENT_STATE);
    assert(client.world_index == 2 && client.difficulty == 3);
    assert(client.options == NET_LOBBY_OPTION_SHARED_GLYPHS);
    assert(net_lobby_player_count(&client) == 2U);
    assert(strcmp(client.players[0].name, "Host") == 0);
    assert(client.players[1].tribe == 1);

    /* Tribe requests: a shared tribe is allowed (cooperation). */
    length = net_lobby_encode_tribe(bytes, sizeof(bytes), 1, 0);
    deliver(&reader, bytes, length, &frame);
    assert(frame.type == NET_RECORD_TRIBE && frame.sender == 1);
    assert(net_lobby_set_tribe(&host, frame.sender, frame.payload[0]));
    assert(net_lobby_can_start(&host));
    assert(!net_lobby_set_tribe(&host, 1, 4));
    assert(net_lobby_set_tribe(&host, 1, 3));
    assert(net_lobby_can_start(&host));

    /* Game start carries seed, world, difficulty and the tribe per slot. */
    assert(net_lobby_game_start(&host, &start));
    length = net_lobby_encode_game_start(&start, bytes, sizeof(bytes));
    deliver(&reader, bytes, length, &frame);
    assert(net_lobby_client_handle(&client, &frame, &received, &reason) ==
           NET_LOBBY_EVENT_START);
    assert(received.seed == 0x12345678U && received.world_index == 2 &&
           received.difficulty == 3 && received.player_count == 2);
    assert(received.tribes[0] == 0 && received.tribes[1] == 3 &&
           received.tribes[2] == NET_LOBBY_NO_TRIBE);
    assert(received.options == NET_LOBBY_OPTION_SHARED_GLYPHS);
    assert(client.started);
    /* Options are frozen once the game started. */
    net_lobby_set_options(&client, 0);
    assert(client.options == NET_LOBBY_OPTION_SHARED_GLYPHS);

    /* Full lobby, version mismatch, departure. */
    length = net_lobby_encode_hello(bytes, sizeof(bytes), "C");
    deliver(&reader, bytes, length, &frame);
    host.started = 0;
    assert(net_lobby_host_add_player(&host, 3, &frame) == 3);
    assert(host.players[3].tribe == 1);
    assert(net_lobby_host_add_player(&host, 2, &frame) == 2);
    assert(host.players[2].tribe == 2);
    assert(net_lobby_host_add_player(&host, 2, &frame) == -NET_REJECT_FULL);
    assert(net_lobby_host_add_player(&host, 0, &frame) == -NET_REJECT_FULL);
    net_lobby_remove_player(&host, 2);
    assert(net_lobby_player_count(&host) == 3U);
    frame.payload[0] = NET_LOBBY_VERSION + 1;
    assert(net_lobby_host_add_player(&host, 2, &frame) == -NET_REJECT_VERSION);
    host.started = 1;
    frame.payload[0] = NET_LOBBY_VERSION;
    assert(net_lobby_host_add_player(&host, 2, &frame) == -NET_REJECT_STARTED);

    length = net_lobby_encode_reject(bytes, sizeof(bytes), NET_REJECT_FULL);
    deliver(&reader, bytes, length, &frame);
    assert(net_lobby_client_handle(&client, &frame, &received, &reason) ==
           NET_LOBBY_EVENT_REJECT);
    assert(reason == NET_REJECT_FULL);

    /* A frame claiming more than the payload limit is malformed. */
    memset(&reader, 0, sizeof(reader));
    bytes[0] = 0xff;
    bytes[1] = 0xff;
    bytes[2] = 1;
    bytes[3] = 0;
    assert(net_frame_reader_push(&reader, bytes, 4));
    assert(net_frame_reader_next(&reader, &frame) == -1);
    return 0;
}
