// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_BASE_LAYER
#define VN_BASE_LAYER

#include <string>

#include "version/core.hpp"
#include "version/event.hpp"

namespace vn {
	class VN_API layer {
	private:
#ifdef VN_DEBUG
		std::string name_;
#endif
	public:
		layer() = default;
#ifdef VN_DEBUG
		explicit layer(std::string name);
#endif

		virtual void attach();
		virtual void detach();
		virtual void update();
		virtual void handle_event(ev& e);
	};
}

#endif //VN_BASE_LAYER
