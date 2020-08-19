// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_APPLICATION
#define VN_APPLICATION

#include <iostream>
#include <utility>
#include <version/event/base_event.hpp>

#include "version/core.hpp"
#include "version/layer_stack.hpp"
#include "version/util/singleton.hpp"

namespace vn {
	class VN_API SINGLETON(application) {
	private:
		std::string name_;

		layer_stack layers_;
		bool is_running_{true};
	public:
		explicit application(std::string name = VN_APPLICATION_DEFAULT_NAME);
		// virtual ~application() = default;

		[[nodiscard]] inline layer_stack layers() const noexcept { return this->layers_; }

		void run();
		virtual void tick();
		virtual void on_event(ev &e);
	private:
		void on_window_close(window_close_ev &event);
	};

	// To be defined in client
	extern application *create();
}

#endif //VN_APPLICATION
