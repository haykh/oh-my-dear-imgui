#include "components/safe.h"

#include "managers/toasts.h"
#include "utils.h"

#include <functional>

namespace omdi::safe {

  void Render(const std::function<void()>& item, omdi::ToastManager* toastManager) {
    try {
      item();
    } catch (const std::exception& e) {
      omdi::logger::Error("Exception: %s", e.what());
      if (toastManager != nullptr) {
        toastManager->Add(omdi::toasts::Type::Error, std::string(e.what()));
      }
    } catch (...) {
      omdi::logger::Error("Unknown exception");
      if (toastManager != nullptr) {
        toastManager->Add(omdi::toasts::Type::Error, "Unknown exception");
      }
    }
  }

  void PushPop(const std::function<void()>& push,
               const std::function<void()>& item,
               const std::function<void()>& pop,
               omdi::ToastManager*          toastManager) {
    push();
    Render(item, toastManager);
    pop();
  }

} // namespace omdi::safe

namespace omdi {

  void Component(const std::function<bool()>& opener,
                 const std::function<void()>& item,
                 const std::function<void()>& closer,
                 omdi::ToastManager*          toastManager) {
    if (opener()) {
      omdi::safe::Render(item, toastManager);
      closer();
    }
  }

} // namespace omdi
