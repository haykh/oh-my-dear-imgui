# cmake-lint: disable=C0103,C0111,E1120,R0913,R0915

if(NOT WIN32)
  string(ASCII 27 Esc)
  set(ColorReset "${Esc}[m")
  set(ColourBold "${Esc}[1m")
  set(Underline "${Esc}[4m")
  set(Red "${Esc}[31m")
  set(Green "${Esc}[32m")
  set(Yellow "${Esc}[33m")
  set(Blue "${Esc}[34m")
  set(Magenta "${Esc}[35m")
  set(Cyan "${Esc}[36m")
  set(White "${Esc}[37m")
  set(BoldRed "${Esc}[1;31m")
  set(BoldGreen "${Esc}[1;32m")
  set(BoldYellow "${Esc}[1;33m")
  set(BoldBlue "${Esc}[1;34m")
  set(BoldMagenta "${Esc}[1;35m")
  set(BoldCyan "${Esc}[1;36m")
  set(BoldWhite "${Esc}[1;37m")
  set(DarkGray "${Esc}[1;90m")
  set(Dim "${Esc}[2m")
  set(StrikeBegin "${Esc}[9m")
  set(StrikeEnd "${Esc}[0m")
endif()

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

set(LIBS)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

set(plog_REPOSITORY "https://github.com/SergiusTheBest/plog.git")
set(plog_TAG "master")

set(toml11_REPOSITORY "https://github.com/ToruNiina/toml11.git")
set(toml11_TAG "v4.4.0")

set(stb_REPOSITORY "https://github.com/nothings/stb.git")
set(stb_TAG "master")

set(imgui_REPOSITORY "https://github.com/ocornut/imgui.git")
set(imgui_TAG "docking")

set(ImGuiFileDialog_REPOSITORY "https://github.com/aiekick/ImGuiFileDialog.git")
set(ImGuiFileDialog_TAG "master")

set(implot_REPOSITORY "https://github.com/epezent/implot.git")
set(implot_TAG "master")

# -----------------------------------------------------------------------------
# dir_non_empty
#
# Description:
#
# * Check if a directory is non-empty
#
# Arguments:
#
# * dir (string) - The directory to check
#
# Returns:
#
# * is_non_empty (bool) - Whether the directory is non-empty
#
# Notes:
#
# * This function checks if the directory exists and contains at least one file
#   or subdirectory
#
# -----------------------------------------------------------------------------
function(dir_non_empty dir is_non_empty)
  if(EXISTS "${dir}" AND IS_DIRECTORY "${dir}")
    file(GLOB files "${dir}/*")
    if(files)
      set(${is_non_empty}
          TRUE
          PARENT_SCOPE)
    else()
      set(${is_non_empty}
          FALSE
          PARENT_SCOPE)
    endif()
  else()
    set(${is_non_empty}
        FALSE
        PARENT_SCOPE)
  endif()
endfunction()

# -----------------------------------------------------------------------------
# fetch_library
#
# Description:
#
# * Fetch a library using different methods
#
# * If the library is already present in the extern directory, nothing is done
#
# Arguments:
#
# * name (string) - The name of the library to fetch
#
# * method (string) - The method to use for fetching the library
#
# Sets:
#
# * ${name}_SOURCE_DIR (string) - The source directory of the library
#
# * ${name}_AS_SUBMODULE (bool) - Whether the library is being used as a
#   submodule
#
# * ${name}_FETCHED (bool) - Whether the library is being fetched
#
# * ${name}_CLONED (bool) - Whether the library is being cloned
#
# Notes:
#
# * method can be "FETCH" or "CLONE"
#
# * "FETCH" uses FetchContent to fetch the library
#
# * "CLONE" uses git clone to fetch the library
# -----------------------------------------------------------------------------
function(fetch_library name method)
  # if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/extern/${name}"
  dir_non_empty("${CMAKE_CURRENT_SOURCE_DIR}/extern/${name}" is_non_empty)
  if(is_non_empty)
    set(${name}_AS_SUBMODULE TRUE)
    set(${name}_FETCHED FALSE)
    set(${name}_CLONED FALSE)

    message(STATUS "${Green}${name} is being used as a submodule${ColorReset}")
    set(${name}_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/extern/${name}")
  else()
    set(${name}_AS_SUBMODULE FALSE)
    if("${method}" STREQUAL "FETCH")
      message(STATUS "${Blue}Fetching ${name} from git${ColorReset}")
      FetchContent_Declare(
        ${name}
        GIT_REPOSITORY ${${name}_REPOSITORY}
        GIT_TAG ${${name}_TAG}
        GIT_PROGRESS TRUE)
      set(${name}_SOURCE_DIR ${CMAKE_BINARY_DIR}/_deps/${name}-src)

      set(${name}_FETCHED TRUE)
      set(${name}_CLONED FALSE)
    elseif("${method}" STREQUAL "CLONE")
      message(STATUS "${Blue}Cloning ${name} from git${ColorReset}")
      set(${name}_SOURCE_DIR ${CMAKE_BINARY_DIR}/_deps/${name}-src)
      if(NOT EXISTS ${${name}_SOURCE_DIR})
        execute_process(
          COMMAND git clone --branch ${${name}_TAG} ${${name}_REPOSITORY}
                  ${${name}_SOURCE_DIR} RESULT_VARIABLE clone_result)
        if(NOT clone_result EQUAL 0)
          message(FATAL_ERROR "Failed to clone ${name}")
        endif()
      endif()

      set(${name}_FETCHED FALSE)
      set(${name}_CLONED TRUE)
    endif()
  endif()

  set(${name}_AS_SUBMODULE
      ${${name}_AS_SUBMODULE}
      CACHE BOOL "${name} is being used as a submodule")
  set(${name}_FETCHED
      ${${name}_FETCHED}
      CACHE BOOL "${name} is being fetched")
  set(${name}_CLONED
      ${${name}_CLONED}
      CACHE BOOL "${name} is being cloned")
  set(${name}_SOURCE_DIR
      ${${name}_SOURCE_DIR}
      CACHE STRING "${name} source directory")
endfunction()

# -----------------------------------------------------------------------------
# fullpath_files
#
# Description:
#
# * Get the full path of the files in the specified directory
#
# Arguments:
#
# * files (list) - The list of files to get the full path for
#
# * path (string) - The path to the directory
#
# Returns:
#
# * fullpath_files (list) - The list of full paths of the files
# -----------------------------------------------------------------------------
function(files_to_fullpath files path fullpath_files)
  set(temp "")
  foreach(file ${files})
    list(APPEND temp "${path}/${file}")
  endforeach()
  set(${fullpath_files}
      "${temp}"
      PARENT_SCOPE)
endfunction()

# -----------------------------------------------------------------------------
# build_library
#
# Description:
#
# * Build the pre-fetched library using specified source files
#
# * If no source files provided, it will use the default
#   FetchContent_MakeAvailable behavior (if library is used as a submodule), or
#   it will GLOB_RECURSE the `src/` directory
#
# Arguments:
#
# * name (string) - The name of the library to fetch
#
# * src_files (list) - The source files to use for building the library
#
# * inc_dirs (list) - The include directories to use for building the library
#
# * links (list) - The libraries to link against
#
# * options (list) - The compile-time options to use for building the library
#
# * altname (string) - The alternative name of the library to use for
# -----------------------------------------------------------------------------
function(
  build_library
  name
  src_files
  inc_dirs
  links
  options
  altname)
  set(full_src_files "")
  if(${${name}_AS_SUBMODULE} OR ${${name}_CLONED})
    if("${src_files}" STREQUAL "")
      file(GLOB_RECURSE full_src_files "${${name}_SOURCE_DIR}/src/*.cpp")
    else()
      set(source_dir "${${name}_SOURCE_DIR}")
      files_to_fullpath("${src_files}" "${source_dir}" full_src_files)
    endif()
  elseif(${${name}_FETCHED})
    FetchContent_MakeAvailable(${name})
    if(NOT "${src_files}" STREQUAL "")
      set(source_dir "${${name}_SOURCE_DIR}")
      files_to_fullpath("${src_files}" "${source_dir}" full_src_files)
    elseif(NOT "${altname}" STREQUAL "")
      set(LIBS
          "${LIBS};${altname}"
          PARENT_SCOPE)
    endif()
  else()
    message(
      FATAL_ERROR "Library ${name} not fetched/cloned and is not a submodule")
  endif()
  if(NOT "${full_src_files}" STREQUAL "")
    add_library("${name}" "${full_src_files}")
    if(NOT "${inc_dirs}" STREQUAL "")
      foreach(dir ${inc_dirs})
        target_include_directories("${name}" PUBLIC "$<BUILD_INTERFACE:${dir}>")
      endforeach()
    endif()
    if(NOT "${links}" STREQUAL "")
      target_link_libraries("${name}" "${links}")
    endif()
    if(NOT "${options}" STREQUAL "")
      target_compile_definitions("${name}" PRIVATE "${options}")
    endif()
    set(LIBS
        "${LIBS};${name}"
        PARENT_SCOPE)
  endif()
endfunction()

set(imgui_SRC_FILES imgui.cpp imgui_draw.cpp imgui_widgets.cpp imgui_tables.cpp
                    imgui_demo.cpp)
set(imgui_backends_SRC_FILES imgui_impl_glfw.cpp imgui_impl_opengl3.cpp)
set(implot_SRC_FILES implot.cpp implot_items.cpp implot_demo.cpp)

fetch_library(plog "FETCH")
fetch_library(toml11 "FETCH")
fetch_library(stb "FETCH")
fetch_library(imgui "FETCH")
fetch_library(implot "FETCH")
fetch_library(ImGuiFileDialog "CLONE")

set(imgui_backends_SOURCE_DIR "${imgui_SOURCE_DIR}/backends")
set(imgui_backends_AS_SUBMODULE FALSE)
set(imgui_backends_FETCHED FALSE)
set(imgui_backends_CLONED TRUE)

build_library(plog "" "" "" "" "")
build_library(toml11 "" "${toml11_SOURCE_DIR}/include" ""
              "-DTOML11_COMPILE_SOURCES" "toml11::toml11")
build_library(imgui "${imgui_SRC_FILES}" "${imgui_SOURCE_DIR}" "" "" "")
build_library(imgui_backends "${imgui_backends_SRC_FILES}"
              "${imgui_SOURCE_DIR};${imgui_backends_SOURCE_DIR}" "glfw" "" "")
build_library(implot "${implot_SRC_FILES}"
              "${implot_SOURCE_DIR};${imgui_SOURCE_DIR}" "imgui" "" "")

if(TARGET imgui)
  target_include_directories(imgui PUBLIC "$<INSTALL_INTERFACE:include/imgui>")
  install(
    TARGETS imgui
    EXPORT oh-my-dear-imguiTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include/imgui)
  install(
    DIRECTORY ${imgui_SOURCE_DIR}/
    DESTINATION include/imgui
    FILES_MATCHING
      PATTERN "*.h"
      PATTERN "*.hpp"
      PATTERN "*.inl")
endif()

if(TARGET imgui_backends)
  target_include_directories(
    imgui_backends
    PUBLIC
      "$<INSTALL_INTERFACE:include/imgui>"
      "$<INSTALL_INTERFACE:include/imgui/backends>")
  install(
    TARGETS imgui_backends
    EXPORT oh-my-dear-imguiTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include/imgui)
endif()

if(TARGET implot)
  target_include_directories(implot PUBLIC "$<INSTALL_INTERFACE:include/implot>")
  install(
    TARGETS implot
    EXPORT oh-my-dear-imguiTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include/implot)
  install(
    DIRECTORY ${implot_SOURCE_DIR}/
    DESTINATION include/implot
    FILES_MATCHING
      PATTERN "*.h"
      PATTERN "*.hpp"
      PATTERN "*.inl")
endif()

if(TARGET toml11)
  target_include_directories(
    toml11
    PUBLIC
      "$<BUILD_INTERFACE:${toml11_SOURCE_DIR}/include>"
      "$<INSTALL_INTERFACE:include>")
  install(
    TARGETS toml11
    EXPORT oh-my-dear-imguiTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include)
endif()

if(EXISTS ${plog_SOURCE_DIR}/include)
  install(DIRECTORY ${plog_SOURCE_DIR}/include/ DESTINATION include)
endif()

if(EXISTS ${toml11_SOURCE_DIR}/include)
  install(DIRECTORY ${toml11_SOURCE_DIR}/include/ DESTINATION include)
endif()

if(EXISTS ${stb_SOURCE_DIR})
  install(
    DIRECTORY ${stb_SOURCE_DIR}/
    DESTINATION include
    FILES_MATCHING
      PATTERN "*.h"
      PATTERN "*.hpp"
      PATTERN "*.inl")
endif()

if(EXISTS ${ImGuiFileDialog_SOURCE_DIR})
  install(
    DIRECTORY ${ImGuiFileDialog_SOURCE_DIR}/
    DESTINATION include/ImGuiFileDialog
    FILES_MATCHING
      PATTERN "*.h"
      PATTERN "*.hpp")
endif()

set(LIBRARIES
    "${LIBS}"
    CACHE STRING "Libraries to link against")
