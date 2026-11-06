/* CPU image upscaler: see upscale.h for the pass/threading contract.
 *
 * Passes per filter (the last one writes dst):
 *   Nearest            1: direct mapping
 *   (Sharp) bilinear   2: horizontal into tmp, vertical into dst
 *   Bicubic, Lanczos3  2: same, with normalised kernel taps
 *   xBR, HQx           2: k-x prescale into pre, (sharp) bilinear to dst
 *   ScaleFX            5: shader passes 0, 1, 2, 3+4 (3x into pre), resample
 *
 * Pixel-art filter fidelity:
 *
 * HQx (hq2x/hq3x/hq4x) - exact port, upscale_hqx.c, LGPL-2.1-or-later.
 *   Adapted from grom358/hqx (Maxim Stepin's algorithm; Cameron Zemek,
 *   Francois Gannaz): same YUV formula, thresholds, interpolators, PIXEL
 *   macros and 256-case pattern switches (checked token for token against the
 *   reference when the file was generated). The 16M-entry YUV table is
 *   replaced by evaluating the same formula per loaded source pixel.
 *
 * ScaleFX (Sp00kyFox, 3x) - port of the libretro slang-shaders preset
 *   scalefx.slangp (passes 0..4, default parameters), upscale_scalefx.c, MIT.
 *   One deliberate deviation: texel fetches clamp to the edge, whereas the
 *   preset's default wrap (transparent-black border) would pull black into the
 *   frame's border sub-pixels. Passes 0/1 are evaluated in 32-bit floats in
 *   the shader's operation order; GPU float rounding is not bit-reproducible,
 *   so only exact ties of those comparisons could resolve differently.
 *   Passes 2..4 are discrete and reproduced exactly.
 *
 * xBR (Hyllian, level 2, 2x/3x/4x) - exact port, upscale_xbr.c,
 *   LGPL-2.1-or-later. Adapted from FFmpeg libavfilter/vf_xbr.c (Hyllian/
 *   Jararaca, Arwa Arif): pixel_diff() |dY| + |dU| + |dV| on FFmpeg's
 *   integer RGB->YUV, eq() < 155, the FILT2/3/4 macros, ALPHA_BLEND_*
 *   rounding and corner calls copied verbatim (checked line by line when the
 *   file was generated); the 16M-entry YUV table is replaced by the same
 *   integer expression evaluated per loaded source pixel.
 */
#include "upscale.h"
#include "upscale_impl.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#if defined(__GNUC__) || defined(__clang__)
#define UP_INLINE static inline __attribute__((always_inline))
#elif defined(_MSC_VER)
#define UP_INLINE static __forceinline
#else
#define UP_INLINE static inline
#endif

#define KBITS 12               /* separable kernel weight precision */
#define KONE (1 << KBITS)
#define LANE_BIAS ((1 << 19) + (KONE >> 1)) /* keeps SWAR lanes positive, adds rounding */
#define RGB_MASK 0x00FFFFFFu


struct UpscaleContext {
    int valid;
    UpscaleFilter filter;
    int sw, sh, dw, dh;
    int k;                       /* pixel-art prescale factor, 1 otherwise */
    int pw, ph;                  /* prescaled size (pixel-art filters) */
    uint32_t *pre;               /* pixel-art prescaled image, pw x ph */
    uint32_t *tmp;               /* horizontal pass result, dw x sh */
    uint64_t *ex;                /* source expanded to 21-bit lanes, sw x sh */
    int32_t *xmap, *ymap;        /* nearest */
    int32_t *xi0, *xi1, *yi0, *yi1; /* linear: left/right taps */
    uint16_t *xw, *yw;           /* linear: 8-bit weights of the second tap */
    int ht, vt;                  /* separable: taps per axis */
    int32_t *hidx, *hwt, *vidx, *vwt;
    SfxBuffers sfx;              /* ScaleFX pass buffers */
};

static int clampi(int v, int lo, int hi) { return v < lo ? lo : v > hi ? hi : v; }

/* ---- small pixel helpers ------------------------------------------------ */

/* a + (b - a) * w / 256 per channel, w in 0..256; packed two-lane form. */
UP_INLINE uint32_t lerp8(uint32_t a, uint32_t b, uint32_t w)
{
    uint32_t iw = 256 - w;
    uint32_t rb = ((a & 0xFF00FFu) * iw + (b & 0xFF00FFu) * w) >> 8;
    uint32_t g = ((a & 0x00FF00u) * iw + (b & 0x00FF00u) * w) >> 8;
    return (rb & 0xFF00FFu) | (g & 0x00FF00u);
}

/* ---- table builders ----------------------------------------------------- */

/* Linear taps with the sharp-bilinear weight remap; k == 1 is plain bilinear. */
static void build_linear(int ns, int nd, int k, int32_t *i0, int32_t *i1, uint16_t *w)
{
    double scale = (double)ns / nd;
    for (int x = 0; x < nd; ++x) {
        double u = (x + 0.5) * scale - 0.5;
        double t = floor(u);
        double f = (u - t - 0.5 + 0.5 / k) * k;
        f = f < 0.0 ? 0.0 : f > 1.0 ? 1.0 : f;
        int a = clampi((int)t, 0, ns - 1);
        int b = clampi((int)t + 1, 0, ns - 1);
        int wi = (int)(f * 256.0 + 0.5);
        if (wi >= 256) { a = b; wi = 0; }
        if (a == b) wi = 0;
        i0[x] = a; i1[x] = b; w[x] = (uint16_t)wi;
    }
}

static double kernel_cubic(double x) /* Catmull-Rom, a = -0.5 */
{
    x = fabs(x);
    if (x < 1.0) return (1.5 * x - 2.5) * x * x + 1.0;
    if (x < 2.0) return ((-0.5 * x + 2.5) * x - 4.0) * x + 2.0;
    return 0.0;
}

static double kernel_lanczos3(double x)
{
    const double pi = 3.14159265358979323846;
    x = fabs(x);
    if (x < 1e-9) return 1.0;
    if (x >= 3.0) return 0.0;
    double px = pi * x;
    return 3.0 * sin(px) * sin(px / 3.0) / (px * px);
}

/* Normalised fixed-point taps; the kernel is widened by the ratio when downscaling. */
static int build_kernel(int ns, int nd, int lanczos, int *taps_out, int32_t **idx_out, int32_t **wt_out)
{
    double scale = (double)ns / nd;
    double fs = scale > 1.0 ? scale : 1.0;
    double radius = (lanczos ? 3.0 : 2.0) * fs;
    int half = (int)ceil(radius);
    int taps = 2 * half;
    int32_t *idx = (int32_t *)malloc((size_t)nd * taps * sizeof *idx);
    int32_t *wt = (int32_t *)malloc((size_t)nd * taps * sizeof *wt);
    double *fw = (double *)malloc((size_t)taps * sizeof *fw);
    if (!idx || !wt || !fw) { free(idx); free(wt); free(fw); return 0; }
    for (int x = 0; x < nd; ++x) {
        double u = (x + 0.5) * scale - 0.5;
        int left = (int)floor(u) - half + 1;
        double sum = 0.0;
        for (int t = 0; t < taps; ++t) {
            fw[t] = lanczos ? kernel_lanczos3((left + t - u) / fs) : kernel_cubic((left + t - u) / fs);
            sum += fw[t];
        }
        if (sum == 0.0) sum = 1.0;
        int isum = 0, best = 0;
        for (int t = 0; t < taps; ++t) {
            int wi = (int)lround(fw[t] / sum * KONE);
            wt[x * taps + t] = wi;
            idx[x * taps + t] = clampi(left + t, 0, ns - 1);
            isum += wi;
            if (fabs(fw[t]) > fabs(fw[best])) best = t;
        }
        wt[x * taps + best] += KONE - isum;
    }
    free(fw);
    *taps_out = taps; *idx_out = idx; *wt_out = wt;
    return 1;
}

/* ---- context lifetime --------------------------------------------------- */

static void release(UpscaleContext *c)
{
    free(c->pre); free(c->tmp); free(c->ex);
    free(c->xmap); free(c->ymap);
    free(c->xi0); free(c->xi1); free(c->yi0); free(c->yi1); free(c->xw); free(c->yw);
    free(c->hidx); free(c->hwt); free(c->vidx); free(c->vwt);
    upscale_sfx_free(&c->sfx);
    c->pre = c->tmp = NULL; c->ex = NULL;
    c->xmap = c->ymap = c->xi0 = c->xi1 = c->yi0 = c->yi1 = NULL;
    c->xw = c->yw = NULL;
    c->hidx = c->hwt = c->vidx = c->vwt = NULL;
    c->valid = 0;
}

UpscaleContext *upscale_create(void)
{
    return (UpscaleContext *)calloc(1, sizeof(UpscaleContext));
}

void upscale_destroy(UpscaleContext *c)
{
    if (!c) return;
    release(c);
    free(c);
}

static int alloc_linear(UpscaleContext *c, int ns_x, int ns_y, int k)
{
    c->xi0 = (int32_t *)malloc((size_t)c->dw * sizeof(int32_t));
    c->xi1 = (int32_t *)malloc((size_t)c->dw * sizeof(int32_t));
    c->xw = (uint16_t *)malloc((size_t)c->dw * sizeof(uint16_t));
    c->yi0 = (int32_t *)malloc((size_t)c->dh * sizeof(int32_t));
    c->yi1 = (int32_t *)malloc((size_t)c->dh * sizeof(int32_t));
    c->yw = (uint16_t *)malloc((size_t)c->dh * sizeof(uint16_t));
    if (!c->xi0 || !c->xi1 || !c->xw || !c->yi0 || !c->yi1 || !c->yw) return 0;
    build_linear(ns_x, c->dw, k, c->xi0, c->xi1, c->xw);
    build_linear(ns_y, c->dh, k, c->yi0, c->yi1, c->yw);
    return 1;
}

static int whole_factor(int sw, int sh, int dw, int dh)
{
    int fx = dw / sw, fy = dh / sh;
    int f = fx < fy ? fx : fy;
    return f < 1 ? 1 : f;
}

int upscale_prepare(UpscaleContext *c, UpscaleFilter filter, int sw, int sh, int dw, int dh)
{
    if (!c) return 0;
    if (c->valid && c->filter == filter && c->sw == sw && c->sh == sh && c->dw == dw && c->dh == dh)
        return 1;
    release(c);
    if ((unsigned)filter >= UPSCALE_FILTER_COUNT || sw <= 0 || sh <= 0 || dw <= 0 || dh <= 0)
        return 0;
    c->filter = filter;
    c->sw = sw; c->sh = sh; c->dw = dw; c->dh = dh;
    c->k = 1; c->pw = sw; c->ph = sh;

    int ok = 1;
    switch (filter) {
    case UPSCALE_NEAREST:
        c->xmap = (int32_t *)malloc((size_t)dw * sizeof(int32_t));
        c->ymap = (int32_t *)malloc((size_t)dh * sizeof(int32_t));
        ok = c->xmap && c->ymap;
        if (ok) {
            for (int x = 0; x < dw; ++x)
                c->xmap[x] = clampi((int)(((int64_t)2 * x + 1) * sw / ((int64_t)2 * dw)), 0, sw - 1);
            for (int y = 0; y < dh; ++y)
                c->ymap[y] = clampi((int)(((int64_t)2 * y + 1) * sh / ((int64_t)2 * dh)), 0, sh - 1);
        }
        break;
    case UPSCALE_BILINEAR:
    case UPSCALE_SHARP_BILINEAR: {
        int k = filter == UPSCALE_SHARP_BILINEAR ? whole_factor(sw, sh, dw, dh) : 1;
        c->tmp = (uint32_t *)malloc((size_t)dw * sh * sizeof(uint32_t));
        ok = c->tmp && alloc_linear(c, sw, sh, k);
        break;
    }
    case UPSCALE_BICUBIC:
    case UPSCALE_LANCZOS3: {
        int lz = filter == UPSCALE_LANCZOS3;
        c->tmp = (uint32_t *)malloc((size_t)dw * sh * sizeof(uint32_t));
        c->ex = (uint64_t *)malloc((size_t)sw * sh * sizeof(uint64_t));
        ok = c->tmp && c->ex
            && build_kernel(sw, dw, lz, &c->ht, &c->hidx, &c->hwt)
            && build_kernel(sh, dh, lz, &c->vt, &c->vidx, &c->vwt);
        break;
    }
    default: { /* pixel-art */
        int k = filter == UPSCALE_SCALEFX ? 3 : clampi(whole_factor(sw, sh, dw, dh), 2, 4);
        c->k = k; c->pw = sw * k; c->ph = sh * k;
        c->pre = (uint32_t *)malloc((size_t)c->pw * c->ph * sizeof(uint32_t));
        ok = c->pre && alloc_linear(c, c->pw, c->ph, whole_factor(c->pw, c->ph, dw, dh));
        if (ok && filter == UPSCALE_SCALEFX) ok = upscale_sfx_alloc(&c->sfx, sw, sh);
        break;
    }
    }
    if (!ok) { release(c); return 0; }
    c->valid = 1;
    return 1;
}

int upscale_filter_factor(const UpscaleContext *c)
{
    return (c && c->valid) ? c->k : 1;
}

const char *upscale_filter_name(UpscaleFilter f)
{
    static const char *const names[UPSCALE_FILTER_COUNT] = {
        "Nearest", "Bilinear", "Sharp bilinear", "Bicubic", "Lanczos3", "xBR", "HQx", "ScaleFX"
    };
    return (unsigned)f < UPSCALE_FILTER_COUNT ? names[f] : "?";
}

/* ---- separable filters (linear and kernel) ------------------------------ */

/* Horizontal linear pass of source rows into tmp. */
static void linear_h(UpscaleContext *c, const uint32_t *src, int ss, int y0, int y1)
{
    const int32_t *i0 = c->xi0, *i1 = c->xi1;
    const uint16_t *w = c->xw;
    for (int y = y0; y < y1; ++y) {
        const uint32_t *s = src + (size_t)y * ss;
        uint32_t *t = c->tmp + (size_t)y * c->dw;
        for (int x = 0; x < c->dw; ++x) {
            uint32_t p = s[i0[x]];
            t[x] = w[x] ? lerp8(p, s[i1[x]], w[x]) : (p & RGB_MASK);
        }
    }
}

/* Vertical linear pass of tmp rows; bytes are independent so this vectorises. */
static void linear_v(UpscaleContext *c, uint32_t *dst, int ds, int y0, int y1)
{
    const size_t n = (size_t)c->dw * 4;
    for (int y = y0; y < y1; ++y) {
        uint32_t *out = dst + (size_t)y * ds;
        const uint32_t *ra = c->tmp + (size_t)c->yi0[y] * c->dw;
        unsigned wb = c->yw[y];
        if (wb == 0) { memcpy(out, ra, n); continue; }
        const uint8_t *restrict a = (const uint8_t *)ra;
        const uint8_t *restrict b = (const uint8_t *)(c->tmp + (size_t)c->yi1[y] * c->dw);
        uint8_t *restrict o = (uint8_t *)out;
        unsigned wa = 256 - wb;
        size_t i = 0;
        for (; i + 64 <= n; i += 64)
            for (int j = 0; j < 64; ++j)
                o[i + j] = (uint8_t)((a[i + j] * wa + b[i + j] * wb) >> 8);
        for (; i < n; ++i)
            o[i] = (uint8_t)((a[i] * wa + b[i] * wb) >> 8);
    }
}

UP_INLINE int lane_out(uint64_t acc, int shift)
{
    int v = (int)((acc >> shift) & 0x1FFFFF) - (1 << 19);
    v = v < 0 ? 0 : v >> KBITS;
    return v > 255 ? 255 : v;
}

/* Horizontal kernel pass. Each pixel is spread into three 21-bit lanes of a
 * uint64; signed taps accumulate modulo 2^64 and the bias makes every lane's
 * final value non-negative, so the lanes separate exactly. */
static void kernel_h(UpscaleContext *c, const uint32_t *src, int ss, int y0, int y1)
{
    const int taps = c->ht, sw = c->sw, dw = c->dw;
    const uint64_t bias = (uint64_t)LANE_BIAS | ((uint64_t)LANE_BIAS << 21) | ((uint64_t)LANE_BIAS << 42);
    for (int y = y0; y < y1; ++y) {
        const uint32_t *s = src + (size_t)y * ss;
        uint64_t *e = c->ex + (size_t)y * sw;
        for (int x = 0; x < sw; ++x) {
            uint64_t p = s[x];
            e[x] = (p & 0xFF) | ((p & 0xFF00) << 13) | ((p & 0xFF0000) << 26);
        }
        uint32_t *t = c->tmp + (size_t)y * dw;
        const int32_t *ix = c->hidx, *wt = c->hwt;
        for (int x = 0; x < dw; ++x, ix += taps, wt += taps) {
            uint64_t acc = bias;
            if (taps == 4) {
                acc += (uint64_t)(int64_t)wt[0] * e[ix[0]] + (uint64_t)(int64_t)wt[1] * e[ix[1]]
                     + (uint64_t)(int64_t)wt[2] * e[ix[2]] + (uint64_t)(int64_t)wt[3] * e[ix[3]];
            } else if (taps == 6) {
                acc += (uint64_t)(int64_t)wt[0] * e[ix[0]] + (uint64_t)(int64_t)wt[1] * e[ix[1]]
                     + (uint64_t)(int64_t)wt[2] * e[ix[2]] + (uint64_t)(int64_t)wt[3] * e[ix[3]]
                     + (uint64_t)(int64_t)wt[4] * e[ix[4]] + (uint64_t)(int64_t)wt[5] * e[ix[5]];
            } else {
                for (int k = 0; k < taps; ++k) acc += (uint64_t)(int64_t)wt[k] * e[ix[k]];
            }
            t[x] = (uint32_t)lane_out(acc, 0) | ((uint32_t)lane_out(acc, 21) << 8)
                 | ((uint32_t)lane_out(acc, 42) << 16);
        }
    }
}

/* Vertical kernel pass over tmp, per byte in fixed chunks so it vectorises. */
static void kernel_v(UpscaleContext *c, uint32_t *dst, int ds, int y0, int y1)
{
    enum { CH = 256 };
    const size_t n = (size_t)c->dw * 4;
    const int taps = c->vt;
    int32_t acc[CH];
    for (int y = y0; y < y1; ++y) {
        uint8_t *o = (uint8_t *)(dst + (size_t)y * ds);
        const int32_t *ix = c->vidx + (size_t)y * taps, *wt = c->vwt + (size_t)y * taps;
        for (size_t i0 = 0; i0 < n; i0 += CH) {
            size_t m = n - i0 < CH ? n - i0 : CH;
            /* +2^20 keeps the sum positive so the shift below is a plain floor */
            for (int i = 0; i < CH; ++i) acc[i] = (KONE >> 1) + (1 << 20);
            /* taps in pairs: 16-bit products summed in pairs map onto pmaddwd-style ops */
            int t = 0;
            for (; t + 2 <= taps; t += 2) {
                const uint8_t *r0 = (const uint8_t *)(c->tmp + (size_t)ix[t] * c->dw) + i0;
                const uint8_t *r1 = (const uint8_t *)(c->tmp + (size_t)ix[t + 1] * c->dw) + i0;
                const int16_t w0 = (int16_t)wt[t], w1 = (int16_t)wt[t + 1];
                if (m == CH) {
                    for (int i = 0; i < CH; ++i) acc[i] += w0 * (int16_t)r0[i] + w1 * (int16_t)r1[i];
                } else {
                    for (size_t i = 0; i < m; ++i) acc[i] += w0 * (int16_t)r0[i] + w1 * (int16_t)r1[i];
                }
            }
            for (; t < taps; ++t) {
                const uint8_t *r0 = (const uint8_t *)(c->tmp + (size_t)ix[t] * c->dw) + i0;
                const int16_t w0 = (int16_t)wt[t];
                for (size_t i = 0; i < m; ++i) acc[i] += w0 * (int16_t)r0[i];
            }
            for (size_t i = 0; i < m; ++i) {
                int v = (acc[i] >> KBITS) - 256;
                v = v < 0 ? 0 : v;
                o[i0 + i] = (uint8_t)(v > 255 ? 255 : v);
            }
        }
    }
}

/* Direct 2-D (sharp) bilinear from the pixel-art prescaled buffer. */
static void linear_2d(UpscaleContext *c, uint32_t *dst, int ds, int y0, int y1)
{
    const int32_t *i0 = c->xi0, *i1 = c->xi1;
    const uint16_t *w = c->xw;
    for (int y = y0; y < y1; ++y) {
        const uint32_t *a = c->pre + (size_t)c->yi0[y] * c->pw;
        const uint32_t *b = c->pre + (size_t)c->yi1[y] * c->pw;
        uint32_t wy = c->yw[y];
        uint32_t *out = dst + (size_t)y * ds;
        if (wy == 0) {
            for (int x = 0; x < c->dw; ++x)
                out[x] = w[x] ? lerp8(a[i0[x]], a[i1[x]], w[x]) : a[i0[x]];
        } else {
            for (int x = 0; x < c->dw; ++x) {
                uint32_t h0 = lerp8(a[i0[x]], a[i1[x]], w[x]);
                uint32_t h1 = lerp8(b[i0[x]], b[i1[x]], w[x]);
                out[x] = lerp8(h0, h1, wy);
            }
        }
    }
}

static void nearest(UpscaleContext *c, const uint32_t *src, int ss, uint32_t *dst, int ds, int y0, int y1)
{
    for (int y = y0; y < y1; ++y) {
        uint32_t *out = dst + (size_t)y * ds;
        int sy = c->ymap[y];
        if (y > y0 && c->ymap[y - 1] == sy) {
            memcpy(out, out - ds, (size_t)c->dw * 4);
            continue;
        }
        const uint32_t *s = src + (size_t)sy * ss;
        for (int x = 0; x < c->dw; ++x) out[x] = s[c->xmap[x]] & RGB_MASK;
    }
}

/* ---- pass table and public run entry points ------------------------------ */

/* What each pass of a filter does; the last pass of every filter writes dst. */
typedef enum PassKind {
    P_NEAREST, P_LINEAR_H, P_LINEAR_V, P_KERNEL_H, P_KERNEL_V,
    P_XBR, P_HQX, P_SFX0, P_SFX1, P_SFX2, P_SFX34, P_RESAMPLE
} PassKind;

enum { MAX_PASSES = 5 };

/* Pass list of the prepared filter; returns the pass count. */
static int pass_list(const UpscaleContext *c, PassKind out[MAX_PASSES])
{
    static const PassKind nearest_p[] = { P_NEAREST };
    static const PassKind linear_p[] = { P_LINEAR_H, P_LINEAR_V };
    static const PassKind kernel_p[] = { P_KERNEL_H, P_KERNEL_V };
    static const PassKind xbr_p[] = { P_XBR, P_RESAMPLE };
    static const PassKind hqx_p[] = { P_HQX, P_RESAMPLE };
    static const PassKind sfx_p[] = { P_SFX0, P_SFX1, P_SFX2, P_SFX34, P_RESAMPLE };
    const PassKind *l;
    int n;
    switch (c->filter) {
    case UPSCALE_NEAREST: l = nearest_p; n = 1; break;
    case UPSCALE_BILINEAR:
    case UPSCALE_SHARP_BILINEAR: l = linear_p; n = 2; break;
    case UPSCALE_BICUBIC:
    case UPSCALE_LANCZOS3: l = kernel_p; n = 2; break;
    case UPSCALE_XBR: l = xbr_p; n = 2; break;
    case UPSCALE_HQX: l = hqx_p; n = 2; break;
    default: l = sfx_p; n = 5; break;
    }
    for (int i = 0; i < n; ++i) out[i] = l[i];
    return n;
}

int upscale_pass_count(const UpscaleContext *c)
{
    PassKind p[MAX_PASSES];
    if (!c || !c->valid) return 1;
    return pass_list(c, p);
}

int upscale_pass_rows(const UpscaleContext *c, int pass)
{
    PassKind p[MAX_PASSES];
    if (!c || !c->valid) return 0;
    const int n = pass_list(c, p);
    if (pass < 0 || pass >= n) return 0;
    return pass == n - 1 ? c->dh : c->sh;
}

void upscale_run_pass(UpscaleContext *c, int pass, const uint32_t *src, int ss,
                      uint32_t *dst, int ds, int y0, int y1)
{
    PassKind p[MAX_PASSES];
    if (!c || !c->valid) return;
    const int n = pass_list(c, p);
    if (pass < 0 || pass >= n) return;
    const int rows = pass == n - 1 ? c->dh : c->sh;
    if (y0 < 0) y0 = 0;
    if (y1 > rows) y1 = rows;
    if (y0 >= y1) return;
    switch (p[pass]) {
    case P_NEAREST: if (src && dst) nearest(c, src, ss, dst, ds, y0, y1); break;
    case P_LINEAR_H: if (src) linear_h(c, src, ss, y0, y1); break;
    case P_LINEAR_V: if (dst) linear_v(c, dst, ds, y0, y1); break;
    case P_KERNEL_H: if (src) kernel_h(c, src, ss, y0, y1); break;
    case P_KERNEL_V: if (dst) kernel_v(c, dst, ds, y0, y1); break;
    case P_XBR: if (src) upscale_xbr_rows(c->k, src, ss, c->sw, c->sh, c->pre, c->pw, y0, y1); break;
    case P_HQX: if (src) upscale_hqx_rows(c->k, src, ss, c->sw, c->sh, c->pre, c->pw, y0, y1); break;
    case P_SFX0: if (src) upscale_sfx_pass0(&c->sfx, src, ss, y0, y1); break;
    case P_SFX1: upscale_sfx_pass1(&c->sfx, y0, y1); break;
    case P_SFX2: upscale_sfx_pass2(&c->sfx, y0, y1); break;
    case P_SFX34: if (src) upscale_sfx_pass34(&c->sfx, src, ss, c->pre, c->pw, y0, y1); break;
    case P_RESAMPLE: if (dst) linear_2d(c, dst, ds, y0, y1); break;
    }
}

void upscale_run(UpscaleContext *c, const uint32_t *src, int ss, uint32_t *dst, int ds)
{
    if (!c || !c->valid) return;
    const int n = upscale_pass_count(c);
    for (int pass = 0; pass < n; ++pass)
        upscale_run_pass(c, pass, src, ss, dst, ds, 0, upscale_pass_rows(c, pass));
}
