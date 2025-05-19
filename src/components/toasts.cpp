#include "toasts.h"

#include <imgui_internal.h>

#include <cstdio>

#if !defined(_WIN32) && !defined(__linux__) && !defined(__APPLE__) &&          \
  !defined(__EMSCRIPTEN__)
  #include <stdexcept>
#endif

namespace ui::toasts {

  void Toasts::add(const Type& type, unsigned int dismiss_time) {
    auto toast = std::make_unique<Toast>(type, dismiss_time);
    m_toasts.push_back(std::move(toast));
  }

  void Toasts::add(const Type& type, const std::string& content) {
    auto toast = std::make_unique<Toast>(type);
    toast->setContent(content);
    m_toasts.push_back(std::move(toast));
  }

  void Toasts::add(const Type&        type,
                   unsigned int       dismiss_time,
                   const std::string& content) {
    auto toast = std::make_unique<Toast>(type, dismiss_time);
    toast->setContent(content);
    m_toasts.push_back(std::move(toast));
  }

  void Toasts::add(const Type&                  type,
                   unsigned int                 dismiss_time,
                   const std::string&           content,
                   const std::string&           button_label,
                   const std::function<void()>& button_callback) {
    auto toast = std::make_unique<Toast>(type, dismiss_time);
    toast->setContent(content);

    toast->setButtonCallback(button_callback);
    toast->setButtonLabel(button_label.c_str());

    m_toasts.push_back(std::move(toast));
  }

  void Toasts::render() {
    const ImVec2 mainWindowSize = ImGui::GetMainViewport()->Size;

    float height = 0.f;

    auto it = m_toasts.begin();
    while (it != m_toasts.end()) {
      auto&      toast = *it;
      const auto idx   = it - m_toasts.begin();

      if ((toast->fade_phase() == Phase::Expired) || (toast->closing())) {
        it = m_toasts.erase(it);
        continue;
      }
      if ((RENDER_LIMIT > 0) && (idx > RENDER_LIMIT)) {
        ++it;
        continue;
      }

      const auto icon          = toast->icon();
      const auto title         = toast->title();
      const auto content       = toast->content();
      const auto default_title = toast->default_title();
      const auto opacity       = toast->fade_percent();

      auto text_color = toast->color();
      text_color.w    = opacity;

      char window_name[50];
#if defined(_WIN32)
      sprintf_s(windowName, "##TOAST%d", (int)i);
#elif defined(__linux__) || defined(__EMSCRIPTEN__)
      std::sprintf(window_name, "##TOAST%d", (int)idx);
#elif defined(__APPLE__)
      std::snprintf(windowName, 50, "##TOAST%d", (int)i);
#else
      throw "Unsupported platform";
#endif

      ImGui::SetNextWindowBgAlpha(opacity);
      auto mainWindowPos = ImGui::GetMainViewport()->Pos;
      ImGui::SetNextWindowPos(
        ImVec2(mainWindowPos.x + mainWindowSize.x - NOTIFY_PADDING_X,
               mainWindowPos.y + mainWindowSize.y - NOTIFY_PADDING_Y - height),
        ImGuiCond_Always,
        ImVec2(1.0f, 1.0f));

      if (ImGui::Begin(window_name, nullptr, toast->flags())) {
        ImGui::BringWindowToDisplayFront(ImGui::GetCurrentWindow());

        ImGui::PushTextWrapPos(mainWindowSize.x / 3.f);
        {

          bool was_title_rendered = false;

          // If an icon is set
          if (icon != nullptr) {
            // Text(icon); // Render icon text
            ImGui::TextColored(text_color, "%s", icon);
            was_title_rendered = true;
          }

          if (!title.empty()) {
            if (icon != nullptr) {
              ImGui::SameLine();
            }
            ImGui::Text("%s", title.c_str());
            was_title_rendered = true;
          } else if (!default_title.empty()) {
            if (icon != nullptr) {
              ImGui::SameLine();
            }

            ImGui::Text("%s", default_title.c_str());
            was_title_rendered = true;
          }

          if (was_title_rendered || !content.empty()) {
            ImGui::SameLine();
          }

          auto close = ICON_FA_XMARK;

          ImGui::SetCursorPosX(ImGui::GetCursorPosX() +
                               ImMax(0.0f,
                                     ImGui::GetContentRegionAvail().x -
                                       2.0f * ImGui::CalcTextSize(close).x));

          if (ImGui::Button(close)) {
            toast->close();
          }

          if (was_title_rendered && !content.empty()) {
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.f);
          }

          if (!content.empty()) {
            if (was_title_rendered) {
              ImGui::Separator();
            }

            ImGui::Text("%s", content.c_str());
          }

          if (toast->button_callback() != nullptr) {
            if (ImGui::Button(toast->button_label().c_str())) {
              toast->button_callback()();
            }
          }
        }
        ImGui::PopTextWrapPos();

        height += ImGui::GetWindowHeight() + NOTIFY_PADDING_MESSAGE_Y;

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.f);
        auto color = toast->color();
        color.w    = 0.5f;
        ImGui::PushStyleColor(ImGuiCol_PlotHistogram, color);
        {
          ImGui::ProgressBar(toast->percent(),
                             ImVec2(ImGui::GetContentRegionAvail().x, 5.f),
                             ""); // Progress bar
        }
        ImGui::PopStyleColor();

        ImGui::End();
      }
      ++it;
    }
  }

} // namespace ui::toasts
