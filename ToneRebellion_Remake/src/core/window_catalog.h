#ifndef TONE_REBELLION_WINDOW_CATALOG_H
#define TONE_REBELLION_WINDOW_CATALOG_H

#include <stddef.h>
#include <stdint.h>

enum {
    WINDOW_CATALOG_MAX_WINDOWS = 128,
    WINDOW_CATALOG_NAME_CAPACITY = 64,
    WINDOW_CATALOG_VALUE_CAPACITY = 64,
    WINDOW_CATALOG_MAX_STATES = 4
};

typedef struct WindowPane {
    int32_t left;
    int32_t top;
    int32_t right;
    int32_t bottom;
} WindowPane;

/* A parsed windows.txt descriptor. These are configuration fields, not a
   claim that the reconstructed C types match the binary's object layout. */
typedef struct WindowTemplate {
    uint16_t source_line;
    uint16_t type_id;
    uint8_t state_count;
    int32_t states[WINDOW_CATALOG_MAX_STATES];
    int32_t shape_frame;
    int32_t mouse_focus;
    int32_t continue_redraw;
    int32_t nstates;
    int32_t hilite_frame;
    int32_t end_value;
    uint8_t has_continue_redraw;
    uint8_t has_pane_extras;
    uint8_t has_nstates;
    uint8_t has_hilite_frame;
    uint8_t has_open_pane;
    uint8_t has_end_value;
    WindowPane pane;
    int32_t pane_extras[2];
    WindowPane open_pane;
    int32_t send_message[3];
    char name[WINDOW_CATALOG_NAME_CAPACITY];
    char shape_id[WINDOW_CATALOG_VALUE_CAPACITY];
    char message_destination[16];
    char movie_name[WINDOW_CATALOG_VALUE_CAPACITY];
} WindowTemplate;

typedef struct WindowCatalog {
    uint32_t shape_cache_size;
    uint16_t count;
    WindowTemplate windows[WINDOW_CATALOG_MAX_WINDOWS];
} WindowCatalog;

enum WindowIslandPanelMode {
    WINDOW_ISLAND_PANEL_NONE = -1,
    WINDOW_ISLAND_PANEL_GENERAL = 0,
    WINDOW_ISLAND_PANEL_TASKS = 2,
    WINDOW_ISLAND_PANEL_INVENTORY = 4,
    WINDOW_ISLAND_PANEL_GLYPHS = 5,
    WINDOW_ISLAND_PANEL_DIPLOMACY = 6,
    WINDOW_ISLAND_PANEL_TRADE = 7,
    WINDOW_ISLAND_PANEL_EFFECT_DEBUG = 8
};

enum WindowIslandButton {
    WINDOW_ISLAND_BUTTON_NONE = -1,
    WINDOW_ISLAND_BUTTON_MAP = 0,
    WINDOW_ISLAND_BUTTON_PANIC = 1,
    WINDOW_ISLAND_BUTTON_REALM = 2,
    WINDOW_ISLAND_BUTTON_TASKS = 3
};

/* Parse the local/source-format windows.txt bytes. Output is left untouched
   on malformed, incomplete, or unsupported records. */
int window_catalog_load(const unsigned char *bytes, size_t length,
                        WindowCatalog *out, char *error,
                        size_t error_capacity);

const WindowTemplate *window_catalog_find(const WindowCatalog *catalog,
                                          const char *name, int32_t state);
/* Tests pane rectangles in reverse descriptor order, so overlaps agree with
   this renderer's forward source-order drawing. Right and bottom edges are
   exclusive; that convention still needs verification for each UI class. */
const WindowTemplate *window_catalog_hit_test(const WindowCatalog *catalog,
                                               int32_t state, int32_t x,
                                               int32_t y);
const WindowTemplate *window_catalog_hit_test_names(
    const WindowCatalog *catalog, int32_t state, int32_t x, int32_t y,
    const char *const *names, size_t name_count);

/* Select the adjacent SHP frame only when a real control index is hovered.
   Negative indices represent non-interactive/unmapped templates. */
int32_t window_catalog_hover_frame(int32_t base_frame,
                                   int32_t control_index,
                                   int32_t hovered_control_index);

/* Use the descriptor's explicit HILITEFRAME when present; windows.txt controls
   without one use the adjacent frame convention used by the title menus. */
int32_t window_catalog_control_frame(const WindowTemplate *control,
                                     int hovered);

/* These names and panel numbers mirror FUN_0042f150 / FUN_0042f303 and the
   permanent-button messages dispatched by FUN_0042fa0f. */
int window_catalog_hall_panel_mode(const char *control_name);
/* FUN_0042fa0f routes scrollup/dn to IWTasks and escrollup/dn to IWEffList. */
int window_catalog_scroll_panel_mode(const char *control_name);
/* FUN_00445145 handles scroll messages even when bounds keep the offset at
   its current value. Returns -1 for up, +1 for down, and 0 for other controls. */
int window_catalog_scroll_direction(const char *control_name, int panel_mode);
/* Bounded one-row scroll step used by IWTasks (messages 6000/6001). */
int window_catalog_scroll_step(int offset, int item_count, int visible_rows,
                               int direction);
int window_catalog_island_button(const char *control_name);

#endif
