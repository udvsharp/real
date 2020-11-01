// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_CORE
#define REAL_CORE

// region Configured By CMake
// Export Macros
#include "real/core-export.hpp"
// Compilers
#include "real/core-compiler.hpp"
// endregion

#define REAL_APPLICATION_DEFAULT_NAME "Real Engine"
#define REAL_DEFAULT_WINDOW_HEIGHT 720
#define REAL_DEFAULT_WINDOW_WIDTH 1280
#define REAL_DEFAULT_WINDOW_TITLE "Real Engine"
#define REAL_DEFAULT_WINDOW_V_SYNC false

#include "real/pch.hpp"
#include "real/assert.hpp"
#include <cassert>
#define real_assert(expr, msg) assert((expr) && (msg))

namespace real {
	// region types
	// Input
	using keycode_t = int32_t;
	using mouse_btn_t = int32_t;
	using mouse_position_t = int32_t;

	// Window
	using window_dimension_t = int32_t;
	using window_position_t = int32_t;

	// Renderer
	using renderer_id_t = uint32_t;
	//// Textures
	using texture_dimension_t = uint32_t;
	// endregion
	//region util
	constexpr uint16_t bit(uint16_t x) {
		return static_cast<uint16_t>(1u << x);
	}
	// endregion
	// region Pointers
	// TODO: make own pointers
	template<typename T>
	using reference = std::shared_ptr<T>;

	template<typename T>
	using scoped_ptr = std::unique_ptr<T>;
	// endregion
}

#endif //REAL_CORE