cmake_minimum_required(VERSION 2.8.11)

project(metaheuristic)

set(PROJECT_SRC_DIR ${PROJECT_SOURCE_DIR})

configure_file (
  "${PROJECT_SOURCE_DIR}/Config.h.in"
  "${PROJECT_BINARY_DIR}/Config.h")

include_directories("${PROJECT_BINARY_DIR}")

SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake" ${CMAKE_MODULE_PATH})
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(src)
