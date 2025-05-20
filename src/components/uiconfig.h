#ifndef COMPONENTS_UI_CONFIG_H
#define COMPONENTS_UI_CONFIG_H

#include "components/picker.h"
#include "components/state.h"
#include "components/toasts.h"
#include "style/fonts.h"

namespace ui::config {

  /**
   * @brief A panel to handle style changes.
   */
  class StyleDialog {

  public:
    void render(bool*,
                ui::state::State&,
                ui::picker::PickerManager&,
                ui::fonts::FontManager&,
                ui::toasts::ToastManager&);
  };

} // namespace ui::config

#endif // COMPONENTS_UI_CONFIG_H
