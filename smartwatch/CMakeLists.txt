# SPDX-License-Identifier: MIT
cmake_minimum_required(VERSION 3.20.0)

project(smartwatch LANGUAGES C)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_compile_definitions(USE_SDL=1)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

FILE(GLOB_RECURSE SOURCES ./src/custom/*.c ./src/generated/*.c ./main.c)
add_executable(smartwatch ${SOURCES})
target_include_directories(smartwatch PRIVATE src/generated src/custom src/generated/guider_customer_fonts src/generated/guider_fonts src/generated/images)

include_directories(${CMAKE_SOURCE_DIR})
add_subdirectory(lvgl ${CMAKE_SOURCE_DIR}/lvgl)
add_subdirectory(lv_drivers ${CMAKE_SOURCE_DIR}/lv_drivers)

target_link_libraries(smartwatch PUBLIC lvgl lv_drivers ${SDL2_LIBRARIES})
