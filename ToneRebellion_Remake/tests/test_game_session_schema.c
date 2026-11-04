#include "game_session_schema.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Compares the bytes the schema describes (padding aside). */
static int described_bytes_equal(const GameSessionSchemaType *type,
                                 const unsigned char *a, const unsigned char *b)
{
    uint32_t f;
    for (f = 0; f < type->field_count; ++f) {
        const GameSessionSchemaField *field = &type->fields[f];
        uint32_t i;
        if (field->type < 0) {
            if (memcmp(a + field->offset, b + field->offset,
                       (size_t)field->element_size * field->count) != 0)
                return 0;
            continue;
        }
        for (i = 0; i < field->count; ++i) {
            size_t at = field->offset + (size_t)i * field->element_size;
            if (!described_bytes_equal(&game_session_schema_types[field->type],
                                       a + at, b + at)) return 0;
        }
    }
    return 1;
}

static const GameSessionSchemaField *root_field(const char *name)
{
    const GameSessionSchemaType *root =
        &game_session_schema_types[game_session_schema_root];
    uint32_t f;
    for (f = 0; f < root->field_count; ++f)
        if (strcmp(root->fields[f].name, name) == 0) return &root->fields[f];
    return NULL;
}

/* Last occurrence of a serialised name (the root type is written last). */
static unsigned char *find_name(unsigned char *bytes, size_t length,
                                const char *name)
{
    size_t name_length = strlen(name);
    size_t at;
    for (at = length - name_length - 2; at > 0; --at) {
        if (bytes[at] == (unsigned char)name_length && bytes[at + 1] == 0 &&
            memcmp(bytes + at + 2, name, name_length) == 0) return bytes + at;
    }
    return NULL;
}

static void fill_pattern(unsigned char *bytes, size_t length, uint32_t seed)
{
    size_t i;
    for (i = 0; i < length; ++i) {
        seed = seed * 1103515245u + 12345u;
        bytes[i] = (unsigned char)(seed >> 16);
    }
}

int main(void)
{
    char error[160];
    size_t schema_length = game_session_schema_write(NULL, 0);
    unsigned char *schema = (unsigned char *)malloc(schema_length);
    GameSession *saved = (GameSession *)malloc(sizeof(GameSession));
    GameSession *loaded = (GameSession *)malloc(sizeof(GameSession));
    const GameSessionSchemaField *tick = root_field("simulation_tick");
    const GameSessionSchemaField *floaters = root_field("floaters");
    unsigned char *entry;
    size_t half;

    assert(schema != NULL && saved != NULL && loaded != NULL);
    assert(tick != NULL && floaters != NULL && floaters->type >= 0);

    /* Every byte of every type is described. */
    if (!game_session_schema_check(error, sizeof(error))) {
        fprintf(stderr, "%s\n", error);
        return 1;
    }
    assert(game_session_schema_types[game_session_schema_root].size ==
           sizeof(GameSession));
    assert(game_session_schema_write(schema, schema_length) == schema_length);
    assert(game_session_schema_write(schema, schema_length - 1) == 0);

    /* Same layout: every described byte comes back. */
    fill_pattern((unsigned char *)saved, sizeof(GameSession), 1u);
    memset(loaded, 0, sizeof(GameSession));
    assert(game_session_schema_migrate(loaded, schema, schema_length,
                                       (const unsigned char *)saved,
                                       sizeof(GameSession)));
    assert(described_bytes_equal(
        &game_session_schema_types[game_session_schema_root],
        (const unsigned char *)saved, (const unsigned char *)loaded));

    /* A field renamed since the save keeps the loading build's value; the
       others still come back. */
    entry = find_name(schema, schema_length, "simulation_tick");
    assert(entry != NULL);
    entry[2 + strlen("simulation_tick") - 2] = 'o'; /* simulation_tock */
    memset(loaded, 0xab, sizeof(GameSession));
    assert(game_session_schema_migrate(loaded, schema, schema_length,
                                       (const unsigned char *)saved,
                                       sizeof(GameSession)));
    assert(loaded->simulation_tick == 0xababababu);
    assert(loaded->floater_count == saved->floater_count);
    entry[2 + strlen("simulation_tick") - 2] = 'i';

    /* A shorter array in the save: only its prefix is copied. */
    entry = find_name(schema, schema_length, "floaters");
    assert(entry != NULL);
    half = floaters->count / 2;
    {
        unsigned char *count = entry + 2 + strlen("floaters") + 8;
        count[0] = (unsigned char)half;
        count[1] = (unsigned char)(half >> 8);
        count[2] = 0;
        count[3] = 0;
    }
    memset(loaded, 0, sizeof(GameSession));
    assert(game_session_schema_migrate(loaded, schema, schema_length,
                                       (const unsigned char *)saved,
                                       sizeof(GameSession)));
    assert(described_bytes_equal(&game_session_schema_types[floaters->type],
        (const unsigned char *)&saved->floaters[0],
        (const unsigned char *)&loaded->floaters[0]));
    assert(described_bytes_equal(&game_session_schema_types[floaters->type],
        (const unsigned char *)&saved->floaters[half - 1],
        (const unsigned char *)&loaded->floaters[half - 1]));
    {
        GameFloaterStart zero;
        memset(&zero, 0, sizeof(zero));
        assert(memcmp(&loaded->floaters[half], &zero, sizeof(zero)) == 0);
    }

    /* Malformed tables or data sizes are refused. */
    assert(!game_session_schema_migrate(loaded, schema, schema_length / 2,
                                        (const unsigned char *)saved,
                                        sizeof(GameSession)));
    assert(!game_session_schema_migrate(loaded, schema, schema_length,
                                        (const unsigned char *)saved,
                                        sizeof(GameSession) - 1));

    free(schema);
    free(saved);
    free(loaded);
    puts("game session schema: ok");
    return 0;
}
