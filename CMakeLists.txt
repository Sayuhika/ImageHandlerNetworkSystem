cmake_minimum_required(VERSION 3.12)

set_property(GLOBAL PROPERTY CXX_STANDARD 17)

message ("Hello")
project(ihns LANGUAGES C CXX)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
endif (MSVC)

add_subdirectory(libs/proto-lib)
add_subdirectory(libs/comms-lib)

# add_subdirectory(apps/ics-app)
# add_subdirectory(apps/ih-app)
# add_subdirectory(apps/wcs-app)
