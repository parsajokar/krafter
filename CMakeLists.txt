cmake_minimum_required(VERSION 3.20)

# Libraries

set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
add_subdirectory(lib/glfw)

# Krafter

project(krafter LANGUAGES CXX)

add_executable(krafter)

target_sources(
    krafter
    PRIVATE
    src/game.h
    src/game.cpp
    src/main.cpp
)

target_include_directories(
    krafter
    PRIVATE
    src
    lib/glfw/include
)

target_link_libraries(
    krafter
    PRIVATE
    glfw
    GL
)
