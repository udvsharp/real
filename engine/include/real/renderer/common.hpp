// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_RENDERER_COMMON
#define REAL_RENDERER_COMMON

#include "real/core.hpp"
#include "real/logger.hpp"

namespace real {

	enum class shader_data_t : uint32_t {
		none = 0,
		vec, vec2, vec3, vec4,
		mat3, mat4,
		ivec, ivec2, ivec3, ivec4,
		bvec, bvec2, bvec3, bvec4,
	};

	[[nodiscard]] static constexpr uint32_t sizeofsdt(shader_data_t type) noexcept {
		switch (type) {
			case shader_data_t::vec   : return 4;
			case shader_data_t::vec2  : return 4 * 2;
			case shader_data_t::vec3  : return 4 * 3;
			case shader_data_t::vec4  : return 4 * 4;
			case shader_data_t::mat3  : return 4 * 3 * 3;
			case shader_data_t::mat4  : return 4 * 4 * 4;
			case shader_data_t::ivec  : return 4;
			case shader_data_t::ivec2 : return 4 * 2;
			case shader_data_t::ivec3 : return 4 * 3;
			case shader_data_t::ivec4 : return 4 * 4;
			case shader_data_t::bvec  : return 1;
			case shader_data_t::bvec2 : return 1 * 2;
			case shader_data_t::bvec3 : return 1 * 3;
			case shader_data_t::bvec4 : return 1 * 4;

			default:
			case shader_data_t::none: REAL_CORE_ERROR("Unsupported data type: {}!", type); return 0;
		}
	}
}

#endif //REAL_RENDERER_COMMON
