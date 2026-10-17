#include "cob_archive.h"
#include "island_data.h"
#include "shp_image.h"

#include <ctype.h>
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

static unsigned int starting_hall_frame_count(const char *name)
{
    if (strcmp(name, "data\\p-hall.shp") == 0 ||
        strcmp(name, "data\\s-hall.shp") == 0) return 3;
    if (strcmp(name, "data\\m-hall.shp") == 0 ||
        strcmp(name, "data\\l-hall.shp") == 0) return 4;
    return 0;
}

static int ascii_case_equal(const char *left, const char *right);

static int island_template_variant(const char *name)
{
    unsigned int variant;
    if (!ascii_case_equal(name, "data\\isletmp0.shp") &&
        !ascii_case_equal(name, "data\\isletmp1.shp") &&
        !ascii_case_equal(name, "data\\isletmp2.shp") &&
        !ascii_case_equal(name, "data\\isletmp3.shp")) return -1;
    for (variant = 0; variant < 4; ++variant) {
        char expected[32];
        (void)snprintf(expected, sizeof(expected), "data\\isletmp%u.shp", variant);
        if (ascii_case_equal(name, expected)) return (int)variant;
    }
    return -1;
}

static int initial_worker_shape_kind(const char *name)
{
    static const char *const body_names[4] = {
        "data\\pbod.shp", "data\\sbod.shp", "data\\mbod.shp", "data\\lbod.shp"
    };
    static const char *const leg_names[4] = {
        "data\\plegs.shp", "data\\slegs.shp", "data\\mlegs.shp", "data\\llegs.shp"
    };
    unsigned int i;
    for (i = 0; i < 4; ++i) {
        if (ascii_case_equal(name, body_names[i])) return 1;
        if (ascii_case_equal(name, leg_names[i])) return 2;
    }
    return 0;
}

static int is_newgame_button_sheet(const char *name)
{
    return ascii_case_equal(name, "data\\ngmeintr.shp");
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

static int ascii_case_equal(const char *left, const char *right)
{
    while (*left != '\0' && *right != '\0') {
        if (tolower((unsigned char)*left) != tolower((unsigned char)*right)) return 0;
        ++left;
        ++right;
    }
    return *left == *right;
}

static int manifest_contains(char names[][64], size_t name_count, const char *name)
{
    size_t i;
    for (i = 0; i < name_count; ++i) {
        if (ascii_case_equal(names[i], name)) return 1;
    }
    return 0;
}

static unsigned int island_ui_frame_requirement(const char *name)
{
    if (ascii_case_equal(name, "data\\thall0.shp")) return 10;
    if (ascii_case_equal(name, "data\\thbutt.shp")) return 6;
    if (ascii_case_equal(name, "data\\temphol0.shp")) return 8;
    if (ascii_case_equal(name, "data\\glinv.shp")) return 29;
    if (ascii_case_equal(name, "data\\trade.shp")) return 4;
    if (ascii_case_equal(name, "data\\bildtone.shp") ||
        ascii_case_equal(name, "data\\tonecrys.shp") ||
        ascii_case_equal(name, "data\\magctone.shp")) return 5;
    if (ascii_case_equal(name, "data\\alltrigs.shp")) return 29;
    if (ascii_case_equal(name, "data\\diploma.shp")) return 24;
    if (ascii_case_equal(name, "data\\fltinfo.shp")) return 26;
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
    unsigned int halls_found = 0;
    unsigned int floater_body_sheets_found = 0;
    unsigned int floater_leg_sheets_found = 0;
    unsigned int island_template_sheets_found = 0;
    unsigned int island_ui_sheets_found = 0;
    unsigned int health_badge_frames_found = 0;
    unsigned int realm_badge_frames_found = 0;
    unsigned int newgame_footer_frames_found = 0;
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
            (manifest_contains(shape_names, shape_name_count, member->name) ||
             island_template_variant(member->name) >= 0)) {
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
            {
                unsigned int required_ui_frames =
                    island_ui_frame_requirement(member->name);
                if (required_ui_frames != 0) {
                    if (shp.frame_count < required_ui_frames) {
                        (void)fprintf(stderr,
                                      "%s: expected at least %u UI frames, found %u\n",
                                      member->name, required_ui_frames,
                                      (unsigned)shp.frame_count);
                        free(bytes);
                        cob_archive_close(&archive);
                        return 1;
                    }
                    ++island_ui_sheets_found;
                }
            }
            if (island_template_variant(member->name) >= 0) {
                ShpFrame frame;
                if (shp.frame_count != 1 ||
                    !shp_decode_frame(&shp, 0, &frame, error, sizeof(error))) {
                    (void)fprintf(stderr,
                                  "%s: expected one decodable tribe-specific template frame: %s\n",
                                  member->name, error);
                    free(bytes);
                    cob_archive_close(&archive);
                    return 1;
                }
                if (frame.width != 640 || frame.height != 160) {
                    (void)fprintf(stderr,
                                  "%s: expected 640x160 frame, found %ux%u\n",
                                  member->name, (unsigned)frame.width,
                                  (unsigned)frame.height);
                    shp_frame_free(&frame);
                    free(bytes);
                    cob_archive_close(&archive);
                    return 1;
                }
                shp_frame_free(&frame);
                ++island_template_sheets_found;
            }
            {
                unsigned int required_hall_frames = starting_hall_frame_count(member->name);
                if (required_hall_frames != 0) {
                    if (shp.frame_count < required_hall_frames) {
                    (void)fprintf(stderr,
                                      "%s: expected at least %u BASE frames, found %u\n",
                                      member->name, required_hall_frames,
                                      (unsigned)shp.frame_count);
                        free(bytes);
                        cob_archive_close(&archive);
                        return 1;
                    }
                    ++halls_found;
                }
            }
            {
                int worker_shape_kind = initial_worker_shape_kind(member->name);
                if (worker_shape_kind == 1) {
                    if (shp.frame_count < 1) {
                        (void)fprintf(stderr, "%s: missing base-worker body frame 0\n",
                                      member->name);
                        free(bytes);
                        cob_archive_close(&archive);
                        return 1;
                    }
                    ++floater_body_sheets_found;
                } else if (worker_shape_kind == 2) {
                    if (shp.frame_count < 16) {
                        (void)fprintf(stderr, "%s: missing hover frames 0..15\n",
                                      member->name);
                        free(bytes);
                        cob_archive_close(&archive);
                        return 1;
                    }
                    ++floater_leg_sheets_found;
                }
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
                if (ascii_case_equal(member->name, "data\\fltinfo.shp") &&
                    frame_index == 18) {
                    size_t pixel;
                    size_t opaque_pixels = 0;
                    for (pixel = 0; pixel < (size_t)frame.width * frame.height;
                         ++pixel) {
                        if (frame.opaque[pixel]) ++opaque_pixels;
                    }
                    if (frame.width != 5 || frame.height != 12 || opaque_pixels == 0) {
                        (void)fprintf(stderr,
                                      "%s frame 18: expected a visible 5x12 health badge\n",
                                      member->name);
                        shp_frame_free(&frame);
                        free(bytes);
                        cob_archive_close(&archive);
                        return 1;
                    }
                    ++health_badge_frames_found;
                }
                if (ascii_case_equal(member->name, "data\\fltinfo.shp") &&
                    frame_index >= 22 && frame_index <= 25) {
                    size_t pixel;
                    size_t opaque_pixels = 0;
                    for (pixel = 0; pixel < (size_t)frame.width * frame.height;
                         ++pixel) {
                        if (frame.opaque[pixel]) ++opaque_pixels;
                    }
                    if (frame.width == 0 || frame.height == 0 || opaque_pixels == 0) {
                        (void)fprintf(stderr,
                                      "%s frame %u: expected a visible realm badge\n",
                                      member->name, (unsigned)frame_index);
                        shp_frame_free(&frame);
                        free(bytes);
                        cob_archive_close(&archive);
                        return 1;
                    }
                    ++realm_badge_frames_found;
                }
                if (is_newgame_button_sheet(member->name) && frame_index == 0) {
                    size_t pixel;
                    size_t opaque_pixels = 0;
                    for (pixel = 0; pixel < (size_t)frame.width * frame.height;
                         ++pixel) {
                        if (frame.opaque[pixel]) ++opaque_pixels;
                    }
                    if (frame.width != 640 || frame.height != 73 ||
                        frame.y_offset != 407 || opaque_pixels == 0) {
                        (void)fprintf(stderr,
                                      "%s frame 0: expected the 640x73 footer overlay at y=407\n",
                                      member->name);
                        shp_frame_free(&frame);
                        free(bytes);
                        cob_archive_close(&archive);
                        return 1;
                    }
                    ++newgame_footer_frames_found;
                }
                shp_frame_free(&frame);
                ++frames_decoded;
            }
            free(bytes);
            ++shapes_found;
        }
    }

    if (shapes_found == 0 || halls_found != 4 || island_template_sheets_found != 4 ||
        island_ui_sheets_found != 11 ||
        health_badge_frames_found != 1 ||
        realm_badge_frames_found != 4 ||
        newgame_footer_frames_found != 1 ||
        floater_body_sheets_found != 4 || floater_leg_sheets_found != 4 ||
        cob_archive_find(&archive, "data\\br-trg01.shp") == NULL ||
        !manifest_contains(shape_names, shape_name_count, "data\\br-trg01.shp")) {
        (void)fprintf(stderr,
                      "expected Hall/UI and Trade resource sheets, the New Game footer overlay, four tribe templates, four worker bodies, four worker leg sheets, and manifested data\\br-trg01.shp\n");
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
    (void)printf("decoded %u SHP sheets (%u frames), including island UI sheets\n", shapes_found,
                 frames_decoded);
    return 0;
}
