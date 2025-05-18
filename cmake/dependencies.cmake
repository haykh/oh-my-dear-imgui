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

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

set(imgui_REPOSITORY "https://github.com/ocornut/imgui.git")
set(imgui_TAG "docking")

set(ImGuiFileDialog_REPOSITORY "https://github.com/aiekick/ImGuiFileDialog.git")
set(ImGuiFileDialog_TAG "master")

set(implot_REPOSITORY "https://github.com/epezent/implot.git")
set(implot_TAG "master")

set(plog_REPOSITORY "https://github.com/SergiusTheBest/plog.git")
set(plog_TAG "master")

function(fetch_library name)
  if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/extern/${name}")
    message(STATUS "${Green}${name} is being used as a submodule${ColorReset}")
    set(${name}_SOURCE_DIR
        "${CMAKE_CURRENT_SOURCE_DIR}/extern/${name}"
        CACHE STRING "${name} source directory")
  else()
    message(STATUS "${Blue}Fetching ${name}${ColorReset}")

    if(${name} STREQUAL "ImGuiFileDialog")
      set(${name}_SOURCE_DIR ${CMAKE_BINARY_DIR}/_deps/${name}-src)
      if(NOT EXISTS ${${name}_SOURCE_DIR})
        execute_process(
          COMMAND git clone --branch ${${name}_TAG} ${${name}_REPOSITORY}
                  ${${name}_SOURCE_DIR} RESULT_VARIABLE clone_result)
        if(NOT clone_result EQUAL 0)
          message(FATAL_ERROR "Failed to clone ${name}")
        endif()
      endif()
    else()
      FetchContent_Declare(
        ${name}
        GIT_REPOSITORY ${${name}_REPOSITORY}
        GIT_TAG ${${name}_TAG}
        GIT_PROGRESS TRUE)
      FetchContent_MakeAvailable(${name})
    endif()
    set(${name}_SOURCE_DIR
        ${${name}_SOURCE_DIR}
        CACHE STRING "${name} source directory")
  endif()
  if(${name} STREQUAL "imgui")
    set(imgui_backends_SOURCE_DIR
        "${imgui_SOURCE_DIR}/backends"
        CACHE STRING "imgui/backends source directory")
  endif()
endfunction()

function(declare_library name src_files)
  if(NOT ${name} STREQUAL "imgui_backends")
    fetch_library(${name})
  endif()
  set(full_src_files "")
  foreach(file ${src_files})
    list(APPEND full_src_files ${${name}_SOURCE_DIR}/${file})
  endforeach()
  message(STATUS "files are: ${full_src_files}")
  add_library(${name} ${full_src_files})
endfunction()

fetch_library(plog)
fetch_library(ImGuiFileDialog)

declare_library(
  imgui
  "imgui.cpp;imgui_demo.cpp;imgui_draw.cpp;imgui_widgets.cpp;imgui_tables.cpp")
declare_library(imgui_backends "imgui_impl_glfw.cpp;imgui_impl_opengl3.cpp")
declare_library(implot "implot.cpp;implot_items.cpp;implot_demo.cpp")

target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR})
target_include_directories(imgui_backends PUBLIC ${imgui_SOURCE_DIR}
                                                 ${imgui_backends_SOURCE_DIR})
target_include_directories(implot PUBLIC ${implot_SOURCE_DIR}
                                         ${imgui_SOURCE_DIR})

target_link_libraries(imgui_backends PUBLIC glfw)
target_link_libraries(implot PUBLIC imgui)
