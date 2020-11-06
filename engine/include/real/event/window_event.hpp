// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_EVENT_WINDOW
#define REAL_EVENT_WINDOW

#include <sstream>

#include "real/event/base_event.hpp"

namespace Real
{

	class WindowEvent : public Event
	{
	public:
		[[nodiscard]] inline ev_category_t Categories() const override
		{
			return static_cast<ev_category_t>(EventCategory::Window);
		}

		[[nodiscard]] EventType Type() const override
		{
			return EventType::None;
		}

		[[nodiscard]] static EventType StaticType()
		{
			return EventType::None;
		};
	};

	class WindowClosedEvent : public WindowEvent
	{
	public:
		WindowClosedEvent() = default;

		[[nodiscard]] EventType Type() const override
		{
			return EventType::WindowClose;
		}

		[[nodiscard]] static EventType StaticType()
		{
			return EventType::WindowClose;
		};

#ifdef REAL_DEBUG
		[[nodiscard]] std::string Name() const override
		{
			return "window_close_ev";
		}
#endif
		[[nodiscard]] std::string ToString() const override
		{
			return "window_close_ev";
		}

	};

	class WindowResizedEvent : public WindowEvent
	{
	private:
		window_dimension_t width, heigth;
	public:
		WindowResizedEvent(window_dimension_t w, window_dimension_t h)
				:width(w), heigth(h)
		{}

		[[nodiscard]] mouse_btn_t Width() const
		{ return width; }
		[[nodiscard]] mouse_btn_t Height() const
		{ return heigth; }

		[[nodiscard]] EventType Type() const override
		{
			return EventType::WindowResize;
		}

		[[nodiscard]] static EventType StaticType()
		{
			return EventType::WindowResize;
		};

#ifdef REAL_DEBUG
		[[nodiscard]] std::string Name() const override
		{
			return "window_resize_ev";
		}
#endif
		[[nodiscard]] std::string ToString() const override
		{
			std::stringstream ss;
			ss << "window_resize_ev: (";
			ss << width << ", " << heigth;
			ss << ")";
			return ss.str();
		}

	};

	class WindowMovedEvent : public WindowEvent
	{
	private:
		window_position_t xPos, yPos;
	public:
		WindowMovedEvent(window_position_t x, window_position_t y)
				:xPos(x), yPos(y)
		{}

		[[nodiscard]] mouse_btn_t X() const
		{ return xPos; }
		[[nodiscard]] mouse_btn_t Y() const
		{ return yPos; }

		[[nodiscard]] EventType Type() const override
		{
			return EventType::WindowMove;
		}

		[[nodiscard]] static EventType StaticType()
		{
			return EventType::WindowMove;
		};

#ifdef REAL_DEBUG
		[[nodiscard]] std::string Name() const override
		{
			return "window_move_ev";
		}
#endif

		[[nodiscard]] std::string ToString() const override
		{
			std::stringstream ss;
			ss << "window_move_ev: (";
			ss << xPos << ", " << yPos;
			ss << ")";
			return ss.str();
		}

	};

	class WindowFocusedEvent : public WindowEvent
	{
	public:
		WindowFocusedEvent() = default;

		[[nodiscard]] EventType Type() const override
		{
			return EventType::WindowFocus;
		}

		[[nodiscard]] static EventType StaticType()
		{
			return EventType::WindowFocus;
		};

#ifdef REAL_DEBUG
		[[nodiscard]] std::string Name() const override
		{
			return "window_focus_ev";
		}
#endif

		[[nodiscard]] std::string ToString() const override
		{
			std::stringstream ss;
			ss << "window_resize_ev";
			return ss.str();
		}

	};

	class WindowUnfocusedEvent : public WindowEvent
	{
	public:
		WindowUnfocusedEvent() = default;

		[[nodiscard]] EventType Type() const override
		{
			return EventType::WindowUnfocus;
		}

		[[nodiscard]] static EventType StaticType()
		{
			return EventType::WindowUnfocus;
		};

#ifdef REAL_DEBUG
		[[nodiscard]] std::string Name() const override
		{
			return "window_unfocus_ev";
		}
#endif

		[[nodiscard]] std::string ToString() const override
		{
			std::stringstream ss;
			ss << "window_resize_ev";
			return ss.str();
		}

	};
}

#endif //REAL_EVENT_WINDOW
