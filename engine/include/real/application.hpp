// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_APPLICATION
#define REAL_APPLICATION

#include <memory>

#include "real/event.hpp"
#include "real/core.hpp"
#include "real/window.hpp"
#include "real/input.hpp"
#include "real/layer_stack.hpp"
#include "real/renderer.hpp"
#include "real/time.hpp"
#include "real/util/singleton.hpp"

namespace real {
	class REAL_API SINGLETON(application) {
	public:
		explicit application(std::string name = REAL_APPLICATION_DEFAULT_NAME);
		// virtual ~application() = default;

		[[nodiscard]] inline layer_stack &layers() noexcept { return this->layers_; }
		[[nodiscard]] inline window &window() const noexcept { return *(this->window_); }

		double time() const;
		virtual void init();
		void run();
	protected:
		virtual void render(timestep ts);
		virtual void update(timestep ts);
		virtual void on_event(ev &e);
	private:
		void on_window_close(window_close_ev &event);
	private:
		std::string name_;

		real::scoped_ptr<real::window> window_;
		real::scoped_ptr<real::input> input_;

		layer_stack layers_;

		bool is_running_{ true };

		float frametime_ = 0.0f;
	};

	// To be defined in client
	extern application *create();
}

#endif //REAL_APPLICATION
