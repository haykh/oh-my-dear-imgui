set(examples "example-app" "example-min" "example-plotting")

foreach(example ${examples})
  set(SRC ${example}.cpp)
  add_executable(${example} ${SRC})
  target_link_libraries(${example} PRIVATE oh-my-dear-imgui)
endforeach()
