#include "cob_archive.h"

#include <inttypes.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    CobArchive archive = {0};
    char error[256];
    uint32_t i;

    if (argc != 2) {
        (void)fprintf(stderr, "usage: remake_inspect_cob <archive.cob>\n");
        return 2;
    }
    if (!cob_archive_open(argv[1], &archive, error, sizeof(error))) {
        (void)fprintf(stderr, "could not read COB archive: %s\n", error);
        return 1;
    }
    (void)printf("members: %" PRIu32 "\n", archive.member_count);
    for (i = 0; i < archive.member_count; ++i) {
        const CobMember *member = cob_archive_member_at(&archive, i);
        (void)printf("%3" PRIu32 "  %10" PRIu32 "  %10" PRIu32 "  %s\n",
                     i, member->offset, member->length, member->name);
    }
    cob_archive_close(&archive);
    return 0;
}
