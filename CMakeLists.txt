# Projects Settings
cmake_minimum_required (VERSION 3.14)
project (myapp)

# The main executable
add_executable(myapp
  src/main.c
  lib/nanovg/src/nanovg.c
)

include_directories(
  lib/nanovg/src
  include
)


target_compile_options(myapp PRIVATE -Wall)

add_definitions(-DGLEW_STATIC)
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
add_subdirectory(lib/glew EXCLUDE_FROM_ALL)
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)

target_link_libraries(myapp
  PRIVATE glfw
  PRIVATE libglew_static
  PRIVATE glm
)

