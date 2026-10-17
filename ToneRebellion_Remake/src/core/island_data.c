#include "island_data.h"

#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { ISLAND_LINE_CAPACITY = 256 };

static void set_error(char *error, size_t capacity, const char *message,
                      size_t line_number)
{
    if (error == NULL || capacity == 0) return;
    if (line_number == 0) {
        (void)snprintf(error, capacity, "%s", message);
    } else {
        (void)snprintf(error, capacity, "line %lu: %s", (unsigned long)line_number, message);
    }
    error[capacity - 1] = '\0';
}

static int next_line(const unsigned char *bytes, size_t length, size_t *position,
                     size_t *line_number, char line[ISLAND_LINE_CAPACITY])
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
        if (line_length >= ISLAND_LINE_CAPACITY) return -1;
        memcpy(line, bytes + start, line_length);
        line[line_length] = '\0';

        comment = strchr(line, ';');
        slash_comment = strstr(line, "//");
        if (comment == NULL || (slash_comment != NULL && slash_comment < comment)) {
            comment = slash_comment;
        }
        if (comment != NULL) *comment = '\0';
        begin = line;
        while (isspace((unsigned char)*begin)) ++begin;
        end = begin + strlen(begin);
        while (end > begin && isspace((unsigned char)end[-1])) --end;
        *end = '\0';
        if (begin != line) memmove(line, begin, (size_t)(end - begin) + 1);
        if (line[0] != '\0') return 1;
    }
    return 0;
}

static int parse_nonnegative(const char *text, long minimum, long maximum, long *value)
{
    char *end;
    long parsed;
    if (text == NULL || *text == '\0') return 0;
    parsed = strtol(text, &end, 10);
    if (end == text || *end != '\0' || parsed < minimum || parsed > maximum) return 0;
    *value = parsed;
    return 1;
}

int island_data_load(const unsigned char *bytes, size_t length, IslandData *out,
                     char *error, size_t error_capacity)
{
    IslandData parsed;
    size_t position = 0;
    size_t line_number = 0;
    char line[ISLAND_LINE_CAPACITY];
    char *cursor;
    long expected_count;
    int line_status;

    if (error != NULL && error_capacity != 0) error[0] = '\0';
    if (bytes == NULL || out == NULL) {
        set_error(error, error_capacity, "input bytes and output are required", 0);
        return 0;
    }
    memset(&parsed, 0, sizeof(parsed));

    line_status = next_line(bytes, length, &position, &line_number, line);
    if (line_status != 1 || strncmp(line, "NUM_LOCATIONS", 13) != 0 ||
        (line[13] != '\0' && !isspace((unsigned char)line[13]))) {
        set_error(error, error_capacity, "expected NUM_LOCATIONS header", line_number);
        return 0;
    }
    cursor = line + 13;
    while (isspace((unsigned char)*cursor)) ++cursor;
    if (*cursor == '\0' || !parse_nonnegative(cursor, 1, ISLAND_DATA_MAX_LOCATIONS,
                                               &expected_count)) {
        set_error(error, error_capacity, "invalid location count", line_number);
        return 0;
    }

    while ((line_status = next_line(bytes, length, &position, &line_number, line)) == 1) {
        long id;
        long x;
        long y;
        long special_value;
        char type[ISLAND_LOCATION_TYPE_CAPACITY];
        char extra;
        int fields;
        IslandLocation *location;

        if (parsed.location_count >= expected_count) {
            set_error(error, error_capacity, "more rows than NUM_LOCATIONS declares", line_number);
            return 0;
        }
        fields = sscanf(line, "%ld %ld %ld %15s %ld %c",
                        &id, &x, &y, type, &special_value, &extra);
        if (fields != 5 || id != parsed.location_count || x < 0 || x > 2559 ||
            y < 0 || y > 319 || special_value < INT32_MIN || special_value > INT32_MAX) {
            set_error(error, error_capacity, "invalid location row", line_number);
            return 0;
        }
        location = &parsed.locations[parsed.location_count];
        location->id = (uint16_t)id;
        location->x = (uint16_t)x;
        location->y = (uint16_t)y;
        location->special_value = (int32_t)special_value;
        memcpy(location->type, type, strlen(type) + 1);
        ++parsed.location_count;
    }
    if (line_status < 0) {
        set_error(error, error_capacity, "line exceeds parser capacity", line_number);
        return 0;
    }
    if (parsed.location_count != expected_count) {
        set_error(error, error_capacity, "location count does not match NUM_LOCATIONS", line_number);
        return 0;
    }
    *out = parsed;
    return 1;
}
