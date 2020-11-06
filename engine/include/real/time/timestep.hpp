// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_TIMESTEP
#define REAL_TIMESTEP

#include "real/core.hpp"

namespace Real {
	class REAL_API Timestep {
	public:
		Timestep(double time = 0.0f) :time_{ time } {}

		[[nodiscard]] float seconds() const { return time_; };
		[[nodiscard]] float milliseconds() const { return time_ * 1000.0f; };
	private:
		double time_;
	};
}

#endif //REAL_TIMESTEP
