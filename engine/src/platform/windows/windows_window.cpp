// Copyright (c) 2020 udv. All rights reserved.


#include "real/time/timestep.hpp"

#include "real/logger.hpp"
#include "real/event.hpp"
#include "real/platform/windows/windows_window.hpp"

namespace Real::Platform
{

	static bool s_glfw_initialized = false;

	void GLFWErrorCallback(int32_t code, const char* msg)
	{
		REAL_CORE_ERROR("GLFW Error: ({:#x}) {}", code, msg);
	}

	Window::Window(WindowData data)
			:nativeWindow { nullptr }, renderingContext { nullptr },
			 windowData(std::move(data))
	{
	}

	void Window::Init()
	{
		if (!s_glfw_initialized)
		{
			REAL_CORE_TRACE("Initializing GLFW...");

			if (glfwInit() == GLFW_TRUE)
			{
				s_glfw_initialized = true;
				REAL_CORE_INFO("Successfully initialized GLFW");
			}
			else
			{
				REAL_CORE_ERROR("Couldn't initialize GLFW!");
			}

			glfwSetErrorCallback(GLFWErrorCallback);
		}

		REAL_CORE_TRACE("Creating window: {0}, {1}, {2}", windowData.title,
				windowData.width,
				windowData.height);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		// Testing
		// Antialiasing
		glfwWindowHint(GLFW_SAMPLES, 4);
		nativeWindow = glfwCreateWindow(windowData.width, windowData.height,
				windowData.title.c_str(),
				nullptr, nullptr);
		// TODO: abstract api
		renderingContext = new GLRenderingContext { nativeWindow };
		renderingContext->Init();

		glfwSetWindowUserPointer(nativeWindow, &windowData);
		VSyncNative(windowData.isVSync);

		// GLFW callbacks
		glfwSetWindowSizeCallback(nativeWindow,
				[](GLFWwindow* window, int width, int height)
				{
					WindowData& data = *(WindowData*)glfwGetWindowUserPointer(
							window);

					data.width = width;
					data.height = height;

					WindowResizedEvent ev {
							static_cast<window_dimension_t>(width),
							static_cast<window_dimension_t>(height) };
					data.ev_callback(ev);
				});

		glfwSetWindowCloseCallback(nativeWindow, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowClosedEvent ev {};
			data.ev_callback(ev);
		});

		glfwSetKeyCallback(nativeWindow,
				[](GLFWwindow* window, int key, int scancode, int action,
						int mods)
				{
					WindowData& data = *(WindowData*)glfwGetWindowUserPointer(
							window);

					switch (action)
					{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key);
						data.ev_callback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						data.ev_callback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key);
						data.ev_callback(event);
						break;
					}
					default:
					{
						REAL_CORE_ERROR("Unknown key action: {}", action);
					}
					}
				});

		glfwSetCharCallback(nativeWindow, [](GLFWwindow* window, uint32_t character)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent ev(character);
			data.ev_callback(ev);
		});

		glfwSetMouseButtonCallback(nativeWindow,
				[](GLFWwindow* window, int button, int action,
						int mods)
				{
					WindowData& data = *(WindowData*)glfwGetWindowUserPointer(
							window);

					switch (action)
					{
					case GLFW_PRESS:
					{
						MouseBtnPressedEvent event(button);
						data.ev_callback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseBtnReleasedEvent event(button);
						data.ev_callback(event);
						break;
					}
					default:
					{
						REAL_CORE_ERROR("Unknown key action: {}",
								action);
					}
					}
				});

		glfwSetScrollCallback(nativeWindow,
				[](GLFWwindow* window, double xOffset, double yOffset)
				{
					WindowData& data = *(WindowData*)glfwGetWindowUserPointer(
							window);

					MouseScrolledEvent event((float)xOffset, (float)yOffset);
					data.ev_callback(event);
				});

		glfwSetCursorPosCallback(nativeWindow,
				[](GLFWwindow* window, double xPos, double yPos)
				{
					WindowData& data = *(WindowData*)glfwGetWindowUserPointer(
							window);

					MouseMovedEvent event((float)xPos, (float)yPos);
					data.ev_callback(event);
				});
	}

	Window::~Window()
	{
		::Real::Window::~Window();
		REAL_CORE_TRACE("Destroying native window");
		glfwDestroyWindow(nativeWindow);
		glfwTerminate(); // TODO: terminate GLFW in rendering context?
	}

	void Window::OnUpdate(Timestep ts)
	{
		::Real::Window::OnUpdate(ts);
		glfwPollEvents();
		renderingContext->SwapBuffers();
	}

	void Window::VSyncNative(bool enabled)
	{
		renderingContext->VSync(enabled);
	}

	void Window::VSync(bool enabled)
	{
		VSyncNative(enabled);
		windowData.isVSync = enabled;
	}

	void Window::EventCallback(const event_callback_t& callback)
	{
		windowData.ev_callback = callback;
	}
}