// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_GL_CONVERSIONS
#define VN_GL_CONVERSIONS

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "version/core.hpp"
#include "version/renderer/common.hpp"

namespace vn {
	constexpr GLuint gl_type_from(shader_data_t type) noexcept {
		switch (type) {
			case shader_data_t::vec   : return GL_FLOAT;
			case shader_data_t::vec2  : return GL_FLOAT;
			case shader_data_t::vec3  : return GL_FLOAT;
			case shader_data_t::vec4  : return GL_FLOAT;
			case shader_data_t::mat3  : return GL_FLOAT;
			case shader_data_t::mat4  : return GL_FLOAT;
			case shader_data_t::ivec  : return GL_INT;
			case shader_data_t::ivec2 : return GL_INT;
			case shader_data_t::ivec3 : return GL_INT;
			case shader_data_t::ivec4 : return GL_INT;
			case shader_data_t::bvec  : return GL_BOOL;
			case shader_data_t::bvec2 : return GL_BOOL;
			case shader_data_t::bvec3 : return GL_BOOL;
			case shader_data_t::bvec4 : return GL_BOOL;

			case shader_data_t::none:
			default: VN_CORE_ERROR("Unsupported data type: {}!", type); return 0;
		}
	}
}

#endif //VN_GL_CONVERSIONS
