#include "pad_catalog.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { PAD_CATALOG_LINE_CAPACITY = 256 };

static void set_error(char *error, size_t capacity, const char *message, size_t line)
{
    if (error == NULL || capacity == 0) return;
    if (line == 0) {
        (void)snprintf(error, capacity, "%s", message);
    } else {
        (void)snprintf(error, capacity, "line %lu: %s", (unsigned long)line, message);
    }
    error[capacity - 1] = '\0';
}

static int next_line(const unsigned char *bytes, size_t length, size_t *position,
                     size_t *line_number, char line[PAD_CATALOG_LINE_CAPACITY])
{
    while (*position < length) {
        size_t start = *position;
        size_t line_length;
        char *comment;
        char *slash_comment;
        char *begin;
        char *end;

        while (*position < length && bytes[*position] != '\n' && bytes[*position] != 0x1a) {
            ++*position;
        }
        line_length = *position - start;
        if (*position < length && bytes[*position] == '\n') ++*position;
        else if (*position < length && bytes[*position] == 0x1a) *position = length;
        ++*line_number;
        if (line_length != 0 && bytes[start + line_length - 1] == '\r') --line_length;
        if (line_length >= PAD_CATALOG_LINE_CAPACITY) return -1;
        memcpy(line, bytes + start, line_length);
        line[line_length] = '\0';

        comment = strchr(line, ';');
        slash_comment = strstr(line, "//");
        if (comment == NULL || (slash_comment != NULL && slash_comment < comment)) {
            comment = slash_comment;
        }
        if (comment != NULL) *comment = '\0';
        begin = line;
        while (*begin == ' ' || *begin == '\t' || *begin == '\v' || *begin == '\f') ++begin;
        end = begin + strlen(begin);
        while (end > begin && (end[-1] == ' ' || end[-1] == '\t' ||
                               end[-1] == '\v' || end[-1] == '\f')) --end;
        *end = '\0';
        if (begin != line) memmove(line, begin, (size_t)(end - begin) + 1);
        if (line[0] != '\0') return 1;
    }
    return 0;
}

static int next_token(const char **cursor, char *token, size_t capacity)
{
    const char *start;
    size_t length;

    while (**cursor == ' ' || **cursor == '\t' || **cursor == '\v' || **cursor == '\f') {
        ++*cursor;
    }
    if (**cursor == '\0') return 0;
    start = *cursor;
    while (**cursor != '\0' && **cursor != ' ' && **cursor != '\t' &&
           **cursor != '\v' && **cursor != '\f') {
        ++*cursor;
    }
    length = (size_t)(*cursor - start);
    if (length == 0 || length >= capacity) return -1;
    memcpy(token, start, length);
    token[length] = '\0';
    return 1;
}

static int parse_integer_token(const char *token, long minimum, long maximum, long *value)
{
    char *end;
    long parsed;

    if (token == NULL || *token == '\0') return 0;
    parsed = strtol(token, &end, 10);
    if (end == token || *end != '\0' || parsed < minimum || parsed > maximum) return 0;
    *value = parsed;
    return 1;
}

static int parse_movement_costs(const char *token, int16_t costs[3])
{
    const char *cursor = token;
    unsigned i;

    for (i = 0; i < 3; ++i) {
        char *end;
        long value = strtol(cursor, &end, 10);
        if (end == cursor || value < INT16_MIN || value > INT16_MAX) return 0;
        costs[i] = (int16_t)value;
        if (i < 2) {
            if (*end != ',') return 0;
            cursor = end + 1;
        } else if (*end != '\0') {
            return 0;
        }
    }
    return 1;
}

static int parse_tribe(const char *token, PadTribe *tribe)
{
    if (strcmp(token, "None") == 0) *tribe = PAD_TRIBE_NONE;
    else if (strcmp(token, "Levi") == 0) *tribe = PAD_TRIBE_LEVIATHAN;
    else if (strcmp(token, "Prot") == 0) *tribe = PAD_TRIBE_PROTECTOR;
    else if (strcmp(token, "Seek") == 0) *tribe = PAD_TRIBE_SEEKER;
    else if (strcmp(token, "Myst") == 0) *tribe = PAD_TRIBE_MYSTIC;
    else if (strcmp(token, "Life") == 0) *tribe = PAD_TRIBE_LIFEGIVER;
    else return 0;
    return 1;
}

static int parse_record(const char *line, uint16_t item_id, PadCatalogItem *item)
{
    char token[PAD_CATALOG_TEXT_CAPACITY];
    const char *cursor = line;
    long fields[5];
    unsigned i;
    int status;

    memset(item, 0, sizeof(*item));
    item->item_id = item_id;
    for (i = 0; i < 2; ++i) {
        status = next_token(&cursor, token, sizeof(token));
        if (status != 1 || !parse_integer_token(token, i == 0 ? 0 : -1,
                                                i == 0 ? 2 : INT16_MAX, &fields[i])) return 0;
    }
    item->size = (int8_t)fields[0];
    item->building_tone_cost = (int16_t)fields[1];

    status = next_token(&cursor, token, sizeof(token));
    if (status != 1 || !parse_movement_costs(token, item->movement_cost)) return 0;
    for (i = 2; i < 5; ++i) {
        status = next_token(&cursor, token, sizeof(token));
        if (status != 1 || !parse_integer_token(token, 0, INT16_MAX, &fields[i])) return 0;
    }
    item->maintenance_tone_cost = (int16_t)fields[2];
    item->hit_points = (int16_t)fields[3];
    item->tone_range_extension = (int16_t)fields[4];
    status = next_token(&cursor, token, sizeof(token));
    if (status != 1 || !parse_tribe(token, &item->tribe)) return 0;
    status = next_token(&cursor, token, sizeof(token));
    if (status != 1) return 0;
    (void)strcpy(item->shape_id, token);

    status = next_token(&cursor, token, sizeof(token));
    if (status < 0) return 0;
    if (status == 1) {
        (void)strcpy(item->text_id, token);
        if (next_token(&cursor, token, sizeof(token)) != 0) return 0;
    }
    return 1;
}

int pad_catalog_load(const unsigned char *bytes, size_t length, PadCatalog *out,
                     char *error, size_t error_capacity)
{
    PadCatalog parsed;
    size_t position = 0;
    size_t line_number = 0;
    char line[PAD_CATALOG_LINE_CAPACITY];
    int line_status;

    if (error != NULL && error_capacity != 0) error[0] = '\0';
    if (bytes == NULL || out == NULL) {
        set_error(error, error_capacity, "input bytes and output are required", 0);
        return 0;
    }
    memset(&parsed, 0, sizeof(parsed));
    while ((line_status = next_line(bytes, length, &position, &line_number, line)) > 0) {
        if (parsed.item_count >= PAD_CATALOG_MAX_ITEMS) {
            set_error(error, error_capacity, "too many pad catalog records", line_number);
            return 0;
        }
        if (!parse_record(line, parsed.item_count, &parsed.items[parsed.item_count])) {
            set_error(error, error_capacity, "invalid pad catalog record", line_number);
            return 0;
        }
        ++parsed.item_count;
    }
    if (line_status < 0) {
        set_error(error, error_capacity, "pad catalog line is too long", line_number);
        return 0;
    }
    if (parsed.item_count == 0) {
        set_error(error, error_capacity, "pad catalog contains no records", 0);
        return 0;
    }
    *out = parsed;
    return 1;
}

const PadCatalogItem *pad_catalog_find(const PadCatalog *catalog, uint16_t item_id)
{
    if (catalog == NULL || item_id >= catalog->item_count) return NULL;
    return &catalog->items[item_id];
}

size_t pad_catalog_tribe_item_count(const PadCatalog *catalog, PadTribe tribe)
{
    size_t i;
    size_t count = 0;
    if (catalog == NULL) return 0;
    for (i = 0; i < catalog->item_count; ++i) {
        if (catalog->items[i].tribe == tribe) ++count;
    }
    return count;
}

const PadCatalogItem *pad_catalog_tribe_item_at(const PadCatalog *catalog,
                                               PadTribe tribe, size_t ordinal)
{
    size_t i;
    if (catalog == NULL) return NULL;
    for (i = 0; i < catalog->item_count; ++i) {
        if (catalog->items[i].tribe == tribe) {
            if (ordinal == 0) return &catalog->items[i];
            --ordinal;
        }
    }
    return NULL;
}

size_t pad_catalog_count_for(const PadCatalog *catalog, PadTribe tribe, int size)
{
    size_t i;
    size_t count = 0;
    if (catalog == NULL || size < 0 || size > 2) return 0;
    for (i = 0; i < catalog->item_count; ++i) {
        const PadCatalogItem *item = &catalog->items[i];
        if (item->tribe == tribe && item->size == size &&
            item->building_tone_cost >= 0 && strcmp(item->shape_id, "noshape") != 0) {
            ++count;
        }
    }
    return count;
}

const PadCatalogItem *pad_catalog_nth_for(const PadCatalog *catalog, PadTribe tribe,
                                          int size, size_t ordinal)
{
    size_t i;
    if (catalog == NULL || size < 0 || size > 2) return NULL;
    for (i = 0; i < catalog->item_count; ++i) {
        const PadCatalogItem *item = &catalog->items[i];
        if (item->tribe == tribe && item->size == size &&
            item->building_tone_cost >= 0 && strcmp(item->shape_id, "noshape") != 0) {
            if (ordinal == 0) return item;
            --ordinal;
        }
    }
    return NULL;
}
