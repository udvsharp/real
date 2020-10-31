// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_GL_CONVERSIONS
#define REAL_GL_CONVERSIONS

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "real/core.hpp"
#include "real/renderer/common.hpp"
#include "real/logger.hpp"

namespace real {
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

			default:
			case shader_data_t::none: REAL_CORE_ERROR("Unsupported data type: {}!", type); return 0;
		}
	}

	inline GLenum gl_shader_type_from(std::string_view type) noexcept {
		if (type == "vertex") {
			return GL_VERTEX_SHADER;
		}

		if (type == "fragment") {
			return GL_FRAGMENT_SHADER;
		}

		REAL_CORE_ERROR("Unknown shader type {0}", type);
		return 0;
	}
}

#endif //REAL_GL_CONVERSIONS
