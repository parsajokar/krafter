cmake_minimum_required(VERSION 3.20)

project(krafter LANGUAGES CXX)

# Libraries

set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
add_subdirectory(lib/glfw)

add_subdirectory(lib/glad)

set(IMGUI_GLFW_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw/include")
add_subdirectory(lib/imgui)

find_package(OpenGL REQUIRED)

# Krafter

add_executable(krafter)

target_sources(
    krafter
    PRIVATE
    src/window.h
    src/window.cpp
    src/renderer.h
    src/renderer.cpp
    src/game.h
    src/game.cpp
    src/main.cpp
)

target_include_directories(
    krafter
    PRIVATE
    src
    lib/glfw/include
    lib/glad/include
    lib/imgui
    lib/imgui/backends
)

target_link_libraries(
    krafter
    PRIVATE
    glfw
    glad
    imgui
    OpenGL
)
