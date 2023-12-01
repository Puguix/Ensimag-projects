cmake_minimum_required(VERSION 3.10)

project(MonteCarlo)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)

# Detect PNL
find_package(Pnl REQUIRED)
set(LIBS ${LIBS} ${PNL_LIBRARIES})
include_directories(${PNL_INCLUDE_DIRS})

# Add executable
add_executable(tp1 tp1/tp1.cpp)
target_link_libraries(tp1
    ${LIBS}
)

add_executable(tp2-1 tp2/tp2-1.cpp)
target_link_libraries(tp2-1
    ${LIBS}
)

add_executable(tp2-2 tp2/tp2-partie2/BSCall.cpp tp2/tp2-partie2/MonteCarlo.cpp tp2/tp2-partie2/main.cpp)
target_link_libraries(tp2-2
    ${LIBS}
)

add_executable(tp3 tp3/BSBarrier.cpp tp3/MonteCarlo.cpp tp3/main.cpp)
target_link_libraries(tp3
    ${LIBS}
)

add_executable(tp4 tp4/main.cpp)
target_link_libraries(tp4
    ${LIBS}
)

add_executable(tp5 tp5/main.cpp tp5/BSCall.cpp tp5/MonteCarlo.cpp)
target_link_libraries(tp5
    ${LIBS}
)

add_executable(tp6 tp6/main.cpp tp6/BSScheme.cpp)
target_link_libraries(tp6
    ${LIBS}
)

add_executable(tp7-1 tp7/AsianOption.cpp tp7/Heston.cpp tp7/mcpricer.cpp tp7/Model.cpp tp7/MonteCarlo.cpp tp7/MultiLevelMonteCarlo.cpp)
target_link_libraries(tp7-1
    ${LIBS}
)

add_executable(tp7-2 tp7/AsianOption.cpp tp7/Heston.cpp tp7/mlmcpricer.cpp tp7/Model.cpp tp7/MonteCarlo.cpp tp7/MultiLevelMonteCarlo.cpp)
target_link_libraries(tp7-2
    ${LIBS}
)

add_executable(tp8 tp8/AsianOption.cpp tp8/BlackScholes.cpp tp8/main.cpp tp8/MonteCarlo.cpp)
target_link_libraries(tp8
    ${LIBS}
)