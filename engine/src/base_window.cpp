// Copyright (c) 2020 udv. All rights reserved.

#include "real/time/timestep.hpp"
#include "real/window.hpp"

namespace Real
{
	Real::Scope<Window> Window::Make(const WindowProperties& props)
	{
		Real::Scope<Window> window;
#ifdef REAL_PLATFORM_WINDOWS
		window = Real::MakeScope<Platform::Window>(props);
#endif
		return window;
	}

	Window::~Window() = default;

	void Window::OnUpdate(Timestep ts)
	{

	}
}
