# TODO — Portage Web (WASM)

Toutes les étapes sont faites (build Web jouable, mono-joueur). Détail : historique git et [validation](docs/build-and-validation.md).

## Choix

- Adaptateur SDL3 (règle de `AGENTS.md`), Emscripten `--use-port=sdl3`. Chaîne bureau : MSYS2 UCRT64 (`C:\msys64`), voir [build](docs/build-and-validation.md#sdl3-build). Le même adaptateur sert Linux/macOS.
- Rendu logiciel conservé : tampon RGBA 32 bits présenté par une texture SDL (WebGL en dessous). Pas de rendu WebGL direct : un seul blit plein écran par image.

## Étapes

1. [x] Surface portable, encore sous Win32
2. [x] Interfaces plateforme
3. [x] Adaptateur SDL3 bureau
4. [x] Cible Emscripten
5. [x] Données utilisateur
   - Limite : fichier `.iso` non accepté par la page (dossier seulement); les données vivent aussi en mémoire JS (MEMFS sous `IDBFS`), environ 360 Mo avec les musiques.
6. [x] Sauvegardes et options
7. [x] Audio navigateur
8. [x] Multijoueur (optionnel)
