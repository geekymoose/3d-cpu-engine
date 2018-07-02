cmake_minimum_required(VERSION 2.8.2 FATAL_ERROR)
project(3d-cpu-engine)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
    message(FATAL_ERROR "in-source build not allowed. Use another directory.")
endif()


# ------------------------------------------------------------------------------
# Compiler Flags
# ------------------------------------------------------------------------------
message(STATUS "Detected Operating System: ${CMAKE_SYSTEM_NAME}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "No BUILD_TYPE set: uses Release")
    message(STATUS "Available build types: Debug Release RelWithDebInfo MinSizeRel")
    set(CMAKE_BUILD_TYPE Release)
endif()


# ------------------------------------------------------------------------------
# Dependencies
# ------------------------------------------------------------------------------
set(dependency_dir "${CMAKE_SOURCE_DIR}/dependencies/")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake/")
find_package(SDL2 REQUIRED)


# ------------------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------------------
option(build_tests "Build unit tests" ON)
if(build_tests)
    message(STATUS "Tests enabled")
    add_subdirectory(test)
endif()


# ------------------------------------------------------------------------------
# Engine Executable
# ------------------------------------------------------------------------------
add_subdirectory(src)


