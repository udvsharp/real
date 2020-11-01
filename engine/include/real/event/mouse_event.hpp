// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_EVENT_MOUSE
#define REAL_EVENT_MOUSE

#include "real/event/base_event.hpp"

namespace real {

	class mouse_ev : public ev {
	public:
		[[nodiscard]] inline ev_category_t categories() const override {
			return static_cast<ev_category_t>(ev_category::mouse);
		}

		[[nodiscard]] ev_type type() const override {
			return ev_type::none;
		}

		[[nodiscard]] static ev_type static_type() {
			return ev_type::none;
		};
	};

	class mouse_btn_press_ev : public mouse_ev {
	private:
		mouse_btn_t btn_;
	public:
		explicit mouse_btn_press_ev(mouse_btn_t btn) : btn_(btn) {};

		[[nodiscard]] mouse_btn_t button() const { return btn_; }

		[[nodiscard]] ev_type type() const override {
			return ev_type::mouse_btn_press;
		}

		[[nodiscard]] static ev_type static_type() {
			return ev_type::mouse_btn_press;
		};

#ifdef REAL_DEBUG
		[[nodiscard]] std::string name() const override {
			return "mouse_btn_press_ev";
		}
#endif
		[[nodiscard]] std::string to_string() const override {
			std::stringstream ss;
			ss << "mouse_btn_press_ev: (";
			ss << btn_;
			ss << ")";
			return ss.str();
		}

	};

	class mouse_btn_release_ev : public mouse_ev {
	private:
		mouse_btn_t btn_;
	public:
		explicit mouse_btn_release_ev(mouse_btn_t btn) : btn_(btn) {};

		[[nodiscard]] mouse_btn_t button() const { return btn_; }

		[[nodiscard]] ev_type type() const override {
			return ev_type::mouse_btn_release;
		}

		[[nodiscard]] static ev_type static_type() {
			return ev_type::mouse_btn_release;
		};

#ifdef REAL_DEBUG
		[[nodiscard]] std::string name() const override {
			return "mouse_btn_release_ev";
		}
#endif
		[[nodiscard]] std::string to_string() const override {
			std::stringstream ss;
			ss << "mouse_btn_release_ev: (";
			ss << btn_;
			ss << ")";
			return ss.str();
		}

	};

	class mouse_move_ev : public mouse_ev {
	private:
		mouse_position_t x_, y_;
	public:
		mouse_move_ev(mouse_position_t x, mouse_position_t y) : x_(x), y_(y) {}

		[[nodiscard]] mouse_position_t x() const { return x_; }
		[[nodiscard]] mouse_position_t y() const { return y_; }

		[[nodiscard]] ev_type type() const override {
			return ev_type::mouse_move;
		}

		[[nodiscard]] static ev_type static_type() {
			return ev_type::mouse_move;
		};

#ifdef REAL_DEBUG
		[[nodiscard]] std::string name() const override {
			return "mouse_move_ev";
		}
#endif
		[[nodiscard]] std::string to_string() const override {
			std::stringstream ss;
			ss << "mouse_move_ev: (";
			ss << x_ << ", " << y_;
			ss << ")";
			return ss.str();
		}

	};

	class mouse_scroll_ev : public mouse_ev {
	public:
		mouse_scroll_ev(mouse_position_t x_offset, mouse_position_t y_offset) : x_offset_(
				x_offset),
		                                                                        y_offset_(
				                                                                        y_offset) {}

		[[nodiscard]] mouse_position_t x_offset() const { return x_offset_; }
		[[nodiscard]] mouse_position_t y_offset() const { return y_offset_; }

		[[nodiscard]] ev_type type() const override {
			return ev_type::mouse_scroll;
		}

		[[nodiscard]] static ev_type static_type() {
			return ev_type::mouse_scroll;
		};

#ifdef REAL_DEBUG
		[[nodiscard]] std::string name() const override {
			return "mouse_scroll_ev";
		}
#endif

		[[nodiscard]] std::string to_string() const override {
			std::stringstream ss;
			ss << "mouse_btn_press_ev: (";
			ss << x_offset_ << ", " << y_offset_;
			ss << ")";
			return ss.str();
		}
	private:
		mouse_position_t x_offset_;
		mouse_position_t y_offset_;
	};
}

#endif //REAL_EVENT_MOUSE
