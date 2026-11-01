#!/bin/sh
# Web build (TODO_WEB.md step 4) from an MSYS2 UCRT64 shell with the
# mingw-w64-ucrt-x86_64-emscripten package installed.
#
#   tools/build_web.sh <SDL3 source directory>
#
# SDL3 is built once from source for Emscripten (static, into
# build/web/sdl3) instead of Emscripten's sdl3 port, which downloads from
# the network. The game then builds into build/web/game; the page, script
# and wasm are copied to web/out/, to be served as static files (for
# example `python -m http.server` in web/out).
set -e
here=$(cd "$(dirname "$0")/.." && pwd)
sdl_source=${1:?usage: tools/build_web.sh <SDL3 source directory>}
. /ucrt64/etc/profile.d/emscripten.sh

if [ ! -f "$here/build/web/sdl3/lib/cmake/SDL3/SDL3Config.cmake" ]; then
    emcmake cmake -S "$sdl_source" -B "$here/build/web/sdl3-build" -G Ninja \
        -DCMAKE_BUILD_TYPE=Release -DSDL_SHARED=OFF -DSDL_STATIC=ON \
        -DSDL_TEST_LIBRARY=OFF -DSDL_EXAMPLES=OFF \
        -DCMAKE_INSTALL_PREFIX="$here/build/web/sdl3"
    cmake --build "$here/build/web/sdl3-build"
    cmake --install "$here/build/web/sdl3-build"
fi

emcmake cmake -S "$here" -B "$here/build/web/game" -G Ninja \
    -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=OFF \
    -DSDL3_DIR="$here/build/web/sdl3/lib/cmake/SDL3"
cmake --build "$here/build/web/game" --target remake_sdl
mkdir -p "$here/web/out"
cp "$here/build/web/game/ToneRebellion_Remake.html" \
   "$here/build/web/game/ToneRebellion_Remake.js" \
   "$here/build/web/game/ToneRebellion_Remake.wasm" "$here/web/out/"
echo "web build: $here/web/out/ToneRebellion_Remake.html"
