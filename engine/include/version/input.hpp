// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_INPUT
#define VN_INPUT

#include "version/core.hpp"
#include "version/keycode.hpp"
#include "version/input/base_input.hpp"

#ifdef VN_PLATFORM_WINDOWS
	#include "version/input/windows_input.hpp"
#else
	#error Unsupported platform!
#endif

#endif //VN_INPUT
