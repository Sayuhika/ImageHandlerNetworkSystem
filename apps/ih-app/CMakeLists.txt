# ImageHandler
cmake_minimum_required(VERSION 3.5)

project(ih-app LANGUAGES C CXX)

set(IH_APP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(IH_APP_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB IH_APP_HEADERS ${IH_APP_INCLUDE_DIR}/*.hpp)
file(GLOB IH_APP_SOURCE ${IH_APP_SOURCE_DIR}/*.cpp)

# Создание цели для сборки
add_executable(${PROJECT_NAME} ${IH_APP_HEADERS} ${IH_APP_SOURCE})

# Линковка с библиотекой protobuf
target_link_libraries(${PROJECT_NAME} comms-lib)