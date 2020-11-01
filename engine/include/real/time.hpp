// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_TIME
#define REAL_TIME

#include "real/time/timestep.hpp"

#ifdef REAL_PLATFORM_WINDOWS
	#include "real/platform/windows/windows_time.hpp"
#else
	#error Unsupported platform!
#endif

namespace real {

	inline double time() { return real::platform::time(); };
}

#endif //REAL_TIME
