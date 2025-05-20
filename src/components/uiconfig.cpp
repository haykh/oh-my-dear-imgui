#include "components/uiconfig.h"

#include "components/picker.h"
#include "components/safe.h"
#include "components/state.h"
#include "components/toasts.h"
#include "components/uiconfig.h"
#include "style/fonts.h"
#include "style/themes.h"

#include <imgui.h>

namespace ui::config {

  void StyleDialog::render(bool*                      open,
                           ui::state::State&          state,
                           ui::picker::PickerManager& pickerManager,
                           ui::fonts::FontManager&    fontManager,
                           ui::toasts::ToastManager&  toastManager) {
    ImGuiIO& io = ImGui::GetIO();

    if (ImGui::Begin("Style Dialog", open)) {
      {
        ImGui::SeparatorText("Colors");
        if (ImGui::Combo(" theme",
                         &state.get<int>("theme_idx"),
                         ui::themes::ALL_THEMES,
                         IM_ARRAYSIZE(ui::themes::ALL_THEMES))) {
          ui::themes::picker(
            ui::themes::ALL_THEMES[state.get<int>("theme_idx")],
            ImGui::GetStyle());
        }
        ImGui::ColorEdit4(" background color",
                          (float*)&state.get<ImVec4>("bg_color"),
                          ImGuiColorEditFlags_NoInputs);
      }

      {
        ImGui::SeparatorText("Fonts");
        const auto fontnames = fontManager.fontnames();
        const auto fontsizes = fontManager.SIZES;

        ui::safe::Component(
          []() {
            return ImGui::BeginListBox("##");
          },
          [&]() {
            for (auto i { 0 }; i < fontnames.size(); ++i) {
              ui::safe::PushPop(
                [&]() {
                  ImGui::PushFont(
                    fontManager.font(fontnames[i], fontManager.active_font_size()));
                },
                [&]() {
                  if (ImGui::Selectable(fontnames[i],
                                        state.get<int>("main_font_idx") == i)) {
                    state.set("main_font_idx", i);
                    PLOGD << "Active font changed to "
                          << fontnames[state.get<int>("main_font_idx")];
                    fontManager.setActiveFont(
                      &io,
                      state.get<int>("main_font_idx"),
                      state.get<int>("main_fontsize_idx"));
                  }
                },
                []() {
                  ImGui::PopFont();
                },
                &toastManager);
            }
          },
          []() {
            ImGui::EndListBox();
          },
          &toastManager);

        if (ImGui::Button("Load from file")) {
          pickerManager.add(
            [&](IGFD::FileDialog* dialog) {
              const auto fpath_name = dialog->GetFilePathName();
              // const auto fpath      = dialog->GetCurrentPath();
              // fontManager.resetMainFont(fpath_name);
              PLOGD << "Loading new fonts from " << fpath_name;
            },
            "FontPicker",
            "Pick a font file",
            ".",
            ".ttf");
        }
      }
      ImGui::End();
    }
  }

} // namespace ui::config
