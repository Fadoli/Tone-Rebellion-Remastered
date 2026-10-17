#include "pad_catalog.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void verify_local_corpus(const char *path)
{
    FILE *file = fopen(path, "rb");
    unsigned char *bytes;
    long file_length;
    PadCatalog catalog;
    char error[128];
    assert(file != NULL);
    assert(fseek(file, 0, SEEK_END) == 0);
    file_length = ftell(file);
    assert(file_length > 0 && file_length < 65536);
    assert(fseek(file, 0, SEEK_SET) == 0);
    bytes = (unsigned char *)malloc((size_t)file_length);
    assert(bytes != NULL);
    assert(fread(bytes, 1, (size_t)file_length, file) == (size_t)file_length);
    assert(fclose(file) == 0);
    assert(pad_catalog_load(bytes, (size_t)file_length, &catalog,
                            error, sizeof(error)));
    free(bytes);

    assert(catalog.item_count == 101);
    assert(catalog.items[37].tribe == PAD_TRIBE_PROTECTOR);
    assert(catalog.items[53].tribe == PAD_TRIBE_SEEKER);
    assert(catalog.items[69].tribe == PAD_TRIBE_MYSTIC);
    assert(catalog.items[85].tribe == PAD_TRIBE_LIFEGIVER);
    assert(catalog.items[100].item_id == 100);
    assert(pad_catalog_tribe_item_count(&catalog, PAD_TRIBE_PROTECTOR) == 16);
    assert(pad_catalog_tribe_item_count(&catalog, PAD_TRIBE_SEEKER) == 16);
    assert(pad_catalog_tribe_item_count(&catalog, PAD_TRIBE_MYSTIC) == 16);
    assert(pad_catalog_tribe_item_count(&catalog, PAD_TRIBE_LIFEGIVER) == 16);
    assert(pad_catalog_tribe_item_at(&catalog, PAD_TRIBE_PROTECTOR, 0)->item_id == 37);
    assert(pad_catalog_tribe_item_at(&catalog, PAD_TRIBE_LIFEGIVER, 15)->item_id == 100);
    (void)puts("real pad.txt catalog passed");
}

int main(int argc, char **argv)
{
    static const unsigned char fixture[] =
        "; size cost bld,cry,mag upkeep hp range tribe shape text\r\n"
        "0 0 0,0,0 0 0 0 None noshape\r\n"
        "0 0 0,0,0 0 20 0 Levi v-shld0\r\n"
        "0 35 10,0,10 1 30 0 Prot p-bldton BLDTON\r\n"
        "1 -1 20,0,20 0 14 0 Prot noshape NONE\r\n";
    static const unsigned char malformed[] =
        "0 35 10,0 1 30 0 Prot p-bldton BLDTON\n";
    PadCatalog catalog;
    char error[128];
    const PadCatalogItem *item;

    assert(pad_catalog_load(fixture, sizeof(fixture) - 1, &catalog,
                            error, sizeof(error)));
    assert(catalog.item_count == 4);
    assert(catalog.items[0].item_id == 0);
    assert(catalog.items[0].tribe == PAD_TRIBE_NONE);
    assert(strcmp(catalog.items[0].shape_id, "noshape") == 0);
    assert(catalog.items[1].tribe == PAD_TRIBE_LEVIATHAN);
    assert(strcmp(catalog.items[1].shape_id, "v-shld0") == 0);
    assert(catalog.items[2].item_id == 2);
    assert(catalog.items[2].size == 0);
    assert(catalog.items[2].building_tone_cost == 35);
    assert(catalog.items[2].movement_cost[0] == 10);
    assert(catalog.items[2].movement_cost[1] == 0);
    assert(catalog.items[2].movement_cost[2] == 10);
    assert(catalog.items[2].maintenance_tone_cost == 1);
    assert(catalog.items[2].hit_points == 30);
    assert(catalog.items[2].tone_range_extension == 0);
    assert(strcmp(catalog.items[2].text_id, "BLDTON") == 0);
    assert(pad_catalog_find(&catalog, 2) == &catalog.items[2]);
    assert(pad_catalog_find(&catalog, 4) == NULL);
    assert(pad_catalog_count_for(&catalog, PAD_TRIBE_PROTECTOR, 0) == 1);
    assert(pad_catalog_count_for(&catalog, PAD_TRIBE_PROTECTOR, 1) == 0);
    item = pad_catalog_nth_for(&catalog, PAD_TRIBE_PROTECTOR, 0, 0);
    assert(item == &catalog.items[2]);
    assert(pad_catalog_nth_for(&catalog, PAD_TRIBE_PROTECTOR, 0, 1) == NULL);
    assert(pad_catalog_tribe_item_count(&catalog, PAD_TRIBE_PROTECTOR) == 2);
    assert(pad_catalog_tribe_item_at(&catalog, PAD_TRIBE_PROTECTOR, 0) == &catalog.items[2]);
    assert(pad_catalog_tribe_item_at(&catalog, PAD_TRIBE_PROTECTOR, 1) == &catalog.items[3]);
    assert(pad_catalog_tribe_item_at(&catalog, PAD_TRIBE_PROTECTOR, 2) == NULL);

    catalog.item_count = 17;
    assert(!pad_catalog_load(malformed, sizeof(malformed) - 1, &catalog,
                             error, sizeof(error)));
    assert(catalog.item_count == 17);
    assert(strstr(error, "line 1") != NULL);
    if (argc == 2) verify_local_corpus(argv[1]);
    else if (argc != 1) return 2;
    (void)puts("pad catalog tests passed");
    return 0;
}
