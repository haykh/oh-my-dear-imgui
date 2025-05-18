#ifndef UTILS_H
#define UTILS_H

#include <GLFW/glfw3.h>
#include <imgui.h>

#include <string>

namespace ui {

  namespace gl {
    void SetGLVersion(std::string&);
  } // namespace gl

  namespace imgui {
    void SetFonts(ImGuiIO*);
  } // namespace imgui

} // namespace ui

#endif // UTILS_H
