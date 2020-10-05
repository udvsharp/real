// Copyright (c) 2020 udv. All rights reserved.

#include "real/platform/windows/windows_time.hpp"
#include "real/api/gl/gl_headers.hpp"

namespace real::platform {
	float time() {
		// TODO: use native time
		return glfwGetTime();
	}
}
