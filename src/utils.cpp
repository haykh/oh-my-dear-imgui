#include "utils.h"

#include "assets/generated/MonaspaceKryptonFrozen-Regular.h"
#include "assets/generated/fa-regular-400.h"
#include "assets/generated/fa-solid-900.h"
#include "icons.h"

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <plog/Log.h>

#include <string>

namespace ui {

  void gl::SetGLVersion(std::string& glsl_version) {
    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100 (WebGL 1.0)
    PLOGD << "Using GLSL 100.";
    glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(IMGUI_IMPL_OPENGL_ES3)
    // GL ES 3.0 + GLSL 300 es (WebGL 2.0)
    PLOGD << "Using GLSL 300.";
    glsl_version = "#version 300 es";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    PLOGD << "Using GLSL 150.";
    glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on Mac
#else
    // GL 3.0 + GLSL 130
    PLOGD << "Using GLSL 130.";
    glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+
    // only glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // 3.0+ only
#endif

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  }

  void imgui::SetFonts(ImGuiIO* io) {
    ImFontConfig icons_config;

    ImFont* default_font = io->Fonts->AddFontDefault();
    io->Fonts->Build();
    const float default_font_size = (16.0 / 13.0) * default_font->FontSize;
    io->Fonts->Clear();

    ImFontConfig font_config;
    font_config.PixelSnapH = true;
    io->Fonts->AddFontFromMemoryCompressedTTF(
      MonaspaceKryptonFrozen_Regular_compressed_data,
      MonaspaceKryptonFrozen_Regular_compressed_size,
      default_font_size,
      &font_config);

    // 4. Add icon fonts using same size
    icons_config.MergeMode              = true;
    icons_config.PixelSnapH             = true;
    static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };

    io->Fonts->AddFontFromMemoryCompressedTTF(fa_regular_400_compressed_data,
                                              fa_regular_400_compressed_size,
                                              default_font_size,
                                              &icons_config,
                                              icons_ranges);

    io->Fonts->AddFontFromMemoryCompressedTTF(fa_solid_900_compressed_data,
                                              fa_solid_900_compressed_size,
                                              default_font_size,
                                              &icons_config,
                                              icons_ranges);

    // 5. Build font atlas
    io->Fonts->Build();
  }

} // namespace ui
