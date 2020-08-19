// Copyright (c) 2020 udv. All rights reserved.

#include "version/window.hpp"

namespace vn {
	window *window::make(const window_props &props) {
		window *window;
#ifdef VN_PLATFORM_WINDOWS
		window = new platform::window{props};
#endif
		return window;
	}

	window::~window() = default;

	void window::on_update() {

	}
}
