#include "game_session_schema.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Table layout (little endian): u32 type count, u32 root type; per type a
   name, u32 size, u32 field count; per field a name, u32 offset, element
   size and count, i32 type. A name is u16 length + bytes. */

typedef struct SavedField {
    const unsigned char *name;
    uint16_t name_length;
    uint32_t offset;
    uint32_t element_size;
    uint32_t count;
    int32_t type;
} SavedField;

typedef struct SavedType {
    const unsigned char *name;
    uint16_t name_length;
    uint32_t size;
    uint32_t field_count;
    SavedField *fields;
} SavedType;

typedef struct SavedSchema {
    uint32_t type_count;
    uint32_t root;
    SavedType *types;
    SavedField *fields;
} SavedSchema;

static size_t put_u32(unsigned char *buffer, size_t capacity, size_t at,
                      uint32_t value)
{
    if (buffer != NULL && at + 4 <= capacity) {
        buffer[at] = (unsigned char)value;
        buffer[at + 1] = (unsigned char)(value >> 8);
        buffer[at + 2] = (unsigned char)(value >> 16);
        buffer[at + 3] = (unsigned char)(value >> 24);
    }
    return at + 4;
}

static size_t put_name(unsigned char *buffer, size_t capacity, size_t at,
                       const char *name)
{
    size_t length = strlen(name);
    if (buffer != NULL && at + 2 + length <= capacity) {
        buffer[at] = (unsigned char)length;
        buffer[at + 1] = (unsigned char)(length >> 8);
        memcpy(buffer + at + 2, name, length);
    }
    return at + 2 + length;
}

size_t game_session_schema_write(unsigned char *buffer, size_t capacity)
{
    size_t at = 0;
    uint32_t t;
    at = put_u32(buffer, capacity, at, game_session_schema_type_count);
    at = put_u32(buffer, capacity, at, game_session_schema_root);
    for (t = 0; t < game_session_schema_type_count; ++t) {
        const GameSessionSchemaType *type = &game_session_schema_types[t];
        uint32_t f;
        at = put_name(buffer, capacity, at, type->name);
        at = put_u32(buffer, capacity, at, type->size);
        at = put_u32(buffer, capacity, at, type->field_count);
        for (f = 0; f < type->field_count; ++f) {
            const GameSessionSchemaField *field = &type->fields[f];
            at = put_name(buffer, capacity, at, field->name);
            at = put_u32(buffer, capacity, at, field->offset);
            at = put_u32(buffer, capacity, at, field->element_size);
            at = put_u32(buffer, capacity, at, field->count);
            at = put_u32(buffer, capacity, at, (uint32_t)field->type);
        }
    }
    if (buffer != NULL && at > capacity) return 0;
    return at;
}

static int get_u32(const unsigned char *bytes, size_t length, size_t *at,
                   uint32_t *value)
{
    if (*at + 4 > length) return 0;
    *value = (uint32_t)bytes[*at] | (uint32_t)bytes[*at + 1] << 8 |
        (uint32_t)bytes[*at + 2] << 16 | (uint32_t)bytes[*at + 3] << 24;
    *at += 4;
    return 1;
}

static int get_name(const unsigned char *bytes, size_t length, size_t *at,
                    const unsigned char **name, uint16_t *name_length)
{
    uint16_t size;
    if (*at + 2 > length) return 0;
    size = (uint16_t)(bytes[*at] | bytes[*at + 1] << 8);
    if (*at + 2 + size > length) return 0;
    *name = bytes + *at + 2;
    *name_length = size;
    *at += 2 + (size_t)size;
    return 1;
}

static void free_saved_schema(SavedSchema *schema)
{
    free(schema->types);
    free(schema->fields);
}

static int parse_saved_schema(const unsigned char *bytes, size_t length,
                              SavedSchema *schema)
{
    size_t at = 0;
    size_t field_total = 0;
    size_t field_capacity = 0;
    uint32_t t;
    memset(schema, 0, sizeof(*schema));
    if (!get_u32(bytes, length, &at, &schema->type_count) ||
        !get_u32(bytes, length, &at, &schema->root) ||
        schema->type_count == 0 || schema->type_count > 4096 ||
        schema->root >= schema->type_count) return 0;
    schema->types = (SavedType *)calloc(schema->type_count, sizeof(SavedType));
    /* Every field takes at least 22 bytes: bounds the field array. */
    field_capacity = length / 22 + 1;
    schema->fields = (SavedField *)calloc(field_capacity, sizeof(SavedField));
    if (schema->types == NULL || schema->fields == NULL) goto fail;
    for (t = 0; t < schema->type_count; ++t) {
        SavedType *type = &schema->types[t];
        uint32_t f;
        if (!get_name(bytes, length, &at, &type->name, &type->name_length) ||
            !get_u32(bytes, length, &at, &type->size) ||
            !get_u32(bytes, length, &at, &type->field_count) ||
            type->field_count > field_capacity - field_total) goto fail;
        type->fields = schema->fields + field_total;
        field_total += type->field_count;
        for (f = 0; f < type->field_count; ++f) {
            SavedField *field = &type->fields[f];
            uint32_t kind;
            if (!get_name(bytes, length, &at, &field->name, &field->name_length) ||
                !get_u32(bytes, length, &at, &field->offset) ||
                !get_u32(bytes, length, &at, &field->element_size) ||
                !get_u32(bytes, length, &at, &field->count) ||
                !get_u32(bytes, length, &at, &kind)) goto fail;
            field->type = (int32_t)kind;
            /* A field must sit inside its type, and only refer to an
               earlier type (the table lists nested types first). */
            if (field->element_size == 0 ||
                field->count > (type->size - (field->offset < type->size
                    ? field->offset : type->size)) / field->element_size ||
                field->offset > type->size ||
                (field->type != -1 && (field->type < 0 ||
                    (uint32_t)field->type >= t ||
                    schema->types[field->type].size != field->element_size)))
                goto fail;
        }
    }
    return 1;
fail:
    free_saved_schema(schema);
    memset(schema, 0, sizeof(*schema));
    return 0;
}

static int name_equals(const unsigned char *saved, uint16_t length,
                       const char *name)
{
    return strlen(name) == length && memcmp(saved, name, length) == 0;
}

typedef struct MigrateContext {
    const SavedSchema *schema;
    const GameSessionSchemaRename *renames;
    uint32_t rename_count;
} MigrateContext;

/* The saved type name matches the current type, directly or through a
   type rename. */
static int type_matches(const MigrateContext *context, const SavedType *saved,
                        const char *name)
{
    uint32_t r;
    if (name_equals(saved->name, saved->name_length, name)) return 1;
    for (r = 0; r < context->rename_count; ++r) {
        const GameSessionSchemaRename *rename = &context->renames[r];
        if (rename->field == NULL && rename->type != NULL &&
            strcmp(rename->type, name) == 0 &&
            name_equals(saved->name, saved->name_length, rename->old_name))
            return 1;
    }
    return 0;
}

static const SavedField *find_saved_field(const MigrateContext *context,
                                          const SavedType *saved,
                                          const char *type_name,
                                          const char *field_name)
{
    uint32_t s;
    uint32_t r;
    for (s = 0; s < saved->field_count; ++s)
        if (name_equals(saved->fields[s].name, saved->fields[s].name_length,
                        field_name)) return &saved->fields[s];
    for (r = 0; r < context->rename_count; ++r) {
        const GameSessionSchemaRename *rename = &context->renames[r];
        if (rename->field == NULL || rename->type == NULL ||
            strcmp(rename->type, type_name) != 0 ||
            strcmp(rename->field, field_name) != 0) continue;
        for (s = 0; s < saved->field_count; ++s)
            if (name_equals(saved->fields[s].name, saved->fields[s].name_length,
                            rename->old_name)) return &saved->fields[s];
    }
    return NULL;
}

static int integer_size(uint32_t size)
{
    return size == 1 || size == 2 || size == 4 || size == 8;
}

/* Integer element of another width: extended with this build's signedness,
   stored when it fits (otherwise the fresh value stays). Little endian. */
static void convert_integers(const GameSessionSchemaField *field,
                             unsigned char *out, const SavedField *match,
                             const unsigned char *in, uint32_t count)
{
    int is_signed = field->kind == GAME_SESSION_SCHEMA_SIGNED;
    uint32_t i;
    for (i = 0; i < count; ++i) {
        const unsigned char *from = in + (size_t)i * match->element_size;
        unsigned char *to = out + (size_t)i * field->element_size;
        uint64_t raw = 0;
        int64_t value;
        uint32_t b;
        for (b = 0; b < match->element_size; ++b)
            raw |= (uint64_t)from[b] << (8u * b);
        if (is_signed && match->element_size < 8 &&
            (raw >> (8u * match->element_size - 1u)) != 0)
            raw |= ~UINT64_C(0) << (8u * match->element_size);
        value = (int64_t)raw;
        if (field->element_size < 8) {
            uint32_t bits = 8u * field->element_size;
            if (is_signed) {
                int64_t low = -(INT64_C(1) << (bits - 1u));
                int64_t high = (INT64_C(1) << (bits - 1u)) - 1;
                if (value < low || value > high) continue;
            } else if (raw >> bits != 0) {
                continue;
            }
        } else if (!is_signed && match->element_size < 8 && value < 0) {
            continue;
        }
        for (b = 0; b < field->element_size; ++b)
            to[b] = (unsigned char)(raw >> (8u * b));
    }
}

static void migrate_type(const MigrateContext *context,
                         const GameSessionSchemaType *type, unsigned char *out,
                         const SavedType *saved, const unsigned char *in,
                         unsigned int depth)
{
    uint32_t f;
    if (depth > 16) return;
    for (f = 0; f < type->field_count; ++f) {
        const GameSessionSchemaField *field = &type->fields[f];
        const SavedField *match =
            find_saved_field(context, saved, type->name, field->name);
        uint32_t count;
        uint32_t i;
        if (match == NULL || (match->type == -1) != (field->type == -1))
            continue;
        count = match->count < field->count ? match->count : field->count;
        if (field->type == -1) {
            /* Scalars and scalar arrays: same element size, or an integer
               of another width. */
            if (match->element_size == field->element_size)
                memcpy(out + field->offset, in + match->offset,
                       (size_t)count * field->element_size);
            else if (field->kind != GAME_SESSION_SCHEMA_FLOAT &&
                     integer_size(field->element_size) &&
                     integer_size(match->element_size))
                convert_integers(field, out + field->offset, match,
                                 in + match->offset, count);
            continue;
        }
        {
            const GameSessionSchemaType *nested =
                &game_session_schema_types[field->type];
            const SavedType *saved_nested = &context->schema->types[match->type];
            if (!type_matches(context, saved_nested, nested->name)) continue;
            for (i = 0; i < count; ++i)
                migrate_type(context, nested,
                    out + field->offset + (size_t)i * field->element_size,
                    saved_nested,
                    in + match->offset + (size_t)i * match->element_size,
                    depth + 1);
        }
    }
}

int game_session_schema_migrate_with(GameSession *session,
                                     const unsigned char *schema_bytes,
                                     size_t schema_length,
                                     const unsigned char *data,
                                     size_t data_length,
                                     const GameSessionSchemaRename *renames,
                                     uint32_t rename_count)
{
    SavedSchema schema;
    const SavedType *root;
    MigrateContext context;
    if (session == NULL || schema_bytes == NULL || data == NULL ||
        !parse_saved_schema(schema_bytes, schema_length, &schema)) return 0;
    context.schema = &schema;
    context.renames = renames;
    context.rename_count = renames != NULL ? rename_count : 0;
    root = &schema.types[schema.root];
    if (root->size != data_length ||
        !type_matches(&context, root,
            game_session_schema_types[game_session_schema_root].name)) {
        free_saved_schema(&schema);
        return 0;
    }
    migrate_type(&context, &game_session_schema_types[game_session_schema_root],
                 (unsigned char *)session, root, data, 0);
    free_saved_schema(&schema);
    return 1;
}

int game_session_schema_migrate(GameSession *session,
                                const unsigned char *schema_bytes,
                                size_t schema_length,
                                const unsigned char *data,
                                size_t data_length)
{
    return game_session_schema_migrate_with(session, schema_bytes,
        schema_length, data, data_length, game_session_schema_renames,
        game_session_schema_rename_count);
}

int game_session_schema_check(char *error, size_t error_capacity)
{
    uint32_t t;
    for (t = 0; t < game_session_schema_type_count; ++t) {
        const GameSessionSchemaType *type = &game_session_schema_types[t];
        uint32_t position = 0;
        uint32_t type_align = 1;
        uint32_t f;
        for (f = 0; f < type->field_count; ++f) {
            const GameSessionSchemaField *field = &type->fields[f];
            uint32_t expected = (position + field->align - 1) / field->align *
                field->align;
            if (field->offset != expected) {
                (void)snprintf(error, error_capacity,
                    "%s: %u bytes before %s are not described",
                    type->name, (unsigned)(field->offset - position), field->name);
                return 0;
            }
            position = field->offset + field->element_size * field->count;
            if (field->align > type_align) type_align = field->align;
        }
        if ((position + type_align - 1) / type_align * type_align != type->size) {
            (void)snprintf(error, error_capacity,
                "%s: %u bytes after the last field are not described",
                type->name, (unsigned)(type->size - position));
            return 0;
        }
    }
    return 1;
}
