cmake_minimum_required(VERSION 3.5)
project(JLParser CXX)

# Release or Debug
if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "Setting build type to 'Debug' as none was specified.")
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif ()

set(CMAKE_CXX_STANDARD 17) # C++11...
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11

# Find nlohmann_json to parse json files
# Add nlohmann_json::nlohmann_json to target_link_libraries
find_package(nlohmann_json)
if (NOT nlohmann_json_FOUND)
    if (${CMAKE_VERSION} VERSION_GREATER "3.24.0")
        CMAKE_POLICY(SET CMP0135 NEW)
    endif()
    include(FetchContent)
    FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
    FetchContent_MakeAvailable(json)
endif()

# Detect PNL
find_package(Pnl REQUIRED)
set(LIBS ${LIBS} ${PNL_LIBRARIES})
include_directories(${PNL_INCLUDE_DIRS})
if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    add_definitions(-DPNL_RANGE_CHECK_OFF)
endif()

add_library(jl_parser INTERFACE)
target_include_directories(jl_parser INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_sources(jl_parser INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/parser.cpp ${CMAKE_CURRENT_SOURCE_DIR}/json_helper.cpp)
target_link_libraries(jl_parser INTERFACE ${PNL_LIBRARIES} nlohmann_json::nlohmann_json)


# Add -lm -ldl if needed
if (UNIX)
    set(LIBS ${LIBS} m dl)
endif (UNIX)

include_directories(${CMAKE_SOURCE_DIR})

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    # Testing the parser
    add_executable(parser-test test_parser.cpp)
    target_link_libraries(parser-test ${LIBS} jl_parser)
endif()
