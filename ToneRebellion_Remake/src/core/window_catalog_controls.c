#include "window_catalog.h"

#include <limits.h>
#include <string.h>

const WindowTemplate *window_catalog_find(const WindowCatalog *catalog,
                                          const char *name, int32_t state)
{
    size_t i;
    if (catalog == NULL || name == NULL) return NULL;
    for (i = 0; i < catalog->count; ++i) {
        const WindowTemplate *window = &catalog->windows[i];
        size_t j;
        if (strcmp(window->name, name) != 0) continue;
        for (j = 0; j < window->state_count; ++j) {
            if (window->states[j] == state) return window;
        }
    }
    return NULL;
}

const WindowTemplate *window_catalog_hit_test(const WindowCatalog *catalog,
                                               int32_t state, int32_t x,
                                               int32_t y)
{
    size_t i = catalog == NULL ? 0 : catalog->count;
    while (i != 0) {
        const WindowTemplate *window = &catalog->windows[--i];
        size_t j;
        int matches_state = 0;
        if (window->mouse_focus == 0) continue;
        for (j = 0; j < window->state_count; ++j) {
            if (window->states[j] == state) {
                matches_state = 1;
                break;
            }
        }
        if (matches_state && window->pane.left <= x && x < window->pane.right &&
            window->pane.top <= y && y < window->pane.bottom) return window;
    }
    return NULL;
}

const WindowTemplate *window_catalog_hit_test_names(
    const WindowCatalog *catalog, int32_t state, int32_t x, int32_t y,
    const char *const *names, size_t name_count)
{
    size_t i = catalog == NULL ? 0 : catalog->count;
    if (names == NULL || name_count == 0) return NULL;
    while (i != 0) {
        const WindowTemplate *window = &catalog->windows[--i];
        size_t name_index;
        int matches_name = 0;
        int matches_state = 0;
        if (window->mouse_focus == 0) continue;
        for (name_index = 0; name_index < name_count; ++name_index) {
            if (names[name_index] != NULL &&
                strcmp(window->name, names[name_index]) == 0) {
                matches_name = 1;
                break;
            }
        }
        if (!matches_name) continue;
        for (name_index = 0; name_index < window->state_count; ++name_index) {
            if (window->states[name_index] == state) {
                matches_state = 1;
                break;
            }
        }
        if (matches_state && window->pane.left <= x && x < window->pane.right &&
            window->pane.top <= y && y < window->pane.bottom) return window;
    }
    return NULL;
}

int32_t window_catalog_hover_frame(int32_t base_frame,
                                   int32_t control_index,
                                   int32_t hovered_control_index)
{
    if (control_index >= 0 && control_index == hovered_control_index)
        return base_frame + 1;
    return base_frame;
}

int32_t window_catalog_control_frame(const WindowTemplate *control,
                                     int hovered)
{
    if (control == NULL) return -1;
    if (!hovered || control->mouse_focus == 0 || control->shape_frame < 0)
        return control->shape_frame;
    if (control->has_hilite_frame) return control->hilite_frame;
    return control->shape_frame + 1;
}

int32_t window_catalog_control_overlay_frame(const WindowTemplate *control,
                                             int hovered)
{
    if (control == NULL || !hovered || control->mouse_focus == 0 ||
        control->shape_frame < 0) return -1;
    if (control->has_hilite_frame) return control->hilite_frame;
    return control->shape_frame + 1;
}

size_t window_catalog_control_render_frames(const WindowTemplate *control,
                                            int hovered,
                                            int32_t frames[2])
{
    int32_t overlay;
    if (control == NULL || frames == NULL || control->shape_frame < 0) return 0;
    frames[0] = control->shape_frame;
    overlay = window_catalog_control_overlay_frame(control, hovered);
    if (overlay >= 0 && overlay != frames[0]) {
        frames[1] = overlay;
        return 2;
    }
    return 1;
}

int window_catalog_onoff_state_control(const WindowTemplate *control,
                                       int enabled, WindowTemplate *out)
{
    if (control == NULL || out == NULL) return 0;
    *out = *control;
    if (!enabled && out->nstates > 1 && out->shape_frame >= 0)
        ++out->shape_frame;
    return 1;
}

int window_catalog_hall_panel_mode(const char *control_name)
{
    if (control_name == NULL) return WINDOW_ISLAND_PANEL_NONE;
    if (strcmp(control_name, "BC_GenInfo") == 0)
        return WINDOW_ISLAND_PANEL_GENERAL;
    if (strcmp(control_name, "BC_Storage") == 0)
        return WINDOW_ISLAND_PANEL_INVENTORY;
    if (strcmp(control_name, "BC_Knowledge") == 0)
        return WINDOW_ISLAND_PANEL_GLYPHS;
    if (strcmp(control_name, "BC_Diplomacy") == 0)
        return WINDOW_ISLAND_PANEL_DIPLOMACY;
    if (strcmp(control_name, "BC_Trade") == 0)
        return WINDOW_ISLAND_PANEL_TRADE;
    return WINDOW_ISLAND_PANEL_NONE;
}

int window_catalog_scroll_panel_mode(const char *control_name)
{
    if (control_name == NULL) return WINDOW_ISLAND_PANEL_NONE;
    if (strcmp(control_name, "scrollup") == 0 ||
        strcmp(control_name, "scrolldn") == 0) {
        return WINDOW_ISLAND_PANEL_TASKS;
    }
    if (strcmp(control_name, "escrollup") == 0 ||
        strcmp(control_name, "escrolldn") == 0) {
        return WINDOW_ISLAND_PANEL_EFFECT_DEBUG;
    }
    return WINDOW_ISLAND_PANEL_NONE;
}

int window_catalog_scroll_direction(const char *control_name, int panel_mode)
{
    if (control_name == NULL ||
        window_catalog_scroll_panel_mode(control_name) != panel_mode)
        return 0;
    if (strcmp(control_name, "scrollup") == 0 ||
        strcmp(control_name, "escrollup") == 0) return -1;
    if (strcmp(control_name, "scrolldn") == 0 ||
        strcmp(control_name, "escrolldn") == 0) return 1;
    return 0;
}

int window_catalog_scroll_step(int offset, int item_count, int visible_rows,
                               int direction)
{
    int maximum;
    if (item_count < 0) item_count = 0;
    if (visible_rows < 0) visible_rows = 0;
    maximum = item_count > visible_rows ? item_count - visible_rows : 0;
    if (offset < 0) offset = 0;
    if (offset > maximum) offset = maximum;
    if (direction < 0) {
        if (offset > 0) --offset;
    } else if (direction > 0 && item_count > visible_rows && offset < maximum) {
        ++offset;
    }
    return offset;
}

int window_catalog_island_button(const char *control_name)
{
    if (control_name == NULL) return WINDOW_ISLAND_BUTTON_NONE;
    if (strcmp(control_name, "GOTOMAP") == 0)
        return WINDOW_ISLAND_BUTTON_MAP;
    if (strcmp(control_name, "PANIC") == 0)
        return WINDOW_ISLAND_BUTTON_PANIC;
    if (strcmp(control_name, "TOGREALM") == 0)
        return WINDOW_ISLAND_BUTTON_REALM;
    if (strcmp(control_name, "TASKLIST") == 0)
        return WINDOW_ISLAND_BUTTON_TASKS;
    return WINDOW_ISLAND_BUTTON_NONE;
}
