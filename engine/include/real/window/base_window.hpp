// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_WINDOW_BASE
#define REAL_WINDOW_BASE

#include "real/time/timestep.hpp"

#include "real/core.hpp"
#include "real/event.hpp"
#include "real/renderer.hpp"

namespace Real
{

	using event_callback_t = std::function<void(Event&)>;

	namespace Platform
	{
		// To be defined per platform
		struct WindowData;
	}

	struct WindowProperties
	{
		std::string title;
		window_dimension_t width;
		window_dimension_t height;

		explicit WindowProperties(std::string title = REAL_DEFAULT_WINDOW_TITLE,
				window_dimension_t width = REAL_DEFAULT_WINDOW_WIDTH,
				window_dimension_t height = REAL_DEFAULT_WINDOW_HEIGHT)
				:title { std::move(title) }, width { width }, height { height }
		{}
	};

	class REAL_API Window
	{
	public:
		virtual ~Window();

		virtual void OnUpdate(Timestep ts);

		virtual void Init() = 0;

		[[nodiscard]] virtual window_dimension_t Width() const = 0;
		[[nodiscard]] virtual window_dimension_t Height() const = 0;

		virtual void EventCallback(const event_callback_t& callback) = 0;
		virtual void VSync(bool enabled) = 0;
		[[nodiscard]] virtual bool IsVSync() const = 0;

		virtual void* Native() const = 0;
		virtual RenderingContext* Context() const = 0;

		// Generates window depending on platform
		static Real::Scope<Window> Make(const WindowProperties& props);
	};
}

#endif //REAL_WINDOW_BASE
