#ifndef OMDI_HPP
#define OMDI_HPP

#include "core/app.h"
#include "core/state.h"
/**/
#include "implot-gpu/plotters.h"

#include "components/menubar.h"
#include "components/safe.h"
#include "components/uiconfig.h"
#include "containers/containers.h"
#include "managers/fonts.h"
#include "managers/picker.h"
#include "managers/screenshot.h"
#include "managers/toasts.h"
#include "plots/pcolor.h"
#include "plots/plot.h"
#include "plots/scatter.h"
#include "style/icons.h"
#include "style/themes.h"
#include "utils.h"

#include <map>
#include <string>

namespace omdi {
  using namespace plots;

  namespace utils {
    using namespace timer;
  } // namespace utils

} // namespace omdi

namespace omdi {
  using managers_t   = std::map<std::string, void*>;
  using components_t = std::map<std::string, void*>;
} // namespace omdi

#endif // OMDI_HPP
