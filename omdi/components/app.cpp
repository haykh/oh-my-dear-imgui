#include "components/app.h"

#include "utils.h"

#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
  #include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <implot.h>

#include <string>

namespace omdi::app {

  App::App(int                width,
           int                height,
           const std::string& name,
           int                swapInterval,
           bool               isResizable) {
    glfwSetErrorCallback([](int error, const char* description) {
      omdi::logger::Fatal("GLFW Error %d : %s", error, description);
    });
    if (not glfwInit()) {
      omdi::logger::Fatal("Failed to initialize GLFW.");
    } else {
      omdi::logger::Debug("GLFW initialized.");
    }

    omdi::gl::SetGLVersion(m_glsl_version);

    if (!isResizable) {
      glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    }

    m_win = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

    if (m_win == nullptr) {
      omdi::logger::Fatal("Failed to open window.");
    } else {
      omdi::logger::Debug("Window opened.");
    }

    glfwMakeContextCurrent(m_win);
    glfwSwapInterval(swapInterval);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    omdi::logger::Debug("ImGui context created.");
    ImPlot::CreateContext();
    omdi::logger::Debug("ImPlot context created.");
    m_io               = &ImGui::GetIO();
    // m_io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    m_io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    // m_io->ConfigFlags |= ImGuiConfigFlags_None;
    // m_io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui_ImplGlfw_InitForOpenGL(m_win, true);
    ImGui_ImplOpenGL3_Init(m_glsl_version.c_str());
  }

  App::~App() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    omdi::logger::Debug("ImPlot context destroyed.");
    ImGui::DestroyContext();
    omdi::logger::Debug("ImGui context destroyed.");

    glfwDestroyWindow(m_win);
    glfwTerminate();
    omdi::logger::Debug("GLFW terminated.");
  }

  void App::processInput() {
    if (glfwGetKey(m_win, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(m_win, true);
    }
  }

  auto App::startFrame() -> bool {
    glfwPollEvents();
    processInput();
    if (glfwGetWindowAttrib(m_win, GLFW_ICONIFIED) != 0) {
      ImGui_ImplGlfw_Sleep(10);
      return false;
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    return true;
  }

  void App::render() {
    ImGui::Render();
    if (m_io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
    }
  }

  void App::endFrame(int& width, int& height, ImVec4& bg_color) {
    glfwGetFramebufferSize(m_win, &width, &height);
    glViewport(0, 0, width, height);
    glClearColor(bg_color.x * bg_color.w,
                 bg_color.y * bg_color.w,
                 bg_color.z * bg_color.w,
                 bg_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(m_win);
  }

} // namespace omdi::app
