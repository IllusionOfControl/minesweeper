cmake_minimum_required(VERSION 3.24)
project(minesweeper)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BUILD_TYPE Debug)

set(SOURCE_FILES ${SOURCE_FILES} src/MineSweeper.cpp src/MineSweeper.hpp)
set(SOURCE_FILES ${SOURCE_FILES} src/managers/AssetManager.cpp src/managers/AssetManager.hpp)
set(SOURCE_FILES ${SOURCE_FILES} src/managers/StateManager.cpp src/managers/StateManager.hpp)
set(SOURCE_FILES ${SOURCE_FILES} src/states/State.hpp)
set(SOURCE_FILES ${SOURCE_FILES} src/states/MainMenuState.cpp src/states/MainMenuState.hpp)
set(SOURCE_FILES ${SOURCE_FILES} src/states/GameState.cpp src/states/GameState.hpp)
set(SOURCE_FILES ${SOURCE_FILES} src/states/AboutState.cpp src/states/AboutState.hpp)
set(SOURCE_FILES ${SOURCE_FILES} src/states/DifficultyMenuState.cpp src/states/DifficultyMenuState.hpp)
set(SOURCE_FILES ${SOURCE_FILES} src/states/CustomDifficultyState.cpp src/states/CustomDifficultyState.hpp)
set(SOURCE_FILES ${SOURCE_FILES} src/gui/Component.cpp src/gui/Component.hpp)
set(SOURCE_FILES ${SOURCE_FILES} src/gui/Button.cpp src/gui/Button.hpp)
set(SOURCE_FILES ${SOURCE_FILES} src/gui/Container.cpp src/gui/Container.hpp)
set(SOURCE_FILES ${SOURCE_FILES} src/gui/Input.cpp src/gui/Input.hpp)
set(SOURCE_FILES ${SOURCE_FILES} src/gui/Background.cpp src/gui/Background.hpp)
set(SOURCE_FILES ${SOURCE_FILES} src/gui/Indicator.cpp src/gui/Indicator.hpp)
#set(SOURCE_FILES ${SOURCE_FILES} src/gui/GameField.cpp src/gui/GameField.hpp)
set(SOURCE_FILES ${SOURCE_FILES} src/main.cpp src/DEFINITIONS.h src/gui/SmileButton.cpp src/gui/SmileButton.hpp)
find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)
add_executable(minesweeper ${SOURCE_FILES})

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(minesweeper PRIVATE sfml-system sfml-network sfml-graphics sfml-window)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}\\_Resources\\
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}\\_Resources\\)