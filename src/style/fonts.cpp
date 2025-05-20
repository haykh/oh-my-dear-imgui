#include "style/fonts.h"

// #include "assets/generated/MonaspaceKryptonFrozen-Regular.h"
#include "assets/generated/fa-regular-400.h"
#include "assets/generated/fa-solid-900.h"
#include "icons.h"

#include <imgui.h>
#include <plog/Log.h>

#include <utility>
#include <vector>

namespace ui::fonts {

  auto FontManager::get(Type type, Size size) -> ImFont* {
    if (type == Type::Text) {
      auto it = m_textfonts.find(size);
      if (it != m_textfonts.end()) {
        return it->second;
      } else {
        PLOGE << "Font not found for size: " << size;
        throw std::runtime_error("Font not found");
      }
    } else if (type == Type::Icon) {
      auto it = m_iconfonts.find(size);
      if (it != m_iconfonts.end()) {
        return it->second;
      } else {
        PLOGE << "Font not found for size: " << size;
        throw std::runtime_error("Font not found");
      }
    } else {
      PLOGE << "Invalid font type: " << type;
      throw std::runtime_error("Invalid font type");
    }
  }

  void FontManager::clear(ImGuiIO* io) const {
    io->Fonts->Clear();
  }

  void FontManager::build(ImGuiIO* io) const {
    io->Fonts->Build();
  }

  void FontManager::add(ImGuiIO*       io,
                        Type           type,
                        Size           size,
                        const void*    data,
                        int            data_size,
                        const ImWchar* ranges) {
    auto        font_config = new ImFontConfig();
    const float font_size   = static_cast<float>(size);
    font_config->PixelSnapH = true;
    if (type == Type::Text) {
      m_textfonts[size] = io->Fonts->AddFontFromMemoryCompressedTTF(data,
                                                                    data_size,
                                                                    font_size,
                                                                    font_config,
                                                                    ranges);
    } else if (type == Type::Icon) {
      m_iconfonts[size] = io->Fonts->AddFontFromMemoryCompressedTTF(data,
                                                                    data_size,
                                                                    font_size,
                                                                    font_config,
                                                                    ranges);
    }
  }

  void FontManager::add(ImGuiIO*           io,
                        Type               type,
                        Size               size,
                        const std::string& fontfile,
                        const ImWchar*     ranges) {
    auto        font_config = new ImFontConfig();
    const float font_size   = static_cast<float>(size);
    font_config->PixelSnapH = true;
    if (type == Type::Text) {
      m_textfonts[size] = io->Fonts->AddFontFromFileTTF(fontfile.c_str(),
                                                        font_size,
                                                        font_config,
                                                        ranges);
    } else if (type == Type::Icon) {
      m_iconfonts[size] = io->Fonts->AddFontFromFileTTF(fontfile.c_str(),
                                                        font_size,
                                                        font_config,
                                                        ranges);
    }
  }

  void FontManager::add(ImGuiIO*                                        io,
                        Type                                            type,
                        Size                                            size,
                        const std::vector<std::pair<const void*, int>>& data,
                        const ImWchar* ranges) {
    auto        font_config = new ImFontConfig();
    const float font_size   = static_cast<float>(size);
    font_config->PixelSnapH = true;
    font_config->MergeMode  = true;
    for (const auto& [font_data, font_data_size] : data) {
      if (type == Type::Text) {
        m_textfonts[size] = io->Fonts->AddFontFromMemoryCompressedTTF(font_data,
                                                                      font_data_size,
                                                                      font_size,
                                                                      font_config,
                                                                      ranges);
      } else if (type == Type::Icon) {
        m_iconfonts[size] = io->Fonts->AddFontFromMemoryCompressedTTF(font_data,
                                                                      font_data_size,
                                                                      font_size,
                                                                      font_config,
                                                                      ranges);
      }
    }
  }

  void FontManager::addFontAwesomeIcons(ImGuiIO* io, Size size) {
    static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
    add(io,
        ui::fonts::Type::Icon,
        size,
        {
          { fa_regular_400_compressed_data, fa_regular_400_compressed_size },
          {   fa_solid_900_compressed_data,   fa_solid_900_compressed_size }
    },
        icon_ranges);
  };

  void FontManager::resetMainFont(ImGuiIO* io, const void* data, int data_size) {
    clear(io);
    for (auto& size : { Size::Normal, Size::Small, Size::Large, Size::Huge }) {
      add(io, ui::fonts::Type::Text, size, data, data_size);
      addFontAwesomeIcons(io, size);
    }
    build(io);
  }

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
