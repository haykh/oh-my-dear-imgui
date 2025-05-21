#include <imgui.h>
#include <imgui_node_editor.h>
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

    auto app = omdi::app::App(state.get<int>("window_width"),
                              state.get<int>("window_height"),
                              "example-app",
                              1,
                              true);

    // managers
    auto pickerDialogManager = omdi::picker::PickerManager();
    auto toastManager        = omdi::toasts::ToastManager();
    auto fontManager         = omdi::fonts::FontManager();

    // ui elements
    auto styleDialog = omdi::config::StyleDialog();
    auto menubar     = omdi::menubar::Menubar();

    fontManager.initFonts(app.io());
    fontManager.setActiveFont(app.io(),
                              state.get<int>("main_font_idx"),
                              state.get<int>("main_fontsize_idx"));

    menubar.addLeft([&]() {
      omdi::safe::Component(
        []() {
          return ImGui::BeginMenu("File");
        },
        [&]() {
          if (ImGui::MenuItem("Open")) {
            pickerDialogManager.add([&](IGFD::FileDialog* dialog) {
              const auto fpath_name = dialog->GetFilePathName();
              const auto fpath      = dialog->GetCurrentPath();
              toastManager.add(omdi::toasts::Type::Success,
                               omdi::fmt::format("picked %s %s",
                                                 fpath_name.c_str(),
                                                 fpath.c_str()));
            });
          }
          if (ImGui::MenuItem("Save State")) {
            const auto data = state.to_toml();
            if (std::filesystem::exists("state.toml")) {
              toastManager.add(omdi::toasts::Type::Warning,
                               "File already exists, overwriting...");
            }
            std::ofstream file("state.toml");
            if (file.is_open()) {
              file << data;
              file.close();
              toastManager.add(omdi::toasts::Type::Success,
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

    menubar.addRight([&]() {
      if (ImGui::Button(ICON_FA_CIRCLE_INFO)) {
        toastManager.add(omdi::toasts::Type::Info, "This is an info message.");
      }
      ImGui::SameLine();
      if (ImGui::Button(ICON_FA_CIRCLE_CHECK)) {
        toastManager.add(omdi::toasts::Type::Success, "This is a success message.");
      }
      ImGui::SameLine();
      if (ImGui::Button(ICON_FA_TRIANGLE_EXCLAMATION)) {
        toastManager.add(omdi::toasts::Type::Warning, "This is a warning message.");
      }
      ImGui::SameLine();
      if (ImGui::Button(ICON_FA_CIRCLE_EXCLAMATION)) {
        throw std::runtime_error("This is an error message.");
      }
    });

    // init state
    ui::themes::picker(ui::themes::ALL_THEMES[state.get<int>("theme_idx")],
                       ImGui::GetStyle());

    namespace ed = ax::NodeEditor;

    auto ed_ctx = ed::CreateEditor();

    while (not app.windowShouldClose()) {
      if (app.startFrame()) {

        auto& io = ImGui::GetIO();

        ImGui::Text("FPS: %.2f (%.2gms)",
                    io.Framerate,
                    io.Framerate ? 1000.0f / io.Framerate : 0.0f);

        ImGui::Separator();

        ed::SetCurrentEditor(ed_ctx);
        ed::Begin("My Editor", ImVec2(0.0, 0.0f));
        int uniqueId = 1;
        // Start drawing nodes.
        ed::BeginNode(uniqueId++);
        ImGui::Text("Node A");
        ed::BeginPin(uniqueId++, ed::PinKind::Input);
        ImGui::Text("-> In");
        ed::EndPin();
        ImGui::SameLine();
        ed::BeginPin(uniqueId++, ed::PinKind::Output);
        ImGui::Text("Out ->");
        ed::EndPin();
        ed::EndNode();
        ed::End();
        ed::SetCurrentEditor(nullptr);
        // if (state.get<bool>("show_imgui_demo")) {
        //   ImGui::ShowDemoWindow(&state.get<bool>("show_imgui_demo"));
        // }
        // if (state.get<bool>("show_implot_demo")) {
        //   ImPlot::ShowDemoWindow(&state.get<bool>("show_implot_demo"));
        // }
        //
        // // ui elements
        // menubar.render(&toastManager);
        // if (state.get<bool>("show_style_dialog")) {
        //   styleDialog.render(&state.get<bool>("show_style_dialog"),
        //                      state,
        //                      pickerDialogManager,
        //                      fontManager,
        //                      toastManager);
        // }
        //
        // pickerDialogManager.render();
        // toastManager.render();

        app.endFrame(state.get<int>("window_width"),
                     state.get<int>("window_height"),
                     state.get<ImVec4>("bg_color"));
        // fontManager.reset(window.io());
      }
    }
  } catch (const std::exception& e) {
    omdi::logger::Error("Fatal exception %s", e.what());
    return 1;
  } catch (...) {
    omdi::logger::Error("Unknown fatal exception");
    return 1;
  }
  return 0;
}
