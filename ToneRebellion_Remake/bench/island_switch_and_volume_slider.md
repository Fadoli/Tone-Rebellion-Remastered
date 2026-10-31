# Island switch and volume slider lag

## Findings

- `load_island_surface` reloaded every island sheet on each switch (~120 COB
  reads, SHP decodes, 32-bit DIB conversions and horizontal mirrors), although
  most of them do not depend on the island.
- The 15 `ISLANDnn.PAL` files differ only in entries 224..254; entries 0..223
  and 255 are identical.
- A probe over `TONE01.COB` (local ISO copy) decoding every `.shp`: 92 of 309
  sheets use an opaque pixel in 224..254. The others (floater bodies/legs,
  Leviathan sheets, controls, most effects) convert to the same bitmaps on
  every island. Island-specific users include `islandNN.shp`, `iNN-feat.shp`,
  `lilmap.shp`, `solidpad.shp`, `v-sht2fx.shp`, `spl21.shp`.
- The slider wrote `saves\audio.cfg` (plus `CreateDirectory`) and sent a
  synchronous MCI `setaudio` on every `WM_MOUSEMOVE`, even when the value did
  not change.

## Changes

- `load_sprite_sheet` / `mirror_sprite_sheet_horizontally` share loaded
  sheets by COB member and the palette colors their pixels use, with a
  reference count released by `free_sprite_sheet`. The island loader builds
  replacements before releasing old sheets, so the previous island's sheets
  are reused.
- The slider writes `audio.cfg` once on release. A first version still
  repainted on each changed move: a queued `WM_PAINT` outranks `WM_TIMER`, so
  the game frame clock stalled during the drag (same cause as the IWLilMap
  drag). The drag now relies on the per-frame 20 Hz repaint, and the music
  volume is sent to MCI at most once per frame (`slide_panel_tick`).

No timing benchmark was run (needs interactive island switching).
