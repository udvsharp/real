// Copyright (c) 2020 udv. All rights reserved.

#include "version/event/base_event.hpp"
#include "version/application.hpp"

namespace vn {
	DEFINE_SINGLETON_INSTANCE(application);

	application::application(std::string name)
			: singleton<application>{},
			  name_{std::move(name)} {}

	void application::run() {
		while (is_running_);
	}

	void application::on_event(const ev &e) {

	}
}

