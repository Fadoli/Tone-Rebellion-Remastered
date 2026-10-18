#include "floater_catalog.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { FLOATER_LINE_CAPACITY = 256, FLOATER_TOKEN_CAPACITY = 32 };

static void set_error(char *error, size_t capacity, const char *message,
                      size_t line_number)
{
    if (error == NULL || capacity == 0) return;
    if (line_number == 0)
        (void)snprintf(error, capacity, "%s", message);
    else
        (void)snprintf(error, capacity, "line %lu: %s", (unsigned long)line_number,
                       message);
    error[capacity - 1] = '\0';
}

static int next_record(const unsigned char *bytes, size_t length,
                       size_t *position, size_t *line_number,
                       char line[FLOATER_LINE_CAPACITY])
{
    while (*position < length) {
        size_t start = *position;
        size_t line_length;
        char *comment;
        char *begin;
        char *end;

        while (*position < length && bytes[*position] != '\n' &&
               bytes[*position] != 0x1a) ++*position;
        line_length = *position - start;
        if (*position < length && bytes[*position] == '\n') ++*position;
        else if (*position < length && bytes[*position] == 0x1a) *position = length;
        ++*line_number;
        if (line_length != 0 && bytes[start + line_length - 1] == '\r') --line_length;
        if (line_length >= FLOATER_LINE_CAPACITY) return -1;
        memcpy(line, bytes + start, line_length);
        line[line_length] = '\0';
        comment = strchr(line, ';');
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
    while (**cursor == ' ' || **cursor == '\t' || **cursor == '\v' || **cursor == '\f')
        ++*cursor;
    if (**cursor == '\0') return 0;
    start = *cursor;
    while (**cursor != '\0' && **cursor != ' ' && **cursor != '\t' &&
           **cursor != '\v' && **cursor != '\f') ++*cursor;
    length = (size_t)(*cursor - start);
    if (length == 0 || length >= capacity) return -1;
    memcpy(token, start, length);
    token[length] = '\0';
    return 1;
}

static int parse_short(const char *token, int16_t *value)
{
    char *end;
    long parsed;
    if (token == NULL || *token == '\0') return 0;
    parsed = strtol(token, &end, 10);
    if (end == token || *end != '\0' || parsed < INT16_MIN || parsed > INT16_MAX)
        return 0;
    *value = (int16_t)parsed;
    return 1;
}

static int parse_row(const char *line, FloaterStats *row)
{
    char token[FLOATER_TOKEN_CAPACITY];
    const char *cursor = line;
    int16_t *values[] = { &row->attack_range, &row->attack_realm,
        &row->hit_points, &row->max_attack_points, &row->attack_strength,
        &row->movement_speed };
    unsigned int i;
    int status = next_token(&cursor, token, sizeof(token));
    if (status != 1) return 0;
    for (i = 0; i < sizeof(values) / sizeof(values[0]); ++i) {
        status = next_token(&cursor, token, sizeof(token));
        if (status != 1 || !parse_short(token, values[i])) return 0;
    }
    return next_token(&cursor, token, sizeof(token)) == 0;
}

int floater_catalog_load(const unsigned char *bytes, size_t length,
                         FloaterCatalog *out, char *error,
                         size_t error_capacity)
{
    FloaterCatalog parsed;
    size_t position = 0;
    size_t line_number = 0;
    unsigned int row_count = 0;
    char line[FLOATER_LINE_CAPACITY];
    int status;

    if (error != NULL && error_capacity != 0) error[0] = '\0';
    if (bytes == NULL || out == NULL) {
        set_error(error, error_capacity, "input bytes and output are required", 0);
        return 0;
    }
    memset(&parsed, 0, sizeof(parsed));
    while ((status = next_record(bytes, length, &position, &line_number, line)) > 0) {
        if (row_count >= FLOATER_CATALOG_ROW_COUNT ||
            !parse_row(line, &parsed.rows[row_count])) {
            set_error(error, error_capacity, "invalid floater stats row", line_number);
            return 0;
        }
        ++row_count;
    }
    if (status < 0) {
        set_error(error, error_capacity, "floater stats line is too long", line_number);
        return 0;
    }
    if (row_count != FLOATER_CATALOG_ROW_COUNT) {
        set_error(error, error_capacity, "expected exactly 45 floater stats rows", 0);
        return 0;
    }
    *out = parsed;
    return 1;
}

const FloaterStats *floater_catalog_find(const FloaterCatalog *catalog,
                                        int type_index, int subtype)
{
    int row_index;
    if (catalog == NULL || type_index < 0 || type_index > 4 || subtype < 0)
        return NULL;
    if (type_index == 4) {
        if (subtype > 17) return NULL;
        row_index = subtype + 27;
    } else {
        if (subtype > 8) return NULL;
        row_index = type_index * 9 + subtype;
    }
    return &catalog->rows[row_index];
}
