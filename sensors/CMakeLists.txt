cmake_minimum_required(VERSION 3.20.0)

project(smartwatch LANGUAGES C)

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
