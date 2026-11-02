static const SpriteSheet g_empty_floater_sheet;

/* fltinf.txt's ascend item (floater.txt subtype 8 of every tribe) has an
   alegs shape and no body line. */
static int island_floater_is_ascended(const GameFloaterStart *floater)
{
    return floater->type_index < 4U && floater->source_subtype == 8U;
}

static const SpriteSheet *island_floater_body_art(
    const GameFloaterStart *floater)
{
    if (island_floater_is_ascended(floater)) return &g_empty_floater_sheet;
    return floater->facing_left
        ? &g_initial_floater_bodies_flipped[floater->type_index]
        : &g_initial_floater_bodies[floater->type_index];
}

static const SpriteSheet *island_floater_legs_art(
    const GameFloaterStart *floater)
{
    if (island_floater_is_ascended(floater))
        return floater->facing_left ? &g_ascend_legs_art_flipped
                                    : &g_ascend_legs_art;
    return floater->facing_left
        ? &g_initial_floater_legs_flipped[floater->type_index]
        : &g_initial_floater_legs[floater->type_index];
}

static uint32_t island_floater_body_sprite_frame(
    const GameFloaterStart *floater, const SpriteSheet *body_art)
{
    uint32_t frame;
    if (floater == NULL || body_art == NULL ||
        !island_floater_body_frame(
            floater->type_index, floater->source_subtype,
            floater->attack_level_flags & 0x0fU, &frame) ||
        frame >= body_art->frame_count) return 0;
    return frame;
}

static uint32_t island_floater_legs_frame(const GameFloaterStart *floater)
{
    if (floater == NULL) return 0;
    if ((floater->movement_state == 6 || floater->movement_state == 7) &&
        floater->attack_timer != 0 &&
        floater->attack_timer <= floater->attack_frame_duration) {
        return island_worker_attack_legs_frame(
            floater->attack_frame_first, floater->attack_frame_last,
            floater->attack_frame_ticks_per_frame,
            floater->attack_frame_ping_pong, floater->attack_timer);
    }
    /* FUN_0042704b also plays the fltinf attack range in state 0x13
       (FA_Cast) while 0 < +0x34 <= FUN_004251a2(0x13), which returns the
       same attack duration as states 6/7 (ev_4a090340). The port keeps the
       cast's +0x34 counter in order_timer. */
    if (floater->movement_state == 0x13 && floater->order_timer != 0 &&
        floater->order_timer <= floater->attack_frame_duration) {
        return island_worker_attack_legs_frame(
            floater->attack_frame_first, floater->attack_frame_last,
            floater->attack_frame_ticks_per_frame,
            floater->attack_frame_ping_pong, floater->order_timer);
    }
    if (island_floater_is_ascended(floater))
    {
        /* hover 0..28, speed div 2; clamp to the shipped sheet. */
        uint32_t count = g_ascend_legs_art.frame_count < 29U
            ? g_ascend_legs_art.frame_count : 29U;
        return count == 0U ? 0U : (g_menu.animation_ticks / 2U) % count;
    }
    return island_worker_legs_frame(
        floater->type_index, floater->carried_resource_code != 0,
        g_menu.animation_ticks);
}

static unsigned int island_leviathan_leg_sheet(uint8_t subtype)
{
    return subtype >= 9U && subtype <= 17U
        ? (unsigned int)(subtype - 9U) : 9U;
}

/* FUN_0044338b indexes the 16-byte beast slot table at 0x4a4a50 by
   level + (subtype - 9) * 2. FUN_0041d70d overwrites the initial "x" strings
   with the names.txt beast names at startup. */
static const char *island_leviathan_info_name(uint8_t subtype,
                                              unsigned int level)
{
    unsigned int index;
    if (subtype < 9U || subtype > 17U) return "";
    index = level + (unsigned int)(subtype - 9U) * 2U;
    return index < 18U ? g_beast_names[index] : "";
}

/* FUN_00439673 mode 0 for non-building sites: kind 1 (pool) starts at POOL;
   owner 4 uses POOLINFECT for item 5 or SUPPLY(item - 6), otherwise the
   viewing tribe's bit in the +0x22 visibility byte selects PRIMEPOOL.
   Kind 2 (bridge) shows BRIDGE. Kind 3 (FEAT%02d) needs the per-island
   feature table (DAT_005eebf8), which the port does not model. */
static const char *island_site_info_text(const GameRuntimeLocation *location,
                                         unsigned int tribe)
{
    unsigned int index = SITE_TEXT_POOL;
    if (location == NULL) return NULL;
    if (location->renderer_class == 2) {
        index = SITE_TEXT_BRIDGE;
    } else if (location->renderer_class == 1) {
        if (location->owner_id == 4) {
            if (location->record_value_10 == 5) {
                index = SITE_TEXT_POOL_INFECT;
            } else if (location->record_value_10 >= 6 &&
                       location->record_value_10 <= 9) {
                index = SITE_TEXT_SUPPLY0 +
                    (unsigned int)(location->record_value_10 - 6);
            }
        } else if (tribe < 8U &&
                   ((location->source_value_22 & 0xffU) & (1U << tribe)) != 0U) {
            index = SITE_TEXT_PRIME_POOL;
        }
    } else {
        return NULL;
    }
    return g_site_texts[index][0] != '\0' ? g_site_texts[index] : NULL;
}

/* FUN_0042704b draws the optional body shape at fltinf "base first last"
   frame first + FUN_0041ff2e (floater +0x0a & 0xf, the unit level), clamped
   to [first, last]; no time animation. vbod holds base 2*(subtype-10) and
   2*(subtype-10)+1 per Leviathan item. FUN_0041ff2e is a thiscall whose ECX
   is not visible in the decompiled output; the floater is an interpretation. */
static uint32_t island_leviathan_body_frame(const GameFloaterStart *floater)
{
    uint32_t level = floater->attack_level_flags & 0xfU;
    return 2U * (uint32_t)(floater->source_subtype - 10U) +
           (level > 1U ? 1U : level);
}

/* FUN_0042704b draws cargo first (behind body and legs) at floater + fltinf
   graspxy (record +0x25/+0x26), the offset mirrored with the facing while the
   cargo sprite itself is drawn unflipped (plain FUN_00404770/FUN_00410bd2
   calls, no scale argument), plus the per-item vertical offset (DAT_0049acbe,
   not yet extracted: 0 here). */
/* FUN_0042704b with param_5 set and state 0x11 (+0x2c) at +0x34 >= 1: the
   counter, capped at 0x78 and less 0x3c above 0x3c, lifts the floater by
   t*t/20 and drops param_6 to 8 - t/8, so every layer goes through the
   FUN_00410bd2 stipple; the facing flip is skipped and DAT_005dc668 cleared.
   The departure rise (+0x34 1..0x3c), the 200/500-tick hold (t = 0x3c) and
   the arrival descent (0x78..0x3d) all come from this single formula. */
static int island_floater_bridge_lift(const GameFloaterStart *floater,
                                      int *stipple_level)
{
    int t;
    *stipple_level = 8;
    if (floater->movement_state != 0x11 || (int16_t)floater->order_timer < 1)
        return 0;
    t = (int16_t)floater->order_timer;
    if (t > 0x78) t = 0x78;
    if (t > 0x3c) t -= 0x3c;
    *stipple_level = 8 - t / 8;
    return t * t / 20;
}

/* FUN_00410bd2 draws through DAT_0049b444's 4x4 reveal mask below level 8;
   the region covers the (possibly scaled) blit rectangle. */
static void draw_island_floater_layer(RenderSurface *surface, const SpriteSheet *art,
                                      uint32_t frame_index, int x, int y,
                                      uint32_t scale_16_16, int stipple_level)
{
    const SpriteFrame *frame;
    const uint8_t *mask;
    int saved;
    int left;
    int top;
    int width;
    int height;
    if (stipple_level >= 8) {
        draw_sprite_scaled(surface, art, frame_index, x, y, scale_16_16);
        return;
    }
    if (stipple_level < 1 || art == NULL || frame_index >= art->frame_count)
        return;
    frame = &art->frames[frame_index];
    left = x + (int)(((int64_t)frame->x_offset * scale_16_16) >> 16);
    top = y + (int)(((int64_t)frame->y_offset * scale_16_16) >> 16);
    width = (int)(((uint64_t)(unsigned)frame->width * scale_16_16) >> 16);
    height = (int)(((uint64_t)(unsigned)frame->height * scale_16_16) >> 16);
    mask = feature_reveal_mask(g_island_surface_id, stipple_level,
                               width, height, left, top);
    if (mask == NULL) return;
    saved = render_surface_save(surface);
    if (saved == 0) return;
    if (render_surface_intersect_mask(surface, mask, left, top, width, height,
                                      width))
        draw_sprite_scaled(surface, art, frame_index, x, y, scale_16_16);
    render_surface_restore(surface, saved);
}

/* FUN_0042704b (ev_4bbcbdab) draws the cargo full size through FUN_00404770:
   bildtone/tonecrys/magctone frame 0, or TRIGGERS (alltrigs.shp) frame
   code - 5, at the hand point plus FUN_0040ad94's height for artifacts. */
static void draw_island_floater_cargo(RenderSurface *surface, const GameFloaterStart *floater,
                                      int x, int y, int stipple_level)
{
    static const int8_t grasp_x[4] = {10, 10, 13, 11};
    static const int8_t grasp_y[4] = {12, 14, 14, 20};
    int hand_x;
    int hand_y;
    if (floater == NULL || floater->carried_resource_code == 0 ||
        floater->type_index > 3U) return;
    hand_x = x + (floater->facing_left ? -grasp_x[floater->type_index]
                                       : grasp_x[floater->type_index]);
    hand_y = y + grasp_y[floater->type_index];
    if (floater->carried_resource_code >= 1 &&
        floater->carried_resource_code <= GAME_RESOURCE_TYPE_COUNT) {
        static const SpriteSheet *const carried_art[] = {
            &g_bildtone_art, &g_tone_crys_art, &g_magctone_art
        };
        const SpriteSheet *cargo_art = carried_art[
            (unsigned int)floater->carried_resource_code - 1U];
        if (cargo_art->frame_count != 0)
            draw_island_floater_layer(surface, cargo_art, 0, hand_x, hand_y,
                                      0x00010000U, stipple_level);
    } else if (floater->carried_resource_code >= GAME_INVENTORY_ITEM_FIRST_ID &&
               floater->carried_resource_code <
                   GAME_INVENTORY_ITEM_FIRST_ID + GAME_INVENTORY_ITEM_COUNT &&
               (uint32_t)(floater->carried_resource_code -
                   GAME_INVENTORY_ITEM_FIRST_ID) <
                       g_inventory_item_art.frame_count) {
        draw_island_floater_layer(surface, &g_inventory_item_art,
                                  (uint32_t)(floater->carried_resource_code -
                                      GAME_INVENTORY_ITEM_FIRST_ID),
                                  hand_x, hand_y +
                                      game_session_carried_item_height(
                                          floater->carried_resource_code),
                                  0x00010000U, stipple_level);
    }
}

static uint32_t island_leviathan_legs_frame(const GameFloaterStart *floater,
                                             unsigned int sheet_index)
{
    static const uint8_t move_last[9] = {9, 15, 15, 7, 7, 16, 10, 15, 24};
    uint32_t phase;
    if (floater == NULL || sheet_index >= 9U) return 0;
    if ((floater->movement_state == 6 || floater->movement_state == 7) &&
        floater->attack_timer != 0 && floater->attack_frame_duration != 0) {
        uint32_t attack_frame = island_worker_attack_legs_frame(
            floater->attack_frame_first, floater->attack_frame_last,
            floater->attack_frame_ticks_per_frame,
            floater->attack_frame_ping_pong, floater->attack_timer);
        if (attack_frame < g_leviathan_legs[sheet_index].frame_count)
            return attack_frame;
    }
    phase = (g_game_session.simulation_tick + floater->animation_seed) / 2U;
    return phase % ((uint32_t)move_last[sheet_index] + 1U);
}

/* Badge frame is 0x15 - n, n clamped to 10: frame 11 is the full gauge and 21
   the empty one, so n is the filled tenths, current/max hits * 10 (truncated
   like __ftol). Interpretation: the x87 operands before __ftol are not in the
   decompiled output. */
static int16_t island_floater_health_stat(const GameFloaterStart *floater)
{
    if (floater->max_hit_points <= 0 || floater->current_hit_points <= 0)
        return 0;
    return (int16_t)(((int32_t)floater->current_hit_points * 10) /
                     floater->max_hit_points);
}

/* FUN_0042822b calls FUN_0042704b with param_5=1 for world floaters. The first
   overlay global gates FLTINFO realm frames 22..25; the second gates the
   combat-stat badge (FUN_00420f28), which the source does not restrict to
   workers: leviathans with a body shape get it too (type 4 is only excluded
   from the third, strength, badge). Anchor is the body frame's hit box. */
static void draw_island_floater_overlays(RenderSurface *surface, const GameFloaterStart *floater,
                                         const SpriteSheet *body_art,
                                         uint32_t body_frame_index,
                                         int x, int y)
{
    const SpriteFrame *body_frame;
    int32_t body_left;
    int32_t body_top;
    int32_t body_right;
    uint32_t frame;
    int32_t badge_x;
    int32_t badge_y;
    int16_t charge_now;
    int16_t charge_max;
    if (g_floater_info_art.frame_count < 26|| body_art == NULL ||
        body_frame_index >= body_art->frame_count) return;
    body_frame = &body_art->frames[body_frame_index];
    body_left = x + body_frame->x_offset + body_frame->hit_left;
    body_top = y + body_frame->y_offset + body_frame->hit_top;
    body_right = x + body_frame->x_offset + body_frame->hit_right;
    /* FUN_0042003c: the fltinf row realm (not the tribe), with the linked
       source site shift; Leviathans get it too (ev_fe27bac4). */
    if (island_worker_realm_overlay_enabled(g_floater_overlay_flags, 1) &&
        island_worker_realm_badge_layout(
            (uint8_t)game_session_floater_realm(&g_game_session, floater), 0, 0,
            floater->facing_left,
            body_left, body_top, body_right, &frame, &badge_x, &badge_y) &&
        frame < g_floater_info_art.frame_count) {
        draw_sprite(surface, &g_floater_info_art, frame, badge_x, badge_y);
    }
    /* Initial workers are created with +0x1c cleared by
       FUN_00466fe4/FUN_0041e4e4, so their world badge is eligible. */
    if (island_worker_health_overlay_enabled(g_floater_overlay_flags, 1) &&
        island_worker_stat_badge_layout(
            floater->source_subtype,
            island_floater_health_stat(floater),
            floater->facing_left, body_left, body_top, body_right,
            &frame, &badge_x, &badge_y) &&
        frame < g_floater_info_art.frame_count) {
        draw_sprite(surface, &g_floater_info_art, frame, badge_x, badge_y);
    }
    /* Charge gauge beside the health one, friendly units only. */
    if (island_worker_state_overlay_enabled(g_floater_overlay_flags, 1) &&
        floater->owner_slot == g_menu.selected_tribe &&
        game_session_floater_charge_values(floater, &g_floater_catalog,
                                           &charge_now, &charge_max) &&
        charge_max > 0 &&
        island_worker_charge_badge_layout(
            floater->type_index, floater->source_subtype,
            (int16_t)(((int32_t)(charge_now > 0 ? charge_now : 0) * 10) /
                      charge_max),
            floater->facing_left, body_left, body_top, body_right,
            &frame, &badge_x, &badge_y) &&
        frame < g_floater_info_art.frame_count) {
        draw_sprite(surface, &g_floater_info_art, frame, badge_x, badge_y);
    }
}

static void draw_island_leviathan_floater(RenderSurface *surface,
                                          const GameFloaterStart *floater,
                                          int x, int y)
{
    unsigned int sheet_index = island_leviathan_leg_sheet(
        floater != NULL ? floater->source_subtype : 0);
    const SpriteSheet *leg_art;
    const SpriteSheet *body_art;
    uint32_t leg_frame;
    if (floater == NULL || sheet_index >= 9U) return;
    leg_art = floater->facing_left
        ? &g_leviathan_legs_flipped[sheet_index]
        : &g_leviathan_legs[sheet_index];
    leg_frame = island_leviathan_legs_frame(floater, sheet_index);
    /* FUN_0042704b draws the optional body shape (fltinf shape 0) before the
       mandatory legs shape (shape 1); subtype 9 has legs only. */
    if (floater->source_subtype != 9U) {
        body_art = floater->facing_left
            ? &g_leviathan_body_art_flipped : &g_leviathan_body_art;
        if (body_art->frame_count >= 16U) {
            draw_sprite(surface, body_art, island_leviathan_body_frame(floater),
                        x, y);
        }
    }
    draw_sprite(surface, leg_art, leg_frame, x, y);
}

static void draw_leviathan_sprite_revealed(RenderSurface *surface, const SpriteSheet *art,
                                           uint32_t frame, int x, int y,
                                           int mask_progress)
{
    if (art == NULL || frame >= art->frame_count) return;
    if (mask_progress >= 8) draw_sprite(surface, art, frame, x, y);
    else if (mask_progress > 0)
        draw_feature_reveal(surface, art, g_island_surface_id, frame,
                            x, y, mask_progress);
}

/* FUN_0040bf98's item-6, -8 and -9 branches call FUN_00428191 on the floater
   linked at raw +0x2e, drawing its body/legs at the PROD output point. */
static int draw_island_leviathan_spawn_effect(
    RenderSurface *surface, const GameRuntimeLocation *location,
    const BuildingRenderItem *item, int x, int y, int full_reveal)
{
    int32_t spawned_index;
    const GameFloaterStart *floater;
    unsigned int sheet_index;
    const SpriteSheet *leg_art;
    uint32_t leg_frame;
    uint64_t mask_progress_raw;
    uint32_t prod_duration;
    int mask_progress;
    BuildingRenderPoint output;

    if (location == NULL || item == NULL || !g_game_session_valid ||
        location->leviathan_spawned_floater < 0 ||
        (unsigned int)location->leviathan_spawned_floater >=
            g_game_session.floater_count) return 0;
    spawned_index = location->leviathan_spawned_floater;
    floater = &g_game_session.floaters[(unsigned int)spawned_index];
    if (!game_session_floater_is_active(floater) || floater->type_index != 4)
        return 0;

    /* FUN_00455833 initializes PROD +0x0c as its complete animation-cycle
       duration; use that native divisor for item 8's reveal mask. */
    prod_duration = building_render_prod_duration(item);
    if (full_reveal) {
        mask_progress = 8;
    } else {
        if (prod_duration == 0U) return 0;
        mask_progress_raw = ((uint64_t)location->production_progress * 8U) /
                            prod_duration;
        if (mask_progress_raw == 0U) return 0;
        mask_progress = mask_progress_raw >= 8U ? 8 : (int)mask_progress_raw;
    }
    output = building_render_prod_threshold_position(item, x, y);
    sheet_index = island_leviathan_leg_sheet(floater->source_subtype);
    if (sheet_index >= 9U) return 0;
    leg_art = floater->facing_left
        ? &g_leviathan_legs_flipped[sheet_index]
        : &g_leviathan_legs[sheet_index];
    leg_frame = island_leviathan_legs_frame(floater, sheet_index);
    if (floater->source_subtype >= 10U && floater->source_subtype <= 17U) {
        const SpriteSheet *body_art = floater->facing_left
            ? &g_leviathan_body_art_flipped : &g_leviathan_body_art;
        uint32_t body_frame = island_leviathan_body_frame(floater);
        draw_leviathan_sprite_revealed(surface, body_art, body_frame,
                                       output.x, output.y, mask_progress);
    }
    draw_leviathan_sprite_revealed(surface, leg_art, leg_frame,
                                   output.x, output.y, mask_progress);
    return 1;
}

/* FUN_0040b09a (class-1 sites outside items 6..9) shows the floater a site
   holds at +0x2e while flag 0x002 runs: frame 0 of its body then legs shape,
   unmirrored at (x, y - 0x28), through the FUN_004106dd(1, level) white
   table. Below +0x42 == 17 FUN_004109a6 only recolors the ground under the
   silhouette (level +0x42 / 2); afterwards FUN_00404c5a blits the sprite
   itself through the table, level (100 - +0x42) / 2, both clamped to 0..7. */
static void draw_island_worker_birth(RenderSurface *surface,
                                     const GameRuntimeLocation *location,
                                     int x, int y)
{
    const GameFloaterStart *floater;
    const SpriteSheet *shapes[2];
    int progress;
    int level;
    unsigned int shape;

    if (location == NULL || !g_game_session_valid ||
        location->renderer_class != 1 ||
        (location->record_value_10 >= 6 && location->record_value_10 <= 9) ||
        (location->source_flags & 0x002U) == 0 ||
        location->leviathan_spawned_floater < 0 ||
        (unsigned int)location->leviathan_spawned_floater >=
            g_game_session.floater_count) return;
    floater = &g_game_session.floaters[
        (unsigned int)location->leviathan_spawned_floater];
    if (!game_session_floater_is_active(floater) || floater->type_index >= 4U)
        return;
    shapes[0] = &g_initial_floater_bodies[floater->type_index];
    shapes[1] = &g_initial_floater_legs[floater->type_index];
    progress = (int)location->production_progress;
    level = progress < 0x11 ? progress / 2 : (100 - progress) / 2;
    if (level < 0) level = 0;
    if (level > 7) level = 7;
    for (shape = 0; shape < 2U; ++shape) {
        if (shapes[shape]->frame_count == 0) continue;
        if (progress < 0x11) {
            recolor_under_sprite(surface, shapes[shape], 0, x, y - 0x28,
                                 ISLAND_HAZE_WHITE_BANK, level);
        } else {
            g_sprite_haze_selector = ISLAND_HAZE_WHITE_BANK;
            g_sprite_haze_level = level;
            draw_sprite_scaled(surface, shapes[shape], 0, x, y - 0x28, 0x10000U);
            g_sprite_haze_level = -1;
        }
    }
}

/* FUN_0044034e fills six panel slots from the selected site's eight floater
   links (+4..+0x12): kind 0 fills slots 0..2, kind 1 slots 3..4, kind 2 slot 5
   (no per-kind cap in the source), where the kind is the low nibble of the
   floater's +0x0a (the port's unit level). FUN_00440567 then draws each
   present floater through FUN_0042704b at the fixed pane offsets below; the
   selected floater goes through the FUN_004106dd(1, 1) table. */
static int building_slot_floater_layout(const GameRuntimeLocation *location,
                                        int16_t slots[6], const int **xs,
                                        const int **ys)
{
    static const int x_default[6] = {230, 230, 230, 195, 195, 160};
    static const int y_default[6] = {21, 55, 89, 35, 72, 55};
    static const int x_hall[6] = {220, 999, 999, 220, 999, 170};
    static const int y_hall[6] = {28, 999, 999, 82, 999, 55};
    unsigned int kind;
    unsigned int slot;

    for (slot = 0; slot < 6U; ++slot) slots[slot] = -1;
    /* FUN_00440567 tests the base +0x10 ID; the port's record_value_10 is
       owner-specific, so normalize it or non-slot-0 tribes get the warrior
       table. */
    *xs = location_base_item_id(location) == 0x2f ? x_hall : x_default;
    *ys = location_base_item_id(location) == 0x2f ? y_hall : y_default;
    if (!g_game_session_valid || location->source_location_slot_18 == -1)
        return 0;
    for (kind = 0; kind < 3U; ++kind) {
        unsigned int k = kind == 1U ? 3U : kind == 2U ? 5U : 0U;
        int link;
        for (link = 0; link < 8; ++link) {
            int16_t id = location->charge_floater_slots[link];
            if (id < 0 || (unsigned int)id >= g_game_session.floater_count ||
                (g_game_session.floaters[id].attack_level_flags & 0x0fU) != kind)
                continue;
            if (k < 6U) slots[k] = id;
            ++k;
        }
    }
    return 1;
}

/* FUN_00440451: the first filled slot within |dx| < 15 and |dy| < 15 of its
   fixed pane offset. Returns the floater index or -1. */
static int building_slot_floater_at(const WindowTemplate *info,
                                    const GameRuntimeLocation *location,
                                    int x, int y)
{
    int16_t slots[6];
    const int *xs;
    const int *ys;
    unsigned int slot;
    if (info == NULL || location == NULL ||
        !building_slot_floater_layout(location, slots, &xs, &ys)) return -1;
    for (slot = 0; slot < 6U; ++slot) {
        int dx = x - (info->pane.left + xs[slot]);
        int dy = y - (info->pane.top + ys[slot]);
        if (slots[slot] < 0 || xs[slot] == 999) continue;
        if (dx > -15 && dx < 15 && dy > -15 && dy < 15) return slots[slot];
    }
    return -1;
}

static void draw_building_slot_floaters(RenderSurface *surface, const WindowTemplate *info,
                                        const GameRuntimeLocation *location)
{
    int16_t slots[6];
    const int *xs;
    const int *ys;
    unsigned int slot;
    if (!building_slot_floater_layout(location, slots, &xs, &ys)) return;
    for (slot = 0; slot < 6U; ++slot) {
        const GameFloaterStart *floater;
        GameFloaterStart mirrored;
        uint32_t body_frame;
        const SpriteSheet *body_art;
        const SpriteSheet *leg_art;
        int x = info->pane.left + xs[slot];
        int y = info->pane.top + ys[slot];
        if (slots[slot] < 0 || xs[slot] == 999) continue;
        floater = &g_game_session.floaters[slots[slot]];
        if (floater->type_index >= 4U) continue;
        /* FUN_00440567 sets flag bit 2 (mirrored) on the floater copy it
           passes to FUN_0042704b, so staff face left; param_5 = 1 keeps the
           fltinfo overlays (realm, health, charge) enabled. */
        mirrored = *floater;
        mirrored.facing_left = 1;
        body_art = island_floater_body_art(&mirrored);
        leg_art = island_floater_legs_art(&mirrored);
        body_frame = island_floater_body_sprite_frame(&mirrored, body_art);
        /* param_8 = 1 for the selected floater: FUN_00404c3b loads the
           FUN_004106dd(1, 1) table so body and legs blit through it
           (FUN_00405265 flag bit 0); overlays are drawn unremapped. */
        if (slots[slot] == g_selected_floater) {
            g_sprite_haze_selector = 1;
            g_sprite_haze_level = 1;
        }
        if (body_art->frame_count != 0)
            draw_sprite_scaled(surface, body_art, body_frame, x, y, 0x10000U);
        if (leg_art->frame_count != 0)
            draw_sprite_scaled(surface, leg_art, island_floater_legs_frame(&mirrored),
                               x, y, 0x10000U);
        g_sprite_haze_level = -1;
        draw_island_floater_overlays(surface, &mirrored, body_art, body_frame, x, y);
    }
}

/* Painter at 0x4384f2 (not a Ghidra procedure, decoded by hand from bytes).
   Pass 1 walks the island's 0x60-byte site records and stamps a 3x3 dot
   (FUN_0043842c) at (x,y)/10 + pane origin:
     class 0 pad: owned (FUN_00453cf5: +0x14 == viewer or flag 0x800<<viewer)
                  -> palette slot 1; else +0x14 == 4 -> slot 0
     class 1:     +0x10 == 0 -> slot 4; else slot 0
     class 2:     flag bit 0 (bridge complete) -> slot 5
   Pass 2 walks every floater of the island (FUN_004656d6 mode -2) and writes
   a 2x2 block at (x,y)/10 clamped inside the pane. Pixel n&1 / n>>1 of the
   block carries the owner index (type 4 = both diagonal pixels), the rest
   is slot 0. Colour: slot 1; own floater with link +0x0c != -1 -> slot 2
   (slot 4 for subtype 4); selected own floater -> slot 5.
   Palette slots: g_lilmap_slot_colors (lilmap_slot_color).
   No explored/fog test: the painter never reads the per-player visibility
   spans (FUN_00462285), so unexplored columns are drawn like the rest. */
static void lilmap_fill(RenderSurface *surface, int left, int top, int width, int height,
                        COLORREF color)
{
    render_surface_fill_rect(surface, left, top, left + width, top + height,
                             colorref_pixel(color));
}

static void draw_island_lilmap_dots(RenderSurface *surface, const WindowTemplate *mini_map,
                                    const GameRuntimeIsland *island)
{
    int saved = render_surface_save(surface);
    unsigned int n;
    int viewer = g_menu.selected_tribe;
    render_surface_intersect_clip(surface, mini_map->pane.left, mini_map->pane.top,
                                  mini_map->pane.right + 1, mini_map->pane.bottom + 1);
    if (island != NULL) {
        for (n = 0; n < island->location_count; ++n) {
            const GameRuntimeLocation *loc = &island->locations[n];
            int cx = (int)loc->x / 10 + mini_map->pane.left;
            int cy = (int)loc->y / 10 + mini_map->pane.top;
            int slot = -1;
            if (loc->renderer_class == 0) {
                if (viewer >= 0 && (loc->source_value_14 == viewer ||
                    (loc->source_flags & (0x800U << viewer)) != 0)) slot = 1;
                else if (loc->source_value_14 == 4) slot = 0;
            } else if (loc->renderer_class == 1) {
                slot = loc->record_value_10 == 0 ? 4 : 0;
            } else if (loc->renderer_class == 2) {
                if ((loc->source_flags & 1U) != 0) slot = 5;
            }
            if (slot < 0) continue;
            lilmap_fill(surface, cx - 1, cy - 1, 3, 3, g_lilmap_slot_colors[slot]);
        }
    }
    if (g_game_session_valid) {
        for (n = 0; n < g_game_session.floater_count; ++n) {
            const GameFloaterStart *fl = &g_game_session.floaters[n];
            int own = viewer >= 0 && fl->type_index == (uint8_t)viewer;
            int slot = 1;
            int px;
            int py;
            int pixel;
            if (!game_session_floater_is_active(fl) ||
                fl->island_index != g_menu.selected_map_island) continue;
            if (own && fl->source_link_0c != -1)
                slot = fl->source_subtype == 4 ? 4 : 2;
            /* Port-only: the warriors linked to the selected building are
               drawn like the selected floater. */
            if (own && ((int)n == g_selected_floater ||
                        floater_belongs_to_selected_building(fl))) slot = 5;
            px = (int)fl->x / 10 + mini_map->pane.left;
            py = (int)fl->y / 10 + mini_map->pane.top;
            if (px < mini_map->pane.left) px = mini_map->pane.left;
            if (px > mini_map->pane.right - 1) px = mini_map->pane.right - 1;
            if (py < mini_map->pane.top) py = mini_map->pane.top;
            if (py > mini_map->pane.bottom - 1) py = mini_map->pane.bottom - 1;
            for (pixel = 0; pixel < 4; ++pixel) {
                int lit = fl->type_index == 4 ? (pixel == 0 || pixel == 3)
                                              : pixel == fl->type_index;
                lilmap_fill(surface, px + (pixel & 1), py + (pixel >> 1), 1, 1,
                            g_lilmap_slot_colors[lit ? slot : 0]);
            }
        }
    }
    /* Tail of 0x4384f2, after the dots: bars over the pane outside the
       player's explored extent, then two slot-1 vertical lines 63 px apart at
       scroll/10. */
    {
        int pane_height = mini_map->pane.bottom - mini_map->pane.top + 1;
        int line_x;
        const GameRuntimeIsland *bounds_island = NULL;
        if (g_game_session_valid && viewer >= 0 &&
            viewer < GAME_FLOATER_CATEGORY_COUNT &&
            g_menu.selected_map_island >= 0 &&
            g_menu.selected_map_island < (int)g_game_session.island_count)
            bounds_island = &g_game_session.islands[g_menu.selected_map_island];
        if (bounds_island != NULL) {
            /* island+0x408 / +0x40c per player (floater_min_x / floater_max_x):
               left bar when left > 0, right bar when right < 0x9ff. */
            int left = bounds_island->floater_min_x[viewer];
            int right = bounds_island->floater_max_x[viewer];
            int bar_left[2];
            int bar_right[2];
            int bar;
            bar_left[0] = mini_map->pane.left;
            bar_right[0] = mini_map->pane.left + (left > 0 ? left / 10 : 0);
            bar_left[1] = mini_map->pane.left + right / 10;
            bar_right[1] = right < 0x9ff ? mini_map->pane.right + 1
                                         : bar_left[1];
            for (bar = 0; bar < 2; ++bar) {
                if (bar_right[bar] <= bar_left[bar]) continue;
                /* Default path ([0x4c2bac] == 0, set only by a float.cfg
                   "temphole" line): FillRect8 with palette index
                   [0x4c2b08] == 0 ("holecolor" in float.cfg overrides). */
                lilmap_fill(surface, bar_left[bar], mini_map->pane.top,
                            bar_right[bar] - bar_left[bar], pane_height,
                            g_island_palette[0]);
            }
        }
        line_x = mini_map->pane.left + g_island_scroll_x / 10;
        lilmap_fill(surface, line_x, mini_map->pane.top, 1, pane_height,
                    g_lilmap_slot_colors[1]);
        lilmap_fill(surface, line_x + 63, mini_map->pane.top, 1, pane_height,
                    g_lilmap_slot_colors[1]);
    }
    if (saved != 0) render_surface_restore(surface, saved);
}

/* FUN_0042f8f7 hides IWTextInfo while IWFltInfo (same 456,328 pane) shows the
   selected floater. */
static int island_floater_info_shown(void)
{
    if (!g_game_session_valid || g_selected_floater < 0 ||
        (unsigned int)g_selected_floater >= g_game_session.floater_count ||
        g_menu.selected_map_island < 0) return 0;
    return g_game_session.floaters[g_selected_floater].island_index ==
            g_menu.selected_map_island &&
        game_session_floater_is_active(
            &g_game_session.floaters[g_selected_floater]);
}

/* FUN_0042fa0f message 7 (control hover): IWMove/IWHallMove give index 1,
   other BC_* buttons their 0x49e700 index (spells 0x15..0x1c use mode 4);
   IWTextInfo mode 5 then shows gamey.txt BC<index>. Returns -1 when no
   BC_* control is hovered. */
static int hovered_control_caption_index(void)
{
    static const int order_genre_index[5] = {16, 17, 18, 19, 15};
    IslandLocationActionControl action = selected_location_action();
    if (action != ISLAND_LOCATION_ACTION_NONE &&
        g_hovered_location_action == action) return 1;
    if (g_hovered_onoff_control) return 0;
    if (g_hovered_upgrade_control) return 2;
    if (g_hovered_repair_control) return 3;
    if (g_hovered_training_stock == 1 || g_hovered_training_stock == 2)
        return 4 + g_hovered_training_stock;
    if (g_hovered_hall_stock >= 0 && g_hovered_hall_stock < 3)
        return 7 + g_hovered_hall_stock;
    switch (g_hovered_hall_command) {
    case WINDOW_ISLAND_PANEL_GENERAL: return 10;
    case WINDOW_ISLAND_PANEL_INVENTORY: return 11;
    case WINDOW_ISLAND_PANEL_GLYPHS: return 12;
    case WINDOW_ISLAND_PANEL_TRADE: return 13;
    case WINDOW_ISLAND_PANEL_DIPLOMACY: return 14;
    default: break;
    }
    if (g_hovered_defend_area >= 6 && g_hovered_defend_area <= 10)
        return order_genre_index[g_hovered_defend_area - 6];
    if (g_hovered_upgspread) return 20;
    return -1;
}

/* spells.txt (TONE00.COB): entries of a name line, "Level n", "MagCost n",
   "CryCost n", description lines and END; ';' lines are comments. The
   description lines are joined with spaces, as FUN_00428baa re-wraps them. */
static void load_spell_text(void)
{
    CobArchive archive;
    const CobMember *member;
    unsigned char *bytes;
    char error[256];
    size_t cursor = 0;
    int entry = 0;
    int state = 0;

    if (g_spell_text_loaded) return;
    g_spell_text_loaded = 1;
    if (!cob_archive_open(game_file_path("TONE00.COB"), &archive,
                          error, sizeof(error))) return;
    member = cob_archive_find(&archive, "spells.txt");
    bytes = member == NULL ? NULL : (unsigned char *)malloc(member->length + 1);
    if (bytes != NULL &&
        cob_archive_read_member(&archive, member, bytes, member->length,
                                error, sizeof(error))) {
        while (cursor < member->length && entry < SPELL_TEXT_COUNT) {
            char line[256];
            size_t length = 0;
            while (cursor < member->length && bytes[cursor] != '\n') {
                if (bytes[cursor] != '\r' && length + 1 < sizeof(line))
                    line[length++] = (char)bytes[cursor];
                ++cursor;
            }
            ++cursor;
            while (length > 0 && line[length - 1] == ' ') --length;
            line[length] = '\0';
            if (length == 0 || line[0] == ';') continue;
            if (state == 0) {
                (void)snprintf(g_spell_names[entry], sizeof(g_spell_names[entry]),
                               "%s", line);
                g_spell_descriptions[entry][0] = '\0';
                state = 1;
            } else if (strncmp(line, "Level", 5) == 0) {
                g_spell_levels[entry] = atoi(line + 5);
            } else if (strncmp(line, "MagCost", 7) == 0 ||
                       strncmp(line, "CryCost", 7) == 0) {
            } else if (strcmp(line, "END") == 0) {
                ++entry;
                state = 0;
            } else {
                size_t used = strlen(g_spell_descriptions[entry]);
                (void)snprintf(g_spell_descriptions[entry] + used,
                               sizeof(g_spell_descriptions[entry]) - used,
                               used != 0 ? " %s" : "%s", line);
            }
        }
    }
    free(bytes);
    cob_archive_close(&archive);
}

/* FUN_00439673 mode 4 (ev_4a8e68ad): the hovered spell's spells.txt row
   (FUN_00450070 = the 0x4a2878 table entry of the world and button). Name
   at (10, 2), "Niveau <Level>" at (10, 11), both in SMFONT, the name in
   palette index 2 when no linked floater can cast it (FUN_0045d8f4 < 0),
   then the description in index 6 wrapped like the building texts from
   y = 13 + h. */
static int draw_spell_hover_info(RenderSurface *surface)
{
    const WindowTemplate *text_panel;
    COLORREF name_color = native_text_color(g_island_palette, 6);
    char level_text[64];
    int kind = g_hovered_spell_kind;
    int h = (int)g_small_font.height;
    if (kind < 0 || kind >= SPELL_TEXT_COUNT) return 0;
    load_spell_text();
    if (g_spell_names[kind][0] == '\0') return 0;
    text_panel = window_catalog_find(&g_window_catalog, "IWTextInfo", 3);
    if (text_panel == NULL || text_panel->shape_frame < 0 ||
        (uint32_t)text_panel->shape_frame >= g_temp_hole_art.frame_count) return 0;
    draw_sprite(surface, &g_temp_hole_art, (uint32_t)text_panel->shape_frame,
                text_panel->pane.left, text_panel->pane.top);
    if (selection_island() >= 0 && g_selected_location >= 0 &&
        g_menu.selected_tribe >= 0 &&
        g_menu.selected_tribe < GAME_START_PLAYER_COUNT &&
        !game_session_spell_has_caster(&g_game_session,
            (uint8_t)selection_island(), (uint16_t)g_selected_location,
            (uint8_t)g_menu.selected_tribe, (unsigned int)kind))
        name_color = native_text_color(g_island_palette, 2);
    draw_small_label(surface, g_spell_names[kind], text_panel->pane.left + 10,
                     text_panel->pane.top + 2, name_color);
    (void)snprintf(level_text, sizeof(level_text), "%s %d",
                   g_unit_label_text[2], g_spell_levels[kind]);
    draw_small_label(surface, level_text, text_panel->pane.left + 10,
                     text_panel->pane.top + 11, name_color);
    draw_wrapped_small_label(surface, g_spell_descriptions[kind],
        text_panel->pane.left + 10, text_panel->pane.top + 13 + h + h + 1,
        173 - 10, (LOGICAL_HEIGHT - text_panel->pane.top) / (h + 1), h + 1,
        native_text_color(g_island_palette, 6));
    return 1;
}

/* FUN_00439673 mode 5: the BC<index> caption centred in IWTextInfo with
   BIGFONT, palette index 6, at y = (bottom - top) / 2 - 10. */
static void draw_control_hover_caption(RenderSurface *surface)
{
    const WindowTemplate *text_panel;
    const char *caption;
    int index = hovered_control_caption_index();
    int width;
    int x;
    int y;
    /* Spell buttons (0x15..0x1c) take mode 4 instead of mode 5. */
    if (draw_spell_hover_info(surface)) return;
    if (index < 0) return;
    caption = g_bc_text[index];
    if (caption[0] == '\0') return;
    text_panel = window_catalog_find(&g_window_catalog, "IWTextInfo", 3);
    if (text_panel == NULL || text_panel->shape_frame < 0 ||
        (uint32_t)text_panel->shape_frame >= g_temp_hole_art.frame_count) return;
    draw_sprite(surface, &g_temp_hole_art, (uint32_t)text_panel->shape_frame,
                text_panel->pane.left, text_panel->pane.top);
    width = g_big_font.bytes != NULL
        ? measure_big_text(caption, strlen(caption))
        : measure_bitmap_text(NULL, caption, strlen(caption));
    x = text_panel->pane.left +
        ((text_panel->pane.right - text_panel->pane.left) - width) / 2;
    y = text_panel->pane.top +
        (text_panel->pane.bottom - text_panel->pane.top) / 2 - 10;
    if (g_big_font.bytes != NULL)
        draw_big_label(surface, caption, x, y,
                       native_text_color(g_island_palette, 6));
    else
        draw_bitmap_label(surface, caption, x, y,
                          native_text_color(g_island_palette, 6));
}

static void render_island_view(RenderSurface *surface)
{
    const int image_top = 0;
    const int status_top = 320;
    const GameFloaterStart *selected_floater = NULL;
    int hall_player;
    /* FUN_0042f303 mode 0 selects the home Hall through FUN_0042f755, so an
       empty selection behaves exactly like a manual Hall click (description,
       controls, clipboard entry), on any island. */
    if (hall_default_selected()) {
        const GamePlayerEconomy *home =
            &g_game_session.economy[g_menu.selected_tribe];
        select_location_anywhere(home->hall_island_index,
                                 (int)home->hall_location_index);
    }
    hall_player = selected_hall_player();
    int saved_dc;
    uint16_t i;
    const GameRuntimeIsland *runtime_island = NULL;
    const GameRuntimeLocation *selected_runtime_location = NULL;
    int selected_ground_item = -1;
    const GameRuntimeIsland *info_island = NULL;
    int info_location = -1;
    uint8_t info_island_index = 0;

    if (g_game_session_valid && g_menu.selected_map_island >= 0 &&
        g_menu.selected_map_island < g_game_session.island_count) {
        runtime_island = &g_game_session.islands[g_menu.selected_map_island];
        if (view_selected_location() >= 0 &&
            view_selected_location() < runtime_island->location_count) {
            selected_runtime_location =
                &runtime_island->locations[view_selected_location()];
            selected_ground_item = island_panel_info_ground_item_id(
                selected_runtime_location->record_value_10,
                selected_runtime_location->renderer_class,
                selected_runtime_location->owner_id,
                selected_runtime_location->record_value_24);
        }
        if (g_selected_floater >= 0 &&
            g_selected_floater < g_game_session.floater_count) {
            const GameFloaterStart *candidate =
                &g_game_session.floaters[g_selected_floater];
            /* FUN_0044338b: a released/dying unit (flag 0x8, +0x24 >= 40)
               hides IWFltInfo, posts 0x44 and the location stays selected. */
            if (candidate->island_index == g_menu.selected_map_island &&
                game_session_floater_is_active(candidate)) {
                selected_floater = candidate;
            }
        }
    }

    g_island_scroll_x = island_clamp_scroll(g_island_scroll_x);
    if (g_menu.selected_map_island >= 0 &&
        g_menu.selected_map_island < WORLD_MAP_MAX_ISLANDS) {
        g_island_scroll_by_island[g_menu.selected_map_island] = g_island_scroll_x;
    }
    fill_rect(surface, 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT, RGB(0, 0, 0));
    if (g_island_height_data == NULL ||
        g_island_height_length != ISLAND_HAZE_FILE_BYTES) {
        draw_sprite(surface, &g_island_template_art, 0, 0, status_top);
        return;
    }
    draw_sprite_region(surface, &g_island_surface_art, 0, g_island_scroll_x, 0,
                       LOGICAL_WIDTH, 320, 0, image_top);

    /* windows.txt defines ISLEVIEW as the 640x320 upper pane. Clip sprites to
       that view so tall SHP frames cannot overwrite the ISLETEMP controls. */
    saved_dc = render_surface_save(surface);
    render_surface_intersect_clip(surface, 0, 0, LOGICAL_WIDTH, status_top);
    for (i = 0; i < g_island_surface_data.location_count; ++i) {
        uint16_t location_index = g_island_draw_order[i];
        const IslandLocation *location = &g_island_surface_data.locations[location_index];
        const GameRuntimeLocation *runtime_location =
            runtime_island != NULL && location_index < runtime_island->location_count
                ? &runtime_island->locations[location_index] : NULL;
        int x = (int)location->x - g_island_scroll_x;
        int y = image_top + (int)location->y;
        int pad_group = island_pad_group(location);
        int runtime_class = location->renderer_class;
        if (location->renderer_class == 3 &&
            (location->renderer_variant == 4 || location->renderer_variant == 0x16)) {
            draw_island_feature(surface, g_island_surface_id, location,
                                runtime_location, -g_island_scroll_x,
                                image_top);
            continue;
        }
        /* FUN_00461859 demotes unmatched class-2 records to class 0 at game
           startup. Draw the bridge trigger only for records still paired to a
           world-map neighbor; preserve the source class in the parsed data. */
        if (runtime_location != NULL && location->renderer_class == 2 &&
            runtime_location->bridge_neighbor_island < 0) {
            runtime_class = 0;
        }
        /* The island loop FUN_00435f4d and the painter FUN_0040bf98 do not
           test the WORLDPOS bridge flag (DAT_006136b4) or +0x36: a marker
           whose link is inactive still draws its BASE layer
           (ev_9466be6d877d3a7686cb6bcf7838301774c412a8e560a476b938307aac8b32ad). */
        /* PIT_Object has no building SHP of its own; generated collectible
           items draw their TRIGGERS frame from +0x24 below. PIT_FeatureTrigger
           also has no SHP. Item IDs are distinct from renderer_class. */
        if (location->renderer_class == 3 && location->renderer_variant == 3) {
            if (runtime_location == NULL || runtime_location->record_value_10 <= 0) continue;
        }
        if (x < -4 || x >= LOGICAL_WIDTH + 4) continue;
        if (island_site_is_hidden_pad((int)location_index)) continue;
        /* The original class-2 bridge site is distinct from class-0 pads.
           bldinf.txt defines BR-TRG01's static BASE as frame 1; the COB's
           corresponding SHP stores that frame at index 0. */
        if (runtime_class == 2 && runtime_location != NULL &&
            draw_runtime_item(surface, runtime_location, x, y)) continue;
        if (runtime_class == 2 && g_bridge_trigger_art.frame_count == 23) {
            draw_sprite(surface, &g_bridge_trigger_art, 0, x, y);
            continue;
        }
        {
        /* Island TXT `tone` rows denote unoccupied Tone pools. shapes.txt maps
           POOL to tone.shp; bldinf.txt gives the 2..40 ping-pong animation. */
        {
        int32_t runtime_item_id = runtime_location != NULL
            ? runtime_location->record_value_10 : 0;
        int covered_by_leviathan_building = runtime_item_id > 0 &&
            runtime_item_id < g_pad_catalog.item_count &&
            g_pad_catalog.items[runtime_item_id].tribe == PAD_TRIBE_LEVIATHAN;
        if (island_tone_pool_should_draw(location->kind == ISLAND_LOCATION_TONE,
                                         runtime_item_id,
                                         covered_by_leviathan_building) &&
            g_tone_field_art.frame_count == 40) {
            uint16_t render_counter = runtime_location != NULL
                ? island_tone_pool_render_counter(runtime_item_id,
                    runtime_location->owner_id,
                    runtime_location->tribe_visibility_mask,
                    g_game_session.config.selected_tribe,
                    runtime_location->chug_progress)
                : 0U;
            uint32_t frame = island_tone_pool_frame(runtime_item_id,
                render_counter);
            /* FUN_0040bf98 draws POOL's BASE segment, then composites CHUG on
               top. bldinf.txt stores BASE 1 1, hence frame zero in decoded SHP. */
            draw_sprite(surface, &g_tone_field_art, ISLAND_TONE_POOL_BASE_FRAME, x, y);
            draw_sprite(surface, &g_tone_field_art, frame, x, y);
            draw_island_worker_birth(surface, runtime_location, x, y);
        }
        }
        /* FUN_0040bf98 draws an installed runtime item at this record. Such an
           item occupies the construction site, so its sprite replaces PAD.SHP.
           Keep the animated ring only when no drawable item occupies the site. */
        {
            int is_construction_site = location->kind == ISLAND_LOCATION_PAD ||
                island_pad_group(location) >= 0;
            int32_t runtime_item_id = runtime_location != NULL
                ? runtime_location->record_value_10 : 0;
            int is_leviathan_building_on_tone =
                location->kind == ISLAND_LOCATION_TONE &&
                runtime_item_id > 0 &&
                runtime_item_id != ISLAND_TONE_POOL_ITEM_ALTERNATE &&
                runtime_item_id < g_pad_catalog.item_count &&
                g_pad_catalog.items[runtime_item_id].tribe == PAD_TRIBE_LEVIATHAN;
            int is_item_render_site = is_construction_site ||
                is_leviathan_building_on_tone;
            /* FUN_0040ae4d keeps the PADS ring under a resource pile
               (+0x10 == 1, +0x24 1..3); only trigger codes 5.. replace it. */
            int resource_pile = runtime_location != NULL &&
                runtime_location->record_value_10 == 1 &&
                runtime_location->record_value_24 >= 1 &&
                runtime_location->record_value_24 <= 3;
            int occupied = is_item_render_site && runtime_location != NULL &&
                runtime_location->record_value_10 > 0 && !resource_pile;
            int has_runtime_item = is_item_render_site && !resource_pile
                ? draw_runtime_item(surface, runtime_location, x, y) : 0;
            if (occupied && !has_runtime_item)
                (void)draw_ground_item_icon(surface, runtime_location, x, y);
            if (!has_runtime_item && !occupied &&
                island_site_should_draw_pad(pad_group, occupied) &&
                g_pad_art.frame_count == 27) {
                uint32_t frame = island_pad_frame(g_menu.animation_ticks,
                                                  location->x,
                                                  (unsigned)pad_group,
                                                  location->renderer_subtype);
                draw_sprite(surface, &g_pad_art, frame, x, y);
            }
            /* FUN_0040ae4d draws the PADS ring, then the pad's resource pile:
               FUN_004502dc gives +0x24 when +0x10 == 1, and code 1 selects
               bildtone frame min(+0x28 - 1, 0x31) at the site point
               (ev_2383b2e1, ev_c3e3a1fb). FUN_004503bd turns an empty
               class-0 pad into that state on the first Build Tone deposit
               (ev_a294ffae); the port keeps +0x10 at 0 and stores the
               deposit in resource_stock[0], so both states draw the pile. */
            if (is_construction_site && runtime_location != NULL &&
                (runtime_location->record_value_10 == 0 ||
                 (runtime_location->record_value_10 == 1 &&
                  runtime_location->record_value_24 == 1)) &&
                runtime_location->resource_stock[GAME_RESOURCE_BUILD_TONE] != 0 &&
                g_bildtone_art.frame_count != 0) {
                uint32_t frame = (uint32_t)runtime_location->resource_stock[
                    GAME_RESOURCE_BUILD_TONE] - 1U;
                if (frame > 0x31U) frame = 0x31U;
                if (frame >= g_bildtone_art.frame_count)
                    frame = g_bildtone_art.frame_count - 1U;
                draw_sprite(surface, &g_bildtone_art, frame, x, y);
            }
        }
        }
    }
    /* FUN_0046466f creates four idle type-0 floaters for each player at the
       selected hall marker. FUN_0042704b draws tribe-specific legs and body
       separately, switching from hover to carry legs when cargo is present.
       FUN_00435f4d skips floaters with +0x1c bit 0x001: a newborn held at its
       site (0x801, FUN_004532e2) stays hidden until release, and only the
       Leviathan sites 6/8/9 draw it themselves. */
    if (runtime_island != NULL && g_game_session_valid) {
        unsigned floater_index;
        for (floater_index = 0; floater_index < g_game_session.floater_count;
             ++floater_index) {
            const GameFloaterStart *floater = &g_game_session.floaters[floater_index];
            int floater_x;
            int floater_y;
            uint32_t leg_frame;
            uint32_t body_frame_index;
            const SpriteSheet *body_art;
            const SpriteSheet *leg_art;
            if (!game_session_floater_is_active(floater) ||
                floater->island_index != g_menu.selected_map_island ||
                floater->type_index > 4 ||
                (floater->source_runtime_flags & 0x001U) != 0) continue;
            floater_x = (int)floater->x - g_island_scroll_x;
            if (floater_x < -64 || floater_x >= LOGICAL_WIDTH + 64) continue;
            floater_y = image_top + (int)floater->y;
            if (floater->type_index == 4) {
                draw_island_leviathan_floater(surface, floater, floater_x, floater_y);
                /* Overlays need the body shape (local_c != 0): subtype 9
                   has legs only and gets none. */
                if (floater->source_subtype >= 10U &&
                    floater->source_subtype <= 17U) {
                    draw_island_floater_overlays(
                        surface, floater,
                        floater->facing_left ? &g_leviathan_body_art_flipped
                                             : &g_leviathan_body_art,
                        island_leviathan_body_frame(floater),
                        floater_x, floater_y);
                }
                continue;
            }
            {
                /* Bridge crossings draw unflipped, lifted and stippled;
                   the overlays keep the facing bounds (local_a4). */
                GameFloaterStart drawn = *floater;
                int stipple_level;
                floater_y -= island_floater_bridge_lift(floater,
                                                        &stipple_level);
                if (stipple_level < 8) drawn.facing_left = 0;
                leg_frame = island_floater_legs_frame(&drawn);
                body_art = island_floater_body_art(&drawn);
                leg_art = island_floater_legs_art(&drawn);
                draw_island_floater_cargo(surface, &drawn, floater_x, floater_y,
                                          stipple_level);
                body_frame_index = island_floater_body_sprite_frame(&drawn,
                                                                    body_art);
                if (body_art->frame_count != 0)
                    draw_island_floater_layer(surface, body_art, body_frame_index,
                                              floater_x, floater_y, 0x10000U,
                                              stipple_level);
                if (leg_art->frame_count != 0)
                    draw_island_floater_layer(surface, leg_art, leg_frame,
                                              floater_x, floater_y, 0x10000U,
                                              stipple_level);
                body_art = island_floater_body_art(floater);
                draw_island_floater_overlays(surface, floater, body_art,
                                             body_frame_index,
                                             floater_x, floater_y);
            }
        }
    }
    if (runtime_island != NULL && g_game_session_valid) {
        unsigned int projectile_index;
        for (projectile_index = 0; projectile_index < 32; ++projectile_index) {
            const GameDefenseProjectile *projectile =
                &g_game_session.defense_projectiles[projectile_index];
            const SpriteSheet *effect_art;
            uint32_t frame;
            int x;
            int y;
            if (projectile->active == 0 ||
                projectile->island_index != g_menu.selected_map_island ||
                projectile->effect_sheet_index >= 4) continue;
            effect_art = projectile->impact_phase != 0
                ? &g_leviathan_impact_art[projectile->effect_sheet_index]
                : &g_leviathan_projectile_art[projectile->effect_sheet_index];
            if (effect_art->frame_count == 0) continue;
            x = (int)projectile->x - g_island_scroll_x;
            y = image_top + (int)projectile->y;
            if (x < -32 || x >= LOGICAL_WIDTH + 32) continue;
            if (projectile->impact_phase != 0) {
                uint32_t impact_offset = projectile->animation_tick / 2U;
                if (projectile->impact_frame_count == 0) continue;
                if (impact_offset >= projectile->impact_frame_count)
                    impact_offset = projectile->impact_frame_count - 1U;
                frame = (uint32_t)projectile->impact_frame_start + impact_offset;
            } else {
                frame = (projectile->animation_tick / 2U) % effect_art->frame_count;
            }
            if (frame >= effect_art->frame_count) continue;
            draw_sprite(surface, effect_art, frame, x, y);
        }
        /* fltinf atteff effects (FUN_00415fc6 path A): ONESHOT, BULLET and
           CAST+CHAIN instances; world anchor is an interpretation. */
        for (projectile_index = 0; projectile_index < GAME_SESSION_MAX_CAST_EFFECTS;
             ++projectile_index) {
            int def_index;
            int visual_realm;
            unsigned int effect_frame;
            uint16_t world_x;
            uint16_t world_y;
            uint8_t effect_island;
            const SpriteSheet *effect_art;
            int x;
            if (!game_session_attack_visual(&g_game_session, projectile_index,
                    &def_index, &effect_frame, &world_x, &world_y,
                    &effect_island, &visual_realm)) continue;
            if (effect_island != g_menu.selected_map_island) continue;
            if (visual_realm < 0 && def_index >= 0 && def_index < FLOATER_EFFECT_MAX &&
                g_floater_catalog.effects[def_index].type == FLOATER_EFFECT_LIGHTNING) {
                /* FUN_004182c8: up to ten stacked sprites growing down onto
                   the target; segments 3..5 of the pattern are mirrored. */
                GameLightningSegment segments[GAME_LIGHTNING_MAX_SEGMENTS];
                int segment_count = game_session_lightning_segments(
                    &g_game_session, projectile_index, segments);
                int segment;
                for (segment = 0; segment < segment_count; ++segment) {
                    const SpriteSheet *bolt_art =
                        segments[segment].mirrored &&
                        g_attack_effect_art_flipped[def_index].frame_count != 0
                            ? &g_attack_effect_art_flipped[def_index]
                            : &g_attack_effect_art[def_index];
                    int bolt_x = segments[segment].x - g_island_scroll_x;
                    if (segments[segment].frame >= bolt_art->frame_count ||
                        bolt_x < -64 || bolt_x >= LOGICAL_WIDTH + 64) continue;
                    draw_sprite(surface, bolt_art, segments[segment].frame, bolt_x,
                                image_top + segments[segment].y);
                }
                continue;
            }
            /* FUN_004182c8 flips the slot horizontally when flag 0x1 is set. */
            if (visual_realm >= 0) {
                effect_art = &g_leviathan_impact_art[visual_realm & 3];
                if (game_session_attack_visual_mirrored(&g_game_session,
                        projectile_index) &&
                    g_attack_impact_art_flipped[visual_realm & 3].frame_count != 0)
                    effect_art = &g_attack_impact_art_flipped[visual_realm & 3];
            } else {
                if (def_index < 0 || def_index >= FLOATER_EFFECT_MAX) continue;
                effect_art = &g_attack_effect_art[def_index];
                if (game_session_attack_visual_mirrored(&g_game_session,
                        projectile_index) &&
                    g_attack_effect_art_flipped[def_index].frame_count != 0)
                    effect_art = &g_attack_effect_art_flipped[def_index];
            }
            if (effect_frame >= effect_art->frame_count) continue;
            x = (int)world_x - g_island_scroll_x;
            if (x < -64 || x >= LOGICAL_WIDTH + 64) continue;
            draw_sprite(surface, effect_art, effect_frame, x, image_top + (int)world_y);
        }
        /* Floater attack hit: the realm IMPACT instance FUN_0041e569 starts
           when damage lands (frames per effects.txt). The target anchor is an
           interpretation, as for tower bolt impacts. */
        for (projectile_index = 0; projectile_index < g_game_session.floater_count;
             ++projectile_index) {
            unsigned int impact_realm;
            unsigned int impact_frame;
            uint16_t world_x;
            uint16_t world_y;
            const SpriteSheet *impact_art;
            int x;
            if (!game_session_attack_effect_visual(&g_game_session,
                    projectile_index, &impact_realm, &impact_frame,
                    &world_x, &world_y)) continue;
            if (g_game_session.floaters[projectile_index].island_index !=
                g_menu.selected_map_island) continue;
            impact_art = &g_leviathan_impact_art[impact_realm];
            if (impact_frame >= impact_art->frame_count) continue;
            x = (int)world_x - g_island_scroll_x;
            if (x < -64 || x >= LOGICAL_WIDTH + 64) continue;
            draw_sprite(surface, impact_art, impact_frame, x, image_top + (int)world_y);
        }
        /* FA_Cast visuals (FUN_0041660b names, FUN_00415063 frame stepping).
           Anchor on the effect position is an interpretation; the original
           effect-slot blitter is not located. Drawn after floaters. */
        for (projectile_index = 0; projectile_index < GAME_SESSION_MAX_CAST_EFFECTS;
             ++projectile_index) {
            int visual;
            unsigned int cast_frame;
            const SpriteSheet *cast_art;
            int x;
            int y;
            GameCastSprite specials[3];
            int special_count = game_session_cast_special_sprites(
                &g_game_session, projectile_index, specials);
            if (special_count >= 0) {
                int special;
                if (g_game_session.floaters[g_game_session.cast_effects[
                        projectile_index].caster_index].island_index !=
                    g_menu.selected_map_island) continue;
                for (special = 0; special < special_count; ++special) {
                    const GameCastSprite *sprite = &specials[special];
                    cast_art = sprite->visual == GAME_CAST_SPRITE_OBJECT
                        ? &g_inventory_item_art
                        : &g_cast_effect_art[sprite->visual];
                    x = (int)sprite->x - g_island_scroll_x;
                    y = image_top + (int)sprite->y;
                    if (sprite->frame >= cast_art->frame_count ||
                        x < -64 || x >= LOGICAL_WIDTH + 64) continue;
                    if (sprite->stipple >= 8)
                        draw_sprite(surface, cast_art, sprite->frame, x, y);
                    else
                        draw_feature_reveal(surface, cast_art, g_island_surface_id,
                                            sprite->frame, x, y, sprite->stipple);
                }
                continue;
            }
            if (!game_session_cast_effect_visual(&g_game_session,
                    projectile_index, &visual, &cast_frame)) continue;
            if (g_game_session.floaters[g_game_session.cast_effects[
                    projectile_index].caster_index].island_index !=
                g_menu.selected_map_island) continue;
            /* FUN_004182c8 draws with x scale -1.0 when flag bit 0 is set. */
            cast_art = g_game_session.cast_effects[projectile_index].mirrored &&
                    g_cast_effect_art_flipped[visual].frame_count != 0
                ? &g_cast_effect_art_flipped[visual]
                : &g_cast_effect_art[visual];
            if (cast_frame >= cast_art->frame_count) continue;
            x = (int)g_game_session.cast_effects[projectile_index].effect_x -
                g_island_scroll_x;
            y = image_top +
                (int)g_game_session.cast_effects[projectile_index].effect_y;
            if (x < -64 || x >= LOGICAL_WIDTH + 64) continue;
            draw_sprite(surface, cast_art, cast_frame, x, y);
        }
    }
    if (saved_dc != 0) render_surface_restore(surface, saved_dc);

    /* ISLETMP is the original 640x160 bottom template at y=320, matching the
       ISLETMP pane in windows.txt. It uses the active island palette. */
    draw_sprite(surface, &g_island_template_art, 0, 0, status_top);

    /* windows.txt declares the always-present island controls separately from
       ISLETEMP. FUN_0042fa0f shows GOTOMAP/PANIC/TOGREALM/TASKLIST at entry to
       island state; mainbut0.shp supplies their normal and adjacent hover
       frames, while ISREALM is the companion left-panel artwork. */
    {
        const WindowTemplate *realm_panel = window_catalog_find(
            &g_window_catalog, "IWRealm", 3);
        static const char *const button_names[] = {
            "GOTOMAP", "PANIC", "TOGREALM", "TASKLIST"
        };
        size_t button_index;
        /* ISREALM frames 0..27 are the 32x32 realm markers and 28..41 the
           6x6 slider dots; FUN_00438b05 replaces the WINTYPE 17 paint, so
           SHAPEFRAME 0 is never blitted at the pane origin. */
        /* FUN_00438b05 (IWRealm paint, ev_e22d777e / ev_75d19e75): marker i
           shows realm k = tribe + i with frame 7 * (k & 3) + v, v the cycle
           level of its parity (min(A / 1428, 6) odd, min(B / 1142, 6) even),
           mirrored to 6 - v when (k & 2) == 0. The A slider (frame 41 - vA)
           runs along the diamond edge whose k & 3 is 1 and the B slider
           (34 - vB) along the one whose k & 3 is 0, D * A / 10000 or
           D * B / 8000 pixels toward the opposite corner. */
        if (realm_panel != NULL && g_game_session_valid &&
            g_island_realm_art.frame_count != 0) {
            static const int marker_x[4] = { 62, 109, 62, 15 };
            static const int marker_y[4] = { 335, 382, 429, 382 };
            static const int corner_x[4] = { 77, 105, 77, 51 };
            static const int corner_y[4] = { 372, 397, 426, 397 };
            int32_t cycle_a = g_game_session.realm_cycle_a;
            int32_t cycle_b = g_game_session.realm_cycle_b;
            int level_a = cycle_a / 1428 > 6 ? 6 : cycle_a / 1428;
            int level_b = cycle_b / 1142 > 6 ? 6 : cycle_b / 1142;
            int corner;
            /* Two FUN_00406604 inclusive fills in palette index 0
               (FUN_0042dd0f(0), DAT_0049e140[0] = 0) form the slider
               cross: x 74..80 / y 367..431 and x 46..110 / y 394..400. */
            fill_rect(surface, corner_x[0] - 3, corner_y[0] - 5,
                      corner_x[0] + 3 + 1, corner_y[2] + 5 + 1,
                      g_island_palette[0]);
            fill_rect(surface, corner_x[3] - 5, corner_y[3] - 3,
                      corner_x[1] + 5 + 1, corner_y[3] + 3 + 1,
                      g_island_palette[0]);
            for (corner = 0; corner < 4; ++corner) {
                int k = g_menu.selected_tribe + corner;
                int level = (k & 1) != 0 ? level_a : level_b;
                uint32_t frame;
                if ((k & 2) == 0) level = 6 - level;
                frame = (uint32_t)(7 * (k & 3) + level);
                if (frame < g_island_realm_art.frame_count)
                    draw_sprite(surface, &g_island_realm_art, frame,
                                marker_x[corner], marker_y[corner]);
            }
            for (corner = 0; corner < 4; ++corner) {
                int k = (g_menu.selected_tribe + corner) & 3;
                int opposite = (corner + 2) & 3;
                int span = (corner_x[opposite] - corner_x[corner]) +
                           (corner_y[opposite] - corner_y[corner]);
                int offset;
                int x = corner_x[corner];
                int y = corner_y[corner];
                uint32_t frame;
                if (k == 1) {
                    if (span < 0) span = -span;
                    offset = (int)((double)span * cycle_a / 10000.0);
                    frame = (uint32_t)(41 - level_a);
                } else if (k == 0) {
                    if (span < 0) span = -span;
                    offset = (int)((double)span * cycle_b / 8000.0);
                    frame = (uint32_t)(34 - level_b);
                } else {
                    continue;
                }
                if (corner_y[corner] == corner_y[opposite])
                    x += corner_x[opposite] > x ? offset : -offset;
                else
                    y += corner_y[opposite] > y ? offset : -offset;
                if (frame < g_island_realm_art.frame_count)
                    draw_sprite(surface, &g_island_realm_art, frame, x, y);
            }
        }
        for (button_index = 0;
             button_index < sizeof(button_names) / sizeof(button_names[0]);
             ++button_index) {
            const WindowTemplate *button = window_catalog_find(
                &g_window_catalog, button_names[button_index], 3);
            int frame;
            if (button == NULL || button->shape_frame < 0) continue;
            /* Remake: PANIC keeps its highlighted frame while the mode is on. */
            frame = window_catalog_control_frame(
                button, (int)button_index == g_hovered_island_button ||
                ((int)button_index == WINDOW_ISLAND_BUTTON_PANIC &&
                 g_game_session_valid && g_menu.selected_map_island >= 0 &&
                 game_session_panic_active(
                     &g_game_session, (uint8_t)g_menu.selected_tribe,
                     (uint8_t)g_menu.selected_map_island)));
            if (frame >= 0 && (uint32_t)frame < g_island_main_buttons.frame_count) {
                draw_sprite(surface, &g_island_main_buttons, (uint32_t)frame,
                            button->pane.left, button->pane.top);
            }
        }
    }

    draw_hall_panel(surface, hall_player);

    /* windows.txt places IWLilMap at (192,328)-(447,359), and shapes.txt
       binds it to the 16-frame LILMAP sheet. The SHP frame is indexed by the
       selected island's existing surface id (the local 15-island corpus uses
       the corresponding first 15 frames). */
    if (g_island_surface_id >= 0 && g_island_surface_id < 16) {
        const WindowTemplate *mini_map = window_catalog_find(
            &g_window_catalog, "IWLilMap", 3);
        if (mini_map != NULL) {
            draw_sprite(surface, &g_island_lilmap_art,
                        (uint32_t)g_island_surface_id,
                        mini_map->pane.left, mini_map->pane.top);
            draw_island_lilmap_dots(surface, mini_map, runtime_island);
        }
    }

    draw_iw_construct(surface);
    if (selected_ground_item >= 0 &&
        island_panel_location_info_visible(g_island_panel_mode)) {
        const WindowTemplate *info = window_catalog_find(
            &g_window_catalog, "IWLocInfo", 3);
        if (info != NULL && g_temp_hole_art.frame_count > 1) {
            RECT pane = {info->pane.left, info->pane.top,
                         info->pane.right + 1, info->pane.bottom + 1};
            int saved_info_dc = render_surface_save(surface);
            unsigned int item_frame = (unsigned int)(selected_ground_item -
                GAME_INVENTORY_ITEM_FIRST_ID);
            render_surface_intersect_clip(surface, pane.left, pane.top,
                                          pane.right, pane.bottom);
            draw_sprite(surface, &g_temp_hole_art, 1,
                        info->pane.left, info->pane.top);
            /* FUN_00440567 sends P+4==0, P+0x10 in {0,1} sites to FUN_00441aae:
               no text and no buttons, only the TRIGGERS (alltrigs.shp) frame
               +0x24-5 centred in the pane by FUN_004119ba. FUN_0044338b is the
               unit detail renderer and is not used here. */
            if (item_frame < g_inventory_item_art.frame_count &&
                g_inventory_item_art.frames[item_frame].pixels != NULL) {
                const SpriteFrame *icon = &g_inventory_item_art.frames[item_frame];
                int icon_x = info->pane.left +
                    ((info->pane.right - info->pane.left + 1) -
                     (int)icon->width) / 2 - icon->x_offset;
                int icon_y = info->pane.top +
                    ((info->pane.bottom - info->pane.top + 1) -
                     (int)icon->height) / 2 - icon->y_offset;
                draw_sprite(surface, &g_inventory_item_art, item_frame,
                            icon_x, icon_y);
            }
            if (saved_info_dc != 0) render_surface_restore(surface, saved_info_dc);
        }
    }
    /* FUN_0042f8f7 (floater select) keeps the source building in
       IWLocInfo/IWLocControl and shows the floater in IWFltInfo, the
       456,328 pane shared with the hidden IWTextInfo. */
    if (selected_floater != NULL && selected_floater->type_index < 4 &&
        island_panel_location_info_visible(g_island_panel_mode)) {
        const WindowTemplate *info = window_catalog_find(
            &g_window_catalog, "IWFltInfo", 3);
        if (info != NULL && g_temp_hole_art.frame_count > 2) {
            RECT pane = {info->pane.left, info->pane.top,
                         info->pane.right + 1, info->pane.bottom + 1};
            int saved_info_dc = render_surface_save(surface);
            render_surface_intersect_clip(surface, pane.left, pane.top,
                                          pane.right, pane.bottom);
            draw_sprite(surface, &g_temp_hole_art, (uint32_t)info->shape_frame,
                        info->pane.left, info->pane.top);

            /* FUN_0044338b (Iwloc.cpp) draws the selected object's details in
               IWLocInfo. Initial workers are class 0, level 0, and have the
               four tribe-specific *work rows: 3 hit points and 0 strength.
               FUN_00466fe4 initializes current hits to FUN_00420f28's max. */
            if (selected_floater->source_link_0c != -1) {
                /* FUN_0044338b, linked branch (FUN_004207f2 non-null,
                   ev_347b34f6...): BLDNAME centred y=3, then LEVEL 18,
                   EXP 28, CHARGE 38, HITS 48, STRENGTH 58 at x=4. */
                static const int16_t exp_t1[18] = {
                    0, 0, 0, 25, 100, 0, 30, 120, 0, 40, -1, 0, 25, 100, 0,
                    25, 100, 0};
                static const int16_t exp_t2[18] = {
                    0, 0, 0, 75, 200, 0, 90, 240, 0, 120, -1, 0, 75, 200, 0,
                    75, 200, 0};
                const GameRuntimeLocation *linked = NULL;
                char row[48];
                int16_t current_charge = 0;
                int16_t maximum_charge = 0;
                unsigned int level = selected_floater->attack_level_flags & 0x0fU;
                int exp_cap = 0;
                int row_y = info->pane.top + 18;
                if (runtime_island != NULL &&
                    selected_floater->charge_source_island ==
                        g_menu.selected_map_island &&
                    selected_floater->charge_source_location <
                        runtime_island->location_count) {
                    linked = &runtime_island->locations[
                        selected_floater->charge_source_location];
                }
                if (linked != NULL) {
                    uint16_t catalog_item;
                    size_t name_index;
                    int owner = linked->owner_id >= 0 && linked->owner_id < 4
                        ? linked->owner_id : 0;
                    if (island_panel_info_construction_task_indices(
                            (int16_t)(linked->record_value_10 - owner * 16),
                            (uint8_t)owner, &catalog_item, &name_index) &&
                        name_index < BUILDING_NAME_COUNT &&
                        g_building_names[name_index][0] != '\0') {
                        int w = measure_bitmap_text(NULL,
                            g_building_names[name_index],
                            strlen(g_building_names[name_index]));
                        draw_bitmap_label(surface, g_building_names[name_index],
                            info->pane.left +
                                ((info->pane.right - info->pane.left + 1) - w) / 2,
                            info->pane.top + 3, RGB(230, 238, 255));
                    }
                }
                (void)snprintf(row, sizeof(row), "%s %u", g_unit_label_text[2],
                               level + 1U);
                /* FUN_0044338b draws the linked rows at x = 4 (ev_347b34f6). */
                draw_bitmap_label(surface, row, info->pane.left + 4, row_y,
                                  RGB(230, 238, 255));
                row_y += 10;
                if (level < 2 && selected_floater->source_subtype < 6) {
                    /* ((4 - D) * DAT_004a424a[i] + D * DAT_004a4282[i]) / 4
                       with D = DAT_004bf11c, the game difficulty, as in the
                       FUN_0045cd75 promotion test (ev_347b34f6, ev_aad45101). */
                    unsigned int i = level + 3U * selected_floater->source_subtype;
                    int difficulty = g_game_session.config.difficulty;
                    exp_cap = ((4 - difficulty) * exp_t1[i] +
                               difficulty * exp_t2[i]) / 4;
                }
                if (exp_cap >= 1) {
                    (void)snprintf(row, sizeof(row), "EXP %u/%d",
                        (unsigned int)selected_floater->source_progress_08,
                        exp_cap);
                } else {
                    (void)snprintf(row, sizeof(row), "EXP %u",
                        (unsigned int)selected_floater->source_progress_08);
                }
                draw_bitmap_label(surface, row, info->pane.left + 4, row_y,
                                  RGB(230, 238, 255));
                row_y += 10;
                if (game_session_floater_charge_values(selected_floater,
                        &g_floater_catalog, &current_charge, &maximum_charge)) {
                    (void)snprintf(row, sizeof(row), "%s %d/%d",
                        g_unit_label_text[5], (int)current_charge,
                        (int)maximum_charge);
                    draw_bitmap_label(surface, row, info->pane.left + 4, row_y,
                                      RGB(230, 238, 255));
                }
                row_y += 10;
                (void)snprintf(row, sizeof(row), "%s %u/%u",
                    g_unit_label_text[3],
                    (unsigned int)selected_floater->current_hit_points,
                    (unsigned int)selected_floater->max_hit_points);
                draw_bitmap_label(surface, row, info->pane.left + 4, row_y,
                                  RGB(230, 238, 255));
                row_y += 10;
                (void)snprintf(row, sizeof(row), "%s %u",
                    g_unit_label_text[4],
                    (unsigned int)selected_floater->attack_strength);
                draw_bitmap_label(surface, row, info->pane.left + 4, row_y,
                                  RGB(230, 238, 255));
            } else {
            {
                /* Name row: "%s %s" of the names.txt tribe slot and the
                   gamey.txt WORKER label (FUN_0044338b, class 0). */
                char worker_label[96];
                int label_width;
                (void)snprintf(worker_label, sizeof(worker_label), "%s %s",
                    g_tribe_names[selected_floater->type_index],
                    /* FUN_0044338b: WORKER for subtype 0, AWAKE otherwise. */
                    g_unit_label_text[selected_floater->source_subtype == 0
                                      ? 0 : 1]);
                label_width = measure_bitmap_text(NULL, worker_label,
                                                   strlen(worker_label));
                draw_bitmap_label(surface, worker_label,
                    info->pane.left +
                        ((info->pane.right - info->pane.left + 1) - label_width) / 2,
                    info->pane.top + 3, RGB(230, 238, 255));
            }
            {
                char hit_points_label[24];
                char strength_label[24];
                char charge_label[24];
                int16_t current_charge;
                int16_t maximum_charge;
                (void)snprintf(hit_points_label, sizeof(hit_points_label),
                    "%s %u/%u", g_unit_label_text[3],
                    (unsigned int)selected_floater->current_hit_points,
                    (unsigned int)selected_floater->max_hit_points);
                (void)snprintf(strength_label, sizeof(strength_label),
                    "%s %u", g_unit_label_text[4],
                    (unsigned int)selected_floater->attack_strength);
                draw_bitmap_label(surface, hit_points_label,
                                  info->pane.left + 5, info->pane.top + 23,
                                  RGB(230, 238, 255));
                draw_bitmap_label(surface, strength_label,
                                  info->pane.left + 5, info->pane.top + 33,
                                  RGB(230, 238, 255));
                /* FUN_0044338b gates CHARGE through FUN_004207f2, which
                   returns null for floater +0x0c == -1. */
                if (game_session_floater_charge_values(selected_floater,
                        &g_floater_catalog, &current_charge, &maximum_charge)) {
                    (void)snprintf(charge_label, sizeof(charge_label),
                        "%s %d/%d", g_unit_label_text[5], (int)current_charge,
                        (int)maximum_charge);
                    draw_bitmap_label(surface, charge_label,
                                      info->pane.left + 5,
                                      info->pane.top + 43,
                                      RGB(230, 238, 255));
                }
            }

            }

            /* FUN_0044338b places the selected unit sprite to the right of
               the text. The island renderer's original base-worker sheets
               supply the same body and animated legs used in the world view. */
            {
                uint32_t leg_frame = island_floater_legs_frame(selected_floater);
                int sprite_x = info->pane.right - 50;
                int sprite_y = info->pane.top +
                    (info->pane.bottom - info->pane.top) / 2 + 5;
                const SpriteSheet *body_art = island_floater_body_art(selected_floater);
                const SpriteSheet *leg_art = island_floater_legs_art(selected_floater);
                uint32_t body_frame_index =
                    island_floater_body_sprite_frame(selected_floater,
                                                     body_art);
                const SpriteFrame *body_frame = body_art->frame_count != 0
                    ? &body_art->frames[body_frame_index] : NULL;
                /* FUN_0042704b draws the carried item first, behind the body
                   and legs, at the fltinf graspxy anchor, never as a separate
                   CARRY text row. */
                /* FUN_0044338b passes a 0x4c-byte copy with param_5 = 1, so
                   a crossing floater rises and fades inside the panel
                   surface too, unflipped. */
                {
                    GameFloaterStart drawn = *selected_floater;
                    int stipple_level;
                    int lift = island_floater_bridge_lift(selected_floater,
                                                          &stipple_level);
                    const SpriteSheet *drawn_body = body_art;
                    const SpriteSheet *drawn_legs = leg_art;
                    if (stipple_level < 8) {
                        drawn.facing_left = 0;
                        drawn_body = island_floater_body_art(&drawn);
                        drawn_legs = island_floater_legs_art(&drawn);
                    }
                    if (render_surface_save(surface) != 0) {
                        render_surface_intersect_clip(surface, info->pane.left,
                                                      info->pane.top,
                                                      info->pane.right,
                                                      info->pane.bottom);
                        draw_island_floater_cargo(surface, &drawn, sprite_x,
                                                  sprite_y - lift,
                                                  stipple_level);
                        if (drawn_body->frame_count != 0)
                            draw_island_floater_layer(surface, drawn_body,
                                body_frame_index, sprite_x, sprite_y - lift,
                                0x10000U, stipple_level);
                        if (drawn_legs->frame_count != 0)
                            draw_island_floater_layer(surface, drawn_legs,
                                leg_frame, sprite_x, sprite_y - lift,
                                0x10000U, stipple_level);
                        render_surface_restore(surface, -1);
                    }
                    sprite_y -= lift;
                }
                /* FUN_0044338b enables the info flags around this sprite.
                   FUN_0042003c maps the floater's fltinf row realm to
                   frames 22..25, shifted by its linked source site flags. */
                if (g_floater_info_art.frame_count >= 26 && body_frame != NULL) {
                    uint32_t realm_frame;
                    int32_t badge_x;
                    int32_t badge_y;
                    int32_t body_left = sprite_x + body_frame->x_offset +
                                        body_frame->hit_left;
                    int32_t body_top = sprite_y + body_frame->y_offset +
                                       body_frame->hit_top;
                    int32_t body_right = sprite_x + body_frame->x_offset +
                                         body_frame->hit_right;
                    if (island_worker_realm_badge_layout(
                            (uint8_t)game_session_floater_realm(
                                &g_game_session, selected_floater),
                            0, 0, selected_floater->facing_left,
                            body_left, body_top, body_right,
                            &realm_frame, &badge_x, &badge_y) &&
                        realm_frame < g_floater_info_art.frame_count) {
                        draw_sprite(surface, &g_floater_info_art, realm_frame,
                                    badge_x, badge_y);
                    }
                }
                /* Combat-stat frame and anchor are independently derived from
                   FUN_0042704b / FUN_00420f28. Ascended Ones have no body
                   frame to anchor it, as in the world-view badge path. */
                if (g_floater_info_art.frame_count >= 26 && body_frame != NULL) {
                    uint32_t stat_frame;
                    int32_t badge_x;
                    int32_t badge_y;
                    int32_t body_left = sprite_x + body_frame->x_offset +
                                        body_frame->hit_left;
                    int32_t body_top = sprite_y + body_frame->y_offset +
                                       body_frame->hit_top;
                    int32_t body_right = sprite_x + body_frame->x_offset +
                                         body_frame->hit_right;
                    if (island_worker_stat_badge_layout(
                            selected_floater->source_subtype,
                            island_floater_health_stat(selected_floater),
                            selected_floater->facing_left,
                            body_left, body_top, body_right,
                            &stat_frame, &badge_x, &badge_y) &&
                        stat_frame < g_floater_info_art.frame_count) {
                        draw_sprite(surface, &g_floater_info_art, stat_frame,
                                    badge_x, badge_y);
                    }
                }
            }
            if (saved_info_dc != 0) render_surface_restore(surface, saved_info_dc);
        }
    } else if (selected_floater != NULL && selected_floater->owner_slot == 4U &&
               game_session_floater_is_active(selected_floater) &&
               selected_floater->source_subtype >= 9U &&
               selected_floater->source_subtype <= 17U &&
               island_panel_location_info_visible(g_island_panel_mode)) {
        const WindowTemplate *info = window_catalog_find(
            &g_window_catalog, "IWFltInfo", 3);
        if (info != NULL && g_temp_hole_art.frame_count > 2) {
            RECT pane = {info->pane.left, info->pane.top,
                         info->pane.right + 1, info->pane.bottom + 1};
            int saved_info_dc = render_surface_save(surface);
            unsigned int level = selected_floater->attack_level_flags & 0x0fU;
            char name_label[24];
            char row_label[32];
            int label_width;
            int row_y;
            render_surface_intersect_clip(surface, pane.left, pane.top,
                                          pane.right, pane.bottom);
            draw_sprite(surface, &g_temp_hole_art, (uint32_t)info->shape_frame,
                        info->pane.left, info->pane.top);

            /* FUN_0044338b, category-4 (Leviathan) unit branch (Evidence
               ev_5f9c5a49...): FUN_004207f2 is null, so the building rows are
               skipped. A centred name row at y=3 comes from the xSpores table
               index (level + (subtype - 9) * 2), then LEVEL (level + 1),
               HITS cur/max, STRENGTH at x=4 and the monster sprite at
               (W-50, H/2+5). The table strings keep their source "x" prefix. */
            (void)snprintf(name_label, sizeof(name_label), "%s",
                island_leviathan_info_name(selected_floater->source_subtype,
                                           level));
            label_width = measure_bitmap_text(NULL, name_label,
                                              strlen(name_label));
            draw_bitmap_label(surface, name_label,
                info->pane.left +
                    ((info->pane.right - info->pane.left + 1) - label_width) / 2,
                info->pane.top + 3, RGB(230, 238, 255));
            row_y = info->pane.top + 23;
            (void)snprintf(row_label, sizeof(row_label), "%s %u", g_unit_label_text[2],
                           level + 1U);
            draw_bitmap_label(surface, row_label, info->pane.left + 5, row_y,
                              RGB(230, 238, 255));
            row_y += 10;
            (void)snprintf(row_label, sizeof(row_label), "%s %d/%d",
                g_unit_label_text[3],
                selected_floater->current_hit_points < 0
                    ? 0 : (int)selected_floater->current_hit_points,
                (int)selected_floater->max_hit_points);
            draw_bitmap_label(surface, row_label, info->pane.left + 5, row_y,
                              RGB(230, 238, 255));
            row_y += 10;
            (void)snprintf(row_label, sizeof(row_label), "%s %u",
                g_unit_label_text[4],
                (unsigned int)selected_floater->attack_strength);
            draw_bitmap_label(surface, row_label, info->pane.left + 5, row_y,
                              RGB(230, 238, 255));
            draw_island_leviathan_floater(surface, selected_floater,
                info->pane.right - 50,
                info->pane.top + (info->pane.bottom - info->pane.top) / 2 + 5);
            if (saved_info_dc != 0) render_surface_restore(surface, saved_info_dc);
        }
    }
    if (!(selected_ground_item >= 0 &&
          island_panel_location_info_visible(g_island_panel_mode)) &&
        island_panel_location_info_visible(g_island_panel_mode) &&
        effective_info_location(&info_island, &info_location,
                                &info_island_index)) {
        const GameRuntimeLocation *selected_location =
            &info_island->locations[info_location];
        int32_t raw_item_id = selected_location->record_value_10;
        /* FUN_00440567 paints any kind-0 site with item >= 2 (Evidence
           ev_cb0962ae...); owner-4 sites draw only the building sprite there.
           Hall/task blocks are skipped (+0x18 == -1, no owner HITS gauge). */
        int leviathan_building = selected_location->owner_id == 4 &&
            selected_location->renderer_class == 0 && raw_item_id >= 5;
        if ((raw_item_id >= 0x25 || leviathan_building) &&
            raw_item_id < g_pad_catalog.item_count) {
            const WindowTemplate *info = window_catalog_find(
                &g_window_catalog, "IWLocInfo", 3);
            if (info != NULL && g_temp_hole_art.frame_count > 1) {
                RECT pane = {info->pane.left, info->pane.top,
                             info->pane.right + 1, info->pane.bottom + 1};
                int saved_info_dc = render_surface_save(surface);
                render_surface_intersect_clip(surface, pane.left, pane.top,
                                              pane.right, pane.bottom);
                draw_sprite(surface, &g_temp_hole_art, 1,
                            info->pane.left, info->pane.top);
                /* The source paints the selected building in IWLocInfo via
                   FUN_0042704b. Reuse the same data-driven BASE/CHUG/etc.
                   layers already used by the island renderer. */
                {
                    int sprite_x;
                    int sprite_y;
                    if (island_panel_info_building_sprite_position(
                            info, &sprite_x, &sprite_y)) {
                        /* FUN_00440567 shifts training halls right by level
                           (location +0x4a) to leave room for the staff. */
                        sprite_x += island_panel_info_training_hall_x_shift(
                            location_base_item_id(selected_location),
                            selected_location->source_capacity_4a);
                        /* FUN_0044338b passes full scale (0x10000) and a
                           pane-relative width/height anchor to FUN_0042704b. */
                        (void)draw_runtime_item_scaled(surface, selected_location,
                            sprite_x, sprite_y, 0x10000U);
                    }
                }
                draw_building_info_extras(surface, info, selected_location,
                    info_island_index, (uint16_t)info_location);
                draw_building_slot_floaters(surface, info, selected_location);
                if (saved_info_dc != 0) render_surface_restore(surface, saved_info_dc);
            }
        }
    }
    /* FUN_00440567 sends non-building sites (class != 0) to FUN_00441b36
       (ev_ef973ec0): a gamey.txt caption centred at ((W - w) / 2, H / 2 - 10).
       Class 1: owner 4 -> INFECT (item 5) or BEASTI, else PRIMED / UNPRIM by
       the viewer's bit of +0x22; class 2 CBRIDGE; class 3 MYSTLOC. */
    if (!(selected_ground_item >= 0 &&
          island_panel_location_info_visible(g_island_panel_mode)) &&
        island_panel_location_info_visible(g_island_panel_mode) &&
        effective_info_location(&info_island, &info_location,
                                &info_island_index) &&
        info_island->locations[info_location].renderer_class != 0) {
        const GameRuntimeLocation *site = &info_island->locations[info_location];
        const WindowTemplate *info = window_catalog_find(
            &g_window_catalog, "IWLocInfo", 3);
        const char *caption = NULL;
        if (site->renderer_class == 1) {
            if (site->owner_id == 4)
                caption = g_site_class_label_text[
                    site->record_value_10 == 5 ? 0 : 1];
            else if (g_menu.selected_tribe >= 0 && g_menu.selected_tribe < 8)
                caption = g_site_class_label_text[
                    (site->source_value_22 >> g_menu.selected_tribe) & 1U ? 2 : 3];
        } else if (site->renderer_class == 2) {
            caption = g_site_class_label_text[4];
        } else if (site->renderer_class == 3) {
            caption = g_site_class_label_text[5];
        }
        if (info != NULL && caption != NULL && caption[0] != 0) {
            /* FUN_00441b36 draws the caption with BIGFONT (ECX = 0x5c2870 at
               0x441ca0, ev_1202ec55) in the font's current colour, the panel
               default index 6. */
            int use_big = g_big_font.bytes != NULL;
            int width = use_big ? measure_big_text(caption, strlen(caption))
                                : measure_bitmap_text(NULL, caption, strlen(caption));
            int x = info->pane.left +
                ((info->pane.right - info->pane.left) - width) / 2;
            int y = info->pane.top +
                (info->pane.bottom - info->pane.top) / 2 - 10;
            if (g_temp_hole_art.frame_count > 1)
                draw_sprite(surface, &g_temp_hole_art, 1,
                            info->pane.left, info->pane.top);
            if (use_big)
                draw_big_label(surface, caption, x, y,
                               native_text_color(g_island_palette, 6));
            else
                draw_bitmap_label(surface, caption, x, y, RGB(230, 238, 255));
        }
    }
    /* IWLocInfo's selected-building painter clears and redraws this pane, so
       render the Hall's economy view after it. */
    if (island_panel_location_info_visible(g_island_panel_mode)) {
        draw_hall_stock_summary(surface, hall_player, runtime_island);
    }

    /* The Hall summary's worker is not a real unit: FUN_00440567
       (0x4412e4..0x44138c) builds a stack floater with FUN_0041e4e4 (state 0,
       no cargo, flags 0), sets class = Hall owner and subtype 0 (worker), then
       draws it with FUN_0042704b at pane (200, FUN_00426fd0 bob + 0x11, -3 more
       for active tribe 3) with the three overlay globals cleared. The phase
       byte +0x14 is left unset by the constructor; the port uses 0. */
    {
        int player = selected_hall_player();
        if (player >= 0 && player < 4 &&
            island_panel_location_info_visible(g_island_panel_mode)) {
            const WindowTemplate *info = window_catalog_find(
                &g_window_catalog, "IWLocInfo", 3);
            if (info != NULL) {
                const SpriteSheet *body_art = &g_initial_floater_bodies[player];
                const SpriteSheet *leg_art = &g_initial_floater_legs[player];
                RECT pane = {info->pane.left, info->pane.top,
                             info->pane.right + 1, info->pane.bottom + 1};
                int saved_worker_dc = render_surface_save(surface);
                int x = info->pane.left + 200;
                int y = info->pane.top + 0x11 +
                    island_worker_hover_bob(g_menu.animation_ticks, 0);
                uint32_t body_frame;
                uint32_t leg_frame = island_worker_legs_frame(
                    (uint8_t)player, 0, g_menu.animation_ticks);
                if (ui_art_tribe() == 3) y -= 3;
                render_surface_intersect_clip(surface, pane.left, pane.top,
                                              pane.right, pane.bottom);
                if (body_art->frame_count != 0 &&
                    island_floater_body_frame((uint8_t)player, 0, 0,
                                              &body_frame) &&
                    body_frame < body_art->frame_count)
                    draw_sprite(surface, body_art, body_frame, x, y);
                if (leg_art->frame_count != 0 &&
                    leg_frame < leg_art->frame_count)
                    draw_sprite(surface, leg_art, leg_frame, x, y);
                if (saved_worker_dc != 0) render_surface_restore(surface, saved_worker_dc);
            }
        }
    }
    /* IWLocInfo includes these controls in its pane. Draw them after the
       Hall stock summary, which repaints that pane's background. */
    if (hall_player >= 0 && g_hall_stock_art.frame_count >= 5 &&
        island_panel_location_info_visible(g_island_panel_mode)) {
        static const char *const stock_control_names[GAME_RESOURCE_TYPE_COUNT] = {
            "BC_HallStkB", "BC_HallStkC", "BC_HallStkM"
        };
        unsigned int resource;
        for (resource = 0; resource < GAME_RESOURCE_TYPE_COUNT; ++resource) {
            const WindowTemplate *button = window_catalog_find(
                &g_window_catalog, stock_control_names[resource], 3);
            uint32_t frame;
            if (button == NULL) continue;
            /* THBUTT frames 1/2/3 are fill arrow, empty arrow, roof (help
               text order); stock modes are 0 = Hall serves as source (empty),
               1 = keep stocked (roof), 2 = request (fill). */
            frame = (uint32_t)button->shape_frame +
                (g_game_session.economy[hall_player].stock_mode[resource] +
                 1U) % 3U;
            if (frame < g_hall_stock_art.frame_count) {
                draw_sprite(surface, &g_hall_stock_art, frame,
                            button->pane.left, button->pane.top);
            }
            /* The highlight is a transparent overlay; keep the active stock
               mode icon visible underneath it while hovering. */
            if ((int)resource == g_hovered_hall_stock &&
                button->has_hilite_frame && button->hilite_frame >= 0 &&
                (uint32_t)button->hilite_frame < g_hall_stock_art.frame_count) {
                draw_sprite(surface, &g_hall_stock_art,
                            (uint32_t)button->hilite_frame,
                            button->pane.left, button->pane.top);
            }
        }
    }
    draw_clipboard_strip(surface);
    draw_location_action_panel(surface);
    draw_control_hover_caption(surface);

    /* IWLocControl's backdrop overlaps the Hall command buttons. Draw the
       THALL button frames last so the selected Hall's five commands remain
       visible above that panel. */
    if (hall_player >= 0 &&
        island_panel_location_control_visible(g_island_panel_mode)) {
        static const char *const command_names[] = {
            "BC_GenInfo", "BC_Storage", "BC_Knowledge",
            "BC_Diplomacy", "BC_Trade"
        };
        size_t command_index;
        for (command_index = 0;
             command_index < sizeof(command_names) / sizeof(command_names[0]);
             ++command_index) {
            const WindowTemplate *button = window_catalog_find(
                &g_window_catalog, command_names[command_index], 3);
            int frame;
            if (button == NULL) continue;
            frame = window_catalog_control_frame(button,
                window_catalog_hall_panel_mode(button->name) ==
                    g_hovered_hall_command);
            if (frame >= 0 && (uint32_t)frame < g_hall_command_art.frame_count) {
                draw_sprite(surface, &g_hall_command_art, (uint32_t)frame,
                            button->pane.left, button->pane.top);
            }
        }
    }
    roll_cryptic_message();
    draw_island_message(surface);
}

/* CLIPSEL1-3 / CLIPBD1-3 are not among the 16 windows FUN_0042f303 hides, so
   the shortcut strip shows in every panel mode and whatever is selected. */
static void draw_clipboard_strip(RenderSurface *surface)
{
    if (g_game_session_valid && g_menu.selected_tribe >= 0 &&
        g_menu.selected_tribe < GAME_START_PLAYER_COUNT &&
        ensure_clipboard_art()) {
        static const char *const tabs[3] = {"CLIPSEL1", "CLIPSEL2", "CLIPSEL3"};
        static const char *const slots[3] = {"CLIPBD1", "CLIPBD2", "CLIPBD3"};
        unsigned int index;
        /* FUN_0042f755 -> FUN_00438120: each selection refresh remembers the
           selected training building in the active group. */
        game_session_clip_auto_register(&g_game_session,
                                        (uint8_t)g_menu.selected_tribe);
        if (g_selected_location >= 0 && selection_island() >= 0)
            game_session_clip_remember(&g_game_session,
                (uint8_t)g_menu.selected_tribe,
                (uint8_t)selection_island(),
                (uint16_t)g_selected_location);
        for (index = 0; index < 3U; ++index) {
            const WindowTemplate *tab = window_catalog_find(&g_window_catalog, tabs[index], 3);
            const WindowTemplate *slot = window_catalog_find(&g_window_catalog, slots[index], 3);
            uint8_t clip_island = 0;
            uint16_t clip_location = 0;
            unsigned int dots;
            if (tab != NULL && tab->shape_frame >= 0) {
                /* CLIP frames: 4 per group; +2 marks the active group. */
                uint32_t frame = (uint32_t)tab->shape_frame +
                    (g_game_session.clip_group == index ? 2U : 0U);
                if (frame < g_clip_art.frame_count)
                    draw_sprite(surface, &g_clip_art, frame, tab->pane.left, tab->pane.top);
            }
            if (slot == NULL) continue;
            if (slot->shape_frame >= 0 &&
                (uint32_t)slot->shape_frame < g_temp_hole_art.frame_count)
                draw_sprite(surface, &g_temp_hole_art, (uint32_t)slot->shape_frame,
                            slot->pane.left, slot->pane.top);
            dots = game_session_clip_slot(&g_game_session,
                (uint8_t)g_menu.selected_tribe, index, &clip_island, &clip_location);
            if (dots != 0) {
                /* FUN_004391ab (ev_ee7544ff): the building through FUN_0040bf98
                   at (12, 30) with flags 0x6000, then bildicon dots: count =
                   the 0-based instance number +0x60 (FUN_0045ee26, ev_a4a51711),
                   step 5, five per row from (1, 1), frame = clamp(owner, 0..3). */
                const GameRuntimeLocation *building =
                    &g_game_session.islands[clip_island].locations[clip_location];
                uint32_t frame = (uint32_t)(building->owner_id < 0 ? 0
                    : building->owner_id > 3 ? 3 : building->owner_id);
                unsigned int dot;
                (void)draw_runtime_item_scaled(surface, building,
                    slot->pane.left + 12, slot->pane.top + 30, 0x6000U);
                for (dot = 0; dot + 1U < dots && dot < 10U; ++dot) {
                    if (frame < g_bildicon_art.frame_count)
                        draw_sprite(surface, &g_bildicon_art, frame,
                            slot->pane.left + 1 + (int)(dot % 5U) * 5,
                            slot->pane.top + 1 + (int)(dot / 5U) * 5);
                }
            }
        }
    }
}

static void draw_location_action_panel(RenderSurface *surface)
{
    const GameRuntimeIsland *island;
    const WindowTemplate *panel;
    const WindowTemplate *button;
    const WindowTemplate *text_panel;
    const WindowTemplate *repair_button;
    IslandLocationActionControl action;
    const char *button_name;
    const GameRuntimeLocation *selected_location;

    /* IWLocControl overlaps IWConstructInfo in windows.txt. Keep the selected
       construction item's pane visible while the modal build window is open. */
    if (!island_panel_location_control_visible(g_island_panel_mode) ||
        !iw_construct_location_control_pane_visible(g_iw_construct_open) ||
        !g_game_session_valid || g_menu.screen != SCREEN_ISLAND ||
        selection_island() < 0 ||
        selection_island() >= g_game_session.island_count ||
        g_selected_location < 0) return;
    island = &g_game_session.islands[selection_island()];
    if (g_selected_location >= island->location_count) return;
    selected_location = &island->locations[g_selected_location];
    panel = window_catalog_find(&g_window_catalog, "IWLocControl", 3);
    if (panel != NULL && panel->shape_frame >= 0 &&
        (uint32_t)panel->shape_frame < g_temp_hole_art.frame_count) {
        draw_sprite(surface, &g_temp_hole_art, (uint32_t)panel->shape_frame,
                    panel->pane.left, panel->pane.top);
    }

    /* IWTextInfo is the selected-location description pane. The source UI
       fills it for a selected building; the remake previously left it empty
       unless a move control was hovered. */
    if (island_floater_info_shown()) {
        /* IWTextInfo is hidden; the floater panel owns this pane. */
    } else if (g_island_panel_mode == WINDOW_ISLAND_PANEL_GENERAL &&
               selected_location->renderer_class == 0 &&
               selected_location->record_value_10 == 0x2a &&
               selected_location->owner_id >= 0 &&
               selected_location->owner_id < 4 &&
               selected_location->owner_id != g_menu.selected_tribe &&
               g_newgame_text[selected_location->owner_id][0] != '\0') {
        /* FUN_00439673 mode 0 (ev_20a8dd58): another tribe's Hall (item 0x2a,
           +0x14 != DAT_0049f538) shows NEWGAME<owner>, the tribe name, centred
           like LEVNAME. */
        const char *tribe_name = g_newgame_text[selected_location->owner_id];
        text_panel = window_catalog_find(&g_window_catalog, "IWTextInfo", 3);
        if (text_panel != NULL && text_panel->shape_frame >= 0 &&
            (uint32_t)text_panel->shape_frame < g_temp_hole_art.frame_count) {
            int pane_width = text_panel->pane.right - text_panel->pane.left;
            int pane_height = text_panel->pane.bottom - text_panel->pane.top;
            int name_width = measure_bitmap_text(NULL, tribe_name,
                                                 strlen(tribe_name));
            draw_sprite(surface, &g_temp_hole_art,
                        (uint32_t)text_panel->shape_frame,
                        text_panel->pane.left, text_panel->pane.top);
            draw_bitmap_label(surface, tribe_name,
                text_panel->pane.left + (pane_width - name_width) / 2,
                text_panel->pane.top + pane_height / 2 - 10,
                RGB(230, 238, 255));
        }
    } else if (g_island_panel_mode == WINDOW_ISLAND_PANEL_GENERAL &&
        selected_location->record_value_10 >= 0x25 &&
        selected_location->record_value_10 < PAD_CATALOG_MAX_ITEMS &&
        g_building_descriptions[selected_location->record_value_10][0] != '\0') {
        text_panel = window_catalog_find(&g_window_catalog, "IWTextInfo", 3);
        if (text_panel != NULL && text_panel->shape_frame >= 0 &&
            (uint32_t)text_panel->shape_frame < g_temp_hole_art.frame_count) {
            draw_sprite(surface, &g_temp_hole_art,
                        (uint32_t)text_panel->shape_frame,
                        text_panel->pane.left, text_panel->pane.top);
            /* Same FUN_00439673 SMFONT wrap as the Hall info text. */
            draw_iw_text_info_text(surface, text_panel,
                g_building_descriptions[selected_location->record_value_10]);
        }
    } else if (g_island_panel_mode == WINDOW_ISLAND_PANEL_GENERAL &&
               selected_location->owner_id == 4 &&
               selected_location->renderer_class == 0 &&
               selected_location->record_value_10 >= 5 &&
               selected_location->record_value_10 - 5 < LEVIATHAN_NAME_COUNT &&
               g_leviathan_names[selected_location->record_value_10 - 5][0] != '\0') {
        /* FUN_00439673 mode 0: pad items have no description key for owner 4,
           so the LEVNAME entry (item - 5) is centred at y = H/2 - 10. */
        const char *level_name =
            g_leviathan_names[selected_location->record_value_10 - 5];
        text_panel = window_catalog_find(&g_window_catalog, "IWTextInfo", 3);
        if (text_panel != NULL && text_panel->shape_frame >= 0 &&
            (uint32_t)text_panel->shape_frame < g_temp_hole_art.frame_count) {
            int pane_width = text_panel->pane.right - text_panel->pane.left;
            int pane_height = text_panel->pane.bottom - text_panel->pane.top;
            int name_width = measure_bitmap_text(NULL, level_name,
                                                 strlen(level_name));
            draw_sprite(surface, &g_temp_hole_art,
                        (uint32_t)text_panel->shape_frame,
                        text_panel->pane.left, text_panel->pane.top);
            draw_bitmap_label(surface, level_name,
                text_panel->pane.left + (pane_width - name_width) / 2,
                text_panel->pane.top + pane_height / 2 - 10,
                RGB(230, 238, 255));
        }
    } else if (g_island_panel_mode == WINDOW_ISLAND_PANEL_GENERAL &&
               island_site_info_text(selected_location,
                                     g_menu.selected_tribe) != NULL) {
        text_panel = window_catalog_find(&g_window_catalog, "IWTextInfo", 3);
        if (text_panel != NULL && text_panel->shape_frame >= 0 &&
            (uint32_t)text_panel->shape_frame < g_temp_hole_art.frame_count) {
            draw_sprite(surface, &g_temp_hole_art,
                        (uint32_t)text_panel->shape_frame,
                        text_panel->pane.left, text_panel->pane.top);
            draw_iw_text_info_text(surface, text_panel,
                island_site_info_text(selected_location,
                                      g_menu.selected_tribe));
        }
    }

    action = selected_location_action();
    if (g_island_panel_mode == WINDOW_ISLAND_PANEL_GENERAL) {
        const WindowTemplate *onoff_button = window_catalog_find(
            &g_window_catalog, "BC_OnOff", 3);
        const WindowTemplate *upgrade_button = window_catalog_find(
            &g_window_catalog, "BC_Upgrade", 3);
        repair_button = window_catalog_find(&g_window_catalog, "BC_Repair", 3);
        /* Keep normal artwork as the first layer: the source highlight frames
           extend the art but are not substitutes for the button itself. */
        if (selected_onoff_button_visible() && onoff_button != NULL) {
            /* NSTATES 2: BLDCMD frames 19/20 are the two switch positions
               (interpretation: 19 = enabled, matching the default 0x400 bit
               and the descriptor's frame); the hover overlay (21) is shared. */
            WindowTemplate onoff_state;
            (void)window_catalog_onoff_state_control(onoff_button,
                (island->locations[g_selected_location].source_flags &
                 0x400U) != 0, &onoff_state);
            draw_control_with_hover_overlay(surface, &onoff_state,
                &g_building_command_art, g_hovered_onoff_control);
        }
        if (selected_upgrade_button_visible()) {
            draw_control_with_hover_overlay(surface, upgrade_button,
                &g_upgrade_button_art, g_hovered_upgrade_control);
        }
        if (selected_repair_button_visible()) {
            draw_control_with_hover_overlay(surface, repair_button,
                &g_repair_button_art, g_hovered_repair_control);
        }
    }
    /* The grab/place flow starts from the native IWMove / IWHallMove control
       (THBUTT frame 5, drawn with the other location controls); only the
       placement hint remains here while a building is held. */
    if (panel != NULL && g_game_session.location_move_active) {
        draw_bitmap_label(surface, "Click a free site to place",
            panel->pane.left + 8, panel->pane.top + 5, RGB(230, 238, 255));
    }
    if (obtain_button_visible()) {
        const WindowTemplate *obtain_control = window_catalog_find(
            &g_window_catalog, "BC_Obtain", 3);
        if (obtain_control != NULL) {
            draw_control_with_hover_overlay(surface, obtain_control,
                &g_building_command_art, g_hovered_location_grab);
        }
    }
    if (g_hall_stock_art.frame_count >= 5 && g_selected_location >= 0 &&
        g_menu.selected_tribe >= 0 && selection_island() >= 0) {
        static const char *const names[2] = {"BC_TrnStkC", "BC_TrnStkM"};
        unsigned int index;
        for (index = 0; index < 2U; ++index) {
            const WindowTemplate *control = window_catalog_find(
                &g_window_catalog, names[index], 3);
            uint32_t frame;
            if (control == NULL || !game_session_training_stock_visible(
                    &g_game_session, (uint8_t)g_menu.selected_tribe,
                    (uint8_t)selection_island(),
                    (uint16_t)g_selected_location, (int)index)) continue;
            /* NSTATES 2: frame = SHAPEFRAME + state; the state is the
               building's +0x58 / +0x5c flag (FUN_004421f1). FUN_0042a55d
               draws the frame and the highlight into the pane-sized control
               surface at the PANE extras (+0x6c/+0x6e; TrnStkC "-4 0"). */
            const int draw_x = control->pane.left +
                (control->has_pane_extras ? control->pane_extras[0] : 0);
            const int draw_y = control->pane.top +
                (control->has_pane_extras ? control->pane_extras[1] : 0);
            const int saved_dc = render_surface_save(surface);
            render_surface_intersect_clip(surface, control->pane.left, control->pane.top,
                                          control->pane.right, control->pane.bottom);
            frame = (uint32_t)control->shape_frame +
                (uint32_t)game_session_training_stock_state(&g_game_session,
                    (uint8_t)selection_island(),
                    (uint16_t)g_selected_location, (int)index);
            if (frame < g_hall_stock_art.frame_count)
                draw_sprite(surface, &g_hall_stock_art, frame, draw_x, draw_y);
            if (g_hovered_training_stock == (int)index + 1 &&
                control->has_hilite_frame && control->hilite_frame >= 0 &&
                (uint32_t)control->hilite_frame < g_hall_stock_art.frame_count)
                draw_sprite(surface, &g_hall_stock_art,
                            (uint32_t)control->hilite_frame, draw_x, draw_y);
            if (saved_dc != 0) render_surface_restore(surface, saved_dc);
        }
    }
    if (g_game_session_valid && g_menu.selected_tribe >= 0 &&
        g_menu.selected_tribe < GAME_START_PLAYER_COUNT &&
        selection_island() >= 0 && g_selected_location >= 0 &&
        game_session_upgspread_available(&g_game_session,
            (uint8_t)g_menu.selected_tribe, (uint8_t)selection_island(),
            (uint16_t)g_selected_location) &&
        g_upgrade_button_art.frame_count > 13) {
        const WindowTemplate *control = window_catalog_find(
            &g_window_catalog, "BC_UpgSpread", 3);
        if (control != NULL) {
            /* NSTATES 13: the active entry cycles the 13 frames
               (FUN_00442a7b animation counter); HILITEFRAME 13 on hover. */
            int active = game_session_upgspread_active(&g_game_session,
                (uint8_t)g_menu.selected_tribe,
                (uint8_t)selection_island(),
                (uint16_t)g_selected_location);
            uint32_t frame = (uint32_t)control->shape_frame +
                (active ? (uint32_t)((platform_ticks_ms() / 100U) % 13U) : 0U);
            draw_sprite(surface, &g_upgrade_button_art, frame,
                        control->pane.left, control->pane.top);
            if (g_hovered_upgspread)
                draw_sprite(surface, &g_upgrade_button_art, 13,
                            control->pane.left, control->pane.top);
        }
    }
    {
        /* FUN_0042f755 sends each BC_Spell button message 0xc with frame
           FUN_00450070(site, 0x15 + n) * 2 on its own SPELLBUT shape; the
           hover overlay is the next frame. The armed spell keeps its overlay
           while its target is picked. */
        const GameRuntimeLocation *spell_hall = selected_spell_hall();
        unsigned int spell_index;
        for (spell_index = 0; spell_hall != NULL && spell_index < 8U;
             ++spell_index) {
            int kind = game_session_cast_kind_for_action(
                (uint8_t)spell_hall->source_value_14,
                (uint8_t)(0x15U + spell_index));
            const WindowTemplate *spell_button = window_catalog_find(
                &g_window_catalog, k_spell_button_names[spell_index], 3);
            WindowTemplate spell_state;
            if (kind < 0 || spell_button == NULL) continue;
            spell_state = *spell_button;
            spell_state.shape_frame = kind * 2;
            draw_control_with_hover_overlay(surface, &spell_state,
                &g_spell_button_art,
                g_hovered_spell_kind == kind ||
                g_armed_spell_action == (int)(0x15U + spell_index));
        }
    }
    if (defend_area_button_visible() && ensure_trainb_art()) {
        unsigned int index;
        for (index = 0; index < 5U; ++index) {
            const WindowTemplate *control = window_catalog_find(
                &g_window_catalog, k_building_order_buttons[index], 3);
            int genre = (int)(6U + index);
            if (control != NULL)
                draw_control_with_hover_overlay(surface, control, &g_trainb_art,
                    g_hovered_defend_area == genre ||
                    g_defend_area_armed == genre);
        }
    }
    button_name = action == ISLAND_LOCATION_ACTION_HALL_MOVE
        ? "IWHallMove" : action == ISLAND_LOCATION_ACTION_MOVE
        ? "IWMove" : NULL;
    if (button_name == NULL) return;
    button = window_catalog_find(&g_window_catalog, button_name, 3);
    if (button != NULL && button->shape_frame >= 0 &&
        (uint32_t)button->shape_frame < g_hall_stock_art.frame_count) {
        /* windows.txt binds both move controls to THBUTT frame 5. */
        draw_sprite(surface, &g_hall_stock_art, (uint32_t)button->shape_frame,
                    button->pane.left, button->pane.top);
    }
    /* The hovered move control's BC1 caption is drawn by
       draw_control_hover_caption. */
}

/* The x87 helpers called by FUN_00471536 continue past Ghidra's short
   function boundaries: static disassembly shows FCOS at 0x477ad2 and FSIN at
   0x477332. The constructor supplies the two scale factors used here. */
