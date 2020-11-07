// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_EVENT_MOUSE
#define REAL_EVENT_MOUSE

#include "real/event/base_event.hpp"

namespace Real
{

	class MouseEvent : public Event
	{
	public:
		[[nodiscard]] ev_category_t Categories() const override
		{
			return static_cast<ev_category_t>(EventCategory::Mouse);
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

	class MouseBtnPressedEvent : public MouseEvent
	{
	private:
		mouse_btn_t mouseBtn;
	public:
		explicit MouseBtnPressedEvent(mouse_btn_t btn)
				:mouseBtn(btn)
		{};

		[[nodiscard]] mouse_btn_t Button() const
		{ return mouseBtn; }

		[[nodiscard]] EventType Type() const override
		{
			return EventType::MouseBtnPress;
		}

		[[nodiscard]] static EventType StaticType()
		{
			return EventType::MouseBtnPress;
		};

#ifdef REAL_DEBUG
		[[nodiscard]] std::string Name() const override
		{
			return "mouse_btn_press_ev";
		}
#endif
		[[nodiscard]] std::string ToString() const override
		{
			std::stringstream ss;
			ss << "mouse_btn_press_ev: (";
			ss << mouseBtn;
			ss << ")";
			return ss.str();
		}

	};

	class MouseBtnReleasedEvent : public MouseEvent
	{
	private:
		mouse_btn_t mouseBtn;
	public:
		explicit MouseBtnReleasedEvent(mouse_btn_t btn)
				:mouseBtn(btn)
		{};

		[[nodiscard]] mouse_btn_t Button() const
		{ return mouseBtn; }

		[[nodiscard]] EventType Type() const override
		{
			return EventType::MouseBtnRelease;
		}

		[[nodiscard]] static EventType StaticType()
		{
			return EventType::MouseBtnRelease;
		};

#ifdef REAL_DEBUG
		[[nodiscard]] std::string Name() const override
		{
			return "mouse_btn_release_ev";
		}
#endif
		[[nodiscard]] std::string ToString() const override
		{
			std::stringstream ss;
			ss << "mouse_btn_release_ev: (";
			ss << mouseBtn;
			ss << ")";
			return ss.str();
		}

	};

	class MouseMovedEvent : public MouseEvent
	{
	private:
		mouse_position_t xPos, yPos;
	public:
		MouseMovedEvent(mouse_position_t x, mouse_position_t y)
				:xPos(x), yPos(y)
		{}

		[[nodiscard]] mouse_position_t X() const
		{ return xPos; }
		[[nodiscard]] mouse_position_t Y() const
		{ return yPos; }

		[[nodiscard]] EventType Type() const override
		{
			return EventType::MouseMove;
		}

		[[nodiscard]] static EventType StaticType()
		{
			return EventType::MouseMove;
		};

#ifdef REAL_DEBUG
		[[nodiscard]] std::string Name() const override
		{
			return "mouse_move_ev";
		}
#endif
		[[nodiscard]] std::string ToString() const override
		{
			std::stringstream ss;
			ss << "mouse_move_ev: (";
			ss << xPos << ", " << yPos;
			ss << ")";
			return ss.str();
		}

	};

	class MouseScrolledEvent : public MouseEvent
	{
	public:
		MouseScrolledEvent(mouse_position_t x_offset, mouse_position_t y_offset)
				:xOffset(x_offset),
				 yOffset(y_offset)
		{}

		[[nodiscard]] mouse_position_t XOffset() const
		{ return xOffset; }
		[[nodiscard]] mouse_position_t YOffset() const
		{ return yOffset; }

		[[nodiscard]] EventType Type() const override
		{
			return EventType::MouseScroll;
		}

		[[nodiscard]] static EventType StaticType()
		{
			return EventType::MouseScroll;
		};

#ifdef REAL_DEBUG
		[[nodiscard]] std::string Name() const override
		{
			return "mouse_scroll_ev";
		}
#endif

		[[nodiscard]] std::string ToString() const override
		{
			std::stringstream ss;
			ss << "mouse_btn_press_ev: (";
			ss << xOffset << ", " << yOffset;
			ss << ")";
			return ss.str();
		}
	private:
		mouse_position_t xOffset;
		mouse_position_t yOffset;
	};
}

#endif //REAL_EVENT_MOUSE
