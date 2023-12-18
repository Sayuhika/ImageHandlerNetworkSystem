# ImageCollectorServer

cmake_minimum_required(VERSION 3.5)

project(ics-app LANGUAGES C CXX)

set(ICS_APP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(ICS_APP_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(OpenCV_DIR C:/OpenCV-4.8.0/opencv/build)
find_package(OpenCV REQUIRED)


file(GLOB ICS_APP_HEADERS ${ICS_APP_INCLUDE_DIR}/*.hpp)
file(GLOB ICS_APP_SOURCE ${ICS_APP_SOURCE_DIR}/*.cpp)

# Создание цели для сборки
add_executable(${PROJECT_NAME} ${ICS_APP_HEADERS} ${ICS_APP_SOURCE})

# Линковка с библиотекой protobuf
target_link_libraries(${PROJECT_NAME} comms-lib ${OpenCV_LIBS})