// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_WINDOW
#define REAL_WINDOW

#include "real/core.hpp"
#include "real/window/base_window.hpp"

#ifdef REAL_PLATFORM_WINDOWS
	#include "real/platform/windows/windows_window.hpp"
#else
	#error Unsupported platform!
#endif

#endif //REAL_WINDOW
