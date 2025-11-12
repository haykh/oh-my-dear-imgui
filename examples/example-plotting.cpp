#include "examples/field.h"
#include "examples/pointcloud.h"

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

    // auto sim = omdi::examples::RotatingPointcloud({
    //   { "athenians", 1000 },
    //   {  "spartans",  300 },
    //   {   "thebans",  500 }
    // });
    // plots.push_back(new omdi::ScatterPlot { sim.get_data(), "ParticlesScatter" });

    auto sim = omdi::examples::OscillatingFields(
      {
        { "Wave1",
         [](float x, float y, double t) {
            return std::sin(x * (2.0 * M_PI) + 0.25 * t) *
                   std::cos(y * (2.0 * M_PI) + 0.2 * t);
            // return std::cos(y + 0.2 * t);
            // return std::sin(x + 0.2 * t);
          } },
        //        { "Wave2",
        //         [](float x, float y, double t) {
        // return std::sin(2.0f * x - 0.5 * t) * std::cos(0.5f * y + 0.5 * t);
        // } },
        //        { "Wave3",
        //         [](float x, float y, double t) {
        // return std::sin(0.5f * x - t * t) * std::cos(2.0f * y - t * t);
        // } }
    },
      { -2.0f, 2.0f, 1024 },
      { -3.0f, 3.0f, 1280 });

    plots.push_back(new omdi::PcolorPlot { sim.get_data(), "FieldsScatter" });

    app.Init(&state);
    app.Render(&state, [&]() {
      for (auto& plot : plots) {
        plot->plot();
      }
      // sim.update(timer.elapsed(), timer.delta());
      omdi::logger::Log("FPS: %.3f", 1.0 / timer.delta());
      timer.tick();
      // ImGui::ShowDemoWindow();
      // ImPlot::ShowDemoWindow();
      // if (ImPlot::BeginPlot("Scatter", ImVec2(-1, -1), ImPlotFlags_Equal)) {
      //   ImPlot::PlotScatter("Particles", xPos, yPos, npoints);
      //   ImPlot::EndPlot();
      // }
    });

  } catch (const std::exception& e) {
    return 1;
  } catch (...) {
    return 1;
  }
  return 0;
}
