cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME oh-my-dear-imgui)

project(
  ${PROJECT_NAME}
  VERSION 1.2.0
  DESCRIPTION "Wrapper library for ImGui based applications")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/dependencies.cmake)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/omdi)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples)
