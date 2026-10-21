#ifndef TONE_REBELLION_GAME_SESSION_DELIVERY_H
#define TONE_REBELLION_GAME_SESSION_DELIVERY_H

#include "game_session.h"
#include "pad_catalog.h"

/* Assign the first eligible task in source slot order for each idle floater. */
void game_session_assign_local_resource_tasks(GameSession *session,
                                               const PadCatalog *catalog);
/* Complete CONSTR tasks whose Build Tone target has reached its pad cost. */
void game_session_update_construction_tasks(GameSession *session,
                                             const PadCatalog *catalog);
void game_session_advance_local_resource_task(GameSession *session,
                                               const PadCatalog *catalog,
                                               GameFloaterStart *floater);
/* Route an active REPAIR task to its next Build Tone pickup source. */
int game_session_start_repair_supply(GameSession *session,
                                     GameFloaterStart *floater);

#endif
