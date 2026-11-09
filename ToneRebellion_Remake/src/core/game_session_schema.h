#ifndef TONE_GAME_SESSION_SCHEMA_H
#define TONE_GAME_SESSION_SCHEMA_H

#include "game_session_types.h"

#include <stddef.h>
#include <stdint.h>

/* Field layout of GameSession and every struct it contains. A remake save
   stores this table next to the raw session bytes, so a build whose
   GameSession has changed can still copy the fields that kept their name
   (game_session_schema_migrate). game_session_schema.c is generated from
   the headers; when a field is added, add its line there (in declaration
   order): test_game_session_schema fails while a byte is not covered. */
typedef struct GameSessionSchemaField {
    const char *name;
    uint32_t offset;
    uint32_t element_size;
    uint32_t count;
    uint32_t align;
    /* Index in game_session_schema_types for a struct element, else -1. */
    int32_t type;
    /* Scalar element kind in this build (not serialised): lets a save whose
       integer field had another width be converted. */
    uint32_t kind;
} GameSessionSchemaField;

enum {
    GAME_SESSION_SCHEMA_UNSIGNED = 0,
    GAME_SESSION_SCHEMA_SIGNED = 1,
    GAME_SESSION_SCHEMA_FLOAT = 2,
    GAME_SESSION_SCHEMA_STRUCT = 3
};

/* Forward compatibility rules for remake saves (later builds reading older
   files):
   - add, remove or reorder fields freely: absent fields keep the fresh
     session's value; array counts may change (common prefix);
   - renaming a field or a struct type: add a line to
     game_session_schema_renames (game_session_schema_compat.c), never
     remove one;
   - changing an integer field's width is converted when the saved value
     fits, read with the field's current signedness (so a widened unsigned
     field that becomes signed reads its high values as negative: rename it
     instead); other kind changes drop the field;
   - changing what a value means: bump GAME_SESSION_SAVE_REVISION and add
     the conversion to game_session_schema_upgrade. */
enum { GAME_SESSION_SAVE_REVISION = 1 };

/* Old name -> current name. field NULL renames the struct type itself;
   otherwise the field of the (current) type named type. */
typedef struct GameSessionSchemaRename {
    const char *type;
    const char *field;
    const char *old_name;
} GameSessionSchemaRename;

extern const GameSessionSchemaRename game_session_schema_renames[];
extern const uint32_t game_session_schema_rename_count;

typedef struct GameSessionSchemaType {
    const char *name;
    uint32_t size;
    const GameSessionSchemaField *fields;
    uint32_t field_count;
} GameSessionSchemaType;

extern const GameSessionSchemaType game_session_schema_types[];
extern const uint32_t game_session_schema_type_count;
extern const uint32_t game_session_schema_root;

/* Serialised table: returns the byte count, or 0 when it does not fit
   (a NULL buffer only measures). */
size_t game_session_schema_write(unsigned char *buffer, size_t capacity);

/* Copies into session every field of the saved session bytes whose name,
   kind and element size match the current layout (arrays: the common
   prefix). Fields absent from the save keep their current value. Returns 0
   when the saved table or data is malformed. */
int game_session_schema_migrate(GameSession *session,
                                const unsigned char *schema,
                                size_t schema_length,
                                const unsigned char *data,
                                size_t data_length);

/* game_session_schema_migrate with an explicit rename table. */
int game_session_schema_migrate_with(GameSession *session,
                                     const unsigned char *schema,
                                     size_t schema_length,
                                     const unsigned char *data,
                                     size_t data_length,
                                     const GameSessionSchemaRename *renames,
                                     uint32_t rename_count);

/* After a migrate: converts values whose meaning changed between the
   save's revision (session->save_revision, 0 when absent) and
   GAME_SESSION_SAVE_REVISION, then stamps the current revision. */
void game_session_schema_upgrade(GameSession *session);

/* Checks that the fields of every type cover it byte for byte, padding
   aside. Writes the first gap found into error. */
int game_session_schema_check(char *error, size_t error_capacity);

#endif
