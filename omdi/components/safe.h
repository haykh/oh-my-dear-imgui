#ifndef COMPONENTS_SAFE_H
#define COMPONENTS_SAFE_H

#include "managers/toasts.h"

#include <functional>

namespace omdi::safe {

  void Render(const std::function<void()>&, omdi::ToastManager* = nullptr);

  void PushPop(const std::function<void()>&,
               const std::function<void()>&,
               const std::function<void()>&,
               omdi::ToastManager* = nullptr);

} // namespace omdi::safe

namespace omdi {

  void Component(const std::function<bool()>&,
                 const std::function<void()>&,
                 const std::function<void()>&,
                 omdi::ToastManager* = nullptr);

} // namespace omdi

#endif // COMPONENTS_SAFE_H
