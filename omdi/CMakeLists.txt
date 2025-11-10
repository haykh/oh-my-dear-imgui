# cmake-lint: disable=C0103,C0111,E1120,R0913,R0915

set(LIB ${PROJECT_NAME})
set(LIBS "${LIBRARIES};glfw;OpenGL::GL")
set(INC_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/style
    ${stb_SOURCE_DIR}/ ${plog_SOURCE_DIR}/include ${ImGuiFileDialog_SOURCE_DIR})

file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
list(FILTER SRC EXCLUDE REGEX "assets")
list(APPEND SRC ${ImGuiFileDialog_SOURCE_DIR}/ImGuiFileDialog.cpp)

add_library(${LIB} ${SRC})
if(NOT TARGET ${PROJECT_NAME}::${PROJECT_NAME})
  add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${LIB})
endif()
target_link_libraries(${LIB} PUBLIC ${LIBS})
target_include_directories(${LIB} PUBLIC ${INC_DIRS})

set(imgui_file_dialog_config
    "${CMAKE_CURRENT_SOURCE_DIR}/style/imgui_file_dialog_config.h")
target_compile_definitions(
  ${LIB} PUBLIC -DCUSTOM_IMGUIFILEDIALOG_CONFIG="${imgui_file_dialog_config}")

set(${LIB}_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
    PARENT_SCOPE)
set(${LIB}_LIBRARIES
    ${LIB} ${LIBS}
    PARENT_SCOPE)
