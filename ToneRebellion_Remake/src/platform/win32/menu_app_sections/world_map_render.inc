static int world_island_at(int x, int y)
{
    const WorldDefinition *world;
    size_t island_index;
    if (g_menu.world_index < 0 || g_menu.world_index >= g_menu.world_map.world_count) return -1;
    world = &g_menu.world_map.worlds[g_menu.world_index];
    island_index = world->island_count;
    while (island_index > 0) {
        const WorldIsland *island;
        uint32_t frame_index;
        const SpriteFrame *frame;
        int island_x;
        int island_y;
        int left;
        int top;
        int right;
        int bottom;
        --island_index;
        island = &world->islands[island_index];
        /* Use the non-hover image's bounds so changing to the highlighted
           frame cannot make the cursor fall out of its own hit target. */
        frame_index = world_island_frame_index(island_index, island->shape_id, 0);
        if (frame_index >= g_small_islands.frame_count) continue;
        frame = &g_small_islands.frames[frame_index];
        if (frame->hit_right <= frame->hit_left || frame->hit_bottom <= frame->hit_top) continue;
        world_island_position(island, &island_x, &island_y);
        left = island_x + frame->x_offset + frame->hit_left;
        top = island_y + frame->y_offset + frame->hit_top;
        right = island_x + frame->x_offset + frame->hit_right;
        bottom = island_y + frame->y_offset + frame->hit_bottom;
        if (left < x && x < right && top < y && y < bottom) return (int)island_index;
    }
    return -1;
}

static int update_world_map_hover(int x, int y)
{
    int island = g_menu.screen == SCREEN_WORLD_MAP ? world_island_at(x, y) : -1;
    if (island == g_hovered_island) return 0;
    g_hovered_island = island;
    return 1;
}

static void draw_bitmap_label(HDC dc, const char *text, int x, int y, COLORREF color)
{
    if (dc == g_paint_buffer_dc && g_paint_buffer_pixels != NULL) {
        uint32_t dib_pixel = ((uint32_t)GetRValue(color) << 16) |
                             ((uint32_t)GetGValue(color) << 8) |
                             (uint32_t)GetBValue(color);
        /* Flush preceding GDI blits before changing the DIB memory directly. */
        (void)GdiFlush();
        (void)bitmap_font_render_pixels(&g_bitmap_font, text,
            (uint32_t *)g_paint_buffer_pixels, LOGICAL_WIDTH, LOGICAL_HEIGHT,
            LOGICAL_WIDTH, x, y, dib_pixel);
        return;
    }
    const unsigned char *cursor = (const unsigned char *)text;
    while (*cursor != '\0') {
        uint32_t code = *cursor < g_bitmap_font.glyph_count ? *cursor : (uint32_t)'?';
        uint32_t glyph_width;
        const uint8_t *glyph_pixels;
        if (bitmap_font_get_glyph(&g_bitmap_font, code, &glyph_width, &glyph_pixels)) {
            uint32_t row;
            uint32_t col;
            for (row = 0; row < g_bitmap_font.height; ++row) {
                for (col = 0; col < glyph_width; ++col) {
                    if (glyph_pixels[(size_t)row * glyph_width + col] == 1u) {
                        int px = x + (int)col;
                        int py = y + (int)row;
                        if (px >= 0 && px < LOGICAL_WIDTH && py >= 0 && py < LOGICAL_HEIGHT) {
                            (void)SetPixelV(dc, px, py, color);
                        }
                    }
                }
            }
            x += (int)glyph_width;
        }
        ++cursor;
    }
}

/* Caller has flushed GDI writes to the paint DIB already. */
static void draw_bitmap_label_pixels(const char *text, int x, int y,
                                     COLORREF color)
{
    uint32_t dib_pixel;
    if (text == NULL || g_paint_buffer_pixels == NULL) return;
    dib_pixel = ((uint32_t)GetRValue(color) << 16) |
                ((uint32_t)GetGValue(color) << 8) |
                (uint32_t)GetBValue(color);
    (void)bitmap_font_render_pixels(&g_bitmap_font, text,
        (uint32_t *)g_paint_buffer_pixels, LOGICAL_WIDTH, LOGICAL_HEIGHT,
        LOGICAL_WIDTH, x, y, dib_pixel);
}

static void draw_wrapped_bitmap_label(HDC dc, const char *text, int x, int y,
                                      int max_width, int max_lines, COLORREF color)
{
    const char *cursor = text;
    int line_height = (int)g_bitmap_font.height + 2;
    int line = 0;
    if (max_width <= 0 || max_lines <= 0) return;
    while (*cursor != '\0' && line < max_lines) {
        const char *line_start;
        const char *scan;
        const char *last_space = NULL;
        char buffer[256];
        size_t length;
        while (*cursor == ' ' || *cursor == '\t') ++cursor;
        line_start = cursor;
        scan = cursor;
        while (*scan != '\0' && *scan != '\r' && *scan != '\n') {
            const char *word_end = scan;
            while (*word_end != '\0' && *word_end != ' ' && *word_end != '\t' &&
                   *word_end != '\r' && *word_end != '\n') ++word_end;
            if (word_end == scan) {
                ++scan;
                continue;
            }
            if (measure_bitmap_text(NULL, line_start, (size_t)(word_end - line_start)) >
                max_width) {
                if (last_space != NULL && last_space > line_start) scan = last_space;
                else scan = word_end;
                break;
            }
            scan = word_end;
            if (*scan == ' ' || *scan == '\t') {
                last_space = scan;
                while (*scan == ' ' || *scan == '\t') ++scan;
            }
        }
        if (scan == line_start) break;
        length = (size_t)(scan - line_start);
        while (length > 0 && (line_start[length - 1] == ' ' ||
                              line_start[length - 1] == '\t')) --length;
        if (length >= sizeof(buffer)) length = sizeof(buffer) - 1;
        memcpy(buffer, line_start, length);
        buffer[length] = '\0';
        draw_bitmap_label(dc, buffer, x, y + line * line_height, color);
        ++line;
        cursor = scan;
        while (*cursor == ' ' || *cursor == '\t') ++cursor;
        if (*cursor == '\r' || *cursor == '\n') {
            if (*cursor == '\r') ++cursor;
            if (*cursor == '\n') ++cursor;
        }
    }
}
