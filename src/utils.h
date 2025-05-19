#ifndef UTILS_H
#define UTILS_H

#include <GLFW/glfw3.h>
#include <imgui.h>

#include <string>
#include <vector>

namespace ui {

  namespace gl {
    void SetGLVersion(std::string&);
  } // namespace gl

  namespace imgui {
    void SetFonts(ImGuiIO*);
  } // namespace imgui

} // namespace ui

namespace fmt {
  inline auto format(const char* format, ...) -> std::string {
    va_list args;
    va_start(args, format);
    int size = std::vsnprintf(nullptr, 0, format, args);
    va_end(args);
    if (size < 0) {
      return "Formatting error!";
    }
    std::vector<char> buffer(size + 1);
    va_start(args, format);
    std::vsnprintf(buffer.data(), buffer.size(), format, args);
    va_end(args);
    return std::string(buffer.data());
  }
} // namespace fmt

#endif // UTILS_H
