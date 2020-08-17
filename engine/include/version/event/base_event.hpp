// Copyright (c) 2020 udv. All rights reserved.

#ifndef VERSION_BASE_EVENT
#define VERSION_BASE_EVENT

#ifdef VN_DEBUG

#include <string> // For event names

#endif

#include <functional>
#include <utility>
#include <type_traits>
#include <ostream>
#include <sstream>

#include "version/core.hpp"

namespace vn {

    using ev_category_t = int;

    enum class ev_type {
        none = 0,

        // category_window types
        window_close, window_resize, window_focus, window_unfocus, window_move,

        // key types
        key_pressed, key_released, key_typed,

        // category_mouse types
        mouse_btn_press, mouse_btn_release, mouse_move, mouse_scroll,
    };

    enum class ev_category : ev_category_t {
        category_none      = 0,
        category_window    = bit(1u),
        category_input     = bit(2u),
        category_mouse     = bit(3u),
        category_mouse_btn = bit(4u),
    };

    class ev {
        friend class ev_dispatcher;

        friend std::ostream &operator<<(std::ostream &os, const ev &ev);
    public:
        [[nodiscard]] virtual inline ev_category_t categories() const = 0;
        [[nodiscard]] virtual inline ev_type type() const = 0;

        [[nodiscard]] inline bool handled() const { return _handled; }

#ifdef VN_DEBUG
        [[nodiscard]] virtual std::string name() const = 0;
        [[nodiscard]] virtual std::string to_string() const { return name(); }
#else
        [[nodiscard]] virtual std::string to_string() const { return "event"; }
#endif

        [[nodiscard]] inline bool has_category(ev_category c) const {
            return static_cast<bool>(static_cast<int>(c) & categories());
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
        static decltype (U::static_type()) detect(const U &);

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

#endif //VERSION_BASE_EVENT