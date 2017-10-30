message(STATUS "Detected Operating System: ${CMAKE_SYSTEM_NAME}")


if(WIN32)
    # Windows (32, 64)
    # TODO
    message(FATAL_ERROR "Windows System is not supported yet")
    exit()

elseif("${CMAKE_SYSTEM_NAME}" MATCHES "Darwin")
    # MAC OS
    message(FATAL_ERROR "Apple System not supported")
    exit()

elseif("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")
    # Linux
    message(STATUS "Set flags and variables for Build '${CMAKE_BUILD_TYPE}'")
    if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
        set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -g")
        set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
        set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -Winline")
    elseif("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
        set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_RELEASE} -g")
        set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_RELEASE} -Wall")
    elseif("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
        set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -g")
        set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -Wall")
    elseif("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
        # Nothing to add
    else()
        message(AUTHOR_WARNING "No Build Type set. You may want to use cmake -DCMAKE_BUILD_TYPE=Debug")
    endif()
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${CMAKE_CXX_FLAGS_DEBUG}")
    set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
    if(ENGINE_ENABLE_SSE)
        include("${CMAKE_SOURCE_DIR}/CMake/Macros/MacroFindSSE.cmake")
        FindSSE()
        add_definitions(-msse4.1)
    else()
        message(STATUS "SSE Disabled")
    endif()

else()
    # Unknown OS
    message(FATAL_ERROR "Unsupported operating system")
    exit()
endif()

