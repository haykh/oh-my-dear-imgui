#ifndef COMPONENTS_UICONFIG_H
#define COMPONENTS_UICONFIG_H

#include "core/state.h"
#include "managers/fonts.h"
#include "managers/picker.h"
#include "managers/toasts.h"

namespace omdi {

  /**
   * @brief A panel to handle style changes.
   */
  class StyleDialog {

  public:
    void render(bool*,
                omdi::State*,
                omdi::PickerManager*,
                omdi::FontManager*,
                omdi::ToastManager*);
  };

} // namespace omdi

#endif // COMPONENTS_UICONFIG_H
