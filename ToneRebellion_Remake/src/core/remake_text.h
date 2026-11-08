#ifndef TONE_REMAKE_TEXT_H
#define TONE_REMAKE_TEXT_H

#include "remake_lang.h"

/* Identifiers of the remake's own texts (remake_text.def). */
typedef enum RemakeTextId {
#define X(id, fr, en, de, it, es) id,
#include "remake_text.def"
#undef X
    REMAKE_TEXT_COUNT
} RemakeTextId;

/* Chooses the language of remake_text(); out-of-range values mean French. */
void remake_text_set_language(int language);
int remake_text_language(void);
/* The text in the current language, in the fonts' code page (CP437).
   The pointer stays valid until the next language change. */
const char *remake_text(RemakeTextId id);
/* The same text in a given language. */
const char *remake_text_in(int language, RemakeTextId id);
/* The text in the current language as written (UTF-8), for the window
   title and system dialogs, which are not drawn with the game fonts. */
const char *remake_text_utf8(RemakeTextId id);

#endif
