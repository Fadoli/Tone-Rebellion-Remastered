#include "game_session.h"
#include "game_session_events.h"

#include "game_session_internal.h"
#include "iw_construct.h"
#include "pad_catalog.h"

#include <stdio.h>

static void set_error(char *error, size_t capacity, const char *message)
{
    if (error == NULL || capacity == 0) return;
    (void)snprintf(error, capacity, "%s", message);
    error[capacity - 1] = '\0';
}

static int reserve_source_record(const GameSession *session,
                                 uint8_t owner,
                                 uint16_t item_id, int16_t *record_index,
                                 int16_t *category_slot)
{
    uint8_t used_records[GAME_SOURCE_RECORDS_PER_PLAYER] = {0};
    uint8_t used_categories[GAME_SOURCE_SUBSLOTS_PER_ITEM] = {0};
    unsigned int record_candidate;
    unsigned int category_candidate;
    unsigned int island_index;

    for (island_index = 0; island_index < session->island_count;
         ++island_index) {
        const GameRuntimeIsland *island = &session->islands[island_index];
        unsigned int location_index;
        for (location_index = 0; location_index < island->location_count;
             ++location_index) {
            const GameRuntimeLocation *location = &island->locations[location_index];
            if (location->owner_id != owner) continue;
            if (location->source_location_slot_18 >= 0 &&
                location->source_location_slot_18 < GAME_SOURCE_RECORDS_PER_PLAYER) {
                used_records[location->source_location_slot_18] = 1;
            }
            if (location->record_value_10 == item_id &&
                location->source_category_slot_60 >= 0 &&
                location->source_category_slot_60 < GAME_SOURCE_SUBSLOTS_PER_ITEM) {
                used_categories[location->source_category_slot_60] = 1;
            }
        }
    }

    for (record_candidate = 0; record_candidate < GAME_SOURCE_RECORDS_PER_PLAYER;
         ++record_candidate) {
        if (!used_records[record_candidate]) break;
    }
    if (record_candidate == GAME_SOURCE_RECORDS_PER_PLAYER) return 0;
    for (category_candidate = 0; category_candidate < GAME_SOURCE_SUBSLOTS_PER_ITEM;
         ++category_candidate) {
        if (!used_categories[category_candidate]) break;
    }
    /* FUN_0045ee26 returns the free player source row even when all ten item
       subslots are occupied; its category field remains initialized to 0. */
    if (category_candidate == GAME_SOURCE_SUBSLOTS_PER_ITEM) category_candidate = 0;
    *record_index = (int16_t)record_candidate;
    *category_slot = (int16_t)category_candidate;
    return 1;
}

int game_session_repair_task_values(const GameSession *session,
                                    const PadCatalog *pad_catalog,
                                    const GamePendingEvent *event,
                                    int16_t *current, int16_t *maximum)
{
    if (session == NULL || pad_catalog == NULL || event == NULL ||
        current == NULL || maximum == NULL || event->active == 0 ||
        event->action_type != 0x12 || event->payload_0a < 0 ||
        event->payload_0a >= session->island_count || event->payload_0e < 0) return 0;
    return game_session_repair_location_values(session, pad_catalog,
        (uint8_t)event->payload_0a, (uint16_t)event->payload_0e,
        current, maximum);
}

int game_session_repair_location_values(const GameSession *session,
                                        const PadCatalog *pad_catalog,
                                        uint8_t island_index,
                                        uint16_t location_index,
                                        int16_t *current, int16_t *maximum)
{
    const GameRuntimeIsland *island;
    const GameRuntimeLocation *location;
    int16_t computed_maximum;

    if (session == NULL || pad_catalog == NULL || current == NULL ||
        maximum == NULL || island_index >= session->island_count) return 0;
    island = &session->islands[island_index];
    if (location_index >= island->location_count) return 0;
    location = &island->locations[location_index];
    if (!game_session_source_value_34_max(pad_catalog, location, &computed_maximum) ||
        location->source_value_34 == -1 || computed_maximum <= 0) return 0;
    *current = location->source_value_34;
    *maximum = computed_maximum;
    return 1;
}

int game_session_construction_task_values(const GameSession *session,
                                          const PadCatalog *pad_catalog,
                                          const GamePendingEvent *event,
                                          int16_t *current, int16_t *maximum)
{
    const GameRuntimeLocation *location;
    const PadCatalogItem *item;
    int32_t item_id;
    if (session == NULL || pad_catalog == NULL || event == NULL ||
        current == NULL || maximum == NULL || event->active == 0 ||
        event->action_type != 5 || event->payload_0a < 0 ||
        event->payload_0e < 0 || event->payload_0a >= session->island_count ||
        event->player_id < 0 || event->player_id >= GAME_START_PLAYER_COUNT) return 0;
    if ((uint16_t)event->payload_0e >=
        session->islands[event->payload_0a].location_count) return 0;
    location = &session->islands[event->payload_0a].locations[event->payload_0e];
    if (location->renderer_class != 0 ||
        !game_session_build_target_available(location,
            (uint8_t)event->player_id) || location->construction_site_size > 2U)
        return 0;
    item_id = (int32_t)event->payload_12 + (int32_t)event->player_id * 16;
    if (item_id < 0 || item_id > 100) return 0;
    item = pad_catalog_find(pad_catalog, (uint16_t)item_id);
    if (item == NULL || item->building_tone_cost == -1) return 0;
    *current = (int16_t)location->resource_stock[0];
    *maximum = item->building_tone_cost;
    return *current >= 0;
}

int game_session_acquire_glyph(GameSession *session, uint8_t player_slot,
                               uint8_t glyph_index)
{
    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT ||
        glyph_index >= GAME_GLYPH_COUNT) return 0;
    session->economy[player_slot].glyph_mask = (uint16_t)(
        session->economy[player_slot].glyph_mask | (uint16_t)(1U << glyph_index));
    if (glyph_index == 13U)
        game_session_refresh_player_maintenance_budgets(session);
    return 1;
}

int game_session_place_building(GameSession *session,
                                const PadCatalog *catalog,
                                uint8_t player_slot,
                                uint8_t island_index,
                                uint16_t location_index,
                                const struct IslandLocation *site,
                                uint16_t base_item_id,
                                char *error, size_t error_capacity)
{
    GameRuntimeLocation *runtime;
    const PadCatalogItem *item;
    uint8_t site_size;
    uint16_t runtime_item_id;
    int16_t source_record_index = -1;
    int16_t source_category_slot = -1;
    int16_t source_value_34_maximum;
    uint16_t previous_source_capacity;

    if (error != NULL && error_capacity != 0) error[0] = '\0';
    if (session == NULL || catalog == NULL || site == NULL || player_slot >= 4 ||
        island_index >= session->island_count ||
        location_index >= session->islands[island_index].location_count) {
        set_error(error, error_capacity, "building placement target or player is out of range");
        return 0;
    }
    runtime = &session->islands[island_index].locations[location_index];
    if (runtime->renderer_class != 0 ||
        !game_session_build_target_available(runtime, player_slot) ||
        !iw_construct_site_size(site, &site_size)) {
        set_error(error, error_capacity,
                  "building placement requires an available construction site");
        return 0;
    }
    if (base_item_id == 0) {
        set_error(error, error_capacity, "source rejects item ID zero for construction");
        return 0;
    }
    runtime_item_id = (uint16_t)(base_item_id + (uint16_t)player_slot * 16U);
    item = pad_catalog_find(catalog, runtime_item_id);
    if (item == NULL || item->size < 0 || item->size > site_size ||
        item->building_tone_cost == -1) {
        set_error(error, error_capacity, "building is not allowed on this site");
        return 0;
    }
    /* FUN_004526de compares the pad cost with player +0x40 (DAT_006191f8),
       the capacity left after upkeep, not the gross +0x3c capacity. */
    if (item->maintenance_tone_cost >
        session->economy[player_slot].source_maintenance_budget) {
        set_error(error, error_capacity,
                  "player maintenance budget is too small for this building");
        return 0;
    }
    if (base_item_id >= 0x2c && base_item_id <= 0x32) {
        /* FUN_004528ca initializes the building before attempting this
           allocation, then returns early if this player's 48-row source
           table is full across all islands.
           FUN_004527ee ignores that return and still completes the placement. */
        (void)reserve_source_record(session, player_slot,
                                    runtime_item_id,
                                    &source_record_index, &source_category_slot);
    }

    /* FUN_004528ca initializes the runtime fields and flags to 0x410. */
    runtime->record_value_10 = runtime_item_id;
    runtime->owner_id = player_slot;
    runtime->maintenance_tone_cost = item->maintenance_tone_cost;
    if (base_item_id >= 0x2c && base_item_id <= 0x32) {
        /* A full native source table leaves the prior empty-site value (normally
           -1) untouched, producing an owned building without a source link. */
        if (source_record_index >= 0) {
            runtime->source_location_slot_18 = source_record_index;
            runtime->source_category_slot_60 = source_category_slot;
        }
    } else {
        runtime->source_location_slot_18 = -1;
        runtime->source_category_slot_60 = -1;
    }
    previous_source_capacity = runtime->source_capacity_4a;
    runtime->source_capacity_4a = 0;
    if (!game_session_source_value_34_max(catalog, runtime,
                                          &source_value_34_maximum)) {
        runtime->record_value_10 = 0;
        runtime->owner_id = -1;
        runtime->maintenance_tone_cost = 0;
        runtime->source_location_slot_18 = -1;
        runtime->source_category_slot_60 = -1;
        runtime->source_capacity_4a = previous_source_capacity;
        set_error(error, error_capacity, "building has no usable source field +0x34");
        return 0;
    }
    /* FUN_004528ca stores its owner argument at site +0x14. It clears +0x22
       only for owner 4 on class 0; the final value is recomputed below. */
    runtime->source_value_14 = player_slot;
    runtime->source_value_32 = 1;
    runtime->source_value_34 = source_value_34_maximum;
    runtime->leviathan_spawned_floater = -1;
    runtime->upgrade_task_handle = -1;
    runtime->record_value_24 = 0;
    runtime->resource_stock[GAME_RESOURCE_BUILD_TONE] = 0;
    runtime->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] = 0;
    runtime->resource_stock[GAME_RESOURCE_MAGIC_TONE] = 0;
    /* FUN_004528ca clears +0x30 directly. FUN_00452fcb clears +0x3a..+0x49
       for a class-0 site and then restores the +0x3e sentinel. */
    runtime->charge_source_value_30 = 0;
    runtime->source_value_3a = 0;
    runtime->source_value_3c = 0;
    runtime->source_value_3e = -1;
    runtime->source_value_40 = 0;
    runtime->source_value_42 = 0;
    runtime->resource_retry_tick_36 = -1;
    runtime->source_value_44 = 0;
    runtime->source_value_46 = 0;
    runtime->source_value_48 = 0;
    /* FUN_004528ca clears bit 0 and adds 0x410; FUN_00452fcb clears bits
       1..3. FUN_004527ee re-ORs bit 0x10, already present in 0x410. */
    runtime->source_flags = (runtime->source_flags & ~0x0fU) | 0x410U;
    /* FUN_004528ca does not write the modeled +0x0c cadence field. */
    runtime->chug_progress = 0;
    runtime->glyph_progress = 0;
    runtime->inci_progress = 0;
    runtime->construction_progress = 0;
    runtime->production_progress = 0;
    runtime->animation_rate = 1;
    /* The placement ramp is native flag 0x010 / +0x48, already set above. */
    runtime->new_build_animation_ticks = 0;
    /* The native initializer leaves BARG's double at +0x50 untouched. */
    (void)game_session_recalculate_active_locations(session);
    game_session_refresh_player_maintenance_budgets(session);
    /* FUN_004528ca finishes through FUN_00466c8b, which recalculates all
       player budgets and then FUN_00460460's island Leviathan rates. */
    game_session_recalculate_leviathan_island(session, island_index);
    (void)game_session_queue_audio_event_at(
        session, GAME_SESSION_AUDIO_BUILD, player_slot, (uint8_t)island_index);
    return 1;
}
