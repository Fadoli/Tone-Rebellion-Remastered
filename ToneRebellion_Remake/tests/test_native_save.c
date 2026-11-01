#include "native_save.h"
#include "floater_catalog.h"

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

/* A worker saved mid-crossing (state 0x11) on its CONSTR task: FUN_004210a9
   kept +0x3c/+0x38/+0x40/+0x42/+0x46, so the port resumes the crossing and
   replans the next leg on arrival (resume action 4, state 0). */
static GameSession crossing_session;
static FloaterCatalog crossing_catalog;

static void test_crossing_worker_resumes_its_task(uint16_t step)
{
    size_t size;
    uint8_t *data = build_save(2, 2, &size);
    NativeSave save;
    uint8_t *event;
    uint8_t *rec;
    const GameFloaterStart *worker;
    unsigned int slot;
    char error[96] = "";

    assert(native_save_parse(data, size, &save, error, sizeof(error)));
    for (slot = 0; slot < FLOATER_SLOTS; ++slot)
        put32(data + save.floater_offset + (size_t)slot * FLOATER_RECORD,
              0xffffffffU);
    event = data + save.stream2_offset + STREAM2_SCALARS + 3U * 0x14U;
    put32(event, 1);
    put16(event + 0x06, 1);    /* priority */
    put16(event + 0x08, 0);    /* player */
    put16(event + 0x0a, 1);    /* island */
    put16(event + 0x0e, 0);    /* site */
    put16(event + 0x10, 5);    /* CONSTR */
    put16(event + 0x12, 0x25);
    rec = data + save.floater_offset;
    put32(rec, 0);             /* owner */
    put32(rec + 4, 0);         /* subtype: worker */
    put16(rec + 0x0e, 0);      /* island */
    put16(rec + 0x10, 120);
    put16(rec + 0x12, 90);
    put16(rec + 0x18, 1);      /* carries Build Tone */
    put32(rec + 0x2c, 0x11);
    put16(rec + 0x30, 1);      /* crossing toward island 1 */
    put16(rec + 0x32, 1);      /* departure site */
    put16(rec + 0x34, 30);
    put32(rec + 0x38, 3);      /* task slot */
    put32(rec + 0x3c, 5);
    put16(rec + 0x40, 1);
    put16(rec + 0x42, 0);
    put16(rec + 0x44, 0x25);
    put16(rec + 0x46, step);

    memset(&crossing_session, 0, sizeof(crossing_session));
    memset(&crossing_catalog, 0, sizeof(crossing_catalog));
    crossing_session.island_count = 2;
    crossing_session.islands[0].location_count = 2;
    crossing_session.islands[1].location_count = 2;
    assert(native_save_apply(&save, &crossing_catalog, &crossing_session,
                             error, sizeof(error)));
    worker = &crossing_session.floaters[0];
    assert(worker->movement_state == 0x11);
    assert(worker->active_order_action == 9);
    assert(worker->linked_task_slot == 3);
    assert(crossing_session.pending_events[3].assigned_floater_count == 1);
    assert(worker->handoff_target_island == 1);
    assert(worker->handoff_departure_location == 1);
    assert(worker->handoff_resume_action == 4);
    assert(worker->handoff_resume_state == 0);
    assert(worker->order_target_island == 1);
    assert(worker->order_target_location == 0);
    assert(worker->task_step == (int32_t)(int16_t)step);
    assert(worker->order_timer == 30);
    free(data);
}

int main(void)
{
    test_valid_save_reports_header_and_offsets();
    test_bad_header_is_rejected();
    test_island_and_site_counts_are_range_checked();
    test_every_truncation_is_rejected_without_overread();
    test_find_world_matches_island_count();
    test_crossing_worker_resumes_its_task(0);
    test_crossing_worker_resumes_its_task(1);
    (void)puts("native save unit tests passed");
    return 0;
}
