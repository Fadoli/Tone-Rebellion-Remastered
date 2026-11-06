#!/bin/sh
# Web build (TODO_WEB.md step 4) from an MSYS2 UCRT64 shell with the
# mingw-w64-ucrt-x86_64-emscripten package installed, or any shell with emcc
# on PATH (the release workflow uses emsdk on Linux).
#
#   tools/build_web.sh [SDL3 source directory] [build directory]
#
# SDL3 is built once from source for Emscripten (static, into
# build/web/sdl3) instead of Emscripten's sdl3 port, which downloads from
# the network; the source directory is only needed for that first build.
# The game then builds into build/web/game (or the second argument); the
# page, script and wasm are copied to web/out/, to be served as static
# files (for example `python -m http.server` in web/out).
set -e
here=$(cd "$(dirname "$0")/.." && pwd)
sdl_source=$1
game_build=${2:-$here/build/web/game}
# MSYS2 puts Emscripten behind a profile script; elsewhere (CI, emsdk) emcc
# is already on PATH.
if [ -f /ucrt64/etc/profile.d/emscripten.sh ]; then
    . /ucrt64/etc/profile.d/emscripten.sh
fi
# wasm-opt's thread pool deadlocked here on Windows (no CPU, the link never
# ends); with one thread the link takes about 25 s.
export BINARYEN_CORES=1

if [ ! -f "$here/build/web/sdl3/lib/cmake/SDL3/SDL3Config.cmake" ]; then
    : "${sdl_source:?usage: tools/build_web.sh <SDL3 source directory> (first build)}"
    emcmake cmake -S "$sdl_source" -B "$here/build/web/sdl3-build" -G Ninja \
        -DCMAKE_BUILD_TYPE=Release -DSDL_SHARED=OFF -DSDL_STATIC=ON \
        -DSDL_TEST_LIBRARY=OFF -DSDL_EXAMPLES=OFF \
        -DCMAKE_INSTALL_PREFIX="$here/build/web/sdl3"
    cmake --build "$here/build/web/sdl3-build"
    cmake --install "$here/build/web/sdl3-build"
fi

emcmake cmake -S "$here" -B "$game_build" -G Ninja \
    -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=OFF \
    -DSDL3_DIR="$here/build/web/sdl3/lib/cmake/SDL3"
cmake --build "$game_build" --target remake_sdl
mkdir -p "$here/web/out"
cp "$game_build/ToneRebellion_Remake.html" \
   "$game_build/ToneRebellion_Remake.js" \
   "$game_build/ToneRebellion_Remake.wasm" "$here/web/out/"
echo "web build: $here/web/out/ToneRebellion_Remake.html"
