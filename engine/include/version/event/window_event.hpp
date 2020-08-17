// Copyright (c) 2020 udv. All rights reserved.

#ifndef VERSION_WINDOW_EVENT
#define VERSION_WINDOW_EVENT

#include <sstream>

#include "version/event/base_event.hpp"

namespace vn {

    class window_ev : public ev {
    public:
        [[nodiscard]] inline ev_category_t categories() const override {
            return static_cast<ev_category_t>(ev_category::category_window);
        }

        [[nodiscard]] ev_type type() const override {
            return ev_type::none;
        }

        [[nodiscard]] static ev_type static_type() {
            return ev_type::none;
        };
    };

    class window_close_ev : public window_ev {
    public:
        window_close_ev() = default;

        [[nodiscard]] ev_type type() const override {
            return ev_type::window_close;
        }

        [[nodiscard]] static ev_type static_type() {
            return ev_type::window_close;
        };

#ifdef VN_DEBUG
        [[nodiscard]] std::string name() const override {
            return "window_close_ev";
        }
#endif
        [[nodiscard]] std::string to_string() const override {
            return "window_close_ev";
        }

    };

    class window_resize_ev : public window_ev {
    private:
        window_dimension_t w_, h_;
    public:
        window_resize_ev(window_dimension_t w, window_dimension_t h) : w_(w), h_(h) {}

        [[nodiscard]] mouse_btn_t width() const { return w_; }
        [[nodiscard]] mouse_btn_t height() const { return h_; }

        [[nodiscard]] ev_type type() const override {
            return ev_type::window_resize;
        }

        [[nodiscard]] static ev_type static_type() {
            return ev_type::window_resize;
        };

#ifdef VN_DEBUG
        [[nodiscard]] std::string name() const override {
            return "window_resize_ev";
        }
#endif
        [[nodiscard]] std::string to_string() const override {
            std::stringstream ss;
            ss << "window_resize_ev: (";
            ss << w_ << ", " << h_;
            ss << ")";
            return ss.str();
        }

    };

    class window_move_ev : public window_ev {
    private:
        window_position_t x_, y_;
    public:
        window_move_ev(window_position_t x, window_position_t y) : x_(x), y_(y) {}

        [[nodiscard]] mouse_btn_t x() const { return x_; }
        [[nodiscard]] mouse_btn_t y() const { return y_; }

        [[nodiscard]] ev_type type() const override {
            return ev_type::window_move;
        }

        [[nodiscard]] static ev_type static_type() {
            return ev_type::window_move;
        };

#ifdef VN_DEBUG
        [[nodiscard]] std::string name() const override {
            return "window_move_ev";
        }
#endif

        [[nodiscard]] std::string to_string() const override {
            std::stringstream ss;
            ss << "window_move_ev: (";
            ss << x_ << ", " << y_;
            ss << ")";
            return ss.str();
        }

    };

    class window_focus_ev : public window_ev {
    public:
        window_focus_ev() = default;

        [[nodiscard]] ev_type type() const override {
            return ev_type::window_focus;
        }

        [[nodiscard]] static ev_type static_type() {
            return ev_type::window_focus;
        };

#ifdef VN_DEBUG
        [[nodiscard]] std::string name() const override {
            return "window_focus_ev";
        }
#endif

        [[nodiscard]] std::string to_string() const override {
            std::stringstream ss;
            ss << "window_resize_ev";
            return ss.str();
        }

    };

    class window_unfocus_ev : public window_ev {
    public:
        window_unfocus_ev() = default;

        [[nodiscard]] ev_type type() const override {
            return ev_type::window_unfocus;
        }

        [[nodiscard]] static ev_type static_type() {
            return ev_type::window_unfocus;
        };

#ifdef VN_DEBUG
        [[nodiscard]] std::string name() const override {
            return "window_unfocus_ev";
        }
#endif

        [[nodiscard]] std::string to_string() const override {
            std::stringstream ss;
            ss << "window_resize_ev";
            return ss.str();
        }

    };
}

#endif //VERSION_WINDOW_EVENT
