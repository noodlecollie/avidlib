#include "OpenMDLFileDialogue.h"
#include "ImGuiFileDialog.h"
#include "MDLLoader.h"

namespace OpenMDLFileDialogue
{
	static constexpr const char* const KEY_OPEN_MDL_FILE = "OpenMDLFile";
	static constexpr ImGuiWindowFlags FLAGS =
		ImGuiFileDialogFlags_DontShowHiddenFiles |
		ImGuiFileDialogFlags_DisableCreateDirectoryButton;

	static bool DialogueActive = false;

	void Draw()
	{
		DialogueActive = ImGuiFileDialog::Instance()->Display(KEY_OPEN_MDL_FILE, ImGuiWindowFlags_NoCollapse, ImVec2(0, 200));
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
		ImGuiFileDialog::Instance()->SetExtentionInfos(".mdl", ImVec4(143.0f / 255.0f, 234.0f / 255.0f, 187.0f / 255.0f, 1.0f));
		ImGuiFileDialog::Instance()->OpenDialog(KEY_OPEN_MDL_FILE, "Choose MDL File", ".mdl", ".", 1, nullptr, FLAGS);
	}
}
