# Changelog

Player-facing changes of the Tone Rebellion remake, newest first. Each release is a `v*` tag (see [Releases](README.md#releases)); its GitHub release text is the matching section below. Behaviour that knowingly differs from `FLOAT.EXE` is detailed in [differences from the original](docs/differences-from-original.md).

## 0.2.1 - unreleased

### Added

- Network games: a "Shared glyphs" host option, on by default. Every player's tribe gets the bonuses (strength, hit points, speed, range, spell cost, upkeep) of all the glyphs the players hold together; each glyph still belongs to the tribe that earned it for the Glyph panel, the glyph bearers and the seals. The host switches it by clicking the "Shared glyphs" line under the player list on the New Game screen; the other players see its state. Reloading a network save in a network game uses the lobby's setting; loaded in solo, the save drops the sharing. Tribes start allied, as before. Every player needs this version (lobby protocol 3).

### Fixed

- Selecting a task in the Tasks list highlights its workers: yellow on the minimap and highlighted in the island view, as in the original.
- Destroying or moving a Tone nebuliser drops every player's UpgSpread entry on it, as the original does; a stale entry could count a later Build Tone delivery to that pad toward a shared link.
- Spells checked one by one against the original:
  - Repair cast on open ground heals up to 2 + 2 x level of your damaged workers.
  - Spiritual Awakening raises the school's units' hit points (up to twice their maximum); it raised their charge.
  - Building Enchantment, Silent Shield, Pool Guardian, Courage of the Brave, Realm Shift and Ethnic Memory are refused, with nothing spent, on a site that is already under such a spell or of the wrong kind (Silent Shield: an empty pad; Pool Guardian: a Tone pool).
  - Sacrifice and Qi Burst protect their wizard from the moment they are cast.
  - Stellar Disc cast on a site it cannot affect plays and ends normally instead of keeping the wizard busy for 20 seconds.
- Courage of the Brave, Realm Shift, Spiritual Awakening, Endurance and Dojo Healing act on the school you target, as in the original, instead of the wizard's own school.
- Tone Pool Release animates as in the original: its opening frames play once, its flight loops its own animation (frames 5 to 14, never shown before), then it bursts on the pool. It used to loop the opening frames all the way.
- Units coming back to their school to recharge no longer all level up at once: a unit levels up only with enough experience and a free place at the next level for the school's tier; otherwise it is just recharged and healed. The original promoted every unit recharging at that moment.
- Pointing at a spell button of a wizard school shows the spell's cost left of the spell grid, as two Tone piles (Magic above, Crystal below) that grow with the cost, as in the original; the Magic pile includes glyph Lod's discount.
- The unit panel's "Puissance" row shows the unit's real strength, which grows by 2 per level (plus the school glyph and Courage of the Brave), as in the original. It showed the base value of the unit type, so a levelled-up unit looked unchanged.
- Silent Shield (on an empty building pad) and Pool Guardian (on a Tone pool) show their shimmer over the protected site while they last; the protection worked but was invisible.
- The Hall keeps showing its resources (and their hover text) in the building panel, e.g. after crossing a bridge with the Hall selected; they only showed in the general panel.
- Reloading a network save: every tribe a player held in that game can be chosen again, even one that had not built anything yet. Before, the host could not start the reloaded game ("every player must choose a played tribe").
- New Game screen: the centre art changes the difficulty within 100 pixels and the world size out to 200 pixels, as in the original; the clickable zones were only 10 and 14 pixels wide.
- Widescreen: the start-up logo (The Logic Factory) is drawn centred instead of as a garbled, sheared image.

## 0.2.0 - 2026-11-11

### Added

- The web page is now in English and explains the project: what the remaster is, why your own copy of the game is needed, what it adds, the useful keys, how saves and privacy work, and where to get the Windows version.
- New game guide (`docs/game-guide.md`, published as `guide.html` beside the browser version): what each world unlocks and when, glyph bonuses, difficulty effects, and unit, spell and building stats.
- The website gains a What's new page (`changelog.html`, this file) and the guide; both share a site header (Play, Guide, What's new, Download, Source) and a contents sidebar.
- The website takes the look of the game's title screen: violet starfield, cyan-lit capitals and blue framed buttons, shared by all its pages.
- The guide explains combat step by step (strength, hit roll, damage, realms and the realm tide shown in the island's lower-left corner) with worked examples and, on the website, an interactive combat calculator.

### Changed

- The Tasks list shows its scroll arrows only when it is longer than its pane (the original always shows them).
- Clicking a building's linked unit that stands on another island opens that island on the unit.
- Clicking the building shown in the lower panel (Hall, soldier house, ...) centres the island view on it, opening its island first.
- The glitter of the final world-map animation follows the game ticks, not the screen refresh rate.
- Remake alerts sit at the top right of the screen instead of a third of the way down, out of the way of the play.

### Fixed

- A spell caster standing on another island than its target crosses the bridges first and casts on arrival, as in the original, instead of casting from afar; its spell is no longer dropped during the crossing.
- Widescreen island: the view no longer slides past the island's edge (broken drawing) when the explored part is narrow or near an end.
- A building's linked unit chosen from another island now shows as selected.
- Mystic site descriptions no longer repeat their title: `;` comment lines in `bldtxt.txt` are skipped, as the original text reader does.
- Hidden building and Hall buttons (orders, spells, training stock, move, on/off, upgrade, repair, Obtain, UpgSpread, Hall stock) no longer react to clicks, hover or shortcut keys in the panels or while the construction window covers them.
- A destroyed Leviathan building frees its pad or pool for every tribe at once: the site shows again and can be built on, instead of staying hidden until something else refreshed the island.
- A trained soldier with enough experience goes back to its building and levels up, as in the original. Before, the building waited for it forever: the soldier stood idle and the building trained no one else.
- Bridges open at the original pace: the bridge trigger's construction animation plays in full (40 ticks) before the opening, instead of being cut after 9.
- Wizards no longer attack enemies on their own: after each task they head back to their building, as in the original, even when the building guards its spot.
- The building panel opened from a unit, a bridge or the Tasks list now shows the building's description and its On/Off, Upgrade and Repair buttons, like the general panel (the original builds the same button list in both). Before, those buttons were missing there.
- During the end of a game (victory or defeat) the world map no longer lets you open an island, as in the original.
- The victory tune keeps playing when the end sequence returns to the world map, instead of being replaced by the menu music.
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

