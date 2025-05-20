set(EXEC example-app)
set(SRC example-app.cpp)
add_executable(${EXEC} ${SRC})

target_link_libraries(${EXEC} PRIVATE oh-my-dear-imgui)
