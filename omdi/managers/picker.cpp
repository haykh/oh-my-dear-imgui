#include "managers/picker.h"

#include "utils.h"

#include <ImGuiFileDialog.h>

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace omdi::picker {

  void PickerManager::Add(callback_t         callback,
                          const std::string& title,
                          const std::string& prompt,
                          const std::string& path,
                          const char*        filter) {
    IGFD::FileDialogConfig config;
    config.path = path;

    auto dialog = std::make_unique<IGFD::FileDialog>();
    dialog->OpenDialog(title, prompt, filter, config);

    m_dialogs.emplace_back(std::move(dialog), std::move(callback));
    omdi::logger::Debug("Dialog %s opened in %s", title.c_str(), path.c_str());
    omdi::logger::Debug("Total dialogs: %d", m_dialogs.size());
  }

  void PickerManager::render() {
    auto it = m_dialogs.begin();
    while (it != m_dialogs.end()) {
      auto& [dialog, callback] = *it;
      dialog->SetFileStyle(IGFD_FileStyleByExtention,
                           ".ttf",
                           ImVec4(1.0f, 1.0f, 1.0f, 1.0f),
                           ICON_FA_FONT);
      const auto key = dialog->GetOpenedKey();
      if (dialog->Display(key)) {
        if (dialog->IsOk()) {
          omdi::logger::Debug("Dialog %s is OK", key.c_str());
          callback(dialog.get());
        } else {
          omdi::logger::Debug("Dialog %s is Cancelled", key.c_str());
        }
        dialog->Close();

        it = m_dialogs.erase(it);
        omdi::logger::Debug("Dialog %s removed from the manager. Remaining: %d",
                            key.c_str(),
                            m_dialogs.size());
      } else {
        ++it;
      }
    }
  }

} // namespace omdi::picker
