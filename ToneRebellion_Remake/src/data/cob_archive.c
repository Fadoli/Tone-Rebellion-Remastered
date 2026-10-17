#include "cob_archive.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    COB_NAME_FIELD_SIZE = 50,
    COB_OFFSET_FIELD_SIZE = 4
};

static void set_error(char *error, size_t capacity, const char *message)
{
    if (error != NULL && capacity > 0) {
        (void)snprintf(error, capacity, "%s", message);
        error[capacity - 1] = '\0';
    }
}

static uint32_t read_u32_le(const unsigned char bytes[4])
{
    return (uint32_t)bytes[0] |
           ((uint32_t)bytes[1] << 8) |
           ((uint32_t)bytes[2] << 16) |
           ((uint32_t)bytes[3] << 24);
}

static int read_exact(FILE *file, void *buffer, size_t size)
{
    return size == 0 || fread(buffer, 1, size, file) == size;
}

void cob_archive_close(CobArchive *archive)
{
    if (archive == NULL) {
        return;
    }
    if (archive->file_handle != NULL) {
        (void)fclose((FILE *)archive->file_handle);
    }
    free(archive->members);
    archive->file_handle = NULL;
    archive->members = NULL;
    archive->member_count = 0;
}

int cob_archive_open(const char *path, CobArchive *out,
                     char *error, size_t error_capacity)
{
    FILE *file;
    CobArchive parsed;
    unsigned char count_bytes[4];
    unsigned char name_fields[COB_ARCHIVE_MAX_MEMBERS][COB_NAME_FIELD_SIZE];
    unsigned char offset_bytes[COB_ARCHIVE_MAX_MEMBERS][COB_OFFSET_FIELD_SIZE];
    long file_size;
    uint32_t data_start;
    uint32_t i;

    if (error != NULL && error_capacity > 0) {
        error[0] = '\0';
    }
    if (path == NULL || out == NULL) {
        set_error(error, error_capacity, "path and output are required");
        return 0;
    }
    out->file_handle = NULL;
    out->members = NULL;
    out->member_count = 0;
    file = fopen(path, "rb");
    if (file == NULL) {
        set_error(error, error_capacity, "could not open COB archive read-only");
        return 0;
    }
    if (fseek(file, 0, SEEK_END) != 0 || (file_size = ftell(file)) < 4 ||
        fseek(file, 0, SEEK_SET) != 0 || !read_exact(file, count_bytes, sizeof(count_bytes))) {
        set_error(error, error_capacity, "could not read COB archive header");
        fclose(file);
        return 0;
    }

    if ((unsigned long)file_size > UINT32_MAX) {
        set_error(error, error_capacity, "COB archive exceeds the 32-bit offset format");
        fclose(file);
        return 0;
    }
    parsed.member_count = read_u32_le(count_bytes);
    if (parsed.member_count > COB_ARCHIVE_MAX_MEMBERS) {
        set_error(error, error_capacity, "COB member count is outside the supported range");
        fclose(file);
        return 0;
    }
    data_start = 4u + parsed.member_count * (COB_NAME_FIELD_SIZE + COB_OFFSET_FIELD_SIZE);
    if ((long)data_start > file_size) {
        set_error(error, error_capacity, "COB directory exceeds archive size");
        fclose(file);
        return 0;
    }
    if (!read_exact(file, name_fields, parsed.member_count * COB_NAME_FIELD_SIZE) ||
        !read_exact(file, offset_bytes, parsed.member_count * COB_OFFSET_FIELD_SIZE)) {
        set_error(error, error_capacity, "could not read COB directory");
        fclose(file);
        return 0;
    }

    parsed.members = parsed.member_count == 0 ? NULL :
        (CobMember *)calloc(parsed.member_count, sizeof(*parsed.members));
    if (parsed.member_count > 0 && parsed.members == NULL) {
        set_error(error, error_capacity, "could not allocate COB directory");
        fclose(file);
        return 0;
    }
    parsed.file_handle = file;
    for (i = 0; i < parsed.member_count; ++i) {
        const unsigned char *terminator = (const unsigned char *)memchr(
            name_fields[i], '\0', COB_NAME_FIELD_SIZE);
        uint32_t offset = read_u32_le(offset_bytes[i]);
        uint32_t next_offset;

        if (terminator == NULL || terminator == name_fields[i]) {
            set_error(error, error_capacity, "COB member name is empty or unterminated");
            cob_archive_close(&parsed);
            return 0;
        }
        if (offset < data_start || (long)offset > file_size) {
            set_error(error, error_capacity, "COB member offset is outside the data region");
            cob_archive_close(&parsed);
            return 0;
        }
        if (i > 0 && offset <= parsed.members[i - 1].offset) {
            set_error(error, error_capacity, "COB member offsets are not strictly increasing");
            cob_archive_close(&parsed);
            return 0;
        }
        memcpy(parsed.members[i].name, name_fields[i], (size_t)(terminator - name_fields[i]));
        parsed.members[i].offset = offset;
        if (i + 1 < parsed.member_count) {
            next_offset = read_u32_le(offset_bytes[i + 1]);
        } else {
            next_offset = (uint32_t)file_size;
        }
        if (next_offset < offset || (long)next_offset > file_size) {
            set_error(error, error_capacity, "COB member range exceeds archive size");
            cob_archive_close(&parsed);
            return 0;
        }
        parsed.members[i].length = next_offset - offset;
    }

    *out = parsed;
    return 1;
}

const CobMember *cob_archive_member_at(const CobArchive *archive, size_t index)
{
    if (archive == NULL || index >= archive->member_count) {
        return NULL;
    }
    return &archive->members[index];
}

const CobMember *cob_archive_find(const CobArchive *archive, const char *name)
{
    size_t i;
    if (archive == NULL || name == NULL) {
        return NULL;
    }
    for (i = 0; i < archive->member_count; ++i) {
        if (strcmp(archive->members[i].name, name) == 0) {
            return &archive->members[i];
        }
    }
    return NULL;
}

int cob_archive_read_member(const CobArchive *archive, const CobMember *member,
                            void *buffer, size_t capacity,
                            char *error, size_t error_capacity)
{
    FILE *file;
    if (error != NULL && error_capacity > 0) {
        error[0] = '\0';
    }
    if (archive == NULL || archive->file_handle == NULL || member == NULL ||
        (member->length > 0 && buffer == NULL)) {
        set_error(error, error_capacity, "archive, member, and destination buffer are required");
        return 0;
    }
    if ((size_t)member->length > capacity) {
        set_error(error, error_capacity, "destination buffer is too small for COB member");
        return 0;
    }
    file = (FILE *)archive->file_handle;
    if (fseek(file, (long)member->offset, SEEK_SET) != 0 ||
        !read_exact(file, buffer, member->length)) {
        set_error(error, error_capacity, "could not read COB member bytes");
        return 0;
    }
    return 1;
}
