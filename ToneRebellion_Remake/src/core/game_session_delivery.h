#ifndef TONE_REBELLION_GAME_SESSION_DELIVERY_H
#define TONE_REBELLION_GAME_SESSION_DELIVERY_H

#include "game_session.h"

/* Internal island-tick helpers for the locally modeled Hall type-4 route. */
void game_session_assign_local_resource_tasks(GameSession *session);
void game_session_advance_local_resource_task(GameSession *session,
                                               GameFloaterStart *floater);

#endif
