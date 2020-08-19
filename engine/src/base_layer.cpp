// Copyright (c) 2020 udv. All rights reserved.

#include <utility>

#include "version/layer/base_layer.hpp"
#include "version/logger.hpp"

namespace vn {

	void layer::attach() {
		VN_CORE_TRACE("Attached layer.");
	}

	void layer::detach() {
		VN_CORE_TRACE("Detached layer.");
	}

	void layer::update() {

	}

	void layer::handle_event(ev &e) {

	}

#ifdef VN_DEBUG
	layer::layer(std::string name)
			: name_{std::move(name)} {}
#endif
}
