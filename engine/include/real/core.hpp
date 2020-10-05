// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_CORE
#define REAL_CORE

// region Configured By CMake
// region Export Macros
#include "real/core-export.hpp"
// endregion
// region Compilers
#include "real/core-compiler.hpp"
// endregion
// endregion
// region Macros
// region Values
#define REAL_APPLICATION_DEFAULT_NAME "The Version"
#define REAL_DEFAULT_WINDOW_HEIGHT 720
#define REAL_DEFAULT_WINDOW_WIDTH 1280
#define REAL_DEFAULT_WINDOW_TITLE "Version Engine"
#define REAL_DEFAULT_WINDOW_V_SYNC false
// endregion
// region util
#include <cassert>
#define real_assert(expr, msg) assert(expr && msg)
// endregion
// endregion
// region Core global functions
#include <cstdint>

namespace real {
	// region types
	// TODO: correct types
	using keycode_t = int;

	using mouse_btn_t = int;
	using mouse_position_t = int;

	using window_dimension_t = int;
	using window_position_t = int;

	using renderer_id_t = uint32_t;
	// endregion
	//region util
	constexpr uint16_t bit(uint16_t x) {
		return static_cast<uint16_t>(1u << x);
	}
	// endregion
}
// endregion

#endif //REAL_CORE