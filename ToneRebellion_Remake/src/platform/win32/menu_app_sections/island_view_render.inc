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

    if (g_game_session_valid && g_menu.selected_map_island >= 0 &&
        g_menu.selected_map_island < g_game_session.island_count) {
        runtime_island = &g_game_session.islands[g_menu.selected_map_island];
        if (g_selected_floater >= 0 &&
            g_selected_floater < g_game_session.floater_count) {
            const GameFloaterStart *candidate =
                &g_game_session.floaters[g_selected_floater];
            if (candidate->island_index == g_menu.selected_map_island) {
                selected_floater = candidate;
            }
        }
    }

    fill_rect(dc, 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT, RGB(0, 0, 0));
    if (g_island_height_data == NULL ||
        g_island_height_length != ISLAND_HAZE_FILE_BYTES) {
        draw_sprite(dc, &g_island_template_art, 0, 0, status_top);
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
                                -g_island_scroll_x, image_top);
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
            /* Build Tone is stored on an empty runtime pad until construction
               consumes it. Keep the deposited stock visible at the site. */
            if (is_construction_site && runtime_location != NULL &&
                runtime_location->record_value_10 == 0 &&
                runtime_location->resource_stock[GAME_RESOURCE_BUILD_TONE] != 0 &&
                g_bildtone_art.frame_count != 0) {
                char stock_label[8];
                unsigned int stock = runtime_location->resource_stock[
                    GAME_RESOURCE_BUILD_TONE];
                draw_sprite_scaled(dc, &g_bildtone_art, 0, x - 5, y - 12,
                                   0x00008000U);
                (void)snprintf(stock_label, sizeof(stock_label), "%u", stock);
                draw_bitmap_label(dc, stock_label, x + 3, y - 10,
                                  RGB(255, 238, 164));
                drew_location = 1;
            }
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
       selected hall marker. FUN_0042704b draws their tribe-specific legs and
       body separately; shapeinf.txt defines body frame 0 and hover frames 0..15. */
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
                floater->type_index >= 4) continue;
            floater_x = (int)floater->x - g_island_scroll_x;
            if (floater_x < -64 || floater_x >= LOGICAL_WIDTH + 64) continue;
            floater_y = image_top + (int)floater->y;
            leg_frame = g_menu.animation_ticks % 16u;
            body_art = floater->facing_left
                           ? &g_initial_floater_bodies_flipped[floater->type_index]
                           : &g_initial_floater_bodies[floater->type_index];
            leg_art = floater->facing_left
                          ? &g_initial_floater_legs_flipped[floater->type_index]
                          : &g_initial_floater_legs[floater->type_index];
            draw_sprite(dc, leg_art, leg_frame, floater_x, floater_y);
            draw_sprite(dc, body_art, 0, floater_x, floater_y);
            /* FUN_0042822b calls FUN_0042704b with param_5=1 for world
               floaters. The first overlay global gates FLTINFO realm frames
               22..25; other overlay values need runtime state not modeled by
               the startup-floater record. */
            if (island_worker_realm_overlay_enabled(
                    g_floater_overlay_flags, 1) &&
                g_floater_info_art.frame_count >= 26 &&
                body_art->frame_count != 0) {
                const SpriteFrame *body_frame = &body_art->frames[0];
                int32_t body_left = floater_x + body_frame->x_offset +
                                    body_frame->hit_left;
                int32_t body_top = floater_y + body_frame->y_offset +
                                   body_frame->hit_top;
                int32_t body_right = floater_x + body_frame->x_offset +
                                     body_frame->hit_right;
                uint32_t realm_frame;
                int32_t badge_x;
                int32_t badge_y;
                if (island_worker_realm_badge_layout(
                        floater->type_index, 0, 0, floater->facing_left,
                        body_left, body_top, body_right,
                        &realm_frame, &badge_x, &badge_y) &&
                    realm_frame < g_floater_info_art.frame_count) {
                    draw_sprite(dc, &g_floater_info_art, realm_frame,
                                badge_x, badge_y);
                }
            }
            /* FUN_0042704b gates health FLTINFO frames with the second
               TOGREALM flag. Initial workers are created with +0x1c cleared
               by FUN_00466fe4/FUN_0041e4e4, so their world badge is eligible. */
            if (island_worker_health_overlay_enabled(
                    g_floater_overlay_flags, 1) &&
                g_floater_info_art.frame_count >= 26 &&
                body_art->frame_count != 0) {
                const SpriteFrame *body_frame = &body_art->frames[0];
                int32_t body_left = floater_x + body_frame->x_offset +
                                    body_frame->hit_left;
                int32_t body_top = floater_y + body_frame->y_offset +
                                   body_frame->hit_top;
                int32_t body_right = floater_x + body_frame->x_offset +
                                     body_frame->hit_right;
                uint32_t health_frame;
                int32_t badge_x;
                int32_t badge_y;
                if (island_worker_health_badge_layout(
                        floater->type_index, floater->max_hit_points,
                        floater->facing_left, body_left, body_top, body_right,
                        &health_frame, &badge_x, &badge_y) &&
                    health_frame < g_floater_info_art.frame_count) {
                    draw_sprite(dc, &g_floater_info_art, health_frame,
                                badge_x, badge_y);
                }
            }
            /* FUN_0042704b places the resolved resource at the body's +0x25/
               +0x26 anchor when +0x18 is nonzero. shapeinf's exact hand offsets
               are unavailable, so attach the half-size sprite beside the body. */
            if (floater->carried_resource_code >= 1 &&
                floater->carried_resource_code <= GAME_RESOURCE_TYPE_COUNT) {
                static const SpriteSheet *const carried_art[] = {
                    &g_bildtone_art, &g_tone_crys_art, &g_magctone_art
                };
                const SpriteSheet *cargo_art = carried_art[
                    (unsigned int)floater->carried_resource_code - 1U];
                if (cargo_art->frame_count != 0 && body_art->frame_count != 0) {
                    const SpriteFrame *body_frame = &body_art->frames[0];
                    int hand_x = floater_x + body_frame->x_offset +
                                 (floater->facing_left ? -6 : 5);
                    int hand_y = floater_y + body_frame->y_offset - 1;
                    draw_sprite_scaled(dc, cargo_art, 0,
                                       hand_x, hand_y,
                                       0x00008000U);
                }
            }
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
            frame = window_catalog_control_frame(
                button, (int)button_index == g_hovered_island_button);
            if (frame >= 0 && (uint32_t)frame < g_island_main_buttons.frame_count) {
                draw_sprite(dc, &g_island_main_buttons, (uint32_t)frame,
                            button->pane.left, button->pane.top);
            }
        }
    }

    draw_hall_panel(dc, hall_player);

    /* The five Hall command controls are clickable THALL frames from the
       active island palette. Their descriptors also own the hover bounds. */
    if (hall_player >= 0) {
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

    /* windows.txt places IWLilMap at (192,328)-(447,359), and shapes.txt
       binds it to the 16-frame LILMAP sheet. The SHP frame is indexed by the
       selected island's existing surface id (the local 15-island corpus uses
       the corresponding first 15 frames). */
    if (g_island_surface_id >= 0 && g_island_surface_id < 16) {
        const WindowTemplate *mini_map = window_catalog_find(
            &g_window_catalog, "IWLilMap", 16);
        if (mini_map != NULL) {
            draw_sprite(dc, &g_island_lilmap_art,
                        (uint32_t)g_island_surface_id,
                        mini_map->pane.left, mini_map->pane.top);
        }
    }

    draw_iw_construct(dc);
    if (selected_floater != NULL && selected_floater->type_index < 4) {
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
            draw_bitmap_label(dc, "WORKER",
                              info->pane.left + 5, info->pane.top + 3,
                              RGB(230, 238, 255));
            {
                char hit_points_label[24];
                char strength_label[24];
                char charge_label[24];
                char carried_label[28];
                int16_t current_charge;
                int16_t maximum_charge;
                (void)snprintf(hit_points_label, sizeof(hit_points_label),
                    "HITS %u/%u",
                    (unsigned int)selected_floater->current_hit_points,
                    (unsigned int)selected_floater->max_hit_points);
                (void)snprintf(strength_label, sizeof(strength_label),
                    "STRENGTH %u",
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
                        "CHARGE %d/%d", (int)current_charge,
                        (int)maximum_charge);
                    draw_bitmap_label(dc, charge_label,
                                      info->pane.left + 5,
                                      info->pane.top + 43,
                                      RGB(230, 238, 255));
                }
                if (selected_floater->carried_resource_code >= 1 &&
                    selected_floater->carried_resource_code <=
                        GAME_RESOURCE_TYPE_COUNT) {
                    static const char *const carried_names[] = {
                        "BUILD", "CRYSTAL", "MAGIC"
                    };
                    static const SpriteSheet *const carried_art[] = {
                        &g_bildtone_art, &g_tone_crys_art, &g_magctone_art
                    };
                    unsigned int resource_index =
                        (unsigned int)selected_floater->carried_resource_code - 1U;
                    (void)snprintf(carried_label, sizeof(carried_label),
                        "CARRY %s", carried_names[resource_index]);
                    draw_bitmap_label(dc, carried_label,
                                      info->pane.left + 5,
                                      info->pane.top + 53,
                                      RGB(230, 238, 255));
                    if (carried_art[resource_index]->frame_count != 0) {
                        draw_sprite_scaled(dc, carried_art[resource_index], 0,
                            info->pane.right - 27, info->pane.top + 48,
                            0x00008000U);
                    }
                }
            }

            /* FUN_0044338b places the selected unit sprite to the right of
               the text. The island renderer's original base-worker sheets
               supply the same body and animated legs used in the world view. */
            {
                uint32_t leg_frame = g_menu.animation_ticks % 16u;
                int sprite_x = info->pane.right - 50;
                int sprite_y = info->pane.top +
                    (info->pane.bottom - info->pane.top) / 2;
                const SpriteSheet *body_art = selected_floater->facing_left
                    ? &g_initial_floater_bodies_flipped[selected_floater->type_index]
                    : &g_initial_floater_bodies[selected_floater->type_index];
                const SpriteSheet *leg_art = selected_floater->facing_left
                    ? &g_initial_floater_legs_flipped[selected_floater->type_index]
                    : &g_initial_floater_legs[selected_floater->type_index];
                const SpriteFrame *body_frame = &body_art->frames[0];
                draw_sprite(dc, leg_art, leg_frame, sprite_x, sprite_y);
                draw_sprite(dc, body_art, 0, sprite_x, sprite_y);
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
                /* Health frame and anchor are independently derived from
                   FUN_0042704b / FUN_00420f28. */
                if (g_floater_info_art.frame_count >= 26) {
                    uint32_t health_frame;
                    int32_t badge_x;
                    int32_t badge_y;
                    int32_t body_left = sprite_x + body_frame->x_offset +
                                        body_frame->hit_left;
                    int32_t body_top = sprite_y + body_frame->y_offset +
                                       body_frame->hit_top;
                    int32_t body_right = sprite_x + body_frame->x_offset +
                                         body_frame->hit_right;
                    if (island_worker_health_badge_layout(
                            selected_floater->type_index,
                            selected_floater->max_hit_points,
                            selected_floater->facing_left,
                            body_left, body_top, body_right,
                            &health_frame, &badge_x, &badge_y) &&
                        health_frame < g_floater_info_art.frame_count) {
                        draw_sprite(dc, &g_floater_info_art, health_frame,
                                    badge_x, badge_y);
                    }
                }
            }
            if (saved_info_dc != 0) RestoreDC(dc, saved_info_dc);
        }
    } else if (runtime_island != NULL && g_selected_location >= 0 &&
               g_selected_location < runtime_island->location_count) {
        const GameRuntimeLocation *selected_location =
            &runtime_island->locations[g_selected_location];
        int32_t raw_item_id = selected_location->record_value_10;
        if (raw_item_id >= 0x25 && raw_item_id < g_pad_catalog.item_count) {
            char level_label[24];
            size_t name_index = (size_t)(raw_item_id - 0x25);
            const WindowTemplate *info = window_catalog_find(
                &g_window_catalog, "IWLocInfo", 3);
            if (name_index < BUILDING_NAME_COUNT &&
                g_building_names[name_index][0] != '\0' && info != NULL &&
                g_temp_hole_art.frame_count > 1) {
                RECT pane = {info->pane.left, info->pane.top,
                             info->pane.right + 1, info->pane.bottom + 1};
                int saved_info_dc = SaveDC(dc);
                (void)IntersectClipRect(dc, pane.left, pane.top,
                                        pane.right, pane.bottom);
                draw_sprite(dc, &g_temp_hole_art, 1,
                            info->pane.left, info->pane.top);
                /* Runtime item IDs already include the owner's 16-item block;
                   subtracting PIT_BuildToneProducer (0x25) gives BLDNAME's
                   player-specific index. */
                draw_bitmap_label(dc, g_building_names[name_index],
                                  info->pane.left + 5, info->pane.top + 3,
                                  RGB(230, 238, 255));
                /* FUN_0044338b displays FUN_0041ff2e()+1 for LEVEL;
                   FUN_0041ff2e reads the selected runtime word at +0x0a,
                   masked to its low nibble. */
                (void)snprintf(level_label, sizeof(level_label), "LEVEL %u",
                    (unsigned int)game_session_location_display_level(selected_location));
                draw_bitmap_label(dc, level_label,
                                  info->pane.left + 5, info->pane.top + 18,
                                  RGB(230, 238, 255));
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
                if (saved_info_dc != 0) RestoreDC(dc, saved_info_dc);
            }
        }
    }
    /* IWLocInfo's selected-building painter clears and redraws this pane, so
       render the Hall's economy view after it. */
    draw_hall_stock_summary(dc, hall_player, runtime_island);

    /* FUN_00440567 redraws the six IWLocInfo roster slots after preparing
       them in FUN_0044034e. This prototype has only the initial class-0
       workers, and the selected starting Hall is the only modeled roster
       context with a source-backed player list. */
    {
        int player = selected_hall_player();
        if (player >= 0) {
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
                        /* shapeinf.txt assigns worker hover/move to frames 0..15;
                           later frames belong to pickup, carry, and training. */
                        draw_sprite(dc, leg_art,
                            g_menu.animation_ticks % 16u,
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
    if (hall_player >= 0 && g_hall_stock_art.frame_count >= 5) {
        static const char *const stock_control_names[GAME_RESOURCE_TYPE_COUNT] = {
            "BC_HallStkB", "BC_HallStkC", "BC_HallStkM"
        };
        unsigned int resource;
        for (resource = 0; resource < GAME_RESOURCE_TYPE_COUNT; ++resource) {
            const WindowTemplate *button = window_catalog_find(
                &g_window_catalog, stock_control_names[resource], 3);
            uint32_t frame;
            if (button == NULL) continue;
            frame = (uint32_t)button->shape_frame +
                g_game_session.economy[hall_player].stock_mode[resource];
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

    /* IWLocControl overlaps IWConstructInfo in windows.txt. Keep the selected
       construction item's pane visible while the modal build window is open. */
    if (!iw_construct_location_control_pane_visible(g_iw_construct_open) ||
        !g_game_session_valid || g_menu.screen != SCREEN_ISLAND ||
        g_menu.selected_map_island < 0 ||
        g_menu.selected_map_island >= g_game_session.island_count ||
        g_selected_location < 0) return;
    island = &g_game_session.islands[g_menu.selected_map_island];
    if (g_selected_location >= island->location_count) return;
    panel = window_catalog_find(&g_window_catalog, "IWLocControl", 3);
    if (panel != NULL && panel->shape_frame >= 0 &&
        (uint32_t)panel->shape_frame < g_temp_hole_art.frame_count) {
        draw_sprite(dc, &g_temp_hole_art, (uint32_t)panel->shape_frame,
                    panel->pane.left, panel->pane.top);
    }

    action = selected_location_action();
    if (g_island_panel_mode == WINDOW_ISLAND_PANEL_GENERAL) {
        const WindowTemplate *onoff_button = window_catalog_find(
            &g_window_catalog, "BC_OnOff", 3);
        repair_button = window_catalog_find(&g_window_catalog, "BC_Repair", 3);
        /* Keep normal artwork as the first layer: the source highlight frames
           extend the art but are not substitutes for the button itself. */
        if (selected_onoff_button_visible()) {
            draw_control_with_hover_overlay(dc, onoff_button,
                &g_building_command_art, g_hovered_onoff_control);
        }
        if (selected_repair_button_visible()) {
            draw_control_with_hover_overlay(dc, repair_button,
                &g_repair_button_art, g_hovered_repair_control);
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
                int text_height = (int)g_bitmap_font.height;
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
    if (g_cryptic_text[1][0] != '\0') {
        size_t text_length = strlen(g_cryptic_text[1]);
        int text_width = measure_bitmap_text(NULL, g_cryptic_text[1], text_length);
        int text_height = (int)g_bitmap_font.height;
        int pane_width = text_panel->pane.right - text_panel->pane.left;
        int pane_height = text_panel->pane.bottom - text_panel->pane.top;
        draw_bitmap_label(dc, g_cryptic_text[1],
            text_panel->pane.left + (pane_width - text_width) / 2,
            text_panel->pane.top + (pane_height - text_height) / 2,
            g_island_palette[6]);
    }
}

/* The x87 helpers called by FUN_00471536 continue past Ghidra's short
   function boundaries: static disassembly shows FCOS at 0x477ad2 and FSIN at
   0x477332. The constructor supplies the two scale factors used here. */
