cmake_minimum_required(VERSION 2.8.2)
project(3d-soft-engine)

option(ENGINE_TEST_ENABLE "Build Unit tests" ON)

# Build and start tests
if(ENGINE_TEST_ENABLE)
    message("Test enabled")
    enable_testing()
    include(CTest)
    add_subdirectory(test)
endif()

add_subdirectory(src)
