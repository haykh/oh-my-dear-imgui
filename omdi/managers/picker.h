#ifndef MANAGERS_PICKER_H
#define MANAGERS_PICKER_H

#include <ImGuiFileDialog.h>
#include <imgui.h>

#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace omdi::picker {

  using callback_t = std::function<void(IGFD::FileDialog*)>;

} // namespace omdi::picker

namespace omdi {

  /**
   * @brief Manager for handling file/directory picker dialogs.
   */
  class PickerManager {
    std::vector<std::pair<std::unique_ptr<IGFD::FileDialog>, omdi::picker::callback_t>> m_dialogs;

  public:
    /**
     * @brief Add a picker dialog to the handler.
     * @param {std::function<void(IGFD::FileDialog*)>} callback - The callback function to be called when the dialog is closed
     * @param {std::string} title - The title of the dialog (default = "PickerDialog")
     * @param {std::string} prompt - The prompt message to be displayed in the dialog (default = "Pick a file or directory")
     * @param {std::string} path - The initial path to be displayed in the dialog (default = ".")
     * @param {char*} filter - File extension filter (default = nullptr, pick directory)
     */
    void Add(omdi::picker::callback_t,
             const std::string& = "PickerDialog",
             const std::string& = "Pick a file or directory",
             const std::string& = ".",
             const char*        = nullptr);

    void render();
  };

} // namespace omdi

#endif // MANAGERS_PICKER_H
