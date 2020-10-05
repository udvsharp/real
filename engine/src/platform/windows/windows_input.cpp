// Copyright (c) 2020 udv. All rights reserved.

#include "real/keycode.hpp"
#include "real/input.hpp"
#include "real/application.hpp"

namespace real::platform {
	bool input::is_key_pressed(key_code keycode) {
		auto window = static_cast<GLFWwindow *>(application::instance().window().native());
		auto state  = glfwGetKey(window, static_cast<int>(keycode));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool input::is_mouse_btn_pressed(mouse_btn_t mouse_btn) {
		auto window = static_cast<GLFWwindow *>(application::instance().window().native());
		auto state  = glfwGetMouseButton(window, mouse_btn);
		return state == GLFW_PRESS;
	}

	std::pair<mouse_position_t, mouse_position_t> input::mouse_position() {
		auto   window = static_cast<GLFWwindow *>(application::instance().window().native());
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return {x, y};
	}

	mouse_position_t input::mouse_x() {
		auto[x, y] = mouse_position();
		return x;
	}

	mouse_position_t input::mouse_y() {
		auto[x, y] = mouse_position();
		return y;
	}
}
