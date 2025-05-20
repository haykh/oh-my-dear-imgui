#ifndef UI_FONTS_H
#define UI_FONTS_H

#include <imgui.h>

#include <map>
#include <string>
#include <utility>
#include <vector>

namespace ui::fonts {

  enum Type {
    Text = 0,
    Icon = 1,
  };

  enum Size {

    Small  = 12,
    Normal = 16,
    Large  = 24,
    Huge   = 32,
  };

  class FontManager {
    std::map<Size, ImFont*> m_textfonts;
    std::map<Size, ImFont*> m_iconfonts;

  public:
    auto get(Type, Size) -> ImFont*;

    void clear(ImGuiIO*) const;
    void build(ImGuiIO*) const;

    void add(ImGuiIO*, Type, Size, const void*, int, const ImWchar* = nullptr);
    void add(ImGuiIO*, Type, Size, const std::string&, const ImWchar* = nullptr);
    void add(ImGuiIO*,
             Type,
             Size,
             const std::vector<std::pair<const void*, int>>&,
             const ImWchar* = nullptr);

    void addFontAwesomeIcons(ImGuiIO*, Size);

    void resetMainFont(ImGuiIO* io, const void*, int);
  };

  auto AddFontFromMem(ImGuiIO*,
                      const void*,
                      int,
                      ImFontConfig*  = nullptr,
                      const ImWchar* = nullptr,
                      float          = 16.f) -> ImFont*;

  auto AddFontFromTTF(ImGuiIO*,
                      const char*,
                      ImFontConfig*  = nullptr,
                      const ImWchar* = nullptr,
                      float          = 16.f) -> ImFont*;

  void AddFontAwesomeIcons(ImGuiIO*, float = 16.f);
  void SetDefaultFonts(ImGuiIO*);

} // namespace ui::fonts

#endif // UI_FONTS_H
