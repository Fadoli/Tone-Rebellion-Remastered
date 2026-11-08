/* Intro movie: THING2\INTRO.AVI (640x480 Cinepak at 15 frames/s with 8-bit
   stereo 22,050 Hz PCM, interleaved). Native: windows.txt state 6
   (INTROMOVIE) plays it through DirectShow (FUN_00449b80) and the end of
   playback queues SetState(0); the only way in is the title's I key when
   FLOAT.CFG holds `nevada` (decompilation/behavior/title-screen.md).
   Remake: an INTRO button on the title (lower left) and the I key, without
   `nevada`; a click or a key ends the movie early. The music in progress
   stops for the movie and starts again afterwards. Not in the browser
   build: the page does not copy the 90 MB movie, so the button and the key
   are left out there. */
#ifdef __EMSCRIPTEN__
enum { INTRO_AVAILABLE = 0 };
#else
enum { INTRO_AVAILABLE = 1 };
#endif

/* Lower left, mirroring PARTIE EN LIGNE: under NEWGAME (99 + 15), level
   with EXITAPP. */
static const RECT g_intro_title_button = {114, 416, 216, 465};
static int g_intro_title_hover;

typedef struct IntroMovie {
    FILE *video;          /* reads the picture chunks */
    FILE *audio;          /* reads the sound chunks, ahead of the picture */
    long movi_end;
    long video_at;
    long audio_at;
    int frame_count;
    int frames_shown;
    uint32_t us_per_frame;
    int audio_bytes_per_second;
    int64_t audio_pushed;
    uint32_t started_ms;
    uint8_t *chunk;
    size_t chunk_capacity;
    char resume_tune[32];
    CinepakDecoder decoder;
} IntroMovie;

static IntroMovie g_intro;

static uint32_t intro_u32(const unsigned char *p)
{
    return (uint32_t)p[0] | ((uint32_t)p[1] << 8) | ((uint32_t)p[2] << 16) |
           ((uint32_t)p[3] << 24);
}

static void intro_close(void)
{
    sdl_movie_audio_close();
    if (g_intro.video != NULL) (void)fclose(g_intro.video);
    if (g_intro.audio != NULL) (void)fclose(g_intro.audio);
    free(g_intro.chunk);
    cinepak_free(&g_intro.decoder);
    memset(&g_intro, 0, sizeof(g_intro));
}

/* Next chunk of `kind` ("dc" picture, "wb" sound) at or after *at in the
   movi list; LIST 'rec ' groups are entered. Returns its data size and
   leaves the file at its data, or -1 at the end. */
/* Whether a chunk of `size` data bytes (plus its pad byte) starting at `at`
   ends by `limit`. Sizes are unsigned 32-bit and long may be 32-bit: the
   comparison never converts `size` to long. */
static int intro_chunk_fits(long at, uint32_t size, long limit)
{
    uint64_t room;
    if (at < 0 || limit - at < 8) return 0;
    room = (uint64_t)(limit - at - 8);
    return (uint64_t)size <= room;
}

/* After a chunk that fits: the next chunk header (data plus its pad). */
static long intro_after_chunk(long at, uint32_t size)
{
    return at + 8 + (long)size + (long)(size & 1U);
}

static long intro_next_chunk(FILE *file, long *at, const char *kind)
{
    unsigned char header[12];
    while (*at + 8 <= g_intro.movi_end) {
        uint32_t size;
        if (fseek(file, *at, SEEK_SET) != 0 || fread(header, 1, 8, file) != 8) return -1;
        size = intro_u32(header + 4);
        if (memcmp(header, "LIST", 4) == 0) {
            *at += 12;
            continue;
        }
        if (!intro_chunk_fits(*at, size, g_intro.movi_end)) return -1;
        if (memcmp(header + 2, kind, 2) == 0 ||
            (kind[0] == 'd' && memcmp(header + 2, "db", 2) == 0)) {
            const long data = *at + 8;
            *at = intro_after_chunk(*at, size);
            return fseek(file, data, SEEK_SET) == 0 ? (long)size : -1;
        }
        *at = intro_after_chunk(*at, size);
    }
    return -1;
}

/* INTRO.AVI chunks stay under 100 KB (the stream headers announce 84,072
   and 3,206 bytes); a larger one is malformed. */
enum { INTRO_CHUNK_LIMIT = 16 * 1024 * 1024 };

static int intro_read_chunk(FILE *file, long size)
{
    if (size < 0 || size > INTRO_CHUNK_LIMIT) return 0;
    if ((size_t)size > g_intro.chunk_capacity) {
        uint8_t *grown = (uint8_t *)realloc(g_intro.chunk, (size_t)size);
        if (grown == NULL) return 0;
        g_intro.chunk = grown;
        g_intro.chunk_capacity = (size_t)size;
    }
    return size == 0 || fread(g_intro.chunk, 1, (size_t)size, file) == (size_t)size;
}

/* Reads the hdrl list (avih, the video and audio stream formats) and finds
   the movi list. */
static int intro_parse_header(int *width, int *height, int *channels, int *frequency, int *bits)
{
    unsigned char header[12];
    long at = 12;
    long end;
    int in_video = -1;
    if (fseek(g_intro.video, 0, SEEK_END) != 0) return 0;
    end = ftell(g_intro.video);
    if (fseek(g_intro.video, 0, SEEK_SET) != 0 || fread(header, 1, 12, g_intro.video) != 12 ||
        memcmp(header, "RIFF", 4) != 0 || memcmp(header + 8, "AVI ", 4) != 0) return 0;
    *width = *height = *channels = *frequency = *bits = 0;
    while (at + 8 <= end) {
        uint32_t size;
        if (fseek(g_intro.video, at, SEEK_SET) != 0 ||
            fread(header, 1, 12, g_intro.video) < 8) return 0;
        size = intro_u32(header + 4);
        if (memcmp(header, "LIST", 4) == 0) {
            if (memcmp(header + 8, "movi", 4) == 0) {
                g_intro.video_at = g_intro.audio_at = at + 12;
                g_intro.movi_end = intro_chunk_fits(at, size, end) ? at + 8 + (long)size : end;
                return *width > 0 && *height > 0 && g_intro.us_per_frame > 0;
            }
            at += 12; /* hdrl, strl: enter */
            continue;
        }
        if (!intro_chunk_fits(at, size, end)) return 0;
        if (size <= 64) {
            unsigned char body[64];
            if (fseek(g_intro.video, at + 8, SEEK_SET) != 0 ||
                fread(body, 1, size, g_intro.video) != size) return 0;
            if (memcmp(header, "avih", 4) == 0 && size >= 40) {
                g_intro.us_per_frame = intro_u32(body);
                g_intro.frame_count = (int)intro_u32(body + 16);
            } else if (memcmp(header, "strh", 4) == 0 && size >= 8) {
                in_video = memcmp(body, "vids", 4) == 0 ? 1
                         : memcmp(body, "auds", 4) == 0 ? 0 : -1;
                if (in_video == 1 && memcmp(body + 4, "cvid", 4) != 0 &&
                    memcmp(body + 4, "CVID", 4) != 0) return 0;
            } else if (memcmp(header, "strf", 4) == 0) {
                if (in_video == 1 && size >= 12) {
                    *width = (int)intro_u32(body + 4);
                    *height = (int)intro_u32(body + 8);
                } else if (in_video == 0 && size >= 16 && (body[0] | (body[1] << 8)) == 1) {
                    *channels = body[2] | (body[3] << 8);
                    *frequency = (int)intro_u32(body + 4);
                    *bits = body[14] | (body[15] << 8);
                }
            }
        }
        at = intro_after_chunk(at, size);
    }
    return 0;
}

/* Queues sound up to half a second past `elapsed_ms`. */
static void intro_feed_audio(uint64_t elapsed_ms)
{
    int64_t wanted;
    if (g_intro.audio == NULL || g_intro.audio_bytes_per_second <= 0) return;
    wanted = (int64_t)(elapsed_ms + 500U) * g_intro.audio_bytes_per_second / 1000;
    while (g_intro.audio_pushed < wanted) {
        long size = intro_next_chunk(g_intro.audio, &g_intro.audio_at, "wb");
        if (size < 0 || !intro_read_chunk(g_intro.audio, size)) {
            (void)fclose(g_intro.audio);
            g_intro.audio = NULL;
            return;
        }
        sdl_movie_audio_put(g_intro.chunk, (int)size);
        g_intro.audio_pushed += size;
    }
}

static void intro_stop(void)
{
    char tune[sizeof(g_intro.resume_tune)];
    (void)memcpy(tune, g_intro.resume_tune, sizeof(tune));
    intro_close();
    g_menu.screen = SCREEN_MAIN_MENU;
    /* The once-only `start` tune hands over to the ambi1 bed. */
    if (tune[0] == '\0' || strcmp(tune, "start") == 0) set_background_tune("ambi1");
    else set_background_tune(tune);
}

/* Opens INTRO.AVI (beside the tunes, THING2) and switches to the movie.
   Returns 0, staying on the title, when the file is missing or unusable. */
static int intro_start(void)
{
    char path[MAX_PATH];
    int width;
    int height;
    int channels;
    int frequency;
    int bits;
    intro_close();
    if (!INTRO_AVAILABLE || !resolve_music_directory("INTRO.AVI", path, sizeof(path))) return 0;
    g_intro.video = fopen(path, "rb");
    if (g_intro.video == NULL ||
        !intro_parse_header(&width, &height, &channels, &frequency, &bits) ||
        !cinepak_init(&g_intro.decoder, width, height)) {
        intro_close();
        return 0;
    }
    (void)snprintf(g_intro.resume_tune, sizeof(g_intro.resume_tune), "%s", g_current_tune);
    stop_background_tune();
    /* Rates beyond any real PCM track are malformed (and would overflow the
       byte rate below). */
    if (channels > 0 && frequency > 0 && frequency <= 192000 &&
        sdl_movie_audio_open(channels, frequency, bits,
                             g_music_enabled ? volume_gain(g_music_volume) : 0.0)) {
        g_intro.audio = fopen(path, "rb");
        g_intro.audio_bytes_per_second = channels * frequency * (bits / 8);
    }
    g_intro.started_ms = platform_ticks_ms();
    g_menu.screen = SCREEN_INTRO;
    intro_feed_audio(0);
    return 1;
}

/* Run once per UI frame: decodes every picture due by now (inter frames
   need all of them) and tops up the sound. Ends after the last picture
   once its sound has played. */
static void intro_tick(void)
{
    const uint64_t elapsed = (uint32_t)(platform_ticks_ms() - g_intro.started_ms);
    /* Capped so a tiny frame duration cannot overflow the count. */
    const uint64_t due_frames = elapsed * 1000U / g_intro.us_per_frame + 1U;
    const int limit = g_intro.frame_count > 0 ? g_intro.frame_count : INT_MAX;
    const int due = due_frames < (uint64_t)limit ? (int)due_frames : limit;
    int ended = 0;
    intro_feed_audio(elapsed);
    while (g_intro.frames_shown < due && !ended) {
        long size = intro_next_chunk(g_intro.video, &g_intro.video_at, "dc");
        if (size < 0 || !intro_read_chunk(g_intro.video, size)) {
            ended = 1;
            break;
        }
        (void)cinepak_decode(&g_intro.decoder, g_intro.chunk, (size_t)size);
        ++g_intro.frames_shown;
    }
    if (g_intro.frame_count > 0 && g_intro.frames_shown >= g_intro.frame_count) ended = 1;
    if (ended && (g_intro.audio == NULL || sdl_movie_audio_queued() <= 0 ||
                  elapsed > (uint64_t)g_intro.frame_count * g_intro.us_per_frame / 1000U + 1000U))
        intro_stop();
}

static void render_intro(RenderSurface *surface)
{
    const CinepakDecoder *decoder = &g_intro.decoder;
    fill_rect(surface, 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT, RGB(0, 0, 0));
    if (decoder->pixels == NULL) return;
    render_surface_blit(surface, decoder->pixels, decoder->width, decoder->height,
                        decoder->width, 0, 0, decoder->width, decoder->height,
                        (LOGICAL_WIDTH - decoder->width) / 2,
                        (LOGICAL_HEIGHT - decoder->height) / 2, 0x10000U, NULL, NULL);
}

static void render_intro_title_button(RenderSurface *surface)
{
    if (!INTRO_AVAILABLE) return;
    net_setup_draw_button(surface, &g_intro_title_button, T_BTN_INTRO, REMAKE_TEXT_COUNT,
                          g_intro_title_hover);
}

/* Returns 1 when the hover changed. */
static int update_intro_hover(int x, int y)
{
    const int hover = INTRO_AVAILABLE && g_menu.screen == SCREEN_MAIN_MENU &&
                      net_setup_point_in(&g_intro_title_button, x, y);
    const int changed = hover != g_intro_title_hover;
    g_intro_title_hover = hover;
    return changed;
}

/* Title screen: 1 if the click was on the Intro button. */
static int intro_title_click(int x, int y)
{
    if (!INTRO_AVAILABLE || !net_setup_point_in(&g_intro_title_button, x, y)) return 0;
    g_intro_title_hover = 0;
    (void)intro_start();
    return 1;
}
