static void draw_hall_panel(HDC dc, int hall_player)
{
    const WindowTemplate *panel = NULL;
    const char *empty_message = NULL;
    int panel_state = g_island_panel_mode;
    hall_player = island_panel_player_for_mode(panel_state,
        g_game_session_valid ? (int)g_game_session.config.selected_tribe : -1,
        hall_player);
    if (panel_state == WINDOW_ISLAND_PANEL_TASKS ||
        panel_state == WINDOW_ISLAND_PANEL_EFFECT_DEBUG) {
        const char *const task_window_names[] = {
            "IWTasks", "IWTaskInfo", "IWTaskOptions"
        };
        const char *const effect_window_names[] = {
            "IWEffList", "IWSFXList"
        };
        static const char *const task_scroll_names[] = {
            "scrollup", "scrolldn", "escrollup", "escrolldn"
        };
        const WindowTemplate *hover_scroll = g_mouse_inside
            ? window_catalog_hit_test_names(&g_window_catalog, 3,
                  g_mouse_x, g_mouse_y, task_scroll_names,
                  sizeof(task_scroll_names) / sizeof(task_scroll_names[0]))
            : NULL;
        size_t task_index;
        if (panel_state == WINDOW_ISLAND_PANEL_TASKS) {
            for (task_index = 0;
                 task_index < sizeof(task_window_names) / sizeof(task_window_names[0]);
                 ++task_index) {
                const WindowTemplate *task_panel = window_catalog_find(
                    &g_window_catalog, task_window_names[task_index], 3);
                if (task_panel != NULL && task_panel->shape_frame >= 0 &&
                    g_temp_hole_art.frame_count > (uint32_t)task_panel->shape_frame) {
                    draw_sprite(dc, &g_temp_hole_art,
                                (uint32_t)task_panel->shape_frame,
                                task_panel->pane.left, task_panel->pane.top);
                }
            }
        } else {
            for (task_index = 0;
                 task_index < sizeof(effect_window_names) / sizeof(effect_window_names[0]);
                 ++task_index) {
                const WindowTemplate *effect_panel = window_catalog_find(
                    &g_window_catalog, effect_window_names[task_index], 3);
                if (effect_panel != NULL && effect_panel->shape_frame >= 0 &&
                    g_temp_hole_art.frame_count > (uint32_t)effect_panel->shape_frame) {
                    draw_sprite(dc, &g_temp_hole_art,
                                (uint32_t)effect_panel->shape_frame,
                                effect_panel->pane.left, effect_panel->pane.top);
                }
            }
        }
        for (task_index = 0;
             task_index < sizeof(task_scroll_names) / sizeof(task_scroll_names[0]);
             ++task_index) {
            const WindowTemplate *control = window_catalog_find(
                &g_window_catalog, task_scroll_names[task_index], 3);
            if (control != NULL &&
                window_catalog_scroll_panel_mode(control->name) == panel_state &&
                control->shape_frame >= 0) {
                int frame = window_catalog_control_frame(
                    control, control == hover_scroll);
                if (frame < 0 || g_task_scroll_art.frame_count <= (uint32_t)frame)
                    continue;
                /* FUN_0042fa0f routes each pair to its distinct list panel. */
                draw_sprite(dc, &g_task_scroll_art, (uint32_t)frame,
                            control->pane.left, control->pane.top);
            }
        }
        if (panel_state == WINDOW_ISLAND_PANEL_TASKS) {
            const WindowTemplate *task_list_panel = window_catalog_find(
                &g_window_catalog, "IWTasks", 3);
            const WindowTemplate *task_info_panel = window_catalog_find(
                &g_window_catalog, "IWTaskInfo", 3);
            uint8_t task_slots[GAME_SESSION_MAX_TASKS];
            size_t task_count = g_game_session_valid && hall_player >= 0
                ? game_session_collect_task_slots(&g_game_session,
                    (int16_t)hall_player, task_slots,
                    sizeof(task_slots) / sizeof(task_slots[0])) : 0;
            struct TaskRowLabel {
                const char *text;
                int x;
                int y;
                COLORREF color;
            } row_labels[GAME_SESSION_MAX_TASKS * 2];
            size_t row_label_count = 0;
            int visible_rows = task_list_panel != NULL
                ? (task_list_panel->pane.bottom - task_list_panel->pane.top) / 13
                : 0;
            const GamePendingEvent *selected_event = NULL;
            size_t selected_index;
            if (task_count == 0) {
                g_selected_task_slot = -1;
            } else {
                for (selected_index = 0; selected_index < task_count;
                     ++selected_index) {
                    if (task_slots[selected_index] == g_selected_task_slot) {
                        selected_event = &g_game_session.pending_events[
                            task_slots[selected_index]];
                        break;
                    }
                }
                if (selected_event == NULL) {
                    g_selected_task_slot = task_slots[0];
                    selected_event = &g_game_session.pending_events[
                        task_slots[0]];
                    /* FUN_004455d1 selects the first task when the previous
                       selection is absent from the refreshed projection. */
                }
            }
            if (task_list_panel != NULL && task_count != 0 &&
                visible_rows > 0) {
                size_t visible_index;
                int offset = window_catalog_scroll_step(
                    g_task_scroll_offset, (int)task_count, visible_rows, 0);
                /* Task slots can disappear between scroll input events. Keep
                   the view inside the same max offset used by 6000/6001 so
                   the list cannot remain blank past its new end. */
                g_task_scroll_offset = offset;
                for (visible_index = 0;
                     visible_index < (size_t)visible_rows &&
                     (size_t)offset + visible_index < task_count;
                     ++visible_index) {
                    const GamePendingEvent *event = &g_game_session.pending_events[
                        task_slots[(size_t)offset + visible_index]];
                    const int stock_resource = hall_resource_task_index(
                        hall_player, task_slots[(size_t)offset + visible_index]);
                    static const SpriteSheet *const resource_art[] = {
                        &g_bildtone_art, &g_tone_crys_art, &g_magctone_art
                    };
                    IslandTaskRow row;
                    IslandTaskRowPosition position;
                    const char *label;
                    /* FUN_004459e6: a type-4 sub-type-1 task whose building
                       has a pending UPGRADE request is the UPGRADE row (icon
                       2, secondary frame (item == 0x2f) + 5, bildtone icon,
                       gauge +0x28 over 20). The port's staff upgrade request
                       is that task (payload_12 == 1, location in payload_0e). */
                    const GameRuntimeLocation *upgrade_site = NULL;
                    if (stock_resource < 0 && event->action_type == 4 &&
                        event->payload_12 == 1 && event->payload_0a >= 0 &&
                        (unsigned int)event->payload_0a <
                            g_game_session.island_count &&
                        event->payload_0e >= 0 &&
                        (unsigned int)event->payload_0e <
                            g_game_session.islands[event->payload_0a]
                                .location_count)
                        upgrade_site = &g_game_session.islands[event->payload_0a]
                            .locations[event->payload_0e];
                    if (upgrade_site != NULL) {
                        row.label_key = "UPGRADE";
                        row.task_icon_frame = 2;
                        row.secondary_task_icon_frame =
                            (int8_t)(upgrade_site->record_value_10 == 0x2f ? 6 : 5);
                        row.resource_icon_type = -1;
                    }
                    if (!(upgrade_site != NULL ? 1 : stock_resource >= 0
                            ? island_panel_info_stock_task_row(
                                  (unsigned int)stock_resource, &row)
                            : island_panel_info_task_row(event->action_type,
                                  event->payload_12, &row)) ||
                        !island_panel_info_task_row_position(task_list_panel,
                            (unsigned int)visible_rows,
                            (unsigned int)visible_index, &position)) continue;
                    /* FUN_004459e6 writes colour index 5 into the SMFONT object for
                       priority 2 and index 2 for priority 3 before the label
                       and the "[n]" count, then restores index 6. */
                    COLORREF row_text_color = event->priority == 2U
                        ? g_island_palette[5] : event->priority == 3U
                        ? g_island_palette[2] : g_island_palette[6];
                    label = task_label_text(row.label_key);
                    if (label == NULL || label[0] == '\0') continue;
                    if (task_slots[(size_t)offset + visible_index] ==
                        g_selected_task_slot) {
                        draw_task_row_highlight(dc, task_list_panel,
                            (unsigned int)visible_rows,
                            (unsigned int)visible_index);
                    }
                    if (row.task_icon_frame >= 0 &&
                        g_task_icon_art.frame_count >
                            (uint32_t)row.task_icon_frame) {
                        draw_sprite(dc, &g_task_icon_art,
                            (uint32_t)row.task_icon_frame,
                            task_list_panel->pane.left + position.icon_x,
                            task_list_panel->pane.top + position.y);
                    }
                    if (row_label_count < GAME_SESSION_MAX_TASKS) {
                        row_labels[row_label_count].text = label;
                        row_labels[row_label_count].color = row_text_color;
                        row_labels[row_label_count].x = task_list_panel->pane.left +
                                                       position.label_x;
                        row_labels[row_label_count].y = task_list_panel->pane.top +
                                                       position.y;
                        ++row_label_count;
                    }
                    /* FUN_004459e6 draws "[%d]" from task+4 at x=5 on every
                       row; FUN_00421ec1 increments it when a floater attaches
                       to the task, so it counts the floaters linked to it. */
                    if (row_label_count < GAME_SESSION_MAX_TASKS * 2U) {
                        static char task_count_text[GAME_SESSION_MAX_TASKS * 2][12];
                        unsigned int attached = 0;
                        unsigned int floater_slot;
                        for (floater_slot = 0;
                             floater_slot < g_game_session.floater_count;
                             ++floater_slot) {
                            if (g_game_session.floaters[floater_slot]
                                    .linked_task_slot ==
                                (int16_t)task_slots[(size_t)offset +
                                                    visible_index])
                                ++attached;
                        }
                        (void)snprintf(task_count_text[row_label_count],
                            sizeof(task_count_text[row_label_count]),
                            "[%u]", attached);
                        row_labels[row_label_count].text =
                            task_count_text[row_label_count];
                        row_labels[row_label_count].color = row_text_color;
                        row_labels[row_label_count].x =
                            task_list_panel->pane.left + 5;
                        row_labels[row_label_count].y =
                            task_list_panel->pane.top + position.y;
                        ++row_label_count;
                    }
                    if (row.secondary_task_icon_frame >= 0 &&
                        g_task_icon_art.frame_count >
                            (uint32_t)row.secondary_task_icon_frame) {
                        draw_sprite(dc, &g_task_icon_art,
                            (uint32_t)row.secondary_task_icon_frame,
                            task_list_panel->pane.left + position.secondary_icon_x,
                            task_list_panel->pane.top + position.y);
                    }
                    if (row.resource_icon_type >= 0 &&
                        row.resource_icon_type < GAME_RESOURCE_TYPE_COUNT &&
                        resource_art[(unsigned int)row.resource_icon_type]->frame_count > 0) {
                        draw_sprite(dc,
                            resource_art[(unsigned int)row.resource_icon_type], 0,
                            task_list_panel->pane.left + position.resource_icon_x,
                            task_list_panel->pane.top + position.y + 7);
                        draw_task_stock_gauge(dc, task_list_panel, hall_player,
                            (unsigned int)row.resource_icon_type, position.y);
                    }
                    if (upgrade_site != NULL) {
                        /* Gauge numerator is the building's +0x28 counter
                           (Build Tone stock), denominator 20, __ftol chop. */
                        unsigned int upgrade_fill = 66U;
                        if (g_bildtone_art.frame_count > 0) {
                            draw_sprite(dc, &g_bildtone_art, 0,
                                task_list_panel->pane.left +
                                    position.resource_icon_x,
                                task_list_panel->pane.top + position.y + 7);
                        }
                        if (upgrade_site->resource_stock[0] < 20U)
                            upgrade_fill = (66U *
                                (unsigned int)upgrade_site->resource_stock[0]) /
                                20U;
                        draw_task_gauge(dc, task_list_panel, position.y,
                                        upgrade_fill);
                    } else if (event->action_type == 0x12) {
                        draw_task_repair_gauge(dc, task_list_panel, event,
                                               position.y);
                    } else if (event->action_type == 5) {
                        draw_task_construction_gauge(dc, task_list_panel, event,
                                                     position.y);
                    }
                }
            }
            if (row_label_count != 0) {
                size_t label_index;
                /* Row icons and gauges are GDI blits. Flush once, then write
                   all task labels directly so each row doesn't stall GDI. */
                (void)GdiFlush();
                for (label_index = 0; label_index < row_label_count;
                     ++label_index) {
                    draw_small_label_pixels(row_labels[label_index].text,
                        row_labels[label_index].x, row_labels[label_index].y,
                        row_labels[label_index].color);
                }
            }
            if (task_info_panel != NULL && g_empty_task_text[0] != '\0') {
                if (selected_event == NULL) {
                    int label_width = measure_bitmap_text(NULL, g_empty_task_text,
                                                          strlen(g_empty_task_text));
                    int label_x;
                    int label_y;
                    if (island_panel_info_empty_task_label_position(task_info_panel,
                            label_width, &label_x, &label_y)) {
                        draw_bitmap_label(dc, g_empty_task_text, label_x, label_y,
                                          RGB(185, 205, 220));
                    }
                } else {
                    const char *priority_key =
                        island_panel_info_task_priority_key(selected_event->priority);
                    const char *priority_text = task_label_text(priority_key);
                    if (priority_text != NULL && priority_text[0] != '\0') {
                        draw_bitmap_label(dc, priority_text,
                            task_info_panel->pane.left + 10,
                            task_info_panel->pane.top + 0x2b,
                            RGB(185, 205, 220));
                    }
                    if (selected_event->action_type == 5 && hall_player >= 0 &&
                        hall_player < GAME_START_PLAYER_COUNT &&
                        selected_event->payload_12 >= 0x25 &&
                        selected_event->payload_12 <= 0x34) {
                        uint16_t building_id = (uint16_t)(
                            selected_event->payload_12 + hall_player * 16);
                        const PadCatalogItem *building = pad_catalog_find(
                            &g_pad_catalog, building_id);
                        int32_t maintenance_budget = g_game_session
                            .economy[hall_player].source_maintenance_budget;
                        if (building != NULL &&
                            building->maintenance_tone_cost > maintenance_budget) {
                            char warning[96];
                            (void)snprintf(warning, sizeof(warning),
                                "Entretien insuffisant %ld/%d",
                                (long)maintenance_budget,
                                (int)building->maintenance_tone_cost);
                            draw_bitmap_label(dc, warning,
                                task_info_panel->pane.left + 10,
                                task_info_panel->pane.top + 0x42,
                                RGB(245, 190, 96));
                        }
                    }
                    /* FUN_004469d6 resolves payload island/site into the
                       runtime location and calls FUN_0040bf98 only when its
                       dword at +4 is zero. GameRuntimeLocation.owner_id maps
                       that field; its current item layers supply the preview. */
                    if (task_info_panel != NULL && g_game_session_valid &&
                        selected_event->payload_0a >= 0 &&
                        (unsigned int)selected_event->payload_0a <
                            g_game_session.island_count) {
                        GameRuntimeIsland *target_island =
                            &g_game_session.islands[
                                (unsigned int)selected_event->payload_0a];
                        if (selected_event->payload_0e >= 0 &&
                            (unsigned int)selected_event->payload_0e <
                                target_island->location_count) {
                            GameRuntimeLocation *target_location =
                                &target_island->locations[
                                    (unsigned int)selected_event->payload_0e];
                            int preview_x;
                            int preview_y;
                            if (island_panel_info_task_target_preview_position(
                                    task_info_panel, selected_event->action_type,
                                    target_location->owner_id,
                                    &preview_x, &preview_y)) {
                                (void)draw_runtime_item_scaled(dc, target_location,
                                    preview_x, preview_y, 0x8000U);
                            }
                        }
                    }
                    {
                        if (selected_event->action_type == 5) {
                            uint16_t item_id;
                            size_t name_index;
                            int info_width = task_info_panel->pane.right -
                                             task_info_panel->pane.left;
                            int info_height = task_info_panel->pane.bottom -
                                              task_info_panel->pane.top;
                            if (island_panel_info_construction_task_indices(
                                    selected_event->payload_12,
                                    (uint8_t)hall_player, &item_id,
                                    &name_index)) {
                                if (g_task_building_const_text[0] != '\0') {
                                    int label_width = measure_bitmap_text(NULL,
                                        g_task_building_const_text,
                                        strlen(g_task_building_const_text));
                                    int info_width =
                                        task_info_panel->pane.right -
                                        task_info_panel->pane.left;
                                    draw_bitmap_label(dc,
                                        g_task_building_const_text,
                                        task_info_panel->pane.left +
                                            (info_width - label_width) / 2,
                                        task_info_panel->pane.top + 5,
                                        RGB(185, 205, 220));
                                }
                                if (name_index < BUILDING_NAME_COUNT &&
                                    g_building_names[name_index][0] != '\0') {
                                    /* Leave room for the right-side building
                                       preview; long localized names otherwise
                                       draw underneath the sprite. */
                                    draw_wrapped_bitmap_label(dc,
                                        g_building_names[name_index],
                                        task_info_panel->pane.left + 10,
                                        task_info_panel->pane.top + 0x1e,
                                        info_width - 0x50, 1,
                                        RGB(185, 205, 220));
                                }
                                if (item_id < g_pad_catalog.item_count &&
                                    item_id < PAD_CATALOG_MAX_ITEMS &&
                                    g_building_art[item_id].frame_count != 0) {
                                    (void)draw_building_preview(dc, item_id,
                                        (uint8_t)hall_player,
                                        task_info_panel->pane.left + info_width - 0x1e,
                                        task_info_panel->pane.top + info_height - 10,
                                        0x8000U);
                                }
                            }
                        } else {
                            const char *title_key = NULL;
                            const char *category_key = NULL;
                            if (island_panel_info_task_transfer_keys(
                                    selected_event->action_type,
                                    selected_event->payload_12,
                                    &title_key, &category_key)) {
                                const char *title_text = task_label_text(title_key);
                                const char *category_text =
                                    task_label_text(category_key);
                                if (title_text != NULL && title_text[0] != '\0') {
                                    int title_width = measure_bitmap_text(NULL,
                                        title_text, strlen(title_text));
                                    int info_width = task_info_panel->pane.right -
                                                     task_info_panel->pane.left;
                                    draw_bitmap_label(dc, title_text,
                                        task_info_panel->pane.left +
                                            (info_width - title_width) / 2,
                                        task_info_panel->pane.top + 5,
                                        RGB(185, 205, 220));
                                }
                                if (category_text != NULL && category_text[0] != '\0') {
                                    draw_bitmap_label(dc, category_text,
                                        task_info_panel->pane.left + 10,
                                        task_info_panel->pane.top + 0x1e,
                                        RGB(185, 205, 220));
                                }
                                if (selected_event->payload_12 >= 1 &&
                                    selected_event->payload_12 <= 3) {
                                    static const SpriteSheet *const resource_art[] = {
                                        &g_bildtone_art, &g_tone_crys_art,
                                        &g_magctone_art
                                    };
                                    const SpriteSheet *sheet = resource_art[
                                        (unsigned int)selected_event->payload_12 - 1U];
                                    if (sheet->frame_count > 4U) {
                                        const SpriteFrame *icon = &sheet->frames[4];
                                        int icon_x;
                                        int icon_y;
                                        if (island_panel_info_task_icon_position(
                                                task_info_panel, icon->x_offset,
                                                icon->y_offset, icon->hit_left,
                                                icon->hit_top, icon->hit_right,
                                                icon->hit_bottom, 10,
                                                &icon_x, &icon_y)) {
                                            draw_sprite(dc, sheet, 4,
                                                        icon_x, icon_y);
                                        }
                                    }
                                }
                                {
                                    int artifact_frame =
                                        island_panel_info_task_artifact_frame(
                                            selected_event->payload_12);
                                    if (artifact_frame >= 0 &&
                                        (uint32_t)artifact_frame <
                                            g_inventory_item_art.frame_count) {
                                        const SpriteFrame *icon =
                                            &g_inventory_item_art.frames[
                                                (unsigned int)artifact_frame];
                                        int icon_x;
                                        int icon_y;
                                        if (island_panel_info_task_icon_position(
                                                task_info_panel,
                                                icon->x_offset, icon->y_offset,
                                                icon->hit_left, icon->hit_top,
                                                icon->hit_right, icon->hit_bottom,
                                                0, &icon_x, &icon_y)) {
                                            /* FUN_004469d6 draws TRIGGERS at
                                               item_id - 5; local shapes.txt
                                               maps that sheet to alltrigs.shp. */
                                            draw_sprite(dc, &g_inventory_item_art,
                                                (uint32_t)artifact_frame,
                                                icon_x, icon_y);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (selected_event != NULL) {
                static const char *const task_option_names[] = {
                    "TaskNorm", "TaskHigh", "TaskExcl", "TaskKill"
                };
                const WindowTemplate *hovered_option = g_mouse_inside
                    ? window_catalog_hit_test_names(&g_window_catalog, 3,
                        g_mouse_x, g_mouse_y, task_option_names,
                        sizeof(task_option_names) / sizeof(task_option_names[0]))
                    : NULL;
                size_t option_index;
                for (option_index = 0;
                     option_index < sizeof(task_option_names) /
                                    sizeof(task_option_names[0]);
                     ++option_index) {
                    const WindowTemplate *option = window_catalog_find(
                        &g_window_catalog, task_option_names[option_index], 3);
                    int frame;
                    if (option == NULL ||
                        strcmp(option->shape_id, "PRIOR") != 0 ||
                        option->shape_frame < 0) continue;
                    frame = window_catalog_control_frame(
                        option, option == hovered_option);
                    if (frame >= 0 &&
                        g_task_priority_art.frame_count > (uint32_t)frame) {
                        draw_sprite(dc, &g_task_priority_art, (uint32_t)frame,
                                    option->pane.left, option->pane.top);
                    }
                }
            }
        }
        return;
    }
    if (hall_player < 0) return;
    if (panel_state == WINDOW_ISLAND_PANEL_INVENTORY) {
        panel = window_catalog_find(&g_window_catalog, "IWInventory", 3);
    } else if (panel_state == WINDOW_ISLAND_PANEL_GLYPHS) {
        panel = window_catalog_find(&g_window_catalog, "IWGlyphs", 3);
        if (g_game_session.economy[(unsigned int)hall_player].glyph_mask == 0) {
            /* FUN_0043dee3 draws TEMPHOLE/NOKNOW for a zero ownership mask. */
            empty_message = g_empty_glyph_text;
        }
    } else if (panel_state == WINDOW_ISLAND_PANEL_DIPLOMACY) {
        panel = window_catalog_find(&g_window_catalog, "IWDiplomacy", 3);
    } else if (panel_state == WINDOW_ISLAND_PANEL_TRADE) {
        panel = window_catalog_find(&g_window_catalog, "IWTrade", 3);
    }
    if (panel == NULL || panel->shape_frame < 0 ||
        g_temp_hole_art.frame_count <= (uint32_t)panel->shape_frame) return;
    draw_sprite(dc, &g_temp_hole_art, (uint32_t)panel->shape_frame,
                panel->pane.left, panel->pane.top);
    if (panel_state == WINDOW_ISLAND_PANEL_TRADE) {
        const SpriteSheet *const resource_sheets[GAME_RESOURCE_TYPE_COUNT] = {
            &g_bildtone_art, &g_tone_crys_art, &g_magctone_art
        };
        const GamePlayerEconomy *economy =
            &g_game_session.economy[(unsigned int)hall_player];
        unsigned int resource;
        unsigned int target;
        for (target = 0; target < GAME_TRADE_TARGET_COUNT; ++target) {
            /* FUN_0043edac: FUN_00428191(class, 0, x = 55 + 38c, y = 12) with
               class c, or c + 1 once c reaches the local player. */
            unsigned int tribe = target >= (unsigned int)hall_player
                ? target + 1U : target;
            draw_diplomacy_initial_worker_icon(dc, NULL, tribe,
                panel->pane.left + 55 + (int)target * 38,
                panel->pane.top + 12);
        }
        for (resource = 0; resource < GAME_RESOURCE_TYPE_COUNT; ++resource) {
            if (resource_sheets[resource]->frame_count > 4U) {
                /* FUN_0043edac draws frame 4 of each named Tone sheet. */
                draw_sprite(dc, resource_sheets[resource], 4,
                            panel->pane.left + 30,
                            panel->pane.top + 52 + (int)resource * 24);
            }
        }
        for (resource = 0; resource < GAME_RESOURCE_TYPE_COUNT; ++resource) {
            for (target = 0; target < GAME_TRADE_TARGET_COUNT; ++target) {
                char amount_text[8];
                unsigned int amount = economy->trade_offer[resource][target];
                int width;
                int x;
                int y;
                /* FUN_0043edac prints "%d" for a nonzero offer and "-" for zero. */
                if (amount != 0)
                    (void)snprintf(amount_text, sizeof(amount_text), "%u", amount);
                else
                    (void)snprintf(amount_text, sizeof(amount_text), "-");
                width = measure_bitmap_text(NULL, amount_text, strlen(amount_text));
                x = panel->pane.left + (int)target * 38 + 40 + (28 - width) / 2;
                y = panel->pane.top + (int)resource * 24 + 44;
                draw_bitmap_label(dc, amount_text, x, y, RGB(220, 232, 244));
            }
        }
    }
    if (panel_state == WINDOW_ISLAND_PANEL_INVENTORY) {
        GameInventoryEntry entries[GAME_INVENTORY_ITEM_COUNT];
        GameInventoryEntry page[GAME_INVENTORY_PAGE_SIZE];
        const GamePlayerEconomy *economy =
            &g_game_session.economy[(unsigned int)hall_player];
        size_t entry_count = game_inventory_collect(economy->inventory_count,
            entries, GAME_INVENTORY_ITEM_COUNT);
        size_t visible_count;
        size_t slot;
        const WindowTemplate *cycle = window_catalog_find(
            &g_window_catalog, "InvCycle", 3);
        const char *const cycle_names[] = {"InvCycle"};
        const WindowTemplate *hover_cycle = g_mouse_inside
            ? window_catalog_hit_test_names(&g_window_catalog, 3,
                  g_mouse_x, g_mouse_y, cycle_names, 1)
            : NULL;
        if (entry_count == 0) {
            /* FUN_0043d6a3 draws NOART with BIGFONT (palette index 6). */
            int use_big = g_big_font.bytes != NULL;
            int width = use_big
                ? measure_big_text(g_empty_inventory_text,
                                   strlen(g_empty_inventory_text))
                : measure_small_text(g_empty_inventory_text,
                                     strlen(g_empty_inventory_text));
            int x = panel->pane.left +
                ((panel->pane.right - panel->pane.left) - width) / 2;
            /* FUN_0043d6a3 passes y = (bottom - top) / 2 - 6 for the NOART
               text, with no text-height term (ev_7105b54d…). */
            int y = panel->pane.top +
                (panel->pane.bottom - panel->pane.top) / 2 - 6;
            if (use_big)
                draw_big_label(dc, g_empty_inventory_text, x, y,
                               g_island_palette[6]);
            else
                draw_small_label(dc, g_empty_inventory_text, x, y,
                                 g_island_palette[6]);
        } else {
            /* FUN_0043d6a3 uses the stored page index directly. If the item
               count shrinks, the source leaves an out-of-range page empty
               until InvCycle wraps it back to zero. */
            size_t current_page = g_inventory_page;
            int pane_width = panel->pane.right - panel->pane.left;
            int pane_height = panel->pane.bottom - panel->pane.top;
            int column_width = pane_width / 5;
            int row_height = (pane_height - 24) / 2;
            visible_count = game_inventory_page(entries, entry_count,
                                                 current_page, page);
            for (slot = 0; slot < visible_count; ++slot) {
                uint32_t frame_index = page[slot].item_id -
                    GAME_INVENTORY_ITEM_FIRST_ID;
                const SpriteFrame *icon = &g_inventory_item_art.frames[frame_index];
                int column = (int)(slot % 5);
                int row = (int)(slot / 5);
                int cell_left = panel->pane.left + column * column_width;
                int cell_top = panel->pane.top + 24 + row * row_height;
                int x;
                int y;
                if (!game_inventory_sprite_position(
                        cell_left, cell_top, column_width, row_height,
                        icon->x_offset, icon->y_offset,
                        icon->hit_left, icon->hit_top,
                        icon->hit_right, icon->hit_bottom,
                        &x, &y)) {
                    /* Empty SHP frames have no opaque bounds and contribute
                       no visible pixels; keep a deterministic cell origin. */
                    x = cell_left;
                    y = cell_top;
                }
                if (page[slot].item_id == (uint8_t)g_selected_inventory_item ||
                    page[slot].item_id == (uint8_t)g_hovered_inventory_item) {
                    int palette_index = page[slot].item_id ==
                        (uint8_t)g_selected_inventory_item ? 4 : 1;
                    HPEN outline = CreatePen(PS_SOLID, 1,
                                              g_island_palette[palette_index]);
                    if (outline != NULL) {
                        HGDIOBJ previous = SelectObject(dc, outline);
                        HGDIOBJ previous_brush = SelectObject(dc, GetStockObject(NULL_BRUSH));
                        Rectangle(dc, cell_left + 1, cell_top + 1,
                                  cell_left + column_width - 1,
                                  cell_top + row_height - 1);
                        SelectObject(dc, previous_brush);
                        SelectObject(dc, previous);
                        DeleteObject(outline);
                    }
                }
                draw_sprite(dc, &g_inventory_item_art, frame_index, x, y);
                if (page[slot].count > 1) {
                    char count_text[12];
                    /* The count format at 0x4a020c is "(%d)". */
                    (void)snprintf(count_text, sizeof(count_text), "(%u)",
                                   (unsigned int)page[slot].count);
                    draw_bitmap_label(dc, count_text,
                        x + 7, y - 21, RGB(235, 235, 220));
                }
            }
        }
        if (entry_count > GAME_INVENTORY_PAGE_SIZE && cycle != NULL) {
            int frame = window_catalog_control_frame(cycle, cycle == hover_cycle);
            if (frame >= 0 && g_build_cycle_art.frame_count > (uint32_t)frame) {
                draw_sprite(dc, &g_build_cycle_art, (uint32_t)frame,
                            cycle->pane.left, cycle->pane.top);
            }
        }
    }
    if (panel_state == WINDOW_ISLAND_PANEL_GLYPHS) {
        const GamePlayerEconomy *economy =
            &g_game_session.economy[(unsigned int)hall_player];
        uint16_t glyph_mask = economy->glyph_mask;
        int pane_width = panel->pane.right - panel->pane.left;
        int pane_height = panel->pane.bottom - panel->pane.top;
        unsigned int glyph_index;
        if (glyph_mask != 0) {
            int anchor_x = panel->pane.left + pane_width;
            int anchor_y = panel->pane.top + pane_height;
            draw_sprite(dc, &g_glyph_inventory_art, 0,
                        panel->pane.left, panel->pane.top);
            for (glyph_index = 0; glyph_index < GAME_GLYPH_COUNT; ++glyph_index) {
                uint32_t frame = game_glyph_inventory_frame(
                    glyph_mask, (int)glyph_index, g_hovered_glyph);
                if (frame != UINT32_MAX) {
                    draw_sprite(dc, &g_glyph_inventory_art, frame,
                                anchor_x, anchor_y);
                }
            }
        } else if (g_temp_hole_art.frame_count > 1U) {
            draw_sprite(dc, &g_temp_hole_art, 1,
                        panel->pane.left, panel->pane.top);
        }
    }
    if (panel_state == WINDOW_ISLAND_PANEL_DIPLOMACY) {
        draw_diplomacy_panel(dc, panel, hall_player);
    }
    if (empty_message != NULL && empty_message[0] != '\0') {
        int width = measure_bitmap_text(NULL, empty_message, strlen(empty_message));
        int x = panel->pane.left +
            ((panel->pane.right - panel->pane.left) - width) / 2;
        int y = panel->pane.top +
            ((panel->pane.bottom - panel->pane.top) -
             (int)g_small_font.height) / 2 - 6;
        draw_bitmap_label(dc, empty_message, x, y, RGB(185, 205, 220));
    }
    if (panel_state == WINDOW_ISLAND_PANEL_TRADE) {
        static const char *const trade_names[] = {"TradeZERO", "TradeDOIT"};
        size_t index;
        for (index = 0; index < sizeof(trade_names) / sizeof(trade_names[0]); ++index) {
            const WindowTemplate *button = window_catalog_find(
                &g_window_catalog, trade_names[index], 3);
            const WindowTemplate *hover_control;
            int hovered;
            int frame;
            if (button == NULL) continue;
            hover_control = g_mouse_inside
                ? window_catalog_hit_test_names(&g_window_catalog, 3,
                    g_mouse_x, g_mouse_y, trade_names,
                    sizeof(trade_names) / sizeof(trade_names[0])) : NULL;
            hovered = hover_control == button;
            frame = window_catalog_control_frame(button, hovered);
            if (frame >= 0 && (uint32_t)frame < g_trade_button_art.frame_count) {
                draw_sprite(dc, &g_trade_button_art, (uint32_t)frame,
                            button->pane.left, button->pane.top);
            }
            /* The hovered button's caption (TRZERO / TRDOIT) is drawn at
               (156, 50) of IWTrade by FUN_0043edac. */
            if (hovered && g_trade_caption_text[index][0] != '\0') {
                draw_bitmap_label(dc, g_trade_caption_text[index],
                                  panel->pane.left + 156, panel->pane.top + 50,
                                  RGB(185, 205, 220));
            }
        }
    }
    draw_hall_info_panel(dc, panel_state);
}
