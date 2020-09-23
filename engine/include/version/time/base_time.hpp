// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_TIME_BASE
#define VN_TIME_BASE

#include "version/core.hpp"

namespace vn {
	// To be defined per platform
	namespace platform {
		float time();
	}

	inline float time() { return vn::platform::time(); };
}

#endif //VN_TIME_BASE
