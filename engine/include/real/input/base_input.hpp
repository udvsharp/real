// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_INPUT_BASE
#define REAL_INPUT_BASE

#include "real/core.hpp"
#include "real/keycode.hpp"
#include "real/util/singleton.hpp"

namespace Real
{
	class REAL_API SINGLETON(Input)
	{
	public:
		virtual ~Input() = default;

		virtual bool IsKeyPressed(KeyCode keycode) = 0;
		virtual bool IsMouseBtnPressed(mouse_btn_t mouseBtn) = 0;

		virtual std::pair<mouse_position_t, mouse_position_t> MousePosition() = 0;
		virtual mouse_position_t MouseX() = 0;
		virtual mouse_position_t MouseY() = 0;

		static Real::Scope<Input> Make();
	};
}

#endif //REAL_INPUT_BASE
