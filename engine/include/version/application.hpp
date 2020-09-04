// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_APPLICATION
#define VN_APPLICATION

#include <iostream>
#include <utility>
#include <memory>

#include "version/event.hpp"
#include "version/core.hpp"
#include "version/window.hpp"
#include "version/input.hpp"
#include "version/layer_stack.hpp"
#include "version/renderer.hpp"
#include "version/util/singleton.hpp"

namespace vn {
	class VN_API SINGLETON(application) {
	private:
		std::string name_;

		std::unique_ptr<vn::window> window_;
		std::unique_ptr<vn::input> input_;

		layer_stack layers_;
		bool is_running_{true};

		// Rendering
		std::shared_ptr<vn::vertex_array> vao_;
		std::shared_ptr<vn::vertex_buffer> vbo_;
		std::shared_ptr<vn::index_buffer> ibo_;
		std::shared_ptr<vn::shader> shader_;
	public:
		explicit application(std::string name = VN_APPLICATION_DEFAULT_NAME);
		// virtual ~application() = default;

		[[nodiscard]] inline layer_stack &layers() noexcept { return this->layers_; }
		[[nodiscard]] inline window &window() const noexcept { return *(this->window_); }

		void run();
	protected:
		virtual void on_event(ev &e);
		virtual void tick();
	private:
		void on_window_close(window_close_ev &event);
	};

	// To be defined in client
	extern application *create();
}

#endif //VN_APPLICATION
