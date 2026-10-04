cmake_minimum_required(VERSION 4.0)

project(minesweeper CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML COMPONENTS Network Graphics Window Audio System CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(fmt)
find_package(nlohmann_json CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        "src/*.cpp"
        "src/*.c"
)

file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
        "src/*.hpp"
        "src/*.h"
)

add_executable(minesweeper ${SOURCES} ${HEADERS})

target_link_libraries(minesweeper PRIVATE SFML::Network SFML::Graphics SFML::Window SFML::Audio SFML::System)
target_link_libraries(minesweeper PRIVATE spdlog::spdlog)
target_link_libraries(minesweeper PRIVATE fmt::fmt)
target_link_libraries(minesweeper PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(minesweeper PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_custom_command(TARGET minesweeper POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:minesweeper>/assets
)

option(MINESWEEPER_BUILD_TESTS "Build unit tests" ON)
if (MINESWEEPER_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif ()
