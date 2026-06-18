cmake_minimum_required(VERSION 3.24)
project(minesweeper CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES
        src/main.cpp
        src/DEFINITIONS.h
        src/MineSweeper.cpp src/MineSweeper.hpp
        src/managers/AssetManager.cpp src/managers/AssetManager.hpp
        src/managers/StateManager.cpp src/managers/StateManager.hpp
        src/states/State.hpp
        src/states/MainMenuState.cpp src/states/MainMenuState.hpp
        src/states/GameState.cpp src/states/GameState.hpp
        src/states/AboutState.cpp src/states/AboutState.hpp
        src/states/DifficultyMenuState.cpp src/states/DifficultyMenuState.hpp
        src/states/CustomDifficultyState.cpp src/states/CustomDifficultyState.hpp
        src/gui/Component.cpp src/gui/Component.hpp
        src/gui/Button.cpp src/gui/Button.hpp
        src/gui/Container.cpp src/gui/Container.hpp
        src/gui/Input.cpp src/gui/Input.hpp
        src/gui/Background.cpp src/gui/Background.hpp
        src/gui/Indicator.cpp src/gui/Indicator.hpp
        src/gui/SmileButton.cpp src/gui/SmileButton.hpp)

find_package(SFML 2.5 COMPONENTS system window graphics CONFIG REQUIRED)

add_executable(minesweeper ${SOURCE_FILES})
target_link_libraries(minesweeper PRIVATE sfml-system sfml-window sfml-graphics)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/_Resources/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/_Resources/)
