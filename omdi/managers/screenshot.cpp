#include "screenshot.h"

#include "managers/toasts.h"
#include "utils.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <stb_image_write.h>

#undef STB_IMAGE_WRITE_IMPLEMENTATION

#include <GLFW/glfw3.h>
#include <imgui.h>

#include <filesystem>
#include <vector>

namespace omdi::save {

  void ScreenshotManager::process(omdi::toasts::ToastManager* toasts) {
    if (not processing()) {
      return;
    } else if (m_delay > 0) {
      m_delay--;
      return;
    }
    m_screenshot_requested = false;

    ImGuiIO& io = ImGui::GetIO();

    omdi::logger::Debug("Image saving");

    int x = 0, y = 0;
    int W = io.DisplaySize.x * io.DisplayFramebufferScale.x;
    int H = io.DisplaySize.y * io.DisplayFramebufferScale.y;

    std::vector<unsigned char> pixels(4 * W * H);

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadPixels(x, y, W, H, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());

    stbi_flip_vertically_on_write(true);

    if (not std::filesystem::exists(m_path)) {
      std::filesystem::create_directories(m_path);
    }

    stbi_write_png((m_path / m_fname).c_str(), W, H, 4, pixels.data(), 4 * W);
    if (toasts != nullptr) {
      toasts->add(omdi::toasts::Type::Info,
                  omdi::fmt::format("Saved screenshot to %s/%s",
                                    m_path.string().c_str(),
                                    m_fname.string().c_str()));
    }
  }

} // namespace omdi::save
