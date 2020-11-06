// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_GL_RENDERING_CONTEXT
#define REAL_GL_RENDERING_CONTEXT

#include "real/renderer/base_rendering_context.hpp"

// Avoid including glfw
struct GLFWwindow;

namespace Real
{
	class REAL_API GLRenderingContext : public RenderingContext
	{
	public:
		explicit GLRenderingContext(GLFWwindow* windowHandle);

		void Init() override;
		void SwapBuffers() override;
		void VSync(bool enabled) override;
	private:
		GLFWwindow* glfwWindowHandle;
	};
}

#endif //REAL_GL_RENDERING_CONTEXT
