# Changelog

Player-facing changes of the Tone Rebellion remake, newest first. Each release is a `v*` tag (see [Releases](README.md#releases)); its GitHub release text is the matching section below. Behaviour that knowingly differs from `FLOAT.EXE` is detailed in [differences from the original](docs/differences-from-original.md).

## 0.1.4 - unreleased

### Changed

- The Tasks list shows its scroll arrows only when it is longer than its pane (the original always shows them).
- Clicking a building's linked unit that stands on another island opens that island on the unit.

### Fixed

- A spell caster standing on another island than its target crosses the bridges first and casts on arrival, as in the original, instead of casting from afar; its spell is no longer dropped during the crossing.
- Widescreen island: the view no longer slides past the island's edge (broken drawing) when the explored part is narrow or near an end.
- A building's linked unit chosen from another island now shows as selected.
- A destroyed Leviathan building frees its pad or pool for every tribe at once: the site shows again and can be built on, instead of staying hidden until something else refreshed the island.
- A trained soldier with enough experience goes back to its building and levels up, as in the original. Before, the building waited for it forever: the soldier stood idle and the building trained no one else.
- A unit held by a melee attacker answers it: its counter-attack now reaches the holder and strikes, instead of standing still until the holder stops.
- Tribe 0 Gazers' bullets use their own sheet (`PT2B` is `pt2ball.shp` in `shapes.txt`), with the right colours.
- Widescreen island: the alerts sit at the window's right edge and the island message line at its left edge, rather than in the middle.

## 0.1.3 - 2026-11-11

### Fixed

- Units no longer all bob up and down in step: each tribe unit gets its own hover phase, as every unit created by the original does. Games saved before this fix get the phases when loaded.

## 0.1.2 - 2026-11-09

### Added

- Widescreen island: the option "Island max. aspect ratio" (F2, Display) lets the island view grow past 4:3 up to 16:10, 16:9, 21:9 or no limit, following the window's shape. The lower panel and the other screens stay 640x480 and centred; the empty sides next to the panel are framed. Off (4:3) by default.
- The keyboard `Pause` key pauses and resumes the game on the island and the world map (network games: the shared pause).
- Intro movie: an INTRO button and the `I` key on the title play `INTRO.AVI` (desktop only); a click or a key skips it, and the background music stops while it plays.
- Remake texts (options, multiplayer, buttons, alerts, dialogs) in French, English, German, Italian and Spanish, following the system language or the option.
- Multiplayer: "Partie en ligne" title button with player name, "Créer partie" and "Entrer partie"; the addresses joined before are kept in `saves\servers.cfg`.
- Remake-only buttons drawn in the style of the title buttons.
- Overlapping sound effects (default on): a repeated sound plays on its own voice instead of restarting; the option restores the original restart.
- The F2 options are grouped in collapsible sections (Display, Sound, Game, Controls, Saves) with a scrollbar.
- `.img` CD images (raw 2352-byte sectors) are accepted beside `.iso`; the web setup also takes a dropped `.iso` or `.img`.

### Changed

- Developer shortcuts (`Ctrl+F6..F9`, `F11`, the e2e keys) exist only in debug builds.
- Remake saves stay loadable when fields are renamed, change width or change meaning.
- Building upgrades and UpgSpread wait until a building has finished appearing, upgrading or dying (remake choice); a completed UpgSpread refreshes visibility and upkeep at once.

### Fixed

- A repeated sound effect was dropped instead of restarting.
- BC_Upgrade now hides at a building's maximum tier and animates while an upgrade is requested.
- A warrior turned back into a worker when its staff building is destroyed gets the worker's stats again.
- Leviathan defences: tower bullets play their own sounds, direct hits always show their impact, and island floaters bob as in the original.

## 0.1.1 - 2026-11-06

### Changed

- Alerts, smooth scrolling and keyboard shortcuts are off by default; the remake options turn them on.
- The random island captions (`CRYPTIC0..20`) are off by default; the Leviathan bond alert is gone.
- Web: the canvas fills the page at the screen's pixel density.
- Documentation reorganised.

## 0.1.0 - 2026-11-06

First release: Windows and browser builds.

