/*
 * xBR level 2 (2x/3x/4x) for the remake's CPU upscaler (see upscale.c).
 *
 * Adapted in 2026 from FFmpeg libavfilter/vf_xbr.c:
 *
 * This file is part of FFmpeg.
 *
 * Copyright (c) 2011, 2012 Hyllian/Jararaca <sergiogdb@gmail.com>
 * Copyright (c) 2014 Arwa Arif <arwaarif1994@gmail.com>
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

/* XBR Filter is used for depixelization of image. This is based on Hyllian's
 * xBR shader.
 *
 * Kept verbatim from vf_xbr.c: the masks, ALPHA_BLEND_* macros, eq(), the
 * FILT2/FILT3/FILT4 macros, the per-factor corner calls and the body of
 * pixel_diff(). Changes made for this file:
 *   - no 16M-entry rgbtoyuv table: xbr_rgb_to_yuv() evaluates, for one
 *     pixel, the exact integer expression init() stores for it; values are
 *     cached in a 5-row window next to the pixels;
 *   - df(A, B) reads those cached values (variable Y<name> beside each pixel
 *     <name>), so pixel_diff() takes the two YUV words directly;
 *   - the source is walked in column tiles of rows [y0, y1) (several threads
 *     can fill disjoint row ranges); edge pixels are repeated exactly as the
 *     reference's sa0..sa4 / pprev / pnext clamping does;
 *   - source pixels are masked to 0x00RRGGBB.
 */
#include "upscale_impl.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#if defined(__GNUC__) || defined(__clang__)
/* the reference's FILT conditions mix && and || without parentheses */
#pragma GCC diagnostic ignored "-Wparentheses"
#endif

#define LB_MASK       0x00FEFEFE
#define RED_BLUE_MASK 0x00FF00FF
#define GREEN_MASK    0x0000FF00

/* The value init() stores in rgbtoyuv[] for pixel c (same integer steps). */
static inline uint32_t xbr_rgb_to_yuv(uint32_t c)
{
    const int r = (int)((c >> 16) & 255), g = (int)((c >> 8) & 255), b = (int)(c & 255);
    const int bg = b - g, rg = r - g;
    const uint32_t u = (uint32_t)((-169*rg + 500*bg)/1000) + 128;
    const uint32_t v = (uint32_t)(( 500*rg -  81*bg)/1000) + 128;
    int startg = -bg > -rg ? -bg : -rg;
    if (startg < 0) startg = 0;
    const uint32_t y = (uint32_t)(( 299*rg + 1000*startg + 114*bg)/1000) + (uint32_t)(g - startg);
    return (y << 16) + (u << 8) + v;
}

/* pixel_diff() of vf_xbr.c with the two table lookups already done */
static uint32_t pixel_diff(uint32_t yuv1, uint32_t yuv2)
{
#define YMASK 0xff0000
#define UMASK 0x00ff00
#define VMASK 0x0000ff
#define ABSDIFF(a,b) (abs((int)(a)-(int)(b)))

    return (ABSDIFF(yuv1 & YMASK, yuv2 & YMASK) >> 16) +
           (ABSDIFF(yuv1 & UMASK, yuv2 & UMASK) >>  8) +
            ABSDIFF(yuv1 & VMASK, yuv2 & VMASK);
}

#define ALPHA_BLEND_128_W(a, b) ((((a) & LB_MASK) >> 1) + (((b) & LB_MASK) >> 1))
#define ALPHA_BLEND_BASE(a, b, m, s) (  (RED_BLUE_MASK & (((a) & RED_BLUE_MASK) + (((((b) & RED_BLUE_MASK) - ((a) & RED_BLUE_MASK)) * (m)) >> (s)))) \
                                      | (GREEN_MASK    & (((a) & GREEN_MASK)    + (((((b) & GREEN_MASK)    - ((a) & GREEN_MASK))    * (m)) >> (s)))))
#define ALPHA_BLEND_32_W(a, b)  ALPHA_BLEND_BASE(a, b, 1, 3)
#define ALPHA_BLEND_64_W(a, b)  ALPHA_BLEND_BASE(a, b, 1, 2)
#define ALPHA_BLEND_192_W(a, b) ALPHA_BLEND_BASE(a, b, 3, 2)
#define ALPHA_BLEND_224_W(a, b) ALPHA_BLEND_BASE(a, b, 7, 3)

#define df(A, B) pixel_diff(Y##A, Y##B)
#define eq(A, B) (df(A, B) < 155)

#define FILT2(PE, PI, PH, PF, PG, PC, PD, PB, PA, G5, C4, G0, D0, C1, B1, F4, I4, H5, I5, A0, A1,   \
              N0, N1, N2, N3) do {                                                                  \
    if (PE != PH && PE != PF) {                                                                     \
        const unsigned e = df(PE,PC) + df(PE,PG) + df(PI,H5) + df(PI,F4) + (df(PH,PF)<<2);          \
        const unsigned i = df(PH,PD) + df(PH,I5) + df(PF,I4) + df(PF,PB) + (df(PE,PI)<<2);          \
        if (e <= i) {                                                                               \
            const unsigned px = df(PE,PF) <= df(PE,PH) ? PF : PH;                                   \
            if (e < i && (!eq(PF,PB) && !eq(PH,PD) || eq(PE,PI)                                     \
                          && (!eq(PF,I4) && !eq(PH,I5))                                             \
                          || eq(PE,PG) || eq(PE,PC))) {                                             \
                const unsigned ke = df(PF,PG);                                                      \
                const unsigned ki = df(PH,PC);                                                      \
                const int left    = ke<<1 <= ki && PE != PG && PD != PG;                            \
                const int up      = ke >= ki<<1 && PE != PC && PB != PC;                            \
                if (left && up) {                                                                   \
                    E[N3] = ALPHA_BLEND_224_W(E[N3], px);                                           \
                    E[N2] = ALPHA_BLEND_64_W( E[N2], px);                                           \
                    E[N1] = E[N2];                                                                  \
                } else if (left) {                                                                  \
                    E[N3] = ALPHA_BLEND_192_W(E[N3], px);                                           \
                    E[N2] = ALPHA_BLEND_64_W( E[N2], px);                                           \
                } else if (up) {                                                                    \
                    E[N3] = ALPHA_BLEND_192_W(E[N3], px);                                           \
                    E[N1] = ALPHA_BLEND_64_W( E[N1], px);                                           \
                } else { /* diagonal */                                                             \
                    E[N3] = ALPHA_BLEND_128_W(E[N3], px);                                           \
                }                                                                                   \
            } else {                                                                                \
                E[N3] = ALPHA_BLEND_128_W(E[N3], px);                                               \
            }                                                                                       \
        }                                                                                           \
    }                                                                                               \
} while (0)

#define FILT3(PE, PI, PH, PF, PG, PC, PD, PB, PA, G5, C4, G0, D0, C1, B1, F4, I4, H5, I5, A0, A1,   \
              N0, N1, N2, N3, N4, N5, N6, N7, N8) do {                                              \
    if (PE != PH && PE != PF) {                                                                     \
        const unsigned e = df(PE,PC) + df(PE,PG) + df(PI,H5) + df(PI,F4) + (df(PH,PF)<<2);          \
        const unsigned i = df(PH,PD) + df(PH,I5) + df(PF,I4) + df(PF,PB) + (df(PE,PI)<<2);          \
        if (e <= i) {                                                                               \
            const unsigned px = df(PE,PF) <= df(PE,PH) ? PF : PH;                                   \
            if (e < i && (!eq(PF,PB) && !eq(PF,PC) || !eq(PH,PD) && !eq(PH,PG) || eq(PE,PI)         \
                          && (!eq(PF,F4) && !eq(PF,I4) || !eq(PH,H5) && !eq(PH,I5))                 \
                          || eq(PE,PG) || eq(PE,PC))) {                                             \
                const unsigned ke = df(PF,PG);                                                      \
                const unsigned ki = df(PH,PC);                                                      \
                const int left    = ke<<1 <= ki && PE != PG && PD != PG;                            \
                const int up      = ke >= ki<<1 && PE != PC && PB != PC;                            \
                if (left && up) {                                                                   \
                    E[N7] = ALPHA_BLEND_192_W(E[N7], px);                                           \
                    E[N6] = ALPHA_BLEND_64_W( E[N6], px);                                           \
                    E[N5] = E[N7];                                                                  \
                    E[N2] = E[N6];                                                                  \
                    E[N8] = px;                                                                     \
                } else if (left) {                                                                  \
                    E[N7] = ALPHA_BLEND_192_W(E[N7], px);                                           \
                    E[N5] = ALPHA_BLEND_64_W( E[N5], px);                                           \
                    E[N6] = ALPHA_BLEND_64_W( E[N6], px);                                           \
                    E[N8] = px;                                                                     \
                } else if (up) {                                                                    \
                    E[N5] = ALPHA_BLEND_192_W(E[N5], px);                                           \
                    E[N7] = ALPHA_BLEND_64_W( E[N7], px);                                           \
                    E[N2] = ALPHA_BLEND_64_W( E[N2], px);                                           \
                    E[N8] = px;                                                                     \
                } else { /* diagonal */                                                             \
                    E[N8] = ALPHA_BLEND_224_W(E[N8], px);                                           \
                    E[N5] = ALPHA_BLEND_32_W( E[N5], px);                                           \
                    E[N7] = ALPHA_BLEND_32_W( E[N7], px);                                           \
                }                                                                                   \
            } else {                                                                                \
                E[N8] = ALPHA_BLEND_128_W(E[N8], px);                                               \
            }                                                                                       \
        }                                                                                           \
    }                                                                                               \
} while (0)

#define FILT4(PE, PI, PH, PF, PG, PC, PD, PB, PA, G5, C4, G0, D0, C1, B1, F4, I4, H5, I5, A0, A1,   \
              N15, N14, N11, N3, N7, N10, N13, N12, N9, N6, N2, N1, N5, N8, N4, N0) do {            \
    if (PE != PH && PE != PF) {                                                                     \
        const unsigned e = df(PE,PC) + df(PE,PG) + df(PI,H5) + df(PI,F4) + (df(PH,PF)<<2);          \
        const unsigned i = df(PH,PD) + df(PH,I5) + df(PF,I4) + df(PF,PB) + (df(PE,PI)<<2);          \
        if (e <= i) {                                                                               \
            const unsigned px = df(PE,PF) <= df(PE,PH) ? PF : PH;                                   \
            if (e < i && (!eq(PF,PB) && !eq(PH,PD) || eq(PE,PI)                                     \
                          && (!eq(PF,I4) && !eq(PH,I5))                                             \
                          || eq(PE,PG) || eq(PE,PC))) {                                             \
                const unsigned ke = df(PF,PG);                                                      \
                const unsigned ki = df(PH,PC);                                                      \
                const int left    = ke<<1 <= ki && PE != PG && PD != PG;                            \
                const int up      = ke >= ki<<1 && PE != PC && PB != PC;                            \
                if (left && up) {                                                                   \
                    E[N13] = ALPHA_BLEND_192_W(E[N13], px);                                         \
                    E[N12] = ALPHA_BLEND_64_W( E[N12], px);                                         \
                    E[N15] = E[N14] = E[N11] = px;                                                  \
                    E[N10] = E[N3]  = E[N12];                                                       \
                    E[N7]  = E[N13];                                                                \
                } else if (left) {                                                                  \
                    E[N11] = ALPHA_BLEND_192_W(E[N11], px);                                         \
                    E[N13] = ALPHA_BLEND_192_W(E[N13], px);                                         \
                    E[N10] = ALPHA_BLEND_64_W( E[N10], px);                                         \
                    E[N12] = ALPHA_BLEND_64_W( E[N12], px);                                         \
                    E[N14] = px;                                                                    \
                    E[N15] = px;                                                                    \
                } else if (up) {                                                                    \
                    E[N14] = ALPHA_BLEND_192_W(E[N14], px);                                         \
                    E[N7 ] = ALPHA_BLEND_192_W(E[N7 ], px);                                         \
                    E[N10] = ALPHA_BLEND_64_W( E[N10], px);                                         \
                    E[N3 ] = ALPHA_BLEND_64_W( E[N3 ], px);                                         \
                    E[N11] = px;                                                                    \
                    E[N15] = px;                                                                    \
                } else { /* diagonal */                                                             \
                    E[N11] = ALPHA_BLEND_128_W(E[N11], px);                                         \
                    E[N14] = ALPHA_BLEND_128_W(E[N14], px);                                         \
                    E[N15] = px;                                                                    \
                }                                                                                   \
            } else {                                                                                \
                E[N15] = ALPHA_BLEND_128_W(E[N15], px);                                             \
            }                                                                                       \
        }                                                                                           \
    }                                                                                               \
} while (0)

/* ---- 5-row window ------------------------------------------------------- */

#define XBR_TILE 128

typedef struct XbrWin {
    uint32_t pix[5][XBR_TILE + 4], yuv[5][XBR_TILE + 4];
    uint32_t *pr[5], *yr[5];     /* rows y-2 .. y+2 */
} XbrWin;

static int xbr_clamp(int v, int hi) { return v < 0 ? 0 : v > hi ? hi : v; }

/* Source row y (clamped), columns x0-2 .. x0+tw+1 (clamped). */
static void xbr_load(uint32_t *pix, uint32_t *yuv, const uint32_t *src, int ss, int sw, int sh,
                     int y, int x0, int tw)
{
    const uint32_t *s = src + (size_t)xbr_clamp(y, sh - 1) * ss;
    uint32_t last = 0, last_yuv = xbr_rgb_to_yuv(0);
    for (int j = 0; j < tw + 4; ++j) {
        const uint32_t p = s[xbr_clamp(x0 + j - 2, sw - 1)] & 0x00FFFFFFu;
        if (p != last) { last = p; last_yuv = xbr_rgb_to_yuv(p); }
        pix[j] = p;
        yuv[j] = last_yuv;
    }
}

static void xbr_win_row(XbrWin *t, const uint32_t *src, int ss, int sw, int sh,
                        int y, int y0, int x0, int tw)
{
    if (y == y0) {
        for (int q = 0; q < 5; ++q) {
            t->pr[q] = t->pix[q]; t->yr[q] = t->yuv[q];
            xbr_load(t->pr[q], t->yr[q], src, ss, sw, sh, y - 2 + q, x0, tw);
        }
        return;
    }
    uint32_t *p = t->pr[0], *v = t->yr[0];
    for (int q = 0; q < 4; ++q) { t->pr[q] = t->pr[q + 1]; t->yr[q] = t->yr[q + 1]; }
    t->pr[4] = p; t->yr[4] = v;
    xbr_load(p, v, src, ss, sw, sh, y + 2, x0, tw);
}

/* xbr_filter() of vf_xbr.c for source rows [y0, y1), output stride ds. */
static inline void xbr_filter(int n, const uint32_t *src, int ss, int sw, int sh,
                              uint32_t *dst, int ds, int y0, int y1)
{
    XbrWin t;
    const int nl = ds;
    const int nl1 = nl + nl;
    const int nl2 = nl1 + nl;
    (void)nl2;
    for (int x0 = 0; x0 < sw; x0 += XBR_TILE) {
        const int tw = sw - x0 < XBR_TILE ? sw - x0 : XBR_TILE;
        for (int y = y0; y < y1; ++y) {
            xbr_win_row(&t, src, ss, sw, sh, y, y0, x0, tw);
            const uint32_t *sa1 = t.pr[1], *sa2 = t.pr[2], *sa3 = t.pr[3];
            const uint32_t *ya0 = t.yr[0], *ya1 = t.yr[1], *ya2 = t.yr[2], *ya3 = t.yr[3], *ya4 = t.yr[4];
            uint32_t *E = dst + (size_t)y * n * ds + (size_t)x0 * n;
            for (int x = 2; x < tw + 2; ++x, E += n) {
                /* columns x-2 .. x+2 of the window are the reference's clamped
                 * pprev2, pprev, centre, pnext, pnext2; the outer pixels only
                 * enter df(), so only their YUV is kept */
                const uint32_t YB1 = ya0[x];
                const uint32_t PB = sa1[x], YPB = ya1[x];
                const uint32_t PE = sa2[x], YPE = ya2[x];
                const uint32_t PH = sa3[x], YPH = ya3[x];
                const uint32_t YH5 = ya4[x];

                const uint32_t YA1 = ya0[x - 1];
                const uint32_t PA = sa1[x - 1], YPA = ya1[x - 1];
                const uint32_t PD = sa2[x - 1], YPD = ya2[x - 1];
                const uint32_t PG = sa3[x - 1], YPG = ya3[x - 1];
                const uint32_t YG5 = ya4[x - 1];

                const uint32_t YA0 = ya1[x - 2];
                const uint32_t YD0 = ya2[x - 2];
                const uint32_t YG0 = ya3[x - 2];

                const uint32_t YC1 = ya0[x + 1];
                const uint32_t PC = sa1[x + 1], YPC = ya1[x + 1];
                const uint32_t PF = sa2[x + 1], YPF = ya2[x + 1];
                const uint32_t PI = sa3[x + 1], YPI = ya3[x + 1];
                const uint32_t YI5 = ya4[x + 1];

                const uint32_t YC4 = ya1[x + 2];
                const uint32_t YF4 = ya2[x + 2];
                const uint32_t YI4 = ya3[x + 2];

                if (n == 2) {
                    E[0]  = E[1]      =     // 0, 1
                    E[nl] = E[nl + 1] = PE; // 2, 3

                    FILT2(PE, PI, PH, PF, PG, PC, PD, PB, PA, G5, C4, G0, D0, C1, B1, F4, I4, H5, I5, A0, A1, 0, 1, nl, nl+1);
                    FILT2(PE, PC, PF, PB, PI, PA, PH, PD, PG, I4, A1, I5, H5, A0, D0, B1, C1, F4, C4, G5, G0, nl, 0, nl+1, 1);
                    FILT2(PE, PA, PB, PD, PC, PG, PF, PH, PI, C1, G0, C4, F4, G5, H5, D0, A0, B1, A1, I4, I5, nl+1, nl, 1, 0);
                    FILT2(PE, PG, PD, PH, PA, PI, PB, PF, PC, A0, I5, A1, B1, I4, F4, H5, G5, D0, G0, C1, C4, 1, nl+1, 0, nl);
                } else if (n == 3) {
                    E[0]   = E[1]     = E[2]     =     // 0, 1, 2
                    E[nl]  = E[nl+1]  = E[nl+2]  =     // 3, 4, 5
                    E[nl1] = E[nl1+1] = E[nl1+2] = PE; // 6, 7, 8

                    FILT3(PE, PI, PH, PF, PG, PC, PD, PB, PA, G5, C4, G0, D0, C1, B1, F4, I4, H5, I5, A0, A1, 0, 1, 2, nl, nl+1, nl+2, nl1, nl1+1, nl1+2);
                    FILT3(PE, PC, PF, PB, PI, PA, PH, PD, PG, I4, A1, I5, H5, A0, D0, B1, C1, F4, C4, G5, G0, nl1, nl, 0, nl1+1, nl+1, 1, nl1+2, nl+2, 2);
                    FILT3(PE, PA, PB, PD, PC, PG, PF, PH, PI, C1, G0, C4, F4, G5, H5, D0, A0, B1, A1, I4, I5, nl1+2, nl1+1, nl1, nl+2, nl+1, nl, 2, 1, 0);
                    FILT3(PE, PG, PD, PH, PA, PI, PB, PF, PC, A0, I5, A1, B1, I4, F4, H5, G5, D0, G0, C1, C4, 2, nl+2, nl1+2, 1, nl+1, nl1+1, 0, nl, nl1);
                } else if (n == 4) {
                    E[0]   = E[1]     = E[2]     = E[3]     =     //  0,  1,  2,  3
                    E[nl]  = E[nl+1]  = E[nl+2]  = E[nl+3]  =     //  4,  5,  6,  7
                    E[nl1] = E[nl1+1] = E[nl1+2] = E[nl1+3] =     //  8,  9, 10, 11
                    E[nl2] = E[nl2+1] = E[nl2+2] = E[nl2+3] = PE; // 12, 13, 14, 15

                    FILT4(PE, PI, PH, PF, PG, PC, PD, PB, PA, G5, C4, G0, D0, C1, B1, F4, I4, H5, I5, A0, A1, nl2+3, nl2+2, nl1+3, 3, nl+3, nl1+2, nl2+1, nl2, nl1+1, nl+2, 2, 1, nl+1, nl1, nl, 0);
                    FILT4(PE, PC, PF, PB, PI, PA, PH, PD, PG, I4, A1, I5, H5, A0, D0, B1, C1, F4, C4, G5, G0, 3, nl+3, 2, 0, 1, nl+2, nl1+3, nl2+3, nl1+2, nl+1, nl, nl1, nl1+1, nl2+2, nl2+1, nl2);
                    FILT4(PE, PA, PB, PD, PC, PG, PF, PH, PI, C1, G0, C4, F4, G5, H5, D0, A0, B1, A1, I4, I5, 0, 1, nl, nl2, nl1, nl+1, 2, 3, nl+2, nl1+1, nl2+1, nl2+2, nl1+2, nl+3, nl1+3, nl2+3);
                    FILT4(PE, PG, PD, PH, PA, PI, PB, PF, PC, A0, I5, A1, B1, I4, F4, H5, G5, D0, G0, C1, C4, nl2, nl1, nl2+1, nl2+3, nl2+2, nl1+1, nl, 0, nl+1, nl1+2, nl1+3, nl+3, nl+2, 1, 2, 3);
                }
            }
        }
    }
}

void upscale_xbr_rows(int k, const uint32_t *src, int ss, int sw, int sh,
                      uint32_t *dst, int ds, int y0, int y1)
{
    if (k == 2) xbr_filter(2, src, ss, sw, sh, dst, ds, y0, y1);
    else if (k == 3) xbr_filter(3, src, ss, sw, sh, dst, ds, y0, y1);
    else xbr_filter(4, src, ss, sw, sh, dst, ds, y0, y1);
}
