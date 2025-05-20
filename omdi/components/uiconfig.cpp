#include "components/uiconfig.h"

#include "components/safe.h"
#include "components/uiconfig.h"
#include "managers/fonts.h"
#include "managers/picker.h"
#include "managers/state.h"
#include "managers/toasts.h"
#include "style/themes.h"
#include "utils.h"

#include <imgui.h>

namespace omdi::config {

  void StyleDialog::render(bool*                        open,
                           omdi::state::State&          state,
                           omdi::picker::PickerManager& pickerManager,
                           omdi::fonts::FontManager&    fontManager,
                           omdi::toasts::ToastManager&  toastManager) {
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

        omdi::safe::Component(
          []() {
            return ImGui::BeginListBox("##");
          },
          [&]() {
            for (auto i { 0 }; i < fontnames.size(); ++i) {
              omdi::safe::PushPop(
                [&]() {
                  ImGui::PushFont(
                    fontManager.font(fontnames[i], fontManager.active_font_size()));
                },
                [&]() {
                  if (ImGui::Selectable(fontnames[i],
                                        state.get<int>("main_font_idx") == i)) {
                    state.set("main_font_idx", i);
                    omdi::logger::Debug("Active font changed to %s", fontnames[i]);
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
              omdi::logger::Debug("Loading new fonts from %s", fpath_name.c_str());
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

} // namespace omdi::config
