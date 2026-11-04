/* Multiplayer lobby transport (behavior/multiplayer.md). The original opens a
   DirectPlay session outside the game screens and then uses the New Game
   screen (state 1) as the lobby; DirectPlay is not available to the remake,
   so it carries the core NetLobby records over a plain TCP connection: one
   host socket accepts up to three guests, guests talk only to the host (the
   native send path FUN_00412d70 also routes non-host records to the host).
   Sockets are non-blocking (net_socket.c). Under Win32 they post
   WM_NET_SOCKET to the window, so frames are handled when they arrive
   rather than at the next 50 ms timer (that polling alone added up to two
   frames to every round trip); remake_sdl polls them on every 10 ms
   iteration instead. After the start, the same connections carry the
   NetLockstep turns. */

enum { NET_MODE_NONE, NET_MODE_HOST, NET_MODE_CLIENT };
enum { WM_NET_SOCKET = WM_APP + 1 };

static HWND g_net_window;

static int g_net_mode;
static int g_net_wsa_started;
static int g_net_connecting;
static NetSocket g_net_listen = NET_SOCKET_INVALID;
static NetSocket g_net_peers[NET_LOBBY_MAX_PLAYERS] = {
    NET_SOCKET_INVALID, NET_SOCKET_INVALID, NET_SOCKET_INVALID, NET_SOCKET_INVALID};
static NetFrameReader g_net_readers[NET_LOBBY_MAX_PLAYERS];
static NetLobby g_net_lobby;
static char g_net_name[NET_LOBBY_NAME_CAPACITY];
static char g_net_status[128];
static char g_net_join_address[128] = "127.0.0.1";
static unsigned short g_net_port = NET_LOBBY_DEFAULT_PORT;
static int g_net_in_game;
static NetLockstep g_net_lockstep;
/* Draws that only pick local presentation (realm music) must not advance
   the shared session generator during a network game. */
static ToneRng g_net_local_rng;
static GameSession g_net_predicted_session;
/* Host: smoothed round trip per guest (ms), from PING/PONG every second. */
static uint32_t g_net_round_trip[NET_LOBBY_MAX_PLAYERS];
static unsigned g_net_ping_frames;
/* E2E timing aid: clock and tick of the last issued and applied command. */
static uint32_t g_net_issue_ms, g_net_issue_tick, g_net_apply_ms, g_net_apply_tick;

static void simulate_session_tick(uint32_t source_tick);
static void enter_net_setup_screen(void);

/* Network game from a save (remake extension): the host loads a save in the
   lobby, sends the file to every guest in chunks, each machine applies the
   same bytes, the lobby turns into the tribe choice of a loaded game, and
   the start continues that session on every machine. */
enum { NET_RECORD_SAVE_DATA = 0x44,  /* host -> guest: native, total, offset, bytes */
       NET_RECORD_SAVE_ACK = 0x45,   /* guest -> host: save applied */
       NET_RECORD_LOBBY_RETURN = 0x46, /* host -> guests: game over, back to the lobby */
       NET_SAVE_CHUNK = 2048, NET_SAVE_CHUNKS_PER_POLL = 4 };
static unsigned char *g_net_save;
static size_t g_net_save_length;
static uint8_t g_net_save_native;
static size_t g_net_save_received;
static size_t g_net_save_sent[NET_LOBBY_MAX_PLAYERS];
static uint8_t g_net_save_acked;
static int g_net_save_ready;
/* save_game.inc: apply g_net_save to g_game_session (lobby) / start it. */
static int net_load_apply(void);
static int net_load_start(HWND window, uint8_t tribe);

static void net_save_clear(void)
{
    free(g_net_save);
    g_net_save = NULL;
    g_net_save_length = 0;
    g_net_save_received = 0;
    g_net_save_native = 0;
    g_net_save_acked = 0;
    g_net_save_ready = 0;
    memset(g_net_save_sent, 0, sizeof(g_net_save_sent));
    g_tribe_choice_mask = 0;
}

/* Every machine leaves the running network game for the lobby (the host
   loads another game): the lobby settings and players stay. */
static void net_back_to_lobby(void)
{
    g_net_in_game = 0;
    g_game_session_valid = 0;
    g_paused = 0;
    g_net_lobby.started = 0;
    g_menu.screen = SCREEN_NEW_GAME;
}

static uint32_t net_le32(const uint8_t *bytes)
{
    return (uint32_t)bytes[0] | (uint32_t)bytes[1] << 8 |
        (uint32_t)bytes[2] << 16 | (uint32_t)bytes[3] << 24;
}

static void queue_island_message(const char *text, int16_t selector);

static void net_set_status(const char *text)
{
    (void)snprintf(g_net_status, sizeof(g_net_status), "%s", text);
}

/* The lobby status line is not drawn in game: repeat it on the island
   message line so players see who left. */
static void net_notify_in_game(void)
{
    if (g_net_in_game) queue_island_message(g_net_status, 1);
}

static void net_close_socket(NetSocket *socket_handle)
{
    if (*socket_handle != NET_SOCKET_INVALID) {
        net_socket_close(*socket_handle);
        *socket_handle = NET_SOCKET_INVALID;
    }
}

static void net_out_clear(unsigned slot);

static void net_shutdown(void)
{
    unsigned slot;
    net_close_socket(&g_net_listen);
    for (slot = 0; slot < NET_LOBBY_MAX_PLAYERS; ++slot) {
        net_close_socket(&g_net_peers[slot]);
        net_out_clear(slot);
        memset(&g_net_readers[slot], 0, sizeof(g_net_readers[slot]));
    }
    g_net_mode = NET_MODE_NONE;
    g_net_connecting = 0;
    g_net_in_game = 0;
    net_save_clear();
    if (g_net_wsa_started) {
        net_socket_cleanup();
        g_net_wsa_started = 0;
    }
}

/* A lobby that fails before the game starts returns to the setup screen,
   which shows the status line. */
static void net_lobby_failed(const char *status)
{
    net_shutdown();
    net_set_status(status);
    if (g_menu.screen == SCREEN_NEW_GAME) enter_net_setup_screen();
}

static int net_startup(void)
{
    if (g_net_wsa_started) return 1;
    if (!net_socket_startup()) {
#ifdef __EMSCRIPTEN__
        /* The browser has no TCP (Web port step 8). */
        net_set_status("Multijoueur indisponible dans cette version");
#else
        net_set_status("Reseau indisponible");
#endif
        return 0;
    }
    g_net_wsa_started = 1;
    return 1;
}

static void net_default_name(void)
{
    const char *name;
    if (g_net_name[0] != '\0') return;
    name = getenv("COMPUTERNAME");
    (void)snprintf(g_net_name, sizeof(g_net_name), "%s",
                   name != NULL && name[0] != '\0' ? name : "Joueur");
}

/* Win32: readiness arrives as WM_NET_SOCKET. remake_sdl polls instead. */
static void net_watch(NetSocket socket_handle)
{
#ifdef TONE_PLATFORM_SDL
    (void)socket_handle;
#else
    if (g_net_window != NULL)
        (void)WSAAsyncSelect((SOCKET)socket_handle, g_net_window, WM_NET_SOCKET,
                             FD_ACCEPT | FD_CONNECT | FD_READ | FD_CLOSE);
#endif
}

/* Outgoing bytes the system did not take yet, per peer. A full system
   buffer (slow link, a peer whose window is held by a drag, a save being
   sent) used to drop the peer, and a partly sent frame broke the stream;
   the queue keeps the frames in order and net_poll flushes it. Only a
   socket error or this much backlog drops a peer. */
enum { NET_OUT_CAPACITY = 1024 * 1024 };
typedef struct NetOutQueue {
    uint8_t *bytes;
    size_t start;
    size_t used;
} NetOutQueue;
static NetOutQueue g_net_out[NET_LOBBY_MAX_PLAYERS];

static void net_out_clear(unsigned slot)
{
    free(g_net_out[slot].bytes);
    memset(&g_net_out[slot], 0, sizeof(g_net_out[slot]));
}

/* 0 on a socket error. */
static int net_out_flush(unsigned slot)
{
    NetOutQueue *queue = &g_net_out[slot];
    int sent;
    if (queue->used == 0U) return 1;
    sent = net_socket_send_some(g_net_peers[slot], queue->bytes + queue->start, queue->used);
    if (sent < 0) return 0;
    queue->start += (size_t)sent;
    queue->used -= (size_t)sent;
    if (queue->used == 0U) queue->start = 0;
    return 1;
}

static size_t net_out_backlog(unsigned slot)
{
    return slot < NET_LOBBY_MAX_PLAYERS ? g_net_out[slot].used : 0U;
}

static int net_send(unsigned slot, const uint8_t *bytes, size_t length)
{
    NetOutQueue *queue;
    if (slot >= NET_LOBBY_MAX_PLAYERS || g_net_peers[slot] == NET_SOCKET_INVALID) return 0;
    queue = &g_net_out[slot];
    if (!net_out_flush(slot)) return 0;
    if (queue->used == 0U) {
        int sent = net_socket_send_some(g_net_peers[slot], bytes, length);
        if (sent < 0) return 0;
        bytes += sent;
        length -= (size_t)sent;
        if (length == 0U) return 1;
    }
    if (queue->bytes == NULL) {
        queue->bytes = (uint8_t *)malloc(NET_OUT_CAPACITY);
        if (queue->bytes == NULL) return 0;
    }
    if (length > NET_OUT_CAPACITY - queue->used) return 0;
    if (length > NET_OUT_CAPACITY - queue->start - queue->used) {
        memmove(queue->bytes, queue->bytes + queue->start, queue->used);
        queue->start = 0;
    }
    memcpy(queue->bytes + queue->start + queue->used, bytes, length);
    queue->used += length;
    return 1;
}

static void net_drop_peer(unsigned slot);

static void net_host_broadcast(const uint8_t *bytes, size_t length)
{
    unsigned slot;
    for (slot = 1; slot < NET_LOBBY_MAX_PLAYERS; ++slot)
        if (g_net_peers[slot] != NET_SOCKET_INVALID && !net_send(slot, bytes, length))
            net_drop_peer(slot);
}

static void net_sync_menu_from_lobby(void)
{
    uint8_t tribe;
    if (g_net_lobby.local_slot >= NET_LOBBY_MAX_PLAYERS) return;
    tribe = g_net_lobby.players[g_net_lobby.local_slot].tribe;
    if (tribe < NET_LOBBY_MAX_PLAYERS) g_menu.selected_tribe = tribe;
    if (g_net_lobby.world_index < g_menu.world_map.world_count)
        g_menu.world_index = g_net_lobby.world_index;
    if ((int)g_net_lobby.difficulty < g_difficulty_count)
        g_menu.difficulty = g_net_lobby.difficulty;
}

static void net_host_broadcast_state(void)
{
    uint8_t bytes[NET_FRAME_MAX_SIZE];
    size_t length = net_lobby_encode_player_list(&g_net_lobby, bytes, sizeof(bytes));
    net_sync_menu_from_lobby();
    if (length != 0U) net_host_broadcast(bytes, length);
}

static void net_drop_peer(unsigned slot)
{
    net_close_socket(&g_net_peers[slot]);
    net_out_clear(slot);
    memset(&g_net_readers[slot], 0, sizeof(g_net_readers[slot]));
    if (g_net_mode == NET_MODE_HOST) {
        if (g_net_in_game) {
            /* The departed player's tribe stays in the world, idle. As in
               FUN_004121b7 case 2 (FUN_00460072), its glyphs and artifacts
               go back to the world unless another player shares the tribe;
               the host queues it so every machine applies it on one turn. */
            uint8_t tribe = g_net_lobby.players[slot].tribe;
            unsigned other;
            int shared = 0;
            for (other = 0; other < NET_LOBBY_MAX_PLAYERS; ++other) {
                if (other != slot && g_net_lobby.players[other].connected &&
                    g_net_lobby.players[other].tribe == tribe) shared = 1;
            }
            if (!shared && tribe < GAME_START_PLAYER_COUNT) {
                int32_t arg = tribe;
                GameCommand command =
                    game_command_make(GAME_COMMAND_HAND_BACK_PLAYER, 1, &arg);
                (void)net_lockstep_queue_command(&g_net_lockstep, &command);
            }
            net_lockstep_drop_peer(&g_net_lockstep, (uint8_t)slot);
            (void)snprintf(g_net_status, sizeof(g_net_status), "%s a quitte la partie",
                           g_net_lobby.players[slot].name);
            net_notify_in_game();
        } else if (g_net_lobby.players[slot].connected) {
            (void)snprintf(g_net_status, sizeof(g_net_status), "%s a quitte le lobby",
                           g_net_lobby.players[slot].name);
        }
        net_lobby_remove_player(&g_net_lobby, (uint8_t)slot);
        g_net_save_sent[slot] = 0;
        g_net_save_acked &= (uint8_t)~(1U << slot);
        if (!g_net_in_game) net_host_broadcast_state();
    } else {
        /* Without the host no turn can be validated: continue alone. */
        if (!g_net_in_game) {
            net_lobby_failed("Connexion avec l'hote perdue");
            return;
        }
        net_shutdown();
        net_set_status("Connexion avec l'hote perdue, partie poursuivie en solo");
        net_notify_in_game();
    }
}

static int net_start_host(void)
{
    net_shutdown();
    if (!net_startup()) return 0;
    net_default_name();
    g_net_listen = net_socket_listen(g_net_port);
    if (g_net_listen == NET_SOCKET_INVALID) {
        (void)snprintf(g_net_status, sizeof(g_net_status),
                       "Port %u indisponible", (unsigned)g_net_port);
        net_shutdown();
        return 0;
    }
    net_watch(g_net_listen);
    /* Case 0x34 of FUN_00448e5a sends FUN_0041be72() (the low dword of
       QueryPerformanceCounter; here platform_counter) as the type-9 payload, and case 9 seeds the
       game RNG DAT_004a4b78 with it on every machine. */
    net_lobby_host_init(&g_net_lobby, g_net_name, (uint32_t)platform_counter());
    net_lobby_set_world(&g_net_lobby, (uint8_t)g_menu.world_index,
                        (uint8_t)g_menu.difficulty);
    g_net_mode = NET_MODE_HOST;
    net_sync_menu_from_lobby();
    (void)snprintf(g_net_status, sizeof(g_net_status),
                   "Hote sur le port %u, en attente de joueurs", (unsigned)g_net_port);
    return 1;
}

static int net_start_join(void)
{
    int lookup_failed;
    net_shutdown();
    if (!net_startup()) return 0;
    net_default_name();
    /* Blocking name lookup; numeric addresses skip it. */
    g_net_peers[0] = net_socket_connect(g_net_join_address, g_net_port, &lookup_failed);
    if (g_net_peers[0] == NET_SOCKET_INVALID) {
        net_set_status(lookup_failed ? "Adresse de l'hote introuvable" : "Connexion refusee");
        net_shutdown();
        return 0;
    }
    net_watch(g_net_peers[0]);
    net_lobby_client_init(&g_net_lobby);
    g_net_mode = NET_MODE_CLIENT;
    g_net_connecting = 1;
    (void)snprintf(g_net_status, sizeof(g_net_status), "Connexion a %s:%u...",
                   g_net_join_address, (unsigned)g_net_port);
    return 1;
}

static void net_apply_game_start(HWND window, const NetGameStart *start)
{
    uint8_t tribe = g_net_lobby.local_slot < NET_LOBBY_MAX_PLAYERS
        ? start->tribes[g_net_lobby.local_slot] : (uint8_t)NET_LOBBY_NO_TRIBE;
    if (tribe >= NET_LOBBY_MAX_PLAYERS ||
        start->world_index >= g_menu.world_map.world_count) {
        net_set_status("Debut de partie invalide");
        return;
    }
    g_menu.world_index = start->world_index;
    g_menu.difficulty = start->difficulty;
    g_menu.selected_tribe = tribe;
    g_random_state = start->seed;
    if (g_net_save_ready ? net_load_start(window, tribe) : begin_new_game(window)) {
        uint8_t peers = 0;
        unsigned slot;
        /* Same on every machine: built from the shared start record. */
        g_game_session.shared_bridge_player_mask = 0;
        for (slot = 0; slot < NET_LOBBY_MAX_PLAYERS; ++slot)
            if (start->tribes[slot] < GAME_START_PLAYER_COUNT)
                g_game_session.shared_bridge_player_mask |=
                    (uint8_t)(1U << start->tribes[slot]);
        if (g_net_mode == NET_MODE_HOST)
            for (slot = 1; slot < NET_LOBBY_MAX_PLAYERS; ++slot)
                if (g_net_lobby.players[slot].connected) peers |= (uint8_t)(1U << slot);
        net_lockstep_init(&g_net_lockstep, g_net_mode == NET_MODE_HOST, peers);
        tone_rng_seed(&g_net_local_rng, start->seed ^ platform_ticks_ms());
        g_net_in_game = 1;
        net_set_status("Partie en reseau");
    }
}

static void net_host_handle_frame(unsigned slot, const NetFrame *frame)
{
    uint8_t bytes[NET_FRAME_MAX_SIZE];
    size_t length;
    if (g_net_in_game) {
        GameCommand command;
        if (frame->type == NET_RECORD_COMMAND &&
            game_command_decode(frame->payload, frame->length, &command)) {
            if (!net_lockstep_queue_command(&g_net_lockstep, &command))
                net_set_status("File de commandes pleine: commande perdue");
        } else if (frame->type == NET_RECORD_PONG && frame->length == 4U) {
            uint32_t sent = (uint32_t)frame->payload[0] | ((uint32_t)frame->payload[1] << 8) |
                ((uint32_t)frame->payload[2] << 16) | ((uint32_t)frame->payload[3] << 24);
            uint32_t sample = platform_ticks_ms() - sent;
            unsigned peer;
            uint32_t slowest = 0;
            /* Rise at once, fall slowly, so a jitter spike widens the delay
               before it can stall a turn. */
            g_net_round_trip[slot] = sample > g_net_round_trip[slot] ? sample
                : (g_net_round_trip[slot] * 3U + sample) / 4U;
            for (peer = 1; peer < NET_LOBBY_MAX_PLAYERS; ++peer)
                if ((g_net_lockstep.peer_mask & (1U << peer)) &&
                    g_net_round_trip[peer] > slowest) slowest = g_net_round_trip[peer];
            net_lockstep_set_delay(&g_net_lockstep,
                net_lockstep_delay_for_round_trip(slowest, 50U));
        } else if (frame->type == NET_RECORD_TURN_ACK && frame->length == 4U) {
            net_lockstep_receive_ack(&g_net_lockstep, (uint8_t)slot,
                (uint32_t)frame->payload[0] | ((uint32_t)frame->payload[1] << 8) |
                ((uint32_t)frame->payload[2] << 16) | ((uint32_t)frame->payload[3] << 24));
        }
        return;
    }
    if (frame->type == NET_RECORD_HELLO && g_net_lobby.players[slot].connected == 0) {
        /* The socket index is the player slot. */
        int assigned = net_lobby_host_add_player(&g_net_lobby, (uint8_t)slot, frame);
        if (assigned < 0) {
            length = net_lobby_encode_reject(bytes, sizeof(bytes), (uint8_t)-assigned);
            (void)net_send(slot, bytes, length);
            net_close_socket(&g_net_peers[slot]);
            net_out_clear(slot);
            memset(&g_net_readers[slot], 0, sizeof(g_net_readers[slot]));
            return;
        }
        length = net_lobby_encode_welcome(bytes, sizeof(bytes), (uint8_t)assigned);
        (void)net_send((unsigned)assigned, bytes, length);
        net_host_broadcast_state();
        (void)snprintf(g_net_status, sizeof(g_net_status), "%s a rejoint la partie",
                       g_net_lobby.players[assigned].name);
    } else if (frame->type == NET_RECORD_TRIBE && frame->length == 1U &&
               g_net_lobby.players[slot].connected) {
        /* Only the host decides; the sender slot is the socket's, not the
           frame's claim. A loaded game offers its played tribes only. */
        if (g_tribe_choice_mask == 0 ||
            (frame->payload[0] < GAME_START_PLAYER_COUNT &&
             (g_tribe_choice_mask & (1U << frame->payload[0])) != 0))
            (void)net_lobby_set_tribe(&g_net_lobby, (uint8_t)slot, frame->payload[0]);
        net_host_broadcast_state();
    } else if (frame->type == NET_RECORD_SAVE_ACK &&
               g_net_lobby.players[slot].connected && g_net_save != NULL) {
        g_net_save_acked |= (uint8_t)(1U << slot);
        (void)snprintf(g_net_status, sizeof(g_net_status),
                       "%s a recu la partie chargee", g_net_lobby.players[slot].name);
    }
}

/* Guest: one chunk of the host's save; the whole file is applied as soon as
   it is complete and the host is told. */
static void net_client_receive_save(const NetFrame *frame)
{
    uint32_t total;
    uint32_t offset;
    size_t count;
    if (frame->length < 9U) return;
    total = net_le32(frame->payload + 1);
    offset = net_le32(frame->payload + 5);
    count = frame->length - 9U;
    if (total == 0U || total > 64U * 1024U * 1024U || offset > total ||
        count > total - offset) return;
    if (offset == 0U) {
        net_save_clear();
        g_net_save = (unsigned char *)malloc(total);
        if (g_net_save == NULL) return;
        g_net_save_length = total;
        g_net_save_native = frame->payload[0];
        net_set_status("Reception de la partie chargee par l'hote...");
    }
    if (g_net_save == NULL || total != g_net_save_length ||
        offset != g_net_save_received) return;
    memcpy(g_net_save + offset, frame->payload + 9, count);
    g_net_save_received += count;
    if (g_net_save_received != g_net_save_length) return;
    if (net_load_apply()) {
        uint8_t bytes[NET_FRAME_MAX_SIZE];
        size_t length = net_frame_encode(bytes, sizeof(bytes), NET_RECORD_SAVE_ACK,
                                         g_net_lobby.local_slot, NULL, 0);
        g_net_save_ready = 1;
        net_set_status("Partie chargee par l'hote : choisissez une tribu jouee");
        if (!net_send(0, bytes, length)) net_drop_peer(0);
    } else {
        net_set_status("La partie chargee par l'hote n'a pas pu etre lue");
    }
}

/* Host: a few chunks of the loaded save to each guest that lacks it, per
   poll, so the non-blocking sockets never fill up. */
static void net_host_send_save_chunks(void)
{
    unsigned slot;
    if (g_net_save == NULL || g_net_in_game) return;
    for (slot = 1; slot < NET_LOBBY_MAX_PLAYERS; ++slot) {
        unsigned chunk;
        if (g_net_peers[slot] == NET_SOCKET_INVALID ||
            !g_net_lobby.players[slot].connected) continue;
        for (chunk = 0; chunk < NET_SAVE_CHUNKS_PER_POLL &&
                        g_net_save_sent[slot] < g_net_save_length &&
                        net_out_backlog(slot) < 4U * NET_SAVE_CHUNK; ++chunk) {
            uint8_t payload[9 + NET_SAVE_CHUNK];
            uint8_t bytes[NET_FRAME_MAX_SIZE];
            size_t offset = g_net_save_sent[slot];
            size_t count = g_net_save_length - offset;
            size_t length;
            unsigned i;
            if (count > NET_SAVE_CHUNK) count = NET_SAVE_CHUNK;
            payload[0] = g_net_save_native;
            for (i = 0; i < 4U; ++i) {
                payload[1 + i] = (uint8_t)(g_net_save_length >> (8U * i));
                payload[5 + i] = (uint8_t)(offset >> (8U * i));
            }
            memcpy(payload + 9, g_net_save + offset, count);
            length = net_frame_encode(bytes, sizeof(bytes), NET_RECORD_SAVE_DATA, 0,
                                      payload, 9 + count);
            if (length == 0U) return;
            if (!net_send(slot, bytes, length)) {
                net_drop_peer(slot);
                break;
            }
            g_net_save_sent[slot] = offset + count;
        }
    }
}

static void net_poll_peer(HWND window, unsigned slot)
{
    char buffer[512];
    NetFrame frame;
    for (;;) {
        int received = net_socket_receive(g_net_peers[slot], buffer, sizeof(buffer));
        int status;
        if (received == NET_SOCKET_WOULD_BLOCK) return;
        if (received <= 0) {
            net_drop_peer(slot);
            return;
        }
        if (!net_frame_reader_push(&g_net_readers[slot], buffer, (size_t)received)) {
            net_drop_peer(slot);
            return;
        }
        while ((status = net_frame_reader_next(&g_net_readers[slot], &frame)) == 1) {
            if (g_net_mode == NET_MODE_HOST) {
                NetSocket before = g_net_peers[slot];
                net_host_handle_frame(slot, &frame);
                /* A refused HELLO closes the socket. */
                if (g_net_peers[slot] != before) return;
            } else if (frame.type == NET_RECORD_PING && frame.length == 4U) {
                uint8_t bytes[NET_FRAME_MAX_SIZE];
                size_t length = net_frame_encode(bytes, sizeof(bytes), NET_RECORD_PONG,
                    g_net_lobby.local_slot, frame.payload, 4);
                if (!net_send(0, bytes, length)) {
                    net_drop_peer(0);
                    return;
                }
            } else if (frame.type == NET_RECORD_LOBBY_RETURN && g_net_in_game) {
                net_back_to_lobby();
                net_set_status("L'hote charge une autre partie");
            } else if (frame.type == NET_RECORD_SAVE_DATA && !g_net_in_game) {
                net_client_receive_save(&frame);
            } else if (frame.type == NET_RECORD_TURN) {
                NetTurnBundle bundle;
                if (g_net_in_game &&
                    net_lockstep_decode_bundle(frame.payload, frame.length, &bundle))
                    (void)net_lockstep_receive_bundle(&g_net_lockstep, &bundle);
            } else {
                NetGameStart start;
                uint8_t reason = 0;
                int events = net_lobby_client_handle(&g_net_lobby, &frame, &start, &reason);
                if (events & NET_LOBBY_EVENT_REJECT) {
                    net_lobby_failed(reason == NET_REJECT_FULL ? "Partie complete"
                                     : reason == NET_REJECT_STARTED ? "Partie deja lancee"
                                     : "Version incompatible");
                    return;
                }
                if (events & NET_LOBBY_EVENT_WELCOME)
                    net_set_status("Connecte a l'hote");
                if (events & NET_LOBBY_EVENT_STATE) net_sync_menu_from_lobby();
                if (events & NET_LOBBY_EVENT_START) net_apply_game_start(window, &start);
            }
        }
        if (status < 0) {
            net_drop_peer(slot);
            return;
        }
    }
}

/* Called from the 50 ms timer on every screen; returns 1 if the lobby
   changed and the window should repaint. */
static int net_poll(HWND window)
{
    unsigned slot;
    char before[sizeof(g_net_status)];
    NetLobby lobby_before;
    if (g_net_mode == NET_MODE_NONE) return 0;
    memcpy(before, g_net_status, sizeof(before));
    lobby_before = g_net_lobby;
    if (g_net_mode == NET_MODE_HOST && g_net_listen != NET_SOCKET_INVALID) {
        NetSocket incoming;
        while ((incoming = net_socket_accept(g_net_listen)) != NET_SOCKET_INVALID) {
            unsigned free_slot = NET_LOBBY_MAX_PLAYERS;
            for (slot = 1; slot < NET_LOBBY_MAX_PLAYERS; ++slot)
                if (g_net_peers[slot] == NET_SOCKET_INVALID) { free_slot = slot; break; }
            if (free_slot == NET_LOBBY_MAX_PLAYERS || g_net_lobby.started) {
                uint8_t bytes[NET_FRAME_MAX_SIZE];
                size_t length = net_lobby_encode_reject(bytes, sizeof(bytes),
                    g_net_lobby.started ? NET_REJECT_STARTED : NET_REJECT_FULL);
                (void)net_socket_send(incoming, bytes, length);
                net_socket_close(incoming);
                continue;
            }
            net_watch(incoming);
            g_net_peers[free_slot] = incoming;
            memset(&g_net_readers[free_slot], 0, sizeof(g_net_readers[free_slot]));
        }
    }
    if (g_net_mode == NET_MODE_CLIENT && g_net_connecting) {
        int connected = net_socket_connect_status(g_net_peers[0]);
        if (connected < 0) {
            net_lobby_failed("Connexion refusee");
            return 1;
        }
        if (connected > 0) {
            uint8_t bytes[NET_FRAME_MAX_SIZE];
            size_t length = net_lobby_encode_hello(bytes, sizeof(bytes), g_net_name);
            g_net_connecting = 0;
            if (!net_send(0, bytes, length)) net_drop_peer(0);
            else net_set_status("Connecte, en attente de l'hote");
        }
    } else {
        for (slot = 0; slot < NET_LOBBY_MAX_PLAYERS && g_net_mode != NET_MODE_NONE; ++slot)
            if (g_net_peers[slot] != NET_SOCKET_INVALID && !net_out_flush(slot))
                net_drop_peer(slot);
        for (slot = 0; slot < NET_LOBBY_MAX_PLAYERS && g_net_mode != NET_MODE_NONE; ++slot)
            if (g_net_peers[slot] != NET_SOCKET_INVALID) net_poll_peer(window, slot);
    }
    if (g_net_mode == NET_MODE_HOST) net_host_send_save_chunks();
    return memcmp(before, g_net_status, sizeof(before)) != 0 ||
           memcmp(&lobby_before, &g_net_lobby, sizeof(lobby_before)) != 0;
}

/* New Game screen in a session. Native guard (FUN_0044e4f8, FUN_00448e5a):
   world size and difficulty only when DAT_004befec == DAT_004befe8 (local
   player is the host); a tribe click sends type 6 for the local player;
   BEGINGAME sends type 9 from the host. Returns 1 if consumed. */
static int net_newgame_message(HWND window, int message)
{
    if (g_net_mode == NET_MODE_NONE) return 0;
    if (message >= 60 && message <= 63) {
        uint8_t tribe = (uint8_t)(message - 60);
        if (g_tribe_choice_mask != 0 && (g_tribe_choice_mask & (1U << tribe)) == 0)
            return 1;
        if (g_net_mode == NET_MODE_HOST) {
            if (net_lobby_set_tribe(&g_net_lobby, 0, tribe)) net_host_broadcast_state();
        } else if (g_net_lobby.local_slot < NET_LOBBY_MAX_PLAYERS) {
            uint8_t bytes[NET_FRAME_MAX_SIZE];
            size_t length = net_lobby_encode_tribe(bytes, sizeof(bytes),
                                                   g_net_lobby.local_slot, tribe);
            if (!net_send(0, bytes, length)) net_drop_peer(0);
        }
        return 1;
    }
    if (g_net_mode != NET_MODE_HOST) return 1;
    if ((message == 53 || message == 55) && g_net_save != NULL) return 1;
    if (message == 53 || message == 55) {
        if (message == 53)
            g_menu.world_index = (g_menu.world_index + 1) % g_menu.world_map.world_count;
        else
            g_menu.difficulty = (g_menu.difficulty + 1) % g_difficulty_count;
        net_lobby_set_world(&g_net_lobby, (uint8_t)g_menu.world_index,
                            (uint8_t)g_menu.difficulty);
        net_host_broadcast_state();
        return 1;
    }
    if (message == 52) {
        NetGameStart start;
        uint8_t bytes[NET_FRAME_MAX_SIZE];
        size_t length;
        if (!net_lobby_game_start(&g_net_lobby, &start)) {
            net_set_status("Il faut deux joueurs et des tribus differentes");
            return 1;
        }
        if (g_net_save != NULL) {
            /* A loaded game starts once every guest applied the file, and
               only with tribes that were played in it. */
            unsigned slot;
            for (slot = 0; slot < NET_LOBBY_MAX_PLAYERS; ++slot) {
                if (!g_net_lobby.players[slot].connected) continue;
                if (slot != 0 && (g_net_save_acked & (1U << slot)) == 0) {
                    net_set_status("Envoi de la partie chargee en cours");
                    return 1;
                }
                if (start.tribes[slot] >= GAME_START_PLAYER_COUNT ||
                    (g_tribe_choice_mask & (1U << start.tribes[slot])) == 0) {
                    net_set_status("Chaque joueur doit choisir une tribu jouee");
                    return 1;
                }
            }
        }
        length = net_lobby_encode_game_start(&start, bytes, sizeof(bytes));
        net_host_broadcast(bytes, length);
        g_net_lobby.started = 1;
        net_close_socket(&g_net_listen);
        net_apply_game_start(window, &start);
        return 1;
    }
    return 1;
}

/* Every session change from the UI goes through here. Solo applies it at
   once. In a network game the command is bundled by the host and runs on
   every machine at the same turn; the caller gets the result predicted on a
   copy of the current state, since its own effect arrives a few turns later. */
static int issue_command(GameCommandKind kind, size_t count, const int32_t *args)
{
    GameCommand command = game_command_make(kind, count, args);
    GameCommandContext context;
    int predicted;
    context.pads = &g_pad_catalog;
    if (!g_net_in_game) return game_command_apply(&g_game_session, &context, &command);
    g_net_issue_ms = platform_ticks_ms();
    g_net_issue_tick = g_net_lockstep.tick;
    g_net_predicted_session = g_game_session;
    predicted = game_command_apply(&g_net_predicted_session, &context, &command);
    if (g_net_mode == NET_MODE_HOST) {
        if (!net_lockstep_queue_command(&g_net_lockstep, &command))
            net_set_status("File de commandes pleine: commande perdue");
    } else {
        uint8_t payload[GAME_COMMAND_ENCODED_SIZE];
        uint8_t bytes[NET_FRAME_MAX_SIZE];
        size_t length = game_command_encode(&command, payload, sizeof(payload));
        length = net_frame_encode(bytes, sizeof(bytes), NET_RECORD_COMMAND,
                                  g_net_lobby.local_slot, payload, length);
        if (!net_send(0, bytes, length)) net_drop_peer(0);
    }
    return predicted;
}

#define ISSUE_COMMAND(kind, ...) \
    issue_command((kind), sizeof((int32_t[]){__VA_ARGS__}) / sizeof(int32_t), \
                  (int32_t[]){__VA_ARGS__})

/* Runs the turns this frame may take: one turn per 50 ms frame like solo
   (each turn simulates network_speed ticks),
   up to three while a guest lags the host (net_lockstep_frame_ticks). Commands of a turn run before its first tick. The host pings
   every guest once a second; the slowest round trip sets the input delay
   (native: the period the host sends on channel 4, type 1). */
/* Frames the lockstep has waited in a row; past one second every player
   is told who the game waits for (no timeout: TCP keeps the link, and a
   slow player catches up instead of being dropped). */
static unsigned g_net_stall_frames;

static void net_report_stall(void)
{
    unsigned slot;
    const char *name = NULL;
    if (++g_net_stall_frames != 20U) return;
    if (g_net_mode == NET_MODE_HOST) {
        uint32_t turn = net_lockstep_turn(&g_net_lockstep);
        for (slot = 1; slot < NET_LOBBY_MAX_PLAYERS; ++slot)
            if ((g_net_lockstep.peer_mask & (1U << slot)) &&
                g_net_lockstep.acked[slot] + NET_TURN_HOST_LEAD <= turn)
                name = g_net_lobby.players[slot].name;
    } else {
        name = g_net_lobby.players[0].name;
    }
    if (name == NULL) return;
    (void)snprintf(g_net_status, sizeof(g_net_status), "En attente de %s", name);
    net_notify_in_game();
}

static void net_run_frame(HWND window)
{
    unsigned budget = 1;
    GameCommandContext context;
    if (!g_net_in_game || !g_game_session_valid) return;
    context.pads = &g_pad_catalog;
    if (g_net_mode == NET_MODE_HOST && ++g_net_ping_frames >= 20U) {
        uint8_t bytes[NET_FRAME_MAX_SIZE];
        uint32_t now = platform_ticks_ms();
        const uint8_t stamp[4] = {(uint8_t)(now & 0xffU), (uint8_t)((now >> 8) & 0xffU),
                                  (uint8_t)((now >> 16) & 0xffU), (uint8_t)(now >> 24)};
        size_t length = net_frame_encode(bytes, sizeof(bytes), NET_RECORD_PING, 0, stamp, 4);
        g_net_ping_frames = 0;
        net_host_broadcast(bytes, length);
    }
    budget = net_lockstep_frame_ticks(&g_net_lockstep);
    if (!g_net_lockstep.desync) {
        if (net_lockstep_can_tick(&g_net_lockstep)) g_net_stall_frames = 0;
        else net_report_stall();
    }
    while (budget-- != 0U && net_lockstep_can_tick(&g_net_lockstep)) {
        const NetTurnBundle *bundle = net_lockstep_turn_commands(&g_net_lockstep);
        NetTurnBundle created[NET_TURN_MAX_DELAY + 1];
        size_t created_count;
        unsigned i;
        if (bundle != NULL)
            for (i = 0; i < bundle->command_count; ++i) {
                (void)game_command_apply(&g_game_session, &context, &bundle->commands[i]);
                g_net_apply_ms = platform_ticks_ms();
                g_net_apply_tick = g_net_lockstep.tick;
            }
        /* A paused network game keeps exchanging turns (so the command
           that resumes it can arrive) but its world stands still. */
        g_paused = g_game_session.network_paused;
        if (!g_game_session.network_paused) {
            /* FUN_0041c46f runs DAT_004bf110 ticks per frame; a turn here
               carries the same count on every machine. */
            unsigned speed = g_game_session.network_speed;
            unsigned step;
            if (speed < 1U || speed > 3U) speed = 1U;
            for (step = 0; step < speed; ++step) {
                simulate_session_tick(g_game_session.simulation_tick);
                if (run_world_sequence_step(window)) return;
            }
        }
        created_count = net_lockstep_finish_tick(&g_net_lockstep,
            game_session_sync_hash(&g_game_session), created,
            sizeof(created) / sizeof(created[0]));
        {
            uint8_t payload[NET_FRAME_MAX_PAYLOAD];
            uint8_t bytes[NET_FRAME_MAX_SIZE];
            size_t length;
            if (g_net_mode == NET_MODE_HOST) {
                for (i = 0; i < created_count; ++i) {
                    length = net_lockstep_encode_bundle(&created[i], payload, sizeof(payload));
                    length = net_frame_encode(bytes, sizeof(bytes), NET_RECORD_TURN, 0,
                                              payload, length);
                    if (length != 0U) net_host_broadcast(bytes, length);
                }
            } else {
                uint32_t done = net_lockstep_turn(&g_net_lockstep);
                payload[0] = (uint8_t)(done & 0xffU);
                payload[1] = (uint8_t)((done >> 8) & 0xffU);
                payload[2] = (uint8_t)((done >> 16) & 0xffU);
                payload[3] = (uint8_t)(done >> 24);
                length = net_frame_encode(bytes, sizeof(bytes), NET_RECORD_TURN_ACK,
                                          g_net_lobby.local_slot, payload, 4);
                if (!net_send(0, bytes, length)) {
                    net_drop_peer(0);
                    return;
                }
            }
        }
        if (g_net_lockstep.desync) {
            (void)snprintf(g_net_status, sizeof(g_net_status),
                           "Desynchronisation au tour %lu",
                           (unsigned long)g_net_lockstep.desync_turn);
            net_notify_in_game();
            break;
        }
    }
}

static void net_leave_lobby(void)
{
    if (g_net_mode != NET_MODE_NONE) net_shutdown();
    g_net_status[0] = '\0';
}

/* FUN_0044ec5d lists the session players (DAT_004beff0) on the New Game
   screen when DAT_004befe0 != 0; its geometry is not ported, so the remake
   draws a plain two-column list in the free band above the top tribe glyph. */
static void render_net_lobby(RenderSurface *surface)
{
    char line[96];
    unsigned slot;
    COLORREF color = RGB(235, 235, 220);
    if (g_net_mode == NET_MODE_NONE && g_net_status[0] == '\0') return;
    if (g_net_mode != NET_MODE_NONE) {
        draw_small_label(surface, g_net_mode == NET_MODE_HOST ? "Partie reseau (hote)"
                                                          : "Partie reseau (invite)",
                         200, 2, color);
        for (slot = 0; slot < NET_LOBBY_MAX_PLAYERS; ++slot) {
            const NetLobbyPlayer *player = &g_net_lobby.players[slot];
            if (!player->connected) continue;
            if (player->tribe < NET_LOBBY_MAX_PLAYERS)
                (void)snprintf(line, sizeof(line), "%c%u %s - tribu %u",
                               slot == g_net_lobby.local_slot ? '>' : ' ', slot + 1U,
                               player->name, player->tribe + 1U);
            else
                (void)snprintf(line, sizeof(line), "%c%u %s",
                               slot == g_net_lobby.local_slot ? '>' : ' ', slot + 1U,
                               player->name);
            draw_small_label(surface, line, 200 + (int)(slot % 2U) * 130,
                             14 + (int)(slot / 2U) * 12, color);
        }
    }
    draw_small_label(surface, g_net_status, 200, 40, RGB(255, 220, 120));
}
