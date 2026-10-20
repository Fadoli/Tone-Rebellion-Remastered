#include "game_session.h"

#include "building_render.h"
#include "island_render_rules.h"
#include "game_session_world.h"

static const uint8_t source_staff_target_counts[8][3][3] = {
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{3, 0, 0}, {3, 2, 0}, {3, 2, 1}},
    {{3, 0, 0}, {3, 2, 0}, {3, 2, 1}},
    {{3, 0, 0}, {3, 2, 0}, {0, 0, 0}},
    {{1, 0, 0}, {1, 1, 0}, {1, 1, 1}},
    {{1, 0, 0}, {1, 1, 0}, {1, 1, 1}},
    {{1, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{1, 0, 0}, {0, 0, 0}, {0, 0, 0}}
};

static const int16_t source_staff_level_caps[9] = {0, 2, 2, 1, 2, 2, 0, 0, 0};
static const int16_t source_staff_threshold_low[9][3] = {
    {0, 0, 0}, {25, 100, 0}, {30, 120, 0}, {40, -1, 0},
    {25, 100, 0}, {25, 100, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}
};
static const int16_t source_staff_threshold_high[9][3] = {
    {0, 0, 0}, {75, 200, 0}, {90, 240, 0}, {120, -1, 0},
    {75, 200, 0}, {75, 200, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}
};

static int producer_resource_code(const GameRuntimeLocation *state)
{
    int32_t base_item_id;
    if (state == NULL || state->renderer_class != 0 || state->owner_id < 0 ||
        state->owner_id >= GAME_START_PLAYER_COUNT) return 0;
    base_item_id = state->record_value_10 - state->owner_id * 16;
    if (base_item_id == 0x25) return 1; /* P-BLDTON -> Build Tone */
    if (base_item_id == 0x27) return 2; /* P-CRYTON -> Crystal Tone */
    if (base_item_id == 0x26) return 3; /* P-MAGTON -> Magic Tone */
    return 0;
}

static void tick_source_staff_cycle(GameSession *session,
                                    GameRuntimeLocation *source,
                                    const FloaterCatalog *floater_catalog,
                                    uint8_t island_index,
                                    unsigned int location_index)
{
    unsigned int slot;
    int32_t base_item_id;
    int16_t existing_by_level[3] = {0, 0, 0};
    int16_t need_by_level[3];
    int32_t source_level;
    int32_t difficulty;
    int32_t stock_available;
    unsigned int worker_index;
    int current_worker_active = 0;

    if (source->owner_id < 0 || source->owner_id >= GAME_START_PLAYER_COUNT)
        return;
    base_item_id = source->record_value_10 - source->owner_id * 16;
    if (base_item_id < 0x2c || base_item_id > 0x32 ||
        (source->source_flags & 0x90U) != 0) return;

    source_level = source->source_capacity_4a;
    if (source_level < 0) source_level = 0;
    if (source_level > 2) source_level = 2;
    difficulty = session->config.difficulty;
    if (difficulty > 4) difficulty = 4;
    stock_available = source->resource_stock[1] > 9;
    for (slot = 0; slot < 8; ++slot) {
        int16_t index = source->charge_floater_slots[slot];
        if (index < 0 || (unsigned int)index >= session->floater_count) continue;
        worker_index = (unsigned int)index;
        {
            uint16_t level = session->floaters[worker_index].attack_level_flags & 0x0fU;
            if (level < 3U) ++existing_by_level[level];
        }
    }
    for (slot = 0; slot < 3; ++slot)
        need_by_level[slot] = (int16_t)(
            source_staff_target_counts[base_item_id - 0x2b][source_level][slot] -
            existing_by_level[slot]);

    for (slot = 0; slot < 8; ++slot) {
        int16_t index = source->charge_floater_slots[slot];
        GameFloaterStart *floater;
        const FloaterStats *stats;
        uint32_t progress;
        uint32_t increment;
        uint16_t level;

        if (index < 0 || (unsigned int)index >= session->floater_count) continue;
        floater = &session->floaters[(unsigned int)index];
        if ((floater->source_runtime_flags & 0x20U) == 0) {
            int32_t threshold;
            int32_t weighted_threshold;

            level = (uint16_t)(floater->attack_level_flags & 0x0fU);
            if (source->charge_recent_floater != -1 ||
                source->charge_staff_task_handle != -1 ||
                level >= 2U || level >= source_staff_level_caps[
                    floater->source_subtype <= 8 ? floater->source_subtype : 0] ||
                level >= (uint16_t)source_level || need_by_level[level + 1U] == 0 ||
                !stock_available || floater->source_subtype > 8) continue;

            weighted_threshold = (4 - difficulty) *
                source_staff_threshold_low[floater->source_subtype][level] +
                difficulty * source_staff_threshold_high[floater->source_subtype][level];
            threshold = weighted_threshold / 4;
            if (threshold <= 0 ||
                threshold > (int16_t)floater->source_progress_08) continue;
            source->charge_recent_floater = index;
            continue;
        }

        /* FUN_0045cd75 adds source +0x32 (initialized to 1 by FUN_004528ca)
           for each linked worker in the active-work branch. */
        increment = source->animation_rate;
        if (increment == 0) increment = 1;
        progress = (uint32_t)source->charge_source_value_30 + increment;
        if (progress < 251U) {
            source->charge_source_value_30 = (uint16_t)progress;
            source->barg_progress = (double)progress / 250.0;
            continue;
        }

        /* At 251, FUN_0045cd75 trains subtype 0 to the source class, then
           advances an already trained floater's low-nibble level. */
        if (floater->source_subtype == 0) {
            floater->source_subtype = (uint8_t)(base_item_id - 0x2b);
            floater->attack_level_flags &= 0xfff0U;
        } else {
            level = (uint16_t)(floater->attack_level_flags & 0x0fU);
            if (level < 5U) ++level;
            else level = 5U;
            floater->attack_level_flags = (uint16_t)(
                (floater->attack_level_flags & 0xfff0U) | level);
        }

        stats = floater_catalog_find(floater_catalog, floater->type_index,
                                     floater->source_subtype);
        if (stats != NULL) {
            int32_t trained_strength;
            level = (uint16_t)(floater->attack_level_flags & 0x0fU);
            floater->charge_current = stats->attack_strength;
            /* FUN_00420f28 scales max-attack-points with the trained level.
               Category 4 uses its distinct 7n+10 multiplier. Its tribe and
               linked-building bonuses require mask bits from DAT_00619242;
               that table is zero in the loaded image, and no runtime writer
               is established, so those conditional bonuses remain unmodeled. */
            if (floater->type_index == 4) {
                trained_strength = (stats->max_attack_points *
                                    ((int32_t)level * 7 + 10)) / 10;
            } else {
                trained_strength = (stats->max_attack_points *
                                    ((int32_t)level + 2)) / 2;
            }
            if (trained_strength > INT16_MAX) trained_strength = INT16_MAX;
            if (trained_strength < INT16_MIN) trained_strength = INT16_MIN;
            floater->max_attack_points = (int16_t)trained_strength;
            level = (uint16_t)(floater->attack_level_flags & 0x0fU);
            if (level > 0 && level <= 3U)
                --need_by_level[level - 1U];
        }
        /* FUN_0045c82f clears the current worker, then FUN_00421ec1(-1)
           ends its active source action and clears runtime mask 0x65. */
        floater->source_runtime_flags &= ~0x65U;
        floater->movement_state = 0;
        floater->active_order_action = 0;
        floater->has_move_order = 0;
        source->charge_recent_floater = -1;
        if (source->charge_staff_task_handle >= 0 &&
            source->charge_staff_task_handle < GAME_SESSION_MAX_PENDING_EVENTS) {
            (void)game_session_pending_event_release(
                session, (uint8_t)source->charge_staff_task_handle);
            source->charge_staff_task_handle = -1;
        }
    }

    {
        int16_t current = source->charge_recent_floater;
        if (current >= 0 && (unsigned int)current < session->floater_count)
            current_worker_active =
                (session->floaters[(unsigned int)current].source_runtime_flags &
                 0x20U) != 0;
    }
    if (source->barg_progress > 0.0) {
        if (!current_worker_active) {
            source->barg_progress -= 0.25;
            if (source->barg_progress < 0.0) source->barg_progress = 0.0;
        }
    }

    if (source->resource_stock[1] <= 9U &&
        source->charge_staff_task_handle >= 0 &&
        !current_worker_active) {
        (void)game_session_pending_event_release(
            session, (uint8_t)source->charge_staff_task_handle);
        source->charge_staff_task_handle = -1;
    } else if (need_by_level[0] != 0 &&
               source->charge_recent_floater == -1 &&
               source->charge_staff_task_handle == -1 && stock_available) {
        /* FUN_0045c325 confirms source-table header words [0]/[1] are the
           island and location indices used by this task's payload. */
        int task_slot = game_session_pending_event_add(
            session, (int16_t)source->owner_id, (int16_t)island_index, 0x0b,
            (int16_t)location_index, 0, 0);
        if (task_slot >= 0) source->charge_staff_task_handle = (int16_t)task_slot;
    }
}

void game_session_tick_item_animations_with_floaters(
    GameSession *session, const struct BuildingRenderCatalog *catalog,
    const FloaterCatalog *floater_catalog)
{
    unsigned int island_index;
    if (session == NULL || catalog == NULL) return;
    for (island_index = 0; island_index < session->island_count; ++island_index) {
        GameRuntimeIsland *island = &session->islands[island_index];
        unsigned int location_index;
        for (location_index = 0; location_index < island->location_count; ++location_index) {
            GameRuntimeLocation *state = &island->locations[location_index];
            const BuildingRenderItem *item;
            uint32_t duration;
            int construction_completed = 0;
            int production_completed = 0;

            if (state->renderer_class > 2) continue;

            /* FUN_00450a71 has two POOL-specific class-1 counter sequences.
               ID 0 loops 0..89; ID 5 advances to 125 then restarts at 102.
               FUN_0040bf98 later maps each counter through POOL's CHUG segment. */
            if (state->renderer_class == 1 &&
                (state->record_value_10 == 0 ||
                 state->record_value_10 == ISLAND_TONE_POOL_ITEM_ALTERNATE)) {
                state->chug_progress = island_tone_pool_next_counter(
                    state->record_value_10, state->chug_progress);
                continue;
            }

            if (state->renderer_class == 0 && floater_catalog != NULL)
                tick_source_staff_cycle(session, state, floater_catalog,
                                        (uint8_t)island_index, location_index);

            if (state->record_value_10 <= 0 ||
                state->record_value_10 >= catalog->item_count) continue;
            item = building_render_find(catalog, (uint16_t)state->record_value_10);
            if (item == NULL) continue;

            /* FUN_00450a71 has a separate class-1 path: items 6..9 animate
               their CHUG layer every source tick and wrap at the descriptor
               duration. They do not use the class-0 construction flag gate. */
            if (state->renderer_class == 1) {
                if (item->chug.present) {
                    duration = building_render_chug_duration(item);
                    if (duration != 0) {
                        state->chug_progress = (uint16_t)(state->chug_progress + 1U);
                        if (state->chug_progress >= duration) state->chug_progress = 0;
                    }
                }
                continue;
            }

            /* FUN_00450a71 increments class-0 CHUG only while source flag bit 0
               is set; objects created by FUN_004528ca begin with it clear. */
            if ((state->source_flags & 1U) != 0 && item->chug.present) {
                uint32_t increment = state->owner_id == 4 || state->animation_rate < 2
                    ? 1U : item->chug.ticks_per_frame;
                duration = building_render_chug_duration(item);
                if (duration != 0) {
                    state->chug_progress = (uint16_t)(state->chug_progress + increment);
                    if (state->chug_progress >= duration) state->chug_progress = 0;
                }
            }

            /* GLYP's +0x3c counter runs only after it is active or when both
               source flags 0x400 and 0x001 are set; it wraps at 40 ticks. */
            if (item->glyph.present &&
                (state->glyph_progress > 0 ||
                 (state->source_flags & 0x401U) == 0x401U)) {
                ++state->glyph_progress;
                if (state->glyph_progress == 40) state->glyph_progress = 0;
            }

            /* FUN_00450a71 advances PROD (+0x42) while flag 0x002 is set,
               then clears that flag at the item's +0x0c limit. The catalog's
               PROD threshold is that value. A missing descriptor uses the
               observed fallback limit 0x28. Completion side effects later in
               the source switch are still outside this animation tick port. */
            if ((state->source_flags & 0x002U) != 0) {
                uint32_t limit = item->prod.present ? item->prod.threshold : 0x28U;
                ++state->production_progress;
                if (limit <= state->production_progress) {
                    state->source_flags &= ~0x002U;
                    production_completed = 1;
                    /* FUN_00450a71 maps completed producer cycles into the
                       pending output code held in runtime +0x24. */
                    if (state->record_value_24 == 0)
                        state->record_value_24 = producer_resource_code(state);
                }
            }

            /* FUN_00450a71 starts producer PROD cycles from source +0x0c
               when the object is running, no output is pending, and PROD is
               idle. It adds +0x32 and starts at a strict value > 0x13. */
            if (producer_resource_code(state) != 0 &&
                state->record_value_24 == 0 &&
                (state->source_flags & 0x001U) != 0 &&
                (state->source_flags & 0x002U) == 0) {
                state->producer_cadence = (uint16_t)(state->producer_cadence +
                                                     state->animation_rate);
                if (state->producer_cadence > 0x13U) {
                    state->source_flags |= 0x002U;
                    state->production_progress = 0;
                    state->producer_cadence = 0;
                }
            }

            /* The same source tick advances CONS (+0x40) while flag 0x004 is
               set. FUN_00456b8d resolves a construction descriptor; its +0x0a
               threshold is stored as CONS's first parameter by bldinf.txt. */
            if ((state->source_flags & 0x004U) != 0) {
                ++state->construction_progress;
                if (item->cons.present &&
                    item->cons.fallback_frame <= state->construction_progress) {
                    state->source_flags &= ~0x004U;
                    construction_completed = 1;
                }
            }

            /* FUN_00450a71 case 2 chains CONS into PROD for an unbuilt class-2
               bridge marker, then FUN_004669bd activates its paired link when
               that production animation finishes. The event that starts CONS
               remains outside the current gameplay input model. */
            if (state->renderer_class == 2 && state->record_value_10 == 2 &&
                (state->source_flags & 1U) == 0) {
                if (construction_completed) {
                    state->source_flags |= 0x002U;
                    state->production_progress = 0;
                } else if (production_completed) {
                    (void)game_session_mark_bridge_constructed_at(
                        session, (uint8_t)island_index, (uint16_t)location_index);
                }
            }
        }
    }
}

void game_session_tick_item_animations(GameSession *session,
                                       const struct BuildingRenderCatalog *catalog)
{
    game_session_tick_item_animations_with_floaters(session, catalog, NULL);
}

