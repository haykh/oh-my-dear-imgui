# cmake-lint: disable=C0103,C0111,E1120,R0913,R0915

set(LIB ${PROJECT_NAME})
set(LIBS "${LIBRARIES};glfw;OpenGL::GL")

file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
list(FILTER SRC EXCLUDE REGEX "assets")
list(APPEND SRC ${ImGuiFileDialog_SOURCE_DIR}/ImGuiFileDialog.cpp)

add_library(${LIB} ${SRC})
if(NOT TARGET ${PROJECT_NAME}::${PROJECT_NAME})
  add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${LIB})
endif()
target_link_libraries(${LIB} PUBLIC ${LIBS})
target_include_directories(
  ${LIB}
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/style>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/gl>
         $<BUILD_INTERFACE:${stb_SOURCE_DIR}>
         $<BUILD_INTERFACE:${plog_SOURCE_DIR}/include>
         $<BUILD_INTERFACE:${ImGuiFileDialog_SOURCE_DIR}>
         $<BUILD_INTERFACE:${imgui_SOURCE_DIR}>
         $<BUILD_INTERFACE:${implot_SOURCE_DIR}>
         $<INSTALL_INTERFACE:include>
         $<INSTALL_INTERFACE:include/oh-my-dear-imgui>
         $<INSTALL_INTERFACE:include/oh-my-dear-imgui/gl>
         $<INSTALL_INTERFACE:include/imgui>
         $<INSTALL_INTERFACE:include/implot>
         $<INSTALL_INTERFACE:include/ImGuiFileDialog>)

target_compile_definitions(
  ${LIB}
  PUBLIC CUSTOM_IMGUIFILEDIALOG_CONFIG="style/imgui_file_dialog_config.h")

install(
  TARGETS ${LIB}
  EXPORT oh-my-dear-imguiTargets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES
  DESTINATION include/oh-my-dear-imgui)

install(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
  DESTINATION include/oh-my-dear-imgui
  FILES_MATCHING
  PATTERN "*.h"
  PATTERN "*.hpp")

set(${LIB}_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
    PARENT_SCOPE)
set(${LIB}_LIBRARIES
    ${LIB} ${LIBS}
    PARENT_SCOPE)
