/* ScaleFX for the remake's CPU upscaler (see upscale.c).
 *
 * C port of the libretro slang-shaders ScaleFX preset (scalefx.slangp,
 * scalefx-pass0..pass4.slang), by Sp00kyFox:
 *
 *   Copyright (c) 2016 Sp00kyFox - ScaleFX@web.de
 *
 *   Permission is hereby granted, free of charge, to any person obtaining a copy
 *   of this software and associated documentation files (the "Software"), to deal
 *   in the Software without restriction, including without limitation the rights
 *   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *   copies of the Software, and to permit persons to whom the Software is
 *   furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in
 *   all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *   THE SOFTWARE.
 *
 * Port notes (preset defaults: SFX_CLR 0.50, SFX_SAA 1.00, SFX_SCN 1.0; every
 * pass nearest-filtered at source scale, pass 4 at 3x; pass 0 reads the stock
 * "refpass" copy of the input):
 *   - texel fetches outside the frame clamp to the edge texel of the texture
 *     read (input or pass output), i.e. the preset run with
 *     wrap_mode = clamp_to_edge on every pass. The preset's own default wrap
 *     (clamp_to_border, transparent black) would detect edges against black
 *     all around the frame and pull black into its border sub-pixels; this
 *     is the one deliberate deviation from the preset defaults;
 *   - pass 0/1 values (float framebuffers in the preset) are kept as 32-bit
 *     floats computed in the shader's operation order; a backend storing them
 *     as 16-bit floats could resolve exact near-ties differently;
 *   - pass 2/3 write 8-bit UNORM targets whose decoding (loadCorn/.../loadMid)
 *     recovers the encoded small integers exactly, so they are kept here as
 *     those integers (pass 2: four 4-bit fields, pass 3: crn/mid 0..8);
 *   - pass 2's vertex shader scales TexCoord by 1.0001; that only moves the
 *     sampled texel for frames at least 5000 texels wide, so it is ignored;
 *   - pass 4 reads only its own pass-3 texel, so it is fused with pass 3.
 */
#include "upscale_impl.h"

#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define SFX_CLR 0.50f
#define SFX_SAA 1.00f
#define SFX_SCN 1.0f

typedef struct V4 { float x, y, z, w; } V4;
typedef struct B4 { int x, y, z, w; } B4;
typedef struct B2 { int x, y; } B2;

int upscale_sfx_alloc(SfxBuffers *b, int sw, int sh)
{
    const size_t n1 = (size_t)(sw + 2) * (sh + 2), n3 = (size_t)(sw + 6) * (sh + 6);
    b->sw = sw; b->sh = sh;
    b->metric = (float *)calloc(n1 * 4, sizeof(float));
    b->strength = (float *)calloc(n1 * 4, sizeof(float));
    b->flags = (uint16_t *)calloc(n3, sizeof(uint16_t));
    for (int i = 0; i < 256; ++i) b->unorm[i] = (float)i / 255.0f;
    if (!b->metric || !b->strength || !b->flags) { upscale_sfx_free(b); return 0; }
    return 1;
}

void upscale_sfx_free(SfxBuffers *b)
{
    free(b->metric); free(b->strength); free(b->flags);
    b->metric = b->strength = NULL;
    b->flags = NULL;
}

/* texel (x, y) of a 1-texel padded float4 buffer */
static inline const float *t1(const float *buf, int sw, int x, int y)
{
    return buf + ((size_t)(y + 1) * (sw + 2) + (x + 1)) * 4;
}

static inline V4 ld(const float *buf, int sw, int x, int y)
{
    const float *p = t1(buf, sw, x, y);
    V4 v = { p[0], p[1], p[2], p[3] };
    return v;
}

/* Clamp-to-edge padding of row y of a buffer with pad p (texel size n
 * elements): side pads of row y, then the whole padded row copied into the
 * p rows above (y == 0) or below (y == sh - 1). Only the slice that owns row
 * y writes these cells. */
#define PAD_ROW(T, buf, sw, sh, p, n, y) do {         const size_t pitch_ = (size_t)((sw) + 2 * (p)) * (n);         T *row_ = (buf) + (size_t)((y) + (p)) * pitch_;         for (int q_ = 0; q_ < (p); ++q_)             for (int e_ = 0; e_ < (n); ++e_) {                 row_[(size_t)q_ * (n) + e_] = row_[(size_t)(p) * (n) + e_];                 row_[pitch_ - (size_t)(q_ + 1) * (n) + e_] = row_[pitch_ - (size_t)((p) + 1) * (n) + e_];             }         if ((y) == 0)             for (int q_ = 1; q_ <= (p); ++q_) memcpy(row_ - (size_t)q_ * pitch_, row_, pitch_ * sizeof(T));         if ((y) == (sh) - 1)             for (int q_ = 1; q_ <= (p); ++q_) memcpy(row_ + (size_t)q_ * pitch_, row_, pitch_ * sizeof(T));     } while (0)

static int clampi(int v, int hi) { return v < 0 ? 0 : v > hi ? hi : v; }

/* ---- pass 0: metric -------------------------------------------------- */

typedef struct C3 { float r, g, b; } C3;

static inline C3 tex_rgb(const float *unorm, const uint32_t *src, int ss, int sw, int sh, int x, int y)
{
    const uint32_t p = src[(size_t)clampi(y, sh - 1) * ss + clampi(x, sw - 1)];
    C3 c = { unorm[(p >> 16) & 255], unorm[(p >> 8) & 255], unorm[p & 255] };
    return c;
}

/* Reference: http://www.compuphase.com/cmetric.htm */
static inline float dist(C3 A, C3 B)
{
    const float r = 0.5f * (A.r + B.r);
    const float dr = A.r - B.r, dg = A.g - B.g, db = A.b - B.b;
    const float cr = 2 + r, cg = 4, cb = 3 - r;
    return sqrtf((cr * dr) * dr + (cg * dg) * dg + (cb * db) * db) / 3;
}

void upscale_sfx_pass0(SfxBuffers *b, const uint32_t *src, int ss, int y0, int y1)
{
    const int sw = b->sw, sh = b->sh;
    /*	grid		metric
     *	A B C		x y z
     *	  E F		  o w
     */
    for (int y = y0; y < y1; ++y) {
        C3 A = tex_rgb(b->unorm, src, ss, sw, sh, -1, y - 1), B = tex_rgb(b->unorm, src, ss, sw, sh, 0, y - 1);
        C3 E = tex_rgb(b->unorm, src, ss, sw, sh, 0, y);
        float *out = b->metric + ((size_t)(y + 1) * (sw + 2) + 1) * 4;
        for (int x = 0; x < sw; ++x, out += 4) {
            const C3 C = tex_rgb(b->unorm, src, ss, sw, sh, x + 1, y - 1);
            const C3 F = tex_rgb(b->unorm, src, ss, sw, sh, x + 1, y);
            out[0] = dist(E, A);
            out[1] = dist(E, B);
            out[2] = dist(E, C);
            out[3] = dist(E, F);
            A = B; B = C; E = F;
        }
        PAD_ROW(float, b->metric, sw, b->sh, 1, 4, y);
    }
}

/* ---- pass 1: corner strength ------------------------------------------ */

static inline float minf(float a, float b) { return b < a ? b : a; }
static inline float maxf(float a, float b) { return a < b ? b : a; }

static inline float str(float d, float ax, float ay, float bx, float by)
{
    const float diff = ax - ay;
    const float wght1 = maxf(SFX_CLR - d, 0) / SFX_CLR;
    const float wght2 = minf(maxf((1 - d) + (minf(ax, bx) + ax > minf(ay, by) + ay ? diff : -diff), 0.0f), 1.0f);
    return (SFX_SAA == 1.0f || 2.0f * d < ax + ay) ? (wght1 * wght2) * (ax * ay) : 0.0f;
}

void upscale_sfx_pass1(SfxBuffers *b, int y0, int y1)
{
    const int sw = b->sw;
    const float *m = b->metric;
    /*	grid		metric		pattern
     *	A B		x y z		x y
     *	D E F		  o w		w z
     *	G H I
     */
    for (int y = y0; y < y1; ++y) {
        float *out = b->strength + ((size_t)(y + 1) * (sw + 2) + 1) * 4;
        for (int x = 0; x < sw; ++x, out += 4) {
            const V4 A = ld(m, sw, x - 1, y - 1), B = ld(m, sw, x, y - 1);
            const V4 D = ld(m, sw, x - 1, y), E = ld(m, sw, x, y), F = ld(m, sw, x + 1, y);
            const V4 G = ld(m, sw, x - 1, y + 1), H = ld(m, sw, x, y + 1), I = ld(m, sw, x + 1, y + 1);
            out[0] = str(D.z, D.w, E.y, A.w, D.y);
            out[1] = str(F.x, E.w, E.y, B.w, F.y);
            out[2] = str(H.z, E.w, H.y, H.w, I.y);
            out[3] = str(H.x, D.w, H.y, G.w, G.y);
        }
        PAD_ROW(float, b->strength, sw, b->sh, 1, 4, y);
    }
}

/* ---- pass 2: junctions, edges and orientation -------------------------- */

static inline float comp(V4 v, int i)
{
    return i == 0 ? v.x : i == 1 ? v.y : i == 2 ? v.z : v.w;
}

/* One junction of four texels P0 (top-left) .. P3 (bottom-left, clockwise);
 * texel Pi meets it with its corner ci = (i + 2) & 3. Gives jS and
 *   j = min(GE(jD, 0) * (LEQ(jD.yzwx, 0) * LEQ(jD.wxyz, 0)
 *                        + GE(jD + jD.zwxy, jD.yzwx + jD.wxyz)), 1)
 * with jD = dom(...) exactly as the shader builds jSx/jDx .. jSw/jDw. */
typedef struct Junc { float jS[4]; int j[4]; } Junc;

static inline void junction(V4 P0, V4 P1, V4 P2, V4 P3, float jS[4], int j[4])
{
    const V4 P[4] = { P0, P1, P2, P3 };
    float jD[4];
    for (int i = 0; i < 4; ++i) {
        const int c = (i + 2) & 3;
        jS[i] = comp(P[i], c);
        jD[i] = 2 * comp(P[i], c) - (comp(P[i], (c + 3) & 3) + comp(P[i], (c + 1) & 3));
    }
    for (int i = 0; i < 4; ++i) {
        const float a = jD[(i + 1) & 3], c = jD[(i + 3) & 3];
        j[i] = jD[i] > 0 && ((a <= 0 && c <= 0) || jD[i] + jD[(i + 2) & 3] > a + c);
    }
}

/* res component of the texel sitting at position p of its junction */
static inline int inject(const float jS[4], const int j[4], int p)
{
    const int pm = (p + 3) & 3, pp = (p + 1) & 3, po = (p + 2) & 3;
    return j[p] || (!j[pm] && !j[pp] && jS[p] > 0 && (j[po] || jS[p] + jS[po] > jS[pm] + jS[pp]));
}

/* necessary but not sufficient junction condition for orthogonal edges */
static inline int clear(float crnx, float crny, float ax, float ay, float bx, float by)
{
    return crnx >= maxf(minf(ax, ay), minf(bx, by)) && crny >= maxf(minf(ax, by), minf(bx, ay));
}

/* Junction at the top-left corner of texel (x, y): texels (x-1, y-1),
 * (x, y-1), (x, y), (x-1, y). Texel E's jx/jy/jz/jw are the junctions at
 * (x, y), (x+1, y), (x+1, y+1), (x, y+1); each is computed once per row pair
 * here and shared by the four texels around it (same values as computing
 * them per texel like the shader). */
static inline void junction_at(const float *s, int sw, int x, int y, Junc *out)
{
    junction(ld(s, sw, x - 1, y - 1), ld(s, sw, x, y - 1), ld(s, sw, x, y), ld(s, sw, x - 1, y),
             out->jS, out->j);
}

#define SFX_TILE 256

void upscale_sfx_pass2(SfxBuffers *b, int y0, int y1)
{
    const int sw = b->sw;
    const float *m = b->metric, *s = b->strength;
    Junc jrow[2][SFX_TILE + 1];
    /*	grid		metric		pattern
     *	A B C		x y z		x y
     *	D E F		  o w		w z
     *	G H I
     */
    for (int x0 = 0; x0 < sw; x0 += SFX_TILE) {
        const int tw = sw - x0 < SFX_TILE ? sw - x0 : SFX_TILE;
        Junc *top = jrow[0], *bot = jrow[1];
        for (int i = 0; i <= tw; ++i) junction_at(s, sw, x0 + i, y0, &top[i]);
        for (int y = y0; y < y1; ++y) {
            uint16_t *out = b->flags + (size_t)(y + 3) * (sw + 6) + 3;
            for (int i = 0; i <= tw; ++i) junction_at(s, sw, x0 + i, y + 1, &bot[i]);
            for (int x = x0; x < x0 + tw; ++x) {
                const V4 A = ld(m, sw, x - 1, y - 1), B = ld(m, sw, x, y - 1);
                const V4 D = ld(m, sw, x - 1, y), E = ld(m, sw, x, y), F = ld(m, sw, x + 1, y);
                const V4 G = ld(m, sw, x - 1, y + 1), H = ld(m, sw, x, y + 1), I = ld(m, sw, x + 1, y + 1);

                /* strength & dominance junctions, majority vote */
                const float *jSx = top[x - x0].jS, *jSy = top[x - x0 + 1].jS;
                const float *jSz = bot[x - x0 + 1].jS, *jSw = bot[x - x0].jS;
                const int *jx = top[x - x0].j, *jy = top[x - x0 + 1].j;
                const int *jz = bot[x - x0 + 1].j, *jw = bot[x - x0].j;

                /* inject strength without creating new contradictions */
                int r0[4], res[4];
                r0[0] = inject(jSx, jx, 2);
                r0[1] = inject(jSy, jy, 3);
                r0[2] = inject(jSz, jz, 0);
                r0[3] = inject(jSw, jw, 1);

                /* single pixel & end of line detection */
                const int own[4] = { jx[2], jy[3], jz[0], jw[1] };
                for (int i = 0; i < 4; ++i)
                    res[i] = r0[i] && (own[i] || !(r0[(i + 3) & 3] && r0[(i + 1) & 3]));

                int clr[4];
                clr[0] = clear(D.z, E.x, D.w, E.y, A.w, D.y);
                clr[1] = clear(F.x, E.z, E.w, E.y, B.w, F.y);
                clr[2] = clear(H.z, I.x, E.w, H.y, H.w, I.y);
                clr[3] = clear(H.x, G.z, D.w, H.y, G.w, G.y);

                const float h[4] = { minf(D.w, A.w), minf(E.w, B.w), minf(E.w, H.w), minf(D.w, G.w) };
                const float v[4] = { minf(E.y, D.y), minf(E.y, F.y), minf(H.y, I.y), minf(H.y, G.y) };
                const float ho[4] = { D.w, E.w, E.w, D.w }, vo[4] = { E.y, E.y, H.y, H.y };

                /* (res + 2 * hori + 4 * vert + 8 * orien) per component, as bit fields */
                unsigned f = 0;
                for (int i = 0; i < 4; ++i) {
                    const int orien = h[i] + ho[i] > v[i] + vo[i];   /* orientation */
                    const int hori = h[i] < v[i] && clr[i];          /* horizontal edges */
                    const int vert = h[i] > v[i] && clr[i];          /* vertical edges */
                    f |= (unsigned)res[i] << i | (unsigned)hori << (4 + i)
                       | (unsigned)vert << (8 + i) | (unsigned)orien << (12 + i);
                }
                out[x] = (uint16_t)f;
            }
            Junc *t = top; top = bot; bot = t;
        }
    }
    for (int y = y0; y < y1; ++y) PAD_ROW(uint16_t, b->flags, sw, b->sh, 3, 1, y);
}

/* ---- passes 3 + 4: edge levels, sub-pixel selection, output ------------ */

/* pass-2 field q of a texel: 0 corners, 1 horizontal, 2 vertical, 3 orientation
 * (loadCorn / loadHori / loadVert / loadOr) */
static inline B4 field(unsigned f, int q)
{
    const unsigned v = f >> (4 * q);
    B4 r = { (int)(v & 1), (int)((v >> 1) & 1), (int)((v >> 2) & 1), (int)((v >> 3) & 1) };
    return r;
}

void upscale_sfx_pass34(const SfxBuffers *b, const uint32_t *src, int ss,
                        uint32_t *dst, int ds, int y0, int y1)
{
    /* output coordinate - 0 = E, 1 = D, 2 = D0, 3 = F, 4 = F0, 5 = B, 6 = B0, 7 = H, 8 = H0 */
    static const signed char OX[9] = { 0, -1, -2, 1, 2, 0, 0, 0, 0 };
    static const signed char OY[9] = { 0, 0, 0, 0, 0, -1, -2, 1, 2 };
    const int sw = b->sw, sh = b->sh, fs = sw + 6;
    /*	grid		corners		mids
     *	  B		x   y	  	  x
     *	D E F				w   y
     *	  H		w   z	  	  z
     */
    for (int y = y0; y < y1; ++y) {
        const uint16_t *row = b->flags + (size_t)(y + 3) * fs + 3;
        uint32_t *o = dst + (size_t)y * 3 * ds;
        for (int x = 0; x < sw; ++x, o += 3) {
            const uint16_t *p = row + x;
            const unsigned e = p[0];
            if ((e & 0x0FFFu) == 0) {
                /* every lvl/mid term below needs a corner, horizontal or
                 * vertical bit of E (Ec/Eh/Ev), so all nine sub-pixels are 0 = E */
                const uint32_t c = src[(size_t)y * ss + x] & 0x00FFFFFFu;
                for (int r = 0; r < 3; ++r) o[(size_t)r * ds] = o[(size_t)r * ds + 1] = o[(size_t)r * ds + 2] = c;
                continue;
            }
            const unsigned d = p[-1], d0 = p[-2], d1 = p[-3], f = p[1], f0 = p[2], f1 = p[3];
            const unsigned bb = p[-fs], b0 = p[-2 * fs], b1 = p[-3 * fs];
            const unsigned hh = p[fs], h0 = p[2 * fs], h1 = p[3 * fs];

            /* extract data */
            const B4 Ec = field(e, 0), Eh = field(e, 1), Ev = field(e, 2), Eo = field(e, 3);
            const B4 Dc = field(d, 0), Dh = field(d, 1), Do = field(d, 3), D0c = field(d0, 0), D0h = field(d0, 1), D1h = field(d1, 1);
            const B4 Fc = field(f, 0), Fh = field(f, 1), Fo = field(f, 3), F0c = field(f0, 0), F0h = field(f0, 1), F1h = field(f1, 1);
            const B4 Bc = field(bb, 0), Bv = field(bb, 2), Bo = field(bb, 3), B0c = field(b0, 0), B0v = field(b0, 2), B1v = field(b1, 2);
            const B4 Hc = field(hh, 0), Hv = field(hh, 2), Ho = field(hh, 3), H0c = field(h0, 0), H0v = field(h0, 2), H1v = field(h1, 2);

            /* lvl1 corners (hori, vert) */
            const int lvl1x = Ec.x && (Dc.z || Bc.z || SFX_SCN == 1);
            const int lvl1y = Ec.y && (Fc.w || Bc.w || SFX_SCN == 1);
            const int lvl1z = Ec.z && (Fc.x || Hc.x || SFX_SCN == 1);
            const int lvl1w = Ec.w && (Dc.y || Hc.y || SFX_SCN == 1);

            /* lvl2 mid (left, right / up, down) */
            const B2 lvl2x = { (Ec.x && Eh.y) && Dc.z, (Ec.y && Eh.x) && Fc.w };
            const B2 lvl2y = { (Ec.y && Ev.z) && Bc.w, (Ec.z && Ev.y) && Hc.x };
            const B2 lvl2z = { (Ec.w && Eh.z) && Dc.y, (Ec.z && Eh.w) && Fc.x };
            const B2 lvl2w = { (Ec.x && Ev.w) && Bc.z, (Ec.w && Ev.x) && Hc.y };

            /* lvl3 corners (hori, vert) */
            const B2 lvl3x = { lvl2x.y && (Dh.y && Dh.x) && Fh.z, lvl2w.y && (Bv.w && Bv.x) && Hv.z };
            const B2 lvl3y = { lvl2x.x && (Fh.x && Fh.y) && Dh.w, lvl2y.y && (Bv.z && Bv.y) && Hv.w };
            const B2 lvl3z = { lvl2z.x && (Fh.w && Fh.z) && Dh.x, lvl2y.x && (Hv.y && Hv.z) && Bv.x };
            const B2 lvl3w = { lvl2z.y && (Dh.z && Dh.w) && Fh.y, lvl2w.x && (Hv.x && Hv.w) && Bv.y };

            /* lvl4 corners (hori, vert) */
            const B2 lvl4x = { (Dc.x && Dh.y && Eh.x && Eh.y && Fh.x && Fh.y) && (D0c.z && D0h.w), (Bc.x && Bv.w && Ev.x && Ev.w && Hv.x && Hv.w) && (B0c.z && B0v.y) };
            const B2 lvl4y = { (Fc.y && Fh.x && Eh.y && Eh.x && Dh.y && Dh.x) && (F0c.w && F0h.z), (Bc.y && Bv.z && Ev.y && Ev.z && Hv.y && Hv.z) && (B0c.w && B0v.x) };
            const B2 lvl4z = { (Fc.z && Fh.w && Eh.z && Eh.w && Dh.z && Dh.w) && (F0c.x && F0h.y), (Hc.z && Hv.y && Ev.z && Ev.y && Bv.z && Bv.y) && (H0c.x && H0v.w) };
            const B2 lvl4w = { (Dc.w && Dh.z && Eh.w && Eh.z && Fh.w && Fh.z) && (D0c.y && D0h.x), (Hc.w && Hv.x && Ev.w && Ev.x && Bv.w && Bv.x) && (H0c.y && H0v.z) };

            /* lvl5 mid (left, right / up, down) */
            const B2 lvl5x = { lvl4x.x && (F0h.x && F0h.y) && (D1h.z && D1h.w), lvl4y.x && (D0h.y && D0h.x) && (F1h.w && F1h.z) };
            const B2 lvl5y = { lvl4y.y && (H0v.y && H0v.z) && (B1v.w && B1v.x), lvl4z.y && (B0v.z && B0v.y) && (H1v.x && H1v.w) };
            const B2 lvl5z = { lvl4w.x && (F0h.w && F0h.z) && (D1h.y && D1h.x), lvl4z.x && (D0h.z && D0h.w) && (F1h.x && F1h.y) };
            const B2 lvl5w = { lvl4x.y && (H0v.x && H0v.w) && (B1v.z && B1v.y), lvl4w.y && (B0v.w && B0v.x) && (H1v.y && H1v.z) };

            /* lvl6 corners (hori, vert) */
            const B2 lvl6x = { lvl5x.y && (D1h.y && D1h.x), lvl5w.y && (B1v.w && B1v.x) };
            const B2 lvl6y = { lvl5x.x && (F1h.x && F1h.y), lvl5y.y && (B1v.z && B1v.y) };
            const B2 lvl6z = { lvl5z.x && (F1h.w && F1h.z), lvl5y.x && (H1v.y && H1v.z) };
            const B2 lvl6w = { lvl5z.y && (D1h.z && D1h.w), lvl5w.x && (H1v.x && H1v.w) };

            /* subpixels - 0 = E, 1 = D, 2 = D0, 3 = F, 4 = F0, 5 = B, 6 = B0, 7 = H, 8 = H0
             * (the shader's "a && b || c && d" with explicit parentheses) */
            B4 crn;
            crn.x = ((lvl1x && Eo.x) || (lvl3x.x && Eo.y) || (lvl4x.x && Do.x) || (lvl6x.x && Fo.y)) ? 5 : (lvl1x || (lvl3x.y && !Eo.w) || (lvl4x.y && !Bo.x) || (lvl6x.y && !Ho.w)) ? 1 : lvl3x.x ? 3 : lvl3x.y ? 7 : lvl4x.x ? 2 : lvl4x.y ? 6 : lvl6x.x ? 4 : lvl6x.y ? 8 : 0;
            crn.y = ((lvl1y && Eo.y) || (lvl3y.x && Eo.x) || (lvl4y.x && Fo.y) || (lvl6y.x && Do.x)) ? 5 : (lvl1y || (lvl3y.y && !Eo.z) || (lvl4y.y && !Bo.y) || (lvl6y.y && !Ho.z)) ? 3 : lvl3y.x ? 1 : lvl3y.y ? 7 : lvl4y.x ? 4 : lvl4y.y ? 6 : lvl6y.x ? 2 : lvl6y.y ? 8 : 0;
            crn.z = ((lvl1z && Eo.z) || (lvl3z.x && Eo.w) || (lvl4z.x && Fo.z) || (lvl6z.x && Do.w)) ? 7 : (lvl1z || (lvl3z.y && !Eo.y) || (lvl4z.y && !Ho.z) || (lvl6z.y && !Bo.y)) ? 3 : lvl3z.x ? 1 : lvl3z.y ? 5 : lvl4z.x ? 4 : lvl4z.y ? 8 : lvl6z.x ? 2 : lvl6z.y ? 6 : 0;
            crn.w = ((lvl1w && Eo.w) || (lvl3w.x && Eo.z) || (lvl4w.x && Do.w) || (lvl6w.x && Fo.z)) ? 7 : (lvl1w || (lvl3w.y && !Eo.x) || (lvl4w.y && !Ho.w) || (lvl6w.y && !Bo.x)) ? 1 : lvl3w.x ? 3 : lvl3w.y ? 5 : lvl4w.x ? 2 : lvl4w.y ? 8 : lvl6w.x ? 4 : lvl6w.y ? 6 : 0;

            B4 mid;
            mid.x = ((lvl2x.x &&  Eo.x) || (lvl2x.y &&  Eo.y) || (lvl5x.x &&  Do.x) || (lvl5x.y &&  Fo.y)) ? 5 : lvl2x.x ? 1 : lvl2x.y ? 3 : lvl5x.x ? 2 : lvl5x.y ? 4 : (Ec.x && Dc.z && Ec.y && Fc.w) ? ( Eo.x ?  Eo.y ? 5 : 3 : 1) : 0;
            mid.y = ((lvl2y.x && !Eo.y) || (lvl2y.y && !Eo.z) || (lvl5y.x && !Bo.y) || (lvl5y.y && !Ho.z)) ? 3 : lvl2y.x ? 5 : lvl2y.y ? 7 : lvl5y.x ? 6 : lvl5y.y ? 8 : (Ec.y && Bc.w && Ec.z && Hc.x) ? (!Eo.y ? !Eo.z ? 3 : 7 : 5) : 0;
            mid.z = ((lvl2z.x &&  Eo.w) || (lvl2z.y &&  Eo.z) || (lvl5z.x &&  Do.w) || (lvl5z.y &&  Fo.z)) ? 7 : lvl2z.x ? 1 : lvl2z.y ? 3 : lvl5z.x ? 2 : lvl5z.y ? 4 : (Ec.z && Fc.x && Ec.w && Dc.y) ? ( Eo.z ?  Eo.w ? 7 : 1 : 3) : 0;
            mid.w = ((lvl2w.x && !Eo.x) || (lvl2w.y && !Eo.w) || (lvl5w.x && !Bo.x) || (lvl5w.y && !Ho.w)) ? 1 : lvl2w.x ? 5 : lvl2w.y ? 7 : lvl5w.x ? 6 : lvl5w.y ? 8 : (Ec.w && Hc.y && Ec.x && Bc.z) ? (!Eo.w ? !Eo.x ? 1 : 5 : 7) : 0;

            /* pass 4: determine subpixel, fetch refpass at E + res */
            const int sp[9] = { crn.x, mid.x, crn.y, mid.w, 0, mid.y, crn.w, mid.z, crn.z };
            for (int q = 0; q < 9; ++q) {
                const int sx = clampi(x + OX[sp[q]], sw - 1), sy = clampi(y + OY[sp[q]], sh - 1);
                o[(size_t)(q / 3) * ds + q % 3] = src[(size_t)sy * ss + sx] & 0x00FFFFFFu;
            }
        }
    }
}

