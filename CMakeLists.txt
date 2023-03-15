cmake_minimum_required(VERSION 3.24)
project(minesweeper)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BUILD_TYPE Debug)

set(SOURCE_FILES ${SOURCE_FILES} src/MineSweeper.cpp src/MineSweeper.h)
set(SOURCE_FILES ${SOURCE_FILES} src/managers/AssetManager.cpp src/managers/AssetManager.h)
set(SOURCE_FILES ${SOURCE_FILES} src/managers/StateManager.cpp src/managers/StateManager.h)
set(SOURCE_FILES ${SOURCE_FILES} src/states/State.h)
set(SOURCE_FILES ${SOURCE_FILES} src/states/MainMenuState.cpp src/states/MainMenuState.h)
set(SOURCE_FILES ${SOURCE_FILES} src/states/GameState.cpp src/states/GameState.h)
set(SOURCE_FILES ${SOURCE_FILES} src/states/AboutState.cpp src/states/AboutState.h)
set(SOURCE_FILES ${SOURCE_FILES} src/states/DifficultyMenuState.cpp src/states/DifficultyMenuState.h)
set(SOURCE_FILES ${SOURCE_FILES} src/states/CustomDifficultyState.cpp src/states/CustomDifficultyState.h)
set(SOURCE_FILES ${SOURCE_FILES} src/states/LeaderboardState.cpp src/states/LeaderboardState.h)
set(SOURCE_FILES ${SOURCE_FILES} src/states/RecordSaveState.cpp src/states/RecordSaveState.h)
set(SOURCE_FILES ${SOURCE_FILES} src/managers/LeaderboardManager.cpp src/managers/LeaderboardManager.h)
set(SOURCE_FILES ${SOURCE_FILES} src/main.cpp src/DEFINITIONS.h src/gui/Component.cpp src/gui/Component.hpp src/gui/Button.cpp src/gui/Button.hpp src/gui/Container.cpp src/gui/Container.hpp src/gui/Input.cpp src/gui/Input.hpp)
find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)
add_executable(minesweeper ${SOURCE_FILES})

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(minesweeper PRIVATE sfml-system sfml-network sfml-graphics sfml-window)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}\\_Resources\\
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}\\_Resources\\)