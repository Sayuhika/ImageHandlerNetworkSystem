cmake_minimum_required(VERSION 3.5)

project(proto-lib LANGUAGES C CXX)

set_property(GLOBAL PROPERTY CXX_STANDARD 14)

# Добавление папки с протофайлами
set(PROTO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/proto)
file(GLOB PROTO_FILES ${PROTO_DIR}/*.proto)

set(PROTOC ${CMAKE_CURRENT_SOURCE_DIR}/../protoc/protoc.exe)

# Генерация кода из протофайлов
set(GENERATED_CODE_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated)
set(PROTO_SRCS ${GENERATED_CODE_DIR}/message.pb.cc)
set(PROTO_HDRS ${GENERATED_CODE_DIR}/message.pb.h)

add_custom_command(
    OUTPUT ${PROTO_SRCS} ${PROTO_HDRS}
    COMMAND ${PROTOC} --proto_path ${PROTO_DIR} ${PROTO_FILES} --cpp_out ${CMAKE_CURRENT_BINARY_DIR}/generated
    DEPENDS ${PROTOC} ${PROTO_FILES}
    )

#protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})

# Создание цели для сборки
add_library(${PROJECT_NAME} ${PROTO_SRCS} ${PROTO_HDRS})

target_include_directories(${PROJECT_NAME} PUBLIC ${protobuf_SOURCE_DIR}/src)

# Линковка с библиотекой protobuf
target_link_libraries(${PROJECT_NAME} protobuf)