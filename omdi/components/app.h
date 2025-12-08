#ifndef COMPONENTS_APP_H
#define COMPONENTS_APP_H

#include "managers/state.h"

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <imgui.h>

#include <functional>
#include <map>
#include <string>

namespace omdi::app {

  /**
   * @brief Main class for the omdi application.
   *
   * @param {omdi::state::State*} state - pointer to the state manager
   * @param {std::string} name - window name [optional]
   * @param {int} swapInterval - swap interval for VSync [optional]
   * @param {bool} isResizable - whether the window is resizable [optional]
   *
   * @brief State uses the following optional keys:
   * - "window_width" (int): width of the window
   * - "window_height" (int): height of the window
   * - "bg_color" (ImVec4): background color of the window
   */
  class App {
  private:
    GLFWwindow* m_win;
    std::string m_glsl_version;

    ImGuiIO* m_io;

  public:
    App(omdi::state::State* state,
        const std::string&  name         = "omdi App",
        int                 swapInterval = 1,
        bool                isResizable  = true);
    ~App();

    void processInput();

    auto startFrame() -> bool;
    void renderFrame();
    void endFrame(int&, int&, ImVec4&);

    /**
     * @brief Initialize the omdi app with a given state.
     * @param {omdi::state::State*} state - pointer to the state manager
     * @param {std::map<std::string, void*>} managers - map of optional omdi managers
     */
    void Init(omdi::state::State*, const std::map<std::string, void*>& = {});

    /**
     * @brief Run the render loop with provided custom function, and omdi components and managers.
     * @param {omdi::state::State*} state - pointer to the state manager
     * @param {std::function<void()>} custom_render - custom render function
     * @param {std::map<std::string, void*>} components - map of optional omdi UI components
     * @param {std::map<std::string, void*>} managers - map of optional omdi managers
     */
    void Render(omdi::state::State*,
                const std::function<void()>&        = nullptr,
                const std::map<std::string, void*>& = {},
                const std::map<std::string, void*>& = {});

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
