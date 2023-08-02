// Copyright (c) 2020 udv. All rights reserved.

#include "real/logger.hpp"
#include "real/api/gl/gl_headers.hpp"
#include "real/api/gl/gl_rendering_context.hpp"

namespace Real
{
	GLRenderingContext::GLRenderingContext(GLFWwindow* windowHandle)
	{
		this->glfwWindowHandle = windowHandle;
	}

	GLRenderingContext::~GLRenderingContext()
	{
		REAL_CORE_TRACE("Destroying rendering context...");
		glfwDestroyWindow(glfwWindowHandle);
		glfwTerminate();
	}

	void GLRenderingContext::Init()
	{
		REAL_CORE_TRACE("Initializing GL rendering context...");

		glfwMakeContextCurrent(glfwWindowHandle);

		if (glfwWindowHandle == nullptr)
		{
			REAL_CORE_ERROR("Failed to create window(handle is nullptr)!");
			glfwTerminate();
			std::terminate();
		}

		// Glad
		REAL_CORE_TRACE("Loading GL...");
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
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
                reinterpret_cast<const char*>(glGetString(GL_VENDOR)),
                reinterpret_cast<const char*>(glGetString(GL_RENDERER)),
                reinterpret_cast<const char*>(glGetString(GL_VERSION))
		);
	}

	void GLRenderingContext::SwapBuffers()
	{
		glfwSwapBuffers(glfwWindowHandle);
	}

	void GLRenderingContext::VSync(bool enabled)
	{
		if (enabled)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}
	}
}