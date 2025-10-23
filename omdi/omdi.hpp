#ifndef OMDI_HPP
#define OMDI_HPP

#include "components/app.h"
#include "components/menubar.h"
#include "components/safe.h"
#include "components/uiconfig.h"
#include "managers/fonts.h"
#include "managers/picker.h"
#include "managers/screenshot.h"
#include "managers/state.h"
#include "managers/toasts.h"
#include "style/icons.h"
#include "style/themes.h"
#include "utils.h"

#include <map>
#include <string>

namespace omdi {
  using managers_t   = std::map<std::string, void*>;
  using components_t = std::map<std::string, void*>;
} // namespace omdi

#endif // OMDI_HPP
