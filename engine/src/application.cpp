// Copyright (c) 2020 udv. All rights reserved.

#include "real/application.hpp"

namespace real {

	application::application(std::string name)
			: singleton<application>{},
			  name_{std::move(name)} {

		// Setup systems
		window_props props{};
		window_.reset(window::make(props));
		input_.reset(input::make());

		window_->ev_callback([this](ev &e) {
			application::on_event(e);
		});
	}

	void application::init() {
		window_->init();
	}

	void application::run() {
		REAL_CORE_TRACE("Application is running!");

		while (is_running_) {
			float time = real::time();
			timestep timestep = time - frametime_;
			frametime_ = time;

			render_command::clear_color({ 0.1f, 0.1f, 0.1f, 1.0f });
			render_command::clear();

			render(timestep);

			for (auto *layer : layers_) {
				layer->update(timestep);
			}

			window_->on_update(timestep);
			update(timestep);
		}

		REAL_CORE_TRACE("Closing application;");
	}

	void application::render(timestep ts) {}

	void application::update(timestep ts) {}

	void application::on_event(ev &e) {
		// REAL_CORE_TRACE("Got event: {0}", e);

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

	float application::time() const {
		return glfwGetTime();
	}

	void application::on_window_close(window_close_ev &e) {
		this->is_running_ = false;
	}
}

