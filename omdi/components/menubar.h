#ifndef COMPONENTS_MENUBAR_H
#define COMPONENTS_MENUBAR_H

#include "managers/toasts.h"

#include <imgui.h>

#include <functional>
#include <vector>

namespace omdi::menubar {

  struct MenuItem {
    std::function<void()> render;
  };

  class Menubar {
    std::vector<MenuItem> m_items_left;
    std::vector<MenuItem> m_items_center;
    std::vector<MenuItem> m_items_right;

    [[nodiscard]]
    auto measureWidth(const std::vector<MenuItem>& items) const -> float;

  public:
    void addLeft(const std::function<void()>& item) {
      m_items_left.push_back(MenuItem { item });
    }

    void addCenter(const std::function<void()>& item) {
      m_items_center.push_back(MenuItem { item });
    }

    void addRight(const std::function<void()>& item) {
      m_items_right.push_back(MenuItem { item });
    }

    void render(omdi::toasts::ToastManager* = nullptr) const;
  };

} // namespace omdi::menubar

#endif // COMPONENTS_MENUBAR_H
