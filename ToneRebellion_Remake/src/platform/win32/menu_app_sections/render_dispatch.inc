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

static void render_load_game(HDC dc)
{
    fill_rect(dc, 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT, RGB(0, 0, 0));
    /* windows.txt state 4 layers LOADSAVE frame 0 and frame 1 full-screen. */
    draw_sprite(dc, &g_load_save_art, 0, 0, 0);
    draw_sprite(dc, &g_load_save_art, 1, 0, 0);
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
        } else {
            render_load_game(back);
        }
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
