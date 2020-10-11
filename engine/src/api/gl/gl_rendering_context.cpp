// Copyright (c) 2020 udv. All rights reserved.

#include "real/logger.hpp"
#include "real/api/gl/gl_headers.hpp"
#include "real/api/gl/gl_rendering_context.hpp"

namespace real {
	gl_rendering_context::gl_rendering_context(GLFWwindow *window_handle) {
		window_handle_ = window_handle;
	}

	void gl_rendering_context::init() {
		REAL_CORE_TRACE("Initializing GL rendering context...");

		glfwMakeContextCurrent(window_handle_);

		if (window_handle_ == nullptr) {
			REAL_CORE_ERROR("Failed to create window(handle is nullptr)!");
			glfwTerminate();
			std::terminate();
		}

		// Glad
		REAL_CORE_TRACE("Loading GL...");
		if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
			REAL_CORE_ERROR("Couldn't load GL!");
			glfwTerminate();
			std::terminate();
		}
		REAL_CORE_INFO("Loaded GL successfully!");

		// Info
		REAL_CORE_INFO(
				"\nOpenGL info:\n"
				"\tVendor  : {}\n"
				"\tRenderer: {}\n"
				"\tVersion : {}",
				glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION)
		);
	}

	void gl_rendering_context::swap_buffers() {
		glfwSwapBuffers(window_handle_);
	}

	void gl_rendering_context::vsync(bool enabled) {
		if (enabled) {
			glfwSwapInterval(1);
		} else {
			glfwSwapInterval(0);
		}
	}
}