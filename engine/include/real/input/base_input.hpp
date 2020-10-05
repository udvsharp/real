// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_INPUT_BASE
#define REAL_INPUT_BASE

#include "real/core.hpp"
#include "real/keycode.hpp"
#include "real/util/singleton.hpp"

namespace real {
    class REAL_API SINGLETON(input) {
    public:
        virtual ~input() = default;

        virtual bool is_key_pressed(key_code keycode) = 0;
        virtual bool is_mouse_btn_pressed(mouse_btn_t mouse_btn) = 0;

        virtual std::pair<mouse_position_t, mouse_position_t> mouse_position() = 0;
        virtual mouse_position_t mouse_x() = 0;
        virtual mouse_position_t mouse_y() = 0;

        static input *make();
    };
}

#endif //REAL_INPUT_BASE
