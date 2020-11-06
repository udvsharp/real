// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_WINDOWS_INPUT
#define REAL_WINDOWS_INPUT

#include "real/core.hpp"
#include "real/input/base_input.hpp"

namespace Real::Platform
{
	class REAL_API Input : public ::Real::Input
	{
	public:
		~Input() override = default;

		bool IsKeyPressed(KeyCode keycode) override;
		bool IsMouseBtnPressed(mouse_btn_t mouse_btn) override;

		std::pair<mouse_position_t, mouse_position_t> MousePosition() override;
		mouse_position_t MouseX() override;
		mouse_position_t MouseY() override;
	};
}

#endif //REAL_WINDOWS_INPUT
