#include "net_socket.h"

#include <string.h>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
typedef int socklen_t;
#define net_socket_error() WSAGetLastError()
#define NET_ERROR_WOULD_BLOCK WSAEWOULDBLOCK
#define NET_ERROR_IN_PROGRESS WSAEWOULDBLOCK
#else
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
typedef int SOCKET;
#define INVALID_SOCKET (-1)
#define closesocket close
#define net_socket_error() errno
#define NET_ERROR_WOULD_BLOCK EWOULDBLOCK
#define NET_ERROR_IN_PROGRESS EINPROGRESS
#endif

/* A peer that closes must not kill the process with SIGPIPE. */
#ifdef MSG_NOSIGNAL
#define NET_SEND_FLAGS MSG_NOSIGNAL
#else
#define NET_SEND_FLAGS 0
#endif

static int net_socket_would_block(void)
{
    int error = net_socket_error();
#ifndef _WIN32
    if (error == EAGAIN) return 1;
#endif
    return error == NET_ERROR_WOULD_BLOCK;
}

static int net_socket_set_nonblocking(SOCKET socket_handle)
{
#ifdef _WIN32
    u_long enabled = 1;
    return ioctlsocket(socket_handle, FIONBIO, &enabled) == 0;
#else
    int flags = fcntl(socket_handle, F_GETFL, 0);
#ifdef SO_NOSIGPIPE
    int enabled = 1;
    (void)setsockopt(socket_handle, SOL_SOCKET, SO_NOSIGPIPE, &enabled, sizeof(enabled));
#endif
    return flags >= 0 && fcntl(socket_handle, F_SETFL, flags | O_NONBLOCK) == 0;
#endif
}

int net_socket_startup(void)
{
#if defined(__EMSCRIPTEN__)
    /* Emscripten maps sockets onto WebSockets, not TCP. */
    return 0;
#elif defined(_WIN32)
    WSADATA data;
    return WSAStartup(MAKEWORD(2, 2), &data) == 0;
#else
    return 1;
#endif
}

void net_socket_cleanup(void)
{
#ifdef _WIN32
    (void)WSACleanup();
#endif
}

NetSocket net_socket_listen(uint16_t port)
{
    struct sockaddr_in address;
    SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listener == INVALID_SOCKET) return NET_SOCKET_INVALID;
#ifndef _WIN32
    {
        /* Lets a new host reuse the port while the last game's connections
           wait out TIME_WAIT. On Windows the option would let another
           program take the port over, so it stays off. */
        int enabled = 1;
        (void)setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &enabled, sizeof(enabled));
    }
#endif
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(port);
    if (bind(listener, (struct sockaddr *)&address, sizeof(address)) != 0 ||
        listen(listener, 4) != 0 || !net_socket_set_nonblocking(listener)) {
        (void)closesocket(listener);
        return NET_SOCKET_INVALID;
    }
    return (NetSocket)listener;
}

NetSocket net_socket_accept(NetSocket listener)
{
    SOCKET incoming = accept((SOCKET)listener, NULL, NULL);
    if (incoming == INVALID_SOCKET) return NET_SOCKET_INVALID;
    (void)net_socket_set_nonblocking(incoming);
    return (NetSocket)incoming;
}

NetSocket net_socket_connect(const char *host, uint16_t port, int *lookup_failed)
{
    struct addrinfo hints;
    struct addrinfo *found = NULL;
    struct sockaddr_in address;
    SOCKET peer;
    *lookup_failed = 0;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    if (getaddrinfo(host, NULL, &hints, &found) != 0 || found == NULL ||
        found->ai_addrlen < (socklen_t)sizeof(address)) {
        if (found != NULL) freeaddrinfo(found);
        *lookup_failed = 1;
        return NET_SOCKET_INVALID;
    }
    memcpy(&address, found->ai_addr, sizeof(address));
    freeaddrinfo(found);
    address.sin_port = htons(port);
    peer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (peer == INVALID_SOCKET) return NET_SOCKET_INVALID;
    if (!net_socket_set_nonblocking(peer) ||
        (connect(peer, (struct sockaddr *)&address, sizeof(address)) != 0 &&
         net_socket_error() != NET_ERROR_IN_PROGRESS)) {
        (void)closesocket(peer);
        return NET_SOCKET_INVALID;
    }
    return (NetSocket)peer;
}

int net_socket_connect_status(NetSocket socket_handle)
{
    SOCKET peer = (SOCKET)socket_handle;
    fd_set writable;
    fd_set failed;
    struct timeval no_wait = {0, 0};
    int error = 0;
    socklen_t size = (socklen_t)sizeof(error);
    FD_ZERO(&writable);
    FD_ZERO(&failed);
    FD_SET(peer, &writable);
    FD_SET(peer, &failed);
    /* Winsock ignores the first argument and reports a refused connection
       in the exception set; POSIX reports it as writable with SO_ERROR. */
    if (select((int)peer + 1, NULL, &writable, &failed, &no_wait) <= 0) return 0;
    if (FD_ISSET(peer, &failed)) return -1;
    if (!FD_ISSET(peer, &writable)) return 0;
    if (getsockopt(peer, SOL_SOCKET, SO_ERROR, (char *)&error, &size) != 0 || error != 0)
        return -1;
    return 1;
}

int net_socket_send(NetSocket socket_handle, const void *bytes, size_t length)
{
    size_t sent = 0;
    while (sent < length) {
        int result = (int)send((SOCKET)socket_handle, (const char *)bytes + sent,
                               (int)(length - sent), NET_SEND_FLAGS);
        if (result <= 0) return 0;
        sent += (size_t)result;
    }
    return 1;
}

int net_socket_receive(NetSocket socket_handle, void *buffer, size_t capacity)
{
    int received = (int)recv((SOCKET)socket_handle, (char *)buffer, (int)capacity, 0);
    if (received >= 0) return received;
    return net_socket_would_block() ? NET_SOCKET_WOULD_BLOCK : NET_SOCKET_FAILED;
}

void net_socket_close(NetSocket socket_handle)
{
    if (socket_handle != NET_SOCKET_INVALID) (void)closesocket((SOCKET)socket_handle);
}
