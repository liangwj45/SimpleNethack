# project
project(SimpleNethack)

# cmake minimum version
cmake_minimum_required(VERSION 3.9.4)

# target
set(TARGET Nethack)

# header directories
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

# source files
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc")

# executable
add_executable(${TARGET} ${SOURCE_FILES})
set_target_properties(${TARGET} 
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY
    "${PROJECT_SOURCE_DIR}/bin"
  CXX_STANDARD 14
)