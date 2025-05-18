cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME imgui-boilerplate)

project(
  ${PROJECT_NAME}
  VERSION 1.0.0
  DESCRIPTION "Boilerplate for ImGui applications")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/dependencies.cmake)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
