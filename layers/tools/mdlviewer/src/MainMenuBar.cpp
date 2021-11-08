#include "imgui.h"
#include "MainMenuBar.h"
#include "OpenMDLFileDialogue.h"
#include "InfoDisplay.h"
#include "Sokol/SokolHeaders.h"
#include "Sokol/SokolGFXImGUI.h"

namespace MainMenuBar
{
	static bool OpenFileRequested = false;
	static bool ExitRequested = false;

	void Draw()
	{
		if ( ImGui::BeginMainMenuBar() )
		{
			if ( ImGui::BeginMenu("File") )
			{
				ImGui::MenuItem("Open", nullptr, &OpenFileRequested);
				ImGui::MenuItem("Exit", nullptr, &ExitRequested);

				ImGui::EndMenu();
			}

			if ( ImGui::BeginMenu("View") )
			{
				ImGui::MenuItem("MDL Info", nullptr, &InfoDisplay::Visible);

				ImGui::EndMenu();
			}

#ifdef SOKOL_TRACE_HOOKS
			if ( ImGui::BeginMenu("GFX Debug") )
			{
				ImGui::MenuItem("Buffers", nullptr, &SokolGFXImGUI::GetPersistence()->buffers.open);
				ImGui::MenuItem("Images", nullptr, &SokolGFXImGUI::GetPersistence()->images.open);
				ImGui::MenuItem("Shaders", nullptr, &SokolGFXImGUI::GetPersistence()->shaders.open);
				ImGui::MenuItem("Pipelines", nullptr, &SokolGFXImGUI::GetPersistence()->pipelines.open);
				ImGui::MenuItem("Passes", nullptr, &SokolGFXImGUI::GetPersistence()->passes.open);
				ImGui::MenuItem("Calls", nullptr, &SokolGFXImGUI::GetPersistence()->capture.open);

				ImGui::EndMenu();
			}
#endif // SOKOL_TRACE_HOOKS

			ImGui::EndMainMenuBar();
		}
	}

	void Poll()
	{
		if ( ExitRequested )
		{
			sapp_request_quit();
			ExitRequested = false;
		}

		if ( OpenFileRequested )
		{
			OpenMDLFileDialogue::Open();
			OpenFileRequested = false;
		}
	}
}
