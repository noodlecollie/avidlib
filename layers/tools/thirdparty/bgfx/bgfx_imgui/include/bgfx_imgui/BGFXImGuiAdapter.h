#ifndef BGFX_IMGUI_BGFXIMGUIADAPTER_H
#define BGFX_IMGUI_BGFXIMGUIADAPTER_H

#include <memory>
#include "imgui.h"

class BGFXImGuiAdapter
{
public:
	BGFXImGuiAdapter();
	~BGFXImGuiAdapter();

	void Create(float fontSize = 18.0f);
	void Destroy();
	void BeginFrame();
	void EndFrame();

	ImVec2 DisplaySize() const;
	void SetDisplaySize(const ImVec2& size);

	float DisplayScale() const;
	void SetDisplayScale(float scale);

	ImVec2 MousePosition() const;
	void SetMousePosition(const ImVec2& pos);

	uint32_t MouseButtonsPressed() const;
	void OverwriteMouseButtonsPressed(uint32_t buttons);
	void SetMouseButtonPressed(ImGuiMouseButton_ button, bool pressed);

	ImVec2 ScrollDelta() const;
	void SetScrollDelta(const ImVec2& delta);

	void SetInputChar(unsigned int input);

private:
	class Impl;

	inline Impl& GetImpl()
	{
		return *m_Impl.get();
	}

	inline const Impl& GetImpl() const
	{
		return *m_Impl.get();
	}

	std::unique_ptr<Impl> m_Impl;
};

#endif // BGFX_IMGUI_BGFXIMGUIADAPTER_H
