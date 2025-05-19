#ifndef COMPONENTS_SAFE_H
#define COMPONENTS_SAFE_H

#include "components/toasts.h"

#include <plog/Log.h>

#include <functional>

namespace ui::safe {

  void Render(const std::function<void()>&, ui::toasts::Toasts* = nullptr);

  void Component(const std::function<bool()>&,
                 const std::function<void()>&,
                 const std::function<void()>&,
                 ui::toasts::Toasts* = nullptr);

} // namespace ui::safe

#endif // COMPONENTS_SAFE_H
