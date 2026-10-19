#include "window_catalog.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { WINDOW_LINE_CAPACITY = 256 };

enum WindowField {
    FIELD_TYPE = 1u << 0,
    FIELD_NAME = 1u << 1,
    FIELD_STATE = 1u << 2,
    FIELD_SHAPE = 1u << 3,
    FIELD_FRAME = 1u << 4,
    FIELD_FOCUS = 1u << 5,
    FIELD_PANE = 1u << 6,
    FIELD_MESSAGE = 1u << 7,
    FIELD_DESTINATION = 1u << 8,
    FIELD_REQUIRED = (1u << 9) - 1u
};

static void set_error(char *error, size_t capacity, const char *message,
                      size_t line)
{
    if (error == NULL || capacity == 0) return;
    if (line == 0) (void)snprintf(error, capacity, "%s", message);
    else (void)snprintf(error, capacity, "line %lu: %s", (unsigned long)line,
                        message);
    error[capacity - 1] = '\0';
}

static int next_line(const unsigned char *bytes, size_t length, size_t *position,
                     size_t *line_number, char line[WINDOW_LINE_CAPACITY])
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
        if (line_length >= WINDOW_LINE_CAPACITY) return -1;
        memcpy(line, bytes + start, line_length);
        line[line_length] = '\0';

        comment = strchr(line, ';');
        if (comment != NULL) *comment = '\0';
        comment = strstr(line, "//");
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

    while (**cursor == ' ' || **cursor == '\t' || **cursor == '\v' || **cursor == '\f') ++*cursor;
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

static int parse_number(const char *token, int32_t *value)
{
    char *end;
    long parsed;
    if (token == NULL || *token == '\0') return 0;
    parsed = strtol(token, &end, 10);
    if (end == token || *end != '\0' || parsed < INT32_MIN || parsed > INT32_MAX) return 0;
    *value = (int32_t)parsed;
    return 1;
}

static int read_numbers(const char *cursor, int32_t *values, size_t count)
{
    char token[32];
    size_t i;
    for (i = 0; i < count; ++i) {
        int result = next_token(&cursor, token, sizeof(token));
        if (result != 1 || !parse_number(token, &values[i])) return 0;
    }
    return next_token(&cursor, token, sizeof(token)) == 0;
}

static int read_numbers_range(const char *cursor, int32_t *values,
                              size_t minimum, size_t maximum, size_t *count)
{
    char token[32];
    size_t parsed = 0;
    int result;
    while ((result = next_token(&cursor, token, sizeof(token))) == 1) {
        if (parsed == maximum || !parse_number(token, &values[parsed])) return 0;
        ++parsed;
    }
    if (result < 0 || parsed < minimum) return 0;
    *count = parsed;
    return 1;
}

static int copy_token(const char *cursor, char *destination, size_t capacity)
{
    char token[WINDOW_CATALOG_VALUE_CAPACITY];
    int result = next_token(&cursor, token, sizeof(token));
    if (result != 1 || next_token(&cursor, (char[2]){0}, 2) != 0) return 0;
    if (strlen(token) >= capacity) return 0;
    memcpy(destination, token, strlen(token) + 1);
    return 1;
}

static int record_complete(uint32_t fields)
{
    return (fields & FIELD_REQUIRED) == FIELD_REQUIRED;
}

static int parse_directive(WindowCatalog *catalog, WindowTemplate *current,
                           uint32_t *fields, char *line, size_t line_number,
                           char *error, size_t error_capacity)
{
    const char *cursor = line;
    char key[32];
    char token[WINDOW_CATALOG_VALUE_CAPACITY];
    int result = next_token(&cursor, key, sizeof(key));
    int32_t numbers[6];

    if (result != 1) return 1;
    if (strcmp(key, "SHAPECACHE_SIZE") == 0) {
        if (!read_numbers(cursor, numbers, 1) || numbers[0] < 0) goto bad_value;
        catalog->shape_cache_size = (uint32_t)numbers[0];
        return 1;
    }
    if (strcmp(key, "WINTYPE") == 0) {
        if (current != NULL && !record_complete(*fields)) {
            set_error(error, error_capacity, "incomplete window record", line_number);
            return 0;
        }
        if (catalog->count >= WINDOW_CATALOG_MAX_WINDOWS) {
            set_error(error, error_capacity, "window record limit exceeded", line_number);
            return 0;
        }
        current = &catalog->windows[catalog->count++];
        memset(current, 0, sizeof(*current));
        current->source_line = (uint16_t)line_number;
        *fields = 0;
        if (!read_numbers(cursor, numbers, 1) || numbers[0] < 0 ||
            numbers[0] > (int32_t)UINT16_MAX) goto bad_value;
        current->type_id = (uint16_t)numbers[0];
        *fields |= FIELD_TYPE;
        return 1;
    }
    if (current == NULL) {
        set_error(error, error_capacity, "directive outside a window record", line_number);
        return 0;
    }
    if (strcmp(key, "NAME") == 0) {
        if (!copy_token(cursor, current->name, sizeof(current->name))) goto bad_value;
        *fields |= FIELD_NAME;
    } else if (strcmp(key, "STATE") == 0) {
        uint8_t count = 0;
        while ((result = next_token(&cursor, token, sizeof(token))) == 1) {
            if (count >= WINDOW_CATALOG_MAX_STATES || !parse_number(token, &current->states[count])) goto bad_value;
            ++count;
        }
        if (result < 0 || count == 0) goto bad_value;
        current->state_count = count;
        *fields |= FIELD_STATE;
    } else if (strcmp(key, "SHAPEID") == 0) {
        if (!copy_token(cursor, current->shape_id, sizeof(current->shape_id))) goto bad_value;
        *fields |= FIELD_SHAPE;
    } else if (strcmp(key, "SHAPEFRAME") == 0) {
        if (!read_numbers(cursor, numbers, 1)) goto bad_value;
        current->shape_frame = numbers[0];
        *fields |= FIELD_FRAME;
    } else if (strcmp(key, "MOUSEFOCUS") == 0) {
        if (!read_numbers(cursor, numbers, 1)) goto bad_value;
        current->mouse_focus = numbers[0];
        *fields |= FIELD_FOCUS;
    } else if (strcmp(key, "PANE") == 0) {
        size_t pane_value_count;
        if (!read_numbers_range(cursor, numbers, 4, 6, &pane_value_count)) goto bad_value;
        current->pane = (WindowPane){numbers[0], numbers[1], numbers[2], numbers[3]};
        if (pane_value_count == 6) {
            current->pane_extras[0] = numbers[4];
            current->pane_extras[1] = numbers[5];
            current->has_pane_extras = 1;
        }
        *fields |= FIELD_PANE;
    } else if (strcmp(key, "OPENPANE") == 0) {
        if (!read_numbers(cursor, numbers, 4)) goto bad_value;
        current->open_pane = (WindowPane){numbers[0], numbers[1], numbers[2], numbers[3]};
        current->has_open_pane = 1;
    } else if (strcmp(key, "SENDMESSAGE") == 0) {
        if (!read_numbers(cursor, numbers, 3)) goto bad_value;
        memcpy(current->send_message, numbers, sizeof(current->send_message));
        *fields |= FIELD_MESSAGE;
    } else if (strcmp(key, "MSGDEST") == 0) {
        if (!copy_token(cursor, current->message_destination, sizeof(current->message_destination))) goto bad_value;
        *fields |= FIELD_DESTINATION;
    } else if (strcmp(key, "CONTREDRAW") == 0) {
        if (!read_numbers(cursor, numbers, 1)) goto bad_value;
        current->continue_redraw = numbers[0];
        current->has_continue_redraw = 1;
    } else if (strcmp(key, "NSTATES") == 0) {
        if (!read_numbers(cursor, numbers, 1)) goto bad_value;
        current->nstates = numbers[0];
        current->has_nstates = 1;
    } else if (strcmp(key, "HILITEFRAME") == 0) {
        if (!read_numbers(cursor, numbers, 1)) goto bad_value;
        current->hilite_frame = numbers[0];
        current->has_hilite_frame = 1;
    } else if (strcmp(key, "MOVIENAME") == 0) {
        if (!copy_token(cursor, current->movie_name, sizeof(current->movie_name))) goto bad_value;
    } else if (strcmp(key, "END") == 0) {
        if (!read_numbers(cursor, numbers, 1)) goto bad_value;
        current->end_value = numbers[0];
        current->has_end_value = 1;
    } else {
        set_error(error, error_capacity, "unsupported windows.txt directive", line_number);
        return 0;
    }
    return 1;

bad_value:
    set_error(error, error_capacity, "invalid directive value", line_number);
    return 0;
}

int window_catalog_load(const unsigned char *bytes, size_t length,
                        WindowCatalog *out, char *error,
                        size_t error_capacity)
{
    WindowCatalog parsed;
    WindowTemplate *current = NULL;
    uint32_t fields = 0;
    size_t position = 0;
    size_t line_number = 0;
    char line[WINDOW_LINE_CAPACITY];
    int result;

    if (bytes == NULL || out == NULL) {
        set_error(error, error_capacity, "invalid argument", 0);
        return 0;
    }
    memset(&parsed, 0, sizeof(parsed));
    while ((result = next_line(bytes, length, &position, &line_number, line)) > 0) {
        if (current == NULL && strncmp(line, "WINTYPE", 7) == 0) {
            /* The parser creates the record when it consumes WINTYPE. */
        }
        if (!parse_directive(&parsed, current, &fields, line, line_number,
                             error, error_capacity)) return 0;
        if (strncmp(line, "WINTYPE", 7) == 0 && parsed.count != 0) current = &parsed.windows[parsed.count - 1];
    }
    if (result < 0) {
        set_error(error, error_capacity, "line exceeds parser capacity", line_number);
        return 0;
    }
    if (current != NULL && !record_complete(fields)) {
        set_error(error, error_capacity, "incomplete final window record", current->source_line);
        return 0;
    }
    if (parsed.count == 0) {
        set_error(error, error_capacity, "no window records found", 0);
        return 0;
    }
    *out = parsed;
    if (error != NULL && error_capacity != 0) error[0] = '\0';
    return 1;
}
