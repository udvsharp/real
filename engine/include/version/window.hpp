// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_WINDOW
#define VN_WINDOW

#include "version/core.hpp"
#include "version/window/base_window.hpp"

#ifdef VN_PLATFORM_WINDOWS
	#include "version/window/windows_window.hpp"
#else
	#error Unsupported platform!
#endif

#endif //VN_WINDOW
