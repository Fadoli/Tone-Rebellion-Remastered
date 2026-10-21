static void draw_hall_info_panel(HDC dc, int panel_state)
{
    const WindowTemplate *panel;
    const char *text = NULL;
    char hover_text[256];
    int pane_width;
    int pane_height;
    int line_height;
    int max_lines;

    if (panel_state == WINDOW_ISLAND_PANEL_INVENTORY) {
        if (g_inventory_info_mode == ISLAND_PANEL_INFO_INVENTORY_DETAIL) {
            int detail_index = island_panel_info_inventory_detail_index(
                g_inventory_info_mode, g_hovered_inventory_item);
            if (detail_index >= 0)
                text = g_inventory_item_info_text[detail_index];
        } else {
            text = g_inventory_info_text;
        }
    } else if (panel_state == WINDOW_ISLAND_PANEL_GLYPHS) {
        if (g_hovered_glyph >= 0 && g_hovered_glyph < GAME_GLYPH_COUNT) {
            text = g_glyph_item_info_text[g_hovered_glyph];
        } else if (g_glyph_info_default) {
            text = g_glyph_info_text;
        }
    } else if (panel_state == WINDOW_ISLAND_PANEL_GENERAL) {
        const int hall_player = selected_hall_player();
        if (hall_player >= 0 && g_hovered_hall_stock >= 0 &&
            g_hovered_hall_stock < GAME_RESOURCE_TYPE_COUNT) {
            const unsigned int resource = (unsigned int)g_hovered_hall_stock;
            const unsigned int mode = g_game_session.economy[hall_player]
                .stock_mode[resource];
            const char *resource_name = g_task_category_text[resource];
            if (resource_name == NULL || resource_name[0] == '\0')
                resource_name = "RESOURCE";
            if (mode == 2U) {
                (void)snprintf(hover_text, sizeof(hover_text),
                    "%s\nREAPPRO AUTO\nCLIC : CHANGER LE MODE", resource_name);
            } else {
                (void)snprintf(hover_text, sizeof(hover_text),
                    "%s\nMODE %u\nCLIC : CHANGER LE MODE",
                    resource_name, mode);
            }
            text = hover_text;
        } else {
            switch (g_hovered_hall_command) {
            case WINDOW_ISLAND_PANEL_GENERAL:
                text = "INFORMATIONS GENERALES";
                break;
            case WINDOW_ISLAND_PANEL_INVENTORY:
                text = "RESERVE ET INVENTAIRE";
                break;
            case WINDOW_ISLAND_PANEL_GLYPHS:
                text = "GLYPHES";
                break;
            case WINDOW_ISLAND_PANEL_DIPLOMACY:
                text = "DIPLOMATIE";
                break;
            case WINDOW_ISLAND_PANEL_TRADE:
                text = "COMMERCE";
                break;
            default:
                break;
            }
        }
    } else {
        return;
    }
    panel = window_catalog_find(&g_window_catalog, "IWTextInfo", 3);
    if (panel == NULL || panel->shape_frame < 0 ||
        (uint32_t)panel->shape_frame >= g_temp_hole_art.frame_count) return;
    draw_sprite(dc, &g_temp_hole_art, (uint32_t)panel->shape_frame,
                panel->pane.left, panel->pane.top);
    if (text == NULL || text[0] == '\0') return;

    /* FUN_00439673 passes (10,6) to FUN_00428baa, whose callback FUN_0043954d
       overrides it for every line: x = 6, right bound 173 (wrap width 167), and
       y = previous y + 1 + font height starting from y = 6, so line k has its top
       at 6 + (k + 1) * (h + 1) (ev_ff703ed6, ev_4fa53e73). Text is drawn with y as
       the glyph-row top and has no native line limit; the port only stops at the
       screen bottom. */
    pane_width = panel->pane.right - panel->pane.left;
    pane_height = panel->pane.bottom - panel->pane.top;
    /* The text uses SMFONT (FUN_0042de0d returns &DAT_005c30b8, height 8) in
       palette index 6 (FUN_0042da69), so h = 8 and the pitch is 9. */
    line_height = (int)g_small_font.height + 1;
    max_lines = (LOGICAL_HEIGHT - panel->pane.top) / line_height;
    draw_wrapped_small_label(dc, text, panel->pane.left + 6,
                             panel->pane.top + 6 + line_height,
                             pane_width - 8, max_lines, line_height,
                             g_island_palette[6]);
}

static void draw_diplomacy_initial_worker_icon(HDC dc,
                                               const GameFloaterStart *floater,
                                               unsigned int fallback_tribe,
                                               int x, int y)
{
    const SpriteSheet *body_art;
    const SpriteSheet *leg_art;
    unsigned int type_index;
    int facing_left;
    /* FUN_00428191 builds its descriptor from the class (tribe) and subtype 0
       only, never from a live floater, so a player without a live floater
       still gets the tribe's worker banner. */
    if (floater != NULL && floater->type_index < GAME_START_PLAYER_COUNT) {
        type_index = floater->type_index;
        facing_left = floater->facing_left;
    } else if (fallback_tribe < GAME_START_PLAYER_COUNT) {
        type_index = fallback_tribe;
        facing_left = 0;
    } else {
        return;
    }
    body_art = facing_left
        ? &g_initial_floater_bodies_flipped[type_index]
        : &g_initial_floater_bodies[type_index];
    leg_art = facing_left
        ? &g_initial_floater_legs_flipped[type_index]
        : &g_initial_floater_legs[type_index];
    if (body_art->frame_count == 0 || leg_art->frame_count == 0) return;
    /* FUN_0042704b uses frame zero for the observed initial worker pose.
       Its later per-object animation and status-dependent frames are not
       represented by the four-worker startup model. */
    draw_sprite(dc, leg_art, 0, x, y);
    draw_sprite(dc, body_art, 0, x, y);
}

static void draw_diplomacy_panel(HDC dc, const WindowTemplate *panel,
                                 int player_slot)
{
    static const int32_t emblem_x[GAME_TRADE_TARGET_COUNT] = {264, 301, 325};
    static const int32_t emblem_y[GAME_TRADE_TARGET_COUNT] = {378, 386, 379};
    static const int32_t action_x[GAME_TRADE_TARGET_COUNT] = {220, 300, 380};
    unsigned int column;
    int pane_width = panel->pane.right - panel->pane.left;
    int pane_height = panel->pane.bottom - panel->pane.top;
    const GameFloaterStart *player_floaters[GAME_START_PLAYER_COUNT] = {0};
    if (g_game_session_valid) {
        unsigned floater_index;
        for (floater_index = 0; floater_index < g_game_session.floater_count;
             ++floater_index) {
            const GameFloaterStart *floater =
                &g_game_session.floaters[floater_index];
            if (game_session_floater_is_active(floater) &&
                floater->owner_slot < GAME_START_PLAYER_COUNT &&
                floater->type_index < GAME_START_PLAYER_COUNT &&
                player_floaters[floater->owner_slot] == NULL) {
                player_floaters[floater->owner_slot] = floater;
            }
        }
    }
    {
        int32_t icon_x;
        int32_t icon_y;
        if (game_diplomacy_player_icon_position(0, panel->pane.left,
                pane_width, pane_height, &icon_x, &icon_y)) {
            draw_diplomacy_initial_worker_icon(dc, player_floaters[player_slot],
                (unsigned int)player_slot,
                panel->pane.left + (int)icon_x,
                panel->pane.top + (int)icon_y);
        }
    }
    for (column = 0; column < GAME_TRADE_TARGET_COUNT; ++column) {
        uint8_t target_player;
        uint32_t emblem_frame = column * 7U;
        uint32_t action_frame;
        /* FUN_0043e5aa's helpers add the pane origin to their arguments, and
           the caller passes the emblem and action coordinates minus that
           origin, so they land at these window-absolute positions; the port's
           draw_sprite does not add the origin, so use them directly. */
        int action_y = panel->pane.top + pane_height -
                       (column == 1U ? 20 : 30) - 15;
        int32_t emblem_left = emblem_x[column];
        int32_t emblem_top = emblem_y[column];
        int32_t control_left = action_x[column];
        if (!game_diplomacy_target_player((uint8_t)player_slot,
                                          (uint8_t)column, &target_player)) continue;

        /* FUN_0043e5aa draws each other-player group's base frame (0, 7, 14)
           and, for the hovered policy row, blends the group's last frame
           (+6) on top of it instead of replacing it. */
        /* B = DAT_006192a0[local][target], the message-recipient flag the
           remake keeps in message_recipient_mask: when set, FUN_0043e5aa draws
           the animated variant 7c + 1 + anim, with anim stepping 0..4 every
           third paint (the port steps it every third animation tick). */
        if (g_game_session_valid &&
            (g_game_session.message_recipient_mask[player_slot] &
             (uint8_t)(1U << target_player)) != 0)
            emblem_frame += 1U + (g_menu.animation_ticks / 3U) % 5U;
        draw_sprite(dc, &g_diplomacy_art, emblem_frame,
                    (int)emblem_left, (int)emblem_top);
        emblem_frame = column * 7U;
        if (g_diplomacy_hover_valid &&
            g_diplomacy_hover.action == GAME_DIPLOMACY_POLICY &&
            g_diplomacy_hover.displayed_column == column) {
            draw_sprite(dc, &g_diplomacy_art, emblem_frame + 6U,
                        (int)emblem_left, (int)emblem_top);
        }

        if (g_diplomacy_hover_valid &&
            g_diplomacy_hover.action == GAME_DIPLOMACY_RECIPIENT &&
            g_diplomacy_hover.displayed_column == column) {
            draw_sprite(dc, &g_diplomacy_art, 23,
                        (int)control_left, action_y);
        }
        {
            int32_t icon_x;
            int32_t icon_y;
            if (game_diplomacy_player_icon_position((uint8_t)(column + 1U),
                    panel->pane.left, pane_width, pane_height,
                    &icon_x, &icon_y)) {
                /* FUN_0043e5aa draws each player icon before its policy state. */
                draw_diplomacy_initial_worker_icon(dc, player_floaters[target_player],
                    (unsigned int)target_player,
                    panel->pane.left + (int)icon_x,
                    panel->pane.top + (int)icon_y);
            }
        }
        action_frame =
            (g_game_session.diplomacy_policy_mask[player_slot] &
             (uint8_t)(1U << target_player)) != 0 ? 21U : 22U;
        /* FUN_0043e5aa draws recipient highlight frame 23 before the
           policy-state frame 21/22. The source's separate player-banner
           helper (FUN_00428191, flag 8) is not yet mapped to remake art. */
        draw_sprite(dc, &g_diplomacy_art, action_frame,
                    (int)control_left, action_y);
    }
    if (g_diplomacy_hover_valid) {
        /* The source condition chooses TRCOMHI for +0x72 (policy row) and
           TRDIPHI for +0x74 (recipient row), despite the labels' wording. */
        const char *caption = g_diplomacy_hover.action == GAME_DIPLOMACY_POLICY
            ? g_diplomacy_recipient_text : g_diplomacy_policy_text;
        int x = panel->pane.left + pane_width / 2 + 15;
        /* Drawn with SMFONT in palette index 6 (FUN_0043e5aa, ev_8f64bfc2). */
        draw_small_label(dc, caption, x, panel->pane.top + 7,
                         g_island_palette[6]);
    }
}

static const char *task_label_text(const char *key)
{
    if (key == NULL) return NULL;
    if (strcmp(key, "CONSTR") == 0) return g_task_label_text[0];
    if (strcmp(key, "REPAIR") == 0) return g_task_label_text[1];
    if (strcmp(key, "DARTIFACT") == 0) return g_task_label_text[2];
    if (strcmp(key, "OARTIFACT") == 0) return g_task_label_text[3];
    if (strcmp(key, "UPGRADE") == 0) return g_task_label_text[4];
    if (strcmp(key, "STOCK") == 0) return g_task_stock_text;
    if (strcmp(key, "TNORM") == 0) return g_task_priority_text[0];
    if (strcmp(key, "THIGH") == 0) return g_task_priority_text[1];
    if (strcmp(key, "TEXCL") == 0) return g_task_priority_text[2];
    if (strcmp(key, "DELIVER") == 0) return g_task_transfer_text[0];
    if (strcmp(key, "RETRIEVE") == 0) return g_task_transfer_text[1];
    if (strcmp(key, "STONE") == 0) return g_task_category_text[0];
    if (strcmp(key, "CTONE") == 0) return g_task_category_text[1];
    if (strcmp(key, "MTONE") == 0) return g_task_category_text[2];
    if (strcmp(key, "ARTIFACT") == 0) return g_task_category_text[3];
    return NULL;
}

static int hall_resource_task_index(int hall_player, int slot)
{
    unsigned int resource;
    const GamePendingEvent *event;
    if (!g_game_session_valid || hall_player < 0 ||
        hall_player >= GAME_START_PLAYER_COUNT || slot < 0 ||
        slot >= GAME_SESSION_MAX_PENDING_EVENTS) return -1;
    event = &g_game_session.pending_events[slot];
    if (event->active == 0) return -1;
    for (resource = 0; resource < GAME_RESOURCE_TYPE_COUNT; ++resource) {
        const GamePlayerEconomy *economy = &g_game_session.economy[hall_player];
        if (economy->resource_task_slot[resource] == slot &&
            event->player_id == hall_player && event->action_type == 4 &&
            event->payload_0a == economy->hall_island_index &&
            event->payload_0e == economy->hall_location_index &&
            event->payload_12 == (int16_t)(resource + 1U)) return (int)resource;
    }
    return -1;
}

static void draw_task_row_highlight(HDC dc, const WindowTemplate *panel,
                                    unsigned int visible_rows,
                                    unsigned int visible_index)
{
    const SpriteFrame *mask_frame;
    DIBSECTION mask_dib;
    int row_top;
    int row_height;
    int left;
    int right;
    int y;
    if (panel == NULL || panel->shape_frame < 0 ||
        (uint32_t)panel->shape_frame >= g_temp_hole_art.frame_count ||
        !island_panel_info_task_highlight_position(panel, visible_rows,
                                                   visible_index,
                                                   &row_top, &row_height)) return;
    mask_frame = &g_temp_hole_art.frames[(uint32_t)panel->shape_frame];
    ZeroMemory(&mask_dib, sizeof(mask_dib));
    if (mask_frame->bitmap == NULL ||
        GetObjectA(mask_frame->bitmap, sizeof(mask_dib), &mask_dib) <
            (int)sizeof(mask_dib) || mask_dib.dsBm.bmBits == NULL ||
        mask_dib.dsBm.bmBitsPixel != 32 ||
        mask_dib.dsBm.bmWidthBytes < mask_frame->width * 4) return;
    if (g_paint_buffer_pixels == NULL) return;
    left = panel->pane.left;
    right = panel->pane.right;
    if (right <= left) return;
    /* Finish GDI drawing into the DIB before reading its bits directly. */
    (void)GdiFlush();
    for (y = row_top + panel->pane.top; y < row_top + panel->pane.top + row_height; ++y) {
        int mask_y = y - panel->pane.top - mask_frame->y_offset;
        const uint32_t *mask_row;
        int x;
        if (mask_y < 0 || mask_y >= mask_frame->height) continue;
        mask_row = (const uint32_t *)((const unsigned char *)mask_dib.dsBm.bmBits +
            (size_t)mask_y * (size_t)mask_dib.dsBm.bmWidthBytes);
        for (x = left; x < right; ++x) {
            int mask_x = x - panel->pane.left - mask_frame->x_offset;
            DWORD background_pixel;
            COLORREF background;
            uint8_t source_index;
            if (mask_x < 0 || mask_x >= mask_frame->width) continue;
            if ((mask_row[mask_x] >> 24) == 0U) continue;
            background_pixel = g_paint_buffer_pixels[(size_t)y * LOGICAL_WIDTH +
                                                       (size_t)x];
            background = RGB((background_pixel >> 16) & 0xffU,
                             (background_pixel >> 8) & 0xffU,
                             background_pixel & 0xffU);
            /* Most panel pixels use exact palette colors. Repeated
               non-palette colors share an exact memoized nearest-color result. */
            if (!island_palette_lookup_nearest(&g_island_palette_lookup,
                    (uint32_t)background & UINT32_C(0x00ffffff),
                    &source_index)) continue;
            g_paint_buffer_pixels[(size_t)y * LOGICAL_WIDTH + (size_t)x] =
                g_task_highlight_pixels[source_index];
        }
    }
}

static void draw_task_gauge(HDC dc, const WindowTemplate *panel, int row_y,
                            unsigned int progress_width)
{
    const unsigned int interior_width = 0x46U - 4U;
    int gauge_x;
    int gauge_y;
    if (panel == NULL || g_task_icon_art.frame_count <= 9U) return;
    /* FUN_004459e6 passes a 70x7 track and inset 2 to FUN_004118df. */
    if (progress_width > interior_width) progress_width = interior_width;
    gauge_x = panel->pane.left + 0xaa;
    gauge_y = panel->pane.top + row_y;
    /* FUN_004118df draws frame 9, then masks the unfilled remainder to the
       right of the filled portion. */
    draw_sprite(dc, &g_task_icon_art, 9U, gauge_x, gauge_y);
    if (progress_width < interior_width) {
        fill_rect(dc, gauge_x + 2 + (int)progress_width, gauge_y + 2,
                  gauge_x + 2 + (int)interior_width, gauge_y + 5,
                  g_island_palette[0]);
    }
}

static void draw_task_stock_gauge(HDC dc, const WindowTemplate *panel,
                                  int hall_player, unsigned int resource,
                                  int row_y)
{
    const GamePlayerEconomy *economy;
    const GameRuntimeIsland *island;
    const GameRuntimeLocation *hall;
    unsigned int fill_width;
    if (!g_game_session_valid || panel == NULL || hall_player < 0 ||
        hall_player >= GAME_START_PLAYER_COUNT ||
        resource >= GAME_RESOURCE_TYPE_COUNT ||
        g_task_icon_art.frame_count <= 9U) return;
    economy = &g_game_session.economy[hall_player];
    if (economy->hall_island_index >= g_game_session.island_count ||
        economy->hall_location_index >=
            g_game_session.islands[economy->hall_island_index].location_count)
        return;
    island = &g_game_session.islands[economy->hall_island_index];
    hall = &island->locations[economy->hall_location_index];
    if (!island_panel_info_stock_gauge_fill(hall->resource_stock[resource],
            hall->source_capacity_4a, 0x46U - 4U,
            &fill_width)) return;
    draw_task_gauge(dc, panel, row_y, fill_width);
}

static void draw_task_repair_gauge(HDC dc, const WindowTemplate *panel,
                                   const GamePendingEvent *event, int row_y)
{
    int16_t current;
    int16_t maximum;
    unsigned int fill_width;
    if (!g_game_session_valid || panel == NULL || event == NULL ||
        g_task_icon_art.frame_count <= 9U ||
        !game_session_repair_task_values(&g_game_session, &g_pad_catalog,
                                         event, &current, &maximum) ||
        !island_panel_info_task_gauge_fill(current, maximum, 0x46U - 4U,
                                           &fill_width))
        return;
    draw_task_gauge(dc, panel, row_y, fill_width);
}

static void draw_task_construction_gauge(HDC dc, const WindowTemplate *panel,
                                         const GamePendingEvent *event,
                                         int row_y)
{
    int16_t current;
    int16_t maximum;
    unsigned int fill_width;
    if (!g_game_session_valid || panel == NULL || event == NULL ||
        g_task_icon_art.frame_count <= 9U ||
        !game_session_construction_task_values(&g_game_session, &g_pad_catalog,
                                                event, &current, &maximum) ||
        !island_panel_info_task_gauge_fill(current, maximum, 0x46U - 4U,
                                           &fill_width))
        return;
    draw_task_gauge(dc, panel, row_y, fill_width);
}
