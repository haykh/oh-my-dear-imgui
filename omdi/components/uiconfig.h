#ifndef COMPONENTS_UICONFIG_H
#define COMPONENTS_UICONFIG_H

#include "managers/fonts.h"
#include "managers/picker.h"
#include "managers/state.h"
#include "managers/toasts.h"

namespace omdi::config {

  /**
   * @brief A panel to handle style changes.
   */
  class StyleDialog {

  public:
    void render(bool*,
                omdi::state::State*,
                omdi::picker::PickerManager*,
                omdi::fonts::FontManager*,
                omdi::toasts::ToastManager*);
  };

} // namespace omdi::config

#endif // COMPONENTS_UICONFIG_H
