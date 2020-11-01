// Copyright (c) 2020 udv. All rights reserved.



#include "real/layer/base_layer.hpp"
#include "real/logger.hpp"

namespace real {

	void layer::attach() {
		REAL_CORE_TRACE("Attached layer.");
	}

	void layer::detach() {
		REAL_CORE_TRACE("Detached layer.");
	}

	void layer::update(timestep ts) {

	}

	void layer::handle_event(ev &e) {

	}

#ifdef REAL_DEBUG
	layer::layer(std::string name)
			: name_{ std::move(name) } {}
#endif
}
