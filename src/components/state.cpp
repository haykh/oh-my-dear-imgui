#include "components/state.h"

#include <string>

namespace ui::state {

  bool State::has(const std::string& key) const {
    return m_state_vars.find(key) != m_state_vars.end();
  }

  void State::remove(const std::string& key) {
    m_state_vars.erase(key);
  }

} // namespace ui::state
