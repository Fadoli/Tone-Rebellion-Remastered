#include "island_palette_lookup.h"

#include <assert.h>
#include <stdint.h>

static uint8_t reference_nearest(const uint32_t *palette, size_t count,
                                 uint32_t color)
{
    uint8_t best = 0;
    uint32_t best_distance = UINT32_MAX;
    size_t i;
    color &= UINT32_C(0x00ffffff);
    for (i = 0; i < count; ++i) {
        uint32_t candidate = palette[i] & UINT32_C(0x00ffffff);
        int red = (int)((color >> 16) & 0xffU) -
                  (int)((candidate >> 16) & 0xffU);
        int green = (int)((color >> 8) & 0xffU) -
                    (int)((candidate >> 8) & 0xffU);
        int blue = (int)(color & 0xffU) - (int)(candidate & 0xffU);
        uint32_t distance = (uint32_t)(red * red + green * green + blue * blue);
        if (distance < best_distance) {
            best_distance = distance;
            best = (uint8_t)i;
            if (distance == 0U) break;
        }
    }
    return best;
}

int main(void)
{
    IslandPaletteLookup lookup;
    uint32_t palette[256];
    uint8_t index;
    unsigned int i;

    for (i = 0; i < 256U; ++i) {
        palette[i] = ((i * 73U) & 0xffU) << 16 |
                     ((i * 151U) & 0xffU) << 8 |
                     ((i * 199U) & 0xffU);
    }
    palette[255] = palette[17];
    island_palette_lookup_build(&lookup, palette, 256U);
    for (i = 0; i < 255U; ++i) {
        assert(island_palette_lookup_find(&lookup, palette[i], &index));
        assert(index == i);
    }
    assert(island_palette_lookup_find(&lookup, palette[255], &index));
    assert(index == 17U);
    assert(!island_palette_lookup_find(&lookup, UINT32_C(0x123456), &index));
    assert(!island_palette_lookup_find(NULL, palette[0], &index));
    assert(!island_palette_lookup_find(&lookup, palette[0], NULL));

    {
        static const uint32_t samples[] = {
            UINT32_C(0x123456), UINT32_C(0xabcdef), UINT32_C(0x000000),
            UINT32_C(0xffffff), UINT32_C(0x123457), UINT32_C(0x123456)
        };
        size_t sample;
        for (sample = 0; sample < sizeof(samples) / sizeof(samples[0]); ++sample) {
            uint8_t expected = reference_nearest(palette, 256U, samples[sample]);
            assert(island_palette_lookup_nearest(&lookup, samples[sample], &index));
            assert(index == expected);
            /* Repeated reads exercise the memoized path. */
            assert(island_palette_lookup_nearest(&lookup, samples[sample], &index));
            assert(index == expected);
        }
    }

    {
        uint32_t sample = UINT32_C(0x6d2b79f5);
        unsigned int probe;
        for (probe = 0; probe < 1024U; ++probe) {
            uint32_t color;
            uint8_t expected;
            sample = sample * UINT32_C(1664525) + UINT32_C(1013904223);
            color = sample & UINT32_C(0x00ffffff);
            expected = reference_nearest(palette, 256U, color);
            assert(island_palette_lookup_nearest(&lookup, color, &index));
            assert(index == expected);
        }
    }

    /* Rebuilding with a different palette clears cached nearest results. */
    palette[0] = UINT32_C(0xffffff);
    island_palette_lookup_build(&lookup, palette, 1U);
    assert(island_palette_lookup_nearest(&lookup, UINT32_C(0x123456), &index));
    assert(index == 0U);

    island_palette_lookup_build(&lookup, palette, 0U);
    assert(!island_palette_lookup_find(&lookup, palette[0], &index));
    assert(!island_palette_lookup_nearest(&lookup, palette[0], &index));
    return 0;
}
