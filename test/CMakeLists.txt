enable_testing()


# -----------------------------------------------------------------------------
# GoogleTest framework
# -----------------------------------------------------------------------------
# See: https://github.com/google/googletest/tree/master/googletest

configure_file(
    "${CMAKE_SOURCE_DIR}/CMake/GoogleTest.cmake"
    "${CMAKE_BINARY_DIR}/googletest-download/CMakeLists.txt")

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download")
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download")
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory("${dependency_dir}/googletest"
                 "${CMAKE_BINARY_DIR}/googletest-build"
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
endif()


# -----------------------------------------------------------------------------
# Executables
# -----------------------------------------------------------------------------
include_directories("${CMAKE_SOURCE_DIR}/include")
file(GLOB_RECURSE srcTestFiles "${CMAKE_SOURCE_DIR}/test/*.cpp")
add_executable(tests ${srcTestFiles})
target_link_libraries(tests gtest)
add_custom_target(runAllTests tests)

# Individual tests
function(add_test_executable target_name srcfile)
    add_executable(${target_name} runAllTests.cpp ${srcfile})
    target_link_libraries(${target_name} gtest)
    add_test(NAME ${target_name} COMMAND ${target_name})
    add_custom_target("run${target_name}" ${target_name})
endfunction()

add_test_executable("test_VectF2"           "math/VectF2_Test.cpp")
add_test_executable("test_VectF3"           "math/VectF3_Test.cpp")
add_test_executable("test_VectF4"           "math/VectF4_Test.cpp")
add_test_executable("test_MatrixF4"         "math/MatrixF4_Test.cpp")
add_test_executable("test_MatrixTransform"  "math/MatrixTransform_Test.cpp")


