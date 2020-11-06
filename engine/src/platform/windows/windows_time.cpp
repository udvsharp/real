// Copyright (c) 2020 udv. All rights reserved.

#include "real/platform/windows/windows_time.hpp"

namespace Real::Platform
{
	double Time()
	{
		return glfwGetTime();
	}
}
