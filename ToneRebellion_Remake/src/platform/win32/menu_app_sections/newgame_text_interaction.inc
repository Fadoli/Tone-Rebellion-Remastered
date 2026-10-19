static int update_hover_help(int x, int y)
{
    int help = -1;
    if (g_menu.screen == SCREEN_MAIN_MENU) {
        const WindowTemplate *control = window_catalog_hit_test(&g_window_catalog, 0, x, y);
        if (control != NULL && strcmp(control->name, "NEWGAME") == 0) help = HELP_MAIN_NEWGAME;
        else if (control != NULL && strcmp(control->name, "RESUME") == 0 && g_resume_available)
            help = HELP_MAIN_RESUME;
        else if (control != NULL && strcmp(control->name, "LOADGAME") == 0) help = HELP_MAIN_LOAD;
        else if (control != NULL && strcmp(control->name, "EXITAPP") == 0) help = HELP_MAIN_EXIT;
    }
    if (help == g_hovered_help) return 0;
    g_hovered_help = help;
    return 1;
}

static int tribe_icon_at(int x, int y)
{
    static const POINT centers[4] = {{170, 240}, {320, 90}, {470, 240}, {320, 390}};
    int tribe;
    for (tribe = 0; tribe < 4; ++tribe) {
        int dx = x - centers[tribe].x;
        int dy = y - centers[tribe].y;
        if (dx * dx + dy * dy < 2500) return tribe;
    }
    return -1;
}

static int newgame_text_index_at(int x, int y)
{
    int tribe = tribe_icon_at(x, y);
    const WindowTemplate *control;
    if (tribe >= 0) return tribe;
    {
        int dx = x - 320;
        int dy = y - 240;
        int distance_squared = dx * dx + dy * dy;
        if (distance_squared < 100) return 4;
        if (distance_squared < 200) return 5;
    }
    control = window_catalog_hit_test(&g_window_catalog, 1, x, y);
    if (control == NULL) return -1;
    if (strcmp(control->message_destination, "WINMGR") == 0 &&
        control->send_message[0] == 1 && control->send_message[1] == 0) return 6;
    if (strcmp(control->message_destination, "MASTER") != 0) return -1;
    if (control->send_message[0] == 52) return 7;
    if (control->send_message[0] == 53) return 5;
    if (control->send_message[0] == 55) return 4;
    if (control->send_message[0] >= 60 && control->send_message[0] <= 63)
        return control->send_message[0] - 60;
    return -1;
}

static int update_newgame_text(int x, int y)
{
    int text_index = g_menu.screen == SCREEN_NEW_GAME ? newgame_text_index_at(x, y) : -1;
    if (text_index == g_hovered_newgame_text) return 0;
    g_hovered_newgame_text = text_index;
    return 1;
}

static void draw_hover_help(HDC dc)
{
    if (g_menu.screen != SCREEN_MAIN_MENU || !g_mouse_inside || g_hovered_help < 0 ||
        (uint32_t)g_hovered_help >= g_menu_help.frame_count) return;
    /* Keep contextual help away from the title buttons and their baked-in
       captions. Anchoring it to the pointer covered the active control. */
    draw_sprite(dc, &g_menu_help, (uint32_t)g_hovered_help,
                12, 12);
}

static void draw_newgame_text(HDC dc)
{
    if (g_menu.screen != SCREEN_NEW_GAME || !g_mouse_inside ||
        g_hovered_newgame_text < 0 || g_hovered_newgame_text >= 8) return;
    draw_sprite(dc, &g_newgame_captions, (uint32_t)g_hovered_newgame_text, 160, 430);
}

static void draw_tribe_descriptions(HDC dc)
{
    int left_index;
    int right_index;
    if (g_menu.screen != SCREEN_NEW_GAME || g_menu.selected_tribe < 0 ||
        g_menu.selected_tribe >= 4) return;
    left_index = g_menu.selected_tribe * 2;
    right_index = left_index + 1;
    if ((uint32_t)right_index >= g_tribe_descriptions.frame_count) return;
    draw_sprite(dc, &g_tribe_descriptions, (uint32_t)left_index, 0, 0);
    draw_sprite(dc, &g_tribe_descriptions, (uint32_t)right_index, 0, 0);
}

