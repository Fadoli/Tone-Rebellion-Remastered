#ifndef TONE_REBELLION_GAME_SESSION_DELIVERY_H
#define TONE_REBELLION_GAME_SESSION_DELIVERY_H

#include "game_session.h"
#include "pad_catalog.h"

/* Internal island-tick helpers for the locally modeled Hall type-4 route. */
void game_session_assign_local_resource_tasks(GameSession *session);
/* Assign workers to local CONSTR tasks, deposit Build Tone at their target,
   and place the selected building once its pad.txt cost has arrived. */
void game_session_update_construction_tasks(GameSession *session,
                                             const PadCatalog *catalog);
void game_session_advance_local_resource_task(GameSession *session,
                                               GameFloaterStart *floater);

#endif
