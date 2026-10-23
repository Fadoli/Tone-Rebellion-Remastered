#include "native_save.h"

#include "game_session_internal.h"
#include "game_session_action9.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    HEADER_SIZE = 0x80,
    HEADER_KEY = 0x000378b8,
    STREAM1_SIZE = 0x148,
    STREAM2_SCALARS = 15 * 4,
    STREAM2_BLOBS = 0x500 + 0x100 + 0x100 + 3 * 0x1e,
    ISLAND_SCALARS = 4 * 4,
    ISLAND_BLOBS = 8 + 0x400 + 0x20 + 0x10 + 0x10 + 0xc,
    SITE_RECORD = 0x60,
    PLAYER_RECORD = 0x14a0,
    GLOBAL_BLOCK = 0x1614,
    FLOATER_RECORD = 0x4c,
    FLOATER_SLOTS = 0x100,
    STREAM3_SIZE = 4 + 0x280,
    /* Offsets inside a player record (P = 0x6191b8 + player * 0x14a0). */
    PLAYER_COUNT_TABLE = 0x44, /* DAT_006191fc: u16 per item id */
    PLAYER_GLYPH_WORD = 0x8a,  /* DAT_00619242 */
    PLAYER_BIRTH_TIMER = 0x8c,
    ROW_BASE = 0xf8,           /* DAT_006192b0: 48 rows of 100 bytes */
    ROW_SIZE = 100,
    PLAYER_POLICY_ROW = 0xd8,    /* DAT_00619290 */
    PLAYER_RECIPIENT_ROW = 0xe8, /* DAT_006192a0 */
    PLAYER_STOCK_MODES = 0x13d0, /* DAT_0061a588: u16 per resource */
    ISLAND_WINDOW_BLOB = 0x408,  /* island +0x408: (min x, max x) per player */
    ISLAND_ACCESS_BLOB = 0x428,
    ISLAND_EVENT_BLOB = 0x438,
    /* FUN_00452859(0x2a, player): the starting Hall. */
    HALL_ITEM_ID = 0x2a
};

static void set_error(char *error, size_t capacity, const char *message)
{
    if (error == NULL || capacity == 0) return;
    (void)snprintf(error, capacity, "%s", message);
    error[capacity - 1] = '\0';
}

static uint16_t u16_at(const uint8_t *p)
{
    return (uint16_t)(p[0] | (p[1] << 8));
}

static uint32_t u32_at(const uint8_t *p)
{
    return (uint32_t)p[0] | ((uint32_t)p[1] << 8) | ((uint32_t)p[2] << 16) |
           ((uint32_t)p[3] << 24);
}

int native_save_parse(const uint8_t *data, size_t size, NativeSave *out,
                      char *error, size_t error_capacity)
{
    NativeSave save;
    size_t cursor;
    unsigned int island;
    if (data == NULL || out == NULL || size < HEADER_SIZE + 12U + STREAM1_SIZE +
                                                  STREAM2_SCALARS) {
        set_error(error, error_capacity, "save file is too short");
        return 0;
    }
    if (memcmp(data, "1.16", 4) != 0 || u32_at(data + 0x7c) != HEADER_KEY) {
        set_error(error, error_capacity, "save header is not a Tone Rebellion save");
        return 0;
    }
    memset(&save, 0, sizeof(save));
    save.data = data;
    save.size = size;
    save.mode = u32_at(data + HEADER_SIZE);
    save.tribe = u32_at(data + HEADER_SIZE + 4);
    save.value_8c = u32_at(data + HEADER_SIZE + 8);
    cursor = HEADER_SIZE + 12U + STREAM1_SIZE;
    save.island_count = u16_at(data + cursor);
    if (save.island_count == 0 || save.island_count > NATIVE_SAVE_MAX_ISLANDS) {
        set_error(error, error_capacity, "save island count is out of range");
        return 0;
    }
    save.stream2_offset = cursor;
    cursor += STREAM2_SCALARS + STREAM2_BLOBS;
    for (island = 0; island < save.island_count; ++island) {
        uint16_t sites;
        if (cursor + ISLAND_SCALARS + ISLAND_BLOBS > size) {
            set_error(error, error_capacity, "save is truncated in the island table");
            return 0;
        }
        sites = u16_at(data + cursor);
        if (sites > ISLAND_DATA_MAX_LOCATIONS) {
            set_error(error, error_capacity, "save island has too many sites");
            return 0;
        }
        save.island_offset[island] = cursor;
        cursor += ISLAND_SCALARS + ISLAND_BLOBS;
        if (cursor + (size_t)sites * SITE_RECORD > size) {
            set_error(error, error_capacity, "save is truncated in the site records");
            return 0;
        }
        save.site_count[island] = sites;
        save.site_offset[island] = cursor;
        cursor += (size_t)sites * SITE_RECORD;
    }
    save.player_offset = cursor;
    save.global_offset = cursor + 4U * PLAYER_RECORD;
    save.floater_offset = save.global_offset + GLOBAL_BLOCK;
    cursor = save.floater_offset + (size_t)FLOATER_SLOTS * FLOATER_RECORD +
             STREAM3_SIZE;
    if (cursor > size) {
        set_error(error, error_capacity, "save is truncated after the floater table");
        return 0;
    }
    *out = save;
    return 1;
}

int native_save_find_world(const NativeSave *save, const WorldMap *worlds)
{
    unsigned int index;
    if (save == NULL || worlds == NULL) return -1;
    for (index = 0; index < worlds->world_count; ++index) {
        if (worlds->worlds[index].island_count == save->island_count)
            return (int)index;
    }
    return -1;
}

static void apply_site(GameRuntimeLocation *site, const uint8_t *rec)
{
    int32_t item = (int32_t)u32_at(rec + 0x10);
    int32_t owner = (int32_t)u32_at(rec + 0x14);
    site->source_value_14 = owner;
    site->owner_id = owner;
    /* The port keeps owner-specific PAD IDs in record_value_10; native +0x10
       is the base item (game_session_base_item_id). */
    if (owner >= 0 && owner < GAME_START_PLAYER_COUNT && item > 1)
        item += owner * 16;
    site->record_value_10 = item;
    site->source_progress_08 = u16_at(rec + 0x08);
    site->source_level_flags = u16_at(rec + 0x0a);
    site->source_location_slot_18 = (int16_t)u16_at(rec + 0x18);
    site->source_flags = u32_at(rec + 0x1c);
    site->source_value_22 = u16_at(rec + 0x22);
    site->tribe_visibility_mask = (uint8_t)site->source_value_22;
    site->record_value_24 = (int32_t)u32_at(rec + 0x24);
    if (owner >= 0 && owner < GAME_START_PLAYER_COUNT &&
        item - owner * 16 == HALL_ITEM_ID) {
        unsigned int resource;
        for (resource = 0; resource < GAME_RESOURCE_TYPE_COUNT; ++resource)
            site->resource_stock[resource] = u16_at(rec + 0x28 + resource * 2U);
    }
    site->charge_source_value_30 = u16_at(rec + 0x30);
    site->source_value_32 = (int16_t)u16_at(rec + 0x32);
    site->source_value_34 = (int16_t)u16_at(rec + 0x34);
    site->resource_retry_tick_36 = (int16_t)u16_at(rec + 0x36);
    site->source_effect_timer_38 = u32_at(rec + 0x38);
    site->source_value_3a = (int16_t)u16_at(rec + 0x3a);
    site->source_value_3c = (int16_t)u16_at(rec + 0x3c);
    site->source_value_3e = (int16_t)u16_at(rec + 0x3e);
    site->source_value_40 = (int16_t)u16_at(rec + 0x40);
    site->source_value_42 = (int16_t)u16_at(rec + 0x42);
    site->source_value_44 = (int16_t)u16_at(rec + 0x44);
    site->source_value_46 = (int16_t)u16_at(rec + 0x46);
    site->source_value_48 = (int16_t)u16_at(rec + 0x48);
    site->source_capacity_4a = (int16_t)u16_at(rec + 0x4a);
    site->source_value_58 = (int16_t)u16_at(rec + 0x58);
    {
        /* BARG gauge (+0x50 double, 0..1 while a staff floater trains). */
        double barg;
        memcpy(&barg, rec + 0x50, sizeof(barg));
        site->barg_progress = barg >= 0.0 && barg <= 1.0 ? barg : 0.0;
    }
    /* FUN_004669bd sets bit 0 on both paired class-2 bridge objects. */
    site->bridge_constructed = site->renderer_class == 2 && (site->source_flags & 1U) != 0;
}

/* The owner's 100-byte source row for a site (P + 0xf8 + slot * 100, with the
   site's +0x18 as slot). Row +0 / +2 name the island and location it belongs
   to; a row that disagrees is ignored. */
static const uint8_t *source_row(const NativeSave *save, unsigned int island,
                                 unsigned int location,
                                 const GameRuntimeLocation *site)
{
    const uint8_t *row;
    if (site->owner_id < 0 || site->owner_id >= GAME_START_PLAYER_COUNT ||
        site->source_location_slot_18 < 0 ||
        site->source_location_slot_18 >= GAME_SOURCE_RECORDS_PER_PLAYER)
        return NULL;
    row = save->data + save->player_offset +
          (size_t)site->owner_id * PLAYER_RECORD + ROW_BASE +
          (size_t)site->source_location_slot_18 * ROW_SIZE;
    if (u16_at(row) != island || u16_at(row + 2) != location) return NULL;
    return row;
}

static int16_t live_task_handle(const GameSession *session, int16_t handle)
{
    return handle >= 0 && handle < GAME_SESSION_MAX_PENDING_EVENTS &&
           session->pending_events[handle].active != 0 ? handle : -1;
}

static void apply_source_row(const GameSession *session,
                             GameRuntimeLocation *site, const uint8_t *row)
{
    unsigned int link;
    site->upgrade_task_handle = live_task_handle(session, (int16_t)u16_at(row + 0x4e));
    site->charge_staff_task_handle = live_task_handle(session, (int16_t)u16_at(row + 0x50));
    for (link = 0; link < 8; ++link)
        site->charge_floater_slots[link] = (int16_t)u16_at(row + 4 + link * 2U);
    site->charge_floater_count = u16_at(row + 0x24);
    if (site->charge_floater_count > 8) site->charge_floater_count = 8;
    site->building_order_island = (uint8_t)u32_at(row + 0x28);
    site->building_order_genre = (uint8_t)u32_at(row + 0x2c);
    site->building_order_coordinate = (uint16_t)u32_at(row + 0x30);
    site->training_stock_crystal = (uint8_t)u32_at(row + 0x58);
    site->training_stock_magic = (uint8_t)u32_at(row + 0x5c);
    site->source_category_slot_60 = (int16_t)u16_at(row + 0x60);
    site->charge_recent_floater = (int16_t)u16_at(row + 0x4c);
}

/* Per-player words of the 0x14a0 record. */
typedef struct PlayerMasks {
    uint8_t policy;
    uint8_t recipient;
} PlayerMasks;

static void apply_player_record(GamePlayerEconomy *economy, PlayerMasks *economy_masks,
                                const uint8_t *player)
{
    unsigned int item;
    economy->glyph_mask = u16_at(player + PLAYER_GLYPH_WORD);
    economy->special_feature_island_mask = economy->glyph_mask;
    /* DAT_00619290 (policy, set = friend) and DAT_006192a0 (message recipient):
       one dword per target player at P+0xd8 / P+0xe8. The original game has no
       enemy tribes, so its saved rows are all friends, own tribe included. */
    economy_masks->policy = 0;
    economy_masks->recipient = 0;
    for (item = 0; item < GAME_START_PLAYER_COUNT; ++item) {
        if (u32_at(player + PLAYER_POLICY_ROW + item * 4U) != 0)
            economy_masks->policy |= (uint8_t)(1U << item);
        if (u32_at(player + PLAYER_RECIPIENT_ROW + item * 4U) != 0)
            economy_masks->recipient |= (uint8_t)(1U << item);
    }
    economy->floater_birth_timer = u32_at(player + PLAYER_BIRTH_TIMER);
    for (item = 0; item < GAME_RESOURCE_TYPE_COUNT; ++item) {
        uint16_t mode = u16_at(player + PLAYER_STOCK_MODES + item * 2U);
        economy->stock_mode[item] = mode > 2U ? 1U : (uint8_t)mode;
        economy->resource_task_slot[item] = -1;
    }
    for (item = 0; item < GAME_INVENTORY_ITEM_COUNT; ++item)
        economy->inventory_count[item] = u16_at(
            player + PLAYER_COUNT_TABLE +
            (GAME_INVENTORY_ITEM_FIRST_ID + item) * 2U);
}

/* Stream 2 blob +0x2c1a4: 64 task records of 0x14 bytes, the layout of
   GamePendingEvent. Workers are not carrying their order across the load, so
   the attached-worker counts restart at zero; tasks naming a missing island
   or site are dropped. */
static void apply_events(const NativeSave *save, GameSession *session)
{
    const uint8_t *table = save->data + save->stream2_offset + STREAM2_SCALARS;
    unsigned int slot;
    memset(session->pending_events, 0, sizeof(session->pending_events));
    session->pending_event_count = 0;
    for (slot = 0; slot < GAME_SESSION_MAX_PENDING_EVENTS; ++slot) {
        const uint8_t *rec = table + (size_t)slot * 0x14U;
        GamePendingEvent *event = &session->pending_events[slot];
        int16_t island;
        int16_t location;
        if (u32_at(rec) == 0) continue;
        island = (int16_t)u16_at(rec + 0x0a);
        location = (int16_t)u16_at(rec + 0x0e);
        if (island < 0 || island >= session->island_count || location < 0 ||
            location >= session->islands[island].location_count) continue;
        event->active = 1;
        event->assigned_floater_count = 0;
        event->priority = u16_at(rec + 0x06);
        event->player_id = (int16_t)u16_at(rec + 0x08);
        event->payload_0a = island;
        event->payload_0c = (int16_t)u16_at(rec + 0x0c);
        event->payload_0e = location;
        event->action_type = (int16_t)u16_at(rec + 0x10);
        event->payload_12 = (int16_t)u16_at(rec + 0x12);
        ++session->pending_event_count;
    }
}

/* Hall refill requests (action 4) are referenced by the Hall's resource slot. */
static void link_hall_requests(GameSession *session)
{
    unsigned int slot;
    for (slot = 0; slot < GAME_SESSION_MAX_PENDING_EVENTS; ++slot) {
        const GamePendingEvent *event = &session->pending_events[slot];
        GamePlayerEconomy *economy;
        if (event->active == 0 || event->action_type != 4 ||
            event->player_id < 0 || event->player_id >= GAME_START_PLAYER_COUNT ||
            event->payload_12 < 1 || event->payload_12 > GAME_RESOURCE_TYPE_COUNT)
            continue;
        economy = &session->economy[event->player_id];
        if (event->payload_0a == economy->hall_island_index &&
            event->payload_0e == economy->hall_location_index) {
            economy->resource_task_slot[event->payload_12 - 1] = (int16_t)slot;
            economy->stock_mode[event->payload_12 - 1] = 2;
        }
    }
}

/* Island blobs: +0x408 per-player wander window, +0x428 access dwords,
   +0x438 per-player event words (island +0x29ac / +0x29bc). */
static void apply_islands(const NativeSave *save, GameSession *session)
{
    unsigned int island;
    for (island = 0; island < session->island_count; ++island) {
        const uint8_t *base = save->data + save->island_offset[island] +
                              ISLAND_SCALARS;
        GameRuntimeIsland *runtime = &session->islands[island];
        unsigned int player;
        runtime->access_mask = 0;
        for (player = 0; player < GAME_START_PLAYER_COUNT; ++player) {
            if (u32_at(base + ISLAND_ACCESS_BLOB + player * 4U) != 0)
                runtime->access_mask |= (uint8_t)(1U << player);
            runtime->source_event_state[player] =
                u32_at(base + ISLAND_EVENT_BLOB + player * 4U);
            runtime->source_event3_pending_parity[player] = 0;
            runtime->floater_min_x[player] =
                (int32_t)u32_at(base + ISLAND_WINDOW_BLOB + player * 8U);
            runtime->floater_max_x[player] =
                (int32_t)u32_at(base + ISLAND_WINDOW_BLOB + player * 8U + 4U);
        }
    }
}

/* Stream 2 blob +0x2749c: one {active dword, island a, island b} entry per
   WORLDPOS bridge, in file order. */
static void apply_bridges(const NativeSave *save, GameSession *session)
{
    const uint8_t *table = save->data + save->stream2_offset + STREAM2_SCALARS +
                           0x500U;
    unsigned int bridge;
    session->active_bridge_mask = 0;
    for (bridge = 0; bridge < session->world_bridge_count && bridge < 32U;
         ++bridge) {
        const uint8_t *entry = table + (size_t)bridge * 8U;
        const WorldBridge *topology = &session->world_bridges[bridge];
        if (u16_at(entry + 4) != topology->island_a ||
            u16_at(entry + 6) != topology->island_b) continue;
        if (u32_at(entry) != 0)
            session->active_bridge_mask |= UINT32_C(1) << bridge;
    }
}

/* Refills the per-player Hall bookkeeping from the restored sites. */
static void rebuild_halls(GameSession *session)
{
    unsigned int island;
    unsigned int player;
    /* The original game has no Hall for tribes that do not play; the port's
       guards treat an out-of-range island as "no Hall". */
    for (player = 0; player < GAME_START_PLAYER_COUNT; ++player)
        session->economy[player].hall_island_index = UINT8_MAX;
    for (island = 0; island < session->island_count; ++island) {
        GameRuntimeIsland *runtime = &session->islands[island];
        unsigned int location;
        for (location = 0; location < runtime->location_count; ++location) {
            const GameRuntimeLocation *site = &runtime->locations[location];
            if (site->owner_id >= 0 && site->owner_id < GAME_START_PLAYER_COUNT &&
                game_session_base_item_id(site) == HALL_ITEM_ID) {
                GamePlayerEconomy *economy = &session->economy[site->owner_id];
                economy->hall_island_index = (uint8_t)island;
                economy->hall_location_index = (uint16_t)location;
                economy->hall_x = site->x;
                economy->hall_y = site->y;
            }
        }
    }
}

static int16_t i16_at(const uint8_t *p)
{
    return (int16_t)u16_at(p);
}

/* Resource (action 4) and construction-supply (action 5) tasks. Native
   record: +0x38 task slot, +0x40 / +0x42 target island / site, +0x44 the
   task's payload (resource code, or the item to build), +0x30 resource code,
   +0x32 the site being walked to (state 3: pickup source, state 4: target),
   +0x34 timer, +0x46 phase (0 fetching, 1 delivering). The port models both
   as action 4 (construction uses resource code 1). State 0x11 is the
   inter-island hand-off: +0x30 island and +0x32 bridge site. A floater whose
   task no longer matches keeps the idle default. Returns 1 when restored. */
static int restore_task_order(GameSession *session, GameFloaterStart *floater,
                              const uint8_t *rec, uint32_t state,
                              uint32_t action)
{
    int32_t slot = (int32_t)u32_at(rec + 0x38);
    uint16_t target_island = u16_at(rec + 0x40);
    int16_t target_location = i16_at(rec + 0x42);
    int16_t payload = i16_at(rec + 0x44);
    int progress = (int16_t)u16_at(rec + 0x46) != 0;
    GamePendingEvent *event;
    const GameRuntimeIsland *island;

    if ((action != 4 && action != 5) || (state != 3 && state != 4 && state != 0x11) ||
        slot < 0 || slot >= GAME_SESSION_MAX_PENDING_EVENTS ||
        floater->island_index >= session->island_count) return 0;
    event = &session->pending_events[slot];
    if (event->active == 0 || event->action_type != (action == 4 ? 4 : 5) ||
        event->player_id != floater->owner_slot ||
        event->payload_0a != (int16_t)target_island ||
        event->payload_0e != target_location || event->payload_12 != payload ||
        target_island >= session->island_count || target_location < 0 ||
        target_location >= session->islands[target_island].location_count)
        return 0;
    island = &session->islands[floater->island_index];

    floater->order_resource_code = action == 4 ? payload : 1;
    floater->order_target_island = (uint8_t)target_island;
    floater->order_target_location = target_location;
    floater->order_source_island = floater->island_index;
    floater->order_source_location = -1;
    floater->order_progress = progress ? 1U : 0U;
    floater->order_timer = u16_at(rec + 0x34);
    floater->destination_x = u16_at(rec + 0x28);
    floater->destination_y = u16_at(rec + 0x2a);
    floater->stop_radius = 0;
    floater->has_wander_order = 0;
    floater->wander_timer = 0;

    if (state == 3 || state == 4) {
        int16_t site = i16_at(rec + 0x32);
        if (state == 3) {
            if (site < 0 || site >= island->location_count) return 0;
            floater->order_source_location = site;
        }
        floater->active_order_action = 4;
        floater->movement_state = (uint8_t)state;
        floater->has_move_order = 1;
    } else {
        uint32_t handoff_island = u16_at(rec + 0x30);
        int16_t departure = i16_at(rec + 0x32);
        if (handoff_island >= session->island_count ||
            handoff_island == floater->island_index || departure < 0 ||
            departure >= island->location_count) return 0;
        floater->handoff_target_island = (uint8_t)handoff_island;
        floater->handoff_departure_location = departure;
        floater->handoff_resume_action = 4;
        floater->handoff_resume_state = progress ? 4 : 3;
        if (!progress) {
            const GamePlayerEconomy *economy = &session->economy[floater->owner_slot];
            floater->order_source_island = (uint8_t)handoff_island;
            if (economy->hall_island_index == handoff_island)
                floater->order_source_location = (int16_t)economy->hall_location_index;
        }
        floater->active_order_action = 9;
        floater->movement_state = 0x11;
        floater->has_move_order = 1;
    }
    floater->linked_task_slot = (int16_t)slot;
    if (event->assigned_floater_count < INT16_MAX) ++event->assigned_floater_count;
    return 1;
}

/* FA_Recharge (action 2, state 2): the unit waits at a linked site and
   withdraws one resource. +0x40 / +0x42 name the island and site, +0x30 the
   requested code, +0x34 the wait counter. */
static int restore_recharge_order(const GameSession *session,
                                  GameFloaterStart *floater, const uint8_t *rec)
{
    int16_t site = i16_at(rec + 0x42);
    if (u16_at(rec + 0x40) != floater->island_index ||
        floater->island_index >= session->island_count || site < 0 ||
        site >= session->islands[floater->island_index].location_count)
        return 0;
    floater->active_order_action = 2;
    floater->movement_state = 2;
    floater->order_target_island = floater->island_index;
    floater->order_target_location = site;
    floater->source_order_coordinate_30 = u16_at(rec + 0x30);
    floater->order_timer = u16_at(rec + 0x34);
    floater->destination_x = u16_at(rec + 0x28);
    floater->destination_y = u16_at(rec + 0x2a);
    floater->stop_radius = 0;
    floater->has_move_order = floater->destination_x != floater->x ||
                              floater->destination_y != floater->y;
    floater->has_wander_order = 0;
    return 1;
}

/* Category-4 subtype 9 attack-site order (action 1, state 1): +0x40 island,
   +0x42 / +0x32 target site, destination in +0x28 / +0x2a. */
static int restore_leviathan_site_order(const GameSession *session,
                                        GameFloaterStart *floater,
                                        const uint8_t *rec)
{
    int16_t site = i16_at(rec + 0x42);
    if (floater->type_index != 4U || floater->source_subtype != 9U ||
        u16_at(rec + 0x40) != floater->island_index ||
        floater->island_index >= session->island_count || site < 0 ||
        site >= session->islands[floater->island_index].location_count)
        return 0;
    floater->active_order_action = 1;
    floater->order_target_location = site;
    floater->order_target_floater = -1;
    floater->order_target_island = floater->island_index;
    floater->source_order_parameter_32 = (uint16_t)site;
    floater->order_progress = 1;
    floater->movement_state = 1;
    floater->stop_radius = 0;
    floater->destination_x = u16_at(rec + 0x28);
    floater->destination_y = u16_at(rec + 0x2a);
    floater->has_move_order = 1;
    floater->has_wander_order = 0;
    return 1;
}

/* Attack / defend orders (docs: MOVEMENT_LOCAL_ATTACK.md, MOVEMENT_LOCAL_DEFEND.md).
   Targets are floater slots, which keep their file numbering, so this runs
   after every floater exists. The saves available hold no such order; the
   mapping follows the documented encoding and is unverified on real data.
   +0x42 target (floater or site), +0x32 the current approach target, +0x46
   progress (-1 once the strike state runs; the port stores 2). */
static void restore_combat_order(GameSession *session, unsigned int slot,
                                 const uint8_t *rec)
{
    GameFloaterStart *floater = &session->floaters[slot];
    uint32_t state = u32_at(rec + 0x2c);
    uint32_t action = u32_at(rec + 0x3c);
    int16_t target = i16_at(rec + 0x42);
    int16_t current = i16_at(rec + 0x32);
    int16_t progress = i16_at(rec + 0x46);

    if (!game_session_floater_is_active(floater) || floater->type_index == 4U ||
        floater->island_index >= session->island_count) return;
    if (action == 7 && (state == 0x10 || state == 7)) {
        const GameRuntimeLocation *site;
        if (target < 0 ||
            target >= session->islands[floater->island_index].location_count)
            return;
        site = &session->islands[floater->island_index].locations[target];
        floater->active_order_action = 7;
        floater->order_target_location = target;
        floater->order_target_floater = -1;
        floater->order_target_island = floater->island_index;
        floater->movement_state = (uint8_t)state;
        if (state == 0x10) {
            floater->stop_radius = game_session_floater_approach_radius(session, floater);
            game_session_set_approach_point(floater, site->x, site->y);
            floater->order_progress = 1;
            floater->has_move_order = 1;
        } else {
            floater->order_progress = progress == -1 ? 2 : 1;
            floater->has_move_order = 0;
        }
    } else if ((action == 6 || action == 8) &&
               (state == 0x0f || state == 6 || state == 8)) {
        int16_t victim_index = action == 8 && state == 8 ? target : current;
        const GameFloaterStart *victim;
        if (victim_index < 0 || (unsigned int)victim_index >= session->floater_count ||
            (unsigned int)victim_index == slot) return;
        victim = &session->floaters[victim_index];
        if (!game_session_floater_is_active(victim) ||
            (victim->source_runtime_flags & 0x008U) != 0 ||
            victim->island_index != floater->island_index) return;
        floater->active_order_action = (uint8_t)action;
        floater->order_target_floater = victim_index;
        floater->defend_target_floater = action == 8 ? target : -1;
        floater->order_target_location = -1;
        floater->order_target_island = action == 8 && state == 8
            ? UINT8_MAX : floater->island_index;
        floater->movement_state = (uint8_t)state;
        if (state == 8) {
            floater->follow_offset_x = i16_at(rec + 0x28);
            floater->follow_offset_y = i16_at(rec + 0x2a);
            floater->order_progress = 1;
            floater->stop_radius = 0;
            floater->has_move_order = 1;
        } else if (state == 0x0f) {
            floater->stop_radius = game_session_floater_approach_radius(session, floater);
            game_session_set_approach_point(floater, victim->x, victim->y);
            floater->order_progress = action == 8 ? 2 : 1;
            floater->has_move_order = 1;
        } else {
            floater->order_progress = progress == -1 ? 2 : 1;
            floater->has_move_order = 0;
        }
    } else {
        return;
    }
    floater->has_wander_order = 0;
    floater->wander_timer = 0;
    floater->order_timer = 0;
}

static int apply_floater(GameSession *session, const FloaterCatalog *catalog,
                         unsigned int slot, const uint8_t *rec,
                         char *error, size_t error_capacity)
{
    GameFloaterStart *floater = &session->floaters[slot];
    int32_t owner = (int32_t)u32_at(rec);
    uint32_t subtype = u32_at(rec + 4);
    uint16_t island = u16_at(rec + 0x0e);
    const FloaterStats *stats;
    uint8_t type_index;

    if (owner < 0 || owner > GAME_START_PLAYER_COUNT || subtype > 0x11U ||
        island >= session->island_count) {
        set_error(error, error_capacity, "save floater record is out of range");
        return 0;
    }
    type_index = owner == GAME_START_PLAYER_COUNT
        ? 4 : session->player_starts.players[owner].floater_type_index;
    stats = floater_catalog_find(catalog, type_index, (int)subtype);
    if (stats == NULL || stats->hit_points < 0 ||
        stats->hit_points > (int16_t)UINT8_MAX ||
        stats->attack_strength < 0 ||
        stats->attack_strength > (int16_t)UINT8_MAX ||
        stats->movement_speed < 0) {
        set_error(error, error_capacity, "save floater type is not in the catalog");
        return 0;
    }
    memset(floater, 0, sizeof(*floater));
    floater->is_active = 1;
    floater->island_index = (uint8_t)island;
    floater->type_index = type_index;
    floater->source_subtype = (uint8_t)subtype;
    floater->owner_slot = (uint8_t)owner;
    /* The native record carries no hit-point field that is decoded yet. */
    floater->current_hit_points = stats->hit_points;
    floater->max_hit_points = stats->hit_points;
    floater->attack_strength = (uint8_t)stats->attack_strength;
    floater->max_attack_points = stats->max_attack_points;
    floater->base_max_attack_points = stats->max_attack_points;
    floater->attack_realm = stats->attack_realm;
    if (stats->attack_realm >= 0 && stats->attack_realm < 4) {
        memcpy(floater->attack_impact_frame_counts,
               catalog->impact_frame_counts[stats->attack_realm],
               sizeof(floater->attack_impact_frame_counts));
    }
    floater->attack_range = stats->attack_range;
    floater->attack_period = stats->attack_period;
    floater->attack_frame_first = stats->attack_frame_first;
    floater->attack_frame_last = stats->attack_frame_last;
    floater->attack_frame_ticks_per_frame = stats->attack_frame_ticks_per_frame;
    floater->attack_frame_duration = stats->attack_frame_duration;
    floater->attack_frame_ping_pong = stats->attack_frame_ping_pong;
    floater->movement_speed = (uint16_t)stats->movement_speed;
    floater->source_progress_08 = u16_at(rec + 0x08);
    floater->attack_level_flags = u16_at(rec + 0x0a);
    floater->x = u16_at(rec + 0x10);
    floater->y = u16_at(rec + 0x12);
    floater->animation_seed = rec[0x14];
    floater->carried_resource_code = (int16_t)u16_at(rec + 0x18);
    floater->source_runtime_flags = u32_at(rec + 0x1c);
    floater->charge_current = (int16_t)u16_at(rec + 0x22);
    floater->source_death_timer = u16_at(rec + 0x24);
    floater->destination_x = floater->x;
    floater->destination_y = floater->y;
    /* +0x0c is the index of the linked building's source row (FUN_0045c325);
       the row names the island and location. Orders (+0x2c..+0x46) and tasks
       (+0x38) are not restored: the unit resumes from idle and its link. */
    floater->source_link_0c = -1;
    floater->charge_source_island = UINT8_MAX;
    floater->charge_source_location = UINT16_MAX;
    {
        int16_t link = (int16_t)u16_at(rec + 0x0c);
        if (owner < GAME_START_PLAYER_COUNT && link >= 0 &&
            link < GAME_SOURCE_RECORDS_PER_PLAYER) {
            unsigned int island_index;
            for (island_index = 0; island_index < session->island_count;
                 ++island_index) {
                const GameRuntimeIsland *runtime = &session->islands[island_index];
                unsigned int location;
                for (location = 0; location < runtime->location_count; ++location) {
                    const GameRuntimeLocation *site = &runtime->locations[location];
                    if (site->owner_id == owner &&
                        site->source_location_slot_18 == link) {
                        floater->source_link_0c = link;
                        floater->charge_source_island = (uint8_t)island_index;
                        floater->charge_source_location = (uint16_t)location;
                    }
                }
            }
        }
    }
    floater->linked_task_slot = -1;
    floater->order_source_location = -1;
    floater->order_target_location = -1;
    floater->order_target_floater = -1;
    floater->order_target_island = floater->island_index;
    floater->order_source_island = floater->island_index;
    floater->handoff_departure_location = -1;
    floater->has_wander_order = 1;
    {
        /* Runtime state +0x2c and action +0x3c. In 8 saves the states seen
           are 0xe/0xe (wander, 529 floaters), 9/9 (hold the building's defend
           area, 130), resource states 3/4 with actions 4/5 (tasks, not
           restored), and a handful of others, which restart from idle. */
        uint32_t state = u32_at(rec + 0x2c);
        uint32_t action = u32_at(rec + 0x3c);
        if (state == 0x0e && action == 0x0e) {
            floater->movement_state = 0x0e;
            floater->active_order_action = 0x0e;
            floater->order_target_island = (uint8_t)u16_at(rec + 0x40);
            floater->destination_x = u16_at(rec + 0x28);
            floater->destination_y = u16_at(rec + 0x2a);
            floater->wander_timer = u16_at(rec + 0x34);
            floater->facing_left = floater->destination_x < floater->x;
        } else if (state == 9 && action == 9 && owner < GAME_START_PLAYER_COUNT &&
                   u16_at(rec + 0x30) == floater->island_index) {
            /* +0x30 is the island and +0x32 the packed (x/10, y/10) anchor of
               the Hall order; the port keeps both in the source_order_*
               fields (game_session_adopt_building_order). */
            floater->movement_state = 9;
            floater->active_order_action = 9;
            floater->source_order_state_2c = 9;
            floater->source_order_island_28 = floater->island_index;
            floater->source_order_coordinate_30 = u16_at(rec + 0x32);
            floater->destination_x = u16_at(rec + 0x28);
            floater->destination_y = u16_at(rec + 0x2a);
            floater->stop_radius = 0;
            floater->has_move_order = 1;
            floater->has_wander_order = 0;
            floater->order_progress = 1;
            floater->facing_left = floater->destination_x < floater->x;
        } else if (owner < GAME_START_PLAYER_COUNT &&
                   restore_task_order(session, floater, rec, state, action)) {
            floater->facing_left = floater->destination_x < floater->x;
        } else if (owner < GAME_START_PLAYER_COUNT && state == 2 && action == 2 &&
                   restore_recharge_order(session, floater, rec)) {
            floater->facing_left = floater->destination_x < floater->x;
        } else if (owner == GAME_START_PLAYER_COUNT && state == 1 && action == 1 &&
                   restore_leviathan_site_order(session, floater, rec)) {
            floater->facing_left = floater->destination_x < floater->x;
        }
    }
    game_session_recalculate_floater_attack_points(session, floater);
    /* HITS (FUN_0044338b): +0x20 is the current value and FUN_00420f28 the
       maximum, i.e. the catalog hit-point column scaled by level (and the
       glyph / building bonuses). FUN_00420f28 is the function the port
       evaluates with game_session_recalculate_floater_attack_points, which
       takes the charge column: run it once over the hit-point column. */
    {
        int16_t saved_base = floater->base_max_attack_points;
        int16_t saved_charge_max = floater->max_attack_points;
        int32_t current = (int16_t)u16_at(rec + 0x20);
        floater->base_max_attack_points = stats->hit_points;
        game_session_recalculate_floater_attack_points(session, floater);
        floater->max_hit_points = floater->max_attack_points > 0
            ? floater->max_attack_points : stats->hit_points;
        floater->base_max_attack_points = saved_base;
        floater->max_attack_points = saved_charge_max;
        if (current < 0) current = 0;
        if (current > floater->max_hit_points) current = floater->max_hit_points;
        floater->current_hit_points = (int16_t)current;
    }
    return 1;
}

int native_save_apply(const NativeSave *save, const FloaterCatalog *floaters,
                      GameSession *session, char *error, size_t error_capacity)
{
    GameSession *next;
    unsigned int island;
    unsigned int slot;
    unsigned int highest = 0;
    int ok = 0;

    if (save == NULL || floaters == NULL || session == NULL) return 0;
    if (save->island_count != session->island_count) {
        set_error(error, error_capacity,
                  "save island count differs from the selected world");
        return 0;
    }
    for (island = 0; island < session->island_count; ++island) {
        if (save->site_count[island] != session->islands[island].location_count) {
            set_error(error, error_capacity,
                      "save site count differs from the island layout");
            return 0;
        }
    }
    next = (GameSession *)malloc(sizeof(*next));
    if (next == NULL) {
        set_error(error, error_capacity, "could not allocate the restored session");
        return 0;
    }
    *next = *session;
    for (island = 0; island < next->island_count; ++island) {
        unsigned int site;
        for (site = 0; site < save->site_count[island]; ++site)
            apply_site(&next->islands[island].locations[site],
                       save->data + save->site_offset[island] +
                           (size_t)site * SITE_RECORD);
    }
    apply_events(save, next);
    next->simulation_tick = u32_at(save->data + save->stream2_offset + 4U * 4U);
    for (island = 0; island < next->island_count; ++island) {
        unsigned int site;
        for (site = 0; site < save->site_count[island]; ++site) {
            GameRuntimeLocation *runtime = &next->islands[island].locations[site];
            const uint8_t *row = source_row(save, island, site, runtime);
            if (row != NULL) apply_source_row(next, runtime, row);
        }
    }
    apply_islands(save, next);
    apply_bridges(save, next);
    for (slot = 0; slot < GAME_START_PLAYER_COUNT; ++slot) {
        PlayerMasks masks;
        apply_player_record(&next->economy[slot], &masks, save->data +
                            save->player_offset + (size_t)slot * PLAYER_RECORD);
        next->diplomacy_policy_mask[slot] = masks.policy;
        next->message_recipient_mask[slot] = masks.recipient;
    }
    rebuild_halls(next);
    link_hall_requests(next);
    memset(next->floaters, 0, sizeof(next->floaters));
    for (slot = 0; slot < FLOATER_SLOTS; ++slot) {
        const uint8_t *rec = save->data + save->floater_offset +
                             (size_t)slot * FLOATER_RECORD;
        if ((int32_t)u32_at(rec) == -1) continue;
        if (!apply_floater(next, floaters, slot, rec, error, error_capacity))
            goto done;
        highest = slot + 1U;
    }
    next->floater_count = (uint16_t)highest;
    for (slot = 0; slot < highest; ++slot)
        restore_combat_order(next, slot, save->data + save->floater_offset +
                                            (size_t)slot * FLOATER_RECORD);
    for (island = 0; island < next->island_count; ++island)
        game_session_recalculate_leviathan_island(next, (uint8_t)island);
    game_session_refresh_player_maintenance_budgets(next);
    *session = *next;
    ok = 1;
done:
    free(next);
    return ok;
}
