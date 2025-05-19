#ifndef WINDOW_H
#define WINDOW_H

#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
  #include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h>
#include <imgui.h>

#include <string>

namespace ui::components {

  class Window {
  private:
    GLFWwindow* m_win;
    std::string m_glsl_version;

    ImGuiIO* m_io;

  public:
    Window(int                width,
           int                height,
           const std::string& name,
           int                swapInterval,
           bool               isResizable = true);
    ~Window();

    void processInput();
    auto startFrame() -> bool;
    void endFrame(int&, int&, ImVec4&);

    [[nodiscard]]
    auto windowShouldClose() const -> int {
      return glfwWindowShouldClose(m_win);
    }

    // getters
    [[nodiscard]]
    auto window() const -> GLFWwindow* {
      return m_win;
    }

    [[nodiscard]]
    auto io() -> ImGuiIO* {
      return m_io;
    }

    [[nodiscard]]
    auto glsl_version() const -> const char* {
      return m_glsl_version.c_str();
    }
  };

} // namespace ui::components

#endif // WINDOW_H
