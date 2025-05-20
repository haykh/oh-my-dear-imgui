#ifndef COMPONENTS_SAFE_H
#define COMPONENTS_SAFE_H

#include "managers/toasts.h"

#include <functional>

namespace omdi::safe {

  void Render(const std::function<void()>&, omdi::toasts::ToastManager* = nullptr);

  void PushPop(const std::function<void()>&,
               const std::function<void()>&,
               const std::function<void()>&,
               omdi::toasts::ToastManager* = nullptr);

  void Component(const std::function<bool()>&,
                 const std::function<void()>&,
                 const std::function<void()>&,
                 omdi::toasts::ToastManager* = nullptr);

} // namespace omdi::safe

#endif // COMPONENTS_SAFE_H
