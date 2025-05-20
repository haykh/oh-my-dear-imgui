#include "assets/generated/MonaspaceKryptonFrozen-Regular.h"
#include "components/dialog.h"
#include "components/menubar.h"
#include "components/safe.h"
#include "components/state.h"
#include "components/toasts.h"
#include "components/window.h"
#include "style/fonts.h"
#include "style/themes.h"

#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
  #include <GLES2/gl2.h>
#endif

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <implot.h>
#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Init.h>
#include <plog/Log.h>
#include <toml.hpp>

#include <filesystem>
#include <fstream>

auto main(int argc, char* argv[]) -> int {
  try {
    plog::ColorConsoleAppender<plog::TxtFormatter> console_appender;
    plog::init(plog::debug, &console_appender);

    // configurations
    auto state = ui::state::State();
    state.set("window_width", 1920);
    state.set("window_height", 1080);
    state.set("bg_color", ImVec4(0.24f, 0.24f, 0.24f, 1.00f));
    state.set("show_implot_demo", false);
    state.set("show_imgui_demo", false);
    state.set("show_style_dialog", false);
    state.set("theme_idx", 0);

    auto window = ui::components::Window(state.get<int>("window_width"),
                                         state.get<int>("window_height"),
                                         "imgui-boilerplate",
                                         1,
                                         true);

    // managers
    auto pickerDialogManager = ui::dialog::PickerDialogs();
    auto toastManager        = ui::toasts::Toasts();
    auto fontManager         = ui::fonts::FontManager();

    // ui elements
    auto styleDialog = ui::dialog::StyleDialog();
    auto menubar     = ui::menubar::Menubar();

    fontManager.resetMainFont(window.io(),
                              MonaspaceKryptonFrozen_Regular_compressed_data,
                              MonaspaceKryptonFrozen_Regular_compressed_size);

    menubar.addLeft([&]() {
      ui::safe::Component(
        []() {
          return ImGui::BeginMenu("File");
        },
        [&]() {
          if (ImGui::MenuItem("Open")) {
            pickerDialogManager.add([&](IGFD::FileDialog* dialog) {
              const auto fpath_name = dialog->GetFilePathName();
              const auto fpath      = dialog->GetCurrentPath();
              toastManager.add(
                ui::toasts::Type::Success,
                fmt::format("picked %s %s", fpath_name.c_str(), fpath.c_str()));
            });
          }
          if (ImGui::MenuItem("Save State")) {
            const auto data = state.to_toml();
            if (std::filesystem::exists("state.toml")) {
              toastManager.add(ui::toasts::Type::Warning,
                               "File already exists, overwriting...");
            }
            std::ofstream file("state.toml");
            if (file.is_open()) {
              file << data;
              file.close();
              toastManager.add(ui::toasts::Type::Success,
                               "State saved to state.toml");
            } else {
              throw std::runtime_error("Failed to open file for writing.");
            }
          }
          if (ImGui::MenuItem("Configure UI")) {
            state.set("show_style_dialog", true);
          }
        },
        []() {
          ImGui::EndMenu();
        },
        &toastManager);
    });

    menubar.addLeft([&]() {
      ui::safe::Component(
        []() {
          return ImGui::BeginMenu("Demo");
        },
        [&]() {
          ImGui::Checkbox("Show ImGui demo", &state.get<bool>("show_imgui_demo"));
          ImGui::Checkbox("Show ImPlot demo", &state.get<bool>("show_implot_demo"));
        },
        []() {
          ImGui::EndMenu();
        },
        &toastManager);
    });

    menubar.addRight([&]() {
      if (ImGui::Button(ICON_FA_CIRCLE_INFO)) {
        toastManager.add(ui::toasts::Type::Info, "This is an info message.");
      }
      ImGui::SameLine();
      if (ImGui::Button(ICON_FA_CIRCLE_CHECK)) {
        toastManager.add(ui::toasts::Type::Success, "This is a success message.");
      }
      ImGui::SameLine();
      if (ImGui::Button(ICON_FA_TRIANGLE_EXCLAMATION)) {
        toastManager.add(ui::toasts::Type::Warning, "This is a warning message.");
      }
      ImGui::SameLine();
      if (ImGui::Button(ICON_FA_CIRCLE_EXCLAMATION)) {
        throw std::runtime_error("This is an error message.");
      }
    });

    // init state
    ui::themes::picker(ui::themes::ALL_THEMES[state.get<int>("theme_idx")],
                       ImGui::GetStyle());

    while (not window.windowShouldClose()) {
      if (window.startFrame()) {

        if (state.get<bool>("show_imgui_demo")) {
          ImGui::ShowDemoWindow(&state.get<bool>("show_imgui_demo"));
        }
        if (state.get<bool>("show_implot_demo")) {
          ImPlot::ShowDemoWindow(&state.get<bool>("show_implot_demo"));
        }

        // ui elements
        menubar.render(&toastManager);
        if (state.get<bool>("show_style_dialog")) {
          styleDialog.render(&state.get<bool>("show_style_dialog"),
                             state,
                             fontManager);
        }

        pickerDialogManager.render();
        toastManager.render();

        window.endFrame(state.get<int>("window_width"),
                        state.get<int>("window_height"),
                        state.get<ImVec4>("bg_color"));
      }
    }
  } catch (const std::exception& e) {
    PLOGF << "Fatal exception: " << e.what();
    return 1;
  } catch (...) {
    PLOGF << "Unknown fatal exception";
    return 1;
  }
  return 0;
}

// dialog_handler.handle();
// if (ImGui::BeginMainMenuBar()) {
//   if (ImGui::BeginMenu("Simulation")) {
//     // if (ImGui::MenuItem(ICON_FA_UPLOAD " load")) {
//     // }
//     if (ImGui::Button("Open File Dialog")) {
//       dialog_handler.add_dialog([](IGFD::FileDialog* dialog) {
//         PLOGD << "File dialog callback";
//         const auto fpath_name = dialog->GetFilePathName();
//         const auto fpath      = dialog->GetCurrentPath();
//         PLOGD << "Picked: " << fpath_name << " " << fpath;
//       });
//     }
//     //   ImGuiFileDialog::Instance()->OpenDialog("ChooseDirDlgKey",
//     //                                           "Choose a Directory",
//     //                                           nullptr,
//     //                                           config);
//     // }
//     // // display
//     // ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByTypeDir,
//     //                                           "",
//     //                                           ImVec4(0.5f, 1.0f, 0.9f, 0.9f),
//     //                                           ICON_FA_FOLDER);
//     // if (ImGuiFileDialog::Instance()->Display("ChooseDirDlgKey")) {
//     //   if (ImGuiFileDialog::Instance()->IsOk()) {
//     //     std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
//     //     std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
//     //     // action
//     //   }
//     //
//     //   // close
//     //   ImGuiFileDialog::Instance()->Close();
//     // }
//     // ImGui::MenuItem("(plots)", NULL, false, false);
//     // ImGui::Separator();
//     // ImGui::MenuItem("(state)", NULL, false, false);
//     // ImGui::Separator();
//     // if (ImGui::BeginMenu("configure ui")) {
//     //   ImGui::Text("domain outline");
//     //   ImGui::EndMenu();
//     // }
//     ImGui::EndMenu();
//   }
//   ImGui::EndMainMenuBar();
// }
