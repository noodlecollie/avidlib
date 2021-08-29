#include "OpenMDLFileDialogue.h"
#include "ImGuiFileDialog.h"

namespace OpenMDLFileDialogue
{
	static constexpr const char* const KEY_OPEN_MDL_FILE = "OpenMDLFile";

	void Draw()
	{
		if ( ImGuiFileDialog::Instance()->Display(KEY_OPEN_MDL_FILE, 32, ImVec2(0, 200)) )
		{
			if ( ImGuiFileDialog::Instance()->IsOk() )
			{
				// TODO: Do something with path.
			}

			ImGuiFileDialog::Instance()->Close();
		}
	}

	void Poll()
	{
		// TODO
	}

	void Open()
	{
		static constexpr ImGuiWindowFlags FLAGS =
				ImGuiFileDialogFlags_DontShowHiddenFiles |
				ImGuiFileDialogFlags_DisableCreateDirectoryButton;

		ImGuiFileDialog::Instance()->OpenDialog(KEY_OPEN_MDL_FILE, "Choose MDL File", ".mdl", ".", 1, nullptr, FLAGS);
	}
}
