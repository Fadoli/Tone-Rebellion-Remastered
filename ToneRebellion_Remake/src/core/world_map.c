#include "world_map.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { WORLD_MAP_LINE_CAPACITY = 512 };

typedef struct LineReader {
    FILE *file;
    const unsigned char *data;
    size_t data_length;
    size_t data_position;
    size_t line_number;
    char buffer[WORLD_MAP_LINE_CAPACITY];
} LineReader;

static void set_error(char *error, size_t capacity, const char *message,
                      size_t line_number)
{
    if (error == NULL || capacity == 0) {
        return;
    }
    if (line_number == 0) {
        (void)snprintf(error, capacity, "%s", message);
    } else {
        (void)snprintf(error, capacity, "line %lu: %s", (unsigned long)line_number, message);
    }
    error[capacity - 1] = '\0';
}

static char *next_data_line(LineReader *reader)
{
    for (;;) {
        size_t length;
        char *comment;
        char *slash_comment;
        char *cursor;

        if (reader->file != NULL) {
            if (fgets(reader->buffer, sizeof(reader->buffer), reader->file) == NULL) {
                return NULL;
            }
            length = strlen(reader->buffer);
            if (length > 0 && reader->buffer[length - 1] != '\n' && !feof(reader->file)) {
                int ch;
                while ((ch = fgetc(reader->file)) != '\n' && ch != EOF) {
                }
                reader->line_number++;
                return NULL;
            }
        } else {
            size_t start = reader->data_position;
            while (reader->data_position < reader->data_length &&
                   reader->data[reader->data_position] != '\n') {
                reader->data_position++;
            }
            length = reader->data_position - start;
            if (reader->data_position < reader->data_length) {
                reader->data_position++;
            }
            if (length == 0 && start == reader->data_length) {
                return NULL;
            }
            if (length >= sizeof(reader->buffer)) {
                reader->line_number++;
                return NULL;
            }
            memcpy(reader->buffer, reader->data + start, length);
            reader->buffer[length] = '\0';
        }

        reader->line_number++;
        length = strlen(reader->buffer);

        comment = strchr(reader->buffer, ';');
        slash_comment = strstr(reader->buffer, "//");
        if (comment == NULL || (slash_comment != NULL && slash_comment < comment)) {
            comment = slash_comment;
        }
        if (comment != NULL) {
            *comment = '\0';
        }

        /* The shipped text files use DOS EOF (0x1a); ignore it as whitespace. */
        for (cursor = reader->buffer; *cursor != '\0'; ++cursor) {
            if ((unsigned char)*cursor == 0x1a) {
                *cursor = ' ';
            }
            if (*cursor == ',') {
                *cursor = ' ';
            }
        }
        cursor = reader->buffer;
        while (*cursor == ' ' || *cursor == '\t' || *cursor == '\r' || *cursor == '\n') {
            ++cursor;
        }
        if (*cursor != '\0') {
            return cursor;
        }
    }
    return NULL;
}

static int parse_integer(char **cursor, int32_t *value)
{
    char *end;
    long parsed;

    while (**cursor == ' ' || **cursor == '\t' || **cursor == '\r' || **cursor == '\n') {
        ++*cursor;
    }
    if (**cursor == '\0') {
        return 0;
    }
    errno = 0;
    parsed = strtol(*cursor, &end, 10);
    if (end == *cursor || errno == ERANGE || parsed < INT32_MIN || parsed > INT32_MAX) {
        return 0;
    }
    *cursor = end;
    *value = (int32_t)parsed;
    return 1;
}

static int only_whitespace_remains(const char *cursor)
{
    while (*cursor == ' ' || *cursor == '\t' || *cursor == '\r' || *cursor == '\n') {
        ++cursor;
    }
    return *cursor == '\0';
}

static int parse_exact_integers(char *line, int32_t *values, size_t count)
{
    char *cursor = line;
    size_t i;

    for (i = 0; i < count; ++i) {
        if (!parse_integer(&cursor, &values[i])) {
            return 0;
        }
    }
    return only_whitespace_remains(cursor);
}

static int parse_world_map(LineReader *reader, WorldMap *out,
                           char *error, size_t error_capacity)
{
    WorldMap parsed;
    char *line;
    int32_t values[4];
    size_t world_index;

    memset(&parsed, 0, sizeof(parsed));

    line = next_data_line(reader);
    if (line == NULL || !parse_exact_integers(line, values, 1) ||
        values[0] < 1 || values[0] > WORLD_MAP_MAX_WORLDS) {
        set_error(error, error_capacity, "invalid world count", reader->line_number);
        return 0;
    }
    parsed.world_count = (uint8_t)values[0];

    for (world_index = 0; world_index < parsed.world_count; ++world_index) {
        WorldDefinition *world = &parsed.worlds[world_index];
        size_t island_index;

        line = next_data_line(reader);
        if (line == NULL || !parse_exact_integers(line, values, 1) ||
            values[0] < 1 || values[0] > WORLD_MAP_MAX_ISLANDS) {
            set_error(error, error_capacity, "invalid island count", reader->line_number);
            return 0;
        }
        world->island_count = (uint8_t)values[0];

        for (island_index = 0; island_index < world->island_count; ++island_index) {
            WorldIsland *island = &world->islands[island_index];
            line = next_data_line(reader);
            if (line == NULL || !parse_exact_integers(line, values, 4)) {
                set_error(error, error_capacity, "invalid island row; expected 4 integers",
                          reader->line_number);
                return 0;
            }
            island->angle_degrees = values[0];
            island->range = values[1];
            island->z = values[2];
            island->shape_id = values[3];
        }

        for (;;) {
            line = next_data_line(reader);
            if (line == NULL) {
                set_error(error, error_capacity, "missing world link terminator", reader->line_number);
                return 0;
            }
            if (!parse_exact_integers(line, values, 1)) {
                int32_t pair[2];
                if (!parse_exact_integers(line, pair, 2)) {
                    set_error(error, error_capacity, "invalid bridge row; expected pair or -1",
                              reader->line_number);
                    return 0;
                }
                if (world->bridge_count >= WORLD_MAP_MAX_BRIDGES || pair[0] < 0 || pair[1] < 0 ||
                    pair[0] >= world->island_count || pair[1] >= world->island_count ||
                    pair[0] == pair[1]) {
                    set_error(error, error_capacity, "bridge index or count is out of range",
                              reader->line_number);
                    return 0;
                }
                world->bridges[world->bridge_count].island_a = (uint8_t)pair[0];
                world->bridges[world->bridge_count].island_b = (uint8_t)pair[1];
                world->bridge_count++;
                continue;
            }
            if (values[0] != -1) {
                set_error(error, error_capacity, "expected -1 after bridge rows", reader->line_number);
                return 0;
            }
            break;
        }
    }

    if (reader->file != NULL && ferror(reader->file)) {
        set_error(error, error_capacity, "error reading world data", reader->line_number);
        return 0;
    }
    *out = parsed;
    return 1;
}

int world_map_load_file(const char *path, WorldMap *out,
                        char *error, size_t error_capacity)
{
    FILE *file;
    LineReader reader;
    int result;
    if (error != NULL && error_capacity > 0) {
        error[0] = '\0';
    }
    if (path == NULL || out == NULL) {
        set_error(error, error_capacity, "path and output are required", 0);
        return 0;
    }
    file = fopen(path, "rb");
    if (file == NULL) {
        set_error(error, error_capacity, "could not open world data", 0);
        return 0;
    }
    memset(&reader, 0, sizeof(reader));
    reader.file = file;
    result = parse_world_map(&reader, out, error, error_capacity);
    fclose(file);
    return result;
}

int world_map_load_data(const unsigned char *data, size_t length, WorldMap *out,
                        char *error, size_t error_capacity)
{
    LineReader reader;
    if (error != NULL && error_capacity > 0) {
        error[0] = '\0';
    }
    if (data == NULL || out == NULL) {
        set_error(error, error_capacity, "data and output are required", 0);
        return 0;
    }
    memset(&reader, 0, sizeof(reader));
    reader.data = data;
    reader.data_length = length;
    return parse_world_map(&reader, out, error, error_capacity);
}
