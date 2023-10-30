cmake_minimum_required(VERSION 3.5)

project(proto-lib LANGUAGES C CXX)

# Внешние зависимости
set(MIN_PROTOBUF_VERSION 3.19.4)
find_package(Protobuf REQUIRED)

# Генерация кода из протофайлов
set(PROTO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/proto)
file(GLOB PROTO_FILES ${PROTO_DIR}/*.proto)
PROTOBUF_GENERATE_CPP(PROTO_LIB_SOURCES PROTO_LIB_HEADERS ${PROTO_FILES})
set_source_files_properties(
    ${PROTO_LIB_SOURCES} ${PROTO_LIB_HEADERS}
    PROPERTIES GENERATED TRUE)

# Создание цели для сборки
add_library(${PROJECT_NAME} ${PROTO_LIB_SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES CMAKE_CXX_STANDARD 14)
target_compile_options(${PROJECT_NAME} PRIVATE "-Wall")

# Экспорт интерфейсов
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROTOBUF_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${Protobuf_LIBRARIES})
