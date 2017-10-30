cmake_minimum_required(VERSION 2.8.2 FATAL_ERROR)
project(3d-soft-engine)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
    message(FATAL_ERROR "in-source build not allowed. Use another directory.")
endif()

include(CMake/CompilerFlags.cmake)
include(CMake/Dependencies.cmake)
include(CMake/Tests.cmake)

add_subdirectory(src)

#TMP, copy resources
file(COPY resources DESTINATION "${CMAKE_BINARY_DIR}/src")
