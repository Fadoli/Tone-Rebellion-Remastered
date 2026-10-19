#ifndef TONE_REBELLION_BUILDING_RENDER_INTERNAL_H
#define TONE_REBELLION_BUILDING_RENDER_INTERNAL_H

#include "building_render.h"

enum { BUILDING_RENDER_LINE_CAPACITY = 256 };

void building_render_set_error(char *error, size_t capacity,
                               const char *message, size_t line);
int building_render_ascii_case_equal(const char *left, const char *right);
int building_render_next_line(const unsigned char *bytes, size_t length,
                              size_t *position,
                              char line[BUILDING_RENDER_LINE_CAPACITY]);
BuildingRenderItem *building_render_find_item_name(BuildingRenderCatalog *catalog,
                                                   const PadCatalog *pads,
                                                   const char *name);
int building_render_parse_segment(const char *line, int is_chug,
                                  BuildingRenderSegment *segment);
int building_render_parse_animation_layer(const char *line, const char *tag,
                                          BuildingRenderSegment *segment);
int building_render_parse_occu(const char *line, BuildingRenderSegment *segment);
int building_render_parse_barg(const char *line, BuildingRenderSegment *segment);

#endif
