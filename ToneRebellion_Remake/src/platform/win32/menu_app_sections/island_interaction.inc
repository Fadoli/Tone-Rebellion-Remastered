/* Port records keep owner-specific item IDs (base + owner * 16); native
   predicates such as the 0x2f spell-caster hall tests read the base ID. */
static int32_t location_base_item_id(const GameRuntimeLocation *location)
{
    int32_t item = location->record_value_10;
    if (location->owner_id >= 0 && location->owner_id < GAME_START_PLAYER_COUNT)
        item -= location->owner_id * 16;
    return item;
}

/* FUN_00435ea7: clamp the camera x to [left, right - 0x27f] of the current
   player's island+0x408/+0x40c bounds (floater_min_x / floater_max_x), then to
   [0, 0x781]. Falls back to 0..1920 when no session is available. */
static int island_clamp_scroll(int scroll)
{
    int lo = 0;
    int hi = 1920;
    if (g_game_session_valid && g_menu.selected_tribe >= 0 &&
        g_menu.selected_tribe < GAME_FLOATER_CATEGORY_COUNT &&
        g_menu.selected_map_island >= 0 &&
        g_menu.selected_map_island < g_game_session.island_count) {
        const GameRuntimeIsland *island =
            &g_game_session.islands[g_menu.selected_map_island];
        lo = island->floater_min_x[g_menu.selected_tribe];
        hi = island->floater_max_x[g_menu.selected_tribe] - 0x27f;
        if (lo < 0) lo = 0;
        if (hi > 1920) hi = 1920;
        if (hi < lo) hi = lo;
        if (lo > 1920) lo = 1920;
    }
    return scroll < lo ? lo : scroll > hi ? hi : scroll;
}

/* Remake: the IWLilMap pane shows the whole 2560x320 island at 1/10 scale, so
   a pane x maps to world x * 10. Centre the 640-wide view on the point, clamped
   to the same 0..1920 range as the wheel and arrow keys. `clamp_to_pane`
   lets a drag keep scrolling when the cursor leaves the pane horizontally. */
static int island_lilmap_scroll_to(int x, int y, int clamp_to_pane)
{
    const WindowTemplate *mini_map;
    int scroll;
    if (g_menu.screen != SCREEN_ISLAND) return 0;
    mini_map = window_catalog_find(&g_window_catalog, "IWLilMap", 3);
    if (mini_map == NULL) return 0;
    if (!clamp_to_pane &&
        (x < mini_map->pane.left || x > mini_map->pane.right ||
         y < mini_map->pane.top || y > mini_map->pane.bottom)) return 0;
    scroll = (x - mini_map->pane.left) * 10 - LOGICAL_WIDTH / 2;
    scroll = island_clamp_scroll(scroll);
    if (scroll != g_island_scroll_x) {
        g_island_scroll_x = scroll;
        g_hovered_location = -1;
    }
    return 1;
}

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
    g_island_scroll_x = island_clamp_scroll(g_island_scroll_x);
    g_selected_floater = -1;
    g_menu.screen = SCREEN_ISLAND;
    {
        char tune_id[16];
        if (game_music_enter_realm(&g_game_music, (uint8_t)island_id,
                                   (uint8_t)g_game_session.config.selected_tribe,
                                   g_net_in_game ? &g_net_local_rng
                                                 : &g_game_session.random_state,
                                   tune_id, sizeof(tune_id))) {
            if (tune_id[0] != '\0') set_background_tune(tune_id);
        }
    }
    update_window_title(window);
    InvalidateRect(window, NULL, FALSE);
    return 1;
}

static int island_pad_group(const IslandLocation *location);
static int island_site_buildable_by_player(int location_index,
                                           int32_t *out_items,
                                           size_t *out_count);

/* FUN_00435826 + FUN_0042fa0f (0x32 path, bridge branch, ev_52232fe9...):
   clicking a constructed class-2 bridge marker switches to its partner island
   (message 0x4d) and scrolls to the partner marker, x = partner.x - 0x140
   (message 0x3d -> 0x35). No mode switch runs, so the open panel survives.
   The partner is the destination island's class-2 marker whose neighbour is
   the current island (FUN_00466c08). */
static int enter_bridge_destination(HWND window, int location_index)
{
    const GameRuntimeIsland *island;
    const GameRuntimeLocation *bridge;
    const GameRuntimeIsland *target;
    unsigned int i;
    int origin = g_menu.selected_map_island;
    int partner_x = -1;
    int saved_panel_mode = g_island_panel_mode;
    int saved_hovered_hall = g_hovered_hall_command;
    int saved_scroll_target;
    if (!g_game_session_valid || origin < 0 ||
        origin >= g_game_session.island_count || location_index < 0) return 0;
    island = &g_game_session.islands[origin];
    if ((unsigned int)location_index >= island->location_count) return 0;
    bridge = &island->locations[location_index];
    if (bridge->renderer_class != 2 || !bridge->bridge_constructed ||
        bridge->bridge_neighbor_island < 0 ||
        bridge->bridge_neighbor_island >= g_game_session.island_count) return 0;
    if (!game_session_bridge_marker_is_active(&g_game_session, (uint8_t)origin,
                                              (uint16_t)location_index)) return 0;
    target = &g_game_session.islands[bridge->bridge_neighbor_island];
    for (i = 0; i < target->location_count; ++i) {
        if (target->locations[i].renderer_class == 2 &&
            target->locations[i].bridge_neighbor_island == origin) {
            partner_x = target->locations[i].x;
            break;
        }
    }
    if (!open_island_view(window, bridge->bridge_neighbor_island)) return 0;
    g_island_panel_mode = saved_panel_mode;
    g_hovered_hall_command = saved_hovered_hall;
    if (partner_x >= 0) {
        saved_scroll_target = partner_x - 0x140;
        g_island_scroll_x = island_clamp_scroll(saved_scroll_target);
    }
    return 1;
}

/* An empty construction site the local tribe cannot build on is neither drawn
   nor clickable: it behaves like bare ground. */
static int island_site_is_hidden_pad(int location_index)
{
    const IslandLocation *location;
    const GameRuntimeIsland *runtime_island;
    const GameRuntimeLocation *runtime_location;
    if (!g_game_session_valid || g_menu.selected_map_island < 0 ||
        g_menu.selected_map_island >= g_game_session.island_count ||
        location_index < 0 ||
        location_index >= g_island_surface_data.location_count) return 0;
    location = &g_island_surface_data.locations[location_index];
    runtime_island = &g_game_session.islands[g_menu.selected_map_island];
    if (location_index >= runtime_island->location_count) return 0;
    runtime_location = &runtime_island->locations[location_index];
    if (location->kind != ISLAND_LOCATION_PAD &&
        island_pad_group(location) < 0) return 0;
    if (runtime_location->renderer_class != 0 ||
        runtime_location->record_value_10 > 0) return 0;
    return !island_site_buildable_by_player(location_index, NULL, NULL);
}

/* FUN_00435581 location pass: a site is pickable when its class (+4) or item
   (+0x10) is nonzero, or the active player's bit is set in the visibility
   byte (+0x22); there is no explored-cell test
   (ev_fd65e30cf8e5016cd62c94f95aa773e60aa16693a519b2f4d4e9c34963c9d2ae). */
static int island_location_pickable(int location_index)
{
    const GameRuntimeIsland *island;
    const GameRuntimeLocation *location;
    if (!g_game_session_valid || g_menu.selected_tribe < 0 ||
        g_menu.selected_tribe >= GAME_START_PLAYER_COUNT) return 1;
    if (g_menu.selected_map_island < 0 ||
        g_menu.selected_map_island >= g_game_session.island_count) return 1;
    island = &g_game_session.islands[g_menu.selected_map_island];
    if (location_index < 0 || (unsigned int)location_index >= island->location_count)
        return 1;
    location = &island->locations[location_index];
    return location->renderer_class != 0 || location->record_value_10 != 0 ||
        (location->tribe_visibility_mask >> g_menu.selected_tribe & 1U) != 0;
}

/* FUN_00435581 location zone: |dx| < W and -W/2 < dy < W/2 around the site,
   W from DAT_0049f560 = {20, 30, 40}: class != 0 uses 40, an empty class-0
   site its subtype index, a built item the pad row's size. The native extra
   upward reach (byte of FUN_00456a87's shape entry, meaning unknown) is not
   modelled (ev_fd65e30cf8e5016cd62c94f95aa773e60aa16693a519b2f4d4e9c34963c9d2ae,
   ev_817a8f60...). */
static int island_location_hit_width(int location_index)
{
    static const int widths[3] = {20, 30, 40};
    const IslandLocation *location =
        &g_island_surface_data.locations[location_index];
    const GameRuntimeIsland *island;
    const GameRuntimeLocation *runtime = NULL;
    int index = location->renderer_subtype;
    if (location->renderer_class != 0) return widths[2];
    if (g_game_session_valid && g_menu.selected_map_island >= 0 &&
        g_menu.selected_map_island < g_game_session.island_count) {
        island = &g_game_session.islands[g_menu.selected_map_island];
        if ((unsigned int)location_index < island->location_count) {
            runtime = &island->locations[location_index];
        }
    }
    if (runtime != NULL && runtime->renderer_class != 0) return widths[2];
    if (runtime != NULL && runtime->record_value_10 > 0 &&
        (unsigned int)runtime->record_value_10 < g_pad_catalog.item_count) {
        int size = g_pad_catalog.items[runtime->record_value_10].size;
        if (size >= 0 && size <= 2) index = size;
    }
    if (index < 0 || index > 2) index = 2;
    return widths[index];
}

static int island_location_at(int x, int y)
{
    int map_x = x + g_island_scroll_x;
    int map_y = y;
    int index;
    if (x < 0 || x >= LOGICAL_WIDTH || map_y < 0 || map_y >= 320) return -1;
    /* The native loop returns the first match in record order. */
    for (index = 0; index < (int)g_island_surface_data.location_count; ++index) {
        const IslandLocation *location = &g_island_surface_data.locations[index];
        int dx = map_x - location->x;
        int dy = map_y - location->y;
        int width;
        if (dx < 0) dx = -dx;
        if (dx >= 101 || island_site_is_hidden_pad(index) ||
            !island_location_pickable(index)) continue;
        width = island_location_hit_width(index);
        if (dx < width && dy > -(width / 2) && dy < width / 2) return index;
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
        selection_island() < 0 ||
        selection_island() >= g_game_session.island_count ||
        g_selected_location < 0) return ISLAND_LOCATION_ACTION_NONE;
    island = &g_game_session.islands[selection_island()];
    if (g_selected_location >= island->location_count) {
        return ISLAND_LOCATION_ACTION_NONE;
    }
    location = &island->locations[g_selected_location];
    /* record_value_10 is owner-specific (base + owner * 16); the control
       choice (Hall vs. other buildings) tests the base ID. */
    return island_panel_location_action_control(
        location->owner_id >= 0 && location->owner_id < GAME_START_PLAYER_COUNT
            ? location->record_value_10 - location->owner_id * 16
            : location->record_value_10,
        location->owner_id, g_menu.selected_tribe);
}

static int selected_repair_button_visible(void)
{
    const GameRuntimeIsland *island;
    int16_t current_hit_points;
    int16_t maximum_hit_points;
    if (!g_game_session_valid || g_menu.screen != SCREEN_ISLAND ||
        selection_island() < 0 ||
        selection_island() >= g_game_session.island_count ||
        g_selected_location < 0) return 0;
    island = &g_game_session.islands[selection_island()];
    if (g_selected_location >= island->location_count) return 0;
    if (!game_session_repair_location_values(&g_game_session, &g_pad_catalog,
            (uint8_t)selection_island(),
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
        selection_island() < 0 ||
        selection_island() >= g_game_session.island_count ||
        g_selected_location < 0) return 0;
    island = &g_game_session.islands[selection_island()];
    if (g_selected_location >= island->location_count) return 0;
    location = &island->locations[g_selected_location];
    return island_panel_onoff_button_visible(location->record_value_10,
        location->renderer_class, location->owner_id,
        g_game_session.config.selected_tribe);
}

static int selected_upgrade_button_visible(void)
{
    const GameRuntimeIsland *island;
    const GameRuntimeLocation *location;
    int32_t base_item_id;

    if (!g_game_session_valid || g_menu.screen != SCREEN_ISLAND ||
        g_menu.selected_tribe < 0 ||
        g_menu.selected_tribe >= GAME_START_PLAYER_COUNT ||
        selection_island() < 0 ||
        selection_island() >= g_game_session.island_count ||
        g_selected_location < 0) return 0;
    island = &g_game_session.islands[selection_island()];
    if ((unsigned int)g_selected_location >= island->location_count) return 0;
    location = &island->locations[g_selected_location];
    /* FUN_0045302a lists BC_Upgrade (id 2, through FUN_0045d5ba) only for
       an owned site with a source record (+0x18 != -1, ev_acb06186,
       ev_ae0e78b3); a building left without a record has no button. */
    if (location->renderer_class != 0 ||
        location->owner_id != g_menu.selected_tribe ||
        location->source_location_slot_18 == -1) return 0;
    base_item_id = location->record_value_10 -
        (int32_t)g_menu.selected_tribe * 16;

    /* Source buildings 0x2c..0x30 only: the Hall tier is raised automatically
       by update_player_hall_tier, so its Upgrade button stays hidden. */
    return base_item_id >= 0x2c && base_item_id <= 0x30;
}

static const char *const k_spell_button_names[8] = {
    "BC_Spell1", "BC_Spell2", "BC_Spell3", "BC_Spell4",
    "BC_Spell5", "BC_Spell6", "BC_Spell7", "BC_Spell8"
};

/* The selected (+0x16c) owned item 0x2f/0x30 site with a staff record whose
   BC_Spell buttons FUN_0045d5ba lists, on any island, else NULL. Like the
   order buttons these show in the building panel (FUN_0042f755 mode 3) as
   well as in the general one. */
static const GameRuntimeLocation *selected_spell_hall(void)
{
    const GameRuntimeLocation *location;
    int island_index = selection_island();
    if (!g_game_session_valid || g_menu.screen != SCREEN_ISLAND ||
        !island_panel_location_info_visible(g_island_panel_mode) ||
        g_menu.selected_tribe < 0 ||
        g_menu.selected_tribe >= GAME_START_PLAYER_COUNT ||
        island_index < 0 || island_index >= g_game_session.island_count ||
        g_selected_location < 0 ||
        g_selected_location >= g_game_session.islands[island_index].location_count)
        return NULL;
    location = &g_game_session.islands[island_index].locations[g_selected_location];
    if (location->renderer_class != 0 ||
        location->owner_id != g_menu.selected_tribe ||
        location->source_location_slot_18 < 0 ||
        (location_base_item_id(location) != 0x2f &&
         location_base_item_id(location) != 0x30)) return NULL;
    return location;
}

static int selected_cast_action_at(int x, int y)
{
    const GameRuntimeLocation *location = selected_spell_hall();
    const WindowTemplate *button;
    unsigned int index;

    if (location == NULL) return -1;
    button = window_catalog_hit_test_names(&g_window_catalog, 3, x, y,
        k_spell_button_names, 8);
    if (button == NULL) return -1;
    for (index = 0; index < 8; ++index) {
        if (strcmp(button->name, k_spell_button_names[index]) == 0) {
            /* FUN_0045d5ba lists all eight BC_Spell buttons for 0x2f/0x30;
               the dispatcher covers kinds 0..0x15. */
            int kind = game_session_cast_kind_for_action(
                (uint8_t)location->source_value_14,
                (uint8_t)(0x15U + index));
            return kind >= 0 && kind <= 0x15 ? (int)(0x15U + index) : -1;
        }
    }
    return -1;
}

/* FUN_0042fa0f msg 0x65 sub 0x15..0x1c: DAT_004a2898[kind] == 0 sends the
   cast at once with the building as target; otherwise FUN_0043530b arms a
   site (1) or floater (2) pick. Pressing the armed button again disarms it
   (port convenience, like the order buttons). */
static void press_cast_action(int action)
{
    int kind = game_session_cast_kind_for_action(
        (uint8_t)g_game_session.islands[selection_island()]
            .locations[g_selected_location].source_value_14,
        (uint8_t)action);
    int pick = game_session_cast_kind_target_pick(kind);
    g_defend_area_armed = 0;
    if (pick == 0) {
        g_armed_spell_action = 0;
        (void)ISSUE_COMMAND(GAME_COMMAND_QUEUE_CAST_ACTION,
            (uint8_t)g_menu.selected_tribe, (uint8_t)selection_island(),
            (uint16_t)g_selected_location, (uint8_t)action, -1,
            (uint8_t)selection_island(), -1);
    } else if (pick > 0) {
        g_armed_spell_action = g_armed_spell_action == action ? 0 : action;
        g_armed_spell_pick = pick;
    }
    update_interaction_cursor();
}

/* FUN_00435826 in a spell mode: a site click under pick 1 sends msg 0x40
   (clicked island/site), a floater click under pick 2 msg 0x41 (viewed
   island, floater); both clear the mode. Any other click clears it and is
   handled as a plain selection (local_8 path). Returns 1 when consumed. */
static int island_spell_target_click(int clicked_floater, int x, int y)
{
    int action = g_armed_spell_action;
    int building_island = selection_island();
    int clicked_location;
    if (action == 0) return 0;
    g_armed_spell_action = 0;
    update_interaction_cursor();
    if (building_island < 0 || building_island >= g_game_session.island_count ||
        g_selected_location < 0 ||
        g_selected_location >= g_game_session.islands[building_island].location_count)
        return 0;
    clicked_location = clicked_floater >= 0 ? -1 : island_location_at(x, y);
    if (g_armed_spell_pick == 1 && clicked_location >= 0) {
        (void)ISSUE_COMMAND(GAME_COMMAND_QUEUE_CAST_ACTION,
            (uint8_t)g_menu.selected_tribe, (uint8_t)building_island,
            (uint16_t)g_selected_location, (uint8_t)action, -1,
            (uint8_t)g_menu.selected_map_island, clicked_location);
        return 1;
    }
    if (g_armed_spell_pick == 2 && clicked_floater >= 0) {
        (void)ISSUE_COMMAND(GAME_COMMAND_QUEUE_CAST_ACTION,
            (uint8_t)g_menu.selected_tribe, (uint8_t)building_island,
            (uint16_t)g_selected_location, (uint8_t)action, clicked_floater,
            (uint8_t)building_island, -1);
        return 1;
    }
    return 0;
}

static void draw_control_with_hover_overlay(RenderSurface *surface,
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
            draw_sprite(surface, art, (uint32_t)frames[frame_index],
                        control->pane.left, control->pane.top);
        }
    }
}

/* Spell kind (spells.txt row) of the BC_Spell1..8 button under the pointer on a
   player's item 0x2f/0x30 building, without the click-path kind filter. */
static int hovered_spell_button_kind(int x, int y)
{
    const GameRuntimeLocation *location = selected_spell_hall();
    const WindowTemplate *button;
    unsigned int index;

    if (location == NULL) return -1;
    button = window_catalog_hit_test_names(&g_window_catalog, 3, x, y,
        k_spell_button_names, 8);
    if (button == NULL) return -1;
    for (index = 0; index < 8; ++index) {
        if (strcmp(button->name, k_spell_button_names[index]) == 0) {
            return game_session_cast_kind_for_action(
                (uint8_t)location->source_value_14,
                (uint8_t)(0x15U + index));
        }
    }
    return -1;
}

static int update_location_action_hover(int x, int y)
{
    const char *const move_names[] = {"IWMove", "IWHallMove"};
    static const char *const repair_names[] = {"BC_Repair"};
    static const char *const upgrade_names[] = {"BC_Upgrade"};
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
    const WindowTemplate *upgrade_control = NULL;
    const WindowTemplate *onoff_control = NULL;
    int repair_hovered = 0;
    int upgrade_hovered = 0;
    int onoff_hovered = 0;
    if (g_game_session_valid && g_menu.screen == SCREEN_ISLAND &&
        g_island_panel_mode == WINDOW_ISLAND_PANEL_GENERAL &&
        g_menu.selected_map_island >= 0 &&
        g_menu.selected_map_island < g_game_session.island_count &&
        view_selected_location() >= 0) {
        island = &g_game_session.islands[g_menu.selected_map_island];
        if (view_selected_location() < island->location_count) {
            if (selected_repair_button_visible()) {
                repair_control = window_catalog_hit_test_names(&g_window_catalog,
                    3, x, y, repair_names,
                    sizeof(repair_names) / sizeof(repair_names[0]));
            }
            if (selected_upgrade_button_visible()) {
                upgrade_control = window_catalog_hit_test_names(&g_window_catalog,
                    3, x, y, upgrade_names,
                    sizeof(upgrade_names) / sizeof(upgrade_names[0]));
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
    upgrade_hovered = upgrade_control != NULL &&
        strcmp(upgrade_control->name, "BC_Upgrade") == 0;
    onoff_hovered = onoff_control != NULL &&
        strcmp(onoff_control->name, "BC_OnOff") == 0;
    IslandLocationActionControl hovered = ISLAND_LOCATION_ACTION_NONE;
    if (control != NULL && strcmp(control->name, name) == 0) hovered = action;
    {
        int spell_kind = hovered_spell_button_kind(x, y);
        if (hovered == g_hovered_location_action &&
            repair_hovered == g_hovered_repair_control &&
            upgrade_hovered == g_hovered_upgrade_control &&
            onoff_hovered == g_hovered_onoff_control &&
            spell_kind == g_hovered_spell_kind) return 0;
        g_hovered_spell_kind = spell_kind;
    }
    g_hovered_location_action = hovered;
    g_hovered_repair_control = repair_hovered;
    g_hovered_upgrade_control = upgrade_hovered;
    g_hovered_onoff_control = onoff_hovered;
    return 1;
}

/* FUN_0042f755 builds the IWLocControl commands of the selected site (modes
   0 and 3 show that pane); FUN_0045302a lists command 4 (Obtain) for a
   PIT_Object (+0x10 == 1, +0x24 in 5..0x21) without an owner or range test
   (ev_b40413cf, ev_13a87deb). FUN_0042fa0f (0x39) only posts the type-0xd
   task while the site is on the viewed island. */
static int obtain_button_visible(void)
{
    if (!g_game_session_valid || g_menu.screen != SCREEN_ISLAND ||
        !island_panel_location_control_visible(g_island_panel_mode) ||
        view_selected_location() < 0 ||
        g_menu.selected_map_island < 0 ||
        g_menu.selected_map_island >= g_game_session.island_count ||
        g_menu.selected_tribe < 0 ||
        g_menu.selected_tribe >= GAME_START_PLAYER_COUNT) return 0;
    return game_session_location_offers_obtain(&g_game_session,
        (uint8_t)g_menu.selected_map_island,
        (uint16_t)view_selected_location());
}

static int obtain_button_rect(RECT *rect)
{
    /* windows.txt BC_Obtain (BLDCMD frame 15) owns the pane; the hit area is
       the control's own pane. */
    const WindowTemplate *control;
    if (rect == NULL || !obtain_button_visible()) return 0;
    control = window_catalog_find(&g_window_catalog, "BC_Obtain", 3);
    if (control == NULL) return 0;
    rect->left = control->pane.left;
    rect->top = control->pane.top;
    rect->right = control->pane.right;
    rect->bottom = control->pane.bottom;
    return 1;
}

static int obtain_button_at(int x, int y)
{
    RECT rect;
    return obtain_button_rect(&rect) && x >= rect.left &&
        x < rect.right && y >= rect.top && y < rect.bottom;
}

/* BC_DefendArea (TRAINB frame 0, pane 453,438..507,471): offered by
   FUN_0045d5ba for an owned, built 0x2c..0x2e site; a click arms the map
   target (cursor mode 19), the next island click writes the building order. */
static int defend_area_button_visible(void)
{
    if (!g_game_session_valid || g_menu.screen != SCREEN_ISLAND ||
        g_menu.selected_tribe < 0 ||
        g_menu.selected_tribe >= GAME_START_PLAYER_COUNT ||
        selection_island() < 0 || g_selected_location < 0) return 0;
    return game_session_building_has_defend_area(&g_game_session,
        (uint8_t)g_menu.selected_tribe, (uint8_t)selection_island(),
        (uint16_t)g_selected_location);
}

/* Genre written by each building order control: BC_AttackFlt 6,
   BC_AttackLoc 7, BC_DefendFlt 8, BC_DefendArea 9; BC_Recall (list index 15,
   FUN_0045dcf4: genre 9 at the building's own packed tile) is reported as
   10 and acts at once. */
static const char *const k_building_order_buttons[5] = {
    "BC_AttackFlt", "BC_AttackLoc", "BC_DefendFlt", "BC_DefendArea",
    "BC_Recall"
};

/* Genre (6..9) of the building order button at (x, y), else 0. */
static int building_order_button_at(int x, int y)
{
    unsigned int index;
    if (!defend_area_button_visible()) return 0;
    for (index = 0; index < 5U; ++index) {
        const WindowTemplate *control = window_catalog_find(
            &g_window_catalog, k_building_order_buttons[index], 3);
        if (control != NULL && x >= control->pane.left &&
            x < control->pane.right && y >= control->pane.top &&
            y < control->pane.bottom) return (int)(6U + index);
    }
    return 0;
}

/* BC_TrnStkC / BC_TrnStkM (THBUTT, NSTATES 2): 1 = crystal, 2 = magic when the
   control is offered for the selected site under the pointer at (x, y). */
static int training_stock_control_at(int x, int y)
{
    static const char *const names[2] = {"BC_TrnStkC", "BC_TrnStkM"};
    unsigned int index;
    if (!g_game_session_valid || g_menu.screen != SCREEN_ISLAND ||
        g_menu.selected_tribe < 0 ||
        g_menu.selected_tribe >= GAME_START_PLAYER_COUNT ||
        selection_island() < 0 || g_selected_location < 0) return 0;
    /* The TrnStkC pane (192..243) covers TrnStkM (215..247); TrnStkM is
       drawn over it, so test it first. */
    for (index = 2U; index-- > 0U;) {
        const WindowTemplate *control = window_catalog_find(
            &g_window_catalog, names[index], 3);
        if (control != NULL && x >= control->pane.left &&
            x < control->pane.right && y >= control->pane.top &&
            y < control->pane.bottom &&
            game_session_training_stock_visible(&g_game_session,
                (uint8_t)g_menu.selected_tribe,
                (uint8_t)selection_island(),
                (uint16_t)g_selected_location, (int)index)) return (int)index + 1;
    }
    return 0;
}

/* CLIPSEL1-3 / CLIPBD1-3 (island view clipboard strip). Returns 1..3 for a
   group tab and 11..13 for a slot column under (x, y), else 0. */
static int clipboard_control_at(int x, int y)
{
    static const char *const tabs[3] = {"CLIPSEL1", "CLIPSEL2", "CLIPSEL3"};
    static const char *const slots[3] = {"CLIPBD1", "CLIPBD2", "CLIPBD3"};
    unsigned int index;
    if (!g_game_session_valid || g_menu.screen != SCREEN_ISLAND) return 0;
    for (index = 0; index < 3U; ++index) {
        const WindowTemplate *tab = window_catalog_find(&g_window_catalog, tabs[index], 3);
        const WindowTemplate *slot = window_catalog_find(&g_window_catalog, slots[index], 3);
        if (tab != NULL && x >= tab->pane.left && x < tab->pane.right &&
            y >= tab->pane.top && y < tab->pane.bottom) return (int)index + 1;
        if (slot != NULL && x >= slot->pane.left && x < slot->pane.right &&
            y >= slot->pane.top && y < slot->pane.bottom) return (int)index + 11;
    }
    return 0;
}

static int ensure_clipboard_art(void)
{
    CobArchive archive = {0};
    char error[128];
    if (g_clip_art.frame_count != 0 && g_bildicon_art.frame_count != 0) return 1;
    if (!cob_archive_open(game_file_path("TONE01.COB"), &archive,
                          error, sizeof(error))) return 0;
    if (g_clip_art.frame_count == 0)
        (void)load_sprite_sheet(&archive, "data\\clip0.shp", g_island_palette,
                                &g_clip_art, error, sizeof(error));
    if (g_bildicon_art.frame_count == 0)
        (void)load_sprite_sheet(&archive, "data\\bildicon.shp", g_island_palette,
                                &g_bildicon_art, error, sizeof(error));
    cob_archive_close(&archive);
    return g_clip_art.frame_count != 0 && g_bildicon_art.frame_count != 0;
}

/* BC_UpgSpread (UPGRADE shape, pane 246,400..270,425): FUN_0045302a offers it
   on another tribe's base-0x28 block while FUN_00452bc5 holds. */
static int upgspread_button_at(int x, int y)
{
    const WindowTemplate *control;
    if (!g_game_session_valid || g_menu.screen != SCREEN_ISLAND ||
        g_menu.selected_tribe < 0 ||
        g_menu.selected_tribe >= GAME_START_PLAYER_COUNT ||
        selection_island() < 0 || g_selected_location < 0 ||
        !game_session_upgspread_available(&g_game_session,
            (uint8_t)g_menu.selected_tribe, (uint8_t)selection_island(),
            (uint16_t)g_selected_location)) return 0;
    control = window_catalog_find(&g_window_catalog, "BC_UpgSpread", 3);
    return control != NULL && x >= control->pane.left &&
        x < control->pane.right && y >= control->pane.top &&
        y < control->pane.bottom;
}

static int ensure_trainb_art(void)
{
    CobArchive archive = {0};
    char error[128];
    if (g_trainb_art.frame_count != 0) return 1;
    if (!cob_archive_open(game_file_path("TONE01.COB"), &archive,
                          error, sizeof(error))) return 0;
    (void)load_sprite_sheet(&archive, "data\\trainb.shp", g_island_palette,
                            &g_trainb_art, error, sizeof(error));
    cob_archive_close(&archive);
    return g_trainb_art.frame_count != 0;
}

static int update_location_grab_hover(int x, int y)
{
    int hovered = obtain_button_at(x, y);
    int defend_hovered = building_order_button_at(x, y);
    int changed = 0;
    int training_hovered = training_stock_control_at(x, y);
    int spread_hovered = upgspread_button_at(x, y);
    if (spread_hovered != g_hovered_upgspread) {
        g_hovered_upgspread = spread_hovered;
        changed = 1;
    }
    if (training_hovered != g_hovered_training_stock) {
        g_hovered_training_stock = training_hovered;
        changed = 1;
    }
    if (defend_hovered != g_hovered_defend_area) {
        g_hovered_defend_area = defend_hovered;
        changed = 1;
    }
    if (hovered == g_hovered_location_grab) return changed;
    g_hovered_location_grab = hovered;
    return 1;
}

static int selected_location_can_be_grabbed(void)
{
    const GameRuntimeIsland *island;
    const GameRuntimeLocation *location;
    const GameRuntimeLocation *hall;
    int32_t costs[GAME_RESOURCE_TYPE_COUNT];
    unsigned int resource;
    int32_t item_id;
    if (g_game_session.location_move_active) return 1;
    if (!g_game_session_valid || g_menu.screen != SCREEN_ISLAND ||
        g_menu.selected_tribe < 0 ||
        g_menu.selected_tribe >= GAME_START_PLAYER_COUNT ||
        g_menu.selected_map_island < 0 ||
        g_menu.selected_map_island >= g_game_session.island_count ||
        view_selected_location() < 0) return 0;
    island = &g_game_session.islands[g_menu.selected_map_island];
    if (view_selected_location() >= island->location_count) return 0;
    location = &island->locations[view_selected_location()];
    item_id = location->record_value_10 - (int32_t)g_menu.selected_tribe * 16;
    if (location->owner_id != (int32_t)g_menu.selected_tribe ||
        item_id < 0x25 || item_id > 0x34 || item_id == 0x28 ||
        (location->source_flags & 0x90U) != 0) return 0;
    if ((location->source_value_22 & (uint16_t)(1U << g_menu.selected_tribe)) == 0 ||
        !game_session_location_move_costs(&g_game_session, &g_pad_catalog,
            (uint8_t)g_menu.selected_map_island,
            (uint16_t)view_selected_location(), costs)) return 0;
    if (g_game_session.economy[g_menu.selected_tribe].hall_island_index >=
            g_game_session.island_count ||
        g_game_session.economy[g_menu.selected_tribe].hall_location_index >=
            g_game_session.islands[g_game_session.economy[
                g_menu.selected_tribe].hall_island_index].location_count) return 0;
    hall = &g_game_session.islands[g_game_session.economy[
        g_menu.selected_tribe].hall_island_index].locations[
        g_game_session.economy[g_menu.selected_tribe].hall_location_index];
    for (resource = 0; resource < GAME_RESOURCE_TYPE_COUNT; ++resource) {
        if (costs[resource] < 0 ||
            (uint32_t)costs[resource] > hall->resource_stock[resource]) return 0;
    }
    return 1;
}

/* FUN_0042f303 mode 0 shows the player's home record (FUN_0042f755 on the
   Hall at DAT_0061a580/82) whatever the current island is, so with nothing
   else selected the Hall stays the default selection even away from its
   island. */
static int hall_default_selected(void)
{
    const GamePlayerEconomy *economy;
    if (!g_game_session_valid || g_menu.screen != SCREEN_ISLAND ||
        g_menu.selected_tribe < 0 ||
        g_menu.selected_tribe >= GAME_START_PLAYER_COUNT ||
        g_selected_location >= 0) return 0;
    /* FUN_0042f8f7 falls back to mode 0 (Hall) for an unlinked floater, so a
       selected floater no longer disables the default. */
    economy =&g_game_session.economy[g_menu.selected_tribe];
    return economy->hall_island_index < g_game_session.island_count &&
        economy->hall_location_index <
            g_game_session.islands[economy->hall_island_index].location_count;
}

/* Island/location whose record IWLocInfo describes: the selected site, or the
   default Hall. Returns 0 when there is none. */
static int effective_info_location(const GameRuntimeIsland **island_out,
                                   int *location_out, uint8_t *island_index_out)
{
    if (!g_game_session_valid || selection_island() < 0 ||
        selection_island() >= g_game_session.island_count) return 0;
    if (g_selected_location >= 0) {
        const GameRuntimeIsland *island =
            &g_game_session.islands[selection_island()];
        if (g_selected_location >= island->location_count) return 0;
        *island_out = island;
        *location_out = g_selected_location;
        *island_index_out = (uint8_t)selection_island();
        return 1;
    }
    if (hall_default_selected()) {
        const GamePlayerEconomy *economy =
            &g_game_session.economy[g_menu.selected_tribe];
        *island_out = &g_game_session.islands[economy->hall_island_index];
        *location_out = (int)economy->hall_location_index;
        *island_index_out = economy->hall_island_index;
        return 1;
    }
    return 0;
}

static int selected_hall_player(void)
{
    unsigned int player;
    if (hall_default_selected()) return g_menu.selected_tribe;
    const GameRuntimeIsland *island;
    const GameRuntimeLocation *hall;
    if (!g_game_session_valid || g_menu.screen != SCREEN_ISLAND ||
        g_menu.selected_tribe >= GAME_START_PLAYER_COUNT ||
        selection_island() < 0 ||
        selection_island() >= g_game_session.island_count ||
        g_selected_location < 0) return -1;
    player = g_menu.selected_tribe;
    if (g_game_session.economy[player].hall_island_index !=
            (uint8_t)selection_island() ||
        g_game_session.economy[player].hall_location_index !=
            (uint16_t)g_selected_location) return -1;
    island = &g_game_session.islands[selection_island()];
    if (g_selected_location >= island->location_count) return -1;
    hall = &island->locations[g_selected_location];
    if (hall->owner_id != (int32_t)player ||
        hall->record_value_10 != (int32_t)(0x2aU + player * 16U)) return -1;
    return (int)player;
}

/* FUN_0042f8f7 (floater select, message 0x3f) resolves the floater's +0x0c
   link through FUN_004207f2/FUN_0045c3bb to its source building and shows it
   via FUN_0042f755, on any island. With no link the current location is kept
   unless it has no staff slot. */
static void select_floater_source_building(int floater_index)
{
    const GameFloaterStart *floater;
    if (!g_game_session_valid || floater_index < 0 ||
        (unsigned int)floater_index >= g_game_session.floater_count) return;
    floater = &g_game_session.floaters[floater_index];
    if (floater->source_link_0c < 0) {
        /* FUN_0042f8f7: no linked row and the kept location is null or has
           +0x18 == -1 (no staff slot) -> FUN_0042f303(0), the Hall default
           in mode 0. */
        const GameRuntimeIsland *island = selection_island() >= 0 &&
            selection_island() < g_game_session.island_count
            ? &g_game_session.islands[selection_island()] : NULL;
        if (island == NULL || g_selected_location < 0 ||
            (uint16_t)g_selected_location >= island->location_count ||
            island->locations[g_selected_location].source_location_slot_18 ==
                -1) {
            select_location_on_view(-1);
            g_island_panel_mode = WINDOW_ISLAND_PANEL_GENERAL;
        }
        return;
    }
    /* +0x16c takes the linked building on any island, and FUN_0042f755(.., 1)
       switches to the building panel (FUN_0042f303(3)) (ev_aa63a0e6). */
    if (floater->charge_source_island >= g_game_session.island_count ||
        floater->charge_source_location >=
            g_game_session.islands[floater->charge_source_island].location_count)
        return;
    select_location_anywhere((int)floater->charge_source_island,
                             (int)floater->charge_source_location);
    g_island_panel_mode = WINDOW_ISLAND_PANEL_LOCATION;
}

/* FUN_00435826 with param_3 = (event == 7), the right button (call site
   0x4341c1..0x4341d6, ev_136c9e2d). With an owned building holding a staff
   record selected (+0x16c, any island) it gives that building's group order
   (FUN_0043530b mode, then msg 0x41 / 0x40 / 0x4c -> FUN_00465793 ->
   FUN_0045d867 / FUN_0045d8b2, ev_52232fe9, ev_614c66b1):
   - a floater: genre 6 (attack) for category 4 or an enemy owner, else 8
     (defend); the clicked floater is then selected (msg 0x3f);
   - a site of category 4 or an enemy: genre 7 (attack location);
   - an unowned or friendly site, or empty ground: genre 9 at the point.
   "Enemy" is a zero DAT_00619290[player][owner] policy flag. Interpretation:
   the self entry is not established, so the player's own floaters and sites
   are treated as friendly (defend) rather than attacked.
   Without such a building the click only selects, like the left button. */
static void island_right_click(int clicked_floater, int x, int y)
{
    uint8_t player = (uint8_t)g_menu.selected_tribe;
    uint8_t viewed = (uint8_t)g_menu.selected_map_island;
    int building_island = selection_island();
    int clicked_location;
    int ordering;

    if (island_spell_target_click(clicked_floater, x, y)) return;
    clicked_location = clicked_floater >= 0 ? -1 : island_location_at(x, y);
    ordering = g_selected_location >= 0 && building_island >= 0 &&
        building_island < g_game_session.island_count &&
        game_session_building_takes_orders(&g_game_session, player,
            (uint8_t)building_island, (uint16_t)g_selected_location);

    if (ordering) {
        unsigned int genre = 9;
        unsigned int target = (unsigned int)(x + g_island_scroll_x);
        unsigned int target_y = (unsigned int)y;
        if (clicked_floater >= 0) {
            const GameFloaterStart *victim =
                &g_game_session.floaters[clicked_floater];
            int friendly = victim->type_index != 4U &&
                (victim->owner_slot == player ||
                 (victim->owner_slot < GAME_START_PLAYER_COUNT &&
                  ((g_game_session.diplomacy_policy_mask[player] >>
                    victim->owner_slot) & 1U) != 0));
            genre = friendly ? 8U : 6U;
            target = (unsigned int)clicked_floater;
            target_y = 0;
        } else if (clicked_location >= 0) {
            const GameRuntimeLocation *site =
                &g_game_session.islands[viewed].locations[clicked_location];
            /* Raw +0x14 is the native owner: a Spore claim writes 4 there
               before the record's item changes (FUN_0041e569). */
            int enemy = site->owner_id == 4 || site->source_value_14 == 4 ||
                (site->owner_id >= 0 &&
                 site->owner_id < GAME_START_PLAYER_COUNT &&
                 site->owner_id != (int32_t)player &&
                 ((g_game_session.diplomacy_policy_mask[player] >>
                   site->owner_id) & 1U) == 0);
            if (enemy) {
                genre = 7;
                target = (unsigned int)clicked_location;
                target_y = 0;
            }
        }
        (void)ISSUE_COMMAND(GAME_COMMAND_SET_BUILDING_ORDER, player,
            (uint8_t)building_island, (uint16_t)g_selected_location, genre,
            viewed, target, target_y);
        g_defend_area_armed = 0;
        update_interaction_cursor();
        if (clicked_floater < 0) return;
    }
    if (clicked_floater >= 0) {
        /* msg 0x3f -> FUN_0042f8f7. */
        g_selected_floater = clicked_floater;
        select_floater_source_building(clicked_floater);
        g_hovered_location = -1;
    } else if (!ordering && clicked_location >= 0) {
        /* msg 0x32: the site becomes +0x16c. */
        select_location_on_view(clicked_location);
        select_building_warrior();
    } else if (!ordering) {
        /* msg 0x4b then 0x33: FUN_0042f303(0). */
        g_selected_floater = -1;
        select_location_on_view(-1);
        g_island_panel_mode = WINDOW_ISLAND_PANEL_GENERAL;
    }
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
    return ISSUE_COMMAND(GAME_COMMAND_ADJUST_TRADE_OFFER, (uint8_t)hall_player, resource_row, target_column, direction);
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
    (void)ISSUE_COMMAND(GAME_COMMAND_TOGGLE_DIPLOMACY, (uint8_t)player_slot, target_player, hit.action);
    return 1;
}

/* Shared by the click path and the pad renderer: a site is buildable when
   FUN_004526de's owner/state/visibility guard passes for the local tribe and
   FUN_0045f121 yields at least one candidate for the site size. */
static int island_site_buildable_by_player(int location_index,
                                           int32_t *out_items,
                                           size_t *out_count)
{
    int32_t scratch_items[IW_CONSTRUCT_BUILD_CANDIDATE_COUNT];
    size_t scratch_count = 0;
    const IslandLocation *site;
    const GameRuntimeIsland *runtime_island;
    uint16_t owned_island_count = 0;
    uint16_t owner_bit;
    unsigned int island_index;

    if (!g_game_session_valid || g_menu.selected_map_island < 0 ||
        g_menu.selected_map_island >= g_game_session.island_count ||
        location_index < 0 || location_index >= g_island_surface_data.location_count) {
        return 0;
    }
    site = &g_island_surface_data.locations[location_index];
    runtime_island = &g_game_session.islands[g_menu.selected_map_island];
    if (location_index >= runtime_island->location_count ||
        g_menu.selected_tribe < 0 ||
        g_menu.selected_tribe >= GAME_START_PLAYER_COUNT) return 0;
    owner_bit = (uint16_t)(1U << g_menu.selected_tribe);
    {
        const GameRuntimeLocation *runtime_site =
            &runtime_island->locations[location_index];
        int16_t owner = (int16_t)g_menu.selected_tribe;
        if (runtime_site->renderer_class != 0 ||
            (runtime_site->source_value_14 != -1 &&
             runtime_site->source_value_14 != owner) ||
            (runtime_site->record_value_10 != 0 &&
             runtime_site->record_value_10 != 1) ||
            (runtime_site->source_value_22 & owner_bit) == 0) return 0;
    }

    /* FUN_0045f121 counts one nonzero +0x29ac player-access dword per island,
       then indexes the threshold table with DAT_006136b2. The session's
       access_mask stores those same per-player island states; world_index
       selects the corresponding world rule table. */
    for (island_index = 0; island_index < g_game_session.island_count;
         ++island_index) {
        if ((g_game_session.islands[island_index].access_mask & owner_bit) != 0 &&
            owned_island_count < UINT16_MAX) {
            ++owned_island_count;
        }
    }
    if (!iw_construct_build_list_for_site(
            &g_pad_catalog, g_game_session.config.selected_tribe, site,
            g_game_session.config.world_index, owned_island_count,
            scratch_items, sizeof(scratch_items) / sizeof(scratch_items[0]),
            &scratch_count) || scratch_count == 0) return 0;
    if (out_items != NULL && out_count != NULL) {
        memcpy(out_items, scratch_items, scratch_count * sizeof(scratch_items[0]));
        *out_count = scratch_count;
    }
    return 1;
}

static int open_iw_construct(int location_index)
{
    if (!island_site_buildable_by_player(location_index, g_iw_construct_items,
                                         &g_iw_construct_item_count)) return 0;

    iw_construct_init(&g_iw_construct, g_iw_construct_item_count);
    iw_construct_info_init(&g_iw_construct_info);
    g_iw_construct_open = 1;
    return 1;
}

/* Remake addition (no native path found): a site holding the active tribe's
   pending CONSTR task opens the Tasks view with that task selected and
   scrolled into view, instead of IWConstruct. */
static int open_construction_task(int location_index)
{
    const WindowTemplate *task_panel;
    uint8_t task_slots[GAME_SESSION_MAX_TASKS];
    size_t task_count;
    size_t index;
    int slot;
    int visible_rows;
    if (!g_game_session_valid || location_index < 0 ||
        g_menu.selected_map_island < 0 ||
        g_menu.selected_map_island >= g_game_session.island_count) return 0;
    slot = game_session_construction_task_slot(&g_game_session,
        (int16_t)g_game_session.config.selected_tribe,
        (uint16_t)g_menu.selected_map_island, (uint16_t)location_index);
    if (slot < 0) return 0;
    task_count = game_session_collect_task_slots(&g_game_session,
        (int16_t)g_game_session.config.selected_tribe, task_slots,
        sizeof(task_slots) / sizeof(task_slots[0]));
    task_panel = window_catalog_find(&g_window_catalog, "IWTasks", 3);
    visible_rows = task_panel != NULL
        ? (task_panel->pane.bottom - task_panel->pane.top) / 13 : 0;
    g_iw_construct_open = 0;
    g_island_panel_mode = WINDOW_ISLAND_PANEL_TASKS;
    g_selected_task_slot = slot;
    g_task_scroll_offset = 0;
    for (index = 0; index < task_count &&
         index < sizeof(task_slots) / sizeof(task_slots[0]); ++index) {
        if (task_slots[index] != (uint8_t)slot) continue;
        if (visible_rows > 0 && (int)index >= visible_rows)
            g_task_scroll_offset = (int)index - visible_rows + 1;
        break;
    }
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
    int build_queued = 0;

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
                view_selected_location() >= 0 &&
                view_selected_location() <= UINT16_MAX &&
                view_selected_location() < g_island_surface_data.location_count) {
                /* FUN_0042fa0f turns this selection message into the observed
                   category-0/type-5 request. Its consumer is unknown, so the
                   UI queues the packet and does not place the item here. */
                build_queued = ISSUE_COMMAND(GAME_COMMAND_QUEUE_BUILD_SELECTION, g_game_session.config.selected_tribe,
                    (uint8_t)g_menu.selected_map_island,
                    (uint16_t)view_selected_location(),
                    (uint16_t)message->value);
                handled = build_queued;
            }
        } else if (message->code == IW_CONSTRUCT_MSG_CLEAR_BUILD) {
            /* Keep the chooser open if its bounded outbox could not accept the
               order, so another click can enqueue it after the next tick. */
            if (build_queued) {
                g_iw_construct_open = 0;
                (void)iw_construct_info_handle_message(&g_iw_construct_info, 1, 0);
            }
        }
    }
    return handled;
}
