// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_CORE
#define VN_CORE

// region Configured By CMake
// region Export Macros
#include "version/core-export.hpp"
// endregion
// region Compilers
#include "version/core-compiler.hpp"
// endregion
// endregion
// region Macros
// region Values
#define VN_APPLICATION_DEFAULT_NAME "The Version"
#define VN_DEFAULT_WINDOW_HEIGHT 720
#define VN_DEFAULT_WINDOW_WIDTH 1280
#define VN_DEFAULT_WINDOW_TITLE "Version Engine"
#define VN_DEFAULT_WINDOW_V_SYNC true
// endregion
// region util
#include <cassert>
#define vn_assert(expr, msg) assert(expr && msg)
// endregion
// endregion
// region Core global functions
#include <cstdint>

namespace vn {
	// region types
	// TODO: correct types
	using keycode_t = int;

	using mouse_btn_t = int;
	using mouse_position_t = int;

	using window_dimension_t = int;
	using window_position_t = int;
	// endregion
	//region util
	constexpr uint16_t bit(uint16_t x) {
		return static_cast<uint16_t>(1u << x);
	}
	// endregion
}
// endregion

#endif //VN_CORE