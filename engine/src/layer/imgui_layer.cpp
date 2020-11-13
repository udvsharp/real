// Copyright (c) 2020 udv. All rights reserved.

#define GLFW_INCLUDE_NONE

// FIXME remove GL Headers
#include "real/api/gl/gl_headers.hpp"

#include "real/input.hpp"
#include "real/layer/imgui_layer.hpp"
#include "real/application.hpp"
#include "api/gl/imgui_impl_opengl3.h"

namespace Real
{

	void ImGUILayer::Attach()
	{
		Layer::Attach();

		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		// @formatter:off
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;         // We can honor GetMouseCursor() values (optional)
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;          // We can honor io.WantSetMousePos requests (optional, rarely used)
		io.ConfigFlags  |= ImGuiConfigFlags_DockingEnable;
		io.BackendPlatformName = "imgui_impl_glfw";

		// Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[] array.
		io.KeyMap[ImGuiKey_Tab]          = static_cast<int>(REAL_KEY_TAB);
		io.KeyMap[ImGuiKey_LeftArrow]    = static_cast<int>(REAL_KEY_LEFT);
		io.KeyMap[ImGuiKey_RightArrow]   = static_cast<int>(REAL_KEY_RIGHT);
		io.KeyMap[ImGuiKey_UpArrow]      = static_cast<int>(REAL_KEY_UP);
		io.KeyMap[ImGuiKey_DownArrow]    = static_cast<int>(REAL_KEY_DOWN);
		io.KeyMap[ImGuiKey_PageUp]       = static_cast<int>(REAL_KEY_PAGE_UP);
		io.KeyMap[ImGuiKey_PageDown]     = static_cast<int>(REAL_KEY_PAGE_DOWN);
		io.KeyMap[ImGuiKey_Home]         = static_cast<int>(REAL_KEY_HOME);
		io.KeyMap[ImGuiKey_End]          = static_cast<int>(REAL_KEY_END);
		io.KeyMap[ImGuiKey_Insert]       = static_cast<int>(REAL_KEY_INSERT);
		io.KeyMap[ImGuiKey_Delete]       = static_cast<int>(REAL_KEY_DELETE);
		io.KeyMap[ImGuiKey_Backspace]    = static_cast<int>(REAL_KEY_BACKSPACE);
		io.KeyMap[ImGuiKey_Space]        = static_cast<int>(REAL_KEY_SPACE);
		io.KeyMap[ImGuiKey_Enter]        = static_cast<int>(REAL_KEY_ENTER);
		io.KeyMap[ImGuiKey_Escape]       = static_cast<int>(REAL_KEY_ESCAPE);
		io.KeyMap[ImGuiKey_KeyPadEnter]  = static_cast<int>(REAL_KEY_KP_ENTER);
		io.KeyMap[ImGuiKey_A]            = static_cast<int>(REAL_KEY_A);
		io.KeyMap[ImGuiKey_C]            = static_cast<int>(REAL_KEY_C);
		io.KeyMap[ImGuiKey_V]            = static_cast<int>(REAL_KEY_V);
		io.KeyMap[ImGuiKey_X]            = static_cast<int>(REAL_KEY_X);
		io.KeyMap[ImGuiKey_Y]            = static_cast<int>(REAL_KEY_Y);
		io.KeyMap[ImGuiKey_Z]            = static_cast<int>(REAL_KEY_Z);
		// @formatter:on

		ImGui_ImplOpenGL3_Init("#version 410 core");
	}

	void ImGUILayer::Detach()
	{
		Layer::Detach();
	}

	void ImGUILayer::Update(Timestep ts)
	{
		Layer::Update(ts);

		ImGuiIO& io = ImGui::GetIO();
		Window& window = Application::Instance().Window();
		io.DisplaySize = ImVec2(static_cast<float>(window.Width()),
				static_cast<float>(window.Height()));

		static float old_time = 0.0f;
		auto time = static_cast<float>(glfwGetTime());
		io.DeltaTime = time > 0.0 ? (time - old_time) : (1.0f / 60.0f);
		old_time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGUILayer::HandleEvent(Event& ev)
	{
		Layer::HandleEvent(ev);

		ImGuiIO& io = ImGui::GetIO();

		EventDispatcher dispatcher { &ev };
		dispatcher.Dispatch<MouseBtnPressedEvent>([&io](MouseBtnPressedEvent& ev) -> bool
		{
			io.MouseDown[ev.Button()] = true;

			return false;
		});
		dispatcher.Dispatch<MouseBtnReleasedEvent>(
				[&io](MouseBtnReleasedEvent& ev) -> bool
				{
					io.MouseDown[ev.Button()] = false;

					return false;
				});
		dispatcher.Dispatch<MouseMovedEvent>([&io](MouseMovedEvent& ev) -> bool
		{
			io.MousePos = ImVec2(static_cast<float>(ev.X()), static_cast<float>(ev.Y()));

			return false;
		});
		dispatcher.Dispatch<MouseScrolledEvent>([&io](MouseScrolledEvent& ev) -> bool
		{
			io.MouseWheel += static_cast<float>(ev.XOffset());
			io.MouseWheelH += static_cast<float>(ev.YOffset());

			return false;
		});

		dispatcher.Dispatch<WindowResizedEvent>([&io](WindowResizedEvent& ev) -> bool
		{
			io.DisplaySize = ImVec2(static_cast<float>(ev.Width()),
					static_cast<float>(ev.Height()));
			io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
			glViewport(0, 0, ev.Width(), ev.Height());

			return false;
		});

		dispatcher.Dispatch<KeyPressedEvent>([&io](KeyPressedEvent& ev) -> bool
		{
			io.KeysDown[ev.KeyCode()] = true;
			io.KeyCtrl = io.KeysDown[static_cast<int>(REAL_KEY_LEFT_CONTROL)] ||
					io.KeysDown[static_cast<int>(REAL_KEY_RIGHT_CONTROL)];
			io.KeyShift = io.KeysDown[static_cast<int>(REAL_KEY_LEFT_SHIFT)] ||
					io.KeysDown[static_cast<int>(REAL_KEY_RIGHT_SHIFT)];
			io.KeyAlt = io.KeysDown[static_cast<int>(REAL_KEY_LEFT_ALT)] ||
					io.KeysDown[static_cast<int>(REAL_KEY_RIGHT_ALT)];
			io.KeySuper = io.KeysDown[static_cast<int>(REAL_KEY_LEFT_SUPER)] ||
					io.KeysDown[static_cast<int>(REAL_KEY_RIGHT_SUPER)];

			return false;
		});
		dispatcher.Dispatch<KeyReleasedEvent>([&io](KeyReleasedEvent& ev) -> bool
		{
			io.KeysDown[ev.KeyCode()] = false;

			return false;
		});
		dispatcher.Dispatch<KeyTypedEvent>([&io](KeyTypedEvent& ev) -> bool
		{
			io.AddInputCharacter(static_cast<unsigned int>(ev.KeyCode()));

			return false;
		});
	}

#ifdef REAL_DEBUG
	ImGUILayer::ImGUILayer()
			:Layer("imgui layer")
	{}
#else
	ImGUILayer::ImGUILayer() : layer() {

	}
#endif

	ImGUILayer::~ImGUILayer() = default;
}
