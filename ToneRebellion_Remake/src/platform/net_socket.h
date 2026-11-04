/* Non-blocking TCP sockets for the multiplayer transport (net_session.inc),
   shared by remake_menu and remake_sdl: Winsock on Windows, BSD sockets
   elsewhere. No system type crosses this header, so the SDL shell, which
   does not include <windows.h>, can use it too. */
#ifndef TONE_NET_SOCKET_H
#define TONE_NET_SOCKET_H

#include <stddef.h>
#include <stdint.h>

/* Winsock's SOCKET or a POSIX descriptor; both fit an intptr_t. */
typedef intptr_t NetSocket;
#define NET_SOCKET_INVALID ((NetSocket)-1)

enum {
    NET_SOCKET_WOULD_BLOCK = -1,
    NET_SOCKET_FAILED = -2
};

/* Returns 0 when the system has no TCP (the browser build). Each successful
   startup needs one cleanup. */
int net_socket_startup(void);
void net_socket_cleanup(void);

/* Listens on every IPv4 interface. */
NetSocket net_socket_listen(uint16_t port);
/* NET_SOCKET_INVALID when no connection is waiting. */
NetSocket net_socket_accept(NetSocket listener);
/* Starts a connection to a numeric address or a host name (blocking name
   lookup). On failure *lookup_failed tells whether the name was unknown. */
NetSocket net_socket_connect(const char *host, uint16_t port, int *lookup_failed);
/* 1 connected, 0 still pending, -1 refused. */
int net_socket_connect_status(NetSocket socket_handle);
/* Sends the whole buffer; 0 if it does not fit (a full buffer is a failure). */
int net_socket_send(NetSocket socket_handle, const void *bytes, size_t length);
/* Sends what the system takes now: bytes sent (0 when its buffer is full),
   or NET_SOCKET_FAILED. */
int net_socket_send_some(NetSocket socket_handle, const void *bytes, size_t length);
/* Bytes read, 0 once the peer closed, or NET_SOCKET_WOULD_BLOCK / FAILED. */
int net_socket_receive(NetSocket socket_handle, void *buffer, size_t capacity);
void net_socket_close(NetSocket socket_handle);

#endif
