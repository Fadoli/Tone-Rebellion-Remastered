/* Remake-only buttons (Intro, multiplayer and the multiplayer setup screen)
   drawn like the TITSCRN title buttons. Nothing new is shipped: both the
   texture and the letters are taken from the original frames at run time.
   - TITSCRN frames 2..9 are RESUME, NEWGAME, LOADGAME and EXITAPP, each a
     102x49 button and its hover frame (+1) on the same background art; only
     the baked caption differs. A blank texture keeps, per pixel, a frame
     whose caption does not cover it; pixels covered in all four (where
     PARTIE and Tone overlap) are filled from their neighbours.
   - Captions are cut from those same frames (REPRENDRE, NOUVELLE, PARTIE,
     CHARGER, QUITTER): the letters A C D E G H I L N O P Q R T U V. A label
     may only use them (and spaces); others are not drawn.
   Interpretation: the frame columns below come from the frame data (bright
   pixel runs of each caption), not from Ghidra; FLOAT.EXE has no such
   buttons. */

enum { REMAKE_BUTTON_WIDTH = 102, REMAKE_BUTTON_HEIGHT = 49,
       REMAKE_BUTTON_FIRST_FRAME = 2, REMAKE_BUTTON_FRAMES = 8 };
/* 3R + 6G + B over 8-bit channels (0..2550). Caption pixels are brighter
   than the art behind them; a few light streaks are as bright but are the
   same pixels in every frame. */
enum { REMAKE_BUTTON_TEXT_LUMA = 1150, REMAKE_BUTTON_GLYPH_LUMA = 1500,
       REMAKE_BUTTON_SPACE = 8 };

typedef struct RemakeGlyph {
    char letter;
    uint8_t frame;  /* normal TITSCRN frame; the hover frame is frame + 1 */
    uint8_t left;   /* first and last column of the letter */
    uint8_t right;
    uint8_t top;    /* first row of the caption line */
} RemakeGlyph;

static const RemakeGlyph g_remake_glyphs[] = {
    {'R', 2, 4, 12, 10}, {'E', 2, 15, 22, 10}, {'P', 2, 26, 33, 10},
    {'N', 2, 57, 65, 10}, {'D', 2, 69, 77, 10},
    {'O', 4, 17, 28, 10}, {'U', 4, 31, 40, 10}, {'V', 4, 43, 53, 10},
    {'L', 4, 68, 75, 10}, {'T', 4, 56, 63, 30}, {'I', 4, 67, 68, 30},
    {'C', 6, 7, 17, 10}, {'H', 6, 20, 29, 10}, {'A', 6, 32, 42, 10},
    {'G', 6, 58, 69, 10},
    {'Q', 8, 12, 23, 6}
};
enum { REMAKE_GLYPH_COUNT = sizeof(g_remake_glyphs) / sizeof(g_remake_glyphs[0]) };

/* [0] normal, [1] hovered; NULL until built (or when TITSCRN differs). */
static uint32_t *g_remake_button_texture[2];
static int g_remake_buttons_tried;

static int remake_button_luma(uint32_t pixel)
{
    return 3 * (int)((pixel >> 16) & 0xFFU) + 6 * (int)((pixel >> 8) & 0xFFU) +
           (int)(pixel & 0xFFU);
}

static const SpriteFrame *remake_button_source(int frame)
{
    const SpriteFrame *source;
    if ((uint32_t)frame >= g_title_art.frame_count) return NULL;
    source = &g_title_art.frames[frame];
    if (source->pixels == NULL || source->width != REMAKE_BUTTON_WIDTH ||
        source->height != REMAKE_BUTTON_HEIGHT) return NULL;
    return source;
}

static void free_remake_buttons(void)
{
    free(g_remake_button_texture[0]);
    free(g_remake_button_texture[1]);
    g_remake_button_texture[0] = NULL;
    g_remake_button_texture[1] = NULL;
    g_remake_buttons_tried = 0;
}

static void build_remake_buttons(void)
{
    enum { N = REMAKE_BUTTON_WIDTH * REMAKE_BUTTON_HEIGHT };
    const SpriteFrame *frames[REMAKE_BUTTON_FRAMES];
    static uint8_t covered[4][N];
    static uint8_t hole[N];
    int set;
    int i;
    int p;
    g_remake_buttons_tried = 1;
    for (i = 0; i < REMAKE_BUTTON_FRAMES; ++i) {
        frames[i] = remake_button_source(REMAKE_BUTTON_FIRST_FRAME + i);
        if (frames[i] == NULL) return;
    }
    /* Caption masks from the normal frames (the hover frames place their
       captions identically), grown by one pixel for the glow. */
    memset(covered, 0, sizeof(covered));
    for (p = 0; p < N; ++p) {
        const int x = p % REMAKE_BUTTON_WIDTH;
        const int y = p / REMAKE_BUTTON_WIDTH;
        int bright = 0;
        if (x < 4 || x >= REMAKE_BUTTON_WIDTH - 4 || y < 4 || y >= REMAKE_BUTTON_HEIGHT - 4)
            continue;
        for (i = 0; i < 4; ++i)
            bright += remake_button_luma(frames[i * 2]->pixels[p]) >= REMAKE_BUTTON_TEXT_LUMA &&
                      frames[i * 2]->pixels[p] == frames[0]->pixels[p];
        /* The same bright pixel in every frame is art (a streak), not a
           caption; captions that overlap differ. */
        if (bright == 4) continue;
        for (i = 0; i < 4; ++i) {
            int dx;
            int dy;
            if (remake_button_luma(frames[i * 2]->pixels[p]) < REMAKE_BUTTON_TEXT_LUMA) continue;
            for (dy = -1; dy <= 1; ++dy)
                for (dx = -1; dx <= 1; ++dx) {
                    const int nx = x + dx;
                    const int ny = y + dy;
                    if (nx >= 3 && nx < REMAKE_BUTTON_WIDTH - 3 &&
                        ny >= 3 && ny < REMAKE_BUTTON_HEIGHT - 3)
                        covered[i][ny * REMAKE_BUTTON_WIDTH + nx] = 1;
                }
        }
    }
    for (set = 0; set < 2; ++set) {
        uint32_t *texture = (uint32_t *)malloc(N * sizeof(uint32_t));
        int holes = 0;
        if (texture == NULL) {
            free_remake_buttons();
            g_remake_buttons_tried = 1;
            return;
        }
        for (p = 0; p < N; ++p) {
            hole[p] = 1;
            for (i = 0; i < 4; ++i) {
                if (covered[i][p]) continue;
                texture[p] = frames[i * 2 + set]->pixels[p];
                hole[p] = 0;
                break;
            }
            holes += hole[p];
        }
        /* Fill the remaining caption pixels from the filled neighbours,
           growing inwards. */
        while (holes > 0) {
            int filled = 0;
            for (p = 0; p < N; ++p) {
                static const int step[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
                const int x = p % REMAKE_BUTTON_WIDTH;
                const int y = p / REMAKE_BUTTON_WIDTH;
                unsigned r = 0;
                unsigned g = 0;
                unsigned b = 0;
                unsigned count = 0;
                int k;
                if (hole[p] != 1) continue;
                for (k = 0; k < 4; ++k) {
                    const int nx = x + step[k][0];
                    const int ny = y + step[k][1];
                    uint32_t pixel;
                    if (nx < 0 || ny < 0 || nx >= REMAKE_BUTTON_WIDTH ||
                        ny >= REMAKE_BUTTON_HEIGHT || hole[ny * REMAKE_BUTTON_WIDTH + nx] == 1)
                        continue;
                    pixel = texture[ny * REMAKE_BUTTON_WIDTH + nx];
                    r += (pixel >> 16) & 0xFFU;
                    g += (pixel >> 8) & 0xFFU;
                    b += pixel & 0xFFU;
                    ++count;
                }
                if (count == 0) continue;
                texture[p] = 0xFF000000U | ((r / count) << 16) | ((g / count) << 8) | (b / count);
                hole[p] = 2; /* filled this pass: not a source until the next */
                ++filled;
            }
            for (p = 0; p < N; ++p)
                if (hole[p] == 2) hole[p] = 0;
            holes -= filled;
            if (filled == 0) break;
        }
        g_remake_button_texture[set] = texture;
    }
}

static const RemakeGlyph *remake_glyph(char letter)
{
    int i;
    for (i = 0; i < REMAKE_GLYPH_COUNT; ++i)
        if (g_remake_glyphs[i].letter == letter) return &g_remake_glyphs[i];
    return NULL;
}

/* Spacing as in the baked captions: two columns between letters, three
   beside the narrow I, eight for a space. */
static int remake_label_width(const char *label)
{
    int width = 0;
    char previous = 0;
    for (; *label != '\0'; ++label) {
        const RemakeGlyph *glyph = remake_glyph(*label);
        if (*label == ' ') {
            width += REMAKE_BUTTON_SPACE;
            previous = 0;
            continue;
        }
        if (glyph == NULL) continue;
        if (previous != 0) width += (previous == 'I' || *label == 'I') ? 3 : 2;
        width += glyph->right - glyph->left + 1;
        previous = *label;
    }
    return width;
}

/* Copies the caption pixels of `label` into the 102x49 `button`, its glyph
   tops on row `top`. */
static void remake_button_label(uint32_t *button, const char *label, int top, int hovered)
{
    int x = (REMAKE_BUTTON_WIDTH - remake_label_width(label)) / 2;
    char previous = 0;
    for (; *label != '\0'; ++label) {
        const RemakeGlyph *glyph = remake_glyph(*label);
        const SpriteFrame *mask_frame;
        const SpriteFrame *ink_frame;
        int column;
        int row;
        if (*label == ' ') {
            x += REMAKE_BUTTON_SPACE;
            previous = 0;
            continue;
        }
        if (glyph == NULL) continue;
        mask_frame = remake_button_source(glyph->frame);
        ink_frame = remake_button_source(glyph->frame + (hovered ? 1 : 0));
        if (mask_frame == NULL || ink_frame == NULL) continue;
        if (previous != 0) x += (previous == 'I' || *label == 'I') ? 3 : 2;
        for (row = -1; row <= 10; ++row) {
            const int source_y = glyph->top + row;
            const int target_y = top + row;
            if (source_y < 0 || source_y >= REMAKE_BUTTON_HEIGHT ||
                target_y < 0 || target_y >= REMAKE_BUTTON_HEIGHT) continue;
            for (column = glyph->left; column <= glyph->right; ++column) {
                const int source = source_y * REMAKE_BUTTON_WIDTH + column;
                const int target_x = x + column - glyph->left;
                if (target_x < 0 || target_x >= REMAKE_BUTTON_WIDTH) continue;
                if (remake_button_luma(mask_frame->pixels[source]) < REMAKE_BUTTON_GLYPH_LUMA)
                    continue;
                button[target_y * REMAKE_BUTTON_WIDTH + target_x] = ink_frame->pixels[source];
            }
        }
        x += glyph->right - glyph->left + 1;
        previous = *label;
    }
}

/* Draws a button whose top-left corner is (x, y); `second` may be NULL for
   a one-line caption. Returns 0 when the TITSCRN art is not usable. */
static int draw_remake_button(RenderSurface *surface, int x, int y,
                              const char *first, const char *second, int hovered)
{
    uint32_t button[REMAKE_BUTTON_WIDTH * REMAKE_BUTTON_HEIGHT];
    const uint32_t *texture;
    if (!g_remake_buttons_tried) build_remake_buttons();
    texture = g_remake_button_texture[hovered ? 1 : 0];
    if (texture == NULL) return 0;
    memcpy(button, texture, sizeof(button));
    /* The baked captions sit on rows 10 and 30. */
    if (second != NULL) {
        remake_button_label(button, first, 10, hovered);
        remake_button_label(button, second, 30, hovered);
    } else {
        remake_button_label(button, first, 19, hovered);
    }
    render_surface_blit(surface, button, REMAKE_BUTTON_WIDTH, REMAKE_BUTTON_HEIGHT,
                        REMAKE_BUTTON_WIDTH, 0, 0, REMAKE_BUTTON_WIDTH, REMAKE_BUTTON_HEIGHT,
                        x, y, 0x10000U, NULL, NULL);
    return 1;
}

/* The opaque part of a button drawn at (left, top). */
static int remake_button_contains(int left, int top, int x, int y)
{
    return x >= left + 2 && x < left + REMAKE_BUTTON_WIDTH - 2 &&
           y >= top + 2 && y < top + REMAKE_BUTTON_HEIGHT - 2;
}
