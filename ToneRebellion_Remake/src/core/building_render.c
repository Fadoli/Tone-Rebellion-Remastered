#include "building_render.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { BUILDING_RENDER_LINE_CAPACITY = 256 };

static void set_error(char *error, size_t capacity, const char *message, size_t line)
{
    if (error == NULL || capacity == 0) return;
    if (line == 0) (void)snprintf(error, capacity, "%s", message);
    else (void)snprintf(error, capacity, "line %lu: %s", (unsigned long)line, message);
    error[capacity - 1] = '\0';
}

static int ascii_case_equal(const char *left, const char *right)
{
    while (*left != '\0' && *right != '\0') {
        if (tolower((unsigned char)*left) != tolower((unsigned char)*right)) return 0;
        ++left;
        ++right;
    }
    return *left == *right;
}

static int next_line(const unsigned char *bytes, size_t length, size_t *position,
                     char line[BUILDING_RENDER_LINE_CAPACITY])
{
    size_t start = *position;
    size_t line_length;
    char *comment;
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

static BuildingRenderItem *find_item_name(BuildingRenderCatalog *catalog,
                                          const PadCatalog *pads, const char *name)
{
    uint16_t item_id;
    for (item_id = 0; item_id < pads->item_count; ++item_id) {
        const PadCatalogItem *pad = &pads->items[item_id];
        if (ascii_case_equal(pad->shape_id, "noshape")) continue;
        if (ascii_case_equal(pad->shape_id, name)) return find_mutable(catalog, item_id);
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

static int parse_segment(const char *line, int is_chug, BuildingRenderSegment *segment)
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
    if (is_chug && !ascii_case_equal(mode_token, "L") &&
        !ascii_case_equal(mode_token, "P")) return 0;
    segment->first_frame = (uint16_t)first;
    segment->last_frame = (uint16_t)last;
    segment->ticks_per_frame = (uint16_t)speed;
    segment->ping_pong = (uint8_t)(is_chug && ascii_case_equal(mode_token, "P"));
    segment->present = 1;
    return 1;
}

int building_render_catalog_load(const unsigned char *bytes, size_t length,
                                 const PadCatalog *pads, BuildingRenderCatalog *out,
                                 char *error, size_t error_capacity)
{
    BuildingRenderCatalog parsed;
    BuildingRenderItem *current = NULL;
    size_t position = 0;
    size_t line_number = 0;
    char line[BUILDING_RENDER_LINE_CAPACITY];
    int status;

    if (error != NULL && error_capacity != 0) error[0] = '\0';
    if (bytes == NULL || pads == NULL || out == NULL || pads->item_count == 0 ||
        pads->item_count > PAD_CATALOG_MAX_ITEMS) {
        set_error(error, error_capacity, "input, pad catalog and output are required", 0);
        return 0;
    }
    memset(&parsed, 0, sizeof(parsed));
    parsed.item_count = pads->item_count;
    while ((status = next_line(bytes, length, &position, line)) != 0) {
        char tag[16];
        char value[BUILDING_RENDER_SHAPE_CAPACITY];
        ++line_number;
        if (status < 0) {
            set_error(error, error_capacity, "bldinf line is too long", line_number);
            return 0;
        }
        if (status == 2) continue;
        if (sscanf(line, "%15s %23s", tag, value) < 1) continue;
        if (ascii_case_equal(tag, "item")) {
            current = find_item_name(&parsed, pads, value);
            if (current != NULL) {
                const PadCatalogItem *pad = &pads->items[current->item_id];
                current->present = 1;
                (void)strncpy(current->shape_id, pad->shape_id,
                              sizeof(current->shape_id) - 1U);
                current->shape_id[sizeof(current->shape_id) - 1U] = '\0';
            }
        } else if (current != NULL && ascii_case_equal(tag, "shape")) {
            if (strlen(value) >= sizeof(current->shape_id)) {
                set_error(error, error_capacity, "shape ID is too long", line_number);
                return 0;
            }
            (void)strcpy(current->shape_id, value);
        } else if (current != NULL && ascii_case_equal(tag, "base")) {
            if (!parse_segment(line, 0, &current->base)) {
                set_error(error, error_capacity, "invalid BASE animation segment", line_number);
                return 0;
            }
        } else if (current != NULL && ascii_case_equal(tag, "chug")) {
            if (!parse_segment(line, 1, &current->chug)) {
                set_error(error, error_capacity, "invalid CHUG animation segment", line_number);
                return 0;
            }
        } else if (current != NULL && ascii_case_equal(tag, "glyp")) {
            if (!parse_segment(line, 0, &current->glyph)) {
                set_error(error, error_capacity, "invalid GLYP animation segment", line_number);
                return 0;
            }
        }
    }
    *out = parsed;
    return 1;
}

const BuildingRenderItem *building_render_find(const BuildingRenderCatalog *catalog,
                                               uint16_t item_id)
{
    if (catalog == NULL || item_id >= catalog->item_count ||
        !catalog->items[item_id].present) return NULL;
    return &catalog->items[item_id];
}

uint32_t building_render_base_frame(const BuildingRenderItem *item)
{
    const BuildingRenderSegment *segment;
    if (item == NULL) return 0;
    segment = item->base.present ? &item->base : &item->chug;
    if (!segment->present || segment->first_frame == 0 ||
        segment->last_frame < segment->first_frame) return 0;
    return (uint32_t)segment->first_frame - 1U;
}

uint32_t building_render_chug_frame(const BuildingRenderItem *item,
                                    uint32_t animation_ticks)
{
    const BuildingRenderSegment *segment;
    uint32_t first;
    uint32_t last;
    uint32_t span;
    uint32_t step;
    uint32_t offset;

    if (item == NULL || !item->chug.present || item->chug.first_frame == 0 ||
        item->chug.last_frame < item->chug.first_frame ||
        item->chug.ticks_per_frame == 0) return 0;
    segment = &item->chug;
    first = (uint32_t)segment->first_frame - 1U;
    last = (uint32_t)segment->last_frame - 1U;
    span = last - first;
    step = animation_ticks / (uint32_t)segment->ticks_per_frame;
    if (segment->ping_pong != 0 && span != 0) {
        uint32_t cycle = span * 2U;
        offset = step % cycle;
        if (offset > span) offset = cycle - offset;
    } else {
        offset = step % (span + 1U);
    }
    return first + offset;
}

uint32_t building_render_glyph_frame(const BuildingRenderItem *item,
                                     uint32_t animation_ticks)
{
    uint32_t first;
    uint32_t last;
    uint32_t phase;

    if (item == NULL || !item->glyph.present || item->glyph.first_frame == 0 ||
        item->glyph.last_frame < item->glyph.first_frame) return 0;
    first = (uint32_t)item->glyph.first_frame - 1U;
    last = (uint32_t)item->glyph.last_frame - 1U;
    phase = animation_ticks % 40U;
    if (phase > 20U) phase = 40U - phase;
    return first + ((last - first) * phase) / 20U;
}
