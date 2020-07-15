cmake_minimum_required(VERSION 3.16.3)
project(rogue)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

# Note: only works for GCC
add_compile_options(-Wfatal-errors)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
file(COPY config DESTINATION ${CMAKE_BINARY_DIR})

include_directories(include/game)
include_directories(include/game/actions)
include_directories(include/game/items)
include_directories(include/graphics)
include_directories(include/input)
include_directories(include/map)
include_directories(include/utils)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/googletest)