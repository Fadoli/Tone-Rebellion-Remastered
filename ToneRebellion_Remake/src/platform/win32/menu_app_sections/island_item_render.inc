static void draw_iw_construct(HDC dc)
{
    const WindowTemplate *window;
    const WindowTemplate *info_window;
    const WindowTemplate *cycle_window;
    const PadCatalogItem *info_item;
    unsigned int column;

    if (!g_iw_construct_open) return;
    window = window_catalog_find(&g_window_catalog, "IWConstruct", 3);
    info_window = window_catalog_find(&g_window_catalog, "IWConstructInfo", 3);
    cycle_window = window_catalog_find(&g_window_catalog, "BuildCycle", 3);
    if (window == NULL || info_window == NULL) return;

    /* The pane extents, backdrop frames, and optional cycle button come from
       windows.txt; the original draw loop lays out four columns per page. */
    draw_sprite(dc, &g_temp_hole_art, (uint32_t)window->shape_frame,
                window->pane.left, window->pane.top);
    for (column = 0; column < IW_CONSTRUCT_ITEMS_PER_PAGE; ++column) {
        size_t item_index = (size_t)g_iw_construct.page *
                            IW_CONSTRUCT_ITEMS_PER_PAGE + column;
        int pane_width = window->pane.right - window->pane.left;
        /* FUN_0043aee8 starts at pane_width/8 and advances (pane_width >> 2)
           per column: 31, 94, 157, 220 for the 255-px pane. */
        int center_x = window->pane.left + pane_width / 8 +
                       (pane_width >> 2) * (int)column;
        if (item_index >= g_iw_construct_item_count) break;
        {
            uint16_t item_id = (uint16_t)(g_iw_construct_items[item_index] +
                (int32_t)g_game_session.config.selected_tribe * 16);
            if (item_id < PAD_CATALOG_MAX_ITEMS &&
                g_building_art[item_id].frame_count != 0 &&
                item_id < g_pad_catalog.item_count) {
                const PadCatalogItem *item = &g_pad_catalog.items[item_id];
                (void)draw_building_preview(dc, item_id,
                    (uint8_t)g_game_session.config.selected_tribe,
                    center_x, window->pane.top +
                    (window->pane.bottom - window->pane.top) - 0x23, 0x8000U);
                if (item->building_tone_cost > 0) {
                    int cost_frame = item->building_tone_cost - 1;
                    if (cost_frame > 0x31) cost_frame = 0x31;
                    if ((uint32_t)cost_frame < g_bildtone_art.frame_count) {
                        draw_sprite_scaled(dc, &g_bildtone_art, (uint32_t)cost_frame,
                            center_x, window->pane.top +
                            (window->pane.bottom - window->pane.top) - 0x0f, 0x8000U);
                    }
                }
            }
        }
        if ((int)column == g_iw_construct.hovered_column) {
            /* FUN_0043aee8 frames x in [cx - W/8 + 5, cx + W/8 - 5] and
               y in [top + 0x1a, bottom - 10], centred on the column. */
            RECT highlight = {
                center_x - pane_width / 8 + 5,
                window->pane.top + 0x1a,
                center_x + pane_width / 8 - 5,
                window->pane.bottom - 10
            };
            /* FUN_0042dd0f(1) = DAT_0049e140[1]: palette index 1. */
            HBRUSH brush = CreateSolidBrush(g_island_palette[1]);
            FrameRect(dc, &highlight, brush);
            DeleteObject(brush);
        }
    }
    if (g_iw_construct.cycle_button_visible && cycle_window != NULL) {
        draw_sprite(dc, &g_build_cycle_art, (uint32_t)cycle_window->shape_frame,
                    cycle_window->pane.left, cycle_window->pane.top);
    }

    draw_sprite(dc, &g_temp_hole_art, (uint32_t)info_window->shape_frame,
                info_window->pane.left, info_window->pane.top);
    info_item = g_iw_construct_info.item_id < 0 ? NULL : pad_catalog_find(
        &g_pad_catalog, (uint16_t)(g_iw_construct_info.item_id +
        (int32_t)g_game_session.config.selected_tribe * 16));
    if (info_item != NULL) {
        uint16_t item_id = info_item->item_id;
        if (item_id < PAD_CATALOG_MAX_ITEMS &&
            g_building_art[item_id].frame_count != 0) {
            (void)draw_building_preview(dc, item_id,
                (uint8_t)g_game_session.config.selected_tribe,
                info_window->pane.left +
                    (info_window->pane.right - info_window->pane.left) - 0x37,
                info_window->pane.top + 0x55, 0x10000U);
        }
        if (item_id < g_pad_catalog.item_count && info_item->building_tone_cost > 0) {
            int cost_frame = info_item->building_tone_cost - 1;
            if (cost_frame > 0x31) cost_frame = 0x31;
            if ((uint32_t)cost_frame < g_bildtone_art.frame_count) {
                draw_sprite(dc, &g_bildtone_art, (uint32_t)cost_frame,
                            info_window->pane.left + 0x2d,
                            info_window->pane.top + 0x4b);
            }
            {
                /* FUN_0043b369 also prints the cost with the "%d" format at
                   (0x25, 0x2d) (ev_16025862, ev_b8912db6). The text colour
                   is not decoded. */
                char cost_text[16];
                (void)snprintf(cost_text, sizeof(cost_text), "%d",
                               (int)info_item->building_tone_cost);
                draw_bitmap_label(dc, cost_text,
                                  info_window->pane.left + 0x25,
                                  info_window->pane.top + 0x2d,
                                  RGB(185, 205, 220));
            }
        }
        if (item_id < PAD_CATALOG_MAX_ITEMS &&
            g_building_descriptions[item_id][0] != '\0') {
            /* FUN_0043b369 wraps through FUN_0043b333 (same body as
               FUN_0043954d): x = 6, right bound 173, first top = y + 1 + h
               from y = 0x58, pitch h + 1 (ev_ddd2a7e7, ev_342f06e5). */
            int text_width = 173 - 6;
            int text_height = info_window->pane.bottom - info_window->pane.top - 0x58;
            /* SMFONT (height 8), palette index 6: first top = 0x58 + 9. */
            int line_height = (int)g_small_font.height + 1;
            int max_lines = line_height > 0 ? text_height / line_height : 0;
            draw_wrapped_small_label(dc, g_building_descriptions[item_id],
                info_window->pane.left + 6,
                info_window->pane.top + 0x58 + line_height,
                text_width, max_lines, line_height, g_island_palette[6]);
        }
    }
}

static COLORREF island_location_color(const char *type)
{
    if (strcmp(type, "tone") == 0) return RGB(255, 202, 68);
    if (strcmp(type, "bridge") == 0) return RGB(61, 218, 248);
    if (strcmp(type, "special") == 0 || strcmp(type, "levhub") == 0) {
        return RGB(238, 95, 218);
    }
    if (strcmp(type, "feature") == 0 || strcmp(type, "feattrig") == 0) {
        return RGB(131, 237, 116);
    }
    return RGB(104, 174, 255);
}

/* Only explicit size tags use PAD.SHP. Class/subtype alone is insufficient:
   Tone pools and Leviathan shields share class-0/subtype-0 in the source. */
static int island_pad_group(const IslandLocation *location)
{
    return island_pad_size_group(location->kind);
}

static void draw_feature_reveal(HDC dc, const SpriteSheet *art,
                                int island_id, uint32_t frame_index,
                                int x, int y, int progress);
static int draw_island_leviathan_spawn_effect(
    HDC dc, const GameRuntimeLocation *location,
    const BuildingRenderItem *item, int x, int y, int full_reveal);

/* FUN_00411478 (site flag 0x200): dithered shimmer over a rectangle around the
   site, seeded with DAT_00618e44 >> 1. Colours are the palette entries nearest
   to (30,30,30) and (46,46,46) on a 0..63 scale plus palette index 1
   (FUN_004108fa/FUN_0042dd0f). The native palette is filled at runtime, so
   the island palette stands in for it. Writes keep the native order, including
   the copy of the just-written neighbour pixel. */
static void draw_site_shimmer(HDC dc, int left, int top, int right, int bottom,
                              uint32_t seed)
{
    static const uint8_t first[7] = {0, 1, 1, 2, 1, 1, 0};
    static const uint8_t second[7] = {4, 4, 0, 1, 0, 4, 4};
    COLORREF colors[3];
    uint32_t state = 0xdefeca35U;
    uint8_t index;
    int x;
    int y;
    int c;
    static const int gray[2] = {30, 46};

    for (c = 0; c < 2; ++c) {
        int level = gray[c] * 255 / 63;
        colors[c] = RGB(level, level, level);
        if (island_palette_lookup_nearest(&g_island_palette_lookup,
                (uint32_t)RGB(level, level, level) & UINT32_C(0x00ffffff),
                &index)) colors[c] = g_island_palette[index];
    }
    colors[2] = g_island_palette[1];
    for (y = top; y <= bottom; y += 2) {
        for (x = left; x <= right; x += 2) {
            uint32_t u = (state + seed + (uint32_t)(x - left) +
                          (uint32_t)(y - top)) % 119U;
            state >>= 1;
            if (state < 0x40U) state += 0xdefeca35U;
            if (u >= 7U) continue;
            (void)SetPixel(dc, x, y, colors[first[u]]);
            if (second[u] != 4U) {
                (void)SetPixel(dc, x + 1, y, colors[second[u]]);
                (void)SetPixel(dc, x, y + 1, GetPixel(dc, x + 1, y));
                (void)SetPixel(dc, x, y - 1, GetPixel(dc, x - 1, y));
            }
        }
    }
}

/* FUN_0040bf98's +0x58 mode selects a FUN_00410bd2 stipple level for every
   layer: mode 1 (grabbed) dips and recovers, mode 2 (placed) fades in, mode 3
   (removed) fades out, from the +0x46 counter (0..15); level 8 is opaque. */
static int g_item_stipple_level = 8;

static int item_stipple_level(const GameRuntimeLocation *location)
{
    int counter = location->source_value_46;
    if (counter < 0) counter = 0;
    switch (location->source_value_58) {
    case 1: return counter < 8 ? 8 - counter / 2 : (counter - 8) / 2 + 4;
    case 2: return counter / 2;
    case 3: return 8 - counter / 2;
    default: return 8;
    }
}

static void draw_item_layer(HDC dc, const SpriteSheet *sheet, uint32_t frame,
                            int x, int y, uint32_t scale_16_16)
{
    if (g_item_stipple_level >= 8 || scale_16_16 != 0x10000U) {
        draw_sprite_scaled(dc, sheet, frame, x, y, scale_16_16);
        return;
    }
    draw_feature_reveal(dc, sheet, g_island_surface_id, frame, x, y,
                        g_item_stipple_level);
}

static int draw_runtime_item_scaled(HDC dc, const GameRuntimeLocation *runtime_location,
                                    int x, int y, uint32_t scale_16_16)
{
    int32_t raw_id;
    const BuildingRenderItem *item;
    const SpriteSheet *sheet;
    uint32_t frame;
    int destruction_origin_y = y;
    int drew = 0;

    if (runtime_location == NULL || (raw_id = runtime_location->record_value_10) <= 0 ||
        raw_id >= g_pad_catalog.item_count) return 0;
    item = building_render_find(&g_building_render_catalog, (uint16_t)raw_id);
    if (item == NULL || (unsigned int)raw_id >= PAD_CATALOG_MAX_ITEMS) return 0;
    sheet = &g_building_art[raw_id];
    if (sheet->frames == NULL || sheet->frame_count == 0) return 0;
    g_item_stipple_level = scale_16_16 == 0x10000U
        ? item_stipple_level(runtime_location) : 8;

    /* FUN_0040bf98 shifts the intact building downward after destruction
       tick 30; the CRUMBLE overlay remains anchored at its original position. */
    if ((runtime_location->source_flags & 0x080U) != 0 &&
        scale_16_16 == 0x10000U && runtime_location->source_value_48 > 0x1e) {
        int32_t fall_ticks = runtime_location->source_value_48 - 0x1e;
        y += fall_ticks + (fall_ticks * fall_ticks) / 0x28;
    }

    /* Flag 0x010 (set by FUN_004528ca at placement, cleared at +0x48 == 100)
       is the native placement ramp. Below tick 84 the solidpad frame recolors
       the ground under its silhouette through a haze table, then every later
       layer is shifted down by a decaying offset; later layers are blitted
       through the same table, whose level follows FUN_0040bf98's +0x48 rule.
       The type-1 "pool" variant, the +0x58 stipple levels and flag 0x100 are
       not ported. */
    if ((runtime_location->source_flags & 0x010U) != 0 &&
        scale_16_16 == 0x10000U) {
        int pose_ticks = runtime_location->source_value_48;
        int pose_selector = runtime_location->source_value_14 != 4 ? 1 : 0;
        int pose_level = pose_ticks < 16 ? pose_ticks / 2
                       : pose_ticks > 84 ? (100 - pose_ticks) / 2 : 7;
        if (pose_ticks >= 0 && pose_ticks <= 100) {
            if (pose_ticks < 84) {
                const PadCatalogItem *pose_pad = pad_catalog_find(
                    &g_pad_catalog, (uint16_t)raw_id);
                uint32_t pad_frame = pose_pad != NULL && pose_pad->size >= 0
                    ? (uint32_t)pose_pad->size : 0U;
                int remaining = 84 - pose_ticks;
                recolor_under_sprite(dc, &g_solidpad_art, pad_frame, x, y,
                                     pose_selector, pose_level);
                y += remaining < 8 ? (remaining * remaining) / 8
                                   : 2 * remaining - 8;
            }
            g_sprite_haze_selector = pose_selector;
            g_sprite_haze_level = pose_level;
        }
    }

    /* Flag 0x100: FUN_004106dd(1, level) haze table, level 0..3 from the
       +0x44 counter (0..999), applied to every later layer. The native setter
       of the flag is not identified, so this only shows once a writer exists. */
    if ((runtime_location->source_flags & 0x100U) != 0 &&
        scale_16_16 == 0x10000U && g_sprite_haze_level < 0) {
        int v = runtime_location->source_value_44;
        g_sprite_haze_selector = 1;
        g_sprite_haze_level = v < 20 ? v / 5 : 1000 - v < 20 ? (1000 - v) / 5 : 3;
    }
    /* FUN_0040bf98 draws the static/base item layer and then the CHUG layer.
       The source divides the object's +0x3a progress by CHUG speed. The menu
       timer is only a provisional source for that per-object counter. */
    if (item->base.present) {
        frame = building_render_base_frame_for_state(item,
                                                     runtime_location->source_capacity_4a,
                                                     runtime_location->source_flags);
        if (frame < sheet->frame_count) {
            draw_item_layer(dc, sheet, frame, x, y, scale_16_16);
            drew = 1;
        }
    }
    if (item->chug.present) {
        frame = building_render_chug_frame(item, runtime_location->chug_progress);
        if (frame < sheet->frame_count) {
            draw_item_layer(dc, sheet, frame, x, y, scale_16_16);
            drew = 1;
            /* Keep rendering later layers: GLYP is drawn after CHUG by
               FUN_0040bf98 and may be the visible top layer. */
        }
    }
    if (item->glyph.present) {
        frame = building_render_glyph_frame(item, runtime_location->glyph_progress);
        if (frame < sheet->frame_count) {
            draw_item_layer(dc, sheet, frame, x, y, scale_16_16);
            drew = 1;
        }
    }
    /* FUN_0040bf98's remaining item layers are data-driven too. INCI uses
       +0x3e; CONS uses +0x40 and flag 0x004; PROD uses +0x42 and flag 0x002.
       The animated PROD frame stays at the item anchor; only its separate
       threshold effect uses the descriptor offset. OCCU is gated by flag 8.
       Simulation ticks advance these counters from deliveries, production,
       placement and staff actions. */
    if (item->inci.present) {
        frame = building_render_inci_frame(item, runtime_location->inci_progress);
        if (frame < sheet->frame_count) {
            draw_item_layer(dc, sheet, frame, x, y, scale_16_16);
            drew = 1;
        }
    }
    if (item->cons.present) {
        frame = building_render_cons_frame(item,
            runtime_location->construction_progress,
            runtime_location->source_flags);
        if (frame < sheet->frame_count) {
            draw_item_layer(dc, sheet, frame, x, y, scale_16_16);
            drew = 1;
        }
    }
    if (item->prod.present) {
        BuildingRenderPoint prod_position =
            building_render_prod_frame_position(x, y);
        frame = building_render_prod_frame(item, runtime_location->production_progress,
                                           runtime_location->source_flags);
        if (frame < sheet->frame_count) {
            draw_item_layer(dc, sheet, frame, prod_position.x, prod_position.y,
                               scale_16_16);
            drew = 1;
        }
        /* FUN_0040bf98 draws the producer's resource marker at the PROD
           descriptor offset when its threshold is reached or output is pending. */
        {
            int resource_code = building_render_visible_resource_code(
                item, runtime_location->record_value_10, runtime_location->owner_id,
                runtime_location->production_progress,
                runtime_location->source_flags, runtime_location->record_value_24);
            const SpriteSheet *resource_art = resource_code == 1
                ? &g_bildtone_art : resource_code == 2
                ? &g_tone_crys_art : resource_code == 3
                ? &g_magctone_art : NULL;
            if (resource_art != NULL && resource_art->frame_count != 0) {
                BuildingRenderPoint effect_position =
                    building_render_prod_threshold_position(item, x, y);
                draw_sprite_scaled(dc, resource_art, 0, effect_position.x,
                                   effect_position.y, scale_16_16);
                drew = 1;
            }
        }
        /* FUN_0040bf98 reveals the linked type-4 floater at item 6's PROD
           output point before overlaying the late-production building frame. */
        if (scale_16_16 == 0x10000U &&
            runtime_location->renderer_class == 1 &&
            runtime_location->record_value_10 == 6 &&
            (runtime_location->source_flags & 0x002U) != 0) {
            if (draw_island_leviathan_spawn_effect(
                    dc, runtime_location, item, x, y, 1))
                drew = 1;
            if (frame > 0x17U && frame < 0x27U &&
                frame + 0x13U < sheet->frame_count) {
                draw_sprite(dc, sheet, frame + 0x13U, x, y);
                drew = 1;
            }
        }
        /* FUN_0040bf98 reveals V-NSUPP frame 0 through a stipple mask while
           class-1 item 9 is running its PROD cycle. */
        if (scale_16_16 == 0x10000U && runtime_location->renderer_class == 1 &&
            runtime_location->record_value_10 == 9 &&
            (runtime_location->source_flags & 0x002U) != 0 &&
            draw_island_leviathan_spawn_effect(
                dc, runtime_location, item, x, y, 1)) {
            drew = 1;
        }
        if (scale_16_16 == 0x10000U && runtime_location->renderer_class == 1 &&
            runtime_location->record_value_10 == 9 &&
            (runtime_location->source_flags & 0x002U) != 0 &&
            g_leviathan_reveal_art.frame_count != 0) {
            uint32_t prod_duration = building_render_prod_duration(item);
            if (prod_duration != 0U) {
                uint64_t mask_progress =
                    ((uint64_t)runtime_location->production_progress * 15U) /
                    prod_duration + 1U;
                if (mask_progress > 8U && mask_progress < 16U)
                    mask_progress = 16U - mask_progress;
                if (mask_progress > 0U && mask_progress < 16U) {
                    if (mask_progress >= 8U) {
                        draw_sprite(dc, &g_leviathan_reveal_art, 0, x + 1,
                                    y - 0x5a);
                    } else {
                        draw_feature_reveal(dc, &g_leviathan_reveal_art,
                            g_island_surface_id, 0, x + 1, y - 0x5a,
                            (int)mask_progress);
                    }
                    drew = 1;
                }
            }
        }
        if (scale_16_16 == 0x10000U && runtime_location->renderer_class == 1 &&
            runtime_location->record_value_10 == 8 &&
            (runtime_location->source_flags & 0x002U) != 0 &&
            draw_island_leviathan_spawn_effect(dc, runtime_location, item, x, y, 0)) {
            drew = 1;
        }
    }
    if (item->occu.present && (runtime_location->source_flags & 8U) != 0) {
        frame = (uint32_t)item->occu.first_frame - 1U;
        if (frame < sheet->frame_count) {
            draw_item_layer(dc, sheet, frame, x, y, scale_16_16);
            drew = 1;
        }
    }
    if (item->barg.present) {
        frame = building_render_barg_frame(item, runtime_location->barg_progress);
        if (frame < sheet->frame_count) {
            draw_item_layer(dc, sheet, frame, x, y, scale_16_16);
            drew = 1;
        }
    }
    g_sprite_haze_level = -1;
    g_item_stipple_level = 8;
    if ((runtime_location->source_flags & 0x200U) != 0 &&
        scale_16_16 == 0x10000U) {
        uint32_t seed = g_game_session.simulation_tick >> 1;
        if (runtime_location->renderer_class == 1)
            draw_site_shimmer(dc, x - 50, y - 20, x + 50, y + 20, seed);
        else
            draw_site_shimmer(dc, x - 20, y - 50, x + 20, y, seed);
        drew = 1;
    }
    /* FUN_0040bf98 draws CRUMBLE after the item's data layers on the full-size
       in-world path. The overlay runs for flag 0x080 through the destruction
       timer and uses a nine-frame band for each pad size (class 1 uses band 4). */
    if ((runtime_location->source_flags & 0x080U) != 0 &&
        scale_16_16 == 0x10000U && g_crumble_art.frames != NULL) {
        const PadCatalogItem *pad_item = pad_catalog_find(
            &g_pad_catalog, (uint16_t)raw_id);
        int8_t item_size = pad_item == NULL ? -1 : pad_item->size;
        frame = building_render_crumble_frame(runtime_location->renderer_class,
            item_size, runtime_location->source_value_48);
        if (frame < g_crumble_art.frame_count) {
            draw_sprite(dc, &g_crumble_art, frame, x, destruction_origin_y);
            drew = 1;
        }
    }
    return drew;
}

static int draw_runtime_item(HDC dc, const GameRuntimeLocation *runtime_location,
                             int x, int y)
{
    return draw_runtime_item_scaled(dc, runtime_location, x, y, 0x10000U);
}

/* Resolve the map sprite independently from the pad catalog shape. PIT_Object
   (runtime ID 1) stores its collectible shape/frame selector in +0x24; the
   source renderer maps values 5..33 to TRIGGERS frames 0..28. Ordinary loose
   inventory items use their runtime item ID for that same sheet. */
static int ground_item_icon_frame(const GameRuntimeLocation *runtime_location,
                                  uint32_t *frame_index)
{
    const SpriteFrame *frame;
    int32_t item_id;
    uint32_t resolved_frame;

    if (runtime_location == NULL || frame_index == NULL) return 0;
    item_id = runtime_location->record_value_10;
    if (item_id == 1) {
        int32_t shape = runtime_location->record_value_24;
        if (shape < GAME_INVENTORY_ITEM_FIRST_ID ||
            shape >= GAME_INVENTORY_ITEM_FIRST_ID + GAME_INVENTORY_ITEM_COUNT) return 0;
        resolved_frame = (uint32_t)(shape - GAME_INVENTORY_ITEM_FIRST_ID);
    } else {
        if (item_id < GAME_INVENTORY_ITEM_FIRST_ID ||
            item_id >= GAME_INVENTORY_ITEM_FIRST_ID + GAME_INVENTORY_ITEM_COUNT) return 0;
        resolved_frame = (uint32_t)(item_id - GAME_INVENTORY_ITEM_FIRST_ID);
    }
    if (resolved_frame >= g_inventory_item_art.frame_count) return 0;
    frame = &g_inventory_item_art.frames[resolved_frame];
    if (frame->bitmap == NULL) return 0;
    *frame_index = resolved_frame;
    return 1;
}

/* Use the inventory sprite only when an item has no drawable building SHP.
   Drawing it over the building creates a second, mismatched image. */
static int draw_ground_item_icon(HDC dc,
                                 const GameRuntimeLocation *runtime_location,
                                 int x, int y)
{
    uint32_t frame_index;
    if (!ground_item_icon_frame(runtime_location, &frame_index)) return 0;
    draw_sprite(dc, &g_inventory_item_art, frame_index, x, y);
    return 1;
}

/* Occupied runtime records without a drawable SHP need a neutral marker when
   no inventory icon exists (the normal icon path handles IDs 5..33). */
static void draw_ground_item_fallback(HDC dc,
                                      const GameRuntimeLocation *runtime_location,
                                      int x, int y)
{
    uint32_t frame_index;
    if (runtime_location == NULL) return;
    if (ground_item_icon_frame(runtime_location, &frame_index)) return;

    /* Keep a neutral marker only for occupied records with no known frame. */
    {
        HPEN outline = CreatePen(PS_SOLID, 1, RGB(96, 62, 24));
        HBRUSH fill = CreateSolidBrush(RGB(244, 197, 77));
        HGDIOBJ previous_pen;
        HGDIOBJ previous_brush;
        if (outline == NULL || fill == NULL) {
            if (outline != NULL) DeleteObject(outline);
            if (fill != NULL) DeleteObject(fill);
            return;
        }
        previous_pen = SelectObject(dc, outline);
        previous_brush = SelectObject(dc, fill);
        Ellipse(dc, x - 6, y - 12, x + 7, y + 1);
        MoveToEx(dc, x, y - 11, NULL);
        LineTo(dc, x, y);
        SelectObject(dc, previous_brush);
        SelectObject(dc, previous_pen);
        DeleteObject(fill);
        DeleteObject(outline);
    }
}

/* FUN_0040d3e1 builds a temporary default item and calls FUN_0040bf98 with
   animation disabled and the requested scale. This shows every declared
   static/idle layer, rather than drawing the asset's frame zero in isolation. */
static int draw_building_preview(HDC dc, uint16_t item_id, uint8_t player_slot,
                                 int x, int y, uint32_t scale_16_16)
{
    GameRuntimeLocation preview;
    memset(&preview, 0, sizeof(preview));
    preview.record_value_10 = item_id;
    preview.owner_id = player_slot;
    preview.source_flags = 0x410U;
    preview.animation_rate = 1;
    return draw_runtime_item_scaled(dc, &preview, x, y, scale_16_16);
}

static int feature_reveal_pixel(uint8_t pattern, int x, int origin_x)
{
    int high = ((int)(int8_t)pattern >> 4) & 0x0f;
    int low = pattern & 0x0f;
    int phase = (origin_x + x) & 3;
    int visible = 0;
    if (low == 0) return 0;
    if (low == 4) return 1;
    if ((pattern & 2U) != 0 && ((phase - high) & 1) == 0) visible = 1;
    if ((pattern & 1U) != 0 &&
        phase == ((high + (low == 3)) & 3)) visible = 1;
    return visible;
}

/* FUN_00410bd2 applies DAT_0049b444's 4x4 reveal mask for progress 1..7.
   Cache local-coordinate clip regions by island, stage, and horizontal
   phase; the feature art does not change during a session, so scrolling only
   selects one of four prebuilt GDI regions. */
static HRGN feature_reveal_region(int island_id, int progress,
                                  int width, int height,
                                  int origin_x, int origin_y)
{
    static const uint8_t masks[8][4] = {
        {0x00, 0x00, 0x00, 0x00},
        {0x01, 0x00, 0x21, 0x00},
        {0x02, 0x00, 0x02, 0x00},
        {0x02, 0x11, 0x02, 0x31},
        {0x02, 0x12, 0x02, 0x12},
        {0x03, 0x12, 0x23, 0x12},
        {0x04, 0x12, 0x04, 0x12},
        {0x04, 0x13, 0x04, 0x33}
    };
    static HRGN regions[15][7][4];
    static int cached_width[15][7][4];
    static int cached_height[15][7][4];
    static int cached_origin_phase[15][7][4];
    RGNDATA *region_data;
    RGNDATAHEADER *header;
    RECT *rects;
    HRGN region;
    size_t rect_count = 0;
    size_t rect_bytes;
    size_t data_bytes;
    int mask_stage;
    int stage_index;
    int x_phase_index;
    int y;
    int min_x = width;
    int min_y = height;
    int max_x = 0;
    int max_y = 0;
    int origin_x_phase = origin_x & 3;
    int origin_phase = origin_y & 3;

    if (island_id < 0 || island_id >= 15 || progress < 1 || progress > 7 ||
        width <= 0 || height <= 0) return NULL;
    stage_index = progress - 1;
    x_phase_index = origin_x_phase;
    region = regions[island_id][stage_index][x_phase_index];
    if (region != NULL &&
        cached_width[island_id][stage_index][x_phase_index] == width &&
        cached_height[island_id][stage_index][x_phase_index] == height &&
        cached_origin_phase[island_id][stage_index][x_phase_index] == origin_phase)
        return region;

    mask_stage = progress;
    for (y = 0; y < height; ++y) {
        uint8_t pattern = masks[mask_stage][(origin_y + y) & 3];
        int x = 0;
        while (x < width) {
            int begin;
            if (!feature_reveal_pixel(pattern, x, origin_x)) {
                ++x;
                continue;
            }
            begin = x++;
            while (x < width && feature_reveal_pixel(pattern, x, origin_x)) ++x;
            ++rect_count;
            if (begin < min_x) min_x = begin;
            if (y < min_y) min_y = y;
            if (x > max_x) max_x = x;
            if (y + 1 > max_y) max_y = y + 1;
        }
    }
    if (rect_count == 0) {
        region = CreateRectRgn(0, 0, 0, 0);
        if (region == NULL) return NULL;
        goto cache_region;
    }
    if (rect_count > (SIZE_MAX - sizeof(RGNDATAHEADER)) / sizeof(RECT))
        return NULL;
    rect_bytes = rect_count * sizeof(RECT);
    data_bytes = sizeof(RGNDATAHEADER) + rect_bytes;
    if (rect_count > UINT32_MAX || rect_bytes > UINT32_MAX ||
        data_bytes > UINT32_MAX) return NULL;
    region_data = (RGNDATA *)malloc(data_bytes);
    if (region_data == NULL) return NULL;
    header = (RGNDATAHEADER *)region_data;
    header->dwSize = sizeof(RGNDATAHEADER);
    header->iType = RDH_RECTANGLES;
    header->nCount = (DWORD)rect_count;
    header->nRgnSize = (DWORD)rect_bytes;
    header->rcBound.left = min_x;
    header->rcBound.top = min_y;
    header->rcBound.right = max_x;
    header->rcBound.bottom = max_y;
    rects = (RECT *)region_data->Buffer;
    rect_count = 0;
    for (y = 0; y < height; ++y) {
        uint8_t pattern = masks[mask_stage][(origin_y + y) & 3];
        int x = 0;
        while (x < width) {
            int begin;
            if (!feature_reveal_pixel(pattern, x, origin_x)) {
                ++x;
                continue;
            }
            begin = x++;
            while (x < width && feature_reveal_pixel(pattern, x, origin_x)) ++x;
            rects[rect_count].left = begin;
            rects[rect_count].top = y;
            rects[rect_count].right = x;
            rects[rect_count].bottom = y + 1;
            ++rect_count;
        }
    }
    region = ExtCreateRegion(NULL, (DWORD)data_bytes, region_data);
    free(region_data);
    if (region == NULL) return NULL;

cache_region:
    if (regions[island_id][stage_index][x_phase_index] != NULL)
        DeleteObject(regions[island_id][stage_index][x_phase_index]);
    regions[island_id][stage_index][x_phase_index] = region;
    cached_width[island_id][stage_index][x_phase_index] = width;
    cached_height[island_id][stage_index][x_phase_index] = height;
    cached_origin_phase[island_id][stage_index][x_phase_index] = origin_phase;
    return region;
}

static void draw_feature_reveal(HDC dc, const SpriteSheet *art,
                                int island_id, uint32_t frame_index,
                                int x, int y, int progress)
{
    const SpriteFrame *frame;
    HRGN region;
    int destination_x;
    int destination_y;
    if (art == NULL || frame_index >= art->frame_count || progress < 1 ||
        progress > 7) return;
    frame = &art->frames[frame_index];
    if (frame->bitmap == NULL) return;
    destination_x = x + frame->x_offset;
    destination_y = y + frame->y_offset;
    region = feature_reveal_region(island_id, progress, frame->width,
                                   frame->height, destination_x,
                                   destination_y);
    if (region == NULL) return;
    if (SaveDC(dc) == 0) return;
    OffsetRgn(region, destination_x, destination_y);
    (void)ExtSelectClipRgn(dc, region, RGN_AND);
    draw_sprite(dc, art, frame_index, x, y);
    OffsetRgn(region, -destination_x, -destination_y);
    RestoreDC(dc, -1);
}

/* FUN_0040b345 draws feature layers at fixed world coordinates from the
   island-window origin. Pair bits come from the live object's +0x4a mask;
   retain the layout special value for the pre-session/static presentation. */
static void draw_island_feature(HDC dc, int island_id, const IslandLocation *site,
                                const GameRuntimeLocation *runtime_site,
                                int world_origin_x, int world_origin_y)
{
    uint16_t feature_bits = (uint16_t)site->special_value;
    if (runtime_site != NULL)
        feature_bits |= (uint16_t)runtime_site->source_capacity_4a;
    const int bit0 = (feature_bits & 1U) != 0;
    const int bit1 = (feature_bits & 2U) != 0;
    const SpriteSheet *art = &g_island_feature_art;

#define FEATURE_FRAME(frame, dx, dy) \
    do { if ((uint32_t)(frame) < art->frame_count) \
        draw_sprite(dc, art, (uint32_t)(frame), world_origin_x + (dx), \
                    world_origin_y + (dy)); } while (0)
#define FEATURE_ACTIVE(frame, dx, dy) \
    do { \
        int reveal = (int)(runtime_site->charge_source_value_30 / 4U); \
        if (reveal >= 8) FEATURE_FRAME(frame, dx, dy); \
        else if (reveal > 0) draw_feature_reveal(dc, art, island_id, \
            (uint32_t)(frame), world_origin_x + (dx), world_origin_y + (dy), \
            reveal); \
    } while (0)

    switch (island_id) {
    case 0:
        FEATURE_FRAME(bit0 ? 2 : 0, 0x6b3, 100);
        FEATURE_FRAME(bit1 ? 3 : 1, 0x6b3, 100);
        break;
    case 1:
        if (bit0) FEATURE_FRAME(0, 0x11a, 0xe9);
        if (bit1) FEATURE_FRAME(1, 0x169, 0xf6);
        break;
    case 2:
        if (bit0) FEATURE_FRAME(0, 0x4c, 0);
        if (bit1) FEATURE_FRAME(1, 0x144, 0);
        break;
    case 3:
        if (bit0 || bit1) FEATURE_FRAME(0, 0x8f, 99);
        break;
    case 4:
        if (bit0) FEATURE_FRAME(0, 0x529, 0x8c);
        if (bit1) FEATURE_FRAME(1, 0x5c2, 0x90);
        break;
    case 5:
        if (bit0) FEATURE_FRAME(0, 0x2d4, 0xd5);
        if (bit1) FEATURE_FRAME(1, 0x33e, 0xd5);
        break;
    case 6:
        if (bit0) FEATURE_FRAME(0, 0x40, 0x6c);
        if (bit1) FEATURE_FRAME(1, 0xa0, 0x69);
        break;
    case 7:
        if (bit0) FEATURE_FRAME(0, 0x8f, 0xa2);
        if (bit1) FEATURE_FRAME(1, 0xf5, 0xa5);
        break;
    case 8:
        if (bit0) FEATURE_FRAME(0, 0x4a1, 0x43);
        if (bit1) FEATURE_FRAME(1, 0x51a, 0x9e);
        break;
    case 9:
        if (bit0) FEATURE_FRAME(0, 0x42a, 0x74);
        if (bit1) FEATURE_FRAME(1, 0x4d6, 0x7f);
        break;
    case 10:
        if (bit0) FEATURE_FRAME(0, 0x421, 0x87);
        if (bit1) FEATURE_FRAME(1, 0x43b, 0x18);
        break;
    case 11:
        FEATURE_FRAME(0, 0x57b, 0xf0);
        if (bit0) FEATURE_FRAME(1, 0x57b, 0xf0);
        if (bit1) FEATURE_FRAME(2, 0x57b, 0xf0);
        break;
    case 12:
        if (bit0) FEATURE_FRAME(0, 0x4e7, 0xa0);
        if (bit1) FEATURE_FRAME(1, 0x4e7, 0xa0);
        break;
    case 13:
        if (bit0 || bit1) FEATURE_FRAME(0, 0x463, 0x82);
        break;
    case 14:
    default:
        break;
    }

    /* FUN_00410bd2 switches to a normal frame blit once the active feature's
       +0x30 counter reaches 32 (the caller passes +0x30 / 4). */
    if (runtime_site != NULL && (runtime_site->source_flags & 1U) != 0) {
        switch (island_id) {
        case 0: FEATURE_ACTIVE(4, 0x6b3, 100); break;
        case 1: FEATURE_ACTIVE(2, 0x131, 0xae); break;
        case 2: FEATURE_ACTIVE(2, 0x2d, 0); break;
        case 3: FEATURE_ACTIVE(1, 0x3e, 0); break;
        case 4: FEATURE_ACTIVE(2, 0x4a5, 0); break;
        case 5: FEATURE_ACTIVE(2, 0x25e, 0x23); break;
        case 6: FEATURE_ACTIVE(2, 0x26, 9); break;
        case 7: FEATURE_ACTIVE(2, 0x61, 0); break;
        case 8: FEATURE_ACTIVE(2, 0x47b, 0x33); break;
        case 9: FEATURE_ACTIVE(2, 0x460, 0); break;
        case 10: FEATURE_ACTIVE(2, 0x3bc, 0x60); break;
        case 11: FEATURE_ACTIVE(3, 0x58e, 0x75); break;
        case 12: FEATURE_ACTIVE(2, 0x4e7, 0xa0); break;
        case 13: FEATURE_ACTIVE(2, 0x463, 0x82); break;
        case 14: FEATURE_ACTIVE(0, 0x45d, 0); break;
        default: break;
        }
    }
#undef FEATURE_ACTIVE
#undef FEATURE_FRAME
}

/* FUN_00440567 tail block (both Hall variants, ev_671a1431...): ACTICON frames
   chosen by the building item and the owner's feature mask G. Which of the
   bits {0,1,3}/{6,7,5}/{10,11,9} draw, and whether x advances only on a drawn
   icon, is an interpretation of the pseudocode; the owner-parity test is
   observed but unexplained. */
/* Port records keep owner-specific item IDs (base + owner * 16); native Hall
   text and icon predicates test the base ID. */
static int32_t location_base_item_id(const GameRuntimeLocation *location)
{
    int32_t item = location->record_value_10;
    if (location->owner_id >= 0 && location->owner_id < GAME_START_PLAYER_COUNT)
        item -= location->owner_id * 16;
    return item;
}

static void draw_hall_feature_icons(HDC dc, const WindowTemplate *info,
                                    int32_t item, int32_t owner)
{
    static const unsigned int bits_2c[3] = {0U, 1U, 3U};
    static const unsigned int bits_2d[3] = {6U, 7U, 5U};
    static const unsigned int bits_2e[3] = {10U, 11U, 9U};
    const unsigned int *bits = NULL;
    unsigned int mask;
    int x = 178;
    unsigned int k;

    if (info == NULL || !g_game_session_valid || owner < 0 ||
        owner >= GAME_START_PLAYER_COUNT) return;
    mask = g_game_session.economy[owner].special_feature_island_mask;
    if (item == 0x2c) bits = bits_2c;
    else if (item == 0x2d) bits = bits_2d;
    else if (item == 0x2e) bits = bits_2e;
    if (bits != NULL) {
        for (k = 0; k < 3U; ++k) {
            if ((mask >> bits[k]) & 1U) {
                draw_sprite(dc, &g_activation_icon_art, bits[k],
                            info->pane.left + x, info->pane.top + 1);
                x += 10;
            }
        }
        if (((owner & 1) != 0) == (item == 0x2c) && (mask & 4U) != 0) {
            draw_sprite(dc, &g_activation_icon_art, 2U,
                        info->pane.left + x, info->pane.top + 1);
        }
        if ((mask & 0x1000U) != 0) {
            draw_sprite(dc, &g_activation_icon_art, 12U,
                        info->pane.left + 16, info->pane.top + 21);
        }
    } else if (item == 0x2f) {
        if ((mask & 0x100U) != 0) {
            draw_sprite(dc, &g_activation_icon_art, 8U,
                        info->pane.left + 43, info->pane.top + 21);
        }
    } else if (item == 0x2a) {
        if ((mask & 0x2000U) != 0) {
            draw_sprite(dc, &g_activation_icon_art, 13U,
                        info->pane.left + 63, info->pane.top + 14);
        }
        if ((mask & 0x10U) != 0) {
            draw_sprite(dc, &g_activation_icon_art, 4U,
                        info->pane.left + 173, info->pane.top + 16);
        }
    }
}

/* FUN_004118df call at 0x440b2a: TASKICON frame 8 at (x,20), 6x55, inset 2,
   vertical (dir 1): interior x+2..x+4 by y+22..y+73, filled from the bottom
   by ftol(51 * stock / cap), the remaining top part painted with palette
   index 0. cap = FUN_0045cd27 = 50 + 25 * L, L = short +0x4a of the
   building's own location entry (taken as source_capacity_4a: interpretation;
   the 2 px interior width follows the pushed arguments and has no visual
   cross-check). */
static void draw_building_stock_gauge(HDC dc, const WindowTemplate *info,
                                      int x, uint16_t stock, int16_t level)
{
    const int interior_height = 55 - 4;
    int32_t capacity = (int32_t)level * 25 + 50;
    int filled;
    int gauge_x = info->pane.left + x;
    int gauge_y = info->pane.top + 20;

    if (g_task_icon_art.frame_count <= 8U || capacity <= 0) return;
    filled = (int32_t)stock >= capacity ? interior_height :
        (int)((int64_t)interior_height * stock / capacity);
    draw_sprite(dc, &g_task_icon_art, 8U, gauge_x, gauge_y);
    if (filled < interior_height) {
        fill_rect(dc, gauge_x + 2, gauge_y + 2, gauge_x + 4,
                  gauge_y + 2 + (interior_height - filled),
                  g_island_palette[0]);
    }
}

/* FUN_0041179e (calls 0x440d96/0x440eac): 3x55 vertical segment, filled from
   the bottom by ftol(55 * ratio), outlined in palette index 1 with the
   interior (1 px inset) in `colour`. Nothing is drawn for a zero-length fill. */
static void draw_spell_cost_bar(HDC dc, int left, int top, int cost,
                                int32_t capacity, int colour)
{
    const int height = 55;
    int filled;
    int bar_top;
    if (capacity <= 0 || cost <= 0) return;
    filled = cost >= capacity ? height : (int)((int64_t)height * cost / capacity);
    if (filled <= 0) return;
    bar_top = top + height - filled;
    fill_rect(dc, left, bar_top, left + 3, top + height, g_island_palette[1]);
    if (filled > 2) {
        fill_rect(dc, left + 1, bar_top + 1, left + 2, top + height - 1,
                  g_island_palette[colour]);
    }
}

/* FUN_00440567 draws these only for item 0x2f while this+0x74 >= 0 (spell
   row s): bar 1 at x=15 is CryCost (spells.txt +0x24) against the site stock
   +0x2a, bar 2 at x=42 is MagCost (+0x22, x2/3 when the owner's mask bit 0x100
   is set) against +0x2c; both over 50 + 25 * L. Colour 2 when the cost exceeds
   the stock, otherwise 4. The pointer-hover trigger for s is interpreted
   from message 0x350d's spell-button context. */
static void draw_spell_cost_bars(HDC dc, const WindowTemplate *info,
                                 const GameRuntimeLocation *location)
{
    uint16_t magic_cost;
    uint16_t crystal_cost;
    int32_t capacity = (int32_t)location->source_capacity_4a * 25 + 50;
    int owner = location->owner_id;
    int magic;

    if (g_hovered_spell_kind < 0 ||
        !game_session_cast_kind_costs(g_hovered_spell_kind, &magic_cost,
                                      &crystal_cost)) return;
    magic = magic_cost;
    if (owner >= 0 && owner < GAME_START_PLAYER_COUNT &&
        (g_game_session.economy[owner].special_feature_island_mask & 0x100U))
        magic = magic * 2 / 3;
    draw_spell_cost_bar(dc, info->pane.left + 15, info->pane.top + 20,
        crystal_cost, capacity,
        (int)crystal_cost > (int)location->resource_stock[1] ? 2 : 4);
    draw_spell_cost_bar(dc, info->pane.left + 42, info->pane.top + 20,
        magic, capacity,
        magic > (int)location->resource_stock[2] ? 2 : 4);
}

/* Non-summary variant (P+0x18 != -1): bldgage frame 0 at (W/2-18, 0), 36x8,
   inset 2, filled by +0x34 over FUN_00450978's maximum unless the item is
   0x2a or the owner is 4; tonecrys frame 4 at (11,17); for item 0x2f also
   magctone frame 4 at (38,17). The taskicon stock bars at (8,20)/(35,20) need
   the staff-record capacity (FUN_0045cd27) and are not ported. */
static void draw_building_info_extras(HDC dc, const WindowTemplate *info,
                                      const GameRuntimeLocation *location,
                                      uint8_t island_index,
                                      uint16_t location_index)
{
    int16_t current;
    int16_t maximum;
    int32_t item = location_base_item_id(location);
    int base = (info->pane.right - info->pane.left) / 2;

    if (location->source_location_slot_18 == -1) return;
    if (item != 0x2a && location->owner_id != 4 &&
        g_building_gauge_art.frame_count != 0 &&
        game_session_repair_location_values(&g_game_session, &g_pad_catalog,
                island_index, location_index, &current, &maximum) &&
        maximum > 0) {
        int gauge_x = info->pane.left + base - 18;
        int gauge_y = info->pane.top;
        int inner_width = 36 - 4;
        int filled = current <= 0 ? 0 :
            (int)((long)inner_width * current / maximum);
        if (filled > inner_width) filled = inner_width;
        draw_sprite(dc, &g_building_gauge_art, 0U, gauge_x, gauge_y);
        if (filled < inner_width) {
            fill_rect(dc, gauge_x + 2 + filled, gauge_y + 2,
                      gauge_x + 2 + inner_width, gauge_y + 6,
                      g_island_palette[0]);
        }
    }
    /* BILDICON dots: N = source +0x60 (the 0..9 instance id FUN_0045ee26
       assigns among same-item rows, ev_a4a51711), frame clamp(owner+4,4,7),
       x0 = W/2-40, y = 5, step 8, five per row. Reading N as a count of
       dots is literal from the loop; the numbering meaning is inferred. */
    {
        int icon_frame = location->owner_id + 4;
        int dot;
        int dots = location->source_category_slot_60;
        if (icon_frame < 4) icon_frame = 4;
        if (icon_frame > 7) icon_frame = 7;
        for (dot = 0; dot < dots; ++dot) {
            draw_sprite(dc, &g_building_number_art, (uint32_t)icon_frame,
                        info->pane.left + base - 40 + 8 * (dot % 5),
                        info->pane.top + 5 + 8 * (dot / 5));
        }
    }
    if (g_tone_crys_art.frame_count > 4U) {
        draw_sprite(dc, &g_tone_crys_art, 4U,
                    info->pane.left + 11, info->pane.top + 17);
    }
    draw_building_stock_gauge(dc, info, 8, location->resource_stock[1],
                              location->source_capacity_4a);
    if (item == 0x2f && g_magctone_art.frame_count > 4U) {
        draw_sprite(dc, &g_magctone_art, 4U,
                    info->pane.left + 38, info->pane.top + 17);
        draw_building_stock_gauge(dc, info, 35, location->resource_stock[2],
                                  location->source_capacity_4a);
        draw_spell_cost_bars(dc, info, location);
    }
    draw_hall_feature_icons(dc, info, item, location->owner_id);
}

static void draw_hall_stock_summary(HDC dc, int hall_player,
                                    const GameRuntimeIsland *island)
{
    static const SpriteSheet *const resource_sheets[GAME_RESOURCE_TYPE_COUNT] = {
        &g_bildtone_art, &g_tone_crys_art, &g_magctone_art
    };
    const WindowTemplate *info;
    const GameRuntimeLocation *hall;
    RECT pane;
    int saved_dc;
    unsigned int resource;

    if (hall_player < 0 || selected_hall_player() != hall_player ||
        island == NULL ||
        g_island_panel_mode != WINDOW_ISLAND_PANEL_GENERAL ||
        g_selected_location < 0 ||
        (uint16_t)g_selected_location >= island->location_count) return;
    info = window_catalog_find(&g_window_catalog, "IWLocInfo", 3);
    if (info == NULL || g_temp_hole_art.frame_count <= 1U) return;

    hall = &island->locations[g_selected_location];
    /* FUN_00440567 draws this summary only inside the P+0x18 == -1 branch
       when P+0x10 == 0x2a (ev_671a1431...). */
    if (hall->source_location_slot_18 != -1 ||
        location_base_item_id(hall) != 0x2a) return;
    pane.left = info->pane.left;
    pane.top = info->pane.top;
    pane.right = info->pane.right + 1;
    pane.bottom = info->pane.bottom + 1;
    saved_dc = SaveDC(dc);
    (void)IntersectClipRect(dc, pane.left, pane.top, pane.right, pane.bottom);
    /* The selected-location painter has already drawn IWLocInfo's background
       and the Hall's layered building sprite. Repainting the pane here erased
       that sprite; only update the economy content on top of it. */
    for (resource = 0; resource < GAME_RESOURCE_TYPE_COUNT; ++resource) {
        IslandHallResourceRow row;
        char amount[8];
        if (!island_panel_info_hall_resource_row(resource, &row)) continue;
        if (resource_sheets[resource]->frame_count > row.icon_frame) {
            draw_sprite(dc, resource_sheets[resource], row.icon_frame,
                        info->pane.left + row.icon_x,
                        info->pane.top + row.icon_y);
        }
        (void)snprintf(amount, sizeof(amount), "%d",
            (int)(int16_t)hall->resource_stock[resource]);
        draw_bitmap_label(dc, amount,
                          info->pane.left + row.amount_x,
                          info->pane.top + row.amount_y,
                          RGB(230, 238, 255));
    }
    draw_hall_feature_icons(dc, info, location_base_item_id(hall),
                            hall->owner_id);
    /* FUN_00440567 draws ACTICON frame i for each island i whose bit is set in
       DAT_00619242 + owner*0x14a0 (the remake's special_feature_island_mask),
       for i < DAT_006136b0 (runtime-written; taken as the island count, an
       assumption). The cursor starts at (220,1), steps x by 10 per index and
       wraps after i = 2, 5, 8 and 11; the i == 11 wrap uses x = 225. */
    {
        unsigned int icon_x = 220U;
        unsigned int icon_y = 1U;
        unsigned int i;
        uint16_t feature_mask =
            g_game_session.economy[hall_player].special_feature_island_mask;
        for (i = 0; i < (unsigned int)g_game_session.island_count; ++i) {
            if ((feature_mask >> (i & 31U)) & 1U) {
                draw_sprite(dc, &g_activation_icon_art, i,
                            info->pane.left + (int)icon_x,
                            info->pane.top + (int)icon_y);
            }
            icon_x += 10U;
            if (i == 2U || i == 5U || i == 8U || i == 11U) {
                icon_x = i == 11U ? 225U : 220U;
                icon_y += 10U;
            }
        }
    }
    {
        char population[96];
        char work_summary[96];
        char tone_surplus[96];
        unsigned int count;
        unsigned int total;
        unsigned int percentage;
        if (game_session_workstr_summary(&g_game_session,
                (uint8_t)hall_player, &count, &total, &percentage)) {
            (void)snprintf(population, sizeof(population), "%s %u",
                           g_hall_population_label, total);
            draw_bitmap_label(dc, population,
                              info->pane.left + 0xb6,
                              info->pane.top + 0x29,
                              RGB(230, 238, 255));
            /* WORKSTR is drawn unconditionally in the binary (no total > 0
               branch in the FUN_00440567 pseudocode). */
            (void)snprintf(work_summary, sizeof(work_summary),
                           "%s %u (%u%%)",
                           g_hall_work_label, count, percentage);
            draw_bitmap_label(dc, work_summary,
                              info->pane.left + 0xb6,
                              info->pane.top + 0x33,
                              RGB(230, 238, 255));
        }
        (void)snprintf(tone_surplus, sizeof(tone_surplus),
            "%s %ld", g_hall_surplus_label,
            (long)g_game_session.economy[hall_player].source_maintenance_budget);
        draw_bitmap_label(dc, tone_surplus,
                          info->pane.left + 5,
                          info->pane.top + 4,
                          RGB(230, 238, 255));
    }
    RestoreDC(dc, saved_dc);
}
