// Copyright (c) 2020 udv. All rights reserved.

#define GLFW_INCLUDE_NONE

// FIXME remove GL Headers
#include "version/api/gl/gl_headers.hpp"

#include "version/input.hpp"
#include "version/layer/imgui_layer.hpp"
#include "version/application.hpp"
#include "api/gl/imgui_impl_opengl3.h"

namespace vn {

    void imgui_layer::attach() {
        layer::attach();

        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO &io            = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;         // We can honor GetMouseCursor() values (optional)
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;          // We can honor io.WantSetMousePos requests (optional, rarely used)
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.BackendPlatformName = "imgui_impl_glfw";

        // Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[] array.
        io.KeyMap[ImGuiKey_Tab]         = static_cast<int>(VN_KEY_TAB);
        io.KeyMap[ImGuiKey_LeftArrow]   = static_cast<int>(VN_KEY_LEFT);
        io.KeyMap[ImGuiKey_RightArrow]  = static_cast<int>(VN_KEY_RIGHT);
        io.KeyMap[ImGuiKey_UpArrow]     = static_cast<int>(VN_KEY_UP);
        io.KeyMap[ImGuiKey_DownArrow]   = static_cast<int>(VN_KEY_DOWN);
        io.KeyMap[ImGuiKey_PageUp]      = static_cast<int>(VN_KEY_PAGE_UP);
        io.KeyMap[ImGuiKey_PageDown]    = static_cast<int>(VN_KEY_PAGE_DOWN);
        io.KeyMap[ImGuiKey_Home]        = static_cast<int>(VN_KEY_HOME);
        io.KeyMap[ImGuiKey_End]         = static_cast<int>(VN_KEY_END);
        io.KeyMap[ImGuiKey_Insert]      = static_cast<int>(VN_KEY_INSERT);
        io.KeyMap[ImGuiKey_Delete]      = static_cast<int>(VN_KEY_DELETE);
        io.KeyMap[ImGuiKey_Backspace]   = static_cast<int>(VN_KEY_BACKSPACE);
        io.KeyMap[ImGuiKey_Space]       = static_cast<int>(VN_KEY_SPACE);
        io.KeyMap[ImGuiKey_Enter]       = static_cast<int>(VN_KEY_ENTER);
        io.KeyMap[ImGuiKey_Escape]      = static_cast<int>(VN_KEY_ESCAPE);
        io.KeyMap[ImGuiKey_KeyPadEnter] = static_cast<int>(VN_KEY_KP_ENTER);
        io.KeyMap[ImGuiKey_A]           = static_cast<int>(VN_KEY_A);
        io.KeyMap[ImGuiKey_C]           = static_cast<int>(VN_KEY_C);
        io.KeyMap[ImGuiKey_V]           = static_cast<int>(VN_KEY_V);
        io.KeyMap[ImGuiKey_X]           = static_cast<int>(VN_KEY_X);
        io.KeyMap[ImGuiKey_Y]           = static_cast<int>(VN_KEY_Y);
        io.KeyMap[ImGuiKey_Z]           = static_cast<int>(VN_KEY_Z);

        ImGui_ImplOpenGL3_Init("#version 410 core");
    }

    void imgui_layer::detach() {
        layer::detach();
    }

    void imgui_layer::update(timestep ts) {
	    layer::update(ts);

        ImGuiIO &io     = ImGui::GetIO();
        window  &window = application::instance().window();
        io.DisplaySize = ImVec2(static_cast<float>(window.width()), static_cast<float>(window.height()));

        static float old_time = 0.0f;
        auto         time     = static_cast<float>(glfwGetTime());
        io.DeltaTime = time > 0.0 ? (time - old_time) : (1.0f / 60.0f);
        old_time = time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void imgui_layer::handle_event(ev &ev) {
        layer::handle_event(ev);

        ImGuiIO &io = ImGui::GetIO();

        ev_dispatcher dispatcher{&ev};
        dispatcher.dispatch<mouse_btn_press_ev>([&io](mouse_btn_press_ev &ev) -> bool {
            io.MouseDown[ev.button()] = true;

            return false;
        });
        dispatcher.dispatch<mouse_btn_release_ev>([&io](mouse_btn_release_ev &ev) -> bool {
            io.MouseDown[ev.button()] = false;

            return false;
        });
        dispatcher.dispatch<mouse_move_ev>([&io](mouse_move_ev &ev) -> bool {
            io.MousePos = ImVec2(static_cast<float>(ev.x()), static_cast<float>(ev.y()));

            return false;
        });
        dispatcher.dispatch<mouse_scroll_ev>([&io](mouse_scroll_ev &ev) -> bool {
            io.MouseWheel += static_cast<float>(ev.x_offset());
            io.MouseWheelH += static_cast<float>(ev.y_offset());

            return false;
        });

        dispatcher.dispatch<window_resize_ev>([&io](window_resize_ev &ev) -> bool {
            io.DisplaySize             = ImVec2(static_cast<float>(ev.width()), static_cast<float>(ev.height()));
            io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
            glViewport(0, 0, ev.width(), ev.height());

            return false;
        });

        dispatcher.dispatch<key_press_ev>([&io](key_press_ev &ev) -> bool {
            io.KeysDown[ev.key_code()] = true;
            io.KeyCtrl  = io.KeysDown[static_cast<int>(VN_KEY_LEFT_CONTROL)] || io.KeysDown[static_cast<int>(VN_KEY_RIGHT_CONTROL)];
            io.KeyShift = io.KeysDown[static_cast<int>(VN_KEY_LEFT_SHIFT)]   || io.KeysDown[static_cast<int>(VN_KEY_RIGHT_SHIFT)];
            io.KeyAlt   = io.KeysDown[static_cast<int>(VN_KEY_LEFT_ALT)]     || io.KeysDown[static_cast<int>(VN_KEY_RIGHT_ALT)];
            io.KeySuper = io.KeysDown[static_cast<int>(VN_KEY_LEFT_SUPER)]   || io.KeysDown[static_cast<int>(VN_KEY_RIGHT_SUPER)];

            return false;
        });
        dispatcher.dispatch<key_release_ev>([&io](key_release_ev &ev) -> bool {
            io.KeysDown[ev.key_code()] = false;

            return false;
        });
        dispatcher.dispatch<key_typed_ev>([&io](key_typed_ev &ev) -> bool {
            io.AddInputCharacter(ev.key_code());

            return false;
        });
    }

#ifdef VN_DEBUG
    imgui_layer::imgui_layer() : layer("imgui layer") {}
#else
    imgui_layer::imgui_layer() : layer() {

    }
#endif

    imgui_layer::~imgui_layer() {

    }
}
