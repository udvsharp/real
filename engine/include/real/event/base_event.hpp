// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_EVENT_BASE
#define REAL_EVENT_BASE

#include <string>
#include <functional>
#include <utility>
#include <type_traits>
#include <sstream>

#include <ostream>

#include "real/core.hpp"

namespace real {

	using ev_type_t = int;
	using ev_category_t = int;

	enum class ev_type : ev_type_t {
		none = 0,

		// category_window types
		window_close, window_resize, window_focus, window_unfocus, window_move,

		// key types
		key_pressed, key_released, key_typed,

		// category_mouse types
		mouse_btn_press, mouse_btn_release, mouse_move, mouse_scroll,
	};

	enum class ev_category : ev_category_t {
		none      = 0,
		window    = bit(1u),
		input     = bit(2u),
		mouse     = bit(3u),
		mouse_btn = bit(4u),
	};

	class ev {
		friend class ev_dispatcher;

		friend std::ostream &operator<<(std::ostream &os, const ev &ev);
	public:
		[[nodiscard]] virtual inline ev_category_t categories() const = 0;
		[[nodiscard]] virtual inline ev_type type() const = 0;

		[[nodiscard]] inline bool handled() const { return _handled; }

#ifdef REAL_DEBUG
		[[nodiscard]] virtual std::string name() const = 0;
		[[nodiscard]] virtual std::string to_string() const { return name(); }
#else
		[[nodiscard]] virtual std::string to_string() const { return "event"; }
#endif

		[[nodiscard]] inline bool has_category(ev_category c) const {
			return static_cast<bool>(static_cast<ev_category_t>(c) & categories());
		}
	protected:
		bool _handled = false;
	};

	template<typename T>
	struct is_event {
#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"
		static int detect(...);

		template<typename U>
		static decltype(U::static_type()) detect(const U &);

		static constexpr bool value = std::is_same<
				ev_type,
				decltype(
				detect(std::declval<
						typename std::enable_if<
								std::is_base_of<ev, T>::value,
								T
						>::type
				>())
				)
		>::value;
#pragma clang diagnostic pop
	};

	class ev_dispatcher {
		template<typename T>
		using ev_function_t = std::function<bool(T &)>;
	public:

		explicit ev_dispatcher(ev *ev) : ev_(ev) {}

		template<typename T>
		bool dispatch(
				ev_function_t<
						typename std::enable_if<is_event<T>::value, T>::type
				> function
		) noexcept {
			if (ev_->type() == T::static_type()) {
				ev_->_handled = function(*((T *) ev_));
				return true;
			}
			return false;
		}

	private:
		ev *ev_;
	};

	inline std::ostream &operator<<(std::ostream &os, const ev &ev) {
		os << ev.to_string() << ", handled: " << ev._handled;
		return os;
	}
}

#endif //REAL_EVENT_BASE