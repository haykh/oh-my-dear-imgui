#include "window.h"

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
#include <plog/Log.h>

#include <string>

namespace ui {

  Window::Window(int                width,
                 int                height,
                 const std::string& name,
                 int                swapInterval,
                 bool               isResizable)
    : m_winWidth { width }
    , m_winHeight { height } {
    glfwSetErrorCallback([](int error, const char* description) {
      PLOGE << "GLFW Error " << error << ": " << description;
    });
    if (not glfwInit()) {
      PLOGE << "Failed to initialize GLFW.";
      throw std::runtime_error("Failed to initialize GLFW.");
    } else {
      PLOGD << "GLFW initialized.";
    }

    gl::SetGLVersion(m_glsl_version);

    if (!isResizable) {
      glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    }

    m_win = glfwCreateWindow(m_winWidth, m_winHeight, name.c_str(), nullptr, nullptr);

    if (m_win == nullptr) {
      PLOGE << "Failed to open window.";
      throw std::runtime_error("Failed to open window.");
    } else {
      PLOGD << "Window opened.";
    }

    glfwMakeContextCurrent(m_win);
    glfwSwapInterval(swapInterval);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    PLOGD << "ImGui context created.";
    ImPlot::CreateContext();
    PLOGD << "ImPlot context created.";
    m_io               = &ImGui::GetIO();
    // m_io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    m_io->ConfigFlags |= ImGuiConfigFlags_None;

    ImGui::StyleColorsDark();
    imgui::SetFonts(m_io);

    ImGui_ImplGlfw_InitForOpenGL(m_win, true);
    ImGui_ImplOpenGL3_Init(m_glsl_version.c_str());

    m_clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  }

  Window::~Window() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    PLOGD << "ImPlot context destroyed.";
    ImGui::DestroyContext();
    PLOGD << "ImGui context destroyed.";

    glfwDestroyWindow(m_win);
    glfwTerminate();
    PLOGD << "GLFW terminated.";
  }

  void Window::processInput() {
    if (glfwGetKey(m_win, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(m_win, true);
    }
  }

  auto Window::startFrame() -> bool {
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

  void Window::endFrame() {
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(m_win, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(m_clear_color.x * m_clear_color.w,
                 m_clear_color.y * m_clear_color.w,
                 m_clear_color.z * m_clear_color.w,
                 m_clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(m_win);
  }

} // namespace ui
