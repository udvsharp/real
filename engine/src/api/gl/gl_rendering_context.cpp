// Copyright (c) 2020 udv. All rights reserved.

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "version/logger.hpp"
#include "version/renderer/gl_rendering_context.hpp"

namespace vn {
	gl_rendering_context::gl_rendering_context(GLFWwindow *window_handle) {
		window_handle_ = window_handle;
		vn_assert(window_handle_, "Window handle is nullptr!");
	}

	void gl_rendering_context::init() {
		glfwMakeContextCurrent(window_handle_);

		// Glad
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			VN_CORE_ERROR("Couldn't load GL!");
		}
	}

	void gl_rendering_context::swap_buffers() {
		glfwSwapBuffers(window_handle_);
	}

	void gl_rendering_context::vsync(bool enabled) {
		// TODO: read about vsync
		if (enabled) {
			glfwSwapInterval(1);
		} else {
			glfwSwapInterval(0);
		}
	}
}