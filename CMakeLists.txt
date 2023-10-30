cmake_minimum_required(VERSION 3.5)

project(ihns LANGUAGES C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/proto-lib)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/comms-lib)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/libzmq)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/cppzmq)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/protobuf)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/apps/ics-app)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/apps/ih-app)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/apps/wcs-app)
