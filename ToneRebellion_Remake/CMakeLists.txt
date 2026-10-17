cmake_minimum_required(VERSION 3.16)
project(tone_rebellion_remake LANGUAGES C)

include(CTest)

add_library(tone_core STATIC
    src/data/cob_archive.c
    src/data/font_image.c
    src/data/shp_image.c
    src/core/island_haze.c
    src/core/island_data.c
    src/core/world_map.c
)
target_include_directories(tone_core PUBLIC src/core src/data)
target_compile_features(tone_core PUBLIC c_std_11)

if(MSVC)
    target_compile_options(tone_core PRIVATE /W4)
else()
    target_compile_options(tone_core PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(remake_inspect_worlds src/tools/inspect_worlds.c)
target_link_libraries(remake_inspect_worlds PRIVATE tone_core)
target_compile_features(remake_inspect_worlds PRIVATE c_std_11)

add_executable(remake_inspect_cob src/tools/inspect_cob.c)
target_link_libraries(remake_inspect_cob PRIVATE tone_core)
target_compile_features(remake_inspect_cob PRIVATE c_std_11)

if(BUILD_TESTING)
    add_executable(test_island_data tests/test_island_data.c)
    target_link_libraries(test_island_data PRIVATE tone_core)
    target_compile_features(test_island_data PRIVATE c_std_11)
    add_test(NAME island_data_unit COMMAND test_island_data)

    add_executable(test_island_corpus tests/test_island_corpus.c)
    target_link_libraries(test_island_corpus PRIVATE tone_core)
    target_compile_features(test_island_corpus PRIVATE c_std_11)

    add_executable(test_island_cob tests/test_island_cob.c)
    target_link_libraries(test_island_cob PRIVATE tone_core)
    target_compile_features(test_island_cob PRIVATE c_std_11)
endif()

if(WIN32)
    add_executable(remake_menu WIN32 src/platform/win32/menu_app.c)
    target_link_libraries(remake_menu PRIVATE tone_core user32 gdi32 msimg32 winmm)
    target_compile_features(remake_menu PRIVATE c_std_11)
    if(NOT MSVC)
        target_link_libraries(remake_menu PRIVATE m)
    endif()
endif()
