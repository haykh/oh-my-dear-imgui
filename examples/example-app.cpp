#include <imgui.h>
#include <implot.h>
#include <omdi.hpp>
#include <toml.hpp>

#include <filesystem>
#include <fstream>

auto main(int argc, char* argv[]) -> int {
  try {
    omdi::logger::Init();

    auto state = omdi::state::State();
    state.set("window_width", 1920);
    state.set("window_height", 1080);
    state.set("bg_color", ImVec4(0.24f, 0.24f, 0.24f, 1.00f));
    state.set("show_implot_demo", false);
    state.set("show_imgui_demo", false);
    state.set("show_style_dialog", false);
    state.set("main_font_idx", 0);
    state.set("main_fontsize_idx", 1);
    state.set("theme_idx", 0);

    auto app = omdi::app::App(&state, "example-app", 1, true);

    // managers
    auto pickerDialogManager = omdi::picker::PickerManager();
    auto toastManager        = omdi::toasts::ToastManager();
    auto fontManager         = omdi::fonts::FontManager();
    auto screenshotManager   = omdi::save::ScreenshotManager();

    // ui elements
    auto styleDialog = omdi::config::StyleDialog();
    auto menubar     = omdi::menubar::Menubar();

    menubar.AddLeft([&]() {
      omdi::safe::Component(
        []() {
          return ImGui::BeginMenu("File");
        },
        [&]() {
          if (ImGui::MenuItem("Open")) {
            pickerDialogManager.Add([&](IGFD::FileDialog* dialog) {
              const auto fpath_name = dialog->GetFilePathName();
              const auto fpath      = dialog->GetCurrentPath();
              toastManager.Add(omdi::toasts::Type::Success,
                               omdi::fmt::format("picked %s %s",
                                                 fpath_name.c_str(),
                                                 fpath.c_str()));
            });
          }
          if (ImGui::MenuItem("Save State")) {
            const auto data = state.to_toml();
            if (std::filesystem::exists("state.toml")) {
              toastManager.Add(omdi::toasts::Type::Warning,
                               "File already exists, overwriting...");
            }
            std::ofstream file("state.toml");
            if (file.is_open()) {
              file << data;
              file.close();
              toastManager.Add(omdi::toasts::Type::Success,
                               "State saved to state.toml");
            } else {
              throw std::runtime_error("Failed to open file for writing.");
            }
          }
          if (ImGui::MenuItem("Configure UI")) {
            state.set("show_style_dialog", true);
          }
          if (ImGui::MenuItem("Save Image")) {
            screenshotManager.request();
          }
        },
        []() {
          ImGui::EndMenu();
        },
        &toastManager);
    });

    menubar.AddLeft([&]() {
      omdi::safe::Component(
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

    menubar.AddRight([&]() {
      if (ImGui::Button(ICON_FA_CIRCLE_INFO)) {
        toastManager.Add(omdi::toasts::Type::Info, "This is an info message.");
      }
      ImGui::SameLine();
      if (ImGui::Button(ICON_FA_CIRCLE_CHECK)) {
        toastManager.Add(omdi::toasts::Type::Success, "This is a success message.");
      }
      ImGui::SameLine();
      if (ImGui::Button(ICON_FA_TRIANGLE_EXCLAMATION)) {
        toastManager.Add(omdi::toasts::Type::Warning, "This is a warning message.");
      }
      ImGui::SameLine();
      if (ImGui::Button(ICON_FA_CIRCLE_EXCLAMATION)) {
        throw std::runtime_error("This is an error message.");
      }
    });

    auto components = omdi::components_t {
      {      "menubar",     &menubar },
      { "style_dialog", &styleDialog }
    };
    auto managers = omdi::managers_t {
      {      "toast_manager",        &toastManager },
      {       "font_manager",         &fontManager },
      { "screenshot_manager",   &screenshotManager },
      {     "picker_manager", &pickerDialogManager }
    };

    app.Init(&state, managers);

    app.Render(
      &state,
      [&]() {
        if (state.get<bool>("show_imgui_demo")) {
          ImGui::ShowDemoWindow(&state.get<bool>("show_imgui_demo"));
        }
        if (state.get<bool>("show_implot_demo")) {
          ImPlot::ShowDemoWindow(&state.get<bool>("show_implot_demo"));
        }
      },
      components,
      managers);

  } catch (const std::exception& e) {
    omdi::logger::Error("Fatal exception %s", e.what());
    return 1;
  } catch (...) {
    omdi::logger::Error("Unknown fatal exception");
    return 1;
  }
  return 0;
}
