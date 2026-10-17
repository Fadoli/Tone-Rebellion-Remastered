#include "building_render.h"
#include "game_session.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void verify_local_corpus(const char *pad_path, const char *bldinf_path)
{
    FILE *file;
    unsigned char *pad_bytes;
    unsigned char *bldinf_bytes;
    long pad_length;
    long bldinf_length;
    PadCatalog pads;
    BuildingRenderCatalog buildings;
    const BuildingRenderItem *item;
    static const uint16_t hall_ids[4] = {42, 58, 74, 90};
    static const uint16_t hall_last_frames[4] = {3, 3, 4, 4};
    unsigned int i;
    unsigned int glyph_count = 0;
    char error[128];

    file = fopen(pad_path, "rb");
    assert(file != NULL && fseek(file, 0, SEEK_END) == 0);
    pad_length = ftell(file);
    assert(pad_length > 0 && pad_length < 65536 && fseek(file, 0, SEEK_SET) == 0);
    pad_bytes = (unsigned char *)malloc((size_t)pad_length);
    assert(pad_bytes != NULL && fread(pad_bytes, 1, (size_t)pad_length, file) ==
           (size_t)pad_length && fclose(file) == 0);

    file = fopen(bldinf_path, "rb");
    assert(file != NULL && fseek(file, 0, SEEK_END) == 0);
    bldinf_length = ftell(file);
    assert(bldinf_length > 0 && bldinf_length < 262144 &&
           fseek(file, 0, SEEK_SET) == 0);
    bldinf_bytes = (unsigned char *)malloc((size_t)bldinf_length);
    assert(bldinf_bytes != NULL && fread(bldinf_bytes, 1, (size_t)bldinf_length, file) ==
           (size_t)bldinf_length && fclose(file) == 0);

    assert(pad_catalog_load(pad_bytes, (size_t)pad_length, &pads, error, sizeof(error)));
    if (!building_render_catalog_load(bldinf_bytes, (size_t)bldinf_length, &pads,
                                      &buildings, error, sizeof(error))) {
        (void)fprintf(stderr, "bldinf corpus parse failed: %s\n", error);
        assert(0);
    }
    free(pad_bytes);
    free(bldinf_bytes);

    item = building_render_find(&buildings, 42);
    assert(item != NULL && strcmp(item->shape_id, "p-hall") == 0);
    assert(item->base.present && item->base.first_frame == 1 &&
           item->base.last_frame == 3 && item->base.ticks_per_frame == 50);
    for (i = 0; i < 4; ++i) {
        item = building_render_find(&buildings, hall_ids[i]);
        assert(item != NULL && item->base.present &&
               item->base.last_frame == hall_last_frames[i]);
    }
    item = building_render_find(&buildings, 6);
    assert(item != NULL && item->base.present && item->chug.present);
    assert(strcmp(item->shape_id, "v-psupp") == 0);
    for (i = 7; i <= 9; ++i) {
        item = building_render_find(&buildings, (uint16_t)i);
        assert(item != NULL && item->base.present && item->shape_id[0] != '\0');
    }
    for (i = 0; i < buildings.item_count; ++i) {
        item = building_render_find(&buildings, (uint16_t)i);
        if (item != NULL && item->glyph.present) {
            assert(item->glyph.first_frame <= item->glyph.last_frame);
            ++glyph_count;
        }
    }
    assert(glyph_count > 0);
    (void)puts("real pad.txt + bldinf.txt catalogs passed");
}

int main(int argc, char **argv)
{
    static const unsigned char pad_fixture[] =
        "0 0 0,0,0 0 0 0 None noshape\n"
        "0 0 0,0,0 0 80 0 Levi v-psupp\n"
        "0 0 0,0,0 0 80 0 Levi v-ssupp\n"
        "0 0 0,0,0 0 50 0 Prot p-hall\n"
        "0 0 0,0,0 0 50 0 Levi v-chug\n";
    static const unsigned char bldinf_fixture[] =
        "item P-HALL\n"
        "BASE 1 3 50\n"
        "item V-PSUPP\n"
        "BASE 1 1 70\n"
        "CHUG 2 15 2 L\n"
        "item V-SSUPP\n"
        "BASE 1 1 70\n"
        "CHUG 2 4 3 P\n"
        "GLYP 22 25\n"
        "INCI 2 5 1 L 0\n"
        "CONS 8 17 2 L 9 -3,-40\n"
        "PROD 7 14 3 L 0 11 6,-13\n"
        "OCCU 4 4 -6,-14\n"
        "BARG 16 20\n"
        "item V-CHUG\n"
        "CHUG 2 4 3 P\n";
    PadCatalog pads;
    BuildingRenderCatalog buildings;
    GameSession session;
    const BuildingRenderItem *item;
    unsigned int i;
    char error[128];

    assert(pad_catalog_load(pad_fixture, sizeof(pad_fixture) - 1, &pads,
                            error, sizeof(error)));
    assert(building_render_catalog_load(bldinf_fixture, sizeof(bldinf_fixture) - 1,
                                        &pads, &buildings, error, sizeof(error)));
    item = building_render_find(&buildings, 3);
    assert(item != NULL && item->item_id == 3 && item->base.present && !item->chug.present);
    /* BASE is a static frame; CHUG and GLYP use separate source counters. */
    item = building_render_find(&buildings, 3);
    assert(building_render_base_frame(item) == 0);
    assert(building_render_base_frame_for_state(item, 1, 0) == 1);
    assert(building_render_base_frame_for_state(item, 99, 0) == 2);
    assert(building_render_base_frame_for_state(item, 1, 0x20) == 0);

    item = building_render_find(&buildings, 2);
    assert(item != NULL && item->chug.present && item->chug.ping_pong == 1);
    assert(building_render_base_frame(item) == 0);
    assert(building_render_chug_frame(item, 0) == 1);
    assert(building_render_chug_frame(item, 3) == 2);
    assert(building_render_chug_frame(item, 6) == 3);
    assert(building_render_chug_frame(item, 9) == 2);
    assert(building_render_chug_duration(item) == 12);
    assert(item->glyph.present);
    assert(building_render_glyph_frame(item, 0) == 21);
    assert(building_render_glyph_frame(item, 10) == 23);
    assert(building_render_glyph_frame(item, 20) == 24);
    assert(building_render_glyph_frame(item, 30) == 23);
    assert(item->inci.present && item->cons.present && item->prod.present &&
           item->occu.present && item->barg.present);
    assert(building_render_inci_frame(item, 0) == 1);
    assert(building_render_inci_frame(item, 2) == 3);
    assert(building_render_cons_frame(item, 0, 0) == 8);
    assert(building_render_cons_frame(item, 2, 4) == 8);
    assert(building_render_prod_frame(item, 0, 0) == UINT32_MAX);
    assert(building_render_prod_frame(item, 3, 2) == 7);
    assert(item->prod.offset_x == 6 && item->prod.offset_y == -13);
    {
        BuildingRenderPoint position = building_render_prod_frame_position(120, 80);
        assert(position.x == 120 && position.y == 80);
        position = building_render_prod_threshold_position(item, 120, 80);
        assert(position.x == 126 && position.y == 67);
        position = building_render_prod_threshold_position(NULL, 120, 80);
        assert(position.x == 120 && position.y == 80);
    }
    assert(item->occu.first_frame == 4 && item->occu.parameter_a == -6 &&
           item->occu.parameter_b == -14);
    assert(item->barg.first_frame == 16 && item->barg.last_frame == 20);
    assert(building_render_barg_frame(item, 0.0) == UINT32_MAX);
    assert(building_render_barg_frame(item, 0.05) == UINT32_MAX);
    assert(building_render_barg_frame(item, 0.1) == 15);
    assert(building_render_barg_frame(item, 0.25) == 16); /* 1.5 rounds to even 2 */
    assert(building_render_barg_frame(item, 0.5) == 17);
    assert(building_render_barg_frame(item, 1.0) == 19);
    assert(building_render_barg_frame(item, -0.5) == UINT32_MAX);
    assert(building_render_barg_frame(item, 1000000000.0) == UINT32_MAX);
    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    session.islands[0].location_count = 1;
    session.islands[0].locations[0].record_value_10 = 2;
    session.islands[0].locations[0].renderer_class = 1;
    game_session_tick_item_animations(&session, &buildings);
    assert(session.islands[0].locations[0].chug_progress == 1);
    game_session_tick_item_animations(&session, &buildings);
    game_session_tick_item_animations(&session, &buildings);
    assert(session.islands[0].locations[0].chug_progress == 3);
    assert(building_render_chug_frame(item,
           session.islands[0].locations[0].chug_progress) == 2);
    for (i = 3; i < 12; ++i) game_session_tick_item_animations(&session, &buildings);
    assert(session.islands[0].locations[0].chug_progress == 0);
    item = building_render_find(&buildings, 4);
    assert(item != NULL && !item->base.present && item->chug.present);
    assert(building_render_base_frame(item) == 0);
    assert(building_render_chug_frame(item, 0) == 1);
    item = building_render_find(&buildings, 2);
    assert(item != NULL && building_render_base_frame(item) == 0);
    if (argc == 3) verify_local_corpus(argv[1], argv[2]);
    else if (argc != 1) return 2;
    (void)puts("building render tests passed");
    return 0;
}
