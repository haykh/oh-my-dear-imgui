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

set(omdi_BUILD_EXAMPLES
    "OFF"
    CACHE BOOL "Build omdi examples")

if(${omdi_BUILD_EXAMPLES})
  message(STATUS "Building examples")
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples)
else()
  message(STATUS "Skipping examples")
endif()

include(CMakePackageConfigHelpers)

set(INSTALL_CONFIGDIR lib/cmake/oh-my-dear-imgui)

configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/oh-my-dear-imguiConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/oh-my-dear-imguiConfig.cmake
  INSTALL_DESTINATION ${INSTALL_CONFIGDIR})

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/oh-my-dear-imguiConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion)

install(
  EXPORT oh-my-dear-imguiTargets
  NAMESPACE oh-my-dear-imgui::
  FILE oh-my-dear-imguiTargets.cmake
  DESTINATION ${INSTALL_CONFIGDIR})

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/oh-my-dear-imguiConfig.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/oh-my-dear-imguiConfigVersion.cmake
        DESTINATION ${INSTALL_CONFIGDIR})
