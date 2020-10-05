// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_INPUT
#define REAL_INPUT

#include "real/core.hpp"
#include "real/keycode.hpp"
#include "real/input/base_input.hpp"

#ifdef REAL_PLATFORM_WINDOWS
	#include "real/platform/windows/windows_input.hpp"
#else
	#error Unsupported platform!
#endif

#endif //REAL_INPUT
