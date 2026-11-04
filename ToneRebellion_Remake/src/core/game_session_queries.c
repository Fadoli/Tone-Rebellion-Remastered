#include "game_session.h"
#include "game_session_internal.h"

#include <string.h>

/* FUN_00435581 floater pass: first floater in island-list order whose raw
   +0x1c flag bit 0x1 is clear and whose Chebyshev distance to the click is
   < 20. No owner, type, subtype, death-flag or explored-cell test is made, so
   Leviathans (type 4) and dying floaters stay pickable
   (ev_fd65e30cf8e5016cd62c94f95aa773e60aa16693a519b2f4d4e9c34963c9d2ae).
   Remake deviation: a floater in its bridge animation (state 0x11, +0x34 >= 1)
   is skipped. FUN_0041e569 case 0x10 never sets +0x1c bit 0x1 there
   (ev_348f5497...), so natively it stays pickable while it sits on the bridge
   marker and swallows the bridge click. */
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
        int32_t dy;
        if (!game_session_floater_is_active(floater) ||
            (floater->source_runtime_flags & 0x001U) != 0) continue;
        if (floater->movement_state == 0x11 &&
            (int16_t)floater->order_timer >= 1) continue;
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


uint8_t game_session_active_player_mask(const GameSession *session)
{
    unsigned int building_count[GAME_START_PLAYER_COUNT] = {0};
    uint8_t mask = 0;
    unsigned int i;
    unsigned int j;
    if (session == NULL) return 0;
    for (i = 0; i < session->island_count; ++i) {
        const GameRuntimeIsland *island = &session->islands[i];
        for (j = 0; j < island->location_count; ++j) {
            const GameRuntimeLocation *location = &island->locations[j];
            int32_t owner = location->owner_id;
            int32_t item;
            if (owner < 0 || owner >= GAME_START_PLAYER_COUNT ||
                location->renderer_class != 0) continue;
            item = game_session_base_item_id(location);
            if (item < 0x25 || item > 0x34) continue;
            ++building_count[owner];
            if (location->building_order_genre != 0)
                mask |= (uint8_t)(1U << owner);
        }
    }
    for (i = 0; i < GAME_START_PLAYER_COUNT; ++i)
        if (building_count[i] > 1U) mask |= (uint8_t)(1U << i);
    for (i = 0; i < session->pending_event_count &&
                i < GAME_SESSION_MAX_PENDING_EVENTS; ++i) {
        const GamePendingEvent *event = &session->pending_events[i];
        int recruiter = 0;
        if (!event->active || event->player_id < 0 ||
            event->player_id >= GAME_START_PLAYER_COUNT) continue;
        for (j = 0; j < GAME_RESOURCE_TYPE_COUNT; ++j)
            if (session->economy[event->player_id].resource_task_slot[j] ==
                (int16_t)i) recruiter = 1;
        if (!recruiter) mask |= (uint8_t)(1U << event->player_id);
    }
    return mask;
}

int game_session_end_game_score(const GameSession *session, uint8_t player_slot,
                                GameEndGameScore *score)
{
    static const int32_t weights[4] = {420, 300, 480, 600};
    const GamePlayerEconomy *economy;
    unsigned int count;
    unsigned int total;
    unsigned int percentage;
    unsigned int i;
    int32_t sum;
    int32_t level;

    if (session == NULL || score == NULL ||
        player_slot >= GAME_START_PLAYER_COUNT) return 0;
    /* 0x45f8b7: L = DAT_004bf11c, the New Game level (session block +0x13c,
       cycled 0..4 by message 55), clamped to 0..4: p4 = 50 L. */
    level = session->config.difficulty > 4U ? 4 : (int32_t)session->config.difficulty;
    memset(score, 0, sizeof(*score));
    economy = &session->economy[player_slot];
    for (i = 0; i < session->island_count; ++i) {
        if ((session->islands[i].access_mask &
             (uint8_t)(1U << player_slot)) != 0) ++score->visited_islands;
    }
    for (i = 0; i < GAME_GLYPH_COUNT; ++i) {
        if ((economy->glyph_mask & (uint16_t)(1U << i)) != 0) ++score->glyphs;
    }
    (void)game_session_workstr_summary(session, player_slot, &count, &total,
                                       &percentage);
    score->tribe_floaters = (uint16_t)total;
    score->losses = economy->floater_losses;
    score->points_level = 50 * level;
    score->points_visited = (int32_t)score->visited_islands * 100 / 14;
    score->points_glyphs = (int32_t)score->glyphs * 200 / 14;
    score->points_tribe = total > 100U ? 100 : (int32_t)total;
    score->points_losses = (int32_t)score->losses * 500 / 280;
    sum = score->points_level + score->points_visited + score->points_glyphs +
          score->points_tribe;
    for (i = 0; i < 4U; ++i) {
        /* Native pair k reads the shorts at +0x1480 + 4k and +0x1482 + 4k:
           leviathan subtypes 10 + 2k and 11 + 2k. */
        uint16_t kills = (uint16_t)(economy->leviathan_kills_by_subtype[10 + 2 * i] +
                                    economy->leviathan_kills_by_subtype[11 + 2 * i]);
        score->shadow_total = (uint16_t)(score->shadow_total + kills);
        score->points_kills[i] = (int32_t)kills *
            weights[(i + 4U - (unsigned int)player_slot % 4U) % 4U] / 200;
        sum += score->points_kills[i];
    }
    score->shadow_card_total = (uint16_t)(
        economy->leviathan_kills_by_subtype[9] +
        economy->leviathan_kills_by_subtype[10] +
        economy->leviathan_kills_by_subtype[11] +
        economy->leviathan_kills_by_subtype[12]);
    sum -= score->points_losses;
    score->total = sum < 0 ? 0 : sum;
    {
        int32_t grade = score->total * 10 / 1200;
        score->grade = (uint8_t)(grade > 9 ? 9 : grade < 0 ? 0 : grade);
    }
    return 1;
}

static int game_session_clip_building(const GameSession *session,
                                      uint8_t player_slot, uint8_t island_index,
                                      uint16_t location_index)
{
    const GameRuntimeLocation *location;
    int32_t item;
    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT ||
        island_index >= session->island_count ||
        location_index >= session->islands[island_index].location_count)
        return 0;
    location = &session->islands[island_index].locations[location_index];
    item = location->record_value_10 - location->owner_id * 16;
    return location->owner_id == (int32_t)player_slot &&
           location->source_location_slot_18 != -1 && item >= 0x2c && item <= 0x32;
}

void game_session_clip_remember(GameSession *session, uint8_t player_slot,
                                uint8_t island_index, uint16_t location_index)
{
    unsigned int i;
    unsigned int base;
    if (!game_session_clip_building(session, player_slot, island_index,
                                    location_index)) return;
    for (i = 0; i < 9U; ++i) {
        if (session->clip_slot_used[i] &&
            session->clip_slot_island[i] == island_index &&
            session->clip_slot_location[i] == location_index) return;
    }
    base = (unsigned int)(session->clip_group % 3U) * 3U;
    for (i = 0; i < 3U; ++i) {
        if (!session->clip_slot_used[base + i]) {
            session->clip_slot_used[base + i] = 1;
            session->clip_slot_island[base + i] = island_index;
            session->clip_slot_location[base + i] = location_index;
            return;
        }
    }
}

/* Remake: every training building the player owns gets a shortcut slot (first
   free slot across the three groups), so the strip lists them without having to
   select each one first. */
void game_session_clip_auto_register(GameSession *session, uint8_t player_slot)
{
    unsigned int island_index;
    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT) return;
    for (island_index = 0; island_index < session->island_count; ++island_index) {
        const GameRuntimeIsland *island = &session->islands[island_index];
        unsigned int location_index;
        for (location_index = 0; location_index < island->location_count;
             ++location_index) {
            unsigned int slot;
            int known = 0;
            if (!game_session_clip_building(session, player_slot,
                    (uint8_t)island_index, (uint16_t)location_index)) continue;
            for (slot = 0; slot < 9U; ++slot) {
                if (session->clip_slot_used[slot] &&
                    session->clip_slot_island[slot] == island_index &&
                    session->clip_slot_location[slot] == location_index) {
                    known = 1;
                    break;
                }
            }
            if (known) continue;
            /* Fill the active group first, then the following ones. */
            for (slot = 0; slot < 9U; ++slot) {
                unsigned int candidate =
                    ((unsigned int)(session->clip_group % 3U) * 3U + slot) % 9U;
                if (!session->clip_slot_used[candidate]) {
                    session->clip_slot_used[candidate] = 1;
                    session->clip_slot_island[candidate] = (uint8_t)island_index;
                    session->clip_slot_location[candidate] = (uint16_t)location_index;
                    break;
                }
            }
        }
    }
}

unsigned int game_session_clip_building_count(const GameSession *session,
                                              uint8_t player_slot)
{
    unsigned int island_index;
    unsigned int count = 0;
    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT) return 0;
    for (island_index = 0; island_index < session->island_count; ++island_index) {
        unsigned int location_index;
        for (location_index = 0;
             location_index < session->islands[island_index].location_count;
             ++location_index) {
            if (game_session_clip_building(session, player_slot,
                    (uint8_t)island_index, (uint16_t)location_index)) ++count;
        }
    }
    return count;
}

void game_session_clip_set_group(GameSession *session, unsigned int group)
{
    if (session != NULL && group < 3U) session->clip_group = (uint8_t)group;
}

void game_session_clip_clear_cell(GameSession *session, unsigned int column)
{
    if (session == NULL || column >= 3U) return;
    session->clip_slot_used[(unsigned int)(session->clip_group % 3U) * 3U +
                            column] = 0;
}

unsigned int game_session_clip_slot(GameSession *session, uint8_t player_slot,
                                    unsigned int column, uint8_t *island_index,
                                    uint16_t *location_index)
{
    unsigned int slot;
    if (session == NULL || column >= 3U) return 0;
    slot = (unsigned int)(session->clip_group % 3U) * 3U + column;
    if (!session->clip_slot_used[slot]) return 0;
    if (!game_session_clip_building(session, player_slot,
                                    session->clip_slot_island[slot],
                                    session->clip_slot_location[slot])) {
        session->clip_slot_used[slot] = 0;
        return 0;
    }
    if (island_index != NULL) *island_index = session->clip_slot_island[slot];
    if (location_index != NULL) *location_index = session->clip_slot_location[slot];
    {
        /* Returns the instance number +0x60 plus one (1 when unassigned), so a
           used slot is never 0; FUN_004391ab draws that number minus one. */
        int16_t sub_slot = session->islands[session->clip_slot_island[slot]]
            .locations[session->clip_slot_location[slot]].source_category_slot_60;
        return sub_slot >= 0 ? (unsigned int)sub_slot + 1U : 1U;
    }
}
