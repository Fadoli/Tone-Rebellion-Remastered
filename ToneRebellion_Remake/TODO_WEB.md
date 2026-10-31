# TODO — Portage Web (WASM)

**Priorité : dernière.** Ne commencer qu'après une version solo complète et jouable (phases 1 à 3 de la [feuille de route](ROADMAP.md)). Aucun item ici ne doit retarder le gameplay.

## Constat (2026-10-31, comptage par grep)

- `src/core` (~25 k lignes) n'inclut aucun en-tête Windows; un seul `fopen`. Compilable par Emscripten sans changement attendu (non essayé).
- `src/platform/win32` (~15 k lignes) concentre la dépendance. Le rendu n'en fait plus partie (étape 1) : il dessine dans un `RenderSurface` (`src/render`), et GDI ne sert qu'à présenter le tampon (`present_back_buffer`).
- Boucle : un seul `GetMessageA`, cadence `SetTimer` 33 ms, pas de thread ni `Sleep` : compatible `emscripten_set_main_loop`.
- Audio : mixeur `waveOut*` + `PlaySoundA` (effets), MCI `tone_music` (musiques `THING2\*.WAV`).
- Réseau : TCP Winsock (`net_session.inc`); sockets bruts interdits en navigateur.
- Données : le jeu original n'est pas redistribuable. L'utilisateur fournit son ISO ou ses fichiers; `src/data/iso9660.c` lit déjà une image.

## Choix

- Adaptateur SDL3 (règle de `AGENTS.md`), Emscripten `--use-port=sdl3`. Le même adaptateur sert Linux/macOS.
- Rendu logiciel conservé : tampon RGBA 32 bits présenté par une texture SDL (WebGL en dessous). Pas de rendu WebGL direct : un seul blit plein écran par image.

## Étapes

1. [x] **Surface portable, encore sous Win32.** `src/render/render_surface.{h,c}` (bibliothèque `tone_render`, sans en-tête Windows) : pixels 0xAARRGGBB, pile de découpe (rectangle + masque par pixel à la place des régions GDI), remplissage, cadre, pixel, blit prémultiplié avec mise à l'échelle au plus proche et transformation (brume). Les `SpriteFrame` portent des tableaux de pixels; les fonctions de rendu prennent un `RenderSurface *`. Seuls `ensure_paint_buffer`/`present_back_buffer` (`render_dispatch.inc`) touchent GDI. Parité : 38 captures `--bench-dump` identiques octet pour octet à la build précédente, et un banc hors dépôt GDI contre `RenderSurface` (découpe, masque, `AlphaBlend` à l'échelle, `FillRect`, `FrameRect`, `Rectangle`, `SetPixel`/`GetPixel`) sans écart sur 20 000 tirages ([mesures](bench/gameplay_hotspots.md#rendersurface-2026-10-31)).
2. [ ] **Interfaces plateforme.** Isoler entrée (souris, clavier, molette), horloge (`GetTickCount`), audio (effets + flux musique), fichiers (dossiers de sauvegarde, `FindFirstFileA`, `CreateDirectoryA`), boîtes d'erreur (`MessageBoxA` ×10) derrière de petites interfaces C; implémentation Win32 inchangée en comportement.
3. [ ] **Adaptateur SDL3 bureau.** Fenêtre, présentation du tampon, événements, `SDL_AudioStream` pour le mixeur et les musiques WAV. Parité avec Win32 avant la cible Web.
4. [ ] **Cible Emscripten.** Préréglage CMake (`emcmake`), boucle `emscripten_set_main_loop`, page HTML minimale, `-sALLOW_MEMORY_GROWTH`. Mesurer taille `.wasm` et temps de chargement.
5. [ ] **Données utilisateur.** Sélecteur de fichier (ISO ou dossier `THING1`/`THING2`) vers le système de fichiers virtuel, cache persistant `IDBFS` (équivalent de `iso_cache`); aucune donnée originale hébergée.
6. [ ] **Sauvegardes et options.** `saves/` et `float.cfg` sur `IDBFS`, synchronisation après écriture; export/import manuel d'une sauvegarde.
7. [ ] **Audio navigateur.** Démarrage du contexte audio au premier geste utilisateur; vérifier la latence du mixeur.
8. [ ] **Multijoueur (optionnel).** Transport WebSocket derrière l'interface réseau + relais (type websockify) côté serveur, ou désactiver le multijoueur dans la build Web.

## Estimation

Étape 1 : 1–2 semaines; étapes 2–4 : ~1 semaine; étapes 5–7 : quelques jours; étape 8 : ~1 semaine ou abandon.
