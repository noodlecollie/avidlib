#include "bgfx_imgui/BGFXImGuiAdapter.h"
#include "imgui.h"

#include "bgfx/bgfx.h"
#include "bgfx/embedded_shader.h"

#include "bx/allocator.h"
#include "bx/timer.h"
#include "bx/math.h"

#include "vs_ocornut_imgui.bin.h"
#include "fs_ocornut_imgui.bin.h"
#include "vs_imgui_image.bin.h"
#include "fs_imgui_image.bin.h"

#include "roboto_regular.ttf.h"
#include "robotomono_regular.ttf.h"
#include "icons_kenney.ttf.h"
#include "icons_font_awesome.ttf.h"
#include "icons_kenney.h"
#include "icons_font_awesome.h"

static constexpr bgfx::ViewId VIEW_ID = 255;
static constexpr uint8_t IMGUI_FLAGS_NONE = 0;
static constexpr uint8_t IMGUI_FLAGS_ALPHA_BLEND = 1;

enum FontID
{
	Regular,
	Mono,

	Count
};

struct FontRangeMerge
{
	const void* data;
	size_t size;
	ImWchar ranges[3];
};

static bx::DefaultAllocator DefaultAllocator;

static const bgfx::EmbeddedShader s_embeddedShaders[] =
{
	BGFX_EMBEDDED_SHADER(vs_ocornut_imgui),
	BGFX_EMBEDDED_SHADER(fs_ocornut_imgui),
	BGFX_EMBEDDED_SHADER(vs_imgui_image),
	BGFX_EMBEDDED_SHADER(fs_imgui_image),

	BGFX_EMBEDDED_SHADER_END()
};

static FontRangeMerge s_fontRangeMerge[] =
{
	{ s_iconsKenneyTtf, sizeof(s_iconsKenneyTtf), { ICON_MIN_KI, ICON_MAX_KI, 0 } },
	{ s_iconsFontAwesomeTtf, sizeof(s_iconsFontAwesomeTtf), { ICON_MIN_FA, ICON_MAX_FA, 0 } },
};

static void* memAlloc(size_t _size, void* _userData)
{
	BX_UNUSED(_userData);
	return BX_ALLOC(&DefaultAllocator, _size);
}

static void memFree(void* _ptr, void* _userData)
{
	BX_UNUSED(_userData);
	BX_FREE(&DefaultAllocator, _ptr);
}

template<typename T, size_t SIZE>
static constexpr size_t ArraySize(T (&)[SIZE])
{
	return SIZE;
}

class BGFXImGuiAdapter::Impl
{
public:
	void Create(float fontSize)
	{
		m_FontSize = fontSize;
		m_LastFrameTimestamp = bx::getHPCounter();

		ImGui::SetAllocatorFunctions(memAlloc, memFree, nullptr);
		m_ImGuiContext = ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2{1280, 720};
		io.DisplayFramebufferScale = ImVec2{1, 1};
		io.DeltaTime = 1.0f / 60.0f;
		io.IniFilename = nullptr;

		ImGui::StyleColorsDark(&ImGui::GetStyle());

		CreateImGuiProgram();
		CreateImageProgram();
		CreateVertexLayout();

		m_TextureSampler = bgfx::createUniform("s_tex", bgfx::UniformType::Sampler);

		CreateFonts();
	}

	void Destroy()
	{
		ImGui::DestroyContext(m_ImGuiContext);

		bgfx::destroy(m_TextureSampler);
		bgfx::destroy(m_FontsTexture);

		bgfx::destroy(m_ImageLodEnabled);
		bgfx::destroy(m_ImageProgram);
		bgfx::destroy(m_ImGuiProgram);
	}

	void BeginFrame()
	{
		ImGuiIO& io = ImGui::GetIO();

		if ( m_InputChar >= 0 )
		{
			io.AddInputCharacter(m_InputChar);
			m_InputChar = -1;
		}

		if ( m_KeyState != 0 )
		{
			const bool isPressed = m_KeyState > 0;
			const int keyCode = m_KeyState < 0 ? -m_KeyState : m_KeyState;

			if ( keyCode < static_cast<int>(ArraySize(io.KeysDown)) )
			{
				io.KeysDown[keyCode] = isPressed;
			}

			m_KeyState = 0;
		}

		const int64_t now = bx::getHPCounter();
		const int64_t frameTime = now - m_LastFrameTimestamp;
		m_LastFrameTimestamp = now;

		io.DisplaySize = m_DisplaySize;
		io.DisplayFramebufferScale = ImVec2{m_DisplayScale, m_DisplayScale};
		io.DeltaTime = static_cast<float>(frameTime) / static_cast<float>(bx::getHPFrequency());
		io.MousePos = m_MousePosition;
		io.MouseDown[0] = (m_MouseButtonsPressed & (1 << ImGuiMouseButton_Left)) != 0;
		io.MouseDown[1] = (m_MouseButtonsPressed & (1 << ImGuiMouseButton_Right)) != 0;
		io.MouseDown[2] = (m_MouseButtonsPressed & (1 << ImGuiMouseButton_Middle)) != 0;
		io.MouseWheel = m_ScrollDelta.y;

		m_ScrollDelta = ImVec2{0, 0};

		ImGui::NewFrame();
	}

	void EndFrame()
	{
		ImGui::Render();
		Render(ImGui::GetDrawData());
	}

	// Values that may change between frames:
	ImVec2 m_DisplaySize;
	float m_DisplayScale = 1.0f;
	ImVec2 m_MousePosition;
	uint32_t m_MouseButtonsPressed = 0;
	ImVec2 m_ScrollDelta;
	int m_InputChar = -1;
	int m_KeyState = 0;
	int64_t m_LastFrameTimestamp = 0;

private:
	void Render(ImDrawData* drawData)
	{
		// Avoid rendering when minimized, scale coordinates for retina displays (screen coordinates != framebuffer coordinates)
		const float fbWidth = drawData->DisplaySize.x * drawData->FramebufferScale.x;
		const float fbHeight = drawData->DisplaySize.y * drawData->FramebufferScale.y;

		if ( fbWidth < 1.0f || fbHeight < 1.0f)
		{
			return;
		}

		bgfx::setViewName(VIEW_ID, "ImGui");
		bgfx::setViewMode(VIEW_ID, bgfx::ViewMode::Sequential);

		SetViewport(drawData);

		for ( int32_t index = 0; index < drawData->CmdListsCount; ++index )
		{
			if ( !RenderCommandList(drawData, drawData->CmdLists[index]) )
			{
				break;
			}
		}
	}

	void SetViewport(ImDrawData* drawData)
	{
		const bgfx::Caps* caps = bgfx::getCaps();

		float ortho[16];
		const float x = drawData->DisplayPos.x;
		const float y = drawData->DisplayPos.y;
		const float width = drawData->DisplaySize.x;
		const float height = drawData->DisplaySize.y;

		bx::mtxOrtho(ortho, x, x + width, y + height, y, 0.0f, 1000.0f, 0.0f, caps->homogeneousDepth);
		bgfx::setViewTransform(VIEW_ID, nullptr, ortho);
		bgfx::setViewRect(VIEW_ID, 0, 0, static_cast<uint16_t>(width), static_cast<uint16_t>(height));
	}

	bool RenderCommandList(ImDrawData* drawData, const ImDrawList* drawList)
	{
		// (0,0) unless using multi-viewports
		const ImVec2 clipPos = drawData->DisplayPos;

		// (1,1) unless using retina display which are often (2,2)
		const ImVec2 clipScale = drawData->FramebufferScale;

		const float fbWidth = drawData->DisplaySize.x * drawData->FramebufferScale.x;
		const float fbHeight = drawData->DisplaySize.y * drawData->FramebufferScale.y;

		bgfx::TransientVertexBuffer tvb;
		bgfx::TransientIndexBuffer tib;

		const uint32_t numVertices = static_cast<uint32_t>(drawList->VtxBuffer.size());
		const uint32_t numIndices = static_cast<uint32_t>(drawList->IdxBuffer.size());

		if ( !TransientBuffersAvailable(numVertices, numIndices) )
		{
			// Not enough space in transient buffer, just quit drawing the rest.
			return false;
		}

		bgfx::allocTransientVertexBuffer(&tvb, numVertices, m_VertexLayout);
		bgfx::allocTransientIndexBuffer(&tib, numIndices, sizeof(ImDrawIdx) == 4);

		ImDrawVert* verts = reinterpret_cast<ImDrawVert*>(tvb.data);
		bx::memCopy(verts, drawList->VtxBuffer.begin(), numVertices * sizeof(ImDrawVert));

		ImDrawIdx* indices = reinterpret_cast<ImDrawIdx*>(tib.data);
		bx::memCopy(indices, drawList->IdxBuffer.begin(), numIndices * sizeof(ImDrawIdx));

		uint32_t offset = 0;
		for ( const ImDrawCmd* cmd = drawList->CmdBuffer.begin(); cmd != drawList->CmdBuffer.end(); ++cmd )
		{
			if ( cmd->UserCallback )
			{
				cmd->UserCallback(drawList, cmd);
			}
			else if ( cmd->ElemCount != 0 )
			{
				uint64_t state = BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_MSAA;

				bgfx::TextureHandle th = m_FontsTexture;
				bgfx::ProgramHandle program = m_ImGuiProgram;

				if ( cmd->TextureId )
				{
					union TextureIDUnion
					{
						ImTextureID ptr;

						struct
						{
							bgfx::TextureHandle handle;
							uint8_t flags;
							uint8_t mip;
						} s;
					};

					TextureIDUnion texture{cmd->TextureId};

					if ( texture.s.flags & IMGUI_FLAGS_ALPHA_BLEND )
					{
						state |= BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA);
					}

					th = texture.s.handle;

					if ( texture.s.mip != 0 )
					{
						const float lodEnabled[4] = { static_cast<float>(texture.s.mip), 1.0f, 0.0f, 0.0f };
						bgfx::setUniform(m_ImageLodEnabled, lodEnabled);
						program = m_ImageProgram;
					}
				}
				else
				{
					state |= BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA);
				}

				// Project scissor/clipping rectangles into framebuffer space
				ImVec4 clipRect;
				clipRect.x = (cmd->ClipRect.x - clipPos.x) * clipScale.x;
				clipRect.y = (cmd->ClipRect.y - clipPos.y) * clipScale.y;
				clipRect.z = (cmd->ClipRect.z - clipPos.x) * clipScale.x;
				clipRect.w = (cmd->ClipRect.w - clipPos.y) * clipScale.y;

				if ( clipRect.x < fbWidth && clipRect.y < fbHeight && clipRect.z >= 0.0f && clipRect.w >= 0.0f )
				{
					const uint16_t xx = static_cast<uint16_t>(bx::max(clipRect.x, 0.0f));
					const uint16_t yy = static_cast<uint16_t>(bx::max(clipRect.y, 0.0f));

					bgfx::setScissor(xx,
									 yy,
									 static_cast<uint16_t>(bx::min(clipRect.z, 65535.0f) - xx),
									 static_cast<uint16_t>(bx::min(clipRect.w, 65535.0f) - yy));

					bgfx::setState(state);
					bgfx::setTexture(0, m_TextureSampler, th);
					bgfx::setVertexBuffer(0, &tvb, 0, numVertices);
					bgfx::setIndexBuffer(&tib, offset, cmd->ElemCount);
					bgfx::submit(VIEW_ID, program);
				}
			}

			offset += cmd->ElemCount;
		}

		return true;
	}

	void CreateImGuiProgram()
	{
		const bgfx::RendererType::Enum type = bgfx::getRendererType();

		m_ImGuiProgram = bgfx::createProgram(
			bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_ocornut_imgui"),
			bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_ocornut_imgui"),
			true
		);
	}

	void CreateImageProgram()
	{
		const bgfx::RendererType::Enum type = bgfx::getRendererType();
		m_ImageLodEnabled = bgfx::createUniform("u_imageLodEnabled", bgfx::UniformType::Vec4);

		m_ImageProgram = bgfx::createProgram(
			bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_imgui_image"),
			bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_imgui_image"),
			true
		);
	}

	void CreateVertexLayout()
	{
		m_VertexLayout
			.begin()
			.add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
			.end();
	}

	// Boo to all the const_casts in this function. The ImGui functions take
	// a void* rather than a const void*, so unfortunately this is required.
	void CreateFonts()
	{
		ImFontConfig config;
		config.FontDataOwnedByAtlas = false;
		config.MergeMode = false;

		ImGuiIO& io = ImGui::GetIO();
		const ImWchar* ranges = io.Fonts->GetGlyphRangesCyrillic();

		m_KnownFonts[FontID::Regular] = io.Fonts->AddFontFromMemoryTTF(
			const_cast<uint8_t*>(s_robotoRegularTtf),
			sizeof(s_robotoRegularTtf),
			m_FontSize,
			&config,
			ranges
		);

		m_KnownFonts[FontID::Mono] = io.Fonts->AddFontFromMemoryTTF(
			const_cast<uint8_t*>(s_robotoMonoRegularTtf),
			sizeof(s_robotoMonoRegularTtf),
			m_FontSize - 3.0f,
			&config,
			ranges
		);

		config.MergeMode = true;
		config.DstFont = m_KnownFonts[FontID::Regular];

		for ( size_t index = 0; index < BX_COUNTOF(s_fontRangeMerge); ++index )
		{
			const FontRangeMerge& frm = s_fontRangeMerge[index];

			io.Fonts->AddFontFromMemoryTTF(
				const_cast<void*>(frm.data),
				static_cast<int>(frm.size),
				m_FontSize - 3.0f,
				&config,
				frm.ranges
			);
		}

		uint8_t* data = nullptr;
		int32_t width = 0;
		int32_t height = 0;
		io.Fonts->GetTexDataAsRGBA32(&data, &width, &height);

		m_FontsTexture = bgfx::createTexture2D(
			static_cast<uint16_t>(width),
			static_cast<uint16_t>(height),
			false,
			1,
			bgfx::TextureFormat::BGRA8,
			0,
			bgfx::copy(data, width * height * 4)
		);
	}

	inline bool TransientBuffersAvailable(uint32_t numVertices, uint32_t numIndices) const
	{
		return
			numVertices == bgfx::getAvailTransientVertexBuffer(numVertices, m_VertexLayout) &&
			(numIndices == 0 || numIndices == bgfx::getAvailTransientIndexBuffer(numIndices));
	}

	// Persistent values used for creation:
	float m_FontSize = 18.0f;
	ImGuiContext* m_ImGuiContext;
	bgfx::VertexLayout  m_VertexLayout;
	bgfx::ProgramHandle m_ImGuiProgram;
	bgfx::ProgramHandle m_ImageProgram;
	bgfx::TextureHandle m_FontsTexture;
	bgfx::UniformHandle m_TextureSampler;
	bgfx::UniformHandle m_ImageLodEnabled;
	ImFont* m_KnownFonts[FontID::Count];
};

BGFXImGuiAdapter::BGFXImGuiAdapter() :
	m_Impl(new Impl())
{
}

BGFXImGuiAdapter::~BGFXImGuiAdapter()
{
}

void BGFXImGuiAdapter::Create(float fontSize)
{
	GetImpl().Create(fontSize);
}

void BGFXImGuiAdapter::Destroy()
{
	GetImpl().Destroy();
}

void BGFXImGuiAdapter::BeginFrame()
{
	GetImpl().BeginFrame();
}

void BGFXImGuiAdapter::EndFrame()
{
	GetImpl().EndFrame();
}

void BGFXImGuiAdapter::SetKeyMapping(ImGuiKey_ imguiKey, int externalKey)
{
	ImGuiIO& io = ImGui::GetIO();

	if ( imguiKey < ImGuiKey_COUNT && externalKey >= 0 && externalKey < static_cast<int>(ArraySize(io.KeysDown)) )
	{
		io.KeyMap[imguiKey] = externalKey;
	}
}

ImVec2 BGFXImGuiAdapter::DisplaySize() const
{
	return GetImpl().m_DisplaySize;
}

void BGFXImGuiAdapter::SetDisplaySize(const ImVec2& size)
{
	GetImpl().m_DisplaySize = size;
}

float BGFXImGuiAdapter::DisplayScale() const
{
	return GetImpl().m_DisplayScale;
}

void BGFXImGuiAdapter::SetDisplayScale(float scale)
{
	GetImpl().m_DisplayScale = scale;
}

ImVec2 BGFXImGuiAdapter::MousePosition() const
{
	return GetImpl().m_MousePosition;
}

void BGFXImGuiAdapter::SetMousePosition(const ImVec2& pos)
{
	GetImpl().m_MousePosition = pos;
}

uint32_t BGFXImGuiAdapter::MouseButtonsPressed() const
{
	return GetImpl().m_MouseButtonsPressed;
}

void BGFXImGuiAdapter::OverwriteMouseButtonsPressed(uint32_t buttons)
{
	GetImpl().m_MouseButtonsPressed = buttons;
}

void BGFXImGuiAdapter::SetMouseButtonPressed(ImGuiMouseButton_ button, bool pressed)
{
	if ( pressed )
	{
		GetImpl().m_MouseButtonsPressed |= (1 << button);
	}
	else
	{
		GetImpl().m_MouseButtonsPressed &= ~(1 << button);
	}
}

ImVec2 BGFXImGuiAdapter::ScrollDelta() const
{
	return GetImpl().m_ScrollDelta;
}

void BGFXImGuiAdapter::SetScrollDelta(const ImVec2& delta)
{
	GetImpl().m_ScrollDelta = delta;
}

void BGFXImGuiAdapter::SetInputChar(unsigned int input)
{
	const int inputSigned = static_cast<int>(input);

	if ( inputSigned >= 0 )
	{
		GetImpl().m_InputChar = inputSigned;
	}
}

void BGFXImGuiAdapter::SetKeyState(int key, bool pressed)
{
	if ( key > 0 )
	{
		GetImpl().m_KeyState = pressed ? key : -key;
	}
}
