#include "components/dialog.h"

#include "components/state.h"
#include "icons.h"
#include "style/fonts.h"
#include "style/themes.h"

#include <ImGuiFileDialog.h>
#include <plog/Log.h>

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace ui::dialog {

  void PickerDialogs::add(callback_t         callback,
                          const std::string& title,
                          const std::string& prompt,
                          const std::string& path,
                          const char*        filter) {
    IGFD::FileDialogConfig config;
    config.path = path;

    auto dialog = std::make_unique<IGFD::FileDialog>();
    dialog->OpenDialog(title, prompt, filter, config);

    m_dialogs.emplace_back(std::move(dialog), std::move(callback));
    PLOGD << "Opening a dialog " << title << " in " << path;
    PLOGD << "Total dialogs: " << m_dialogs.size();
  }

  void PickerDialogs::render() {
    auto it = m_dialogs.begin();
    while (it != m_dialogs.end()) {
      auto& [dialog, callback] = *it;
      const auto key           = dialog->GetOpenedKey();
      if (dialog->Display(key)) {
        if (dialog->IsOk()) {
          PLOGD << "Callback for dialog " << key;
          callback(dialog.get());
        } else {
          PLOGD << "Dialog " << key << " is closed";
        }
        dialog->Close();

        it = m_dialogs.erase(it);
        PLOGD << "Dialog " << key
              << " removed from the manager. Remaining: " << m_dialogs.size();
      } else {
        ++it;
      }
    }
  }

  void StyleDialog::render(bool*                   open,
                           ui::state::State&       state,
                           ui::fonts::FontManager& fontManager) {
    ImGuiIO& io        = ImGui::GetIO();
    auto     main_font = io.Fonts->Fonts[0];

    if (ImGui::Begin("Style Dialog", open)) {
      ImGui::PushFont(
        fontManager.get(ui::fonts::Type::Icon, ui::fonts::Size::Large));
      ImGui::Text(ICON_FA_PALETTE);
      ImGui::PopFont();
      ImGui::SameLine();
      if (ImGui::Combo(" theme",
                       &state.get<int>("theme_idx"),
                       ui::themes::ALL_THEMES,
                       IM_ARRAYSIZE(ui::themes::ALL_THEMES))) {
        ui::themes::picker(ui::themes::ALL_THEMES[state.get<int>("theme_idx")],
                           ImGui::GetStyle());
      }
      ImGui::Text(ICON_FA_BRUSH);
      ImGui::SameLine();
      ImGui::ColorEdit4(" background",
                        (float*)&state.get<ImVec4>("bg_color"),
                        ImGuiColorEditFlags_NoInputs);
      ImGui::End();
    }
  }

} // namespace ui::dialog
