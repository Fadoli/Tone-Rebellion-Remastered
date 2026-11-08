#ifndef TONE_NET_SERVER_LIST_H
#define TONE_NET_SERVER_LIST_H

#include <stddef.h>
#include <stdint.h>

/* Servers shown on the remake's Join screen. Today the list holds the hosts
   this player joined (saved in saves\servers.cfg, most recent first); a
   future lobby server will add public entries, which are never saved.
   Remake only: the original joins through a DirectPlay property sheet. */

enum {
    NET_SERVER_LIST_MAX = 16,
    NET_SERVER_ADDRESS_CAPACITY = 128,
    NET_SERVER_LABEL_CAPACITY = 32
};

typedef enum NetServerSource {
    NET_SERVER_SOURCE_RECENT = 0, /* joined from this machine */
    NET_SERVER_SOURCE_PUBLIC = 1  /* announced by a lobby server (not yet) */
} NetServerSource;

typedef struct NetServerEntry {
    char address[NET_SERVER_ADDRESS_CAPACITY]; /* host name or IP, no spaces */
    uint16_t port;
    char label[NET_SERVER_LABEL_CAPACITY];     /* host player name, if known */
    uint64_t last_used;                        /* seconds since 1970, 0 = unknown */
    uint8_t source;
} NetServerEntry;

typedef struct NetServerList {
    NetServerEntry entries[NET_SERVER_LIST_MAX];
    unsigned count;
} NetServerList;

void net_server_list_clear(NetServerList *list);
/* Reads "server <port> <last_used> <address> [label]" lines; malformed
   lines are skipped. Returns the number of entries read. */
unsigned net_server_list_parse(NetServerList *list, const char *text, size_t length);
/* Writes the recent entries in the parse format; returns the length, or 0
   when `capacity` is too small (the output is then empty). */
size_t net_server_list_format(const NetServerList *list, char *out, size_t capacity);
/* Moves (or adds) address:port to the top as a recent entry. A non-empty
   `label` replaces the stored one. The oldest entry goes when full.
   Returns its index (0), or -1 for an unusable address or port. */
int net_server_list_remember(NetServerList *list, const char *address, uint16_t port,
                             const char *label, uint64_t now);
/* Index of address:port, or -1. */
int net_server_list_find(const NetServerList *list, const char *address, uint16_t port);
void net_server_list_remove(NetServerList *list, unsigned index);
/* Whether an address can be stored and typed: 1..127 printable characters
   without spaces. */
int net_server_address_valid(const char *address);

#endif
