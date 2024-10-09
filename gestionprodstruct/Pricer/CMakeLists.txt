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

#set(fxhedging_hdrs Tools/json_reader.hpp)
#add_library(fx_hedging Tools/json_reader.cpp ${fxhedging_hdrs})
#target_link_libraries(fx_hedging ${PNL_LIBRARIES} nlohmann_json::nlohmann_json)

# add_executable(test_fx_hedging test_fx_hedging.cpp)
# target_link_libraries(test_fx_hedging fx_hedging)
# pnl_add_postbuild(test_fx_hedging)

#add_executable(test_json_reader Tools/json_reader.cpp)
#target_link_libraries(test_json_reader ${PNL_LIBRARIES} nlohmann_json::nlohmann_json)
#pnl_add_postbuild(test_json_reader)


file(GLOB PRODUIT "Produit/*")
file(GLOB MONTECARLO "MonteCarlo/*")
file(GLOB TOOLS "Tools/*")
file(GLOB RISKYASSETS "RiskyAssets/*")
file(GLOB TIMEHANDLER "TimeHandler/*")

# Find Protobuf installation
# Must use the CONFIG mode
set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)
find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${Protobuf_VERSION}")

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_REFLECTION gRPC::grpc++_reflection)
set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)
# Find gRPC installation
# Looks for gRPCConfig.cmake file installed by gRPC's cmake installation.
find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

set(_GRPC_GRPCPP gRPC::grpc++)
set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)

# Proto file
get_filename_component(pricer_proto "GrpcPricer.proto" ABSOLUTE)
get_filename_component(pricer_proto_path "${pricer_proto}" PATH)

message(STATUS "Proto file path: ${pricer_proto_path}")
message(STATUS "GRPC plugin executable: ${_GRPC_CPP_PLUGIN_EXECUTABLE}")

# Generated sources
# Generated sources
set(pricer_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/GrpcPricer.pb.cc")
set(pricer_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/GrpcPricer.pb.h")
set(pricer_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/GrpcPricer.grpc.pb.cc")
set(pricer_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/GrpcPricer.grpc.pb.h")
add_custom_command(
    OUTPUT "${pricer_proto_srcs}" "${pricer_proto_hdrs}" "${pricer_grpc_srcs}" "${pricer_grpc_hdrs}"
    COMMAND ${_PROTOBUF_PROTOC}
    ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
      --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
      -I "${pricer_proto_path}"
      --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
      "${pricer_proto}"
    DEPENDS "${pricer_proto}"
)

# pricer_grpc_proto
add_library(pricer_grpc_proto
    ${pricer_grpc_srcs}
    ${pricer_grpc_hdrs}
    ${pricer_proto_srcs}
    ${pricer_proto_hdrs}
)

target_link_libraries(pricer_grpc_proto
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF}
)

# Assurez-vous d'inclure également les fichiers générés dans la liste des sources
target_sources(pricer_grpc_proto PRIVATE
    ${pricer_grpc_srcs}
    ${pricer_grpc_hdrs}
    ${pricer_proto_srcs}
    ${pricer_proto_hdrs}
)

find_package(nlohmann_json REQUIRED)
include_directories("${CMAKE_CURRENT_BINARY_DIR}")


add_executable(pricing_server ${PRODUIT} ${MONTECARLO} ${TOOLS} ${RISKYASSETS} ${TIMEHANDLER} Portfolio.cpp Portfolio.hpp Pricer.hpp pricing_server.cpp
        Pricer.cpp)
target_link_libraries(pricing_server
    pricer_grpc_proto
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF}
    ${PNL_LIBRARIES}
    nlohmann_json::nlohmann_json
)
pnl_add_postbuild(pricing_server)

add_executable(priceAndDelta ${PRODUIT} ${MONTECARLO} ${TOOLS} ${RISKYASSETS} ${TIMEHANDLER} Pricer.hpp testPrice&Delta.cpp
        Pricer.cpp)
target_link_libraries(priceAndDelta
        ${PNL_LIBRARIES}
        nlohmann_json::nlohmann_json)
pnl_add_postbuild(priceAndDelta)


