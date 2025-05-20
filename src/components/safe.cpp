#include "components/safe.h"

#include "components/toasts.h"

#include <functional>

namespace ui::safe {

  void Render(const std::function<void()>& item,
              ui::toasts::ToastManager*    toastManager) {
    try {
      item();
    } catch (const std::exception& e) {
      PLOGE << e.what();
      if (toastManager != nullptr) {
        toastManager->add(ui::toasts::Type::Error, std::string(e.what()));
      }
    } catch (...) {
      PLOGE << "Unknown exception";
      if (toastManager != nullptr) {
        toastManager->add(ui::toasts::Type::Error, "Unknown exception");
      }
    }
  }

  void PushPop(const std::function<void()>& push,
               const std::function<void()>& item,
               const std::function<void()>& pop,
               ui::toasts::ToastManager*    toastManager) {
    push();
    Render(item, toastManager);
    pop();
  }

  void Component(const std::function<bool()>& opener,
                 const std::function<void()>& item,
                 const std::function<void()>& closer,
                 ui::toasts::ToastManager*    toastManager) {
    if (opener()) {
      Render(item, toastManager);
      closer();
    }
  }

} // namespace ui::safe
