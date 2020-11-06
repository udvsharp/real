// Copyright (c) 2020 udv. All rights reserved.

#include "real/keycode.hpp"
#include "real/input.hpp"
#include "real/application.hpp"

namespace Real::Platform
{
	bool Input::IsKeyPressed(KeyCode keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Instance().Window().Native());
		auto state = glfwGetKey(window, static_cast<int>(keycode));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseBtnPressed(mouse_btn_t mouse_btn)
	{
		auto window = static_cast<GLFWwindow*>(Application::Instance().Window().Native());
		auto state = glfwGetMouseButton(window, mouse_btn);
		return state == GLFW_PRESS;
	}

	std::pair<mouse_position_t, mouse_position_t> Input::MousePosition()
	{
		auto window = static_cast<GLFWwindow*>(Application::Instance().Window().Native());
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return { x, y };
	}

	mouse_position_t Input::MouseX()
	{
		auto[x, y] = MousePosition();
		return x;
	}

	mouse_position_t Input::MouseY()
	{
		auto[x, y] = MousePosition();
		return y;
	}
}
