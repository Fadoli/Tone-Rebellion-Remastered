#include "game_session.h"

#include <string.h>

/* Read-only session queries used by island selection and status panels. */
int game_session_floater_at(const GameSession *session,
                            uint8_t island_index,
                            uint16_t x,
                            uint16_t y)
{
    unsigned int i;

    if (session == NULL || island_index >= session->island_count) return -1;
    for (i = 0; i < session->floater_count; ++i) {
        const GameFloaterStart *floater = &session->floaters[i];
        int32_t dx;
        if (!game_session_floater_is_active(floater) ||
            (floater->source_runtime_flags & 0x008U) != 0) continue;
        int32_t dy;

        if (floater->island_index != island_index) continue;
        dx = (int32_t)x - floater->x;
        dy = (int32_t)y - floater->y;
        if (dx < 0) dx = -dx;
        if (dy < 0) dy = -dy;
        if ((dx > dy ? dx : dy) < 20) return (int)i;
    }
    return -1;
}

unsigned int game_session_count_player_floaters(const GameSession *session,
                                                uint8_t player_slot)
{
    unsigned int count = 0;
    unsigned int i;
    unsigned int limit;

    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT) return 0;
    limit = session->floater_count;
    if (limit > GAME_SESSION_MAX_FLOATERS) limit = GAME_SESSION_MAX_FLOATERS;
    for (i = 0; i < limit; ++i) {
        if (game_session_floater_is_active(&session->floaters[i]) &&
            session->floaters[i].owner_slot == player_slot) ++count;
    }
    return count;
}

int game_session_floater_charge_values(const GameFloaterStart *floater,
                                       const FloaterCatalog *catalog,
                                       int16_t *current, int16_t *maximum)
{
    const FloaterStats *stats;
    if (floater == NULL || catalog == NULL || current == NULL ||
        maximum == NULL || floater->source_link_0c == -1) return 0;
    stats = floater_catalog_find(catalog, floater->type_index,
                                 floater->source_subtype);
    if (stats == NULL) return 0;
    *current = floater->charge_current;
    *maximum = stats->max_attack_points;
    return 1;
}

int game_session_workstr_summary(const GameSession *session,
                                 uint8_t type_index,
                                 unsigned int *count,
                                 unsigned int *total,
                                 unsigned int *percentage)
{
    unsigned int subtype_zero = 0;
    unsigned int type_total = 0;
    unsigned int limit;
    unsigned int i;

    if (count != NULL) *count = 0;
    if (total != NULL) *total = 0;
    if (percentage != NULL) *percentage = 0;
    if (session == NULL || type_index >= GAME_START_PLAYER_COUNT ||
        count == NULL || total == NULL || percentage == NULL) return 0;

    limit = session->floater_count;
    if (limit > GAME_SESSION_MAX_FLOATERS) limit = GAME_SESSION_MAX_FLOATERS;
    for (i = 0; i < limit; ++i) {
        const GameFloaterStart *floater = &session->floaters[i];
        if (!game_session_floater_is_active(floater) ||
            floater->type_index != type_index) continue;
        ++type_total;
        if (floater->source_subtype == 0) ++subtype_zero;
    }
    *count = subtype_zero;
    *total = type_total;
    if (type_total > 0) {
        /* Source performs this ratio in floating point and converts the
           nonnegative result to int; integer division has same truncation. */
        *percentage = (subtype_zero * 100U) / type_total;
    }
    return 1;
}

