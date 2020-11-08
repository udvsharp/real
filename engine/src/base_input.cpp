// Copyright (c) 2020 udv. All rights reserved.

#include "real/input.hpp"

namespace Real
{
	Real::Scope<Input> Input::Make()
	{
		Real::Scope<Input> input;

#ifdef REAL_PLATFORM_WINDOWS
		input = Real::MakeScope<Platform::Input>();
#endif
		return input;
	}
}
