#include "iso9660.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { ISO_LOGICAL_SECTOR = 2048, ISO_PVD_SECTOR = 16, ISO_MAX_DIRECTORY = 1 << 20 };

static uint32_t read_u32le(const unsigned char *bytes)
{
    return (uint32_t)bytes[0] | ((uint32_t)bytes[1] << 8) |
           ((uint32_t)bytes[2] << 16) | ((uint32_t)bytes[3] << 24);
}

static void set_error(char *error, size_t capacity, const char *message)
{
    if (error != NULL && capacity > 0) (void)snprintf(error, capacity, "%s", message);
}

static int seek_to(FILE *file, unsigned long long position)
{
    return fseek(file, (long)position, SEEK_SET) == 0;
}

/* Reads one logical sector (2048 bytes of user data). */
static int read_logical(const Iso9660 *iso, uint32_t sector, unsigned char *out)
{
    FILE *file = (FILE *)iso->file_handle;
    return seek_to(file, (unsigned long long)sector * iso->sector_size + iso->data_offset) &&
           fread(out, 1, ISO_LOGICAL_SECTOR, file) == ISO_LOGICAL_SECTOR;
}

int iso9660_open(const char *path, Iso9660 *out, char *error, size_t error_capacity)
{
    static const struct { uint32_t sector_size, data_offset; } layouts[] = {
        {2048, 0}, {2352, 16}, {2352, 24}
    };
    unsigned char sector[ISO_LOGICAL_SECTOR];
    FILE *file;
    size_t index;

    memset(out, 0, sizeof(*out));
    file = fopen(path, "rb");
    if (file == NULL) {
        set_error(error, error_capacity, "could not open the ISO image");
        return 0;
    }
    out->file_handle = file;
    for (index = 0; index < sizeof(layouts) / sizeof(layouts[0]); ++index) {
        out->sector_size = layouts[index].sector_size;
        out->data_offset = layouts[index].data_offset;
        if (read_logical(out, ISO_PVD_SECTOR, sector) && sector[0] == 1 &&
            memcmp(sector + 1, "CD001", 5) == 0) {
            /* Root directory record sits at byte 156 of the descriptor. */
            out->root_extent = read_u32le(sector + 156 + 2);
            out->root_length = read_u32le(sector + 156 + 10);
            return 1;
        }
    }
    fclose(file);
    memset(out, 0, sizeof(*out));
    set_error(error, error_capacity, "not an ISO 9660 image");
    return 0;
}

void iso9660_close(Iso9660 *iso)
{
    if (iso->file_handle != NULL) fclose((FILE *)iso->file_handle);
    memset(iso, 0, sizeof(*iso));
}

static char fold(char c)
{
    return (c >= 'a' && c <= 'z') ? (char)(c - 'a' + 'A') : c;
}

/* Compares a directory record name with a path component, ignoring case,
   the `;version` suffix and a trailing dot. */
static int name_matches(const unsigned char *record_name, size_t record_length,
                        const char *component, size_t component_length)
{
    size_t length = record_length;
    size_t index;
    for (index = 0; index < record_length; ++index) {
        if (record_name[index] == ';') { length = index; break; }
    }
    if (length > 0 && record_name[length - 1] == '.') --length;
    if (length != component_length) return 0;
    for (index = 0; index < length; ++index) {
        if (fold((char)record_name[index]) != fold(component[index])) return 0;
    }
    return 1;
}

static int find_in_directory(const Iso9660 *iso, uint32_t extent, uint32_t length,
                             const char *component, size_t component_length,
                             IsoFile *out, int *is_directory)
{
    unsigned char sector[ISO_LOGICAL_SECTOR];
    uint32_t consumed;

    if (length > ISO_MAX_DIRECTORY) return 0;
    for (consumed = 0; consumed < length; consumed += ISO_LOGICAL_SECTOR) {
        uint32_t position = 0;
        if (!read_logical(iso, extent + consumed / ISO_LOGICAL_SECTOR, sector)) return 0;
        while (position + 34U <= ISO_LOGICAL_SECTOR) {
            unsigned record_length = sector[position];
            unsigned name_length;
            if (record_length == 0) break;
            if (position + record_length > ISO_LOGICAL_SECTOR || record_length < 34U) break;
            name_length = sector[position + 32];
            if (33U + name_length <= record_length &&
                name_matches(sector + position + 33, name_length,
                             component, component_length)) {
                out->extent = read_u32le(sector + position + 2);
                out->length = read_u32le(sector + position + 10);
                *is_directory = (sector[position + 25] & 2U) != 0;
                return 1;
            }
            position += record_length;
        }
    }
    return 0;
}

int iso9660_find(const Iso9660 *iso, const char *path, IsoFile *out)
{
    IsoFile current;
    int is_directory = 1;
    const char *cursor = path;

    current.extent = iso->root_extent;
    current.length = iso->root_length;
    while (*cursor != '\0') {
        size_t count = 0;
        while (*cursor == '/' || *cursor == '\\') ++cursor;
        if (*cursor == '\0') break;
        while (cursor[count] != '\0' && cursor[count] != '/' && cursor[count] != '\\') ++count;
        if (!is_directory) return 0;
        if (!find_in_directory(iso, current.extent, current.length, cursor, count,
                               &current, &is_directory)) return 0;
        cursor += count;
    }
    if (is_directory) return 0;
    *out = current;
    return 1;
}

size_t iso9660_read(const Iso9660 *iso, const IsoFile *file, uint32_t offset,
                    void *buffer, size_t capacity)
{
    unsigned char sector[ISO_LOGICAL_SECTOR];
    unsigned char *destination = (unsigned char *)buffer;
    size_t done = 0;

    if (offset >= file->length) return 0;
    if (capacity > file->length - offset) capacity = file->length - offset;
    while (done < capacity) {
        uint32_t position = offset + (uint32_t)done;
        uint32_t within = position % ISO_LOGICAL_SECTOR;
        size_t chunk = ISO_LOGICAL_SECTOR - within;
        if (chunk > capacity - done) chunk = capacity - done;
        if (!read_logical(iso, file->extent + position / ISO_LOGICAL_SECTOR, sector)) break;
        memcpy(destination + done, sector + within, chunk);
        done += chunk;
    }
    return done;
}

int iso9660_extract(const Iso9660 *iso, const IsoFile *file, const char *destination,
                    char *error, size_t error_capacity)
{
    enum { CHUNK = 1 << 16 };
    unsigned char *buffer;
    FILE *output = fopen(destination, "rb");
    uint32_t offset = 0;

    if (output != NULL) {
        long size;
        (void)fseek(output, 0, SEEK_END);
        size = ftell(output);
        fclose(output);
        if (size >= 0 && (uint32_t)size == file->length) return 1;
    }
    buffer = (unsigned char *)malloc(CHUNK);
    if (buffer == NULL) {
        set_error(error, error_capacity, "out of memory");
        return 0;
    }
    output = fopen(destination, "wb");
    if (output == NULL) {
        free(buffer);
        set_error(error, error_capacity, "could not create the cache file");
        return 0;
    }
    while (offset < file->length) {
        size_t want = file->length - offset < CHUNK ? file->length - offset : CHUNK;
        size_t got = iso9660_read(iso, file, offset, buffer, want);
        if (got != want || fwrite(buffer, 1, got, output) != got) {
            fclose(output);
            (void)remove(destination);
            free(buffer);
            set_error(error, error_capacity, "ISO read or cache write failed");
            return 0;
        }
        offset += (uint32_t)got;
    }
    free(buffer);
    return fclose(output) == 0;
}
