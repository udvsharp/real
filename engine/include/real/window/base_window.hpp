// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_WINDOW_BASE
#define REAL_WINDOW_BASE

#include "real/time/timestep.hpp"

#include "real/core.hpp"
#include "real/event.hpp"
#include "real/renderer.hpp"

namespace real {

	using ev_callback_t = std::function<void(ev &)>;

	namespace platform {
		// To be defined per platform
		struct window_data;
	}

	struct window_props {
		std::string title;
		window_dimension_t width;
		window_dimension_t height;

		explicit window_props(std::string title = REAL_DEFAULT_WINDOW_TITLE,
		                      window_dimension_t width = REAL_DEFAULT_WINDOW_WIDTH,
		                      window_dimension_t height = REAL_DEFAULT_WINDOW_HEIGHT)
				: title(std::move(title)), width(width), height(height) {}
	};

	class REAL_API window {
	public:
		virtual ~window();

		virtual void on_update(timestep ts);

		virtual void init() = 0;

		[[nodiscard]] virtual window_dimension_t width() const = 0;
		[[nodiscard]] virtual window_dimension_t height() const = 0;

		virtual void ev_callback(const ev_callback_t &callback) = 0;
		virtual void vsync(bool enabled) = 0;
		[[nodiscard]] virtual bool is_v_sync() const = 0;

		virtual void *native() const = 0;
		virtual rendering_context *context() const = 0;

		// Generates window depending on platform
		static window *make(const window_props &props);
	};
}

#endif //REAL_WINDOW_BASE
