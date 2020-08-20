// Copyright (c) 2020 udv. All rights reserved.

#include "version/application.hpp"
#include "version/logger.hpp"

namespace vn {

	application::application(std::string name)
			: singleton<application>{},
			  name_{std::move(name)} {

		// Setup systems
		window_props props{};
		window_.reset(window::make(props));
		input_.reset(input::make());

		window_->set_ev_callback([this](ev &e) {
			application::on_event(e);
		});
	}

	void application::tick() {
	}

	void application::run() {
		VN_CORE_TRACE("Application is running!");

		while (is_running_) {
			glClearColor(0, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (auto *layer : layers_) {
				layer->update();
			}

			window_->on_update();
		}

		VN_CORE_TRACE("Closing application;");
	}

	void application::on_event(ev &e) {
		VN_CORE_TRACE("Got event: {0}", e);

		ev_dispatcher dispatcher{&e};
		dispatcher.dispatch<window_close_ev>([this](window_close_ev &event) -> bool {
			this->on_window_close(event);
			return false;
		});

		for (auto it = layers_.end(); it != layers_.begin();) {
			(*--it)->handle_event(e);
			if (e.handled()) {
				break;
			}
		}
	}

	void application::on_window_close(window_close_ev &e) {
		this->is_running_ = false;
	}
}

