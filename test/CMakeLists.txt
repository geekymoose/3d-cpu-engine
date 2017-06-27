#
# CMake to build tests
# Each test file creates a specific executable
#
# EXECUTE TESTS
# `make test` to run them all
# `./test/x_test` to run only the specific one (With GoogleTest syntax)
#


# -----------------------------------------------------------------------------
# Functions
# -----------------------------------------------------------------------------
function (add_test_executable target_name srcfile)
    add_executable(${target_name} runAllTests.cpp ${srcfile})
    target_link_libraries(${target_name} gtest)
    add_test(NAME ${target_name} COMMAND ${target_name})
endfunction()


# -----------------------------------------------------------------------------
# Build Google Test framework
# -----------------------------------------------------------------------------

# Clone GoogleTest lib and build it
# From https://github.com/google/googletest/blob/master/googletest/README.md
configure_file(CMakeLists.txt.in ${CMAKE_BINARY_DIR}/googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result} / ${CMAKE_BINARY_DIR}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

# GoogleTest lib is now cloned and built


# -----------------------------------------------------------------------------
# Create all test executables
# -----------------------------------------------------------------------------
include_directories("${CMAKE_SOURCE_DIR}/src")

add_test_executable("runMatrixF4_tests" math/MatrixF4_Test.cpp)
add_test_executable("runVectF4_tests" math/VectF4_Test.cpp)

