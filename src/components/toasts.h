#ifndef COMPONENTS_TOASTS_H
#define COMPONENTS_TOASTS_H

#include "icons.h"
#include "utils.h"

#include <imgui_internal.h>
#include <inttypes.h>
#include <plog/Log.h>

#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace ui::toasts {

  enum class Type : uint8_t {
    None,
    Success,
    Warning,
    Error,
    Info,
    COUNT
  };

  enum class Phase : uint8_t {
    FadeIn,
    Wait,
    FadeOut,
    Expired,
    COUNT
  };

  enum class Pos : uint8_t {
    TopLeft,
    TopCenter,
    TopRight,
    BottomLeft,
    BottomCenter,
    BottomRight,
    Center,
    COUNT
  };

  class Toast {
    ImGuiWindowFlags m_flags = ImGuiWindowFlags_AlwaysAutoResize |
                               ImGuiWindowFlags_NoDecoration |
                               ImGuiWindowFlags_NoNav |
                               ImGuiWindowFlags_NoBringToFrontOnFocus |
                               ImGuiWindowFlags_NoFocusOnAppearing;

    unsigned int m_dismiss_time { NOTIFY_DEFAULT_DISMISS };
    const std::chrono::system_clock::time_point m_creation_time;

    const Type m_type;

    std::string m_title, m_content, m_button_label;

    // A lambda function, which will be executed when button in notification is pressed
    std::function<void()> m_button_callback = nullptr;

    bool m_closing { false };

  public:
    // Fade in and out duration
    static constexpr unsigned int NOTIFY_FADE_IN_OUT_TIME = 150u;
    // Toast opacity: 0 to 1
    static constexpr float        NOTIFY_OPACITY          = 0.8f;
    // Auto dismiss after X ms (default, applied only of no data provided in constructors)
    static constexpr unsigned int NOTIFY_DEFAULT_DISMISS  = 3000u;

    // Setters
    inline void setFlags(const ImGuiWindowFlags& flags) {
      m_flags = flags;
    }

    // inline void setType(const Type& type) {
    //   m_type = type;
    // };

    inline void setTitle(const char* format, ...) {
      va_list args;
      va_start(args, format);
      m_title = fmt::format(format, args);
      va_end(args);
    }

    inline void setContent(const std::string& content) {
      m_content = content;
    }

    inline void setButtonLabel(const char* format, ...) {
      va_list args;
      va_start(args, format);
      m_button_label = fmt::format(format, args);
      va_end(args);
    }

    inline void setButtonCallback(const std::function<void()>& button_callback) {
      m_button_callback = button_callback;
    }

    inline void close() {
      m_closing = true;
    }

    // Getters
    [[nodiscard]]
    inline auto flags() const -> ImGuiWindowFlags {
      return m_flags;
    }

    [[nodiscard]]
    inline auto type() const -> Type {
      return m_type;
    };

    [[nodiscard]]
    inline auto color() const -> ImVec4 {
      switch (m_type) {
        case Type::None:
          return { 255, 255, 255, 255 }; // White
        case Type::Success:
          return { 0, 255, 0, 255 }; // Green
        case Type::Warning:
          return { 255, 255, 0, 255 }; // Yellow
        case Type::Error:
          return { 255, 0, 0, 255 }; // Error
        case Type::Info:
          return { 0, 157, 255, 255 }; // Blue
        default:
          return { 255, 255, 255, 255 }; // White
      }
    }

    [[nodiscard]]
    inline auto icon() const -> const char* {
      switch (m_type) {
        case Type::None:
          return nullptr;
        case Type::Success:
          return ICON_FA_CIRCLE_CHECK; // Font Awesome 6
        case Type::Warning:
          return ICON_FA_TRIANGLE_EXCLAMATION; // Font Awesome 6
        case Type::Error:
          return ICON_FA_CIRCLE_EXCLAMATION; // Font Awesome 6
        case Type::Info:
          return ICON_FA_CIRCLE_INFO; // Font Awesome 6
        default:
          return nullptr;
      }
    }

    [[nodiscard]]
    inline auto title() const -> std::string {
      return m_title;
    };

    [[nodiscard]]
    inline auto default_title() const -> std::string {
      if (m_title.empty()) {
        switch (m_type) {
          case Type::None:
            return "";
          case Type::Success:
            return "Success";
          case Type::Warning:
            return "Warning";
          case Type::Error:
            return "Error";
          case Type::Info:
            return "Info";
          default:
            return "";
        }
      }
      return m_title;
    };

    [[nodiscard]]
    inline auto content() const -> std::string {
      return m_content;
    };

    [[nodiscard]]
    inline auto button_label() const -> std::string {
      return m_button_label;
    }

    [[nodiscard]]
    inline auto button_callback() -> std::function<void()> {
      return m_button_callback;
    }

    [[nodiscard]]
    inline auto dismiss_time() const -> unsigned int {
      return m_dismiss_time;
    }

    [[nodiscard]]
    inline auto elapsed_time() const -> std::chrono::nanoseconds {
      return std::chrono::system_clock::now() - m_creation_time;
    }

    /**
     * @brief Get the current phase of the toast notification based on the elapsed time since its creation.
     *
     * @return ImGuiToastPhase The current phase of the toast notification.
     *         - Phase::FadeIn: The notification is fading in.
     *         - Phase::Wait: The notification is waiting to be dismissed.
     *         - Phase::FadeOut: The notification is fading out.
     *         - Phase::Expired: The notification has expired and should be removed.
     */
    [[nodiscard]]
    inline auto fade_phase() const -> Phase {
      if (m_dismiss_time == 0u) {
        return Phase::Wait;
      }

      const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                             elapsed_time())
                             .count();

      if (elapsed >
          NOTIFY_FADE_IN_OUT_TIME + m_dismiss_time + NOTIFY_FADE_IN_OUT_TIME) {
        return Phase::Expired;
      } else if (elapsed > NOTIFY_FADE_IN_OUT_TIME + m_dismiss_time) {
        return Phase::FadeOut;
      } else if (elapsed > NOTIFY_FADE_IN_OUT_TIME) {
        return Phase::Wait;
      } else {
        return Phase::FadeIn;
      }
    }

    [[nodiscard]]
    inline auto percent() const -> float {
      if (m_dismiss_time == 0u) {
        return 1.f;
      }

      auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                       elapsed_time())
                       .count();
      return (float)elapsed / (float)m_dismiss_time;
    }

    [[nodiscard]]
    inline auto fade_percent() const -> float {
      if (m_dismiss_time == 0u) {
        return 1.f * NOTIFY_OPACITY;
      }

      const auto phase = fade_phase();
      const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                             elapsed_time())
                             .count();

      if (phase == Phase::FadeIn) {
        return ((float)elapsed / (float)NOTIFY_FADE_IN_OUT_TIME) * NOTIFY_OPACITY;
      } else if (phase == Phase::FadeOut) {
        return (1.f - (float)(elapsed - NOTIFY_FADE_IN_OUT_TIME - m_dismiss_time) /
                        (float)NOTIFY_FADE_IN_OUT_TIME) *
               NOTIFY_OPACITY;
      }

      return 1.f * NOTIFY_OPACITY;
    }

    [[nodiscard]]
    inline auto closing() const -> bool {
      return m_closing;
    }

    // Constructors
    Toast(const Type& type)
      : m_type { type }
      , m_creation_time { std::chrono::system_clock::now() } {
      if (type == Type::Error) {
        m_dismiss_time = 0u;
      }
      PLOGD << "Toast created";
    }

    Toast(const Type& type, unsigned int dismiss_time)
      : m_type { type }
      , m_dismiss_time { dismiss_time }
      , m_creation_time { std::chrono::system_clock::now() } {
      PLOGD << "Toast created with dismiss time";
    }
  };

  class Toasts {
    // Max number of toasts to render
    static constexpr unsigned int RENDER_LIMIT             = 10u;
    // Bottom-left X padding
    static constexpr float        NOTIFY_PADDING_X         = 20.f;
    // Bottom-left Y padding
    static constexpr float        NOTIFY_PADDING_Y         = 20.f;
    // Padding Y between each message
    static constexpr float        NOTIFY_PADDING_MESSAGE_Y = 10.f;

    std::vector<std::unique_ptr<Toast>> m_toasts;

  public:
    void add(const Type&, unsigned int = Toast::NOTIFY_DEFAULT_DISMISS);
    void add(const Type&, unsigned int, const std::string&);
    void add(const Type&, const std::string&);
    void add(const Type&,
             unsigned int,
             const std::string&,
             const std::string&,
             const std::function<void()>&);

    void render();
  };
} // namespace ui::toasts

#endif // COMPONENTS_TOASTS_H
