#include "world_map.h"
#include "cob_archive.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    WorldMap map;
    char error[256];
    unsigned char *member_data = NULL;
    CobArchive archive = {0};
    size_t world_index;

    if (argc != 2 && argc != 4) {
        (void)fprintf(stderr,
                      "usage: remake_inspect_worlds <worldpos.txt>\n"
                      "   or: remake_inspect_worlds --cob <archive.cob> <member-name>\n");
        return 2;
    }
    if (argc == 4 && strcmp(argv[1], "--cob") == 0) {
        const CobMember *member;
        if (!cob_archive_open(argv[2], &archive, error, sizeof(error))) {
            (void)fprintf(stderr, "could not open COB archive: %s\n", error);
            return 1;
        }
        member = cob_archive_find(&archive, argv[3]);
        if (member == NULL) {
            (void)fprintf(stderr, "COB member not found: %s\n", argv[3]);
            cob_archive_close(&archive);
            return 1;
        }
        member_data = (unsigned char *)malloc(member->length == 0 ? 1 : member->length);
        if (member_data == NULL ||
            !cob_archive_read_member(&archive, member, member_data, member->length,
                                     error, sizeof(error)) ||
            !world_map_load_data(member_data, member->length, &map, error, sizeof(error))) {
            (void)fprintf(stderr, "could not parse COB world data: %s\n", error);
            free(member_data);
            cob_archive_close(&archive);
            return 1;
        }
        free(member_data);
        cob_archive_close(&archive);
    } else if (argc == 2 && !world_map_load_file(argv[1], &map, error, sizeof(error))) {
        (void)fprintf(stderr, "could not load world data: %s\n", error);
        return 1;
    } else if (argc != 2) {
        (void)fprintf(stderr, "invalid arguments; use --help syntax shown above\n");
        return 2;
    }

    (void)printf("worlds: %u\n", (unsigned)map.world_count);
    for (world_index = 0; world_index < map.world_count; ++world_index) {
        const WorldDefinition *world = &map.worlds[world_index];
        size_t island_index;
        size_t bridge_index;

        (void)printf("world[%zu]: islands=%u bridges=%u\n", world_index,
                     (unsigned)world->island_count, (unsigned)world->bridge_count);
        for (island_index = 0; island_index < world->island_count; ++island_index) {
            const WorldIsland *island = &world->islands[island_index];
            (void)printf("  island[%zu]: angle=%" PRId32 " range=%" PRId32
                         " z=%" PRId32 " shape=%" PRId32 "\n",
                         island_index, island->angle_degrees, island->range,
                         island->z, island->shape_id);
        }
        for (bridge_index = 0; bridge_index < world->bridge_count; ++bridge_index) {
            const WorldBridge *bridge = &world->bridges[bridge_index];
            (void)printf("  bridge[%zu]: %u-%u\n", bridge_index,
                         (unsigned)bridge->island_a, (unsigned)bridge->island_b);
        }
    }
    return 0;
}
