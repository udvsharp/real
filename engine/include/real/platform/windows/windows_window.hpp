// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_WINDOWS_WINDOW
#define REAL_WINDOWS_WINDOW

#include "real/time/timestep.hpp"

// TODO: remove api dependency completely
#include "real/api/gl/gl_headers.hpp"

#include "real/core.hpp"
#include "real/window/base_window.hpp"

namespace Real::Platform
{
	struct WindowData
	{
		std::string title;
		::Real::window_dimension_t width;
		::Real::window_dimension_t height;
		bool isVSync;
		event_callback_t ev_callback;

		explicit WindowData(
				std::string title = REAL_DEFAULT_WINDOW_TITLE,
				window_dimension_t width = REAL_DEFAULT_WINDOW_WIDTH,
				window_dimension_t height = REAL_DEFAULT_WINDOW_HEIGHT,
				bool is_v_sync = REAL_DEFAULT_WINDOW_V_SYNC,
				event_callback_t callback = nullptr
		)
				:title(std::move(title)), width(width), height(height),
				 isVSync(is_v_sync),
				 ev_callback(std::move(callback))
		{}

		explicit WindowData(const ::Real::WindowProperties& props,
				bool is_v_sync = REAL_DEFAULT_WINDOW_V_SYNC,
				event_callback_t callback = nullptr)
				:title { props.title }, width { props.width }, height { props.height },
				 isVSync { is_v_sync },
				 ev_callback { std::move(callback) }
		{}
	};

	class REAL_API Window : public ::Real::Window
	{
	public:
		explicit Window(WindowData data);
		explicit Window(const WindowProperties& props)
				:Window(WindowData { props })
		{};

		~Window() override;

		void Init() override;

		[[nodiscard]] window_dimension_t Width() const noexcept override
		{ return windowData.width; };
		[[nodiscard]] window_dimension_t Height() const noexcept override
		{ return windowData.height; };
		[[nodiscard]] bool IsVSync() const noexcept override
		{ return windowData.isVSync; }

		[[nodiscard]] void* Native() const noexcept override
		{ return nativeWindow; }
		[[nodiscard]] RenderingContext* Context() const noexcept override
		{ return renderingContext; };

		void EventCallback(const event_callback_t& callback) override;
		void VSync(bool enabled) override;

		void OnUpdate(Timestep ts) override;
	private:
		// Maybe this should be virtual?
		// void init();
		// void shutdown();

		void VSyncNative(bool enabled);
	private:
		// TODO: create window using Win32 API
		GLFWwindow* nativeWindow;
		RenderingContext* renderingContext;
		WindowData windowData;
	};
}

#endif //REAL_WINDOWS_WINDOW
