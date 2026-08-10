cmake_minimum_required(VERSION 3.15...4.4)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

project(AudioVisualizer)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


