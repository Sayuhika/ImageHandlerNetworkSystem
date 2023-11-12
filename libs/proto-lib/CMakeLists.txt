cmake_minimum_required(VERSION 3.5)

project(proto-lib LANGUAGES C CXX)

set_property(GLOBAL PROPERTY CXX_STANDARD 14)

set(Protobuf_DIR${CMAKE_CURRENT_SOURCE_DIR}/libs/protobuf)
# Установка пути к файлам protobuf
set(PROTOBUF_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/libs/protobuf)
list(APPEND CMAKE_PREFIX_PATH ${PROTOBUF_ROOT})
find_package(Protobuf REQUIRED)

# Генерация *.pb.h и *.pb.cc файлов из протофайлов
set(PROTO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/proto)
file(GLOB PROTO_FILES ${PROTO_DIR}/*.proto)
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})

# Добавление сгенерированных файлов в цель сборки
add_library(${PROJECT_NAME} ${PROTO_SRCS} ${PROTO_HDRS})

target_include_directories(${PROJECT_NAME} PUBLIC ${protobuf_SOURCE_DIR}/src)

# Линковка с библиотекой protobuf
target_link_libraries(${PROJECT_NAME} PUBLIC protobuf::libprotobuf)