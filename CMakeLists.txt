cmake_minimum_required(VERSION 3.22)
project(
    func-sig-interface
    DESCRIPTION "Header only library for a type erasure function based type"
    LANGUAGES CXX
)

option(BUILD_TESTS "Toggle and run unit tests" OFF)

set(CMAKE_COLOR_DIAGNOSTICS ON)

include("${PROJECT_SOURCE_DIR}/cmake/compile_options.cmake")
include("${PROJECT_SOURCE_DIR}/cmake/package.cmake")

if (CCACHE_FOUND)
    message(STATUS "Using ccache ...")
endif()

add_subdirectory(src)
add_subdirectory(tests)
