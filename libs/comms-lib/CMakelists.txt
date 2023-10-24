cmake_minimum_required(VERSION 3.5)

project(comms-lib LANGUAGES C CXX)

set(COMMS_LIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(COMMS_LIB_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB COMMS_LIB_HEADERS ${COMMS_LIB_INCLUDE_DIR}/*.hpp)
file(GLOB COMMS_LIB_SOURCE ${COMMS_LIB_SOURCE_DIR}/*.cpp)

# Создание цели для сборки
add_library(${PROJECT_NAME} ${COMMS_LIB_HEADERS} ${COMMS_LIB_SOURCE})

# Линковка с библиотекой protobuf
target_link_libraries(${PROJECT_NAME} zeromq cppzmq proto-lib)