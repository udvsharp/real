// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_WINDOWS_INPUT
#define VN_WINDOWS_INPUT

#include "version/core.hpp"
#include "version/input/base_input.hpp"

namespace vn::platform {
    class VN_API input : public ::vn::input {
    public:
        virtual ~input() {}

        bool is_key_pressed(key_code keycode) override;
        bool is_mouse_btn_pressed(mouse_btn_t mouse_btn) override;

        std::pair<mouse_position_t, mouse_position_t> mouse_position() override;
        mouse_position_t mouse_x() override;
        mouse_position_t mouse_y() override;
    };
}

#endif //VN_WINDOWS_INPUT
