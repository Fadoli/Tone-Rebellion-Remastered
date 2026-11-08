#include "remake_text.h"

#include <string.h>

enum { REMAKE_TEXT_CAPACITY = 128 };

static const char *const g_source[REMAKE_TEXT_COUNT][REMAKE_LANG_COUNT] = {
#define X(id, fr, en, de, it, es) {fr, en, de, it, es},
#include "remake_text.def"
#undef X
};

/* Converted once per language on first use. */
static char g_converted[REMAKE_LANG_COUNT][REMAKE_TEXT_COUNT][REMAKE_TEXT_CAPACITY];
static unsigned char g_ready[REMAKE_LANG_COUNT];
static int g_language = REMAKE_LANG_FR;

void remake_text_set_language(int language)
{
    g_language = language >= 0 && language < REMAKE_LANG_COUNT ? language : REMAKE_LANG_FR;
}

int remake_text_language(void)
{
    return g_language;
}

const char *remake_text_in(int language, RemakeTextId id)
{
    int i;
    if (language < 0 || language >= REMAKE_LANG_COUNT) language = REMAKE_LANG_FR;
    if ((unsigned)id >= REMAKE_TEXT_COUNT) return "";
    if (!g_ready[language]) {
        for (i = 0; i < REMAKE_TEXT_COUNT; ++i)
            (void)remake_lang_to_cp437(g_source[i][language], g_converted[language][i],
                                       REMAKE_TEXT_CAPACITY);
        g_ready[language] = 1;
    }
    return g_converted[language][id];
}

const char *remake_text(RemakeTextId id)
{
    return remake_text_in(g_language, id);
}

const char *remake_text_utf8(RemakeTextId id)
{
    return (unsigned)id < REMAKE_TEXT_COUNT ? g_source[id][g_language] : "";
}
