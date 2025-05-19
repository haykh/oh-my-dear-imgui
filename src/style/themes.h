#ifndef UI_THEMES_THEMES_H
#define UI_THEMES_THEMES_H

#include <imgui.h>

#include <string>

namespace ui::themes {

  constexpr const char* ALL_THEMES[] = { "default", "dark", "dracula",
                                         "nord",    "grey", "photoshop",
                                         "cherry",  "ue4",  "light" };

  void picker(const std::string&, ImGuiStyle&);

  void dark(ImGuiStyle&);
  void dracula(ImGuiStyle&);
  void nord(ImGuiStyle&);
  void grey(ImGuiStyle&);
  void photoshop(ImGuiStyle&);
  void cherry(ImGuiStyle&);
  void ue4(ImGuiStyle&);
  void light(ImGuiStyle&);

} // namespace ui::themes

#endif // UI_THEMES_THEMES_H
