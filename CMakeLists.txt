cmake_minimum_required(VERSION 3.24)

project(minesweeper CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML COMPONENTS Network Graphics Window Audio System CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

set(SOURCE_FILES
        src/main.cpp
#        src/DEFINITIONS.h
#        src/WindowUtils.hpp
#        src/Board.cpp src/Board.hpp
#        src/MineSweeper.cpp src/MineSweeper.hpp
#        src/managers/AssetManager.cpp src/managers/AssetManager.hpp
#        src/managers/StateManager.cpp src/managers/StateManager.hpp
#        src/states/State.hpp
#        src/states/MainMenuState.cpp src/states/MainMenuState.hpp
#        src/states/GameState.cpp src/states/GameState.hpp
#        src/states/AboutState.cpp src/states/AboutState.hpp
#        src/states/DifficultyMenuState.cpp src/states/DifficultyMenuState.hpp
#        src/states/CustomDifficultyState.cpp src/states/CustomDifficultyState.hpp
#        src/gui/Component.cpp src/gui/Component.hpp
#        src/gui/PassiveComponent.hpp
#        src/gui/WidgetFactory.cpp src/gui/WidgetFactory.hpp
#        src/gui/Button.cpp src/gui/Button.hpp
#        src/gui/Container.cpp src/gui/Container.hpp
#        src/gui/Input.cpp src/gui/Input.hpp
#        src/gui/Background.cpp src/gui/Background.hpp
#        src/gui/Indicator.cpp src/gui/Indicator.hpp
#        src/gui/SmileButton.cpp src/gui/SmileButton.hpp
#        src/states/DefaultState.cpp
#        src/states/DefaultState.h
)

add_executable(minesweeper ${SOURCE_FILES})

target_link_libraries(minesweeper PRIVATE SFML::Network SFML::Graphics SFML::Window SFML::Audio SFML::System)
target_link_libraries(minesweeper PRIVATE spdlog::spdlog)

target_include_directories(minesweeper PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Copy resources next to the executable (handles multi-config generators).
add_custom_command(TARGET minesweeper POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/_Resources
                $<TARGET_FILE_DIR:minesweeper>/_Resources)

option(MINESWEEPER_BUILD_TESTS "Build unit tests" ON)
if (MINESWEEPER_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif ()
