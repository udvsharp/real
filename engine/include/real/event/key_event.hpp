// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_EVENT_KEY
#define REAL_EVENT_KEY

#include "real/event/base_event.hpp"

namespace real {
	class key_ev : public ev {
	public:
		[[nodiscard]] inline ev_category_t categories() const override {
			return static_cast<ev_category_t>(ev_category::input);
		}

		[[nodiscard]] ev_type type() const override {
			return ev_type::none;
		}

		[[nodiscard]] static ev_type static_type() {
			return ev_type::none;
		};
	};

	class key_press_ev : public key_ev {
	private:
		keycode_t btn_;
	public:
		explicit key_press_ev(keycode_t btn) : btn_(btn) {};

		[[nodiscard]] mouse_btn_t key_code() const { return btn_; }

		[[nodiscard]] ev_type type() const override {
			return ev_type::key_pressed;
		}

		[[nodiscard]] static ev_type static_type() {
			return ev_type::key_pressed;
		};
#ifdef REAL_DEBUG
		[[nodiscard]] std::string name() const override {
			return "key_press_ev";
		}
#endif
		[[nodiscard]] std::string to_string() const override {
			std::stringstream ss;
			ss << "key_press_ev: (";
			ss << btn_;
			ss << ")";
			return ss.str();
		}

	};

	class key_release_ev : public key_ev {
	private:
		keycode_t btn_;
	public:
		explicit key_release_ev(keycode_t btn) : btn_(btn) {};

		[[nodiscard]] mouse_btn_t key_code() const { return btn_; }

		[[nodiscard]] ev_type type() const override {
			return ev_type::key_released;
		}

		[[nodiscard]] static ev_type static_type() {
			return ev_type::key_released;
		};

#ifdef REAL_DEBUG
		[[nodiscard]] std::string name() const override {
			return "key_release_ev";
		}
#endif
		[[nodiscard]] std::string to_string() const override {
			std::stringstream ss;
			ss << "key_release_ev: (";
			ss << btn_;
			ss << ")";
			return ss.str();
		}

	};

	class key_typed_ev : public key_ev {
	private:
		keycode_t keycode_;
		keycode_t repeat_count_ = 0;
	public:
		explicit key_typed_ev(keycode_t btn) : keycode_(btn) {};

		[[nodiscard]] mouse_btn_t key_code() const { return keycode_; }
		[[nodiscard]] mouse_btn_t repeats() const { return repeat_count_; }

		[[nodiscard]] ev_type type() const override {
			return ev_type::key_typed;
		}

		[[nodiscard]] static ev_type static_type() {
			return ev_type::key_typed;
		};

#ifdef REAL_DEBUG
		[[nodiscard]] std::string name() const override {
			return "key_typed_ev";
		}
#endif
		[[nodiscard]] std::string to_string() const override {
			std::stringstream ss;
			ss << "key_typed_ev: (";
			ss << keycode_ << ", " << repeat_count_;
			ss << ")";
			return ss.str();
		}

	};
}

#endif //REAL_EVENT_KEY
