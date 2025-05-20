#ifndef COMPONENTS_DIALOG_H
#define COMPONENTS_DIALOG_H

#include <ImGuiFileDialog.h>
#include <imgui.h>

#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace ui::picker {
  using callback_t = std::function<void(IGFD::FileDialog*)>;

  /**
   * @brief Dialogues to handle file/directory picking.
   */
  class PickerManager {
    std::vector<std::pair<std::unique_ptr<IGFD::FileDialog>, callback_t>> m_dialogs;

  public:
    /**
     * @brief Add a picker dialog to the handler.
     * @param callback The callback function to be called when the dialog is closed.
     * @param title The title of the dialog (default = "PickerDialog").
     * @param prompt The prompt message to be displayed in the dialog (default = "Pick a file or directory").
     * @param path The initial path to be displayed in the dialog (default = ".").
     * @param filter File extension filter (default = nullptr, pick directory)
     */
    void add(callback_t,
             const std::string& = "PickerDialog",
             const std::string& = "Pick a file or directory",
             const std::string& = ".",
             const char*        = nullptr);

    void render();
  };

} // namespace ui::picker

#endif // COMPONENTS_DIALOG_H
