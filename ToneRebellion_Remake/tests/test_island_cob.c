#include "cob_archive.h"
#include "island_data.h"

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

int main(int argc, char **argv)
{
    CobArchive archive = {0};
    char error[256];
    uint32_t i;
    unsigned int files_found = 0;
    unsigned int records_found = 0;

    if (argc != 2) {
        (void)fprintf(stderr, "usage: test_island_cob <TONE01.COB>\n");
        return 2;
    }
    if (!cob_archive_open(argv[1], &archive, error, sizeof(error))) {
        (void)fprintf(stderr, "could not open COB: %s\n", error);
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
    return 0;
}
