// Copyright (c) 2020 udv. All rights reserved.

#include "real/time/timestep.hpp"
#include "real/window.hpp"

namespace real {
	window *window::make(const window_props &props) {
		window *window;
#ifdef REAL_PLATFORM_WINDOWS
		window = new platform::window{ props };
#endif
		return window;
	}

	window::~window() = default;

	void window::on_update(timestep ts) {

	}
}
