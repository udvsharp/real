// Copyright (c) 2020 udv. All rights reserved.

#include "real/time/timestep.hpp"
#include "real/window.hpp"

namespace Real
{
	Window* Window::Make(const WindowProperties& props)
	{
		Window* window;
#ifdef REAL_PLATFORM_WINDOWS
		window = new Platform::Window { props };
#endif
		return window;
	}

	Window::~Window() = default;

	void Window::OnUpdate(Timestep ts)
	{

	}
}
