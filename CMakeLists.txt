cmake_minimum_required(VERSION 2.8.2 FATAL_ERROR)
project(3d-soft-engine)


# -----------------------------------------------------------------------------
# SSE Optimizations
# -----------------------------------------------------------------------------
option(ENGINE_ENABLE_SIMD_SSE4_1 "Enable SSE4.1 optimizations" OFF)

if(ENGINE_ENABLE_SIMD_SSE4_1)
    message("SSE4.1 optimizations allowed")
    add_definitions(-msse4.1)
else()
    message("SSE4.1 optimizations disabled")
endif()


# -----------------------------------------------------------------------------
# Build option
# -----------------------------------------------------------------------------
option(ENGINE_BUILD_MODE_DEBUG "Build on DEBUG mode" ON)
option(ENGINE_BUILD_MODE_RELEASE "Build on RELEASE mode" OFF)
option(ENGINE_BUILD_MODE_PRODUCTION "Build on PRODUCTION mode" OFF)
option(ENGINE_BUILD_MODE_TOOLS "Build on TOOLS mode" OFF)

if(ENGINE_BUILD_MODE_DEBUG)
    message("Build mode: DEBUG")
    add_definitions(-D _DEBUG)
    add_definitions(-g -Wall)
    add_definitions(-D _ASSERTIONS_ENABLED)
elseif(ENGINE_BUILD_MODE_RELEASE)
    message("Build mode: RELEASE")
    add_definitions(-D NDEBUG)
    add_definitions(-g -Wall)
elseif(ENGINE_BUILD_MODE_PRODUCTION)
    message("Build mode: PRODUCTION")
elseif(ENGINE_BUILD_MODE_TOOLS)
    message("Build mode: TOOLS")
endif()


# -----------------------------------------------------------------------------
# Unit Test options
# -----------------------------------------------------------------------------
option(ENGINE_TEST_ENABLE "Build Unit tests" ON)

if(ENGINE_TEST_ENABLE)
    message("Test enabled")
    enable_testing()
    include(CTest)
    add_subdirectory(test)
else()
    message("Test disabled")
endif()


# -----------------------------------------------------------------------------
# Other
# -----------------------------------------------------------------------------
add_subdirectory(src)
