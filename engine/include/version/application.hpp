// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_APPLICATION
#define VN_APPLICATION

#include <iostream>
#include <utility>
#include <version/event/base_event.hpp>

#include "version/core.hpp"
#include "version/util/singleton.hpp"

namespace vn {
	class VN_API SINGLETON(application) {
	private:
		std::string name_;

		bool is_running_{true};
	public:
		explicit application(std::string name = VN_APPLICATION_DEFAULT_NAME);
		// virtual ~application() = default;

		virtual void run();
		virtual void on_event(const vn::ev &e);
	};

	// To be defined in client
	extern application *create();
}

#endif //VN_APPLICATION
