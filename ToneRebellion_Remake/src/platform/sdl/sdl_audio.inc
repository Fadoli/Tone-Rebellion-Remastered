/* SDL3 audio for remake_sdl (TODO_WEB.md step 3): one playback device with
   two streams, each filled from SDL's audio thread by a get-callback so a
   modal Win32 loop (window drag, message box) does not starve them.
   - Effects: the sfx_mixer.inc voices, mixed to 16-bit stereo at SFX_RATE.
     The main thread changes voices under SDL_LockAudioStream.
   - Music: the THING2 PCM WAV streamed from disk in its own format (the
     tunes are 8-bit stereo 22,050 Hz); SDL converts. The stream gain plays
     the part of MCI `setaudio volume`. */

static SDL_AudioDeviceID g_sdl_audio_device;
static int g_sdl_audio_failed;

typedef struct SdlMusic {
    SDL_AudioStream *stream;
    FILE *file;
    long data_start;
    uint32_t data_size;
    uint32_t data_read;
    int loop;
    SDL_AtomicInt finished; /* set once a non-looping tune has been read */
} SdlMusic;

static SdlMusic g_sdl_music;

static int sdl_audio_device(void)
{
    if (g_sdl_audio_device != 0) return 1;
    if (g_sdl_audio_failed) return 0;
    if (!SDL_InitSubSystem(SDL_INIT_AUDIO)) {
        g_sdl_audio_failed = 1;
        return 0;
    }
    g_sdl_audio_device = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
    if (g_sdl_audio_device == 0) {
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
        g_sdl_audio_failed = 1;
        return 0;
    }
    return 1;
}

/* A stream from `spec` bound to the device, fed by `callback`. */
static SDL_AudioStream *sdl_audio_stream(const SDL_AudioSpec *spec,
                                         SDL_AudioStreamCallback callback,
                                         void *userdata)
{
    SDL_AudioStream *stream;
    if (!sdl_audio_device()) return NULL;
    stream = SDL_CreateAudioStream(spec, NULL);
    if (stream == NULL) return NULL;
    if (!SDL_SetAudioStreamGetCallback(stream, callback, userdata) ||
        !SDL_BindAudioStream(g_sdl_audio_device, stream)) {
        SDL_DestroyAudioStream(stream);
        return NULL;
    }
    return stream;
}

static void SDLCALL sdl_music_callback(void *userdata, SDL_AudioStream *stream,
                                       int additional_amount, int total_amount)
{
    SdlMusic *music = (SdlMusic *)userdata;
    unsigned char buffer[8192];
    (void)total_amount;
    while (additional_amount > 0) {
        uint32_t left = music->data_size - music->data_read;
        size_t want = (size_t)additional_amount < sizeof(buffer)
            ? (size_t)additional_amount : sizeof(buffer);
        size_t got;
        if (left == 0) {
            if (!music->loop ||
                fseek(music->file, music->data_start, SEEK_SET) != 0) {
                SDL_SetAtomicInt(&music->finished, 1);
                return;
            }
            music->data_read = 0;
            left = music->data_size;
        }
        if (want > left) want = left;
        want &= ~(size_t)1; /* whole 8-bit stereo frames */
        if (want == 0) want = left;
        got = fread(buffer, 1, want, music->file);
        if (got == 0) {
            /* A short file: treat the end of what was read as the end. */
            music->data_size = music->data_read;
            if (!music->loop) {
                SDL_SetAtomicInt(&music->finished, 1);
                return;
            }
            continue;
        }
        music->data_read += (uint32_t)got;
        (void)SDL_PutAudioStreamData(stream, buffer, (int)got);
        additional_amount -= (int)got;
    }
}

static void sdl_music_close(void)
{
    /* Destroying the stream waits for a running callback. */
    if (g_sdl_music.stream != NULL) SDL_DestroyAudioStream(g_sdl_music.stream);
    if (g_sdl_music.file != NULL) (void)fclose(g_sdl_music.file);
    g_sdl_music.stream = NULL;
    g_sdl_music.file = NULL;
}

static uint32_t sdl_wav_u32(const unsigned char *p)
{
    return (uint32_t)p[0] | ((uint32_t)p[1] << 8) |
           ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24);
}

/* Opens a PCM WAV and starts it. Returns 0 when the file or the device
   cannot be used (the caller treats it as an MCI open failure). */
static int sdl_music_open(const char *path, int loop, double gain)
{
    unsigned char header[8];
    SDL_AudioSpec spec;
    int have_format = 0;
    long offset = 12;
    sdl_music_close();
    g_sdl_music.file = fopen(path, "rb");
    if (g_sdl_music.file == NULL) return 0;
    if (fread(header, 1, 8, g_sdl_music.file) != 8 ||
        memcmp(header, "RIFF", 4) != 0 ||
        fread(header, 1, 4, g_sdl_music.file) != 4 ||
        memcmp(header, "WAVE", 4) != 0) {
        sdl_music_close();
        return 0;
    }
    memset(&spec, 0, sizeof(spec));
    for (;;) {
        uint32_t chunk;
        if (fseek(g_sdl_music.file, offset, SEEK_SET) != 0 ||
            fread(header, 1, 8, g_sdl_music.file) != 8) {
            sdl_music_close();
            return 0;
        }
        chunk = sdl_wav_u32(header + 4);
        if (memcmp(header, "fmt ", 4) == 0 && chunk >= 16U) {
            unsigned char format[16];
            unsigned int bits;
            if (fread(format, 1, 16, g_sdl_music.file) != 16 ||
                (format[0] | (format[1] << 8)) != 1) {
                sdl_music_close();
                return 0;
            }
            spec.channels = format[2] | (format[3] << 8);
            spec.freq = (int)sdl_wav_u32(format + 4);
            bits = (unsigned)(format[14] | (format[15] << 8));
            spec.format = bits == 8U ? SDL_AUDIO_U8 : SDL_AUDIO_S16LE;
            if ((bits != 8U && bits != 16U) || spec.channels < 1 ||
                spec.channels > 2 || spec.freq <= 0) {
                sdl_music_close();
                return 0;
            }
            have_format = 1;
        } else if (memcmp(header, "data", 4) == 0) {
            if (!have_format) {
                sdl_music_close();
                return 0;
            }
            g_sdl_music.data_start = offset + 8;
            g_sdl_music.data_size = chunk;
            break;
        }
        offset += 8L + (long)chunk + (long)(chunk & 1U);
    }
    if (fseek(g_sdl_music.file, g_sdl_music.data_start, SEEK_SET) != 0) {
        sdl_music_close();
        return 0;
    }
    g_sdl_music.data_read = 0;
    g_sdl_music.loop = loop;
    SDL_SetAtomicInt(&g_sdl_music.finished, 0);
    g_sdl_music.stream = sdl_audio_stream(&spec, sdl_music_callback, &g_sdl_music);
    if (g_sdl_music.stream == NULL) {
        sdl_music_close();
        return 0;
    }
    (void)SDL_SetAudioStreamGain(g_sdl_music.stream, (float)gain);
    return 1;
}

/* MCI `status mode` == "stopped": the tune was read to its end and the
   stream has played what was queued. */
static int sdl_music_stopped(void)
{
    return g_sdl_music.stream == NULL ||
           (SDL_GetAtomicInt(&g_sdl_music.finished) != 0 &&
            SDL_GetAudioStreamQueued(g_sdl_music.stream) <= 0);
}

static void sdl_music_set_gain(double gain)
{
    if (g_sdl_music.stream != NULL)
        (void)SDL_SetAudioStreamGain(g_sdl_music.stream, (float)gain);
}

/* Before SDL_Quit (sdl_destroy_window): the streams and the device. */
static void sdl_audio_close(void)
{
    sdl_music_close();
    if (g_sdl_audio_device != 0) {
        SDL_CloseAudioDevice(g_sdl_audio_device);
        g_sdl_audio_device = 0;
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
    }
}
