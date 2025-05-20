#include "style/fonts.h"

#include "assets/generated/JetBrainsMono-Regular.h"
#include "assets/generated/MonaspaceKryptonFrozen-Regular.h"
#include "assets/generated/MonaspaceRadonFrozen-Regular.h"
#include "assets/generated/fa-regular-400.h"
#include "assets/generated/fa-solid-900.h"
#include "assets/generated/xkcd-script.h"
#include "icons.h"

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <plog/Log.h>

#include <algorithm>
#include <stdexcept>
#include <string>

namespace ui::fonts {

  auto FontManager::font(const std::string& name, Size size) -> ImFont* {
    auto it = m_fonts.find(name);
    if (it != m_fonts.end()) {
      auto it2 = it->second.find(size);
      if (it2 != it->second.end()) {
        return it2->second;
      } else {
        PLOGE << "Font size not found for name: " << name << ", size: " << size;
        throw std::runtime_error("Font size not found");
      }
    } else {
      PLOGE << "Font not found for size: " << size;
      throw std::runtime_error("Font not found");
    }
  }

  auto FontManager::icon(const std::string& name, Size size) -> ImFont* {
    auto it = m_icons.find(name);
    if (it != m_icons.end()) {
      auto it2 = it->second.find(size);
      if (it2 != it->second.end()) {
        return it2->second;
      } else {
        PLOGE << "Icon size not found for name: " << name << ", size: " << size;
        throw std::runtime_error("Icon size not found");
      }
    } else {
      PLOGE << "Icon not found for size: " << size;
      throw std::runtime_error("Icon not found");
    }
  }

  auto FontManager::fontnames() const -> std::vector<const char*> {
    std::vector<const char*> names;
    for (const auto& name : m_font_list) {
      names.push_back(name.c_str());
    }
    return names;
  }

  void FontManager::setActiveFont(ImGuiIO* io, int font_idx, int fontsize_idx) {
    if (font_idx >= m_font_list.size()) {
      PLOGE << "Font index out of range: " << font_idx;
      throw std::runtime_error("Font index out of range");
    }
    const auto font_name = m_font_list[font_idx];
    if (fontsize_idx < 0 || fontsize_idx >= 4) {
      PLOGE << "Font size index out of range: " << fontsize_idx;
      throw std::runtime_error("Font size index out of range");
    }
    const auto fontsize = SIZES[fontsize_idx];
    if (m_fonts.find(font_name) == m_fonts.end()) {
      PLOGE << "Font not found: " << font_name;
      throw std::runtime_error("Font not found");
    }
    if (m_fonts[font_name].find(fontsize) == m_fonts[font_name].end()) {
      PLOGE << "Font size not found: " << fontsize;
      throw std::runtime_error("Font size not found");
    }

    m_active_font_idx  = font_idx;
    m_active_font      = font_name;
    m_active_font_size = fontsize;

    io->FontDefault = m_fonts[font_name][fontsize];
  }

  void FontManager::initFonts(ImGuiIO* io) {
    clear(io);

    for (auto& size : { Size::Small, Size::Normal, Size::Large, Size::Huge }) {
      add(io,
          "MonaspaceKr",
          size,
          MonaspaceKryptonFrozen_Regular_compressed_data,
          MonaspaceKryptonFrozen_Regular_compressed_size);
      add(io,
          "MonaspaceRn",
          size,
          MonaspaceRadonFrozen_Regular_compressed_data,
          MonaspaceRadonFrozen_Regular_compressed_size);
      add(io,
          "JetBrainsMono",
          size,
          JetBrainsMono_Regular_compressed_data,
          JetBrainsMono_Regular_compressed_size);
      add(io,
          "xkcd-script",
          size,
          xkcd_script_compressed_data,
          xkcd_script_compressed_size);
    }
    build(io);
  }

  void FontManager::clear(ImGuiIO* io) const {
    io->Fonts->Clear();
  }

  void FontManager::build(ImGuiIO* io) const {
    io->Fonts->Build();
  }

  void FontManager::add(ImGuiIO*           io,
                        const std::string& name,
                        Size               size,
                        const void*        data,
                        int                data_size,
                        const ImWchar*     ranges) {
    const float font_size = static_cast<float>(size);

    auto font_config        = new ImFontConfig();
    font_config->PixelSnapH = true;

    static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };

    auto icon_config        = new ImFontConfig();
    icon_config->PixelSnapH = true;
    icon_config->MergeMode  = true;

    auto it = m_fonts.find(name);

    if (it == m_fonts.end()) {
      m_fonts[name] = {};
    }
    auto it2 = m_fonts[name].find(size);
    if (it2 != m_fonts[name].end()) {
      PLOGW << "Font already exists: " << name << ", size: " << size;
    } else {
      m_fonts[name][size] = io->Fonts->AddFontFromMemoryCompressedTTF(data,
                                                                      data_size,
                                                                      font_size,
                                                                      font_config,
                                                                      ranges);
      if (std::find(m_font_list.begin(), m_font_list.end(), name) ==
          m_font_list.end()) {
        m_font_list.push_back(name);
      }
    }
    io->Fonts->AddFontFromMemoryCompressedTTF(fa_regular_400_compressed_data,
                                              fa_regular_400_compressed_size,
                                              static_cast<float>(size),
                                              icon_config,
                                              icon_ranges);
    io->Fonts->AddFontFromMemoryCompressedTTF(fa_solid_900_compressed_data,
                                              fa_solid_900_compressed_size,
                                              static_cast<float>(size),
                                              icon_config,
                                              icon_ranges);
  }

  void FontManager::add(ImGuiIO*           io,
                        const std::string& name,
                        Size               size,
                        const std::string& fontfile,
                        const ImWchar*     ranges) {
    auto        font_config = new ImFontConfig();
    const float font_size   = static_cast<float>(size);
    font_config->PixelSnapH = true;
    auto it                 = m_fonts.find(name);
    if (it == m_fonts.end()) {
      m_fonts[name] = {};
    }
    auto it2 = m_fonts[name].find(size);
    if (it2 != m_fonts[name].end()) {
      PLOGW << "Font already exists: " << name << ", size: " << size;
    } else {
      m_fonts[name][size] = io->Fonts->AddFontFromFileTTF(fontfile.c_str(),
                                                          font_size,
                                                          font_config,
                                                          ranges);
      if (std::find(m_font_list.begin(), m_font_list.end(), name) ==
          m_font_list.end()) {
        m_font_list.push_back(name);
      }
    }
  }

  // void FontManager::reset(ImGuiIO* io) {
  //   if (m_staged_data != std::pair<const void*, int> {}) {
  //     clear(io);
  //     for (auto& size : { Size::Normal, Size::Small, Size::Large, Size::Huge }) {
  //       add(io, ui::fonts::Type::Text, size, m_staged_data.first, m_staged_data.second);
  //       addFontAwesomeIcons(io, size);
  //     }
  //     build(io);
  //     ImGui_ImplOpenGL3_CreateDeviceObjects();
  //     m_staged_data = {};
  //   } else if (!m_staged_fontfile.empty()) {
  //     clear(io);
  //     for (auto& size : { Size::Normal, Size::Small, Size::Large, Size::Huge }) {
  //       add(io, ui::fonts::Type::Text, size, m_staged_fontfile);
  //       addFontAwesomeIcons(io, size);
  //     }
  //     build(io);
  //     ImGui_ImplOpenGL3_CreateDeviceObjects();
  //     m_staged_fontfile = "";
  //   }
  // }

  // auto AddFontFromMem(ImGuiIO*       io,
  //                     const void*    font_data,
  //                     int            font_data_size,
  //                     ImFontConfig*  font_config,
  //                     const ImWchar* ranges,
  //                     float          font_size) -> ImFont* {
  //   if (font_config == nullptr) {
  //     font_config = new ImFontConfig();
  //   }
  //   font_config->PixelSnapH = true;
  //   return io->Fonts->AddFontFromMemoryCompressedTTF(font_data,
  //                                                    font_data_size,
  //                                                    font_size,
  //                                                    font_config,
  //                                                    ranges);
  // }
  //
  // auto AddFontFromTTF(ImGuiIO*       io,
  //                     const char*    font_path,
  //                     ImFontConfig*  font_config,
  //                     const ImWchar* ranges,
  //                     float          font_size) -> ImFont* {
  //   if (font_config == nullptr) {
  //     font_config = new ImFontConfig();
  //   }
  //   font_config->PixelSnapH = true;
  //   return io->Fonts->AddFontFromFileTTF(font_path, font_size, font_config, ranges);
  // }
  //
  // void AddFontAwesomeIcons(ImGuiIO* io, float font_size) {
  //   ImFontConfig icons_config;
  //   icons_config.MergeMode              = true;
  //   static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
  //
  //   AddFontFromMem(io,
  //                  fa_regular_400_compressed_data,
  //                  fa_regular_400_compressed_size,
  //                  &icons_config,
  //                  icons_ranges,
  //                  font_size);
  //   AddFontFromMem(io,
  //                  fa_solid_900_compressed_data,
  //                  fa_solid_900_compressed_size,
  //                  &icons_config,
  //                  icons_ranges,
  //                  font_size);
  // }
  //
  // void SetDefaultFonts(ImGuiIO* io) {
  //   ImFont* default_font = io->Fonts->AddFontDefault();
  //   BuildFonts(io);
  //   const float default_font_size = (16.0 / 13.0) * default_font->FontSize;
  //   ClearFonts(io);
  //
  //   AddFontFromMem(io,
  //                  MonaspaceKryptonFrozen_Regular_compressed_data,
  //                  MonaspaceKryptonFrozen_Regular_compressed_size,
  //                  nullptr,
  //                  nullptr,
  //                  default_font_size);
  //   // AddFontFromTTF(io, "src/style/xkcd-script.ttf", nullptr, nullptr, 24.f);
  //
  //   AddFontAwesomeIcons(io, default_font_size);
  //   BuildFonts(io);
  // }

} // namespace ui::fonts
