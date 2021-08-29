#include "OpenMDLFileDialogue.h"
#include "ImGuiFileDialog.h"
#include "MDLLoader.h"

namespace OpenMDLFileDialogue
{
	static constexpr const char* const KEY_OPEN_MDL_FILE = "OpenMDLFile";

	static bool DialogueActive = false;

	void Draw()
	{
		DialogueActive = ImGuiFileDialog::Instance()->Display(KEY_OPEN_MDL_FILE, 32, ImVec2(0, 200));
	}

	void Poll()
	{
		if ( DialogueActive )
		{
			if ( ImGuiFileDialog::Instance()->IsOk() )
			{
				MDLLoader::SetMDLPath(ImGuiFileDialog::Instance()->GetFilePathName());
			}

			ImGuiFileDialog::Instance()->Close();
		}
	}

	void Open()
	{
		static constexpr ImGuiWindowFlags FLAGS =
				ImGuiFileDialogFlags_DontShowHiddenFiles |
				ImGuiFileDialogFlags_DisableCreateDirectoryButton;

		ImGuiFileDialog::Instance()->OpenDialog(KEY_OPEN_MDL_FILE, "Choose MDL File", ".mdl", ".", 1, nullptr, FLAGS);
	}
}
