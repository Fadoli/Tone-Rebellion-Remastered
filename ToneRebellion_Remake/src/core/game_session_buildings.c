#include "game_session.h"

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

int game_session_repair_task_values(const GameSession *session,
                                    const PadCatalog *pad_catalog,
                                    const GamePendingEvent *event,
                                    int16_t *current, int16_t *maximum)
{
    if (session == NULL || pad_catalog == NULL || event == NULL ||
        current == NULL || maximum == NULL || event->active == 0 ||
        event->action_type != 0x12 || event->payload_0a < 0 ||
        event->payload_0e < 0 || event->payload_0a >= session->island_count) return 0;
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
    item_id = (int32_t)event->payload_12 + (int32_t)event->player_id * 16;
    if (item_id < 0 || item_id > 100) return 0;
    item = pad_catalog_find(pad_catalog, (uint16_t)item_id);
    if (item == NULL || item->building_tone_cost <= 0) return 0;
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

    if (error != NULL && error_capacity != 0) error[0] = '\0';
    if (session == NULL || catalog == NULL || site == NULL || player_slot >= 4 ||
        island_index >= session->island_count ||
        location_index >= session->islands[island_index].location_count) {
        set_error(error, error_capacity, "building placement target or player is out of range");
        return 0;
    }
    runtime = &session->islands[island_index].locations[location_index];
    if (runtime->renderer_class != 0 || runtime->record_value_10 != 0 ||
        runtime->owner_id != -1 ||
        !iw_construct_site_size(site, &site_size)) {
        set_error(error, error_capacity, "building placement requires an empty construction site");
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

    /* FUN_004528ca sets +0x32 to 1 and flags to 0x410. The source does not
       explicitly reset producer +0x0c; new remake placements start it at 0. */
    runtime->record_value_10 = runtime_item_id;
    runtime->owner_id = player_slot;
    runtime->source_capacity_4a = 0;
    if (!game_session_source_value_34_max(catalog, runtime, &runtime->source_value_34)) {
        set_error(error, error_capacity, "building has no usable source field +0x34");
        return 0;
    }
    runtime->record_value_24 = 0;
    runtime->source_flags = 0x410;
    runtime->base_progress = 0;
    runtime->producer_cadence = 0;
    runtime->chug_progress = 0;
    runtime->glyph_progress = 0;
    runtime->inci_progress = 0;
    runtime->construction_progress = 0;
    runtime->production_progress = 0;
    runtime->animation_rate = 1;
    runtime->barg_progress = 0.0;
    runtime->tribe_visibility_mask = 0;
    return 1;
}
