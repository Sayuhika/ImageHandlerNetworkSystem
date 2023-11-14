# WebCamServer

cmake_minimum_required(VERSION 3.5)

project(wcs-app LANGUAGES C CXX)

set(WCS_APP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(WCS_APP_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB WCS_APP_HEADERS ${WCS_APP_INCLUDE_DIR}/*.hpp)
file(GLOB WCS_APP_SOURCE ${WCS_APP_SOURCE_DIR}/*.cpp)

# Создание цели для сборки
add_executable(${PROJECT_NAME} ${WCS_APP_HEADERS} ${WCS_APP_SOURCE})

# Линковка с библиотекой protobuf
target_link_libraries(${PROJECT_NAME} comms-lib opencv-lib)