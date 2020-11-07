// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_EVENT_KEY
#define REAL_EVENT_KEY

#include "real/event/base_event.hpp"

namespace Real
{
	class KeyEvent : public Event
	{
	public:
		[[nodiscard]] ev_category_t Categories() const override
		{
			return static_cast<ev_category_t>(EventCategory::Input);
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

	class KeyPressedEvent : public KeyEvent
	{
	private:
		keycode_t btnKeycode;
	public:
		explicit KeyPressedEvent(keycode_t btn)
				:btnKeycode(btn)
		{};

		[[nodiscard]] mouse_btn_t KeyCode() const
		{ return btnKeycode; }

		[[nodiscard]] EventType Type() const override
		{
			return EventType::KeyPressed;
		}

		[[nodiscard]] static EventType StaticType()
		{
			return EventType::KeyPressed;
		};
#ifdef REAL_DEBUG
		[[nodiscard]] std::string Name() const override
		{
			return "key_press_ev";
		}
#endif
		[[nodiscard]] std::string ToString() const override
		{
			std::stringstream ss;
			ss << "key_press_ev: (";
			ss << btnKeycode;
			ss << ")";
			return ss.str();
		}

	};

	class KeyReleasedEvent : public KeyEvent
	{
	private:
		keycode_t btnKeycode;
	public:
		explicit KeyReleasedEvent(keycode_t btn)
				:btnKeycode(btn)
		{};

		[[nodiscard]] mouse_btn_t KeyCode() const
		{ return btnKeycode; }

		[[nodiscard]] EventType Type() const override
		{
			return EventType::KeyReleased;
		}

		[[nodiscard]] static EventType StaticType()
		{
			return EventType::KeyReleased;
		};

#ifdef REAL_DEBUG
		[[nodiscard]] std::string Name() const override
		{
			return "key_release_ev";
		}
#endif
		[[nodiscard]] std::string ToString() const override
		{
			std::stringstream ss;
			ss << "key_release_ev: (";
			ss << btnKeycode;
			ss << ")";
			return ss.str();
		}

	};

	class KeyTypedEvent : public KeyEvent
	{
	private:
		keycode_t keycode;
		keycode_t repeatCount = 0;
	public:
		explicit KeyTypedEvent(keycode_t btn)
				:keycode(btn)
		{};

		[[nodiscard]] mouse_btn_t KeyCode() const
		{ return keycode; }
		[[nodiscard]] mouse_btn_t Repeats() const
		{ return repeatCount; }

		[[nodiscard]] EventType Type() const override
		{
			return EventType::KeyTyped;
		}

		[[nodiscard]] static EventType StaticType()
		{
			return EventType::KeyTyped;
		};

#ifdef REAL_DEBUG
		[[nodiscard]] std::string Name() const override
		{
			return "key_typed_ev";
		}
#endif
		[[nodiscard]] std::string ToString() const override
		{
			std::stringstream ss;
			ss << "key_typed_ev: (";
			ss << keycode << ", " << repeatCount;
			ss << ")";
			return ss.str();
		}

	};
}

#endif //REAL_EVENT_KEY
