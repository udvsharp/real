// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_BASE_SHADER
#define VN_BASE_SHADER

#include "version/core.hpp"

namespace vn {
	class VN_API shader {
	public:
		virtual ~shader();

		virtual void add_shader(int64_t type, const std::string &filename) = 0;
		virtual void link() = 0;

		// region Uniforms
		// Floats
		virtual void uniform_float(const std::string &name, glm::f32 value) = 0;
		virtual void uniform_float(const std::string &name, const glm::fvec2 &value) = 0;
		virtual void uniform_float(const std::string &name, const glm::fvec3 &value) = 0;
		virtual void uniform_float(const std::string &name, const glm::fvec4 &value) = 0;
		virtual void uniform_matrix(const std::string &name, const glm::fmat3 &matrix) = 0;
		virtual void uniform_matrix(const std::string &name, const glm::fmat4 &matrix) = 0;

		// Ints
		virtual void uniform_int(const std::string &name, glm::int32 value) = 0;
		virtual void uniform_int(const std::string &name, const glm::ivec2 &value) = 0;
		virtual void uniform_int(const std::string &name, const glm::ivec3 &value) = 0;
		virtual void uniform_int(const std::string &name, const glm::ivec4 &value) = 0;
		// endregion

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

	public:
		static shader *make();
	};
}

#endif //VN_BASE_SHADER
