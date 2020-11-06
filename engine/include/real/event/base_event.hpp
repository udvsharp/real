// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_EVENT_BASE
#define REAL_EVENT_BASE

#include <type_traits>
#include <sstream>

#include <ostream>

#include "real/core.hpp"

namespace Real
{

	using ev_type_t = int32_t;
	using ev_category_t = int32_t;

	enum class EventType : ev_type_t
	{
		None = 0,

		// category_window types
		WindowClose, WindowResize, WindowFocus, WindowUnfocus, WindowMove,

		// key types
		KeyPressed, KeyReleased, KeyTyped,

		// category_mouse types
		MouseBtnPress, MouseBtnRelease, MouseMove, MouseScroll,
	};

	enum class EventCategory : ev_category_t
	{
		None = 0,
		Window = bit(1u),
		Input = bit(2u),
		Mouse = bit(3u),
		MouseBtn = bit(4u),
	};

	class Event
	{
		friend class EventDispatcher;

		friend std::ostream& operator<<(std::ostream& os, const Event& ev);
	public:
		[[nodiscard]] virtual inline ev_category_t Categories() const = 0;
		[[nodiscard]] virtual inline EventType Type() const = 0;

		[[nodiscard]] inline bool IsHandled() const
		{ return handled; }

#ifdef REAL_DEBUG
		[[nodiscard]] virtual std::string Name() const = 0;
		[[nodiscard]] virtual std::string ToString() const
		{ return Name(); }
#else
		[[nodiscard]] virtual std::string ToString() const { return "event"; }
#endif

		[[nodiscard]] inline bool HasCategory(EventCategory c) const
		{
			return static_cast<bool>(static_cast<ev_category_t>(c) & Categories());
		}
	protected:
		bool handled = false;
	};

	template<typename T>
	struct IsEvent
	{
#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"
		static int Detect(...);

		template<typename U>
		static decltype(U::StaticType()) Detect(const U&);

		static constexpr bool value = std::is_same<
				EventType,
				decltype(
				Detect(std::declval<
						typename std::enable_if<std::is_base_of<Event, T>::value, T>::type
				>()))
		>::value;
#pragma clang diagnostic pop
	};

	class EventDispatcher
	{
		template<typename T>
		using ev_function_t = std::function<bool(T&)>;
	public:

		explicit EventDispatcher(Event* ev)
				:event(ev)
		{}

		template<typename T>
		bool Dispatch(
				ev_function_t<
						typename std::enable_if<IsEvent<T>::value, T>::type
				> function
		) noexcept
		{
			if (event->Type() == T::StaticType())
			{
				event->handled = function(*((T*)event));
				return true;
			}
			return false;
		}

	private:
		Event* event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& event)
	{
		os << event.ToString() << ", handled: " << event.handled;
		return os;
	}
}

#endif //REAL_EVENT_BASE