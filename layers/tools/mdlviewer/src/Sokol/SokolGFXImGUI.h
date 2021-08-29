#ifndef AVIDLIB_TOOLS_MDLVIEWER_SOKOLGFXIMGUI_H
#define AVIDLIB_TOOLS_MDLVIEWER_SOKOLGFXIMGUI_H

typedef struct sg_imgui_t sg_imgui_t;

namespace SokolGFXImGUI
{
	sg_imgui_t* GetPersistence();

	void Init();
	void Draw();
}

#endif // AVIDLIB_TOOLS_MDLVIEWER_SOKOLGFXIMGUI_H
