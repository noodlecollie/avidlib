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
		uint32_t numBones = 0;
		uint32_t numBoneControllers = 0;
		uint32_t numBodyParts = 0;
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

			UpdateMDLInfo(static_cast<ALC_MDLv10_Model*>(MDLLoader::GetUnderlyingContainer(ALIO_UNIT_MDLV10)));
			LastMDLPath = mdlPath;
		}
	}
}
