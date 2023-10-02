cmake_minimum_required(VERSION 3.10)

project(MonteCarlo)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)

# Detect PNL
find_package(Pnl REQUIRED)
set(LIBS ${LIBS} ${PNL_LIBRARIES})
include_directories(${PNL_INCLUDE_DIRS})

# Add executable
add_executable(tp1 tp1.cpp)
target_link_libraries(tp1
    ${LIBS}
)