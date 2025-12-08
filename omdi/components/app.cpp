#include "components/app.h"
#include "implot-gpu/implot.h"

#include "components/defaults.h"
#include "components/menubar.h"
#include "components/uiconfig.h"
#include "managers/fonts.h"
#include "managers/picker.h"
#include "managers/screenshot.h"
#include "managers/toasts.h"
#include "style/themes.h"
#include "utils.h"

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <implot.h>

#include <functional>
#include <string>

namespace omdi::app {

  App::App(omdi::state::State* state,
           const std::string&  name,
           int                 swapInterval,
           bool                isResizable) {
    state->ensure("window_width", omdi::defaults::WINDOW_WIDTH);
    state->ensure("window_height", omdi::defaults::WINDOW_HEIGHT);
    state->ensure("bg_color", omdi::defaults::BG_COLOR);

    const int width  = state->get<int>("window_width");
    const int height = state->get<int>("window_height");
    glfwSetErrorCallback([](int error, const char* description) {
      omdi::logger::Fatal("GLFW Error %d : %s", error, description);
    });
    if (not glfwInit()) {
      omdi::logger::Fatal("Failed to initialize GLFW.");
    } else {
      omdi::logger::Debug("GLFW initialized.");
    }

    omdi::gl::SetGLVersion(m_glsl_version);
    omdi::logger::Debug("Using GLSL version: %s", m_glsl_version.c_str());

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

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      omdi::logger::Fatal("Failed to initialize OpenGL context.");
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    omdi::logger::Debug("ImGui context created.");
    omdi::implot::Init();

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
    omdi::implot::Destroy();
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

  void App::renderFrame() {
    ImGui::Render();
    if (m_io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
    }
  }

  auto is_in_map(const std::string& key, const std::map<std::string, void*>& m)
    -> bool {
    return m.find(key) != m.end() and m.at(key) != nullptr;
  }

  void App::Init(omdi::state::State*                 state,
                 const std::map<std::string, void*>& managers) {
    state->ensure<int>("theme_idx", omdi::defaults::THEME_IDX);
    state->ensure<bool>("show_style_dialog", false);
    state->ensure<int>("main_font_idx", omdi::defaults::MAIN_FONT_IDX);
    state->ensure<int>("main_fontsize_idx", omdi::defaults::MAIN_FONTSIZE_IDX);

    omdi::themes::picker(omdi::themes::ALL_THEMES[state->get<int>("theme_idx")],
                         ImGui::GetStyle());
    omdi::fonts::FontManager* fontManager = is_in_map("font_manager", managers)
                                              ? static_cast<omdi::fonts::FontManager*>(
                                                  managers.at("font_manager"))
                                              : nullptr;
    if (fontManager != nullptr) {
      fontManager->initFonts(io());
      fontManager->setActiveFont(io(),
                                 state->get<int>("main_font_idx"),
                                 state->get<int>("main_fontsize_idx"));
    }
  }

  void App::Render(omdi::state::State*                 state,
                   const std::function<void()>&        custom_render,
                   const std::map<std::string, void*>& components,
                   const std::map<std::string, void*>& managers) {
    omdi::menubar::Menubar*    menubar = is_in_map("menubar", components)
                                           ? static_cast<omdi::menubar::Menubar*>(
                                            components.at("menubar"))
                                           : nullptr;
    omdi::config::StyleDialog* styleDialog =
      is_in_map("style_dialog", components)
        ? static_cast<omdi::config::StyleDialog*>(components.at("style_dialog"))
        : nullptr;
    omdi::toasts::ToastManager* toastManager =
      is_in_map("toast_manager", managers)
        ? static_cast<omdi::toasts::ToastManager*>(managers.at("toast_manager"))
        : nullptr;
    omdi::fonts::FontManager* fontManager = is_in_map("font_manager", managers)
                                              ? static_cast<omdi::fonts::FontManager*>(
                                                  managers.at("font_manager"))
                                              : nullptr;
    omdi::save::ScreenshotManager* screenshotManager =
      is_in_map("screenshot_manager", managers)
        ? static_cast<omdi::save::ScreenshotManager*>(
            managers.at("screenshot_manager"))
        : nullptr;
    omdi::picker::PickerManager* pickerDialogManager =
      is_in_map("picker_manager", managers)
        ? static_cast<omdi::picker::PickerManager*>(
            managers.at("picker_manager"))
        : nullptr;
    while (not windowShouldClose()) {
      if (startFrame()) {
        if (custom_render != nullptr) {
          custom_render();
        }

        // ui elements + managers rendering
        if (menubar != nullptr) {
          if (screenshotManager == nullptr or not screenshotManager->processing()) {
            menubar->render(toastManager);
          }
        }
        if (styleDialog != nullptr) {
          styleDialog->render(&state->get<bool>("show_style_dialog"),
                              state,
                              pickerDialogManager,
                              fontManager,
                              toastManager);
        }

        if (pickerDialogManager != nullptr) {
          pickerDialogManager->render();
        }
        if (toastManager != nullptr) {
          toastManager->render();
        }

        renderFrame();
        if (screenshotManager != nullptr) {
          screenshotManager->process(toastManager);
        }
        endFrame(state->get<int>("window_width"),
                 state->get<int>("window_height"),
                 state->get<ImVec4>("bg_color"));
        // fontManager.reset(window.io());
      }
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
