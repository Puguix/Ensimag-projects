cmake_minimum_required(VERSION 3.5.1)

project(FXHedging CXX)

# Release or Debug
if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "Setting build type to 'Debug' as none was specified.")
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif ()

# Find Pnl
find_package(Pnl REQUIRED)
set(LIBS ${LIBS} ${PNL_LIBRARIES})
include_directories(${PNL_INCLUDE_DIRS})
if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    add_definitions(-DPNL_RANGE_CHECK_OFF)
endif()

# Find nlohmann_json to parse json files
# Add nlohmann_json::nlohmann_json to target_link_libraries
find_package(nlohmann_json REQUIRED)

set(fxhedging_hdrs Tools/json_reader.hpp)
add_library(fx_hedging Tools/json_reader.cpp ${fxhedging_hdrs})
target_link_libraries(fx_hedging ${PNL_LIBRARIES} nlohmann_json::nlohmann_json)

# add_executable(test_fx_hedging test_fx_hedging.cpp)
# target_link_libraries(test_fx_hedging fx_hedging)
# pnl_add_postbuild(test_fx_hedging)

add_executable(test_json_reader Tools/json_reader.cpp)
target_link_libraries(test_json_reader ${PNL_LIBRARIES} nlohmann_json::nlohmann_json)
pnl_add_postbuild(test_json_reader)


#add_executable(my_json_reader ./Tools/TestParser.cpp ./Tools/Parser.cpp ./Tools/Parser.hpp json_reader.cpp)
#target_link_libraries(my_json_reader
#                      ${PNL_LIBRARIES}
#                      nlohmann_json::nlohmann_json)
#pnl_add_postbuild(my_json_reader)

file(GLOB PARSER "Tools/*")
file(GLOB OPTION "Options/*")
file(GLOB ORACLE "Oracle/*")
file(GLOB ASSET "Assets/*")
file(GLOB TIMEHANDLER "TimeHandler/*")

add_executable(hedging ${PARSER} ${OPTION} ${ORACLE}  ${ASSET} ${TIMEHANDLER} GlobalModel.cpp GlobalModel.hpp Hedger.cpp
               Portfolio.cpp Portfolio.hpp MonteCarlo.hpp MonteCarlo.cpp)
target_link_libraries(hedging
        ${PNL_LIBRARIES}
        nlohmann_json::nlohmann_json)
pnl_add_postbuild(hedging)
