// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_WINDOWS_WINDOW
#define REAL_WINDOWS_WINDOW

#include <utility>
#include "real/time/timestep.hpp"

// TODO: remove api dependency completely
#include "real/api/gl/gl_headers.hpp"

#include "real/core.hpp"
#include "real/window/base_window.hpp"

namespace real::platform {
	struct window_data {
		std::string title;
		::real::window_dimension_t width;
		::real::window_dimension_t height;
		bool is_v_sync;
		ev_callback_t ev_callback;

		explicit window_data(
				std::string title = REAL_DEFAULT_WINDOW_TITLE,
				window_dimension_t width = REAL_DEFAULT_WINDOW_WIDTH,
				window_dimension_t height = REAL_DEFAULT_WINDOW_HEIGHT,
				bool is_v_sync = REAL_DEFAULT_WINDOW_V_SYNC,
				ev_callback_t callback = nullptr
		)
				: title(std::move(title)), width(width), height(height), is_v_sync(is_v_sync),
				  ev_callback(std::move(callback)) {}

		explicit window_data(const ::real::window_props &props, bool is_v_sync = REAL_DEFAULT_WINDOW_V_SYNC,
		                     ev_callback_t callback = nullptr)
				: title(props.title), width(props.width), height(props.height), is_v_sync(is_v_sync),
				  ev_callback(std::move(callback)) {}
	};

	class REAL_API window : public ::real::window {
	public:
		explicit window(window_data data);
		explicit window(const window_props &props) : window(window_data{props}) {};

		~window() override;

		void init() override;

		[[nodiscard]] inline window_dimension_t width() const noexcept override { return data_.width; };
		[[nodiscard]] inline window_dimension_t height() const noexcept override { return data_.height; };
		[[nodiscard]] inline bool is_v_sync() const noexcept override { return data_.is_v_sync; }

		[[nodiscard]] inline void *native() const noexcept override { return native_window_; }
		[[nodiscard]] rendering_context *context() const noexcept override { return rendering_context_; };

		void ev_callback(const ev_callback_t &callback) override;
		void vsync(bool enabled) override;

		void on_update(timestep ts) override;
	private:
		// Maybe this should be virtual?
		// void init();
		// void shutdown();

		void vsync_native(bool enabled);
	private:
		// TODO: create window using Win32 API
		GLFWwindow *native_window_;
		rendering_context *rendering_context_;
		window_data data_;
	};
}

#endif //REAL_WINDOWS_WINDOW
