// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_LAYER_BASE
#define REAL_LAYER_BASE

#include <string>
#include "real/time/timestep.hpp"

#include "real/core.hpp"
#include "real/event.hpp"

namespace real {
	class REAL_API layer {
	private:
#ifdef REAL_DEBUG
		std::string name_;
#endif
	public:
		layer() = default;
#ifdef REAL_DEBUG
		explicit layer(std::string name);
#endif

		virtual void attach();
		virtual void detach();
		virtual void update(timestep ts);
		virtual void handle_event(ev& e);
	};
}

#endif //REAL_LAYER_BASE