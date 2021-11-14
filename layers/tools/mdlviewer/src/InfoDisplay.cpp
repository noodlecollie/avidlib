#include <cstdint>
#include <iostream>
#include "imgui.h"
#include "InfoDisplay.h"
#include "MDLLoader.h"
#include "AVIDLib_Plat/Ptr.h"
#include "AVIDLib_IO/UnitSupport.h"
#include "AVIDLib_Containers/MDLv10/Model.h"

namespace InfoDisplay
{
	struct Info
	{
		std::string name;
		ALP_Size numBones = 0;
		ALP_Size numBoneControllers = 0;
		ALP_Size numBodyParts = 0;
	};

	bool Visible = false;

	static std::string LastMDLPath;
	static Info CachedMDLInfo{};

	static void UpdateMDLInfo(ALC_MDLv10_Model* model)
	{
		if ( !model )
		{
			CachedMDLInfo = Info{};
			return;
		}

		CachedMDLInfo.name = model->name;
		CachedMDLInfo.numBones = model->numBones;
		CachedMDLInfo.numBoneControllers = model->numBoneControllers;
		CachedMDLInfo.numBodyParts = model->numBodyParts;
	}

	void Draw()
	{
		if ( Visible )
		{
			if ( ImGui::Begin("MDL Info", &InfoDisplay::Visible) )
			{
				ImGui::Text("Internal name: %s", CachedMDLInfo.name.c_str());
				ImGui::Text("Bones: %u", CachedMDLInfo.numBones);
				ImGui::Text("Bone controllers: %u", CachedMDLInfo.numBoneControllers);
				ImGui::Text("Body parts: %u", CachedMDLInfo.numBodyParts);
			}

			ImGui::End();
		}
	}

	void Poll()
	{
		std::string mdlPath = MDLLoader::GetMDLPath();

		if ( mdlPath != LastMDLPath )
		{
			std::cout << "Updating info display for newly loaded model." << std::endl;

			// For now, we just assume that the model is v10.
			// If this is not the case, null will be returned.
			UpdateMDLInfo(static_cast<ALC_MDLv10_Model*>(MDLLoader::GetUnderlyingContainer(ALIO_UNIT_MDLV10)));
			LastMDLPath = mdlPath;
		}
	}
}
