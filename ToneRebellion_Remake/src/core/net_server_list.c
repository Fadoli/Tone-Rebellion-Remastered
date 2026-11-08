#include "net_server_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void net_server_list_clear(NetServerList *list)
{
    memset(list, 0, sizeof(*list));
}

int net_server_address_valid(const char *address)
{
    size_t length = 0;
    if (address == NULL) return 0;
    for (; address[length] != '\0'; ++length) {
        const unsigned char c = (unsigned char)address[length];
        if (c <= ' ' || c > '~' || length + 1U >= NET_SERVER_ADDRESS_CAPACITY) return 0;
    }
    return length > 0;
}

/* Labels are player names: printable ASCII, cut to the capacity. */
static void copy_label(char *out, const char *label)
{
    size_t i;
    for (i = 0; label != NULL && label[i] != '\0' && i + 1U < NET_SERVER_LABEL_CAPACITY; ++i) {
        const unsigned char c = (unsigned char)label[i];
        out[i] = (char)(c < ' ' || c > '~' ? '?' : c);
    }
    out[i] = '\0';
}

int net_server_list_find(const NetServerList *list, const char *address, uint16_t port)
{
    unsigned i;
    for (i = 0; i < list->count; ++i)
        if (list->entries[i].port == port && strcmp(list->entries[i].address, address) == 0)
            return (int)i;
    return -1;
}

void net_server_list_remove(NetServerList *list, unsigned index)
{
    if (index >= list->count) return;
    memmove(&list->entries[index], &list->entries[index + 1U],
            (list->count - index - 1U) * sizeof(list->entries[0]));
    --list->count;
    memset(&list->entries[list->count], 0, sizeof(list->entries[0]));
}

int net_server_list_remember(NetServerList *list, const char *address, uint16_t port,
                             const char *label, uint64_t now)
{
    NetServerEntry entry;
    int found;
    if (!net_server_address_valid(address) || port == 0) return -1;
    found = net_server_list_find(list, address, port);
    if (found >= 0) {
        entry = list->entries[found];
        net_server_list_remove(list, (unsigned)found);
    } else {
        memset(&entry, 0, sizeof(entry));
        (void)snprintf(entry.address, sizeof(entry.address), "%s", address);
        entry.port = port;
        if (list->count == NET_SERVER_LIST_MAX) net_server_list_remove(list, list->count - 1U);
    }
    if (label != NULL && label[0] != '\0') copy_label(entry.label, label);
    entry.last_used = now;
    entry.source = NET_SERVER_SOURCE_RECENT;
    memmove(&list->entries[1], &list->entries[0], list->count * sizeof(list->entries[0]));
    list->entries[0] = entry;
    ++list->count;
    return 0;
}

/* One line, already cut out of the text (no newline). */
static void parse_line(NetServerList *list, const char *line)
{
    char address[NET_SERVER_ADDRESS_CAPACITY];
    char *end;
    unsigned long port;
    unsigned long long stamp;
    size_t length;
    NetServerEntry *entry;
    if (strncmp(line, "server ", 7) != 0 || list->count >= NET_SERVER_LIST_MAX) return;
    line += 7;
    port = strtoul(line, &end, 10);
    if (end == line || *end != ' ' || port == 0 || port > 65535UL) return;
    line = end + 1;
    stamp = strtoull(line, &end, 10);
    if (end == line || *end != ' ') return;
    line = end + 1;
    length = strcspn(line, " ");
    if (length == 0 || length >= sizeof(address)) return;
    memcpy(address, line, length);
    address[length] = '\0';
    if (!net_server_address_valid(address) ||
        net_server_list_find(list, address, (uint16_t)port) >= 0) return;
    line += length;
    if (*line == ' ') ++line;
    entry = &list->entries[list->count++];
    memset(entry, 0, sizeof(*entry));
    memcpy(entry->address, address, length + 1U);
    entry->port = (uint16_t)port;
    entry->last_used = (uint64_t)stamp;
    entry->source = NET_SERVER_SOURCE_RECENT;
    copy_label(entry->label, line);
}

unsigned net_server_list_parse(NetServerList *list, const char *text, size_t length)
{
    char line[256];
    size_t at = 0;
    net_server_list_clear(list);
    while (at < length) {
        size_t used = 0;
        while (at < length && text[at] != '\n') {
            if (text[at] != '\r' && used + 1U < sizeof(line)) line[used++] = text[at];
            ++at;
        }
        ++at; /* the newline */
        line[used] = '\0';
        parse_line(list, line);
    }
    return list->count;
}

size_t net_server_list_format(const NetServerList *list, char *out, size_t capacity)
{
    size_t used = 0;
    unsigned i;
    if (capacity == 0) return 0;
    out[0] = '\0';
    for (i = 0; i < list->count; ++i) {
        const NetServerEntry *entry = &list->entries[i];
        int written;
        if (entry->source != NET_SERVER_SOURCE_RECENT) continue;
        written = snprintf(out + used, capacity - used, "server %u %llu %s%s%s\n",
                           (unsigned)entry->port, (unsigned long long)entry->last_used,
                           entry->address, entry->label[0] != '\0' ? " " : "",
                           entry->label);
        if (written < 0 || (size_t)written >= capacity - used) {
            out[0] = '\0';
            return 0;
        }
        used += (size_t)written;
    }
    return used;
}
