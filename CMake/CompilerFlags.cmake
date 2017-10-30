message(STATUS "Detected Operating System: ${CMAKE_SYSTEM_NAME}")


if(WIN32)
    # Windows (32, 64)
    message(FATAL_ERROR "Windows System not supported, use Visual Studio instead")

elseif("${CMAKE_SYSTEM_NAME}" MATCHES "Darwin")
    # MAC OS
    message(FATAL_ERROR "Apple System not supported")

elseif("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")
    # Linux
    message(STATUS "Set flags and variables for Build '${CMAKE_BUILD_TYPE}'")
    if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Winline")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++11")
    elseif("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++11")
    elseif("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
        set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -g")
        set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -Wall")
        set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -std=c++11")
    elseif("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
        set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} -std=c++11")
    elseif("${CMAKE_BUILD_TYPE}" STREQUAL "")
        message(AUTHOR_WARNING "No Build Type set. You may want to use option -DCMAKE_BUILD_TYPE=Debug")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    else()
        message(FATAL_ERROR "Invalid Build Type. You may want to use option -DCMAKE_BUILD_TYPE=Debug")
    endif()

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
endif()

