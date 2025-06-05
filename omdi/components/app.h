#ifndef COMPONENTS_APP_H
#define COMPONENTS_APP_H

#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
  #include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h>
#include <imgui.h>

#include <string>

namespace omdi::app {

  class App {
  private:
    GLFWwindow* m_win;
    std::string m_glsl_version;

    ImGuiIO* m_io;

  public:
    App(int                width,
        int                height,
        const std::string& name,
        int                swapInterval,
        bool               isResizable = true);
    ~App();

    void processInput();
    auto startFrame() -> bool;
    void render();
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

} // namespace omdi::app

#endif // COMPONENTS_APP_H
