#include "island_data.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned char *read_file(const char *path, size_t *length)
{
    FILE *file = fopen(path, "rb");
    long file_length;
    unsigned char *bytes;

    if (file == NULL) return NULL;
    if (fseek(file, 0, SEEK_END) != 0 || (file_length = ftell(file)) < 0 ||
        fseek(file, 0, SEEK_SET) != 0) {
        fclose(file);
        return NULL;
    }
    bytes = (unsigned char *)malloc(file_length == 0 ? 1U : (size_t)file_length);
    if (bytes == NULL || fread(bytes, 1, (size_t)file_length, file) !=
                         (size_t)file_length) {
        free(bytes);
        fclose(file);
        return NULL;
    }
    fclose(file);
    *length = (size_t)file_length;
    return bytes;
}

int main(int argc, char **argv)
{
    unsigned int island_id;
    unsigned int files_found = 0;
    unsigned int records_found = 0;

    if (argc != 2) {
        (void)fprintf(stderr, "usage: test_island_corpus <original_content_directory>\n");
        return 2;
    }

    for (island_id = 0; island_id < 100; ++island_id) {
        char path[1024];
        size_t length = 0;
        unsigned char *bytes;
        IslandData data;
        char error[256];
        int written = snprintf(path, sizeof(path), "%s/ISLAND%02u.TXT",
                              argv[1], island_id);

        if (written < 0 || (size_t)written >= sizeof(path)) {
            (void)fprintf(stderr, "content directory path is too long\n");
            return 2;
        }
        bytes = read_file(path, &length);
        if (bytes == NULL) continue;
        ++files_found;
        if (!island_data_load(bytes, length, &data, error, sizeof(error))) {
            (void)fprintf(stderr, "%s: %s\n", path, error);
            free(bytes);
            return 1;
        }
        records_found += data.location_count;
        free(bytes);
    }

    if (files_found == 0) {
        (void)fprintf(stderr, "no ISLANDnn.TXT files found in %s\n", argv[1]);
        return 1;
    }
    (void)printf("parsed %u island files (%u location rows)\n",
                 files_found, records_found);
    return 0;
}
