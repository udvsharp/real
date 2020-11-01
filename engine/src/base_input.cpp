// Copyright (c) 2020 udv. All rights reserved.

#include "real/input.hpp"

namespace real {
	input *input::make() {
		input *input;

#ifdef REAL_PLATFORM_WINDOWS
		input = new platform::input{};
#endif
		return input;
	}
}
