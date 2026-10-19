cmake_minimum_required(VERSION 3.16)
project(tone_rebellion_remake LANGUAGES C)

include(CTest)

add_library(tone_core STATIC
    src/data/cob_archive.c
    src/data/font_image.c
    src/core/bitmap_font_render.c
    src/data/shp_image.c
    src/core/island_haze.c
    src/core/island_palette_lookup.c
    src/core/island_data.c
    src/core/island_render_rules.c
    src/core/curved_text_layout.c
    src/core/iw_construct.c
    src/core/pad_catalog.c
    src/core/floater_catalog.c
    src/core/floater_effect_catalog.c
    src/core/building_render.c
    src/core/building_render_parser.c
    src/core/building_render_frames.c
    src/core/window_catalog.c
    src/core/window_catalog_controls.c
    src/core/world_map.c
    src/core/game_start.c
    src/core/game_start_tones.c
    src/core/game_session.c
    src/core/game_session_start.c
    src/core/game_session_buildings.c
    src/core/game_session_layout.c
    src/core/game_session_pending_events.c
    src/core/game_session_animation.c
    src/core/game_session_movement.c
    src/core/game_session_combat.c
    src/core/game_session_queries.c
    src/core/game_session_action9.c
    src/core/game_session_delivery.c
    src/core/game_session_delivery_advance.c
    src/core/game_session_world_map.c
    src/core/game_session_economy.c
    src/core/game_session_trade.c
    src/core/game_session_events.c
    src/core/game_session_site_events.c
    src/core/game_session_build_events.c
    src/core/game_inventory.c
    src/core/game_trade.c
    src/core/game_diplomacy.c
    src/core/game_glyph_inventory.c
    src/core/island_panel_info.c
    src/core/island_panel_info_tasks.c
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
    find_program(NODE_EXECUTABLE NAMES node)
    if(NODE_EXECUTABLE)
        add_test(
            NAME documentation_integrity
            COMMAND ${NODE_EXECUTABLE} --test "${CMAKE_CURRENT_SOURCE_DIR}/tests/test_docs_integrity.mjs"
        )
    endif()

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

    add_executable(test_bitmap_font_render tests/test_bitmap_font_render.c)
    target_link_libraries(test_bitmap_font_render PRIVATE tone_core)
    target_compile_features(test_bitmap_font_render PRIVATE c_std_11)
    enable_test_assertions(test_bitmap_font_render)
    add_test(NAME bitmap_font_render_unit COMMAND test_bitmap_font_render)

    add_executable(test_island_render_rules tests/test_island_render_rules.c)
    target_link_libraries(test_island_render_rules PRIVATE tone_core)
    target_compile_features(test_island_render_rules PRIVATE c_std_11)
    enable_test_assertions(test_island_render_rules)
    add_test(NAME island_render_rules_unit COMMAND test_island_render_rules)

    add_executable(test_island_palette_lookup tests/test_island_palette_lookup.c)
    target_link_libraries(test_island_palette_lookup PRIVATE tone_core)
    target_compile_features(test_island_palette_lookup PRIVATE c_std_11)
    enable_test_assertions(test_island_palette_lookup)
    add_test(NAME island_palette_lookup_unit COMMAND test_island_palette_lookup)

    add_executable(test_pad_catalog tests/test_pad_catalog.c)
    target_link_libraries(test_pad_catalog PRIVATE tone_core)
    target_compile_features(test_pad_catalog PRIVATE c_std_11)
    enable_test_assertions(test_pad_catalog)
    add_test(NAME pad_catalog_unit COMMAND test_pad_catalog)

    add_executable(test_floater_catalog tests/test_floater_catalog.c)
    target_link_libraries(test_floater_catalog PRIVATE tone_core)
    target_compile_features(test_floater_catalog PRIVATE c_std_11)
    enable_test_assertions(test_floater_catalog)
    add_test(NAME floater_catalog_unit COMMAND test_floater_catalog)

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

    add_executable(test_game_inventory tests/test_game_inventory.c)
    target_link_libraries(test_game_inventory PRIVATE tone_core)
    target_compile_features(test_game_inventory PRIVATE c_std_11)
    enable_test_assertions(test_game_inventory)
    add_test(NAME game_inventory_unit COMMAND test_game_inventory)

    add_executable(test_game_trade tests/test_game_trade.c)
    target_link_libraries(test_game_trade PRIVATE tone_core)
    target_compile_features(test_game_trade PRIVATE c_std_11)
    enable_test_assertions(test_game_trade)
    add_test(NAME game_trade_unit COMMAND test_game_trade)

    add_executable(test_game_diplomacy tests/test_game_diplomacy.c)
    target_link_libraries(test_game_diplomacy PRIVATE tone_core)
    target_compile_features(test_game_diplomacy PRIVATE c_std_11)
    enable_test_assertions(test_game_diplomacy)
    add_test(NAME game_diplomacy_unit COMMAND test_game_diplomacy)

    add_executable(test_game_glyph_inventory tests/test_game_glyph_inventory.c)
    target_link_libraries(test_game_glyph_inventory PRIVATE tone_core)
    target_compile_features(test_game_glyph_inventory PRIVATE c_std_11)
    enable_test_assertions(test_game_glyph_inventory)
    add_test(NAME game_glyph_inventory_unit COMMAND test_game_glyph_inventory)

    add_executable(test_island_panel_info tests/test_island_panel_info.c)
    target_link_libraries(test_island_panel_info PRIVATE tone_core)
    target_compile_features(test_island_panel_info PRIVATE c_std_11)
    enable_test_assertions(test_island_panel_info)
    add_test(NAME island_panel_info_unit COMMAND test_island_panel_info)

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
    add_custom_command(TARGET remake_menu POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:remake_menu>"
            "${CMAKE_CURRENT_SOURCE_DIR}/ToneRebellion_Remake.exe"
        COMMENT "Updating the ready-to-launch ToneRebellion_Remake.exe"
        VERBATIM
    )

    add_executable(bench_task_text bench/task_text_bench.c)
    target_link_libraries(bench_task_text PRIVATE tone_core user32 gdi32)
    target_compile_features(bench_task_text PRIVATE c_std_11)
endif()
