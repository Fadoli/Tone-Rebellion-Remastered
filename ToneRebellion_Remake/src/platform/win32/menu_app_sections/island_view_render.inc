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

static void draw_island_access_notice(HDC dc)
{
    char label[96];
    const char *island_name;
    int level = g_island_access_notice_level;
    if (g_menu.animation_ticks < g_building_destroyed_notice_until) {
        (void)snprintf(label, sizeof(label), "BATIMENT DETRUIT");
    } else {
        if (level < 0 || level >= ISLAND_NAME_COUNT ||
            g_menu.animation_ticks >= g_island_access_notice_until) return;
        island_name = g_island_names[level][0] != '\0'
            ? g_island_names[level] : "?";
        /* The bundled bitmap font is byte-oriented; keep this caption ASCII. */
        (void)snprintf(label, sizeof(label), "ACCES OUVERT : %.32s", island_name);
    }
    fill_rect(dc, 176, 10, 464, 34, RGB(20, 30, 35));
    fill_rect(dc, 178, 12, 462, 32, RGB(47, 77, 75));
    draw_bitmap_label(dc, label, 188, 18, RGB(238, 226, 177));
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
static void draw_island_floater_overlays(HDC dc, const GameFloaterStart *floater,
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
    if (g_floater_info_art.frame_count < 26 || body_art == NULL ||
        body_frame_index >= body_art->frame_count) return;
    body_frame = &body_art->frames[body_frame_index];
    body_left = x + body_frame->x_offset + body_frame->hit_left;
    body_top = y + body_frame->y_offset + body_frame->hit_top;
    body_right = x + body_frame->x_offset + body_frame->hit_right;
    if (island_worker_realm_overlay_enabled(g_floater_overlay_flags, 1) &&
        island_worker_realm_badge_layout(
            floater->type_index, 0, 0, floater->facing_left,
            body_left, body_top, body_right, &frame, &badge_x, &badge_y) &&
        frame < g_floater_info_art.frame_count) {
        draw_sprite(dc, &g_floater_info_art, frame, badge_x, badge_y);
    }
    /* Initial workers are created with +0x1c cleared by
       FUN_00466fe4/FUN_0041e4e4, so their world badge is eligible. */
    if (island_worker_health_overlay_enabled(g_floater_overlay_flags, 1) &&
        island_worker_stat_badge_layout(
            floater->type_index, island_floater_health_stat(floater),
            floater->facing_left, body_left, body_top, body_right,
            &frame, &badge_x, &badge_y) &&
        frame < g_floater_info_art.frame_count) {
        draw_sprite(dc, &g_floater_info_art, frame, badge_x, badge_y);
    }
}

static void draw_island_leviathan_floater(HDC dc,
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
    draw_sprite(dc, leg_art, leg_frame, x, y);
    if (floater->source_subtype == 9U) return;
    body_art = floater->facing_left
        ? &g_leviathan_body_art_flipped : &g_leviathan_body_art;
    if (body_art->frame_count >= 16U) {
        uint32_t body_frame = 2U * (floater->source_subtype - 10U) +
            (((g_game_session.simulation_tick + floater->animation_seed) / 8U) & 1U);
        draw_sprite(dc, body_art, body_frame, x, y);
    }
}

static void draw_leviathan_sprite_revealed(HDC dc, const SpriteSheet *art,
                                           uint32_t frame, int x, int y,
                                           int mask_progress)
{
    if (art == NULL || frame >= art->frame_count) return;
    if (mask_progress >= 8) draw_sprite(dc, art, frame, x, y);
    else if (mask_progress > 0)
        draw_feature_reveal(dc, art, g_island_surface_id, frame,
                            x, y, mask_progress);
}

/* FUN_0040bf98's item-6, -8 and -9 branches call FUN_00428191 on the floater
   linked at raw +0x2e, drawing its body/legs at the PROD output point. */
static int draw_island_leviathan_spawn_effect(
    HDC dc, const GameRuntimeLocation *location,
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
    draw_leviathan_sprite_revealed(dc, leg_art, leg_frame,
                                   output.x, output.y, mask_progress);
    if (floater->source_subtype >= 10U && floater->source_subtype <= 17U) {
        const SpriteSheet *body_art = floater->facing_left
            ? &g_leviathan_body_art_flipped : &g_leviathan_body_art;
        uint32_t body_frame = 2U * (floater->source_subtype - 10U) +
            (((g_game_session.simulation_tick + floater->animation_seed) / 8U) & 1U);
        draw_leviathan_sprite_revealed(dc, body_art, body_frame,
                                       output.x, output.y, mask_progress);
    }
    return 1;
}

/* FUN_0044034e fills six panel slots from the selected site's eight floater
   links (+4..+0x12): kind 0 fills slots 0..2, kind 1 slots 3..4, kind 2 slot 5
   (no per-kind cap in the source), where the kind is the low nibble of the
   floater's +0x0a (the port's unit level). FUN_00440567 then draws each
   present floater through FUN_0042704b at the fixed pane offsets below; the
   selected-floater highlight path is not ported. */
static void draw_building_slot_floaters(HDC dc, const WindowTemplate *info,
                                        const GameRuntimeLocation *location)
{
    static const int x_default[6] = {230, 230, 230, 195, 195, 160};
    static const int y_default[6] = {21, 55, 89, 35, 72, 55};
    static const int x_hall[6] = {220, 999, 999, 220, 999, 170};
    static const int y_hall[6] = {28, 999, 999, 82, 999, 55};
    int16_t slots[6] = {-1, -1, -1, -1, -1, -1};
    const int *xs = location->record_value_10 == 0x2f ? x_hall : x_default;
    const int *ys = location->record_value_10 == 0x2f ? y_hall : y_default;
    unsigned int kind;
    unsigned int slot;

    if (!g_game_session_valid || location->source_location_slot_18 == -1) return;
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
    for (slot = 0; slot < 6U; ++slot) {
        const GameFloaterStart *floater;
        const SpriteSheet *body_art;
        const SpriteSheet *leg_art;
        int x = info->pane.left + xs[slot];
        int y = info->pane.top + ys[slot];
        if (slots[slot] < 0 || xs[slot] == 999) continue;
        floater = &g_game_session.floaters[slots[slot]];
        if (floater->type_index >= 4U) continue;
        body_art = floater->facing_left
            ? &g_initial_floater_bodies_flipped[floater->type_index]
            : &g_initial_floater_bodies[floater->type_index];
        leg_art = floater->facing_left
            ? &g_initial_floater_legs_flipped[floater->type_index]
            : &g_initial_floater_legs[floater->type_index];
        if (leg_art->frame_count != 0)
            draw_sprite(dc, leg_art, island_floater_legs_frame(floater), x, y);
        if (body_art->frame_count != 0) draw_sprite(dc, body_art, 0, x, y);
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
   Palette slots DAT_0049e140[1..6] are the 6-bit RGB triples at 0x49e148
   matched to the island palette by FUN_0041081b (assumed nearest colour).
   Remake only: columns outside the explored extent are blacked out, since
   the camera cannot reach them, and no dot is drawn there. */
static COLORREF lilmap_slot_color(int slot)
{
    static const unsigned char rgb6[7][3] = {
        {0, 0, 0}, {63, 63, 63}, {63, 0, 0}, {0, 63, 0},
        {0, 0, 63}, {63, 63, 0}, {50, 50, 50}
    };
    int best = 0;
    int best_distance = 0x7fffffff;
    int index;
    if (slot <= 0 || slot > 6) return g_island_palette[0];
    for (index = 0; index < 256; ++index) {
        int dr = (int)GetRValue(g_island_palette[index]) - rgb6[slot][0] * 255 / 63;
        int dg = (int)GetGValue(g_island_palette[index]) - rgb6[slot][1] * 255 / 63;
        int db = (int)GetBValue(g_island_palette[index]) - rgb6[slot][2] * 255 / 63;
        int distance = dr * dr + dg * dg + db * db;
        if (distance < best_distance) {
            best_distance = distance;
            best = index;
        }
    }
    return g_island_palette[best];
}

static void lilmap_fill(HDC dc, int left, int top, int width, int height,
                        COLORREF color)
{
    RECT box;
    HBRUSH brush;
    box.left = left; box.top = top;
    box.right = left + width; box.bottom = top + height;
    brush = CreateSolidBrush(color);
    FillRect(dc, &box, brush);
    DeleteObject(brush);
}

static int lilmap_explored(int island_index, int x)
{
    if (!g_game_session_valid || g_menu.selected_tribe < 0) return 1;
    return game_session_island_x_explored(&g_game_session,
        (uint8_t)island_index, (uint8_t)g_menu.selected_tribe, x);
}

static void draw_island_lilmap_dots(HDC dc, const WindowTemplate *mini_map,
                                    const GameRuntimeIsland *island)
{
    int saved = SaveDC(dc);
    unsigned int n;
    int column;
    int pane_width = mini_map->pane.right - mini_map->pane.left + 1;
    int pane_height = mini_map->pane.bottom - mini_map->pane.top + 1;
    int viewer = g_menu.selected_tribe;
    (void)IntersectClipRect(dc, mini_map->pane.left, mini_map->pane.top,
                            mini_map->pane.right + 1, mini_map->pane.bottom + 1);
    /* Hide unreachable (unexplored) columns; one minimap pixel = 10 units. */
    for (column = 0; column < pane_width; ) {
        int run = column;
        while (run < pane_width &&
               !lilmap_explored(g_menu.selected_map_island, run * 10)) ++run;
        if (run > column) {
            lilmap_fill(dc, mini_map->pane.left + column, mini_map->pane.top,
                        run - column, pane_height, RGB(0, 0, 0));
            column = run;
        } else {
            ++column;
        }
    }
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
            if (!lilmap_explored(g_menu.selected_map_island, (int)loc->x)) continue;
            lilmap_fill(dc, cx - 1, cy - 1, 3, 3, lilmap_slot_color(slot));
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
            if (!lilmap_explored(g_menu.selected_map_island, (int)fl->x)) continue;
            if (own && fl->source_link_0c != -1)
                slot = fl->source_subtype == 4 ? 4 : 2;
            if (own && (int)n == g_selected_floater) slot = 5;
            px = (int)fl->x / 10 + mini_map->pane.left;
            py = (int)fl->y / 10 + mini_map->pane.top;
            if (px < mini_map->pane.left) px = mini_map->pane.left;
            if (px > mini_map->pane.right - 1) px = mini_map->pane.right - 1;
            if (py < mini_map->pane.top) py = mini_map->pane.top;
            if (py > mini_map->pane.bottom - 1) py = mini_map->pane.bottom - 1;
            for (pixel = 0; pixel < 4; ++pixel) {
                int lit = fl->type_index == 4 ? (pixel == 0 || pixel == 3)
                                              : pixel == fl->type_index;
                lilmap_fill(dc, px + (pixel & 1), py + (pixel >> 1), 1, 1,
                            lilmap_slot_color(lit ? slot : 0));
            }
        }
    }
    if (saved != 0) RestoreDC(dc, saved);
}

static void render_island_view(HDC dc)
{
    const int image_top = 0;
    const int status_top = 320;
    const IslandLocation *focus = NULL;
    const GameFloaterStart *selected_floater = NULL;
    int focus_index = g_hovered_location >= 0 ? g_hovered_location : g_selected_location;
    int hall_player = selected_hall_player();
    int saved_dc;
    uint16_t i;
    const GameRuntimeIsland *runtime_island = NULL;
    const GameRuntimeLocation *selected_runtime_location = NULL;
    int selected_ground_item = -1;

    if (g_game_session_valid && g_menu.selected_map_island >= 0 &&
        g_menu.selected_map_island < g_game_session.island_count) {
        runtime_island = &g_game_session.islands[g_menu.selected_map_island];
        if (g_selected_location >= 0 &&
            g_selected_location < runtime_island->location_count) {
            selected_runtime_location =
                &runtime_island->locations[g_selected_location];
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
            if (candidate->island_index == g_menu.selected_map_island) {
                selected_floater = candidate;
            }
        }
    }

    g_island_scroll_x = island_clamp_scroll(g_island_scroll_x);
    fill_rect(dc, 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT, RGB(0, 0, 0));
    if (g_island_height_data == NULL ||
        g_island_height_length != ISLAND_HAZE_FILE_BYTES) {
        draw_sprite(dc, &g_island_template_art, 0, 0, status_top);
        draw_island_access_notice(dc);
        return;
    }
    draw_sprite_region(dc, &g_island_surface_art, 0, g_island_scroll_x, 0,
                       LOGICAL_WIDTH, 320, 0, image_top);

    if (focus_index >= 0 && focus_index < g_island_surface_data.location_count) {
        focus = &g_island_surface_data.locations[focus_index];
    }
    /* windows.txt defines ISLEVIEW as the 640x320 upper pane. Clip sprites to
       that view so tall SHP frames cannot overwrite the ISLETEMP controls. */
    saved_dc = SaveDC(dc);
    (void)IntersectClipRect(dc, 0, 0, LOGICAL_WIDTH, status_top);
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
        COLORREF color = island_location_color(location->type);
        int dx;
        int dy;
        if (location->renderer_class == 3 &&
            (location->renderer_variant == 4 || location->renderer_variant == 0x16)) {
            draw_island_feature(dc, g_island_surface_id, location,
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
        if (runtime_class == 2 && g_bridge_trigger_art.frame_count == 23) {
            draw_sprite(dc, &g_bridge_trigger_art, 0, x, y);
            continue;
        }
        {
            int drew_location = 0;
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
            draw_sprite(dc, &g_tone_field_art, ISLAND_TONE_POOL_BASE_FRAME, x, y);
            draw_sprite(dc, &g_tone_field_art, frame, x, y);
            drew_location = 1;
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
                runtime_item_id < g_pad_catalog.item_count &&
                g_pad_catalog.items[runtime_item_id].tribe == PAD_TRIBE_LEVIATHAN;
            int is_item_render_site = is_construction_site ||
                is_leviathan_building_on_tone;
            int occupied = is_item_render_site && runtime_location != NULL &&
                runtime_location->record_value_10 > 0;
            int has_runtime_item = is_item_render_site
                ? draw_runtime_item(dc, runtime_location, x, y) : 0;
            if (occupied && !has_runtime_item &&
                !draw_ground_item_icon(dc, runtime_location, x, y)) {
                draw_ground_item_fallback(dc, runtime_location, x, y);
            }
            if (has_runtime_item || occupied) drew_location = 1;
            else if (island_site_should_draw_pad(pad_group, occupied) &&
                                          g_pad_art.frame_count == 27) {
                uint32_t frame = island_pad_frame(g_menu.animation_ticks,
                                                  location->x,
                                                  (unsigned)pad_group,
                                                  location->renderer_subtype);
                draw_sprite(dc, &g_pad_art, frame, x, y);
                drew_location = 1;
            }
            /* No native overlay shows Build Tone deposited on an empty pad:
               the object painter FUN_0040bf98 never reads site +0x28, and the
               readers found (FUN_004459e6, FUN_00440567) gate on hall sites
               (+0x10 == 0x2a). The former icon + count was invented. */
        }
        if (drew_location) continue;
        }
        for (dy = -2; dy <= 2; ++dy) {
            for (dx = -2; dx <= 2; ++dx) {
                if (dx * dx + dy * dy <= 5) (void)SetPixelV(dc, x + dx, y + dy, color);
            }
        }
    }
    /* FUN_0046466f creates four idle type-0 floaters for each player at the
       selected hall marker. FUN_0042704b draws tribe-specific legs and body
       separately, switching from hover to carry legs when cargo is present. */
    if (runtime_island != NULL && g_game_session_valid) {
        unsigned floater_index;
        for (floater_index = 0; floater_index < g_game_session.floater_count;
             ++floater_index) {
            const GameFloaterStart *floater = &g_game_session.floaters[floater_index];
            int floater_x;
            int floater_y;
            uint32_t leg_frame;
            const SpriteSheet *body_art;
            const SpriteSheet *leg_art;
            if (!game_session_floater_is_active(floater) ||
                floater->island_index != g_menu.selected_map_island ||
                floater->type_index > 4) continue;
            floater_x = (int)floater->x - g_island_scroll_x;
            if (floater_x < -64 || floater_x >= LOGICAL_WIDTH + 64) continue;
            floater_y = image_top + (int)floater->y;
            if (floater->type_index == 4) {
                draw_island_leviathan_floater(dc, floater, floater_x, floater_y);
                /* Overlays need the body shape (local_c != 0): subtype 9
                   has legs only and gets none. */
                if (floater->source_subtype >= 10U &&
                    floater->source_subtype <= 17U) {
                    draw_island_floater_overlays(
                        dc, floater,
                        floater->facing_left ? &g_leviathan_body_art_flipped
                                             : &g_leviathan_body_art,
                        2U * (floater->source_subtype - 10U) +
                            (((g_game_session.simulation_tick +
                               floater->animation_seed) / 8U) & 1U),
                        floater_x, floater_y);
                }
                continue;
            }
            leg_frame = island_floater_legs_frame(floater);
            body_art = floater->facing_left
                           ? &g_initial_floater_bodies_flipped[floater->type_index]
                           : &g_initial_floater_bodies[floater->type_index];
            leg_art = floater->facing_left
                          ? &g_initial_floater_legs_flipped[floater->type_index]
                          : &g_initial_floater_legs[floater->type_index];
            /* FUN_0042704b draws cargo first (behind legs and body) at
               floater + fltinf graspxy (record +0x25/+0x26), mirrored with
               the facing, plus the per-item vertical offset (DAT_0049acbe,
               not yet extracted: 0 here). */
            if (floater->carried_resource_code != 0) {
                static const int8_t grasp_x[4] = {10, 10, 13, 11};
                static const int8_t grasp_y[4] = {12, 14, 14, 20};
                int hand_x = floater_x + (floater->facing_left
                    ? -grasp_x[floater->type_index]
                    : grasp_x[floater->type_index]);
                int hand_y = floater_y + grasp_y[floater->type_index];
                if (floater->carried_resource_code >= 1 &&
                    floater->carried_resource_code <= GAME_RESOURCE_TYPE_COUNT) {
                    static const SpriteSheet *const carried_art[] = {
                        &g_bildtone_art, &g_tone_crys_art, &g_magctone_art
                    };
                    const SpriteSheet *cargo_art = carried_art[
                        (unsigned int)floater->carried_resource_code - 1U];
                    if (cargo_art->frame_count != 0) {
                        draw_sprite_scaled(dc, cargo_art, 0, hand_x, hand_y,
                                           0x00008000U);
                    }
                } else if (floater->carried_resource_code >=
                               GAME_INVENTORY_ITEM_FIRST_ID &&
                           floater->carried_resource_code <
                               GAME_INVENTORY_ITEM_FIRST_ID +
                                   GAME_INVENTORY_ITEM_COUNT &&
                           (uint32_t)(floater->carried_resource_code -
                               GAME_INVENTORY_ITEM_FIRST_ID) <
                                   g_inventory_item_art.frame_count) {
                    draw_sprite_scaled(dc, &g_inventory_item_art,
                                       (uint32_t)(floater->carried_resource_code -
                                           GAME_INVENTORY_ITEM_FIRST_ID),
                                       hand_x, hand_y, 0x00008000U);
                }
            }
            draw_sprite(dc, leg_art, leg_frame, floater_x, floater_y);
            draw_sprite(dc, body_art, 0, floater_x, floater_y);
            draw_island_floater_overlays(dc, floater, body_art, 0,
                                         floater_x, floater_y);
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
            draw_sprite(dc, effect_art, frame, x, y);
        }
    }
    if (focus != NULL) {
        int x = (int)focus->x - g_island_scroll_x;
        int y = image_top + (int)focus->y;
        HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
        HGDIOBJ old_pen = SelectObject(dc, pen);
        HGDIOBJ old_brush = SelectObject(dc, GetStockObject(NULL_BRUSH));
        Ellipse(dc, x - 8, y - 8, x + 9, y + 9);
        SelectObject(dc, old_brush);
        SelectObject(dc, old_pen);
        DeleteObject(pen);
    }
    if (saved_dc != 0) RestoreDC(dc, saved_dc);

    /* ISLETMP is the original 640x160 bottom template at y=320, matching the
       ISLETMP pane in windows.txt. It uses the active island palette. */
    draw_sprite(dc, &g_island_template_art, 0, 0, status_top);

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
        if (realm_panel != NULL && g_island_realm_art.frame_count != 0) {
            draw_sprite(dc, &g_island_realm_art,
                        (uint32_t)realm_panel->shape_frame,
                        realm_panel->pane.left, realm_panel->pane.top);
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
                draw_sprite(dc, &g_island_main_buttons, (uint32_t)frame,
                            button->pane.left, button->pane.top);
            }
        }
    }

    draw_hall_panel(dc, hall_player);

    /* windows.txt places IWLilMap at (192,328)-(447,359), and shapes.txt
       binds it to the 16-frame LILMAP sheet. The SHP frame is indexed by the
       selected island's existing surface id (the local 15-island corpus uses
       the corresponding first 15 frames). */
    if (g_island_surface_id >= 0 && g_island_surface_id < 16) {
        const WindowTemplate *mini_map = window_catalog_find(
            &g_window_catalog, "IWLilMap", 3);
        if (mini_map != NULL) {
            draw_sprite(dc, &g_island_lilmap_art,
                        (uint32_t)g_island_surface_id,
                        mini_map->pane.left, mini_map->pane.top);
            draw_island_lilmap_dots(dc, mini_map, runtime_island);
            /* Remake: outline of the 640px view on the 1/10 scale minimap. */
            {
                HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
                HGDIOBJ old_pen = SelectObject(dc, pen);
                HGDIOBJ old_brush = SelectObject(dc, GetStockObject(NULL_BRUSH));
                int view_left = mini_map->pane.left + g_island_scroll_x / 10;
                int view_right = view_left + LOGICAL_WIDTH / 10;
                /* Two nested outlines so the frame stays readable on any art. */
                Rectangle(dc, view_left, mini_map->pane.top,
                          view_right + 1, mini_map->pane.bottom + 1);
                Rectangle(dc, view_left + 1, mini_map->pane.top + 1,
                          view_right, mini_map->pane.bottom);
                SelectObject(dc, old_brush);
                SelectObject(dc, old_pen);
                DeleteObject(pen);
            }
        }
    }

    draw_iw_construct(dc);
    if (selected_ground_item >= 0 &&
        island_panel_location_info_visible(g_island_panel_mode)) {
        const WindowTemplate *info = window_catalog_find(
            &g_window_catalog, "IWLocInfo", 3);
        if (info != NULL && g_temp_hole_art.frame_count > 1) {
            RECT pane = {info->pane.left, info->pane.top,
                         info->pane.right + 1, info->pane.bottom + 1};
            int saved_info_dc = SaveDC(dc);
            unsigned int item_frame = (unsigned int)(selected_ground_item -
                GAME_INVENTORY_ITEM_FIRST_ID);
            (void)IntersectClipRect(dc, pane.left, pane.top,
                                    pane.right, pane.bottom);
            draw_sprite(dc, &g_temp_hole_art, 1,
                        info->pane.left, info->pane.top);
            /* FUN_00440567 sends P+4==0, P+0x10 in {0,1} sites to FUN_00441aae:
               no text and no buttons, only the TRIGGERS (alltrigs.shp) frame
               +0x24-5 centred in the pane by FUN_004119ba. FUN_0044338b is the
               unit detail renderer and is not used here. */
            if (item_frame < g_inventory_item_art.frame_count &&
                g_inventory_item_art.frames[item_frame].bitmap != NULL) {
                const SpriteFrame *icon = &g_inventory_item_art.frames[item_frame];
                int icon_x = info->pane.left +
                    ((info->pane.right - info->pane.left + 1) -
                     (int)icon->width) / 2 - icon->x_offset;
                int icon_y = info->pane.top +
                    ((info->pane.bottom - info->pane.top + 1) -
                     (int)icon->height) / 2 - icon->y_offset;
                draw_sprite(dc, &g_inventory_item_art, item_frame,
                            icon_x, icon_y);
            }
            if (saved_info_dc != 0) RestoreDC(dc, saved_info_dc);
        }
    } else if (selected_floater != NULL && selected_floater->type_index < 4 &&
        island_panel_location_info_visible(g_island_panel_mode)) {
        const WindowTemplate *info = window_catalog_find(
            &g_window_catalog, "IWLocInfo", 3);
        if (info != NULL && g_temp_hole_art.frame_count > 1) {
            RECT pane = {info->pane.left, info->pane.top,
                         info->pane.right + 1, info->pane.bottom + 1};
            int saved_info_dc = SaveDC(dc);
            (void)IntersectClipRect(dc, pane.left, pane.top,
                                    pane.right, pane.bottom);
            draw_sprite(dc, &g_temp_hole_art, 1,
                        info->pane.left, info->pane.top);

            /* FUN_0044338b (Iwloc.cpp) draws the selected object's details in
               IWLocInfo. Initial workers are class 0, level 0, and have the
               four tribe-specific *work rows: 3 hit points and 0 strength.
               FUN_00466fe4 initializes current hits to FUN_00420f28's max. */
            {
                /* Name row: "%s %s" of the names.txt tribe slot and the
                   gamey.txt WORKER label (FUN_0044338b, class 0). */
                char worker_label[96];
                int label_width;
                (void)snprintf(worker_label, sizeof(worker_label), "%s %s",
                    g_tribe_names[selected_floater->type_index],
                    g_unit_label_text[0]);
                label_width = measure_bitmap_text(NULL, worker_label,
                                                   strlen(worker_label));
                draw_bitmap_label(dc, worker_label,
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
                draw_bitmap_label(dc, hit_points_label,
                                  info->pane.left + 5, info->pane.top + 23,
                                  RGB(230, 238, 255));
                draw_bitmap_label(dc, strength_label,
                                  info->pane.left + 5, info->pane.top + 33,
                                  RGB(230, 238, 255));
                /* FUN_0044338b gates CHARGE through FUN_004207f2, which
                   returns null for floater +0x0c == -1. */
                if (game_session_floater_charge_values(selected_floater,
                        &g_floater_catalog, &current_charge, &maximum_charge)) {
                    (void)snprintf(charge_label, sizeof(charge_label),
                        "%s %d/%d", g_unit_label_text[5], (int)current_charge,
                        (int)maximum_charge);
                    draw_bitmap_label(dc, charge_label,
                                      info->pane.left + 5,
                                      info->pane.top + 43,
                                      RGB(230, 238, 255));
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
                const SpriteSheet *body_art = selected_floater->facing_left
                    ? &g_initial_floater_bodies_flipped[selected_floater->type_index]
                    : &g_initial_floater_bodies[selected_floater->type_index];
                const SpriteSheet *leg_art = selected_floater->facing_left
                    ? &g_initial_floater_legs_flipped[selected_floater->type_index]
                    : &g_initial_floater_legs[selected_floater->type_index];
                const SpriteFrame *body_frame = &body_art->frames[0];
                draw_sprite(dc, leg_art, leg_frame, sprite_x, sprite_y);
                draw_sprite(dc, body_art, 0, sprite_x, sprite_y);
                /* The source draws a carried item as part of FUN_0042704b's
                   floater sprite, never as a separate CARRY text row. Until
                   shapeinf.txt hand anchors and carry-frame ranges are loaded,
                   keep the icon attached to the body's hand area. */
                if (selected_floater->carried_resource_code >= 1 &&
                    selected_floater->carried_resource_code <=
                        GAME_RESOURCE_TYPE_COUNT) {
                    static const SpriteSheet *const carried_art[] = {
                        &g_bildtone_art, &g_tone_crys_art, &g_magctone_art
                    };
                    unsigned int resource_index =
                        (unsigned int)selected_floater->carried_resource_code - 1U;
                    int hand_x = sprite_x + body_frame->x_offset +
                                 (selected_floater->facing_left ? -6 : 5);
                    int hand_y = sprite_y + body_frame->y_offset - 1;
                    if (carried_art[resource_index]->frame_count != 0) {
                        draw_sprite_scaled(dc, carried_art[resource_index], 0,
                            hand_x, hand_y, 0x00008000U);
                    }
                } else if (selected_floater->carried_resource_code >=
                               GAME_INVENTORY_ITEM_FIRST_ID &&
                           selected_floater->carried_resource_code <
                               GAME_INVENTORY_ITEM_FIRST_ID +
                                   GAME_INVENTORY_ITEM_COUNT &&
                           (uint32_t)(selected_floater->carried_resource_code -
                               GAME_INVENTORY_ITEM_FIRST_ID) <
                                   g_inventory_item_art.frame_count &&
                           body_art->frame_count != 0) {
                    const SpriteFrame *body_frame = &body_art->frames[0];
                    int hand_x = sprite_x + body_frame->x_offset +
                                 (selected_floater->facing_left ? -6 : 5);
                    int hand_y = sprite_y + body_frame->y_offset - 1;
                    uint32_t item_frame = (uint32_t)(
                        selected_floater->carried_resource_code -
                        GAME_INVENTORY_ITEM_FIRST_ID);
                    draw_sprite_scaled(dc, &g_inventory_item_art, item_frame,
                                       hand_x, hand_y, 0x00008000U);
                }
                /* FUN_0044338b enables the info flags around this sprite.
                   FUN_0042003c maps the startup *work row's realm to frames
                   22..25 and adjusts it from the retained current-location
                   flags when that location context is available. */
                if (g_floater_info_art.frame_count >= 26) {
                    uint32_t realm_frame;
                    int32_t badge_x;
                    int32_t badge_y;
                    const GameRuntimeLocation *current_location = NULL;
                    if (runtime_island != NULL && g_selected_location >= 0 &&
                        g_selected_location < runtime_island->location_count) {
                        current_location = &runtime_island->locations[g_selected_location];
                    }
                    int32_t body_left = sprite_x + body_frame->x_offset +
                                        body_frame->hit_left;
                    int32_t body_top = sprite_y + body_frame->y_offset +
                                       body_frame->hit_top;
                    int32_t body_right = sprite_x + body_frame->x_offset +
                                         body_frame->hit_right;
                    if (island_worker_realm_badge_layout(
                            selected_floater->type_index,
                            current_location != NULL,
                            current_location == NULL ? 0 : current_location->source_flags,
                            selected_floater->facing_left,
                            body_left, body_top, body_right,
                            &realm_frame, &badge_x, &badge_y) &&
                        realm_frame < g_floater_info_art.frame_count) {
                        draw_sprite(dc, &g_floater_info_art, realm_frame,
                                    badge_x, badge_y);
                    }
                }
                /* Combat-stat frame and anchor are independently derived from
                   FUN_0042704b / FUN_00420f28. */
                if (g_floater_info_art.frame_count >= 26) {
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
                            selected_floater->type_index,
                            island_floater_health_stat(selected_floater),
                            selected_floater->facing_left,
                            body_left, body_top, body_right,
                            &stat_frame, &badge_x, &badge_y) &&
                        stat_frame < g_floater_info_art.frame_count) {
                        draw_sprite(dc, &g_floater_info_art, stat_frame,
                                    badge_x, badge_y);
                    }
                }
            }
            if (saved_info_dc != 0) RestoreDC(dc, saved_info_dc);
        }
    } else if (selected_floater != NULL && selected_floater->owner_slot == 4U &&
               game_session_floater_is_active(selected_floater) &&
               selected_floater->source_subtype >= 9U &&
               selected_floater->source_subtype <= 17U &&
               island_panel_location_info_visible(g_island_panel_mode)) {
        const WindowTemplate *info = window_catalog_find(
            &g_window_catalog, "IWLocInfo", 3);
        if (info != NULL && g_temp_hole_art.frame_count > 1) {
            RECT pane = {info->pane.left, info->pane.top,
                         info->pane.right + 1, info->pane.bottom + 1};
            int saved_info_dc = SaveDC(dc);
            unsigned int level = selected_floater->attack_level_flags & 0x0fU;
            char name_label[24];
            char row_label[32];
            int label_width;
            int row_y;
            (void)IntersectClipRect(dc, pane.left, pane.top,
                                    pane.right, pane.bottom);
            draw_sprite(dc, &g_temp_hole_art, 1,
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
            draw_bitmap_label(dc, name_label,
                info->pane.left +
                    ((info->pane.right - info->pane.left + 1) - label_width) / 2,
                info->pane.top + 3, RGB(230, 238, 255));
            row_y = info->pane.top + 23;
            (void)snprintf(row_label, sizeof(row_label), "%s %u", g_unit_label_text[2],
                           level + 1U);
            draw_bitmap_label(dc, row_label, info->pane.left + 5, row_y,
                              RGB(230, 238, 255));
            row_y += 10;
            (void)snprintf(row_label, sizeof(row_label), "%s %d/%d",
                g_unit_label_text[3],
                selected_floater->current_hit_points < 0
                    ? 0 : (int)selected_floater->current_hit_points,
                (int)selected_floater->max_hit_points);
            draw_bitmap_label(dc, row_label, info->pane.left + 5, row_y,
                              RGB(230, 238, 255));
            row_y += 10;
            (void)snprintf(row_label, sizeof(row_label), "%s %u",
                g_unit_label_text[4],
                (unsigned int)selected_floater->attack_strength);
            draw_bitmap_label(dc, row_label, info->pane.left + 5, row_y,
                              RGB(230, 238, 255));
            draw_island_leviathan_floater(dc, selected_floater,
                info->pane.right - 50,
                info->pane.top + (info->pane.bottom - info->pane.top) / 2 + 5);
            if (saved_info_dc != 0) RestoreDC(dc, saved_info_dc);
        }
    } else if (island_panel_location_info_visible(g_island_panel_mode) &&
               runtime_island != NULL && g_selected_location >= 0 &&
               g_selected_location < runtime_island->location_count) {
        const GameRuntimeLocation *selected_location =
            &runtime_island->locations[g_selected_location];
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
                int saved_info_dc = SaveDC(dc);
                (void)IntersectClipRect(dc, pane.left, pane.top,
                                        pane.right, pane.bottom);
                draw_sprite(dc, &g_temp_hole_art, 1,
                            info->pane.left, info->pane.top);
                /* The source paints the selected building in IWLocInfo via
                   FUN_0042704b. Reuse the same data-driven BASE/CHUG/etc.
                   layers already used by the island renderer. */
                {
                    int sprite_x;
                    int sprite_y;
                    if (island_panel_info_building_sprite_position(
                            info, &sprite_x, &sprite_y)) {
                        /* FUN_0044338b passes full scale (0x10000) and a
                           pane-relative width/height anchor to FUN_0042704b. */
                        (void)draw_runtime_item_scaled(dc, selected_location,
                            sprite_x, sprite_y, 0x10000U);
                    }
                }
                draw_building_info_extras(dc, info, selected_location,
                    (uint8_t)g_menu.selected_map_island,
                    (uint16_t)g_selected_location);
                draw_building_slot_floaters(dc, info, selected_location);
                if (saved_info_dc != 0) RestoreDC(dc, saved_info_dc);
            }
        }
    }
    /* IWLocInfo's selected-building painter clears and redraws this pane, so
       render the Hall's economy view after it. */
    if (island_panel_location_info_visible(g_island_panel_mode)) {
        draw_hall_stock_summary(dc, hall_player, runtime_island);
    }

    /* Show one representative worker beside the Hall's population summary.
       The Hall is not a roster container, so don't paint every player worker
       as if they were attached to this building. */
    {
        int player = selected_hall_player();
        if (player >= 0 &&
            island_panel_location_info_visible(g_island_panel_mode)) {
            const WindowTemplate *info = window_catalog_find(
                &g_window_catalog, "IWLocInfo", 3);
            int roster[ISLAND_PANEL_INFO_ROSTER_SLOT_COUNT];
            uint8_t count = collect_initial_worker_roster((unsigned int)player,
                                                          roster);
            uint8_t slot;
            if (info != NULL && count != 0) {
                RECT pane = {info->pane.left, info->pane.top,
                             info->pane.right + 1, info->pane.bottom + 1};
                int saved_roster_dc = SaveDC(dc);
                (void)IntersectClipRect(dc, pane.left, pane.top,
                                        pane.right, pane.bottom);
                for (slot = 0; slot < count; ++slot) {
                    const GameFloaterStart *floater =
                        &g_game_session.floaters[roster[slot]];
                    const SpriteSheet *body_art;
                    const SpriteSheet *leg_art;
                    int offset_x;
                    int offset_y;
                    if (!island_panel_info_roster_position(slot, 0,
                                                          &offset_x, &offset_y)) {
                        continue;
                    }
                    body_art = floater->facing_left
                        ? &g_initial_floater_bodies_flipped[floater->type_index]
                        : &g_initial_floater_bodies[floater->type_index];
                    leg_art = floater->facing_left
                        ? &g_initial_floater_legs_flipped[floater->type_index]
                        : &g_initial_floater_legs[floater->type_index];
                    if (leg_art->frame_count != 0) {
                        draw_sprite(dc, leg_art,
                            island_floater_legs_frame(floater),
                            info->pane.left + offset_x,
                            info->pane.top + offset_y);
                    }
                    if (body_art->frame_count != 0) {
                        draw_sprite(dc, body_art, 0,
                            info->pane.left + offset_x,
                            info->pane.top + offset_y);
                    }
                }
                if (saved_roster_dc != 0) RestoreDC(dc, saved_roster_dc);
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
                draw_sprite(dc, &g_hall_stock_art, frame,
                            button->pane.left, button->pane.top);
            }
            /* The highlight is a transparent overlay; keep the active stock
               mode icon visible underneath it while hovering. */
            if ((int)resource == g_hovered_hall_stock &&
                button->has_hilite_frame && button->hilite_frame >= 0 &&
                (uint32_t)button->hilite_frame < g_hall_stock_art.frame_count) {
                draw_sprite(dc, &g_hall_stock_art,
                            (uint32_t)button->hilite_frame,
                            button->pane.left, button->pane.top);
            }
        }
    }
    draw_location_action_panel(dc);

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
                draw_sprite(dc, &g_hall_command_art, (uint32_t)frame,
                            button->pane.left, button->pane.top);
            }
        }
    }
    draw_island_access_notice(dc);
}

static void draw_location_action_panel(HDC dc)
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
        g_menu.selected_map_island < 0 ||
        g_menu.selected_map_island >= g_game_session.island_count ||
        g_selected_location < 0) return;
    island = &g_game_session.islands[g_menu.selected_map_island];
    if (g_selected_location >= island->location_count) return;
    selected_location = &island->locations[g_selected_location];
    panel = window_catalog_find(&g_window_catalog, "IWLocControl", 3);
    if (panel != NULL && panel->shape_frame >= 0 &&
        (uint32_t)panel->shape_frame < g_temp_hole_art.frame_count) {
        draw_sprite(dc, &g_temp_hole_art, (uint32_t)panel->shape_frame,
                    panel->pane.left, panel->pane.top);
    }

    /* IWTextInfo is the selected-location description pane. The source UI
       fills it for a selected building; the remake previously left it empty
       unless a move control was hovered. */
    if (g_island_panel_mode == WINDOW_ISLAND_PANEL_GENERAL &&
        selected_location->record_value_10 >= 0x25 &&
        selected_location->record_value_10 < PAD_CATALOG_MAX_ITEMS &&
        g_building_descriptions[selected_location->record_value_10][0] != '\0') {
        text_panel = window_catalog_find(&g_window_catalog, "IWTextInfo", 3);
        if (text_panel != NULL && text_panel->shape_frame >= 0 &&
            (uint32_t)text_panel->shape_frame < g_temp_hole_art.frame_count) {
            int pane_width = text_panel->pane.right - text_panel->pane.left;
            int pane_height = text_panel->pane.bottom - text_panel->pane.top;
            int line_height = (int)g_bitmap_font.height + 2;
            int max_lines = line_height > 0
                ? (pane_height - 0x10) / line_height : 0;
            draw_sprite(dc, &g_temp_hole_art,
                        (uint32_t)text_panel->shape_frame,
                        text_panel->pane.left, text_panel->pane.top);
            draw_wrapped_bitmap_label(dc,
                g_building_descriptions[selected_location->record_value_10],
                text_panel->pane.left + 10, text_panel->pane.top + 0x10,
                pane_width - 20, max_lines, RGB(230, 238, 255));
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
            draw_sprite(dc, &g_temp_hole_art,
                        (uint32_t)text_panel->shape_frame,
                        text_panel->pane.left, text_panel->pane.top);
            draw_bitmap_label(dc, level_name,
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
            int pane_width = text_panel->pane.right - text_panel->pane.left;
            int pane_height = text_panel->pane.bottom - text_panel->pane.top;
            int line_height = (int)g_bitmap_font.height + 2;
            int max_lines = line_height > 0
                ? (pane_height - 0x10) / line_height : 0;
            draw_sprite(dc, &g_temp_hole_art,
                        (uint32_t)text_panel->shape_frame,
                        text_panel->pane.left, text_panel->pane.top);
            draw_wrapped_bitmap_label(dc,
                island_site_info_text(selected_location,
                                      g_menu.selected_tribe),
                text_panel->pane.left + 10, text_panel->pane.top + 0x10,
                pane_width - 20, max_lines, RGB(230, 238, 255));
        }
    }

    action = selected_location_action();
    if (g_island_panel_mode == WINDOW_ISLAND_PANEL_GENERAL) {
        static const char *const spell_names[8] = {
            "BC_Spell1", "BC_Spell2", "BC_Spell3", "BC_Spell4",
            "BC_Spell5", "BC_Spell6", "BC_Spell7", "BC_Spell8"
        };
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
            draw_control_with_hover_overlay(dc, &onoff_state,
                &g_building_command_art, g_hovered_onoff_control);
        }
        if (selected_upgrade_button_visible()) {
            draw_control_with_hover_overlay(dc, upgrade_button,
                &g_upgrade_button_art, g_hovered_upgrade_control);
        }
        if (selected_repair_button_visible()) {
            draw_control_with_hover_overlay(dc, repair_button,
                &g_repair_button_art, g_hovered_repair_control);
        }
        if (island->locations[g_selected_location].renderer_class == 0 &&
            island->locations[g_selected_location].owner_id ==
                g_menu.selected_tribe &&
            island->locations[g_selected_location].source_location_slot_18 >= 0 &&
            (island->locations[g_selected_location].record_value_10 == 0x2f ||
             island->locations[g_selected_location].record_value_10 == 0x30)) {
            unsigned int spell_index;
            for (spell_index = 0; spell_index < 8; ++spell_index) {
                int kind = game_session_cast_kind_for_action(
                    (uint8_t)island->locations[g_selected_location].source_value_14,
                    (uint8_t)(0x15U + spell_index));
                const WindowTemplate *spell_button;
                uint32_t frame;
                if (kind != 8 && kind != 0x14 && kind != 0x16) continue;
                spell_button = window_catalog_find(&g_window_catalog,
                    spell_names[spell_index], 3);
                frame = (uint32_t)kind * 2U;
                if (spell_button != NULL && frame < g_building_command_art.frame_count) {
                    draw_sprite(dc, &g_building_command_art, frame,
                                spell_button->pane.left, spell_button->pane.top);
                }
            }
        }
    }
    if (panel != NULL && selected_location_can_be_grabbed()) {
        RECT button_rect;
        HBRUSH button_brush;
        HBRUSH border_brush;
        const char *label = g_game_session.location_move_active
            ? "CANCEL MOVE" : "GRAB BUILDING";
        if (location_grab_button_rect(&button_rect)) {
            COLORREF fill = g_hovered_location_grab
                ? RGB(72, 91, 126) : RGB(43, 57, 84);
            button_brush = CreateSolidBrush(fill);
            border_brush = CreateSolidBrush(RGB(168, 190, 224));
            if (button_brush != NULL) {
                (void)FillRect(dc, &button_rect, button_brush);
                DeleteObject(button_brush);
            }
            if (border_brush != NULL) {
                (void)FrameRect(dc, &button_rect, border_brush);
                DeleteObject(border_brush);
            }
            {
                int text_width = measure_bitmap_text(NULL, label, strlen(label));
                int text_height = (int)g_small_font.height;
                draw_bitmap_label(dc, label,
                    button_rect.left + ((button_rect.right - button_rect.left) -
                                        text_width) / 2,
                    button_rect.top + ((button_rect.bottom - button_rect.top) -
                                       text_height) / 2,
                    RGB(240, 244, 255));
            }
            if (g_game_session.location_move_active) {
                draw_bitmap_label(dc, "Click a free site to place",
                    panel->pane.left + 8, panel->pane.top + 5,
                    RGB(230, 238, 255));
            }
        }
    }
    if (obtain_button_visible()) {
        const WindowTemplate *obtain_control = window_catalog_find(
            &g_window_catalog, "BC_Obtain", 3);
        if (obtain_control != NULL) {
            draw_control_with_hover_overlay(dc, obtain_control,
                &g_building_command_art, g_hovered_location_grab);
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
        draw_sprite(dc, &g_hall_stock_art, (uint32_t)button->shape_frame,
                    button->pane.left, button->pane.top);
    }
    if (g_hovered_location_action != action) return;
    text_panel = window_catalog_find(&g_window_catalog, "IWTextInfo", 3);
    if (text_panel == NULL || text_panel->shape_frame < 0 ||
        (uint32_t)text_panel->shape_frame >= g_temp_hole_art.frame_count) return;
    draw_sprite(dc, &g_temp_hole_art, (uint32_t)text_panel->shape_frame,
                text_panel->pane.left, text_panel->pane.top);
    if (g_move_button_text[0] != '\0') {
        size_t text_length = strlen(g_move_button_text);
        int text_width = measure_bitmap_text(NULL, g_move_button_text, text_length);
        int text_height = (int)g_small_font.height;
        int pane_width = text_panel->pane.right - text_panel->pane.left;
        int pane_height = text_panel->pane.bottom - text_panel->pane.top;
        draw_bitmap_label(dc, g_move_button_text,
            text_panel->pane.left + (pane_width - text_width) / 2,
            text_panel->pane.top + (pane_height - text_height) / 2,
            g_island_palette[6]);
    }
}

/* The x87 helpers called by FUN_00471536 continue past Ghidra's short
   function boundaries: static disassembly shows FCOS at 0x477ad2 and FSIN at
   0x477332. The constructor supplies the two scale factors used here. */
