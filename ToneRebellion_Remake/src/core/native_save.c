#include "native_save.h"

#include "game_session_internal.h"

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
}

/* Refills the per-player Hall bookkeeping from the restored sites. */
static void rebuild_halls(GameSession *session)
{
    unsigned int island;
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
    /* Building links (+0x0c), orders (+0x2c..+0x46) and tasks (+0x38) refer to
       the player's 100-byte source rows, which are not decoded yet: the unit
       restarts as an unassigned wanderer. */
    floater->source_link_0c = -1;
    floater->charge_source_island = UINT8_MAX;
    floater->charge_source_location = UINT16_MAX;
    floater->linked_task_slot = -1;
    floater->order_source_location = -1;
    floater->order_target_location = -1;
    floater->order_target_floater = -1;
    floater->order_target_island = floater->island_index;
    floater->order_source_island = floater->island_index;
    floater->handoff_departure_location = -1;
    floater->has_wander_order = 1;
    game_session_recalculate_floater_attack_points(session, floater);
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
    rebuild_halls(next);
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
    game_session_refresh_player_maintenance_budgets(next);
    *session = *next;
    ok = 1;
done:
    free(next);
    return ok;
}
