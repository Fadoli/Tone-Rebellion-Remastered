#include "remake_lang.h"

#include <string.h>

static const char *const g_lang_codes[REMAKE_LANG_COUNT] = {"fr", "en", "de", "it", "es"};
/* CP437: \x87 = ç, \xA4 = ñ. */
static const char *const g_lang_names[REMAKE_LANG_COUNT] = {
    "Fran\x87" "ais", "English", "Deutsch", "Italiano", "Espa\xA4" "ol"};

const char *remake_lang_name(int language)
{
    return language >= 0 && language < REMAKE_LANG_COUNT ? g_lang_names[language] : "?";
}

const char *remake_lang_code(int language)
{
    return language >= 0 && language < REMAKE_LANG_COUNT ? g_lang_codes[language] : "";
}

int remake_lang_from_code(const char *code)
{
    int language;
    if (code == NULL) return -1;
    for (language = 0; language < REMAKE_LANG_COUNT; ++language) {
        const char *own = g_lang_codes[language];
        if ((code[0] | 0x20) == own[0] && (code[1] | 0x20) == own[1] &&
            (code[2] == '\0' || code[2] == '_' || code[2] == '-'))
            return language;
    }
    return -1;
}

/* Unicode code point -> CP437 byte the game fonts draw, or 0. */
static unsigned char cp437_of(unsigned long point)
{
    static const struct { unsigned short point; unsigned char byte; } map[] = {
        {0x00C7, 0x80}, {0x00FC, 0x81}, {0x00E9, 0x82}, {0x00E2, 0x83}, {0x00E4, 0x84},
        {0x00E0, 0x85}, {0x00E7, 0x87}, {0x00EA, 0x88}, {0x00EB, 0x89}, {0x00E8, 0x8A},
        {0x00EF, 0x8B}, {0x00EE, 0x8C}, {0x00EC, 0x8D}, {0x00C4, 0x8E}, {0x00C9, 0x90},
        {0x00F4, 0x93}, {0x00F6, 0x94}, {0x00F2, 0x95}, {0x00FB, 0x96}, {0x00F9, 0x97},
        {0x00FF, 0x98}, {0x00D6, 0x99}, {0x00DC, 0x9A}, {0x00E1, 0xA0}, {0x00ED, 0xA1},
        {0x00F3, 0xA2}, {0x00FA, 0xA3}, {0x00F1, 0xA4}, {0x00D1, 0xA5}, {0x00BF, 0xA8},
        {0x00DF, 0xE1}};
    size_t i;
    if (point >= 0x20 && point < 0x7F) return (unsigned char)point;
    for (i = 0; i < sizeof(map) / sizeof(map[0]); ++i)
        if (map[i].point == point) return map[i].byte;
    /* Capitals the fonts lack: their plain letter. */
    if (point == 0x00C0 || point == 0x00C1 || point == 0x00C2) return 'A';
    if (point == 0x00C8 || point == 0x00CA) return 'E';
    if (point == 0x00CC || point == 0x00CD || point == 0x00CE) return 'I';
    if (point == 0x00D2 || point == 0x00D3 || point == 0x00D4) return 'O';
    if (point == 0x00D9 || point == 0x00DA || point == 0x00DB) return 'U';
    if (point == 0x00A1) return '!';
    if (point == 0x2019) return '\'';
    return 0;
}

size_t remake_lang_to_cp437(const char *utf8, char *out, size_t capacity)
{
    const unsigned char *in = (const unsigned char *)utf8;
    size_t used = 0;
    if (capacity == 0) return 0;
    while (in != NULL && *in != '\0' && used + 1U < capacity) {
        unsigned long point;
        int extra;
        unsigned char byte;
        if (*in < 0x80) {
            point = *in;
            extra = 0;
        } else if ((*in & 0xE0) == 0xC0) {
            point = *in & 0x1FUL;
            extra = 1;
        } else if ((*in & 0xF0) == 0xE0) {
            point = *in & 0x0FUL;
            extra = 2;
        } else if ((*in & 0xF8) == 0xF0) {
            point = *in & 0x07UL;
            extra = 3;
        } else {
            point = 0xFFFDUL;
            extra = 0;
        }
        ++in;
        for (; extra > 0; --extra) {
            if ((*in & 0xC0) != 0x80) {
                point = 0xFFFDUL;
                break;
            }
            point = (point << 6) | (*in++ & 0x3FUL);
        }
        byte = point < 0x20 ? (unsigned char)point : cp437_of(point);
        out[used++] = (char)(byte != 0 ? byte : '?');
    }
    out[used] = '\0';
    return used;
}
