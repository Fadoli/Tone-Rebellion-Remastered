#include "floater_catalog.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { EFFECT_LINE_CAPACITY = 256, EFFECT_NAME_CAPACITY = 32 };

static void set_error(char *error, size_t capacity, const char *message,
                      size_t line_number)
{
    if (error == NULL || capacity == 0) return;
    if (line_number == 0) {
        (void)snprintf(error, capacity, "%s", message);
    } else {
        (void)snprintf(error, capacity, "line %lu: %s",
                       (unsigned long)line_number, message);
    }
    error[capacity - 1] = '\0';
}

static char *skip_space(char *text)
{
    while (*text == ' ' || *text == '\t' || *text == '\r') ++text;
    return text;
}

static int impact_effect_index(const char *name)
{
    static const char *const names[FLOATER_IMPACT_REALM_COUNT] = {
        "PHYIMP", "SUPIMP", "ETHIMP", "NATIMP"
    };
    unsigned int i;
    for (i = 0; i < FLOATER_IMPACT_REALM_COUNT; ++i) {
        if (strcmp(name, names[i]) == 0) return (int)i;
    }
    return -1;
}

static int parse_impact_frames(char *text,
                               uint8_t frames[FLOATER_IMPACT_LEVEL_COUNT])
{
    char *cursor = skip_space(text);
    char *end;
    long level_count = strtol(cursor, &end, 10);
    unsigned int i;

    if (end == cursor || level_count != FLOATER_IMPACT_LEVEL_COUNT) return 0;
    cursor = end;
    for (i = 0; i < FLOATER_IMPACT_LEVEL_COUNT; ++i) {
        long first;
        long last;
        cursor = skip_space(cursor);
        first = strtol(cursor, &end, 10);
        if (end == cursor || *end != ',') return 0;
        cursor = end + 1;
        last = strtol(cursor, &end, 10);
        if (end == cursor || first < 1 || last < first ||
            last - first + 1 > (long)UINT8_MAX) return 0;
        frames[i] = (uint8_t)(last - first + 1);
        cursor = end;
    }
    return *skip_space(cursor) == '\0';
}

int floater_catalog_load_impact_effects(const unsigned char *bytes,
                                        size_t length,
                                        FloaterCatalog *catalog,
                                        char *error,
                                        size_t error_capacity)
{
    uint8_t parsed[FLOATER_IMPACT_REALM_COUNT][FLOATER_IMPACT_LEVEL_COUNT] = {{0}};
    uint8_t seen_effects = 0;
    uint8_t seen_types = 0;
    uint8_t seen_realms = 0;
    uint8_t seen_frames = 0;
    int current_effect = -1;
    size_t position = 0;
    size_t line_number = 0;

    if (error != NULL && error_capacity != 0) error[0] = '\0';
    if (bytes == NULL || catalog == NULL) {
        set_error(error, error_capacity, "invalid effect catalog arguments", 0);
        return 0;
    }
    while (position < length) {
        char line[EFFECT_LINE_CAPACITY];
        size_t start = position;
        size_t line_length;
        char key[EFFECT_NAME_CAPACITY];
        char value[EFFECT_NAME_CAPACITY];
        char *comment;
        char *content;
        char *argument;

        while (position < length && bytes[position] != '\n' &&
               bytes[position] != 0x1a) ++position;
        line_length = position - start;
        if (position < length && bytes[position] == '\n') ++position;
        else if (position < length && bytes[position] == 0x1a) position = length;
        ++line_number;
        if (line_length >= sizeof(line)) {
            set_error(error, error_capacity, "line is too long", line_number);
            return 0;
        }
        memcpy(line, bytes + start, line_length);
        line[line_length] = '\0';
        comment = strstr(line, "//");
        if (comment != NULL) *comment = '\0';
        content = skip_space(line);
        if (*content == '\0' || sscanf(content, "%31s %31s", key, value) != 2)
            continue;
        argument = content;
        while (*argument != '\0' && *argument != ' ' && *argument != '\t') ++argument;
        argument = skip_space(argument);

        if (strcmp(key, "EFFECT") == 0) {
            current_effect = impact_effect_index(value);
            if (current_effect >= 0) {
                uint8_t bit = (uint8_t)(1U << current_effect);
                if (seen_effects & bit) {
                    set_error(error, error_capacity, "duplicate impact effect",
                              line_number);
                    return 0;
                }
                seen_effects |= bit;
            }
        } else if (current_effect >= 0 && strcmp(key, "TYPE") == 0) {
            uint8_t bit = (uint8_t)(1U << current_effect);
            if (strcmp(value, "IMPACT") != 0 || (seen_types & bit)) {
                set_error(error, error_capacity, "expected one IMPACT type",
                          line_number);
                return 0;
            }
            seen_types |= bit;
        } else if (current_effect >= 0 && strcmp(key, "REALM") == 0) {
            static const char *const realms[FLOATER_IMPACT_REALM_COUNT] = {
                "PHY", "SUP", "ETH", "NAT"
            };
            uint8_t bit = (uint8_t)(1U << current_effect);
            if (strcmp(value, realms[current_effect]) != 0 || (seen_realms & bit)) {
                set_error(error, error_capacity, "impact effect realm mismatch",
                          line_number);
                return 0;
            }
            seen_realms |= bit;
        } else if (current_effect >= 0 && strcmp(key, "LEVELFRAMES") == 0) {
            uint8_t bit = (uint8_t)(1U << current_effect);
            if ((seen_frames & bit) ||
                !parse_impact_frames(argument, parsed[current_effect])) {
                set_error(error, error_capacity, "invalid impact LEVELFRAMES",
                          line_number);
                return 0;
            }
            seen_frames |= bit;
        }
    }

    if (seen_effects != 0x0fU || seen_types != 0x0fU ||
        seen_realms != 0x0fU || seen_frames != 0x0fU) {
        set_error(error, error_capacity, "effects.txt is missing an impact record", 0);
        return 0;
    }
    memcpy(catalog->impact_frame_counts, parsed, sizeof(parsed));
    return 1;
}
