// Copyright (c) 2020 udv. All rights reserved.

#include "version/event.hpp"
#include "version/application.hpp"
#include "version/logger.hpp"

namespace vn {

	application::application(std::string name)
			: singleton<application>{},
			  name_{std::move(name)} {}

	void application::tick() {
	}

	void application::run() {
		while (is_running_) {
			application::tick();

			for (auto* layer : layers_) {
				layer->update();
			}

		}
	}

	void application::on_event(ev &e) {
		VN_CORE_TRACE("Got event: {0}", e);

		ev_dispatcher dispatcher{&e};
		dispatcher.dispatch<window_close_ev>([this] (window_close_ev& event) -> bool {
			this->on_window_close(event);
			return false;
		});

		for (auto it = layers_.end(); it != layers_.begin(); ) {
			(*--it)->handle_event(e);
			if (e.handled()) {
				break;
			}
		}
	}

	void application::on_window_close(window_close_ev& e) {

	}
}

