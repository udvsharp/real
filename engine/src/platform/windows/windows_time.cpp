// Copyright (c) 2020 udv. All rights reserved.

#include "version/platform/windows/windows_time.hpp"
#include "version/api/gl/gl_headers.hpp"

namespace vn::platform {
	float time() {
		// TODO: use native time
		return glfwGetTime();
	}
}
