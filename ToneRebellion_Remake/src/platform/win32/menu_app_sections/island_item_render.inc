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
        /* FUN_0043aee8 starts at pane_width/8 and advances pane_width/4. */
        int center_x = window->pane.left + pane_width / 8 +
                       pane_width * (int)column / IW_CONSTRUCT_ITEMS_PER_PAGE;
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
            int hit_width = pane_width + 1;
            RECT highlight = {
                window->pane.left + hit_width * (int)column /
                    IW_CONSTRUCT_ITEMS_PER_PAGE,
                window->pane.top + 0x1a,
                window->pane.left + hit_width * ((int)column + 1) /
                    IW_CONSTRUCT_ITEMS_PER_PAGE,
                window->pane.bottom - 10
            };
            HBRUSH brush = CreateSolidBrush(RGB(119, 199, 234));
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
        }
        if (item_id < PAD_CATALOG_MAX_ITEMS &&
            g_building_descriptions[item_id][0] != '\0') {
            int text_width = (info_window->pane.right - info_window->pane.left) - 0x4f;
            int text_height = info_window->pane.bottom - info_window->pane.top - 0x60;
            int line_height = (int)g_bitmap_font.height + 2;
            int max_lines = line_height > 0 ? text_height / line_height : 0;
            draw_wrapped_bitmap_label(dc, g_building_descriptions[item_id],
                info_window->pane.left + 10, info_window->pane.top + 0x58,
                text_width, max_lines, RGB(232, 236, 244));
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

static int draw_runtime_item_scaled(HDC dc, const GameRuntimeLocation *runtime_location,
                                    int x, int y, uint32_t scale_16_16)
{
    int32_t raw_id;
    const BuildingRenderItem *item;
    const SpriteSheet *sheet;
    uint32_t frame;
    int drew = 0;

    if (runtime_location == NULL || (raw_id = runtime_location->record_value_10) <= 0 ||
        raw_id >= g_pad_catalog.item_count) return 0;
    item = building_render_find(&g_building_render_catalog, (uint16_t)raw_id);
    if (item == NULL || (unsigned int)raw_id >= PAD_CATALOG_MAX_ITEMS) return 0;
    sheet = &g_building_art[raw_id];
    if (sheet->frames == NULL || sheet->frame_count == 0) return 0;

    /* FUN_0040bf98 draws the static/base item layer and then the CHUG layer.
       The source divides the object's +0x3a progress by CHUG speed. The menu
       timer is only a provisional source for that per-object counter. */
    if (item->base.present) {
        frame = building_render_base_frame_for_state(item, runtime_location->base_progress,
                                                     runtime_location->source_flags);
        if (frame < sheet->frame_count) {
            draw_sprite_scaled(dc, sheet, frame, x, y, scale_16_16);
            drew = 1;
        }
    }
    if (item->chug.present) {
        frame = building_render_chug_frame(item, runtime_location->chug_progress);
        if (frame < sheet->frame_count) {
            draw_sprite_scaled(dc, sheet, frame, x, y, scale_16_16);
            drew = 1;
            /* Keep rendering later layers: GLYP is drawn after CHUG by
               FUN_0040bf98 and may be the visible top layer. */
        }
    }
    if (item->glyph.present) {
        frame = building_render_glyph_frame(item, runtime_location->glyph_progress);
        if (frame < sheet->frame_count) {
            draw_sprite_scaled(dc, sheet, frame, x, y, scale_16_16);
            drew = 1;
        }
    }
    /* FUN_0040bf98's remaining item layers are data-driven too. INCI uses
       +0x3e; CONS uses +0x40 and flag 0x004; PROD uses +0x42 and flag 0x002.
       The animated PROD frame stays at the item anchor; only its separate
       threshold effect uses the descriptor offset. OCCU is gated by flag 8.
       Initial counters remain zero until their game events are ported. */
    if (item->inci.present) {
        frame = building_render_inci_frame(item, runtime_location->inci_progress);
        if (frame < sheet->frame_count) {
            draw_sprite_scaled(dc, sheet, frame, x, y, scale_16_16);
            drew = 1;
        }
    }
    if (item->cons.present) {
        frame = building_render_cons_frame(item, runtime_location->construction_progress,
                                           runtime_location->source_flags);
        if (frame < sheet->frame_count) {
            draw_sprite_scaled(dc, sheet, frame, x, y, scale_16_16);
            drew = 1;
        }
    }
    if (item->prod.present) {
        BuildingRenderPoint prod_position =
            building_render_prod_frame_position(x, y);
        frame = building_render_prod_frame(item, runtime_location->production_progress,
                                           runtime_location->source_flags);
        if (frame < sheet->frame_count) {
            draw_sprite_scaled(dc, sheet, frame, prod_position.x, prod_position.y,
                               scale_16_16);
            drew = 1;
        }
    }
    if (item->occu.present && (runtime_location->source_flags & 8U) != 0) {
        frame = (uint32_t)item->occu.first_frame - 1U;
        if (frame < sheet->frame_count) {
            draw_sprite_scaled(dc, sheet, frame, x, y, scale_16_16);
            drew = 1;
        }
    }
    if (item->barg.present) {
        frame = building_render_barg_frame(item, runtime_location->barg_progress);
        if (frame < sheet->frame_count) {
            draw_sprite_scaled(dc, sheet, frame, x, y, scale_16_16);
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

/* FUN_0040b345 draws feature layers at fixed world coordinates from the
   island-window origin. The object contributes its special-value bits. This
   renders only the static branch (object flag bit 0 clear); triggered and
   altitude-hazed variants depend on live game state. */
static void draw_island_feature(HDC dc, int island_id, const IslandLocation *site,
                                int world_origin_x, int world_origin_y)
{
    const int bit0 = (site->special_value & 1) != 0;
    const int bit1 = (site->special_value & 2) != 0;
    const SpriteSheet *art = &g_island_feature_art;

#define FEATURE_FRAME(frame, dx, dy) \
    do { if ((uint32_t)(frame) < art->frame_count) \
        draw_sprite(dc, art, (uint32_t)(frame), world_origin_x + (dx), \
                    world_origin_y + (dy)); } while (0)

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
#undef FEATURE_FRAME
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
    if (hall->source_location_slot_18 != -1) return;
    pane.left = info->pane.left;
    pane.top = info->pane.top;
    pane.right = info->pane.right + 1;
    pane.bottom = info->pane.bottom + 1;
    saved_dc = SaveDC(dc);
    (void)IntersectClipRect(dc, pane.left, pane.top, pane.right, pane.bottom);
    draw_sprite(dc, &g_temp_hole_art, 1, info->pane.left, info->pane.top);
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
            if (total > 0) {
                (void)snprintf(work_summary, sizeof(work_summary),
                               "%s %u (%u%%)",
                               g_hall_work_label, count, percentage);
                draw_bitmap_label(dc, work_summary,
                                  info->pane.left + 0xb6,
                                  info->pane.top + 0x33,
                                  RGB(230, 238, 255));
            }
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
