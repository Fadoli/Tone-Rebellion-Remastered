#ifndef TONE_REBELLION_ISO9660_H
#define TONE_REBELLION_ISO9660_H

#include <stddef.h>
#include <stdint.h>

/* Minimal read-only ISO 9660 reader (primary volume descriptor only). It
   accepts cooked 2048-byte images and raw 2352-byte mode 1 / mode 2 form 1
   images. Nothing is ever written to the image. */

typedef struct IsoFile {
    uint32_t extent;
    uint32_t length;
} IsoFile;

typedef struct Iso9660 {
    void *file_handle;
    uint32_t sector_size;
    uint32_t data_offset;
    uint32_t root_extent;
    uint32_t root_length;
} Iso9660;

int iso9660_open(const char *path, Iso9660 *out, char *error, size_t error_capacity);
void iso9660_close(Iso9660 *iso);

/* Finds a file by path (`/` or `\` separators, case-insensitive, `;1` version
   suffixes ignored). */
int iso9660_find(const Iso9660 *iso, const char *path, IsoFile *out);

/* Reads `capacity` bytes at `offset` within the file; returns bytes read. */
size_t iso9660_read(const Iso9660 *iso, const IsoFile *file, uint32_t offset,
                    void *buffer, size_t capacity);

/* Copies the file to `destination` unless a file of the same length already
   exists there. Returns 1 on success. */
int iso9660_extract(const Iso9660 *iso, const IsoFile *file, const char *destination,
                    char *error, size_t error_capacity);

#endif
