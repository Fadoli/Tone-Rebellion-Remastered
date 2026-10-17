#include "window_catalog.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const unsigned char fixture[] =
    "SHAPECACHE_SIZE 4000000\n"
    "WINTYPE 1 // BitmapButton\n"
    "NAME NEWGAME\n"
    "STATE 1\n"
    "SHAPEID NEWBUTT\n"
    "SHAPEFRAME 15\n"
    "MOUSEFOCUS 1\n"
    "PANE 564 419 633 464\n"
    "SENDMESSAGE 52 0 0\n"
    "MSGDEST MASTER\n"
    "HILITEFRAME 16\n"
    "WINTYPE 12\n"
    "NAME SHADE\n"
    "STATE 2 3\n"
    "SHAPEID slidewin\n"
    "SHAPEFRAME 0\n"
    "MOUSEFOCUS 1\n"
    "PANE 0 0 639 0\n"
    "SENDMESSAGE 0 0 0\n"
    "MSGDEST WINMGR\n"
    "OPENPANE 0 0 639 99\n"
    "END -1\n";

static unsigned char *read_file(const char *path, size_t *length)
{
    FILE *file = fopen(path, "rb");
    long size;
    unsigned char *bytes;
    if (file == NULL) return NULL;
    if (fseek(file, 0, SEEK_END) != 0 || (size = ftell(file)) < 0 ||
        fseek(file, 0, SEEK_SET) != 0) {
        fclose(file);
        return NULL;
    }
    bytes = (unsigned char *)malloc((size_t)size);
    if (bytes == NULL || fread(bytes, 1, (size_t)size, file) != (size_t)size) {
        free(bytes);
        fclose(file);
        return NULL;
    }
    fclose(file);
    *length = (size_t)size;
    return bytes;
}

static void verify_fixture(void)
{
    WindowCatalog catalog;
    const WindowTemplate *window;
    char error[128];
    memset(&catalog, 0xa5, sizeof(catalog));
    assert(window_catalog_load(fixture, sizeof(fixture) - 1, &catalog,
                               error, sizeof(error)));
    assert(catalog.shape_cache_size == 4000000u);
    assert(catalog.count == 2);
    window = window_catalog_find(&catalog, "NEWGAME", 1);
    assert(window != NULL && window->type_id == 1);
    assert(window->pane.left == 564 && window->pane.bottom == 464);
    assert(window->send_message[0] == 52);
    assert(strcmp(window->message_destination, "MASTER") == 0);
    assert(window->has_hilite_frame && window->hilite_frame == 16);
    assert(window_catalog_hit_test(&catalog, 1, 564, 419) == window);
    assert(window_catalog_hit_test(&catalog, 1, 633, 419) == NULL);
    window = window_catalog_find(&catalog, "SHADE", 3);
    assert(window != NULL && window->state_count == 2);
    assert(window->has_open_pane && window->open_pane.bottom == 99);
    assert(window->has_end_value && window->end_value == -1);
    assert(window_catalog_find(&catalog, "SHADE", 4) == NULL);
}

static void verify_rejects_incomplete_records(void)
{
    static const unsigned char incomplete[] =
        "WINTYPE 1\nNAME BROKEN\nSTATE 0\n";
    WindowCatalog catalog;
    WindowCatalog before;
    char error[128];
    memset(&catalog, 0x5a, sizeof(catalog));
    before = catalog;
    assert(!window_catalog_load(incomplete, sizeof(incomplete) - 1,
                                &catalog, error, sizeof(error)));
    assert(memcmp(&catalog, &before, sizeof(catalog)) == 0);
    assert(strstr(error, "incomplete") != NULL);
}

static void verify_hover_frame_selection(void)
{
    /* Empty hover state must keep unmapped background templates on base art. */
    assert(window_catalog_hover_frame(0, -1, -1) == 0);
    assert(window_catalog_hover_frame(4, -1, -1) == 4);
    assert(window_catalog_hover_frame(0, 3, -1) == 0);
    assert(window_catalog_hover_frame(8, 3, 3) == 9);
    assert(window_catalog_hover_frame(8, 3, 2) == 8);
    {
        WindowTemplate control;
        memset(&control, 0, sizeof(control));
        control.shape_frame = 1;
        control.mouse_focus = 1;
        control.has_hilite_frame = 1;
        control.hilite_frame = 4;
        assert(window_catalog_control_frame(&control, 0) == 1);
        assert(window_catalog_control_frame(&control, 1) == 4);
        control.has_hilite_frame = 0;
        assert(window_catalog_control_frame(&control, 1) == 2);
        control.shape_frame = -1;
        assert(window_catalog_control_frame(&control, 1) == -1);
    }
}

static void verify_original_manifest(const char *path)
{
    WindowCatalog catalog;
    const WindowTemplate *window;
    char error[128];
    size_t length = 0;
    unsigned char *bytes = read_file(path, &length);
    assert(bytes != NULL);
    if (!window_catalog_load(bytes, length, &catalog, error, sizeof(error))) {
        fprintf(stderr, "windows.txt parse failed: %s\n", error);
        assert(0);
    }
    free(bytes);
    assert(catalog.count == 100);
    assert(catalog.shape_cache_size == 4000000u);
    window = window_catalog_hit_test(&catalog, 1, 600, 430);
    assert(window != NULL && strcmp(window->name, "BEGINGAME") == 0);
    window = window_catalog_hit_test(&catalog, 1, 10, 430);
    assert(window != NULL && strcmp(window->name, "EXITNEWGAME") == 0);
    window = window_catalog_find(&catalog, "NEWGAMWND", 1);
    assert(window != NULL && window->type_id == 4);
    window = window_catalog_find(&catalog, "IWConstruct", 3);
    assert(window != NULL && window->type_id == 0x12);
    assert(window->pane.left == 192 && window->pane.top == 368 &&
           window->pane.right == 447 && window->pane.bottom == 471);
    window = window_catalog_find(&catalog, "IWConstructInfo", 3);
    assert(window != NULL && window->type_id == 0x1c);
    window = window_catalog_find(&catalog, "BuildCycle", 3);
    assert(window != NULL && window->type_id == 1);
    assert(window->pane.left == 282 && window->pane.top == 368 &&
           window->pane.right == 358 && window->pane.bottom == 391);
    assert(window->send_message[0] == 0x45);
    assert(strcmp(window->message_destination, "IWConstruct") == 0);
    window = window_catalog_find(&catalog, "WORLDVIEW", 2);
    assert(window != NULL && window->type_id == 0x0b);
    window = window_catalog_find(&catalog, "BC_TrnStkC", 3);
    assert(window != NULL && window->has_pane_extras);
    assert(window->pane_extras[0] == -4 && window->pane_extras[1] == 0);
    window = window_catalog_find(&catalog, "BC_HallStkB", 3);
    assert(window != NULL && window->type_id == 35 && window->state_count == 1 &&
           window->states[0] == 3);
    assert(strcmp(window->shape_id, "THBUTT") == 0 && window->shape_frame == 1);
    assert(window->pane.left == 191 && window->pane.top == 384 &&
           window->pane.right == 223 && window->pane.bottom == 416);
    assert(window->nstates == 3 && window->has_hilite_frame &&
           window->hilite_frame == 4);
    window = window_catalog_find(&catalog, "BC_HallStkC", 3);
    assert(window != NULL && window->pane.top == 412 && window->pane.bottom == 444);
    window = window_catalog_find(&catalog, "BC_HallStkM", 3);
    assert(window != NULL && window->pane.top == 440 && window->pane.bottom == 471);
    {
        static const char *const permanent_buttons[] = {
            "GOTOMAP", "PANIC", "TOGREALM", "TASKLIST"
        };
        static const int32_t button_x[] = {20, 120, 20, 120};
        static const int32_t button_y[] = {340, 340, 440, 440};
        size_t button;
        for (button = 0; button < sizeof(permanent_buttons) / sizeof(permanent_buttons[0]);
             ++button) {
            window = window_catalog_find(&catalog, permanent_buttons[button], 3);
            assert(window != NULL && window->mouse_focus == 1);
            assert(window_catalog_hit_test(&catalog, 3, button_x[button],
                                           button_y[button]) == window);
        }
    }
    puts("parsed original windows.txt: 100 descriptors; menu, world, construction and Hall reserve controls found");
}

int main(int argc, char **argv)
{
    verify_fixture();
    verify_rejects_incomplete_records();
    verify_hover_frame_selection();
    if (argc > 1) verify_original_manifest(argv[1]);
    puts("window_catalog tests passed");
    return 0;
}
