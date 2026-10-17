#ifndef TONE_REBELLION_COB_ARCHIVE_H
#define TONE_REBELLION_COB_ARCHIVE_H

#include <stddef.h>
#include <stdint.h>

enum { COB_ARCHIVE_MAX_MEMBERS = 500, COB_ARCHIVE_NAME_CAPACITY = 51 };

typedef struct CobMember {
    char name[COB_ARCHIVE_NAME_CAPACITY];
    uint32_t offset;
    uint32_t length;
} CobMember;

typedef struct CobArchive {
    void *file_handle;
    uint32_t member_count;
    CobMember *members;
} CobArchive;

/* Opens an existing COB read-only. The output is left empty on failure. */
int cob_archive_open(const char *path, CobArchive *out,
                     char *error, size_t error_capacity);
void cob_archive_close(CobArchive *archive);
const CobMember *cob_archive_member_at(const CobArchive *archive, size_t index);
const CobMember *cob_archive_find(const CobArchive *archive, const char *name);

/* Copies one member into caller-owned memory; no file is created or modified. */
int cob_archive_read_member(const CobArchive *archive, const CobMember *member,
                            void *buffer, size_t capacity,
                            char *error, size_t error_capacity);

#endif
