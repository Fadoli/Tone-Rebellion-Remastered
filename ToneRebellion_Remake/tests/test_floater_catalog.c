#include "floater_catalog.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned char fixture[4096];

static void test_fixture_and_lookup(void)
{
    FloaterCatalog catalog;
    char error[128];
    size_t length = 0;
    unsigned int i;

    for (i = 0; i < FLOATER_CATALOG_ROW_COUNT; ++i) {
        int written = snprintf((char *)fixture + length, sizeof(fixture) - length,
            "unit%u 0 0 3 0 0 3\n", i);
        assert(written > 0 && (size_t)written < sizeof(fixture) - length);
        length += (size_t)written;
    }
    assert(floater_catalog_load(fixture, length, &catalog, error, sizeof(error)));
    assert(catalog.rows[0].attack_range == 0 && catalog.rows[0].hit_points == 3);
    assert(catalog.rows[8].movement_speed == 3);
    assert(floater_catalog_find(&catalog, 0, 0) == &catalog.rows[0]);
    assert(floater_catalog_find(&catalog, 3, 0) == &catalog.rows[27]);
    assert(floater_catalog_find(&catalog, 4, 0) == &catalog.rows[27]);
    assert(floater_catalog_find(&catalog, 4, 17) == &catalog.rows[44]);
    assert(floater_catalog_find(&catalog, 4, 18) == NULL);
    assert(floater_catalog_find(&catalog, 0, 9) == NULL);
    assert(floater_catalog_find(NULL, 0, 0) == NULL);
}

static void test_rejects_bad_catalog_atomically(void)
{
    FloaterCatalog catalog;
    FloaterCatalog before;
    char error[128];
    static const unsigned char malformed[] = "unit 0 0 0 3 0 0 nope\n";

    memset(&catalog, 0x5a, sizeof(catalog));
    before = catalog;
    assert(!floater_catalog_load(malformed, sizeof(malformed) - 1,
                                 &catalog, error, sizeof(error)));
    assert(memcmp(&catalog, &before, sizeof(catalog)) == 0);
    assert(error[0] != '\0');
    assert(!floater_catalog_load(NULL, 0, &catalog, error, sizeof(error)));
}

static unsigned char *read_file(const char *path, size_t *length)
{
    FILE *file = fopen(path, "rb");
    long file_length;
    size_t read_length;
    int close_status;
    unsigned char *bytes;
    if (file == NULL || fseek(file, 0, SEEK_END) != 0) return NULL;
    file_length = ftell(file);
    if (file_length < 0 || fseek(file, 0, SEEK_SET) != 0) {
        fclose(file);
        return NULL;
    }
    bytes = (unsigned char *)malloc(file_length == 0 ? 1U : (size_t)file_length);
    if (bytes == NULL) {
        fclose(file);
        return NULL;
    }
    read_length = fread(bytes, 1, (size_t)file_length, file);
    close_status = fclose(file);
    if (read_length != (size_t)file_length || close_status != 0) {
        free(bytes);
        return NULL;
    }
    *length = (size_t)file_length;
    return bytes;
}

static void test_local_corpus(const char *path)
{
    FloaterCatalog catalog;
    size_t length;
    unsigned char *bytes = read_file(path, &length);
    char error[128];
    unsigned int tribe;
    assert(bytes != NULL);
    if (!floater_catalog_load(bytes, length, &catalog, error, sizeof(error))) {
        (void)fprintf(stderr, "local floater.txt rejected: %s\n", error);
        assert(0);
    }
    for (tribe = 0; tribe < 4; ++tribe) {
        const FloaterStats *work = floater_catalog_find(&catalog, (int)tribe, 0);
        assert(work != NULL);
        assert(work->hit_points == 3);
        assert(work->attack_strength == 0);
        assert(work->movement_speed == 3);
    }
    free(bytes);
}

int main(int argc, char **argv)
{
    test_fixture_and_lookup();
    test_rejects_bad_catalog_atomically();
    if (argc > 1) test_local_corpus(argv[1]);
    return 0;
}
