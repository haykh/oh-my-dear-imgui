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

  /**
   * @brief Top menubar component for omdi applications.
   */
  class Menubar {
    std::vector<MenuItem> m_items_left;
    std::vector<MenuItem> m_items_center;
    std::vector<MenuItem> m_items_right;

    [[nodiscard]]
    auto measureWidth(const std::vector<MenuItem>& items) const -> float;

  public:
    void AddLeft(const std::function<void()>& item) {
      m_items_left.push_back(MenuItem { item });
    }

    void AddCenter(const std::function<void()>& item) {
      m_items_center.push_back(MenuItem { item });
    }

    void AddRight(const std::function<void()>& item) {
      m_items_right.push_back(MenuItem { item });
    }

    void render(omdi::toasts::ToastManager* = nullptr) const;
  };

} // namespace omdi::menubar

#endif // COMPONENTS_MENUBAR_H
