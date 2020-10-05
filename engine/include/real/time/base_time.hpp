// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_TIME_BASE
#define REAL_TIME_BASE

#include "real/core.hpp"

namespace real {
	// To be defined per platform
	namespace platform {
		float time();
	}

	inline float time() { return real::platform::time(); };
}

#endif //REAL_TIME_BASE
