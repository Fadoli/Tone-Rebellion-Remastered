#include "island_data.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

static void test_original_type_tags(void)
{
    static const struct {
        const char *tag;
        IslandLocationKind kind;
    } cases[] = {
        { "tone", ISLAND_LOCATION_TONE },
        { "pad", ISLAND_LOCATION_PAD },
        { "smpad", ISLAND_LOCATION_PAD_SMALL },
        { "mdpad", ISLAND_LOCATION_PAD_MEDIUM },
        { "lgpad", ISLAND_LOCATION_PAD_LARGE },
        { "special", ISLAND_LOCATION_SPECIAL },
        { "bridge", ISLAND_LOCATION_BRIDGE },
        { "levhub", ISLAND_LOCATION_LEVEL_HUB },
        { "levshld", ISLAND_LOCATION_LEVEL_SHIELD },
        { "feature", ISLAND_LOCATION_FEATURE },
        { "feattrig", ISLAND_LOCATION_FEATURE_TRIGGER }
    };
    size_t i;

    for (i = 0; i < sizeof(cases) / sizeof(cases[0]); ++i) {
        assert(island_location_kind(cases[i].tag) == cases[i].kind);
    }
    assert(island_location_kind("unknown") == ISLAND_LOCATION_UNKNOWN);
    assert(island_location_kind(NULL) == ISLAND_LOCATION_UNKNOWN);
}

static void test_tone_location_with_zero_special_value(void)
{
    static const unsigned char fixture[] =
        "NUM_LOCATIONS 8\r\n"
        "; original ISLAND00.TXT has tone records with special_value 0\r\n"
        "0 278 229 tone 0\r\n"
        "1 209 154 smpad 0\r\n"
        "2 912 160 bridge 4\r\n"
        "3 100 100 pad 0\r\n"
        "4 200 100 feattrig 0\r\n"
        "5 250 100 tone 1\r\n"
        "6 300 100 mdpad 0\r\n"
        "7 350 100 lgpad 0\r\n";
    IslandData data;
    char error[128];

    assert(island_data_load(fixture, sizeof(fixture) - 1, &data,
                            error, sizeof(error)));
    assert(data.location_count == 8);
    assert(data.locations[0].kind == ISLAND_LOCATION_TONE);
    assert(data.locations[0].kind != ISLAND_LOCATION_PAD_SMALL);
    assert(data.locations[0].special_value == 0);
    assert(data.locations[0].renderer_class == 1);
    assert(data.locations[0].renderer_subtype == 0);
    assert(data.locations[0].renderer_variant == 0);
    assert(strcmp(data.locations[0].type, "tone") == 0);
    assert(data.locations[2].kind == ISLAND_LOCATION_BRIDGE);
    assert(data.locations[2].renderer_class == 2);
    assert(data.locations[3].renderer_class == 0);
    assert(data.locations[3].renderer_variant == 0);
    assert(data.locations[4].renderer_class == 3);
    assert(data.locations[4].renderer_variant == 3);
    assert(data.locations[5].kind == ISLAND_LOCATION_TONE);
    assert(data.locations[5].special_value == 1);
    assert(data.locations[5].renderer_class == 1);
    assert(data.locations[5].renderer_variant == 0);
    assert(data.locations[1].renderer_subtype == 0);
    assert(data.locations[6].renderer_subtype == 1);
    assert(data.locations[7].renderer_subtype == 2);
}

static void test_unknown_type_is_preserved(void)
{
    static const unsigned char fixture[] =
        "NUM_LOCATIONS 1\n"
        "0 10 20 not_a_location 0\n";
    IslandData data;
    char error[128];

    assert(island_data_load(fixture, sizeof(fixture) - 1, &data,
                            error, sizeof(error)));
    assert(data.location_count == 1);
    assert(data.locations[0].kind == ISLAND_LOCATION_UNKNOWN);
    assert(strcmp(data.locations[0].type, "not_a_location") == 0);
    assert(data.locations[0].renderer_class == 0);
}

static void test_count_mismatch_is_rejected(void)
{
    static const unsigned char fixture[] =
        "NUM_LOCATIONS 2\n"
        "0 10 20 tone 0\n";
    IslandData data;
    char error[128];

    assert(!island_data_load(fixture, sizeof(fixture) - 1, &data,
                             error, sizeof(error)));
    assert(strstr(error, "location count does not match") != NULL);
}

int main(void)
{
    test_original_type_tags();
    test_tone_location_with_zero_special_value();
    test_unknown_type_is_preserved();
    test_count_mismatch_is_rejected();
    (void)puts("island data unit tests passed");
    return 0;
}
