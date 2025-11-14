#include "examples/field.h"
#include "examples/pointcloud.h"
#include "examples/sim.h"

#include <imgui.h>
#include <implot.h>
#include <omdi.hpp>

auto main(int argc, char* argv[]) -> int {
  try {
    omdi::logger::Init();
    auto state = omdi::State();
    state.set("window_width", 1920);
    state.set("window_height", 1080);
    auto app   = omdi::App(&state);
    auto timer = omdi::timer::Timer();

    auto plots = std::vector<omdi::Plot*> {};

    auto sim1 = omdi::examples::RotatingPointcloud({
      { "athenians", 1000 },
      {  "spartans",  300 },
      {   "thebans",  500 }
    });

    auto sim2 = omdi::examples::OscillatingFields(
      {
        { "Wavey",
         [](float x, float y, double t) {
            return std::sin(x * (2.0 * M_PI) + 0.25 * t) *
                   std::cos(y * (2.0 * M_PI) + 0.2 * t);
          } },
    },
      { -2.0f, 2.0f, 128 },
      { -3.0f, 3.0f, 256 });

    plots.push_back(new omdi::ScatterPlot { sim1.get_data(), "ScatterExample" });
    plots.push_back(new omdi::PcolorPlot { sim2.get_data(), "PcolorExample" });

    app.Init(&state);
    app.Render(&state, [&]() {
      for (auto& plot : plots) {
        if (ImGui::Begin(plot->label().c_str())) {
          plot->plot();
          ImGui::End();
        }
      }
      for (auto sim : std::vector<omdi::examples::Sim*> { &sim1, &sim2 }) {
        sim->update(timer.elapsed(), timer.delta());
      }
      omdi::logger::Log("FPS: %.3f", 1.0 / timer.delta());
      timer.tick();
      // ImGui::ShowDemoWindow();
      // ImPlot::ShowDemoWindow();
    });

  } catch (const std::exception& e) {
    return 1;
  } catch (...) {
    return 1;
  }
  return 0;
}
