static unsigned game_random(void)
{
    return tone_rng_next15(&g_random_state);
}

static int logical_viewport(int client_width, int client_height, RECT *viewport)
{
    if (client_width <= 0 || client_height <= 0 || viewport == NULL) return 0;
    if ((int64_t)client_width * LOGICAL_HEIGHT <=
        (int64_t)client_height * LOGICAL_WIDTH) {
        viewport->left = 0;
        viewport->right = client_width;
        viewport->top = (client_height - client_width * LOGICAL_HEIGHT / LOGICAL_WIDTH) / 2;
        viewport->bottom = viewport->top + client_width * LOGICAL_HEIGHT / LOGICAL_WIDTH;
    } else {
        viewport->top = 0;
        viewport->bottom = client_height;
        viewport->left = (client_width - client_height * LOGICAL_WIDTH / LOGICAL_HEIGHT) / 2;
        viewport->right = viewport->left + client_height * LOGICAL_WIDTH / LOGICAL_HEIGHT;
    }
    return viewport->right > viewport->left && viewport->bottom > viewport->top;
}

static int template_is_in_state(const WindowTemplate *window, int state)
{
    size_t i;
    for (i = 0; i < window->state_count; ++i) {
        if (window->states[i] == state) return 1;
    }
    return 0;
}

static int template_help_index(const WindowTemplate *window)
{
    if (strcmp(window->name, "RESUME") == 0) return HELP_MAIN_RESUME;
    if (strcmp(window->name, "NEWGAME") == 0) return HELP_MAIN_NEWGAME;
    if (strcmp(window->name, "LOADGAME") == 0) return HELP_MAIN_LOAD;
    if (strcmp(window->name, "EXITAPP") == 0) return HELP_MAIN_EXIT;
    return -1;
}

static int template_caption_index(const WindowTemplate *window)
{
    if (strcmp(window->message_destination, "WINMGR") == 0 &&
        window->send_message[0] == 1 && window->send_message[1] == 0) return 6;
    if (strcmp(window->message_destination, "MASTER") != 0) return -1;
    if (window->send_message[0] == 52) return 7;
    if (window->send_message[0] == 53) return 5;
    if (window->send_message[0] == 55) return 4;
    if (window->send_message[0] >= 60 && window->send_message[0] <= 63)
        return window->send_message[0] - 60;
    return -1;
}

static void draw_configured_buttons(HDC dc, int state, const char *shape_id,
                                    SpriteSheet *sheet)
{
    size_t i;
    for (i = 0; i < g_window_catalog.count; ++i) {
        const WindowTemplate *window = &g_window_catalog.windows[i];
        int frame;
        if (!template_is_in_state(window, state) ||
            strcmp(window->shape_id, shape_id) != 0 || window->shape_frame < 0) continue;
        /* FUN_004489c0 (message 1) sends message 2 to RESUME when the resume
           file has no valid header; for the generic button class message 2
           clears +0x3c/+0x38 and FUN_0042a55d then skips the draw (hidden). */
        if (state == 0 && strcmp(window->name, "RESUME") == 0 &&
            !g_resume_available) continue;
        frame = window->shape_frame;
        if (state == 0) {
            int help_index = template_help_index(window);
            int hovered = window_catalog_hover_frame(
                window->shape_frame, help_index, g_hovered_help) !=
                window->shape_frame;
            frame = window_catalog_control_frame(window, hovered);
        } else if (state == 1) {
            int caption_index = template_caption_index(window);
            int hovered = window_catalog_hover_frame(
                window->shape_frame, caption_index,
                g_hovered_newgame_text) != window->shape_frame;
            frame = window_catalog_control_frame(window, hovered);
        }
        draw_sprite(dc, sheet, (uint32_t)frame, window->pane.left, window->pane.top);
    }
}

static void render_main_menu(HDC dc)
{
    fill_rect(dc, 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT, RGB(0, 0, 0));
    draw_configured_buttons(dc, 0, "TITSCRN", &g_title_art);
    draw_hover_help(dc);
}

static void render_new_game(HDC dc)
{
    static const POINT tribe_centers[4] = {{170, 240}, {320, 90}, {470, 240}, {320, 390}};
    static const int orbit_radii[3] = {150, 170, 130};
    int tribe;
    int ring;
    int angle_step;
    fill_rect(dc, 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT, RGB(0, 0, 0));
    draw_sprite(dc, &g_new_background, 0, 0, 0);
    for (ring = 0; ring < 3; ++ring) {
        const int radius = orbit_radii[ring];
        COLORREF color = g_newgame_palette[0];
        for (angle_step = 2; angle_step < 16; ++angle_step) {
            float angle = (float)(angle_step * 5) * 0.017453292f;
            int dx = (int)(sin((double)angle) * radius);
            int dy = (int)(cos((double)angle) * radius);
            const int xs[4] = {315 + dx, 315 - dx, 315 - dx, 315 + dx};
            const int ys[4] = {236 + dy, 236 + dy, 236 - dy, 236 - dy};
            int quadrant;
            for (quadrant = 0; quadrant < 4; ++quadrant) {
                RECT dot = {xs[quadrant], ys[quadrant], xs[quadrant] + 10, ys[quadrant] + 8};
                HBRUSH brush = CreateSolidBrush(color);
                FillRect(dc, &dot, brush);
                DeleteObject(brush);
            }
            /* The original emits ten randomized pixels for each quadrant,
               using FUN_00474b90's LCG. Its palette byte is 0xb6..0xc6. */
            if (ring <= g_menu.world_index) {
                int speck;
                for (speck = 0; speck < 10; ++speck) {
                    int side;
                    for (side = 0; side < 4; ++side) {
                        int sx;
                        int sy;
                        unsigned color = game_random() % 17u + 0xb6u;
                        unsigned y_jitter = game_random() % 6u;
                        unsigned x_jitter = game_random() % 7u;
                        sx = (side == 0 || side == 3 ? 325 + dx : 325 - dx) - (int)x_jitter;
                        sy = (side < 2 ? 244 + dy : 244 - dy) - (int)y_jitter;
                        SetPixelV(dc, sx, sy, g_newgame_palette[color]);
                    }
                }
            }
        }
    }
    /* NEWGAMWND contributes the 640x73 frame-0 footer at y=407; do not draw
       it twice or let its unmapped hover index select frame 1. */
    draw_configured_buttons(dc, 1, "NEWBUTT", &g_new_buttons);
    draw_sprite(dc, &g_realm_art, (uint32_t)g_menu.selected_tribe, 60, 40);
    draw_sprite(dc, &g_realm_art,
                (uint32_t)((g_menu.selected_tribe + 1) % 4), 140, 40);
    draw_sprite(dc, &g_difficulty_art, (uint32_t)g_menu.difficulty, 320, 240);
    {
        uint32_t tribe_frame = (uint32_t)(g_menu.selected_tribe * 17);
        uint32_t animation_frame = tribe_frame + ((g_menu.animation_ticks / 2u) % 16u) + 1u;
        unsigned game_tick = g_menu.animation_ticks / 2u;
        int floater_y = 38 + (int)(sin((double)(game_tick % 24u) *
                                       0.261799388) * 5.0) -
                        (g_menu.selected_tribe == 3 ? 5 : 0);
        /* FUN_0044ec5d draws the tribe's base frame and a cycling overlay
           frame at the same point; drawing only the overlay loses half of
           the original floater artwork. */
        draw_sprite(dc, &g_big_floaters, tribe_frame, 530, floater_y);
        draw_sprite(dc, &g_big_floaters, animation_frame, 530, floater_y);
    }
    for (tribe = 0; tribe < 4; ++tribe) {
        draw_sprite(dc, &g_glyphs,
                    (uint32_t)(tribe * 20 + (g_menu.animation_ticks / 3u) % 20u),
                    tribe_centers[tribe].x, tribe_centers[tribe].y);
    }
    draw_tribe_descriptions(dc);
    draw_hover_help(dc);
    draw_newgame_text(dc);
}

static void world_island_position(const WorldIsland *island, int *x, int *y)
{
    const float scale_x = 0.12999999523162842f;
    const float scale_y = 0.06000000238418579f;
    /* FUN_00471536 uses angle - phase. Keep WORLDPOS immutable and advance
       the phase by 0.25 degree per 33 ms remake animation tick. */
    float angle = ((float)island->angle_degrees -
                   (float)(g_menu.animation_ticks % 1440u) * 0.25f) *
                  0.017453277f;
    float x_delta = (float)(cos((double)angle) * island->range * scale_x);
    float y_delta = (float)(sin((double)angle) * island->range * scale_y);
    float z_delta = (float)island->z * scale_y;
    /* FUN_00470259 sets the centre to half the WORLDVIEW pane (0 0 639 479,
       inclusive coordinates as the other Iw* panes): cx = 639 / 2 and
       cy = 479 / 2 + 15 (this+0x784/0x786). */
    *x = 319 + (int)(x_delta + 0.5f);
    *y = 254 - (int)(y_delta + z_delta + 0.5f);
}

static uint8_t world_map_player_mask(void)
{
    if (g_game_session.config.selected_tribe >= GAME_START_PLAYER_COUNT) return 0;
    return (uint8_t)(1U << g_game_session.config.selected_tribe);
}

/* Stable within a rendered frame but advanced by the map's 33 ms timer.
   Drawing must not consume the gameplay RNG because WM_PAINT can run for
   reasons unrelated to simulation time. */
static uint32_t world_map_visual_sample(uint32_t tick, size_t bridge_index,
                                        int step, int spark)
{
    uint32_t value = tick * UINT32_C(0x9e3779b9) +
                     (uint32_t)bridge_index * UINT32_C(0x85ebca6b) +
                     (uint32_t)step * UINT32_C(0xc2b2ae35) +
                     (uint32_t)spark * UINT32_C(0x27d4eb2f);
    value ^= value >> 16;
    value *= UINT32_C(0x7feb352d);
    value ^= value >> 15;
    value *= UINT32_C(0x846ca68b);
    return value ^ (value >> 16);
}

static uint32_t world_island_frame_index(size_t island_index, int shape_id,
                                         int hovered)
{
    int offset;
    if (!g_game_session_valid || island_index >= UINT8_MAX || shape_id < 0) return UINT32_MAX;
    offset = game_session_world_map_frame_offset(
        &g_game_session, (uint8_t)island_index, world_map_player_mask(),
        hovered);
    return offset < 0 ? UINT32_MAX : (uint32_t)offset + (uint32_t)shape_id;
}

/* FUN_00472013 walks display items back-to-front and checks the opaque SHP
   bounds prepared by FUN_00405e11. The remake uses the same opaque bounds. */
