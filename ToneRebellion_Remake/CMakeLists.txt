cmake_minimum_required(VERSION 3.16)
project(tone_rebellion_remake LANGUAGES C)

include(CTest)

add_library(tone_core STATIC
    src/data/cob_archive.c
    src/data/font_image.c
    src/data/shp_image.c
    src/core/island_haze.c
    src/core/island_data.c
    src/core/island_render_rules.c
    src/core/curved_text_layout.c
    src/core/iw_construct.c
    src/core/pad_catalog.c
    src/core/building_render.c
    src/core/window_catalog.c
    src/core/world_map.c
    src/core/game_start.c
    src/core/game_session.c
    src/core/game_music.c
    src/core/floater_motion.c
    src/core/tone_rng.c
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
    function(enable_test_assertions target)
        if(MSVC)
            target_compile_options(${target} PRIVATE /UNDEBUG)
        else()
            target_compile_options(${target} PRIVATE -UNDEBUG)
        endif()
    endfunction()

    add_executable(test_island_data tests/test_island_data.c)
    target_link_libraries(test_island_data PRIVATE tone_core)
    target_compile_features(test_island_data PRIVATE c_std_11)
    enable_test_assertions(test_island_data)
    add_test(NAME island_data_unit COMMAND test_island_data)

    add_executable(test_shp_image tests/test_shp_image.c)
    target_link_libraries(test_shp_image PRIVATE tone_core)
    target_compile_features(test_shp_image PRIVATE c_std_11)
    enable_test_assertions(test_shp_image)
    add_test(NAME shp_image_unit COMMAND test_shp_image)

    add_executable(test_island_render_rules tests/test_island_render_rules.c)
    target_link_libraries(test_island_render_rules PRIVATE tone_core)
    target_compile_features(test_island_render_rules PRIVATE c_std_11)
    enable_test_assertions(test_island_render_rules)
    add_test(NAME island_render_rules_unit COMMAND test_island_render_rules)

    add_executable(test_pad_catalog tests/test_pad_catalog.c)
    target_link_libraries(test_pad_catalog PRIVATE tone_core)
    target_compile_features(test_pad_catalog PRIVATE c_std_11)
    enable_test_assertions(test_pad_catalog)
    add_test(NAME pad_catalog_unit COMMAND test_pad_catalog)

    add_executable(test_building_render tests/test_building_render.c)
    target_link_libraries(test_building_render PRIVATE tone_core)
    target_compile_features(test_building_render PRIVATE c_std_11)
    enable_test_assertions(test_building_render)
    add_test(NAME building_render_unit COMMAND test_building_render)

    add_executable(test_window_catalog tests/test_window_catalog.c)
    target_link_libraries(test_window_catalog PRIVATE tone_core)
    target_compile_features(test_window_catalog PRIVATE c_std_11)
    enable_test_assertions(test_window_catalog)
    add_test(NAME window_catalog_unit COMMAND test_window_catalog)

    add_executable(test_iw_construct tests/test_iw_construct.c)
    target_link_libraries(test_iw_construct PRIVATE tone_core)
    target_compile_features(test_iw_construct PRIVATE c_std_11)
    enable_test_assertions(test_iw_construct)
    add_test(NAME iw_construct_unit COMMAND test_iw_construct)

    add_executable(test_curved_text_layout tests/test_curved_text_layout.c)
    target_link_libraries(test_curved_text_layout PRIVATE tone_core)
    target_compile_features(test_curved_text_layout PRIVATE c_std_11)
    enable_test_assertions(test_curved_text_layout)
    add_test(NAME curved_text_layout_unit COMMAND test_curved_text_layout)

    add_executable(test_game_start tests/test_game_start.c)
    target_link_libraries(test_game_start PRIVATE tone_core)
    target_compile_features(test_game_start PRIVATE c_std_11)
    enable_test_assertions(test_game_start)
    add_test(NAME game_start_unit COMMAND test_game_start)

    add_executable(test_tone_rng tests/test_tone_rng.c)
    target_link_libraries(test_tone_rng PRIVATE tone_core)
    target_compile_features(test_tone_rng PRIVATE c_std_11)
    enable_test_assertions(test_tone_rng)
    add_test(NAME tone_rng_unit COMMAND test_tone_rng)

    add_executable(test_game_start_tones tests/test_game_start_tones.c)
    target_link_libraries(test_game_start_tones PRIVATE tone_core)
    target_compile_features(test_game_start_tones PRIVATE c_std_11)
    enable_test_assertions(test_game_start_tones)
    add_test(NAME game_start_tones_unit COMMAND test_game_start_tones)

    add_executable(test_game_session tests/test_game_session.c)
    target_link_libraries(test_game_session PRIVATE tone_core)
    target_compile_features(test_game_session PRIVATE c_std_11)
    enable_test_assertions(test_game_session)
    add_test(NAME game_session_unit COMMAND test_game_session)

    add_executable(test_floater_motion tests/test_floater_motion.c)
    target_link_libraries(test_floater_motion PRIVATE tone_core)
    target_compile_features(test_floater_motion PRIVATE c_std_11)
    enable_test_assertions(test_floater_motion)
    add_test(NAME floater_motion_unit COMMAND test_floater_motion)

    add_executable(test_game_music tests/test_game_music.c)
    target_link_libraries(test_game_music PRIVATE tone_core)
    target_compile_features(test_game_music PRIVATE c_std_11)
    enable_test_assertions(test_game_music)
    add_test(NAME game_music_unit COMMAND test_game_music)

    add_executable(test_island_corpus tests/test_island_corpus.c)
    target_link_libraries(test_island_corpus PRIVATE tone_core)
    target_compile_features(test_island_corpus PRIVATE c_std_11)
    enable_test_assertions(test_island_corpus)

    add_executable(test_island_cob tests/test_island_cob.c)
    target_link_libraries(test_island_cob PRIVATE tone_core)
    target_compile_features(test_island_cob PRIVATE c_std_11)
    enable_test_assertions(test_island_cob)
endif()

if(WIN32)
    add_executable(remake_menu WIN32 src/platform/win32/menu_app.c)
    target_link_libraries(remake_menu PRIVATE tone_core user32 gdi32 msimg32 winmm)
    target_compile_features(remake_menu PRIVATE c_std_11)
    if(NOT MSVC)
        target_link_libraries(remake_menu PRIVATE m)
    endif()
endif()
