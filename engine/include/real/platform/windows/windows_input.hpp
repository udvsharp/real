// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_WINDOWS_INPUT
#define REAL_WINDOWS_INPUT

#include "real/core.hpp"
#include "real/input/base_input.hpp"

namespace real::platform {
    class REAL_API input : public ::real::input {
    public:
        virtual ~input() {}

        bool is_key_pressed(key_code keycode) override;
        bool is_mouse_btn_pressed(mouse_btn_t mouse_btn) override;

        std::pair<mouse_position_t, mouse_position_t> mouse_position() override;
        mouse_position_t mouse_x() override;
        mouse_position_t mouse_y() override;
    };
}

#endif //REAL_WINDOWS_INPUT
