#ifndef TONE_REMAKE_LANG_H
#define TONE_REMAKE_LANG_H

#include <stddef.h>

/* Languages of the remake's own texts (options panel, multiplayer screens,
   remake buttons, notices). The original game's texts come from its data
   files and are not translated. */
typedef enum RemakeLanguage {
    REMAKE_LANG_FR,
    REMAKE_LANG_EN,
    REMAKE_LANG_DE,
    REMAKE_LANG_IT,
    REMAKE_LANG_ES,
    REMAKE_LANG_COUNT
} RemakeLanguage;

/* The language's own name ("Français", "English", ...), in CP437. */
const char *remake_lang_name(int language);
/* Two-letter code ("fr", "en", ...). */
const char *remake_lang_code(int language);
/* Language for an ISO 639 code such as "de" or "de_CH"; -1 if none. */
int remake_lang_from_code(const char *code);

/* UTF-8 to the game fonts' code page (CP437: the accented letters at
   0x80..0xA8 and 0xE1). Characters the fonts lack become '?'. Always
   terminates `out`; returns the length written. */
size_t remake_lang_to_cp437(const char *utf8, char *out, size_t capacity);

#endif
