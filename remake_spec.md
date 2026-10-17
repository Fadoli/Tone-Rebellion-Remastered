# Remake specification — first pass

## Goal

Turn static Ghidra observations and the local game data into verifiable requirements for a remake. Ghidra pseudocode is reconstructed output, not recovered source; automatic names, types, and fields remain provisional. Comments in the data files are useful format documentation, but are not independent proof of runtime behavior.

Keep game rules separate from platform APIs. The core uses portable C11. SDL3 was the planned platform API, but it is not installed in this environment. To keep the menu runnable without downloading dependencies, the initial Windows adapter currently uses built-in Win32/GDI; keep it isolated from `core/` so it can be replaced with SDL3. Decode legacy shapes and palettes into core-owned pixel/animation data before handing them to a renderer. Inventory the asset encodings before fixing texture formats or the final rendering pipeline.

### SDL3 boundary

SDL3 offers a C API with a 2D renderer and event queue. The original interface references a 640×480 client area in `windows.txt`; use 640×480 logical coordinates with integer scaling/letterboxing as the initial compatibility target. The adapter should translate SDL events into `GameEvent` values and keep all SDL types out of `core/`.

SDL3 remains a possible cross-platform adapter after its SDK is available. Current GDI drawing and Win32 event translation live under `ToneRebellion_Remake/src/platform/win32/`; the portable core does not include Windows headers.

## Evidence and provenance

| Topic | Observation | Source |
|---|---|---|
| Target identity | `FLOAT.EXE`, SHA-256 `bb229d7f09c88caf4dc1825c00b957961c22c201cf1a8dd8139bf6f4599ff28c`, PE x86, Ghidra 12.1.4 | `README.md`, REA manifest |
| Data corpus | All 483 members from the two COB archives match the local corpus by name, size, and SHA-256 | `cob_archives.md`, `archive_index.jsonl` |
| World tables | `FUN_004642a3` loads `pad.txt`, `floater.txt`, `spells.txt`, then `data\\worldpos.txt` | `functions/0017_batch_0013.md`, Evidence `ev_561df3c3edee5a21c16764f7b95d5fa1e14e3a19d3ca83157c30bd51568c31c9` |
| World creation | `FUN_004637fc` accepts a world-size index and difficulty, validates them, and initializes associated state | `functions/0017_batch_0013.md`, Evidence `ev_96a46390b086f06a56b3c395f6e1a9de7ba2c2a1c30396c7ca72c63944a1039e` |
| Start-location setup | `FUN_004637fc` calls `FUN_0046466f` and `FUN_00464b9e`; the former iterates four slots, assigns a starting location and calls a helper four times for each slot | `functions/0017_batch_0013.md`, Evidence `ev_ac313cb8cc73f9c102676395cd14cb97b5b1f9355d074df1e6656ce028d2d36f` |
| Start balancing | `FUN_00464b9e` scans location arrays and makes additional assignments using a mode bit and random-choice helper | `functions/0017_batch_0013.md`, Evidence `ev_af395cb5dc0ed1efd405d0c4880d5843648c434a49f9d811e53dccc4b1268377` |
| New-game controls | Local `windows.txt` defines `WORLDSIZE`, `DIFFICULTY`, and `TRIBE0..3` controls with `SENDMESSAGE` IDs 53, 55, and 60..63 to `MASTER`; `FUN_0046cd22` builds the window hierarchy from its data records | Corpus `windows.txt`; parser function dossier in `functions/0018_batch_0014.md` |
| Periodic service | `FUN_00413e8a` increments a counter, processes queues/callbacks, and calls helpers whose roles still need resolution | `functions/0009_batch_0005.md`, Evidence `ev_f39fecaa50c8d1e93f75d9965a68335c0693806c5b4f23f578af0ea1c87eba72` |
| Update path | `FUN_00466ce2` iterates bounded collections, calls helpers, decrements counters, advances two bounded coordinates, and increments a tick-like value | `functions/0017_batch_0013.md`, Evidence `ev_b51f2311ff9bd9ad209f0663ea00bfe330e7ff0eff117e8a273292d3112a4e0e` |

### Remake implementation progress

The C11 prototype has a read-only COB directory API in `ToneRebellion_Remake/src/data/cob_archive.*`: it validates the 32-bit member count, 50-byte names, offset table, increasing member ranges, and can copy a member to caller-owned memory. `remake_inspect_cob` lists a container. The world table parser accepts those member bytes directly. The Windows `remake_menu` has title, setup, orbital map, and an initial island view. Setup input changes world size, difficulty, and tribe; Begin opens the orbital map. Enter on the map opens the selected island, or the selected tribe's homeworld if none is selected. The island view loads the corresponding original panorama, palette, HZT bytes, and ordered location table from `TONE01.COB`; arrow keys and the mouse wheel scroll horizontally, and clicking a site selects its original location record. The colored markers and inspection footer are remake-only scaffolding. The HZT palette transform, original site sprites, construction, unit actions, and simulation are not implemented. The 640×480 positions follow local `windows.txt`; `FUN_00448e5a` confirms world-size messages cycle 0..2 and difficulty messages cycle 0..4. Tribe message consumers remain unresolved. This C is newly written from observed formats and Ghidra evidence, not recovered source. The latest GUI build opens Tarzus and supports location selection; remake-only captures are in `ToneRebellion_Remake/build/island_view/`.

Recheck the target hash before further analysis. Never modify or execute the original binary or COB archives. Read game data from `C:\git\ToneRebellion_Raw\original_content`; do not use GitHub.

## Minimum data model

The schemas below combine the Ghidra parser and local data. Fields named only by comments are identified as the data-file documentation, not as recovered binary variable names.

### Worlds and islands

`FUN_004642a3` loads `pad.txt`, `floater.txt`, and `spells.txt`, then parses `data\\worldpos.txt`. Ghidra enforces at most 3 world definitions and at most 16 islands in each. Each island row is parsed with `%d %d %d %d`; the first value is converted from degrees to radians and the four values are written into global tables. Index pairs follow as links; a `-1` row ends that world’s link list.

The local `worldpos.txt` defines exactly three sizes with 7, 11, and 15 islands, and respectively 8, 14, and 22 bridge pairs. Its comments label the island columns angle, range, z, and shape ID, and describe the pairs as bridges indexed by island order. The parser’s bounds and table writes are consistent with those comments. Preserve explicit links; do not derive bridges from geometric proximity.

### Object and unit tables

- **`pad.txt`**: `FUN_0046303b` reads up to 101 rows using `%d %d %d,%d,%d %d %d %d %s %s %s`. It writes costs, hit points, range extension, tribe IDs, shape, and text values. The parser accepts at least 10 conversions though the format has 11, so the last field may be optional. File comments label the columns as size, build cost, three movement costs, maintenance, hit points, range, tribe, item/shape ID, and text ID. Some constants and the mapping from rows to `PIT_*` classes remain to be established.
- **`floater.txt`**: `FUN_004633a7` expects exactly 7 conversions per row and fills a 45-entry table. The file header labels them draw ID, attack range, realm, hit points, maximum attack points, attack strength, and speed. Enum values and units are not fully established.
- **`fltinf.txt` and `shapeinf.txt`**: `FUN_00454d1f` reads `item` blocks with properties such as `body`, `legs`, `base`, `hover`, `pickup`, `carry`, `attack`, `atteff`, `graspxy`, and `attxy`. `shapeinf.txt` provides frame ranges and offsets by shape. Its comments link some indices to `FloaterClass`, `ASEG`, and `OFFSET` constants; the exact loader/call-site for `shapeinf.txt` is still unresolved.
- **`spells.txt`**: `FUN_00463563` loads at most 32 entries. For each entry it reads a title, three following lines parsed as `%s %d`, and description lines until an `END` prefix; the description is stored in the shared text table. The local examples use `Level`, `MagCost`, and `CryCost`. The observed parser does not validate those labels before taking the numeric value.
- **`bldinf.txt` and `effects.txt`**: initialization call sites link these files to their parsers as recorded in `data_catalog.md`. They contain building-animation records and effect records, but are outside the first vertical slice.

## Proposed target architecture

```text
src/
  core/       game data, world, units, deterministic rules, saves
  data/       COB reader and parsers for local text formats
  platform/   time, input, window, file, and audio interfaces
  render/     shape/palette adaptation to the selected graphics API
  app/        screens, navigation, and system composition
```

Possible C-facing boundary (a proposal, not an ABI recovered from the binary):

```c
typedef struct Game Game;

Game *game_create(const GameConfig *config, const GameServices *services);
void game_destroy(Game *game);
void game_handle_event(Game *game, const GameEvent *event);
void game_update(Game *game, uint32_t elapsed_ms);
void game_render(const Game *game, GameRenderer *renderer);
```

The core should not directly depend on Win32, DirectDraw, DirectSound, or Ghidra-reconstructed method pointers. Validate legacy data while loading it into modern structures, while preserving original IDs and table order.

## First vertical slice

### Scope

Show a new-game/world selection view backed by the local data, then enter the selected island panorama: load all three sizes, build the islands and explicit bridge links for the selected size, and expose world-size, difficulty, and four tribe controls. `windows.txt` supplies the control names/message IDs; `FUN_004637fc` confirms that world-size and difficulty values enter game-state initialization. The handlers that map message IDs to those values remain to be traced, so the prototype must not assume that numeric IDs match world array indices without confirmation.

### Acceptance criteria

1. Load all three definitions and enforce the observed limits of 3 worlds and 16 islands; the shipped data has `(7, 8)`, `(11, 14)`, and `(15, 22)` island/bridge counts.
2. Preserve each island’s angle, range, z, and shape ID, and preserve every link pair exactly as read.
3. Display the selected size and all islands/links; use temporary shapes until the original asset renderer is understood.
4. Let mouse/keyboard input change selection through platform-independent events; keep the historical `SENDMESSAGE` codes in a translation table until their handler mapping is proven.
5. Check record counts and fields against the local corpus; malformed inputs must return explicit load errors.
6. Load the selected `ISLANDnn.SHP` panorama and palette, preserve its `ISLANDnn.TXT` site IDs/coordinates, and allow horizontal scrolling and site selection without modifying the source archives.

This validates data loading, the game model, input, and rendering before implementing the full simulation. It does not claim the original menu is limited to this view.

## Open questions before a faithful simulation port

- The meanings of many global tables and offsets are not yet reconstructed as types.
- `FUN_00413e8a` appears to combine timing, queue processing, and callbacks. Resolve indirect targets and execution order before writing an equivalent scheduler.
- `FUN_00466ce2` performs periodic work, but its pseudocode does not establish which operations are game rules, animation, or instrumentation.
- `FUN_0046466f` initializes four slots and places four entities through helpers, while `FUN_00464b9e` changes assignments by mode. Recovered fields do not establish whether each slot is a player/tribe, or what entity types and placement constraints those helpers implement.
- Trace the consumers of `pad`, `floater`, and `spells` before fixing public core structures.
- Locate save/load paths and screen transitions needed to resume a game.
- No original runtime behavior has been measured. Until an independent visual or behavioral reference is available, comparison is limited to static evidence and local data.

## Next analysis steps

1. Produce exact schemas and parser checks for `worldpos.txt`, `pad.txt`, `floater.txt`, and `spells.txt`, retaining original values and record counts.
2. Trace callers and consumers of the global tables, particularly `FUN_0046466f`, `FUN_00464b9e`, `FUN_004637fc`, and the helper that creates starting entities.
3. Identify the class/instance that owns the state passed in `ECX`, array bounds, and key field meanings from read/write cross references.
4. Resolve `SENDMESSAGE` codes 53, 55, and 60..63 through the window-manager/master handlers and map them to the arguments of `FUN_004637fc`.
5. Inventory `.SHP`, `.PAL`, `.GIF`, and `.WAV` encodings and implement the SDL3 adapter around the resulting decoded asset model.
