/* Sound effect mixer. The original plays each effect in its own DirectSound
   buffer (FUN_0045afb9: Stop, SetCurrentPosition(0), SetPan, SetVolume,
   Play), so several effects sound at once; a buffer already playing is not
   restarted unless it is a death sound (ev_aabff0f0). PlaySound has one
   voice and no volume or pan, so the remake mixes the effects itself into a
   waveOut stream (remake_sdl: an SDL audio stream, sdl_audio.inc). */

enum {
    SFX_RATE = 22050,
    SFX_VOICES = 16,
    SFX_BUFFERS = 4,
    SFX_BUFFER_FRAMES = 1024,
    SFX_CACHE = 160
};

typedef struct SfxSample {
    int16_t *pcm;      /* mono, SFX_RATE */
    uint32_t frames;
} SfxSample;

typedef struct SfxVoice {
    const SfxSample *sample;
    uint32_t position;
    double gain_left;
    double gain_right;
} SfxVoice;

static SDL_AudioStream *g_sfx_stream;
static int g_sfx_open;
static int g_sfx_failed;
static SfxVoice g_sfx_voices[SFX_VOICES];
static const unsigned char *g_sfx_cache_keys[SFX_CACHE];
static SfxSample g_sfx_cache[SFX_CACHE];

static uint32_t sfx_u32(const unsigned char *p)
{
    return (uint32_t)p[0] | ((uint32_t)p[1] << 8) |
           ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24);
}

/* Decode a RIFF PCM WAV (8/16-bit, mono/stereo, any rate) to mono 16-bit at
   SFX_RATE (nearest sample). */
static int sfx_decode_wav(const unsigned char *wav, SfxSample *out)
{
    uint32_t total;
    uint32_t offset;
    unsigned int channels = 0;
    unsigned int bits = 0;
    uint32_t rate = 0;
    const unsigned char *data = NULL;
    uint32_t data_size = 0;
    uint32_t source_frames;
    uint32_t frame;
    unsigned int bytes_per_frame;

    memset(out, 0, sizeof(*out));
    if (wav == NULL || memcmp(wav, "RIFF", 4) != 0 ||
        memcmp(wav + 8, "WAVE", 4) != 0) return 0;
    total = 8U + sfx_u32(wav + 4);
    if (total < 44U || total > 64U * 1024U * 1024U) return 0;
    for (offset = 12; offset + 8U <= total;) {
        uint32_t chunk = sfx_u32(wav + offset + 4);
        if (memcmp(wav + offset, "fmt ", 4) == 0 && chunk >= 16U &&
            offset + 24U <= total) {
            if ((wav[offset + 8] | (wav[offset + 9] << 8)) != 1) return 0;
            channels = (unsigned)(wav[offset + 10] | (wav[offset + 11] << 8));
            rate = sfx_u32(wav + offset + 12);
            bits = (unsigned)(wav[offset + 22] | (wav[offset + 23] << 8));
        } else if (memcmp(wav + offset, "data", 4) == 0) {
            data = wav + offset + 8;
            data_size = chunk;
            if (offset + 8U + data_size > total) data_size = total - offset - 8U;
            break;
        }
        offset += 8U + chunk + (chunk & 1U);
    }
    if (data == NULL || channels == 0 || channels > 2 || rate == 0 ||
        (bits != 8 && bits != 16)) return 0;
    bytes_per_frame = channels * (bits / 8U);
    source_frames = data_size / bytes_per_frame;
    if (source_frames == 0) return 0;
    out->frames = (uint32_t)((uint64_t)source_frames * SFX_RATE / rate);
    if (out->frames == 0) return 0;
    out->pcm = (int16_t *)malloc(out->frames * sizeof(int16_t));
    if (out->pcm == NULL) return 0;
    for (frame = 0; frame < out->frames; ++frame) {
        uint32_t source = (uint32_t)((uint64_t)frame * rate / SFX_RATE);
        const unsigned char *p = data + source * bytes_per_frame;
        int value = 0;
        unsigned int channel;
        for (channel = 0; channel < channels; ++channel) {
            value += bits == 16U
                ? (int)(int16_t)(p[channel * 2] | (p[channel * 2 + 1] << 8))
                : ((int)p[channel] - 128) * 256;
        }
        out->pcm[frame] = (int16_t)(value / (int)channels);
    }
    return 1;
}

/* Decoded copy of an in-memory WAV, made once per WAV. */
static const SfxSample *sfx_sample_for(const unsigned char *wav)
{
    unsigned int i;
    if (wav == NULL) return NULL;
    for (i = 0; i < SFX_CACHE; ++i) {
        if (g_sfx_cache_keys[i] == wav)
            return g_sfx_cache[i].pcm != NULL ? &g_sfx_cache[i] : NULL;
        if (g_sfx_cache_keys[i] == NULL) {
            g_sfx_cache_keys[i] = wav;
            (void)sfx_decode_wav(wav, &g_sfx_cache[i]);
            return g_sfx_cache[i].pcm != NULL ? &g_sfx_cache[i] : NULL;
        }
    }
    return NULL;
}

static void sfx_fill(int16_t *buffer)
{
    unsigned int frame;
    for (frame = 0; frame < SFX_BUFFER_FRAMES; ++frame) {
        double left = 0.0;
        double right = 0.0;
        unsigned int v;
        for (v = 0; v < SFX_VOICES; ++v) {
            SfxVoice *voice = &g_sfx_voices[v];
            double sample;
            if (voice->sample == NULL) continue;
            sample = voice->sample->pcm[voice->position];
            left += sample * voice->gain_left;
            right += sample * voice->gain_right;
            if (++voice->position >= voice->sample->frames)
                voice->sample = NULL;
        }
        if (left > 32767.0) left = 32767.0;
        if (left < -32768.0) left = -32768.0;
        if (right > 32767.0) right = 32767.0;
        if (right < -32768.0) right = -32768.0;
        buffer[frame * 2] = (int16_t)left;
        buffer[frame * 2 + 1] = (int16_t)right;
    }
}

/* Runs on SDL's audio thread with the stream locked, so the voices the main
   thread changes under SDL_LockAudioStream stay consistent. */
static void SDLCALL sfx_stream_callback(void *userdata, SDL_AudioStream *stream,
                                        int additional_amount, int total_amount)
{
    int16_t buffer[SFX_BUFFER_FRAMES * 2];
    (void)userdata;
    (void)total_amount;
    while (additional_amount > 0) {
        sfx_fill(buffer);
        (void)SDL_PutAudioStreamData(stream, buffer, (int)sizeof(buffer));
        additional_amount -= (int)sizeof(buffer);
    }
}

static int sfx_open(void)
{
    SDL_AudioSpec spec;
    if (g_sfx_open) return 1;
    if (g_sfx_failed) return 0;
    spec.format = SDL_AUDIO_S16;
    spec.channels = 2;
    spec.freq = SFX_RATE;
    g_sfx_stream = sdl_audio_stream(&spec, sfx_stream_callback, NULL);
    if (g_sfx_stream == NULL) {
        g_sfx_failed = 1;
        return 0;
    }
    g_sfx_open = 1;
    return 1;
}

/* The stream callback pulls the mix. */
static void sfx_pump(void)
{
}

static void sfx_close(void)
{
    unsigned int i;
    if (!g_sfx_open) return;
    SDL_DestroyAudioStream(g_sfx_stream);
    g_sfx_stream = NULL;
    memset(g_sfx_voices, 0, sizeof(g_sfx_voices));
    g_sfx_open = 0;
    for (i = 0; i < SFX_CACHE; ++i) {
        free(g_sfx_cache[i].pcm);
        g_sfx_cache[i].pcm = NULL;
        g_sfx_cache_keys[i] = NULL;
    }
}

/* FUN_0045afb9(sound, volume %, pan): volume and pan are DirectSound
   hundredths of a dB after FUN_004595cc; the effects slider scales every
   voice. `restart` mirrors the death-sound exception. */
static void sfx_play(const unsigned char *wav, int volume, int pan, int restart)
{
    const SfxSample *sample;
    double gain;
    double left;
    double right;
    unsigned int v;
    unsigned int free_voice = SFX_VOICES;

    if (!g_sound_enabled || g_sound_volume <= 0 || volume <= 0) return;
    sample = sfx_sample_for(wav);
    if (sample == NULL || !sfx_open()) return;
    gain = volume_gain(volume) * volume_gain(g_sound_volume);
    left = gain;
    right = gain;
    if (pan > 0) left *= pow(10.0, -pan / 2000.0);
    else if (pan < 0) right *= pow(10.0, pan / 2000.0);
    if (!SDL_LockAudioStream(g_sfx_stream)) return;
    for (v = 0; v < SFX_VOICES; ++v) {
        if (g_sfx_voices[v].sample == sample) {
            if (restart) free_voice = v;
            else free_voice = SFX_VOICES + 1U; /* already playing */
            break;
        }
        if (g_sfx_voices[v].sample == NULL && free_voice == SFX_VOICES)
            free_voice = v;
    }
    if (free_voice < SFX_VOICES) {
        g_sfx_voices[free_voice].sample = sample;
        g_sfx_voices[free_voice].position = 0;
        g_sfx_voices[free_voice].gain_left = left;
        g_sfx_voices[free_voice].gain_right = right;
    }
    (void)SDL_UnlockAudioStream(g_sfx_stream);
    if (free_voice < SFX_VOICES) sfx_pump();
}

/* FUN_0045b24d with d = view centre (scroll + 0x140) - effect x: volume
   100 * (2000 - min(|d|, 2000)) / 2000, pan magnitude from the same
   attenuation of 100 * (500 - min(|d|, 500)) / 500, to the right when the
   effect is right of the centre (ev_effbb692). x < 0 plays centred. */
static void sfx_play_at(const unsigned char *wav, int x, int restart)
{
    int volume = 100;
    int pan = 0;
    if (x >= 0) {
        int d = (g_island_scroll_x + 0x140) - x;
        int distance = d < 0 ? -d : d;
        int pan_distance = distance > 500 ? 500 : distance;
        if (distance > 2000) distance = 2000;
        volume = 100 * (2000 - distance) / 2000;
        pan = -volume_attenuation(100 * (500 - pan_distance) / 500);
        if (d > 0) pan = -pan; /* effect left of the centre */
    }
    sfx_play(wav, volume, pan, restart);
}
