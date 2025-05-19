#include "components/dialog.h"
#include "components/toasts.h"
#include "style/themes.h"
#include "utils.h"
#include "window.h"

#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Init.h>
#include <plog/Log.h>

#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
  #include <GLES2/gl2.h>
#endif

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <implot.h>
#include <plog/Log.h>

auto main(int argc, char* argv[]) -> int {
  try {
    plog::ColorConsoleAppender<plog::TxtFormatter> console_appender;
    plog::init(plog::debug, &console_appender);

    auto window              = ui::Window(1920, 1080, "nttiny", 1, true);
    auto pickerDialogManager = ui::dialog::PickerDialogs();
    auto toastManager        = ui::toasts::Toasts();

    auto show_implot_demo = false;
    auto show_imgui_demo  = false;

    int theme_idx = 4;
    ui::themes::picker(ui::themes::ALL_THEMES[theme_idx], ImGui::GetStyle());

    while (not window.windowShouldClose()) {
      if (window.startFrame()) {

        if (show_imgui_demo) {
          ImGui::ShowDemoWindow(&show_imgui_demo);
        }
        if (show_implot_demo) {
          ImPlot::ShowDemoWindow(&show_implot_demo);
        }
        if (ImGui::BeginMainMenuBar()) {
          if (ImGui::Button(ICON_FA_BELL)) {
            toastManager.add(ui::toasts::Type::Warning,
                             "Hello world! This is a toast message.");
          }
          if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem(ICON_FA_UPLOAD " load")) {
              pickerDialogManager.add([&](IGFD::FileDialog* dialog) {
                const auto fpath_name = dialog->GetFilePathName();
                const auto fpath      = dialog->GetCurrentPath();
                toastManager.add(
                  ui::toasts::Type::Success,
                  fmt::format("picked %s %s", fpath_name.c_str(), fpath.c_str()));
              });
            }
            ImGui::EndMenu();
          }
          if (ImGui::BeginMenu("UI")) {
            if (ImGui::Combo(ICON_FA_PAINTBRUSH,
                             &theme_idx,
                             ui::themes::ALL_THEMES,
                             IM_ARRAYSIZE(ui::themes::ALL_THEMES))) {
              ui::themes::picker(ui::themes::ALL_THEMES[theme_idx],
                                 ImGui::GetStyle());
            }
            ImGui::ColorEdit4(ICON_FA_PAINT_ROLLER " background",
                              (float*)&window.clear_color(),
                              ImGuiColorEditFlags_NoInputs);
            ImGui::Checkbox("Show ImGui demo", &show_imgui_demo);
            ImGui::Checkbox("Show ImPlot demo", &show_implot_demo);
            ImGui::EndMenu();
          }
          ImGui::EndMainMenuBar();
        }
        pickerDialogManager.render();
        toastManager.render();
        window.endFrame();
      }
    }
  } catch (const std::exception& e) {
    PLOGE << "Exception: " << e.what();
    return 1;
  } catch (...) {
    PLOGE << "Unknown exception";
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
