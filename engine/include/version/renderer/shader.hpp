// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_SHADER
#define VN_SHADER

#include <string>
#include <fstream>
#include <iostream>

#include <glm/glm.hpp>

#include "version/core.hpp"
#include "version/logger.hpp"
#include "version/api/gl/gl_headers.hpp"

// TODO: abstract api
namespace vn {
	class VN_API shader {
	private:
		GLuint id_;

	private:
		static void checkhandle_program_error(GLuint id, GLenum action);
		static void checkhandle_shader_error(GLuint id, GLenum action);

		static std::string read_file(const std::string &filepath);

	public:
		shader();
		shader(std::string &&vertex_filename, std::string &&fragment_filename);

		void uniform(const std::string &name, const glm::mat4 &matrix);

		void bind() const;
		void unbind() const;
	};
}

#endif //VN_SHADER
