#ifndef UI_FONTS_H
#define UI_FONTS_H

#include <imgui.h>
#include <plog/Log.h>

#include <map>
#include <string>
#include <vector>

namespace ui::fonts {

  enum Size : int {
    None   = 0,
    Small  = 12,
    Normal = 16,
    Large  = 24,
    Huge   = 32,
  };

  class FontManager {
    std::map<std::string, std::map<Size, ImFont*>> m_fonts;
    std::map<std::string, std::map<Size, ImFont*>> m_icons;

    std::vector<std::string> m_font_list;

    int         m_active_font_idx { -1 };
    std::string m_active_font { "" };
    Size        m_active_font_size { Size::None };

  public:
    static constexpr Size SIZES[] = { Small, Normal, Large, Huge };

    [[nodiscard]]
    auto font(const std::string&, Size) -> ImFont*;

    [[nodiscard]]
    auto icon(const std::string&, Size) -> ImFont*;

    [[nodiscard]]
    auto fontnames() const -> std::vector<const char*>;

    [[nodiscard]]
    auto active_font() const -> std::string {
      return m_active_font;
    }

    [[nodiscard]]
    auto active_font_idx() const -> int {
      return m_active_font_idx;
    }

    [[nodiscard]]
    auto active_font_size() const -> Size {
      return m_active_font_size;
    }

    void initFonts(ImGuiIO*);
    void setActiveFont(ImGuiIO*, int, int);

    void clear(ImGuiIO*) const;
    void build(ImGuiIO*) const;

    void add(ImGuiIO*, const std::string&, Size, const void*, int, const ImWchar* = nullptr);
    void add(ImGuiIO*,
             const std::string&,
             Size,
             const std::string&,
             const ImWchar* = nullptr);

    // void resetMainFont(const void*, int);
    // void resetMainFont(const std::string&);

    // void reset(ImGuiIO* io);
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
