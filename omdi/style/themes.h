#ifndef UI_THEMES_THEMES_H
#define UI_THEMES_THEMES_H

#include <imgui.h>

#include <string>

namespace ui::themes {

  constexpr const char* ALL_THEMES[] = {
    "default",        "darkness",       "grey",          "light",  "ue4",
    "enemymouse",     "nord",           "photoshop",     "cherry", "dracula",
    "ledsynthmaster", "spectrum-light", "spectrum-dark",
  };

  void picker(const std::string&, ImGuiStyle&);

  void darkness(ImGuiStyle&);
  void dracula(ImGuiStyle&);
  void nord(ImGuiStyle&);
  void grey(ImGuiStyle&);
  void photoshop(ImGuiStyle&);
  void cherry(ImGuiStyle&);
  void ue4(ImGuiStyle&);
  void light(ImGuiStyle&);
  void ledsynthmaster(ImGuiStyle&);
  void enemymouse(ImGuiStyle&);

  template <bool IsDark = false>
  void spectrum(ImGuiStyle&);
} // namespace ui::themes

#endif // UI_THEMES_THEMES_H
