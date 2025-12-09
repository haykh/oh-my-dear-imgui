#ifndef CORE_DEFAULTS_H
#define CORE_DEFAULTS_H

#include <imgui.h>

namespace omdi::defaults {

  constexpr int    WINDOW_WIDTH      = 1280;
  constexpr int    WINDOW_HEIGHT     = 720;
  constexpr int    THEME_IDX         = 0;
  constexpr int    MAIN_FONT_IDX     = 0;
  constexpr int    MAIN_FONTSIZE_IDX = 1;
  constexpr ImVec4 BG_COLOR          = ImVec4 { 0.24f, 0.24f, 0.24f, 1.00f };

} // namespace omdi::defaults

#endif // CORE_DEFAULTS_H
