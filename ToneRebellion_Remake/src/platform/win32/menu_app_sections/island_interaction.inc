static int open_island_view(HWND window, int map_island_index)
{
    const WorldDefinition *world;
    int island_id;
    char error[256];
    if (g_menu.world_index < 0 || g_menu.world_index >= g_menu.world_map.world_count) return 0;
    world = &g_menu.world_map.worlds[g_menu.world_index];
    if (map_island_index < 0 || map_island_index >= world->island_count) return 0;
    if (!g_game_session_valid || g_game_session_world_index != g_menu.world_index) {
        if (!load_game_session_for_selected_world(error, sizeof(error))) {
            MessageBoxA(window, error, "Tone Rebellion remake - game setup error",
                        MB_OK | MB_ICONERROR);
            return 0;
        }
    }
    if (!game_session_can_enter_island(&g_game_session,
                                       (uint8_t)map_island_index,
                                       (uint8_t)(1U << g_game_session.config.selected_tribe))) {
        return 0;
    }
    island_id = world->islands[map_island_index].shape_id;
    if (!load_island_surface(island_id, map_island_index, error, sizeof(error))) {
        MessageBoxA(window, error, "Tone Rebellion remake - island data error",
                    MB_OK | MB_ICONERROR);
        return 0;
    }
    g_menu.selected_map_island = map_island_index;
    g_selected_floater = -1;
    g_menu.screen = SCREEN_ISLAND;
    {
        char tune_id[16];
        if (game_music_enter_realm(&g_game_music, (uint8_t)island_id,
                                   (uint8_t)g_game_session.config.selected_tribe,
                                   &g_game_session.random_state,
                                   tune_id, sizeof(tune_id))) {
            if (tune_id[0] != '\0') set_background_tune(tune_id);
        }
    }
    update_window_title(window);
    InvalidateRect(window, NULL, FALSE);
    return 1;
}

static int island_location_at(int x, int y)
{
    int map_x = x + g_island_scroll_x;
    int map_y = y;
    int index = (int)g_island_surface_data.location_count - 1;
    if (x < 0 || x >= LOGICAL_WIDTH || map_y < 0 || map_y >= 320) return -1;
    for (; index >= 0; --index) {
        const IslandLocation *location = &g_island_surface_data.locations[index];
        int dx = map_x - location->x;
        int dy = map_y - location->y;
        if (dx * dx + dy * dy <= 100) return index;
    }
    return -1;
}

static int update_island_location_hover(int x, int y)
{
    int location = g_menu.screen == SCREEN_ISLAND ? island_location_at(x, y) : -1;
    if (location == g_hovered_location) return 0;
    g_hovered_location = location;
    return 1;
}

static IslandLocationActionControl selected_location_action(void)
{
    const GameRuntimeIsland *island;
    const GameRuntimeLocation *location;
    if (!g_game_session_valid || g_menu.screen != SCREEN_ISLAND ||
        g_menu.selected_tribe < 0 ||
        g_menu.selected_tribe >= GAME_START_PLAYER_COUNT ||
        g_menu.selected_map_island < 0 ||
        g_menu.selected_map_island >= g_game_session.island_count ||
        g_selected_location < 0) return ISLAND_LOCATION_ACTION_NONE;
    island = &g_game_session.islands[g_menu.selected_map_island];
    if (g_selected_location >= island->location_count) {
        return ISLAND_LOCATION_ACTION_NONE;
    }
    location = &island->locations[g_selected_location];
    return island_panel_location_action_control(
        location->record_value_10, location->owner_id, g_menu.selected_tribe);
}

static int selected_repair_button_visible(void)
{
    const GameRuntimeIsland *island;
    int16_t current_hit_points;
    int16_t maximum_hit_points;
    if (!g_game_session_valid || g_menu.screen != SCREEN_ISLAND ||
        g_menu.selected_map_island < 0 ||
        g_menu.selected_map_island >= g_game_session.island_count ||
        g_selected_location < 0) return 0;
    island = &g_game_session.islands[g_menu.selected_map_island];
    if (g_selected_location >= island->location_count) return 0;
    if (!game_session_repair_location_values(&g_game_session, &g_pad_catalog,
            (uint8_t)g_menu.selected_map_island,
            (uint16_t)g_selected_location,
            &current_hit_points, &maximum_hit_points)) return 0;
    return island_panel_repair_button_visible(
        island->locations[g_selected_location].record_value_10,
        island->locations[g_selected_location].owner_id,
        g_game_session.config.selected_tribe,
        current_hit_points, maximum_hit_points);
}

static int selected_onoff_button_visible(void)
{
    const GameRuntimeIsland *island;
    const GameRuntimeLocation *location;
    if (!g_game_session_valid || g_menu.screen != SCREEN_ISLAND ||
        g_menu.selected_map_island < 0 ||
        g_menu.selected_map_island >= g_game_session.island_count ||
        g_selected_location < 0) return 0;
    island = &g_game_session.islands[g_menu.selected_map_island];
    if (g_selected_location >= island->location_count) return 0;
    location = &island->locations[g_selected_location];
    return island_panel_onoff_button_visible(location->record_value_10,
        location->renderer_class, location->owner_id,
        g_game_session.config.selected_tribe);
}

static void draw_control_with_hover_overlay(HDC dc,
        const WindowTemplate *control, const SpriteSheet *art, int hovered)
{
    int32_t frames[2];
    size_t frame_count = window_catalog_control_render_frames(
        control, hovered, frames);
    size_t frame_index;
    if (control == NULL || art == NULL) return;
    for (frame_index = 0; frame_index < frame_count; ++frame_index) {
        if (frames[frame_index] >= 0 &&
            (uint32_t)frames[frame_index] < art->frame_count) {
            draw_sprite(dc, art, (uint32_t)frames[frame_index],
                        control->pane.left, control->pane.top);
        }
    }
}

static int update_location_action_hover(int x, int y)
{
    const char *const move_names[] = {"IWMove", "IWHallMove"};
    static const char *const repair_names[] = {"BC_Repair"};
    static const char *const onoff_names[] = {"BC_OnOff"};
    IslandLocationActionControl action = selected_location_action();
    const char *name = action == ISLAND_LOCATION_ACTION_HALL_MOVE
        ? "IWHallMove" : action == ISLAND_LOCATION_ACTION_MOVE
        ? "IWMove" : NULL;
    const WindowTemplate *control = name != NULL
        ? window_catalog_hit_test_names(&g_window_catalog, 3, x, y,
                                        move_names, 2)
        : NULL;
    const GameRuntimeIsland *island = NULL;
    const WindowTemplate *repair_control = NULL;
    const WindowTemplate *onoff_control = NULL;
    int repair_hovered = 0;
    int onoff_hovered = 0;
    if (g_game_session_valid && g_menu.screen == SCREEN_ISLAND &&
        g_island_panel_mode == WINDOW_ISLAND_PANEL_GENERAL &&
        g_menu.selected_map_island >= 0 &&
        g_menu.selected_map_island < g_game_session.island_count &&
        g_selected_location >= 0) {
        island = &g_game_session.islands[g_menu.selected_map_island];
        if (g_selected_location < island->location_count) {
            if (selected_repair_button_visible()) {
                repair_control = window_catalog_hit_test_names(&g_window_catalog,
                    3, x, y, repair_names,
                    sizeof(repair_names) / sizeof(repair_names[0]));
            }
            if (selected_onoff_button_visible()) {
                onoff_control = window_catalog_hit_test_names(&g_window_catalog,
                    3, x, y, onoff_names,
                    sizeof(onoff_names) / sizeof(onoff_names[0]));
            }
        }
    }
    repair_hovered = repair_control != NULL &&
        strcmp(repair_control->name, "BC_Repair") == 0;
    onoff_hovered = onoff_control != NULL &&
        strcmp(onoff_control->name, "BC_OnOff") == 0;
    IslandLocationActionControl hovered = ISLAND_LOCATION_ACTION_NONE;
    if (control != NULL && strcmp(control->name, name) == 0) hovered = action;
    if (hovered == g_hovered_location_action &&
        repair_hovered == g_hovered_repair_control &&
        onoff_hovered == g_hovered_onoff_control) return 0;
    g_hovered_location_action = hovered;
    g_hovered_repair_control = repair_hovered;
    g_hovered_onoff_control = onoff_hovered;
    return 1;
}

static int selected_hall_player(void)
{
    unsigned int player;
    const GameRuntimeIsland *island;
    const GameRuntimeLocation *hall;
    if (!g_game_session_valid || g_menu.screen != SCREEN_ISLAND ||
        g_menu.selected_tribe >= GAME_START_PLAYER_COUNT ||
        g_menu.selected_map_island < 0 ||
        g_menu.selected_map_island >= g_game_session.island_count ||
        g_selected_location < 0) return -1;
    player = g_menu.selected_tribe;
    if (g_game_session.economy[player].hall_island_index !=
            (uint8_t)g_menu.selected_map_island ||
        g_game_session.economy[player].hall_location_index !=
            (uint16_t)g_selected_location) return -1;
    island = &g_game_session.islands[g_menu.selected_map_island];
    if (g_selected_location >= island->location_count) return -1;
    hall = &island->locations[g_selected_location];
    if (hall->owner_id != (int32_t)player ||
        hall->record_value_10 != (int32_t)(0x2aU + player * 16U)) return -1;
    return (int)player;
}

/* The source roster query FUN_0045d7e8 selects entries from the player's
   list by level. The current session models only the four initial level-0
   workers, so their owner-list order is the only roster subset we can render. */
static uint8_t collect_initial_worker_roster(unsigned int player,
                                             int indices[ISLAND_PANEL_INFO_ROSTER_SLOT_COUNT])
{
    uint8_t count = 0;
    unsigned int i;
    if (indices == NULL || player >= GAME_START_PLAYER_COUNT ||
        !g_game_session_valid) return 0;
    for (i = 0; i < ISLAND_PANEL_INFO_ROSTER_SLOT_COUNT; ++i) indices[i] = -1;
    for (i = 0; i < g_game_session.floater_count &&
         count < ISLAND_PANEL_INFO_ROSTER_SLOT_COUNT; ++i) {
        const GameFloaterStart *floater = &g_game_session.floaters[i];
        if (floater->owner_slot != player || floater->type_index >= 4) continue;
        indices[count++] = (int)i;
    }
    return count;
}

static int selected_hall_roster_hit_test(int x, int y)
{
    int roster[ISLAND_PANEL_INFO_ROSTER_SLOT_COUNT];
    const WindowTemplate *info;
    int player = selected_hall_player();
    uint8_t count;
    uint8_t occupied = 0;
    uint8_t slot;
    int special_layout = 0;
    const GameRuntimeIsland *island;
    if (player < 0) return -1;
    count = collect_initial_worker_roster((unsigned int)player, roster);
    if (count == 0) return -1;
    for (slot = 0; slot < count; ++slot) occupied |= (uint8_t)(1u << slot);
    island = &g_game_session.islands[g_menu.selected_map_island];
    if ((uint16_t)g_selected_location < island->location_count) {
        special_layout = island->locations[g_selected_location].record_value_10 == 0x2f;
    }
    info = window_catalog_find(&g_window_catalog, "IWLocInfo", 3);
    if (info == NULL) return -1;
    slot = (uint8_t)island_panel_info_roster_hit_test(
        info->pane.left, info->pane.top, x, y, special_layout, occupied);
    return slot < ISLAND_PANEL_INFO_ROSTER_SLOT_COUNT ? roster[slot] : -1;
}

static int hall_stock_control_at(int x, int y)
{
    static const char *const names[] = {
        "BC_HallStkB", "BC_HallStkC", "BC_HallStkM"
    };
    const WindowTemplate *control = window_catalog_hit_test_names(
        &g_window_catalog, 3, x, y, names, sizeof(names) / sizeof(names[0]));
    if (control == NULL) return -1;
    if (strcmp(control->name, "BC_HallStkB") == 0) return GAME_RESOURCE_BUILD_TONE;
    if (strcmp(control->name, "BC_HallStkC") == 0) return GAME_RESOURCE_CRYSTAL_TONE;
    if (strcmp(control->name, "BC_HallStkM") == 0) return GAME_RESOURCE_MAGIC_TONE;
    return -1;
}

static int update_hall_stock_hover(int x, int y)
{
    int hovered = selected_hall_player() >= 0 ? hall_stock_control_at(x, y) : -1;
    if (hovered == g_hovered_hall_stock) return 0;
    g_hovered_hall_stock = hovered;
    return 1;
}

static int island_button_index(const char *name)
{
    return window_catalog_island_button(name);
}

static int update_island_button_hover(int x, int y)
{
    static const char *const names[] = {
        "GOTOMAP", "PANIC", "TOGREALM", "TASKLIST"
    };
    const WindowTemplate *control = window_catalog_hit_test_names(
        &g_window_catalog, 3, x, y, names, sizeof(names) / sizeof(names[0]));
    int hovered = control != NULL ? island_button_index(control->name) : -1;
    if (hovered == g_hovered_island_button) return 0;
    g_hovered_island_button = hovered;
    return 1;
}

static int update_hall_command_hover(int x, int y)
{
    static const char *const names[] = {
        "BC_GenInfo", "BC_Storage", "BC_Knowledge", "BC_Trade", "BC_Diplomacy"
    };
    const WindowTemplate *control = selected_hall_player() >= 0
        ? window_catalog_hit_test_names(&g_window_catalog, 3, x, y,
              names, sizeof(names) / sizeof(names[0])) : NULL;
    int hovered = control != NULL
        ? window_catalog_hall_panel_mode(control->name)
        : WINDOW_ISLAND_PANEL_NONE;
    if (hovered == g_hovered_hall_command) return 0;
    g_hovered_hall_command = hovered;
    return 1;
}

static int inventory_item_at(int x, int y)
{
    int hall_player = selected_hall_player();
    if (g_menu.screen == SCREEN_ISLAND && hall_player >= 0 &&
        g_island_panel_mode == WINDOW_ISLAND_PANEL_INVENTORY) {
        const WindowTemplate *panel = window_catalog_find(
            &g_window_catalog, "IWInventory", 3);
        if (panel != NULL) {
            GameInventoryEntry entries[GAME_INVENTORY_ITEM_COUNT];
            size_t entry_count = game_inventory_collect(
                g_game_session.economy[(unsigned int)hall_player].inventory_count,
                entries, GAME_INVENTORY_ITEM_COUNT);
            return game_inventory_hit_test(entries, entry_count,
                g_inventory_page, x, y, panel->pane.left, panel->pane.top,
                panel->pane.right, panel->pane.bottom);
        }
    }
    return -1;
}

static int update_inventory_hover(int x, int y)
{
    int hovered = inventory_item_at(x, y);
    if (hovered == g_hovered_inventory_item) return 0;
    g_hovered_inventory_item = hovered;
    /* FUN_0043d45c sends the hovered ID to IWTextInfo; 0x42 selection is
       emitted only by FUN_0043d41a on click. */
    g_inventory_info_mode = ISLAND_PANEL_INFO_INVENTORY_DETAIL;
    return 1;
}

static int update_glyph_hover(int x, int y)
{
    int hall_player = selected_hall_player();
    const WindowTemplate *panel;
    const GamePlayerEconomy *economy;
    GameGlyphCenter centers[GAME_GLYPH_COUNT];
    int pane_width;
    int pane_height;
    unsigned int glyph_index;
    int hovered;

    if (g_menu.screen != SCREEN_ISLAND || hall_player < 0 ||
        g_island_panel_mode != WINDOW_ISLAND_PANEL_GLYPHS) return 0;
    panel = window_catalog_find(&g_window_catalog, "IWGlyphs", 3);
    if (panel == NULL) return 0;

    economy = &g_game_session.economy[(unsigned int)hall_player];
    if (x >= panel->pane.left && x <= panel->pane.right &&
        y >= panel->pane.top && y <= panel->pane.bottom) {
        pane_width = panel->pane.right - panel->pane.left;
        pane_height = panel->pane.bottom - panel->pane.top;
        for (glyph_index = 0; glyph_index < GAME_GLYPH_COUNT; ++glyph_index) {
            const SpriteFrame *frame = &g_glyph_inventory_art.frames[glyph_index + 1U];
            if (frame->hit_right <= frame->hit_left ||
                frame->hit_bottom <= frame->hit_top) {
                centers[glyph_index].x = -10000;
                centers[glyph_index].y = -10000;
                continue;
            }
            centers[glyph_index].x = pane_width + frame->x_offset + frame->hit_left +
                (frame->hit_right - frame->hit_left + 1) / 2;
            centers[glyph_index].y = pane_height + frame->y_offset + frame->hit_top +
                (frame->hit_bottom - frame->hit_top + 1) / 2;
        }
        hovered = game_glyph_inventory_update_hover(g_hovered_glyph,
            economy->glyph_mask, centers, 1, x - panel->pane.left,
            y - panel->pane.top);
    } else {
        hovered = game_glyph_inventory_update_hover(g_hovered_glyph,
            economy->glyph_mask, NULL, 0, 0, 0);
    }
    if (hovered == g_hovered_glyph) return 0;
    g_hovered_glyph = hovered;
    g_glyph_info_default = 0;
    return 1;
}

static int adjust_trade_cell(int x, int y, int direction)
{
    const WindowTemplate *panel;
    uint8_t resource_row;
    uint8_t target_column;
    int hall_player = selected_hall_player();
    if (g_menu.screen != SCREEN_ISLAND || hall_player < 0 ||
        g_island_panel_mode != WINDOW_ISLAND_PANEL_TRADE) return 0;
    panel = window_catalog_find(&g_window_catalog, "IWTrade", 3);
    if (panel == NULL ||
        !game_trade_cell_at(x - panel->pane.left, y - panel->pane.top,
                            &resource_row, &target_column)) return 0;
    return game_session_adjust_trade_offer(&g_game_session,
        (uint8_t)hall_player, resource_row, target_column, direction);
}

static int update_diplomacy_hover(int x, int y)
{
    const WindowTemplate *panel;
    GameDiplomacyHit hit;
    int has_hit;
    int changed;
    if (g_menu.screen != SCREEN_ISLAND || selected_hall_player() < 0 ||
        g_island_panel_mode != WINDOW_ISLAND_PANEL_DIPLOMACY) {
        has_hit = 0;
    } else {
        panel = window_catalog_find(&g_window_catalog, "IWDiplomacy", 3);
        has_hit = panel != NULL && game_diplomacy_hit_test(
            x, y, panel->pane.left, panel->pane.top,
            panel->pane.right, panel->pane.bottom, &hit);
    }
    changed = has_hit != g_diplomacy_hover_valid;
    if (has_hit && (!g_diplomacy_hover_valid ||
        hit.action != g_diplomacy_hover.action ||
        hit.displayed_column != g_diplomacy_hover.displayed_column)) {
        g_diplomacy_hover = hit;
        changed = 1;
    }
    g_diplomacy_hover_valid = has_hit;
    return changed;
}

static int click_diplomacy_action(int x, int y, int player_slot)
{
    const WindowTemplate *panel;
    GameDiplomacyHit hit;
    uint8_t target_player;
    if (player_slot < 0 || g_island_panel_mode != WINDOW_ISLAND_PANEL_DIPLOMACY) {
        return 0;
    }
    panel = window_catalog_find(&g_window_catalog, "IWDiplomacy", 3);
    if (panel == NULL || !game_diplomacy_hit_test(
        x, y, panel->pane.left, panel->pane.top,
        panel->pane.right, panel->pane.bottom, &hit) ||
        !game_diplomacy_target_player((uint8_t)player_slot,
                                      hit.displayed_column, &target_player)) {
        return 0;
    }
    (void)game_session_toggle_diplomacy(&g_game_session,
        (uint8_t)player_slot, target_player, hit.action);
    return 1;
}

static int open_iw_construct(int location_index)
{
    const IslandLocation *site;
    const GameRuntimeIsland *runtime_island;
    char error[96];

    if (!g_game_session_valid || g_menu.selected_map_island < 0 ||
        g_menu.selected_map_island >= g_game_session.island_count ||
        location_index < 0 || location_index >= g_island_surface_data.location_count) {
        return 0;
    }
    site = &g_island_surface_data.locations[location_index];
    runtime_island = &g_game_session.islands[g_menu.selected_map_island];
    if (location_index >= runtime_island->location_count ||
        runtime_island->locations[location_index].renderer_class != 0 ||
        runtime_island->locations[location_index].record_value_10 != 0 ||
        runtime_island->locations[location_index].owner_id != -1) return 0;

    /* Initial new-game state gives each player one home island. The rule-set
       selector is still unresolved; at owned-island count 1 the only gated
       row that can pass is candidate 44, whose threshold is 1 in all tables. */
    if (!iw_construct_build_list_for_site(
            &g_pad_catalog, g_game_session.config.selected_tribe, site, 0, 1,
            g_iw_construct_items,
            sizeof(g_iw_construct_items) / sizeof(g_iw_construct_items[0]),
            &g_iw_construct_item_count) || g_iw_construct_item_count == 0) return 0;

    iw_construct_init(&g_iw_construct, g_iw_construct_item_count);
    iw_construct_info_init(&g_iw_construct_info);
    g_iw_construct_open = 1;
    return 1;
}

static int apply_iw_construct_messages(const IwConstructTransition *transition)
{
    unsigned int i;
    int old_item = g_iw_construct_info.item_id;
    if (transition == NULL) return 0;
    for (i = 0; i < transition->message_count; ++i) {
        if (transition->messages[i].code == IW_CONSTRUCT_MSG_SELECT_HOVER) {
            (void)iw_construct_info_handle_message(
                &g_iw_construct_info, IW_CONSTRUCT_INFO_MSG_ITEM,
                transition->messages[i].value);
        }
    }
    return transition->changed || old_item != g_iw_construct_info.item_id;
}

static int update_iw_construct_hover(int x, int y)
{
    const WindowTemplate *window;
    IwConstructTransition transition;

    if (!g_iw_construct_open) return 0;
    window = window_catalog_find(&g_window_catalog, "IWConstruct", 3);
    if (window == NULL) return 0;
    iw_construct_mouse_move(&g_iw_construct, &window->pane, x, y,
                            g_iw_construct_items, g_iw_construct_item_count,
                            &transition);
    return apply_iw_construct_messages(&transition);
}

static int select_iw_construct_item(void)
{
    IwConstructTransition transition;
    unsigned int i;
    int handled = 0;

    iw_construct_mouse_click(&g_iw_construct, g_game_session.config.selected_tribe,
                             &transition);
    for (i = 0; i < transition.message_count; ++i) {
        const IwConstructMessage *message = &transition.messages[i];
        if (message->code == IW_CONSTRUCT_MSG_SELECT_BUILD) {
            if (g_game_session_valid && message->value >= 0 &&
                message->value <= UINT16_MAX &&
                g_game_session.config.selected_tribe < GAME_START_PLAYER_COUNT &&
                g_menu.selected_map_island >= 0 &&
                g_menu.selected_map_island < g_game_session.island_count &&
                g_selected_location >= 0 &&
                g_selected_location <= UINT16_MAX &&
                g_selected_location < g_island_surface_data.location_count) {
                /* FUN_0042fa0f turns this selection message into the observed
                   category-0/type-5 request. Its consumer is unknown, so the
                   UI queues the packet and does not place the item here. */
                handled = 1;
                (void)game_session_queue_build_selection(
                    &g_game_session, g_game_session.config.selected_tribe,
                    (uint8_t)g_menu.selected_map_island,
                    (uint16_t)g_selected_location,
                    (uint16_t)message->value);
            }
        } else if (message->code == IW_CONSTRUCT_MSG_CLEAR_BUILD) {
            g_iw_construct_open = 0;
            (void)iw_construct_info_handle_message(&g_iw_construct_info, 1, 0);
        }
    }
    return handled;
}
