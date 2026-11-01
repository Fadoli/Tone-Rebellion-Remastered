#include "pe_cursor.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    RT_CURSOR_TYPE = 1,
    RT_GROUP_CURSOR_TYPE = 12,
    RESOURCE_DIRECTORY_ENTRY = 2 /* IMAGE_DIRECTORY_ENTRY_RESOURCE */
};

typedef struct PeView {
    const uint8_t *data;
    size_t size;
    const uint8_t *resources; /* start of .rsrc (resource directory root) */
    size_t resources_size;
    uint32_t resources_rva;
} PeView;

static uint16_t u16_at(const uint8_t *p)
{
    return (uint16_t)(p[0] | (p[1] << 8));
}

static uint32_t u32_at(const uint8_t *p)
{
    return (uint32_t)p[0] | ((uint32_t)p[1] << 8) | ((uint32_t)p[2] << 16) |
           ((uint32_t)p[3] << 24);
}

int pe_image_load(const char *path, uint8_t **data, size_t *size)
{
    FILE *file;
    long length;
    *data = NULL;
    *size = 0;
    file = fopen(path, "rb");
    if (file == NULL) return 0;
    if (fseek(file, 0, SEEK_END) != 0 || (length = ftell(file)) <= 0 ||
        fseek(file, 0, SEEK_SET) != 0) {
        (void)fclose(file);
        return 0;
    }
    *data = (uint8_t *)malloc((size_t)length);
    if (*data == NULL || fread(*data, 1, (size_t)length, file) != (size_t)length) {
        free(*data);
        *data = NULL;
        (void)fclose(file);
        return 0;
    }
    (void)fclose(file);
    *size = (size_t)length;
    return 1;
}

void pe_image_free(uint8_t *data)
{
    free(data);
}

/* Maps the resource directory through the section that holds its RVA. */
static int pe_view_open(const uint8_t *data, size_t size, PeView *view)
{
    uint32_t pe;
    uint16_t sections;
    uint16_t optional_size;
    uint16_t magic;
    uint32_t directory_offset;
    uint32_t rva;
    const uint8_t *section;
    unsigned int index;
    if (size < 0x40 || data[0] != 'M' || data[1] != 'Z') return 0;
    pe = u32_at(data + 0x3c);
    if (pe > size - 24U || memcmp(data + pe, "PE\0\0", 4) != 0) return 0;
    sections = u16_at(data + pe + 6);
    optional_size = u16_at(data + pe + 20);
    if ((size_t)pe + 24U + optional_size + (size_t)sections * 40U > size) return 0;
    magic = u16_at(data + pe + 24);
    /* Data directories follow 96 (PE32) or 112 (PE32+) bytes of header. */
    directory_offset = pe + 24U + (magic == 0x20b ? 112U : 96U) +
                       RESOURCE_DIRECTORY_ENTRY * 8U;
    if (directory_offset + 8U > (uint32_t)pe + 24U + optional_size) return 0;
    rva = u32_at(data + directory_offset);
    if (rva == 0) return 0;
    section = data + pe + 24 + optional_size;
    for (index = 0; index < sections; ++index, section += 40) {
        uint32_t virtual_address = u32_at(section + 12);
        uint32_t raw_size = u32_at(section + 16);
        uint32_t raw_offset = u32_at(section + 20);
        if (rva >= virtual_address && rva - virtual_address < raw_size &&
            raw_offset <= size && raw_size <= size - raw_offset) {
            view->data = data;
            view->size = size;
            view->resources = data + raw_offset + (rva - virtual_address);
            view->resources_size = raw_size - (rva - virtual_address);
            view->resources_rva = rva;
            return 1;
        }
    }
    return 0;
}

/* Finds entry `id` (numeric) of the resource directory at `offset` within
   .rsrc; returns its target offset with the high (subdirectory) bit kept,
   or UINT32_MAX. id < 0 takes the first entry. */
static uint32_t pe_directory_find(const PeView *view, uint32_t offset, int id)
{
    uint16_t named;
    uint16_t numbered;
    uint32_t entry;
    unsigned int index;
    if (offset > view->resources_size || view->resources_size - offset < 16U)
        return UINT32_MAX;
    named = u16_at(view->resources + offset + 12);
    numbered = u16_at(view->resources + offset + 14);
    entry = offset + 16U;
    if ((size_t)entry + ((size_t)named + numbered) * 8U > view->resources_size)
        return UINT32_MAX;
    for (index = 0; index < (unsigned)named + numbered; ++index, entry += 8U) {
        uint32_t name = u32_at(view->resources + entry);
        if (id < 0 || ((name & 0x80000000U) == 0 && name == (uint32_t)id))
            return u32_at(view->resources + entry + 4);
    }
    return UINT32_MAX;
}

/* Data of resource type/id (first language): pointer and length. */
static const uint8_t *pe_resource(const PeView *view, int type, int id,
                                  uint32_t *length)
{
    uint32_t level = pe_directory_find(view, 0, type);
    uint32_t data_entry;
    uint32_t rva;
    if (level == UINT32_MAX || (level & 0x80000000U) == 0) return NULL;
    level = pe_directory_find(view, level & 0x7fffffffU, id);
    if (level == UINT32_MAX || (level & 0x80000000U) == 0) return NULL;
    data_entry = pe_directory_find(view, level & 0x7fffffffU, -1);
    if (data_entry == UINT32_MAX || (data_entry & 0x80000000U) != 0 ||
        data_entry > view->resources_size ||
        view->resources_size - data_entry < 16U) return NULL;
    rva = u32_at(view->resources + data_entry);
    *length = u32_at(view->resources + data_entry + 4);
    if (rva < view->resources_rva ||
        rva - view->resources_rva > view->resources_size ||
        *length > view->resources_size - (rva - view->resources_rva))
        return NULL;
    return view->resources + (rva - view->resources_rva);
}

static int dib_bit(const uint8_t *row, int x)
{
    return (row[x >> 3] >> (7 - (x & 7))) & 1;
}

int pe_cursor_decode(const uint8_t *image, size_t size, uint16_t group_id,
                     PeCursor *out)
{
    PeView view;
    const uint8_t *group;
    const uint8_t *cursor;
    const uint8_t *dib;
    const uint8_t *palette;
    const uint8_t *colour_rows;
    const uint8_t *mask_rows;
    uint32_t group_length;
    uint32_t cursor_length;
    uint32_t header_size;
    uint32_t colours;
    uint32_t colour_stride;
    uint32_t mask_stride;
    int32_t width;
    int32_t height;
    uint16_t bits;
    int x;
    int y;

    memset(out, 0, sizeof(*out));
    if (!pe_view_open(image, size, &view)) return 0;
    group = pe_resource(&view, RT_GROUP_CURSOR_TYPE, group_id, &group_length);
    /* NEWHEADER (6 bytes) then 14-byte CURSORDIRENTRY, nId at +12. */
    if (group == NULL || group_length < 20U || u16_at(group + 4) == 0) return 0;
    cursor = pe_resource(&view, RT_CURSOR_TYPE, u16_at(group + 6 + 12),
                         &cursor_length);
    if (cursor == NULL || cursor_length < 4U + 40U) return 0;
    dib = cursor + 4;
    header_size = u32_at(dib);
    width = (int32_t)u32_at(dib + 4);
    height = (int32_t)u32_at(dib + 8) / 2;
    bits = u16_at(dib + 14);
    if (header_size < 40U || u32_at(dib + 16) != 0 /* BI_RGB */ ||
        width <= 0 || width > 256 || height <= 0 || height > 256 ||
        (bits != 1 && bits != 4 && bits != 8 && bits != 24 && bits != 32))
        return 0;
    colours = bits <= 8 ? (u32_at(dib + 32) != 0 ? u32_at(dib + 32) : 1U << bits) : 0;
    colour_stride = (((uint32_t)width * bits + 31U) / 32U) * 4U;
    mask_stride = (((uint32_t)width + 31U) / 32U) * 4U;
    if (4U + header_size + colours * 4U + (colour_stride + mask_stride) * (uint32_t)height >
        cursor_length) return 0;
    palette = dib + header_size;
    colour_rows = palette + colours * 4U;
    mask_rows = colour_rows + colour_stride * (uint32_t)height;

    out->pixels = (uint32_t *)malloc((size_t)width * (size_t)height * sizeof(uint32_t));
    if (out->pixels == NULL) return 0;
    out->width = width;
    out->height = height;
    out->hotspot_x = u16_at(cursor);
    out->hotspot_y = u16_at(cursor + 2);
    /* DIB rows are bottom-up. */
    for (y = 0; y < height; ++y) {
        const uint8_t *colour_row = colour_rows + colour_stride * (uint32_t)(height - 1 - y);
        const uint8_t *mask_row = mask_rows + mask_stride * (uint32_t)(height - 1 - y);
        for (x = 0; x < width; ++x) {
            uint32_t rgb;
            uint32_t index = 0;
            if (bits == 1) index = (uint32_t)dib_bit(colour_row, x);
            else if (bits == 4) index = (colour_row[x >> 1] >> ((x & 1) ? 0 : 4)) & 15U;
            else if (bits == 8) index = colour_row[x];
            if (bits <= 8) {
                const uint8_t *entry = palette + (index < colours ? index : 0U) * 4U;
                rgb = ((uint32_t)entry[2] << 16) | ((uint32_t)entry[1] << 8) | entry[0];
            } else {
                const uint8_t *p = colour_row + (size_t)x * (bits / 8U);
                rgb = ((uint32_t)p[2] << 16) | ((uint32_t)p[1] << 8) | p[0];
            }
            if (dib_bit(mask_row, x)) {
                /* AND set: transparent, or screen inversion where the colour
                   is not black, which a colour cursor cannot show. */
                out->pixels[(size_t)y * (size_t)width + (size_t)x] =
                    rgb != 0 ? 0xff000000U : 0U;
            } else {
                out->pixels[(size_t)y * (size_t)width + (size_t)x] =
                    bits == 32 ? (rgb | ((uint32_t)colour_row[(size_t)x * 4U + 3U] << 24))
                               : (rgb | 0xff000000U);
            }
        }
    }
    return 1;
}

void pe_cursor_free(PeCursor *cursor)
{
    free(cursor->pixels);
    cursor->pixels = NULL;
}
