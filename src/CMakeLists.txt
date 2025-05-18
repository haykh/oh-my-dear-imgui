set(EXEC ${PROJECT_NAME}.xc)
set(LIBS imgui imgui_backends implot glfw OpenGL::GL)
set(INC_DIRS ${CMAKE_CURRENT_SOURCE_DIR} ${plog_SOURCE_DIR}/include
             ${ImGuiFileDialog_SOURCE_DIR})

file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
list(FILTER SRC EXCLUDE REGEX "assets")
list(APPEND SRC ${ImGuiFileDialog_SOURCE_DIR}/ImGuiFileDialog.cpp)

add_executable(${EXEC} ${SRC})
target_link_libraries(${EXEC} PRIVATE ${LIBS})
target_include_directories(${EXEC} PRIVATE ${INC_DIRS})

target_compile_definitions(
  ${EXEC}
  PUBLIC
    -DCUSTOM_IMGUIFILEDIALOG_CONFIG="${CMAKE_CURRENT_SOURCE_DIR}/style/imgui_file_dialog_config.h"
)
