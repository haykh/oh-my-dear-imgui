#ifndef COMPONENTS_SAFE_H
#define COMPONENTS_SAFE_H

#include "components/toasts.h"

#include <plog/Log.h>

#include <functional>

namespace ui::safe {

  void Render(const std::function<void()>&, ui::toasts::ToastManager* = nullptr);

  void PushPop(const std::function<void()>&,
               const std::function<void()>&,
               const std::function<void()>&,
               ui::toasts::ToastManager* = nullptr);

  void Component(const std::function<bool()>&,
                 const std::function<void()>&,
                 const std::function<void()>&,
                 ui::toasts::ToastManager* = nullptr);

} // namespace ui::safe

#endif // COMPONENTS_SAFE_H
