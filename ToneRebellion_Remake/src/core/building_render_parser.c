#include "building_render.h"
#include "building_render_internal.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "building_render.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void building_render_set_error(char *error, size_t capacity, const char *message, size_t line)
{
    if (error == NULL || capacity == 0) return;
    if (line == 0) (void)snprintf(error, capacity, "%s", message);
    else (void)snprintf(error, capacity, "line %lu: %s", (unsigned long)line, message);
    error[capacity - 1] = '\0';
}

int building_render_ascii_case_equal(const char *left, const char *right)
{
    while (*left != '\0' && *right != '\0') {
        if (tolower((unsigned char)*left) != tolower((unsigned char)*right)) return 0;
        ++left;
        ++right;
    }
    return *left == *right;
}

int building_render_next_line(const unsigned char *bytes, size_t length, size_t *position,
                     char line[BUILDING_RENDER_LINE_CAPACITY])
{
    size_t start = *position;
    size_t line_length;
    char *comment;
    char *slash_comment;
    char *begin;
    char *end;
    if (*position >= length) return 0;
    while (*position < length && bytes[*position] != '\n' && bytes[*position] != 0x1a) {
        ++*position;
    }
    line_length = *position - start;
    if (*position < length && bytes[*position] == '\n') ++*position;
    else if (*position < length && bytes[*position] == 0x1a) *position = length;
    if (line_length != 0 && bytes[start + line_length - 1] == '\r') --line_length;
    if (line_length >= BUILDING_RENDER_LINE_CAPACITY) return -1;
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
    return line[0] == '\0' ? 2 : 1;
}

static BuildingRenderItem *find_mutable(BuildingRenderCatalog *catalog, uint16_t item_id)
{
    BuildingRenderItem *item;
    if (item_id >= catalog->item_count) return NULL;
    item = &catalog->items[item_id];
    item->item_id = item_id;
    return item;
}

BuildingRenderItem *building_render_find_item_name(BuildingRenderCatalog *catalog,
                                          const PadCatalog *pads, const char *name)
{
    uint16_t item_id;
    for (item_id = 0; item_id < pads->item_count; ++item_id) {
        const PadCatalogItem *pad = &pads->items[item_id];
        if (building_render_ascii_case_equal(pad->shape_id, "noshape")) continue;
        if (building_render_ascii_case_equal(pad->shape_id, name)) return find_mutable(catalog, item_id);
    }
    return NULL;
}

static int parse_unsigned(const char *token, unsigned long maximum, unsigned long *value)
{
    char *end;
    unsigned long parsed;
    if (token == NULL || *token == '\0' || *token == '-') return 0;
    parsed = strtoul(token, &end, 10);
    if (end == token || *end != '\0' || parsed > maximum) return 0;
    *value = parsed;
    return 1;
}

int building_render_parse_segment(const char *line, int is_chug, BuildingRenderSegment *segment)
{
    char tag[16];
    char first_token[24];
    char last_token[24];
    char speed_token[24];
    char mode_token[8] = "L";
    unsigned long first;
    unsigned long last;
    unsigned long speed = 0;
    int fields;

    fields = sscanf(line, "%15s %23s %23s %23s %7s",
                    tag, first_token, last_token, speed_token, mode_token);
    if ((!is_chug && fields < 3) || (is_chug && fields < 4) ||
        !parse_unsigned(first_token, UINT16_MAX, &first) || first == 0 ||
        !parse_unsigned(last_token, UINT16_MAX, &last) || last < first) return 0;
    if (fields >= 4 && !parse_unsigned(speed_token, UINT16_MAX, &speed)) return 0;
    if (is_chug && fields < 5) return 0;
    if (is_chug && !building_render_ascii_case_equal(mode_token, "L") &&
        !building_render_ascii_case_equal(mode_token, "P")) return 0;
    segment->first_frame = (uint16_t)first;
    segment->last_frame = (uint16_t)last;
    segment->ticks_per_frame = (uint16_t)speed;
    segment->ping_pong = (uint8_t)(is_chug && building_render_ascii_case_equal(mode_token, "P"));
    segment->present = 1;
    return 1;
}

int building_render_parse_animation_layer(const char *line, const char *tag,
                                 BuildingRenderSegment *segment)
{
    char read_tag[16];
    char mode_token[8];
    unsigned long first = 0;
    unsigned long last = 0;
    unsigned long speed = 0;
    long value_a = 0;
    long value_b = 0;
    long offset_x = 0;
    long offset_y = 0;
    int consumed = 0;
    int fields;

    if (building_render_ascii_case_equal(tag, "inci")) {
        fields = sscanf(line, "%15s %lu %lu %lu %7s %ld", read_tag, &first, &last,
                        &speed, mode_token, &value_a);
        if (fields != 6) return 0;
    } else if (building_render_ascii_case_equal(tag, "cons")) {
        fields = sscanf(line, "%15s %lu %lu %lu %7s %ld %n", read_tag,
                        &first, &last, &speed, mode_token, &value_a,
                        &consumed);
        if (fields != 6 || sscanf(line + consumed, "%ld , %ld", &offset_x,
                                  &offset_y) != 2) return 0;
    } else if (building_render_ascii_case_equal(tag, "prod")) {
        fields = sscanf(line, "%15s %lu %lu %lu %7s %ld %ld %n",
                        read_tag, &first, &last, &speed, mode_token, &value_a,
                        &value_b, &consumed);
        if (fields != 7 || sscanf(line + consumed, "%ld , %ld", &offset_x,
                                  &offset_y) != 2) return 0;
    } else {
        return 0;
    }

    if (!building_render_ascii_case_equal(read_tag, tag) || first == 0 || last < first ||
        first > UINT16_MAX || last > UINT16_MAX || speed == 0 || speed > UINT16_MAX ||
        value_a < 0 || value_a > (long)UINT16_MAX ||
        value_b < 0 || value_b > (long)UINT16_MAX ||
        offset_x < INT16_MIN || offset_x > INT16_MAX ||
        offset_y < INT16_MIN || offset_y > INT16_MAX ||
        (!building_render_ascii_case_equal(mode_token, "L") && !building_render_ascii_case_equal(mode_token, "P"))) return 0;

    segment->first_frame = (uint16_t)first;
    segment->last_frame = (uint16_t)last;
    segment->ticks_per_frame = (uint16_t)speed;
    segment->fallback_frame = (uint16_t)value_a;
    if (building_render_ascii_case_equal(tag, "prod")) {
        /* FUN_00455833 stores PROD+4 in ticks, not as the source frame
           number. A zero value leaves the native -1 sentinel intact. */
        segment->threshold = value_b == 0 ? UINT16_MAX
            : (uint16_t)(((uint32_t)((int32_t)value_b - (int32_t)first)) *
                         (uint32_t)speed);
    } else {
        segment->threshold = (uint16_t)value_b;
    }
    if (building_render_ascii_case_equal(tag, "cons")) {
        segment->parameter_a = (int16_t)offset_x;
        segment->parameter_b = (int16_t)offset_y;
    } else {
        segment->offset_x = (int16_t)offset_x;
        segment->offset_y = (int16_t)offset_y;
    }
    segment->ping_pong = (uint8_t)building_render_ascii_case_equal(mode_token, "P");
    segment->present = 1;
    return 1;
}

int building_render_parse_occu(const char *line, BuildingRenderSegment *segment)
{
    char tag[16];
    unsigned long first = 0;
    unsigned long last = 0;
    long offset_x;
    long offset_y;
    int consumed = 0;
    if (sscanf(line, "%15s %lu %lu %n", tag, &first, &last, &consumed) != 3 ||
        sscanf(line + consumed, "%ld , %ld", &offset_x, &offset_y) != 2 ||
        !building_render_ascii_case_equal(tag, "occu") ||
        first == 0 || last < first || first > UINT16_MAX || last > UINT16_MAX ||
        offset_x < INT16_MIN || offset_x > INT16_MAX ||
        offset_y < INT16_MIN || offset_y > INT16_MAX) return 0;
    segment->first_frame = (uint16_t)first;
    segment->last_frame = (uint16_t)last;
    segment->parameter_a = (int16_t)offset_x;
    segment->parameter_b = (int16_t)offset_y;
    segment->present = 1;
    return 1;
}

int building_render_parse_barg(const char *line, BuildingRenderSegment *segment)
{
    char tag[16];
    char first_token[24];
    char last_token[24];
    unsigned long first;
    unsigned long last;
    if (sscanf(line, "%15s %23s %23s", tag, first_token, last_token) != 3 ||
        !building_render_ascii_case_equal(tag, "barg") ||
        !parse_unsigned(first_token, UINT16_MAX, &first) || first == 0 ||
        !parse_unsigned(last_token, UINT16_MAX, &last) || last < first) return 0;
    segment->first_frame = (uint16_t)first;
    segment->last_frame = (uint16_t)last;
    segment->present = 1;
    return 1;
}
