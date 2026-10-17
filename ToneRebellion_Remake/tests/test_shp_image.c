#include "shp_image.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* Three frame records occupy bytes 8..31, so frame payload starts at 32. */
enum { TEST_FRAME_DATA_OFFSET = 32, TEST_EMPTY_FRAME_OFFSET = 59,
       TEST_FILE_LENGTH = 83 };

static void write_u32(uint8_t *destination, uint32_t value)
{
    destination[0] = (uint8_t)value;
    destination[1] = (uint8_t)(value >> 8);
    destination[2] = (uint8_t)(value >> 16);
    destination[3] = (uint8_t)(value >> 24);
}

static void write_frame_header(uint8_t *frame, uint32_t right, uint32_t bottom)
{
    /* The leading frame words are zero in some valid shipped sheets. */
    memset(frame, 0, 24);
    write_u32(frame + 16, right);
    write_u32(frame + 20, bottom);
}

static void test_shared_offsets_and_empty_frame(void)
{
    uint8_t bytes[TEST_FILE_LENGTH] = {0};
    ShpFile shp;
    ShpFrame first;
    ShpFrame alias;
    ShpFrame empty;
    char error[160];

    memcpy(bytes, "1.10", 4);
    write_u32(bytes + 4, 3);
    write_u32(bytes + 8, TEST_FRAME_DATA_OFFSET);
    write_u32(bytes + 16, TEST_FRAME_DATA_OFFSET);
    write_u32(bytes + 24, TEST_EMPTY_FRAME_OFFSET);
    write_frame_header(bytes + TEST_FRAME_DATA_OFFSET, 1, 0);
    bytes[TEST_FRAME_DATA_OFFSET + 24] = 3; /* One literal pixel. */
    bytes[TEST_FRAME_DATA_OFFSET + 25] = 42;
    bytes[TEST_FRAME_DATA_OFFSET + 26] = 0; /* End the row. */
    write_frame_header(bytes + TEST_EMPTY_FRAME_OFFSET, 1, 0);

    assert(shp_file_init(&shp, bytes, sizeof(bytes), error, sizeof(error)));
    assert(shp.frame_count == 3);
    assert(shp_decode_frame(&shp, 0, &first, error, sizeof(error)));
    assert(shp_decode_frame(&shp, 1, &alias, error, sizeof(error)));
    assert(shp_decode_frame(&shp, 2, &empty, error, sizeof(error)));
    assert(first.width == 2 && first.height == 1);
    assert(alias.width == first.width && alias.height == first.height);
    assert(first.pixels[0] == 42 && first.opaque[0] == 1);
    assert(alias.pixels[0] == 42 && alias.opaque[0] == 1);
    assert(empty.width == 2 && empty.height == 1);
    assert(empty.opaque[0] == 0 && empty.opaque[1] == 0);
    shp_frame_free(&first);
    shp_frame_free(&alias);
    shp_frame_free(&empty);
}

int main(void)
{
    test_shared_offsets_and_empty_frame();
    (void)puts("SHP frame decoding tests passed");
    return 0;
}
