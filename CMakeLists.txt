cmake_minimum_required(VERSION 3.24)

project(minesweeper CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML COMPONENTS Network Graphics Window Audio System CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(fmt)
find_package(nlohmann_json CONFIG REQUIRED)

set(SOURCE_FILES
        src/main.cpp
        src/Difficulty.hpp
        src/Board.cpp
        src/Board.hpp
        src/GameContext.hpp
        src/MineSweeper.cpp
        src/MineSweeper.hpp
        src/WindowUtils.hpp
        src/Logger.hpp
        src/Layout.hpp
        src/managers/StateManager.cpp
        src/managers/StateManager.hpp
        src/managers/AssetManager.cpp
        src/managers/AssetManager.hpp
        src/managers/ResourceIdentifiers.hpp
        src/managers/ResultManager.cpp
        src/managers/ResultManager.hpp
        src/states/StateIdentifiers.hpp
        src/states/EmptyState.cpp
        src/states/MainMenuState.cpp
        src/states/MainMenuState.hpp
        src/states/DifficultyMenuState.cpp
        src/states/DifficultyMenuState.hpp
        src/states/AboutState.cpp
        src/states/AboutState.hpp
        src/states/CustomDifficultyState.cpp
        src/states/CustomDifficultyState.hpp
        src/states/GameState.cpp
        src/states/GameState.hpp
        src/states/SaveResultState.cpp
        src/states/SaveResultState.hpp
        src/states/LeaderboardState.cpp
        src/states/LeaderboardState.hpp
        src/gui/Background.cpp
        src/gui/Background.hpp
        src/gui/PassiveComponent.hpp
        src/gui/Component.cpp
        src/gui/Component.hpp
        src/gui/Button.cpp
        src/gui/Button.hpp
        src/gui/Container.cpp
        src/gui/Container.hpp
        src/gui/Image.cpp
        src/gui/Image.hpp
        src/gui/TopBar.cpp
        src/gui/TopBar.hpp
        src/gui/Text.cpp
        src/gui/Text.hpp
        src/gui/Input.cpp
        src/gui/Input.hpp
        src/gui/Indicator.cpp
        src/gui/Indicator.hpp
        src/gui/SmileButton.cpp
        src/gui/SmileButton.hpp
)

add_executable(minesweeper ${SOURCE_FILES})

target_link_libraries(minesweeper PRIVATE SFML::Network SFML::Graphics SFML::Window SFML::Audio SFML::System)
target_link_libraries(minesweeper PRIVATE spdlog::spdlog)
target_link_libraries(minesweeper PRIVATE fmt::fmt)
target_link_libraries(minesweeper PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(minesweeper PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_custom_command(TARGET minesweeper POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/_Resources
                $<TARGET_FILE_DIR:minesweeper>/_Resources)

option(MINESWEEPER_BUILD_TESTS "Build unit tests" ON)
if (MINESWEEPER_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif ()
