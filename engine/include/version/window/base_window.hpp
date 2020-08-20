// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_BASE_WINDOW
#define VN_BASE_WINDOW

#include <string>
#include <utility>
#include <functional>

#include "version/core.hpp"
#include "version/event.hpp"
#include "version/renderer.hpp"

namespace vn {

	using ev_callback_t = std::function<void(ev & )>;

	namespace platform {
		// To be defined per platform
		struct window_data;
	}

	struct window_props {
		std::string title;
		window_dimension_t width;
		window_dimension_t height;

		explicit window_props(std::string title = VN_DEFAULT_WINDOW_TITLE,
		                      window_dimension_t width = VN_DEFAULT_WINDOW_WIDTH,
		                      window_dimension_t height = VN_DEFAULT_WINDOW_HEIGHT)
				: title(std::move(title)), width(width), height(height) {}
	};

	class VN_API window {
	public:
		virtual ~window();

		virtual void on_update();

		[[nodiscard]] virtual window_dimension_t width() const = 0;
		[[nodiscard]] virtual window_dimension_t height() const = 0;

		virtual void set_ev_callback(const ev_callback_t &callback) = 0;
		virtual void vsync(bool enabled) = 0;
		[[nodiscard]] virtual bool is_v_sync() const = 0;

		virtual void *native() const = 0;
		virtual rendering_context *context() const = 0;

		// Generates window depending on platform
		static window *make(const window_props &props);
	};
}

#endif //VN_BASE_WINDOW
