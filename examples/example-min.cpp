#include <omdi.hpp>

auto main(int argc, char* argv[]) -> int {
  try {
    auto state = omdi::State();
    auto app   = omdi::App(&state);

    app.Init(&state);
    app.Render(&state);

  } catch (const std::exception& e) {
    return 1;
  } catch (...) {
    return 1;
  }
  return 0;
}
