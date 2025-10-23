#include "style/themes.h"

#include "utils.h"

#include <imgui.h>

#include <string>

namespace omdi::themes {

  void picker(const std::string& theme, ImGuiStyle& style) {
    style = ImGuiStyle();
    ImGui::StyleColorsDark(&style);
    if (theme == "default") {
      return;
    } else if (theme == "darkness") {
      darkness(style);
    } else if (theme == "dracula") {
      dracula(style);
    } else if (theme == "nord") {
      nord(style);
    } else if (theme == "grey") {
      grey(style);
    } else if (theme == "photoshop") {
      photoshop(style);
    } else if (theme == "cherry") {
      cherry(style);
    } else if (theme == "ue4") {
      ue4(style);
    } else if (theme == "spectrum-dark") {
      spectrum<true>(style);
    } else if (theme == "enemymouse") {
      enemymouse(style);
    } else if (theme == "light") {
      ImGui::StyleColorsLight(&style);
      light(style);
    } else if (theme == "ledsynthmaster") {
      ImGui::StyleColorsLight(&style);
      ledsynthmaster(style);
    } else if (theme == "spectrum-light") {
      ImGui::StyleColorsLight(&style);
      spectrum<false>(style);
    } else {
      omdi::logger::Fatal("Unknown theme: %s", theme.c_str());
    }
  }

  void darkness(ImGuiStyle& style) {
    ImVec4* colors                         = style.Colors;
    colors[ImGuiCol_Text]                  = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled]          = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg]              = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_ChildBg]               = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg]               = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
    colors[ImGuiCol_Border]                = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
    colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
    colors[ImGuiCol_FrameBg]               = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
    colors[ImGuiCol_FrameBgActive]         = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_TitleBg]               = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TitleBgActive]         = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_MenuBarBg]             = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
    colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
    colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
    colors[ImGuiCol_CheckMark]             = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    colors[ImGuiCol_SliderGrab]            = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
    colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
    colors[ImGuiCol_Button]                = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_ButtonHovered]         = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
    colors[ImGuiCol_ButtonActive]          = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_Header]                = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_HeaderHovered]         = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
    colors[ImGuiCol_HeaderActive]          = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
    colors[ImGuiCol_Separator]             = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_SeparatorHovered]      = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
    colors[ImGuiCol_SeparatorActive]       = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
    colors[ImGuiCol_ResizeGrip]            = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
    colors[ImGuiCol_ResizeGripActive]      = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
    colors[ImGuiCol_Tab]                   = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TabHovered]            = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_TabActive]             = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
    colors[ImGuiCol_TabUnfocused]          = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TabUnfocusedActive]    = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_DockingPreview]        = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    colors[ImGuiCol_DockingEmptyBg]        = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotLines]             = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]      = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogram]         = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TableHeaderBg]         = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TableBorderStrong]     = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TableBorderLight]      = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_TableRowBg]            = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt]         = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_DragDropTarget]        = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    colors[ImGuiCol_NavHighlight]          = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg]     = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg]      = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);

    style.WindowPadding     = ImVec2(8.00f, 8.00f);
    style.FramePadding      = ImVec2(5.00f, 2.00f);
    style.CellPadding       = ImVec2(6.00f, 6.00f);
    style.ItemSpacing       = ImVec2(6.00f, 6.00f);
    style.ItemInnerSpacing  = ImVec2(6.00f, 6.00f);
    style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
    style.IndentSpacing     = 25;
    style.ScrollbarSize     = 15;
    style.GrabMinSize       = 10;
    style.WindowBorderSize  = 1;
    style.ChildBorderSize   = 1;
    style.PopupBorderSize   = 1;
    style.FrameBorderSize   = 1;
    style.TabBorderSize     = 1;
    style.WindowRounding    = 7;
    style.ChildRounding     = 4;
    style.FrameRounding     = 3;
    style.PopupRounding     = 4;
    style.ScrollbarRounding = 9;
    style.GrabRounding      = 3;
    style.LogSliderDeadzone = 4;
    style.TabRounding       = 4;
  }

  void dracula(ImGuiStyle& style) {
    auto colors                = style.Colors;
    colors[ImGuiCol_WindowBg]  = ImVec4(0.1f, 0.1f, 0.13f, 1.0f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.16f, 0.16f, 0.21f, 1.0f);

    // Border
    colors[ImGuiCol_Border]       = ImVec4(0.44f, 0.37f, 0.61f, 0.29f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.24f);

    // Text
    colors[ImGuiCol_Text]         = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);

    // Headers
    colors[ImGuiCol_Header]        = ImVec4(0.13f, 0.13f, 0.17, 1.0f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.19f, 0.2f, 0.25f, 1.0f);
    colors[ImGuiCol_HeaderActive]  = ImVec4(0.16f, 0.16f, 0.21f, 1.0f);

    // Buttons
    colors[ImGuiCol_Button]        = ImVec4(0.13f, 0.13f, 0.17, 1.0f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.2f, 0.25f, 1.0f);
    colors[ImGuiCol_ButtonActive]  = ImVec4(0.16f, 0.16f, 0.21f, 1.0f);
    colors[ImGuiCol_CheckMark]     = ImVec4(0.74f, 0.58f, 0.98f, 1.0f);

    // Popups
    colors[ImGuiCol_PopupBg] = ImVec4(0.1f, 0.1f, 0.13f, 0.92f);

    // Slider
    colors[ImGuiCol_SliderGrab]       = ImVec4(0.44f, 0.37f, 0.61f, 0.54f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.74f, 0.58f, 0.98f, 0.54f);

    // Frame BG
    colors[ImGuiCol_FrameBg]        = ImVec4(0.13f, 0.13, 0.17, 1.0f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.2f, 0.25f, 1.0f);
    colors[ImGuiCol_FrameBgActive]  = ImVec4(0.16f, 0.16f, 0.21f, 1.0f);

    // Tabs
    colors[ImGuiCol_Tab]                = ImVec4(0.16f, 0.16f, 0.21f, 1.0f);
    colors[ImGuiCol_TabHovered]         = ImVec4(0.24, 0.24f, 0.32f, 1.0f);
    colors[ImGuiCol_TabActive]          = ImVec4(0.2f, 0.22f, 0.27f, 1.0f);
    colors[ImGuiCol_TabUnfocused]       = ImVec4(0.16f, 0.16f, 0.21f, 1.0f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.16f, 0.16f, 0.21f, 1.0f);

    // Title
    colors[ImGuiCol_TitleBg]          = ImVec4(0.16f, 0.16f, 0.21f, 1.0f);
    colors[ImGuiCol_TitleBgActive]    = ImVec4(0.16f, 0.16f, 0.21f, 1.0f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.16f, 0.16f, 0.21f, 1.0f);

    // Scrollbar
    colors[ImGuiCol_ScrollbarBg]          = ImVec4(0.1f, 0.1f, 0.13f, 1.0f);
    colors[ImGuiCol_ScrollbarGrab]        = ImVec4(0.16f, 0.16f, 0.21f, 1.0f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.19f, 0.2f, 0.25f, 1.0f);
    colors[ImGuiCol_ScrollbarGrabActive]  = ImVec4(0.24f, 0.24f, 0.32f, 1.0f);

    // Seperator
    colors[ImGuiCol_Separator]        = ImVec4(0.44f, 0.37f, 0.61f, 1.0f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.74f, 0.58f, 0.98f, 1.0f);
    colors[ImGuiCol_SeparatorActive]  = ImVec4(0.84f, 0.58f, 1.0f, 1.0f);

    // Resize Grip
    colors[ImGuiCol_ResizeGrip]        = ImVec4(0.44f, 0.37f, 0.61f, 0.29f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.74f, 0.58f, 0.98f, 0.29f);
    colors[ImGuiCol_ResizeGripActive]  = ImVec4(0.84f, 0.58f, 1.0f, 0.29f);

    // Docking
    colors[ImGuiCol_DockingPreview] = ImVec4(0.44f, 0.37f, 0.61f, 1.0f);

    style.TabRounding       = 4;
    style.ScrollbarRounding = 9;
    style.WindowRounding    = 7;
    style.GrabRounding      = 3;
    style.FrameRounding     = 3;
    style.PopupRounding     = 4;
    style.ChildRounding     = 4;
  }

  void nord(ImGuiStyle& style) {
    auto colors = style.Colors;

    // Base colors for a pleasant and modern dark theme with dark accents
    colors[ImGuiCol_Text]                  = ImVec4(0.92f, 0.93f, 0.94f, 1.00f);
    colors[ImGuiCol_TextDisabled]          = ImVec4(0.50f, 0.52f, 0.54f, 1.00f);
    colors[ImGuiCol_WindowBg]              = ImVec4(0.14f, 0.14f, 0.16f, 1.00f);
    colors[ImGuiCol_ChildBg]               = ImVec4(0.16f, 0.16f, 0.18f, 1.00f);
    colors[ImGuiCol_PopupBg]               = ImVec4(0.18f, 0.18f, 0.20f, 1.00f);
    colors[ImGuiCol_Border]                = ImVec4(0.28f, 0.29f, 0.30f, 0.60f);
    colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg]               = ImVec4(0.20f, 0.22f, 0.24f, 1.00f);
    colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.22f, 0.24f, 0.26f, 1.00f);
    colors[ImGuiCol_FrameBgActive]         = ImVec4(0.24f, 0.26f, 0.28f, 1.00f);
    colors[ImGuiCol_TitleBg]               = ImVec4(0.14f, 0.14f, 0.16f, 1.00f);
    colors[ImGuiCol_TitleBgActive]         = ImVec4(0.16f, 0.16f, 0.18f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.14f, 0.14f, 0.16f, 1.00f);
    colors[ImGuiCol_MenuBarBg]             = ImVec4(0.20f, 0.20f, 0.22f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.16f, 0.16f, 0.18f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.24f, 0.26f, 0.28f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.28f, 0.30f, 0.32f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.32f, 0.34f, 0.36f, 1.00f);
    colors[ImGuiCol_CheckMark]             = ImVec4(0.46f, 0.56f, 0.66f, 1.00f);
    colors[ImGuiCol_SliderGrab]            = ImVec4(0.36f, 0.46f, 0.56f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.40f, 0.50f, 0.60f, 1.00f);
    colors[ImGuiCol_Button]                = ImVec4(0.24f, 0.34f, 0.44f, 1.00f);
    colors[ImGuiCol_ButtonHovered]         = ImVec4(0.28f, 0.38f, 0.48f, 1.00f);
    colors[ImGuiCol_ButtonActive]          = ImVec4(0.32f, 0.42f, 0.52f, 1.00f);
    colors[ImGuiCol_Header]                = ImVec4(0.24f, 0.34f, 0.44f, 1.00f);
    colors[ImGuiCol_HeaderHovered]         = ImVec4(0.28f, 0.38f, 0.48f, 1.00f);
    colors[ImGuiCol_HeaderActive]          = ImVec4(0.32f, 0.42f, 0.52f, 1.00f);
    colors[ImGuiCol_Separator]             = ImVec4(0.28f, 0.29f, 0.30f, 1.00f);
    colors[ImGuiCol_SeparatorHovered]      = ImVec4(0.46f, 0.56f, 0.66f, 1.00f);
    colors[ImGuiCol_SeparatorActive]       = ImVec4(0.46f, 0.56f, 0.66f, 1.00f);
    colors[ImGuiCol_ResizeGrip]            = ImVec4(0.36f, 0.46f, 0.56f, 1.00f);
    colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.40f, 0.50f, 0.60f, 1.00f);
    colors[ImGuiCol_ResizeGripActive]      = ImVec4(0.44f, 0.54f, 0.64f, 1.00f);
    colors[ImGuiCol_Tab]                   = ImVec4(0.20f, 0.22f, 0.24f, 1.00f);
    colors[ImGuiCol_TabHovered]            = ImVec4(0.28f, 0.38f, 0.48f, 1.00f);
    colors[ImGuiCol_TabActive]             = ImVec4(0.24f, 0.34f, 0.44f, 1.00f);
    colors[ImGuiCol_TabUnfocused]          = ImVec4(0.20f, 0.22f, 0.24f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive]    = ImVec4(0.24f, 0.34f, 0.44f, 1.00f);
    colors[ImGuiCol_PlotLines]             = ImVec4(0.46f, 0.56f, 0.66f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]      = ImVec4(0.46f, 0.56f, 0.66f, 1.00f);
    colors[ImGuiCol_PlotHistogram]         = ImVec4(0.36f, 0.46f, 0.56f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(0.40f, 0.50f, 0.60f, 1.00f);
    colors[ImGuiCol_TableHeaderBg]         = ImVec4(0.20f, 0.22f, 0.24f, 1.00f);
    colors[ImGuiCol_TableBorderStrong]     = ImVec4(0.28f, 0.29f, 0.30f, 1.00f);
    colors[ImGuiCol_TableBorderLight]      = ImVec4(0.24f, 0.25f, 0.26f, 1.00f);
    colors[ImGuiCol_TableRowBg]            = ImVec4(0.20f, 0.22f, 0.24f, 1.00f);
    colors[ImGuiCol_TableRowBgAlt]         = ImVec4(0.22f, 0.24f, 0.26f, 1.00f);
    colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.24f, 0.34f, 0.44f, 0.35f);
    colors[ImGuiCol_DragDropTarget]        = ImVec4(0.46f, 0.56f, 0.66f, 0.90f);
    colors[ImGuiCol_NavHighlight]          = ImVec4(0.46f, 0.56f, 0.66f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg]     = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

    // Style adjustments
    style.WindowPadding     = ImVec2(8.00f, 8.00f);
    style.FramePadding      = ImVec2(5.00f, 2.00f);
    style.CellPadding       = ImVec2(6.00f, 6.00f);
    style.ItemSpacing       = ImVec2(6.00f, 6.00f);
    style.ItemInnerSpacing  = ImVec2(6.00f, 6.00f);
    style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
    style.IndentSpacing     = 25;
    style.ScrollbarSize     = 11;
    style.GrabMinSize       = 10;
    style.WindowBorderSize  = 1;
    style.ChildBorderSize   = 1;
    style.PopupBorderSize   = 1;
    style.FrameBorderSize   = 1;
    style.TabBorderSize     = 1;
    style.WindowRounding    = 7;
    style.ChildRounding     = 4;
    style.FrameRounding     = 3;
    style.PopupRounding     = 4;
    style.ScrollbarRounding = 9;
    style.GrabRounding      = 3;
    style.LogSliderDeadzone = 4;
    style.TabRounding       = 4;
  }

  void grey(ImGuiStyle& style) {
    ImVec4* colors = style.Colors;

    /// 0 = FLAT APPEARENCE
    /// 1 = MORE "3D" LOOK
    int is3D = 1;

    colors[ImGuiCol_Text]             = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled]     = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
    colors[ImGuiCol_ChildBg]          = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_WindowBg]         = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_PopupBg]          = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_Border]           = ImVec4(0.12f, 0.12f, 0.12f, 0.71f);
    colors[ImGuiCol_BorderShadow]     = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    colors[ImGuiCol_FrameBg]          = ImVec4(0.42f, 0.42f, 0.42f, 0.54f);
    colors[ImGuiCol_FrameBgHovered]   = ImVec4(0.42f, 0.42f, 0.42f, 0.40f);
    colors[ImGuiCol_FrameBgActive]    = ImVec4(0.56f, 0.56f, 0.56f, 0.67f);
    colors[ImGuiCol_TitleBg]          = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
    colors[ImGuiCol_TitleBgActive]    = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.17f, 0.17f, 0.17f, 0.90f);
    colors[ImGuiCol_MenuBarBg]        = ImVec4(0.335f, 0.335f, 0.335f, 1.000f);
    colors[ImGuiCol_ScrollbarBg]      = ImVec4(0.24f, 0.24f, 0.24f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab]    = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.52f, 0.52f, 0.52f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]  = ImVec4(0.76f, 0.76f, 0.76f, 1.00f);
    colors[ImGuiCol_CheckMark]            = ImVec4(0.65f, 0.65f, 0.65f, 1.00f);
    colors[ImGuiCol_SliderGrab]           = ImVec4(0.52f, 0.52f, 0.52f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]     = ImVec4(0.64f, 0.64f, 0.64f, 1.00f);
    colors[ImGuiCol_Button]               = ImVec4(0.54f, 0.54f, 0.54f, 0.35f);
    colors[ImGuiCol_ButtonHovered]        = ImVec4(0.52f, 0.52f, 0.52f, 0.59f);
    colors[ImGuiCol_ButtonActive]         = ImVec4(0.76f, 0.76f, 0.76f, 1.00f);
    colors[ImGuiCol_Header]               = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
    colors[ImGuiCol_HeaderHovered]        = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
    colors[ImGuiCol_HeaderActive]         = ImVec4(0.76f, 0.76f, 0.76f, 0.77f);
    colors[ImGuiCol_Separator]         = ImVec4(0.000f, 0.000f, 0.000f, 0.137f);
    colors[ImGuiCol_SeparatorHovered]  = ImVec4(0.700f, 0.671f, 0.600f, 0.290f);
    colors[ImGuiCol_SeparatorActive]   = ImVec4(0.702f, 0.671f, 0.600f, 0.674f);
    colors[ImGuiCol_ResizeGrip]        = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    colors[ImGuiCol_ResizeGripActive]  = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    colors[ImGuiCol_PlotLines]         = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]  = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram]     = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.73f, 0.73f, 0.73f, 0.35f);
    colors[ImGuiCol_ModalWindowDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
    colors[ImGuiCol_DragDropTarget]        = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight]          = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg]     = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);

    style.PopupRounding = 3;

    style.WindowPadding = ImVec2(4, 4);
    style.FramePadding  = ImVec2(6, 4);
    style.ItemSpacing   = ImVec2(6, 2);

    style.ScrollbarSize = 18;

    style.WindowBorderSize = 1;
    style.ChildBorderSize  = 1;
    style.PopupBorderSize  = 1;
    style.FrameBorderSize  = is3D;

    style.WindowRounding    = 3;
    style.ChildRounding     = 3;
    style.FrameRounding     = 3;
    style.ScrollbarRounding = 2;
    style.GrabRounding      = 3;

    style.TabBorderSize = is3D;
    style.TabRounding   = 3;

    colors[ImGuiCol_DockingEmptyBg]     = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
    colors[ImGuiCol_Tab]                = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_TabHovered]         = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
    colors[ImGuiCol_TabActive]          = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
    colors[ImGuiCol_TabUnfocused]       = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
    colors[ImGuiCol_DockingPreview]     = ImVec4(0.85f, 0.85f, 0.85f, 0.28f);

    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
      style.WindowRounding              = 0.0f;
      style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
  }

  void photoshop(ImGuiStyle& style) {
    ImVec4* colors = style.Colors;

    colors[ImGuiCol_Text]             = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
    colors[ImGuiCol_TextDisabled]     = ImVec4(0.500f, 0.500f, 0.500f, 1.000f);
    colors[ImGuiCol_WindowBg]         = ImVec4(0.180f, 0.180f, 0.180f, 1.000f);
    colors[ImGuiCol_ChildBg]          = ImVec4(0.280f, 0.280f, 0.280f, 0.000f);
    colors[ImGuiCol_PopupBg]          = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
    colors[ImGuiCol_Border]           = ImVec4(0.266f, 0.266f, 0.266f, 1.000f);
    colors[ImGuiCol_BorderShadow]     = ImVec4(0.000f, 0.000f, 0.000f, 0.000f);
    colors[ImGuiCol_FrameBg]          = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
    colors[ImGuiCol_FrameBgHovered]   = ImVec4(0.200f, 0.200f, 0.200f, 1.000f);
    colors[ImGuiCol_FrameBgActive]    = ImVec4(0.280f, 0.280f, 0.280f, 1.000f);
    colors[ImGuiCol_TitleBg]          = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
    colors[ImGuiCol_TitleBgActive]    = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
    colors[ImGuiCol_MenuBarBg]        = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
    colors[ImGuiCol_ScrollbarBg]      = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
    colors[ImGuiCol_ScrollbarGrab]    = ImVec4(0.277f, 0.277f, 0.277f, 1.000f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.300f, 0.300f, 0.300f, 1.000f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_CheckMark]         = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
    colors[ImGuiCol_SliderGrab]        = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
    colors[ImGuiCol_SliderGrabActive]  = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_Button]            = ImVec4(1.000f, 1.000f, 1.000f, 0.000f);
    colors[ImGuiCol_ButtonHovered]     = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
    colors[ImGuiCol_ButtonActive]      = ImVec4(1.000f, 1.000f, 1.000f, 0.391f);
    colors[ImGuiCol_Header]            = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
    colors[ImGuiCol_HeaderHovered]     = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
    colors[ImGuiCol_HeaderActive]      = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
    colors[ImGuiCol_Separator]         = colors[ImGuiCol_Border];
    colors[ImGuiCol_SeparatorHovered]  = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
    colors[ImGuiCol_SeparatorActive]   = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_ResizeGrip]        = ImVec4(1.000f, 1.000f, 1.000f, 0.250f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.000f, 1.000f, 1.000f, 0.670f);
    colors[ImGuiCol_ResizeGripActive]  = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_Tab]               = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
    colors[ImGuiCol_TabHovered]        = ImVec4(0.352f, 0.352f, 0.352f, 1.000f);
    colors[ImGuiCol_TabActive]         = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
    colors[ImGuiCol_TabUnfocused]      = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
    colors[ImGuiCol_DockingPreview]   = ImVec4(1.000f, 0.391f, 0.000f, 0.781f);
    colors[ImGuiCol_DockingEmptyBg]   = ImVec4(0.180f, 0.180f, 0.180f, 1.000f);
    colors[ImGuiCol_PlotLines]        = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_PlotHistogram]    = ImVec4(0.586f, 0.586f, 0.586f, 1.000f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_NavHighlight]   = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);
    colors[ImGuiCol_ModalWindowDimBg]  = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);

    style.ChildRounding     = 4.0f;
    style.FrameBorderSize   = 1.0f;
    style.FrameRounding     = 2.0f;
    style.GrabMinSize       = 7.0f;
    style.PopupRounding     = 2.0f;
    style.ScrollbarRounding = 12.0f;
    style.ScrollbarSize     = 13.0f;
    style.TabBorderSize     = 1.0f;
    style.TabRounding       = 0.0f;
    style.WindowRounding    = 4.0f;
  }

  void cherry(ImGuiStyle& style) {
    auto HI = [](float v) {
      return ImVec4(0.502f, 0.075f, 0.256f, v);
    };
    auto MED = [](float v) {
      return ImVec4(0.455f, 0.198f, 0.301f, v);
    };
    auto LOW = [](float v) {
      return ImVec4(0.232f, 0.201f, 0.271f, v);
    };
    auto BG = [](float v) {
      return ImVec4(0.200f, 0.220f, 0.270f, v);
    };
    auto TEXT = [](float v) {
      return ImVec4(0.860f, 0.930f, 0.890f, v);
    };

    style.Colors[ImGuiCol_Text]           = TEXT(0.78f);
    style.Colors[ImGuiCol_TextDisabled]   = TEXT(0.28f);
    style.Colors[ImGuiCol_WindowBg]       = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
    style.Colors[ImGuiCol_PopupBg]        = BG(0.9f);
    style.Colors[ImGuiCol_Border]         = ImVec4(0.31f, 0.31f, 1.00f, 0.00f);
    style.Colors[ImGuiCol_BorderShadow]   = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_FrameBg]        = BG(1.00f);
    style.Colors[ImGuiCol_FrameBgHovered] = MED(0.78f);
    style.Colors[ImGuiCol_FrameBgActive]  = MED(1.00f);
    style.Colors[ImGuiCol_TitleBg]        = LOW(1.00f);
    style.Colors[ImGuiCol_TitleBgActive]  = HI(1.00f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = BG(0.75f);
    style.Colors[ImGuiCol_MenuBarBg]        = BG(0.47f);
    style.Colors[ImGuiCol_ScrollbarBg]      = BG(1.00f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = MED(0.78f);
    style.Colors[ImGuiCol_ScrollbarGrabActive]  = MED(1.00f);
    style.Colors[ImGuiCol_CheckMark]  = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
    style.Colors[ImGuiCol_Button]        = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
    style.Colors[ImGuiCol_ButtonHovered] = MED(0.86f);
    style.Colors[ImGuiCol_ButtonActive]  = MED(1.00f);
    style.Colors[ImGuiCol_Header]        = MED(0.76f);
    style.Colors[ImGuiCol_HeaderHovered] = MED(0.86f);
    style.Colors[ImGuiCol_HeaderActive]  = HI(1.00f);
    style.Colors[ImGuiCol_ResizeGrip]    = ImVec4(0.47f, 0.77f, 0.83f, 0.04f);
    style.Colors[ImGuiCol_ResizeGripHovered]    = MED(0.78f);
    style.Colors[ImGuiCol_ResizeGripActive]     = MED(1.00f);
    style.Colors[ImGuiCol_PlotLines]            = TEXT(0.63f);
    style.Colors[ImGuiCol_PlotLinesHovered]     = MED(1.00f);
    style.Colors[ImGuiCol_PlotHistogram]        = TEXT(0.63f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = MED(1.00f);
    style.Colors[ImGuiCol_TextSelectedBg]       = MED(0.43f);

    style.WindowPadding     = ImVec2(6, 4);
    style.WindowRounding    = 0.0f;
    style.FramePadding      = ImVec2(5, 2);
    style.FrameRounding     = 3.0f;
    style.ItemSpacing       = ImVec2(7, 1);
    style.ItemInnerSpacing  = ImVec2(1, 1);
    style.TouchExtraPadding = ImVec2(0, 0);
    style.IndentSpacing     = 6.0f;
    style.ScrollbarSize     = 12.0f;
    style.ScrollbarRounding = 16.0f;
    style.GrabMinSize       = 20.0f;
    style.GrabRounding      = 2.0f;

    style.WindowTitleAlign.x = 0.50f;

    style.Colors[ImGuiCol_Border] = ImVec4(0.539f, 0.479f, 0.255f, 0.162f);
    style.FrameBorderSize         = 0.0f;
    style.WindowBorderSize        = 1.0f;
  }

  void ue4(ImGuiStyle& style) {
    ImVec4* colors                         = style.Colors;
    colors[ImGuiCol_Text]                  = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled]          = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg]              = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
    colors[ImGuiCol_ChildBg]               = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
    colors[ImGuiCol_PopupBg]               = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border]                = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg]               = ImVec4(0.20f, 0.21f, 0.22f, 0.54f);
    colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.40f, 0.40f, 0.40f, 0.40f);
    colors[ImGuiCol_FrameBgActive]         = ImVec4(0.18f, 0.18f, 0.18f, 0.67f);
    colors[ImGuiCol_TitleBg]               = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
    colors[ImGuiCol_TitleBgActive]         = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg]             = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_CheckMark]             = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
    colors[ImGuiCol_SliderGrab]            = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
    colors[ImGuiCol_Button]                = ImVec4(0.44f, 0.44f, 0.44f, 0.40f);
    colors[ImGuiCol_ButtonHovered]         = ImVec4(0.46f, 0.47f, 0.48f, 1.00f);
    colors[ImGuiCol_ButtonActive]          = ImVec4(0.42f, 0.42f, 0.42f, 1.00f);
    colors[ImGuiCol_Header]                = ImVec4(0.70f, 0.70f, 0.70f, 0.31f);
    colors[ImGuiCol_HeaderHovered]         = ImVec4(0.70f, 0.70f, 0.70f, 0.80f);
    colors[ImGuiCol_HeaderActive]          = ImVec4(0.48f, 0.50f, 0.52f, 1.00f);
    colors[ImGuiCol_Separator]             = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    colors[ImGuiCol_SeparatorHovered]      = ImVec4(0.72f, 0.72f, 0.72f, 0.78f);
    colors[ImGuiCol_SeparatorActive]       = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_ResizeGrip]            = ImVec4(0.91f, 0.91f, 0.91f, 0.25f);
    colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.81f, 0.81f, 0.81f, 0.67f);
    colors[ImGuiCol_ResizeGripActive]      = ImVec4(0.46f, 0.46f, 0.46f, 0.95f);
    colors[ImGuiCol_PlotLines]             = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]      = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram]         = ImVec4(0.73f, 0.60f, 0.15f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.87f, 0.87f, 0.87f, 0.35f);
    colors[ImGuiCol_DragDropTarget]        = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight]          = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
  }

  void light(ImGuiStyle& style) {
    int hspacing                 = 8;
    int vspacing                 = 6;
    style.DisplaySafeAreaPadding = ImVec2(0, 0);
    style.WindowPadding          = ImVec2(hspacing / 2.0, vspacing);
    style.FramePadding           = ImVec2(hspacing, vspacing);
    style.ItemSpacing            = ImVec2(hspacing, vspacing);
    style.ItemInnerSpacing       = ImVec2(hspacing, vspacing);
    style.IndentSpacing          = 20.0f;

    style.WindowRounding = 0.0f;
    style.FrameRounding  = 0.0f;

    style.WindowBorderSize = 0.0f;
    style.FrameBorderSize  = 1.0f;
    style.PopupBorderSize  = 1.0f;

    style.ScrollbarSize     = 20.0f;
    style.ScrollbarRounding = 0.0f;
    style.GrabMinSize       = 5.0f;
    style.GrabRounding      = 0.0f;

    ImVec4 white       = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    ImVec4 transparent = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    ImVec4 dark        = ImVec4(0.00f, 0.00f, 0.00f, 0.20f);
    ImVec4 darker      = ImVec4(0.00f, 0.00f, 0.00f, 0.50f);

    ImVec4 background = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
    ImVec4 text       = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    ImVec4 border     = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    ImVec4 grab       = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);
    ImVec4 header     = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
    ImVec4 active     = ImVec4(0.00f, 0.47f, 0.84f, 1.00f);
    ImVec4 hover      = ImVec4(0.00f, 0.47f, 0.84f, 0.20f);

    auto& colors = style.Colors;

    colors[ImGuiCol_Text]     = text;
    colors[ImGuiCol_WindowBg] = background;
    colors[ImGuiCol_ChildBg]  = background;
    colors[ImGuiCol_PopupBg]  = white;

    colors[ImGuiCol_Border]       = border;
    colors[ImGuiCol_BorderShadow] = transparent;

    colors[ImGuiCol_Button]        = header;
    colors[ImGuiCol_ButtonHovered] = hover;
    colors[ImGuiCol_ButtonActive]  = active;

    colors[ImGuiCol_FrameBg]        = white;
    colors[ImGuiCol_FrameBgHovered] = hover;
    colors[ImGuiCol_FrameBgActive]  = active;

    colors[ImGuiCol_MenuBarBg]     = header;
    colors[ImGuiCol_Header]        = header;
    colors[ImGuiCol_HeaderHovered] = hover;
    colors[ImGuiCol_HeaderActive]  = active;

    colors[ImGuiCol_CheckMark]        = text;
    colors[ImGuiCol_SliderGrab]       = grab;
    colors[ImGuiCol_SliderGrabActive] = darker;

    colors[ImGuiCol_ScrollbarBg]          = header;
    colors[ImGuiCol_ScrollbarGrab]        = grab;
    colors[ImGuiCol_ScrollbarGrabHovered] = dark;
    colors[ImGuiCol_ScrollbarGrabActive]  = darker;
  }

  void ledsynthmaster(ImGuiStyle& style) {
    style.WindowPadding     = ImVec2(15, 15);
    style.WindowRounding    = 5.0f;
    style.FramePadding      = ImVec2(5, 5);
    style.FrameRounding     = 4.0f;
    style.ItemSpacing       = ImVec2(12, 8);
    style.ItemInnerSpacing  = ImVec2(8, 6);
    style.IndentSpacing     = 25.0f;
    style.ScrollbarSize     = 15.0f;
    style.ScrollbarRounding = 9.0f;
    style.GrabMinSize       = 5.0f;
    style.GrabRounding      = 3.0f;

    style.Colors[ImGuiCol_Text]           = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
    style.Colors[ImGuiCol_TextDisabled]   = ImVec4(0.40f, 0.39f, 0.38f, 0.77f);
    style.Colors[ImGuiCol_WindowBg]       = ImVec4(0.92f, 0.91f, 0.88f, 0.70f);
    style.Colors[ImGuiCol_PopupBg]        = ImVec4(0.92f, 0.91f, 0.88f, 0.92f);
    style.Colors[ImGuiCol_Border]         = ImVec4(0.84f, 0.83f, 0.80f, 0.65f);
    style.Colors[ImGuiCol_BorderShadow]   = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
    style.Colors[ImGuiCol_FrameBg]        = ImVec4(1.00f, 0.98f, 0.95f, 1.00f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.99f, 1.00f, 0.40f, 0.78f);
    style.Colors[ImGuiCol_FrameBgActive]  = ImVec4(0.26f, 1.00f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_TitleBg]        = ImVec4(1.00f, 0.98f, 0.95f, 1.00f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_MenuBarBg]     = ImVec4(1.00f, 0.98f, 0.95f, 0.47f);
    style.Colors[ImGuiCol_ScrollbarBg]   = ImVec4(1.00f, 0.98f, 0.95f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.00f, 0.00f, 0.00f, 0.21f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.90f, 0.91f, 0.00f, 0.78f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_CheckMark]  = ImVec4(0.25f, 1.00f, 0.00f, 0.80f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 0.00f, 0.00f, 0.14f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_Button]        = ImVec4(0.00f, 0.00f, 0.00f, 0.14f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.99f, 1.00f, 0.22f, 0.86f);
    style.Colors[ImGuiCol_ButtonActive]  = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_Header]        = ImVec4(0.25f, 1.00f, 0.00f, 0.76f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 1.00f, 0.00f, 0.86f);
    style.Colors[ImGuiCol_HeaderActive]  = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_ResizeGrip]    = ImVec4(0.00f, 0.00f, 0.00f, 0.04f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.25f, 1.00f, 0.00f, 0.78f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
  }

  void enemymouse(ImGuiStyle& style) {
    style.Alpha          = 1.0;
    style.WindowRounding = 3;
    style.GrabRounding   = 1;
    style.GrabMinSize    = 20;
    style.FrameRounding  = 3;

    style.Colors[ImGuiCol_Text]           = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_TextDisabled]   = ImVec4(0.00f, 0.40f, 0.41f, 1.00f);
    style.Colors[ImGuiCol_WindowBg]       = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_Border]         = ImVec4(0.00f, 1.00f, 1.00f, 0.65f);
    style.Colors[ImGuiCol_BorderShadow]   = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_FrameBg]        = ImVec4(0.44f, 0.80f, 0.80f, 0.18f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.44f, 0.80f, 0.80f, 0.27f);
    style.Colors[ImGuiCol_FrameBgActive]  = ImVec4(0.44f, 0.81f, 0.86f, 0.66f);
    style.Colors[ImGuiCol_TitleBg]        = ImVec4(0.14f, 0.18f, 0.21f, 0.73f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.54f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 1.00f, 1.00f, 0.27f);
    style.Colors[ImGuiCol_MenuBarBg]     = ImVec4(0.00f, 0.00f, 0.00f, 0.20f);
    style.Colors[ImGuiCol_ScrollbarBg]   = ImVec4(0.22f, 0.29f, 0.30f, 0.71f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.00f, 1.00f, 1.00f, 0.44f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.00f, 1.00f, 1.00f, 0.74f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_CheckMark]  = ImVec4(0.00f, 1.00f, 1.00f, 0.68f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 1.00f, 1.00f, 0.36f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.00f, 1.00f, 1.00f, 0.76f);
    style.Colors[ImGuiCol_Button]        = ImVec4(0.00f, 0.65f, 0.65f, 0.46f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.01f, 1.00f, 1.00f, 0.43f);
    style.Colors[ImGuiCol_ButtonActive]  = ImVec4(0.00f, 1.00f, 1.00f, 0.62f);
    style.Colors[ImGuiCol_Header]        = ImVec4(0.00f, 1.00f, 1.00f, 0.33f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 1.00f, 1.00f, 0.42f);
    style.Colors[ImGuiCol_HeaderActive]  = ImVec4(0.00f, 1.00f, 1.00f, 0.54f);
    style.Colors[ImGuiCol_ResizeGrip]    = ImVec4(0.00f, 1.00f, 1.00f, 0.54f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.00f, 1.00f, 1.00f, 0.74f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
  }

  struct Colors {
    auto Color(unsigned int c) -> unsigned int {
      // add alpha.
      // also swap red and blue channel for some reason.
      // todo: figure out why, and fix it.
      const short a = 0xFF;
      const short r = (c >> 16) & 0xFF;
      const short g = (c >> 8) & 0xFF;
      const short b = (c >> 0) & 0xFF;
      return (a << 24) | (r << 0) | (g << 8) | (b << 16);
    };
  };

  struct Static : Colors {
    const unsigned int NONE      = 0x00000000;
    const unsigned int WHITE     = Color(0xFFFFFF);
    const unsigned int BLACK     = Color(0x000000);
    const unsigned int GRAY200   = Color(0xF4F4F4);
    const unsigned int GRAY300   = Color(0xEAEAEA);
    const unsigned int GRAY400   = Color(0xD3D3D3);
    const unsigned int GRAY500   = Color(0xBCBCBC);
    const unsigned int GRAY600   = Color(0x959595);
    const unsigned int GRAY700   = Color(0x767676);
    const unsigned int GRAY800   = Color(0x505050);
    const unsigned int GRAY900   = Color(0x323232);
    const unsigned int BLUE400   = Color(0x378EF0);
    const unsigned int BLUE500   = Color(0x2680EB);
    const unsigned int BLUE600   = Color(0x1473E6);
    const unsigned int BLUE700   = Color(0x0D66D0);
    const unsigned int RED400    = Color(0xEC5B62);
    const unsigned int RED500    = Color(0xE34850);
    const unsigned int RED600    = Color(0xD7373F);
    const unsigned int RED700    = Color(0xC9252D);
    const unsigned int ORANGE400 = Color(0xF29423);
    const unsigned int ORANGE500 = Color(0xE68619);
    const unsigned int ORANGE600 = Color(0xDA7B11);
    const unsigned int ORANGE700 = Color(0xCB6F10);
    const unsigned int GREEN400  = Color(0x33AB84);
    const unsigned int GREEN500  = Color(0x2D9D78);
    const unsigned int GREEN600  = Color(0x268E6C);
    const unsigned int GREEN700  = Color(0x12805C);
  };

  template <bool Dark>
  struct Spectrum : Colors {};

  template <>
  struct Spectrum<false> : Colors {
    const unsigned int GRAY50        = Color(0xFFFFFF);
    const unsigned int GRAY75        = Color(0xFAFAFA);
    const unsigned int GRAY100       = Color(0xF5F5F5);
    const unsigned int GRAY200       = Color(0xEAEAEA);
    const unsigned int GRAY300       = Color(0xE1E1E1);
    const unsigned int GRAY400       = Color(0xCACACA);
    const unsigned int GRAY500       = Color(0xB3B3B3);
    const unsigned int GRAY600       = Color(0x8E8E8E);
    const unsigned int GRAY700       = Color(0x707070);
    const unsigned int GRAY800       = Color(0x4B4B4B);
    const unsigned int GRAY900       = Color(0x2C2C2C);
    const unsigned int BLUE400       = Color(0x2680EB);
    const unsigned int BLUE500       = Color(0x1473E6);
    const unsigned int BLUE600       = Color(0x0D66D0);
    const unsigned int BLUE700       = Color(0x095ABA);
    const unsigned int RED400        = Color(0xE34850);
    const unsigned int RED500        = Color(0xD7373F);
    const unsigned int RED600        = Color(0xC9252D);
    const unsigned int RED700        = Color(0xBB121A);
    const unsigned int ORANGE400     = Color(0xE68619);
    const unsigned int ORANGE500     = Color(0xDA7B11);
    const unsigned int ORANGE600     = Color(0xCB6F10);
    const unsigned int ORANGE700     = Color(0xBD640D);
    const unsigned int GREEN400      = Color(0x2D9D78);
    const unsigned int GREEN500      = Color(0x268E6C);
    const unsigned int GREEN600      = Color(0x12805C);
    const unsigned int GREEN700      = Color(0x107154);
    const unsigned int INDIGO400     = Color(0x6767EC);
    const unsigned int INDIGO500     = Color(0x5C5CE0);
    const unsigned int INDIGO600     = Color(0x5151D3);
    const unsigned int INDIGO700     = Color(0x4646C6);
    const unsigned int CELERY400     = Color(0x44B556);
    const unsigned int CELERY500     = Color(0x3DA74E);
    const unsigned int CELERY600     = Color(0x379947);
    const unsigned int CELERY700     = Color(0x318B40);
    const unsigned int MAGENTA400    = Color(0xD83790);
    const unsigned int MAGENTA500    = Color(0xCE2783);
    const unsigned int MAGENTA600    = Color(0xBC1C74);
    const unsigned int MAGENTA700    = Color(0xAE0E66);
    const unsigned int YELLOW400     = Color(0xDFBF00);
    const unsigned int YELLOW500     = Color(0xD2B200);
    const unsigned int YELLOW600     = Color(0xC4A600);
    const unsigned int YELLOW700     = Color(0xB79900);
    const unsigned int FUCHSIA400    = Color(0xC038CC);
    const unsigned int FUCHSIA500    = Color(0xB130BD);
    const unsigned int FUCHSIA600    = Color(0xA228AD);
    const unsigned int FUCHSIA700    = Color(0x93219E);
    const unsigned int SEAFOAM400    = Color(0x1B959A);
    const unsigned int SEAFOAM500    = Color(0x16878C);
    const unsigned int SEAFOAM600    = Color(0x0F797D);
    const unsigned int SEAFOAM700    = Color(0x096C6F);
    const unsigned int CHARTREUSE400 = Color(0x85D044);
    const unsigned int CHARTREUSE500 = Color(0x7CC33F);
    const unsigned int CHARTREUSE600 = Color(0x73B53A);
    const unsigned int CHARTREUSE700 = Color(0x6AA834);
    const unsigned int PURPLE400     = Color(0x9256D9);
    const unsigned int PURPLE500     = Color(0x864CCC);
    const unsigned int PURPLE600     = Color(0x7A42BF);
    const unsigned int PURPLE700     = Color(0x6F38B1);
  };

  template <>
  struct Spectrum<true> : Colors {
    const unsigned int GRAY50        = Color(0x252525);
    const unsigned int GRAY75        = Color(0x2F2F2F);
    const unsigned int GRAY100       = Color(0x323232);
    const unsigned int GRAY200       = Color(0x393939);
    const unsigned int GRAY300       = Color(0x3E3E3E);
    const unsigned int GRAY400       = Color(0x4D4D4D);
    const unsigned int GRAY500       = Color(0x5C5C5C);
    const unsigned int GRAY600       = Color(0x7B7B7B);
    const unsigned int GRAY700       = Color(0x999999);
    const unsigned int GRAY800       = Color(0xCDCDCD);
    const unsigned int GRAY900       = Color(0xFFFFFF);
    const unsigned int BLUE400       = Color(0x2680EB);
    const unsigned int BLUE500       = Color(0x378EF0);
    const unsigned int BLUE600       = Color(0x4B9CF5);
    const unsigned int BLUE700       = Color(0x5AA9FA);
    const unsigned int RED400        = Color(0xE34850);
    const unsigned int RED500        = Color(0xEC5B62);
    const unsigned int RED600        = Color(0xF76D74);
    const unsigned int RED700        = Color(0xFF7B82);
    const unsigned int ORANGE400     = Color(0xE68619);
    const unsigned int ORANGE500     = Color(0xF29423);
    const unsigned int ORANGE600     = Color(0xF9A43F);
    const unsigned int ORANGE700     = Color(0xFFB55B);
    const unsigned int GREEN400      = Color(0x2D9D78);
    const unsigned int GREEN500      = Color(0x33AB84);
    const unsigned int GREEN600      = Color(0x39B990);
    const unsigned int GREEN700      = Color(0x3FC89C);
    const unsigned int INDIGO400     = Color(0x6767EC);
    const unsigned int INDIGO500     = Color(0x7575F1);
    const unsigned int INDIGO600     = Color(0x8282F6);
    const unsigned int INDIGO700     = Color(0x9090FA);
    const unsigned int CELERY400     = Color(0x44B556);
    const unsigned int CELERY500     = Color(0x4BC35F);
    const unsigned int CELERY600     = Color(0x51D267);
    const unsigned int CELERY700     = Color(0x58E06F);
    const unsigned int MAGENTA400    = Color(0xD83790);
    const unsigned int MAGENTA500    = Color(0xE2499D);
    const unsigned int MAGENTA600    = Color(0xEC5AAA);
    const unsigned int MAGENTA700    = Color(0xF56BB7);
    const unsigned int YELLOW400     = Color(0xDFBF00);
    const unsigned int YELLOW500     = Color(0xEDCC00);
    const unsigned int YELLOW600     = Color(0xFAD900);
    const unsigned int YELLOW700     = Color(0xFFE22E);
    const unsigned int FUCHSIA400    = Color(0xC038CC);
    const unsigned int FUCHSIA500    = Color(0xCF3EDC);
    const unsigned int FUCHSIA600    = Color(0xD951E5);
    const unsigned int FUCHSIA700    = Color(0xE366EF);
    const unsigned int SEAFOAM400    = Color(0x1B959A);
    const unsigned int SEAFOAM500    = Color(0x20A3A8);
    const unsigned int SEAFOAM600    = Color(0x23B2B8);
    const unsigned int SEAFOAM700    = Color(0x26C0C7);
    const unsigned int CHARTREUSE400 = Color(0x85D044);
    const unsigned int CHARTREUSE500 = Color(0x8EDE49);
    const unsigned int CHARTREUSE600 = Color(0x9BEC54);
    const unsigned int CHARTREUSE700 = Color(0xA3F858);
    const unsigned int PURPLE400     = Color(0x9256D9);
    const unsigned int PURPLE500     = Color(0x9D64E1);
    const unsigned int PURPLE600     = Color(0xA873E9);
    const unsigned int PURPLE700     = Color(0xB483F0);
  };

  template <bool IsDark>
  void spectrum(ImGuiStyle& style) {
    const auto spectrum = Spectrum<IsDark>();
    const auto stat     = Static();
    using namespace ImGui;

    style.GrabRounding = 4.0f;

    ImVec4* colors                  = style.Colors;
    colors[ImGuiCol_Text]           = ColorConvertU32ToFloat4(spectrum.GRAY800);
    colors[ImGuiCol_TextDisabled]   = ColorConvertU32ToFloat4(spectrum.GRAY500);
    colors[ImGuiCol_WindowBg]       = ColorConvertU32ToFloat4(spectrum.GRAY100);
    colors[ImGuiCol_ChildBg]        = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg]        = ColorConvertU32ToFloat4(spectrum.GRAY50);
    colors[ImGuiCol_Border]         = ColorConvertU32ToFloat4(spectrum.GRAY300);
    colors[ImGuiCol_BorderShadow]   = ColorConvertU32ToFloat4(stat.NONE);
    colors[ImGuiCol_FrameBg]        = ColorConvertU32ToFloat4(spectrum.GRAY75);
    colors[ImGuiCol_FrameBgHovered] = ColorConvertU32ToFloat4(spectrum.GRAY50);
    colors[ImGuiCol_FrameBgActive]  = ColorConvertU32ToFloat4(spectrum.GRAY200);
    colors[ImGuiCol_TitleBg]        = ColorConvertU32ToFloat4(spectrum.GRAY300);
    colors[ImGuiCol_TitleBgActive]  = ColorConvertU32ToFloat4(spectrum.GRAY200);
    colors[ImGuiCol_TitleBgCollapsed] = ColorConvertU32ToFloat4(spectrum.GRAY400);
    colors[ImGuiCol_MenuBarBg]     = ColorConvertU32ToFloat4(spectrum.GRAY100);
    colors[ImGuiCol_ScrollbarBg]   = ColorConvertU32ToFloat4(spectrum.GRAY100);
    colors[ImGuiCol_ScrollbarGrab] = ColorConvertU32ToFloat4(spectrum.GRAY400);
    colors[ImGuiCol_ScrollbarGrabHovered] = ColorConvertU32ToFloat4(
      spectrum.GRAY600);
    colors[ImGuiCol_ScrollbarGrabActive] = ColorConvertU32ToFloat4(spectrum.GRAY700);
    colors[ImGuiCol_CheckMark]  = ColorConvertU32ToFloat4(spectrum.BLUE500);
    colors[ImGuiCol_SliderGrab] = ColorConvertU32ToFloat4(spectrum.GRAY700);
    colors[ImGuiCol_SliderGrabActive] = ColorConvertU32ToFloat4(spectrum.GRAY800);
    colors[ImGuiCol_Button]        = ColorConvertU32ToFloat4(spectrum.GRAY75);
    colors[ImGuiCol_ButtonHovered] = ColorConvertU32ToFloat4(spectrum.GRAY50);
    colors[ImGuiCol_ButtonActive]  = ColorConvertU32ToFloat4(spectrum.GRAY200);
    colors[ImGuiCol_Header]        = ColorConvertU32ToFloat4(spectrum.BLUE400);
    colors[ImGuiCol_HeaderHovered] = ColorConvertU32ToFloat4(spectrum.BLUE500);
    colors[ImGuiCol_HeaderActive]  = ColorConvertU32ToFloat4(spectrum.BLUE600);
    colors[ImGuiCol_Separator]     = ColorConvertU32ToFloat4(spectrum.GRAY400);
    colors[ImGuiCol_SeparatorHovered] = ColorConvertU32ToFloat4(spectrum.GRAY600);
    colors[ImGuiCol_SeparatorActive] = ColorConvertU32ToFloat4(spectrum.GRAY700);
    colors[ImGuiCol_ResizeGrip] = ColorConvertU32ToFloat4(spectrum.GRAY400);
    colors[ImGuiCol_ResizeGripHovered] = ColorConvertU32ToFloat4(spectrum.GRAY600);
    colors[ImGuiCol_ResizeGripActive] = ColorConvertU32ToFloat4(spectrum.GRAY700);
    colors[ImGuiCol_PlotLines] = ColorConvertU32ToFloat4(spectrum.BLUE400);
    colors[ImGuiCol_PlotLinesHovered] = ColorConvertU32ToFloat4(spectrum.BLUE600);
    colors[ImGuiCol_PlotHistogram] = ColorConvertU32ToFloat4(spectrum.BLUE400);
    colors[ImGuiCol_PlotHistogramHovered] = ColorConvertU32ToFloat4(
      spectrum.BLUE600);
    colors[ImGuiCol_TextSelectedBg] = ColorConvertU32ToFloat4(
      (spectrum.BLUE400 & 0x00FFFFFF) | 0x33000000);
    colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight]   = ColorConvertU32ToFloat4(
      (spectrum.GRAY900 & 0x00FFFFFF) | 0x0A000000);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg]     = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg]      = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
  }

} // namespace omdi::themes
