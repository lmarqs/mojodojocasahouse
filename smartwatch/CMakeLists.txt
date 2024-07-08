cmake_minimum_required(VERSION 3.20.0)

project(smartwatch LANGUAGES C)

# Allow lvgl to include lv_conf.h and lv_drv_conf.h files
include_directories(${CMAKE_SOURCE_DIR})

if("$ENV{LV_DRIVER}" STREQUAL "sdl")
  add_compile_definitions(USE_SDL=1)
  add_library(ports ${CMAKE_SOURCE_DIR}/ports/sdl/hal.c)
  target_link_libraries(ports PUBLIC SDL2)
elseif("$ENV{LV_DRIVER}" STREQUAL "fbdev")
  add_compile_definitions(USE_FBDEV=1)
  add_library(ports ${CMAKE_SOURCE_DIR}/ports/fbdev/hal.c)
else()
  message( FATAL_ERROR "You must specify LV_DRIVER=(sdl|fbdev)" )
endif()

target_include_directories(ports PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ports/include)
set_target_properties(
  ports
  PROPERTIES OUTPUT_NAME ports
             ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
             LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
             RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

add_subdirectory(lvgl ${CMAKE_SOURCE_DIR}/lvgl)
add_subdirectory(lv_drivers ${CMAKE_SOURCE_DIR}/lv_drivers)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

FILE(GLOB_RECURSE SOURCES ./src/*.c)
add_executable(smartwatch ./main.c ${SOURCES})

target_include_directories(smartwatch
  PRIVATE src/generated src/custom src/generated/guider_customer_fonts src/generated/guider_fonts src/generated/images
)

target_link_libraries(smartwatch
  PUBLIC lvgl
  PRIVATE ports
)

target_link_libraries(ports
  PUBLIC lv_drivers
)

install(TARGETS smartwatch RUNTIME DESTINATION bin)

install(FILES ${CMAKE_BINARY_DIR}/bin/smartwatch
  DESTINATION /bin
  PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE
  COMPONENT smartwatch
)

install(FILES ${CMAKE_BINARY_DIR}/etc/systemd/system/smartwatch.service
  DESTINATION /etc/systemd/system
  PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
  COMPONENT smartwatch
)
