// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_TIME
#define VN_TIME

#include "version/time/base_time.hpp"
#include "version/time/timestep.hpp"

#ifdef VN_PLATFORM_WINDOWS
	#include "version/platform/windows/windows_time.hpp"
#else
	#error Unsupported platform!
#endif


#endif //VN_TIME
