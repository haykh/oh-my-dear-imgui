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

// #include "assets/icons.h"
#include "components/dialog.h"
#include "window.h"

auto main(int argc, char* argv[]) -> int {
  try {
    plog::ColorConsoleAppender<plog::TxtFormatter> console_appender;
    plog::init(plog::debug, &console_appender);

    auto window = ui::Window(1920, 1080, "ui", 1, true);

    bool show_demo_window    = true;
    bool show_another_window = false;

    auto dialog_handler = ui::dialog::Handler();

    while (not window.windowShouldClose()) {
      if (window.startFrame()) {
        dialog_handler.handle();
        if (ImGui::BeginMainMenuBar()) {
          if (ImGui::BeginMenu("Simulation")) {
            // if (ImGui::MenuItem(ICON_FA_UPLOAD " load")) {
            // }
            if (ImGui::Button("Open File Dialog")) {
              dialog_handler.add_dialog([](IGFD::FileDialog* dialog) {
                PLOGD << "File dialog callback";
                const auto fpath_name = dialog->GetFilePathName();
                const auto fpath      = dialog->GetCurrentPath();
                PLOGD << "Picked: " << fpath_name << " " << fpath;
              });
            }
            //   ImGuiFileDialog::Instance()->OpenDialog("ChooseDirDlgKey",
            //                                           "Choose a Directory",
            //                                           nullptr,
            //                                           config);
            // }
            // // display
            // ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByTypeDir,
            //                                           "",
            //                                           ImVec4(0.5f, 1.0f, 0.9f, 0.9f),
            //                                           ICON_FA_FOLDER);
            // if (ImGuiFileDialog::Instance()->Display("ChooseDirDlgKey")) {
            //   if (ImGuiFileDialog::Instance()->IsOk()) {
            //     std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
            //     std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
            //     // action
            //   }
            //
            //   // close
            //   ImGuiFileDialog::Instance()->Close();
            // }
            // ImGui::MenuItem("(plots)", NULL, false, false);
            // ImGui::Separator();
            // ImGui::MenuItem("(state)", NULL, false, false);
            // ImGui::Separator();
            // if (ImGui::BeginMenu("configure ui")) {
            //   ImGui::Text("domain outline");
            //   ImGui::EndMenu();
            // }
            ImGui::EndMenu();
          }
          ImGui::EndMainMenuBar();
        }
        ImPlot::ShowDemoWindow();
        ImGui::ShowDemoWindow();
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
