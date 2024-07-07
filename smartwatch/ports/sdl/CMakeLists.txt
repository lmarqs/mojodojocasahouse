cmake_minimum_required(VERSION 3.20.0)

# project(ports LANGUAGES C)

if("$ENV{LV_DRIVER}" STREQUAL "sdl")
  add_compile_definitions(USE_SDL=1)
  add_library(ports ./sdl/hal.c)
  target_link_libraries(ports PUBLIC SDL2)
  target_link_libraries(ports PRIVATE SDL2)
elseif("$ENV{LV_DRIVER}" STREQUAL "fbdev")
  add_compile_definitions(USE_FBDEV=1)
  add_library(ports ./fbdev/hal.c)
  target_link_libraries(ports PUBLIC lvgl lv_drivers)
endif()

target_include_directories(ports PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(
  ports
  PROPERTIES OUTPUT_NAME ports
             ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
             LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
             RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
