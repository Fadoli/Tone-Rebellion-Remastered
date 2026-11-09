/* Hand-kept compatibility data for remake saves (see the rules in
   game_session_schema.h). Entries are never removed: a save written before
   a rename must keep loading in every later build. */
#include "game_session_schema.h"

#include <stddef.h>

/* { current type, current field (NULL: the type itself), old name } */
const GameSessionSchemaRename game_session_schema_renames[] = {
    { NULL, NULL, NULL } /* placeholder: C has no empty arrays */
};
const uint32_t game_session_schema_rename_count = 0;

void game_session_schema_upgrade(GameSession *session)
{
    if (session == NULL) return;
    /* Revision 0 -> 1: no change of meaning (the revision field itself was
       added). Later conversions go here, one block per revision:
       if (session->save_revision < 2) { ... } */
    session->save_revision = GAME_SESSION_SAVE_REVISION;
}
