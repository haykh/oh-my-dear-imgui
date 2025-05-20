#include "components/safe.h"

#include "managers/toasts.h"
#include "utils.h"

#include <functional>

namespace omdi::safe {

  void Render(const std::function<void()>& item,
              omdi::toasts::ToastManager*  toastManager) {
    try {
      item();
    } catch (const std::exception& e) {
      omdi::logger::Error("Exception: %s", e.what());
      if (toastManager != nullptr) {
        toastManager->add(omdi::toasts::Type::Error, std::string(e.what()));
      }
    } catch (...) {
      omdi::logger::Error("Unknown exception");
      if (toastManager != nullptr) {
        toastManager->add(omdi::toasts::Type::Error, "Unknown exception");
      }
    }
  }

  void PushPop(const std::function<void()>& push,
               const std::function<void()>& item,
               const std::function<void()>& pop,
               omdi::toasts::ToastManager*  toastManager) {
    push();
    Render(item, toastManager);
    pop();
  }

  void Component(const std::function<bool()>& opener,
                 const std::function<void()>& item,
                 const std::function<void()>& closer,
                 omdi::toasts::ToastManager*  toastManager) {
    if (opener()) {
      Render(item, toastManager);
      closer();
    }
  }

} // namespace omdi::safe
