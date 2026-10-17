#include "cob_archive.h"
#include "island_data.h"
#include "shp_image.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_island_text(const char *name)
{
    const char *base = strrchr(name, '\\');
    if (base == NULL) base = name;
    else ++base;
    return strncmp(base, "island", 6) == 0 &&
           strlen(base) == 12 &&
           base[6] >= '0' && base[6] <= '9' &&
           base[7] >= '0' && base[7] <= '9' &&
           strcmp(base + 8, ".txt") == 0;
}

static int is_shp_member(const char *name)
{
    size_t length = strlen(name);
    const char *extension;
    if (length < 4) return 0;
    extension = name + length - 4;
    return extension[0] == '.' &&
           (extension[1] == 's' || extension[1] == 'S') &&
           (extension[2] == 'h' || extension[2] == 'H') &&
           (extension[3] == 'p' || extension[3] == 'P');
}

static int read_shape_manifest(const char *content_dir,
                               char names[][64], size_t capacity,
                               size_t *name_count)
{
    char path[1024];
    char line[256];
    FILE *file;
    int path_length;

    path_length = snprintf(path, sizeof(path), "%s\\shapes.txt", content_dir);
    if (path_length < 0 || (size_t)path_length >= sizeof(path)) return 0;
    file = fopen(path, "rb");
    if (file == NULL) return 0;
    *name_count = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        char member_name[64];
        size_t length;
        if (sscanf(line, "%63s", member_name) != 1 || !is_shp_member(member_name)) continue;
        length = strlen(member_name);
        if (length >= sizeof(names[0]) || *name_count == capacity) {
            fclose(file);
            return 0;
        }
        memcpy(names[*name_count], member_name, length + 1);
        ++*name_count;
    }
    fclose(file);
    return *name_count != 0;
}

static int manifest_contains(char names[][64], size_t name_count, const char *name)
{
    size_t i;
    for (i = 0; i < name_count; ++i) {
        if (strcmp(names[i], name) == 0) return 1;
    }
    return 0;
}

int main(int argc, char **argv)
{
    CobArchive archive = {0};
    char error[256];
    uint32_t i;
    unsigned int files_found = 0;
    unsigned int records_found = 0;
    unsigned int shapes_found = 0;
    unsigned int frames_decoded = 0;
    char shape_names[512][64];
    size_t shape_name_count = 0;

    if (argc != 3) {
        (void)fprintf(stderr, "usage: test_island_cob <TONE01.COB> <original_content_dir>\n");
        return 2;
    }
    if (!read_shape_manifest(argv[2], shape_names,
                             sizeof(shape_names) / sizeof(shape_names[0]),
                             &shape_name_count)) {
        (void)fprintf(stderr, "could not read SHP manifest from original content\n");
        return 1;
    }
    if (!cob_archive_open(argv[1], &archive, error, sizeof(error))) {
        (void)fprintf(stderr, "could not open COB: %s\n", error);
        return 1;
    }

    for (i = 0; i < archive.member_count; ++i) {
        const CobMember *member = cob_archive_member_at(&archive, i);
        unsigned char *bytes;
        if (is_shp_member(member->name) &&
            manifest_contains(shape_names, shape_name_count, member->name)) {
            ShpFile shp;
            uint32_t frame_index;
            bytes = (unsigned char *)malloc(member->length == 0 ? 1U : member->length);
            if (bytes == NULL ||
                !cob_archive_read_member(&archive, member, bytes, member->length,
                                         error, sizeof(error)) ||
                !shp_file_init(&shp, bytes, member->length,
                               error, sizeof(error))) {
                (void)fprintf(stderr, "%s: %s\n", member->name,
                              bytes == NULL ? "out of memory" : error);
                free(bytes);
                cob_archive_close(&archive);
                return 1;
            }
            if (strcmp(member->name, "data\\tone.shp") == 0 &&
                shp.frame_count != 40) {
                (void)fprintf(stderr, "data\\tone.shp: expected 40 POOL frames, found %u\n",
                              (unsigned)shp.frame_count);
                free(bytes);
                cob_archive_close(&archive);
                return 1;
            }
            for (frame_index = 0; frame_index < shp.frame_count; ++frame_index) {
                ShpFrame frame;
                if (!shp_decode_frame(&shp, frame_index, &frame,
                                      error, sizeof(error))) {
                    (void)fprintf(stderr, "%s frame %u: %s\n", member->name,
                                  (unsigned)frame_index, error);
                    free(bytes);
                    cob_archive_close(&archive);
                    return 1;
                }
                shp_frame_free(&frame);
                ++frames_decoded;
            }
            free(bytes);
            ++shapes_found;
        }
    }

    if (shapes_found == 0 || cob_archive_find(&archive, "data\\br-trg01.shp") == NULL ||
        !manifest_contains(shape_names, shape_name_count, "data\\br-trg01.shp")) {
        (void)fprintf(stderr, "expected manifested SHP members including data\\br-trg01.shp\n");
        cob_archive_close(&archive);
        return 1;
    }

    for (i = 0; i < archive.member_count; ++i) {
        const CobMember *member = cob_archive_member_at(&archive, i);
        unsigned char *bytes;
        IslandData data;

        if (!is_island_text(member->name)) continue;
        bytes = (unsigned char *)malloc(member->length == 0 ? 1U : member->length);
        if (bytes == NULL ||
            !cob_archive_read_member(&archive, member, bytes, member->length,
                                     error, sizeof(error))) {
            (void)fprintf(stderr, "%s: %s\n", member->name,
                          bytes == NULL ? "out of memory" : error);
            free(bytes);
            cob_archive_close(&archive);
            return 1;
        }
        if (!island_data_load(bytes, member->length, &data, error, sizeof(error))) {
            (void)fprintf(stderr, "%s: %s\n", member->name, error);
            free(bytes);
            cob_archive_close(&archive);
            return 1;
        }
        records_found += data.location_count;
        ++files_found;
        free(bytes);
    }

    cob_archive_close(&archive);
    if (files_found == 0) {
        (void)fprintf(stderr, "no island text members found in COB\n");
        return 1;
    }
    (void)printf("parsed %u island COB members (%u location rows)\n",
                 files_found, records_found);
    (void)printf("decoded %u SHP sheets (%u frames)\n", shapes_found,
                 frames_decoded);
    return 0;
}
