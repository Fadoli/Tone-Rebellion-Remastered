#include "game_glyph_inventory.h"
#include "island_panel_info.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    GameGlyphCenter centers[GAME_GLYPH_COUNT] = {{0, 0}};
    char key[16];
    assert(game_glyph_inventory_frame(0, 0, -1) == UINT32_MAX);
    assert(game_glyph_inventory_frame(1U, 0, -1) == 1U);
    assert(game_glyph_inventory_frame(1U, 0, 0) == 15U);
    assert(game_glyph_inventory_frame(0x2000U, 13, 13) == 28U);
    assert(game_glyph_inventory_frame(0x2000U, 12, 13) == UINT32_MAX);
    assert(game_glyph_inventory_frame(1U, 14, -1) == UINT32_MAX);
    centers[0].x = 40;
    centers[0].y = 50;
    centers[13].x = 120;
    centers[13].y = 50;
    assert(game_glyph_inventory_hit_test(1U, centers, 40, 50) == 0);
    assert(game_glyph_inventory_hit_test(1U, centers, 55, 64) == 0);
    assert(game_glyph_inventory_hit_test(1U, centers, 56, 50) == -1);
    assert(game_glyph_inventory_hit_test(0x2000U, centers, 120, 50) == 13);
    assert(game_glyph_inventory_hit_test(0x2000U, centers, 40, 50) == -1);
    assert(game_glyph_inventory_hit_test(0, centers, 40, 50) == -1);
    assert(game_glyph_inventory_hit_test(1U, NULL, 40, 50) == -1);
    assert(game_glyph_inventory_key(0, key, sizeof(key)));
    assert(strcmp(key, "GLYPH00") == 0);
    assert(game_glyph_inventory_key(13, key, sizeof(key)));
    assert(strcmp(key, "GLYPH13") == 0);
    assert(!game_glyph_inventory_key(14, key, sizeof(key)));

    if (argc > 1) {
        FILE *file = fopen(argv[1], "rb");
        unsigned char *bytes;
        long length;
        unsigned int glyph_index;
        assert(file != NULL);
        assert(fseek(file, 0, SEEK_END) == 0);
        length = ftell(file);
        assert(length >= 0);
        assert(fseek(file, 0, SEEK_SET) == 0);
        bytes = (unsigned char *)malloc((size_t)length);
        assert(bytes != NULL || length == 0);
        assert(fread(bytes, 1, (size_t)length, file) == (size_t)length);
        assert(fclose(file) == 0);
        for (glyph_index = 0; glyph_index < GAME_GLYPH_COUNT; ++glyph_index) {
            char description[768];
            assert(game_glyph_inventory_key(glyph_index, key, sizeof(key)));
            assert(island_panel_info_extract_entry(bytes, (size_t)length, key,
                                                   description,
                                                   sizeof(description)));
            assert(description[0] != '\0');
        }
        free(bytes);
    }
    return 0;
}
