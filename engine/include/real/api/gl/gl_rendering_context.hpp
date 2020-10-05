// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_GL_RENDERING_CONTEXT
#define REAL_GL_RENDERING_CONTEXT

#include "real/renderer/base_rendering_context.hpp"

// Avoid including glfw
struct GLFWwindow;

namespace real {
	class REAL_API gl_rendering_context : public rendering_context {
	public:
		explicit gl_rendering_context(GLFWwindow *window_handle);

		void init() override;
		void swap_buffers() override;
		void vsync(bool enabled) override;
	private:
		GLFWwindow *window_handle_;
	};
}

#endif //REAL_GL_RENDERING_CONTEXT
