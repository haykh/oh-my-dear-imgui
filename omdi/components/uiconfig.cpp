#include "components/uiconfig.h"

#include "components/safe.h"
#include "components/uiconfig.h"
#include "managers/fonts.h"
#include "managers/picker.h"
#include "managers/state.h"
#include "managers/toasts.h"
#include "style/themes.h"
#include "utils.h"

#include <cmath>
#include <imgui.h>

namespace omdi::config {

  void StyleDialog::render(bool*                        open,
                           omdi::state::State*          state,
                           omdi::picker::PickerManager* pickerManager,
                           omdi::fonts::FontManager*    fontManager,
                           omdi::toasts::ToastManager*  toastManager) {
    if (*open) {
      ImGuiIO& io = ImGui::GetIO();

      if (ImGui::Begin("Style Dialog", open)) {
        {
          ImGui::SeparatorText("Colors");
          if (ImGui::Combo(" theme",
                           &state->get<int>("theme_idx"),
                           omdi::themes::ALL_THEMES,
                           IM_ARRAYSIZE(omdi::themes::ALL_THEMES))) {
            omdi::themes::picker(
              omdi::themes::ALL_THEMES[state->get<int>("theme_idx")],
              ImGui::GetStyle());
          }
          ImGui::ColorEdit4(" background color",
                            (float*)&state->get<ImVec4>("bg_color"),
                            ImGuiColorEditFlags_NoInputs);
        }

        {
          ImGui::SeparatorText("Fonts");
          const auto fontnames = fontManager->fontnames();
          const auto fontsizes = fontManager->SIZES;

          omdi::safe::Component(
            []() {
              return ImGui::BeginListBox(
                "##pickfont",
                ImVec2(ImGui::GetContentRegionAvail().x - 65.0f, 0.0f));
            },
            [&]() {
              for (auto i { 0 }; i < fontnames.size(); ++i) {
                omdi::safe::PushPop(
                  [&]() {
                    ImGui::PushFont(
                      fontManager->font(fontnames[i],
                                        fontManager->active_font_size()));
                  },
                  [&]() {
                    if (ImGui::Selectable(fontnames[i],
                                          state->get<int>("main_font_idx") == i)) {
                      state->set("main_font_idx", i);
                      omdi::logger::Debug("Active font changed to %s",
                                          fontnames[i]);
                      fontManager->setActiveFont(
                        &io,
                        i,
                        state->get<int>("main_fontsize_idx"));
                    }
                  },
                  []() {
                    ImGui::PopFont();
                  },
                  toastManager);
              }
            },
            []() {
              ImGui::EndListBox();
            },
            toastManager);

          ImGui::SameLine();
          ImGui::SetCursorPosX(
            ImGui::GetCursorPosX() +
            std::fmax(0.0f, ImGui::GetContentRegionAvail().x - 65.0f));
          omdi::safe::Component(
            []() {
              return ImGui::BeginListBox("##pickfontsize", ImVec2(60.0f, 0.0f));
            },
            [&]() {
              const auto active_fontname = fontManager->active_font();
              for (auto i { 0 }; i < fontsizes.size(); ++i) {
                omdi::safe::PushPop(
                  [&]() {
                    ImGui::PushFont(
                      fontManager->font(active_fontname, fontsizes[i]));
                  },
                  [&]() {
                    const auto size_str = std::to_string(
                      static_cast<int>(fontsizes[i]));
                    if (ImGui::Selectable(
                          size_str.c_str(),
                          state->get<int>("main_fontsize_idx") == i)) {
                      state->set("main_fontsize_idx", i);
                      omdi::logger::Debug("Active fontsize changed to %s",
                                          size_str.c_str());
                      fontManager->setActiveFont(
                        &io,
                        state->get<int>("main_font_idx"),
                        i);
                    }
                  },
                  []() {
                    ImGui::PopFont();
                  },
                  toastManager);
              }
            },
            []() {
              ImGui::EndListBox();
            },
            toastManager);
        }
        ImGui::End();
      }
    }
  }

} // namespace omdi::config
