/* CPU image upscaler: see upscale.h for the threading contract.
 *
 * Fidelity notes for the pixel-art filters (all written from memory, no
 * reference source was available while writing this file):
 *
 * xBR (Hyllian, level 2, 2x/3x/4x)
 *   Faithful to the structure of the well-known C port (FFmpeg vf_xbr):
 *   21-pixel window, e/i edge-weight sums (4x the central diagonal), the
 *   eq()-based corner tests (separate 3x test), left/up/diagonal shallow-edge
 *   cases and the 32/64/128/192/224 alpha-blend sub-pixel rules for each
 *   factor, applied in the I, C, A, G corner order. Reconstructed/approximate:
 *   - colour distance is 48|dY| + 7|dU| + 6|dV| on 8-bit integer YUV
 *     (BT.601 weights) of the two pixels, not a 16M-entry table;
 *   - the eq() threshold (3825 on that scale, i.e. a pure-luma step of 80/255)
 *     is taken from the shader's XBR_EQ_THRESHOLD 15 on the 48-weighted luma;
 *   - blends round by truncation, so a sub-pixel may differ by 1 from the C port.
 *
 * HQx (Maxim Stepin, hq2x/hq3x/hq4x)
 *   Exact: the YUV conversion (Y=(r+g+b)/4, U=128+(r-b)/4, V=128+(2g-r-b)/8),
 *   the thresholds Y 48 / U 7 / V 6, the 8-neighbour difference pattern and
 *   the w2/w4-style "Diff(edge, edge)" corner test.
 *   Reconstructed: the 256-case tables are NOT reproduced. Each corner of a
 *   cell is classified from its three neighbours (corner, two edges):
 *   - both edges differ from the centre and match each other: the corner is
 *     cut along the line x+y = 1/2 of the cell; sub-pixels take the edge
 *     colour in proportion to the area beyond that line. This gives exactly
 *     hq2x Interp2 (2:1:1), hq3x Interp4 (2:7:7) / Interp3 (7:1) and the
 *     hq4x 100%/50% pattern for the plain diagonal case;
 *   - both edges differ from the centre and from each other: the corner
 *     sub-pixel blends 1/4 (hq4x 3/8) toward the corner pixel when it differs;
 *   - otherwise the corner sub-pixel is smoothed toward the similar
 *     neighbours with the hq2x Interp1/Interp2 weights (half that at 3x/4x).
 *   The shallow-slope cases of the real tables (Interp6/7/9/10 for 2:1 edges)
 *   are not modelled.
 *
 * ScaleFX (Sp00kyFox, 3x)
 *   Exact: the "redmean" colour metric of pass 0 (sqrt of
 *   (2+r)dR^2 + 4dG^2 + (3-r)dB^2, through an integer sqrt table) and the
 *   colour threshold 0.5 (SFX_CLR); output never blends, every sub-pixel
 *   takes a source colour.
 *   Reconstructed: corner strength/resolution uses the xBR-style e/i sums of
 *   that metric around each 2x2 block instead of the ScaleFX str() formula;
 *   a corner is cut only when the crossing pair is close (2*d < contrast) and
 *   the odd pixel continues diagonally (avoids rounding rectangle corners).
 *   Only level-1 (45 degree) edges are produced: the multi-level edge search
 *   and sub-pixel tags for shallow slopes (passes 3-4) are not reproduced.
 */
#include "upscale.h"

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

#define XBR_EQ 3825            /* see header comment */
#define SFX_CLR 382            /* 0.5 on the 0..765 redmean scale */
#define SQRT_LUT_SHIFT 5
#define SQRT_LUT_SIZE ((584966 >> SQRT_LUT_SHIFT) + 2)

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
    uint16_t *sqrt_lut;          /* ScaleFX metric */
    uint8_t nmap[4][16];         /* pixel-art: sub-pixel index per corner rotation */
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
    free(c->sqrt_lut);
    c->pre = c->tmp = NULL; c->ex = NULL;
    c->xmap = c->ymap = c->xi0 = c->xi1 = c->yi0 = c->yi1 = NULL;
    c->xw = c->yw = NULL;
    c->hidx = c->hwt = c->vidx = c->vwt = NULL;
    c->sqrt_lut = NULL;
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
        for (int r = 0; r < 4; ++r)
            for (int i = 0; i < k * k; ++i) {
                int sx = i % k, sy = i / k;
                for (int q = 0; q < r; ++q) { int t = sx; sx = sy; sy = k - 1 - t; }
                c->nmap[r][i] = (uint8_t)(sy * k + sx);
            }
        if (ok && filter == UPSCALE_SCALEFX) {
            c->sqrt_lut = (uint16_t *)malloc(SQRT_LUT_SIZE * sizeof(uint16_t));
            ok = c->sqrt_lut != NULL;
            for (int i = 0; ok && i < SQRT_LUT_SIZE; ++i)
                c->sqrt_lut[i] = (uint16_t)(sqrt((double)i * (1 << SQRT_LUT_SHIFT)
                                                 + (1 << (SQRT_LUT_SHIFT - 1))) + 0.5);
        }
        break;
    }
    }
    if (!ok) { release(c); return 0; }
    c->valid = 1;
    return 1;
}

int upscale_stage1_rows(const UpscaleContext *c)
{
    if (!c || !c->valid || c->filter == UPSCALE_NEAREST) return 0;
    return c->sh;
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

/* ---- pixel-art prescalers ----------------------------------------------- */

/* Sources are processed in column tiles with a 2-pixel halo; a sliding window
 * of 5 rows (plus per-row diagonal distances and 2x2 block edge sums) lives on
 * the stack so concurrent stage-1 slices share no scratch memory. */
#define TILE_W 128
#define TILE_P (TILE_W + 4)

enum { PA_XBR, PA_HQX, PA_SFX };

typedef struct PaTile {
    uint32_t pix[5][TILE_P], yuv[5][TILE_P];
    int32_t dm[4][TILE_P], da[4][TILE_P];  /* diagonal distances of row pairs */
    int32_t sm[2][TILE_P], sa[2][TILE_P];  /* block edge sums, block rows y-1, y */
    uint32_t *pr[5], *yr[5];
    int32_t *dmr[4], *dar[4], *smr[2], *sar[2];
} PaTile;

UP_INLINE uint32_t xbr_yuv(uint32_t p)
{
    int r = (int)(p >> 16) & 255, g = (int)(p >> 8) & 255, b = (int)p & 255;
    int y = (77 * r + 150 * g + 29 * b + 128) >> 8;
    int u = (-43 * r - 85 * g + 128 * b) / 256 + 128;
    int v = (128 * r - 107 * g - 21 * b) / 256 + 128;
    return (uint32_t)y | ((uint32_t)u << 10) | ((uint32_t)v << 20);
}

UP_INLINE int xbr_df(uint32_t a, uint32_t b)
{
    int dy = (int)(a & 1023) - (int)(b & 1023);
    int du = (int)((a >> 10) & 1023) - (int)((b >> 10) & 1023);
    int dv = (int)(a >> 20) - (int)(b >> 20);
    return 48 * abs(dy) + 7 * abs(du) + 6 * abs(dv);
}

UP_INLINE uint32_t hq_yuv(uint32_t p)
{
    int r = (int)(p >> 16) & 255, g = (int)(p >> 8) & 255, b = (int)p & 255;
    int y = (r + g + b) >> 2;
    int u = ((r - b + 256) >> 2) + 64;          /* 128 + floor((r-b)/4) */
    int v = ((2 * g - r - b + 512) >> 3) + 64;  /* 128 + floor((2g-r-b)/8) */
    return (uint32_t)y | ((uint32_t)u << 8) | ((uint32_t)v << 16);
}

UP_INLINE int hq_diff(uint32_t a, uint32_t b)
{
    return abs((int)(a & 255) - (int)(b & 255)) > 48
        || abs((int)((a >> 8) & 255) - (int)((b >> 8) & 255)) > 7
        || abs((int)(a >> 16) - (int)(b >> 16)) > 6;
}

/* ScaleFX pass-0 metric, scaled to 0..765 (= 765 * metric). */
UP_INLINE int sfx_dist(const uint16_t *lut, uint32_t a, uint32_t b)
{
    int ra = (int)(a >> 16) & 255, rb = (int)(b >> 16) & 255;
    int dr = ra - rb;
    int dg = (int)((a >> 8) & 255) - (int)((b >> 8) & 255);
    int db = (int)(a & 255) - (int)(b & 255);
    int rm = (ra + rb) >> 1;
    uint32_t d2 = ((uint32_t)(512 + rm) * (uint32_t)(dr * dr) + 1024u * (uint32_t)(dg * dg)
                   + (uint32_t)(767 - rm) * (uint32_t)(db * db)) >> 8;
    return lut[d2 >> SQRT_LUT_SHIFT];
}

static void tile_load_row(int mode, uint32_t *pix, uint32_t *yuv, const uint32_t *src, int ss,
                          int sw, int sh, int y, int x0, int n)
{
    const uint32_t *s = src + (size_t)clampi(y, 0, sh - 1) * ss;
    for (int j = 0; j < n; ++j) {
        uint32_t p = s[clampi(x0 + j - 2, 0, sw - 1)] & RGB_MASK;
        pix[j] = p;
        if (mode == PA_XBR) yuv[j] = xbr_yuv(p);
        else if (mode == PA_HQX) yuv[j] = hq_yuv(p);
    }
}

static void tile_pair_row(int mode, const uint16_t *lut, PaTile *t, int pi, int n)
{
    int32_t *dm = t->dmr[pi], *da = t->dar[pi];
    if (mode == PA_XBR) {
        const uint32_t *a = t->yr[pi], *b = t->yr[pi + 1];
        for (int j = 0; j < n - 1; ++j) {
            dm[j] = xbr_df(a[j], b[j + 1]);
            da[j] = xbr_df(a[j + 1], b[j]);
        }
    } else {
        const uint32_t *a = t->pr[pi], *b = t->pr[pi + 1];
        for (int j = 0; j < n - 1; ++j) {
            dm[j] = sfx_dist(lut, a[j], b[j + 1]);
            da[j] = sfx_dist(lut, a[j + 1], b[j]);
        }
    }
}

/* Edge sums of the 2x2 blocks whose top-left pixel is in block row br. */
static void tile_block_row(PaTile *t, int br, int n)
{
    const int32_t *mu = t->dmr[br], *mc = t->dmr[br + 1], *md = t->dmr[br + 2];
    const int32_t *au = t->dar[br], *ac = t->dar[br + 1], *ad = t->dar[br + 2];
    int32_t *sm = t->smr[br], *sa = t->sar[br];
    for (int j = 1; j <= n - 3; ++j) {
        sm[j] = 4 * mc[j] + mc[j - 1] + mc[j + 1] + mu[j] + md[j];
        sa[j] = 4 * ac[j] + ac[j - 1] + ac[j + 1] + au[j] + ad[j];
    }
}

/* Offset (dx, dy) rotated r quarter turns, (x, y) -> (y, -x): corner I -> C -> A -> G. */
UP_INLINE uint32_t at_rot(uint32_t *const *rows, int j, int r, int dx, int dy)
{
    for (int q = 0; q < r; ++q) { int t = dx; dx = dy; dy = -t; }
    return rows[dy + 2][j + dx];
}

/* e/i sums for the corner of rotation r of pixel j (see FFmpeg's FILT order). */
UP_INLINE void corner_sums(const PaTile *t, int r, int j, int *e, int *i)
{
    switch (r) {
    case 0: *e = t->sar[1][j]; *i = t->smr[1][j]; break;
    case 1: *e = t->smr[0][j]; *i = t->sar[0][j]; break;
    case 2: *e = t->sar[0][j - 1]; *i = t->smr[0][j - 1]; break;
    default: *e = t->smr[1][j - 1]; *i = t->sar[1][j - 1]; break;
    }
}

/* One xBR level-2 corner rule (canonical corner I = bottom-right). */
UP_INLINE void xbr_corner(const PaTile *t, const int r, int n, int j, uint32_t *cell, const uint8_t *nm)
{
#define PX(dx, dy) at_rot(t->pr, j, r, dx, dy)
#define YV(dx, dy) at_rot(t->yr, j, r, dx, dy)
#define EQ(a, b) (xbr_df(a, b) < XBR_EQ)
#define N(q) cell[nm[q]]
    const uint32_t E = t->pr[2][j], H = PX(0, 1), F = PX(1, 0);
    int e, i;
    if (E == H || E == F) return;
    corner_sums(t, r, j, &e, &i);
    if (e > i) return;
    const uint32_t yE = t->yr[2][j], yH = YV(0, 1), yF = YV(1, 0);
    const uint32_t px = xbr_df(yE, yF) <= xbr_df(yE, yH) ? F : H;
    const int last = n * n - 1;
    if (e < i) {
        const uint32_t yB = YV(0, -1), yD = YV(-1, 0), yI = YV(1, 1), yG = YV(-1, 1), yC = YV(1, -1);
        const uint32_t yI4 = YV(2, 1), yI5 = YV(1, 2);
        int cond;
        if (n == 3) {
            const uint32_t yF4 = YV(2, 0), yH5 = YV(0, 2);
            cond = (!EQ(yF, yB) && !EQ(yF, yC)) || (!EQ(yH, yD) && !EQ(yH, yG))
                || (EQ(yE, yI) && ((!EQ(yF, yF4) && !EQ(yF, yI4)) || (!EQ(yH, yH5) && !EQ(yH, yI5))))
                || EQ(yE, yG) || EQ(yE, yC);
        } else {
            cond = (!EQ(yF, yB) && !EQ(yH, yD))
                || (EQ(yE, yI) && (!EQ(yF, yI4) || !EQ(yH, yI5)))
                || EQ(yE, yG) || EQ(yE, yC);
        }
        if (cond) {
            const uint32_t G = PX(-1, 1), C = PX(1, -1), D = PX(-1, 0), B = PX(0, -1);
            const int ke = xbr_df(yF, yG), ki = xbr_df(yH, yC);
            const int left = (ke << 1) <= ki && E != G && D != G;
            const int up = ke >= (ki << 1) && E != C && B != C;
            if (n == 2) {
                if (left && up) { N(3) = lerp8(N(3), px, 224); N(2) = lerp8(N(2), px, 64); N(1) = N(2); }
                else if (left) { N(3) = lerp8(N(3), px, 192); N(2) = lerp8(N(2), px, 64); }
                else if (up) { N(3) = lerp8(N(3), px, 192); N(1) = lerp8(N(1), px, 64); }
                else N(3) = lerp8(N(3), px, 128);
            } else if (n == 3) {
                if (left && up) {
                    N(7) = lerp8(N(7), px, 192); N(6) = lerp8(N(6), px, 64);
                    N(5) = N(7); N(2) = N(6); N(8) = px;
                } else if (left) {
                    N(7) = lerp8(N(7), px, 192); N(5) = lerp8(N(5), px, 64);
                    N(6) = lerp8(N(6), px, 64); N(8) = px;
                } else if (up) {
                    N(5) = lerp8(N(5), px, 192); N(7) = lerp8(N(7), px, 64);
                    N(2) = lerp8(N(2), px, 64); N(8) = px;
                } else {
                    N(8) = lerp8(N(8), px, 224); N(5) = lerp8(N(5), px, 32);
                    N(7) = lerp8(N(7), px, 32);
                }
            } else {
                if (left && up) {
                    N(13) = lerp8(N(13), px, 192); N(12) = lerp8(N(12), px, 64);
                    N(15) = N(14) = N(11) = px;
                    N(10) = N(3) = N(12);
                    N(7) = N(13);
                } else if (left) {
                    N(11) = lerp8(N(11), px, 192); N(13) = lerp8(N(13), px, 192);
                    N(10) = lerp8(N(10), px, 64); N(12) = lerp8(N(12), px, 64);
                    N(14) = px; N(15) = px;
                } else if (up) {
                    N(14) = lerp8(N(14), px, 192); N(7) = lerp8(N(7), px, 192);
                    N(10) = lerp8(N(10), px, 64); N(3) = lerp8(N(3), px, 64);
                    N(11) = px; N(15) = px;
                } else {
                    N(11) = lerp8(N(11), px, 128); N(14) = lerp8(N(14), px, 128);
                    N(15) = px;
                }
            }
            return;
        }
    }
    N(last) = lerp8(N(last), px, 128);
#undef PX
#undef YV
#undef EQ
#undef N
}

/* Reconstructed ScaleFX level-1 corner (canonical corner I = bottom-right). */
UP_INLINE void sfx_corner(const PaTile *t, const uint16_t *lut, const int r, int j, uint32_t *cell,
                          const uint8_t *nm)
{
    const uint32_t E = t->pr[2][j], H = at_rot(t->pr, j, r, 0, 1), F = at_rot(t->pr, j, r, 1, 0);
    int e, i;
    if (E == H || E == F) return;
    corner_sums(t, r, j, &e, &i);
    if (e >= i) return;  /* the F-H diagonal must dominate */
    const int dFH = sfx_dist(lut, F, H), dEF = sfx_dist(lut, E, F), dEH = sfx_dist(lut, E, H);
    const int m = dEF < dEH ? dEF : dEH;
    if (dFH >= SFX_CLR || 2 * dFH >= m) return;
    /* odd pixel must continue diagonally, otherwise it is a rectangle corner */
    const uint32_t C = at_rot(t->pr, j, r, 1, -1), G = at_rot(t->pr, j, r, -1, 1);
    if (2 * sfx_dist(lut, E, C) >= m && 2 * sfx_dist(lut, E, G) >= m) return;
    cell[nm[8]] = dEF <= dEH ? F : H;
}

/* Reconstructed HQx cell (see header comment). w/yv: 3x3 neighbourhood. */
static void hq_cell(int k, const uint32_t w[9], const uint32_t yv[9], uint32_t *cell)
{
    static const unsigned char CN[4][3] = { { 0, 1, 3 }, { 2, 1, 5 }, { 6, 7, 3 }, { 8, 7, 5 } };
    static const unsigned char COV_N[5] = { 0, 0, 1, 3, 3 };
    static const unsigned char COV[5][3][3] = {
        { { 0 } }, { { 0 } },
        { { 0, 0, 32 } },
        { { 0, 0, 56 }, { 1, 0, 8 }, { 0, 1, 8 } },
        { { 0, 0, 64 }, { 1, 0, 32 }, { 0, 1, 32 } },
    };
    const uint32_t E = w[4];
    const int kk = k * k;
    if (w[0] == E && w[1] == E && w[2] == E && w[3] == E && w[5] == E && w[6] == E && w[7] == E && w[8] == E) {
        for (int q = 0; q < kk; ++q) cell[q] = E;
        return;
    }
    int d[9];
    for (int q = 0; q < 9; ++q) d[q] = w[q] != E && hq_diff(yv[q], yv[4]);
    int ar[16], ag[16], ab[16], rem[16];
    for (int q = 0; q < kk; ++q) { ar[q] = ag[q] = ab[q] = 0; rem[q] = 64; }
#define ADD(idx, col, wt) do { uint32_t c_ = (col); int w_ = (wt); \
        ar[idx] += (int)((c_ >> 16) & 255) * w_; ag[idx] += (int)((c_ >> 8) & 255) * w_; \
        ab[idx] += (int)(c_ & 255) * w_; rem[idx] -= w_; } while (0)
    for (int q = 0; q < 4; ++q) {
        const int c = CN[q][0], a = CN[q][1], b = CN[q][2];
        const int mx = q & 1, my = q >> 1;
        const int corner = (my ? k - 1 : 0) * k + (mx ? k - 1 : 0);
        if (d[a] && d[b]) {
            if (w[a] == w[b] || !hq_diff(yv[a], yv[b])) {
                for (int s = 0; s < COV_N[k]; ++s) {
                    int lx = COV[k][s][0], ly = COV[k][s][1], wt = COV[k][s][2];
                    int idx = (my ? k - 1 - ly : ly) * k + (mx ? k - 1 - lx : lx);
                    ADD(idx, w[a], wt / 2);
                    ADD(idx, w[b], wt / 2);
                }
            } else if (d[c]) {
                ADD(corner, w[c], k == 4 ? 24 : 16);
            }
        } else {
            const int half = k == 2 ? 16 : 8;
            if (!d[a] && !d[b]) { ADD(corner, w[a], half); ADD(corner, w[b], half); }
            else {
                const int sim = d[a] ? b : a;
                if (!d[c]) { ADD(corner, w[c], half); ADD(corner, w[sim], half); }
                else ADD(corner, w[sim], half);
            }
        }
    }
#undef ADD
    const int er = (int)(E >> 16) & 255, eg = (int)(E >> 8) & 255, eb = (int)E & 255;
    for (int q = 0; q < kk; ++q) {
        uint32_t r = (uint32_t)((ar[q] + er * rem[q] + 32) >> 6);
        uint32_t g = (uint32_t)((ag[q] + eg * rem[q] + 32) >> 6);
        uint32_t b = (uint32_t)((ab[q] + eb * rem[q] + 32) >> 6);
        cell[q] = (r << 16) | (g << 8) | b;
    }
}

static void pixel_art_stage1(UpscaleContext *c, const uint32_t *src, int ss, int y0, int y1)
{
    const int mode = c->filter == UPSCALE_XBR ? PA_XBR : c->filter == UPSCALE_HQX ? PA_HQX : PA_SFX;
    const int k = c->k, sw = c->sw, sh = c->sh, pw = c->pw;
    const uint16_t *lut = c->sqrt_lut;
    const int need_sums = mode != PA_HQX;
    PaTile t;
    uint32_t cell[16];

    for (int x0 = 0; x0 < sw; x0 += TILE_W) {
        const int tw = sw - x0 < TILE_W ? sw - x0 : TILE_W;
        const int n = tw + 4;
        for (int q = 0; q < 5; ++q) { t.pr[q] = t.pix[q]; t.yr[q] = t.yuv[q]; }
        for (int q = 0; q < 4; ++q) { t.dmr[q] = t.dm[q]; t.dar[q] = t.da[q]; }
        for (int q = 0; q < 2; ++q) { t.smr[q] = t.sm[q]; t.sar[q] = t.sa[q]; }
        for (int q = 0; q < 5; ++q) tile_load_row(mode, t.pr[q], t.yr[q], src, ss, sw, sh, y0 + q - 2, x0, n);
        if (need_sums) {
            for (int q = 0; q < 4; ++q) tile_pair_row(mode, lut, &t, q, n);
            tile_block_row(&t, 0, n);
            tile_block_row(&t, 1, n);
        }
        for (int y = y0; y < y1; ++y) {
            uint32_t *orow = c->pre + (size_t)y * k * pw + (size_t)x0 * k;
            for (int j = 2; j < tw + 2; ++j) {
                if (mode == PA_HQX) {
                    uint32_t w[9], yv[9];
                    for (int q = 0; q < 3; ++q) {
                        w[q] = t.pr[1][j - 1 + q]; w[3 + q] = t.pr[2][j - 1 + q]; w[6 + q] = t.pr[3][j - 1 + q];
                        yv[q] = t.yr[1][j - 1 + q]; yv[3 + q] = t.yr[2][j - 1 + q]; yv[6 + q] = t.yr[3][j - 1 + q];
                    }
                    hq_cell(k, w, yv, cell);
                } else {
                    const uint32_t E = t.pr[2][j];
                    for (int q = 0; q < k * k; ++q) cell[q] = E;
                    if (mode == PA_XBR) {
                        xbr_corner(&t, 0, k, j, cell, c->nmap[0]);
                        xbr_corner(&t, 1, k, j, cell, c->nmap[1]);
                        xbr_corner(&t, 2, k, j, cell, c->nmap[2]);
                        xbr_corner(&t, 3, k, j, cell, c->nmap[3]);
                    } else {
                        sfx_corner(&t, lut, 0, j, cell, c->nmap[0]);
                        sfx_corner(&t, lut, 1, j, cell, c->nmap[1]);
                        sfx_corner(&t, lut, 2, j, cell, c->nmap[2]);
                        sfx_corner(&t, lut, 3, j, cell, c->nmap[3]);
                    }
                }
                uint32_t *o = orow + (size_t)(j - 2) * k;
                for (int sy = 0; sy < k; ++sy)
                    for (int sx = 0; sx < k; ++sx) o[(size_t)sy * pw + sx] = cell[sy * k + sx];
            }
            if (y + 1 >= y1) break;
            /* slide the window one row down */
            uint32_t *rp = t.pr[0], *ry = t.yr[0];
            for (int q = 0; q < 4; ++q) { t.pr[q] = t.pr[q + 1]; t.yr[q] = t.yr[q + 1]; }
            t.pr[4] = rp; t.yr[4] = ry;
            tile_load_row(mode, rp, ry, src, ss, sw, sh, y + 3, x0, n);
            if (need_sums) {
                int32_t *m0 = t.dmr[0], *a0 = t.dar[0];
                for (int q = 0; q < 3; ++q) { t.dmr[q] = t.dmr[q + 1]; t.dar[q] = t.dar[q + 1]; }
                t.dmr[3] = m0; t.dar[3] = a0;
                tile_pair_row(mode, lut, &t, 3, n);
                int32_t *s0 = t.smr[0], *s1 = t.sar[0];
                t.smr[0] = t.smr[1]; t.sar[0] = t.sar[1];
                t.smr[1] = s0; t.sar[1] = s1;
                tile_block_row(&t, 1, n);
            }
        }
    }
}

/* ---- public run entry points -------------------------------------------- */

void upscale_run_stage1(UpscaleContext *c, const uint32_t *src, int ss, int y0, int y1)
{
    if (!c || !c->valid || !src) return;
    if (y0 < 0) y0 = 0;
    if (y1 > c->sh) y1 = c->sh;
    if (y0 >= y1) return;
    switch (c->filter) {
    case UPSCALE_BILINEAR:
    case UPSCALE_SHARP_BILINEAR: linear_h(c, src, ss, y0, y1); break;
    case UPSCALE_BICUBIC:
    case UPSCALE_LANCZOS3: kernel_h(c, src, ss, y0, y1); break;
    case UPSCALE_XBR:
    case UPSCALE_HQX:
    case UPSCALE_SCALEFX: pixel_art_stage1(c, src, ss, y0, y1); break;
    default: break;
    }
}

void upscale_run_stage2(UpscaleContext *c, const uint32_t *src, int ss, uint32_t *dst, int ds, int y0, int y1)
{
    if (!c || !c->valid || !dst) return;
    if (y0 < 0) y0 = 0;
    if (y1 > c->dh) y1 = c->dh;
    if (y0 >= y1) return;
    switch (c->filter) {
    case UPSCALE_NEAREST: if (src) nearest(c, src, ss, dst, ds, y0, y1); break;
    case UPSCALE_BILINEAR:
    case UPSCALE_SHARP_BILINEAR: linear_v(c, dst, ds, y0, y1); break;
    case UPSCALE_BICUBIC:
    case UPSCALE_LANCZOS3: kernel_v(c, dst, ds, y0, y1); break;
    default: linear_2d(c, dst, ds, y0, y1); break;
    }
}

void upscale_run(UpscaleContext *c, const uint32_t *src, int ss, uint32_t *dst, int ds)
{
    if (!c || !c->valid) return;
    upscale_run_stage1(c, src, ss, 0, c->sh);
    upscale_run_stage2(c, src, ss, dst, ds, 0, c->dh);
}
