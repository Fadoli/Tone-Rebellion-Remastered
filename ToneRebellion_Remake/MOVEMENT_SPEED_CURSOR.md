# Cursor and tick cadence

## Interaction cursor lifecycle

The cursor is a 17-slot state machine, not a one-off glyph image. `FUN_0041c181`
loads slots 0..16 from the resource IDs in `DAT_0049c950`; `FUN_0042dd47`
chooses the requested slot when its handle exists, otherwise falls back to slot
0, then calls `SetCursor`. `FUN_0043530b` assigns slot 9 for mode 1, slots
3/5/15 for modes `0x10`/`0x12`/`0x13`, and slot 13 or 11 for mode `0x11`
depending on whether an item or glyph is armed. Evidence:
`ev_c726a273b363fd7769f6b98bb6a0fb90f454b1cc5c2da0d264a1175c0aaaca75`,
`ev_f390428e4e2b22a6ce9a9f425844123e7a120340e823e19cc9c45619ebb90e9a`,
`ev_b65156eb13978511b7f06cdb3fee86e7c2c4a37bf3cac67ad0f0badb2f999a68`.

`FUN_0042fa0f` messages `0x42` and `0x43` arm an inventory item or glyph and
enter mode `0x11`; message `0x40` commits a target, restores slot 0 and clears
both armed IDs. Evidence: `ev_a8230350584e54954217dfeda123b6cf8d9dc6ca7211fff2385661c22cdab6ba`
and the `FUN_0042fa0f` dossier in `functions/0012_batch_0008.md`.

Live REA inspection of the shipped `C:\Program Files\Tone\FLOAT.EXE` confirmed
the table bytes at `0x49c950` (Evidence
`ev_870a794f1785a5ab6a4e135cf0a026a2068b803ccd42730199dce261f9631b74`):
slots 0..16 map to resource IDs `84, 75, 76, 77, 78, 79, 7a, 7b, 7c, 7d,
7e, 7f, 74, 80, 81, 82, 83` (hex). The remake now loads the complete table,
uses slot 11 while an inventory item or glyph is armed, and returns to source
slot 0 immediately after the target click or a screen change. `WM_SETCURSOR`
also reapplies the state so Windows cannot leave a stale custom cursor visible.
The other source modes (slots 3, 5, 9, 13, 15 and data-driven 0x15..0x1c) are
not yet raised by remake actions, so they remain available but inactive.
