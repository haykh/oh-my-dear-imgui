#include "components/menubar.h"

#include "components/safe.h"
#include "components/toasts.h"

#include <imgui.h>
#include <plog/Log.h>

namespace ui::menubar {

  void SafeMenu(ui::toasts::ToastManager&    toastManager,
                const std::function<void()>& item,
                const char*                  label,
                bool                         enabled) {
    if (ImGui::BeginMenu(label, enabled)) {
      try {
        item();
      } catch (const std::exception& e) {
        PLOGE << "Exception in SafeMenu: " << e.what();
      } catch (...) {
        PLOGE << "Unknown exception in SafeMenu";
      }
      ImGui::EndMenu();
    }
  }

  auto Menubar::measureWidth(const std::vector<MenuItem>& items) const -> float {
    // Redirect rendering to a dummy window off-screen
    ImGui::SetNextWindowPos(ImVec2(-9999, -9999));
    ImGui::SetNextWindowSize(ImVec2(0, 0));
    ImGui::Begin("##measure_dummy",
                 nullptr,
                 ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs |
                   ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings |
                   ImGuiWindowFlags_NoBackground);

    ImGui::BeginGroup();
    for (size_t i = 0; i < items.size(); ++i) {
      ImGui::PushID((int)i);
      items[i].render();
      if (i < items.size() - 1) {
        ImGui::SameLine();
      }
      ImGui::PopID();
    }
    ImGui::EndGroup();
    float width = ImGui::GetItemRectSize().x;

    ImGui::End(); // Close dummy window
    return width;
  }

  void Menubar::render(ui::toasts::ToastManager* toastManager) const {
    if (ImGui::BeginMainMenuBar()) {
      // Render left-aligned items
      for (size_t i = 0; i < m_items_left.size(); ++i) {
        ImGui::PushID((int)i);
        ui::safe::Render(m_items_left[i].render, toastManager);
        if (i < m_items_left.size() - 1) {
          ImGui::SameLine();
        }
        ImGui::PopID();
      }

      float full_width = ImGui::GetWindowWidth();
      float spacing    = ImGui::GetStyle().ItemSpacing.x;

      float center_width = m_items_center.empty() ? 0.0f
                                                  : measureWidth(m_items_center);
      float right_width  = m_items_right.empty() ? 0.0f
                                                 : measureWidth(m_items_right);

      // Render right-aligned items
      if (!m_items_right.empty()) {
        ImGui::SetCursorPosX(full_width - right_width - spacing);
        ImGui::PushID("RightItems");
        for (size_t i = 0; i < m_items_right.size(); ++i) {
          ImGui::PushID((int)i);
          ui::safe::Render(m_items_right[i].render, toastManager);
          if (i < m_items_right.size() - 1) {
            ImGui::SameLine();
          }
          ImGui::PopID();
        }
        ImGui::PopID();
      }

      // Render center-aligned items
      if (!m_items_center.empty()) {
        ImGui::SetCursorPosX((full_width - center_width) * 0.5f);
        ImGui::PushID("CenterItems");
        for (size_t i = 0; i < m_items_center.size(); ++i) {
          ImGui::PushID((int)i);
          ui::safe::Render(m_items_center[i].render, toastManager);
          if (i < m_items_center.size() - 1) {
            ImGui::SameLine();
          }
          ImGui::PopID();
        }
        ImGui::PopID();
      }
      ImGui::EndMainMenuBar();
    }
  }

} // namespace ui::menubar
