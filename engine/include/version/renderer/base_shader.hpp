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

		//region Uniforms
		virtual void uniform(const std::string &name, const glm::mat4 &matrix) = 0;
		virtual void uniform(const std::string &name, const glm::vec4 &vector) = 0;
		//endregion

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

	public:
		static shader *make();
	};
}

#endif //VN_BASE_SHADER
