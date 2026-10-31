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

static int parse_impact_frames(
    char *text,
    uint8_t starts[FLOATER_IMPACT_LEVEL_COUNT],
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
            last - 1 > (long)UINT8_MAX ||
            last - first + 1 > (long)UINT8_MAX) return 0;
        starts[i] = (uint8_t)(first - 1);
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
    uint8_t parsed_starts[FLOATER_IMPACT_REALM_COUNT]
                         [FLOATER_IMPACT_LEVEL_COUNT] = {{0}};
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
                !parse_impact_frames(argument, parsed_starts[current_effect],
                                     parsed[current_effect])) {
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
    memcpy(catalog->impact_frame_starts, parsed_starts,
           sizeof(parsed_starts));
    return 1;
}

static int effect_name_equal(const char *a, const char *b)
{
    while (*a != '\0' && *b != '\0') {
        char ca = *a;
        char cb = *b;
        if (ca >= 'a' && ca <= 'z') ca = (char)(ca - 'a' + 'A');
        if (cb >= 'a' && cb <= 'z') cb = (char)(cb - 'a' + 'A');
        if (ca != cb) return 0;
        ++a;
        ++b;
    }
    return *a == *b;
}

static int effect_type_from_name(const char *name)
{
    static const char *const names[7] = {
        "ONESHOT", "BULLET", "LIGHTNING", "IMPACT", "CAST", "SPECIAL",
        "SOUNDONLY"
    };
    unsigned int i;
    for (i = 0; i < 7; ++i)
        if (effect_name_equal(name, names[i])) return (int)i;
    return FLOATER_EFFECT_SOUNDONLY;
}

/* "<levels> a,b c,d ..." with 1-based inclusive frame ranges. */
static int parse_effect_levels(char *text, FloaterEffectDef *def)
{
    char *cursor = skip_space(text);
    char *end;
    long levels = strtol(cursor, &end, 10);
    long i;
    if (end == cursor || levels < 1 || levels > FLOATER_IMPACT_LEVEL_COUNT)
        return 0;
    cursor = end;
    for (i = 0; i < levels; ++i) {
        long first;
        long last;
        cursor = skip_space(cursor);
        first = strtol(cursor, &end, 10);
        if (end == cursor || *end != ',') return 0;
        cursor = end + 1;
        last = strtol(cursor, &end, 10);
        if (end == cursor || first < 1 || last < first || last > 255) return 0;
        def->level_start[i] = (uint8_t)(first - 1);
        def->level_frames[i] = (uint8_t)(last - first + 1);
        cursor = end;
    }
    def->level_count = (uint8_t)levels;
    return 1;
}

static int find_effect(const FloaterCatalog *catalog, const char *name)
{
    unsigned int i;
    for (i = 0; i < catalog->effect_count; ++i)
        if (effect_name_equal(catalog->effects[i].name, name)) return (int)i;
    return -1;
}

int floater_catalog_load_effect_defs(const unsigned char *bytes, size_t length,
                                     FloaterCatalog *catalog, char *error,
                                     size_t error_capacity)
{
    char chain_names[FLOATER_EFFECT_MAX][FLOATER_EFFECT_NAME_CAPACITY];
    FloaterEffectDef *current = NULL;
    size_t position = 0;
    size_t line_number = 0;
    unsigned int index;

    if (error != NULL && error_capacity != 0) error[0] = '\0';
    if (bytes == NULL || catalog == NULL) {
        set_error(error, error_capacity, "invalid effect catalog arguments", 0);
        return 0;
    }
    memset(catalog->effects, 0, sizeof(catalog->effects));
    memset(chain_names, 0, sizeof(chain_names));
    catalog->effect_count = 0;
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
        if (*content == '\0' || *content == ';' ||
            sscanf(content, "%31s %31s", key, value) != 2) continue;
        argument = content;
        while (*argument != '\0' && *argument != ' ' && *argument != '\t') ++argument;
        argument = skip_space(argument);

        if (strcmp(key, "EFFECT") == 0) {
            if (catalog->effect_count >= FLOATER_EFFECT_MAX ||
                strlen(value) >= FLOATER_EFFECT_NAME_CAPACITY) {
                set_error(error, error_capacity, "too many or too long effects",
                          line_number);
                return 0;
            }
            current = &catalog->effects[catalog->effect_count++];
            memcpy(current->name, value, strlen(value) + 1);
            current->type = FLOATER_EFFECT_SOUNDONLY;
            current->speed = 5; /* FUN_004153b8 default */
            current->chain = -1;
        } else if (current == NULL) {
            continue;
        } else if (strcmp(key, "TYPE") == 0) {
            current->type = (uint8_t)effect_type_from_name(value);
        } else if (strcmp(key, "SHAPE") == 0) {
            if (strlen(value) >= FLOATER_EFFECT_NAME_CAPACITY) {
                set_error(error, error_capacity, "shape name too long", line_number);
                return 0;
            }
            memcpy(current->shape, value, strlen(value) + 1);
        } else if (strcmp(key, "SPEED") == 0) {
            current->speed = (int16_t)atoi(value);
        } else if (strcmp(key, "CHAIN") == 0) {
            memcpy(chain_names[current - catalog->effects], value,
                   strlen(value) + 1);
        } else if (strcmp(key, "LEVELFRAMES") == 0) {
            if (!parse_effect_levels(argument, current)) {
                set_error(error, error_capacity, "invalid LEVELFRAMES", line_number);
                return 0;
            }
        }
    }
    for (index = 0; index < catalog->effect_count; ++index) {
        if (chain_names[index][0] != '\0')
            catalog->effects[index].chain =
                (int16_t)find_effect(catalog, chain_names[index]);
    }
    for (index = 0; index < FLOATER_CATALOG_ROW_COUNT; ++index) {
        FloaterStats *row = &catalog->rows[index];
        row->attack_effect_def = row->attack_effect_name[0] != '\0'
            ? (int16_t)find_effect(catalog, row->attack_effect_name) : -1;
    }
    return 1;
}
