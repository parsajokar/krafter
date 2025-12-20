cmake_minimum_required(VERSION 3.20)

project(stb LANGUAGES C)

add_library(stb STATIC)

target_sources(
    stb
    PRIVATE
    include/stb_image.h
    src/stb_image.c
)

target_include_directories(
    stb
    PRIVATE
    include
)
