include_directories("${CMAKE_SOURCE_DIR}/include")
file(GLOB_RECURSE srcFiles *.cpp)

add_executable(3d-soft-engine ${srcFiles})
add_custom_target(runengine 3d-soft-engine)

target_link_libraries(3d-soft-engine
    ${SDL2_LIBRARY}
    ${SDL2MAIN_LIBRARY})
