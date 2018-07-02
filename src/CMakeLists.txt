include_directories("${CMAKE_SOURCE_DIR}/include")
file(GLOB_RECURSE srcFiles *.cpp)

add_executable(engine ${srcFiles})
add_custom_target(runEngine engine)
add_dependencies(runEngine copyResources)

target_link_libraries(engine
    ${SDL2_LIBRARY}
    ${SDL2MAIN_LIBRARY})


# Copy resources folder
set(RESOURCES_SRC "${CMAKE_SOURCE_DIR}/resources/")
set(RESOURCES_BIN "${CMAKE_BINARY_DIR}/src/resources/")
add_custom_command(
    OUTPUT "${RESOURCES_BIN}"
    DEPENDS "${RESOURCES_SRC}"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${RESOURCES_SRC}" "${RESOURCES_BIN}"
)
add_custom_target(copyResources ALL DEPENDS "${RESOURCES_BIN}")


