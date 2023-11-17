cmake_minimum_required(VERSION 3.5)

project(worker-lib LANGUAGES C CXX)

set(WORKER_LIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(WORKER_LIB_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB WORKER_LIB_HEADERS ${WORKER_LIB_INCLUDE_DIR}/*.hpp)
file(GLOB WORKER_LIB_SOURCE ${WORKER_LIB_SOURCE_DIR}/*.cpp)

add_library(${PROJECT_NAME} ${WORKER_LIB_HEADERS} ${WORKER_LIB_SOURCE} )

target_link_libraries(${PROJECT_NAME} opencv-lib)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)

# Присоединение bitsery
target_include_directories( ${PROJECT_NAME} PUBLIC ${BITSERY_INCLUDE_DIR})

# Экспорт описания протокола
target_include_directories(${PROJECT_NAME} 
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)