// Copyright (c) 2020 udv. All rights reserved.

#include "real/input.hpp"

namespace Real
{
	Input* Input::Make()
	{
		Input* input;

#ifdef REAL_PLATFORM_WINDOWS
		input = new Platform::Input {};
#endif
		return input;
	}
}
