#ifndef TONE_REBELLION_NET_LOBBY_H
#define TONE_REBELLION_NET_LOBBY_H

#include <stddef.h>
#include <stdint.h>

/* Multiplayer lobby model (decompilation/behavior/multiplayer.md). The original reaches the
   New Game screen (state 1) through a DirectPlay session; that screen is the
   lobby: the session host owns world size and difficulty, every player picks
   a tribe, and BEGINGAME (message 52) broadcasts record type 9. Record types
   below reuse the native FUN_004121b7 numbers where the meaning is
   established (1 player list, 6 tribe choice, 7 world, 8 difficulty, 9 game
   start); the byte layout of each record is the remake's own, not the
   DirectPlay wire format. No OS API: the platform layer moves the bytes. */

enum {
    NET_LOBBY_MAX_PLAYERS = 4,
    NET_LOBBY_NAME_CAPACITY = 16,
    NET_LOBBY_NO_TRIBE = 0xff,
    NET_LOBBY_NO_SLOT = 0xff,
    /* 2: HELLO carries the session build tag after the version byte. */
    NET_LOBBY_VERSION = 2,
    NET_LOBBY_HELLO_HEADER = 5,
    NET_FRAME_HEADER_SIZE = 4,
    NET_FRAME_MAX_PAYLOAD = 2304,
    NET_FRAME_MAX_SIZE = NET_FRAME_HEADER_SIZE + NET_FRAME_MAX_PAYLOAD,
    NET_LOBBY_DEFAULT_PORT = 28610
};

typedef enum NetRecordType {
    NET_RECORD_PLAYER_LIST = 1,  /* host -> all: slots, names, tribes, settings */
    NET_RECORD_TRIBE = 6,        /* client -> host: tribe request */
    NET_RECORD_WORLD = 7,        /* host -> all (folded into the player list) */
    NET_RECORD_DIFFICULTY = 8,   /* host -> all (folded into the player list) */
    NET_RECORD_GAME_START = 9,   /* host -> all: seed, world, difficulty, tribes */
    NET_RECORD_HELLO = 0x40,     /* client -> host: version, build tag, name (remake) */
    NET_RECORD_WELCOME = 0x41,   /* host -> client: assigned slot (remake) */
    NET_RECORD_REJECT = 0x42     /* host -> client: reason (remake) */
} NetRecordType;

typedef enum NetRejectReason {
    NET_REJECT_FULL = 1,
    NET_REJECT_VERSION = 2,
    NET_REJECT_STARTED = 3
} NetRejectReason;

/* Frame = u16 payload length (LE), u8 record type, u8 sender slot, payload. */
typedef struct NetFrame {
    uint8_t type;
    uint8_t sender;
    uint16_t length;
    uint8_t payload[NET_FRAME_MAX_PAYLOAD];
} NetFrame;

/* Byte-stream reassembly for one connection. */
typedef struct NetFrameReader {
    uint8_t buffer[NET_FRAME_MAX_SIZE * 2];
    size_t used;
} NetFrameReader;

typedef struct NetLobbyPlayer {
    uint8_t connected;
    uint8_t tribe;
    char name[NET_LOBBY_NAME_CAPACITY];
} NetLobbyPlayer;

typedef struct NetLobby {
    uint8_t is_host;
    uint8_t local_slot;     /* DAT_004befec analogue; the host is slot 0 */
    uint8_t world_index;
    uint8_t difficulty;
    uint8_t started;
    uint32_t seed;
    NetLobbyPlayer players[NET_LOBBY_MAX_PLAYERS];
} NetLobby;

typedef struct NetGameStart {
    uint32_t seed;
    uint8_t world_index;
    uint8_t difficulty;
    uint8_t player_count;
    uint8_t tribes[NET_LOBBY_MAX_PLAYERS];  /* per slot, NET_LOBBY_NO_TRIBE if empty */
} NetGameStart;

/* Client-side events reported by net_lobby_client_handle. */
enum {
    NET_LOBBY_EVENT_NONE = 0,
    NET_LOBBY_EVENT_WELCOME = 1,
    NET_LOBBY_EVENT_STATE = 2,
    NET_LOBBY_EVENT_START = 4,
    NET_LOBBY_EVENT_REJECT = 8,
    NET_LOBBY_EVENT_ERROR = 16
};

size_t net_frame_encode(uint8_t *out, size_t capacity, uint8_t type, uint8_t sender,
                        const void *payload, size_t length);
/* Appends received bytes; returns 0 if they do not fit (protocol error). */
int net_frame_reader_push(NetFrameReader *reader, const void *bytes, size_t length);
/* Returns 1 with one frame, 0 when incomplete, -1 on a malformed stream. */
int net_frame_reader_next(NetFrameReader *reader, NetFrame *frame);

void net_lobby_host_init(NetLobby *lobby, const char *name, uint32_t seed);
void net_lobby_client_init(NetLobby *lobby);

/* Host: the connection held at `slot` said HELLO. Returns the slot or
   -reason; the slot must be a free guest slot (1..3). */
/* Fingerprint of the GameSession layout (field table and size). Lockstep
   and the reconnection snapshot copy raw session bytes, so two builds play
   together only when their tags match. */
uint32_t net_lobby_build_tag(void);
/* Checks a HELLO (version and build tag) and copies its player name.
   Returns 0, or -NET_REJECT_VERSION. */
int net_lobby_read_hello(const NetFrame *hello,
                         char name[NET_LOBBY_NAME_CAPACITY + 1]);
int net_lobby_host_add_player(NetLobby *lobby, uint8_t slot, const NetFrame *hello);
void net_lobby_remove_player(NetLobby *lobby, uint8_t slot);
/* Host: any tribe. Several players may share one tribe and play it in
   cooperation (remake extension; the native type-6 record refuses a tribe
   another player holds). */
int net_lobby_set_tribe(NetLobby *lobby, uint8_t slot, uint8_t tribe);
void net_lobby_set_world(NetLobby *lobby, uint8_t world_index, uint8_t difficulty);
unsigned net_lobby_player_count(const NetLobby *lobby);
/* Host: at least two players, each with a tribe. */
int net_lobby_can_start(const NetLobby *lobby);
int net_lobby_game_start(const NetLobby *lobby, NetGameStart *start);

size_t net_lobby_encode_hello(uint8_t *out, size_t capacity, const char *name);
size_t net_lobby_encode_welcome(uint8_t *out, size_t capacity, uint8_t slot);
size_t net_lobby_encode_reject(uint8_t *out, size_t capacity, uint8_t reason);
size_t net_lobby_encode_tribe(uint8_t *out, size_t capacity, uint8_t slot, uint8_t tribe);
size_t net_lobby_encode_player_list(const NetLobby *lobby, uint8_t *out, size_t capacity);
size_t net_lobby_encode_game_start(const NetGameStart *start, uint8_t *out, size_t capacity);

/* Client: applies one host frame; returns NET_LOBBY_EVENT_* flags. */
int net_lobby_client_handle(NetLobby *lobby, const NetFrame *frame,
                            NetGameStart *start, uint8_t *reject_reason);

#endif
