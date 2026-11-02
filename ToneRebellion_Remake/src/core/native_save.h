#ifndef TONE_REBELLION_NATIVE_SAVE_H
#define TONE_REBELLION_NATIVE_SAVE_H

#include "game_session_types.h"

#include <stddef.h>
#include <stdint.h>

/*
 * Reader for the original game's NN.SAV files (FUN_0045749a / FUN_004576c7).
 * Layout and evidence: behavior/save-format.md. The file is a raw dump of the
 * 0x80-byte header, three dwords, then the four engine streams. Only the
 * parts the remake models are applied; everything else keeps the value the
 * fresh session for the same world and tribe already has.
 */

enum { NATIVE_SAVE_MAX_ISLANDS = 16 };

typedef struct NativeSave {
    const uint8_t *data;
    size_t size;
    uint32_t mode;       /* DAT_0062d174 */
    uint32_t tribe;      /* DAT_0049f538 */
    uint32_t value_8c;    /* DAT_0049f53c: 0..14 across samples, not a difficulty */
    uint16_t island_count;
    uint16_t site_count[NATIVE_SAVE_MAX_ISLANDS];
    size_t stream2_offset;  /* 15 world scalars, then the world tables */
    size_t island_offset[NATIVE_SAVE_MAX_ISLANDS]; /* island scalars */
    size_t site_offset[NATIVE_SAVE_MAX_ISLANDS]; /* first 0x60-byte record */
    size_t player_offset;  /* 4 x 0x14a0 records */
    size_t global_offset;  /* 0x1614-byte block */
    size_t floater_offset; /* 256 x 0x4c records */
    /* Stream 4 (FUN_0046ea1c -> FUN_004393ab per IsleClipBd): 3 objects x
       {3 row indices (-1 empty), active group}; 0 when the file ends
       before it. */
    size_t clipboard_offset;
} NativeSave;

/* Validates the header and the stream framing against `size`. The pointers in
   `out` borrow `data`, which must outlive it. */
int native_save_parse(const uint8_t *data, size_t size, NativeSave *out,
                      char *error, size_t error_capacity);

/* Index of the world whose island count matches the save, or -1. */
int native_save_find_world(const NativeSave *save, const WorldMap *worlds);

/* Overlays the save onto a session freshly built for the same world and
   tribe. Sites (0x60-byte records) and floaters (0x4c-byte records) are
   restored; `session` is left unchanged on failure. */
int native_save_apply(const NativeSave *save, const FloaterCatalog *floaters,
                      GameSession *session, char *error, size_t error_capacity);

/* Test fixtures: appends one idle floater built like a save record (owner 4
   = Leviathan, catalog stats for `subtype`, no building link). Returns its
   index, or -1. */
int native_save_add_fixture_floater(GameSession *session,
                                    const FloaterCatalog *floaters,
                                    int owner, unsigned int subtype,
                                    uint8_t island, uint16_t x, uint16_t y,
                                    uint8_t level, int16_t charge);

#endif
