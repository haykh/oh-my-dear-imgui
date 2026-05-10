#include <imgui.h>
#include <implot.h>
#include <omdi.hpp>

#include <atomic>
#include <map>
#include <mutex>
#include <string>
#include <thread>
#include <utility>
#include <vector>

auto main(int argc, char* argv[]) -> int {
  std::mutex        mutex;
  std::atomic<bool> running { true };

  std::map<std::string, omdi::Points> snap1;
  auto sim1 = omdi::examples::RotatingPointcloud({
    { "athenians", 1000 },
    {  "spartans",  300 },
    {   "thebans",  500 }
  });

  std::map<std::string, omdi::GridXY> snap2;
  auto                                sim2 = omdi::examples::OscillatingFields(
    {
      { "Wavey",
       [](float x, float y, double t) {
          return std::sin(x * (2.0 * M_PI) + 0.25 * t) *
                 std::cos(y * (2.0 * M_PI) + 0.2 * t) * std::exp(-4.0 * (x * x));
        } },
  },
    { -2.0f, 2.0f, 128 },
    { -3.0f, 3.0f, 256 });

  auto        sim_timer = omdi::utils::Timer();
  std::thread sim_thread([&]() {
    while (running) {
      sim1.update(sim_timer.elapsed(), sim_timer.delta());
      sim2.update(sim_timer.elapsed(), sim_timer.delta());
      sim_timer.tick();
      std::lock_guard lock(mutex);
      snap1 = sim1.get_data();
      snap2 = sim2.get_data();
    }
  });

  try {

    omdi::logger::Init();
    auto state = omdi::State();
    state.set("window_width", 1920);
    state.set("window_height", 1080);
    auto app   = omdi::App(&state);
    auto timer = omdi::utils::Timer();

    auto plots = std::vector<omdi::Plot*> {};

    auto scatter = omdi::ScatterPlot { "ScatterExample" };
    auto pcolor  = omdi::PcolorPlot { "PcolorExample" };

    plots.push_back(&scatter);
    plots.push_back(&pcolor);

    app.Init(&state);
    app.Render(&state, [&]() {
      {
        std::lock_guard lock(mutex);

        if (!snap1.empty()) {
          scatter.update_all(std::move(snap1));
        }
        if (!snap2.empty()) {
          pcolor.update_all(std::move(snap2));
        }
      }

      for (auto& plot : plots) {
        if (ImGui::Begin(plot->label().c_str())) {
          plot->plot();
          ImGui::End();
        }
      }
      omdi::logger::Log("FPS: %.3f", 1.0 / timer.delta());
      timer.tick();
    });
  } catch (const std::exception& e) {
    omdi::logger::Fatal("Exception: %s", e.what());
  }
  running = false;
  sim_thread.join();
  return 0;
}
