/* PARADISE (data\end.shp) and PARAGLOW (data\endglw.shp), loaded with the
   map palette; FUN_004702d9 case 1 preloads them in world state 3. */
static SpriteSheet g_paradise_art;
static SpriteSheet g_paraglow_art;
static void render_world_map(RenderSurface *surface)
{
    const WorldDefinition *world;
    size_t island_index;
    /* FUN_004711e2 (ev_c734e7a6): islands and bridges (FUN_00471e66) are
       drawn while DAT_006191b4 < 4, while state 4 has DAT_006191b6 < 0x3c,
       or while the word at 0x619248 (player 0 +0x90) is set. */
    int sequence_state = g_game_session_valid
        ? g_game_session.world_sequence_state : 0;
    int sequence_tick = g_game_session_valid
        ? g_game_session.world_sequence_tick : 0;
    int player0_latched = g_game_session_valid &&
        g_game_session.economy[0].defeat_latched;
    int draw_records = sequence_state < 4 ||
        (sequence_state == 4 && sequence_tick < 0x3c) || player0_latched;

    fill_rect(surface, 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT, RGB(0, 0, 0));
    draw_sprite(surface, &g_map_background, 0, 0, 0);
    if (g_menu.world_index < 0 || g_menu.world_index >= g_menu.world_map.world_count) return;
    world = &g_menu.world_map.worlds[g_menu.world_index];
    if (!draw_records) goto paradise;
    /* WorldWindow display type 1 (FUN_00471b74) renders explicit bridge pairs
       as animated palette-color pixels. FUN_00471b34's sort puts every bridge
       record before the islands, so the sparks are drawn first. */
    {
        BYTE bridge_colors[8];
        int ramp;
        for (ramp = 0; ramp < 8; ++ramp) {
            int red = (5 + ramp * 7) * 255 / 63;
            /* FUN_00471b74 passes local_48 (5 + 7r) for both red and green. */
            int green = (5 + ramp * 7) * 255 / 63;
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
            /* FUN_00471b74: D = sqrt(dx^2+dy^2); N = ftol(D / 7.0f) steps of
               D/7 ... i.e. the centre advances 7 px per step, not 1. */
            float distance = (float)sqrt((double)dx * dx + (double)dy * dy);
            float step_length = distance / 7.0f;
            int length = (int)step_length;
            float step_x = length > 0 ? (float)dx / step_length : 0.0f;
            float step_y = length > 0 ? (float)dy / step_length : 0.0f;
            int step;
            if (ax < 0 || ax >= LOGICAL_WIDTH || bx < 0 || bx >= LOGICAL_WIDTH ||
                ay < 0 || ay >= LOGICAL_HEIGHT || by < 0 || by >= LOGICAL_HEIGHT ||
                length <= 0) {
                continue;
            }
            for (step = 0; step < length; ++step) {
                int center_x = (int)((float)ax + (float)step * step_x);
                int center_y = (int)((float)ay + (float)step * step_y);
                int width = step * 20 / length;
                /* Colour index = trunc(rand15 * 8 / 32768) = rand15 >> 12. */
                unsigned color = bridge_colors[
                    (world_map_visual_sample(g_menu.animation_ticks,
                                             bridge_index, step, -1) & 0x7fffu) >> 12];
                int spark;
                for (spark = 0; spark < 10; ++spark) {
                    uint32_t random_value = world_map_visual_sample(
                        g_menu.animation_ticks, bridge_index, step, spark) & 0x7fffu;
                    int x_jitter = (width + 1) / 2 -
                        (int)(random_value % (unsigned)(width + 1));
                    int y_jitter = (width + 1) / 2 -
                        (int)(((random_value >> 8) % (unsigned)(width + 1)));
                    render_surface_set_pixel(surface, center_x + x_jitter,
                        center_y + y_jitter, colorref_pixel(g_map_palette[color]));
                }
            }
        }
    }
    {
        /* Islands back to front (FUN_00471b34 order). FUN_00471e66 draws
           islands 0..3 at scale 1.0 and the others at the window scale
           this+0x70 (0xc000 = 75 % by default: FUN_00470259). The hit
           rectangles stay unscaled (FUN_00405e11 bounds). */
        size_t order[WORLD_MAP_MAX_ISLANDS];
        size_t count = world_island_draw_order(world, order);
        size_t k;
        for (k = 0; k < count; ++k) {
            const WorldIsland *island;
            int x;
            int y;
            uint32_t frame;
            island_index = order[k];
            island = &world->islands[island_index];
            frame = world_island_frame_index(island_index, island->shape_id,
                                             g_hovered_island == (int)island_index);
            world_island_position(island, &x, &y);
            if (island_index < 4U)
                draw_sprite(surface, &g_small_islands, frame, x, y);
            else
                draw_sprite_scaled(surface, &g_small_islands, frame, x, y, 0xc000U);
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
                /* FUN_004711e2 draws the hovered island's name with BIGFONT
                   (ECX = FUN_0042de03, 0x471424..0x47148a, ev_1fee9279),
                   centred on 640 at y = 0x3c, in the font's current colour;
                   the port takes the default index 6 of the map palette. */
                const char *name = g_island_names[name_index];
                if (g_big_font.bytes != NULL && name[0] != '\0') {
                    int width = measure_big_text(name, strlen(name));
                    draw_big_label(surface, name, (LOGICAL_WIDTH - width) / 2,
                                   0x3c, g_map_palette[6]);
                } else {
                    draw_sprite(surface, &g_island_names_art,
                                (uint32_t)name_index, 0, 48);
                }
            }
        }
    }
paradise:
    /* FUN_004711e2, state > 3 with 0x619248 clear: PARADISE frame
       DAT_006324b8 % 21 when state != 4 or DAT_006191b6 > 0x3b; PARAGLOW
       frame DAT_006191b6 ping-pong (v <= 61 ? v : 122 - v) while state 4 has
       DAT_006191b6 < 0x50. Both at the map centre (+0x784, +0x786) that
       FUN_00470259 sets to (639 / 2, 479 / 2 + 15). */
    if (sequence_state > 3 && !player0_latched) {
        if ((sequence_state != 4 || sequence_tick > 0x3b) &&
            g_paradise_art.frame_count != 0) {
            /* Remake: the native counter steps on each dirty repaint; here it
               steps once per game tick, so the glitter keeps the game's
               pace at any frame rate. */
            draw_sprite(surface, &g_paradise_art,
                        g_menu.animation_ticks % 21U % g_paradise_art.frame_count,
                        319, 254);
        }
        if (sequence_state == 4 && sequence_tick < 0x50 &&
            g_paraglow_art.frame_count != 0) {
            uint32_t frame = (uint32_t)(sequence_tick <= 61
                ? sequence_tick : 122 - sequence_tick);
            if (frame < g_paraglow_art.frame_count)
                draw_sprite(surface, &g_paraglow_art, frame, 319, 254);
        }
    }
}

/* FUN_0045858a: LOADTMP frame 0 is the 640x480 template; the eight cells are
   LOADSAVE frames 1..8 (300x99) at x 13 / 326 and y 36 + 111 row (slot =
   row + 4 column). A valid slot shows its file date at (2,2) and the header
   summary (SURPFLOW / POPSTR / WORKSTR) on the right. The ENDGAME level frame,
   the resource icons and the preview draw are not ported (their layout and
   palette are not established). */
static void render_load_game(RenderSurface *surface)
{
    int slot;
    ensure_load_save_art();
    fill_rect(surface, 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT, RGB(0, 0, 0));
    draw_sprite(surface, &g_load_save_art, 0, 0, 0);
    for (slot = 0; slot < 8; ++slot) {
        int column = slot / 4;
        int row = slot % 4;
        int x = 13 + 313 * column;
        int y = 36 + 111 * row;
        char text[96];
        draw_sprite(surface, &g_load_save_art, (uint32_t)(1 + slot), x, y);
        if (!g_load_slot_valid[slot] || g_small_font.bytes == NULL) continue;
        {
            /* ENDGAME frame clamp(header +0x78, 0..4) at (-6,-6): the level
               emblem (DAT_004bf11c), coloured with the active game.pal. */
            uint32_t level = (uint32_t)(g_load_slot_header[slot][0x78] |
                (g_load_slot_header[slot][0x79] << 8));
            if (level > 4U) level = 4U;
            if (g_load_endgame_art.frame_count > level)
                draw_sprite(surface, &g_load_endgame_art, level, x - 6, y - 6);
        }
        if (g_load_slot_date[slot][0] != '\0')
            draw_small_label(surface, g_load_slot_date[slot], x + 2, y + 2,
                             native_text_color(g_load_save_palette, 6));
        (void)snprintf(text, sizeof(text), "%s %d", g_hall_surplus_label,
            (int)(g_load_slot_header[slot][0x68] |
                  (g_load_slot_header[slot][0x69] << 8) |
                  (g_load_slot_header[slot][0x6a] << 16) |
                  ((unsigned)g_load_slot_header[slot][0x6b] << 24)));
        draw_small_label(surface, text, x + 0x69, y + 0x0e, native_text_color(g_load_save_palette, 6));
        (void)snprintf(text, sizeof(text), "%s %d", g_hall_population_label,
            (int)(g_load_slot_header[slot][0x6c] |
                  (g_load_slot_header[slot][0x6d] << 8)));
        draw_small_label(surface, text, x + 0xe8, y + 0x28, native_text_color(g_load_save_palette, 6));
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
            draw_small_label(surface, text, x + 0xe8, y + 0x32,
                             native_text_color(g_load_save_palette, 6));
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
                int saved_clip = render_surface_save(surface);
                memset(&preview, 0, sizeof(preview));
                preview.record_value_10 = (int32_t)item;
                preview.owner_id = (int32_t)owner;
                preview.source_flags = 0x400U;
                preview.animation_rate = 1;
                render_surface_intersect_clip(surface, x, y, x + 300, y + 99);
                (void)draw_runtime_item_scaled(surface, &preview, x + 210, y + 90,
                                               0x10000U);
                (void)render_surface_restore(surface, saved_clip);
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
                draw_sprite(surface, &g_load_floater_body[tribe], 0, x + 250,
                            sprite_y);
                if (g_load_floater_legs[tribe].frame_count > 0U)
                    draw_sprite(surface, &g_load_floater_legs[tribe], 0, x + 250,
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
                    draw_sprite(surface, &g_load_tone_art[tone],
                                (uint32_t)icon_frame[tone], x + 141,
                                y + icon_y[tone]);
                (void)snprintf(text, sizeof(text), "%d", value);
                draw_small_label(surface, text, x + 153, y + text_y[tone],
                                 native_text_color(g_load_save_palette, 6));
            }
        }
    }
    /* LSTITLE at (317,0): frame clamp(tribe, 0..7), +4 in Load mode. */
    if (g_load_title_art.frame_count > 7U) {
        uint32_t tribe = g_menu.selected_tribe < 3 ? (uint32_t)g_menu.selected_tribe : 3U;
        draw_sprite(surface, &g_load_title_art, (g_load_save_mode ? 0U : 4U) + tribe, 317, 0);
    }
}
static void render_back_buffer_now(RenderSurface *back);

/* Composes the current screen into the back buffer (640x480, or wider with
   widescreen), with the moving things blended between the last two game
   frames (render_interp.inc). */
static void render_back_buffer(RenderSurface *back)
{
    render_interp_apply();
    render_back_buffer_now(back);
    render_interp_restore();
}

static void render_back_buffer_now(RenderSurface *frame)
{
    /* Widescreen: every screen draws its 640x480 picture into the centred
       window of the wider frame; the island view alone also fills the
       sides (g_frame_surface). */
    RenderSurface *back = &g_panel_surface;
    int side = (frame->width - LOGICAL_WIDTH) / 2;
    if (side < 0) side = 0;
    render_surface_reset_clip(frame);
    if (side > 0)
        render_surface_fill_rect(frame, 0, 0, frame->width, frame->height, 0);
    render_surface_init(back, frame->pixels + side,
                        frame->width < LOGICAL_WIDTH ? frame->width : LOGICAL_WIDTH,
                        frame->height, frame->stride);
    g_frame_surface = frame;
    g_frame_width = frame->width;
    if (g_menu.screen == SCREEN_MAIN_MENU) {
        render_main_menu(back);
        render_net_setup_title_button(back);
        render_intro_title_button(back);
        render_net_lobby(back);
    } else if (g_menu.screen == SCREEN_NEW_GAME) {
        render_new_game(back);
        render_net_lobby(back);
    } else if (g_menu.screen == SCREEN_WORLD_MAP) {
        render_world_map(back);
    } else if (g_menu.screen == SCREEN_ISLAND) {
        render_island_view(back);
    } else if (g_menu.screen == SCREEN_LOGO) {
        render_logo(back);
    } else if (g_menu.screen == SCREEN_END_GAME) {
        render_end_game(back);
    } else if (g_menu.screen == SCREEN_NET_SETUP) {
        render_net_setup(back);
    } else if (g_menu.screen == SCREEN_INTRO) {
        render_intro(back);
    } else {
        render_load_game(back);
    }
    if (g_menu.screen == SCREEN_WORLD_MAP || g_menu.screen == SCREEN_ISLAND) {
        render_pause_eye(back);
        render_slide_panel(back);
        render_alerts(back);
        render_options_panel(back);
    } else if (g_menu.screen == SCREEN_MAIN_MENU) {
        /* Remake: F2 opens the options on the title too (language, display). */
        render_title_options_hint(back);
        render_options_panel(back);
    } else {
        g_options_open = 0;
    }
    /* End-sequence fade (FUN_00410765 through the screen palette): every
       channel is scaled by (256 - level) / 256. The native fade starts from
       the logo.pal buffer at 0x630730; the port darkens the frame as drawn. */
    if (g_game_session_valid &&
        (g_menu.screen == SCREEN_WORLD_MAP || g_menu.screen == SCREEN_ISLAND)) {
        int level = game_session_world_fade_level(&g_game_session,
            (uint8_t)g_game_session.config.selected_tribe);
        if (level > 0) {
            uint32_t keep = (uint32_t)(256 - level);
            int row;
            int column;
            for (row = 0; row < frame->height; ++row) {
                uint32_t *pixel = frame->pixels + (size_t)row * (size_t)frame->stride;
                for (column = 0; column < frame->width; ++column) {
                    uint32_t c = pixel[column];
                    pixel[column] = (c & 0xff000000U) |
                        ((((c >> 16) & 0xffU) * keep >> 8) << 16) |
                        ((((c >> 8) & 0xffU) * keep >> 8) << 8) |
                        (((c & 0xffU) * keep) >> 8);
                }
            }
        }
    }
}

