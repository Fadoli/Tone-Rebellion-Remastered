#include "net_lobby.h"

#include <string.h>

static void copy_name(char *out, const char *name)
{
    size_t length = 0;
    memset(out, 0, NET_LOBBY_NAME_CAPACITY);
    if (name == NULL) return;
    while (length + 1U < NET_LOBBY_NAME_CAPACITY && name[length] != '\0') {
        unsigned char c = (unsigned char)name[length];
        out[length] = (char)(c < 0x20U || c >= 0x7fU ? '?' : c);
        ++length;
    }
}

size_t net_frame_encode(uint8_t *out, size_t capacity, uint8_t type, uint8_t sender,
                        const void *payload, size_t length)
{
    if (out == NULL || length > NET_FRAME_MAX_PAYLOAD ||
        capacity < NET_FRAME_HEADER_SIZE + length) return 0;
    out[0] = (uint8_t)(length & 0xffU);
    out[1] = (uint8_t)(length >> 8);
    out[2] = type;
    out[3] = sender;
    if (length != 0U) memcpy(out + NET_FRAME_HEADER_SIZE, payload, length);
    return NET_FRAME_HEADER_SIZE + length;
}

int net_frame_reader_push(NetFrameReader *reader, const void *bytes, size_t length)
{
    if (reader == NULL || length > sizeof(reader->buffer) - reader->used) return 0;
    memcpy(reader->buffer + reader->used, bytes, length);
    reader->used += length;
    return 1;
}

int net_frame_reader_next(NetFrameReader *reader, NetFrame *frame)
{
    size_t length;
    if (reader == NULL || frame == NULL) return -1;
    if (reader->used < NET_FRAME_HEADER_SIZE) return 0;
    length = (size_t)reader->buffer[0] | ((size_t)reader->buffer[1] << 8);
    if (length > NET_FRAME_MAX_PAYLOAD) return -1;
    if (reader->used < NET_FRAME_HEADER_SIZE + length) return 0;
    frame->length = (uint16_t)length;
    frame->type = reader->buffer[2];
    frame->sender = reader->buffer[3];
    memcpy(frame->payload, reader->buffer + NET_FRAME_HEADER_SIZE, length);
    reader->used -= NET_FRAME_HEADER_SIZE + length;
    memmove(reader->buffer, reader->buffer + NET_FRAME_HEADER_SIZE + length, reader->used);
    return 1;
}

static void reset_players(NetLobby *lobby)
{
    unsigned slot;
    for (slot = 0; slot < NET_LOBBY_MAX_PLAYERS; ++slot) {
        memset(&lobby->players[slot], 0, sizeof(lobby->players[slot]));
        lobby->players[slot].tribe = NET_LOBBY_NO_TRIBE;
    }
}

static uint8_t first_free_tribe(const NetLobby *lobby)
{
    uint8_t tribe;
    for (tribe = 0; tribe < NET_LOBBY_MAX_PLAYERS; ++tribe) {
        unsigned slot;
        int taken = 0;
        for (slot = 0; slot < NET_LOBBY_MAX_PLAYERS; ++slot)
            if (lobby->players[slot].connected && lobby->players[slot].tribe == tribe)
                taken = 1;
        if (!taken) return tribe;
    }
    return NET_LOBBY_NO_TRIBE;
}

void net_lobby_host_init(NetLobby *lobby, const char *name, uint32_t seed)
{
    if (lobby == NULL) return;
    memset(lobby, 0, sizeof(*lobby));
    reset_players(lobby);
    lobby->is_host = 1;
    lobby->local_slot = 0;
    lobby->seed = seed;
    lobby->players[0].connected = 1;
    lobby->players[0].tribe = 0;
    copy_name(lobby->players[0].name, name);
}

void net_lobby_client_init(NetLobby *lobby)
{
    if (lobby == NULL) return;
    memset(lobby, 0, sizeof(*lobby));
    reset_players(lobby);
    lobby->local_slot = NET_LOBBY_NO_SLOT;
}

int net_lobby_host_add_player(NetLobby *lobby, uint8_t slot, const NetFrame *hello)
{
    char name[NET_LOBBY_NAME_CAPACITY + 1];
    size_t name_length;
    if (lobby == NULL || hello == NULL || hello->type != NET_RECORD_HELLO ||
        hello->length < 1U || hello->payload[0] != NET_LOBBY_VERSION)
        return -NET_REJECT_VERSION;
    if (lobby->started) return -NET_REJECT_STARTED;
    if (slot == 0U || slot >= NET_LOBBY_MAX_PLAYERS || lobby->players[slot].connected)
        return -NET_REJECT_FULL;
    name_length = (size_t)hello->length - 1U;
    if (name_length > NET_LOBBY_NAME_CAPACITY) name_length = NET_LOBBY_NAME_CAPACITY;
    memcpy(name, hello->payload + 1, name_length);
    name[name_length] = '\0';
    lobby->players[slot].tribe = first_free_tribe(lobby);
    lobby->players[slot].connected = 1;
    copy_name(lobby->players[slot].name, name);
    return (int)slot;
}

void net_lobby_remove_player(NetLobby *lobby, uint8_t slot)
{
    if (lobby == NULL || slot >= NET_LOBBY_MAX_PLAYERS) return;
    memset(&lobby->players[slot], 0, sizeof(lobby->players[slot]));
    lobby->players[slot].tribe = NET_LOBBY_NO_TRIBE;
}

int net_lobby_set_tribe(NetLobby *lobby, uint8_t slot, uint8_t tribe)
{
    unsigned other;
    if (lobby == NULL || slot >= NET_LOBBY_MAX_PLAYERS || tribe >= NET_LOBBY_MAX_PLAYERS ||
        !lobby->players[slot].connected || lobby->started) return 0;
    for (other = 0; other < NET_LOBBY_MAX_PLAYERS; ++other)
        if (other != slot && lobby->players[other].connected &&
            lobby->players[other].tribe == tribe) return 0;
    lobby->players[slot].tribe = tribe;
    return 1;
}

void net_lobby_set_world(NetLobby *lobby, uint8_t world_index, uint8_t difficulty)
{
    if (lobby == NULL || lobby->started) return;
    lobby->world_index = world_index;
    lobby->difficulty = difficulty;
}

unsigned net_lobby_player_count(const NetLobby *lobby)
{
    unsigned slot;
    unsigned count = 0;
    if (lobby == NULL) return 0;
    for (slot = 0; slot < NET_LOBBY_MAX_PLAYERS; ++slot)
        if (lobby->players[slot].connected) ++count;
    return count;
}

int net_lobby_can_start(const NetLobby *lobby)
{
    unsigned slot;
    unsigned other;
    if (lobby == NULL || !lobby->is_host || lobby->started ||
        net_lobby_player_count(lobby) < 2U) return 0;
    for (slot = 0; slot < NET_LOBBY_MAX_PLAYERS; ++slot) {
        if (!lobby->players[slot].connected) continue;
        if (lobby->players[slot].tribe >= NET_LOBBY_MAX_PLAYERS) return 0;
        for (other = slot + 1U; other < NET_LOBBY_MAX_PLAYERS; ++other)
            if (lobby->players[other].connected &&
                lobby->players[other].tribe == lobby->players[slot].tribe) return 0;
    }
    return 1;
}

int net_lobby_game_start(const NetLobby *lobby, NetGameStart *start)
{
    unsigned slot;
    if (lobby == NULL || start == NULL || !net_lobby_can_start(lobby)) return 0;
    memset(start, 0, sizeof(*start));
    start->seed = lobby->seed;
    start->world_index = lobby->world_index;
    start->difficulty = lobby->difficulty;
    start->player_count = (uint8_t)net_lobby_player_count(lobby);
    for (slot = 0; slot < NET_LOBBY_MAX_PLAYERS; ++slot)
        start->tribes[slot] = lobby->players[slot].connected
            ? lobby->players[slot].tribe : (uint8_t)NET_LOBBY_NO_TRIBE;
    return 1;
}

size_t net_lobby_encode_hello(uint8_t *out, size_t capacity, const char *name)
{
    uint8_t payload[1 + NET_LOBBY_NAME_CAPACITY];
    char clean[NET_LOBBY_NAME_CAPACITY];
    size_t length;
    copy_name(clean, name);
    length = strlen(clean);
    payload[0] = NET_LOBBY_VERSION;
    memcpy(payload + 1, clean, length);
    return net_frame_encode(out, capacity, NET_RECORD_HELLO, NET_LOBBY_NO_SLOT,
                            payload, 1U + length);
}

size_t net_lobby_encode_welcome(uint8_t *out, size_t capacity, uint8_t slot)
{
    return net_frame_encode(out, capacity, NET_RECORD_WELCOME, 0, &slot, 1);
}

size_t net_lobby_encode_reject(uint8_t *out, size_t capacity, uint8_t reason)
{
    return net_frame_encode(out, capacity, NET_RECORD_REJECT, 0, &reason, 1);
}

size_t net_lobby_encode_tribe(uint8_t *out, size_t capacity, uint8_t slot, uint8_t tribe)
{
    return net_frame_encode(out, capacity, NET_RECORD_TRIBE, slot, &tribe, 1);
}

/* Payload: world, difficulty, then per slot: connected, tribe, name[16]. */
size_t net_lobby_encode_player_list(const NetLobby *lobby, uint8_t *out, size_t capacity)
{
    uint8_t payload[2 + NET_LOBBY_MAX_PLAYERS * (2 + NET_LOBBY_NAME_CAPACITY)];
    size_t offset = 2;
    unsigned slot;
    if (lobby == NULL) return 0;
    payload[0] = lobby->world_index;
    payload[1] = lobby->difficulty;
    for (slot = 0; slot < NET_LOBBY_MAX_PLAYERS; ++slot) {
        payload[offset++] = lobby->players[slot].connected;
        payload[offset++] = lobby->players[slot].tribe;
        memcpy(payload + offset, lobby->players[slot].name, NET_LOBBY_NAME_CAPACITY);
        offset += NET_LOBBY_NAME_CAPACITY;
    }
    return net_frame_encode(out, capacity, NET_RECORD_PLAYER_LIST, 0, payload, offset);
}

/* Payload: seed (LE), world, difficulty, player count, tribe per slot. */
size_t net_lobby_encode_game_start(const NetGameStart *start, uint8_t *out, size_t capacity)
{
    uint8_t payload[7 + NET_LOBBY_MAX_PLAYERS];
    if (start == NULL) return 0;
    payload[0] = (uint8_t)(start->seed & 0xffU);
    payload[1] = (uint8_t)((start->seed >> 8) & 0xffU);
    payload[2] = (uint8_t)((start->seed >> 16) & 0xffU);
    payload[3] = (uint8_t)(start->seed >> 24);
    payload[4] = start->world_index;
    payload[5] = start->difficulty;
    payload[6] = start->player_count;
    memcpy(payload + 7, start->tribes, NET_LOBBY_MAX_PLAYERS);
    return net_frame_encode(out, capacity, NET_RECORD_GAME_START, 0,
                            payload, sizeof(payload));
}

int net_lobby_client_handle(NetLobby *lobby, const NetFrame *frame,
                            NetGameStart *start, uint8_t *reject_reason)
{
    unsigned slot;
    if (lobby == NULL || frame == NULL) return NET_LOBBY_EVENT_ERROR;
    switch (frame->type) {
    case NET_RECORD_WELCOME:
        if (frame->length != 1U || frame->payload[0] >= NET_LOBBY_MAX_PLAYERS)
            return NET_LOBBY_EVENT_ERROR;
        lobby->local_slot = frame->payload[0];
        return NET_LOBBY_EVENT_WELCOME;
    case NET_RECORD_REJECT:
        if (reject_reason != NULL)
            *reject_reason = frame->length != 0U ? frame->payload[0] : 0;
        return NET_LOBBY_EVENT_REJECT;
    case NET_RECORD_PLAYER_LIST: {
        size_t offset = 2;
        if (frame->length != 2U + NET_LOBBY_MAX_PLAYERS * (2U + NET_LOBBY_NAME_CAPACITY))
            return NET_LOBBY_EVENT_ERROR;
        lobby->world_index = frame->payload[0];
        lobby->difficulty = frame->payload[1];
        for (slot = 0; slot < NET_LOBBY_MAX_PLAYERS; ++slot) {
            char name[NET_LOBBY_NAME_CAPACITY + 1];
            lobby->players[slot].connected = frame->payload[offset++] != 0U;
            lobby->players[slot].tribe = frame->payload[offset++];
            memcpy(name, frame->payload + offset, NET_LOBBY_NAME_CAPACITY);
            name[NET_LOBBY_NAME_CAPACITY] = '\0';
            copy_name(lobby->players[slot].name, name);
            offset += NET_LOBBY_NAME_CAPACITY;
        }
        return NET_LOBBY_EVENT_STATE;
    }
    case NET_RECORD_GAME_START:
        if (frame->length != 7U + NET_LOBBY_MAX_PLAYERS || start == NULL)
            return NET_LOBBY_EVENT_ERROR;
        memset(start, 0, sizeof(*start));
        start->seed = (uint32_t)frame->payload[0] | ((uint32_t)frame->payload[1] << 8) |
                      ((uint32_t)frame->payload[2] << 16) | ((uint32_t)frame->payload[3] << 24);
        start->world_index = frame->payload[4];
        start->difficulty = frame->payload[5];
        start->player_count = frame->payload[6];
        memcpy(start->tribes, frame->payload + 7, NET_LOBBY_MAX_PLAYERS);
        lobby->seed = start->seed;
        lobby->world_index = start->world_index;
        lobby->difficulty = start->difficulty;
        lobby->started = 1;
        return NET_LOBBY_EVENT_START;
    default:
        return NET_LOBBY_EVENT_NONE;
    }
}
