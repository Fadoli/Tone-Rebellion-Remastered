# TODO — Portage Web (WASM)

**Priorité : dernière.** Ne commencer qu'après une version solo complète et jouable (phases 1 à 3 de la [feuille de route](ROADMAP.md)). Aucun item ici ne doit retarder le gameplay.

## Constat (2026-10-31, comptage par grep)

- `src/core` (~25 k lignes) n'inclut aucun en-tête Windows; un seul `fopen`. Compilable par Emscripten sans changement attendu (non essayé).
- `src/platform/win32` (~15 k lignes) concentre la dépendance : `HDC` traversant ~15 fichiers de rendu (86 usages), primitives GDI limitées (`CreateDIBSection`, `AlphaBlend`, `StretchBlt`, `SetPixel`/`GetPixel`, `FillRect`, `Ellipse`, `LineTo`, `Rectangle`), pas de police GDI (polices bitmap du jeu).
- Boucle : un seul `GetMessageA`, cadence `SetTimer` 33 ms, pas de thread ni `Sleep` : compatible `emscripten_set_main_loop`.
- Audio : mixeur `waveOut*` + `PlaySoundA` (effets), MCI `tone_music` (musiques `THING2\*.WAV`).
- Réseau : TCP Winsock (`net_session.inc`); sockets bruts interdits en navigateur.
- Données : le jeu original n'est pas redistribuable. L'utilisateur fournit son ISO ou ses fichiers; `src/data/iso9660.c` lit déjà une image.

## Choix

- Adaptateur SDL3 (règle de `AGENTS.md`), Emscripten `--use-port=sdl3`. Le même adaptateur sert Linux/macOS.
- Rendu logiciel conservé : tampon RGBA 32 bits présenté par une texture SDL (WebGL en dessous). Pas de rendu WebGL direct : un seul blit plein écran par image.

## Étapes

1. [ ] **Surface portable, encore sous Win32.** Remplacer `HDC`/DIB par un type `RenderSurface` (pixels, largeur, hauteur, pas) dans un module sans en-tête Windows; réécrire les primitives listées ci-dessus (mélange alpha, étirement, rectangle, ellipse, ligne). Win32 ne fait plus que présenter le tampon. Valider par captures `island_e2e.ps1` avant/après (pixel à pixel si possible).
2. [ ] **Interfaces plateforme.** Isoler entrée (souris, clavier, molette), horloge (`GetTickCount`), audio (effets + flux musique), fichiers (dossiers de sauvegarde, `FindFirstFileA`, `CreateDirectoryA`), boîtes d'erreur (`MessageBoxA` ×10) derrière de petites interfaces C; implémentation Win32 inchangée en comportement.
3. [ ] **Adaptateur SDL3 bureau.** Fenêtre, présentation du tampon, événements, `SDL_AudioStream` pour le mixeur et les musiques WAV. Parité avec Win32 avant la cible Web.
4. [ ] **Cible Emscripten.** Préréglage CMake (`emcmake`), boucle `emscripten_set_main_loop`, page HTML minimale, `-sALLOW_MEMORY_GROWTH`. Mesurer taille `.wasm` et temps de chargement.
5. [ ] **Données utilisateur.** Sélecteur de fichier (ISO ou dossier `THING1`/`THING2`) vers le système de fichiers virtuel, cache persistant `IDBFS` (équivalent de `iso_cache`); aucune donnée originale hébergée.
6. [ ] **Sauvegardes et options.** `saves/` et `float.cfg` sur `IDBFS`, synchronisation après écriture; export/import manuel d'une sauvegarde.
7. [ ] **Audio navigateur.** Démarrage du contexte audio au premier geste utilisateur; vérifier la latence du mixeur.
8. [ ] **Multijoueur (optionnel).** Transport WebSocket derrière l'interface réseau + relais (type websockify) côté serveur, ou désactiver le multijoueur dans la build Web.

## Estimation

Étape 1 : 1–2 semaines; étapes 2–4 : ~1 semaine; étapes 5–7 : quelques jours; étape 8 : ~1 semaine ou abandon.
