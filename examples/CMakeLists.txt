set(EXEC example-app)
set(SRC example-app.cpp)
add_executable(${EXEC} ${SRC})

target_link_libraries(${EXEC} PRIVATE ${oh-my-dear-imgui_LIBRARIES})
target_include_directories(${EXEC} PRIVATE ${oh-my-dear-imgui_INCLUDE_DIRS})
