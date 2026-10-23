static void render_world_map(HDC dc)
{
    const WorldDefinition *world;
    size_t island_index;

    fill_rect(dc, 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT, RGB(0, 0, 0));
    draw_sprite(dc, &g_map_background, 0, 0, 0);
    if (g_menu.world_index < 0 || g_menu.world_index >= g_menu.world_map.world_count) return;
    world = &g_menu.world_map.worlds[g_menu.world_index];
    /* WorldWindow display type 1 (FUN_00471b74) renders explicit bridge pairs
       as animated palette-color pixels. They are drawn after the islands
       (see below), as in the original record order. */
    for (island_index = 0; island_index < world->island_count; ++island_index) {
        const WorldIsland *island = &world->islands[island_index];
        int x;
        int y;
        uint32_t frame = world_island_frame_index(
            island_index, island->shape_id, g_hovered_island == (int)island_index);
        world_island_position(island, &x, &y);
        /* FUN_00471e66 draws islands 0..3 at scale 1.0 and the others at the
           window scale this+0x70 (0xc000 = 75 % by default: FUN_00470259). The
           hit rectangles stay unscaled (FUN_00405e11 bounds). */
        if (island_index < 4U)
            draw_sprite(dc, &g_small_islands, frame, x, y);
        else
            draw_sprite_scaled(dc, &g_small_islands, frame, x, y, 0xc000U);
    }
    /* FUN_00471e66 draws records in order: every island record precedes the
       bridge records (FUN_004718eb), so the bridge sparks end up on top. */
    {
        BYTE bridge_colors[8];
        int ramp;
        for (ramp = 0; ramp < 8; ++ramp) {
            int red = (5 + ramp * 7) * 255 / 63;
            int green = (5 + ramp * 2) * 255 / 63;
            int blue = (45 + ramp * 2) * 255 / 63;
            int best_index = 0;
            unsigned best_distance = 0xffffffffu;
            int palette_index;
            for (palette_index = 0; palette_index < 255; ++palette_index) {
                int dr = red - (int)GetRValue(g_map_palette[palette_index]);
                int dg = green - (int)GetGValue(g_map_palette[palette_index]);
                int db = blue - (int)GetBValue(g_map_palette[palette_index]);
                unsigned distance = (unsigned)(dr * dr + dg * dg + db * db);
                if (distance < best_distance) {
                    best_distance = distance;
                    best_index = palette_index;
                }
            }
            bridge_colors[ramp] = (BYTE)best_index;
        }
        for (size_t bridge_index = 0; bridge_index < world->bridge_count; ++bridge_index) {
            const WorldBridge *bridge = &world->bridges[bridge_index];
            if (!game_session_world_bridge_is_renderable(&g_game_session,
                    (uint8_t)bridge_index, world->bridge_count,
                    bridge->island_a, bridge->island_b)) continue;
            const WorldIsland *a = &world->islands[bridge->island_a];
            const WorldIsland *b = &world->islands[bridge->island_b];
            int ax;
            int ay;
            int bx;
            int by;
            world_island_position(a, &ax, &ay);
            world_island_position(b, &bx, &by);
            int dx = bx - ax;
            int dy = by - ay;
            int length = (int)sqrt((double)dx * dx + (double)dy * dy);
            int step;
            if (ax < 0 || ax >= LOGICAL_WIDTH || bx < 0 || bx >= LOGICAL_WIDTH ||
                ay < 0 || ay >= LOGICAL_HEIGHT || by < 0 || by >= LOGICAL_HEIGHT ||
                length <= 0) {
                continue;
            }
            for (step = 0; step < length; ++step) {
                int center_x = ax + dx * step / length;
                int center_y = ay + dy * step / length;
                int width = step * 20 / length;
                unsigned color = bridge_colors[
                    world_map_visual_sample(g_menu.animation_ticks,
                                            bridge_index, step, -1) % 8u];
                int spark;
                for (spark = 0; spark < 10; ++spark) {
                    uint32_t random_value = world_map_visual_sample(
                        g_menu.animation_ticks, bridge_index, step, spark);
                    int x_jitter = (width + 1) / 2 -
                        (int)(random_value % (unsigned)(width + 1));
                    int y_jitter = (width + 1) / 2 -
                        (int)(((random_value >> 8) % (unsigned)(width + 1)));
                    SetPixelV(dc, center_x + x_jitter, center_y + y_jitter,
                              g_map_palette[color]);
                }
            }
        }
    }
    {
        /* FUN_004711e2 follows +0x76, the hovered island only; there is no
           selected-island fallback. */
        int island_index = g_hovered_island;
        if (island_index >= 0 && (size_t)island_index < world->island_count &&
            game_session_can_enter_island(&g_game_session,
                (uint8_t)island_index, world_map_player_mask())) {
            int name_index = world->islands[island_index].shape_id;
            if (name_index >= 0 && name_index < ISLAND_NAME_COUNT) {
                /* FUN_004711e2 centers the current island name at y=0x3c. */
                draw_sprite(dc, &g_island_names_art, (uint32_t)name_index, 0, 48);
            }
        }
    }
}

/* FUN_0045858a: LOADTMP frame 0 is the 640x480 template; the eight cells are
   LOADSAVE frames 1..8 (300x99) at x 13 / 326 and y 36 + 111 row (slot =
   row + 4 column). A valid slot shows its file date at (2,2) and the header
   summary (SURPFLOW / POPSTR / WORKSTR) on the right. The ENDGAME level frame,
   the resource icons and the preview draw are not ported (their layout and
   palette are not established). */
static void render_load_game(HDC dc)
{
    int slot;
    ensure_load_save_art();
    fill_rect(dc, 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT, RGB(0, 0, 0));
    draw_sprite(dc, &g_load_save_art, 0, 0, 0);
    for (slot = 0; slot < 8; ++slot) {
        int column = slot / 4;
        int row = slot % 4;
        int x = 13 + 313 * column;
        int y = 36 + 111 * row;
        char text[96];
        draw_sprite(dc, &g_load_save_art, (uint32_t)(1 + slot), x, y);
        if (!g_load_slot_valid[slot] || g_small_font.bytes == NULL) continue;
        {
            /* ENDGAME frame clamp(header +0x78, 0..4) at (-6,-6): the level
               emblem (DAT_004bf11c), coloured with the active game.pal. */
            uint32_t level = (uint32_t)(g_load_slot_header[slot][0x78] |
                (g_load_slot_header[slot][0x79] << 8));
            if (level > 4U) level = 4U;
            if (g_load_endgame_art.frame_count > level)
                draw_sprite(dc, &g_load_endgame_art, level, x - 6, y - 6);
        }
        if (g_load_slot_date[slot][0] != '\0')
            draw_small_label(dc, g_load_slot_date[slot], x + 2, y + 2,
                             g_load_save_palette[6]);
        (void)snprintf(text, sizeof(text), "%s %d", g_hall_surplus_label,
            (int)(g_load_slot_header[slot][0x68] |
                  (g_load_slot_header[slot][0x69] << 8) |
                  (g_load_slot_header[slot][0x6a] << 16) |
                  ((unsigned)g_load_slot_header[slot][0x6b] << 24)));
        draw_small_label(dc, text, x + 0x69, y + 0x0e, g_load_save_palette[6]);
        (void)snprintf(text, sizeof(text), "%s %d", g_hall_population_label,
            (int)(g_load_slot_header[slot][0x6c] |
                  (g_load_slot_header[slot][0x6d] << 8)));
        draw_small_label(dc, text, x + 0xe8, y + 0x28, g_load_save_palette[6]);
        {
            /* "%s %d (%d%%)": workers over population, truncated (the native
               value is an FPU quotient converted by __ftol). */
            int population = (int)(g_load_slot_header[slot][0x6c] |
                                   (g_load_slot_header[slot][0x6d] << 8));
            int workers = (int)(g_load_slot_header[slot][0x70] |
                                (g_load_slot_header[slot][0x71] << 8));
            int percentage = population > 0 ? workers * 100 / population : 0;
            (void)snprintf(text, sizeof(text), "%s %d (%d%%)", g_hall_work_label,
                           workers, percentage);
            draw_small_label(dc, text, x + 0xe8, y + 0x32,
                             g_load_save_palette[6]);
        }
        {
            /* FUN_0040bf98 draws the saved site record (header +0x08) at
               (210, 90) at scale 1.0: here the Hall's item id (header +0x18),
               when that building's art is loaded (a game is running). */
            uint32_t item = (uint32_t)(g_load_slot_header[slot][0x18] |
                (g_load_slot_header[slot][0x19] << 8));
            uint32_t owner = (uint32_t)(g_load_slot_header[slot][0x1c] |
                (g_load_slot_header[slot][0x1d] << 8));
            if (!g_load_slot_native[slot] && item > 0U &&
                item < PAD_CATALOG_MAX_ITEMS &&
                g_building_art[item].frame_count != 0U && owner < 4U)
            {
                /* The preview struct of FUN_0040d3e1 minus the placement ramp
                   (flag 0x010), which only applies at scale 1.0, clipped to
                   the cell like the native rectangle. */
                GameRuntimeLocation preview;
                int saved_clip = SaveDC(dc);
                memset(&preview, 0, sizeof(preview));
                preview.record_value_10 = (int32_t)item;
                preview.owner_id = (int32_t)owner;
                preview.source_flags = 0x400U;
                preview.animation_rate = 1;
                (void)IntersectClipRect(dc, x, y, x + 300, y + 99);
                (void)draw_runtime_item_scaled(dc, &preview, x + 210, y + 90,
                                               0x10000U);
                (void)RestoreDC(dc, saved_clip);
            }
        }
        {
            /* FUN_0042704b draws the tribe's floater (record +0x14 = header
               +0x1c) at (250, 17), or 14 for tribe 3, scale 1.0. Frame 0 of
               body and legs is an approximation of its idle pose. */
            uint32_t tribe = (uint32_t)(g_load_slot_header[slot][0x1c] |
                (g_load_slot_header[slot][0x1d] << 8));
            if (tribe < 4U && g_load_floater_body[tribe].frame_count > 0U) {
                int sprite_y = y + (tribe == 3U ? 14 : 17);
                if (g_load_floater_legs[tribe].frame_count > 0U)
                    draw_sprite(dc, &g_load_floater_legs[tribe], 0, x + 250,
                                sprite_y);
                draw_sprite(dc, &g_load_floater_body[tribe], 0, x + 250,
                            sprite_y);
            }
        }
        {
            /* Header +0x30/+0x32/+0x34 (record +0x28/+0x2a/+0x2c): bildtone
               frame 24 at (141,40), tonecrys and magctone frame 4 at (141,70)
               and (141,97), values at x 153 and y 34 / 63 / 90. */
            static const int icon_frame[3] = {24, 4, 4};
            static const int icon_y[3] = {40, 70, 97};
            static const int text_y[3] = {34, 63, 90};
            static const int field[3] = {0x30, 0x32, 0x34};
            int tone;
            for (tone = 0; tone < 3; ++tone) {
                int value = (int)(short)(g_load_slot_header[slot][field[tone]] |
                    (g_load_slot_header[slot][field[tone] + 1] << 8));
                if (g_load_tone_art[tone].frame_count >
                    (uint32_t)icon_frame[tone])
                    draw_sprite(dc, &g_load_tone_art[tone],
                                (uint32_t)icon_frame[tone], x + 141,
                                y + icon_y[tone]);
                (void)snprintf(text, sizeof(text), "%d", value);
                draw_small_label(dc, text, x + 153, y + text_y[tone],
                                 g_load_save_palette[6]);
            }
        }
    }
    /* LSTITLE at (317,0): frame clamp(tribe, 0..7), +4 in Load mode. */
    if (g_load_title_art.frame_count > 7U) {
        uint32_t tribe = g_menu.selected_tribe < 3 ? (uint32_t)g_menu.selected_tribe : 3U;
        draw_sprite(dc, &g_load_title_art, (g_load_save_mode ? 0U : 4U) + tribe, 317, 0);
    }
}
static void paint_window(HWND window)
{
    PAINTSTRUCT paint;
    HDC screen = BeginPaint(window, &paint);
    RECT client;
    GetClientRect(window, &client);
    {
        int width = client.right - client.left;
        int height = client.bottom - client.top;
        RECT viewport;
        HDC back;
        if (!ensure_paint_buffer(screen)) {
            EndPaint(window, &paint);
            return;
        }
        back = g_paint_buffer_dc;
        if (g_menu.screen == SCREEN_MAIN_MENU) {
            render_main_menu(back);
        } else if (g_menu.screen == SCREEN_NEW_GAME) {
            render_new_game(back);
        } else if (g_menu.screen == SCREEN_WORLD_MAP) {
            render_world_map(back);
        } else if (g_menu.screen == SCREEN_ISLAND) {
            render_island_view(back);
        } else if (g_menu.screen == SCREEN_LOGO) {
            render_logo(back);
        } else if (g_menu.screen == SCREEN_END_GAME) {
            render_end_game(back);
        } else {
            render_load_game(back);
        }
        if (g_menu.screen == SCREEN_WORLD_MAP || g_menu.screen == SCREEN_ISLAND)
            render_slide_panel(back);
        (void)GdiFlush();
        if (logical_viewport(width, height, &viewport)) {
            /* Clearing the whole client before each StretchBlt exposed a black
               frame on every animated paint. Only clear the letterbox bars. */
            if (viewport.top > 0) {
                RECT bar = {client.left, client.top, client.right, viewport.top};
                FillRect(screen, &bar, (HBRUSH)GetStockObject(BLACK_BRUSH));
            }
            if (viewport.bottom < height) {
                RECT bar = {client.left, viewport.bottom, client.right, client.bottom};
                FillRect(screen, &bar, (HBRUSH)GetStockObject(BLACK_BRUSH));
            }
            if (viewport.left > 0) {
                RECT bar = {client.left, viewport.top, viewport.left, viewport.bottom};
                FillRect(screen, &bar, (HBRUSH)GetStockObject(BLACK_BRUSH));
            }
            if (viewport.right < width) {
                RECT bar = {viewport.right, viewport.top, client.right, viewport.bottom};
                FillRect(screen, &bar, (HBRUSH)GetStockObject(BLACK_BRUSH));
            }
            SetStretchBltMode(screen, HALFTONE);
            StretchBlt(screen, viewport.left, viewport.top,
                       viewport.right - viewport.left, viewport.bottom - viewport.top,
                       back, 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT, SRCCOPY);
        }
    }
    EndPaint(window, &paint);
}
