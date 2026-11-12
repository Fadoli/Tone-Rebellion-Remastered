# Tone Rebellion game guide

What unlocks when, what each glyph does, what the difficulty changes, and the stats of every unit and defence. Built from the game's own data files (`floater.txt`, `pad.txt`, `spells.txt`, `worldpos.txt`, …) and from static analysis of `FLOAT.EXE`, as ported by the remake. Nothing here was measured on the running original game.

Names are those of the French release (the only data set available here); English names are translations or come from comments in the data files. Times are in game ticks: 20 ticks = 1 second at normal speed.

## Contents

1. [Worlds](#worlds)
2. [What unlocks when](#what-unlocks-when)
3. [Glyphs](#glyphs)
4. [Difficulty](#difficulty)
5. [Tribe units](#tribe-units)
6. [Spells](#spells)
7. [Tribe buildings](#tribe-buildings)
8. [Leviathan creatures](#leviathan-creatures)
9. [Leviathan defences](#leviathan-defences)
10. [Combat rules](#combat-rules)
11. [Sources and limits](#sources-and-limits)

## Worlds

The new-game screen offers three worlds ("map sizes"). The last island of each is the Leviathan's island.

| World | Islands | Islands to win back | Glyphs you can find |
|---|---|---|---|
| 0 – small | 7 | 6 | 6 (Tal … Tra) |
| 1 – medium | 11 | 10 | 10 (Tal … Mn) |
| 2 – large | 15 | 14 | all 14 |

**Islands reached** is the number that drives every unlock below: an island counts once one of your floaters has crossed to it (or you built the bridge that reaches it), and it keeps counting for the rest of the game, even if you lose everything there. Your starting island counts.

## What unlocks when

### Building

A small pad takes the four Tone buildings; the schools need a medium or large pad.

| Building | Pad | World 0 | World 1 | World 2 |
|---|---|---|---|---|
| Tone generator, Magic Tone maker, Crystal Tone maker, Tone nebuliser | small | always | always | always |
| Train 1 school (first warriors) | medium | 1 island | 1 island | 1 island |
| Train 2 school | medium | 2 islands | 2 islands | 2 islands |
| Train 3 school | medium | **never** | 8 islands | 8 islands |
| Spell school (wizards) | medium | 3 islands | 3 islands | 3 islands |

### Upgrading a school

The Upgrade button appears on a finished school once you have reached enough islands; the upgrade then needs 20 Build Tone delivered to it.

| School | Max tier | World 0: tier 1 / tier 2 | World 1 | World 2 |
|---|---|---|---|---|
| Train 1 | 2 | 4 / 6 islands | 4 / 7 | 4 / 7 |
| Train 2 | 2 | 5 / never | 5 / 9 | 5 / 9 |
| Train 3 | 1 | never | never | 11 / – |
| Spell school | 2 | never / never | 6 / never | 6 / 10 |

What a tier gives:

- **Unit level cap.** A unit's level can never exceed its school's tier, so tier 1 allows level 2 units ("Niveau 2" in game) and tier 2 allows level 3.
- **More places.** Train 1 and Train 2 keep 3 units at level 0, plus 2 at level 1 from tier 1, plus 1 at level 2 from tier 2 (Train 3 the same, stopping at tier 1). The spell school keeps 1 wizard per level.
- **Sturdier building.** Building HP = base HP + 5 per tier.
- **More spell storage.** A spell school holds 50 + 25 × tier Magic Tone.
- Moving the building costs (tier + 1) times its move cost.

### The Hall

The Hall grows on its own, in every world: tier 1 at 4 islands reached, tier 2 at 6. It never shrinks back. Its restock target is 150 + 50 × tier.

### What each world allows in the end

| | World 0 | World 1 | World 2 |
|---|---|---|---|
| Warrior schools | Train 1, Train 2 | Train 1–3 | Train 1–3 |
| Best warrior level | Train 1: 3, Train 2: 2 | Train 1: 3, Train 2: 3, Train 3: 1 | Train 1: 3, Train 2: 3, Train 3: 2 |
| Wizard spells | level 1 only | levels 1–2 | levels 1–3 |
| Glyph bonuses | Tal, Dre, Lon, Tuka, Dran, Tra | + Ahn, Phet, Lod, Mn | all |

## Glyphs

Each island except the Leviathan's holds two artefacts. Bring both to the island's two trigger sites (the ruins) and you earn that island's glyph. The glyph is numbered by the island's place in the world (first island = Tal), so a small world only ever offers the first six.

A glyph has two uses:

- **A permanent bonus** for your tribe, listed below.
- **Victory.** The Leviathan's island carries one seal per glyph. Late in the game some of your floaters become glyph bearers (more often the more glyphs you hold). Pick a glyph, target its seal: glyph *k* breaks seal *k*. Breaking every seal wins the game.

| # | Glyph | Permanent bonus |
|---|---|---|
| 0 | Tal | Train 1 units: +1 strength |
| 1 | Dre | Train 1 units: HP × 5/4 |
| 2 | Lon | Ranged units of a school: range × 5/4 |
| 3 | Tuka | Train 1 units: +1 speed |
| 4 | Dran | Workers: +1 HP |
| 5 | Tra | Train 2 units: +1 speed |
| 6 | Ahn | Train 2 units: +1 strength |
| 7 | Phet | Train 2 units: HP × 5/4 |
| 8 | Lod | Spells cost 1/3 less Magic Tone (Crystal cost unchanged) |
| 9 | Mn | Train 3 units: +1 speed |
| 10 | Nos | Train 3 units: +1 strength |
| 11 | Grem | Train 3 units: HP × 5/4 |
| 12 | Mef | no bonus found in the code |
| 13 | Vinya | Building upkeep −15 % |

**Network games (remake):** with the host's "Shared glyphs" option, on by default, every player's tribe gets the bonuses of all the glyphs the players hold together. Each glyph still belongs to the tribe that earned it for the seals. Tribes start allied, as in every game.

Glyphs never unlock buildings or spells. The design notes inside `bldtxt.txt` describe other bonuses; the shipped code does what this table says.

## Difficulty

Five levels, chosen on the new-game screen with the Leviathan picture. The game calls them by the Leviathan's mood:

| Level | Name (French release) | Meaning |
|---|---|---|
| 0 | Léviathan peureux | timid |
| 1 | Léviathan joueur | playful |
| 2 | Léviathan maussade | sullen |
| 3 | Léviathan agressif | aggressive |
| 4 | Léviathan destructeur | destructive |

What it changes (d = level 0–4):

| Area | Effect |
|---|---|
| Contamination | A contaminated Tone pool spawns after 1200 − 100 d ticks (60 s at level 0, 40 s at level 4). |
| Spawning | Leviathan buildings spawn sooner (threshold 10000 − 400 d); from level 2 they speed up further late in the game and as the Leviathan loses islands. |
| Leviathan buildings | Stronger kinds join the random pick: 6 kinds at level 0, 10 at level 1, all 12 from level 2. |
| Elite spawns | A new Leviathan creature can start at level 1 (×1.7 HP, +3 strength); the chance grows with d and with the island's place, halved below level 2. |
| Creature ranks | From level 2 only: Leviathan creatures gain rank over time (rank × strength / 22 extra power), faster at higher levels. |
| Garrisons | Each Leviathan island keeps more creatures and rebuilds them faster: island tier = min(island / 4, d), budget per site 2 × tier + 4. |
| Attack waves | Waves grow: (tier + 2 + d) / 2 creatures plus a random extra. |
| Realm advantage | The realm bonus in the hit roll grows: strength / 4 at level 0, / 2 at levels 1–2, × 2/3 at levels 3–4. It applies to both sides. |
| Your warriors | Need more experience to level up: from 25 → 75 (first level) and 100 → 200 (second) at level 0 → 4 for Train 1; see [Tribe units](#tribe-units). |
| Score | +50 per level. |

Difficulty does **not** change your starting Tone, buildings, units or costs.

## Tribe units

How to read the table:

- **Realm**: Physical, Supernatural, Ethereal or Natural (see [Combat rules](#combat-rules)).
- **Range**: in pixels; melee units pin their target in place.
- **HP / Charge**: at levels 1 / 2 / 3. Each attack spends one charge; an empty unit fights like a worker until it recharges at its school (10 Crystal Tone).
- **Str**: strength, the base of hit chance and damage. A charged unit hits with Str + 2 × (level − 1).
- **Spd**: pixels per movement step.
- **Strike**: ticks from the start of an attack to the hit.

Training: a worker enters a school holding more than 9 Crystal Tone, pays 10 and trains for about 12.5 s. Workers are free; a new one appears when you have Tone to spare and room in your population.

Experience: +1 per damaging hit, +5 per spell cast. Level-up thresholds, from difficulty 0 to 4:

| School | to level 2 | to level 3 |
|---|---|---|
| Train 1 | 25 → 75 | 100 → 200 |
| Train 2 | 30 → 90 | 120 → 240 |
| Train 3 | 40 → 120 | – |
| Spell school | 25 → 75 | 100 → 200 |

### Tark (Protectors)

| Unit | Realm | Range | HP | Charge | Str | Spd | Strike |
|---|---|---|---|---|---|---|---|
| Worker | Physical | melee | 3 | 0 | 0 | 3 | 10 |
| Train 1 – Confrérie du Tentacule (Brotherhood of the Tentacle) | Physical | melee | 17 / 25 / 34 | 19 / 28 / 38 | 5 | 3 | 10 |
| Train 2 – Contemplatif (Gazers) | Supernatural | 145 | 14 / 21 / 28 | 17 / 25 / 34 | 4 | 3 | 12 |
| Train 3 – Confédération de l'Étoile (League of the Star) | Physical | 120 | 15 / 22 | 19 / 28 | 5 | 4 | 10 |
| Wizard – Société des Magiciens | Physical | melee | 16 / 24 / 32 | 10 / 15 / 20 | 3 | 3 | 12 |

### Zygon (Seekers)

| Unit | Realm | Range | HP | Charge | Str | Spd | Strike |
|---|---|---|---|---|---|---|---|
| Worker | Supernatural | melee | 3 | 0 | 0 | 3 | 12 |
| Train 1 – Clan de Sol | Supernatural | 160 | 13 / 19 / 26 | 13 / 19 / 26 | 5 | 4 | 12 |
| Train 2 – Voix de l'Esprit (Spirit Callers) | Ethereal | melee | 15 / 22 / 30 | 15 / 22 / 30 | 5 | 3 | 14 |
| Train 3 – Guilde de la Lumière (Light Shapers) | Supernatural | melee | 14 / 21 | 14 / 21 | 6 | 4 | 12 |
| Wizard – Sorcier du Firmament | Supernatural | melee | 14 / 21 / 28 | 10 / 15 / 20 | 2 | 4 | 12 |

### Céphéen (Mystics)

| Unit | Realm | Range | HP | Charge | Str | Spd | Strike |
|---|---|---|---|---|---|---|---|
| Worker | Ethereal | melee | 3 | 0 | 0 | 3 | 10 |
| Train 1 – Fée du requiem (Banshees) | Ethereal | melee | 14 / 21 / 28 | 14 / 21 / 28 | 5 | 4 | 16 |
| Train 2 – Prêtre de l'orage (Stormers) | Natural | 175 | 15 / 22 / 30 | 16 / 24 / 32 | 3 | 4 | 20 |
| Train 3 – Explorateur céleste (Astral Travellers) | Ethereal | 195 | 13 / 19 | 16 / 24 | 4 | 3 | 6 |
| Wizard – Ordre d'Arcania | Ethereal | melee | 15 / 22 / 30 | 10 / 15 / 20 | 2 | 4 | 20 |

### Dyla (Lifegivers)

| Unit | Realm | Range | HP | Charge | Str | Spd | Strike |
|---|---|---|---|---|---|---|---|
| Worker | Natural | melee | 3 | 0 | 0 | 3 | 12 |
| Train 1 – Sorcier Invocateur (Summoners) | Natural | 230 | 13 / 19 / 26 | 16 / 24 / 32 | 5 | 3 | 5 |
| Train 2 – Repaire de la Bête (Den of the Beast) | Physical | melee | 19 / 28 / 38 | 17 / 25 / 34 | 4 | 3 | 12 |
| Train 3 – Façonneur du Vent (Wind Shapers) | Natural | melee | 16 / 24 | 18 / 27 | 3 | 4 | 13 |
| Wizard – Druide Enchanteur | Natural | melee | 16 / 24 / 32 | 12 / 18 / 24 | 2 | 3 | 38 |

Glyph bonuses (Tal, Dre, Tuka, …) come on top of these numbers. A school that is destroyed turns its units back into workers.

## Spells

Each tribe's wizard knows eight spells. A level-2 spell needs a level-2 wizard (spell school tier 1), a level-3 spell a level-3 wizard (tier 2); two exceptions are marked ★ (castable at any level). Costs are Magic / Crystal Tone; glyph Lod cuts the Magic cost by a third.

| Spell | Level | Magic | Crystal | Tark | Zygon | Céphéen | Dyla | Effect |
|---|---|---|---|---|---|---|---|---|
| Guérison du Dojo (Dojo Healing) | 1 | 9 | 7 | | ✓ | | ✓ | heals the floaters of a school |
| Paralysie des germes parasites (Spore Paralysis) | 1 | 16 | 11 | | ✓ | ✓ | | stuns Leviathan spores around the wizard |
| Guérison (Healing) | 1 | 12 | 9 | | | | ✓ | heals your most wounded workers |
| Réparation (Repair) | 1 | 9 | 12 | | | | ✓ | restores a building to full HP; cast on open ground, heals up to 2 + 2 × level of your workers |
| Enchantement de bâtiment (Building Enchantment) | 1 | 10 | 9 | ✓ | | ✓ | | a wall of Tone shields a building from all damage |
| Bouclier silencieux (Silent Shield) | 1 | 12 | 7 | | | ✓ | | protects a Tone nodule from contamination |
| Gardien du bassin (Pool Guardian) | 1 | 14 | 10 | | | | ✓ | protects a Tone pool from contamination |
| Sacrifice | 1 | 11 | 17 | ✓ | | | | a destructive wave, at the cost of the wizard |
| Saisie à distance (Remote Grab) | 1 | 9 | 14 | | ✓ | | | fetches an artefact from any visible area |
| Disque stellaire (Stellar Disc) | 1 | 11 | 13 | ✓ | | | | destroys a building or a spore (not a spawning pond) |
| Pluie de météores (Meteor Shower) | 1 | 7 | 13 | ✓ | | | | rocks that destroy Leviathan creatures |
| Réveil spirituel (Spiritual Awakening) | 2 | 33 | 13 | ✓ | | | ✓ | multiplies a school's floaters' hit points by level + 1 (up to twice their maximum) |
| Courage des braves (Courage of the Brave) | 2 | 28 | 17 | ✓ | | ✓ | | a school's floaters gain strength and skill |
| Changement de royaume (Realm Shift) | 2 | 34 | 12 | | ✓ | | ✓ | moves a school's floaters to the next realm |
| Enchantement de tribu (Tribe Enchantment) | 2 | 36 | 17 | ✓ | ✓ | | | makes your workers invulnerable |
| Résistance (Endurance) | 2 | 22 | 19 | | ✓★ | | | a school's floaters fight without resting |
| Libération de bassin de Tone (Pool Release) | 2 | 27 | 17 | | | ✓ | ✓ | destroys a Leviathan spawning pond |
| Rébellion des bassins de Tone (Pool Rebellion) | 2 | 35 | 12 | | | ✓★ | | freezes the spawning ponds |
| Explosion de Qi (Qi Burst) | 3 | 39 | 18 | | ✓ | | | destroys everything nearby, the wizard stays safe |
| Mémoire ethnique (Ethnic Memory) | 3 | 43 | 18 | | | ✓ | | moves a school's floaters to the previous realm |
| Cadmus | 3 | 59 | 33 | ✓ | | ✓ | | enemy creatures of an island turn on each other |
| Brume temporelle (Time Mist) | 3 | 46 | 22 | | ✓ | | ✓ | all your floaters move faster |

## Tribe buildings

Players build no defence towers: you defend with warriors and spells.

| Building | Role | Pad | Build Tone | Upkeep | HP (Tark / Zygon / Céphéen / Dyla) |
|---|---|---|---|---|---|
| Générateur de Tone structurel | makes Build Tone (pays for buildings) | small | 35 | 1 | 30 / 25 / 25 / 30 |
| Créateur de Tone magique | makes Magic Tone (spells) | small | 60 | 1 | 20 / 30 / 30 / 20 |
| Producteur de Tone cristallin | makes Crystal Tone (training, recharging, healing); extends your Tone range by 320 px | small | 45 | 1 | 30 / 25 / 25 / 30 |
| Nébuliseur de Tone | extends your Tone range by 320 px | small | 10 | 1 | 20 |
| Train 1 / Train 2 / Train 3 school | trains warriors | medium | 50 | 0 | T1 35; T2 35 / 40 / 40 / 40; T3 50 / 50 / 50 / 45 |
| Spell school | trains wizards | medium | 50 | 0 | 30 |
| Hall (Refuge du Clan / Grande Bibliothèque) | home and storage; cannot be built | – | – | 0 | 50 / 45 / 45 / 50 |

HP grows by 5 per tier. A floater hitting a building deals 1 to 6 damage, with no hit roll.

## Leviathan creatures

| Kind | Names | Realm | Range | HP | Charge | Str | Spd | Strike |
|---|---|---|---|---|---|---|---|---|
| Spore (builder, infector) | Spores | Physical | – | 4 | 0 | 0 | 1 | – |
| Physical melee | Rakalingus / Broontilingus | Physical | melee | 16 | 10 | 4 | 2 | 6 |
| Physical ranged | Zeeth / Keth | Physical | 130 | 11 | 10 | 4 | 2 | 40 |
| Supernatural melee | Drack / Nadrack | Supernatural | melee | 13 | 10 | 3 | 3 | 3 |
| Supernatural ranged | Guêpe du Tone / Sasp | Supernatural | 140 | 8 | 10 | 3 | 3 | 14 |
| Ethereal melee | Ronth / Varnth | Ethereal | melee | 14 | 10 | 5 | 4 | 32 |
| Ethereal ranged | Metha / Koalint | Ethereal | 150 | 9 | 10 | 4 | 3 | 20 |
| Natural melee | Zwacker / Zwaup | Natural | melee | 15 | 10 | 3 | 3 | 12 |
| Natural ranged | Shandi / Flindex | Natural | 160 | 10 | 10 | 5 | 2 | 28 |

An elite (level 1) creature has × 1.7 HP and + 3 strength; ranks (difficulty 2 and above) add rank × strength / 22.

## Leviathan defences

The Leviathan's buildings defend its islands. Damage per hit is 1 to strength − 1 (always 1 for strength 2); the hit chance is shown against an untrained target (workers, spores). Period is the time between shots, in ticks.

| Building | Kind | Realm | Range | Str | Damage | Hit % | HP | Period |
|---|---|---|---|---|---|---|---|---|
| Quitch | close attack | Ethereal | < 60 | 4 | 1–3 | 57 | 18 | 40 |
| Blistin | close attack | Natural | < 60 | 5 | 1–4 | 61 | 10 | 40 |
| Menace Aveugle | close attack | Physical | < 60 | 3 | 1–2 | 52 | 15 | 40 |
| Hydron | close attack | Supernatural | < 60 | 7 | 1–6 | 70 | 22 | 40 |
| Essaim de Feu | close attack | Ethereal | < 60 | 8 | 1–7 | 74 | 24 | ≈ 30 |
| Mabus | lightning | Ethereal | < 60 | 10 | 1–9 | 82 | 23 | 160 |
| Plasid | shooter | Ethereal | 150 | 2 | 1 | 48 | 9 | 20 |
| Anénépode | shooter | Supernatural | 260 | 6 | 1–5 | 65 | 15 | 10 |
| Xylus | shooter | Supernatural | 320 | 6 | 1–5 | 65 | 16 | 20 |
| Grender | rod | Ethereal | 100 | 3 | 1–2 | 52 | 13 | ≈ 30 |
| Mesron | rod | Ethereal | 200 | 4 | 1–3 | 57 | 11 | ≈ 30 |
| Sentinelle mécanique | rod | Ethereal | 175 | 5 | 1–4 | 61 | 20 | 40 |

They fire at the floaters of **every** tribe on their island, yours and your rivals' alike (workers included), never at Leviathan creatures. Close-attack buildings and Mabus hit a random one of the first five floaters within 60 px; shooters and rods lock the first floater within their range and fire at it even if it moves away. Plasid and Mesron fire the very same bolt, but a Plasid bolt always deals exactly 1 damage while a Mesron bolt deals 1 to 3 (3 on about 1 hit in 30, enough to kill a fresh 3-HP worker at once). A worker killed by a single Plasid bolt had already lost HP. A shooter's or rod's shot can miss when it lands; the target's own strength lowers the hit chance as for any attack.

**Realm.** Each defence's attack has a realm (the Realm column, the colour of its impact), but the original game cancels it in the hit roll: the building attacks "in the target's own realm", so there is never a realm bonus or penalty against it. Your units' realms do not help or hurt against Leviathan buildings' shots.

Other Leviathan sites: contamination (7 HP); supply centres Marais de Broont (100), Fournaise de Sasp (80), Orbe bestial (80), Arbre de Sanders (100); the hub (20). The seals (20 HP each) cannot be hurt by floaters, only by their glyph.

## Combat rules

Every attack, by a floater, a Leviathan creature or a Leviathan defence, goes through the same three steps.

### 1. Strength on both sides

**A**, the attacker's strength:

| Attacker | A |
|---|---|
| Charged tribe unit | Str + 2 × (level − 1), + 1 with its school's glyph (Tal, Ahn, Nos), + 3 under Courage of the Brave |
| Uncharged tribe unit (charge 0) or worker | 2 × (level − 1): a worker hits with 0, a level-1 unit with no charge with 0 |
| Leviathan creature | Str + 3 × level, + rank × Str / 22 (difficulty 2 and above) |
| Leviathan defence | its Str |

**D**, the defender's strength, is worked out the same way for the target. Workers and spores always count as **D = 0**.

Every attempt spends one charge, hit or miss. An empty unit fights in its tribe's worker realm, at melee range, until it recharges at its school.

### 2. Hit roll

**Hit chance (%) = 10 + 60 × (A + 7 − D + realm bonus) / 14**, rounded down; the game then rolls a number from 0 to 99 and hits when it is lower.

Without any realm bonus that is 61 % between equal strengths, about 4.3 points more for each point of A above D, and 4.3 fewer for each point below.

### 3. Damage

Each hit deals the average of three random draws, from 1 up to A − 1 (at least 1, at most 10):

| A | Damage | Most likely | Average |
|---|---|---|---|
| 2 | always 1 | 1 | 1.0 |
| 3 | 1–2 | 1 (88 %) | 1.1 |
| 4 | 1–3 | 2 (59 %) | 1.7 |
| 5 | 1–4 | 2 (53 %) | 2.2 |
| 6 | 1–5 | 3 (42 %) | 2.7 |
| 7 | 1–6 | 3 (37 %) | 3.2 |
| 8 | 1–7 | 4 (31 %) | 3.7 |
| 10 | 1–9 | 5 (24 %) | 4.7 |

The highest values are rare: a strength-4 hit deals 3 only about once in 27 hits.

### Realms

Physical beats Supernatural, Supernatural beats Ethereal, Ethereal beats Natural, Natural beats Physical. Each realm therefore has one realm it beats, one that beats it, and one **opposite** realm (Physical–Ethereal, Supernatural–Natural).

| Attacker vs target | Realm bonus |
|---|---|
| same realm | 0 |
| attacker beats target | + R |
| target beats attacker | − R |
| opposite realms | from − R/2 to + R/2, following the tide (below) |

R depends on the difficulty: A / 4 at level 0 (at least 1), A / 2 at levels 1–2 (at least 2), 2A / 3 at levels 3–4 (at least 3). Leviathan defences never get a realm bonus: the game makes them attack in the target's own realm.

### The tide

The cross with four realm orbs in the lower-left corner of the island screen shows two tides, one per pair of opposite realms. Each tide is a marker that slides slowly from one realm of its pair to the other and back, without stopping:

- **Physical – Ethereal**: one way in about 6.7 minutes (8000 game ticks), a full swing in 13.3 minutes;
- **Supernatural – Natural**: one way in about 8.3 minutes (10000 ticks), a full swing in 16.7 minutes.

Both start half-way at the beginning of a game, in a random direction. The orbs grow and shrink with them.

The tide only matters between opposite realms. **The realm the marker sits next to is the exposed one**: attacks from its opposite realm on it gain up to + R/2, and its own attacks on the opposite realm lose up to R/2. With the marker half-way the bonus is 0. At difficulty 0 with A = 5 the tide is worth about ± 3 points of hit chance; at difficulty 3–4 about ± 7.

### Examples

At difficulty 0 (R = 1.25 for A = 5):

| Attack | A | D | Realm bonus | Hit chance | Damage per hit |
|---|---|---|---|---|---|
| Tark Train 1 level 1, charged (Physical) → Zygon worker (Supernatural) | 5 | 0 | + 1.25 (Physical beats Supernatural) | 66 % | 1–4, average 2.2 |
| Same unit → Dyla Den of the Beast level 1, charged (Physical) | 5 | 4 | 0 (same realm) | 44 % | 1–4 |
| Céphéen Banshee level 1 (Ethereal) → Tark worker (Physical), tide marker at Physical | 5 | 0 | + 0.63 | 64 % | 1–4 |
| Same, marker half-way / at Ethereal | 5 | 0 | 0 / − 0.63 | 61 % / 58 % | 1–4 |
| Plasid → any worker | 2 | 0 | none | 48 % | always 1 |

The same Tark warrior against the Zygon worker at higher difficulty: 72 % at levels 1–2, 75 % at levels 3–4 (the realm bonus grows), but 56 %, 50 % and 47 % if the realms were the other way round.

### Combat calculator

<p class="github-only">The <a href="https://fadoli.github.io/Tone-Rebellion-Remastered/guide.html#combat-calculator">website version of this guide</a> has an interactive calculator here: pick an attacker, a target, the difficulty and the tide to get the hit chance and the damage.</p>

<!-- calculator -->

## Sources and limits

- Unit and building numbers: `floater.txt`, `fltinf.txt`, `pad.txt`, `bldname.txt`, `bldtxt.txt`, `spells.txt`, `names.txt`, `worldpos.txt` from the game data.
- Rules: the remake's ports of `FLOAT.EXE` (`src/core`), each traced to a function of the original in [the decompilation notes](../../decompilation/behavior/) (island tasks, inventory and glyphs, end game, enemy AI). The upgrade thresholds were read byte for byte from the executable (`0x4a42b8`).
- Limits: the glyph number of an island is its place in the world (from the analysis, not seen in play); glyph 12 (Mef) has no effect found; which of a creature's two names shows is unknown; fire periods marked ≈ are computed from animation data. The original game was never run for this guide.
