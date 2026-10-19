#include "building_render.h"
#include "building_render_internal.h"

#include <stdio.h>
#include <string.h>

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
        building_render_set_error(error, error_capacity, "input, pad catalog and output are required", 0);
        return 0;
    }
    memset(&parsed, 0, sizeof(parsed));
    parsed.item_count = pads->item_count;
    while ((status = building_render_next_line(bytes, length, &position, line)) != 0) {
        char tag[16];
        char value[BUILDING_RENDER_SHAPE_CAPACITY];
        ++line_number;
        if (status < 0) {
            building_render_set_error(error, error_capacity, "bldinf line is too long", line_number);
            return 0;
        }
        if (status == 2) continue;
        if (sscanf(line, "%15s %23s", tag, value) < 1) continue;
        if (building_render_ascii_case_equal(tag, "item")) {
            current = building_render_find_item_name(&parsed, pads, value);
            if (current != NULL) {
                const PadCatalogItem *pad = &pads->items[current->item_id];
                current->present = 1;
                (void)strncpy(current->shape_id, pad->shape_id,
                              sizeof(current->shape_id) - 1U);
                current->shape_id[sizeof(current->shape_id) - 1U] = '\0';
            }
        } else if (current != NULL && building_render_ascii_case_equal(tag, "shape")) {
            if (strlen(value) >= sizeof(current->shape_id)) {
                building_render_set_error(error, error_capacity, "shape ID is too long", line_number);
                return 0;
            }
            (void)strcpy(current->shape_id, value);
        } else if (current != NULL && building_render_ascii_case_equal(tag, "base")) {
            if (!building_render_parse_segment(line, 0, &current->base)) {
                building_render_set_error(error, error_capacity, "invalid BASE animation segment", line_number);
                return 0;
            }
        } else if (current != NULL && building_render_ascii_case_equal(tag, "chug")) {
            if (!building_render_parse_segment(line, 1, &current->chug)) {
                building_render_set_error(error, error_capacity, "invalid CHUG animation segment", line_number);
                return 0;
            }
        } else if (current != NULL && building_render_ascii_case_equal(tag, "glyp")) {
            if (!building_render_parse_segment(line, 0, &current->glyph)) {
                building_render_set_error(error, error_capacity, "invalid GLYP animation segment", line_number);
                return 0;
            }
        } else if (current != NULL && building_render_ascii_case_equal(tag, "inci")) {
            if (!building_render_parse_animation_layer(line, "inci", &current->inci)) {
                building_render_set_error(error, error_capacity, "invalid INCI animation segment", line_number);
                return 0;
            }
        } else if (current != NULL && building_render_ascii_case_equal(tag, "cons")) {
            if (!building_render_parse_animation_layer(line, "cons", &current->cons)) {
                building_render_set_error(error, error_capacity, "invalid CONS animation segment", line_number);
                return 0;
            }
        } else if (current != NULL && building_render_ascii_case_equal(tag, "prod")) {
            if (!building_render_parse_animation_layer(line, "prod", &current->prod)) {
                building_render_set_error(error, error_capacity, "invalid PROD animation segment", line_number);
                return 0;
            }
        } else if (current != NULL && building_render_ascii_case_equal(tag, "occu")) {
            if (!building_render_parse_occu(line, &current->occu)) {
                building_render_set_error(error, error_capacity, "invalid OCCU segment", line_number);
                return 0;
            }
        } else if (current != NULL && building_render_ascii_case_equal(tag, "barg")) {
            if (!building_render_parse_barg(line, &current->barg)) {
                building_render_set_error(error, error_capacity, "invalid BARG segment", line_number);
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
