// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_TIMESTEP
#define VN_TIMESTEP

#include "version/core.hpp"

namespace vn {
	class VN_API timestep {
	public:
		timestep(float time = 0.0f) : time_{ time } {}

		float seconds() const { return time_; };
		float milliseconds() const { return time_ * 1000.0f; };
	private:
		float time_;
	};
}

#endif //VN_TIMESTEP
