/* Multiplayer lobby transport (behavior/multiplayer.md). The original opens a
   DirectPlay session outside the game screens and then uses the New Game
   screen (state 1) as the lobby; DirectPlay is not available to the remake,
   so it carries the core NetLobby records over a plain TCP connection: one
   host socket accepts up to three guests, guests talk only to the host (the
   native send path FUN_00412d70 also routes non-host records to the host).
   Sockets are non-blocking and post WM_NET_SOCKET to the window, so frames
   are handled when they arrive rather than at the next 50 ms timer (that
   polling alone added up to two frames to every round trip). After the
   start, the same connections carry the NetLockstep turns. */

enum { NET_MODE_NONE, NET_MODE_HOST, NET_MODE_CLIENT };
enum { WM_NET_SOCKET = WM_APP + 1 };

static HWND g_net_window;

static int g_net_mode;
static int g_net_wsa_started;
static int g_net_connecting;
static SOCKET g_net_listen = INVALID_SOCKET;
static SOCKET g_net_peers[NET_LOBBY_MAX_PLAYERS] = {
    INVALID_SOCKET, INVALID_SOCKET, INVALID_SOCKET, INVALID_SOCKET};
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

static void net_close_socket(SOCKET *socket_handle)
{
    if (*socket_handle != INVALID_SOCKET) {
        (void)closesocket(*socket_handle);
        *socket_handle = INVALID_SOCKET;
    }
}

static void net_shutdown(void)
{
    unsigned slot;
    net_close_socket(&g_net_listen);
    for (slot = 0; slot < NET_LOBBY_MAX_PLAYERS; ++slot) {
        net_close_socket(&g_net_peers[slot]);
        memset(&g_net_readers[slot], 0, sizeof(g_net_readers[slot]));
    }
    g_net_mode = NET_MODE_NONE;
    g_net_connecting = 0;
    g_net_in_game = 0;
    if (g_net_wsa_started) {
        (void)WSACleanup();
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
    WSADATA data;
    if (g_net_wsa_started) return 1;
    if (WSAStartup(MAKEWORD(2, 2), &data) != 0) {
        net_set_status("Winsock indisponible");
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

static void net_set_nonblocking(SOCKET socket_handle)
{
    u_long enabled = 1;
    /* WSAAsyncSelect also makes the socket non-blocking. */
    if (g_net_window != NULL &&
        WSAAsyncSelect(socket_handle, g_net_window, WM_NET_SOCKET,
                       FD_ACCEPT | FD_CONNECT | FD_READ | FD_CLOSE) == 0) return;
    (void)ioctlsocket(socket_handle, FIONBIO, &enabled);
}

/* Frames are a few hundred bytes; a full send buffer drops the peer. */
static int net_send(unsigned slot, const uint8_t *bytes, size_t length)
{
    size_t sent = 0;
    if (slot >= NET_LOBBY_MAX_PLAYERS || g_net_peers[slot] == INVALID_SOCKET) return 0;
    while (sent < length) {
        int result = send(g_net_peers[slot], (const char *)bytes + sent,
                          (int)(length - sent), 0);
        if (result <= 0) return 0;
        sent += (size_t)result;
    }
    return 1;
}

static void net_drop_peer(unsigned slot);

static void net_host_broadcast(const uint8_t *bytes, size_t length)
{
    unsigned slot;
    for (slot = 1; slot < NET_LOBBY_MAX_PLAYERS; ++slot)
        if (g_net_peers[slot] != INVALID_SOCKET && !net_send(slot, bytes, length))
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
    memset(&g_net_readers[slot], 0, sizeof(g_net_readers[slot]));
    if (g_net_mode == NET_MODE_HOST) {
        if (g_net_in_game) {
            /* The departed player's tribe stays in the world, idle. */
            net_lockstep_drop_peer(&g_net_lockstep, (uint8_t)slot);
            (void)snprintf(g_net_status, sizeof(g_net_status), "%s a quitte la partie",
                           g_net_lobby.players[slot].name);
            net_notify_in_game();
        } else if (g_net_lobby.players[slot].connected) {
            (void)snprintf(g_net_status, sizeof(g_net_status), "%s a quitte le lobby",
                           g_net_lobby.players[slot].name);
        }
        net_lobby_remove_player(&g_net_lobby, (uint8_t)slot);
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
    struct sockaddr_in address;
    LARGE_INTEGER counter;
    net_shutdown();
    if (!net_startup()) return 0;
    net_default_name();
    g_net_listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(g_net_port);
    if (g_net_listen == INVALID_SOCKET ||
        bind(g_net_listen, (struct sockaddr *)&address, sizeof(address)) != 0 ||
        listen(g_net_listen, 4) != 0) {
        (void)snprintf(g_net_status, sizeof(g_net_status),
                       "Port %u indisponible", (unsigned)g_net_port);
        net_shutdown();
        return 0;
    }
    net_set_nonblocking(g_net_listen);
    /* Case 0x34 of FUN_00448e5a sends FUN_0041be72() (the low dword of
       QueryPerformanceCounter) as the type-9 payload, and case 9 seeds the
       game RNG DAT_004a4b78 with it on every machine. */
    QueryPerformanceCounter(&counter);
    net_lobby_host_init(&g_net_lobby, g_net_name, (uint32_t)counter.LowPart);
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
    struct sockaddr_in address;
    int connected;
    net_shutdown();
    if (!net_startup()) return 0;
    net_default_name();
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(g_net_port);
    address.sin_addr.s_addr = inet_addr(g_net_join_address);
    if (address.sin_addr.s_addr == INADDR_NONE) {
        /* Blocking name lookup; numeric addresses skip it. */
        const struct hostent *host = gethostbyname(g_net_join_address);
        if (host == NULL || host->h_addrtype != AF_INET || host->h_addr_list[0] == NULL) {
            net_set_status("Adresse de l'hote introuvable");
            net_shutdown();
            return 0;
        }
        memcpy(&address.sin_addr, host->h_addr_list[0], sizeof(address.sin_addr));
    }
    g_net_peers[0] = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (g_net_peers[0] == INVALID_SOCKET) {
        net_shutdown();
        return 0;
    }
    net_set_nonblocking(g_net_peers[0]);
    connected = connect(g_net_peers[0], (struct sockaddr *)&address, sizeof(address)) == 0;
    if (!connected && WSAGetLastError() != WSAEWOULDBLOCK) {
        net_set_status("Connexion refusee");
        net_shutdown();
        return 0;
    }
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
    if (begin_new_game(window)) {
        uint8_t peers = 0;
        unsigned slot;
        if (g_net_mode == NET_MODE_HOST)
            for (slot = 1; slot < NET_LOBBY_MAX_PLAYERS; ++slot)
                if (g_net_lobby.players[slot].connected) peers |= (uint8_t)(1U << slot);
        net_lockstep_init(&g_net_lockstep, g_net_mode == NET_MODE_HOST, peers);
        tone_rng_seed(&g_net_local_rng, start->seed ^ (uint32_t)GetTickCount());
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
            uint32_t sample = (uint32_t)GetTickCount() - sent;
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
           frame's claim. */
        (void)net_lobby_set_tribe(&g_net_lobby, (uint8_t)slot, frame->payload[0]);
        net_host_broadcast_state();
    }
}

static void net_poll_peer(HWND window, unsigned slot)
{
    char buffer[512];
    NetFrame frame;
    for (;;) {
        int received = recv(g_net_peers[slot], buffer, (int)sizeof(buffer), 0);
        int status;
        if (received == 0 ||
            (received < 0 && WSAGetLastError() != WSAEWOULDBLOCK)) {
            net_drop_peer(slot);
            return;
        }
        if (received < 0) return;
        if (!net_frame_reader_push(&g_net_readers[slot], buffer, (size_t)received)) {
            net_drop_peer(slot);
            return;
        }
        while ((status = net_frame_reader_next(&g_net_readers[slot], &frame)) == 1) {
            if (g_net_mode == NET_MODE_HOST) {
                SOCKET before = g_net_peers[slot];
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
    if (g_net_mode == NET_MODE_HOST && g_net_listen != INVALID_SOCKET) {
        SOCKET incoming;
        while ((incoming = accept(g_net_listen, NULL, NULL)) != INVALID_SOCKET) {
            unsigned free_slot = NET_LOBBY_MAX_PLAYERS;
            for (slot = 1; slot < NET_LOBBY_MAX_PLAYERS; ++slot)
                if (g_net_peers[slot] == INVALID_SOCKET) { free_slot = slot; break; }
            net_set_nonblocking(incoming);
            if (free_slot == NET_LOBBY_MAX_PLAYERS || g_net_lobby.started) {
                uint8_t bytes[NET_FRAME_MAX_SIZE];
                size_t length = net_lobby_encode_reject(bytes, sizeof(bytes),
                    g_net_lobby.started ? NET_REJECT_STARTED : NET_REJECT_FULL);
                (void)send(incoming, (const char *)bytes, (int)length, 0);
                (void)closesocket(incoming);
                continue;
            }
            g_net_peers[free_slot] = incoming;
            memset(&g_net_readers[free_slot], 0, sizeof(g_net_readers[free_slot]));
        }
    }
    if (g_net_mode == NET_MODE_CLIENT && g_net_connecting) {
        fd_set writable;
        fd_set failed;
        struct timeval no_wait = {0, 0};
        FD_ZERO(&writable);
        FD_ZERO(&failed);
        FD_SET(g_net_peers[0], &writable);
        FD_SET(g_net_peers[0], &failed);
        if (select(0, NULL, &writable, &failed, &no_wait) > 0) {
            if (FD_ISSET(g_net_peers[0], &failed)) {
                net_lobby_failed("Connexion refusee");
                return 1;
            }
            if (FD_ISSET(g_net_peers[0], &writable)) {
                uint8_t bytes[NET_FRAME_MAX_SIZE];
                size_t length = net_lobby_encode_hello(bytes, sizeof(bytes), g_net_name);
                g_net_connecting = 0;
                if (!net_send(0, bytes, length)) net_drop_peer(0);
                else net_set_status("Connecte, en attente de l'hote");
            }
        }
    } else {
        for (slot = 0; slot < NET_LOBBY_MAX_PLAYERS && g_net_mode != NET_MODE_NONE; ++slot)
            if (g_net_peers[slot] != INVALID_SOCKET) net_poll_peer(window, slot);
    }
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
    g_net_issue_ms = (uint32_t)GetTickCount();
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

/* Runs the turns this frame may take: one tick per 50 ms frame like solo,
   up to three while a guest lags the host (net_lockstep_frame_ticks). Commands of a turn run before its first tick. The host pings
   every guest once a second; the slowest round trip sets the input delay
   (native: the period the host sends on channel 4, type 1). */
static void net_run_frame(HWND window)
{
    unsigned budget = 1;
    GameCommandContext context;
    (void)window;
    if (!g_net_in_game || !g_game_session_valid) return;
    context.pads = &g_pad_catalog;
    if (g_net_mode == NET_MODE_HOST && ++g_net_ping_frames >= 20U) {
        uint8_t bytes[NET_FRAME_MAX_SIZE];
        uint32_t now = (uint32_t)GetTickCount();
        const uint8_t stamp[4] = {(uint8_t)(now & 0xffU), (uint8_t)((now >> 8) & 0xffU),
                                  (uint8_t)((now >> 16) & 0xffU), (uint8_t)(now >> 24)};
        size_t length = net_frame_encode(bytes, sizeof(bytes), NET_RECORD_PING, 0, stamp, 4);
        g_net_ping_frames = 0;
        net_host_broadcast(bytes, length);
    }
    budget = net_lockstep_frame_ticks(&g_net_lockstep);
    while (budget-- != 0U && net_lockstep_can_tick(&g_net_lockstep)) {
        const NetTurnBundle *bundle = net_lockstep_turn_commands(&g_net_lockstep);
        NetTurnBundle created[NET_TURN_MAX_DELAY + 1];
        size_t created_count;
        unsigned i;
        if (bundle != NULL)
            for (i = 0; i < bundle->command_count; ++i) {
                (void)game_command_apply(&g_game_session, &context, &bundle->commands[i]);
                g_net_apply_ms = (uint32_t)GetTickCount();
                g_net_apply_tick = g_net_lockstep.tick;
            }
        simulate_session_tick(g_game_session.simulation_tick);
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
