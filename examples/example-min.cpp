#include <omdi.hpp>

auto main(int argc, char* argv[]) -> int {
  try {
    auto state = omdi::state::State();
    auto app   = omdi::app::App(&state);

    app.Init(&state);
    app.Render(&state);

  } catch (const std::exception& e) {
    return 1;
  } catch (...) {
    return 1;
  }
  return 0;
}
