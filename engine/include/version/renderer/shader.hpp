// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_SHADER
#define VN_SHADER

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include <glm/glm.hpp>

#include "version/core.hpp"
#include "version/logger.hpp"
#include "version/api/gl/gl_headers.hpp"

// TODO: abstract api
namespace vn {
	class VN_API shader {
	private:
		GLuint program_id_;
		std::vector<GLuint> shaders_;
	private:
		//region Helpers
		static std::string read_file(const std::string &filepath);

		static void checkhandle_program_error(GLuint id, GLenum action);
		static void checkhandle_shader_error(GLuint id, GLenum action);
		//endregion

	public:
		shader();
		shader(std::string &&vertex_filename, std::string &&fragment_filename);

		void add_shader(int64_t type, const std::string& filename);
		void link();

		//region Uniforms
		void uniform(const std::string &name, const glm::mat4 &matrix);
		void uniform(const std::string &name, const glm::vec4 &vector);
		//endregion

		void bind() const;
		void unbind() const;
	};
}

#endif //VN_SHADER
