#include "game_session.h"
#include "game_session_events.h"
#include "pad_catalog.h"

#include <string.h>

/* Site On/Off commands and their active-state recalculation. */

int game_session_queue_onoff_action(GameSession *session,
                                    uint8_t player_slot,
                                    uint8_t island_index,
                                    uint16_t location_index)
{
    GameOnOffActionRequest *request;
    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT ||
        island_index >= session->island_count ||
        location_index >= session->islands[island_index].location_count ||
        session->onoff_action_count >= GAME_SESSION_MAX_ONOFF_ACTIONS) {
        return 0;
    }
    request = &session->onoff_actions[session->onoff_action_count++];
    request->player_slot = player_slot;
    request->island_index = island_index;
    request->location_index = location_index;
    return 1;
}

int game_session_pop_onoff_action(GameSession *session,
                                  GameOnOffActionRequest *out)
{
    if (session == NULL || out == NULL || session->onoff_action_count == 0) {
        return 0;
    }
    *out = session->onoff_actions[0];
    --session->onoff_action_count;
    if (session->onoff_action_count != 0) {
        memmove(&session->onoff_actions[0], &session->onoff_actions[1],
                (size_t)session->onoff_action_count * sizeof(session->onoff_actions[0]));
    }
    memset(&session->onoff_actions[session->onoff_action_count], 0,
           sizeof(session->onoff_actions[session->onoff_action_count]));
    return 1;
}

static int game_session_recalculate_location_active(GameRuntimeLocation *location)
{
    uint32_t previous_flags;
    uint32_t current_flags;
    int can_be_active;

    previous_flags = location->source_flags;
    current_flags = previous_flags & ~1U;
    can_be_active = (previous_flags & 0x90U) == 0 &&
        ((previous_flags & 0x400U) != 0 ||
         location->source_location_slot_18 != -1 ||
         location->renderer_class == 1) &&
        ((previous_flags & 0x100U) == 0 || location->source_value_44 < 20) &&
        location->source_value_58 == 0 && location->record_value_10 >= 2;

    if (can_be_active) current_flags |= 1U;
    location->source_flags = current_flags;
    return ((previous_flags ^ current_flags) & 1U) != 0;
}

unsigned int game_session_recalculate_active_locations(GameSession *session)
{
    unsigned int island_index;
    unsigned int changed = 0;

    if (session == NULL) return 0;
    for (island_index = 0; island_index < session->island_count; ++island_index) {
        GameRuntimeIsland *island = &session->islands[island_index];
        unsigned int location_index;

        for (location_index = 0; location_index < island->location_count;
             ++location_index) {
            changed += (unsigned int)game_session_recalculate_location_active(
                &island->locations[location_index]);
        }
    }
    return changed;
}

unsigned int game_session_dispatch_onoff_actions(GameSession *session,
                                                 const PadCatalog *catalog)
{
    GameOnOffActionRequest request;
    unsigned int changed = 0;

    if (session == NULL || catalog == NULL) return 0;
    while (game_session_pop_onoff_action(session, &request)) {
        GameRuntimeLocation *location;
        const PadCatalogItem *item;
        int base_item_id;
        int was_enabled;
        int active_flag_changed;
        unsigned int subtype;

        if (request.player_slot >= GAME_START_PLAYER_COUNT ||
            request.island_index >= session->island_count ||
            request.location_index >=
                session->islands[request.island_index].location_count) {
            continue;
        }
        location = &session->islands[request.island_index]
                        .locations[request.location_index];
        base_item_id = location->record_value_10 -
                       (int)request.player_slot * 16;
        if (location->renderer_class != 0 ||
            location->owner_id != request.player_slot ||
            base_item_id < 0x25 || base_item_id > 0x27) {
            continue;
        }

        was_enabled = (location->source_flags & 0x400U) != 0;
        if ((location->source_flags & 0x400U) != 0) {
            location->source_flags &= ~0x400U;
        } else {
            item = location->record_value_10 >= 0 &&
                   location->record_value_10 <= (int32_t)UINT16_MAX
                ? pad_catalog_find(catalog, (uint16_t)location->record_value_10)
                : NULL;
            if (item != NULL && item->maintenance_tone_cost <=
                    session->economy[request.player_slot].source_maintenance_budget) {
                location->source_flags |= 0x400U;
            }
        }

        /* FUN_00450385 resolves the linked row; FUN_0045cbaa releases its
           subtype 1..3 task links only after the site has ended up OFF. */
        if (location->source_location_slot_18 != -1 &&
            (location->source_flags & 0x400U) == 0) {
            for (subtype = 0; subtype < GAME_RESOURCE_TYPE_COUNT; ++subtype) {
                int16_t linked_slot = location->source_task_slot[subtype];
                if (linked_slot >= 0 &&
                    linked_slot < GAME_SESSION_MAX_PENDING_EVENTS) {
                    (void)game_session_pending_event_release(
                        session, (uint8_t)linked_slot);
                }
                location->source_task_slot[subtype] = -1;
            }
        }
        active_flag_changed = game_session_recalculate_location_active(location);
        if (was_enabled != ((location->source_flags & 0x400U) != 0) ||
            active_flag_changed) ++changed;
    }
    return changed;
}
