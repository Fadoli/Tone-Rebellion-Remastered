#include "native_save.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Layout constants mirror native_save.c (behavior/save-format.md). */
enum {
    HEADER_SIZE = 0x80,
    STREAM1_SIZE = 0x148,
    STREAM2_SCALARS = 15 * 4,
    STREAM2_BLOBS = 0x500 + 0x100 + 0x100 + 3 * 0x1e,
    ISLAND_SCALARS = 4 * 4,
    ISLAND_BLOBS = 8 + 0x400 + 0x20 + 0x10 + 0x10 + 0xc,
    SITE_RECORD = 0x60,
    PLAYER_RECORD = 0x14a0,
    GLOBAL_BLOCK = 0x1614,
    FLOATER_RECORD = 0x4c,
    FLOATER_SLOTS = 0x100,
    STREAM3_SIZE = 4 + 0x280
};

static void put16(uint8_t *p, uint16_t v) { p[0] = (uint8_t)v; p[1] = (uint8_t)(v >> 8); }
static void put32(uint8_t *p, uint32_t v) { put16(p, (uint16_t)v); put16(p + 2, (uint16_t)(v >> 16)); }

/* Builds a valid zero-filled save with `islands` islands of `sites` sites. */
static uint8_t *build_save(unsigned int islands, unsigned int sites, size_t *size)
{
    size_t total = HEADER_SIZE + 12U + STREAM1_SIZE + STREAM2_SCALARS +
        STREAM2_BLOBS + (size_t)islands * (ISLAND_SCALARS + ISLAND_BLOBS +
        (size_t)sites * SITE_RECORD) + 4U * PLAYER_RECORD + GLOBAL_BLOCK +
        (size_t)FLOATER_SLOTS * FLOATER_RECORD + STREAM3_SIZE;
    uint8_t *data = calloc(total, 1);
    size_t cursor;
    unsigned int island;
    assert(data != NULL);
    memcpy(data, "1.16", 4);
    put32(data + 0x7c, 0x000378b8U);
    put32(data + HEADER_SIZE, 1);     /* mode */
    put32(data + HEADER_SIZE + 4, 3); /* tribe */
    put32(data + HEADER_SIZE + 8, 9);
    cursor = HEADER_SIZE + 12U + STREAM1_SIZE;
    put16(data + cursor, (uint16_t)islands);
    cursor += STREAM2_SCALARS + STREAM2_BLOBS;
    for (island = 0; island < islands; ++island) {
        put16(data + cursor, (uint16_t)sites);
        cursor += ISLAND_SCALARS + ISLAND_BLOBS + (size_t)sites * SITE_RECORD;
    }
    *size = total;
    return data;
}

static void test_valid_save_reports_header_and_offsets(void)
{
    size_t size;
    uint8_t *data = build_save(3, 2, &size);
    NativeSave save;
    char error[96] = "";
    size_t island_span = ISLAND_SCALARS + ISLAND_BLOBS + 2U * SITE_RECORD;

    assert(native_save_parse(data, size, &save, error, sizeof(error)));
    assert(save.mode == 1 && save.tribe == 3 && save.value_8c == 9);
    assert(save.island_count == 3);
    assert(save.site_count[0] == 2 && save.site_count[2] == 2);
    assert(save.island_offset[1] - save.island_offset[0] == island_span);
    assert(save.site_offset[0] == save.island_offset[0] + ISLAND_SCALARS +
                                      ISLAND_BLOBS);
    assert(save.global_offset - save.player_offset == 4U * PLAYER_RECORD);
    assert(save.floater_offset - save.global_offset == GLOBAL_BLOCK);
    assert(save.floater_offset + (size_t)FLOATER_SLOTS * FLOATER_RECORD +
               STREAM3_SIZE == size);
    free(data);
}

static void test_bad_header_is_rejected(void)
{
    size_t size;
    uint8_t *data = build_save(1, 0, &size);
    NativeSave save;
    char error[96];

    data[0] = '2';
    assert(!native_save_parse(data, size, &save, error, sizeof(error)));
    assert(error[0] != '\0');
    data[0] = '1';
    put32(data + 0x7c, 0);
    assert(!native_save_parse(data, size, &save, error, sizeof(error)));
    assert(!native_save_parse(NULL, size, &save, error, sizeof(error)));
    assert(!native_save_parse(data, 16, &save, error, sizeof(error)));
    free(data);
}

static void test_island_and_site_counts_are_range_checked(void)
{
    size_t size;
    uint8_t *data = build_save(1, 0, &size);
    NativeSave save;
    char error[96];
    size_t count_at = HEADER_SIZE + 12U + STREAM1_SIZE;

    put16(data + count_at, 0);
    assert(!native_save_parse(data, size, &save, error, sizeof(error)));
    put16(data + count_at, NATIVE_SAVE_MAX_ISLANDS + 1);
    assert(!native_save_parse(data, size, &save, error, sizeof(error)));
    put16(data + count_at, 1);
    put16(data + count_at + STREAM2_SCALARS + STREAM2_BLOBS, 0xffff);
    assert(!native_save_parse(data, size, &save, error, sizeof(error)));
    free(data);
}

static void test_every_truncation_is_rejected_without_overread(void)
{
    size_t size;
    uint8_t *data = build_save(2, 3, &size);
    NativeSave save;
    char error[96];
    size_t cut;

    assert(native_save_parse(data, size, &save, error, sizeof(error)));
    /* Exact-size copies let sanitizers/valgrind flag any read past the end. */
    for (cut = 0; cut < size; cut += 97) {
        uint8_t *copy = malloc(cut == 0 ? 1U : cut);
        assert(copy != NULL);
        if (cut != 0) memcpy(copy, data, cut);
        assert(!native_save_parse(copy, cut, &save, error, sizeof(error)));
        free(copy);
    }
    assert(!native_save_parse(data, size - 1U, &save, error, sizeof(error)));
    free(data);
}

static void test_find_world_matches_island_count(void)
{
    size_t size;
    uint8_t *data = build_save(2, 0, &size);
    NativeSave save;
    WorldMap worlds;

    assert(native_save_parse(data, size, &save, NULL, 0));
    memset(&worlds, 0, sizeof(worlds));
    worlds.world_count = 3;
    worlds.worlds[0].island_count = 1;
    worlds.worlds[1].island_count = 4;
    worlds.worlds[2].island_count = 2;
    assert(native_save_find_world(&save, &worlds) == 2);
    worlds.worlds[2].island_count = 5;
    assert(native_save_find_world(&save, &worlds) == -1);
    assert(native_save_find_world(NULL, &worlds) == -1);
    free(data);
}

int main(void)
{
    test_valid_save_reports_header_and_offsets();
    test_bad_header_is_rejected();
    test_island_and_site_counts_are_range_checked();
    test_every_truncation_is_rejected_without_overread();
    test_find_world_matches_island_count();
    (void)puts("native save unit tests passed");
    return 0;
}
