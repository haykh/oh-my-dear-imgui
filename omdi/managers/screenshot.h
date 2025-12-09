#ifndef MANAGERS_SCREENSHOT_H
#define MANAGERS_SCREENSHOT_H

#include "managers/toasts.h"

#include <filesystem>

namespace omdi {

  /**
   * @brief Manager for taking and saving screenshots of the application window.
   */
  class ScreenshotManager {
    bool m_screenshot_requested = false;

    unsigned int m_delay = 0u;

    std::filesystem::path m_path  = "screenshots";
    std::filesystem::path m_fname = "screenshot.png";

  public:
    ScreenshotManager() = default;

    void request(const std::filesystem::path& fname = "screenshot.png",
                 const std::filesystem::path& path  = "screenshots") {
      m_screenshot_requested = true;
      m_delay                = 5u;
      m_fname                = fname;
      m_path                 = path;
    }

    void process(omdi::ToastManager* = nullptr);

    [[nodiscard]]
    auto processing() const -> bool {
      return m_screenshot_requested;
    }
  };

} // namespace omdi

#endif // MANAGERS_SCREENSHOT_H
