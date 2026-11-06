/*
 * Copyright (C) 2003 Maxim Stepin ( maxst@hiend3d.com )
 *
 * Copyright (C) 2010 Cameron Zemek ( grom@zeminvaders.net)
 * Copyright (C) 2011 Francois Gannaz <mytskine@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/* hq2x / hq3x / hq4x for the remake's CPU upscaler (see upscale.c).
 *
 * Adapted in 2026 from grom358/hqx (common.h, init.c, hq2x.c, hq3x.c, hq4x.c),
 * the C library implementation of Maxim Stepin's hqx algorithm. Kept verbatim:
 * the YUV formula of hqxInit(), yuv_diff() and its thresholds, Interpolate_2/3
 * and Interp1..Interp10, every PIXELxx_yy macro and every case of the three
 * 256-pattern switches (the switch bodies are only re-wrapped, token for token).
 * Changes made for this file:
 *   - no 16M-entry RGBtoYUV table: rgb_to_yuv() evaluates the hqxInit()
 *     formula for each loaded source pixel, kept in a 3-row window next to the
 *     pixels; the negative U/V terms are truncated through int32_t, which is
 *     what the reference's direct double -> uint32_t conversion does on x86;
 *   - Diff(w[a], w[b]) in the switches is written DIFF(a, b) and reads that
 *     cached YUV (Diff() of the reference converts the same two pixels);
 *   - abs() in yuv_diff() takes an explicit (int) cast of the same value;
 *   - the frame is walked in column tiles of source rows [y0, y1) so several
 *     threads can fill disjoint row ranges; edge pixels are repeated exactly
 *     like the reference's prevline/nextline and i>0/i<Xres-1 tests;
 *   - source pixels are masked to 0x00RRGGBB, so every output alpha is 0.
 */
#include "upscale_impl.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

/* ---- from common.h ------------------------------------------------------ */

#define MASK_2     0x0000FF00
#define MASK_13    0x00FF00FF
#define MASK_RGB   0x00FFFFFF
#define MASK_ALPHA 0xFF000000

#define Ymask 0x00FF0000
#define Umask 0x0000FF00
#define Vmask 0x000000FF
#define trY   0x00300000
#define trU   0x00000700
#define trV   0x00000006

/* hqxInit() formula of init.c, one pixel at a time. */
static inline uint32_t rgb_to_yuv(uint32_t c)
{
    uint32_t r, g, b, y, u, v;
    r = (c & 0xFF0000) >> 16;
    g = (c & 0x00FF00) >> 8;
    b = c & 0x0000FF;
    y = (uint32_t)(0.299*r + 0.587*g + 0.114*b);
    u = (uint32_t)(int32_t)(-0.169*r - 0.331*g + 0.5*b) + 128;
    v = (uint32_t)(int32_t)(0.5*r - 0.419*g - 0.081*b) + 128;
    return (y << 16) + (u << 8) + v;
}

/* Test if there is difference in color */
static inline int yuv_diff(uint32_t yuv1, uint32_t yuv2) {
    return (( abs((int)((yuv1 & Ymask) - (yuv2 & Ymask))) > trY ) ||
            ( abs((int)((yuv1 & Umask) - (yuv2 & Umask))) > trU ) ||
            ( abs((int)((yuv1 & Vmask) - (yuv2 & Vmask))) > trV ) );
}

/* Interpolate functions */
static inline uint32_t Interpolate_2(uint32_t c1, int w1, uint32_t c2, int w2, int s)
{
    if (c1 == c2) {
        return c1;
    }
    return
        (((((c1 & MASK_ALPHA) >> 24) * w1 + ((c2 & MASK_ALPHA) >> 24) * w2) << (24-s)) & MASK_ALPHA) +
        ((((c1 & MASK_2) * w1 + (c2 & MASK_2) * w2) >> s) & MASK_2)	+
        ((((c1 & MASK_13) * w1 + (c2 & MASK_13) * w2) >> s) & MASK_13);
}

static inline uint32_t Interpolate_3(uint32_t c1, int w1, uint32_t c2, int w2, uint32_t c3, int w3, int s)
{
    return
        (((((c1 & MASK_ALPHA) >> 24) * w1 + ((c2 & MASK_ALPHA) >> 24) * w2 + ((c3 & MASK_ALPHA) >> 24) * w3) << (24-s)) & MASK_ALPHA) +
        ((((c1 & MASK_2) * w1 + (c2 & MASK_2) * w2 + (c3 & MASK_2) * w3) >> s) & MASK_2) +
        ((((c1 & MASK_13) * w1 + (c2 & MASK_13) * w2 + (c3 & MASK_13) * w3) >> s) & MASK_13);
}

static inline void Interp1(uint32_t * pc, uint32_t c1, uint32_t c2)
{
    //*pc = (c1*3+c2) >> 2;
    *pc = Interpolate_2(c1, 3, c2, 1, 2);
}

static inline void Interp2(uint32_t * pc, uint32_t c1, uint32_t c2, uint32_t c3)
{
    //*pc = (c1*2+c2+c3) >> 2;
    *pc = Interpolate_3(c1, 2, c2, 1, c3, 1, 2);
}

static inline void Interp3(uint32_t * pc, uint32_t c1, uint32_t c2)
{
    //*pc = (c1*7+c2)/8;
    *pc = Interpolate_2(c1, 7, c2, 1, 3);
}

static inline void Interp4(uint32_t * pc, uint32_t c1, uint32_t c2, uint32_t c3)
{
    //*pc = (c1*2+(c2+c3)*7)/16;
    *pc = Interpolate_3(c1, 2, c2, 7, c3, 7, 4);
}

static inline void Interp5(uint32_t * pc, uint32_t c1, uint32_t c2)
{
    //*pc = (c1+c2) >> 1;
    *pc = Interpolate_2(c1, 1, c2, 1, 1);
}

static inline void Interp6(uint32_t * pc, uint32_t c1, uint32_t c2, uint32_t c3)
{
    //*pc = (c1*5+c2*2+c3)/8;
    *pc = Interpolate_3(c1, 5, c2, 2, c3, 1, 3);
}

static inline void Interp7(uint32_t * pc, uint32_t c1, uint32_t c2, uint32_t c3)
{
    //*pc = (c1*6+c2+c3)/8;
    *pc = Interpolate_3(c1, 6, c2, 1, c3, 1, 3);
}

static inline void Interp8(uint32_t * pc, uint32_t c1, uint32_t c2)
{
    //*pc = (c1*5+c2*3)/8;
    *pc = Interpolate_2(c1, 5, c2, 3, 3);
}

static inline void Interp9(uint32_t * pc, uint32_t c1, uint32_t c2, uint32_t c3)
{
    //*pc = (c1*2+(c2+c3)*3)/8;
    *pc = Interpolate_3(c1, 2, c2, 3, c3, 3, 3);
}

static inline void Interp10(uint32_t * pc, uint32_t c1, uint32_t c2, uint32_t c3)
{
    //*pc = (c1*14+c2+c3)/16;
    *pc = Interpolate_3(c1, 14, c2, 1, c3, 1, 4);
}

/* ---- 3-row source window with cached YUV --------------------------------- */

#define HQ_TILE 256

typedef struct HqWin {
    uint32_t pix[3][HQ_TILE + 2], yuv[3][HQ_TILE + 2];
    uint32_t *pr[3], *yr[3];     /* rows y-1, y, y+1 */
} HqWin;

static int hq_clamp(int v, int hi) { return v < 0 ? 0 : v > hi ? hi : v; }

/* Loads source row y (clamped), columns x0-1 .. x0+tw (clamped). */
static void hq_load(uint32_t *pix, uint32_t *yuv, const uint32_t *src, int ss, int sw, int sh,
                    int y, int x0, int tw)
{
    const uint32_t *s = src + (size_t)hq_clamp(y, sh - 1) * ss;
    uint32_t last = 0, last_yuv = rgb_to_yuv(0);
    for (int j = 0; j < tw + 2; ++j) {
        const uint32_t p = s[hq_clamp(x0 + j - 1, sw - 1)] & MASK_RGB;
        if (p != last) { last = p; last_yuv = rgb_to_yuv(p); }
        pix[j] = p;
        yuv[j] = last_yuv;
    }
}

/* Makes the window hold rows y-1..y+1: a fresh load on the first row of a
 * slice, otherwise one new row slid in. */
static void hq_win_row(HqWin *t, const uint32_t *src, int ss, int sw, int sh,
                       int y, int y0, int x0, int tw)
{
    if (y == y0) {
        for (int q = 0; q < 3; ++q) {
            t->pr[q] = t->pix[q]; t->yr[q] = t->yuv[q];
            hq_load(t->pr[q], t->yr[q], src, ss, sw, sh, y - 1 + q, x0, tw);
        }
        return;
    }
    uint32_t *p = t->pr[0], *v = t->yr[0];
    t->pr[0] = t->pr[1]; t->yr[0] = t->yr[1];
    t->pr[1] = t->pr[2]; t->yr[1] = t->yr[2];
    t->pr[2] = p; t->yr[2] = v;
    hq_load(p, v, src, ss, sw, sh, y + 1, x0, tw);
}

/*   +----+----+----+
 *   | w1 | w2 | w3 |
 *   +----+----+----+
 *   | w4 | w5 | w6 |
 *   +----+----+----+
 *   | w7 | w8 | w9 |
 *   +----+----+----+
 * Fills w[1..9] and their YUV, returns the reference's 8-bit pattern. */
static inline int hq_pattern(const HqWin *t, int i, uint32_t *w, uint32_t *yv)
{
    for (int q = 0; q < 3; ++q) {
        w[1 + 3 * q] = t->pr[q][i - 1]; w[2 + 3 * q] = t->pr[q][i]; w[3 + 3 * q] = t->pr[q][i + 1];
        yv[1 + 3 * q] = t->yr[q][i - 1]; yv[2 + 3 * q] = t->yr[q][i]; yv[3 + 3 * q] = t->yr[q][i + 1];
    }
    int pattern = 0;
    int flag = 1;
    for (int k = 1; k <= 9; k++) {
        if (k == 5) continue;
        if (w[k] != w[5] && yuv_diff(yv[5], yv[k]))
            pattern |= flag;
        flag <<= 1;
    }
    return pattern;
}

#define DIFF(a, b) yuv_diff(yv[a], yv[b])

/* ---- hq2x: PIXEL macros and pattern switch from hq2x.c ------------- */

#define PIXEL00_0     *dp = w[5];
#define PIXEL00_10    Interp1(dp, w[5], w[1]);
#define PIXEL00_11    Interp1(dp, w[5], w[4]);
#define PIXEL00_12    Interp1(dp, w[5], w[2]);
#define PIXEL00_20    Interp2(dp, w[5], w[4], w[2]);
#define PIXEL00_21    Interp2(dp, w[5], w[1], w[2]);
#define PIXEL00_22    Interp2(dp, w[5], w[1], w[4]);
#define PIXEL00_60    Interp6(dp, w[5], w[2], w[4]);
#define PIXEL00_61    Interp6(dp, w[5], w[4], w[2]);
#define PIXEL00_70    Interp7(dp, w[5], w[4], w[2]);
#define PIXEL00_90    Interp9(dp, w[5], w[4], w[2]);
#define PIXEL00_100   Interp10(dp, w[5], w[4], w[2]);
#define PIXEL01_0     *(dp+1) = w[5];
#define PIXEL01_10    Interp1(dp+1, w[5], w[3]);
#define PIXEL01_11    Interp1(dp+1, w[5], w[2]);
#define PIXEL01_12    Interp1(dp+1, w[5], w[6]);
#define PIXEL01_20    Interp2(dp+1, w[5], w[2], w[6]);
#define PIXEL01_21    Interp2(dp+1, w[5], w[3], w[6]);
#define PIXEL01_22    Interp2(dp+1, w[5], w[3], w[2]);
#define PIXEL01_60    Interp6(dp+1, w[5], w[6], w[2]);
#define PIXEL01_61    Interp6(dp+1, w[5], w[2], w[6]);
#define PIXEL01_70    Interp7(dp+1, w[5], w[2], w[6]);
#define PIXEL01_90    Interp9(dp+1, w[5], w[2], w[6]);
#define PIXEL01_100   Interp10(dp+1, w[5], w[2], w[6]);
#define PIXEL10_0     *(dp+dpL) = w[5];
#define PIXEL10_10    Interp1(dp+dpL, w[5], w[7]);
#define PIXEL10_11    Interp1(dp+dpL, w[5], w[8]);
#define PIXEL10_12    Interp1(dp+dpL, w[5], w[4]);
#define PIXEL10_20    Interp2(dp+dpL, w[5], w[8], w[4]);
#define PIXEL10_21    Interp2(dp+dpL, w[5], w[7], w[4]);
#define PIXEL10_22    Interp2(dp+dpL, w[5], w[7], w[8]);
#define PIXEL10_60    Interp6(dp+dpL, w[5], w[4], w[8]);
#define PIXEL10_61    Interp6(dp+dpL, w[5], w[8], w[4]);
#define PIXEL10_70    Interp7(dp+dpL, w[5], w[8], w[4]);
#define PIXEL10_90    Interp9(dp+dpL, w[5], w[8], w[4]);
#define PIXEL10_100   Interp10(dp+dpL, w[5], w[8], w[4]);
#define PIXEL11_0     *(dp+dpL+1) = w[5];
#define PIXEL11_10    Interp1(dp+dpL+1, w[5], w[9]);
#define PIXEL11_11    Interp1(dp+dpL+1, w[5], w[6]);
#define PIXEL11_12    Interp1(dp+dpL+1, w[5], w[8]);
#define PIXEL11_20    Interp2(dp+dpL+1, w[5], w[6], w[8]);
#define PIXEL11_21    Interp2(dp+dpL+1, w[5], w[9], w[8]);
#define PIXEL11_22    Interp2(dp+dpL+1, w[5], w[9], w[6]);
#define PIXEL11_60    Interp6(dp+dpL+1, w[5], w[8], w[6]);
#define PIXEL11_61    Interp6(dp+dpL+1, w[5], w[6], w[8]);
#define PIXEL11_70    Interp7(dp+dpL+1, w[5], w[6], w[8]);
#define PIXEL11_90    Interp9(dp+dpL+1, w[5], w[6], w[8]);
#define PIXEL11_100   Interp10(dp+dpL+1, w[5], w[6], w[8]);

static void hq2x_rows(const uint32_t *src, int ss, int sw, int sh,
                      uint32_t *dst, int ds, int y0, int y1)
{
    HqWin t;
    const int dpL = ds;
    for (int x0 = 0; x0 < sw; x0 += HQ_TILE) {
        const int tw = sw - x0 < HQ_TILE ? sw - x0 : HQ_TILE;
        for (int y = y0; y < y1; ++y) {
            hq_win_row(&t, src, ss, sw, sh, y, y0, x0, tw);
            uint32_t *dp = dst + (size_t)y * 2 * ds + (size_t)x0 * 2;
            for (int i = 1; i <= tw; ++i, dp += 2) {
                uint32_t w[10], yv[10];
                const int pattern = hq_pattern(&t, i, w, yv);
                switch (pattern) {
                    case 0: case 1: case 4: case 32: case 128: case 5: case 132: case 160: case 33: case 129:
                    case 36: case 133: case 164: case 161: case 37: case 165: {
                        PIXEL00_20 PIXEL01_20 PIXEL10_20 PIXEL11_20 break;
                    }
                    case 2: case 34: case 130: case 162: {
                        PIXEL00_22 PIXEL01_21 PIXEL10_20 PIXEL11_20 break;
                    }
                    case 16: case 17: case 48: case 49: {
                        PIXEL00_20 PIXEL01_22 PIXEL10_20 PIXEL11_21 break;
                    }
                    case 64: case 65: case 68: case 69: {
                        PIXEL00_20 PIXEL01_20 PIXEL10_21 PIXEL11_22 break;
                    }
                    case 8: case 12: case 136: case 140: {
                        PIXEL00_21 PIXEL01_20 PIXEL10_22 PIXEL11_20 break;
                    }
                    case 3: case 35: case 131: case 163: {
                        PIXEL00_11 PIXEL01_21 PIXEL10_20 PIXEL11_20 break;
                    }
                    case 6: case 38: case 134: case 166: {
                        PIXEL00_22 PIXEL01_12 PIXEL10_20 PIXEL11_20 break;
                    }
                    case 20: case 21: case 52: case 53: {
                        PIXEL00_20 PIXEL01_11 PIXEL10_20 PIXEL11_21 break;
                    }
                    case 144: case 145: case 176: case 177: {
                        PIXEL00_20 PIXEL01_22 PIXEL10_20 PIXEL11_12 break;
                    }
                    case 192: case 193: case 196: case 197: {
                        PIXEL00_20 PIXEL01_20 PIXEL10_21 PIXEL11_11 break;
                    }
                    case 96: case 97: case 100: case 101: {
                        PIXEL00_20 PIXEL01_20 PIXEL10_12 PIXEL11_22 break;
                    }
                    case 40: case 44: case 168: case 172: {
                        PIXEL00_21 PIXEL01_20 PIXEL10_11 PIXEL11_20 break;
                    }
                    case 9: case 13: case 137: case 141: {
                        PIXEL00_12 PIXEL01_20 PIXEL10_22 PIXEL11_20 break;
                    }
                    case 18: case 50: {
                        PIXEL00_22 if (DIFF(2, 6)) { PIXEL01_10 } else { PIXEL01_20 } PIXEL10_20 PIXEL11_21
                        break;
                    }
                    case 80: case 81: {
                        PIXEL00_20 PIXEL01_22 PIXEL10_21 if (DIFF(6, 8)) { PIXEL11_10 } else { PIXEL11_20 }
                        break;
                    }
                    case 72: case 76: {
                        PIXEL00_21 PIXEL01_20 if (DIFF(8, 4)) { PIXEL10_10 } else { PIXEL10_20 } PIXEL11_22
                        break;
                    }
                    case 10: case 138: {
                        if (DIFF(4, 2)) { PIXEL00_10 } else { PIXEL00_20 } PIXEL01_21 PIXEL10_22 PIXEL11_20
                        break;
                    }
                    case 66: {
                        PIXEL00_22 PIXEL01_21 PIXEL10_21 PIXEL11_22 break;
                    }
                    case 24: {
                        PIXEL00_21 PIXEL01_22 PIXEL10_22 PIXEL11_21 break;
                    }
                    case 7: case 39: case 135: {
                        PIXEL00_11 PIXEL01_12 PIXEL10_20 PIXEL11_20 break;
                    }
                    case 148: case 149: case 180: {
                        PIXEL00_20 PIXEL01_11 PIXEL10_20 PIXEL11_12 break;
                    }
                    case 224: case 228: case 225: {
                        PIXEL00_20 PIXEL01_20 PIXEL10_12 PIXEL11_11 break;
                    }
                    case 41: case 169: case 45: {
                        PIXEL00_12 PIXEL01_20 PIXEL10_11 PIXEL11_20 break;
                    }
                    case 22: case 54: {
                        PIXEL00_22 if (DIFF(2, 6)) { PIXEL01_0 } else { PIXEL01_20 } PIXEL10_20 PIXEL11_21
                        break;
                    }
                    case 208: case 209: {
                        PIXEL00_20 PIXEL01_22 PIXEL10_21 if (DIFF(6, 8)) { PIXEL11_0 } else { PIXEL11_20 }
                        break;
                    }
                    case 104: case 108: {
                        PIXEL00_21 PIXEL01_20 if (DIFF(8, 4)) { PIXEL10_0 } else { PIXEL10_20 } PIXEL11_22
                        break;
                    }
                    case 11: case 139: {
                        if (DIFF(4, 2)) { PIXEL00_0 } else { PIXEL00_20 } PIXEL01_21 PIXEL10_22 PIXEL11_20
                        break;
                    }
                    case 19: case 51: {
                        if (DIFF(2, 6)) { PIXEL00_11 PIXEL01_10 } else { PIXEL00_60 PIXEL01_90 } PIXEL10_20
                        PIXEL11_21 break;
                    }
                    case 146: case 178: {
                        PIXEL00_22 if (DIFF(2, 6)) { PIXEL01_10 PIXEL11_12 } else { PIXEL01_90 PIXEL11_61 }
                        PIXEL10_20 break;
                    }
                    case 84: case 85: {
                        PIXEL00_20 if (DIFF(6, 8)) { PIXEL01_11 PIXEL11_10 } else { PIXEL01_60 PIXEL11_90 }
                        PIXEL10_21 break;
                    }
                    case 112: case 113: {
                        PIXEL00_20 PIXEL01_22
                        if (DIFF(6, 8)) { PIXEL10_12 PIXEL11_10 } else { PIXEL10_61 PIXEL11_90 } break;
                    }
                    case 200: case 204: {
                        PIXEL00_21 PIXEL01_20
                        if (DIFF(8, 4)) { PIXEL10_10 PIXEL11_11 } else { PIXEL10_90 PIXEL11_60 } break;
                    }
                    case 73: case 77: {
                        if (DIFF(8, 4)) { PIXEL00_12 PIXEL10_10 } else { PIXEL00_61 PIXEL10_90 } PIXEL01_20
                        PIXEL11_22 break;
                    }
                    case 42: case 170: {
                        if (DIFF(4, 2)) { PIXEL00_10 PIXEL10_11 } else { PIXEL00_90 PIXEL10_60 } PIXEL01_21
                        PIXEL11_20 break;
                    }
                    case 14: case 142: {
                        if (DIFF(4, 2)) { PIXEL00_10 PIXEL01_12 } else { PIXEL00_90 PIXEL01_61 } PIXEL10_22
                        PIXEL11_20 break;
                    }
                    case 67: {
                        PIXEL00_11 PIXEL01_21 PIXEL10_21 PIXEL11_22 break;
                    }
                    case 70: {
                        PIXEL00_22 PIXEL01_12 PIXEL10_21 PIXEL11_22 break;
                    }
                    case 28: {
                        PIXEL00_21 PIXEL01_11 PIXEL10_22 PIXEL11_21 break;
                    }
                    case 152: {
                        PIXEL00_21 PIXEL01_22 PIXEL10_22 PIXEL11_12 break;
                    }
                    case 194: {
                        PIXEL00_22 PIXEL01_21 PIXEL10_21 PIXEL11_11 break;
                    }
                    case 98: {
                        PIXEL00_22 PIXEL01_21 PIXEL10_12 PIXEL11_22 break;
                    }
                    case 56: {
                        PIXEL00_21 PIXEL01_22 PIXEL10_11 PIXEL11_21 break;
                    }
                    case 25: {
                        PIXEL00_12 PIXEL01_22 PIXEL10_22 PIXEL11_21 break;
                    }
                    case 26: case 31: {
                        if (DIFF(4, 2)) { PIXEL00_0 } else { PIXEL00_20 }
                        if (DIFF(2, 6)) { PIXEL01_0 } else { PIXEL01_20 } PIXEL10_22 PIXEL11_21 break;
                    }
                    case 82: case 214: {
                        PIXEL00_22 if (DIFF(2, 6)) { PIXEL01_0 } else { PIXEL01_20 } PIXEL10_21
                        if (DIFF(6, 8)) { PIXEL11_0 } else { PIXEL11_20 } break;
                    }
                    case 88: case 248: {
                        PIXEL00_21 PIXEL01_22 if (DIFF(8, 4)) { PIXEL10_0 } else { PIXEL10_20 }
                        if (DIFF(6, 8)) { PIXEL11_0 } else { PIXEL11_20 } break;
                    }
                    case 74: case 107: {
                        if (DIFF(4, 2)) { PIXEL00_0 } else { PIXEL00_20 } PIXEL01_21
                        if (DIFF(8, 4)) { PIXEL10_0 } else { PIXEL10_20 } PIXEL11_22 break;
                    }
                    case 27: {
                        if (DIFF(4, 2)) { PIXEL00_0 } else { PIXEL00_20 } PIXEL01_10 PIXEL10_22 PIXEL11_21
                        break;
                    }
                    case 86: {
                        PIXEL00_22 if (DIFF(2, 6)) { PIXEL01_0 } else { PIXEL01_20 } PIXEL10_21 PIXEL11_10
                        break;
                    }
                    case 216: {
                        PIXEL00_21 PIXEL01_22 PIXEL10_10 if (DIFF(6, 8)) { PIXEL11_0 } else { PIXEL11_20 }
                        break;
                    }
                    case 106: {
                        PIXEL00_10 PIXEL01_21 if (DIFF(8, 4)) { PIXEL10_0 } else { PIXEL10_20 } PIXEL11_22
                        break;
                    }
                    case 30: {
                        PIXEL00_10 if (DIFF(2, 6)) { PIXEL01_0 } else { PIXEL01_20 } PIXEL10_22 PIXEL11_21
                        break;
                    }
                    case 210: {
                        PIXEL00_22 PIXEL01_10 PIXEL10_21 if (DIFF(6, 8)) { PIXEL11_0 } else { PIXEL11_20 }
                        break;
                    }
                    case 120: {
                        PIXEL00_21 PIXEL01_22 if (DIFF(8, 4)) { PIXEL10_0 } else { PIXEL10_20 } PIXEL11_10
                        break;
                    }
                    case 75: {
                        if (DIFF(4, 2)) { PIXEL00_0 } else { PIXEL00_20 } PIXEL01_21 PIXEL10_10 PIXEL11_22
                        break;
                    }
                    case 29: {
                        PIXEL00_12 PIXEL01_11 PIXEL10_22 PIXEL11_21 break;
                    }
                    case 198: {
                        PIXEL00_22 PIXEL01_12 PIXEL10_21 PIXEL11_11 break;
                    }
                    case 184: {
                        PIXEL00_21 PIXEL01_22 PIXEL10_11 PIXEL11_12 break;
                    }
                    case 99: {
                        PIXEL00_11 PIXEL01_21 PIXEL10_12 PIXEL11_22 break;
                    }
                    case 57: {
                        PIXEL00_12 PIXEL01_22 PIXEL10_11 PIXEL11_21 break;
                    }
                    case 71: {
                        PIXEL00_11 PIXEL01_12 PIXEL10_21 PIXEL11_22 break;
                    }
                    case 156: {
                        PIXEL00_21 PIXEL01_11 PIXEL10_22 PIXEL11_12 break;
                    }
                    case 226: {
                        PIXEL00_22 PIXEL01_21 PIXEL10_12 PIXEL11_11 break;
                    }
                    case 60: {
                        PIXEL00_21 PIXEL01_11 PIXEL10_11 PIXEL11_21 break;
                    }
                    case 195: {
                        PIXEL00_11 PIXEL01_21 PIXEL10_21 PIXEL11_11 break;
                    }
                    case 102: {
                        PIXEL00_22 PIXEL01_12 PIXEL10_12 PIXEL11_22 break;
                    }
                    case 153: {
                        PIXEL00_12 PIXEL01_22 PIXEL10_22 PIXEL11_12 break;
                    }
                    case 58: {
                        if (DIFF(4, 2)) { PIXEL00_10 } else { PIXEL00_70 }
                        if (DIFF(2, 6)) { PIXEL01_10 } else { PIXEL01_70 } PIXEL10_11 PIXEL11_21 break;
                    }
                    case 83: {
                        PIXEL00_11 if (DIFF(2, 6)) { PIXEL01_10 } else { PIXEL01_70 } PIXEL10_21
                        if (DIFF(6, 8)) { PIXEL11_10 } else { PIXEL11_70 } break;
                    }
                    case 92: {
                        PIXEL00_21 PIXEL01_11 if (DIFF(8, 4)) { PIXEL10_10 } else { PIXEL10_70 }
                        if (DIFF(6, 8)) { PIXEL11_10 } else { PIXEL11_70 } break;
                    }
                    case 202: {
                        if (DIFF(4, 2)) { PIXEL00_10 } else { PIXEL00_70 } PIXEL01_21
                        if (DIFF(8, 4)) { PIXEL10_10 } else { PIXEL10_70 } PIXEL11_11 break;
                    }
                    case 78: {
                        if (DIFF(4, 2)) { PIXEL00_10 } else { PIXEL00_70 } PIXEL01_12
                        if (DIFF(8, 4)) { PIXEL10_10 } else { PIXEL10_70 } PIXEL11_22 break;
                    }
                    case 154: {
                        if (DIFF(4, 2)) { PIXEL00_10 } else { PIXEL00_70 }
                        if (DIFF(2, 6)) { PIXEL01_10 } else { PIXEL01_70 } PIXEL10_22 PIXEL11_12 break;
                    }
                    case 114: {
                        PIXEL00_22 if (DIFF(2, 6)) { PIXEL01_10 } else { PIXEL01_70 } PIXEL10_12
                        if (DIFF(6, 8)) { PIXEL11_10 } else { PIXEL11_70 } break;
                    }
                    case 89: {
                        PIXEL00_12 PIXEL01_22 if (DIFF(8, 4)) { PIXEL10_10 } else { PIXEL10_70 }
                        if (DIFF(6, 8)) { PIXEL11_10 } else { PIXEL11_70 } break;
                    }
                    case 90: {
                        if (DIFF(4, 2)) { PIXEL00_10 } else { PIXEL00_70 }
                        if (DIFF(2, 6)) { PIXEL01_10 } else { PIXEL01_70 }
                        if (DIFF(8, 4)) { PIXEL10_10 } else { PIXEL10_70 }
                        if (DIFF(6, 8)) { PIXEL11_10 } else { PIXEL11_70 } break;
                    }
                    case 55: case 23: {
                        if (DIFF(2, 6)) { PIXEL00_11 PIXEL01_0 } else { PIXEL00_60 PIXEL01_90 } PIXEL10_20
                        PIXEL11_21 break;
                    }
                    case 182: case 150: {
                        PIXEL00_22 if (DIFF(2, 6)) { PIXEL01_0 PIXEL11_12 } else { PIXEL01_90 PIXEL11_61 }
                        PIXEL10_20 break;
                    }
                    case 213: case 212: {
                        PIXEL00_20 if (DIFF(6, 8)) { PIXEL01_11 PIXEL11_0 } else { PIXEL01_60 PIXEL11_90 }
                        PIXEL10_21 break;
                    }
                    case 241: case 240: {
                        PIXEL00_20 PIXEL01_22
                        if (DIFF(6, 8)) { PIXEL10_12 PIXEL11_0 } else { PIXEL10_61 PIXEL11_90 } break;
                    }
                    case 236: case 232: {
                        PIXEL00_21 PIXEL01_20
                        if (DIFF(8, 4)) { PIXEL10_0 PIXEL11_11 } else { PIXEL10_90 PIXEL11_60 } break;
                    }
                    case 109: case 105: {
                        if (DIFF(8, 4)) { PIXEL00_12 PIXEL10_0 } else { PIXEL00_61 PIXEL10_90 } PIXEL01_20
                        PIXEL11_22 break;
                    }
                    case 171: case 43: {
                        if (DIFF(4, 2)) { PIXEL00_0 PIXEL10_11 } else { PIXEL00_90 PIXEL10_60 } PIXEL01_21
                        PIXEL11_20 break;
                    }
                    case 143: case 15: {
                        if (DIFF(4, 2)) { PIXEL00_0 PIXEL01_12 } else { PIXEL00_90 PIXEL01_61 } PIXEL10_22
                        PIXEL11_20 break;
                    }
                    case 124: {
                        PIXEL00_21 PIXEL01_11 if (DIFF(8, 4)) { PIXEL10_0 } else { PIXEL10_20 } PIXEL11_10
                        break;
                    }
                    case 203: {
                        if (DIFF(4, 2)) { PIXEL00_0 } else { PIXEL00_20 } PIXEL01_21 PIXEL10_10 PIXEL11_11
                        break;
                    }
                    case 62: {
                        PIXEL00_10 if (DIFF(2, 6)) { PIXEL01_0 } else { PIXEL01_20 } PIXEL10_11 PIXEL11_21
                        break;
                    }
                    case 211: {
                        PIXEL00_11 PIXEL01_10 PIXEL10_21 if (DIFF(6, 8)) { PIXEL11_0 } else { PIXEL11_20 }
                        break;
                    }
                    case 118: {
                        PIXEL00_22 if (DIFF(2, 6)) { PIXEL01_0 } else { PIXEL01_20 } PIXEL10_12 PIXEL11_10
                        break;
                    }
                    case 217: {
                        PIXEL00_12 PIXEL01_22 PIXEL10_10 if (DIFF(6, 8)) { PIXEL11_0 } else { PIXEL11_20 }
                        break;
                    }
                    case 110: {
                        PIXEL00_10 PIXEL01_12 if (DIFF(8, 4)) { PIXEL10_0 } else { PIXEL10_20 } PIXEL11_22
                        break;
                    }
                    case 155: {
                        if (DIFF(4, 2)) { PIXEL00_0 } else { PIXEL00_20 } PIXEL01_10 PIXEL10_22 PIXEL11_12
                        break;
                    }
                    case 188: {
                        PIXEL00_21 PIXEL01_11 PIXEL10_11 PIXEL11_12 break;
                    }
                    case 185: {
                        PIXEL00_12 PIXEL01_22 PIXEL10_11 PIXEL11_12 break;
                    }
                    case 61: {
                        PIXEL00_12 PIXEL01_11 PIXEL10_11 PIXEL11_21 break;
                    }
                    case 157: {
                        PIXEL00_12 PIXEL01_11 PIXEL10_22 PIXEL11_12 break;
                    }
                    case 103: {
                        PIXEL00_11 PIXEL01_12 PIXEL10_12 PIXEL11_22 break;
                    }
                    case 227: {
                        PIXEL00_11 PIXEL01_21 PIXEL10_12 PIXEL11_11 break;
                    }
                    case 230: {
                        PIXEL00_22 PIXEL01_12 PIXEL10_12 PIXEL11_11 break;
                    }
                    case 199: {
                        PIXEL00_11 PIXEL01_12 PIXEL10_21 PIXEL11_11 break;
                    }
                    case 220: {
                        PIXEL00_21 PIXEL01_11 if (DIFF(8, 4)) { PIXEL10_10 } else { PIXEL10_70 }
                        if (DIFF(6, 8)) { PIXEL11_0 } else { PIXEL11_20 } break;
                    }
                    case 158: {
                        if (DIFF(4, 2)) { PIXEL00_10 } else { PIXEL00_70 }
                        if (DIFF(2, 6)) { PIXEL01_0 } else { PIXEL01_20 } PIXEL10_22 PIXEL11_12 break;
                    }
                    case 234: {
                        if (DIFF(4, 2)) { PIXEL00_10 } else { PIXEL00_70 } PIXEL01_21
                        if (DIFF(8, 4)) { PIXEL10_0 } else { PIXEL10_20 } PIXEL11_11 break;
                    }
                    case 242: {
                        PIXEL00_22 if (DIFF(2, 6)) { PIXEL01_10 } else { PIXEL01_70 } PIXEL10_12
                        if (DIFF(6, 8)) { PIXEL11_0 } else { PIXEL11_20 } break;
                    }
                    case 59: {
                        if (DIFF(4, 2)) { PIXEL00_0 } else { PIXEL00_20 }
                        if (DIFF(2, 6)) { PIXEL01_10 } else { PIXEL01_70 } PIXEL10_11 PIXEL11_21 break;
                    }
                    case 121: {
                        PIXEL00_12 PIXEL01_22 if (DIFF(8, 4)) { PIXEL10_0 } else { PIXEL10_20 }
                        if (DIFF(6, 8)) { PIXEL11_10 } else { PIXEL11_70 } break;
                    }
                    case 87: {
                        PIXEL00_11 if (DIFF(2, 6)) { PIXEL01_0 } else { PIXEL01_20 } PIXEL10_21
                        if (DIFF(6, 8)) { PIXEL11_10 } else { PIXEL11_70 } break;
                    }
                    case 79: {
                        if (DIFF(4, 2)) { PIXEL00_0 } else { PIXEL00_20 } PIXEL01_12
                        if (DIFF(8, 4)) { PIXEL10_10 } else { PIXEL10_70 } PIXEL11_22 break;
                    }
                    case 122: {
                        if (DIFF(4, 2)) { PIXEL00_10 } else { PIXEL00_70 }
                        if (DIFF(2, 6)) { PIXEL01_10 } else { PIXEL01_70 }
                        if (DIFF(8, 4)) { PIXEL10_0 } else { PIXEL10_20 }
                        if (DIFF(6, 8)) { PIXEL11_10 } else { PIXEL11_70 } break;
                    }
                    case 94: {
                        if (DIFF(4, 2)) { PIXEL00_10 } else { PIXEL00_70 }
                        if (DIFF(2, 6)) { PIXEL01_0 } else { PIXEL01_20 }
                        if (DIFF(8, 4)) { PIXEL10_10 } else { PIXEL10_70 }
                        if (DIFF(6, 8)) { PIXEL11_10 } else { PIXEL11_70 } break;
                    }
                    case 218: {
                        if (DIFF(4, 2)) { PIXEL00_10 } else { PIXEL00_70 }
                        if (DIFF(2, 6)) { PIXEL01_10 } else { PIXEL01_70 }
                        if (DIFF(8, 4)) { PIXEL10_10 } else { PIXEL10_70 }
                        if (DIFF(6, 8)) { PIXEL11_0 } else { PIXEL11_20 } break;
                    }
                    case 91: {
                        if (DIFF(4, 2)) { PIXEL00_0 } else { PIXEL00_20 }
                        if (DIFF(2, 6)) { PIXEL01_10 } else { PIXEL01_70 }
                        if (DIFF(8, 4)) { PIXEL10_10 } else { PIXEL10_70 }
                        if (DIFF(6, 8)) { PIXEL11_10 } else { PIXEL11_70 } break;
                    }
                    case 229: {
                        PIXEL00_20 PIXEL01_20 PIXEL10_12 PIXEL11_11 break;
                    }
                    case 167: {
                        PIXEL00_11 PIXEL01_12 PIXEL10_20 PIXEL11_20 break;
                    }
                    case 173: {
                        PIXEL00_12 PIXEL01_20 PIXEL10_11 PIXEL11_20 break;
                    }
                    case 181: {
                        PIXEL00_20 PIXEL01_11 PIXEL10_20 PIXEL11_12 break;
                    }
                    case 186: {
                        if (DIFF(4, 2)) { PIXEL00_10 } else { PIXEL00_70 }
                        if (DIFF(2, 6)) { PIXEL01_10 } else { PIXEL01_70 } PIXEL10_11 PIXEL11_12 break;
                    }
                    case 115: {
                        PIXEL00_11 if (DIFF(2, 6)) { PIXEL01_10 } else { PIXEL01_70 } PIXEL10_12
                        if (DIFF(6, 8)) { PIXEL11_10 } else { PIXEL11_70 } break;
                    }
                    case 93: {
                        PIXEL00_12 PIXEL01_11 if (DIFF(8, 4)) { PIXEL10_10 } else { PIXEL10_70 }
                        if (DIFF(6, 8)) { PIXEL11_10 } else { PIXEL11_70 } break;
                    }
                    case 206: {
                        if (DIFF(4, 2)) { PIXEL00_10 } else { PIXEL00_70 } PIXEL01_12
                        if (DIFF(8, 4)) { PIXEL10_10 } else { PIXEL10_70 } PIXEL11_11 break;
                    }
                    case 205: case 201: {
                        PIXEL00_12 PIXEL01_20 if (DIFF(8, 4)) { PIXEL10_10 } else { PIXEL10_70 } PIXEL11_11
                        break;
                    }
                    case 174: case 46: {
                        if (DIFF(4, 2)) { PIXEL00_10 } else { PIXEL00_70 } PIXEL01_12 PIXEL10_11 PIXEL11_20
                        break;
                    }
                    case 179: case 147: {
                        PIXEL00_11 if (DIFF(2, 6)) { PIXEL01_10 } else { PIXEL01_70 } PIXEL10_20 PIXEL11_12
                        break;
                    }
                    case 117: case 116: {
                        PIXEL00_20 PIXEL01_11 PIXEL10_12 if (DIFF(6, 8)) { PIXEL11_10 } else { PIXEL11_70 }
                        break;
                    }
                    case 189: {
                        PIXEL00_12 PIXEL01_11 PIXEL10_11 PIXEL11_12 break;
                    }
                    case 231: {
                        PIXEL00_11 PIXEL01_12 PIXEL10_12 PIXEL11_11 break;
                    }
                    case 126: {
                        PIXEL00_10 if (DIFF(2, 6)) { PIXEL01_0 } else { PIXEL01_20 }
                        if (DIFF(8, 4)) { PIXEL10_0 } else { PIXEL10_20 } PIXEL11_10 break;
                    }
                    case 219: {
                        if (DIFF(4, 2)) { PIXEL00_0 } else { PIXEL00_20 } PIXEL01_10 PIXEL10_10
                        if (DIFF(6, 8)) { PIXEL11_0 } else { PIXEL11_20 } break;
                    }
                    case 125: {
                        if (DIFF(8, 4)) { PIXEL00_12 PIXEL10_0 } else { PIXEL00_61 PIXEL10_90 } PIXEL01_11
                        PIXEL11_10 break;
                    }
                    case 221: {
                        PIXEL00_12 if (DIFF(6, 8)) { PIXEL01_11 PIXEL11_0 } else { PIXEL01_60 PIXEL11_90 }
                        PIXEL10_10 break;
                    }
                    case 207: {
                        if (DIFF(4, 2)) { PIXEL00_0 PIXEL01_12 } else { PIXEL00_90 PIXEL01_61 } PIXEL10_10
                        PIXEL11_11 break;
                    }
                    case 238: {
                        PIXEL00_10 PIXEL01_12
                        if (DIFF(8, 4)) { PIXEL10_0 PIXEL11_11 } else { PIXEL10_90 PIXEL11_60 } break;
                    }
                    case 190: {
                        PIXEL00_10 if (DIFF(2, 6)) { PIXEL01_0 PIXEL11_12 } else { PIXEL01_90 PIXEL11_61 }
                        PIXEL10_11 break;
                    }
                    case 187: {
                        if (DIFF(4, 2)) { PIXEL00_0 PIXEL10_11 } else { PIXEL00_90 PIXEL10_60 } PIXEL01_10
                        PIXEL11_12 break;
                    }
                    case 243: {
                        PIXEL00_11 PIXEL01_10
                        if (DIFF(6, 8)) { PIXEL10_12 PIXEL11_0 } else { PIXEL10_61 PIXEL11_90 } break;
                    }
                    case 119: {
                        if (DIFF(2, 6)) { PIXEL00_11 PIXEL01_0 } else { PIXEL00_60 PIXEL01_90 } PIXEL10_12
                        PIXEL11_10 break;
                    }
                    case 237: case 233: {
                        PIXEL00_12 PIXEL01_20 if (DIFF(8, 4)) { PIXEL10_0 } else { PIXEL10_100 } PIXEL11_11
                        break;
                    }
                    case 175: case 47: {
                        if (DIFF(4, 2)) { PIXEL00_0 } else { PIXEL00_100 } PIXEL01_12 PIXEL10_11 PIXEL11_20
                        break;
                    }
                    case 183: case 151: {
                        PIXEL00_11 if (DIFF(2, 6)) { PIXEL01_0 } else { PIXEL01_100 } PIXEL10_20 PIXEL11_12
                        break;
                    }
                    case 245: case 244: {
                        PIXEL00_20 PIXEL01_11 PIXEL10_12 if (DIFF(6, 8)) { PIXEL11_0 } else { PIXEL11_100 }
                        break;
                    }
                    case 250: {
                        PIXEL00_10 PIXEL01_10 if (DIFF(8, 4)) { PIXEL10_0 } else { PIXEL10_20 }
                        if (DIFF(6, 8)) { PIXEL11_0 } else { PIXEL11_20 } break;
                    }
                    case 123: {
                        if (DIFF(4, 2)) { PIXEL00_0 } else { PIXEL00_20 } PIXEL01_10
                        if (DIFF(8, 4)) { PIXEL10_0 } else { PIXEL10_20 } PIXEL11_10 break;
                    }
                    case 95: {
                        if (DIFF(4, 2)) { PIXEL00_0 } else { PIXEL00_20 }
                        if (DIFF(2, 6)) { PIXEL01_0 } else { PIXEL01_20 } PIXEL10_10 PIXEL11_10 break;
                    }
                    case 222: {
                        PIXEL00_10 if (DIFF(2, 6)) { PIXEL01_0 } else { PIXEL01_20 } PIXEL10_10
                        if (DIFF(6, 8)) { PIXEL11_0 } else { PIXEL11_20 } break;
                    }
                    case 252: {
                        PIXEL00_21 PIXEL01_11 if (DIFF(8, 4)) { PIXEL10_0 } else { PIXEL10_20 }
                        if (DIFF(6, 8)) { PIXEL11_0 } else { PIXEL11_100 } break;
                    }
                    case 249: {
                        PIXEL00_12 PIXEL01_22 if (DIFF(8, 4)) { PIXEL10_0 } else { PIXEL10_100 }
                        if (DIFF(6, 8)) { PIXEL11_0 } else { PIXEL11_20 } break;
                    }
                    case 235: {
                        if (DIFF(4, 2)) { PIXEL00_0 } else { PIXEL00_20 } PIXEL01_21
                        if (DIFF(8, 4)) { PIXEL10_0 } else { PIXEL10_100 } PIXEL11_11 break;
                    }
                    case 111: {
                        if (DIFF(4, 2)) { PIXEL00_0 } else { PIXEL00_100 } PIXEL01_12
                        if (DIFF(8, 4)) { PIXEL10_0 } else { PIXEL10_20 } PIXEL11_22 break;
                    }
                    case 63: {
                        if (DIFF(4, 2)) { PIXEL00_0 } else { PIXEL00_100 }
                        if (DIFF(2, 6)) { PIXEL01_0 } else { PIXEL01_20 } PIXEL10_11 PIXEL11_21 break;
                    }
                    case 159: {
                        if (DIFF(4, 2)) { PIXEL00_0 } else { PIXEL00_20 }
                        if (DIFF(2, 6)) { PIXEL01_0 } else { PIXEL01_100 } PIXEL10_22 PIXEL11_12 break;
                    }
                    case 215: {
                        PIXEL00_11 if (DIFF(2, 6)) { PIXEL01_0 } else { PIXEL01_100 } PIXEL10_21
                        if (DIFF(6, 8)) { PIXEL11_0 } else { PIXEL11_20 } break;
                    }
                    case 246: {
                        PIXEL00_22 if (DIFF(2, 6)) { PIXEL01_0 } else { PIXEL01_20 } PIXEL10_12
                        if (DIFF(6, 8)) { PIXEL11_0 } else { PIXEL11_100 } break;
                    }
                    case 254: {
                        PIXEL00_10 if (DIFF(2, 6)) { PIXEL01_0 } else { PIXEL01_20 }
                        if (DIFF(8, 4)) { PIXEL10_0 } else { PIXEL10_20 }
                        if (DIFF(6, 8)) { PIXEL11_0 } else { PIXEL11_100 } break;
                    }
                    case 253: {
                        PIXEL00_12 PIXEL01_11 if (DIFF(8, 4)) { PIXEL10_0 } else { PIXEL10_100 }
                        if (DIFF(6, 8)) { PIXEL11_0 } else { PIXEL11_100 } break;
                    }
                    case 251: {
                        if (DIFF(4, 2)) { PIXEL00_0 } else { PIXEL00_20 } PIXEL01_10
                        if (DIFF(8, 4)) { PIXEL10_0 } else { PIXEL10_100 }
                        if (DIFF(6, 8)) { PIXEL11_0 } else { PIXEL11_20 } break;
                    }
                    case 239: {
                        if (DIFF(4, 2)) { PIXEL00_0 } else { PIXEL00_100 } PIXEL01_12
                        if (DIFF(8, 4)) { PIXEL10_0 } else { PIXEL10_100 } PIXEL11_11 break;
                    }
                    case 127: {
                        if (DIFF(4, 2)) { PIXEL00_0 } else { PIXEL00_100 }
                        if (DIFF(2, 6)) { PIXEL01_0 } else { PIXEL01_20 }
                        if (DIFF(8, 4)) { PIXEL10_0 } else { PIXEL10_20 } PIXEL11_10 break;
                    }
                    case 191: {
                        if (DIFF(4, 2)) { PIXEL00_0 } else { PIXEL00_100 }
                        if (DIFF(2, 6)) { PIXEL01_0 } else { PIXEL01_100 } PIXEL10_11 PIXEL11_12 break;
                    }
                    case 223: {
                        if (DIFF(4, 2)) { PIXEL00_0 } else { PIXEL00_20 }
                        if (DIFF(2, 6)) { PIXEL01_0 } else { PIXEL01_100 } PIXEL10_10
                        if (DIFF(6, 8)) { PIXEL11_0 } else { PIXEL11_20 } break;
                    }
                    case 247: {
                        PIXEL00_11 if (DIFF(2, 6)) { PIXEL01_0 } else { PIXEL01_100 } PIXEL10_12
                        if (DIFF(6, 8)) { PIXEL11_0 } else { PIXEL11_100 } break;
                    }
                    case 255: {
                        if (DIFF(4, 2)) { PIXEL00_0 } else { PIXEL00_100 }
                        if (DIFF(2, 6)) { PIXEL01_0 } else { PIXEL01_100 }
                        if (DIFF(8, 4)) { PIXEL10_0 } else { PIXEL10_100 }
                        if (DIFF(6, 8)) { PIXEL11_0 } else { PIXEL11_100 } break;
                    }
                }
            }
        }
    }
}

#undef PIXEL00_0
#undef PIXEL00_10
#undef PIXEL00_11
#undef PIXEL00_12
#undef PIXEL00_20
#undef PIXEL00_21
#undef PIXEL00_22
#undef PIXEL00_60
#undef PIXEL00_61
#undef PIXEL00_70
#undef PIXEL00_90
#undef PIXEL00_100
#undef PIXEL01_0
#undef PIXEL01_10
#undef PIXEL01_11
#undef PIXEL01_12
#undef PIXEL01_20
#undef PIXEL01_21
#undef PIXEL01_22
#undef PIXEL01_60
#undef PIXEL01_61
#undef PIXEL01_70
#undef PIXEL01_90
#undef PIXEL01_100
#undef PIXEL10_0
#undef PIXEL10_10
#undef PIXEL10_11
#undef PIXEL10_12
#undef PIXEL10_20
#undef PIXEL10_21
#undef PIXEL10_22
#undef PIXEL10_60
#undef PIXEL10_61
#undef PIXEL10_70
#undef PIXEL10_90
#undef PIXEL10_100
#undef PIXEL11_0
#undef PIXEL11_10
#undef PIXEL11_11
#undef PIXEL11_12
#undef PIXEL11_20
#undef PIXEL11_21
#undef PIXEL11_22
#undef PIXEL11_60
#undef PIXEL11_61
#undef PIXEL11_70
#undef PIXEL11_90
#undef PIXEL11_100

/* ---- hq3x: PIXEL macros and pattern switch from hq3x.c ------------- */

#define PIXEL00_1M  Interp1(dp, w[5], w[1]);
#define PIXEL00_1U  Interp1(dp, w[5], w[2]);
#define PIXEL00_1L  Interp1(dp, w[5], w[4]);
#define PIXEL00_2   Interp2(dp, w[5], w[4], w[2]);
#define PIXEL00_4   Interp4(dp, w[5], w[4], w[2]);
#define PIXEL00_5   Interp5(dp, w[4], w[2]);
#define PIXEL00_C   *dp   = w[5];
#define PIXEL01_1   Interp1(dp+1, w[5], w[2]);
#define PIXEL01_3   Interp3(dp+1, w[5], w[2]);
#define PIXEL01_6   Interp1(dp+1, w[2], w[5]);
#define PIXEL01_C   *(dp+1) = w[5];
#define PIXEL02_1M  Interp1(dp+2, w[5], w[3]);
#define PIXEL02_1U  Interp1(dp+2, w[5], w[2]);
#define PIXEL02_1R  Interp1(dp+2, w[5], w[6]);
#define PIXEL02_2   Interp2(dp+2, w[5], w[2], w[6]);
#define PIXEL02_4   Interp4(dp+2, w[5], w[2], w[6]);
#define PIXEL02_5   Interp5(dp+2, w[2], w[6]);
#define PIXEL02_C   *(dp+2) = w[5];
#define PIXEL10_1   Interp1(dp+dpL, w[5], w[4]);
#define PIXEL10_3   Interp3(dp+dpL, w[5], w[4]);
#define PIXEL10_6   Interp1(dp+dpL, w[4], w[5]);
#define PIXEL10_C   *(dp+dpL) = w[5];
#define PIXEL11     *(dp+dpL+1) = w[5];
#define PIXEL12_1   Interp1(dp+dpL+2, w[5], w[6]);
#define PIXEL12_3   Interp3(dp+dpL+2, w[5], w[6]);
#define PIXEL12_6   Interp1(dp+dpL+2, w[6], w[5]);
#define PIXEL12_C   *(dp+dpL+2) = w[5];
#define PIXEL20_1M  Interp1(dp+dpL+dpL, w[5], w[7]);
#define PIXEL20_1D  Interp1(dp+dpL+dpL, w[5], w[8]);
#define PIXEL20_1L  Interp1(dp+dpL+dpL, w[5], w[4]);
#define PIXEL20_2   Interp2(dp+dpL+dpL, w[5], w[8], w[4]);
#define PIXEL20_4   Interp4(dp+dpL+dpL, w[5], w[8], w[4]);
#define PIXEL20_5   Interp5(dp+dpL+dpL, w[8], w[4]);
#define PIXEL20_C   *(dp+dpL+dpL) = w[5];
#define PIXEL21_1   Interp1(dp+dpL+dpL+1, w[5], w[8]);
#define PIXEL21_3   Interp3(dp+dpL+dpL+1, w[5], w[8]);
#define PIXEL21_6   Interp1(dp+dpL+dpL+1, w[8], w[5]);
#define PIXEL21_C   *(dp+dpL+dpL+1) = w[5];
#define PIXEL22_1M  Interp1(dp+dpL+dpL+2, w[5], w[9]);
#define PIXEL22_1D  Interp1(dp+dpL+dpL+2, w[5], w[8]);
#define PIXEL22_1R  Interp1(dp+dpL+dpL+2, w[5], w[6]);
#define PIXEL22_2   Interp2(dp+dpL+dpL+2, w[5], w[6], w[8]);
#define PIXEL22_4   Interp4(dp+dpL+dpL+2, w[5], w[6], w[8]);
#define PIXEL22_5   Interp5(dp+dpL+dpL+2, w[6], w[8]);
#define PIXEL22_C   *(dp+dpL+dpL+2) = w[5];

static void hq3x_rows(const uint32_t *src, int ss, int sw, int sh,
                      uint32_t *dst, int ds, int y0, int y1)
{
    HqWin t;
    const int dpL = ds;
    for (int x0 = 0; x0 < sw; x0 += HQ_TILE) {
        const int tw = sw - x0 < HQ_TILE ? sw - x0 : HQ_TILE;
        for (int y = y0; y < y1; ++y) {
            hq_win_row(&t, src, ss, sw, sh, y, y0, x0, tw);
            uint32_t *dp = dst + (size_t)y * 3 * ds + (size_t)x0 * 3;
            for (int i = 1; i <= tw; ++i, dp += 3) {
                uint32_t w[10], yv[10];
                const int pattern = hq_pattern(&t, i, w, yv);
                switch (pattern) {
                    case 0: case 1: case 4: case 32: case 128: case 5: case 132: case 160: case 33: case 129:
                    case 36: case 133: case 164: case 161: case 37: case 165: {
                        PIXEL00_2 PIXEL01_1 PIXEL02_2 PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_2 PIXEL21_1
                        PIXEL22_2 break;
                    }
                    case 2: case 34: case 130: case 162: {
                        PIXEL00_1M PIXEL01_C PIXEL02_1M PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_2 PIXEL21_1
                        PIXEL22_2 break;
                    }
                    case 16: case 17: case 48: case 49: {
                        PIXEL00_2 PIXEL01_1 PIXEL02_1M PIXEL10_1 PIXEL11 PIXEL12_C PIXEL20_2 PIXEL21_1
                        PIXEL22_1M break;
                    }
                    case 64: case 65: case 68: case 69: {
                        PIXEL00_2 PIXEL01_1 PIXEL02_2 PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_C
                        PIXEL22_1M break;
                    }
                    case 8: case 12: case 136: case 140: {
                        PIXEL00_1M PIXEL01_1 PIXEL02_2 PIXEL10_C PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_1
                        PIXEL22_2 break;
                    }
                    case 3: case 35: case 131: case 163: {
                        PIXEL00_1L PIXEL01_C PIXEL02_1M PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_2 PIXEL21_1
                        PIXEL22_2 break;
                    }
                    case 6: case 38: case 134: case 166: {
                        PIXEL00_1M PIXEL01_C PIXEL02_1R PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_2 PIXEL21_1
                        PIXEL22_2 break;
                    }
                    case 20: case 21: case 52: case 53: {
                        PIXEL00_2 PIXEL01_1 PIXEL02_1U PIXEL10_1 PIXEL11 PIXEL12_C PIXEL20_2 PIXEL21_1
                        PIXEL22_1M break;
                    }
                    case 144: case 145: case 176: case 177: {
                        PIXEL00_2 PIXEL01_1 PIXEL02_1M PIXEL10_1 PIXEL11 PIXEL12_C PIXEL20_2 PIXEL21_1
                        PIXEL22_1D break;
                    }
                    case 192: case 193: case 196: case 197: {
                        PIXEL00_2 PIXEL01_1 PIXEL02_2 PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_C
                        PIXEL22_1R break;
                    }
                    case 96: case 97: case 100: case 101: {
                        PIXEL00_2 PIXEL01_1 PIXEL02_2 PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1L PIXEL21_C
                        PIXEL22_1M break;
                    }
                    case 40: case 44: case 168: case 172: {
                        PIXEL00_1M PIXEL01_1 PIXEL02_2 PIXEL10_C PIXEL11 PIXEL12_1 PIXEL20_1D PIXEL21_1
                        PIXEL22_2 break;
                    }
                    case 9: case 13: case 137: case 141: {
                        PIXEL00_1U PIXEL01_1 PIXEL02_2 PIXEL10_C PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_1
                        PIXEL22_2 break;
                    }
                    case 18: case 50: {
                        PIXEL00_1M
                        if (DIFF(2, 6)) { PIXEL01_C PIXEL02_1M PIXEL12_C } else { PIXEL01_3 PIXEL02_4 PIXEL12_3 }
                        PIXEL10_1 PIXEL11 PIXEL20_2 PIXEL21_1 PIXEL22_1M break;
                    }
                    case 80: case 81: {
                        PIXEL00_2 PIXEL01_1 PIXEL02_1M PIXEL10_1 PIXEL11 PIXEL20_1M
                        if (DIFF(6, 8)) { PIXEL12_C PIXEL21_C PIXEL22_1M } else { PIXEL12_3 PIXEL21_3 PIXEL22_4 }
                        break;
                    }
                    case 72: case 76: {
                        PIXEL00_1M PIXEL01_1 PIXEL02_2 PIXEL11 PIXEL12_1
                        if (DIFF(8, 4)) { PIXEL10_C PIXEL20_1M PIXEL21_C } else { PIXEL10_3 PIXEL20_4 PIXEL21_3 }
                        PIXEL22_1M break;
                    }
                    case 10: case 138: {
                        if (DIFF(4, 2)) { PIXEL00_1M PIXEL01_C PIXEL10_C } else { PIXEL00_4 PIXEL01_3 PIXEL10_3 }
                        PIXEL02_1M PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_1 PIXEL22_2 break;
                    }
                    case 66: {
                        PIXEL00_1M PIXEL01_C PIXEL02_1M PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_C
                        PIXEL22_1M break;
                    }
                    case 24: {
                        PIXEL00_1M PIXEL01_1 PIXEL02_1M PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1M PIXEL21_1
                        PIXEL22_1M break;
                    }
                    case 7: case 39: case 135: {
                        PIXEL00_1L PIXEL01_C PIXEL02_1R PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_2 PIXEL21_1
                        PIXEL22_2 break;
                    }
                    case 148: case 149: case 180: {
                        PIXEL00_2 PIXEL01_1 PIXEL02_1U PIXEL10_1 PIXEL11 PIXEL12_C PIXEL20_2 PIXEL21_1
                        PIXEL22_1D break;
                    }
                    case 224: case 228: case 225: {
                        PIXEL00_2 PIXEL01_1 PIXEL02_2 PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1L PIXEL21_C
                        PIXEL22_1R break;
                    }
                    case 41: case 169: case 45: {
                        PIXEL00_1U PIXEL01_1 PIXEL02_2 PIXEL10_C PIXEL11 PIXEL12_1 PIXEL20_1D PIXEL21_1
                        PIXEL22_2 break;
                    }
                    case 22: case 54: {
                        PIXEL00_1M
                        if (DIFF(2, 6)) { PIXEL01_C PIXEL02_C PIXEL12_C } else { PIXEL01_3 PIXEL02_4 PIXEL12_3 }
                        PIXEL10_1 PIXEL11 PIXEL20_2 PIXEL21_1 PIXEL22_1M break;
                    }
                    case 208: case 209: {
                        PIXEL00_2 PIXEL01_1 PIXEL02_1M PIXEL10_1 PIXEL11 PIXEL20_1M
                        if (DIFF(6, 8)) { PIXEL12_C PIXEL21_C PIXEL22_C } else { PIXEL12_3 PIXEL21_3 PIXEL22_4 }
                        break;
                    }
                    case 104: case 108: {
                        PIXEL00_1M PIXEL01_1 PIXEL02_2 PIXEL11 PIXEL12_1
                        if (DIFF(8, 4)) { PIXEL10_C PIXEL20_C PIXEL21_C } else { PIXEL10_3 PIXEL20_4 PIXEL21_3 }
                        PIXEL22_1M break;
                    }
                    case 11: case 139: {
                        if (DIFF(4, 2)) { PIXEL00_C PIXEL01_C PIXEL10_C } else { PIXEL00_4 PIXEL01_3 PIXEL10_3 }
                        PIXEL02_1M PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_1 PIXEL22_2 break;
                    }
                    case 19: case 51: {
                        if (DIFF(2, 6)) { PIXEL00_1L PIXEL01_C PIXEL02_1M PIXEL12_C } else { PIXEL00_2 PIXEL01_6 PIXEL02_5 PIXEL12_1 }
                        PIXEL10_1 PIXEL11 PIXEL20_2 PIXEL21_1 PIXEL22_1M break;
                    }
                    case 146: case 178: {
                        if (DIFF(2, 6)) { PIXEL01_C PIXEL02_1M PIXEL12_C PIXEL22_1D } else { PIXEL01_1 PIXEL02_5 PIXEL12_6 PIXEL22_2 }
                        PIXEL00_1M PIXEL10_1 PIXEL11 PIXEL20_2 PIXEL21_1 break;
                    }
                    case 84: case 85: {
                        if (DIFF(6, 8)) { PIXEL02_1U PIXEL12_C PIXEL21_C PIXEL22_1M } else { PIXEL02_2 PIXEL12_6 PIXEL21_1 PIXEL22_5 }
                        PIXEL00_2 PIXEL01_1 PIXEL10_1 PIXEL11 PIXEL20_1M break;
                    }
                    case 112: case 113: {
                        if (DIFF(6, 8)) { PIXEL12_C PIXEL20_1L PIXEL21_C PIXEL22_1M } else { PIXEL12_1 PIXEL20_2 PIXEL21_6 PIXEL22_5 }
                        PIXEL00_2 PIXEL01_1 PIXEL02_1M PIXEL10_1 PIXEL11 break;
                    }
                    case 200: case 204: {
                        if (DIFF(8, 4)) { PIXEL10_C PIXEL20_1M PIXEL21_C PIXEL22_1R } else { PIXEL10_1 PIXEL20_5 PIXEL21_6 PIXEL22_2 }
                        PIXEL00_1M PIXEL01_1 PIXEL02_2 PIXEL11 PIXEL12_1 break;
                    }
                    case 73: case 77: {
                        if (DIFF(8, 4)) { PIXEL00_1U PIXEL10_C PIXEL20_1M PIXEL21_C } else { PIXEL00_2 PIXEL10_6 PIXEL20_5 PIXEL21_1 }
                        PIXEL01_1 PIXEL02_2 PIXEL11 PIXEL12_1 PIXEL22_1M break;
                    }
                    case 42: case 170: {
                        if (DIFF(4, 2)) { PIXEL00_1M PIXEL01_C PIXEL10_C PIXEL20_1D } else { PIXEL00_5 PIXEL01_1 PIXEL10_6 PIXEL20_2 }
                        PIXEL02_1M PIXEL11 PIXEL12_1 PIXEL21_1 PIXEL22_2 break;
                    }
                    case 14: case 142: {
                        if (DIFF(4, 2)) { PIXEL00_1M PIXEL01_C PIXEL02_1R PIXEL10_C } else { PIXEL00_5 PIXEL01_6 PIXEL02_2 PIXEL10_1 }
                        PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_1 PIXEL22_2 break;
                    }
                    case 67: {
                        PIXEL00_1L PIXEL01_C PIXEL02_1M PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_C
                        PIXEL22_1M break;
                    }
                    case 70: {
                        PIXEL00_1M PIXEL01_C PIXEL02_1R PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_C
                        PIXEL22_1M break;
                    }
                    case 28: {
                        PIXEL00_1M PIXEL01_1 PIXEL02_1U PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1M PIXEL21_1
                        PIXEL22_1M break;
                    }
                    case 152: {
                        PIXEL00_1M PIXEL01_1 PIXEL02_1M PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1M PIXEL21_1
                        PIXEL22_1D break;
                    }
                    case 194: {
                        PIXEL00_1M PIXEL01_C PIXEL02_1M PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_C
                        PIXEL22_1R break;
                    }
                    case 98: {
                        PIXEL00_1M PIXEL01_C PIXEL02_1M PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1L PIXEL21_C
                        PIXEL22_1M break;
                    }
                    case 56: {
                        PIXEL00_1M PIXEL01_1 PIXEL02_1M PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1D PIXEL21_1
                        PIXEL22_1M break;
                    }
                    case 25: {
                        PIXEL00_1U PIXEL01_1 PIXEL02_1M PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1M PIXEL21_1
                        PIXEL22_1M break;
                    }
                    case 26: case 31: {
                        if (DIFF(4, 2)) { PIXEL00_C PIXEL10_C } else { PIXEL00_4 PIXEL10_3 } PIXEL01_C
                        if (DIFF(2, 6)) { PIXEL02_C PIXEL12_C } else { PIXEL02_4 PIXEL12_3 } PIXEL11
                        PIXEL20_1M PIXEL21_1 PIXEL22_1M break;
                    }
                    case 82: case 214: {
                        PIXEL00_1M if (DIFF(2, 6)) { PIXEL01_C PIXEL02_C } else { PIXEL01_3 PIXEL02_4 }
                        PIXEL10_1 PIXEL11 PIXEL12_C PIXEL20_1M
                        if (DIFF(6, 8)) { PIXEL21_C PIXEL22_C } else { PIXEL21_3 PIXEL22_4 } break;
                    }
                    case 88: case 248: {
                        PIXEL00_1M PIXEL01_1 PIXEL02_1M PIXEL11
                        if (DIFF(8, 4)) { PIXEL10_C PIXEL20_C } else { PIXEL10_3 PIXEL20_4 } PIXEL21_C
                        if (DIFF(6, 8)) { PIXEL12_C PIXEL22_C } else { PIXEL12_3 PIXEL22_4 } break;
                    }
                    case 74: case 107: {
                        if (DIFF(4, 2)) { PIXEL00_C PIXEL01_C } else { PIXEL00_4 PIXEL01_3 } PIXEL02_1M
                        PIXEL10_C PIXEL11 PIXEL12_1
                        if (DIFF(8, 4)) { PIXEL20_C PIXEL21_C } else { PIXEL20_4 PIXEL21_3 } PIXEL22_1M break;
                    }
                    case 27: {
                        if (DIFF(4, 2)) { PIXEL00_C PIXEL01_C PIXEL10_C } else { PIXEL00_4 PIXEL01_3 PIXEL10_3 }
                        PIXEL02_1M PIXEL11 PIXEL12_C PIXEL20_1M PIXEL21_1 PIXEL22_1M break;
                    }
                    case 86: {
                        PIXEL00_1M
                        if (DIFF(2, 6)) { PIXEL01_C PIXEL02_C PIXEL12_C } else { PIXEL01_3 PIXEL02_4 PIXEL12_3 }
                        PIXEL10_1 PIXEL11 PIXEL20_1M PIXEL21_C PIXEL22_1M break;
                    }
                    case 216: {
                        PIXEL00_1M PIXEL01_1 PIXEL02_1M PIXEL10_C PIXEL11 PIXEL20_1M
                        if (DIFF(6, 8)) { PIXEL12_C PIXEL21_C PIXEL22_C } else { PIXEL12_3 PIXEL21_3 PIXEL22_4 }
                        break;
                    }
                    case 106: {
                        PIXEL00_1M PIXEL01_C PIXEL02_1M PIXEL11 PIXEL12_1
                        if (DIFF(8, 4)) { PIXEL10_C PIXEL20_C PIXEL21_C } else { PIXEL10_3 PIXEL20_4 PIXEL21_3 }
                        PIXEL22_1M break;
                    }
                    case 30: {
                        PIXEL00_1M
                        if (DIFF(2, 6)) { PIXEL01_C PIXEL02_C PIXEL12_C } else { PIXEL01_3 PIXEL02_4 PIXEL12_3 }
                        PIXEL10_C PIXEL11 PIXEL20_1M PIXEL21_1 PIXEL22_1M break;
                    }
                    case 210: {
                        PIXEL00_1M PIXEL01_C PIXEL02_1M PIXEL10_1 PIXEL11 PIXEL20_1M
                        if (DIFF(6, 8)) { PIXEL12_C PIXEL21_C PIXEL22_C } else { PIXEL12_3 PIXEL21_3 PIXEL22_4 }
                        break;
                    }
                    case 120: {
                        PIXEL00_1M PIXEL01_1 PIXEL02_1M PIXEL11 PIXEL12_C
                        if (DIFF(8, 4)) { PIXEL10_C PIXEL20_C PIXEL21_C } else { PIXEL10_3 PIXEL20_4 PIXEL21_3 }
                        PIXEL22_1M break;
                    }
                    case 75: {
                        if (DIFF(4, 2)) { PIXEL00_C PIXEL01_C PIXEL10_C } else { PIXEL00_4 PIXEL01_3 PIXEL10_3 }
                        PIXEL02_1M PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_C PIXEL22_1M break;
                    }
                    case 29: {
                        PIXEL00_1U PIXEL01_1 PIXEL02_1U PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1M PIXEL21_1
                        PIXEL22_1M break;
                    }
                    case 198: {
                        PIXEL00_1M PIXEL01_C PIXEL02_1R PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_C
                        PIXEL22_1R break;
                    }
                    case 184: {
                        PIXEL00_1M PIXEL01_1 PIXEL02_1M PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1D PIXEL21_1
                        PIXEL22_1D break;
                    }
                    case 99: {
                        PIXEL00_1L PIXEL01_C PIXEL02_1M PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1L PIXEL21_C
                        PIXEL22_1M break;
                    }
                    case 57: {
                        PIXEL00_1U PIXEL01_1 PIXEL02_1M PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1D PIXEL21_1
                        PIXEL22_1M break;
                    }
                    case 71: {
                        PIXEL00_1L PIXEL01_C PIXEL02_1R PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_C
                        PIXEL22_1M break;
                    }
                    case 156: {
                        PIXEL00_1M PIXEL01_1 PIXEL02_1U PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1M PIXEL21_1
                        PIXEL22_1D break;
                    }
                    case 226: {
                        PIXEL00_1M PIXEL01_C PIXEL02_1M PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1L PIXEL21_C
                        PIXEL22_1R break;
                    }
                    case 60: {
                        PIXEL00_1M PIXEL01_1 PIXEL02_1U PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1D PIXEL21_1
                        PIXEL22_1M break;
                    }
                    case 195: {
                        PIXEL00_1L PIXEL01_C PIXEL02_1M PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_C
                        PIXEL22_1R break;
                    }
                    case 102: {
                        PIXEL00_1M PIXEL01_C PIXEL02_1R PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1L PIXEL21_C
                        PIXEL22_1M break;
                    }
                    case 153: {
                        PIXEL00_1U PIXEL01_1 PIXEL02_1M PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1M PIXEL21_1
                        PIXEL22_1D break;
                    }
                    case 58: {
                        if (DIFF(4, 2)) { PIXEL00_1M } else { PIXEL00_2 } PIXEL01_C
                        if (DIFF(2, 6)) { PIXEL02_1M } else { PIXEL02_2 } PIXEL10_C PIXEL11 PIXEL12_C
                        PIXEL20_1D PIXEL21_1 PIXEL22_1M break;
                    }
                    case 83: {
                        PIXEL00_1L PIXEL01_C if (DIFF(2, 6)) { PIXEL02_1M } else { PIXEL02_2 } PIXEL10_1
                        PIXEL11 PIXEL12_C PIXEL20_1M PIXEL21_C
                        if (DIFF(6, 8)) { PIXEL22_1M } else { PIXEL22_2 } break;
                    }
                    case 92: {
                        PIXEL00_1M PIXEL01_1 PIXEL02_1U PIXEL10_C PIXEL11 PIXEL12_C
                        if (DIFF(8, 4)) { PIXEL20_1M } else { PIXEL20_2 } PIXEL21_C
                        if (DIFF(6, 8)) { PIXEL22_1M } else { PIXEL22_2 } break;
                    }
                    case 202: {
                        if (DIFF(4, 2)) { PIXEL00_1M } else { PIXEL00_2 } PIXEL01_C PIXEL02_1M PIXEL10_C
                        PIXEL11 PIXEL12_1 if (DIFF(8, 4)) { PIXEL20_1M } else { PIXEL20_2 } PIXEL21_C
                        PIXEL22_1R break;
                    }
                    case 78: {
                        if (DIFF(4, 2)) { PIXEL00_1M } else { PIXEL00_2 } PIXEL01_C PIXEL02_1R PIXEL10_C
                        PIXEL11 PIXEL12_1 if (DIFF(8, 4)) { PIXEL20_1M } else { PIXEL20_2 } PIXEL21_C
                        PIXEL22_1M break;
                    }
                    case 154: {
                        if (DIFF(4, 2)) { PIXEL00_1M } else { PIXEL00_2 } PIXEL01_C
                        if (DIFF(2, 6)) { PIXEL02_1M } else { PIXEL02_2 } PIXEL10_C PIXEL11 PIXEL12_C
                        PIXEL20_1M PIXEL21_1 PIXEL22_1D break;
                    }
                    case 114: {
                        PIXEL00_1M PIXEL01_C if (DIFF(2, 6)) { PIXEL02_1M } else { PIXEL02_2 } PIXEL10_1
                        PIXEL11 PIXEL12_C PIXEL20_1L PIXEL21_C
                        if (DIFF(6, 8)) { PIXEL22_1M } else { PIXEL22_2 } break;
                    }
                    case 89: {
                        PIXEL00_1U PIXEL01_1 PIXEL02_1M PIXEL10_C PIXEL11 PIXEL12_C
                        if (DIFF(8, 4)) { PIXEL20_1M } else { PIXEL20_2 } PIXEL21_C
                        if (DIFF(6, 8)) { PIXEL22_1M } else { PIXEL22_2 } break;
                    }
                    case 90: {
                        if (DIFF(4, 2)) { PIXEL00_1M } else { PIXEL00_2 } PIXEL01_C
                        if (DIFF(2, 6)) { PIXEL02_1M } else { PIXEL02_2 } PIXEL10_C PIXEL11 PIXEL12_C
                        if (DIFF(8, 4)) { PIXEL20_1M } else { PIXEL20_2 } PIXEL21_C
                        if (DIFF(6, 8)) { PIXEL22_1M } else { PIXEL22_2 } break;
                    }
                    case 55: case 23: {
                        if (DIFF(2, 6)) { PIXEL00_1L PIXEL01_C PIXEL02_C PIXEL12_C } else { PIXEL00_2 PIXEL01_6 PIXEL02_5 PIXEL12_1 }
                        PIXEL10_1 PIXEL11 PIXEL20_2 PIXEL21_1 PIXEL22_1M break;
                    }
                    case 182: case 150: {
                        if (DIFF(2, 6)) { PIXEL01_C PIXEL02_C PIXEL12_C PIXEL22_1D } else { PIXEL01_1 PIXEL02_5 PIXEL12_6 PIXEL22_2 }
                        PIXEL00_1M PIXEL10_1 PIXEL11 PIXEL20_2 PIXEL21_1 break;
                    }
                    case 213: case 212: {
                        if (DIFF(6, 8)) { PIXEL02_1U PIXEL12_C PIXEL21_C PIXEL22_C } else { PIXEL02_2 PIXEL12_6 PIXEL21_1 PIXEL22_5 }
                        PIXEL00_2 PIXEL01_1 PIXEL10_1 PIXEL11 PIXEL20_1M break;
                    }
                    case 241: case 240: {
                        if (DIFF(6, 8)) { PIXEL12_C PIXEL20_1L PIXEL21_C PIXEL22_C } else { PIXEL12_1 PIXEL20_2 PIXEL21_6 PIXEL22_5 }
                        PIXEL00_2 PIXEL01_1 PIXEL02_1M PIXEL10_1 PIXEL11 break;
                    }
                    case 236: case 232: {
                        if (DIFF(8, 4)) { PIXEL10_C PIXEL20_C PIXEL21_C PIXEL22_1R } else { PIXEL10_1 PIXEL20_5 PIXEL21_6 PIXEL22_2 }
                        PIXEL00_1M PIXEL01_1 PIXEL02_2 PIXEL11 PIXEL12_1 break;
                    }
                    case 109: case 105: {
                        if (DIFF(8, 4)) { PIXEL00_1U PIXEL10_C PIXEL20_C PIXEL21_C } else { PIXEL00_2 PIXEL10_6 PIXEL20_5 PIXEL21_1 }
                        PIXEL01_1 PIXEL02_2 PIXEL11 PIXEL12_1 PIXEL22_1M break;
                    }
                    case 171: case 43: {
                        if (DIFF(4, 2)) { PIXEL00_C PIXEL01_C PIXEL10_C PIXEL20_1D } else { PIXEL00_5 PIXEL01_1 PIXEL10_6 PIXEL20_2 }
                        PIXEL02_1M PIXEL11 PIXEL12_1 PIXEL21_1 PIXEL22_2 break;
                    }
                    case 143: case 15: {
                        if (DIFF(4, 2)) { PIXEL00_C PIXEL01_C PIXEL02_1R PIXEL10_C } else { PIXEL00_5 PIXEL01_6 PIXEL02_2 PIXEL10_1 }
                        PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_1 PIXEL22_2 break;
                    }
                    case 124: {
                        PIXEL00_1M PIXEL01_1 PIXEL02_1U PIXEL11 PIXEL12_C
                        if (DIFF(8, 4)) { PIXEL10_C PIXEL20_C PIXEL21_C } else { PIXEL10_3 PIXEL20_4 PIXEL21_3 }
                        PIXEL22_1M break;
                    }
                    case 203: {
                        if (DIFF(4, 2)) { PIXEL00_C PIXEL01_C PIXEL10_C } else { PIXEL00_4 PIXEL01_3 PIXEL10_3 }
                        PIXEL02_1M PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_C PIXEL22_1R break;
                    }
                    case 62: {
                        PIXEL00_1M
                        if (DIFF(2, 6)) { PIXEL01_C PIXEL02_C PIXEL12_C } else { PIXEL01_3 PIXEL02_4 PIXEL12_3 }
                        PIXEL10_C PIXEL11 PIXEL20_1D PIXEL21_1 PIXEL22_1M break;
                    }
                    case 211: {
                        PIXEL00_1L PIXEL01_C PIXEL02_1M PIXEL10_1 PIXEL11 PIXEL20_1M
                        if (DIFF(6, 8)) { PIXEL12_C PIXEL21_C PIXEL22_C } else { PIXEL12_3 PIXEL21_3 PIXEL22_4 }
                        break;
                    }
                    case 118: {
                        PIXEL00_1M
                        if (DIFF(2, 6)) { PIXEL01_C PIXEL02_C PIXEL12_C } else { PIXEL01_3 PIXEL02_4 PIXEL12_3 }
                        PIXEL10_1 PIXEL11 PIXEL20_1L PIXEL21_C PIXEL22_1M break;
                    }
                    case 217: {
                        PIXEL00_1U PIXEL01_1 PIXEL02_1M PIXEL10_C PIXEL11 PIXEL20_1M
                        if (DIFF(6, 8)) { PIXEL12_C PIXEL21_C PIXEL22_C } else { PIXEL12_3 PIXEL21_3 PIXEL22_4 }
                        break;
                    }
                    case 110: {
                        PIXEL00_1M PIXEL01_C PIXEL02_1R PIXEL11 PIXEL12_1
                        if (DIFF(8, 4)) { PIXEL10_C PIXEL20_C PIXEL21_C } else { PIXEL10_3 PIXEL20_4 PIXEL21_3 }
                        PIXEL22_1M break;
                    }
                    case 155: {
                        if (DIFF(4, 2)) { PIXEL00_C PIXEL01_C PIXEL10_C } else { PIXEL00_4 PIXEL01_3 PIXEL10_3 }
                        PIXEL02_1M PIXEL11 PIXEL12_C PIXEL20_1M PIXEL21_1 PIXEL22_1D break;
                    }
                    case 188: {
                        PIXEL00_1M PIXEL01_1 PIXEL02_1U PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1D PIXEL21_1
                        PIXEL22_1D break;
                    }
                    case 185: {
                        PIXEL00_1U PIXEL01_1 PIXEL02_1M PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1D PIXEL21_1
                        PIXEL22_1D break;
                    }
                    case 61: {
                        PIXEL00_1U PIXEL01_1 PIXEL02_1U PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1D PIXEL21_1
                        PIXEL22_1M break;
                    }
                    case 157: {
                        PIXEL00_1U PIXEL01_1 PIXEL02_1U PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1M PIXEL21_1
                        PIXEL22_1D break;
                    }
                    case 103: {
                        PIXEL00_1L PIXEL01_C PIXEL02_1R PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1L PIXEL21_C
                        PIXEL22_1M break;
                    }
                    case 227: {
                        PIXEL00_1L PIXEL01_C PIXEL02_1M PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1L PIXEL21_C
                        PIXEL22_1R break;
                    }
                    case 230: {
                        PIXEL00_1M PIXEL01_C PIXEL02_1R PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1L PIXEL21_C
                        PIXEL22_1R break;
                    }
                    case 199: {
                        PIXEL00_1L PIXEL01_C PIXEL02_1R PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_C
                        PIXEL22_1R break;
                    }
                    case 220: {
                        PIXEL00_1M PIXEL01_1 PIXEL02_1U PIXEL10_C PIXEL11
                        if (DIFF(8, 4)) { PIXEL20_1M } else { PIXEL20_2 }
                        if (DIFF(6, 8)) { PIXEL12_C PIXEL21_C PIXEL22_C } else { PIXEL12_3 PIXEL21_3 PIXEL22_4 }
                        break;
                    }
                    case 158: {
                        if (DIFF(4, 2)) { PIXEL00_1M } else { PIXEL00_2 }
                        if (DIFF(2, 6)) { PIXEL01_C PIXEL02_C PIXEL12_C } else { PIXEL01_3 PIXEL02_4 PIXEL12_3 }
                        PIXEL10_C PIXEL11 PIXEL20_1M PIXEL21_1 PIXEL22_1D break;
                    }
                    case 234: {
                        if (DIFF(4, 2)) { PIXEL00_1M } else { PIXEL00_2 } PIXEL01_C PIXEL02_1M PIXEL11
                        PIXEL12_1
                        if (DIFF(8, 4)) { PIXEL10_C PIXEL20_C PIXEL21_C } else { PIXEL10_3 PIXEL20_4 PIXEL21_3 }
                        PIXEL22_1R break;
                    }
                    case 242: {
                        PIXEL00_1M PIXEL01_C if (DIFF(2, 6)) { PIXEL02_1M } else { PIXEL02_2 } PIXEL10_1
                        PIXEL11 PIXEL20_1L
                        if (DIFF(6, 8)) { PIXEL12_C PIXEL21_C PIXEL22_C } else { PIXEL12_3 PIXEL21_3 PIXEL22_4 }
                        break;
                    }
                    case 59: {
                        if (DIFF(4, 2)) { PIXEL00_C PIXEL01_C PIXEL10_C } else { PIXEL00_4 PIXEL01_3 PIXEL10_3 }
                        if (DIFF(2, 6)) { PIXEL02_1M } else { PIXEL02_2 } PIXEL11 PIXEL12_C PIXEL20_1D
                        PIXEL21_1 PIXEL22_1M break;
                    }
                    case 121: {
                        PIXEL00_1U PIXEL01_1 PIXEL02_1M PIXEL11 PIXEL12_C
                        if (DIFF(8, 4)) { PIXEL10_C PIXEL20_C PIXEL21_C } else { PIXEL10_3 PIXEL20_4 PIXEL21_3 }
                        if (DIFF(6, 8)) { PIXEL22_1M } else { PIXEL22_2 } break;
                    }
                    case 87: {
                        PIXEL00_1L
                        if (DIFF(2, 6)) { PIXEL01_C PIXEL02_C PIXEL12_C } else { PIXEL01_3 PIXEL02_4 PIXEL12_3 }
                        PIXEL10_1 PIXEL11 PIXEL20_1M PIXEL21_C
                        if (DIFF(6, 8)) { PIXEL22_1M } else { PIXEL22_2 } break;
                    }
                    case 79: {
                        if (DIFF(4, 2)) { PIXEL00_C PIXEL01_C PIXEL10_C } else { PIXEL00_4 PIXEL01_3 PIXEL10_3 }
                        PIXEL02_1R PIXEL11 PIXEL12_1 if (DIFF(8, 4)) { PIXEL20_1M } else { PIXEL20_2 }
                        PIXEL21_C PIXEL22_1M break;
                    }
                    case 122: {
                        if (DIFF(4, 2)) { PIXEL00_1M } else { PIXEL00_2 } PIXEL01_C
                        if (DIFF(2, 6)) { PIXEL02_1M } else { PIXEL02_2 } PIXEL11 PIXEL12_C
                        if (DIFF(8, 4)) { PIXEL10_C PIXEL20_C PIXEL21_C } else { PIXEL10_3 PIXEL20_4 PIXEL21_3 }
                        if (DIFF(6, 8)) { PIXEL22_1M } else { PIXEL22_2 } break;
                    }
                    case 94: {
                        if (DIFF(4, 2)) { PIXEL00_1M } else { PIXEL00_2 }
                        if (DIFF(2, 6)) { PIXEL01_C PIXEL02_C PIXEL12_C } else { PIXEL01_3 PIXEL02_4 PIXEL12_3 }
                        PIXEL10_C PIXEL11 if (DIFF(8, 4)) { PIXEL20_1M } else { PIXEL20_2 } PIXEL21_C
                        if (DIFF(6, 8)) { PIXEL22_1M } else { PIXEL22_2 } break;
                    }
                    case 218: {
                        if (DIFF(4, 2)) { PIXEL00_1M } else { PIXEL00_2 } PIXEL01_C
                        if (DIFF(2, 6)) { PIXEL02_1M } else { PIXEL02_2 } PIXEL10_C PIXEL11
                        if (DIFF(8, 4)) { PIXEL20_1M } else { PIXEL20_2 }
                        if (DIFF(6, 8)) { PIXEL12_C PIXEL21_C PIXEL22_C } else { PIXEL12_3 PIXEL21_3 PIXEL22_4 }
                        break;
                    }
                    case 91: {
                        if (DIFF(4, 2)) { PIXEL00_C PIXEL01_C PIXEL10_C } else { PIXEL00_4 PIXEL01_3 PIXEL10_3 }
                        if (DIFF(2, 6)) { PIXEL02_1M } else { PIXEL02_2 } PIXEL11 PIXEL12_C
                        if (DIFF(8, 4)) { PIXEL20_1M } else { PIXEL20_2 } PIXEL21_C
                        if (DIFF(6, 8)) { PIXEL22_1M } else { PIXEL22_2 } break;
                    }
                    case 229: {
                        PIXEL00_2 PIXEL01_1 PIXEL02_2 PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1L PIXEL21_C
                        PIXEL22_1R break;
                    }
                    case 167: {
                        PIXEL00_1L PIXEL01_C PIXEL02_1R PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_2 PIXEL21_1
                        PIXEL22_2 break;
                    }
                    case 173: {
                        PIXEL00_1U PIXEL01_1 PIXEL02_2 PIXEL10_C PIXEL11 PIXEL12_1 PIXEL20_1D PIXEL21_1
                        PIXEL22_2 break;
                    }
                    case 181: {
                        PIXEL00_2 PIXEL01_1 PIXEL02_1U PIXEL10_1 PIXEL11 PIXEL12_C PIXEL20_2 PIXEL21_1
                        PIXEL22_1D break;
                    }
                    case 186: {
                        if (DIFF(4, 2)) { PIXEL00_1M } else { PIXEL00_2 } PIXEL01_C
                        if (DIFF(2, 6)) { PIXEL02_1M } else { PIXEL02_2 } PIXEL10_C PIXEL11 PIXEL12_C
                        PIXEL20_1D PIXEL21_1 PIXEL22_1D break;
                    }
                    case 115: {
                        PIXEL00_1L PIXEL01_C if (DIFF(2, 6)) { PIXEL02_1M } else { PIXEL02_2 } PIXEL10_1
                        PIXEL11 PIXEL12_C PIXEL20_1L PIXEL21_C
                        if (DIFF(6, 8)) { PIXEL22_1M } else { PIXEL22_2 } break;
                    }
                    case 93: {
                        PIXEL00_1U PIXEL01_1 PIXEL02_1U PIXEL10_C PIXEL11 PIXEL12_C
                        if (DIFF(8, 4)) { PIXEL20_1M } else { PIXEL20_2 } PIXEL21_C
                        if (DIFF(6, 8)) { PIXEL22_1M } else { PIXEL22_2 } break;
                    }
                    case 206: {
                        if (DIFF(4, 2)) { PIXEL00_1M } else { PIXEL00_2 } PIXEL01_C PIXEL02_1R PIXEL10_C
                        PIXEL11 PIXEL12_1 if (DIFF(8, 4)) { PIXEL20_1M } else { PIXEL20_2 } PIXEL21_C
                        PIXEL22_1R break;
                    }
                    case 205: case 201: {
                        PIXEL00_1U PIXEL01_1 PIXEL02_2 PIXEL10_C PIXEL11 PIXEL12_1
                        if (DIFF(8, 4)) { PIXEL20_1M } else { PIXEL20_2 } PIXEL21_C PIXEL22_1R break;
                    }
                    case 174: case 46: {
                        if (DIFF(4, 2)) { PIXEL00_1M } else { PIXEL00_2 } PIXEL01_C PIXEL02_1R PIXEL10_C
                        PIXEL11 PIXEL12_1 PIXEL20_1D PIXEL21_1 PIXEL22_2 break;
                    }
                    case 179: case 147: {
                        PIXEL00_1L PIXEL01_C if (DIFF(2, 6)) { PIXEL02_1M } else { PIXEL02_2 } PIXEL10_1
                        PIXEL11 PIXEL12_C PIXEL20_2 PIXEL21_1 PIXEL22_1D break;
                    }
                    case 117: case 116: {
                        PIXEL00_2 PIXEL01_1 PIXEL02_1U PIXEL10_1 PIXEL11 PIXEL12_C PIXEL20_1L PIXEL21_C
                        if (DIFF(6, 8)) { PIXEL22_1M } else { PIXEL22_2 } break;
                    }
                    case 189: {
                        PIXEL00_1U PIXEL01_1 PIXEL02_1U PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1D PIXEL21_1
                        PIXEL22_1D break;
                    }
                    case 231: {
                        PIXEL00_1L PIXEL01_C PIXEL02_1R PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1L PIXEL21_C
                        PIXEL22_1R break;
                    }
                    case 126: {
                        PIXEL00_1M
                        if (DIFF(2, 6)) { PIXEL01_C PIXEL02_C PIXEL12_C } else { PIXEL01_3 PIXEL02_4 PIXEL12_3 }
                        PIXEL11
                        if (DIFF(8, 4)) { PIXEL10_C PIXEL20_C PIXEL21_C } else { PIXEL10_3 PIXEL20_4 PIXEL21_3 }
                        PIXEL22_1M break;
                    }
                    case 219: {
                        if (DIFF(4, 2)) { PIXEL00_C PIXEL01_C PIXEL10_C } else { PIXEL00_4 PIXEL01_3 PIXEL10_3 }
                        PIXEL02_1M PIXEL11 PIXEL20_1M
                        if (DIFF(6, 8)) { PIXEL12_C PIXEL21_C PIXEL22_C } else { PIXEL12_3 PIXEL21_3 PIXEL22_4 }
                        break;
                    }
                    case 125: {
                        if (DIFF(8, 4)) { PIXEL00_1U PIXEL10_C PIXEL20_C PIXEL21_C } else { PIXEL00_2 PIXEL10_6 PIXEL20_5 PIXEL21_1 }
                        PIXEL01_1 PIXEL02_1U PIXEL11 PIXEL12_C PIXEL22_1M break;
                    }
                    case 221: {
                        if (DIFF(6, 8)) { PIXEL02_1U PIXEL12_C PIXEL21_C PIXEL22_C } else { PIXEL02_2 PIXEL12_6 PIXEL21_1 PIXEL22_5 }
                        PIXEL00_1U PIXEL01_1 PIXEL10_C PIXEL11 PIXEL20_1M break;
                    }
                    case 207: {
                        if (DIFF(4, 2)) { PIXEL00_C PIXEL01_C PIXEL02_1R PIXEL10_C } else { PIXEL00_5 PIXEL01_6 PIXEL02_2 PIXEL10_1 }
                        PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_C PIXEL22_1R break;
                    }
                    case 238: {
                        if (DIFF(8, 4)) { PIXEL10_C PIXEL20_C PIXEL21_C PIXEL22_1R } else { PIXEL10_1 PIXEL20_5 PIXEL21_6 PIXEL22_2 }
                        PIXEL00_1M PIXEL01_C PIXEL02_1R PIXEL11 PIXEL12_1 break;
                    }
                    case 190: {
                        if (DIFF(2, 6)) { PIXEL01_C PIXEL02_C PIXEL12_C PIXEL22_1D } else { PIXEL01_1 PIXEL02_5 PIXEL12_6 PIXEL22_2 }
                        PIXEL00_1M PIXEL10_C PIXEL11 PIXEL20_1D PIXEL21_1 break;
                    }
                    case 187: {
                        if (DIFF(4, 2)) { PIXEL00_C PIXEL01_C PIXEL10_C PIXEL20_1D } else { PIXEL00_5 PIXEL01_1 PIXEL10_6 PIXEL20_2 }
                        PIXEL02_1M PIXEL11 PIXEL12_C PIXEL21_1 PIXEL22_1D break;
                    }
                    case 243: {
                        if (DIFF(6, 8)) { PIXEL12_C PIXEL20_1L PIXEL21_C PIXEL22_C } else { PIXEL12_1 PIXEL20_2 PIXEL21_6 PIXEL22_5 }
                        PIXEL00_1L PIXEL01_C PIXEL02_1M PIXEL10_1 PIXEL11 break;
                    }
                    case 119: {
                        if (DIFF(2, 6)) { PIXEL00_1L PIXEL01_C PIXEL02_C PIXEL12_C } else { PIXEL00_2 PIXEL01_6 PIXEL02_5 PIXEL12_1 }
                        PIXEL10_1 PIXEL11 PIXEL20_1L PIXEL21_C PIXEL22_1M break;
                    }
                    case 237: case 233: {
                        PIXEL00_1U PIXEL01_1 PIXEL02_2 PIXEL10_C PIXEL11 PIXEL12_1
                        if (DIFF(8, 4)) { PIXEL20_C } else { PIXEL20_2 } PIXEL21_C PIXEL22_1R break;
                    }
                    case 175: case 47: {
                        if (DIFF(4, 2)) { PIXEL00_C } else { PIXEL00_2 } PIXEL01_C PIXEL02_1R PIXEL10_C
                        PIXEL11 PIXEL12_1 PIXEL20_1D PIXEL21_1 PIXEL22_2 break;
                    }
                    case 183: case 151: {
                        PIXEL00_1L PIXEL01_C if (DIFF(2, 6)) { PIXEL02_C } else { PIXEL02_2 } PIXEL10_1
                        PIXEL11 PIXEL12_C PIXEL20_2 PIXEL21_1 PIXEL22_1D break;
                    }
                    case 245: case 244: {
                        PIXEL00_2 PIXEL01_1 PIXEL02_1U PIXEL10_1 PIXEL11 PIXEL12_C PIXEL20_1L PIXEL21_C
                        if (DIFF(6, 8)) { PIXEL22_C } else { PIXEL22_2 } break;
                    }
                    case 250: {
                        PIXEL00_1M PIXEL01_C PIXEL02_1M PIXEL11
                        if (DIFF(8, 4)) { PIXEL10_C PIXEL20_C } else { PIXEL10_3 PIXEL20_4 } PIXEL21_C
                        if (DIFF(6, 8)) { PIXEL12_C PIXEL22_C } else { PIXEL12_3 PIXEL22_4 } break;
                    }
                    case 123: {
                        if (DIFF(4, 2)) { PIXEL00_C PIXEL01_C } else { PIXEL00_4 PIXEL01_3 } PIXEL02_1M
                        PIXEL10_C PIXEL11 PIXEL12_C
                        if (DIFF(8, 4)) { PIXEL20_C PIXEL21_C } else { PIXEL20_4 PIXEL21_3 } PIXEL22_1M break;
                    }
                    case 95: {
                        if (DIFF(4, 2)) { PIXEL00_C PIXEL10_C } else { PIXEL00_4 PIXEL10_3 } PIXEL01_C
                        if (DIFF(2, 6)) { PIXEL02_C PIXEL12_C } else { PIXEL02_4 PIXEL12_3 } PIXEL11
                        PIXEL20_1M PIXEL21_C PIXEL22_1M break;
                    }
                    case 222: {
                        PIXEL00_1M if (DIFF(2, 6)) { PIXEL01_C PIXEL02_C } else { PIXEL01_3 PIXEL02_4 }
                        PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1M
                        if (DIFF(6, 8)) { PIXEL21_C PIXEL22_C } else { PIXEL21_3 PIXEL22_4 } break;
                    }
                    case 252: {
                        PIXEL00_1M PIXEL01_1 PIXEL02_1U PIXEL11 PIXEL12_C
                        if (DIFF(8, 4)) { PIXEL10_C PIXEL20_C } else { PIXEL10_3 PIXEL20_4 } PIXEL21_C
                        if (DIFF(6, 8)) { PIXEL22_C } else { PIXEL22_2 } break;
                    }
                    case 249: {
                        PIXEL00_1U PIXEL01_1 PIXEL02_1M PIXEL10_C PIXEL11
                        if (DIFF(8, 4)) { PIXEL20_C } else { PIXEL20_2 } PIXEL21_C
                        if (DIFF(6, 8)) { PIXEL12_C PIXEL22_C } else { PIXEL12_3 PIXEL22_4 } break;
                    }
                    case 235: {
                        if (DIFF(4, 2)) { PIXEL00_C PIXEL01_C } else { PIXEL00_4 PIXEL01_3 } PIXEL02_1M
                        PIXEL10_C PIXEL11 PIXEL12_1 if (DIFF(8, 4)) { PIXEL20_C } else { PIXEL20_2 } PIXEL21_C
                        PIXEL22_1R break;
                    }
                    case 111: {
                        if (DIFF(4, 2)) { PIXEL00_C } else { PIXEL00_2 } PIXEL01_C PIXEL02_1R PIXEL10_C
                        PIXEL11 PIXEL12_1 if (DIFF(8, 4)) { PIXEL20_C PIXEL21_C } else { PIXEL20_4 PIXEL21_3 }
                        PIXEL22_1M break;
                    }
                    case 63: {
                        if (DIFF(4, 2)) { PIXEL00_C } else { PIXEL00_2 } PIXEL01_C
                        if (DIFF(2, 6)) { PIXEL02_C PIXEL12_C } else { PIXEL02_4 PIXEL12_3 } PIXEL10_C PIXEL11
                        PIXEL20_1D PIXEL21_1 PIXEL22_1M break;
                    }
                    case 159: {
                        if (DIFF(4, 2)) { PIXEL00_C PIXEL10_C } else { PIXEL00_4 PIXEL10_3 } PIXEL01_C
                        if (DIFF(2, 6)) { PIXEL02_C } else { PIXEL02_2 } PIXEL11 PIXEL12_C PIXEL20_1M
                        PIXEL21_1 PIXEL22_1D break;
                    }
                    case 215: {
                        PIXEL00_1L PIXEL01_C if (DIFF(2, 6)) { PIXEL02_C } else { PIXEL02_2 } PIXEL10_1
                        PIXEL11 PIXEL12_C PIXEL20_1M
                        if (DIFF(6, 8)) { PIXEL21_C PIXEL22_C } else { PIXEL21_3 PIXEL22_4 } break;
                    }
                    case 246: {
                        PIXEL00_1M if (DIFF(2, 6)) { PIXEL01_C PIXEL02_C } else { PIXEL01_3 PIXEL02_4 }
                        PIXEL10_1 PIXEL11 PIXEL12_C PIXEL20_1L PIXEL21_C
                        if (DIFF(6, 8)) { PIXEL22_C } else { PIXEL22_2 } break;
                    }
                    case 254: {
                        PIXEL00_1M if (DIFF(2, 6)) { PIXEL01_C PIXEL02_C } else { PIXEL01_3 PIXEL02_4 }
                        PIXEL11 if (DIFF(8, 4)) { PIXEL10_C PIXEL20_C } else { PIXEL10_3 PIXEL20_4 }
                        if (DIFF(6, 8)) { PIXEL12_C PIXEL21_C PIXEL22_C } else { PIXEL12_3 PIXEL21_3 PIXEL22_2 }
                        break;
                    }
                    case 253: {
                        PIXEL00_1U PIXEL01_1 PIXEL02_1U PIXEL10_C PIXEL11 PIXEL12_C
                        if (DIFF(8, 4)) { PIXEL20_C } else { PIXEL20_2 } PIXEL21_C
                        if (DIFF(6, 8)) { PIXEL22_C } else { PIXEL22_2 } break;
                    }
                    case 251: {
                        if (DIFF(4, 2)) { PIXEL00_C PIXEL01_C } else { PIXEL00_4 PIXEL01_3 } PIXEL02_1M
                        PIXEL11
                        if (DIFF(8, 4)) { PIXEL10_C PIXEL20_C PIXEL21_C } else { PIXEL10_3 PIXEL20_2 PIXEL21_3 }
                        if (DIFF(6, 8)) { PIXEL12_C PIXEL22_C } else { PIXEL12_3 PIXEL22_4 } break;
                    }
                    case 239: {
                        if (DIFF(4, 2)) { PIXEL00_C } else { PIXEL00_2 } PIXEL01_C PIXEL02_1R PIXEL10_C
                        PIXEL11 PIXEL12_1 if (DIFF(8, 4)) { PIXEL20_C } else { PIXEL20_2 } PIXEL21_C
                        PIXEL22_1R break;
                    }
                    case 127: {
                        if (DIFF(4, 2)) { PIXEL00_C PIXEL01_C PIXEL10_C } else { PIXEL00_2 PIXEL01_3 PIXEL10_3 }
                        if (DIFF(2, 6)) { PIXEL02_C PIXEL12_C } else { PIXEL02_4 PIXEL12_3 } PIXEL11
                        if (DIFF(8, 4)) { PIXEL20_C PIXEL21_C } else { PIXEL20_4 PIXEL21_3 } PIXEL22_1M break;
                    }
                    case 191: {
                        if (DIFF(4, 2)) { PIXEL00_C } else { PIXEL00_2 } PIXEL01_C
                        if (DIFF(2, 6)) { PIXEL02_C } else { PIXEL02_2 } PIXEL10_C PIXEL11 PIXEL12_C
                        PIXEL20_1D PIXEL21_1 PIXEL22_1D break;
                    }
                    case 223: {
                        if (DIFF(4, 2)) { PIXEL00_C PIXEL10_C } else { PIXEL00_4 PIXEL10_3 }
                        if (DIFF(2, 6)) { PIXEL01_C PIXEL02_C PIXEL12_C } else { PIXEL01_3 PIXEL02_2 PIXEL12_3 }
                        PIXEL11 PIXEL20_1M
                        if (DIFF(6, 8)) { PIXEL21_C PIXEL22_C } else { PIXEL21_3 PIXEL22_4 } break;
                    }
                    case 247: {
                        PIXEL00_1L PIXEL01_C if (DIFF(2, 6)) { PIXEL02_C } else { PIXEL02_2 } PIXEL10_1
                        PIXEL11 PIXEL12_C PIXEL20_1L PIXEL21_C
                        if (DIFF(6, 8)) { PIXEL22_C } else { PIXEL22_2 } break;
                    }
                    case 255: {
                        if (DIFF(4, 2)) { PIXEL00_C } else { PIXEL00_2 } PIXEL01_C
                        if (DIFF(2, 6)) { PIXEL02_C } else { PIXEL02_2 } PIXEL10_C PIXEL11 PIXEL12_C
                        if (DIFF(8, 4)) { PIXEL20_C } else { PIXEL20_2 } PIXEL21_C
                        if (DIFF(6, 8)) { PIXEL22_C } else { PIXEL22_2 } break;
                    }
                }
            }
        }
    }
}

#undef PIXEL00_1M
#undef PIXEL00_1U
#undef PIXEL00_1L
#undef PIXEL00_2
#undef PIXEL00_4
#undef PIXEL00_5
#undef PIXEL00_C
#undef PIXEL01_1
#undef PIXEL01_3
#undef PIXEL01_6
#undef PIXEL01_C
#undef PIXEL02_1M
#undef PIXEL02_1U
#undef PIXEL02_1R
#undef PIXEL02_2
#undef PIXEL02_4
#undef PIXEL02_5
#undef PIXEL02_C
#undef PIXEL10_1
#undef PIXEL10_3
#undef PIXEL10_6
#undef PIXEL10_C
#undef PIXEL11
#undef PIXEL12_1
#undef PIXEL12_3
#undef PIXEL12_6
#undef PIXEL12_C
#undef PIXEL20_1M
#undef PIXEL20_1D
#undef PIXEL20_1L
#undef PIXEL20_2
#undef PIXEL20_4
#undef PIXEL20_5
#undef PIXEL20_C
#undef PIXEL21_1
#undef PIXEL21_3
#undef PIXEL21_6
#undef PIXEL21_C
#undef PIXEL22_1M
#undef PIXEL22_1D
#undef PIXEL22_1R
#undef PIXEL22_2
#undef PIXEL22_4
#undef PIXEL22_5
#undef PIXEL22_C

/* ---- hq4x: PIXEL macros and pattern switch from hq4x.c ------------- */

#define PIXEL00_0     *dp = w[5];
#define PIXEL00_11    Interp1(dp, w[5], w[4]);
#define PIXEL00_12    Interp1(dp, w[5], w[2]);
#define PIXEL00_20    Interp2(dp, w[5], w[2], w[4]);
#define PIXEL00_50    Interp5(dp, w[2], w[4]);
#define PIXEL00_80    Interp8(dp, w[5], w[1]);
#define PIXEL00_81    Interp8(dp, w[5], w[4]);
#define PIXEL00_82    Interp8(dp, w[5], w[2]);
#define PIXEL01_0     *(dp+1) = w[5];
#define PIXEL01_10    Interp1(dp+1, w[5], w[1]);
#define PIXEL01_12    Interp1(dp+1, w[5], w[2]);
#define PIXEL01_14    Interp1(dp+1, w[2], w[5]);
#define PIXEL01_21    Interp2(dp+1, w[2], w[5], w[4]);
#define PIXEL01_31    Interp3(dp+1, w[5], w[4]);
#define PIXEL01_50    Interp5(dp+1, w[2], w[5]);
#define PIXEL01_60    Interp6(dp+1, w[5], w[2], w[4]);
#define PIXEL01_61    Interp6(dp+1, w[5], w[2], w[1]);
#define PIXEL01_82    Interp8(dp+1, w[5], w[2]);
#define PIXEL01_83    Interp8(dp+1, w[2], w[4]);
#define PIXEL02_0     *(dp+2) = w[5];
#define PIXEL02_10    Interp1(dp+2, w[5], w[3]);
#define PIXEL02_11    Interp1(dp+2, w[5], w[2]);
#define PIXEL02_13    Interp1(dp+2, w[2], w[5]);
#define PIXEL02_21    Interp2(dp+2, w[2], w[5], w[6]);
#define PIXEL02_32    Interp3(dp+2, w[5], w[6]);
#define PIXEL02_50    Interp5(dp+2, w[2], w[5]);
#define PIXEL02_60    Interp6(dp+2, w[5], w[2], w[6]);
#define PIXEL02_61    Interp6(dp+2, w[5], w[2], w[3]);
#define PIXEL02_81    Interp8(dp+2, w[5], w[2]);
#define PIXEL02_83    Interp8(dp+2, w[2], w[6]);
#define PIXEL03_0     *(dp+3) = w[5];
#define PIXEL03_11    Interp1(dp+3, w[5], w[2]);
#define PIXEL03_12    Interp1(dp+3, w[5], w[6]);
#define PIXEL03_20    Interp2(dp+3, w[5], w[2], w[6]);
#define PIXEL03_50    Interp5(dp+3, w[2], w[6]);
#define PIXEL03_80    Interp8(dp+3, w[5], w[3]);
#define PIXEL03_81    Interp8(dp+3, w[5], w[2]);
#define PIXEL03_82    Interp8(dp+3, w[5], w[6]);
#define PIXEL10_0     *(dp+dpL) = w[5];
#define PIXEL10_10    Interp1(dp+dpL, w[5], w[1]);
#define PIXEL10_11    Interp1(dp+dpL, w[5], w[4]);
#define PIXEL10_13    Interp1(dp+dpL, w[4], w[5]);
#define PIXEL10_21    Interp2(dp+dpL, w[4], w[5], w[2]);
#define PIXEL10_32    Interp3(dp+dpL, w[5], w[2]);
#define PIXEL10_50    Interp5(dp+dpL, w[4], w[5]);
#define PIXEL10_60    Interp6(dp+dpL, w[5], w[4], w[2]);
#define PIXEL10_61    Interp6(dp+dpL, w[5], w[4], w[1]);
#define PIXEL10_81    Interp8(dp+dpL, w[5], w[4]);
#define PIXEL10_83    Interp8(dp+dpL, w[4], w[2]);
#define PIXEL11_0     *(dp+dpL+1) = w[5];
#define PIXEL11_30    Interp3(dp+dpL+1, w[5], w[1]);
#define PIXEL11_31    Interp3(dp+dpL+1, w[5], w[4]);
#define PIXEL11_32    Interp3(dp+dpL+1, w[5], w[2]);
#define PIXEL11_70    Interp7(dp+dpL+1, w[5], w[4], w[2]);
#define PIXEL12_0     *(dp+dpL+2) = w[5];
#define PIXEL12_30    Interp3(dp+dpL+2, w[5], w[3]);
#define PIXEL12_31    Interp3(dp+dpL+2, w[5], w[2]);
#define PIXEL12_32    Interp3(dp+dpL+2, w[5], w[6]);
#define PIXEL12_70    Interp7(dp+dpL+2, w[5], w[6], w[2]);
#define PIXEL13_0     *(dp+dpL+3) = w[5];
#define PIXEL13_10    Interp1(dp+dpL+3, w[5], w[3]);
#define PIXEL13_12    Interp1(dp+dpL+3, w[5], w[6]);
#define PIXEL13_14    Interp1(dp+dpL+3, w[6], w[5]);
#define PIXEL13_21    Interp2(dp+dpL+3, w[6], w[5], w[2]);
#define PIXEL13_31    Interp3(dp+dpL+3, w[5], w[2]);
#define PIXEL13_50    Interp5(dp+dpL+3, w[6], w[5]);
#define PIXEL13_60    Interp6(dp+dpL+3, w[5], w[6], w[2]);
#define PIXEL13_61    Interp6(dp+dpL+3, w[5], w[6], w[3]);
#define PIXEL13_82    Interp8(dp+dpL+3, w[5], w[6]);
#define PIXEL13_83    Interp8(dp+dpL+3, w[6], w[2]);
#define PIXEL20_0     *(dp+dpL+dpL) = w[5];
#define PIXEL20_10    Interp1(dp+dpL+dpL, w[5], w[7]);
#define PIXEL20_12    Interp1(dp+dpL+dpL, w[5], w[4]);
#define PIXEL20_14    Interp1(dp+dpL+dpL, w[4], w[5]);
#define PIXEL20_21    Interp2(dp+dpL+dpL, w[4], w[5], w[8]);
#define PIXEL20_31    Interp3(dp+dpL+dpL, w[5], w[8]);
#define PIXEL20_50    Interp5(dp+dpL+dpL, w[4], w[5]);
#define PIXEL20_60    Interp6(dp+dpL+dpL, w[5], w[4], w[8]);
#define PIXEL20_61    Interp6(dp+dpL+dpL, w[5], w[4], w[7]);
#define PIXEL20_82    Interp8(dp+dpL+dpL, w[5], w[4]);
#define PIXEL20_83    Interp8(dp+dpL+dpL, w[4], w[8]);
#define PIXEL21_0     *(dp+dpL+dpL+1) = w[5];
#define PIXEL21_30    Interp3(dp+dpL+dpL+1, w[5], w[7]);
#define PIXEL21_31    Interp3(dp+dpL+dpL+1, w[5], w[8]);
#define PIXEL21_32    Interp3(dp+dpL+dpL+1, w[5], w[4]);
#define PIXEL21_70    Interp7(dp+dpL+dpL+1, w[5], w[4], w[8]);
#define PIXEL22_0     *(dp+dpL+dpL+2) = w[5];
#define PIXEL22_30    Interp3(dp+dpL+dpL+2, w[5], w[9]);
#define PIXEL22_31    Interp3(dp+dpL+dpL+2, w[5], w[6]);
#define PIXEL22_32    Interp3(dp+dpL+dpL+2, w[5], w[8]);
#define PIXEL22_70    Interp7(dp+dpL+dpL+2, w[5], w[6], w[8]);
#define PIXEL23_0     *(dp+dpL+dpL+3) = w[5];
#define PIXEL23_10    Interp1(dp+dpL+dpL+3, w[5], w[9]);
#define PIXEL23_11    Interp1(dp+dpL+dpL+3, w[5], w[6]);
#define PIXEL23_13    Interp1(dp+dpL+dpL+3, w[6], w[5]);
#define PIXEL23_21    Interp2(dp+dpL+dpL+3, w[6], w[5], w[8]);
#define PIXEL23_32    Interp3(dp+dpL+dpL+3, w[5], w[8]);
#define PIXEL23_50    Interp5(dp+dpL+dpL+3, w[6], w[5]);
#define PIXEL23_60    Interp6(dp+dpL+dpL+3, w[5], w[6], w[8]);
#define PIXEL23_61    Interp6(dp+dpL+dpL+3, w[5], w[6], w[9]);
#define PIXEL23_81    Interp8(dp+dpL+dpL+3, w[5], w[6]);
#define PIXEL23_83    Interp8(dp+dpL+dpL+3, w[6], w[8]);
#define PIXEL30_0     *(dp+dpL+dpL+dpL) = w[5];
#define PIXEL30_11    Interp1(dp+dpL+dpL+dpL, w[5], w[8]);
#define PIXEL30_12    Interp1(dp+dpL+dpL+dpL, w[5], w[4]);
#define PIXEL30_20    Interp2(dp+dpL+dpL+dpL, w[5], w[8], w[4]);
#define PIXEL30_50    Interp5(dp+dpL+dpL+dpL, w[8], w[4]);
#define PIXEL30_80    Interp8(dp+dpL+dpL+dpL, w[5], w[7]);
#define PIXEL30_81    Interp8(dp+dpL+dpL+dpL, w[5], w[8]);
#define PIXEL30_82    Interp8(dp+dpL+dpL+dpL, w[5], w[4]);
#define PIXEL31_0     *(dp+dpL+dpL+dpL+1) = w[5];
#define PIXEL31_10    Interp1(dp+dpL+dpL+dpL+1, w[5], w[7]);
#define PIXEL31_11    Interp1(dp+dpL+dpL+dpL+1, w[5], w[8]);
#define PIXEL31_13    Interp1(dp+dpL+dpL+dpL+1, w[8], w[5]);
#define PIXEL31_21    Interp2(dp+dpL+dpL+dpL+1, w[8], w[5], w[4]);
#define PIXEL31_32    Interp3(dp+dpL+dpL+dpL+1, w[5], w[4]);
#define PIXEL31_50    Interp5(dp+dpL+dpL+dpL+1, w[8], w[5]);
#define PIXEL31_60    Interp6(dp+dpL+dpL+dpL+1, w[5], w[8], w[4]);
#define PIXEL31_61    Interp6(dp+dpL+dpL+dpL+1, w[5], w[8], w[7]);
#define PIXEL31_81    Interp8(dp+dpL+dpL+dpL+1, w[5], w[8]);
#define PIXEL31_83    Interp8(dp+dpL+dpL+dpL+1, w[8], w[4]);
#define PIXEL32_0     *(dp+dpL+dpL+dpL+2) = w[5];
#define PIXEL32_10    Interp1(dp+dpL+dpL+dpL+2, w[5], w[9]);
#define PIXEL32_12    Interp1(dp+dpL+dpL+dpL+2, w[5], w[8]);
#define PIXEL32_14    Interp1(dp+dpL+dpL+dpL+2, w[8], w[5]);
#define PIXEL32_21    Interp2(dp+dpL+dpL+dpL+2, w[8], w[5], w[6]);
#define PIXEL32_31    Interp3(dp+dpL+dpL+dpL+2, w[5], w[6]);
#define PIXEL32_50    Interp5(dp+dpL+dpL+dpL+2, w[8], w[5]);
#define PIXEL32_60    Interp6(dp+dpL+dpL+dpL+2, w[5], w[8], w[6]);
#define PIXEL32_61    Interp6(dp+dpL+dpL+dpL+2, w[5], w[8], w[9]);
#define PIXEL32_82    Interp8(dp+dpL+dpL+dpL+2, w[5], w[8]);
#define PIXEL32_83    Interp8(dp+dpL+dpL+dpL+2, w[8], w[6]);
#define PIXEL33_0     *(dp+dpL+dpL+dpL+3) = w[5];
#define PIXEL33_11    Interp1(dp+dpL+dpL+dpL+3, w[5], w[6]);
#define PIXEL33_12    Interp1(dp+dpL+dpL+dpL+3, w[5], w[8]);
#define PIXEL33_20    Interp2(dp+dpL+dpL+dpL+3, w[5], w[8], w[6]);
#define PIXEL33_50    Interp5(dp+dpL+dpL+dpL+3, w[8], w[6]);
#define PIXEL33_80    Interp8(dp+dpL+dpL+dpL+3, w[5], w[9]);
#define PIXEL33_81    Interp8(dp+dpL+dpL+dpL+3, w[5], w[6]);
#define PIXEL33_82    Interp8(dp+dpL+dpL+dpL+3, w[5], w[8]);

static void hq4x_rows(const uint32_t *src, int ss, int sw, int sh,
                      uint32_t *dst, int ds, int y0, int y1)
{
    HqWin t;
    const int dpL = ds;
    for (int x0 = 0; x0 < sw; x0 += HQ_TILE) {
        const int tw = sw - x0 < HQ_TILE ? sw - x0 : HQ_TILE;
        for (int y = y0; y < y1; ++y) {
            hq_win_row(&t, src, ss, sw, sh, y, y0, x0, tw);
            uint32_t *dp = dst + (size_t)y * 4 * ds + (size_t)x0 * 4;
            for (int i = 1; i <= tw; ++i, dp += 4) {
                uint32_t w[10], yv[10];
                const int pattern = hq_pattern(&t, i, w, yv);
                switch (pattern) {
                    case 0: case 1: case 4: case 32: case 128: case 5: case 132: case 160: case 33: case 129:
                    case 36: case 133: case 164: case 161: case 37: case 165: {
                        PIXEL00_20 PIXEL01_60 PIXEL02_60 PIXEL03_20 PIXEL10_60 PIXEL11_70 PIXEL12_70
                        PIXEL13_60 PIXEL20_60 PIXEL21_70 PIXEL22_70 PIXEL23_60 PIXEL30_20 PIXEL31_60
                        PIXEL32_60 PIXEL33_20 break;
                    }
                    case 2: case 34: case 130: case 162: {
                        PIXEL00_80 PIXEL01_10 PIXEL02_10 PIXEL03_80 PIXEL10_61 PIXEL11_30 PIXEL12_30
                        PIXEL13_61 PIXEL20_60 PIXEL21_70 PIXEL22_70 PIXEL23_60 PIXEL30_20 PIXEL31_60
                        PIXEL32_60 PIXEL33_20 break;
                    }
                    case 16: case 17: case 48: case 49: {
                        PIXEL00_20 PIXEL01_60 PIXEL02_61 PIXEL03_80 PIXEL10_60 PIXEL11_70 PIXEL12_30
                        PIXEL13_10 PIXEL20_60 PIXEL21_70 PIXEL22_30 PIXEL23_10 PIXEL30_20 PIXEL31_60
                        PIXEL32_61 PIXEL33_80 break;
                    }
                    case 64: case 65: case 68: case 69: {
                        PIXEL00_20 PIXEL01_60 PIXEL02_60 PIXEL03_20 PIXEL10_60 PIXEL11_70 PIXEL12_70
                        PIXEL13_60 PIXEL20_61 PIXEL21_30 PIXEL22_30 PIXEL23_61 PIXEL30_80 PIXEL31_10
                        PIXEL32_10 PIXEL33_80 break;
                    }
                    case 8: case 12: case 136: case 140: {
                        PIXEL00_80 PIXEL01_61 PIXEL02_60 PIXEL03_20 PIXEL10_10 PIXEL11_30 PIXEL12_70
                        PIXEL13_60 PIXEL20_10 PIXEL21_30 PIXEL22_70 PIXEL23_60 PIXEL30_80 PIXEL31_61
                        PIXEL32_60 PIXEL33_20 break;
                    }
                    case 3: case 35: case 131: case 163: {
                        PIXEL00_81 PIXEL01_31 PIXEL02_10 PIXEL03_80 PIXEL10_81 PIXEL11_31 PIXEL12_30
                        PIXEL13_61 PIXEL20_60 PIXEL21_70 PIXEL22_70 PIXEL23_60 PIXEL30_20 PIXEL31_60
                        PIXEL32_60 PIXEL33_20 break;
                    }
                    case 6: case 38: case 134: case 166: {
                        PIXEL00_80 PIXEL01_10 PIXEL02_32 PIXEL03_82 PIXEL10_61 PIXEL11_30 PIXEL12_32
                        PIXEL13_82 PIXEL20_60 PIXEL21_70 PIXEL22_70 PIXEL23_60 PIXEL30_20 PIXEL31_60
                        PIXEL32_60 PIXEL33_20 break;
                    }
                    case 20: case 21: case 52: case 53: {
                        PIXEL00_20 PIXEL01_60 PIXEL02_81 PIXEL03_81 PIXEL10_60 PIXEL11_70 PIXEL12_31
                        PIXEL13_31 PIXEL20_60 PIXEL21_70 PIXEL22_30 PIXEL23_10 PIXEL30_20 PIXEL31_60
                        PIXEL32_61 PIXEL33_80 break;
                    }
                    case 144: case 145: case 176: case 177: {
                        PIXEL00_20 PIXEL01_60 PIXEL02_61 PIXEL03_80 PIXEL10_60 PIXEL11_70 PIXEL12_30
                        PIXEL13_10 PIXEL20_60 PIXEL21_70 PIXEL22_32 PIXEL23_32 PIXEL30_20 PIXEL31_60
                        PIXEL32_82 PIXEL33_82 break;
                    }
                    case 192: case 193: case 196: case 197: {
                        PIXEL00_20 PIXEL01_60 PIXEL02_60 PIXEL03_20 PIXEL10_60 PIXEL11_70 PIXEL12_70
                        PIXEL13_60 PIXEL20_61 PIXEL21_30 PIXEL22_31 PIXEL23_81 PIXEL30_80 PIXEL31_10
                        PIXEL32_31 PIXEL33_81 break;
                    }
                    case 96: case 97: case 100: case 101: {
                        PIXEL00_20 PIXEL01_60 PIXEL02_60 PIXEL03_20 PIXEL10_60 PIXEL11_70 PIXEL12_70
                        PIXEL13_60 PIXEL20_82 PIXEL21_32 PIXEL22_30 PIXEL23_61 PIXEL30_82 PIXEL31_32
                        PIXEL32_10 PIXEL33_80 break;
                    }
                    case 40: case 44: case 168: case 172: {
                        PIXEL00_80 PIXEL01_61 PIXEL02_60 PIXEL03_20 PIXEL10_10 PIXEL11_30 PIXEL12_70
                        PIXEL13_60 PIXEL20_31 PIXEL21_31 PIXEL22_70 PIXEL23_60 PIXEL30_81 PIXEL31_81
                        PIXEL32_60 PIXEL33_20 break;
                    }
                    case 9: case 13: case 137: case 141: {
                        PIXEL00_82 PIXEL01_82 PIXEL02_60 PIXEL03_20 PIXEL10_32 PIXEL11_32 PIXEL12_70
                        PIXEL13_60 PIXEL20_10 PIXEL21_30 PIXEL22_70 PIXEL23_60 PIXEL30_80 PIXEL31_61
                        PIXEL32_60 PIXEL33_20 break;
                    }
                    case 18: case 50: {
                        PIXEL00_80 PIXEL01_10
                        if (DIFF(2, 6)) { PIXEL02_10 PIXEL03_80 PIXEL12_30 PIXEL13_10 } else { PIXEL02_50 PIXEL03_50 PIXEL12_0 PIXEL13_50 }
                        PIXEL10_61 PIXEL11_30 PIXEL20_60 PIXEL21_70 PIXEL22_30 PIXEL23_10 PIXEL30_20
                        PIXEL31_60 PIXEL32_61 PIXEL33_80 break;
                    }
                    case 80: case 81: {
                        PIXEL00_20 PIXEL01_60 PIXEL02_61 PIXEL03_80 PIXEL10_60 PIXEL11_70 PIXEL12_30
                        PIXEL13_10 PIXEL20_61 PIXEL21_30
                        if (DIFF(6, 8)) { PIXEL22_30 PIXEL23_10 PIXEL32_10 PIXEL33_80 } else { PIXEL22_0 PIXEL23_50 PIXEL32_50 PIXEL33_50 }
                        PIXEL30_80 PIXEL31_10 break;
                    }
                    case 72: case 76: {
                        PIXEL00_80 PIXEL01_61 PIXEL02_60 PIXEL03_20 PIXEL10_10 PIXEL11_30 PIXEL12_70
                        PIXEL13_60
                        if (DIFF(8, 4)) { PIXEL20_10 PIXEL21_30 PIXEL30_80 PIXEL31_10 } else { PIXEL20_50 PIXEL21_0 PIXEL30_50 PIXEL31_50 }
                        PIXEL22_30 PIXEL23_61 PIXEL32_10 PIXEL33_80 break;
                    }
                    case 10: case 138: {
                        if (DIFF(4, 2)) { PIXEL00_80 PIXEL01_10 PIXEL10_10 PIXEL11_30 } else { PIXEL00_50 PIXEL01_50 PIXEL10_50 PIXEL11_0 }
                        PIXEL02_10 PIXEL03_80 PIXEL12_30 PIXEL13_61 PIXEL20_10 PIXEL21_30 PIXEL22_70
                        PIXEL23_60 PIXEL30_80 PIXEL31_61 PIXEL32_60 PIXEL33_20 break;
                    }
                    case 66: {
                        PIXEL00_80 PIXEL01_10 PIXEL02_10 PIXEL03_80 PIXEL10_61 PIXEL11_30 PIXEL12_30
                        PIXEL13_61 PIXEL20_61 PIXEL21_30 PIXEL22_30 PIXEL23_61 PIXEL30_80 PIXEL31_10
                        PIXEL32_10 PIXEL33_80 break;
                    }
                    case 24: {
                        PIXEL00_80 PIXEL01_61 PIXEL02_61 PIXEL03_80 PIXEL10_10 PIXEL11_30 PIXEL12_30
                        PIXEL13_10 PIXEL20_10 PIXEL21_30 PIXEL22_30 PIXEL23_10 PIXEL30_80 PIXEL31_61
                        PIXEL32_61 PIXEL33_80 break;
                    }
                    case 7: case 39: case 135: {
                        PIXEL00_81 PIXEL01_31 PIXEL02_32 PIXEL03_82 PIXEL10_81 PIXEL11_31 PIXEL12_32
                        PIXEL13_82 PIXEL20_60 PIXEL21_70 PIXEL22_70 PIXEL23_60 PIXEL30_20 PIXEL31_60
                        PIXEL32_60 PIXEL33_20 break;
                    }
                    case 148: case 149: case 180: {
                        PIXEL00_20 PIXEL01_60 PIXEL02_81 PIXEL03_81 PIXEL10_60 PIXEL11_70 PIXEL12_31
                        PIXEL13_31 PIXEL20_60 PIXEL21_70 PIXEL22_32 PIXEL23_32 PIXEL30_20 PIXEL31_60
                        PIXEL32_82 PIXEL33_82 break;
                    }
                    case 224: case 228: case 225: {
                        PIXEL00_20 PIXEL01_60 PIXEL02_60 PIXEL03_20 PIXEL10_60 PIXEL11_70 PIXEL12_70
                        PIXEL13_60 PIXEL20_82 PIXEL21_32 PIXEL22_31 PIXEL23_81 PIXEL30_82 PIXEL31_32
                        PIXEL32_31 PIXEL33_81 break;
                    }
                    case 41: case 169: case 45: {
                        PIXEL00_82 PIXEL01_82 PIXEL02_60 PIXEL03_20 PIXEL10_32 PIXEL11_32 PIXEL12_70
                        PIXEL13_60 PIXEL20_31 PIXEL21_31 PIXEL22_70 PIXEL23_60 PIXEL30_81 PIXEL31_81
                        PIXEL32_60 PIXEL33_20 break;
                    }
                    case 22: case 54: {
                        PIXEL00_80 PIXEL01_10
                        if (DIFF(2, 6)) { PIXEL02_0 PIXEL03_0 PIXEL13_0 } else { PIXEL02_50 PIXEL03_50 PIXEL13_50 }
                        PIXEL10_61 PIXEL11_30 PIXEL12_0 PIXEL20_60 PIXEL21_70 PIXEL22_30 PIXEL23_10 PIXEL30_20
                        PIXEL31_60 PIXEL32_61 PIXEL33_80 break;
                    }
                    case 208: case 209: {
                        PIXEL00_20 PIXEL01_60 PIXEL02_61 PIXEL03_80 PIXEL10_60 PIXEL11_70 PIXEL12_30
                        PIXEL13_10 PIXEL20_61 PIXEL21_30 PIXEL22_0
                        if (DIFF(6, 8)) { PIXEL23_0 PIXEL32_0 PIXEL33_0 } else { PIXEL23_50 PIXEL32_50 PIXEL33_50 }
                        PIXEL30_80 PIXEL31_10 break;
                    }
                    case 104: case 108: {
                        PIXEL00_80 PIXEL01_61 PIXEL02_60 PIXEL03_20 PIXEL10_10 PIXEL11_30 PIXEL12_70
                        PIXEL13_60
                        if (DIFF(8, 4)) { PIXEL20_0 PIXEL30_0 PIXEL31_0 } else { PIXEL20_50 PIXEL30_50 PIXEL31_50 }
                        PIXEL21_0 PIXEL22_30 PIXEL23_61 PIXEL32_10 PIXEL33_80 break;
                    }
                    case 11: case 139: {
                        if (DIFF(4, 2)) { PIXEL00_0 PIXEL01_0 PIXEL10_0 } else { PIXEL00_50 PIXEL01_50 PIXEL10_50 }
                        PIXEL02_10 PIXEL03_80 PIXEL11_0 PIXEL12_30 PIXEL13_61 PIXEL20_10 PIXEL21_30 PIXEL22_70
                        PIXEL23_60 PIXEL30_80 PIXEL31_61 PIXEL32_60 PIXEL33_20 break;
                    }
                    case 19: case 51: {
                        if (DIFF(2, 6)) { PIXEL00_81 PIXEL01_31 PIXEL02_10 PIXEL03_80 PIXEL12_30 PIXEL13_10 } else { PIXEL00_12 PIXEL01_14 PIXEL02_83 PIXEL03_50 PIXEL12_70 PIXEL13_21 }
                        PIXEL10_81 PIXEL11_31 PIXEL20_60 PIXEL21_70 PIXEL22_30 PIXEL23_10 PIXEL30_20
                        PIXEL31_60 PIXEL32_61 PIXEL33_80 break;
                    }
                    case 146: case 178: {
                        PIXEL00_80 PIXEL01_10
                        if (DIFF(2, 6)) { PIXEL02_10 PIXEL03_80 PIXEL12_30 PIXEL13_10 PIXEL23_32 PIXEL33_82 } else { PIXEL02_21 PIXEL03_50 PIXEL12_70 PIXEL13_83 PIXEL23_13 PIXEL33_11 }
                        PIXEL10_61 PIXEL11_30 PIXEL20_60 PIXEL21_70 PIXEL22_32 PIXEL30_20 PIXEL31_60
                        PIXEL32_82 break;
                    }
                    case 84: case 85: {
                        PIXEL00_20 PIXEL01_60 PIXEL02_81
                        if (DIFF(6, 8)) { PIXEL03_81 PIXEL13_31 PIXEL22_30 PIXEL23_10 PIXEL32_10 PIXEL33_80 } else { PIXEL03_12 PIXEL13_14 PIXEL22_70 PIXEL23_83 PIXEL32_21 PIXEL33_50 }
                        PIXEL10_60 PIXEL11_70 PIXEL12_31 PIXEL20_61 PIXEL21_30 PIXEL30_80 PIXEL31_10 break;
                    }
                    case 112: case 113: {
                        PIXEL00_20 PIXEL01_60 PIXEL02_61 PIXEL03_80 PIXEL10_60 PIXEL11_70 PIXEL12_30
                        PIXEL13_10 PIXEL20_82 PIXEL21_32
                        if (DIFF(6, 8)) { PIXEL22_30 PIXEL23_10 PIXEL30_82 PIXEL31_32 PIXEL32_10 PIXEL33_80 } else { PIXEL22_70 PIXEL23_21 PIXEL30_11 PIXEL31_13 PIXEL32_83 PIXEL33_50 }
                        break;
                    }
                    case 200: case 204: {
                        PIXEL00_80 PIXEL01_61 PIXEL02_60 PIXEL03_20 PIXEL10_10 PIXEL11_30 PIXEL12_70
                        PIXEL13_60
                        if (DIFF(8, 4)) { PIXEL20_10 PIXEL21_30 PIXEL30_80 PIXEL31_10 PIXEL32_31 PIXEL33_81 } else { PIXEL20_21 PIXEL21_70 PIXEL30_50 PIXEL31_83 PIXEL32_14 PIXEL33_12 }
                        PIXEL22_31 PIXEL23_81 break;
                    }
                    case 73: case 77: {
                        if (DIFF(8, 4)) { PIXEL00_82 PIXEL10_32 PIXEL20_10 PIXEL21_30 PIXEL30_80 PIXEL31_10 } else { PIXEL00_11 PIXEL10_13 PIXEL20_83 PIXEL21_70 PIXEL30_50 PIXEL31_21 }
                        PIXEL01_82 PIXEL02_60 PIXEL03_20 PIXEL11_32 PIXEL12_70 PIXEL13_60 PIXEL22_30
                        PIXEL23_61 PIXEL32_10 PIXEL33_80 break;
                    }
                    case 42: case 170: {
                        if (DIFF(4, 2)) { PIXEL00_80 PIXEL01_10 PIXEL10_10 PIXEL11_30 PIXEL20_31 PIXEL30_81 } else { PIXEL00_50 PIXEL01_21 PIXEL10_83 PIXEL11_70 PIXEL20_14 PIXEL30_12 }
                        PIXEL02_10 PIXEL03_80 PIXEL12_30 PIXEL13_61 PIXEL21_31 PIXEL22_70 PIXEL23_60
                        PIXEL31_81 PIXEL32_60 PIXEL33_20 break;
                    }
                    case 14: case 142: {
                        if (DIFF(4, 2)) { PIXEL00_80 PIXEL01_10 PIXEL02_32 PIXEL03_82 PIXEL10_10 PIXEL11_30 } else { PIXEL00_50 PIXEL01_83 PIXEL02_13 PIXEL03_11 PIXEL10_21 PIXEL11_70 }
                        PIXEL12_32 PIXEL13_82 PIXEL20_10 PIXEL21_30 PIXEL22_70 PIXEL23_60 PIXEL30_80
                        PIXEL31_61 PIXEL32_60 PIXEL33_20 break;
                    }
                    case 67: {
                        PIXEL00_81 PIXEL01_31 PIXEL02_10 PIXEL03_80 PIXEL10_81 PIXEL11_31 PIXEL12_30
                        PIXEL13_61 PIXEL20_61 PIXEL21_30 PIXEL22_30 PIXEL23_61 PIXEL30_80 PIXEL31_10
                        PIXEL32_10 PIXEL33_80 break;
                    }
                    case 70: {
                        PIXEL00_80 PIXEL01_10 PIXEL02_32 PIXEL03_82 PIXEL10_61 PIXEL11_30 PIXEL12_32
                        PIXEL13_82 PIXEL20_61 PIXEL21_30 PIXEL22_30 PIXEL23_61 PIXEL30_80 PIXEL31_10
                        PIXEL32_10 PIXEL33_80 break;
                    }
                    case 28: {
                        PIXEL00_80 PIXEL01_61 PIXEL02_81 PIXEL03_81 PIXEL10_10 PIXEL11_30 PIXEL12_31
                        PIXEL13_31 PIXEL20_10 PIXEL21_30 PIXEL22_30 PIXEL23_10 PIXEL30_80 PIXEL31_61
                        PIXEL32_61 PIXEL33_80 break;
                    }
                    case 152: {
                        PIXEL00_80 PIXEL01_61 PIXEL02_61 PIXEL03_80 PIXEL10_10 PIXEL11_30 PIXEL12_30
                        PIXEL13_10 PIXEL20_10 PIXEL21_30 PIXEL22_32 PIXEL23_32 PIXEL30_80 PIXEL31_61
                        PIXEL32_82 PIXEL33_82 break;
                    }
                    case 194: {
                        PIXEL00_80 PIXEL01_10 PIXEL02_10 PIXEL03_80 PIXEL10_61 PIXEL11_30 PIXEL12_30
                        PIXEL13_61 PIXEL20_61 PIXEL21_30 PIXEL22_31 PIXEL23_81 PIXEL30_80 PIXEL31_10
                        PIXEL32_31 PIXEL33_81 break;
                    }
                    case 98: {
                        PIXEL00_80 PIXEL01_10 PIXEL02_10 PIXEL03_80 PIXEL10_61 PIXEL11_30 PIXEL12_30
                        PIXEL13_61 PIXEL20_82 PIXEL21_32 PIXEL22_30 PIXEL23_61 PIXEL30_82 PIXEL31_32
                        PIXEL32_10 PIXEL33_80 break;
                    }
                    case 56: {
                        PIXEL00_80 PIXEL01_61 PIXEL02_61 PIXEL03_80 PIXEL10_10 PIXEL11_30 PIXEL12_30
                        PIXEL13_10 PIXEL20_31 PIXEL21_31 PIXEL22_30 PIXEL23_10 PIXEL30_81 PIXEL31_81
                        PIXEL32_61 PIXEL33_80 break;
                    }
                    case 25: {
                        PIXEL00_82 PIXEL01_82 PIXEL02_61 PIXEL03_80 PIXEL10_32 PIXEL11_32 PIXEL12_30
                        PIXEL13_10 PIXEL20_10 PIXEL21_30 PIXEL22_30 PIXEL23_10 PIXEL30_80 PIXEL31_61
                        PIXEL32_61 PIXEL33_80 break;
                    }
                    case 26: case 31: {
                        if (DIFF(4, 2)) { PIXEL00_0 PIXEL01_0 PIXEL10_0 } else { PIXEL00_50 PIXEL01_50 PIXEL10_50 }
                        if (DIFF(2, 6)) { PIXEL02_0 PIXEL03_0 PIXEL13_0 } else { PIXEL02_50 PIXEL03_50 PIXEL13_50 }
                        PIXEL11_0 PIXEL12_0 PIXEL20_10 PIXEL21_30 PIXEL22_30 PIXEL23_10 PIXEL30_80 PIXEL31_61
                        PIXEL32_61 PIXEL33_80 break;
                    }
                    case 82: case 214: {
                        PIXEL00_80 PIXEL01_10
                        if (DIFF(2, 6)) { PIXEL02_0 PIXEL03_0 PIXEL13_0 } else { PIXEL02_50 PIXEL03_50 PIXEL13_50 }
                        PIXEL10_61 PIXEL11_30 PIXEL12_0 PIXEL20_61 PIXEL21_30 PIXEL22_0
                        if (DIFF(6, 8)) { PIXEL23_0 PIXEL32_0 PIXEL33_0 } else { PIXEL23_50 PIXEL32_50 PIXEL33_50 }
                        PIXEL30_80 PIXEL31_10 break;
                    }
                    case 88: case 248: {
                        PIXEL00_80 PIXEL01_61 PIXEL02_61 PIXEL03_80 PIXEL10_10 PIXEL11_30 PIXEL12_30
                        PIXEL13_10
                        if (DIFF(8, 4)) { PIXEL20_0 PIXEL30_0 PIXEL31_0 } else { PIXEL20_50 PIXEL30_50 PIXEL31_50 }
                        PIXEL21_0 PIXEL22_0
                        if (DIFF(6, 8)) { PIXEL23_0 PIXEL32_0 PIXEL33_0 } else { PIXEL23_50 PIXEL32_50 PIXEL33_50 }
                        break;
                    }
                    case 74: case 107: {
                        if (DIFF(4, 2)) { PIXEL00_0 PIXEL01_0 PIXEL10_0 } else { PIXEL00_50 PIXEL01_50 PIXEL10_50 }
                        PIXEL02_10 PIXEL03_80 PIXEL11_0 PIXEL12_30 PIXEL13_61
                        if (DIFF(8, 4)) { PIXEL20_0 PIXEL30_0 PIXEL31_0 } else { PIXEL20_50 PIXEL30_50 PIXEL31_50 }
                        PIXEL21_0 PIXEL22_30 PIXEL23_61 PIXEL32_10 PIXEL33_80 break;
                    }
                    case 27: {
                        if (DIFF(4, 2)) { PIXEL00_0 PIXEL01_0 PIXEL10_0 } else { PIXEL00_50 PIXEL01_50 PIXEL10_50 }
                        PIXEL02_10 PIXEL03_80 PIXEL11_0 PIXEL12_30 PIXEL13_10 PIXEL20_10 PIXEL21_30 PIXEL22_30
                        PIXEL23_10 PIXEL30_80 PIXEL31_61 PIXEL32_61 PIXEL33_80 break;
                    }
                    case 86: {
                        PIXEL00_80 PIXEL01_10
                        if (DIFF(2, 6)) { PIXEL02_0 PIXEL03_0 PIXEL13_0 } else { PIXEL02_50 PIXEL03_50 PIXEL13_50 }
                        PIXEL10_61 PIXEL11_30 PIXEL12_0 PIXEL20_61 PIXEL21_30 PIXEL22_30 PIXEL23_10 PIXEL30_80
                        PIXEL31_10 PIXEL32_10 PIXEL33_80 break;
                    }
                    case 216: {
                        PIXEL00_80 PIXEL01_61 PIXEL02_61 PIXEL03_80 PIXEL10_10 PIXEL11_30 PIXEL12_30
                        PIXEL13_10 PIXEL20_10 PIXEL21_30 PIXEL22_0
                        if (DIFF(6, 8)) { PIXEL23_0 PIXEL32_0 PIXEL33_0 } else { PIXEL23_50 PIXEL32_50 PIXEL33_50 }
                        PIXEL30_80 PIXEL31_10 break;
                    }
                    case 106: {
                        PIXEL00_80 PIXEL01_10 PIXEL02_10 PIXEL03_80 PIXEL10_10 PIXEL11_30 PIXEL12_30
                        PIXEL13_61
                        if (DIFF(8, 4)) { PIXEL20_0 PIXEL30_0 PIXEL31_0 } else { PIXEL20_50 PIXEL30_50 PIXEL31_50 }
                        PIXEL21_0 PIXEL22_30 PIXEL23_61 PIXEL32_10 PIXEL33_80 break;
                    }
                    case 30: {
                        PIXEL00_80 PIXEL01_10
                        if (DIFF(2, 6)) { PIXEL02_0 PIXEL03_0 PIXEL13_0 } else { PIXEL02_50 PIXEL03_50 PIXEL13_50 }
                        PIXEL10_10 PIXEL11_30 PIXEL12_0 PIXEL20_10 PIXEL21_30 PIXEL22_30 PIXEL23_10 PIXEL30_80
                        PIXEL31_61 PIXEL32_61 PIXEL33_80 break;
                    }
                    case 210: {
                        PIXEL00_80 PIXEL01_10 PIXEL02_10 PIXEL03_80 PIXEL10_61 PIXEL11_30 PIXEL12_30
                        PIXEL13_10 PIXEL20_61 PIXEL21_30 PIXEL22_0
                        if (DIFF(6, 8)) { PIXEL23_0 PIXEL32_0 PIXEL33_0 } else { PIXEL23_50 PIXEL32_50 PIXEL33_50 }
                        PIXEL30_80 PIXEL31_10 break;
                    }
                    case 120: {
                        PIXEL00_80 PIXEL01_61 PIXEL02_61 PIXEL03_80 PIXEL10_10 PIXEL11_30 PIXEL12_30
                        PIXEL13_10
                        if (DIFF(8, 4)) { PIXEL20_0 PIXEL30_0 PIXEL31_0 } else { PIXEL20_50 PIXEL30_50 PIXEL31_50 }
                        PIXEL21_0 PIXEL22_30 PIXEL23_10 PIXEL32_10 PIXEL33_80 break;
                    }
                    case 75: {
                        if (DIFF(4, 2)) { PIXEL00_0 PIXEL01_0 PIXEL10_0 } else { PIXEL00_50 PIXEL01_50 PIXEL10_50 }
                        PIXEL02_10 PIXEL03_80 PIXEL11_0 PIXEL12_30 PIXEL13_61 PIXEL20_10 PIXEL21_30 PIXEL22_30
                        PIXEL23_61 PIXEL30_80 PIXEL31_10 PIXEL32_10 PIXEL33_80 break;
                    }
                    case 29: {
                        PIXEL00_82 PIXEL01_82 PIXEL02_81 PIXEL03_81 PIXEL10_32 PIXEL11_32 PIXEL12_31
                        PIXEL13_31 PIXEL20_10 PIXEL21_30 PIXEL22_30 PIXEL23_10 PIXEL30_80 PIXEL31_61
                        PIXEL32_61 PIXEL33_80 break;
                    }
                    case 198: {
                        PIXEL00_80 PIXEL01_10 PIXEL02_32 PIXEL03_82 PIXEL10_61 PIXEL11_30 PIXEL12_32
                        PIXEL13_82 PIXEL20_61 PIXEL21_30 PIXEL22_31 PIXEL23_81 PIXEL30_80 PIXEL31_10
                        PIXEL32_31 PIXEL33_81 break;
                    }
                    case 184: {
                        PIXEL00_80 PIXEL01_61 PIXEL02_61 PIXEL03_80 PIXEL10_10 PIXEL11_30 PIXEL12_30
                        PIXEL13_10 PIXEL20_31 PIXEL21_31 PIXEL22_32 PIXEL23_32 PIXEL30_81 PIXEL31_81
                        PIXEL32_82 PIXEL33_82 break;
                    }
                    case 99: {
                        PIXEL00_81 PIXEL01_31 PIXEL02_10 PIXEL03_80 PIXEL10_81 PIXEL11_31 PIXEL12_30
                        PIXEL13_61 PIXEL20_82 PIXEL21_32 PIXEL22_30 PIXEL23_61 PIXEL30_82 PIXEL31_32
                        PIXEL32_10 PIXEL33_80 break;
                    }
                    case 57: {
                        PIXEL00_82 PIXEL01_82 PIXEL02_61 PIXEL03_80 PIXEL10_32 PIXEL11_32 PIXEL12_30
                        PIXEL13_10 PIXEL20_31 PIXEL21_31 PIXEL22_30 PIXEL23_10 PIXEL30_81 PIXEL31_81
                        PIXEL32_61 PIXEL33_80 break;
                    }
                    case 71: {
                        PIXEL00_81 PIXEL01_31 PIXEL02_32 PIXEL03_82 PIXEL10_81 PIXEL11_31 PIXEL12_32
                        PIXEL13_82 PIXEL20_61 PIXEL21_30 PIXEL22_30 PIXEL23_61 PIXEL30_80 PIXEL31_10
                        PIXEL32_10 PIXEL33_80 break;
                    }
                    case 156: {
                        PIXEL00_80 PIXEL01_61 PIXEL02_81 PIXEL03_81 PIXEL10_10 PIXEL11_30 PIXEL12_31
                        PIXEL13_31 PIXEL20_10 PIXEL21_30 PIXEL22_32 PIXEL23_32 PIXEL30_80 PIXEL31_61
                        PIXEL32_82 PIXEL33_82 break;
                    }
                    case 226: {
                        PIXEL00_80 PIXEL01_10 PIXEL02_10 PIXEL03_80 PIXEL10_61 PIXEL11_30 PIXEL12_30
                        PIXEL13_61 PIXEL20_82 PIXEL21_32 PIXEL22_31 PIXEL23_81 PIXEL30_82 PIXEL31_32
                        PIXEL32_31 PIXEL33_81 break;
                    }
                    case 60: {
                        PIXEL00_80 PIXEL01_61 PIXEL02_81 PIXEL03_81 PIXEL10_10 PIXEL11_30 PIXEL12_31
                        PIXEL13_31 PIXEL20_31 PIXEL21_31 PIXEL22_30 PIXEL23_10 PIXEL30_81 PIXEL31_81
                        PIXEL32_61 PIXEL33_80 break;
                    }
                    case 195: {
                        PIXEL00_81 PIXEL01_31 PIXEL02_10 PIXEL03_80 PIXEL10_81 PIXEL11_31 PIXEL12_30
                        PIXEL13_61 PIXEL20_61 PIXEL21_30 PIXEL22_31 PIXEL23_81 PIXEL30_80 PIXEL31_10
                        PIXEL32_31 PIXEL33_81 break;
                    }
                    case 102: {
                        PIXEL00_80 PIXEL01_10 PIXEL02_32 PIXEL03_82 PIXEL10_61 PIXEL11_30 PIXEL12_32
                        PIXEL13_82 PIXEL20_82 PIXEL21_32 PIXEL22_30 PIXEL23_61 PIXEL30_82 PIXEL31_32
                        PIXEL32_10 PIXEL33_80 break;
                    }
                    case 153: {
                        PIXEL00_82 PIXEL01_82 PIXEL02_61 PIXEL03_80 PIXEL10_32 PIXEL11_32 PIXEL12_30
                        PIXEL13_10 PIXEL20_10 PIXEL21_30 PIXEL22_32 PIXEL23_32 PIXEL30_80 PIXEL31_61
                        PIXEL32_82 PIXEL33_82 break;
                    }
                    case 58: {
                        if (DIFF(4, 2)) { PIXEL00_80 PIXEL01_10 PIXEL10_10 PIXEL11_30 } else { PIXEL00_20 PIXEL01_12 PIXEL10_11 PIXEL11_0 }
                        if (DIFF(2, 6)) { PIXEL02_10 PIXEL03_80 PIXEL12_30 PIXEL13_10 } else { PIXEL02_11 PIXEL03_20 PIXEL12_0 PIXEL13_12 }
                        PIXEL20_31 PIXEL21_31 PIXEL22_30 PIXEL23_10 PIXEL30_81 PIXEL31_81 PIXEL32_61
                        PIXEL33_80 break;
                    }
                    case 83: {
                        PIXEL00_81 PIXEL01_31
                        if (DIFF(2, 6)) { PIXEL02_10 PIXEL03_80 PIXEL12_30 PIXEL13_10 } else { PIXEL02_11 PIXEL03_20 PIXEL12_0 PIXEL13_12 }
                        PIXEL10_81 PIXEL11_31 PIXEL20_61 PIXEL21_30
                        if (DIFF(6, 8)) { PIXEL22_30 PIXEL23_10 PIXEL32_10 PIXEL33_80 } else { PIXEL22_0 PIXEL23_11 PIXEL32_12 PIXEL33_20 }
                        PIXEL30_80 PIXEL31_10 break;
                    }
                    case 92: {
                        PIXEL00_80 PIXEL01_61 PIXEL02_81 PIXEL03_81 PIXEL10_10 PIXEL11_30 PIXEL12_31
                        PIXEL13_31
                        if (DIFF(8, 4)) { PIXEL20_10 PIXEL21_30 PIXEL30_80 PIXEL31_10 } else { PIXEL20_12 PIXEL21_0 PIXEL30_20 PIXEL31_11 }
                        if (DIFF(6, 8)) { PIXEL22_30 PIXEL23_10 PIXEL32_10 PIXEL33_80 } else { PIXEL22_0 PIXEL23_11 PIXEL32_12 PIXEL33_20 }
                        break;
                    }
                    case 202: {
                        if (DIFF(4, 2)) { PIXEL00_80 PIXEL01_10 PIXEL10_10 PIXEL11_30 } else { PIXEL00_20 PIXEL01_12 PIXEL10_11 PIXEL11_0 }
                        PIXEL02_10 PIXEL03_80 PIXEL12_30 PIXEL13_61
                        if (DIFF(8, 4)) { PIXEL20_10 PIXEL21_30 PIXEL30_80 PIXEL31_10 } else { PIXEL20_12 PIXEL21_0 PIXEL30_20 PIXEL31_11 }
                        PIXEL22_31 PIXEL23_81 PIXEL32_31 PIXEL33_81 break;
                    }
                    case 78: {
                        if (DIFF(4, 2)) { PIXEL00_80 PIXEL01_10 PIXEL10_10 PIXEL11_30 } else { PIXEL00_20 PIXEL01_12 PIXEL10_11 PIXEL11_0 }
                        PIXEL02_32 PIXEL03_82 PIXEL12_32 PIXEL13_82
                        if (DIFF(8, 4)) { PIXEL20_10 PIXEL21_30 PIXEL30_80 PIXEL31_10 } else { PIXEL20_12 PIXEL21_0 PIXEL30_20 PIXEL31_11 }
                        PIXEL22_30 PIXEL23_61 PIXEL32_10 PIXEL33_80 break;
                    }
                    case 154: {
                        if (DIFF(4, 2)) { PIXEL00_80 PIXEL01_10 PIXEL10_10 PIXEL11_30 } else { PIXEL00_20 PIXEL01_12 PIXEL10_11 PIXEL11_0 }
                        if (DIFF(2, 6)) { PIXEL02_10 PIXEL03_80 PIXEL12_30 PIXEL13_10 } else { PIXEL02_11 PIXEL03_20 PIXEL12_0 PIXEL13_12 }
                        PIXEL20_10 PIXEL21_30 PIXEL22_32 PIXEL23_32 PIXEL30_80 PIXEL31_61 PIXEL32_82
                        PIXEL33_82 break;
                    }
                    case 114: {
                        PIXEL00_80 PIXEL01_10
                        if (DIFF(2, 6)) { PIXEL02_10 PIXEL03_80 PIXEL12_30 PIXEL13_10 } else { PIXEL02_11 PIXEL03_20 PIXEL12_0 PIXEL13_12 }
                        PIXEL10_61 PIXEL11_30 PIXEL20_82 PIXEL21_32
                        if (DIFF(6, 8)) { PIXEL22_30 PIXEL23_10 PIXEL32_10 PIXEL33_80 } else { PIXEL22_0 PIXEL23_11 PIXEL32_12 PIXEL33_20 }
                        PIXEL30_82 PIXEL31_32 break;
                    }
                    case 89: {
                        PIXEL00_82 PIXEL01_82 PIXEL02_61 PIXEL03_80 PIXEL10_32 PIXEL11_32 PIXEL12_30
                        PIXEL13_10
                        if (DIFF(8, 4)) { PIXEL20_10 PIXEL21_30 PIXEL30_80 PIXEL31_10 } else { PIXEL20_12 PIXEL21_0 PIXEL30_20 PIXEL31_11 }
                        if (DIFF(6, 8)) { PIXEL22_30 PIXEL23_10 PIXEL32_10 PIXEL33_80 } else { PIXEL22_0 PIXEL23_11 PIXEL32_12 PIXEL33_20 }
                        break;
                    }
                    case 90: {
                        if (DIFF(4, 2)) { PIXEL00_80 PIXEL01_10 PIXEL10_10 PIXEL11_30 } else { PIXEL00_20 PIXEL01_12 PIXEL10_11 PIXEL11_0 }
                        if (DIFF(2, 6)) { PIXEL02_10 PIXEL03_80 PIXEL12_30 PIXEL13_10 } else { PIXEL02_11 PIXEL03_20 PIXEL12_0 PIXEL13_12 }
                        if (DIFF(8, 4)) { PIXEL20_10 PIXEL21_30 PIXEL30_80 PIXEL31_10 } else { PIXEL20_12 PIXEL21_0 PIXEL30_20 PIXEL31_11 }
                        if (DIFF(6, 8)) { PIXEL22_30 PIXEL23_10 PIXEL32_10 PIXEL33_80 } else { PIXEL22_0 PIXEL23_11 PIXEL32_12 PIXEL33_20 }
                        break;
                    }
                    case 55: case 23: {
                        if (DIFF(2, 6)) { PIXEL00_81 PIXEL01_31 PIXEL02_0 PIXEL03_0 PIXEL12_0 PIXEL13_0 } else { PIXEL00_12 PIXEL01_14 PIXEL02_83 PIXEL03_50 PIXEL12_70 PIXEL13_21 }
                        PIXEL10_81 PIXEL11_31 PIXEL20_60 PIXEL21_70 PIXEL22_30 PIXEL23_10 PIXEL30_20
                        PIXEL31_60 PIXEL32_61 PIXEL33_80 break;
                    }
                    case 182: case 150: {
                        PIXEL00_80 PIXEL01_10
                        if (DIFF(2, 6)) { PIXEL02_0 PIXEL03_0 PIXEL12_0 PIXEL13_0 PIXEL23_32 PIXEL33_82 } else { PIXEL02_21 PIXEL03_50 PIXEL12_70 PIXEL13_83 PIXEL23_13 PIXEL33_11 }
                        PIXEL10_61 PIXEL11_30 PIXEL20_60 PIXEL21_70 PIXEL22_32 PIXEL30_20 PIXEL31_60
                        PIXEL32_82 break;
                    }
                    case 213: case 212: {
                        PIXEL00_20 PIXEL01_60 PIXEL02_81
                        if (DIFF(6, 8)) { PIXEL03_81 PIXEL13_31 PIXEL22_0 PIXEL23_0 PIXEL32_0 PIXEL33_0 } else { PIXEL03_12 PIXEL13_14 PIXEL22_70 PIXEL23_83 PIXEL32_21 PIXEL33_50 }
                        PIXEL10_60 PIXEL11_70 PIXEL12_31 PIXEL20_61 PIXEL21_30 PIXEL30_80 PIXEL31_10 break;
                    }
                    case 241: case 240: {
                        PIXEL00_20 PIXEL01_60 PIXEL02_61 PIXEL03_80 PIXEL10_60 PIXEL11_70 PIXEL12_30
                        PIXEL13_10 PIXEL20_82 PIXEL21_32
                        if (DIFF(6, 8)) { PIXEL22_0 PIXEL23_0 PIXEL30_82 PIXEL31_32 PIXEL32_0 PIXEL33_0 } else { PIXEL22_70 PIXEL23_21 PIXEL30_11 PIXEL31_13 PIXEL32_83 PIXEL33_50 }
                        break;
                    }
                    case 236: case 232: {
                        PIXEL00_80 PIXEL01_61 PIXEL02_60 PIXEL03_20 PIXEL10_10 PIXEL11_30 PIXEL12_70
                        PIXEL13_60
                        if (DIFF(8, 4)) { PIXEL20_0 PIXEL21_0 PIXEL30_0 PIXEL31_0 PIXEL32_31 PIXEL33_81 } else { PIXEL20_21 PIXEL21_70 PIXEL30_50 PIXEL31_83 PIXEL32_14 PIXEL33_12 }
                        PIXEL22_31 PIXEL23_81 break;
                    }
                    case 109: case 105: {
                        if (DIFF(8, 4)) { PIXEL00_82 PIXEL10_32 PIXEL20_0 PIXEL21_0 PIXEL30_0 PIXEL31_0 } else { PIXEL00_11 PIXEL10_13 PIXEL20_83 PIXEL21_70 PIXEL30_50 PIXEL31_21 }
                        PIXEL01_82 PIXEL02_60 PIXEL03_20 PIXEL11_32 PIXEL12_70 PIXEL13_60 PIXEL22_30
                        PIXEL23_61 PIXEL32_10 PIXEL33_80 break;
                    }
                    case 171: case 43: {
                        if (DIFF(4, 2)) { PIXEL00_0 PIXEL01_0 PIXEL10_0 PIXEL11_0 PIXEL20_31 PIXEL30_81 } else { PIXEL00_50 PIXEL01_21 PIXEL10_83 PIXEL11_70 PIXEL20_14 PIXEL30_12 }
                        PIXEL02_10 PIXEL03_80 PIXEL12_30 PIXEL13_61 PIXEL21_31 PIXEL22_70 PIXEL23_60
                        PIXEL31_81 PIXEL32_60 PIXEL33_20 break;
                    }
                    case 143: case 15: {
                        if (DIFF(4, 2)) { PIXEL00_0 PIXEL01_0 PIXEL02_32 PIXEL03_82 PIXEL10_0 PIXEL11_0 } else { PIXEL00_50 PIXEL01_83 PIXEL02_13 PIXEL03_11 PIXEL10_21 PIXEL11_70 }
                        PIXEL12_32 PIXEL13_82 PIXEL20_10 PIXEL21_30 PIXEL22_70 PIXEL23_60 PIXEL30_80
                        PIXEL31_61 PIXEL32_60 PIXEL33_20 break;
                    }
                    case 124: {
                        PIXEL00_80 PIXEL01_61 PIXEL02_81 PIXEL03_81 PIXEL10_10 PIXEL11_30 PIXEL12_31
                        PIXEL13_31
                        if (DIFF(8, 4)) { PIXEL20_0 PIXEL30_0 PIXEL31_0 } else { PIXEL20_50 PIXEL30_50 PIXEL31_50 }
                        PIXEL21_0 PIXEL22_30 PIXEL23_10 PIXEL32_10 PIXEL33_80 break;
                    }
                    case 203: {
                        if (DIFF(4, 2)) { PIXEL00_0 PIXEL01_0 PIXEL10_0 } else { PIXEL00_50 PIXEL01_50 PIXEL10_50 }
                        PIXEL02_10 PIXEL03_80 PIXEL11_0 PIXEL12_30 PIXEL13_61 PIXEL20_10 PIXEL21_30 PIXEL22_31
                        PIXEL23_81 PIXEL30_80 PIXEL31_10 PIXEL32_31 PIXEL33_81 break;
                    }
                    case 62: {
                        PIXEL00_80 PIXEL01_10
                        if (DIFF(2, 6)) { PIXEL02_0 PIXEL03_0 PIXEL13_0 } else { PIXEL02_50 PIXEL03_50 PIXEL13_50 }
                        PIXEL10_10 PIXEL11_30 PIXEL12_0 PIXEL20_31 PIXEL21_31 PIXEL22_30 PIXEL23_10 PIXEL30_81
                        PIXEL31_81 PIXEL32_61 PIXEL33_80 break;
                    }
                    case 211: {
                        PIXEL00_81 PIXEL01_31 PIXEL02_10 PIXEL03_80 PIXEL10_81 PIXEL11_31 PIXEL12_30
                        PIXEL13_10 PIXEL20_61 PIXEL21_30 PIXEL22_0
                        if (DIFF(6, 8)) { PIXEL23_0 PIXEL32_0 PIXEL33_0 } else { PIXEL23_50 PIXEL32_50 PIXEL33_50 }
                        PIXEL30_80 PIXEL31_10 break;
                    }
                    case 118: {
                        PIXEL00_80 PIXEL01_10
                        if (DIFF(2, 6)) { PIXEL02_0 PIXEL03_0 PIXEL13_0 } else { PIXEL02_50 PIXEL03_50 PIXEL13_50 }
                        PIXEL10_61 PIXEL11_30 PIXEL12_0 PIXEL20_82 PIXEL21_32 PIXEL22_30 PIXEL23_10 PIXEL30_82
                        PIXEL31_32 PIXEL32_10 PIXEL33_80 break;
                    }
                    case 217: {
                        PIXEL00_82 PIXEL01_82 PIXEL02_61 PIXEL03_80 PIXEL10_32 PIXEL11_32 PIXEL12_30
                        PIXEL13_10 PIXEL20_10 PIXEL21_30 PIXEL22_0
                        if (DIFF(6, 8)) { PIXEL23_0 PIXEL32_0 PIXEL33_0 } else { PIXEL23_50 PIXEL32_50 PIXEL33_50 }
                        PIXEL30_80 PIXEL31_10 break;
                    }
                    case 110: {
                        PIXEL00_80 PIXEL01_10 PIXEL02_32 PIXEL03_82 PIXEL10_10 PIXEL11_30 PIXEL12_32
                        PIXEL13_82
                        if (DIFF(8, 4)) { PIXEL20_0 PIXEL30_0 PIXEL31_0 } else { PIXEL20_50 PIXEL30_50 PIXEL31_50 }
                        PIXEL21_0 PIXEL22_30 PIXEL23_61 PIXEL32_10 PIXEL33_80 break;
                    }
                    case 155: {
                        if (DIFF(4, 2)) { PIXEL00_0 PIXEL01_0 PIXEL10_0 } else { PIXEL00_50 PIXEL01_50 PIXEL10_50 }
                        PIXEL02_10 PIXEL03_80 PIXEL11_0 PIXEL12_30 PIXEL13_10 PIXEL20_10 PIXEL21_30 PIXEL22_32
                        PIXEL23_32 PIXEL30_80 PIXEL31_61 PIXEL32_82 PIXEL33_82 break;
                    }
                    case 188: {
                        PIXEL00_80 PIXEL01_61 PIXEL02_81 PIXEL03_81 PIXEL10_10 PIXEL11_30 PIXEL12_31
                        PIXEL13_31 PIXEL20_31 PIXEL21_31 PIXEL22_32 PIXEL23_32 PIXEL30_81 PIXEL31_81
                        PIXEL32_82 PIXEL33_82 break;
                    }
                    case 185: {
                        PIXEL00_82 PIXEL01_82 PIXEL02_61 PIXEL03_80 PIXEL10_32 PIXEL11_32 PIXEL12_30
                        PIXEL13_10 PIXEL20_31 PIXEL21_31 PIXEL22_32 PIXEL23_32 PIXEL30_81 PIXEL31_81
                        PIXEL32_82 PIXEL33_82 break;
                    }
                    case 61: {
                        PIXEL00_82 PIXEL01_82 PIXEL02_81 PIXEL03_81 PIXEL10_32 PIXEL11_32 PIXEL12_31
                        PIXEL13_31 PIXEL20_31 PIXEL21_31 PIXEL22_30 PIXEL23_10 PIXEL30_81 PIXEL31_81
                        PIXEL32_61 PIXEL33_80 break;
                    }
                    case 157: {
                        PIXEL00_82 PIXEL01_82 PIXEL02_81 PIXEL03_81 PIXEL10_32 PIXEL11_32 PIXEL12_31
                        PIXEL13_31 PIXEL20_10 PIXEL21_30 PIXEL22_32 PIXEL23_32 PIXEL30_80 PIXEL31_61
                        PIXEL32_82 PIXEL33_82 break;
                    }
                    case 103: {
                        PIXEL00_81 PIXEL01_31 PIXEL02_32 PIXEL03_82 PIXEL10_81 PIXEL11_31 PIXEL12_32
                        PIXEL13_82 PIXEL20_82 PIXEL21_32 PIXEL22_30 PIXEL23_61 PIXEL30_82 PIXEL31_32
                        PIXEL32_10 PIXEL33_80 break;
                    }
                    case 227: {
                        PIXEL00_81 PIXEL01_31 PIXEL02_10 PIXEL03_80 PIXEL10_81 PIXEL11_31 PIXEL12_30
                        PIXEL13_61 PIXEL20_82 PIXEL21_32 PIXEL22_31 PIXEL23_81 PIXEL30_82 PIXEL31_32
                        PIXEL32_31 PIXEL33_81 break;
                    }
                    case 230: {
                        PIXEL00_80 PIXEL01_10 PIXEL02_32 PIXEL03_82 PIXEL10_61 PIXEL11_30 PIXEL12_32
                        PIXEL13_82 PIXEL20_82 PIXEL21_32 PIXEL22_31 PIXEL23_81 PIXEL30_82 PIXEL31_32
                        PIXEL32_31 PIXEL33_81 break;
                    }
                    case 199: {
                        PIXEL00_81 PIXEL01_31 PIXEL02_32 PIXEL03_82 PIXEL10_81 PIXEL11_31 PIXEL12_32
                        PIXEL13_82 PIXEL20_61 PIXEL21_30 PIXEL22_31 PIXEL23_81 PIXEL30_80 PIXEL31_10
                        PIXEL32_31 PIXEL33_81 break;
                    }
                    case 220: {
                        PIXEL00_80 PIXEL01_61 PIXEL02_81 PIXEL03_81 PIXEL10_10 PIXEL11_30 PIXEL12_31
                        PIXEL13_31
                        if (DIFF(8, 4)) { PIXEL20_10 PIXEL21_30 PIXEL30_80 PIXEL31_10 } else { PIXEL20_12 PIXEL21_0 PIXEL30_20 PIXEL31_11 }
                        PIXEL22_0
                        if (DIFF(6, 8)) { PIXEL23_0 PIXEL32_0 PIXEL33_0 } else { PIXEL23_50 PIXEL32_50 PIXEL33_50 }
                        break;
                    }
                    case 158: {
                        if (DIFF(4, 2)) { PIXEL00_80 PIXEL01_10 PIXEL10_10 PIXEL11_30 } else { PIXEL00_20 PIXEL01_12 PIXEL10_11 PIXEL11_0 }
                        if (DIFF(2, 6)) { PIXEL02_0 PIXEL03_0 PIXEL13_0 } else { PIXEL02_50 PIXEL03_50 PIXEL13_50 }
                        PIXEL12_0 PIXEL20_10 PIXEL21_30 PIXEL22_32 PIXEL23_32 PIXEL30_80 PIXEL31_61 PIXEL32_82
                        PIXEL33_82 break;
                    }
                    case 234: {
                        if (DIFF(4, 2)) { PIXEL00_80 PIXEL01_10 PIXEL10_10 PIXEL11_30 } else { PIXEL00_20 PIXEL01_12 PIXEL10_11 PIXEL11_0 }
                        PIXEL02_10 PIXEL03_80 PIXEL12_30 PIXEL13_61
                        if (DIFF(8, 4)) { PIXEL20_0 PIXEL30_0 PIXEL31_0 } else { PIXEL20_50 PIXEL30_50 PIXEL31_50 }
                        PIXEL21_0 PIXEL22_31 PIXEL23_81 PIXEL32_31 PIXEL33_81 break;
                    }
                    case 242: {
                        PIXEL00_80 PIXEL01_10
                        if (DIFF(2, 6)) { PIXEL02_10 PIXEL03_80 PIXEL12_30 PIXEL13_10 } else { PIXEL02_11 PIXEL03_20 PIXEL12_0 PIXEL13_12 }
                        PIXEL10_61 PIXEL11_30 PIXEL20_82 PIXEL21_32 PIXEL22_0
                        if (DIFF(6, 8)) { PIXEL23_0 PIXEL32_0 PIXEL33_0 } else { PIXEL23_50 PIXEL32_50 PIXEL33_50 }
                        PIXEL30_82 PIXEL31_32 break;
                    }
                    case 59: {
                        if (DIFF(4, 2)) { PIXEL00_0 PIXEL01_0 PIXEL10_0 } else { PIXEL00_50 PIXEL01_50 PIXEL10_50 }
                        if (DIFF(2, 6)) { PIXEL02_10 PIXEL03_80 PIXEL12_30 PIXEL13_10 } else { PIXEL02_11 PIXEL03_20 PIXEL12_0 PIXEL13_12 }
                        PIXEL11_0 PIXEL20_31 PIXEL21_31 PIXEL22_30 PIXEL23_10 PIXEL30_81 PIXEL31_81 PIXEL32_61
                        PIXEL33_80 break;
                    }
                    case 121: {
                        PIXEL00_82 PIXEL01_82 PIXEL02_61 PIXEL03_80 PIXEL10_32 PIXEL11_32 PIXEL12_30
                        PIXEL13_10
                        if (DIFF(8, 4)) { PIXEL20_0 PIXEL30_0 PIXEL31_0 } else { PIXEL20_50 PIXEL30_50 PIXEL31_50 }
                        PIXEL21_0
                        if (DIFF(6, 8)) { PIXEL22_30 PIXEL23_10 PIXEL32_10 PIXEL33_80 } else { PIXEL22_0 PIXEL23_11 PIXEL32_12 PIXEL33_20 }
                        break;
                    }
                    case 87: {
                        PIXEL00_81 PIXEL01_31
                        if (DIFF(2, 6)) { PIXEL02_0 PIXEL03_0 PIXEL13_0 } else { PIXEL02_50 PIXEL03_50 PIXEL13_50 }
                        PIXEL10_81 PIXEL11_31 PIXEL12_0 PIXEL20_61 PIXEL21_30
                        if (DIFF(6, 8)) { PIXEL22_30 PIXEL23_10 PIXEL32_10 PIXEL33_80 } else { PIXEL22_0 PIXEL23_11 PIXEL32_12 PIXEL33_20 }
                        PIXEL30_80 PIXEL31_10 break;
                    }
                    case 79: {
                        if (DIFF(4, 2)) { PIXEL00_0 PIXEL01_0 PIXEL10_0 } else { PIXEL00_50 PIXEL01_50 PIXEL10_50 }
                        PIXEL02_32 PIXEL03_82 PIXEL11_0 PIXEL12_32 PIXEL13_82
                        if (DIFF(8, 4)) { PIXEL20_10 PIXEL21_30 PIXEL30_80 PIXEL31_10 } else { PIXEL20_12 PIXEL21_0 PIXEL30_20 PIXEL31_11 }
                        PIXEL22_30 PIXEL23_61 PIXEL32_10 PIXEL33_80 break;
                    }
                    case 122: {
                        if (DIFF(4, 2)) { PIXEL00_80 PIXEL01_10 PIXEL10_10 PIXEL11_30 } else { PIXEL00_20 PIXEL01_12 PIXEL10_11 PIXEL11_0 }
                        if (DIFF(2, 6)) { PIXEL02_10 PIXEL03_80 PIXEL12_30 PIXEL13_10 } else { PIXEL02_11 PIXEL03_20 PIXEL12_0 PIXEL13_12 }
                        if (DIFF(8, 4)) { PIXEL20_0 PIXEL30_0 PIXEL31_0 } else { PIXEL20_50 PIXEL30_50 PIXEL31_50 }
                        PIXEL21_0
                        if (DIFF(6, 8)) { PIXEL22_30 PIXEL23_10 PIXEL32_10 PIXEL33_80 } else { PIXEL22_0 PIXEL23_11 PIXEL32_12 PIXEL33_20 }
                        break;
                    }
                    case 94: {
                        if (DIFF(4, 2)) { PIXEL00_80 PIXEL01_10 PIXEL10_10 PIXEL11_30 } else { PIXEL00_20 PIXEL01_12 PIXEL10_11 PIXEL11_0 }
                        if (DIFF(2, 6)) { PIXEL02_0 PIXEL03_0 PIXEL13_0 } else { PIXEL02_50 PIXEL03_50 PIXEL13_50 }
                        PIXEL12_0
                        if (DIFF(8, 4)) { PIXEL20_10 PIXEL21_30 PIXEL30_80 PIXEL31_10 } else { PIXEL20_12 PIXEL21_0 PIXEL30_20 PIXEL31_11 }
                        if (DIFF(6, 8)) { PIXEL22_30 PIXEL23_10 PIXEL32_10 PIXEL33_80 } else { PIXEL22_0 PIXEL23_11 PIXEL32_12 PIXEL33_20 }
                        break;
                    }
                    case 218: {
                        if (DIFF(4, 2)) { PIXEL00_80 PIXEL01_10 PIXEL10_10 PIXEL11_30 } else { PIXEL00_20 PIXEL01_12 PIXEL10_11 PIXEL11_0 }
                        if (DIFF(2, 6)) { PIXEL02_10 PIXEL03_80 PIXEL12_30 PIXEL13_10 } else { PIXEL02_11 PIXEL03_20 PIXEL12_0 PIXEL13_12 }
                        if (DIFF(8, 4)) { PIXEL20_10 PIXEL21_30 PIXEL30_80 PIXEL31_10 } else { PIXEL20_12 PIXEL21_0 PIXEL30_20 PIXEL31_11 }
                        PIXEL22_0
                        if (DIFF(6, 8)) { PIXEL23_0 PIXEL32_0 PIXEL33_0 } else { PIXEL23_50 PIXEL32_50 PIXEL33_50 }
                        break;
                    }
                    case 91: {
                        if (DIFF(4, 2)) { PIXEL00_0 PIXEL01_0 PIXEL10_0 } else { PIXEL00_50 PIXEL01_50 PIXEL10_50 }
                        if (DIFF(2, 6)) { PIXEL02_10 PIXEL03_80 PIXEL12_30 PIXEL13_10 } else { PIXEL02_11 PIXEL03_20 PIXEL12_0 PIXEL13_12 }
                        PIXEL11_0
                        if (DIFF(8, 4)) { PIXEL20_10 PIXEL21_30 PIXEL30_80 PIXEL31_10 } else { PIXEL20_12 PIXEL21_0 PIXEL30_20 PIXEL31_11 }
                        if (DIFF(6, 8)) { PIXEL22_30 PIXEL23_10 PIXEL32_10 PIXEL33_80 } else { PIXEL22_0 PIXEL23_11 PIXEL32_12 PIXEL33_20 }
                        break;
                    }
                    case 229: {
                        PIXEL00_20 PIXEL01_60 PIXEL02_60 PIXEL03_20 PIXEL10_60 PIXEL11_70 PIXEL12_70
                        PIXEL13_60 PIXEL20_82 PIXEL21_32 PIXEL22_31 PIXEL23_81 PIXEL30_82 PIXEL31_32
                        PIXEL32_31 PIXEL33_81 break;
                    }
                    case 167: {
                        PIXEL00_81 PIXEL01_31 PIXEL02_32 PIXEL03_82 PIXEL10_81 PIXEL11_31 PIXEL12_32
                        PIXEL13_82 PIXEL20_60 PIXEL21_70 PIXEL22_70 PIXEL23_60 PIXEL30_20 PIXEL31_60
                        PIXEL32_60 PIXEL33_20 break;
                    }
                    case 173: {
                        PIXEL00_82 PIXEL01_82 PIXEL02_60 PIXEL03_20 PIXEL10_32 PIXEL11_32 PIXEL12_70
                        PIXEL13_60 PIXEL20_31 PIXEL21_31 PIXEL22_70 PIXEL23_60 PIXEL30_81 PIXEL31_81
                        PIXEL32_60 PIXEL33_20 break;
                    }
                    case 181: {
                        PIXEL00_20 PIXEL01_60 PIXEL02_81 PIXEL03_81 PIXEL10_60 PIXEL11_70 PIXEL12_31
                        PIXEL13_31 PIXEL20_60 PIXEL21_70 PIXEL22_32 PIXEL23_32 PIXEL30_20 PIXEL31_60
                        PIXEL32_82 PIXEL33_82 break;
                    }
                    case 186: {
                        if (DIFF(4, 2)) { PIXEL00_80 PIXEL01_10 PIXEL10_10 PIXEL11_30 } else { PIXEL00_20 PIXEL01_12 PIXEL10_11 PIXEL11_0 }
                        if (DIFF(2, 6)) { PIXEL02_10 PIXEL03_80 PIXEL12_30 PIXEL13_10 } else { PIXEL02_11 PIXEL03_20 PIXEL12_0 PIXEL13_12 }
                        PIXEL20_31 PIXEL21_31 PIXEL22_32 PIXEL23_32 PIXEL30_81 PIXEL31_81 PIXEL32_82
                        PIXEL33_82 break;
                    }
                    case 115: {
                        PIXEL00_81 PIXEL01_31
                        if (DIFF(2, 6)) { PIXEL02_10 PIXEL03_80 PIXEL12_30 PIXEL13_10 } else { PIXEL02_11 PIXEL03_20 PIXEL12_0 PIXEL13_12 }
                        PIXEL10_81 PIXEL11_31 PIXEL20_82 PIXEL21_32
                        if (DIFF(6, 8)) { PIXEL22_30 PIXEL23_10 PIXEL32_10 PIXEL33_80 } else { PIXEL22_0 PIXEL23_11 PIXEL32_12 PIXEL33_20 }
                        PIXEL30_82 PIXEL31_32 break;
                    }
                    case 93: {
                        PIXEL00_82 PIXEL01_82 PIXEL02_81 PIXEL03_81 PIXEL10_32 PIXEL11_32 PIXEL12_31
                        PIXEL13_31
                        if (DIFF(8, 4)) { PIXEL20_10 PIXEL21_30 PIXEL30_80 PIXEL31_10 } else { PIXEL20_12 PIXEL21_0 PIXEL30_20 PIXEL31_11 }
                        if (DIFF(6, 8)) { PIXEL22_30 PIXEL23_10 PIXEL32_10 PIXEL33_80 } else { PIXEL22_0 PIXEL23_11 PIXEL32_12 PIXEL33_20 }
                        break;
                    }
                    case 206: {
                        if (DIFF(4, 2)) { PIXEL00_80 PIXEL01_10 PIXEL10_10 PIXEL11_30 } else { PIXEL00_20 PIXEL01_12 PIXEL10_11 PIXEL11_0 }
                        PIXEL02_32 PIXEL03_82 PIXEL12_32 PIXEL13_82
                        if (DIFF(8, 4)) { PIXEL20_10 PIXEL21_30 PIXEL30_80 PIXEL31_10 } else { PIXEL20_12 PIXEL21_0 PIXEL30_20 PIXEL31_11 }
                        PIXEL22_31 PIXEL23_81 PIXEL32_31 PIXEL33_81 break;
                    }
                    case 205: case 201: {
                        PIXEL00_82 PIXEL01_82 PIXEL02_60 PIXEL03_20 PIXEL10_32 PIXEL11_32 PIXEL12_70
                        PIXEL13_60
                        if (DIFF(8, 4)) { PIXEL20_10 PIXEL21_30 PIXEL30_80 PIXEL31_10 } else { PIXEL20_12 PIXEL21_0 PIXEL30_20 PIXEL31_11 }
                        PIXEL22_31 PIXEL23_81 PIXEL32_31 PIXEL33_81 break;
                    }
                    case 174: case 46: {
                        if (DIFF(4, 2)) { PIXEL00_80 PIXEL01_10 PIXEL10_10 PIXEL11_30 } else { PIXEL00_20 PIXEL01_12 PIXEL10_11 PIXEL11_0 }
                        PIXEL02_32 PIXEL03_82 PIXEL12_32 PIXEL13_82 PIXEL20_31 PIXEL21_31 PIXEL22_70
                        PIXEL23_60 PIXEL30_81 PIXEL31_81 PIXEL32_60 PIXEL33_20 break;
                    }
                    case 179: case 147: {
                        PIXEL00_81 PIXEL01_31
                        if (DIFF(2, 6)) { PIXEL02_10 PIXEL03_80 PIXEL12_30 PIXEL13_10 } else { PIXEL02_11 PIXEL03_20 PIXEL12_0 PIXEL13_12 }
                        PIXEL10_81 PIXEL11_31 PIXEL20_60 PIXEL21_70 PIXEL22_32 PIXEL23_32 PIXEL30_20
                        PIXEL31_60 PIXEL32_82 PIXEL33_82 break;
                    }
                    case 117: case 116: {
                        PIXEL00_20 PIXEL01_60 PIXEL02_81 PIXEL03_81 PIXEL10_60 PIXEL11_70 PIXEL12_31
                        PIXEL13_31 PIXEL20_82 PIXEL21_32
                        if (DIFF(6, 8)) { PIXEL22_30 PIXEL23_10 PIXEL32_10 PIXEL33_80 } else { PIXEL22_0 PIXEL23_11 PIXEL32_12 PIXEL33_20 }
                        PIXEL30_82 PIXEL31_32 break;
                    }
                    case 189: {
                        PIXEL00_82 PIXEL01_82 PIXEL02_81 PIXEL03_81 PIXEL10_32 PIXEL11_32 PIXEL12_31
                        PIXEL13_31 PIXEL20_31 PIXEL21_31 PIXEL22_32 PIXEL23_32 PIXEL30_81 PIXEL31_81
                        PIXEL32_82 PIXEL33_82 break;
                    }
                    case 231: {
                        PIXEL00_81 PIXEL01_31 PIXEL02_32 PIXEL03_82 PIXEL10_81 PIXEL11_31 PIXEL12_32
                        PIXEL13_82 PIXEL20_82 PIXEL21_32 PIXEL22_31 PIXEL23_81 PIXEL30_82 PIXEL31_32
                        PIXEL32_31 PIXEL33_81 break;
                    }
                    case 126: {
                        PIXEL00_80 PIXEL01_10
                        if (DIFF(2, 6)) { PIXEL02_0 PIXEL03_0 PIXEL13_0 } else { PIXEL02_50 PIXEL03_50 PIXEL13_50 }
                        PIXEL10_10 PIXEL11_30 PIXEL12_0
                        if (DIFF(8, 4)) { PIXEL20_0 PIXEL30_0 PIXEL31_0 } else { PIXEL20_50 PIXEL30_50 PIXEL31_50 }
                        PIXEL21_0 PIXEL22_30 PIXEL23_10 PIXEL32_10 PIXEL33_80 break;
                    }
                    case 219: {
                        if (DIFF(4, 2)) { PIXEL00_0 PIXEL01_0 PIXEL10_0 } else { PIXEL00_50 PIXEL01_50 PIXEL10_50 }
                        PIXEL02_10 PIXEL03_80 PIXEL11_0 PIXEL12_30 PIXEL13_10 PIXEL20_10 PIXEL21_30 PIXEL22_0
                        if (DIFF(6, 8)) { PIXEL23_0 PIXEL32_0 PIXEL33_0 } else { PIXEL23_50 PIXEL32_50 PIXEL33_50 }
                        PIXEL30_80 PIXEL31_10 break;
                    }
                    case 125: {
                        if (DIFF(8, 4)) { PIXEL00_82 PIXEL10_32 PIXEL20_0 PIXEL21_0 PIXEL30_0 PIXEL31_0 } else { PIXEL00_11 PIXEL10_13 PIXEL20_83 PIXEL21_70 PIXEL30_50 PIXEL31_21 }
                        PIXEL01_82 PIXEL02_81 PIXEL03_81 PIXEL11_32 PIXEL12_31 PIXEL13_31 PIXEL22_30
                        PIXEL23_10 PIXEL32_10 PIXEL33_80 break;
                    }
                    case 221: {
                        PIXEL00_82 PIXEL01_82 PIXEL02_81
                        if (DIFF(6, 8)) { PIXEL03_81 PIXEL13_31 PIXEL22_0 PIXEL23_0 PIXEL32_0 PIXEL33_0 } else { PIXEL03_12 PIXEL13_14 PIXEL22_70 PIXEL23_83 PIXEL32_21 PIXEL33_50 }
                        PIXEL10_32 PIXEL11_32 PIXEL12_31 PIXEL20_10 PIXEL21_30 PIXEL30_80 PIXEL31_10 break;
                    }
                    case 207: {
                        if (DIFF(4, 2)) { PIXEL00_0 PIXEL01_0 PIXEL02_32 PIXEL03_82 PIXEL10_0 PIXEL11_0 } else { PIXEL00_50 PIXEL01_83 PIXEL02_13 PIXEL03_11 PIXEL10_21 PIXEL11_70 }
                        PIXEL12_32 PIXEL13_82 PIXEL20_10 PIXEL21_30 PIXEL22_31 PIXEL23_81 PIXEL30_80
                        PIXEL31_10 PIXEL32_31 PIXEL33_81 break;
                    }
                    case 238: {
                        PIXEL00_80 PIXEL01_10 PIXEL02_32 PIXEL03_82 PIXEL10_10 PIXEL11_30 PIXEL12_32
                        PIXEL13_82
                        if (DIFF(8, 4)) { PIXEL20_0 PIXEL21_0 PIXEL30_0 PIXEL31_0 PIXEL32_31 PIXEL33_81 } else { PIXEL20_21 PIXEL21_70 PIXEL30_50 PIXEL31_83 PIXEL32_14 PIXEL33_12 }
                        PIXEL22_31 PIXEL23_81 break;
                    }
                    case 190: {
                        PIXEL00_80 PIXEL01_10
                        if (DIFF(2, 6)) { PIXEL02_0 PIXEL03_0 PIXEL12_0 PIXEL13_0 PIXEL23_32 PIXEL33_82 } else { PIXEL02_21 PIXEL03_50 PIXEL12_70 PIXEL13_83 PIXEL23_13 PIXEL33_11 }
                        PIXEL10_10 PIXEL11_30 PIXEL20_31 PIXEL21_31 PIXEL22_32 PIXEL30_81 PIXEL31_81
                        PIXEL32_82 break;
                    }
                    case 187: {
                        if (DIFF(4, 2)) { PIXEL00_0 PIXEL01_0 PIXEL10_0 PIXEL11_0 PIXEL20_31 PIXEL30_81 } else { PIXEL00_50 PIXEL01_21 PIXEL10_83 PIXEL11_70 PIXEL20_14 PIXEL30_12 }
                        PIXEL02_10 PIXEL03_80 PIXEL12_30 PIXEL13_10 PIXEL21_31 PIXEL22_32 PIXEL23_32
                        PIXEL31_81 PIXEL32_82 PIXEL33_82 break;
                    }
                    case 243: {
                        PIXEL00_81 PIXEL01_31 PIXEL02_10 PIXEL03_80 PIXEL10_81 PIXEL11_31 PIXEL12_30
                        PIXEL13_10 PIXEL20_82 PIXEL21_32
                        if (DIFF(6, 8)) { PIXEL22_0 PIXEL23_0 PIXEL30_82 PIXEL31_32 PIXEL32_0 PIXEL33_0 } else { PIXEL22_70 PIXEL23_21 PIXEL30_11 PIXEL31_13 PIXEL32_83 PIXEL33_50 }
                        break;
                    }
                    case 119: {
                        if (DIFF(2, 6)) { PIXEL00_81 PIXEL01_31 PIXEL02_0 PIXEL03_0 PIXEL12_0 PIXEL13_0 } else { PIXEL00_12 PIXEL01_14 PIXEL02_83 PIXEL03_50 PIXEL12_70 PIXEL13_21 }
                        PIXEL10_81 PIXEL11_31 PIXEL20_82 PIXEL21_32 PIXEL22_30 PIXEL23_10 PIXEL30_82
                        PIXEL31_32 PIXEL32_10 PIXEL33_80 break;
                    }
                    case 237: case 233: {
                        PIXEL00_82 PIXEL01_82 PIXEL02_60 PIXEL03_20 PIXEL10_32 PIXEL11_32 PIXEL12_70
                        PIXEL13_60 PIXEL20_0 PIXEL21_0 PIXEL22_31 PIXEL23_81
                        if (DIFF(8, 4)) { PIXEL30_0 } else { PIXEL30_20 } PIXEL31_0 PIXEL32_31 PIXEL33_81
                        break;
                    }
                    case 175: case 47: {
                        if (DIFF(4, 2)) { PIXEL00_0 } else { PIXEL00_20 } PIXEL01_0 PIXEL02_32 PIXEL03_82
                        PIXEL10_0 PIXEL11_0 PIXEL12_32 PIXEL13_82 PIXEL20_31 PIXEL21_31 PIXEL22_70 PIXEL23_60
                        PIXEL30_81 PIXEL31_81 PIXEL32_60 PIXEL33_20 break;
                    }
                    case 183: case 151: {
                        PIXEL00_81 PIXEL01_31 PIXEL02_0 if (DIFF(2, 6)) { PIXEL03_0 } else { PIXEL03_20 }
                        PIXEL10_81 PIXEL11_31 PIXEL12_0 PIXEL13_0 PIXEL20_60 PIXEL21_70 PIXEL22_32 PIXEL23_32
                        PIXEL30_20 PIXEL31_60 PIXEL32_82 PIXEL33_82 break;
                    }
                    case 245: case 244: {
                        PIXEL00_20 PIXEL01_60 PIXEL02_81 PIXEL03_81 PIXEL10_60 PIXEL11_70 PIXEL12_31
                        PIXEL13_31 PIXEL20_82 PIXEL21_32 PIXEL22_0 PIXEL23_0 PIXEL30_82 PIXEL31_32 PIXEL32_0
                        if (DIFF(6, 8)) { PIXEL33_0 } else { PIXEL33_20 } break;
                    }
                    case 250: {
                        PIXEL00_80 PIXEL01_10 PIXEL02_10 PIXEL03_80 PIXEL10_10 PIXEL11_30 PIXEL12_30
                        PIXEL13_10
                        if (DIFF(8, 4)) { PIXEL20_0 PIXEL30_0 PIXEL31_0 } else { PIXEL20_50 PIXEL30_50 PIXEL31_50 }
                        PIXEL21_0 PIXEL22_0
                        if (DIFF(6, 8)) { PIXEL23_0 PIXEL32_0 PIXEL33_0 } else { PIXEL23_50 PIXEL32_50 PIXEL33_50 }
                        break;
                    }
                    case 123: {
                        if (DIFF(4, 2)) { PIXEL00_0 PIXEL01_0 PIXEL10_0 } else { PIXEL00_50 PIXEL01_50 PIXEL10_50 }
                        PIXEL02_10 PIXEL03_80 PIXEL11_0 PIXEL12_30 PIXEL13_10
                        if (DIFF(8, 4)) { PIXEL20_0 PIXEL30_0 PIXEL31_0 } else { PIXEL20_50 PIXEL30_50 PIXEL31_50 }
                        PIXEL21_0 PIXEL22_30 PIXEL23_10 PIXEL32_10 PIXEL33_80 break;
                    }
                    case 95: {
                        if (DIFF(4, 2)) { PIXEL00_0 PIXEL01_0 PIXEL10_0 } else { PIXEL00_50 PIXEL01_50 PIXEL10_50 }
                        if (DIFF(2, 6)) { PIXEL02_0 PIXEL03_0 PIXEL13_0 } else { PIXEL02_50 PIXEL03_50 PIXEL13_50 }
                        PIXEL11_0 PIXEL12_0 PIXEL20_10 PIXEL21_30 PIXEL22_30 PIXEL23_10 PIXEL30_80 PIXEL31_10
                        PIXEL32_10 PIXEL33_80 break;
                    }
                    case 222: {
                        PIXEL00_80 PIXEL01_10
                        if (DIFF(2, 6)) { PIXEL02_0 PIXEL03_0 PIXEL13_0 } else { PIXEL02_50 PIXEL03_50 PIXEL13_50 }
                        PIXEL10_10 PIXEL11_30 PIXEL12_0 PIXEL20_10 PIXEL21_30 PIXEL22_0
                        if (DIFF(6, 8)) { PIXEL23_0 PIXEL32_0 PIXEL33_0 } else { PIXEL23_50 PIXEL32_50 PIXEL33_50 }
                        PIXEL30_80 PIXEL31_10 break;
                    }
                    case 252: {
                        PIXEL00_80 PIXEL01_61 PIXEL02_81 PIXEL03_81 PIXEL10_10 PIXEL11_30 PIXEL12_31
                        PIXEL13_31
                        if (DIFF(8, 4)) { PIXEL20_0 PIXEL30_0 PIXEL31_0 } else { PIXEL20_50 PIXEL30_50 PIXEL31_50 }
                        PIXEL21_0 PIXEL22_0 PIXEL23_0 PIXEL32_0
                        if (DIFF(6, 8)) { PIXEL33_0 } else { PIXEL33_20 } break;
                    }
                    case 249: {
                        PIXEL00_82 PIXEL01_82 PIXEL02_61 PIXEL03_80 PIXEL10_32 PIXEL11_32 PIXEL12_30
                        PIXEL13_10 PIXEL20_0 PIXEL21_0 PIXEL22_0
                        if (DIFF(6, 8)) { PIXEL23_0 PIXEL32_0 PIXEL33_0 } else { PIXEL23_50 PIXEL32_50 PIXEL33_50 }
                        if (DIFF(8, 4)) { PIXEL30_0 } else { PIXEL30_20 } PIXEL31_0 break;
                    }
                    case 235: {
                        if (DIFF(4, 2)) { PIXEL00_0 PIXEL01_0 PIXEL10_0 } else { PIXEL00_50 PIXEL01_50 PIXEL10_50 }
                        PIXEL02_10 PIXEL03_80 PIXEL11_0 PIXEL12_30 PIXEL13_61 PIXEL20_0 PIXEL21_0 PIXEL22_31
                        PIXEL23_81 if (DIFF(8, 4)) { PIXEL30_0 } else { PIXEL30_20 } PIXEL31_0 PIXEL32_31
                        PIXEL33_81 break;
                    }
                    case 111: {
                        if (DIFF(4, 2)) { PIXEL00_0 } else { PIXEL00_20 } PIXEL01_0 PIXEL02_32 PIXEL03_82
                        PIXEL10_0 PIXEL11_0 PIXEL12_32 PIXEL13_82
                        if (DIFF(8, 4)) { PIXEL20_0 PIXEL30_0 PIXEL31_0 } else { PIXEL20_50 PIXEL30_50 PIXEL31_50 }
                        PIXEL21_0 PIXEL22_30 PIXEL23_61 PIXEL32_10 PIXEL33_80 break;
                    }
                    case 63: {
                        if (DIFF(4, 2)) { PIXEL00_0 } else { PIXEL00_20 } PIXEL01_0
                        if (DIFF(2, 6)) { PIXEL02_0 PIXEL03_0 PIXEL13_0 } else { PIXEL02_50 PIXEL03_50 PIXEL13_50 }
                        PIXEL10_0 PIXEL11_0 PIXEL12_0 PIXEL20_31 PIXEL21_31 PIXEL22_30 PIXEL23_10 PIXEL30_81
                        PIXEL31_81 PIXEL32_61 PIXEL33_80 break;
                    }
                    case 159: {
                        if (DIFF(4, 2)) { PIXEL00_0 PIXEL01_0 PIXEL10_0 } else { PIXEL00_50 PIXEL01_50 PIXEL10_50 }
                        PIXEL02_0 if (DIFF(2, 6)) { PIXEL03_0 } else { PIXEL03_20 } PIXEL11_0 PIXEL12_0
                        PIXEL13_0 PIXEL20_10 PIXEL21_30 PIXEL22_32 PIXEL23_32 PIXEL30_80 PIXEL31_61 PIXEL32_82
                        PIXEL33_82 break;
                    }
                    case 215: {
                        PIXEL00_81 PIXEL01_31 PIXEL02_0 if (DIFF(2, 6)) { PIXEL03_0 } else { PIXEL03_20 }
                        PIXEL10_81 PIXEL11_31 PIXEL12_0 PIXEL13_0 PIXEL20_61 PIXEL21_30 PIXEL22_0
                        if (DIFF(6, 8)) { PIXEL23_0 PIXEL32_0 PIXEL33_0 } else { PIXEL23_50 PIXEL32_50 PIXEL33_50 }
                        PIXEL30_80 PIXEL31_10 break;
                    }
                    case 246: {
                        PIXEL00_80 PIXEL01_10
                        if (DIFF(2, 6)) { PIXEL02_0 PIXEL03_0 PIXEL13_0 } else { PIXEL02_50 PIXEL03_50 PIXEL13_50 }
                        PIXEL10_61 PIXEL11_30 PIXEL12_0 PIXEL20_82 PIXEL21_32 PIXEL22_0 PIXEL23_0 PIXEL30_82
                        PIXEL31_32 PIXEL32_0 if (DIFF(6, 8)) { PIXEL33_0 } else { PIXEL33_20 } break;
                    }
                    case 254: {
                        PIXEL00_80 PIXEL01_10
                        if (DIFF(2, 6)) { PIXEL02_0 PIXEL03_0 PIXEL13_0 } else { PIXEL02_50 PIXEL03_50 PIXEL13_50 }
                        PIXEL10_10 PIXEL11_30 PIXEL12_0
                        if (DIFF(8, 4)) { PIXEL20_0 PIXEL30_0 PIXEL31_0 } else { PIXEL20_50 PIXEL30_50 PIXEL31_50 }
                        PIXEL21_0 PIXEL22_0 PIXEL23_0 PIXEL32_0
                        if (DIFF(6, 8)) { PIXEL33_0 } else { PIXEL33_20 } break;
                    }
                    case 253: {
                        PIXEL00_82 PIXEL01_82 PIXEL02_81 PIXEL03_81 PIXEL10_32 PIXEL11_32 PIXEL12_31
                        PIXEL13_31 PIXEL20_0 PIXEL21_0 PIXEL22_0 PIXEL23_0
                        if (DIFF(8, 4)) { PIXEL30_0 } else { PIXEL30_20 } PIXEL31_0 PIXEL32_0
                        if (DIFF(6, 8)) { PIXEL33_0 } else { PIXEL33_20 } break;
                    }
                    case 251: {
                        if (DIFF(4, 2)) { PIXEL00_0 PIXEL01_0 PIXEL10_0 } else { PIXEL00_50 PIXEL01_50 PIXEL10_50 }
                        PIXEL02_10 PIXEL03_80 PIXEL11_0 PIXEL12_30 PIXEL13_10 PIXEL20_0 PIXEL21_0 PIXEL22_0
                        if (DIFF(6, 8)) { PIXEL23_0 PIXEL32_0 PIXEL33_0 } else { PIXEL23_50 PIXEL32_50 PIXEL33_50 }
                        if (DIFF(8, 4)) { PIXEL30_0 } else { PIXEL30_20 } PIXEL31_0 break;
                    }
                    case 239: {
                        if (DIFF(4, 2)) { PIXEL00_0 } else { PIXEL00_20 } PIXEL01_0 PIXEL02_32 PIXEL03_82
                        PIXEL10_0 PIXEL11_0 PIXEL12_32 PIXEL13_82 PIXEL20_0 PIXEL21_0 PIXEL22_31 PIXEL23_81
                        if (DIFF(8, 4)) { PIXEL30_0 } else { PIXEL30_20 } PIXEL31_0 PIXEL32_31 PIXEL33_81
                        break;
                    }
                    case 127: {
                        if (DIFF(4, 2)) { PIXEL00_0 } else { PIXEL00_20 } PIXEL01_0
                        if (DIFF(2, 6)) { PIXEL02_0 PIXEL03_0 PIXEL13_0 } else { PIXEL02_50 PIXEL03_50 PIXEL13_50 }
                        PIXEL10_0 PIXEL11_0 PIXEL12_0
                        if (DIFF(8, 4)) { PIXEL20_0 PIXEL30_0 PIXEL31_0 } else { PIXEL20_50 PIXEL30_50 PIXEL31_50 }
                        PIXEL21_0 PIXEL22_30 PIXEL23_10 PIXEL32_10 PIXEL33_80 break;
                    }
                    case 191: {
                        if (DIFF(4, 2)) { PIXEL00_0 } else { PIXEL00_20 } PIXEL01_0 PIXEL02_0
                        if (DIFF(2, 6)) { PIXEL03_0 } else { PIXEL03_20 } PIXEL10_0 PIXEL11_0 PIXEL12_0
                        PIXEL13_0 PIXEL20_31 PIXEL21_31 PIXEL22_32 PIXEL23_32 PIXEL30_81 PIXEL31_81 PIXEL32_82
                        PIXEL33_82 break;
                    }
                    case 223: {
                        if (DIFF(4, 2)) { PIXEL00_0 PIXEL01_0 PIXEL10_0 } else { PIXEL00_50 PIXEL01_50 PIXEL10_50 }
                        PIXEL02_0 if (DIFF(2, 6)) { PIXEL03_0 } else { PIXEL03_20 } PIXEL11_0 PIXEL12_0
                        PIXEL13_0 PIXEL20_10 PIXEL21_30 PIXEL22_0
                        if (DIFF(6, 8)) { PIXEL23_0 PIXEL32_0 PIXEL33_0 } else { PIXEL23_50 PIXEL32_50 PIXEL33_50 }
                        PIXEL30_80 PIXEL31_10 break;
                    }
                    case 247: {
                        PIXEL00_81 PIXEL01_31 PIXEL02_0 if (DIFF(2, 6)) { PIXEL03_0 } else { PIXEL03_20 }
                        PIXEL10_81 PIXEL11_31 PIXEL12_0 PIXEL13_0 PIXEL20_82 PIXEL21_32 PIXEL22_0 PIXEL23_0
                        PIXEL30_82 PIXEL31_32 PIXEL32_0 if (DIFF(6, 8)) { PIXEL33_0 } else { PIXEL33_20 }
                        break;
                    }
                    case 255: {
                        if (DIFF(4, 2)) { PIXEL00_0 } else { PIXEL00_20 } PIXEL01_0 PIXEL02_0
                        if (DIFF(2, 6)) { PIXEL03_0 } else { PIXEL03_20 } PIXEL10_0 PIXEL11_0 PIXEL12_0
                        PIXEL13_0 PIXEL20_0 PIXEL21_0 PIXEL22_0 PIXEL23_0
                        if (DIFF(8, 4)) { PIXEL30_0 } else { PIXEL30_20 } PIXEL31_0 PIXEL32_0
                        if (DIFF(6, 8)) { PIXEL33_0 } else { PIXEL33_20 } break;
                    }
                }
            }
        }
    }
}

#undef PIXEL00_0
#undef PIXEL00_11
#undef PIXEL00_12
#undef PIXEL00_20
#undef PIXEL00_50
#undef PIXEL00_80
#undef PIXEL00_81
#undef PIXEL00_82
#undef PIXEL01_0
#undef PIXEL01_10
#undef PIXEL01_12
#undef PIXEL01_14
#undef PIXEL01_21
#undef PIXEL01_31
#undef PIXEL01_50
#undef PIXEL01_60
#undef PIXEL01_61
#undef PIXEL01_82
#undef PIXEL01_83
#undef PIXEL02_0
#undef PIXEL02_10
#undef PIXEL02_11
#undef PIXEL02_13
#undef PIXEL02_21
#undef PIXEL02_32
#undef PIXEL02_50
#undef PIXEL02_60
#undef PIXEL02_61
#undef PIXEL02_81
#undef PIXEL02_83
#undef PIXEL03_0
#undef PIXEL03_11
#undef PIXEL03_12
#undef PIXEL03_20
#undef PIXEL03_50
#undef PIXEL03_80
#undef PIXEL03_81
#undef PIXEL03_82
#undef PIXEL10_0
#undef PIXEL10_10
#undef PIXEL10_11
#undef PIXEL10_13
#undef PIXEL10_21
#undef PIXEL10_32
#undef PIXEL10_50
#undef PIXEL10_60
#undef PIXEL10_61
#undef PIXEL10_81
#undef PIXEL10_83
#undef PIXEL11_0
#undef PIXEL11_30
#undef PIXEL11_31
#undef PIXEL11_32
#undef PIXEL11_70
#undef PIXEL12_0
#undef PIXEL12_30
#undef PIXEL12_31
#undef PIXEL12_32
#undef PIXEL12_70
#undef PIXEL13_0
#undef PIXEL13_10
#undef PIXEL13_12
#undef PIXEL13_14
#undef PIXEL13_21
#undef PIXEL13_31
#undef PIXEL13_50
#undef PIXEL13_60
#undef PIXEL13_61
#undef PIXEL13_82
#undef PIXEL13_83
#undef PIXEL20_0
#undef PIXEL20_10
#undef PIXEL20_12
#undef PIXEL20_14
#undef PIXEL20_21
#undef PIXEL20_31
#undef PIXEL20_50
#undef PIXEL20_60
#undef PIXEL20_61
#undef PIXEL20_82
#undef PIXEL20_83
#undef PIXEL21_0
#undef PIXEL21_30
#undef PIXEL21_31
#undef PIXEL21_32
#undef PIXEL21_70
#undef PIXEL22_0
#undef PIXEL22_30
#undef PIXEL22_31
#undef PIXEL22_32
#undef PIXEL22_70
#undef PIXEL23_0
#undef PIXEL23_10
#undef PIXEL23_11
#undef PIXEL23_13
#undef PIXEL23_21
#undef PIXEL23_32
#undef PIXEL23_50
#undef PIXEL23_60
#undef PIXEL23_61
#undef PIXEL23_81
#undef PIXEL23_83
#undef PIXEL30_0
#undef PIXEL30_11
#undef PIXEL30_12
#undef PIXEL30_20
#undef PIXEL30_50
#undef PIXEL30_80
#undef PIXEL30_81
#undef PIXEL30_82
#undef PIXEL31_0
#undef PIXEL31_10
#undef PIXEL31_11
#undef PIXEL31_13
#undef PIXEL31_21
#undef PIXEL31_32
#undef PIXEL31_50
#undef PIXEL31_60
#undef PIXEL31_61
#undef PIXEL31_81
#undef PIXEL31_83
#undef PIXEL32_0
#undef PIXEL32_10
#undef PIXEL32_12
#undef PIXEL32_14
#undef PIXEL32_21
#undef PIXEL32_31
#undef PIXEL32_50
#undef PIXEL32_60
#undef PIXEL32_61
#undef PIXEL32_82
#undef PIXEL32_83
#undef PIXEL33_0
#undef PIXEL33_11
#undef PIXEL33_12
#undef PIXEL33_20
#undef PIXEL33_50
#undef PIXEL33_80
#undef PIXEL33_81
#undef PIXEL33_82

#undef DIFF

void upscale_hqx_rows(int k, const uint32_t *src, int ss, int sw, int sh,
                      uint32_t *dst, int ds, int y0, int y1)
{
    if (k == 2) hq2x_rows(src, ss, sw, sh, dst, ds, y0, y1);
    else if (k == 3) hq3x_rows(src, ss, sw, sh, dst, ds, y0, y1);
    else hq4x_rows(src, ss, sw, sh, dst, ds, y0, y1);
}
